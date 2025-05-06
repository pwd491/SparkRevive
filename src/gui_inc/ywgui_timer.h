#ifndef _YWGUI_TIMER_H_20080423_
#define  _YWGUI_TIMER_H_20080423_

#ifdef __cplusplus
extern "C" {
#endif


extern BOOL  YWGUI_Timer_Init(void);
extern BOOL YWGUI_TimerDestroy(void);
extern void YWGUI_ScanTimerEvent(void);


extern void YWGUI_RemoveMsgQTimerFlag (YWGUI_MsgQueue_P pMsgQueue, S32 slot);
extern YWGUI_HWnd_T YWGUI_GetTimerHWnd (S32 slot);
extern S32 YWGUI_GetTimerId (S32 slot);



#ifdef __cplusplus
}
#endif 
#endif

