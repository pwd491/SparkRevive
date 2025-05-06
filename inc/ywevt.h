/**********************************文件头部注释************************************/
//
//
//  					Copyright (C), 2005-2010, AV Frontier Tech. Co., Ltd.
//
//
// 文件名：		ywevt.h
//
// 创建者：		Maple
//
// 创建时间：	2008.5.5
//
// 文件描述：	事件头文件
//
// 修改记录：   日       期      作      者       版本      修定
//				       ---------         ---------        -----        -----
//              		       2008.5.5           Maple       0.01           新建
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
	YWEVT_ERROR_FUNC_ISEXIST				/*同一设备，同一事件类型不 能注册同一处理函数*/
};

//宏及常量

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

