
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
    YWHTTPC_CMD_INTERRUPT,         /*�жϴ���*/
    YWHTTPC_CMD_QUIT
}YWHTTPC_Cmd_T;

typedef enum YWHTTPC_ErrorCode_e
{
    YWHTTPC_NO_ERROR,
    YWHTTPC_ERROR_USER_INTERRUPT,/*�û��ж����ݽ���*/
    YWHTTPC_ERROR_RCV_FAILED,           /*���ݽ���ʧ��*/
    YWHTTPC_ERROR_INVALID_LINK,         /*��Ч����*/
    YWHTTPC_ERROR_INVALID_CMD,        /*��Ч����*/
    YWHTTPC_ERROR_CREAT_FAILED,       /*socket ����ʧ��*/
    YWHTTPC_ERROR_CONNECT_FAILED,   /*����ʧ��*/
    YWHTTPC_ERROR_SEND_FAILED,          /*����ʧ��*/
    YWHTTPC_ERROR_UNKNOWN                   /*����δ֪*/
}YWHTTPC_ErrorCode_T;
typedef struct YWHTTPC_ReqParam_s
{
    S8 *  pcUrl;/*url*/
    S8 *  pcData;/*����������͵�����*/
    U32  uOffSetStart;/*���յ�ƫ�ƿ�ʼλ��*/
    U32  uOffSetEnd;/*���յ�ƫ�ƽ���λ��*/
    BOOL bSendSlice;/*�Ƿ���Ƭ��*/
    void * pPrivate;/*�û�˽�����ݣ���������*/
    void * pPrivate1;/*�û�˽�����ݣ���������*/
    BOOL bNotFollowLocation;/* redirection or not */
    YWHTTPC_Cmd_T eCmd;/*����*/
}YWHTTPC_ReqParams_T;
#if 0
typedef struct YWHTTPC_OpenParam_s
{
    U32 uTcpIpHandle;   /*tcpipЭ���handle, ����socketʱ��Ҫʹ��*/
}YWHTTPC_OpenParams_T;
#endif

typedef enum YWHTTPC_EventType_e
{
    YWHTTPC_EVENT_DATA=YW_MODULE_SET_ID(YWMID_MODULE_HTTPC_ID),
    YWHTTPC_EVENT_PROGRESS, /*��ǰ���յĽ���*/
    YWHTTPC_EVENT_ERROR,
    YWHTTPC_EVENT_FINISH,
    YWHTTPC_EVENT_LOCATION
}YWHTTPC_EventType_T;

typedef struct YWHTTPC_EventData_s
{
    YWHTTPC_EventType_T     EventType;
    YWHTTPC_Hdl_T      HttpcHandle;
    S8   * pcUrl;
    U8  * pcData;      /*������ݵ�ָ��*/
    U32   uDataLen; /*�ôη��͵����ݳ���*/
    U32   uFileLen;   /*�����ļ��ĳ��ȣ�������͵���Ƭ��, uDataLen��uFileLen���ܲ����*/
    void * pPrivate;  /*˽������,���������ָ�������*/
    void * pPrivate1;  /*˽������,���������ָ�������*/

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
    YWHTTPC_ErrorCode_T  eErrCode;      /*������*/
    void * pPrivate;  /*˽������,���������ָ�������*/
    void * pPrivate1;  /*˽������,���������ָ�������*/

}YWHTTPC_EventError_T;

typedef struct YWHTTPC_EventFinish_s
{
    YWHTTPC_EventType_T     EventType;
    YWHTTPC_Hdl_T           HttpcHandle;
    S8                      *pcUrl;
    void                    *pPrivate;  /*˽������,���������ָ�������*/
    void                    *pPrivate1;  /*˽������,���������ָ�������*/

}YWHTTPC_EventFinish_T;

typedef struct YWHTTPC_EventLocation_s
{
    S8   * pcUrl; /*redirection url*/
    void    *pPrivate;  /*˽������,���������ָ�������*/
    void    *pPrivate1;  /*˽������,���������ָ�������*/

}YWHTTPC_EventLocation_T;

typedef struct YWHTTPC_PostData_s
{
    S8 * name;
    S8 * string;/*����������͵�����*/
}YWHTTPC_PostData_T;

YW_ErrorType_T YWHTTPC_Init(void);
YW_ErrorType_T YWHTTPC_Open(YWHTTPC_Hdl_T * pHandle);//, YWHTTPC_OpenParams_T * pOpenParams);
YW_ErrorType_T YWHTTPC_Close(YWHTTPC_Hdl_T Handle);
YW_ErrorType_T YWHTTPC_Term(void);
YW_ErrorType_T YWHTTPC_SendRequest(YWHTTPC_Hdl_T Handle, YWHTTPC_ReqParams_T* ptReqParams);
YW_ErrorType_T YWHTTPC_StopRequest(YWHTTPC_Hdl_T Handle);
YW_ErrorType_T YWHTTPC_GetIntUrlAndOffset(YWHTTPC_Hdl_T Handle, S8 ** ppcUrl, U32 * uOffSet);/*��ȡ���жϵ�url�͵�ǰλ��*/
YW_ErrorType_T YWHTTPC_ReleaseIntUrlAndOffset(YWHTTPC_Hdl_T Handle);/*�ͷű��жϵ�url�͵�ǰλ��*/
YW_ErrorType_T YWHTTPC_SetConnectTimeout(YWHTTPC_Hdl_T Handle,U32 timeout);//timeout :��


#ifdef __cplusplus
}
#endif
#endif
