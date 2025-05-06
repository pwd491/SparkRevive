
#ifndef _YWHTTPC_EXT_H
#define _YWHTTPC_EXT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef U32 YWHTTPC_Hdl_T;

typedef enum YWHTTPC_Cmd_e
{
    YWHTTPC_CMD_GET=0,       /*get*/
    YWHTTPC_CMD_POST,     /*post*/
    YWHTTPC_CMD_HEAD,         /*head*/
    YWHTTPC_CMD_INTERRUPT,         /*中断处理*/
    YWHTTPC_CMD_QUIT
}YWHTTPC_Cmd_T;

typedef enum YWHTTPC_ErrorCode_e
{
    YWHTTPC_NO_ERROR,
    YWHTTPC_ERROR_USER_INTERRUPT,/*用户中断数据接收*/
    YWHTTPC_ERROR_RCV_FAILED,           /*数据接收失败*/
    YWHTTPC_ERROR_INVALID_LINK,         /*无效链接*/
    YWHTTPC_ERROR_INVALID_CMD,        /*无效命令*/
    YWHTTPC_ERROR_CREAT_FAILED,       /*socket 创建失败*/
    YWHTTPC_ERROR_CONNECT_FAILED,   /*连接失败*/
    YWHTTPC_ERROR_SEND_FAILED,          /*发送失败*/
    YWHTTPC_ERROR_UNKNOWN                   /*错误未知*/
}YWHTTPC_ErrorCode_T;
typedef struct YWHTTPC_ReqParam_s
{
    S8 *  pcUrl;/*url*/
    S8 *  pcData;/*向服务器发送的数据*/
    U32  uOffSetStart;/*接收的偏移开始位置*/
    U32  uOffSetEnd;/*接收的偏移结束位置*/
    BOOL bSendSlice;/*是否发送片断*/
    void * pPrivate;/*用户私有数据，用于区分*/
    void * pPrivate1;/*用户私有数据，用于区分*/
    BOOL bNotFollowLocation;/* redirection or not */
    YWHTTPC_Cmd_T eCmd;/*命令*/
}YWHTTPC_ReqParams_T;
#if 0
typedef struct YWHTTPC_OpenParam_s
{
    U32 uTcpIpHandle;   /*tcpip协议的handle, 创建socket时需要使用*/
}YWHTTPC_OpenParams_T;
#endif

typedef enum YWHTTPC_EventType_e
{
    YWHTTPC_EVENT_DATA=YW_MODULE_SET_ID(YWMID_MODULE_HTTPC_ID),
    YWHTTPC_EVENT_PROGRESS, /*当前接收的进度*/
    YWHTTPC_EVENT_ERROR,
    YWHTTPC_EVENT_FINISH,
    YWHTTPC_EVENT_LOCATION
}YWHTTPC_EventType_T;

typedef struct YWHTTPC_EventData_s
{
    YWHTTPC_EventType_T     EventType;
    YWHTTPC_Hdl_T      HttpcHandle;
    S8   * pcUrl;
    U8  * pcData;      /*存放数据的指针*/
    U32   uDataLen; /*该次发送的数据长度*/
    U32   uFileLen;   /*整个文件的长度，如果发送的是片断, uDataLen和uFileLen可能不相等*/
    void * pPrivate;  /*私有数据,仅用于区分各个请求*/
    void * pPrivate1;  /*私有数据,仅用于区分各个请求*/

}YWHTTPC_EventData_T;

typedef struct YWHTTPC_EventProgress_s
{
    YWHTTPC_EventType_T     EventType;
    YWHTTPC_Hdl_T      HttpcHandle;
    S8   * pcUrl;
    U32 uWholeDataLen;
    U32 uLenReceived;
    U8   uProgress;       /*0-100*/
}YWHTTPC_EventProgress_T;

typedef struct YWHTTPC_EventError_s
{
    YWHTTPC_EventType_T     EventType;
    YWHTTPC_Hdl_T      HttpcHandle;
    S8   * pcUrl;
    YWHTTPC_ErrorCode_T  eErrCode;      /*错误码*/
    void * pPrivate;  /*私有数据,仅用于区分各个请求*/
    void * pPrivate1;  /*私有数据,仅用于区分各个请求*/

}YWHTTPC_EventError_T;

typedef struct YWHTTPC_EventFinish_s
{
    YWHTTPC_EventType_T     EventType;
    YWHTTPC_Hdl_T           HttpcHandle;
    S8                      *pcUrl;
    void                    *pPrivate;  /*私有数据,仅用于区分各个请求*/
    void                    *pPrivate1;  /*私有数据,仅用于区分各个请求*/

}YWHTTPC_EventFinish_T;

typedef struct YWHTTPC_EventLocation_s
{
    S8   * pcUrl; /*redirection url*/
    void    *pPrivate;  /*私有数据,仅用于区分各个请求*/
    void    *pPrivate1;  /*私有数据,仅用于区分各个请求*/

}YWHTTPC_EventLocation_T;

typedef struct YWHTTPC_PostData_s
{
    S8 * name;
    S8 * string;/*向服务器发送的数据*/
}YWHTTPC_PostData_T;

YW_ErrorType_T YWHTTPC_Init(void);
YW_ErrorType_T YWHTTPC_Open(YWHTTPC_Hdl_T * pHandle);//, YWHTTPC_OpenParams_T * pOpenParams);
YW_ErrorType_T YWHTTPC_Close(YWHTTPC_Hdl_T Handle);
YW_ErrorType_T YWHTTPC_Term(void);
YW_ErrorType_T YWHTTPC_SendRequest(YWHTTPC_Hdl_T Handle, YWHTTPC_ReqParams_T* ptReqParams);
YW_ErrorType_T YWHTTPC_StopRequest(YWHTTPC_Hdl_T Handle);
YW_ErrorType_T YWHTTPC_GetIntUrlAndOffset(YWHTTPC_Hdl_T Handle, S8 ** ppcUrl, U32 * uOffSet);/*获取被中断的url和当前位置*/
YW_ErrorType_T YWHTTPC_ReleaseIntUrlAndOffset(YWHTTPC_Hdl_T Handle);/*释放被中断的url和当前位置*/
YW_ErrorType_T YWHTTPC_SetConnectTimeout(YWHTTPC_Hdl_T Handle,U32 timeout);//timeout :秒


#ifdef __cplusplus
}
#endif
#endif
