/**********************************文件头部注释************************************/
//
//
//               Copyright (C), 2005-2010, AV Frontier Tech. Co., Ltd.
//
//
// 文件名：        ywevt.c
//
// 创建者：        Maple
//
// 创建时间：    2008.05.05
//
// 文件描述：    事件的文件。
//
// 修改记录：   日       期      作      者       版本      修定
//                       ---------         ---------        -----        -----
//                      2008.05.05         Maple            0.01         新建
//                                                 
/*****************************************************************************************/

/* Includes --------------------------------------------------------------- */
#include <string.h>
#include <stdio.h>

#include "ywdefs.h"
#include "ywos.h"
#include "ywlib.h"
#include "ywevt.h"

/*Module Version Info*/
#define   Ver_Layer                  "HAL"
#define   Ver_name                   "YWEVT"
#define   Ver_Version                "V1.0"

#ifdef DEBUG_TRACE
    #define YWOSTRACE(x) YWOS_Trace x
//#define YWOSTRACE(x)
    #define YWOSASSERT(x)  \
    do{ \
        if(!(x)) \
            YWOS_Trace(YWOS_TRACE_ERROR,"Assertion: \"%s\" failed, in file %s, line %d\n", \
                #x, __FILE__, __LINE__); \
    }while(0)
#else
#define YWOSASSERT(x) 
#define YWOSTRACE(x)
#endif

/* Private Types ------------------------------------------------------ */


/* Private Constants -------------------------------------------------- */

/* 设备handle链表类型*/
typedef struct YWEVTi_HandleList_s
{
    YWLIB_ListHead_T         YWEVTi_HandleList;      
    U32                      DrvHandle;               /*设备句柄*/
    YWLIB_ListHead_T         EventTypeListHead;       /*此设备下的事件类型的链头*/
}YWEVTi_HandleList_T; 


/*事件处理类型链表*/
typedef struct YWEVTi_EventTypeList_s
{
    YWLIB_ListHead_T         YWEVTi_EventTypeList;
    YW_EventType_T           EventType;                /*事件处理类型*/
    YWLIB_ListHead_T         EventFuncListHead;        /*此类型下的实际处理函数的链头*/    
}YWEVTi_EventTypeList_T;


/*事件处理函数链表*/
typedef struct YWEVTi_EventFuncList_s
{
    YWLIB_ListHead_T         YWEVTi_EventFuncList;
    YWEVT_EventPoc_T         EventFuncPoc;            /*事件处理函数句柄*/
    void*                    UserData;                /*用户自定义指针*/
}YWEVTi_EventFuncList_T;
/* Private Variables -------------------------------------------------- */

static BOOL                 YWEVTi_ISInitialized = FALSE;
static YWOS_MutexID_T       MutexEvtLock = 0;

YWLIB_LIST_HEAD(YWEVTi_HANDLE_LIST_NAME);    /*设备句柄链表名字*/

/* Private Macros ----------------------------------------------------- */


/* Private Function prototypes ---------------------------------------- */

static BOOL YWEVTi_SearchHandleList(U32 Handle, YWEVTi_HandleList_T **HandleList)
{
    BOOL                isSearch = FALSE;
    YWLIB_ListHead_T    *HandleListHead;
    YWEVTi_HandleList_T *handleListTemp;
        
    YWOSASSERT(( Handle != 0 ));
    
    YWLIB_ListForEach(HandleListHead, &YWEVTi_HANDLE_LIST_NAME)
    {
        handleListTemp = YWLIB_ListEntry(HandleListHead, YWEVTi_HandleList_T, YWEVTi_HandleList);
        if(handleListTemp->DrvHandle == Handle)
        {
            *HandleList = handleListTemp;
            isSearch = TRUE;            
            break;
        }
    }

    return isSearch;
}

static BOOL YWEVTi_SearchEventTypeList( YW_EventType_T             EventType, 
                                        YWEVTi_EventTypeList_T     **EventTypeList, 
                                        YWLIB_ListHead_T           *EventTypeListHead)
{
    BOOL                       isSearch = FALSE;
    YWLIB_ListHead_T           *TypeList;
    YWEVTi_EventTypeList_T     *EventTypeListTemp;
        
    YWOSASSERT((EventType != 0) || (EventTypeListHead != NULL));
    YWLIB_ListForEach(TypeList, EventTypeListHead)
    {
        EventTypeListTemp = YWLIB_ListEntry(TypeList, YWEVTi_EventTypeList_T, YWEVTi_EventTypeList);
        if (EventTypeListTemp->EventType == EventType)
        {
            *EventTypeList = EventTypeListTemp;
            isSearch = TRUE;     
            break;
        }
    }

    return isSearch;
}


static BOOL YWEVTi_SearchEventFuncList(YWEVT_EventPoc_T  EventFuncPoc, YWEVTi_EventFuncList_T **EventFuncList, YWLIB_ListHead_T *EventFuncListHead)
{
    BOOL                       isSearch = FALSE;
    YWLIB_ListHead_T           *FuncList;
    YWEVTi_EventFuncList_T     *EventFuncListTemp;
        
    YWOSASSERT(( EventFuncPoc != 0 ) || ( EventFuncListHead != NULL ));
    YWLIB_ListForEach(FuncList, EventFuncListHead)
    {
        EventFuncListTemp = YWLIB_ListEntry(FuncList, YWEVTi_EventFuncList_T, YWEVTi_EventFuncList);
        if(EventFuncListTemp->EventFuncPoc == EventFuncPoc)
        {     
            *EventFuncList = EventFuncListTemp;
            isSearch = TRUE;
            break;
        }
    }

    return isSearch;
}

YW_ErrorType_T YWEVT_Init(void)
{
    YW_ErrorType_T          YW_ErrorCode = YW_NO_ERROR;

    YWOSTRACE(( YWOS_TRACE_INFO, "[YWEVT_Init]  evt init!!!...\n" ) );

    if( YWEVTi_ISInitialized )
    {
        YWOSTRACE(( YWOS_TRACE_ERROR, "[ERROR][YWEVT_Init]  evt  is  init!!!...\n"  ));
        return YWEVT_ERROR_ALREADY_INITIALIZED;
    }
    YW_ErrorCode = YWOS_MutexCreate(&MutexEvtLock);
    if( YW_ErrorCode != YW_NO_ERROR )
    {   
         
        YWOSTRACE(( YWOS_TRACE_ERROR, "[ERROR][YWEVT_Init]Create YWOS_MutexCreate MutexEvtLock failed\n" ));
        return YW_ErrorCode;
    }
    
    YWEVTi_ISInitialized = TRUE;

    return YW_ErrorCode;
}

YW_ErrorType_T YWEVT_Term(void)
{
    YW_ErrorType_T          YW_ErrorCode = YW_NO_ERROR;
    YWOSTRACE(( YWOS_TRACE_INFO, "[YWEVT_Term]  evt Term!!!...\n" ) );
    
    if( !YWEVTi_ISInitialized )
    {
        YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWEVT_Term]  evt  is not init!!!...\n" ));
        return YWEVT_ERROR_NO_INITIALIZED;
    }

    /*清空所有链表，释放资源*/
    YWOS_MutexWait(MutexEvtLock, YWOS_WAIT_INFINITY); 
    
    if( !(YWLIB_ListEmpty( &YWEVTi_HANDLE_LIST_NAME) ) )
    {
        YWLIB_ListHead_T         *HandleListHead;
        YWLIB_ListHead_T         *HandleListHeadNext;
        YWEVTi_HandleList_T      *handleListTemp;

        YWLIB_ListForEachSafe( HandleListHead, HandleListHeadNext, &YWEVTi_HANDLE_LIST_NAME )
        {

            YWLIB_ListHead_T           *TypeList,*TypeListNext;
            YWEVTi_EventTypeList_T     *EventTypeListTemp;
            
            handleListTemp = YWLIB_ListEntry( HandleListHead, YWEVTi_HandleList_T, YWEVTi_HandleList);
            
            YWLIB_ListForEachSafe(TypeList, TypeListNext,& ( handleListTemp->EventTypeListHead ) )
            {

                YWLIB_ListHead_T             *FuncList;
                YWLIB_ListHead_T             *FuncListNext;
                YWEVTi_EventFuncList_T       *EventFuncListTemp;

                EventTypeListTemp = YWLIB_ListEntry( TypeList, YWEVTi_EventTypeList_T, YWEVTi_EventTypeList);

                
                YWLIB_ListForEachSafe( FuncList, FuncListNext, &(EventTypeListTemp->EventFuncListHead) )
                {
                    EventFuncListTemp = YWLIB_ListEntry(FuncList, YWEVTi_EventFuncList_T, YWEVTi_EventFuncList);
                    YWLIB_ListDel(FuncList);
                    
                    YW_ErrorCode = YWOS_Free((void *)EventFuncListTemp);
                    if(YW_ErrorCode != YW_NO_ERROR)
                    {
                        YWOSTRACE(( YWOS_TRACE_ERROR,
                                "[ERROR][YWEVT_UnSubscribeEvent] YWOS_Free !!!...\n") );                              
//                        goto RETADDR;
                    }
                }

                YWLIB_ListDel( TypeList );
                    
                YW_ErrorCode = YWOS_Free((void *)EventTypeListTemp );
                if(YW_ErrorCode != YW_NO_ERROR)
                {
                    YWOSTRACE(( YWOS_TRACE_ERROR,
                            "[ERROR][YWEVT_UnSubscribeEvent] YWOS_Free !!!...\n") );                              
//                    goto RETADDR;
                }        
            }
            YWLIB_ListDel( HandleListHead );
                    
            YW_ErrorCode = YWOS_Free((void *)handleListTemp );
            if(YW_ErrorCode != YW_NO_ERROR)
            {
                YWOSTRACE(( YWOS_TRACE_ERROR,
                        "[ERROR][YWEVT_UnSubscribeEvent] YWOS_Free !!!...\n" )); 
//                goto RETADDR;
            }
            
        }

        
    }
    YWOS_MutexSend(MutexEvtLock); 
    /*清空所有链表，释放资源*/
    YWOS_MutexDelete(MutexEvtLock);
    YWEVTi_ISInitialized = FALSE;
    
//RETADDR:    
    return YW_ErrorCode;
}


YW_ErrorType_T YWEVT_SubscribeEvent (U32 DrvHandle,
                                     YW_EventType_T  EventType,
                                     YWEVT_EventPoc_T EventPoc, 
                                     void * UserData)
{

    YW_ErrorType_T              YW_ErrorCode = YW_NO_ERROR;
    YWEVTi_HandleList_T         *HandlelistTemp = NULL, *HandleListExist = NULL, **ppHandleList = NULL;
    YWEVTi_EventTypeList_T      *TypeListTemp   = NULL, *TypeListExist = NULL,   **ppTypeList   = NULL;
    YWEVTi_EventFuncList_T      *FuncListTemp   = NULL, **ppFuncList = NULL;
    BOOL                        isHandleExist = FALSE, isFuncExist = FALSE, isTypeExist = FALSE;
    U32                         ListAddress;

    YWOSTRACE((YWOS_TRACE_INFO, "[YWEVT_SubscribeEvent] DrvHandle = 0x%x  EventType = 0x%x !!!...\n" ,DrvHandle, EventType));
    YWOSASSERT((DrvHandle != 0) || (EventPoc != NULL) || (EventType != 0)); 
    
    if (!YWEVTi_ISInitialized)
    {
        YWOSTRACE(( YWOS_TRACE_ERROR, "[ERROR][YWEVT_SubscribeEvent]  evt  is not init!!!...\n" ));
        return YWEVT_ERROR_NO_INITIALIZED;
    }
    if ((EventPoc == NULL) || (DrvHandle == 0) || (EventType == 0))
    {
        YWOSTRACE(( YWOS_TRACE_ERROR, "[ERROR][YWEVT_SubscribeEvent]  (EventPoc == NULL) ||  ( DrvHandle == 0 )!!!...\n") );
        return YWEVT_ERROR_BAD_PARAMETER;
    }


    ppHandleList = (YWEVTi_HandleList_T**)&ListAddress;
    
    YWOS_MutexWait(MutexEvtLock, YWOS_WAIT_INFINITY); 
    isHandleExist = YWEVTi_SearchHandleList(DrvHandle, ppHandleList/*HandleListExist*/);

    if(isHandleExist)
    {
        HandleListExist = *ppHandleList;
    }
    else
    {
        /*把handle加入到链表中*/
        HandlelistTemp = (YWEVTi_HandleList_T*) YWOS_Malloc(sizeof(YWEVTi_HandleList_T));
        if(HandlelistTemp == NULL)
        {
            YW_ErrorCode = YWEVT_ERROR_NO_MEMORY;
            YWOSTRACE(( YWOS_TRACE_ERROR, "[ERROR][YWEVT_SubscribeEvent]  HandlelistTemp == NULL !!!...\n" ));
            goto RETADDR;
        }
        HandlelistTemp->DrvHandle = DrvHandle;
        YWLIB_INIT_LIST_HEAD(&(HandlelistTemp->EventTypeListHead));
        YWLIB_ListAddTail(&(HandlelistTemp->YWEVTi_HandleList), &YWEVTi_HANDLE_LIST_NAME);       
        HandleListExist = HandlelistTemp;        
    }
    
    ppTypeList = (YWEVTi_EventTypeList_T**)&ListAddress;
    isTypeExist = YWEVTi_SearchEventTypeList(EventType, ppTypeList/*TypeListExist*/, &(HandleListExist->EventTypeListHead));   
    if(isTypeExist)
    {
        TypeListExist = *ppTypeList;
    }
    else
    {
        /*把EventType加入到链表中*/
        TypeListTemp = (YWEVTi_EventTypeList_T *) YWOS_Malloc( sizeof(YWEVTi_EventTypeList_T));
        if(TypeListTemp == NULL)
        {
            YW_ErrorCode = YWEVT_ERROR_NO_MEMORY;
            YWOSTRACE(( YWOS_TRACE_ERROR, "[ERROR][YWEVT_SubscribeEvent]  TypeListTemp == NULL !!!...\n" ));
            goto RETADDR;
        }
       
        TypeListTemp->EventType = EventType;
        YWLIB_INIT_LIST_HEAD( &(TypeListTemp ->EventFuncListHead));
        YWLIB_ListAddTail(&(TypeListTemp->YWEVTi_EventTypeList), &(HandleListExist->EventTypeListHead));
        TypeListExist = TypeListTemp;
    }
    
    ppFuncList = (YWEVTi_EventFuncList_T**)&ListAddress;
    isFuncExist = YWEVTi_SearchEventFuncList(EventPoc, ppFuncList/*FuncListExist */, &( TypeListExist->EventFuncListHead));

    if (!isFuncExist)
    {
        /*把FuncPoc加入到链表中*/
        FuncListTemp = (YWEVTi_EventFuncList_T *) YWOS_Malloc( sizeof(YWEVTi_EventFuncList_T));
        if(FuncListTemp == NULL)
        {
            YW_ErrorCode = YWEVT_ERROR_NO_MEMORY;
            YWOSTRACE(( YWOS_TRACE_ERROR, "[ERROR][YWEVT_SubscribeEvent]  FuncListTemp == NULL !!!...\n") );
            goto RETADDR;
        }
        
        FuncListTemp->EventFuncPoc     = EventPoc;
        FuncListTemp->UserData         = UserData;
        
        YWLIB_ListAddTail( &(FuncListTemp->YWEVTi_EventFuncList), &(TypeListExist->EventFuncListHead));
    }
    else
    {
        YWOSTRACE(( YWOS_TRACE_ERROR, "[ERROR][YWEVT_SubscribeEvent]  YWEVT_ERROR_FUNC_ISEXIST  !!!...\n" ));
        YW_ErrorCode = YWEVT_ERROR_FUNC_ISEXIST;
    }

RETADDR:   
    YWOS_MutexSend(MutexEvtLock); 
    return YW_ErrorCode;
}
                                                         
YW_ErrorType_T YWEVT_UnSubscribeEvent(   U32 DrvHandle,
                                         YW_EventType_T  EventType,
                                         YWEVT_EventPoc_T EventPoc )
{
    YW_ErrorType_T          YW_ErrorCode = YW_NO_ERROR;
    YWEVTi_HandleList_T     *HandleListExist = NULL, **ppHandleList = NULL;
    YWEVTi_EventTypeList_T  *TypeListExist = NULL, **ppTypeList = NULL;    
    YWEVTi_EventFuncList_T  *FuncListExist = NULL, **ppFuncList = NULL;
    
    BOOL  isHandleExist = FALSE, isFuncExist = FALSE, isTypeExist = FALSE;
    U32   ListAddress;
    
    YWOSTRACE((YWOS_TRACE_INFO, "[YWEVT_UnSubscribeEvent] DrvHandle = 0x%x  EventType = 0x%x !!!...\n", DrvHandle, EventType ));
    
    YWOSASSERT( (DrvHandle != 0) || (EventPoc != NULL) || (EventType != 0)); 
    
    if (!YWEVTi_ISInitialized)
    {
        YWOSTRACE(( YWOS_TRACE_ERROR, "[ERROR][YWEVT_UnSubscribeEvent]  evt  is not init!!!...\n" ));
        return YWEVT_ERROR_NO_INITIALIZED;
    }

    if ((EventPoc == NULL) ||  (DrvHandle == 0) || (EventType == 0))
    {
        YWOSTRACE(( YWOS_TRACE_ERROR,
                    "[ERROR][YWEVT_UnSubscribeEvent]  (EventPoc == NULL) ||  ( DrvHandle == 0 ) || ( EventType == 0 )!!!...\n" ));

        return YWEVT_ERROR_BAD_PARAMETER;
    }

    YWOS_MutexWait(MutexEvtLock, YWOS_WAIT_INFINITY);
/************************************************************************************************************/
    ppHandleList = (YWEVTi_HandleList_T**)&ListAddress;    
    isHandleExist = YWEVTi_SearchHandleList(DrvHandle, ppHandleList);

    if(!isHandleExist)
    {
        /*此设备并没有注册事件函数*/
        YW_ErrorCode = YWEVT_ERROR_NO_SUBSCRIBE_HANDLE;
//            YWOSTRACE(( YWOS_TRACE_ERROR,
//                        "[ERROR][YWEVT_UnSubscribeEvent] is not subscribe handle  YWEVT_ERROR_NO_SUBSCRIBE_HANDLE !!!...\n") );

        goto RETADDR;
    }
    HandleListExist = *ppHandleList;
/************************************************************************************************************/

/************************************************************************************************************/
    ppTypeList = (YWEVTi_EventTypeList_T**)&ListAddress;
    isTypeExist = YWEVTi_SearchEventTypeList(EventType ,  ppTypeList , &( HandleListExist->EventTypeListHead ) );

    if(!isTypeExist)
    {
        /*设备并没有此种事件类型注册事件函数*/
        YW_ErrorCode = YWEVT_ERROR_NO_SUBSCRIBE_EVENTTYPE;
        YWOSTRACE(( YWOS_TRACE_ERROR,
                    "[ERROR][YWEVT_UnSubscribeEvent] this handle is not subscribe EventType  YWEVT_ERROR_NO_SUBSCRIBE_EVENTTYPE !!!...\n" ));

        goto RETADDR;
    }
    TypeListExist = *ppTypeList;
/************************************************************************************************************/
    

    ppFuncList = (YWEVTi_EventFuncList_T**)&ListAddress;
    isFuncExist = YWEVTi_SearchEventFuncList( EventPoc , ppFuncList , &( TypeListExist->EventFuncListHead ) );

    if(!isFuncExist)
    {
        /*设备并没有此种事件类型注册事件函数*/
        YW_ErrorCode = YWEVT_ERROR_NO_SUBSCRIBE_FUNC;
        YWOSTRACE(( YWOS_TRACE_ERROR,
                    "[ERROR][YWEVT_UnSubscribeEvent] this EventType is not subscribe FuncPoc  YWEVT_ERROR_NO_SUBSCRIBE_FUNC !!!...\n") );

        goto RETADDR;
    }
    else
    {
        /*删除事件处理函数*/
        
        FuncListExist = *ppFuncList;
        YWLIB_ListDel( &( FuncListExist->YWEVTi_EventFuncList ) );
        YW_ErrorCode = YWOS_Free((void *)FuncListExist);
        if(YW_ErrorCode != YW_NO_ERROR)
        {
            YWOSTRACE(( YWOS_TRACE_ERROR,
                    "[ERROR][YWEVT_UnSubscribeEvent] YWOS_Free !!!...\n") );    
                    
            goto RETADDR;
        }

        if( YWLIB_ListEmpty( &( TypeListExist->EventFuncListHead ) ) )
        {
            YWLIB_ListDel( &( TypeListExist->YWEVTi_EventTypeList ) );
            
            YW_ErrorCode = YWOS_Free((void *)TypeListExist);
            if(YW_ErrorCode != YW_NO_ERROR)
            {
                YWOSTRACE(( YWOS_TRACE_ERROR,
                        "[ERROR][YWEVT_UnSubscribeEvent] YWOS_Free !!!...\n") );    
                        
                goto RETADDR;
            }

            
            if( YWLIB_ListEmpty( &( HandleListExist->EventTypeListHead ) ) )
            {
                YWLIB_ListDel( &( HandleListExist ->YWEVTi_HandleList ) );
                YW_ErrorCode = YWOS_Free( ( void * ) HandleListExist );
                if( YW_ErrorCode != YW_NO_ERROR )
                {
                    YWOSTRACE(( YWOS_TRACE_ERROR,
                            "[ERROR][YWEVT_UnSubscribeEvent] YWOS_Free !!!...\n") );    
                            
                    goto RETADDR;
                }                
            }
        }        
    }
    
RETADDR:    
    YWOS_MutexSend(MutexEvtLock);
    return YW_ErrorCode;
}


YW_ErrorType_T YWEVT_Notify(U32 DrvHandle, YW_EventType_T  EventType, void* EventData)                                              
{
    YW_ErrorType_T          YW_ErrorCode = YW_NO_ERROR;
    YWEVTi_HandleList_T     *HandleListExist = NULL, **ppHandleList = NULL;
    YWEVTi_EventTypeList_T  *TypeListExist = NULL,   **ppTypeList = NULL;
    
    BOOL isHandleExist = FALSE, isTypeExist = FALSE;
    U32  ListAddress;
    YWEVT_EventPoc_T EventFuncPoc[16]; 
    U32 UserData[16];
    U16 EventFuncPocIndex = 0;
    
    YWOSASSERT( ( DrvHandle != 0 ) || ( EventType != 0 )); 
    
    if (!YWEVTi_ISInitialized)
    {
        YWOSTRACE(( YWOS_TRACE_ERROR, "[ERROR][YWEVT_Notify]  evt  is not init!!!...\n" ));

        return YWEVT_ERROR_NO_INITIALIZED;
    }

    if ((DrvHandle == 0) || (EventType == 0))
    {
        YWOSTRACE(( YWOS_TRACE_ERROR, "[ERROR][YWEVT_Notify](DrvHandle == 0)||( EventType == 0 )!!!...\n"));
        return YWEVT_ERROR_BAD_PARAMETER;
    }
    
    ppHandleList = (YWEVTi_HandleList_T**)&ListAddress;
    YWOS_MutexWait(MutexEvtLock, YWOS_WAIT_INFINITY);
    isHandleExist = YWEVTi_SearchHandleList(DrvHandle, ppHandleList/*HandleListExist*/);

    if(!isHandleExist)
    {
        /*此设备并没有注册事件函数*/
        YW_ErrorCode = YWEVT_ERROR_NO_SUBSCRIBE_HANDLE;
        goto RETADDR;
    }
    HandleListExist = *ppHandleList;
    ppTypeList = (YWEVTi_EventTypeList_T**)&ListAddress;
    isTypeExist = YWEVTi_SearchEventTypeList(EventType, ppTypeList, &(HandleListExist->EventTypeListHead));

    if(!isTypeExist)
    {
        /*设备并没有此种事件类型注册事件函数*/
        YW_ErrorCode = YWEVT_ERROR_NO_SUBSCRIBE_EVENTTYPE;
        goto RETADDR;
    }
    TypeListExist = *ppTypeList;
    
    if( YWLIB_ListEmpty ( &( TypeListExist->EventFuncListHead ) ) )
    {
        /*设备并没有此种事件类型注册事件函数*/
        YW_ErrorCode = YWEVT_ERROR_NO_SUBSCRIBE_FUNC;
        goto RETADDR;
    }
    else
    {
        /*通知事件*/
        
        YWLIB_ListHead_T           *EventFuncList;
        YWEVTi_EventFuncList_T     *EventFuncListTemp;    
        
        YWLIB_ListForEach(EventFuncList, &(TypeListExist->EventFuncListHead))
        {
            EventFuncListTemp = YWLIB_ListEntry( EventFuncList, YWEVTi_EventFuncList_T, YWEVTi_EventFuncList);
            EventFuncPoc[EventFuncPocIndex] = EventFuncListTemp->EventFuncPoc; 
            UserData[EventFuncPocIndex] = (U32)EventFuncListTemp->UserData;
            EventFuncPocIndex++;
        }
    }
    
RETADDR:   
    YWOS_MutexSend(MutexEvtLock);

    if(EventFuncPocIndex != 0)
    {
        U32 i;
        for(i = 0; i < EventFuncPocIndex; i++)
        {
            EventFuncPoc[i](DrvHandle, EventType, EventData, (void*)UserData[i]);
        }
    }
    return YW_ErrorCode;
    
}


U32  YWEVT_GetVersion( S8 *pchVer, U32 nSize  )
{
    S8 Version[256];
    U32  ActLen;
    U32  RetLen;
 

    YWLIB_Sprintf(Version,(S8 *)"%s-%s-%s-%s-%s.\n",Ver_Layer,Ver_name,Ver_Version,__DATE__, __TIME__);
    
     ActLen = YWLIB_Strlen( Version ) + 1;
 
     if ( pchVer == NULL )
     {
          RetLen = ActLen;
     }
     else
     {
          if ( nSize == 0 )
          {  
               RetLen = 0;
          }
          else if ( nSize > ActLen )
          {
               RetLen = ActLen;
          }
          else
          {   
               RetLen = nSize;
          }

          YWLIB_Memcpy((void*) pchVer, (void*)Version, RetLen );
     }

     return RetLen;

}


