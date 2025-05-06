/**********************************�ļ�ͷ��ע��************************************/
//
//
//  					Copyright (C), 2005-2010, AV Frontier Tech. Co., Ltd.
//
//
// �ļ�����		ywtimer.h
//
// �����ߣ�		YYH
//
// ����ʱ�䣺	2008.05.05
//
// �ļ�������	TIMERģ���ͷ�ļ���
//
// �޸ļ�¼��   ��       ��      ��      ��       �汾      �޶�
//				       ---------         ---------        -----        -----
//              		       2008.05.05         YYH                   0.01           �½�
//	
/*****************************************************************************************/

#ifndef _YWTIMER_H
#define _YWTIMER_H

/************************************�꼰����****************************************/
#define YWTIMER_MSG_QUEUE_NUM 	20
#define YWTIMER_MSG_QUEUE_SIZE 	sizeof(YWTIMERi_TimerData_T)
#define TDT_PID 0x0014
#define TDT_TID 0x70

#define YWTIMER_TIME_PRECISION 10
/************************************���ݽṹ****************************************/

typedef struct YWTIMERi_EventInfo_s
{
    YWLIB_ListHead_T TimerEventNode;

	U32 uiEventID;
	U64 uiTimeOut;//ÿ�����봦��һ��
    
	U32 uiStartTime;//��ʼʱ��
	U64 uiLastTime;//�����һ�¼���һ�δ���ʱ��

	U32 uiNumber;//�������¼��ص���Ҫ������
	U32 uiNo;//�Ѿ����˵ڼ���

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

/************************************��������****************************************/
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

