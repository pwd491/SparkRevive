#ifndef _YWHTTPC_H
#define _YWHTTPC_H

#ifdef __cplusplus
extern "C" {
#endif
typedef struct YWHTTPC_ResMng_s
{
    U32  uSockHandle;
    U32  uTcpIpHandle;
    U8 * pcBuf;
    U32  uBufSize;
    U32  uOffSet;/*断点偏移地址*/
    S8 * pcKeptUrl;/*断点的url，恢复时使用*/
    YWOS_ThreadID_T     HttpcThreadId; /*客户端所在线程的ID*/
    YWOS_MessageID_T   HttpcReqMsgQueueId;/*发送命令用的消息队列*/
    YWOS_MessageID_T   HttpcSynSemId;
    struct YWHTTPC_ResMng_s * pPrev;
    struct YWHTTPC_ResMng_s * pNext;
    U8 uRunningStatus;
    U32 nConnectTimeOut;
}YWHTTPC_ResMng_T;


//#define  YWHTTPC_STACK_SIZE   (32*1024)
//#define  YWHTTPC_THREAD_PRIORITY  (3)
#define  YWHTTPC_MAX_PACKET_SIZE (4*1024)

enum
{
    YWHTTPC_STOPED =0,
    YWHTTPC_RUNNING
}eRunningStatus;

enum
{
    E_SOCK_USER_INTERRUPT=-9,
    E_SOCK_RCV_FAILED,
    E_SOCK_INVALID_LINK,
    E_SOCK_INVALID_CMD,
    E_SOCK_CREAT_FAILED,
    E_SOCK_CONNECT_FAILED,
    E_SOCK_SEND_FAILED,
    E_SOCK_CONTINUE,
    E_SOCK_REDIRECTION,
    E_SOCK_RCV_SUCCESS=0,
    E_FILE_NOT_MODIFIED
};

#ifdef __ASYNC_CLOSE__
typedef enum YWHTTPC_MsgType_e
{
    YWHTTPC_MSGTYPE_CLOSE,
    YWHTTPC_MSGTYPE_QUIT
} YWHTTPC_MsgType_T;

typedef struct YWHTTPC_BufferMsg_s
{
    YWHTTPC_MsgType_T MsgType;
    YWHTTPC_Hdl_T pHandle;
} YWHTTPC_BufferMsg_T;
#endif  /* __ASYNC_CLOSE__ */


#ifdef __cplusplus
}
#endif
#endif

