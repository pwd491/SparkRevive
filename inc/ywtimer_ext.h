/**********************************�ļ�ͷ��ע��************************************/
//
//
//  					Copyright (C), 2005-2010, AV Frontier Tech. Co., Ltd.
//
//
// �ļ�����		ywtimer_ext.h
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

#ifndef _YWTIMER_EXT_H
#define _YWTIMER_EXT_H

/************************************�꼰����****************************************/

//��������
enum
{
	YWTIMER_ERROR_WORKING = YW_MODULE_SET_ID( YWMID_MODULE_TIMER_ID),
	//��ʱ�����ڹ���������YWTIMER_Closeʱ����
	
	YWTIMER_ERROR_EVENTID_EXIST,
	//��ʱ���¼��Ѵ��ڣ�����YWTIMER_RegistAppEvent��ͬһHANDLEע����ͬEVENTIDʱ����
	
	YWTIMER_ERROR_EVENTID_NOT_EXIST,
	//��ʱ���¼������ڣ�����YWTIMER_UnRegistAppEvent��ע�᲻���ڵ�EVENTIDʱ����

	YWTIMER_ERROR_TIME_AUTO_UPDATING,
	//�Զ�����ʱ���������У�����YWTIMER_AutoTimeUpdateʱ����
	
	YWTIMER_ERROR_TIME_NOT_AUTO_UPDATE
	//�Զ�����ʱ��û�����У�����YWTIMER_CancelAutoTimeUpdateʱ����
};

enum
{
	YWTIMER_EVENT_APPLICATION = YW_MODULE_SET_ID( YWMID_MODULE_TIMER_ID),
	//��Ӧ�ó���ע��Ķ�ʱ���¼�

	YWTIMER_EVENT_AUTO_UPDATE_SUCCESS,
	//�Զ�����ʱ��ɹ���ͨ��YW_INVALID_HANDLE����
	
	YWTIMER_EVENT_AUTO_UPDATE_FAIL
	//�Զ�����ʱ��ʧ��(������ʱ������һ����)��ͨ��YW_INVALID_HANDLE����
};

#define YWTIMER_MAX_TIMER_NUM 100
#define YWTIMER_INFINITY_NUM 0xFFFFFFFF
#define YWTIMER_BOUND_INGORE    (0xFFFFFFFF)
/************************************���ݽṹ****************************************/

typedef U32 YWTIMER_Hdl_T;

typedef struct YWTIMER_CurTime_s
{
	U16 usYear;
	U8 ucMonth;
	U8 ucDate;
	U8 ucHour;
	U8 ucMinute;
	U8 ucSecond;
}YWTIMER_CurTime_T;//CurTime������ò�̫�ã���һ��ֻ���ڱ�ʾ��ǰʱ��

typedef struct YWTIMER_EventAppData_s
{
	U32 uiEventID;
	U64 uiTimeOut;//ÿ�����봦��һ��
    
	U32 uiStartTime;//��ʼʱ��
	U64 uiLastTime;//�����һ�¼���һ�δ���ʱ��

	U32 uiNumber;//�������¼��ص���Ҫ������
	U32 uiNo;//�Ѿ����˵ڼ���

}YWTIMER_EventAppData_T;

/************************************��������****************************************/

/***********************************************************************
TIMER�����ֹ���:1,��ʱ������,��ʱ����ĳ�¼�
                YWTIMER_Open��Զ�ʱ����,���к���������HANDLE,��Ϊ�Զ�ʱ���Ĳ���

                2,ʱ�����(����,����,��ȡʱ��)
                ���������������HANDLE,��Ϊ���ʱ�����Ĳ���

������Ϊ�����ֹ���Ӧ��Ϊ����ģ��ȥд
************************************************************************/

YW_ErrorType_T YWTIMER_Init(void);
YW_ErrorType_T YWTIMER_Term(void);
YW_ErrorType_T YWTIMER_Open(YWTIMER_Hdl_T * Handle);
YW_ErrorType_T YWTIMER_Close(YWTIMER_Hdl_T Handle);
YW_ErrorType_T YWTIMER_GetFeature(void * Feature);

/***********************************************************************
��������: YWTIMER_RegistAppEvent
��������: ע�ᶨʱ���¼�,ÿ����ʱ����ע���������¼�
************************************************************************/
YW_ErrorType_T YWTIMER_RegistAppEvent(YWTIMER_Hdl_T Handle,U32 TimerEventID);

/***********************************************************************
��������: YWTIMER_UnRegistAppEvent
��������: ��ע�ᶨʱ���¼�
************************************************************************/
YW_ErrorType_T YWTIMER_UnRegistAppEvent(YWTIMER_Hdl_T Handle,U32 TimerEventID);

/***********************************************************************
��������: YWTIMER_AppEventStart
��������: ��ʱ���¼���ʼ,ÿ���Interval����һ��,������Number���
************************************************************************/
YW_ErrorType_T YWTIMER_AppEventStart(YWTIMER_Hdl_T Handle, U32 TimerEventID, U64 Interval, U32 Number );

/***********************************************************************
��������: YWTIMER_AppEventStartGMT
��������: ��ʱ���¼���ʼ,GMTʱ��StartTime��ʼ������һ��,֮��ÿ��Interval����һ��,������Number���
************************************************************************/
YW_ErrorType_T YWTIMER_AppEventStartGMT(YWTIMER_Hdl_T Handle, U32 TimerEventID, YWTIMER_CurTime_T StartTime, U64 Interval,U32 Number );

/***********************************************************************
��������: YWTIMER_AppEventStartLocal
��������: ��ʱ���¼���ʼ,����ʱ��StartTime��ʼ������һ��,֮��ÿ��Interval����һ��,������Number���
************************************************************************/
YW_ErrorType_T YWTIMER_AppEventStartLocal(YWTIMER_Hdl_T Handle, U32 TimerEventID, YWTIMER_CurTime_T StartTime, U64 Interval,U32 Number );

/***********************************************************************
��������: YWTIMER_AppEventStop
��������: ֹͣ��ʱ���¼�
************************************************************************/
YW_ErrorType_T YWTIMER_AppEventStop(YWTIMER_Hdl_T Handle,U32 TimerEventID);

/***********************************************************************
��������: YWTIMER_GetCurGMT
��������: ��õ�ǰGMTʱ��,�����ռ����������
************************************************************************/
YW_ErrorType_T YWTIMER_GetCurGMT(YWTIMER_CurTime_T *CurGMT, U32 *CurGMTSeconds);

/***********************************************************************
��������: YWTIMER_GetCurGMT
��������: ��õ�ǰ����ʱ��,������
************************************************************************/
YW_ErrorType_T YWTIMER_GetCurTime(YWTIMER_CurTime_T *CurTime);

/***********************************************************************
��������: YWTIMER_AutoTimeUpdate
��������: �Զ�����ʱ��,�������л�ȡTDT����
************************************************************************/
YW_ErrorType_T YWTIMER_AutoTimeUpdate(U8 * pcSrcName);
/***********************************************************************
��������: YWTIMER_CancelAutoTimeUpdate
��������: ȡ���Զ�����ʱ��
************************************************************************/
YW_ErrorType_T YWTIMER_CancelAutoTimeUpdate(void);

/***********************************************************************
��������: YWTIMER_SetCurTime
��������: �ֶ�����ʱ��
************************************************************************/
YW_ErrorType_T YWTIMER_SetCurTime(YWTIMER_CurTime_T *CurTime);

/***********************************************************************
��������: YWTIMER_SetTimeOffset
��������: ����ʱ��ƫ��,��λΪ��
************************************************************************/
YW_ErrorType_T YWTIMER_SetTimeOffset(S32 TimeOffset);

/***********************************************************************
��������: YWTIMER_GetTimeOffset
��������: ��ȡʱ��ƫ��,��λΪ��
************************************************************************/
YW_ErrorType_T YWTIMER_GetTimeOffset(S32 *TimeOffset);
/***********************************************************************
��������: YWTIMER_SetAutoTimeUpdateBound
��������: �����Զ�����ʱ�����
************************************************************************/
YW_ErrorType_T YWTIMER_SetAutoTimeUpdateBound(U32 uBound);
#endif

