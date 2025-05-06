#ifndef _YWGUI_WRAP_H_20080709_
#define  _YWGUI_WRAP_H_20080709_


#ifdef __cplusplus
extern "C" {
#endif 

typedef YWOS_SemaphoreID_T          YWGUI_SemaID_T;
typedef YWOS_MutexID_T              YWGUI_MutexID_T;
typedef YWOS_ThreadID_T             YWGUI_ThreadID_T;

extern void YWGUI_WrapInit();
extern void YWGUI_WrapTerm(void);
extern void YWGUI_WrapRegister(void* param);
extern void YWGUI_WrapUnregister(void);

extern YW_ErrorType_T YWGUI_WrapThreadCreate(S8* Name,  void(*Function)(void *Param), void* Param,
            void* Stack, U32 StackSize, U32 Priority, BOOL Start, YWGUI_ThreadID_T * ThreadID ); 
extern YW_ErrorType_T YWGUI_WrapThreadDelete(YWGUI_ThreadID_T  ThreadID );
extern BOOL YWGUI_WrapThreadIsCancel(YWGUI_ThreadID_T  ThreadID );
extern YW_ErrorType_T YWGUI_WrapSemaCreate(YWGUI_SemaID_T* SemaphoreID,U32 Count);
extern S32 YWGUI_WrapAbs(S32 val);
extern YWGUI_ThreadID_T YWGUI_WrapThreadSelf(void);
extern YWGUI_Handle_T YWGUI_WrapGetVisibleLayer(void);
extern BOOL YWGUI_WrapSetOsdLayerAlpha(YWGUI_Handle_T handle,U32 alphaVal);
extern BOOL YWGUI_WrapSetIORect(YWGUI_Handle_T handle,const YWGUI_Rect_T *prcIn,const YWGUI_Rect_T* prcOut);


extern void YWGUI_WrapSinkWait(void);
extern void YWGUI_WrapSinkWake(void);
extern void YWGUI_WrapStartAcceptKey(void);
extern S32 YWGUI_WrapGetKeyEvent(U32 *pMessage,U32 *pScanCode,U32 *pLParam);
/*added by sly, panel func wrap, 2009-4-23*/
extern BOOL YWGUI_WrapSetPanelLEDStr(U8* pcLEDStr, U16 uStrLen);
extern BOOL YWGUI_WrapDispPanelLEDStr(void);
extern BOOL YWGUI_WrapDispPanelLEDTime(void);
extern BOOL YWGUI_WrapPanelLEDClear(void);
extern BOOL YWGUI_WrapSetPanelLBDStatus(YWGUI_PanelLBDType_T  eLBDType, YWGUI_PanelLBDStatus_T  eLBDStatus);
extern BOOL YWGUI_WrapPanelVFDIoControl(YWGUI_PanelVFDIoControlType_T  eIoCtlType, void * pvParam);
extern BOOL YWGUI_WrapPanelSetStbyKey(YWGUI_PanelStandByKeyParam_T  *ptParam);
extern BOOL YWGUI_WrapPanelGetStbyKey(YWGUI_PanelStandByKeyParam_T  *ptParam);
extern BOOL YWGUI_WrapPanelSetBlueKey(YWGUI_PanelBlueKeyParam_T  *ptParam);
extern BOOL YWGUI_WrapPanelGetBlueKey(YWGUI_PanelBlueKeyParam_T  *ptParam);
extern BOOL YWGUI_WrapPanelSetVfdStandbyState(BOOL  IsStandby);
extern BOOL YWGUI_WrapPanelGetVfdStandbyState(BOOL  *IsStandby);
extern BOOL YWGUI_WrapPanelGetPowerOnState(BOOL  *pIsCheck);
extern BOOL YWGUI_WrapPanelSetPowerOnState(BOOL  IsCheck);
extern BOOL YWGUI_WrapPanelGetLoopState(BOOL *bLoop);
extern BOOL YWGUI_WrapPanelSetLoopState(BOOL  bLoop);
extern BOOL YWGUI_WrapPanelGetStartUpState(BOOL  * pIsElectrify);
extern BOOL YWGUI_WrapPanelControlTime(BOOL bStart);
extern BOOL  YWGUI_WrapAddEquiment(YWGUI_PanelEquipmentList_T* pstEquList);
extern BOOL  YWGUI_WrapDeleteEquiment(YWGUI_PanelEquipmentList_T* pstEquList);
extern BOOL YWGUI_WrapPanelGetFeature(YWGUI_PanelFeature_T* pstFeature);
extern BOOL YWGUI_WrapPanelSetKeyRepeatSpeed(U32 uSpeed);
extern BOOL YWGUI_WrapRemoteDisable(void);
extern BOOL YWGUI_WrapRemoteEnable(void);
extern BOOL YWGUI_WrapFrontPanelDisable(void);
extern BOOL YWGUI_WrapFrontPanelEnable(void);

/*end of added*/
extern YWGUI_Handle_T YWGUI_WrapOpenTimer(void);
extern BOOL YWGUI_WrapCloseTimer(YWGUI_Handle_T hTimer);
extern BOOL YWGUI_WrapGetTimerTrigger(S32 slot);
extern BOOL YWGUI_WrapStartTimer(YWGUI_Handle_T hTimer,S32 slot,U32 elapse);
extern BOOL YWGUI_WrapStopTimer(YWGUI_Handle_T hTimer,S32 slot);




extern YWGUI_HSurface_T  YWGUI_WrapInitSurface(BOOL bVisibled);
extern BOOL YWGUI_WrapTermSurface(YWGUI_HSurface_T hSurface);

extern void YWGUI_WrapColorMap2Pixel (YWGUI_HSurface_T hSurface,U32 color, YWGUI_Pixel_T pixel, BOOL b32BitResult);
extern void YWGUI_WrapAColorMap2Pixel (YWGUI_HSurface_T hSurface,U32 color, YWGUI_Pixel_T pixel);
extern void YWGUI_WrapDCAttrValue2Pixel (YWGUI_HSurface_T hSurface,U8 * pValue, YWGUI_Pixel_T pixel);
extern void YWGUI_WrapDCAttrPixel2Value (YWGUI_HSurface_T hSurface,YWGUI_Pixel_T pixel, U8 * pValue);
extern U32 YWGUI_WrapPixelMap2Color (YWGUI_HSurface_T hSurface,YWGUI_Pixel_T pixel);
extern void YWGUI_WrapPixel2Argb (YWGUI_HSurface_T hSurface,YWGUI_Pixel_T pixel, YWGUI_Argb_T* pArgb, U32 * pFlag);
extern void YWGUI_WrapArgb2Pixel (YWGUI_HSurface_T hSurface, YWGUI_Argb_T* pArgb, YWGUI_Pixel_T pixel, U32* pFlag);
extern U8 YWGUI_WrapGetBitsPerPixel(YWGUI_HSurface_T hSurface);
extern U8 YWGUI_WrapGetBytesPerPixel(YWGUI_HSurface_T hSurface);


extern void YWGUI_WrapSetClipping(YWGUI_HSurface_T hSurface,S32 xPos1, S32 yPos1, S32 xPos2, S32 yPos2);
extern void YWGUI_WrapFillBox(YWGUI_HSurface_T hSurface,S32 xPos1, S32 yPos1, S32 xPos2, S32 yPos2,YWGUI_Pixel_T color, YWGUI_CANVAS_OpMode_T OpMode);
extern void YWGUI_WrapRectangle(YWGUI_HSurface_T hSurface,S32 xPos1, S32 yPos1, S32 xPos2, S32 yPos2,YWGUI_Pixel_T color,U32 penWidth, YWGUI_CANVAS_OpMode_T OpMode);
extern void YWGUI_WrapDrawCircle(YWGUI_HSurface_T hSurface, S32 x0, S32 y0, S32 r, YWGUI_Pixel_T color, U32 penWidth, YWGUI_CANVAS_OpMode_T OpMode);
extern void YWGUI_WrapDrawTriangle(YWGUI_HSurface_T hSurface, S32 x1, S32 y1, S32 x2, S32 y2, S32 x3, S32 y3, YWGUI_Pixel_T color, U32 penWidth, YWGUI_CANVAS_OpMode_T OpMode);
extern void YWGUI_WrapDrawLine(YWGUI_HSurface_T hSurface,S32 xPos1, S32 yPos1, S32 xPos2, S32 yPos2, YWGUI_Pixel_T color,U32 penWidth, YWGUI_CANVAS_OpMode_T OpMode);
extern void YWGUI_WrapDrawPixel( YWGUI_HSurface_T hSurface, S32 x, S32 y,YWGUI_Pixel_T pixel);
extern void YWGUI_WrapGetBox( YWGUI_HSurface_T hSurface, S32 x, S32 y, S32 w, S32 h, void *buf);
extern void YWGUI_WrapFillPie(YWGUI_HSurface_T hSurface, S32 x0, S32 y0, S32 r, S32 startAngle, S32 endAngle, YWGUI_Pixel_T color, YWGUI_CANVAS_OpMode_T OpMode);
extern void YWGUI_WrapFillCircle(YWGUI_HSurface_T hSurface, S32 x0, S32 y0, S32 r, YWGUI_Pixel_T color, YWGUI_CANVAS_OpMode_T OpMode);
extern void YWGUI_WrapFillTriangle(YWGUI_HSurface_T hSurface, S32 x1, S32 y1, S32 x2, S32 y2, S32 x3, S32 y3, YWGUI_Pixel_T color, YWGUI_CANVAS_OpMode_T OpMode);
extern YW_ErrorType_T YWGUI_WrapDib2DdbGraphCell (YWGUI_HDc_T hdc,  const YWGUI_GraphCell_T * ptDibGraphCell,YWGUI_GraphCell_T * ptDdbGraphCell);

extern YW_ErrorType_T YWGUI_WrapFillBoxWithGraphCell(YWGUI_HDc_T hdc, S32 x, S32 y, S32 w, S32 h, YWGUI_HGraphCell_T hDdbGraphCell);

extern void*  YWGUI_WrapVMemMalloc(U32 Size);
extern void YWGUI_WrapVMemFree(void *pMem);
extern void YWGUI_WrapPutBox( YWGUI_HSurface_T hSurface, S32 x, S32 y, S32 w, S32 h, S32 pitch, void *buf, YWGUI_GraphCell_T* ptGraphCell);
extern void YWGUI_WrapPutBoxMask ( YWGUI_HSurface_T hSurface, S32 x, S32 y, S32 w, S32 h, S32 pitch, void *buf,YWGUI_Pixel_T pixelMask, YWGUI_GraphCell_T* ptGraphCell);
extern void YWGUI_WrapGetBox( YWGUI_HSurface_T hSurface, S32 x, S32 y, S32 w, S32 h, void *buf);
extern void YWGUI_WrapCopySurface(YWGUI_HSurface_T hDestSurface,YWGUI_HSurface_T hSrcSurface);

#ifdef __cplusplus
}
#endif

/************************内存操作函数***********************/
#define YWGUI_Malloc         YWOS_Malloc
#define YWGUI_Free           YWOS_Free
#define YWGUI_MemSet         YWLIB_Memset
#define YWGUI_MemCpy         YWLIB_Memcpy


/************************字符串操作函数***********************/
#if _YWGUI_WCHAR_DEF_
    #define YWGUI_sprintf       YWLIB_Swprintf
    #define YWGUI_strcpy        YWLIB_Wstrcpy
    #define YWGUI_strncpy       YWLIB_Wstrncpy
    #define YWGUI_strcmp        YWLIB_Wstrcmp
    #define YWGUI_strcat        YWLIB_Wstrcat

    //YWGUI_strlen返回字符个数
    #define YWGUI_strlen        YWLIB_Wstrlen
    #define YWGUI_strchr        YWLIB_Wstrchr
    #define YWGUI_strstr        YWLIB_Wstrstr
#else
    #define YWGUI_sprintf       YWLIB_Sprintf
    
    #define YWGUI_strcpy(pDstStr,pSrcStr) \
                YWLIB_Strcpy((S8*)pDstStr,(S8*)pSrcStr)
            
    #define YWGUI_strncpy(pDstStr,pSrcStr,n) \
                YWLIB_Strncpy((S8*)pDstStr,(S8*)pSrcStr,(S32)n)
    
    #define YWGUI_strcmp(str1,str2)   \
                YWLIB_Strcmp((S8*)str1,(S8*)str2)
            
    #define YWGUI_strcat(pDstStr,pSrcStr) \
                YWLIB_Strcat((S8*)pDstStr,(S8*)pSrcStr)

    #define YWGUI_strlen(pStr)        \
                YWLIB_Strlen((S8*)pStr)
    
    #define YWGUI_strchr(str,ch)      \
                YWLIB_Strchr((S8*)str,(S8)ch)
                
    #define YWGUI_strstr(str1,str2)   \
                YWLIB_Strstr((S8*)str1,(S8*)str2)
#endif

//内部ASCII字符串使用的字符串操作函数
#define ASCII_sprintf           YWLIB_Sprintf

#define ASCII_strcpy(pDstStr,pSrcStr) \
                YWLIB_Strcpy((S8*)pDstStr,(S8*)pSrcStr)
                
#define ASCII_strncpy(pDstStr,pSrcStr,n) \
                YWLIB_Strncpy((S8*)pDstStr,(S8*)pSrcStr,(S32)n)
    
#define ASCII_strcmp(str1,str2)   \
                YWLIB_Strcmp((S8*)str1,(S8*)str2)
            
#define ASCII_strcat(pDstStr,pSrcStr) \
                YWLIB_Strcat((S8*)pDstStr,(S8*)pSrcStr)

#define ASCII_strlen(pStr)        \
                YWLIB_Strlen((S8*)pStr)
                
#define ASCII_strchr(str,ch)      \
                YWLIB_Strchr((S8*)str,(S8)ch)
                
#define ASCII_strstr(str1,str2)   \
                YWLIB_Strstr((S8*)str1,(S8*)str2)

#define ASCII_atoi              YWLIB_Atoi  

/*********************************************************/
//#define YWGUI_AssertTrace(exp)       do{if(!(exp)){YWOS_Trace(YWOS_TRACE_ERROR,"AssertTrace  %s:%d\n",__FILE__,__LINE__);YWOS_Exit(0);}}while(0)     

//#define YWGUI_printf            YWOS_Trace   
//#define YWGUI_Trace             YWOS_Trace

#define YWGUI_abs               YWGUI_WrapAbs
    
/***************************内核对象函数*******************/
#define YWGUI_WAIT_INFINITY         YWOS_WAIT_INFINITY

    
#define YWGUI_ThreadCreate         YWGUI_WrapThreadCreate
#define YWGUI_ThreadDelete          YWGUI_WrapThreadDelete
#define YWGUI_ThreadIsCancel       YWGUI_WrapThreadIsCancel
//#define YWGUI_ThreadSelf           
#define YWGUI_ThreadSelf           YWGUI_WrapThreadSelf

#define YWGUI_MutexCreate          YWOS_MutexCreate
#define YWGUI_MutexWait(mutex)     YWOS_MutexWait(mutex,YWGUI_WAIT_INFINITY)
#define YWGUI_MutexSend            YWOS_MutexSend
#define YWGUI_MutexDelete          YWOS_MutexDelete

#define YWGUI_SemaCreate           YWGUI_WrapSemaCreate
#define YWGUI_SemaWait(sema)       YWOS_SemaphoreWait(sema,YWGUI_WAIT_INFINITY)
#define YWGUI_SemaSend             YWOS_SemaphoreSend
#define YWGUI_SemaDelete           YWOS_SemaphoreDelete  
#define YWGUI_GetSemaVal           YWOS_SemaphoreCount

#define YWGUI_TimeSleep            YWOS_TaskSleep

/***************************画图函数*******************/

#define YWGUI_GALInit                YWGUI_WrapInit
#define YWGUI_GALTerm                YWGUI_WrapTerm
#define YWGUI_GALRegister            YWGUI_WrapRegister
#define YWGUI_GALUnRegister          YWGUI_WrapUnregister

#define YWGUI_GALGetOsdLayer         YWGUI_WrapGetVisibleLayer
#define YWGUI_GalSetOsdLayerAlpha    YWGUI_WrapSetOsdLayerAlpha
#define YWGUI_GalSetIORect           YWGUI_WrapSetIORect

#define YWGUI_InitSurface            YWGUI_WrapInitSurface
#define YWGUI_TermSurface            YWGUI_WrapTermSurface
#define YWGUI_CopySurface            YWGUI_WrapCopySurface            


#define YWGUI_PixelMap2Color         YWGUI_WrapPixelMap2Color
#define YWGUI_ColorMap2Pixel         YWGUI_WrapColorMap2Pixel
#define YWGUI_AColorMap2Pixel        YWGUI_WrapAColorMap2Pixel
#define  YWGUI_DCAttrValue2Pixel         YWGUI_WrapDCAttrValue2Pixel
#define  YWGUI_DCAttrPixel2Value         YWGUI_WrapDCAttrPixel2Value

#define YWGUI_Pixel2Argb                    YWGUI_WrapPixel2Argb
#define YWGUI_Argb2Pixel                    YWGUI_WrapArgb2Pixel
            
#define YWGUI_GetBitsPerPixel        YWGUI_WrapGetBitsPerPixel
#define YWGUI_GetBytesPerPixel       YWGUI_WrapGetBytesPerPixel


#define YWGUI_GalFillBox             YWGUI_WrapFillBox   
#define YWGUI_GalRectangle           YWGUI_WrapRectangle
#define YWGUI_GalSetClipping         YWGUI_WrapSetClipping
#define YWGUI_GalDrawLine            YWGUI_WrapDrawLine
#define YWGUI_GalDrawPixel           YWGUI_WrapDrawPixel
#define YWGUI_GalDrawCircle                YWGUI_WrapDrawCircle
#define YWGUI_GalDrawTriangle                YWGUI_WrapDrawTriangle

#define YWGUI_VMemMalloc             YWGUI_WrapVMemMalloc
#define YWGUI_VMemFree               YWGUI_WrapVMemFree
#define YWGUI_GalPutBox              YWGUI_WrapPutBox
#define YWGUI_GalPutBoxMask          YWGUI_WrapPutBoxMask
#define YWGUI_GalGetBox              YWGUI_WrapGetBox

#define YWGUI_GalFillPie                YWGUI_WrapFillPie
#define YWGUI_GalFillCircle                YWGUI_WrapFillCircle
#define YWGUI_GalFillTriangle                YWGUI_WrapFillTriangle

          

#define YWGUI_DIB2DDBGraphCell           YWGUI_WrapDib2DdbGraphCell
#define YWGUI_GalFillBoxWithGraphCell   YWGUI_WrapFillBoxWithGraphCell


/****************************************************************/
#define YWGUI_SinkWake              YWGUI_WrapSinkWake
#define YWGUI_SinkWait               YWGUI_WrapSinkWait
#define YWGUI_StartAcceptKey         YWGUI_WrapStartAcceptKey
#define YWGUI_GetKeyEvent            YWGUI_WrapGetKeyEvent


#define YWGUI_OpenTimer             YWGUI_WrapOpenTimer
#define YWGUI_CloseTimer            YWGUI_WrapCloseTimer
#define YWGUI_GetTimerTrigger       YWGUI_WrapGetTimerTrigger
#define YWGUI_StartTimer            YWGUI_WrapStartTimer
#define YWGUI_StopTimer             YWGUI_WrapStopTimer

#endif


