/**********************************�ļ�ͷ��ע��************************************/
//
//
//  					Copyright (C), 2005-2010, AV Frontier Tech. Co., Ltd.
//
//
// �ļ�����		ywevt.h
//
// �����ߣ�		Maple
//
// ����ʱ�䣺	2008.5.5
//
// �ļ�������	�¼�ͷ�ļ�
//
// �޸ļ�¼��   ��       ��      ��      ��       �汾      �޶�
//				       ---------         ---------        -----        -----
//              		       2008.5.5           Maple       0.01           �½�
/*****************************************************************************************/


#ifndef __YWEVT_H__
#define __YWEVT_H__

#ifdef __cplusplus
extern "C" {
#endif


enum
{
    	YWEVT_ERROR_INIT  = YW_MODULE_SET_ID(YWOS_MODULE_EVT_ID),
	YWEVT_ERROR_TREM,
   	YWEVT_ERROR_BAD_PARAMETER,
	YWEVT_ERROR_ALREADY_INITIALIZED,
	YWEVT_ERROR_NO_INITIALIZED,
	YWEVT_ERROR_NO_MEMORY,
	YWEVT_ERROR_NO_FREE_INSTANCE,
	YWEVT_ERROR_INVALID_INSTANCE,
	YWEVT_ERROR_INVALID_HANDLE,
	YWEVT_ERROR_NO_SUBSCRIBE_HANDLE,
	YWEVT_ERROR_NO_SUBSCRIBE_EVENTTYPE,
	YWEVT_ERROR_NO_SUBSCRIBE_FUNC,
	YWEVT_ERROR_FUNC_ISEXIST				/*ͬһ�豸��ͬһ�¼����Ͳ� ��ע��ͬһ������*/
};

//�꼰����

typedef  void (*YWEVT_EventPoc_T)( U32 DrvHandle, YW_EventType_T EventType, void* EventData,  void * UserData);


YW_ErrorType_T YWEVT_Init(void);	
YW_ErrorType_T YWEVT_Term(void);	


YW_ErrorType_T YWEVT_SubscribeEvent ( 	U32 DrvHandle,
	                                     					YW_EventType_T  EventType,
	                                     					YWEVT_EventPoc_T EventPoc, 
	                                     					void * UserData  );
YW_ErrorType_T YWEVT_UnSubscribeEvent ( 	U32 DrvHandle,
	                                     					YW_EventType_T  EventType,
	                                     					YWEVT_EventPoc_T EventPoc );
YW_ErrorType_T YWEVT_Notify ( U32 DrvHandle,
	                              			YW_EventType_T  EventType,
                              				void* EventData );

U32  YWEVT_GetVersion( S8 *pchVer, U32 nSize  );                              				

#ifdef __cplusplus
}
#endif

#endif  

