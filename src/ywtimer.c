/**********************************�ļ�ͷ��ע��************************************/
//
//
//                      Copyright (C), 2005-2010, AV Frontier Tech. Co., Ltd.
//
//
// �ļ�����        ywtimer.c
//
// �����ߣ�        YYH
//
// ����ʱ�䣺    2008.05.05
//
// �ļ�������    TIMERģ���C�ļ���
//
// �޸ļ�¼��   ��       ��      ��      ��       �汾      �޶�
//                ---------         ---------       -----     -----
//              2008.05.05        YYH             0.01      �½�
//
/*****************************************************************************************/

/************************************�ļ�����****************************************/
#include "ywdefs.h"
#include "ywos.h"
#include "ywlib.h"
#include "ywevt.h"

#include "ywmid.h"
#include "ywtimer_ext.h"
#include "ywtimer.h"


#define YWTIMER_THREAD_PRIORITY      (1)
#define YWTIMER_STACK_SIZE                    (4*YW_K)

/************************************ȫ�ֱ���****************************************/

static YWOS_ThreadID_T gTimerCallbackThreadID;
//static YWOS_SemaphoreID_T gTimerCbSemaphoreID;
static YWOS_MutexID_T gTimerCbSemaphoreID;
static YWTIMERi_TimerInfo_T *gTimerInfo = NULL;

static S32 gTimeOffset = 0;//(8*60);//������������ʱ��

POSIX_Clock_t  POSIX_TimeNow (void);
struct timeval POSIX_Clockt2Timeval(POSIX_Clock_t clock);

/************************************����ʵ��****************************************/

BOOL YWTIMERi_CheckEventIdExist(YWTIMER_Hdl_T Handle,U32 TimerEventID)
{
    BOOL retVal = FALSE;
    YWTIMERi_TimerInfo_T *TimerInfo;
    YWLIB_ListHead_T *tempNode;
    YWTIMERi_EventInfo_T *TimerEventInfo;

    TimerInfo = (YWTIMERi_TimerInfo_T*)Handle;

    YWLIB_ListForEach(tempNode, TimerInfo->pstEventListHandle)
    {
        TimerEventInfo = YWLIB_ListEntry(tempNode, YWTIMERi_EventInfo_T, TimerEventNode);
        if(TimerEventInfo->uiEventID == TimerEventID)
        {
            retVal = TRUE;
            break;
        }
    }
    return retVal;
}

void YWTIMERi_RegistEventID(YWTIMER_Hdl_T Handle,U32 TimerEventID)
{
    YWTIMERi_TimerInfo_T *TimerInfo;
//    YWLIB_ListHead_T *tempNode;
    YWTIMERi_EventInfo_T *TimerEventInfo;

    TimerInfo = (YWTIMERi_TimerInfo_T *)Handle;

    TimerEventInfo = YWOS_Malloc(sizeof(YWTIMERi_EventInfo_T));
    TimerEventInfo->uiEventID = TimerEventID;
    TimerEventInfo->uiTimeOut.MSW = YWOS_WAIT_INFINITY;
    TimerEventInfo->uiTimeOut.LSW = YWOS_WAIT_INFINITY;
    TimerEventInfo->uiStartTime  = YWOS_WAIT_INFINITY;
    //���ע��������..Local�������ͻ������������¼�����
    //�˶����ĳ�0,������ִ����⡣2009.8.6 XYJ Noted.
    TimerEventInfo->uiLastTime.MSW = 0;//YWOS_WAIT_INFINITY;
    TimerEventInfo->uiLastTime.LSW = 0;//YWOS_WAIT_INFINITY;
    TimerEventInfo->uiNumber = 0;
    TimerEventInfo->uiNo = 0;
    TimerEventInfo->bGMT = FALSE;

    YWLIB_ListAddTail(&(TimerEventInfo->TimerEventNode), TimerInfo->pstEventListHandle);

    return;
}

void YWTIMERi_UnRegistEventID(YWTIMER_Hdl_T Handle,U32 TimerEventID)
{
    YWTIMERi_TimerInfo_T *TimerInfo;
    YWLIB_ListHead_T *tempNode1,*tempNode2;
    YWTIMERi_EventInfo_T *TimerEventInfo;

    TimerInfo = (YWTIMERi_TimerInfo_T*)Handle;

    YWLIB_ListForEachSafe(tempNode1, tempNode2, TimerInfo->pstEventListHandle)
    {
        TimerEventInfo = YWLIB_ListEntry(tempNode1, YWTIMERi_EventInfo_T, TimerEventNode);
        if(TimerEventInfo->uiEventID == TimerEventID)
        {
            YWLIB_ListDel(tempNode1);
            YWOS_Free(TimerEventInfo);
            break;
        }
    }

    return;
}

void YWTIMERi_EventStart(YWTIMER_Hdl_T Handle,U32 TimerEventID,U64 TimeOut,U32 Number )
{
    YWTIMERi_TimerInfo_T *TimerInfo;
    YWLIB_ListHead_T *tempNode;
    YWTIMERi_EventInfo_T *TimerEventInfo;
    U64 TickCount;
    U32 SecondsCount;

    TimerInfo = (YWTIMERi_TimerInfo_T*)Handle;

    YWLIB_ListForEach(tempNode, TimerInfo->pstEventListHandle)
    {
        TimerEventInfo = YWLIB_ListEntry(tempNode, YWTIMERi_EventInfo_T, TimerEventNode);
        if(TimerEventInfo->uiEventID == TimerEventID)
        {
            POSIX_Clock_t clock;
            TimerEventInfo->uiTimeOut = TimeOut;//����

            //YWRTC_GetTickCount( gRtcHandle,&TickCount);
            clock = POSIX_TimeNow();
            TickCount.LSW = clock&0xFFFFFFFF;
            TickCount.MSW = (clock>>32)&0xFFFFFFFF;
            //YWRTC_GetSysClock( gRtcHandle,&SecondsCount);
            SecondsCount = clock/POSIX_GetClocksPerSecond();
            
            TimerEventInfo->uiStartTime = SecondsCount;
            TimerEventInfo->uiLastTime = TickCount;//����

            TimerEventInfo->uiNumber = Number;
            TimerEventInfo->uiNo = 0;
            break;
        }
    }

    return;
}

void YWTIMERi_EventStop(YWTIMER_Hdl_T Handle,U32 TimerEventID )
{
    YWTIMERi_TimerInfo_T *TimerInfo;
    YWLIB_ListHead_T *tempNode;
    YWTIMERi_EventInfo_T *TimerEventInfo;

    TimerInfo = (YWTIMERi_TimerInfo_T*)Handle;

    YWLIB_ListForEach(tempNode, TimerInfo->pstEventListHandle)
    {
        TimerEventInfo = YWLIB_ListEntry(tempNode, YWTIMERi_EventInfo_T, TimerEventNode);
        if(TimerEventInfo->uiEventID == TimerEventID)
        {
            TimerEventInfo->uiTimeOut.MSW = YWOS_WAIT_INFINITY;//��
            TimerEventInfo->uiTimeOut.LSW = YWOS_WAIT_INFINITY;//��

            TimerEventInfo->uiStartTime = YWOS_WAIT_INFINITY;//����
            TimerEventInfo->uiLastTime.MSW = YWOS_WAIT_INFINITY;//����
            TimerEventInfo->uiLastTime.LSW = YWOS_WAIT_INFINITY;//����

            TimerEventInfo->uiNumber = 0;
            TimerEventInfo->uiNo = 0;
            break;
        }
    }

    return;
}

#define YWTIMERi_TimerCbSemWait()  YWOS_MutexWait(gTimerCbSemaphoreID,YWOS_WAIT_INFINITY)
#define YWTIMERi_TimerCbSemSend() YWOS_MutexSend(gTimerCbSemaphoreID)
/*YW_ErrorType_T YWTIMERi_TimerCbSemWait()
{
    return YWOS_SemaphoreWait(gTimerCbSemaphoreID,YWOS_WAIT_INFINITY);
}

YW_ErrorType_T YWTIMERi_TimerCbSemSend()
{
    return YWOS_SemaphoreSend(gTimerCbSemaphoreID) ;
}*/

void YWTIMERi_TimerTask(void *param)
{
    U32 i;
    YWLIB_ListHead_T *tempNode;
    YWTIMERi_EventInfo_T *timerEventInfo;
    YWTIMER_Hdl_T tempHandle;
    U64 TickCount;
    U64 LastTime,TimeOut,SubTime;
    U32 Number,No,CurSec,StartSec,CompSec;
    YWTIMER_EventAppData_T EventData;
    //YW_ErrorType_T ErrorCode = YW_NO_ERROR;
    //U32 uCount =50;
    YWOS_ThreadID_T  ThreadId;
    POSIX_Clock_t clock;

    YWOS_ThreadId(&ThreadId);

    while (!YWOS_ThreadIsCancel(ThreadId))
    {
        YWTIMERi_TimerCbSemWait();
        #if 0
        if(uCount >=50)//���ھ���ֻ��1s��500ms��ȡһ��ʱ��
        {
            //YWRTC_GetSysClock( gRtcHandle,&CurSec);
            uCount =0;
        }
        #endif
        //YWRTC_GetTickCount( gRtcHandle,&TickCount);
        clock = POSIX_TimeNow();
        TickCount.LSW = clock&0xFFFFFFFF;
        TickCount.MSW = (clock>>32)&0xFFFFFFFF;
        //YWRTC_GetSysClock( gRtcHandle,&SecondsCount);
        CurSec = clock/POSIX_GetClocksPerSecond();
        for(i=0;i<YWTIMER_MAX_TIMER_NUM;i++)
        {
            if(gTimerInfo[i].bused == TRUE)
            {
                //YWRTC_GetTickCount( gRtcHandle,&TickCount);   /*�Ƶ�����,10ms���һ�Σ����Ϊ10ms*/
                //CurSec -= gTimeOffset*60;//ת����GMTʱ��
                tempHandle = (YWTIMER_Hdl_T)(&gTimerInfo[i]);

                YWLIB_ListForEach(tempNode, gTimerInfo[i].pstEventListHandle)
                {
                    timerEventInfo = YWLIB_ListEntry(tempNode, YWTIMERi_EventInfo_T, TimerEventNode);

                    LastTime = timerEventInfo->uiLastTime;
                    Number = timerEventInfo->uiNumber;
                    No = timerEventInfo->uiNo;
                    StartSec = timerEventInfo->uiStartTime;
                    TimeOut = timerEventInfo->uiTimeOut;

                    if((LastTime.MSW == YWOS_WAIT_INFINITY)&&(LastTime.LSW == YWOS_WAIT_INFINITY))
                    {
                        BOOL bStart = FALSE;
                        U32 ii = 0;

                        if(timerEventInfo->bGMT)
                        {
                            //��ʱ���¼�����GMTΪ��׼ʱ�䴥��,������ʱ��(��)ת��ΪGMT(��)
                            CompSec = CurSec - gTimeOffset*60;
                        }
                        else
                        {
                            //��ʱ���¼����Ա���ʱ��Ϊ��׼ʱ�䴥��
                            CompSec = CurSec;
                        }

                        for(ii = 0;ii < timerEventInfo->uiNumber;ii++)
                        {
                            if((CompSec>=StartSec+ii*(TimeOut.LSW/YWOS_1_SEC))&&((CompSec-(StartSec+ii*(TimeOut.LSW/YWOS_1_SEC)))<2))
                            {
                                //����ǰʱ�䵽�ﴥ��ʱ��CompSec,����ƫ����2����,��ʼ��һ�δ�����ʱ���¼�
                                bStart = TRUE;
                                break;
                            }
                        }

                        if(bStart)
                        {
                            YWMID_Trace((YWOS_TRACE_INFO, "[YWTIMERi_TimerTask]Time reach1!\n"));
                            timerEventInfo->uiLastTime = TickCount;
                            //if(timerEventInfo->uiNumber != YWTIMER_INFINITY_NUM)
                            {
                                timerEventInfo->uiNo += 1+ii;
                            }

                            //�ص�
                            EventData.uiEventID = timerEventInfo->uiEventID;
                            EventData.uiTimeOut = timerEventInfo->uiTimeOut;
                            EventData.uiStartTime = timerEventInfo->uiStartTime;
                            EventData.uiLastTime = timerEventInfo->uiLastTime;
                            EventData.uiNumber = timerEventInfo->uiNumber;
                            EventData.uiNo = timerEventInfo->uiNo;
                            //YWLIB_Memcpy(&EventData, timerEventInfo+sizeof(YWLIB_ListHead_T), sizeof(YWTIMER_EventAppData_T));
                             //YWTIMERi_TimerCbSemSend();
                            YWEVT_Notify((U32)(&gTimerInfo[i]),YWTIMER_EVENT_APPLICATION,&EventData);
                            //YWTIMERi_TimerCbSemWait();
                        }
                    }
                    else
                    {
                        YWI64_Sub(TickCount,LastTime,SubTime);

                        if((YWI64_IsGreaterOrEqual(SubTime,TimeOut))&&(No<Number))
                        {
                            YWMID_Trace((YWOS_TRACE_INFO, "[YWTIMERi_TimerTask]Time reach2!\n"));
                            timerEventInfo->uiLastTime = TickCount;
                            //if(timerEventInfo->uiNumber != YWTIMER_INFINITY_NUM)
                            {
                                timerEventInfo->uiNo++;
                            }

                            //�ص�
                            EventData.uiEventID = timerEventInfo->uiEventID;
                            EventData.uiTimeOut = timerEventInfo->uiTimeOut;
                            EventData.uiStartTime = timerEventInfo->uiStartTime;
                            EventData.uiLastTime = timerEventInfo->uiLastTime;
                            EventData.uiNumber = timerEventInfo->uiNumber;
                            EventData.uiNo = timerEventInfo->uiNo;
                            //YWLIB_Memcpy(&EventData, timerEventInfo+sizeof(YWLIB_ListHead_T), sizeof(YWTIMER_EventAppData_T));
                             //YWTIMERi_TimerCbSemSend();
                            YWEVT_Notify((U32)(&gTimerInfo[i]),YWTIMER_EVENT_APPLICATION,&EventData);
                            //YWTIMERi_TimerCbSemWait();
                        }
                    }
                }
            }
        }

        YWTIMERi_TimerCbSemSend();
        YWOS_TaskSleep(YWTIMER_TIME_PRECISION);
        //uCount ++;
    }
}

YW_ErrorType_T YWTIMER_Init(void)
{
    YW_ErrorType_T ErrorCode = YW_NO_ERROR;

    BOOL ThreadStart = TRUE;
    
    U32 i=0;

    if(gTimerInfo != NULL)
    {
        ErrorCode = YWMID_ERROR_ALREADY_INITIALIZED;
    }
    else
    {
        //��ʼ����Դ
        gTimerInfo = YWOS_Malloc(YWTIMER_MAX_TIMER_NUM*sizeof(YWTIMERi_TimerInfo_T));
        for(i=0;i<YWTIMER_MAX_TIMER_NUM;i++)
        {
            gTimerInfo[i].bused = FALSE;
            gTimerInfo[i].pstEventListHandle = NULL;
        }

        //�����ź���
        //YWOS_SemaphoreCreate( (S8*)"Timer Semphore", 1, &gTimerCbSemaphoreID );
        YWOS_MutexCreate(&gTimerCbSemaphoreID);
        //������ʱ���߳�
        YWOS_ThreadCreate((S8*)"TimerTask",YWTIMERi_TimerTask, NULL, NULL, YWTIMER_STACK_SIZE, YWTIMER_THREAD_PRIORITY, ThreadStart, &gTimerCallbackThreadID) ;

        YWMID_Trace((YWOS_TRACE_INFO, "[YWTIMER_Init]return %x\n",ErrorCode));
    }
    return ErrorCode;
}

YW_ErrorType_T YWTIMER_Term(void)
{
    YW_ErrorType_T ErrorCode = YW_NO_ERROR;

    if(gTimerInfo == NULL)
    {
        ErrorCode = YWMID_ERROR_NO_INITIALIZED;
    }
    else
    {

        YWTIMERi_TimerCbSemSend();
        //�ر��߳�
        
        //YWOS_ThreadStop(gTimerCallbackThreadID);
        YWOS_ThreadDelete(gTimerCallbackThreadID);
        //ɾ���ź���
        //YWOS_SemaphoreDelete(gTimerCbSemaphoreID);
        YWOS_MutexDelete(gTimerCbSemaphoreID);

        //�ͷ���Դ
        YWOS_Free(gTimerInfo);
    }
    YWMID_Trace((YWOS_TRACE_INFO, "[YWTIMER_Term]return %x\n",ErrorCode));
    return ErrorCode;
}

YW_ErrorType_T YWTIMER_GetFeature(void *Feature)
{
    return YW_NO_ERROR;
}

YW_ErrorType_T YWTIMER_Open(YWTIMER_Hdl_T *Handle)
{
    YW_ErrorType_T ErrorCode = YW_NO_ERROR;
    U32 i;

    if(gTimerInfo == NULL)
    {
        ErrorCode = YWMID_ERROR_NO_INITIALIZED;
    }
    else
    {
        YWTIMERi_TimerCbSemWait();

        //��һ��TIMER��Դ
        for(i=0;i<YWTIMER_MAX_TIMER_NUM;i++)
        {
            if(gTimerInfo[i].bused == FALSE)
            {
                gTimerInfo[i].bused = TRUE;
                gTimerInfo[i].pstEventListHandle = YWOS_Malloc(sizeof(YWLIB_ListHead_T));
                YWLIB_INIT_LIST_HEAD(gTimerInfo[i].pstEventListHandle);
                *Handle = (YWTIMER_Hdl_T)&(gTimerInfo[i]);
                break;
            }
        }
        if(i == YWTIMER_MAX_TIMER_NUM)
        {
            YWMID_Trace((YWOS_TRACE_ERROR, "[YWTIMER_Open]No free Timer!"));
            ErrorCode = YWMID_ERROR_NO_FREE_HANDLES;
        }
        YWTIMERi_TimerCbSemSend();
    }

    return ErrorCode;
}

YW_ErrorType_T YWTIMER_Close(YWTIMER_Hdl_T  Handle)
{
    YW_ErrorType_T ErrorCode = YW_NO_ERROR;
    YWTIMERi_TimerInfo_T *TimerInfo;

    if(gTimerInfo == NULL)
    {
        YWMID_Trace((YWOS_TRACE_ERROR, "[YWTIMER_Close]Timer not init!"));
        ErrorCode = YWMID_ERROR_NO_INITIALIZED;
    }
    else
    {
        YWTIMERi_TimerCbSemWait();
        if(!YW_HandleValid(gTimerInfo,YWTIMER_MAX_TIMER_NUM,Handle))
        {
            YWMID_Trace((YWOS_TRACE_ERROR, "[YWTIMER_Close]Handle invalid!"));
            ErrorCode = YWMID_ERROR_INVALID_HANDLE;
        }
        else
        {
            TimerInfo = (YWTIMERi_TimerInfo_T*)Handle;
            if(!TimerInfo->bused)
            {
                YWMID_Trace((YWOS_TRACE_ERROR, "[YWTIMER_Close]Handle invalid!"));
                ErrorCode = YWMID_ERROR_INVALID_HANDLE;
            }
            else
            {
                if(!YWLIB_ListEmpty(TimerInfo->pstEventListHandle))
                {
                    YWMID_Trace((YWOS_TRACE_ERROR, "[YWTIMER_Close]Timer working,cannot close!"));
                    ErrorCode = YWTIMER_ERROR_WORKING;
                }
                else
                {
                    YWOS_Free(TimerInfo->pstEventListHandle);
                    TimerInfo->bused = FALSE;
                }
            }
        }
        YWTIMERi_TimerCbSemSend();
    }

    return ErrorCode;
}

YW_ErrorType_T YWTIMER_RegistAppEvent(YWTIMER_Hdl_T Handle,U32 TimerEventID)
{
    YW_ErrorType_T ErrorCode = YW_NO_ERROR;
    YWTIMERi_TimerInfo_T *TimerInfo;

    if(gTimerInfo == NULL)
    {
        YWMID_Trace((YWOS_TRACE_ERROR, "[YWTIMER_RegistAppEvent]Timer not init!"));
        ErrorCode = YWMID_ERROR_NO_INITIALIZED;
    }
    else
    {
        YWTIMERi_TimerCbSemWait();

        if(!YW_HandleValid(gTimerInfo,YWTIMER_MAX_TIMER_NUM,Handle))
        {
            YWMID_Trace((YWOS_TRACE_ERROR, "[YWTIMER_RegistAppEvent]Handle invalid!"));
            ErrorCode = YWMID_ERROR_INVALID_HANDLE;
        }
        else
        {
            TimerInfo = (YWTIMERi_TimerInfo_T*)Handle;

            if(YWTIMERi_CheckEventIdExist(Handle, TimerEventID))
            {
                YWMID_Trace((YWOS_TRACE_ERROR, "[YWTIMER_RegistAppEvent]the event have been registed!"));
                ErrorCode = YWTIMER_ERROR_EVENTID_EXIST;
            }
            else
            {
                YWTIMERi_RegistEventID(Handle, TimerEventID);
            }
        }
        YWTIMERi_TimerCbSemSend();
    }
    return ErrorCode;
}

YW_ErrorType_T YWTIMER_UnRegistAppEvent(YWTIMER_Hdl_T Handle, U32 TimerEventID)
{
    YW_ErrorType_T ErrorCode = YW_NO_ERROR;
    YWTIMERi_TimerInfo_T *TimerInfo;

    if(gTimerInfo == NULL)
    {
        YWMID_Trace((YWOS_TRACE_ERROR, "[YWTIMER_UnRegistAppEvent]Timer not init!"));
        ErrorCode = YWMID_ERROR_NO_INITIALIZED;
    }
    else
    {
        YWTIMERi_TimerCbSemWait();
        if(!YW_HandleValid(gTimerInfo,YWTIMER_MAX_TIMER_NUM,Handle))
        {
            YWMID_Trace((YWOS_TRACE_ERROR, "[YWTIMER_UnRegistAppEvent]Handle invalid!"));
            ErrorCode = YWMID_ERROR_INVALID_HANDLE;
        }
        else
        {
            TimerInfo = (YWTIMERi_TimerInfo_T*)Handle;

            if(!YWTIMERi_CheckEventIdExist(Handle, TimerEventID))
            {
                //YWMID_Trace((YWOS_TRACE_ERROR, "[YWTIMER_UnRegistAppEvent]the event have not been registed!\n"));
                ErrorCode = YWTIMER_ERROR_EVENTID_NOT_EXIST;
            }
            else
            {
                YWTIMERi_UnRegistEventID(Handle, TimerEventID);
            }
        }
        YWTIMERi_TimerCbSemSend();
    }
    return ErrorCode;
}

YW_ErrorType_T YWTIMER_AppEventStart(YWTIMER_Hdl_T Handle,U32 TimerEventID,U64 Interval,U32 Number )
{
    YW_ErrorType_T ErrorCode = YW_NO_ERROR;
    YWTIMERi_TimerInfo_T *TimerInfo;

    if(gTimerInfo == NULL)
    {
        YWMID_Trace((YWOS_TRACE_ERROR, "[YWTIMER_AppEventStart]Timer not init!"));
        ErrorCode = YWMID_ERROR_NO_INITIALIZED;
    }
    else
    {
        YWTIMERi_TimerCbSemWait();
        if(!YW_HandleValid(gTimerInfo,YWTIMER_MAX_TIMER_NUM,Handle))
        {
            YWMID_Trace((YWOS_TRACE_ERROR, "[YWTIMER_AppEventStart]Handle invalid!"));
            ErrorCode = YWMID_ERROR_INVALID_HANDLE;
        }
        else
        {
            TimerInfo = (YWTIMERi_TimerInfo_T*)Handle;

            if(!YWTIMERi_CheckEventIdExist(Handle, TimerEventID))
            {
                YWMID_Trace((YWOS_TRACE_ERROR, "[YWTIMER_AppEventStart]the event have not been registed!"));
                ErrorCode = YWTIMER_ERROR_EVENTID_NOT_EXIST;
            }
            else
            {
                YWTIMERi_EventStart(Handle,TimerEventID,Interval,Number);
            }
        }
        YWTIMERi_TimerCbSemSend();
    }
    return ErrorCode;
}


YW_ErrorType_T YWTIMER_AppEventStop(YWTIMER_Hdl_T Handle,U32 TimerEventID)
{
    YW_ErrorType_T ErrorCode = YW_NO_ERROR;
    YWTIMERi_TimerInfo_T *TimerInfo;

    if(gTimerInfo == NULL)
    {
        YWMID_Trace((YWOS_TRACE_ERROR, "[YWTIMER_AppEventStop]Timer not init!"));
        ErrorCode = YWMID_ERROR_NO_INITIALIZED;
    }
    else
    {
        YWTIMERi_TimerCbSemWait();
        if(!YW_HandleValid(gTimerInfo,YWTIMER_MAX_TIMER_NUM,Handle))
        {
            YWMID_Trace((YWOS_TRACE_ERROR, "[YWTIMER_AppEventStop]Handle invalid!"));
            ErrorCode = YWMID_ERROR_INVALID_HANDLE;
        }
        else
        {
            TimerInfo = (YWTIMERi_TimerInfo_T*)Handle;

            if(!YWTIMERi_CheckEventIdExist(Handle, TimerEventID))
            {
                YWMID_Trace((YWOS_TRACE_ERROR, "[YWTIMER_AppEventStop]the event have not been registed!"));
                ErrorCode = YWTIMER_ERROR_EVENTID_NOT_EXIST;
            }
            else
            {
                YWTIMERi_EventStop(Handle, TimerEventID);
            }
        }
        YWTIMERi_TimerCbSemSend();
    }
    return ErrorCode;
}


