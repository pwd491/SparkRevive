
/**********************************文件头部注释************************************/
/*****************************************************************************************/
/************************************文件包含****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ywdefs.h"
#include "ywos.h"
//#include "ywlib.h"

#include "ywtcpip.h"


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
typedef struct YWHTTPC_PostData_s
{
    S8 * name;
    S8 * string;/*向服务器发送的数据*/
}YWHTTPC_PostData_T;

typedef struct YWHTTPC_ReqParam_s
{
    S8 *  pcUrl;/*url*/
    U8 pcDataNum;
    YWHTTPC_PostData_T *pcData;/*向服务器发送的数据*/
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


/*********************************************************************/
typedef struct YWHTTPC_ResMng_s
{
    U32  uSockHandle;
    U32  uTcpIpHandle;
    U8 * pcBuf;
    U32  uBufSize;
    U32  uOffSet;/*断点偏移地址*/
    S8 * pcKeptUrl;/*断点的url，恢复时使用*/
    struct YWHTTPC_ResMng_s * pPrev;
    struct YWHTTPC_ResMng_s * pNext;
    U8 uRunningStatus;
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



#define HTTP_MAX_BUF_SIZE   (256*1024)
#define MAX_URL_LEN 1024
#define HTTP_ONCE_RECEIVE_LEN 4096
#define REDIRECTION_TIMES   10

#define YWHTTPC_BLOCK_STOP

static S8  *HTTPHEAD  		=  (S8 *)"http://";
#define     YWHTTPC_USER_INTERRUPT   (-9)

#define YWHTTPC_MAX_WAIT_TIME     (30)/*( YWOS_WAIT_INFINITY)*/
#define YWHTTPC_CONNECT_TIMEOUT     (10)
#define YWHTTPC_CONNECT_MAX_RETRY   (2)
#define YWMID_Trace(x) YWOS_Trace x


#if 0
#define  YWLIB_Memset(x,y,n)  memset(x,y,n)
#define YWLIB_Strlen(x)   strlen(x)
#define YWLIB_Strncpy(x,y,n)   strncpy(x,y,n)
#define YWOS_Calloc(x,n)   calloc(x,n)
#define YWLIB_Strcpy(x,y)   strcpy(x,y)
#define  YWLIB_Strncasecmp(x,y,n)  strncasecmp(x,y,n)
#define  YWLIB_Strchr(x,y)  strchr(x,y)
#define  YWLIB_Strcat(x,y)  strcat(x,y)
#define  YWOS_Free(x) free(x)
#define YWLIB_Strstr(x,y)  strstr(x,y)
#define  YWLIB_Memcpy(x,y,n) memcpy(x,y,n)
#define YWLIB_Atoi(x)  atoi(x)
#define YWLIB_Strcmp(x,y) strcmp(x,y)
#define YWLIB_Strncmp(x,y,n) strncmp(x,y,n)
#define YWLIB_Sprintf sprintf
#define YWLIB_Memmove(x,y,n)  memmove(x,y,n)
#define  YWOS_Malloc(x)   malloc(x)
#endif
#define  YWLIB_HtoNS(n)  htons(n)

static S8 hexchars[] = "0123456789abcdef";
static S32 YWHTTPC_GetRetCode(S8  * pcBuf)
{
    S32 nRet;
    S8  * pcCurPos;
    //nRet=J_HttpReadLine(pcBuf, nMaxLen);
    pcCurPos=pcBuf;
    while((*pcCurPos==' ' )&& (*pcCurPos!='\0'))
    {
		pcCurPos++;
    }
    if (sscanf((const char *)pcCurPos, "HTTP/1.%*d %03d",(S32*)&nRet)!=1)
		nRet=-1;
    //YWMID_Trace((YWOS_TRACE_INFO, "retcode = %d\n", nRet));
    return nRet;
}

static S32 YWHTTPC_ParseHeader(void  * pcBuf,S8  **ppcUrl, S32 * puDataLen)
{

    //S8  * pcHttpHeader;
    S32 nResult=E_SOCK_RCV_FAILED;
    S32 nRet;
    //S8  * pcBase = (S8 *)pcBuf;
    S8  * pcCurPos = (S8 *)pcBuf;
    //S32 nSearchCnt=0;
    if(pcBuf == NULL)   //jhy
       return E_SOCK_RCV_FAILED;

    while(100==(nRet=YWHTTPC_GetRetCode(pcCurPos)))
    {
		pcCurPos=YWLIB_Strstr(pcCurPos, (S8 *)"\r\n\r\n");
		if(pcCurPos!=NULL)
		{
			pcCurPos+=4;
		}
    }
    //YWOS_Trace(YWOS_TRACE_ERROR,"[YWHTTPC_ParseHeader]nRet=%d\n",nRet);
    switch(nRet)
    {

    case 200:
    case 206:/*部分内容*/
		while((pcCurPos=YWLIB_Strstr(pcCurPos, (S8 *)"\r\n")))
		{
			pcCurPos+=2;
			if(((pcCurPos[0]=='\r')&&(pcCurPos[1]=='\n'))/*||(nSearchCnt==2)*/)
			{
				/*头部已经找完*/
				break;
			}
			switch(pcCurPos[0])
			{
			case 'C':
				if(pcCurPos[9]=='e')/*Content-Length*/
				{
					if(sscanf((const char*)pcCurPos, "Content-Length: %d",puDataLen)!=1)
					{
						*puDataLen=0;
					}
				}
				break;

			case 'S':
#if 0
				{
					S8  acCookie[MAX_COOKIE_PROPERTY_LEN]={0};
					if(sscanf(pcCurPos,"Set-Cookie: %[^;]",acCookie)==1)
					{
						S32 nCookieLen=YWLIB_Strlen(acCookie);
						J_HttpSetCookieProperty( nIpAddr,acCookie, nCookieLen);
						* pbHaveCookie=TRUE;
						pcCurPos+=nCookieLen+12;
						nSearchCnt++;
						if(nSearchCnt>=2)
						{
							pcCurPos=YWLIB_Strstr(pcCurPos,"\r\n\r\n");
							if(pcCurPos!=NULL)
							{
								* pnHeadLen=(pcCurPos-pcBase)+4;
								return E_SOCK_RCV_SUCCESS;
							}
						}

					}
				}
#endif
				break;
			case 'L':
#if 0
				if(sscanf(pcCurPos,"Last-Modified: %s",pcLastModified)==1)
				{
					pcCurPos+=14;
					while(* pcCurPos==' ')
					{
						pcCurPos++;
					}
					YWLIB_Strncpy(pcLastModified,pcCurPos,DATE_LEN);
					pcCurPos = YWLIB_Strstr(pcCurPos,"\r\n\r\n");
					nSearchCnt++;
					if(nSearchCnt>=2)
					{
						if(pcCurPos!=NULL)
						{
							* pnHeadLen=(pcCurPos-pcBase)+4;
							return E_SOCK_RCV_SUCCESS;
						}
					}

				}
#endif
				break;
			default:
				break;

			}
		}
		nResult=E_SOCK_RCV_SUCCESS;

		break;
	case 301:
	case 302:
	case 303:
	case 307:
		{
			//redirection
			S8  * pcLocation;
			S8  * pcLocEnd;
			S8  * pNewUrl = NULL;
			S8 * pcUrl= *ppcUrl;
			pcLocation=YWLIB_Strstr(pcCurPos, (S8 *)"Location:");
			if(pcLocation!=NULL)
			{
				pcLocation+=9;
				while(*pcLocation==' ')
				{
					pcLocation++;
				}
				pcLocEnd=YWLIB_Strstr(pcLocation, (S8 *)"\r\n");
				if(NULL==pcLocEnd)
				{
					nResult=E_SOCK_RCV_FAILED;
				}
				else
				{
					S32 nCpyLen=pcLocEnd-pcLocation;

					if(YWLIB_Strncmp(pcLocation,HTTPHEAD,YWLIB_Strlen(HTTPHEAD))==0)
					{
						if(YWLIB_Strlen(pcUrl) <= nCpyLen)
						{
							YWOS_Free(pcUrl);
							pcUrl = YWOS_Calloc(1, nCpyLen+2);
							*ppcUrl = pcUrl;
							if(!pcUrl)
							{
								return E_SOCK_RCV_FAILED;
							}
						}
						YWLIB_Memcpy(pcUrl,pcLocation,nCpyLen);
						pcUrl[nCpyLen]='\0';
					}
					else
					{
						S8  * pcTmpURL;
						S8  * pcStr;
						U32 uLen=0;
						pcStr = pcTmpURL= *ppcUrl+YWLIB_Strlen(HTTPHEAD);
						if(pcLocation[0] == '/')
						{
                                                pcStr=YWLIB_Strchr(pcTmpURL,'/');
                                                if(pcStr)
                                                {
                                                    pcTmpURL=pcStr+1;
                                                }
                                                else
                                                {
                                                    return E_SOCK_RCV_FAILED;
                                                }
						}
						else
						{
						    while(NULL!=(pcStr=YWLIB_Strchr(pcTmpURL,'/')))
                                                {
                                                    pcStr+=1;
                                                    pcTmpURL=pcStr;
                                                }
						}
						if(NULL==pcTmpURL)
						{
						    return E_SOCK_RCV_FAILED;
						}
						uLen = pcTmpURL -*ppcUrl;
						if(YWLIB_Strlen(*ppcUrl) <= (nCpyLen+uLen))
						{
							if(!(pNewUrl = YWOS_Calloc(nCpyLen+uLen+2, 1)))
							{
								return E_SOCK_RCV_FAILED;
							}
							YWLIB_Memcpy(pNewUrl, *ppcUrl, uLen);
							YWOS_Free(*ppcUrl);
							*ppcUrl = pNewUrl;
							pcTmpURL = pNewUrl + uLen;
						}
						YWLIB_Memcpy(pcTmpURL,pcLocation,nCpyLen);
						//pcTmpURL[nCpyLen]=0;
					}
					nResult=E_SOCK_REDIRECTION;
				}
			}
			else
			{
				nResult=E_SOCK_RCV_FAILED;
			}

		}
		break;
	case 304:
		nResult=E_FILE_NOT_MODIFIED;
		break;
	default:
		break;

    }
    return nResult;

}
static  S32 YWHTTPC_ReceiveData(S32 sockfd, YWHTTPC_ResMng_T* pResMng, YWHTTPC_ReqParams_T * pReq)
{
    S32 nRcvLen,nTotalLen=0, nLenAll =0;
    S32 nResult;
    S32 uHeadLen =0, uDataLen = 0,uCurDataLen;
    S8 * pcRcvBuf = (S8 *)pResMng->pcBuf;
    S8 * pcBufEnd = (S8 *)pResMng->pcBuf + pResMng->uBufSize;
    S8 * pcData = pcRcvBuf;
    S8 * pcCurPos =pcRcvBuf;
    S32 nLeft=0;
    U8 uProgress =0;
    YWHTTPC_EventData_T     tEventData;
    YWHTTPC_EventProgress_T tEventProgress;
    YWHTTPC_EventFinish_T   tEventFinish;
    YW_ErrorType_T          ErrorCode = YW_NO_ERROR;
    YWTCPIP_FDSET_T         fd_set;
    YWTCPIP_TIMEVAL_T       timeout;
    U32                     ii=0;

    nRcvLen=0;
    nTotalLen=0;
    tEventData.EventType = YWHTTPC_EVENT_DATA;
    tEventData.HttpcHandle = (U32)pResMng;
    tEventData.pcUrl = pReq->pcUrl;
    tEventData.pPrivate = pReq->pPrivate;
    tEventData.pPrivate1 = pReq->pPrivate1;

    tEventProgress.EventType = YWHTTPC_EVENT_PROGRESS;
    tEventProgress.HttpcHandle = (U32)pResMng;
    tEventProgress.pcUrl = pReq->pcUrl;
    tEventProgress.uProgress = -1;

    YWLIB_Memset(&tEventFinish, 0, sizeof(YWHTTPC_EventFinish_T));
    tEventFinish.EventType = YWHTTPC_EVENT_FINISH;
    tEventFinish.HttpcHandle = (U32)pResMng;
    tEventFinish.pcUrl = pReq->pcUrl;
    tEventFinish.pPrivate = pReq->pPrivate;
    tEventFinish.pPrivate1 = pReq->pPrivate1;

    /*先接收头部信息*/
    while(1)
    {
        if(pResMng->uRunningStatus == YWHTTPC_STOPED)
        {
            return E_SOCK_USER_INTERRUPT;
        }


        for(ii=0;ii<YWHTTPC_MAX_WAIT_TIME;ii++)
        {
            if(pResMng->uRunningStatus == YWHTTPC_STOPED)
            {
                return E_SOCK_USER_INTERRUPT;

            }

            YWTCPIP_FD_ZERO(&fd_set);
            YWTCPIP_FD_SET(sockfd, &fd_set);

            timeout.TIMEVAL_SEC = 1;
            timeout.TIMDVAL_MSEC = 0;

            ErrorCode = YWTCPIP_Select(sockfd+1,&fd_set,NULL,NULL,&timeout);

            if(ErrorCode==0)
            {
                continue;
            }
            else
            {
                break;
            }
        }

        if((ErrorCode < 0) || (ii == YWHTTPC_MAX_WAIT_TIME))
        {
            return E_SOCK_RCV_FAILED;
        }
        nRcvLen =  YWTCPIP_Recv(sockfd, (void  *)pcRcvBuf+nTotalLen, HTTP_ONCE_RECEIVE_LEN);
        if (nRcvLen<=0)
        {
            break;
        }

        nTotalLen+=nRcvLen;
        pcRcvBuf[nTotalLen] = '\0';
        pcCurPos=YWLIB_Strstr(pcCurPos, (S8 *)"\r\n\r\n");/*已经收到完整头部信息*/
        if(pcCurPos!=NULL)
        {
            pcCurPos+=4;
            uHeadLen = pcCurPos -pcRcvBuf;
            pcData = pcCurPos;
            nLeft = nTotalLen -uHeadLen;
            break;
        }
    }
    nResult=YWHTTPC_ParseHeader(pcRcvBuf, &(pReq->pcUrl), &uDataLen);
    if( YWHTTPC_CMD_HEAD == pReq->eCmd)
    {
        switch(nResult)
        {
            case E_SOCK_REDIRECTION:
            case E_SOCK_RCV_SUCCESS:
            case E_FILE_NOT_MODIFIED:
                tEventFinish.pcUrl = pReq->pcUrl;
                //YWEVT_Notify((U32 )pResMng,  YWHTTPC_EVENT_FINISH, (void *)&tEventFinish);
                break;
             default:
                break;
        }
        return nResult;
    }
    //YWOS_Trace(YWOS_TRACE_ERROR,"[YWHTTPC_ReceiveData]info,YWHTTPC_ParseHeader(%s) return %d\n",pcRcvBuf,nResult);
    if(nResult!=E_SOCK_RCV_SUCCESS)//接收剩余数据后返回。
    {

        while(1)
        {
            if(pResMng->uRunningStatus == YWHTTPC_STOPED)
            {
                return E_SOCK_USER_INTERRUPT;
            }
            YWTCPIP_FD_ZERO(&fd_set);
            YWTCPIP_FD_SET(sockfd, &fd_set);

            for(ii=0;ii<YWHTTPC_MAX_WAIT_TIME;ii++)
            {

                if(pResMng->uRunningStatus == YWHTTPC_STOPED)
                {
                    return E_SOCK_USER_INTERRUPT;

                }

                YWTCPIP_FD_ZERO(&fd_set);
                YWTCPIP_FD_SET(sockfd, &fd_set);

                timeout.TIMEVAL_SEC = 1;
                timeout.TIMDVAL_MSEC = 0;

                ErrorCode = YWTCPIP_Select(sockfd+1,&fd_set,NULL,NULL,&timeout);

                if(ErrorCode==0)
                {
                    continue;
                }
                else
                {
                    break;
                }

            }
            if((ErrorCode<0)||(ii==YWHTTPC_MAX_WAIT_TIME))
            {
                return E_SOCK_RCV_FAILED;
            }
            nRcvLen =  YWTCPIP_Recv(sockfd, (void  *)pcRcvBuf+nTotalLen, HTTP_ONCE_RECEIVE_LEN);
            if (nRcvLen<=0)
            {
            break;
            }
        }
        //YWOS_TaskSleep(5000);
        return nResult;
    }
    if(uDataLen >0)
    {
        nLenAll = uHeadLen + uDataLen;
    }
    if(pReq->bSendSlice&&(nLeft >0))/*发送解析头部后剩下的数据*/
    {
        YWHTTPC_EventData_T tEventData;

        tEventData.EventType = YWHTTPC_EVENT_DATA;
        tEventData.HttpcHandle = (U32)pResMng;
        tEventData.pcUrl = pReq->pcUrl;
        tEventData.pcData = (U8*)pcCurPos;
        tEventData.uDataLen = nLeft;
        tEventData.uFileLen = uDataLen;
        tEventData.pPrivate = pReq->pPrivate;
        tEventData.pPrivate1 = pReq->pPrivate1;

        //YWEVT_Notify((U32 )pResMng,  YWHTTPC_EVENT_DATA, (void *) &tEventData);
    }
    pcCurPos = pcRcvBuf+nTotalLen;
    if(nLenAll >= pResMng->uBufSize)
    {
        //do something
        if((!pReq->bSendSlice)&&(nLenAll>0))
        {
            pcCurPos = YWOS_Malloc(nLenAll+HTTP_ONCE_RECEIVE_LEN+1);
            if(!pcCurPos)
            {
                YWMID_Trace((YWOS_TRACE_ERROR, "[YWHTTPC_ReceiveData] Error, no memory, len=%d\n",nLenAll));
                return E_SOCK_RCV_FAILED;
            }
            pcCurPos[nLenAll] = '\0';

            pResMng->pcBuf = (U8 *)pcCurPos;
            pResMng->uBufSize = (U32)nLenAll+HTTP_ONCE_RECEIVE_LEN+1;
            pcBufEnd = (S8 *)pResMng->pcBuf + pResMng->uBufSize;
            if(nLeft >0)
            {
                YWLIB_Memcpy(pcCurPos, pcData, nLeft);
                pcCurPos += nLeft;
            }
            pcData = (S8 *)pResMng->pcBuf;
            YWOS_Free(pcRcvBuf);
            pcRcvBuf = (S8*)pResMng->pcBuf;
        }
    }
    /*接收数据*/
    uCurDataLen = nLeft;

    while(1)
    {
        if(pResMng->uRunningStatus == YWHTTPC_STOPED)
        {
            nRcvLen = E_SOCK_USER_INTERRUPT;
            break;
        }
        for(ii = 0; ii < YWHTTPC_MAX_WAIT_TIME; ii++)
        {
            if(pResMng->uRunningStatus == YWHTTPC_STOPED)
            {
                return E_SOCK_USER_INTERRUPT;
            }
            YWTCPIP_FD_ZERO(&fd_set);
            YWTCPIP_FD_SET(sockfd, &fd_set);
            timeout.TIMEVAL_SEC = 1;
            timeout.TIMDVAL_MSEC = 0;

            ErrorCode = YWTCPIP_Select(sockfd+1,&fd_set,NULL,NULL,&timeout);
            //YWOS_Trace(YWOS_TRACE_INFO, "YWTCPIP_Select = %d\n", ErrorCode);
            if( ErrorCode == 0)
            {
                continue;
            }
            else
            {
                break;
            }
        }

        if((ErrorCode < 0)||(ii == YWHTTPC_MAX_WAIT_TIME))
        {
            nRcvLen = -1;
            return E_SOCK_RCV_FAILED;
        }

        nRcvLen =  YWTCPIP_Recv(sockfd,(void *) pcCurPos, HTTP_ONCE_RECEIVE_LEN);
        if(nRcvLen<=0)
        {
            //YWMID_Trace((YWOS_TRACE_ERROR, "YWTCPIP_Recv return %d\n", nRcvLen));
            break;
        }
        if(pReq->bSendSlice)
        {
            YWHTTPC_EventData_T tEventData;

            tEventData.EventType = YWHTTPC_EVENT_DATA;
            tEventData.HttpcHandle = (U32)pResMng;
            tEventData.pcUrl = pReq->pcUrl;
            tEventData.pcData = (U8 *)pcCurPos;
            tEventData.uDataLen = nRcvLen;
            tEventData.uFileLen = uDataLen;
            tEventData.pPrivate = pReq->pPrivate;
            tEventData.pPrivate1 = pReq->pPrivate1;

            //YWEVT_Notify((U32 )pResMng,  YWHTTPC_EVENT_DATA, (void *) &tEventData);
        }
        else
        {
            pcCurPos += nRcvLen;
            if((pcCurPos+HTTP_ONCE_RECEIVE_LEN )>pcBufEnd)/*可能存放不下一桢数据*/
            {
                YWMID_Trace((YWOS_TRACE_ERROR, "[YWHTTPC_ReceiveData]Error,space no enough, 0x%x, 0x%x\n", pcCurPos+HTTP_ONCE_RECEIVE_LEN, pcBufEnd));
                return E_SOCK_RCV_FAILED;
            }
        }

        nTotalLen += nRcvLen;
        uCurDataLen +=nRcvLen;

        if((nLenAll>0)&&( nTotalLen>=nLenAll))
        {
           // YWMID_Trace((YWOS_TRACE_ERROR, "[YWHTTPC_ReceiveData]recv over\n"));
            break;
        }

        if(uDataLen)
        {
            unsigned long long llCurDataLen = (unsigned long long)uCurDataLen;
            unsigned long long llDataLen = (unsigned long long)uDataLen;
            uProgress = (U32)((llCurDataLen * 100)/(llDataLen));
            //YWOS_Trace(YWOS_TRACE_INFO, "uProgress = %d\n", uProgress);
        }
        else
        {
            tEventProgress.uProgress =-1;
        }
        if(uProgress!=tEventProgress.uProgress)
        {
            tEventProgress.uWholeDataLen = uDataLen;
            tEventProgress.uLenReceived = uCurDataLen;
            tEventProgress.uProgress = uProgress;

            //YWEVT_Notify((U32 )pResMng,  YWHTTPC_EVENT_PROGRESS, (void *) &tEventProgress);
        }

    }

    if(nRcvLen<0)
    {
        if(YWHTTPC_USER_INTERRUPT == nRcvLen)/*用户中断了数据接收，保存断点和url*/
        {
            pResMng->uOffSet = nTotalLen - uHeadLen;
            if(NULL!=pResMng->pcKeptUrl)
            {
                YWOS_Free(pResMng->pcKeptUrl);
            }
            //pResMng->pcKeptUrl = YWHTTPC_Strdup(pReq->pcUrl);

            return E_SOCK_USER_INTERRUPT;
        }
        else
        {
            return E_SOCK_RCV_FAILED;
        }
    }
    tEventProgress.uProgress = 100;
    tEventProgress.uWholeDataLen = uDataLen;
    tEventProgress.uLenReceived = uCurDataLen;
    //YWEVT_Notify((U32 )pResMng,  YWHTTPC_EVENT_PROGRESS, (void *) &tEventProgress);

    //YWOS_TaskSleep(3000);

    if(!pReq->bSendSlice)
    {
        if(0==uDataLen)
        {
            uDataLen = nTotalLen - uHeadLen;
        }

        tEventData.pcData = (U8 *)pcData;
        tEventData.uDataLen = uDataLen;
        tEventData.uFileLen = uDataLen;
        tEventData.pPrivate = pReq->pPrivate;
        tEventData.pPrivate1 = pReq->pPrivate1;

        pcRcvBuf[nTotalLen] = '\0';//作为字符串处理
        //YWOS_Trace(YWOS_TRACE_INFO, "[YWHTTPC_ReceiceData]stage=%d\n",(*(U8 *)(tEventData.pPrivate1)));

        //YWEVT_Notify((U32 )pResMng,  YWHTTPC_EVENT_DATA, (void *) &tEventData);
    }
    
   // YWEVT_Notify((U32 )pResMng,  YWHTTPC_EVENT_FINISH, (void *)&tEventFinish);

    return nTotalLen;
}

static YW_ErrorType_T YWHTTPC_UrlEncode(S8  * pcInStr , S32 nInStrLen , S8 * pcOutBuf, S32 * pnOutLen)
{
    register U8  c;
    U8  *to, *start;
    U8  const *from, *end;
    YW_ErrorType_T ErrorCode = YW_NO_ERROR;
    if(!pcInStr || !pcOutBuf || !pnOutLen)
    {
        return YWMID_ERROR_BAD_PARAMETER;
    }
    from = (U8*)pcInStr;
    end = (U8*)(pcInStr + nInStrLen);
    start = to = (U8  *) pcOutBuf/*YWOS_Malloc(3* len+1)*/;
    if(* pnOutLen < (3* nInStrLen+1))
    {
        YWOS_Trace(YWOS_TRACE_ERROR, "out buf size too small: %d\n", * pnOutLen);
        return YWMID_ERROR_NO_MEMORY;
    }
    while (from < end) 
    {
        c = *from++;
        //prS32f("%d\n" , c);
        if (c == ' ') 
        {
            *to++ = '+';
        } 
        else if ((c < '0' && c != '-' && c != '.') ||    (c < 'A' && c > '9') ||
                    (c > 'Z' && c < 'a' && c != '_') ||     (c > 'z')) 
        {
            to[0] = '%';
            to[1] = hexchars[c >> 4];
            to[2] = hexchars[c & 15];
            to += 3;
        } 
        else 
        {
            *to++ = c;
        }
    }
    *to = 0;
   
    *pnOutLen = to - start;
  
    return ErrorCode;
}
static U16  YWHTTPC_GetPort(S8  *url)
{
    U16   port;
    S8  *portStrP,*portStrP_E;
    S8   portStr[10] = {0};

    port = 80;
    if(url == NULL) return port;

    portStrP = YWLIB_Strchr(url,':');
    if(portStrP != NULL)
    {
		portStrP_E = YWLIB_Strchr(url,'/');
		YWLIB_Memset(portStr,0,10);
		if(NULL != portStrP_E)
		{
		        S32 nLen = portStrP_E  - portStrP;
		        if(nLen>=10)
		            nLen = 9;
			YWLIB_Memcpy(portStr,portStrP+1, nLen);
		}
		else
		{
			YWLIB_Strncpy(portStr,portStrP+1, 9);
		}
		port = (YWLIB_Atoi(portStr));
		if(port<=0)
		{
			port = 80;
		}
    }
    return  port;
}



//  added 2009/12/14 jhy,from SPARK
//  timeout unit :ms
//  return value :0:success;-1:ERROR;-2 :user interrupt
static S32 YWHTTPC_Connect_Timeout (U32 handle,U32 fd,  S32 *addr, U32 addrlen,U32 timeout)
{
    YWTCPIP_FDSET_T set;
    YWTCPIP_TIMEVAL_T timeo = {0, 0};
    S32 retval, savefl;
	YW_ErrorType_T ErrorCode = YW_NO_ERROR;
    U32 ii = 0;
    YWHTTPC_ResMng_T *pHttpcRes = (YWHTTPC_ResMng_T *)handle;

    savefl = YWTCPIP_FCNTLPARAM_O_BLOCK;
  //  savefl = YWTCPIP_Fcntl(fd, YWTCPIP_F_GETFL,YWTCPIP_FCNTLPARAM_NOARGS);    /*save file state*/
    YWTCPIP_Fcntl(fd, YWTCPIP_F_SETFL, /*savefl | */YWTCPIP_FCNTLPARAM_O_NONBLOCK);

	ErrorCode = YWTCPIP_Connect(fd, (YWTCPIP_SOCKETADDRESS_T *)addr, addrlen);
    if(ErrorCode == 0)
    {
        YWTCPIP_Fcntl(fd, YWTCPIP_F_SETFL, savefl);
        //YWOS_Trace(YWOS_TRACE_INFO,"[YWHTTPC_Connect_Timeout] connect---1 ok!\n");
        return 0;
    }

    if(ErrorCode != YWTCPIP_ERROR_INPROGRESS)
    {
        YWTCPIP_Fcntl(fd, YWTCPIP_F_SETFL, savefl);
        YWOS_Trace(YWOS_TRACE_ERROR,"[YWHTTPC_Connect_Timeout]Error,connect error.\n");
        return -1;
    }

    YWTCPIP_FD_ZERO(&set);
    YWTCPIP_FD_SET(fd, &set);

    for(ii =0;ii<timeout;ii++)
    {
        if(pHttpcRes->uRunningStatus ==YWHTTPC_STOPED)
        {
            YWTCPIP_Fcntl(fd, YWTCPIP_F_SETFL, savefl);
            YWOS_Trace(YWOS_TRACE_ERROR,"[YWHTTPC_Connect_Timeout]Error, User interupt!\n");
            return -2;

        }
        timeo.TIMEVAL_SEC = 1;
        timeo.TIMDVAL_MSEC = 0;
        retval = YWTCPIP_Select(fd+1, NULL, &set, NULL, &timeo);

        if (retval == -1)
        {
            YWTCPIP_Fcntl(fd, YWTCPIP_F_SETFL, savefl);
            YWOS_Trace(YWOS_TRACE_ERROR,"[YWHTTPC_Connect_Timeout]Error, select error \n");
            return -1;
        }
        else if(retval == 0)
        {
            /*YWTCPIP_Fcntl(fd, YWTCPIP_F_SETFL, savefl);
            YWOS_Trace(YWOS_TRACE_ERROR,"[YWHTTPC_Connect_Timeout]Error, select timeout.\n");
            return -1;*/
            YWOS_Trace(YWOS_TRACE_ERROR,"[YWHTTPC_Connect_Timeout]Error, select timeout.\n");

            continue;
        }

        if(YWTCPIP_FD_ISSET (fd,&set))
        {
            S32 error = 0;
            S32 len = sizeof (error);

            if(YWTCPIP_GetSocketOpt(fd, 1,YWTCPIP_SO_ERROR, &error, &len) < 0)
            {
                YWTCPIP_Fcntl(fd, YWTCPIP_F_SETFL, savefl);
                YWOS_Trace(YWOS_TRACE_ERROR,"[YWHTTPC_Connect_Timeout]Error, getsockopt fail, connect fail.\n");
                return -1;
            }

            if(0 == error)
            {
                YWTCPIP_Fcntl(fd, YWTCPIP_F_SETFL, savefl);
                //YWOS_Trace(YWOS_TRACE_INFO,"[YWHTTPC_Connect_Timeout] connect---2 ok!\n");
                return 0;
            }
            else
            {
                YWTCPIP_Fcntl(fd, YWTCPIP_F_SETFL, savefl);
                YWOS_Trace(YWOS_TRACE_ERROR,"[YWHTTPC_Connect_Timeout]Error, connect fail!\n");
                return -1;
            }

        }
    }

    if(ii==timeout)
    {
        YWTCPIP_Fcntl(fd, YWTCPIP_F_SETFL, savefl);
        YWOS_Trace(YWOS_TRACE_ERROR,"[YWHTTPC_Connect_Timeout]Error,wait timeout.\n");
        return -1;

    }

    return 0;
}

static S32 YWHTTPC_FormHeader(S8  * pcSendBuf, YWHTTPC_ReqParams_T * pReq, S8  * pcFilePath,S8  * pcHost)
{
    S8  *HTTPGET   	       =  (S8 *)"GET ";
    S8  *HTTPHEAD   	       =  (S8 *)"HEAD ";

    S8  *HTTPPOST  	       =  (S8 *)"POST ";
    //S8  *FILEHEAD        	=  (S8 *)"HEAD ";
    S8  *HTTP_VEC 	       =  (S8 *)" HTTP/1.0\r\nAccept-language: en\r\n";
    S8  *HTTPACCEPT 	=  (S8 *)"Accept: */*\r\n";
    S8  *User_Agent	      	=  (S8 *)"User-Agent:  Mozilla/4.0 \r\n";
    S8  *HOST			=  (S8 *)"Host: ";
    //S8  *Content_Type      =  (S8 *)"Content-Type: application/x-www-form-urlencoded\r\n";
    S8  *Content_Length	=  (S8 *)"Content-Length: ";
    //S8  *Connection	       =  (S8 *)"Connection: Keep-Alive\r\n";
    S8  *Connection		=  (S8 *)"Connection: close\r\n";
    S8  *Cache_Control	=  (S8 *)"Cache-Control: no-cache\r\n";
    //S8  * Cookie			=  (S8 *)"Cookie: ";
    //S8  * If_Modified_Since = (S8 *)"If-Modified-Since: ";
    S32  nResult;
    //S32  nStrLen=0;
    U32 nDataLen = 0;
    S8  * pcDataEncode = NULL;
	S32 nDataEncodeLen = 0;
    U32 uCmd = pReq->eCmd;
    YWHTTPC_PostData_T * pcData = pReq->pcData;
    U8 i =0;
    U32 TotaldataLen =0;

    nResult=E_SOCK_RCV_SUCCESS;
    switch(uCmd)
    {
	case YWHTTPC_CMD_GET:

	case YWHTTPC_CMD_HEAD:
        if(uCmd==YWHTTPC_CMD_HEAD)
		{
		    YWLIB_Strcpy(pcSendBuf, HTTPHEAD);
		}
		else
		{
		    YWLIB_Strcpy(pcSendBuf, HTTPGET);
		}

		YWLIB_Strcat(pcSendBuf,pcFilePath);

		/* if(pcData != NULL && nDataLen !=0)
		{
		YWLIB_Strcat(pcSendBuf,(S8  *)pcData);
	    }*/

		YWLIB_Strcat(pcSendBuf,HTTP_VEC);
		YWLIB_Strcat(pcSendBuf,HTTPACCEPT);

		YWLIB_Strcat(pcSendBuf,User_Agent);
		YWLIB_Strcat(pcSendBuf,HOST);
		YWLIB_Strcat(pcSendBuf,pcHost);
		// YWLIB_Strcat(pcSendBuf,"www.youtube.com");
		YWLIB_Strcat(pcSendBuf, (S8 *)"\r\n");
		YWLIB_Strcat(pcSendBuf,Connection);
		if((pReq->uOffSetStart!=0)||(pReq->uOffSetEnd!=0))
		{
			S8 * pcStr;
			YWLIB_Strcat(pcSendBuf, (S8 *)"Range: bytes=");
			pcStr = pcSendBuf+YWLIB_Strlen(pcSendBuf);
			YWLIB_Sprintf(pcStr, (S8 *)"%d-", pReq->uOffSetStart);
			if(pReq->uOffSetEnd!=0)
			{
				pcStr = pcSendBuf+YWLIB_Strlen(pcSendBuf);
				YWLIB_Sprintf(pcStr, (S8 *)"%d", pReq->uOffSetEnd);
			}
			YWLIB_Strcat(pcSendBuf, (S8 *)"\r\n");
		}
		YWLIB_Strcat(pcSendBuf, (S8 *)"\r\n");

		break;
	case YWHTTPC_CMD_POST:
		if(pcData != NULL)
		{
		    while(i<pReq->pcDataNum&&pcData!=NULL)
			{
			    nDataLen += YWLIB_Strlen(pcData->name)+YWLIB_Strlen(pcData->string)+1;
			    if(i!=0)
			    {
			        nDataLen+=1;
			    }
			    i++;
			    pcData++;
			}
		}
		nDataEncodeLen = nDataLen*3+1;
		pcDataEncode = YWOS_Malloc(nDataEncodeLen);
		if(pcDataEncode == NULL)
		{
		    return E_SOCK_SEND_FAILED;
		}
        YWLIB_Memset(pcDataEncode,0,nDataLen*3+1);

		pcData = pReq->pcData;
        if(pcData != NULL)
		{
		    i=0;
		    TotaldataLen =0;
		    while(i<pReq->pcDataNum)
		    {
		        if(i!=0)
		        {
         		    YWLIB_Strcat(pcDataEncode+TotaldataLen,(S8  *)"&");	
         		    TotaldataLen+=1;
		        }
        	    nDataEncodeLen =nDataLen*3+1-TotaldataLen ;
		        YWHTTPC_UrlEncode(pcData->name, YWLIB_Strlen(pcData->name), pcDataEncode+TotaldataLen, &nDataEncodeLen);
                TotaldataLen+=nDataEncodeLen;
        	    YWLIB_Strcat(pcDataEncode+TotaldataLen,(S8  *)"=");
        	    TotaldataLen+=1;
        	    nDataEncodeLen =nDataLen*3+1-TotaldataLen ;
		        YWHTTPC_UrlEncode(pcData->string, YWLIB_Strlen(pcData->string), pcDataEncode+TotaldataLen, &nDataEncodeLen);
                TotaldataLen+=nDataEncodeLen;
        		pcData++;
        		i++;

		    }

		}
		
		
		//YWHTTPC_UrlEncode(pcData, nDataLen, pcDataEncode, &nDataEncodeLen);
		YWLIB_Sprintf(pcSendBuf, (S8 *)"%s%s%s%s%s%s%s\r\n%s%d\r\n%s%s",
            			HTTPPOST,
            			pcFilePath,
            			HTTP_VEC,
            			HTTPACCEPT,
            			User_Agent,
            			HOST,
            			pcHost,
            			Content_Length,
            			TotaldataLen,
            			Connection,
            			Cache_Control
            			);

            			

		YWLIB_Strcat(pcSendBuf, (S8 *)"\r\n");
		
		if(pcDataEncode != NULL)
		{
		   
            YWLIB_Strcat(pcSendBuf,pcDataEncode);
            
			YWOS_Free(pcDataEncode);
			pcDataEncode = NULL;
		}
		else
		{
		    YWLIB_Strcat(pcSendBuf, (S8 *)"\r\n");
		}
		break;
	default:
		nResult=E_SOCK_INVALID_CMD;
		break;

    }
    return nResult;
}

/*
*****************************************************************************
   名称: YWHTTPC_ReqProcess

	输入: pcUrl－[输入]请求的URL

				uCmd－[输入]请求的命令（GET/POST/freqency）；

				pcData－[输入]请求附带的数据，只对双向网络（HTTP）有意义；

				nDatalen－[输入]请求附带数据的长度，只对双向网络（HTTP）有意义(Datalen在命令为“NETWORK_DVB_FREQUENCY”时代表频率值)

				输出: o_ppcData  -获取到的文件数据
				o_pnFileSize -获取到的文件长度

				返回: J_SUCCESS  － 成功

				J_FAILURE 　－ 失败

				功能: 该模块用来处理浏览器发送过来请求
*******************************************************************************/

static S32 YWHTTPC_ReqProcess(YWHTTPC_ResMng_T* pResMng, YWHTTPC_ReqParams_T * pReq, U8  ** o_ppcData, S32 * o_pnFileSize)
{
	YW_ErrorType_T ErrorCode = YW_NO_ERROR;
	S32  nResult;
	S32  data_index,nReceiveLen,nAllRcvLen;
	U16 nHttpPort;
	//S8   hostTmp[256]={0};
	S8   acHost[512]={0};
	S8  *tmpP_s;
	S8  *tmpP;
	S8  * pcHttpIp=NULL;
	S32 nRet = YW_NO_ERROR;
	S8  * pcTmpBuf=NULL;
	S8  * pcFilePath;
       S8 * pcRoot =(S8*) "/";
	S32 nTmpBufSize=0;
	U32 uSock;

	if(!pReq)
		return E_SOCK_INVALID_CMD;

	pcHttpIp = pReq->pcUrl;

	nResult = E_SOCK_RCV_SUCCESS;
	if(pcHttpIp == NULL||YWLIB_Strstr(pcHttpIp,HTTPHEAD) == NULL)
	{
		YWOS_Trace(YWOS_TRACE_INFO, "[YWHTTPC_ReqProcess]Error,invalid link!\n");
		nResult = E_SOCK_INVALID_LINK;
		return nResult;
	}
	nResult = E_SOCK_RCV_SUCCESS;
        
        #if 0
	nHttpPort = YWHTTPC_GetPort(pcHttpIp+YWLIB_Strlen(HTTPHEAD));
	tmpP = pcHttpIp+YWLIB_Strlen(HTTPHEAD);
	YWLIB_Memset(hostTmp,0,256);

	tmpP_s = YWLIB_Strchr(tmpP,':');
	if(tmpP_s == NULL)
	{
		tmpP_s = YWLIB_Strchr(tmpP,'/');
		pcFilePath=tmpP_s;
	}
	else
	{
		pcFilePath = YWLIB_Strchr(tmpP,'/');
		if(NULL==pcFilePath)
		{
			YWMID_Trace((YWOS_TRACE_ERROR, "[YWHTTPC_ReqProcess]Error,invalid link!\n"));
			return E_SOCK_INVALID_LINK;
		}
	}
	if(tmpP_s != NULL)
	{
		YWLIB_Memcpy(hostTmp,tmpP,tmpP_s - tmpP);
		YWLIB_Strcpy(acHost,hostTmp);
	}
	else
	{
		YWMID_Trace((YWOS_TRACE_ERROR, "[YWHTTPC_ReqProcess]Error,invalid link2!\n"));
		return E_SOCK_INVALID_LINK;
	}
       #else
       tmpP = pcHttpIp+YWLIB_Strlen(HTTPHEAD);
        pcFilePath = YWLIB_Strchr(tmpP,'/');
        if(NULL==pcFilePath)
        {
        	pcFilePath = pcRoot;
        	YWLIB_Memcpy(acHost, tmpP, YWLIB_Strlen(tmpP));
        }
        else
        {
            YWLIB_Memcpy(acHost, tmpP, pcFilePath -tmpP);
        }
        nHttpPort = YWHTTPC_GetPort(acHost);
        tmpP_s = YWLIB_Strchr(acHost,':');
        if(tmpP_s!=NULL)
        {
            *tmpP_s = 0;
        }
        //YWLIB_Strcpy(acHost,hostTmp);
       #endif
	nResult=E_SOCK_RCV_SUCCESS;
	//YWHTTPC_GetTmpBuf(&pcTmpBuf, &nTmpBufSize);
	//YWLIB_Memset(pcTmpBuf, 0, nTmpBufSize);
	pcTmpBuf = (S8 *)pResMng->pcBuf;
	nTmpBufSize = pResMng->uBufSize;
	if(!pcTmpBuf)
	{
		return E_SOCK_SEND_FAILED;
	}
	ErrorCode = YWTCPIP_Socket(&uSock,YWTCPIP_PF_INET,YWTCPIP_SOCKETTYPE_STREAM,6);
	pResMng->uSockHandle = uSock;
	if(uSock != 0)
	{
        YWTCPIP_SOCKETADDRESSIN_T  destAddr={0};
        YWTCPIP_HOSTINFO_T remoteHost ,*phost ;
        U8  dns_buff[8192];
        S32  h_errnop = 0;
        S8 ** pptr = NULL;
        U8 uIpCount =0;
        destAddr.SOCKETADDRESSIN_Family = 2;
        destAddr.SOCKETADDRESSIN_Port = YWLIB_HtoNS(nHttpPort);

		//remoteHost = YWTCPIP_GetHostByName(acHost);
		ErrorCode = YWTCPIP_GetHostByName_r(acHost,&remoteHost,dns_buff, sizeof(dns_buff), &phost, &h_errnop);
        if(phost==NULL||ErrorCode!=YW_NO_ERROR)
		{
		    YWOS_Trace(YWOS_TRACE_INFO, "[YWHTTPC_ReqProcess]Error,remost host is null\n");
		    YWTCPIP_CloseSocket(uSock);
		    uSock = 0;
		    return E_SOCK_INVALID_LINK;
		}

        for (pptr = remoteHost.pAddresslist; *pptr != NULL; pptr++)
        {
                S32 i;
                YWLIB_Memmove(&destAddr.SOCKETADDRESSIN_IP , *pptr,4);
                
                for(i=0; i<YWHTTPC_CONNECT_MAX_RETRY; i++)
                {
                    nRet = YWHTTPC_Connect_Timeout((U32)pResMng,uSock,(S32 *)&(destAddr),sizeof(destAddr),YWHTTPC_MAX_WAIT_TIME);

                    if((YW_NO_ERROR == nRet) ||(-2==nRet))
                    {
                        break;
                    }
                    else
                    {
                        YWTCPIP_CloseSocket(uSock);
                        uSock = 0;
                        ErrorCode = YWTCPIP_Socket(&uSock,YWTCPIP_PF_INET,YWTCPIP_SOCKETTYPE_STREAM,0);
                        if(ErrorCode!=YW_NO_ERROR)
                        {
                            return E_SOCK_CONNECT_FAILED;
                        } 
                    }
                }
                
                if((YW_NO_ERROR == nRet) ||(-2==nRet))/*连接成功或者用户中断*/
                {
                    break;
                }
                else
                {
                    YWTCPIP_CloseSocket(uSock);
                    uSock = 0;
                    ErrorCode = YWTCPIP_Socket(&uSock,YWTCPIP_PF_INET,YWTCPIP_SOCKETTYPE_STREAM,0);
                    if(ErrorCode!=YW_NO_ERROR)
                    {
                        return E_SOCK_CONNECT_FAILED;
                    }
                }
                if(uIpCount++>2)/*最多尝试2个Ip，防止连接时间过长*/
                    break;
        }
		if(nRet == YW_NO_ERROR)
		{
			S32 nLen2Send = 0;

			data_index = 0;
			nReceiveLen = 0;
			nAllRcvLen = 0;

			nResult=YWHTTPC_FormHeader(pcTmpBuf, pReq, pcFilePath, acHost);
			//YWOS_Trace(YWOS_TRACE_INFO, "%s\n",pcTmpBuf);
			if(nResult != E_SOCK_RCV_SUCCESS)
			{
				YWMID_Trace((YWOS_TRACE_ERROR, "[YWHTTPC_ReqProcesss]form header failed,nResult=%d\n",nResult));
				YWTCPIP_CloseSocket(uSock);
				uSock = 0;
				return nResult;
			}
			nLen2Send = YWLIB_Strlen(pcTmpBuf);

			nAllRcvLen = 0;
			while(nAllRcvLen<nLen2Send)
			{
				// nReceiveLen = YWHTTPC_SocketSend(uSock, (S8 *)pcTmpBuf+nAllRcvLen,nLen2Send-nAllRcvLen);
				nReceiveLen = YWTCPIP_Send(uSock,(void *)pcTmpBuf+nAllRcvLen,nLen2Send-nAllRcvLen,YWTCPIP_SOCKETMSG_NOSIGNAL);//MSG_NOSIGNAL);
				//YWMID_Trace((YWOS_TRACE_ERROR,"[YWHTTPC_ReqProcess]:send data len%d !\n",nReceiveLen));

				if(nReceiveLen>=0)
				{
					nAllRcvLen += nReceiveLen;
				}
				else
				{
					nResult=E_SOCK_SEND_FAILED;
					break;
				}
			}

			if(nResult!=E_SOCK_SEND_FAILED)
			{
				nReceiveLen=YWHTTPC_ReceiveData(uSock, pResMng, pReq);
				if(nReceiveLen<=0)
				{
					if(0==nReceiveLen)
						nResult=E_SOCK_RCV_FAILED;
					else
						nResult=nReceiveLen;
				}
			}
		}
		else if(nRet==-2)
		{
		    YWOS_Trace(YWOS_TRACE_INFO, "[YWHTTPC_ReqProcess]Error, user interrpt!\n");
		    nResult = E_SOCK_USER_INTERRUPT;
		}
		else
		{
			YWOS_Trace(YWOS_TRACE_INFO, "[YWHTTPC_ReqProcess]Error, connect failed!\n");
			nResult = E_SOCK_CONNECT_FAILED;
		}
		
        if(uSock!=0)
        {
            YWTCPIP_CloseSocket(uSock);
            uSock = 0;
            pResMng->uSockHandle = 0;
        }
    }
    else
    {
    	YWOS_Trace(YWOS_TRACE_INFO, "[YWHTTPC_ReqProcess]Error, create socket failed!\n");
    	nResult = E_SOCK_CREAT_FAILED;
    }
    return nResult;
}
 
static void HttpcTask( YWHTTPC_ReqParams_T  tReq)
{
    S32 nRet=0;
    U8 * pcData;
    S32 nFileSize;
    U8 nRedirectionCnt = 0;
    YWHTTPC_ErrorCode_T eEventErr = YWHTTPC_NO_ERROR;
    YWHTTPC_ResMng_T * pNode ;
    
    pNode = YWOS_Calloc(1, sizeof(YWHTTPC_ResMng_T));
    if(pNode)
    {
		YWLIB_Memset(pNode,0,sizeof(YWHTTPC_ResMng_T));
        pNode->pcBuf = YWOS_Calloc(1, HTTP_MAX_BUF_SIZE);
        if(!pNode->pcBuf)
        {
            YWOS_Free(pNode);
            pNode = NULL;
            return ;
        }
        pNode->uBufSize = HTTP_MAX_BUF_SIZE;
        pNode->uRunningStatus  = YWHTTPC_RUNNING;
    }
    else
    {
        return ;
    }

    {
        switch(tReq.eCmd)
        {

            case YWHTTPC_CMD_GET:
            case YWHTTPC_CMD_POST:
            case YWHTTPC_CMD_HEAD:
            //YWMID_Trace((YWOS_TRACE_INFO, " YWHTTPC_ReqProcess!\n"));
            nRet=YWHTTPC_ReqProcess(pNode, &tReq , &pcData,&nFileSize);
            //YWMID_Trace((YWOS_TRACE_INFO, " [YWHTTPC_ReqProcess]tReq.bNotFollowLocation=%d!\n",tReq.bNotFollowLocation));

            if((E_SOCK_REDIRECTION==nRet) && tReq.bNotFollowLocation)
            {
                YWHTTPC_EventLocation_T eventLocation;

                //YWMID_Trace((YWOS_TRACE_INFO, " [YWHTTPC_ReqProcess]11111\n"));

                eventLocation.pcUrl = tReq.pcUrl;
                eventLocation.pPrivate = tReq.pPrivate;

                eventLocation.pPrivate1 = tReq.pPrivate1;
                //YWEVT_Notify((U32 )pNode,  YWHTTPC_EVENT_LOCATION, (void *) &eventLocation);
                //YWMID_Trace((YWOS_TRACE_INFO, " [YWHTTPC_ReqProcess]22222\n"));
                nRet = YW_NO_ERROR;

            }
            else
            {
                nRedirectionCnt = 0;
                while(E_SOCK_REDIRECTION==nRet)
                {
                    if(nRedirectionCnt++ >REDIRECTION_TIMES)
                    {
                    	break;
                    }
                    nRet=YWHTTPC_ReqProcess(pNode, &tReq , &pcData,&nFileSize);
                }
            }
            switch(nRet)
            {
                case E_SOCK_RCV_SUCCESS:
                    eEventErr = YWHTTPC_NO_ERROR;
                    break;

                case E_SOCK_INVALID_LINK:
                    eEventErr = YWHTTPC_ERROR_INVALID_LINK;
                    YWMID_Trace((YWOS_TRACE_ERROR, "[HttpcTask]Error,Invalid link...\n"));
                    break;

                case E_SOCK_INVALID_CMD:
                    eEventErr = YWHTTPC_ERROR_INVALID_CMD;
                    YWMID_Trace((YWOS_TRACE_ERROR, "[HttpcTask]Error,Invalid Command....\n"));
                    break;
                case E_SOCK_CREAT_FAILED:
                    eEventErr = YWHTTPC_ERROR_CREAT_FAILED;
                    YWMID_Trace((YWOS_TRACE_ERROR, "[HttpcTask]Error,Failed to create Socket....\n"));
                    break;
                case E_SOCK_CONNECT_FAILED:
                    eEventErr = YWHTTPC_ERROR_CONNECT_FAILED;
                    YWMID_Trace((YWOS_TRACE_ERROR, "[HttpcTask]Error,Failed to Connect Socket........\n"));
                    break;
                case E_SOCK_SEND_FAILED:
                    eEventErr = YWHTTPC_ERROR_SEND_FAILED;
                    YWMID_Trace((YWOS_TRACE_ERROR,"[HttpcTask]Error,Failed to Send Data....\n"));
                    break;
                case E_SOCK_RCV_FAILED:
                    eEventErr = YWHTTPC_ERROR_RCV_FAILED;
                    YWMID_Trace((YWOS_TRACE_ERROR,"[HttpcTask]Error,Failed to Recv Data....\n"));
                    break;
                case E_SOCK_USER_INTERRUPT:
                    eEventErr = YWHTTPC_ERROR_USER_INTERRUPT;
                    YWMID_Trace((YWOS_TRACE_ERROR, "[HttpcTask]Error, Recv User Interrupt....\n"));
                    break;
                default:
                    eEventErr = YWHTTPC_ERROR_UNKNOWN;
                    YWMID_Trace((YWOS_TRACE_ERROR,"[HttpcTask]Abnormal，unknown error.... %d\n",nRet));
                    break;
            }
                break;
            default:
                eEventErr = YWHTTPC_ERROR_INVALID_CMD;
                YWMID_Trace((YWOS_TRACE_ERROR, "[HttpcTask]Error,invalid cmd %d!\n", tReq.eCmd));
                break;
        }
	 
    }
    
    if(pNode)
    {
        if(pNode->pcBuf)
        {
            YWOS_Free(pNode->pcBuf);
            pNode->pcBuf = NULL;
          
        }
        YWOS_Free(pNode);
        pNode = NULL;
    }
    
}

static YW_ErrorType_T YWHttpc_sendstring( U8 *url,YWHTTPC_PostData_T *pPostData,U8 DataNum)
{
    YWHTTPC_ReqParams_T ReqParams;
    YW_ErrorType_T ErrorType=0;
    U32 uLen = 0, uOrgLen =0;
    S8 * pcUrl;

    if(NULL==pPostData||NULL==url)
    {
        return YWMID_ERROR_BAD_PARAMETER;
    }
    
    YWLIB_Memset(&ReqParams,0,sizeof(YWHTTPC_ReqParams_T));
    ReqParams.eCmd = YWHTTPC_CMD_POST;
    if(url)
    {
            pcUrl = (S8 *)url;
            uOrgLen=uLen = YWLIB_Strlen(pcUrl);
            if(!YWLIB_Strncasecmp(pcUrl, (S8 *)"http://", 7))/*检验协议头*/
            {
				pcUrl+=7;
            }
            else
            {
                uLen+=7;
            }
            if(!YWLIB_Strchr(pcUrl, '/'))/*如果没有目录，就要默认到根目录*/
            {
                uLen +=1;
            }
            if(uLen!= uOrgLen)
            {
                ReqParams.pcUrl= YWOS_Calloc(1, uLen +1);
                if( ! ReqParams.pcUrl)
                {
                    YWMID_Trace((YWOS_TRACE_INFO,"[YWHTTPC_SendRequest]Error, no memery!\n"));
                    return YWMID_ERROR_NO_MEMORY;
                }
                switch(uLen - uOrgLen)
                {
				case 1:
					YWLIB_Strcpy(ReqParams.pcUrl ,(S8 *)url);
					YWLIB_Strcat(ReqParams.pcUrl, (S8 *)"/");
					break;
				case 7:
					YWLIB_Strcpy(ReqParams.pcUrl , (S8 *)"http://");
					YWLIB_Strcat(ReqParams.pcUrl, (S8 *)url);
					break;
				case 8:
					YWLIB_Strcpy(ReqParams.pcUrl , (S8 *)"http://");
					YWLIB_Strcat(ReqParams.pcUrl, (S8 *)url);
					YWLIB_Strcat(ReqParams.pcUrl, (S8 *)"/");
					break;
				default:
					YWLIB_Strcpy(ReqParams.pcUrl, (S8 *)url);
					break;
                }
            }
            else
            {
                ReqParams.pcUrl= YWOS_Calloc(1, uOrgLen+1);
                if( ! ReqParams.pcUrl)
                {
                    YWMID_Trace((YWOS_TRACE_INFO,"[YWHTTPC_SendRequest]Error, no memery!\n"));
                    return YWMID_ERROR_NO_MEMORY;
                }
                YWLIB_Strcpy(ReqParams.pcUrl, (S8 *)url);
                
                
            }
    }
        
    ReqParams.pcData=pPostData;
    ReqParams.pcDataNum = DataNum;
    HttpcTask(ReqParams);
    
    if(ReqParams.pcUrl)
    {
        YWOS_Free(ReqParams.pcUrl);
        ReqParams.pcUrl = NULL;
    }
    return ErrorType;
    
}


void YWHttpc_msg( char *msg, int timeout, int popuptype)
{
	 YWHTTPC_PostData_T postData[3];
	 char temp[100];
	 char temp1[100];

	 memset(temp, 0, sizeof(temp));
	 sprintf(temp, "%d", timeout);

	 memset(temp1, 0, sizeof(temp1));
	 sprintf(temp1, "%d", popuptype);

	 postData[0].name = "text";
	 postData[0].string = msg;

	 postData[1].name = "type";
	 postData[1].string = temp1;

	 postData[2].name = "timeout";
	 postData[2].string = temp;

	 YWHttpc_sendstring("127.0.0.1/web/message",postData,3);

}




