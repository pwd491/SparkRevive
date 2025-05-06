/**********************************文件头部注释************************************/
/*****************************************************************************************/


/* Includes --------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <errno-base.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/netlink.h>
#include <linux/if.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/select.h>
/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include "sys/stat.h"
  
#include "ywdefs.h"
//#include "ywos.h"
//#include "ywlib.h"
//#include "ywhal_assert.h"
#include "ywtcpip.h"
  
/* Global ----------------------------------------------------------------- */

/*Module Version Info*/
#define   Ver_Layer                     "HAL"
#define   Ver_name                      "YWTCPIP"
#define   Ver_Version                   "V1.0"


/* Private Types ------------------------------------------------------ */
#define MAX_MACSTRING_LEN (17)
#define MAX_IPSTRING_LEN (15)  //Only for IPV4

/* Private Constants -------------------------------------------------- */
//static BOOL YWTCPIP_ISInitialized = FALSE;

/* Private Variables -------------------------------------------------- */
extern int errno;

/* Flags for select_fd's WAIT_FOR argument. */
enum 
{
    WAIT_FOR_READ = 1,
    WAIT_FOR_WRITE = 2
};

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
 #define YWLIB_Snprintf snprintf
#define YWOS_TaskSleep(n) sleep(n)
#endif

/************************************局部函数*********************************************/
YW_ErrorType_T YWTCPIPi_GetErr(S32 ErrorNo)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;

	//YWOS_Trace(YWOS_TRACE_INFO, " Err no is %d \n",ErrorNo);
	switch(ErrorNo)
	{
		case EINPROGRESS:
		{
			YW_ErrorCode = YWTCPIP_ERROR_INPROGRESS;
			break;
		}
		case EFAULT:
		{
			YW_ErrorCode = YWTCPIP_ERROR_BADADDRESS;
			break;
		}
		case ENOTSOCK:
		{
			YW_ErrorCode = YWTCPIP_ERROR_NOTSOCKET;
			break;
		}
		case EISCONN:
		{
			YW_ErrorCode = YWTCPIP_ERROR_ISCONNECT;
			break;
		}
		case ECONNREFUSED:
		{
			YW_ErrorCode = YWTCPIP_ERROR_CONNECTREFUSED;
			break;
		}
		case ETIMEDOUT:
		{
			YW_ErrorCode = YWTCPIP_ERROR_TIMEOUT;
			break;
		}
		case ENETUNREACH:
		{
			YW_ErrorCode = YWTCPIP_ERROR_NETUNREACH;
			break;
		}
		case EAFNOSUPPORT:
		{
			YW_ErrorCode = YWTCPIP_ERROR_AFNOTSUPPORT;
			break;
		}
		case EALREADY:
		{
			YW_ErrorCode = YWTCPIP_ERROR_ALREADY;
			break;
		}
		case EPROTONOSUPPORT:
		{
			YW_ErrorCode = YWTCPIP_ERROR_PROTONOSUPPORT;
			break;
		}
		case ENOBUFS:
		{
			YW_ErrorCode = YWTCPIP_ERROR_NOBUFS;
			break;
		}
		case ENOMEM:
		{
			YW_ErrorCode = YWTCPIP_ERROR_NOMEM;
			break;
		}
		case EINVAL:
		{
			YW_ErrorCode = YWTCPIP_ERROR_BADPARAMMETERS;
			break;
		}
		case EBADF:
		{
			YW_ErrorCode = YWTCPIP_ERROR_BADFILENUM;
			break;
		}
		case EOPNOTSUPP:
		{
			YW_ErrorCode = YWTCPIP_ERROR_OPNOTSUPP;
			break;
		}
		case EPERM:
		{
			YW_ErrorCode = YWTCPIP_ERROR_PERM;
			break;
		}
		case EINTR:
		{
			YW_ErrorCode = YWTCPIP_ERROR_INTR;
			break;
		}
		case EAGAIN:
		{
			YW_ErrorCode = YWTCPIP_ERROR_AGAIN;
			break;
		}
		default:
		{
			YW_ErrorCode = YW_NO_ERROR;
			break;
		}
	}
	
	//YWOS_Trace(YWOS_TRACE_INFO, " Errno is 0x%x \n",YW_ErrorCode);
	return YW_ErrorCode;
}


#if 1

/***********************************************************************

************************************************************************/    
YW_ErrorType_T YWTCPIP_Socket(YWTCPIP_SocketFD_T *SocketFD,
								YWTCPIP_PF_T Domain,
								YWTCPIP_SOCKETTYPE_T SockType,
								S32	Protocols)
{   
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	S32 SocketDomain = 0,Type = 0,GotSocketFD=0;

	if( ( Domain > YWTCPIP_PF_NUM ) || ( SockType > YWTCPIP_SOCKETTYPE_PACKET ))
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Socket] Invalid Parameter.\n") );
        return YWHAL_ERROR_BAD_PARAMETER;
	}
	
	switch(Domain)
	{
		case YWTCPIP_PF_UNIX:
		{
			SocketDomain = PF_UNIX;
			break;
		}
		case YWTCPIP_PF_INET6:
		{
			SocketDomain = PF_INET6;
			break;
		}
		case YWTCPIP_PF_IPX:
		{
			SocketDomain = PF_IPX;
			break;
		}
		case YWTCPIP_PF_NETLINK:
		{
			SocketDomain = PF_NETLINK;
			break;
		}
		case YWTCPIP_PF_X25:
		{
			SocketDomain = PF_X25;
			break;
		}
		case YWTCPIP_PF_AX25:
		{
			SocketDomain = PF_AX25;
			break;
		}
		case YWTCPIP_PF_ATMPVC:
		{
			SocketDomain = PF_ATMPVC;
			break;
		}
		case YWTCPIP_PF_APPLETALK:
		{
			SocketDomain = PF_APPLETALK;
			break;
		}
		case YWTCPIP_PF_PACKET:
		{
			SocketDomain = PF_PACKET;
			break;
		}		
		case YWTCPIP_PF_INET:
		default:
		{
			SocketDomain = PF_INET;
			//YWOS_Trace(YWOS_TRACE_INFO, " ==PF INET==%d\n",PF_INET);
			break;
		}
	}

	switch(SockType)
	{
		case YWTCPIP_SOCKETTYPE_DGRAM:
		{
			Type = SOCK_DGRAM;
			break;
		}
		case YWTCPIP_SOCKETTYPE_STREAM:
		{
			Type = SOCK_STREAM;
			//YWOS_Trace(YWOS_TRACE_INFO, " ==SOCK_STREAM==%d\n",SOCK_STREAM);
			break;
		}
		case YWTCPIP_SOCKETTYPE_RAW:
		{
			Type = SOCK_RAW;
			break;
		}
		case YWTCPIP_SOCKETTYPE_RDM:
		{
			Type = SOCK_RDM;
			break;
		}
		case YWTCPIP_SOCKETTYPE_SEQPACKET:
		{
			Type = SOCK_SEQPACKET;
			break;
		}
		/*
		case YWTCPIP_SOCKETTYPE_DCCP:
		{
			Type = SOCK_DCCP;
			break;
		}
		*/
		case YWTCPIP_SOCKETTYPE_PACKET:
		{
			Type = SOCK_PACKET;
			break;
		}
		default:
		{
			Type = SOCK_STREAM;
			break;
		}
	}

	//YWOS_Trace(YWOS_TRACE_INFO, " ==Domain %d  Type==%d Prot = %d\n",SocketDomain,Type,Protocols);

	if( (GotSocketFD = socket(SocketDomain,Type,Protocols)) < 0)
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Socket] Cannot create listening socket.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
		YW_ErrorCode = errno;
	}
	else
	{
		*SocketFD = GotSocketFD;
	}
	
	return YW_ErrorCode;
}

/***********************************************************************

************************************************************************/ 
YW_ErrorType_T YWTCPIP_Bind(YWTCPIP_SocketFD_T SocketFD,
								YWTCPIP_SOCKETADDRESS_T *pSocketAddress,
								S32	AddressLength)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	S32 Error = 0;
	U32 IPAddr = 0;
	U16 PortAddr = 0;
	struct sockaddr_in TarAddress;
	struct sockaddr TargetAddress;
	
	if( ( pSocketAddress == NULL ) || ( AddressLength == 0 ))
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Bind] Invalid Parameter.\n") );
        return YWHAL_ERROR_BAD_PARAMETER;
	}

	//YWOS_Trace(YWOS_TRACE_INFO, "...2..Port %d.....\n",*((U16 *)pSocketAddress->SOCKETADDRESS_Data));

	TarAddress.sin_family 		= pSocketAddress->SOCKETADDRESS_Family;
	IPAddr = *((U32 *)(pSocketAddress->SOCKETADDRESS_Data+2));
	PortAddr = *((U16 *)pSocketAddress->SOCKETADDRESS_Data);
	#if 0
	TarAddress.sin_port   		= htons(*((U16 *)pSocketAddress->SOCKETADDRESS_Data));

	YWOS_Trace(YWOS_TRACE_INFO, "...111..IP %d.....\n",*((U32 *)(pSocketAddress->SOCKETADDRESS_Data+2)) );

	if( IPAddr != 0 )
	{
		TarAddress.sin_addr.s_addr = inet_addr( IPAddr );
	}
	else
	{
		TarAddress.sin_addr.s_addr = INADDR_ANY;
	}
	#else
	TarAddress.sin_port = PortAddr;
	TarAddress.sin_addr.s_addr = IPAddr;
	#endif
	//YWOS_Trace(YWOS_TRACE_INFO, "...1..Port %d.....\n",TarAddress.sin_port);
	//YWOS_Trace(YWOS_TRACE_INFO, "...1..IP %d.....\n",TarAddress.sin_addr.s_addr);
	//YWOS_Trace(YWOS_TRACE_INFO, "....1.Len %d.....\n",AddressLength);
	//Maybe something wrong.
	bzero(&(TarAddress.sin_zero),8); 
	
	YWLIB_Memcpy(&TargetAddress , pSocketAddress, sizeof(YWTCPIP_SOCKETADDRESS_T));
	Error = bind(SocketFD,&TargetAddress,AddressLength);

	#if 0
	TarAddress.sin_family=AF_INET;
	TarAddress.sin_port=htons(3333);
	YWOS_Trace(YWOS_TRACE_INFO, ".....Port %d.....\n",TarAddress.sin_port);//1293
	TarAddress.sin_addr.s_addr = INADDR_ANY;
	YWOS_Trace(YWOS_TRACE_INFO, ".....IP %d.....\n",TarAddress.sin_addr.s_addr);//0
	AddressLength = sizeof(struct sockaddr);
	YWOS_Trace(YWOS_TRACE_INFO, ".....Len %d.....\n",AddressLength);//16
	bzero(&(TarAddress.sin_zero),8);

	Error = bind(SocketFD,(struct sockaddr *)&TarAddress,AddressLength);
	#endif
	
	if( Error < 0)
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Bind] Cannot bind server socket.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
		YW_ErrorCode = errno;
	}
  
	return Error;
}
 
/***********************************************************************

************************************************************************/ 
YW_ErrorType_T YWTCPIP_Connect(YWTCPIP_SocketFD_T SocketFD,
								YWTCPIP_SOCKETADDRESS_T *pSocketAddress,
								S32	AddressLength)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	S32 Error = 0;
	struct sockaddr_in TarAddress;
	struct sockaddr TargetAddress;
	U32 IPAddr = 0;
	U16 PortAddr = 0;


	if( ( pSocketAddress == NULL ) || ( AddressLength == 0 ))
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Connect] Invalid Parameter.\n") );
        return YWHAL_ERROR_BAD_PARAMETER;
	}
	/*
	TarAddress.sin_family 		= pSocketAddress->SOCKETADDRESS_Family;
	TarAddress.sin_port   		= htons(pSocketAddress->SOCKETPORT);
	TarAddress.sin_addr.s_addr 	= inet_addr(pSocketAddress->SOCKETADDRESS_Data);

	//Maybe something wrong.
	bzero(&(TarAddress.sin_zero),8); 
	*/
	
	TarAddress.sin_family 		= pSocketAddress->SOCKETADDRESS_Family;
	IPAddr = *((U32 *)(pSocketAddress->SOCKETADDRESS_Data+2));
	PortAddr = *((U16 *)pSocketAddress->SOCKETADDRESS_Data);

	//YWOS_Trace(YWOS_TRACE_INFO, ".c....Port %d.....\n",PortAddr);//1293
	//YWOS_Trace(YWOS_TRACE_INFO, ".c....IP 0x%x.....\n",IPAddr);//0



	#if 0
	TarAddress.sin_family=AF_INET;
	TarAddress.sin_port=htons(3333);
	YWOS_Trace(YWOS_TRACE_INFO, ".c....Port %d.....\n",TarAddress.sin_port);//1293

	//TarAddress.sin_addr.s_addr = INADDR_ANY;
	inet_aton( "192.168.3.140", &TarAddress.sin_addr );
	YWOS_Trace(YWOS_TRACE_INFO, ".c....IP 0x%x.....\n",TarAddress.sin_addr.s_addr);//0
	AddressLength = sizeof(struct sockaddr);
	YWOS_Trace(YWOS_TRACE_INFO, ".c...Len %d.....\n",AddressLength);//16
	bzero(&(TarAddress.sin_zero),8);

	Error = connect(SocketFD,(struct sockaddr *)&TarAddress,AddressLength);
	if( Error < 0)
	{
        YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Connect] Cannot connect the client connect request.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
	}

	#else

	YWLIB_Memcpy(&TargetAddress , pSocketAddress, sizeof(YWTCPIP_SOCKETADDRESS_T));
	TargetAddress.sa_family=AF_INET;
	Error = connect(SocketFD,&TargetAddress,AddressLength);
	if( Error < 0)
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Connect] Cannot connect the client connect request.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
		//YW_ErrorCode = errno;
	}
	#endif

	return YW_ErrorCode;
}


/***********************************************************************

************************************************************************/ 
YW_ErrorType_T YWTCPIP_Listen(YWTCPIP_SocketFD_T SocketFD,
								S32	Backlog)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	S32 Error = 0;

	if( Backlog == 0 )
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Listen] Invalid Parameter.\n") );
        return YWHAL_ERROR_BAD_PARAMETER;
	}

	Error = listen(SocketFD,Backlog);
	if( Error < 0)
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Listen] Cannot listen the client connect request.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
		//YW_ErrorCode = errno;
	}

	return YW_ErrorCode;
}


/***********************************************************************
    函数说明:    Wait for connection request
    参数说明:    pSocketAddress: Point to the structure of the Socket Address.
    			 AddressLength: Specify the Len of the Socket Address.

    调用说明:    
    返回参数:    YW_NO_ERROR :  
                 其他错误类型： 

    修改记录:    日       期      作      者        修定
                 ---------        ---------         -----
                 2008.08.26       CS                新建
************************************************************************/ 
YW_ErrorType_T YWTCPIP_Accept(YWTCPIP_SocketFD_T SocketFD,
								void *pSocketAddress,
								S32	*pAddressLength,
								YWTCPIP_SocketFD_T *pNewSocketFD)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	S32 NewSocket = 0;

	if( ( pSocketAddress == NULL ) || ( pAddressLength == NULL ))
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Accept] Invalid Parameter.\n") );
        return YWHAL_ERROR_BAD_PARAMETER;
	}

	NewSocket = accept(SocketFD, pSocketAddress, pAddressLength);
	if( NewSocket < 0)
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Accept] Cannot bind server socket.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
		//YW_ErrorCode = errno;
	}
    else
    {
	    *pNewSocketFD = NewSocket;
    }
	return YW_ErrorCode;
}

#if 0
S32 YWTCPIP_Select(YWTCPIP_SocketFD_T SocketFD,
								S32 Maxtime,
								S32 Waitfor)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
    fd_set fdset;
    fd_set *rd = NULL, *wr = NULL;
    struct timeval tmout;
	S32 Error = 0,NewSocket = 0;

    FD_ZERO(&fdset);
    FD_SET(SocketFD, &fdset);
    if (Waitfor & WAIT_FOR_READ)
    {
        rd = &fdset;
    }
    if (Waitfor & WAIT_FOR_WRITE)
    {
        wr = &fdset;
    }

    tmout.tv_sec = (long) Maxtime;
    tmout.tv_usec = 1000000 * (Maxtime - (long) Maxtime);

    do
    {
        Error = select (SocketFD + 1, rd, wr, NULL, &tmout);
    }while (Error < 0 && errno == 4/*EINTR*/);

	if( Error < 0)
	{
        YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Select] Select Error.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
	}
	
	return YW_ErrorCode;
}
#else
S32 YWTCPIP_Select(YWTCPIP_SocketFD_T SocketFD,
								YWTCPIP_FDSET_T *ReadFDS,
								YWTCPIP_FDSET_T *WriteFDS,
								YWTCPIP_FDSET_T *ExceptFDS,
								YWTCPIP_TIMEVAL_T *TimeOut)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	S32 RetVal = 0;

	if( (RetVal = select (SocketFD ,(fd_set *)ReadFDS,(fd_set *)WriteFDS, (fd_set *)ExceptFDS, (struct timeval *)TimeOut)) < 0)
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Select] Select Error.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
	}
	
	return RetVal;
}

void YWTCPIP_FD_CLR(YWTCPIP_SocketFD_T SocketFD,
						YWTCPIP_FDSET_T *Set)
{
	FD_CLR(SocketFD, (fd_set *)Set);
}

S32 YWTCPIP_FD_ISSET(YWTCPIP_SocketFD_T SocketFD,
						YWTCPIP_FDSET_T *Set)
{
	return (FD_ISSET(SocketFD, (fd_set *)Set));
}

void YWTCPIP_FD_SET(YWTCPIP_SocketFD_T SocketFD,
						YWTCPIP_FDSET_T *Set)
{
	FD_SET(SocketFD, (fd_set *)Set);
}

void YWTCPIP_FD_ZERO(YWTCPIP_FDSET_T *Set)
{
	FD_ZERO((fd_set *)Set);
}
#endif


/*Send a message on a socket*/
S32 YWTCPIP_Send(YWTCPIP_SocketFD_T SocketFD,
								const void* pSendMsg,
								S32	MsgLength,
								//S32 Flag)
    							YWTCPIP_SOCKETMSG_T MSGFlag)

{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	S32 SendNum = 0,Flag = 0;

	if( ( MsgLength == 0 ) || ( pSendMsg == NULL ))
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Send] Invalid Parameter.\n") );
        return YWHAL_ERROR_BAD_PARAMETER;
	}

    if( MSGFlag != YWTCPIP_SOCKETMSG_NOSIGNAL )
    {
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Send] Invalid Parameter.\n") );
        return YWHAL_ERROR_BAD_PARAMETER;
    }

    switch(MSGFlag)
    {
        case YWTCPIP_SOCKETMSG_NOSIGNAL:
        default:
            Flag = MSG_NOSIGNAL;
            break;
     }

	//SendNum = send(SocketFD,pSendMsg,MsgLength,0);
	if( (SendNum = send(SocketFD,pSendMsg,MsgLength,Flag)) < 0)
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Send] Send data error.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
	}

	return SendNum;
}

/*receive a message from a socket*/
S32 YWTCPIP_Recv(YWTCPIP_SocketFD_T SocketFD,
								void* pReceivedBuf,
								S32	BufLength)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	S32 RevNum = 0;

	if( ( BufLength == 0 ) || ( pReceivedBuf == NULL ))
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Recv] Invalid Parameter.\n") );
        return YWHAL_ERROR_BAD_PARAMETER;
	}

	//RevNum = recv(SocketFD,pReceivedBuf,BufLength,0);
	if( (RevNum = recv(SocketFD,pReceivedBuf,BufLength,0)) < 0)
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Recv] Receive data error.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
	}

	return RevNum;
}

/*Send a message on a socket*/
S32 YWTCPIP_Sendto(YWTCPIP_SocketFD_T SocketFD,
								const void* pSendMsg,
								S32	MsgLength,
								const YWTCPIP_SOCKETADDRESS_T *pToSocketAddress,
								S32	ToAddressLength)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	struct sockaddr TargetAddress;
	S32 SendNum = 0;

	if( ( MsgLength == 0 ) || ( pSendMsg == NULL ) || ( pToSocketAddress == NULL ) ||
		( ToAddressLength == 0 ) )
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Sendto] Invalid Parameter.\n") );
        return YWHAL_ERROR_BAD_PARAMETER;
	}

	YWLIB_Memcpy(&TargetAddress , pToSocketAddress, sizeof(YWTCPIP_SOCKETADDRESS_T));

	//SendNum = sendto(SocketFD,pSendMsg,MsgLength,0,&TargetAddress,ToAddressLength);
	if( (SendNum = sendto(SocketFD,pSendMsg,MsgLength,0,&TargetAddress,ToAddressLength)) < 0)
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Sendto] Sendto data error.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
	}

	return SendNum;
}

/*receive a message from a socket*/
S32 YWTCPIP_RecvFrom(YWTCPIP_SocketFD_T SocketFD,
								void* pReceivedBuf,
								S32	BufLength,
								const YWTCPIP_SOCKETADDRESS_T *pFromSocketAddress,
								S32	*pFromAddressLength)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	struct sockaddr TargetAddress;
	S32 RevNum = 0;

	if( ( pReceivedBuf == NULL ) || ( BufLength == 0 )  || ( pFromSocketAddress == NULL ) ||
		( pFromAddressLength == 0 ))
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Recv] Invalid Parameter.\n") );
        return YWHAL_ERROR_BAD_PARAMETER;
	}

	YWLIB_Memcpy(&TargetAddress , pFromSocketAddress, sizeof(YWTCPIP_SOCKETADDRESS_T));

	//RevNum = recvfrom(SocketFD,pReceivedBuf,BufLength,0,&TargetAddress,pFromAddressLength);
	if( (RevNum = recvfrom(SocketFD,pReceivedBuf,BufLength,0,&TargetAddress,pFromAddressLength)) < 0)
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Recv] ReceiveFrom data error.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
	}

	return RevNum;
}

#if 0
/*Get Peer name*/
YW_ErrorType_T YWTCPIP_GetPeerName(YWTCPIP_SocketFD_T SocketFD,
								YWTCPIP_SOCKETADDRESS_T *pSocketAddress,
								S32	*pAddressLength)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	S32 Error = 0;
	//struct sockaddr TargetAddress;

	if( ( pSocketAddress == 0 ) || ( pAddressLength == NULL ))
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_GetPeerName] Invalid Parameter.\n") );
        return YWHAL_ERROR_BAD_PARAMETER;
	}

	//YWLIB_Memcpy(&TargetAddress , pSocketAddress, sizeof(YWTCPIP_SOCKETADDRESS_T));

	Error = getpeername(SocketFD,pSocketAddress,pAddressLength);
	if( Error < 0)
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_GetPeerName] Cannot listen the client connect request.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
		//YW_ErrorCode = errno;
	}

	return YW_ErrorCode;
}

/*Get Host name*/
YW_ErrorType_T YWTCPIP_GetHostName(S8 *pHostName,
										U32	NameLength)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	S32 Error = 0;

	if( ( NameLength == 0 ) || ( pHostName == NULL ))
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_GetPeerName] Invalid Parameter.\n") );
        return YWHAL_ERROR_BAD_PARAMETER;
	}

	Error = gethostname(pHostName,NameLength);
	if( Error < 0)
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_GetPeerName] Cannot listen the client connect request.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
		//YW_ErrorCode = errno;
	}

	return YW_ErrorCode;
}
#endif

YW_ErrorType_T YWTCPIP_GetHostByName_r(const S8* pHostName, YWTCPIP_HOSTINFO_T *hostinfo, U8 *buf, U32 buflen, YWTCPIP_HOSTINFO_T **result, S32 *h_errnop )
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;

	if( (pHostName == NULL) || (hostinfo == NULL) || (buf == NULL) || (result == NULL) || (h_errnop == NULL))
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR, "[ERROR][YWTCPIP_GetHostByName] Invalid Parameter.\n") );
        return YWHAL_ERROR_BAD_PARAMETER;
	}
    YW_ErrorCode = gethostbyname_r(pHostName, (struct hostent*)hostinfo, buf, buflen, (struct hostent**)result, h_errnop);
    

	return YW_ErrorCode;
}

YWTCPIP_HOSTINFO_T *YWTCPIP_GetHostByName(const S8* pHostName)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	struct hostent *Hostent;
	//YWTCPIP_HOSTINFO_T HostInfo;
	
	if( pHostName == NULL )
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_GetHostByName] Invalid Parameter.\n") );
        return NULL;
	}

	Hostent = gethostbyname(pHostName);
	if( Hostent == NULL )
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_GetHostByName] Gethostbyname Error.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
	}

	//YWLIB_Memcpy(HostInfo, Hostent, sizeof(hostent));

	return (YWTCPIP_HOSTINFO_T *)Hostent;
}

/*Set options on sockets*/
YW_ErrorType_T YWTCPIP_SetSocketOpt(YWTCPIP_SocketFD_T SocketFD,
										S32 Level,
										S32 OptName,
										const void *OptVal,
										S32 OptLen)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	S32 Error = 0;
	
	Error = setsockopt(SocketFD,Level,OptName,OptVal, (socklen_t)OptLen);
	if( Error < 0)
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_SetSocketOpt] setsockopt Error.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
		//YW_ErrorCode = errno;
	}
	
	return YW_ErrorCode;
}

/*Set options on sockets*/
YW_ErrorType_T YWTCPIP_GetSocketOpt(YWTCPIP_SocketFD_T SocketFD,
										S32 Level,
										S32 OptName,
										void *OptVal,
										S32 *OptLen)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	S32 Error = 0;
	
	Error = getsockopt(SocketFD,Level,OptName,OptVal, (socklen_t *)OptLen);
	if( Error < 0)
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_GetSocketOpt] getsockopt Error.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
		//YW_ErrorCode = errno;
	}
	
	return YW_ErrorCode;
}

/*Close the connection*/
YW_ErrorType_T YWTCPIP_CloseSocket(YWTCPIP_SocketFD_T SocketFD)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	S32 Error = 0;
	Error = close(SocketFD);
	if( Error < 0)
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_CloseSocket] Close Socket Error.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
	}

	return YW_ErrorCode;
}
#endif

/*Shutdown socket connection
How:
0—Further receivesare disallowed
1—Further sendsare disallowed  
2—Further sendsand receivesare disallowed(likeclose())
*/
YW_ErrorType_T YWTCPIP_ShutdownSocket( YWTCPIP_SocketFD_T SocketFD,
										S32 How)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	S32 Error = 0;
	
	Error = shutdown(SocketFD,How);
	if( Error < 0)
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_ShutdownSocket] Shutdown Socket Error.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
	}

	return YW_ErrorCode;
}

S32 YWTCPIP_Fcntl(YWTCPIP_SocketFD_T SocketFD,
										S32 CMD,
										YWTCPIP_FCNTLPARAM_T Param)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	S32 RetVal = 0,Args = 0;

	if( ( Param < YWTCPIP_FCNTLPARAM_O_NONBLOCK ) || ( Param > YWTCPIP_FCNTLPARAM_O_BLOCK ) )
	{
        //YWOS_Trace(YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Fcntl]Invalid Parameter.\n");
		return YWHAL_ERROR_BAD_PARAMETER;
	}

    if( Param == YWTCPIP_FCNTLPARAM_NOARGS )
    {
    	if( (RetVal = fcntl(SocketFD,CMD)) < 0)
    	{
            //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Fcntl] fcntl Error.\n") );
    		YW_ErrorCode = YWTCPIPi_GetErr(errno);
    	}

    }
    else
    {
        Args = fcntl(SocketFD,F_GETFL,0);

        switch(Param)
        {
            case YWTCPIP_FCNTLPARAM_O_NONBLOCK:
            default:
                Args |= O_NONBLOCK;
                break;
            case YWTCPIP_FCNTLPARAM_O_BLOCK:
                Args &= ~O_NONBLOCK;
                break;   
        }

    	if( (RetVal = fcntl(SocketFD,CMD,Args)) < 0)
    	{
            //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_Fcntl] fcntl Error.\n") );
    		YW_ErrorCode = YWTCPIPi_GetErr(errno);
    	}
    }
	
	return RetVal;
}


YW_ErrorType_T YWTCPIP_SetDHCP(void)
{
    S32 Status = 0;

    system("killall udhcpc");
	Status = system("udhcpc -i eth0 &");
    if( Status != 0 )
    {
        //YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWTCPIP_SetDHCP]2. SET Param Failed.\n");
        return YWHAL_ERROR_BAD_PARAMETER;
    }
    YWOS_TaskSleep(1000); //wait dhcp result
    
    return YW_NO_ERROR;   
}

   

void YWTCPIP_StopDHCP(void)
{
    system("killall udhcpc");
}

/***********************************************************************

************************************************************************/
YW_ErrorType_T YWTCPIP_GetNet(U8*pMacBuff, U8 MacLen, U8 *pIPBuff, U8 *pNETMASKBuff, U8 *pGATEWAYBuff)                             
{
    char   line[100] = {0};
    struct ifreq ifr;
    static int skfd = -1;	/* generic raw socket desc.     */
    S8  MACAddr[MAX_MACSTRING_LEN+1]={0},
        IPAddr[MAX_IPSTRING_LEN+1]={0},
        NETMASKAddr[MAX_IPSTRING_LEN+1]={0},
        GATEWAYAddr[MAX_IPSTRING_LEN+1]={0},
        DevName[8] = {0};
    int pIPBuffTmp[4] = {0};
    int pNETMASKBuffTmp[4] = {0};
    int pGATEWAYBuffTmp[4] = {0};
    U8 Temp[6] = {0};
    S32 Status = 0;
	struct stat StatBuff;

	FILE *HostFile = NULL;
	U8 i = 0;

    YWLIB_Memset((void *)&ifr, 0, sizeof(ifr));

	if( (pMacBuff == NULL) || (MacLen != 6) )
	{
        //YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWTCPIP_GetNet]MAC Invalid Parameter.\n");
		return YWHAL_ERROR_BAD_PARAMETER;
	}
    
    if ((pIPBuff == NULL) || (pGATEWAYBuff == NULL) || (pNETMASKBuff == NULL))

    {
        //YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWTCPIP_GetNet]MAC Invalid Parameter.\n");
        return YWHAL_ERROR_BAD_PARAMETER;
    }
	YWLIB_Memset( DevName, 0, 8);
	YWLIB_Memset( Temp, 0, 6);
	YWLIB_Memset( DevName, 0, 8);
	YWLIB_Memset( MACAddr, 0, MAX_MACSTRING_LEN+1);
	YWLIB_Memset( IPAddr, 0, MAX_IPSTRING_LEN+1);
    YWLIB_Memset( NETMASKAddr, 0, MAX_IPSTRING_LEN+1);
    YWLIB_Memset( GATEWAYAddr, 0, MAX_IPSTRING_LEN+1);
	YWLIB_Memset(line, 0, sizeof(line));

#if 1  
	//Get Mac Addr.
	for(i = 0; i < MacLen; i++)
	{
        YWLIB_Memset(Temp, 0, sizeof(Temp));
        YWLIB_Sprintf((S8*)Temp,(S8*)"%02X",(U32)(*pMacBuff));
		YWLIB_Strcat((S8*)line, (const S8*)Temp);
		if(i != MacLen-1)
		{
			YWLIB_Strcat((S8*)line,(S8*)":");
		}
		pMacBuff++;
	}
	YWLIB_Memcpy((void*)MACAddr,(void*)line, MAX_MACSTRING_LEN);


	/*1.Get Device name.*/
    YWLIB_Memset((void*)line, 0, (U32)sizeof(line));
    YWLIB_Sprintf((S8*)line, (S8*)"ifconfig -a | grep %s | awk '{print $1}' > HostTemp.txt", MACAddr);
	Status = system(line);
    if( Status != 0 )
    {
        //YWOS_Trace(YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_SetNet]2. SET Param Failed.\n");
        return YWHAL_ERROR_BAD_PARAMETER;
    }
    
	Status = system("sed -n '1p' HostTemp.txt > Host.txt");
    if( Status != 0 )
    {
        //YWOS_Trace(YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_SetNet]3. SET Param Failed.\n");
        return YWHAL_ERROR_BAD_PARAMETER;
    }

	if( ( HostFile = fopen("Host.txt" ,"rb+") ) == NULL )
    {
    	//YWOS_Trace(YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_SetNet] Can not open Host.txt.\n");
        return YWHAL_ERROR_UNKNOWN_DEVICE;
	}

	stat("Host.txt",&StatBuff);
	if( StatBuff.st_size == 0)
	{
    	//YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWTCPIP_SetNet] Can not find the MAC Addr.\n");
        fclose(HostFile);
        return YWHAL_ERROR_UNKNOWN_DEVICE;
	}

	fread(DevName, StatBuff.st_size-1, 1, HostFile);
    fclose(HostFile);
    
	Status = system("rm -f HostTemp.txt Host.txt");
    if( Status != 0 )
    {
        //YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWTCPIP_SetNet]4. SET Param Failed.\n");
        return YWHAL_ERROR_BAD_PARAMETER;
    }
    //end 1. Then got Device Name.
#else
    YWLIB_Memcpy(DevName, "eth0", sizeof(DevName)); //不应该根据MAC地址
#endif
    
    /*************get ipaddr begin*************/
	skfd = socket(AF_INET, SOCK_DGRAM, 0);
    YWLIB_Strncpy((S8*)ifr.ifr_name, DevName, YWLIB_Strlen(DevName));

	if (ioctl(skfd, SIOCGIFADDR, &ifr) < 0)
	{
    	YWLIB_Memset(IPAddr, 0, MAX_IPSTRING_LEN+1);
        close(skfd);
        return YWHAL_ERROR_UNKNOWN_DEVICE;
	}
	else
	{
		YWLIB_Memcpy(IPAddr, inet_ntoa(((struct sockaddr_in*)(&ifr.ifr_addr))->sin_addr), MAX_IPSTRING_LEN);
	}
    sscanf((const char*)IPAddr, "%d.%d.%d.%d", pIPBuffTmp, pIPBuffTmp+1, pIPBuffTmp+2, pIPBuffTmp+3);
    for (i = 0; i < 4; i++)
    {
        *(pIPBuff+i) = (U8)pIPBuffTmp[i];
    }
    /*************get ipaddr end*************/


    /*************get netmask begin*************/
    if (ioctl(skfd, SIOCGIFNETMASK, &ifr) < 0)
	{
		YWLIB_Memset(NETMASKAddr, 0, MAX_IPSTRING_LEN+1);
        close(skfd);
        return YWHAL_ERROR_UNKNOWN_DEVICE;
	}
	else
	{
		YWLIB_Memcpy(NETMASKAddr, inet_ntoa(((struct sockaddr_in*)(&ifr.ifr_netmask))->sin_addr), MAX_IPSTRING_LEN);
	}   
    sscanf((const char*)NETMASKAddr, "%d.%d.%d.%d", pNETMASKBuffTmp, pNETMASKBuffTmp+1, pNETMASKBuffTmp+2, pNETMASKBuffTmp+3);
    for (i = 0; i < 4; i++)
    {
        *(pNETMASKBuff+i) = (U8)pNETMASKBuffTmp[i];
    }
    
    close(skfd);

    /*************get netmask end*************/


    /*************get gateway begin*************/
    if (!(YWLIB_Strcmp(DevName, (S8*)"eth0")))
    {
        Status = system("route -n | grep eth0 | awk '{print $2}' > RouteGateway.txt");
    }
    else
    {
        YWLIB_Memset((void*)line, 0, (U32)sizeof(line));
        YWLIB_Sprintf((S8*)line, (S8*)"route -n | grep %s | awk '{print $2}' > RouteGateway.txt", DevName);
        system((char*)line);    
    }
    HostFile = fopen("RouteGateway.txt", "r");   
    if (HostFile == NULL)
    {
        system("rm -rf RouteGateway.txt");
        return 0;
    }
    
    YWLIB_Memset((void*)line, 0, (U32)sizeof(line));
	while (fgets(line, sizeof(line), HostFile))
    {
        if (YWLIB_Strncmp((S8*)line, (S8*)"0.0.0.0", YWLIB_Strlen((const S8*)"0.0.0.0")))
        {
            YWLIB_Strncpy(GATEWAYAddr, (const S8*)line, MAX_IPSTRING_LEN+1);
            sscanf((const char*)GATEWAYAddr, "%d.%d.%d.%d", pGATEWAYBuffTmp, pGATEWAYBuffTmp+1, pGATEWAYBuffTmp+2, pGATEWAYBuffTmp+3);
            for (i = 0; i < 4; i++)
            {
                *(pGATEWAYBuff+i) = (U8)pGATEWAYBuffTmp[i];
            }
            break;
        }
	}
    fclose(HostFile);
    system("rm -rf RouteGateway.txt");

    /*************get gateway begin*************/

    return 0;
}
/***********************************************************************

************************************************************************/
YW_ErrorType_T YWTCPIP_SetNet(U8* pMacBuff,
                              U8  MacLen,
                              YWTCPIP_SETNET_T *NetParam)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	U8  i = 0, j = 0;
    S8  pString[100] = {0};	
    S8  MACAddr[MAX_MACSTRING_LEN+1]={0};
    S8  IPAddr[MAX_IPSTRING_LEN+1]={0},
        NETMASKAddr[MAX_IPSTRING_LEN+1]={0},
        GATEWAYAddr[MAX_IPSTRING_LEN+1]={0},
        DevName[8] = {0};

    U8 Temp[6] = {0};
    S32 Status = 0;
	FILE *HostFile = NULL;
	struct stat StatBuff;


	if( (pMacBuff == NULL) || (MacLen != 6) )
	{
        //YWOS_Trace(YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_SetNet]MAC Invalid Parameter.\n");
		return YWHAL_ERROR_BAD_PARAMETER;
	}
	//The max num is 255 for one mac.
	if( ( NetParam->pIPBuff == NULL ) || ( NetParam->IPLen < 4 ) || 
        ( NetParam->IPLen > (255*4) ) || ( NetParam->IPLen%4 != 0) )
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR, "[ERROR][YWTCPIP_SetNet]IP Invalid Parameter.\n") );
        return YWHAL_ERROR_BAD_PARAMETER;
	}

    if( (NetParam->pNETMASKBuff == NULL) || (NetParam->NETMASKLen != NetParam->IPLen) )
    {
        //YWOSTRACE(( YWOS_TRACE_ERROR, "[ERROR][YWTCPIP_SetNet]Netmask Invalid Parameter.\n") );
        return YWHAL_ERROR_BAD_PARAMETER;
    }

    if( (NetParam->pGATEWAYBuff == NULL) || (NetParam->GATEWAYLen != NetParam->IPLen) )
    {
        //YWOSTRACE(( YWOS_TRACE_ERROR, "[ERROR][YWTCPIP_SetNet]Gateway Invalid Parameter.\n") );
        return YWHAL_ERROR_BAD_PARAMETER;
    }
    
	YWLIB_Memset( DevName, 0, sizeof(DevName));
	YWLIB_Memset( Temp, 0, sizeof(Temp));
	YWLIB_Memset( MACAddr, 0, MAX_MACSTRING_LEN+1);
	YWLIB_Memset( IPAddr, 0, MAX_IPSTRING_LEN+1);
    YWLIB_Memset( NETMASKAddr, 0, MAX_IPSTRING_LEN+1);
    YWLIB_Memset( GATEWAYAddr, 0, MAX_IPSTRING_LEN+1);

    #if 1
    {
    	//Get Mac Addr.
    	for(i = 0; i < MacLen; i++)
    	{
            YWLIB_Memset(Temp, 0, sizeof(Temp));
            YWLIB_Sprintf((S8*)Temp,(S8*)"%02X",(U32)(*(pMacBuff+i)));
    		YWLIB_Strcat((S8*)pString,(const S8 *)Temp);
    		if(i != MacLen-1)
    		{
    			YWLIB_Strcat((S8*)pString,(S8*)":");
    		}
    	}
        YWLIB_Memcpy((void*)MACAddr,(void*)pString, sizeof(MACAddr)-1);
        //YWOS_Trace(YWOS_TRACE_INFO, "-----MAC Addr is %s--StrLen is %d---\n",MACAddr,strlen(pString));
        //End.Then,we got the MAC.
    
		/*1.Get Device name.*/
        YWLIB_Memset((void*)pString, 0, (U32)sizeof(pString));
        YWLIB_Sprintf(pString,(S8*)"ifconfig -a | grep %s | awk '{print $1}' > HostTemp.txt", MACAddr);
		Status = system((char*)pString);
        if( Status != 0 )
        {
            //YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWTCPIP_SetNet]2. SET Param get device name Failed.\n");
            return YWHAL_ERROR_BAD_PARAMETER;
        }


		Status = system("sed -n '1p' HostTemp.txt > Host.txt");
        if( Status != 0 )
        {
            //YWOS_Trace(YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_SetNet]3. SET Param Failed.\n");
            return YWHAL_ERROR_BAD_PARAMETER;
        }

        YWLIB_Memset((void*)pString, 0, (U32)sizeof(pString));
		if( ( HostFile = fopen("Host.txt" ,"rb+") ) == NULL )
        {
        	//YWOS_Trace(YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_SetNet] Can not open Host.txt.\n");
            return YWHAL_ERROR_UNKNOWN_DEVICE;
		}

		stat("Host.txt",&StatBuff);
		if( StatBuff.st_size == 0)
		{
        	//YWOS_Trace(YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_SetNet] Can not find the MAC Addr.\n");
            fclose(HostFile);
            return YWHAL_ERROR_UNKNOWN_DEVICE;
		}
		fread(DevName, StatBuff.st_size-1, 1, HostFile);
        fclose(HostFile);
		Status = system("rm -f HostTemp.txt Host.txt");
        if( Status != 0 )
        {
            //YWOS_Trace(YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_SetNet]4. SET Param Failed.\n");
            return YWHAL_ERROR_BAD_PARAMETER;
        }
        //end 1. Then got Device Name.
    }
    #endif

    {
        //2. set IPs to the Device.
		//2.1 Get IP Addr.
        //for(j = 0; j < (NetParam->IPLen/4); j++)//
        {
            YWLIB_Memset(Temp, 0, sizeof(Temp));
            YWLIB_Memset((void*)pString, 0, (U32)sizeof(pString));
    		for(i = 0; i < 4; i++)
    		{
    			YWLIB_Sprintf((S8*)Temp, (S8*)"%d", *(NetParam->pIPBuff+i));
    			YWLIB_Strcat((S8*)pString, (const S8 *)Temp);
    			if(i != 3)
    			{
    				YWLIB_Strcat((S8*)pString,(S8*)".");
    			}
    		}
    		YWLIB_Memcpy((void*)IPAddr, (void*)pString, sizeof(IPAddr)-1);
            //YWOS_Trace(YWOS_TRACE_INFO, "[YWTCPIP_SetNet] Got Ip is %s \n", IPAddr);

            //End . Got Ip.

    		//2.2Get NetMask.
    		YWLIB_Memset( Temp, 0, sizeof(Temp));
            YWLIB_Memset((void*)pString, 0, (U32)sizeof(pString));
    		for(i = 0; i < 4; i++)
    		{
    			YWLIB_Sprintf((S8*)Temp, (S8*)"%d", *(NetParam->pNETMASKBuff+i));
    			YWLIB_Strcat((S8*)pString, (const S8 *)Temp);
    			if(i != 3)
    			{
    				YWLIB_Strcat((S8*)pString, (S8*)".");
    			}
    		}
    		YWLIB_Memcpy((void*)NETMASKAddr, (void*)pString, sizeof(NETMASKAddr)-1);
            //YWOS_Trace(YWOS_TRACE_INFO,"[YWTCPIP_SetNet] Got netmask is %s \n",NETMASKAddr);
                
            //End . Got netmask.

    		//2.4 Get GateWay.
    		YWLIB_Memset( Temp, 0, sizeof(Temp));
            YWLIB_Memset((void*)pString, 0, (U32)sizeof(pString));
    		for(i = 0; i < 4; i++)
    		{
    			YWLIB_Sprintf((S8*)Temp, (S8*)"%d", *(NetParam->pGATEWAYBuff+i));
    			YWLIB_Strcat((S8*)pString, (const S8 *)Temp);
    			if(i != 3)
    			{
    				YWLIB_Strcat((S8*)pString,(S8*)".");
    			}
    		}
    		YWLIB_Memcpy((void*)GATEWAYAddr,(void*)pString, sizeof(GATEWAYAddr)-1);


            //2.5 set Ip and netmask
            YWLIB_Memset((void*)pString, 0, (U32)sizeof(pString));
            YWLIB_Sprintf((S8*)pString, (S8*)"ifconfig %s up", DevName);
            system((char*)pString);    

            YWLIB_Memset((void*)pString, 0, (U32)sizeof(pString));
    		YWLIB_Sprintf((S8*)pString, (S8*)"ifconfig %s %s netmask %s",DevName, IPAddr, NETMASKAddr);
    		//YWOS_Trace(YWOS_TRACE_INFO, "[YWTCPIP_SetNet]  Set Ip pString is %s \n",pString);
    		//Set IP and mask
    		Status = system((char*)pString);
            if( Status != 0 )
            {
                //YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWTCPIP_SetNet]5. SET ipaddr Param Failed.\n");
                return YWHAL_ERROR_BAD_PARAMETER;
            }

            //2.6 set Gateway
    		if (*(NetParam->pGATEWAYBuff) == 0 && *(NetParam->pGATEWAYBuff+1) == 0 
                && *(NetParam->pGATEWAYBuff+2) == 0 && *(NetParam->pGATEWAYBuff+3) == 0)
    		{
                //YWOS_Trace(YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_SetNet]6. Gateway 0.0.0.0 invalid.\n");
                return 0;
    		}
            
            system("route del default");
            YWLIB_Memset((void*)pString, 0, (U32)sizeof(pString));
    		YWLIB_Sprintf((S8*)pString, (S8*)"route add default gateway %s", GATEWAYAddr);//lwj change
    		Status = system((char*)pString);
            if( Status != 0 )
            {
                //YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWTCPIP_SetNet]7. SET gateway Failed.\n");
                return YWHAL_ERROR_BAD_PARAMETER;
            }

        }
	}

	return YW_ErrorCode;
}

YW_ErrorType_T YWTCPIP_GetDNSServerIP(U8* pDNSBuff, U8 DNSLen, U8* pAltDNSBuff, U8 AltDNSLen, U8 *DNSServerNum)
{   
   	FILE    *DnsFp = NULL;
    U8      i = 0, j = 0;
	char    line[256] = {0}; 
    char    *lasts = NULL;
	S8  DNSServerIP[MAX_IPSTRING_LEN+1]={0};
    S8  AltDNSServerIP[MAX_IPSTRING_LEN+1]={0};
    int pDNSBuffTmp[4] = {0};

    YW_ErrorType_T YW_ErrorCode = YWHAL_ERROR_UNKNOWN_DEVICE;
    YWLIB_Memset(line, 0, sizeof(line));
    YWLIB_Memset(DNSServerIP, 0, MAX_IPSTRING_LEN+1);
    YWLIB_Memset(AltDNSServerIP, 0, MAX_IPSTRING_LEN+1);
    YWLIB_Memset(pDNSBuffTmp, 0, sizeof(pDNSBuffTmp));


    *DNSServerNum = 0;
    if (pDNSBuff == NULL || (DNSLen != 4) )
    {
        //YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWTCPIP_GetDNSServerIP]MAIN DNS Invalid Parameter.\n");
        return YWHAL_ERROR_BAD_PARAMETER;
    }
    if (pAltDNSBuff == NULL || (AltDNSLen != 4) )
    {
        //YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWTCPIP_GetDNSServerIP]AltDNS Invalid Parameter.\n");
        return YWHAL_ERROR_BAD_PARAMETER;
    }

	DnsFp = fopen("/etc/resolv.conf", "r");
    if (DnsFp == NULL)
    {
        //YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWTCPIP_GetDNSServerIP] Unknown error.\n");
        return YWHAL_ERROR_UNKNOWN_DEVICE;
    }

	while (fgets(line, sizeof(line), DnsFp))
    {
        strtok_r(line, " ", &lasts);
        if (!YWLIB_Strcmp((S8*)line, (S8*)"nameserver"))
        {
            if (j == 0)
            {
                YWLIB_Strncpy((S8*)DNSServerIP, (const S8*)lasts, MAX_IPSTRING_LEN);
                *DNSServerNum = 1;
            }
            else if(j == 1)
            {
                YWLIB_Strncpy((S8*)AltDNSServerIP, (const S8*)lasts, MAX_IPSTRING_LEN);
                *DNSServerNum = 2;
            }
            j++;
        }
        if (j == 2)
        {
            break;
        }
	}
	fclose(DnsFp);
    DnsFp = NULL;
	sscanf((const char*)DNSServerIP, "%d.%d.%d.%d", pDNSBuffTmp, pDNSBuffTmp+1, pDNSBuffTmp+2, pDNSBuffTmp+3);
    for (i = 0; i < 4; i++)
    {
        *(pDNSBuff+i) = (U8)pDNSBuffTmp[i];
    }

    if (j > 1)
    {
        YWLIB_Memset(pDNSBuffTmp, 0, sizeof(pDNSBuffTmp));
        sscanf((const char*)AltDNSServerIP, "%d.%d.%d.%d", pDNSBuffTmp, pDNSBuffTmp+1, pDNSBuffTmp+2, pDNSBuffTmp+3);
        for (i = 0; i < 4; i++)
        {
            *(pAltDNSBuff+i) = (U8)pDNSBuffTmp[i];
        }
    }
    return YW_ErrorCode;
}

YW_ErrorType_T YWTCPIP_SetDNS(U8* pDNSBuff, U8 DNSLen, U8 *pAltDNSBuff, U8 AltDNSLen)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	U8   i = 0;
	S8   String[100] = {0};
    S8   DNSValue[MAX_IPSTRING_LEN+1]={0};   
    S8   AltDNSValue[MAX_IPSTRING_LEN+1]={0};   
    U8   Temp[4];
    char TmpBuf[256];
    FILE  *resolv_fp;


    if( (pDNSBuff == NULL) || (DNSLen != 4) )
	{
        //YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWTCPIP_SetDNS]Invalid Parameter.\n");
		return YWHAL_ERROR_BAD_PARAMETER;
	}

    //Get DNS Val begin.
    if( (pDNSBuff != NULL) && (DNSLen == 4) )
    {
        YWLIB_Memset( String, 0, sizeof(String));
    	YWLIB_Memset(Temp, 0, sizeof(Temp));
        YWLIB_Memset(DNSValue, 0, sizeof(DNSValue));
    	for(i = 0; i < DNSLen; i++)
    	{
            YWLIB_Sprintf((S8*)Temp,(S8*)"%d",(U32)(*(pDNSBuff+i)));
    		YWLIB_Strcat((S8*)String, (const S8*)Temp);
    		if(i != DNSLen-1)
    		{
    			YWLIB_Strcat((S8*)String,(S8*)".");
    		}
    	}
        YWLIB_Memcpy((void*)DNSValue,(void*)String, MAX_IPSTRING_LEN);
    }
    //Get DNS Val end

    //Get AltDNS Val begin
    if( (pAltDNSBuff != NULL) && (AltDNSLen == 4) )
    {
        YWLIB_Memset( String, 0, sizeof(String));
    	YWLIB_Memset(Temp, 0, sizeof(Temp));
        YWLIB_Memset(AltDNSValue, 0, sizeof(AltDNSValue));
        for(i = 0; i < AltDNSLen; i++)
    	{
            YWLIB_Sprintf((S8*)Temp,(S8*)"%d",(U32)(*(pAltDNSBuff+i)));
    	    YWLIB_Strcat((S8*)String, (const S8*)Temp);
    		if(i != AltDNSLen-1)
    		{
    		    YWLIB_Strcat(String,(S8*)".");
    		}
    	}
        YWLIB_Memcpy((void*)AltDNSValue,(void*)String, MAX_IPSTRING_LEN);
    }
    //Get AltDNS Val end

    resolv_fp = fopen("/etc/resolv.conf", "w");
    if (resolv_fp == NULL)
    {
        //YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWTCPIP_SetDNS] open resolv.conf error.\n");
        return YWHAL_ERROR_UNKNOWN_DEVICE;
    }
    YWLIB_Memset(TmpBuf, 0, sizeof(TmpBuf));
    YWLIB_Sprintf((S8*)TmpBuf, (S8 *)"nameserver %s\n", DNSValue);
    fwrite(TmpBuf, 1, strlen(TmpBuf), resolv_fp);
    
    if( (pAltDNSBuff != NULL) && (AltDNSLen == 4) )
    {
        YWLIB_Memset(TmpBuf, 0, sizeof(TmpBuf));
        YWLIB_Sprintf((S8*)TmpBuf, (S8 *)"nameserver %s\n", AltDNSValue);
        fwrite(TmpBuf, 1, strlen(TmpBuf), resolv_fp);
    }
    fclose(resolv_fp);
    resolv_fp = NULL;

    return YW_ErrorCode;
}


/*YW_ErrorType_T YWTCPIP_GetSocketName(YWTCPIP_SocketFD_T SocketFD,
                                        YWTCPIP_SOCKETADDRESS_T *pSocketAddress,
                                        S32 *pSocketNameLen)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	S32 Error = 0;
	//struct sockaddr TargetAddress;

	if( ( pSocketAddress == 0 ) || ( pSocketNameLen == NULL ))
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_GetSocketName] Invalid Parameter.\n") );
        return YWHAL_ERROR_BAD_PARAMETER;
	}

	//YWLIB_Memcpy(&TargetAddress, pSocketAddress, sizeof(YWTCPIP_SOCKETADDRESS_T));

	Error = getsockname(SocketFD, (struct sockaddr*)pSocketAddress, pSocketNameLen);
	if( Error < 0)
	{
        //YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_GetSocketName] Cannot get socket name.\n") );
		YW_ErrorCode = YWTCPIPi_GetErr(errno);
		YW_ErrorCode = errno;
	}

	return YW_ErrorCode;
}*/
#if 0
/***********************************************************************
    函数说明:    根据输入的IP地址设置该IP的NETMASK
    调用说明:    
    
    修改记录:    日       期      作      者       修定
                 ---------         ---------       -----
                 2009.10.20        CS              新建
************************************************************************/
YW_ErrorType_T YWTCPIP_SetNETMASK(U8* pIPBuff,
                                        U8 IPLen ,
                                        U8* pNETMASKBuff,
                                        U8 NETMASKLen)
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	U8 i=0,j=0;
	S8 *pString = NULL,
        MACAddr[MAX_MACSTRING_LEN+1]={0},
        IPAddr[MAX_IPSTRING_LEN+1]={0},
        DevName[8] = {0},
       *pTempString = NULL;
    U8 Temp[6] = {0};
	FILE *HostFile = NULL ;
	struct stat StatBuff;
	
	if( (pNETMASKBuff == NULL) || (NETMASKLen != 4) )
	{
        YWOS_Trace(YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_SetNETMASK] Invalid Parameter.\n");
		return YWHAL_ERROR_BAD_PARAMETER;
	}

	//The max num is 255 for one mac.
	if( ( IPLen != 4 ) || (pIPBuff == NULL) )
	{
        YWOSTRACE(( YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_SetNETMASK] Invalid Parameter.\n") );
        return YWHAL_ERROR_BAD_PARAMETER;
	}

	pString = (S8*)YWOS_Calloc(1, 100);
	if( pString == NULL)
	{
        YWOS_Trace(YWOS_TRACE_ERROR,"[ERROR][YWTCPIP_SetNet] Allocate Mem Failed.\n");
		return YWHAL_ERROR_NO_MEMORY;
	}

	YWLIB_Memset( DevName, 0, 8);
	YWLIB_Memset( Temp, 0, 6);
	YWLIB_Memset( MACAddr, 0, MAX_MACSTRING_LEN+1);
	YWLIB_Memset( IPAddr, 0, MAX_IPSTRING_LEN+1);

	//Get Mac Addr.
	for(i=0;i<IPLen;i++)
	{
        YWLIB_Sprintf(Temp,(S8*)"%03d",(U32)(*pIPBuff));

		pString = YWLIB_Strcat(pString,Temp);
		if(i!=IPLen-1)
		{
			pString = YWLIB_Strcat(pString,(S8*)".");
			pIPBuff++;
		}
	}

	//YWLIB_Memcpy((void*)MACAddr,(void*)strupr(pString), (U32)YWLIB_Strlen(pString));
	YWLIB_Memcpy((void*)MACAddr,(void*)pString, (U32)YWLIB_Strlen(pString));
	//YWOS_Trace(YWOS_TRACE_INFO, "-----MAC Addr is %s--StrLen is %d---\n",MACAddr,strlen(pString));
	//End.Then,we get the MAC.
}
#endif

U32  YWTCPIP_GetVersion( S8 *pchVer, U32 nSize  )
{
    S8 Version[256];
    U32  ActLen;
    U32  RetLen;

    YWLIB_Sprintf(Version,(S8 *)"%s-%s-%s-%s-%s.\n",Ver_Layer,Ver_name,Ver_Version,__DATE__, __TIME__);
    
     ActLen = YWLIB_Strlen( Version ) + 1;
 
     if ( pchVer == NULL )
     {
          RetLen = ActLen;
     }
     else
     {
          if ( nSize == 0 )
          {  
               RetLen = 0;
          }
          else if ( nSize > ActLen )
          {
               RetLen = ActLen;
          }
          else
          {   
               RetLen = nSize;
          }

          YWLIB_Memcpy((void*) pchVer, (void*)Version, RetLen );
     }

     return RetLen;
}

/* EOF --------------------------------------------------------------------- */
