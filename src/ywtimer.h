/**********************************文件头部注释************************************/
//
//
//  					Copyright (C), 2005-2010, AV Frontier Tech. Co., Ltd.
//
//
// 文件名：		ywtimer.h
//
// 创建者：		YYH
//
// 创建时间：	2008.05.05
//
// 文件描述：	TIMER模块的头文件。
//
// 修改记录：   日       期      作      者       版本      修定
//				       ---------         ---------        -----        -----
//              		       2008.05.05         YYH                   0.01           新建
//	
/*****************************************************************************************/

#ifndef _YWTIMER_H
#define _YWTIMER_H

/************************************宏及常量****************************************/
#define YWTIMER_MSG_QUEUE_NUM 	20
#define YWTIMER_MSG_QUEUE_SIZE 	sizeof(YWTIMERi_TimerData_T)
#define TDT_PID 0x0014
#define TDT_TID 0x70

#define YWTIMER_TIME_PRECISION 10
/************************************数据结构****************************************/

typedef struct YWTIMERi_EventInfo_s
{
    YWLIB_ListHead_T TimerEventNode;

	U32 uiEventID;
	U64 uiTimeOut;//每多少秒处理一次
    
	U32 uiStartTime;//开始时间
	U64 uiLastTime;//针对这一事件上一次处理时间

	U32 uiNumber;//针对这个事件回调需要做几次
	U32 uiNo;//已经做了第几次

	BOOL bGMT;

}YWTIMERi_EventInfo_T;

typedef struct YWTIMERi_TimerInfo_s
{
    BOOL                        bused;
    YWLIB_ListHead_T            *pstEventListHandle;
    //YWTIMER_EventInfoNode_T     *pstEventInfoNode;
}YWTIMERi_TimerInfo_T;

typedef struct YWTIMERi_TimerData_s
{
	U32 			uiEventType;
	U8* 			pucSectionData;
	U32				uiSectionLen;
}YWTIMERi_TimerData_T;

typedef struct  YWTIMERi_UTC_s
{
	U16 				usMjd;
	U8					ucHour;
	U8					ucMinute;
	U8					ucSecond;

} YWTIMERi_UTC_T;

/************************************函数声明****************************************/
BOOL YWTIMERi_CheckEventIdExist(YWTIMER_Hdl_T Handle,U32 TimerEventID);
void YWTIMERi_RegistEventID(YWTIMER_Hdl_T Handle,U32 TimerEventID);
void YWTIMERi_UnRegistEventID(YWTIMER_Hdl_T Handle,U32 TimerEventID);
void YWTIMERi_EventStart(YWTIMER_Hdl_T Handle,U32 TimerEventID,U64 TimeOut,U32 Number );
void YWTIMERi_EventStartGMT(YWTIMER_Hdl_T Handle, U32 TimerEventID, YWTIMER_CurTime_T StartTime, U64 TimeOut, U32 Number );
void YWTIMERi_EventStartLocal(YWTIMER_Hdl_T Handle, U32 TimerEventID, YWTIMER_CurTime_T StartTime, U64 TimeOut, U32 Number );
void YWTIMERi_EventStop(YWTIMER_Hdl_T Handle,U32 TimerEventID );
YW_ErrorType_T YWTIMERi_TimerCbSemWait(void);
YW_ErrorType_T YWTIMERi_TimerCbSemSend(void);
YW_ErrorType_T YWTIMERi_TimerTdtSemWait(void);
YW_ErrorType_T YWTIMERi_TimerTdtSemSend(void);
void YWTIMERi_TimerTDTMonitorTask(void *param);
void YWTIMERi_TimerCallbackTask(void *param);

#endif

