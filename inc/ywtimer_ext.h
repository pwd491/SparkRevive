/**********************************文件头部注释************************************/
//
//
//  					Copyright (C), 2005-2010, AV Frontier Tech. Co., Ltd.
//
//
// 文件名：		ywtimer_ext.h
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

#ifndef _YWTIMER_EXT_H
#define _YWTIMER_EXT_H

/************************************宏及常量****************************************/

//错误类型
enum
{
	YWTIMER_ERROR_WORKING = YW_MODULE_SET_ID( YWMID_MODULE_TIMER_ID),
	//定时器正在工作，调用YWTIMER_Close时返回
	
	YWTIMER_ERROR_EVENTID_EXIST,
	//定时器事件已存在，调用YWTIMER_RegistAppEvent对同一HANDLE注册相同EVENTID时返回
	
	YWTIMER_ERROR_EVENTID_NOT_EXIST,
	//定时器事件不存在，调用YWTIMER_UnRegistAppEvent反注册不存在的EVENTID时返回

	YWTIMER_ERROR_TIME_AUTO_UPDATING,
	//自动更新时间正在运行，调用YWTIMER_AutoTimeUpdate时返回
	
	YWTIMER_ERROR_TIME_NOT_AUTO_UPDATE
	//自动更新时间没有运行，调用YWTIMER_CancelAutoTimeUpdate时返回
};

enum
{
	YWTIMER_EVENT_APPLICATION = YW_MODULE_SET_ID( YWMID_MODULE_TIMER_ID),
	//由应用程序注册的定时器事件

	YWTIMER_EVENT_AUTO_UPDATE_SUCCESS,
	//自动更新时间成功，通过YW_INVALID_HANDLE传递
	
	YWTIMER_EVENT_AUTO_UPDATE_FAIL
	//自动更新时间失败(与现有时间相差超过一个月)，通过YW_INVALID_HANDLE传递
};

#define YWTIMER_MAX_TIMER_NUM 100
#define YWTIMER_INFINITY_NUM 0xFFFFFFFF
#define YWTIMER_BOUND_INGORE    (0xFFFFFFFF)
/************************************数据结构****************************************/

typedef U32 YWTIMER_Hdl_T;

typedef struct YWTIMER_CurTime_s
{
	U16 usYear;
	U8 ucMonth;
	U8 ucDate;
	U8 ucHour;
	U8 ucMinute;
	U8 ucSecond;
}YWTIMER_CurTime_T;//CurTime名字起得不太好，不一定只用于表示当前时间

typedef struct YWTIMER_EventAppData_s
{
	U32 uiEventID;
	U64 uiTimeOut;//每多少秒处理一次
    
	U32 uiStartTime;//开始时间
	U64 uiLastTime;//针对这一事件上一次处理时间

	U32 uiNumber;//针对这个事件回调需要做几次
	U32 uiNo;//已经做了第几次

}YWTIMER_EventAppData_T;

/************************************函数声明****************************************/

/***********************************************************************
TIMER有两种功能:1,定时器功能,定时触发某事件
                YWTIMER_Open针对定时器打开,所有函数中如有HANDLE,则为对定时器的操作

                2,时间管理(设置,更新,获取时间)
                函数中如参数不带HANDLE,则为针对时间管理的操作

个人认为这两种功能应分为两个模块去写
************************************************************************/

YW_ErrorType_T YWTIMER_Init(void);
YW_ErrorType_T YWTIMER_Term(void);
YW_ErrorType_T YWTIMER_Open(YWTIMER_Hdl_T * Handle);
YW_ErrorType_T YWTIMER_Close(YWTIMER_Hdl_T Handle);
YW_ErrorType_T YWTIMER_GetFeature(void * Feature);

/***********************************************************************
函数名称: YWTIMER_RegistAppEvent
函数功能: 注册定时器事件,每个定时器可注册任意多个事件
************************************************************************/
YW_ErrorType_T YWTIMER_RegistAppEvent(YWTIMER_Hdl_T Handle,U32 TimerEventID);

/***********************************************************************
函数名称: YWTIMER_UnRegistAppEvent
函数功能: 反注册定时器事件
************************************************************************/
YW_ErrorType_T YWTIMER_UnRegistAppEvent(YWTIMER_Hdl_T Handle,U32 TimerEventID);

/***********************************************************************
函数名称: YWTIMER_AppEventStart
函数功能: 定时器事件开始,每间隔Interval触发一次,共触发Number多次
************************************************************************/
YW_ErrorType_T YWTIMER_AppEventStart(YWTIMER_Hdl_T Handle, U32 TimerEventID, U64 Interval, U32 Number );

/***********************************************************************
函数名称: YWTIMER_AppEventStartGMT
函数功能: 定时器事件开始,GMT时间StartTime开始触发第一次,之后每隔Interval触发一次,共触发Number多次
************************************************************************/
YW_ErrorType_T YWTIMER_AppEventStartGMT(YWTIMER_Hdl_T Handle, U32 TimerEventID, YWTIMER_CurTime_T StartTime, U64 Interval,U32 Number );

/***********************************************************************
函数名称: YWTIMER_AppEventStartLocal
函数功能: 定时器事件开始,本地时间StartTime开始触发第一次,之后每隔Interval触发一次,共触发Number多次
************************************************************************/
YW_ErrorType_T YWTIMER_AppEventStartLocal(YWTIMER_Hdl_T Handle, U32 TimerEventID, YWTIMER_CurTime_T StartTime, U64 Interval,U32 Number );

/***********************************************************************
函数名称: YWTIMER_AppEventStop
函数功能: 停止定时器事件
************************************************************************/
YW_ErrorType_T YWTIMER_AppEventStop(YWTIMER_Hdl_T Handle,U32 TimerEventID);

/***********************************************************************
函数名称: YWTIMER_GetCurGMT
函数功能: 获得当前GMT时间,年月日及换算的秒数
************************************************************************/
YW_ErrorType_T YWTIMER_GetCurGMT(YWTIMER_CurTime_T *CurGMT, U32 *CurGMTSeconds);

/***********************************************************************
函数名称: YWTIMER_GetCurGMT
函数功能: 获得当前本地时间,年月日
************************************************************************/
YW_ErrorType_T YWTIMER_GetCurTime(YWTIMER_CurTime_T *CurTime);

/***********************************************************************
函数名称: YWTIMER_AutoTimeUpdate
函数功能: 自动更新时间,从码流中获取TDT更新
************************************************************************/
YW_ErrorType_T YWTIMER_AutoTimeUpdate(U8 * pcSrcName);
/***********************************************************************
函数名称: YWTIMER_CancelAutoTimeUpdate
函数功能: 取消自动更新时间
************************************************************************/
YW_ErrorType_T YWTIMER_CancelAutoTimeUpdate(void);

/***********************************************************************
函数名称: YWTIMER_SetCurTime
函数功能: 手动设置时间
************************************************************************/
YW_ErrorType_T YWTIMER_SetCurTime(YWTIMER_CurTime_T *CurTime);

/***********************************************************************
函数名称: YWTIMER_SetTimeOffset
函数功能: 设置时间偏移,单位为分
************************************************************************/
YW_ErrorType_T YWTIMER_SetTimeOffset(S32 TimeOffset);

/***********************************************************************
函数名称: YWTIMER_GetTimeOffset
函数功能: 获取时间偏移,单位为分
************************************************************************/
YW_ErrorType_T YWTIMER_GetTimeOffset(S32 *TimeOffset);
/***********************************************************************
函数名称: YWTIMER_SetAutoTimeUpdateBound
函数功能: 设置自动更新时间界限
************************************************************************/
YW_ErrorType_T YWTIMER_SetAutoTimeUpdateBound(U32 uBound);
#endif

