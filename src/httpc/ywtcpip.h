
#ifndef __YWTCPIP_EXT_H
#define __YWTCPIP_EXT_H

#ifdef __cplusplus
extern "C" {
#endif
/************************************宏定义*******************************************/
#define YWTCPIP_FD_SETSIZE (1024)
#define YWTCPIP_F_GETFL    (3)//F_GETFL		3	/* get file->f_flags */
#define YWTCPIP_F_SETFL    (4)//F_SETFL		4	/* set file->f_flags */
#define YWTCPIP_SO_RCVBUF  (8)
#define YWTCPIP_SO_REUSEADDR (2)
#define YWTCPIP_SO_ERROR   (4)
/************************************常量定义****************************************/
typedef U32   YWTCPIP_SocketFD_T ; 

enum
{
	YWTCPIP_ERROR_INIT  = YW_MODULE_SET_ID(YWHAL_MODULE_TCPIP_ID),  
	YWTCPIP_ERROR_OPEN,   
	YWTCPIP_ERROR_CLOSE,
	YWTCPIP_ERROR_TERM,
	YWTCPIP_ERROR_SOCKET,
	YWTCPIP_ERROR_BIND,
	YWTCPIP_ERROR_ACCEPT,
	YWTCPIP_ERROR_RECV,
	YWTCPIP_ERROR_LISTEN,
	YWTCPIP_ERROR_SEND,
	YWTCPIP_ERROR_SHUTDOWN,//10
	YWTCPIP_ERROR_GETPEERNAME,
	YWTCPIP_ERROR_GETHOSTNAME,
	YWTCPIP_ERROR_BADADDRESS, /*EFAULT(14)	 Bad address */
	YWTCPIP_ERROR_NOTSOCKET,  /*ENOTSOCK(216) Socket operation on non-socket */ 
	YWTCPIP_ERROR_ISCONNECT, /*EISCONN(234) Transport endpoint is already connected */
	YWTCPIP_ERROR_CONNECTREFUSED, /*ECONNREFUSED(239) Connection refused */
	YWTCPIP_ERROR_TIMEOUT, /*ETIMEDOUT(238) Connection timed out */
	YWTCPIP_ERROR_NETUNREACH, /*ENETUNREACH(229) Network is unreachable */
	YWTCPIP_ERROR_AFNOTSUPPORT, /*EAFNOSUPPORT(225) Address family not supported by protocol */
	YWTCPIP_ERROR_ALREADY,//20 /*EALREADY(244) Operation already in progress */
	YWTCPIP_ERROR_PROTONOSUPPORT, /*EPROTONOSUPPORT(221) Protocol not supported */
	YWTCPIP_ERROR_NOBUFS, /*ENOBUFS(233) No buffer space available */
	YWTCPIP_ERROR_NOMEM, /* ENOMEM(12)	Out of Memory */
	YWTCPIP_ERROR_BADPARAMMETERS, /*EINVAL(22) Invalid argument */
	YWTCPIP_ERROR_BADFILENUM, /*EBADF(9) Bad file number */
	YWTCPIP_ERROR_OPNOTSUPP, /*EOPNOTSUPP(223) Operation not supported on transport endpoint */
	YWTCPIP_ERROR_NOTSOCK, /*ENOTSOCK(216) Socket operation on non-socket */
	YWTCPIP_ERROR_PERM, /*EPERM(1) Operation not permitted */
	YWTCPIP_ERROR_INTR, /*EINTR(4) Interrupted system call */
	YWTCPIP_ERROR_INPROGRESS, /* Operation now in progress */
	YWTCPIP_ERROR_AGAIN /*EAGAIN(35) Try again */
};

/************************************变量定义****************************************/

/************************************数据结构****************************************/

/*Protocol Family for communication.Here only include the currently  
understood  formats.*/
typedef enum YWTCPIP_PF_e
{
	YWTCPIP_PF_UNIX = 1,	 /* Unix domain sockets */
	YWTCPIP_PF_INET,		 /* IPv4 Internet protocols */
    YWTCPIP_PF_INET6,		 /* IPv6 Internet protocols */
    YWTCPIP_PF_IPX,          /* IPX - Novell protocols */
    YWTCPIP_PF_NETLINK,      /* Kernel user interface device */
    YWTCPIP_PF_X25,          /* ITU-T X.25 / ISO-8208 protocol */
    YWTCPIP_PF_AX25,         /* Amateur radio AX.25 protocol */
    YWTCPIP_PF_ATMPVC,       /* Access to raw ATM PVCs */
    YWTCPIP_PF_APPLETALK,    /* Appletalk */
    YWTCPIP_PF_PACKET,  	 /* Low level packet interface */
    YWTCPIP_PF_NUM
}YWTCPIP_PF_T;

/***Local communication*/
typedef enum YWTCPIP_AF_e
{
	YWTCPIP_AF_UNIX = 1,	 /* Unix domain sockets */
	YWTCPIP_AF_INET,		 /* IPv4 Internet protocols */
    YWTCPIP_AF_INET6,		 /* IPv6 Internet protocols */
    YWTCPIP_AF_IPX,          /* IPX - Novell protocols */
    YWTCPIP_AF_NETLINK,      /* Kernel user interface device */
    YWTCPIP_AF_X25,          /* ITU-T X.25 / ISO-8208 protocol */
    YWTCPIP_AF_AX25,         /* Amateur radio AX.25 protocol */
    YWTCPIP_AF_ATMPVC,       /* Access to raw ATM PVCs */
    YWTCPIP_AF_APPLETALK,    /* Appletalk */
    YWTCPIP_AF_PACKET,  	 /* Low level packet interface */
    YWTCPIP_AF_NUM
}YWTCPIP_AF_T;

/*Socket types,which specifies the communication semantics*/
typedef enum YWTCPIP_SOCKETTYPE_e
{
	YWTCPIP_SOCKETTYPE_DGRAM	= 1, /*datagram (conn.less) socket*/
	YWTCPIP_SOCKETTYPE_STREAM	= 2, /*stream (connection) socket*/
	YWTCPIP_SOCKETTYPE_RAW		= 3, /*raw socket*/
	YWTCPIP_SOCKETTYPE_RDM		= 4, /*reliably-delivered message*/
	YWTCPIP_SOCKETTYPE_SEQPACKET= 5, /*sequential packet socket*/
	YWTCPIP_SOCKETTYPE_DCCP		= 6, /*datagram (conn.less) socket*/
	YWTCPIP_SOCKETTYPE_PACKET	= 10 
}YWTCPIP_SOCKETTYPE_T;

typedef enum YWTCPIP_FCNTLPARAM_e
{
	YWTCPIP_FCNTLPARAM_O_NONBLOCK = 1,  /* HPUX has separate NDELAY & NONBLOCK */
    YWTCPIP_FCNTLPARAM_NOARGS,          /* YW Define*/
    YWTCPIP_FCNTLPARAM_O_BLOCK         
}YWTCPIP_FCNTLPARAM_T;

typedef enum YWTCPIP_SOCKETMSG_e
{
    YWTCPIP_SOCKETMSG_NOSIGNAL = 1     /* Do not generate SIGPIPE */
}YWTCPIP_SOCKETMSG_T;

typedef struct YWTCPIP_SOCKETADDRESS_s
{
	U16 		 SOCKETADDRESS_Family;		/* address family, AF_xxx	*/
	S8	 		 SOCKETADDRESS_Data[14];	/* 14 bytes of protocol address	*/
}YWTCPIP_SOCKETADDRESS_T;

typedef struct YWTCPIP_SOCKETADDRESSIN_s
{
	U16			 SOCKETADDRESSIN_Family;	/* address family, AF_xxx	*/
	U16			 SOCKETADDRESSIN_Port;		/* Port Number*/
	U32	 		 SOCKETADDRESSIN_IP;	    /* Protocol address	*/
	U8			 SOCKETADDRESSIN_Zero[8];
}YWTCPIP_SOCKETADDRESSIN_T;

/* Description of data base entry for a single host.  */
typedef struct YWTCPIP_HOSTINFO_s
{
	S8*		pName;		/* Official name of host.  */
	S8** 	pAliases;	/* Alias list.  */
	S32		AddressType;/* Host address type.  */
	S32		AddressLen;	/* Length of address.  */
  	S8** 	pAddresslist;			/* List of addresses from name server.  */
	//#define	Addr	pAddresslist[0]	/* Address, for backward compatibility.  */
}YWTCPIP_HOSTINFO_T;

typedef struct YWTCPIP_FDSET_s
{
	U32 FDSET_BITS[32];
}YWTCPIP_FDSET_T;

typedef struct YWTCPIP_TIMEVAL_s
{
	S32 TIMEVAL_SEC;		/* seconds */
	S32 TIMDVAL_MSEC;		/* microseconds */
}YWTCPIP_TIMEVAL_T;

typedef struct YWTCPIP_SETNET_s
{
    //Ip
    U8* pIPBuff;
    U32 IPLen;
    //Netmask
    U8* pNETMASKBuff;
    U32 NETMASKLen;
    //Gateway
    U8* pGATEWAYBuff;
    U32 GATEWAYLen;
}YWTCPIP_SETNET_T;
/************************************变量定义****************************************/

/************************************变量引用****************************************/

/************************************函数定义****************************************/
YW_ErrorType_T YWTCPIP_Init(void);
YW_ErrorType_T YWTCPIP_Term(void);

/*Creates an endpoint for communication.*/
YW_ErrorType_T YWTCPIP_Socket(YWTCPIP_SocketFD_T* pSocketFD,
								YWTCPIP_PF_T Domain,
								YWTCPIP_SOCKETTYPE_T SockType,
								S32	Protocols);

/*Associate or disassocate TIPC name(s) with a socket.*/
YW_ErrorType_T YWTCPIP_Bind(YWTCPIP_SocketFD_T SocketFD,
								YWTCPIP_SOCKETADDRESS_T *pSocketAddress,
								S32	AddressLength);

/*Open a connection on socket to peer at SocketAddress.*/
YW_ErrorType_T YWTCPIP_Connect(YWTCPIP_SocketFD_T SocketFD,
								YWTCPIP_SOCKETADDRESS_T *pSocketAddress,
								S32	AddressLength);

/*Listen for connections on a socket*/
YW_ErrorType_T YWTCPIP_Listen(YWTCPIP_SocketFD_T SocketFD,
								S32	Backlog);

/*wait for connection request*/
YW_ErrorType_T YWTCPIP_Accept(YWTCPIP_SocketFD_T SocketFD,
								void *pSocketAddress,
								S32	*pAddressLength,
								YWTCPIP_SocketFD_T *pNewSocketFD);

/*Send a message on a socket*/
S32 YWTCPIP_Send(YWTCPIP_SocketFD_T SocketFD,
								const void* pSendMsg,
								S32	MsgLength,
								//S32 Flag);
								YWTCPIP_SOCKETMSG_T MSGFlag);

/*receive a message from a socket*/
S32 YWTCPIP_Recv(YWTCPIP_SocketFD_T SocketFD,
								void* pReceivedBuf,
								S32	BufLength);

/*Send a message on a socket*/
S32 YWTCPIP_Sendto(YWTCPIP_SocketFD_T SocketFD,
								const void* pSendMsg,
								S32	MsgLength,
								const YWTCPIP_SOCKETADDRESS_T *pToSocketAddress,
								S32	ToAddressLength);

/*receive a message from a socket*/
S32 YWTCPIP_RecvFrom(YWTCPIP_SocketFD_T SocketFD,
								void* pReceivedBuf,
								S32	BufLength,
								const YWTCPIP_SOCKETADDRESS_T *pFromSocketAddress,
								S32	*pFromAddressLength);

/*Get Peer name*/
YW_ErrorType_T YWTCPIP_GetPeerName(YWTCPIP_SocketFD_T SocketFD,
								YWTCPIP_SOCKETADDRESS_T *pSocketAddress,
								S32	*pAddressLength);

/*Get Host name*/
YW_ErrorType_T YWTCPIP_GetHostName(S8 *pHostName,
										U32	NameLength);

/*Close the connection*/
YW_ErrorType_T YWTCPIP_CloseSocket(YWTCPIP_SocketFD_T SocketFD);

/*Shutdown socket connection
How:
0—Further receivesare disallowed
1—Further sendsare disallowed
2—Further sendsand receivesare disallowed(likeclose())
*/
YW_ErrorType_T YWTCPIP_ShutdownSocket(YWTCPIP_SocketFD_T SocketFD,
										S32 How);
/*
S32 YWTCPIP_Select(YWTCPIP_SocketFD_T SocketFD,
								S32 Maxtime,
								S32 Waitfor);
*/

S32 YWTCPIP_Select(YWTCPIP_SocketFD_T SocketFD,
								YWTCPIP_FDSET_T *ReadFDS,
								YWTCPIP_FDSET_T *WriteFDS,
								YWTCPIP_FDSET_T *ExceptFDS,
								YWTCPIP_TIMEVAL_T *TimeOut);

void YWTCPIP_FD_CLR(YWTCPIP_SocketFD_T SocketFD,
						YWTCPIP_FDSET_T *Set);

S32 YWTCPIP_FD_ISSET(YWTCPIP_SocketFD_T SocketFD,
						YWTCPIP_FDSET_T *Set);

void YWTCPIP_FD_SET(YWTCPIP_SocketFD_T SocketFD,
						YWTCPIP_FDSET_T *Set);

void YWTCPIP_FD_ZERO(YWTCPIP_FDSET_T *Set);

/* get network host entry */
YWTCPIP_HOSTINFO_T *YWTCPIP_GetHostByName(const S8* pHostName);
YW_ErrorType_T YWTCPIP_GetHostByName_r(const S8* pHostName, YWTCPIP_HOSTINFO_T *hostinfo, U8 *buf, U32 buflen, YWTCPIP_HOSTINFO_T **result, S32 *h_errnop );

/*Set options on sockets*/
YW_ErrorType_T YWTCPIP_SetSocketOpt(YWTCPIP_SocketFD_T SocketFD,
										S32 Level,
										S32 OptName,
										const void *OptVal,
										S32 OptLen);

/*Get options on sockets*/
YW_ErrorType_T YWTCPIP_GetSocketOpt(YWTCPIP_SocketFD_T SocketFD,
										S32 Level,
										S32 OptName,
										void *OptVal,
										S32 *OptLen);

S32 YWTCPIP_Fcntl(YWTCPIP_SocketFD_T SocketFD,
										S32 CMD,
										YWTCPIP_FCNTLPARAM_T Param);

/*Associate some IPAddrs  with one MAC.
  We store all the IPAddrs in the IPBuff one by one.
*/
YW_ErrorType_T YWTCPIP_SetNet(U8* pMacBuff,U8 MacLen ,YWTCPIP_SETNET_T *NetParam);
YW_ErrorType_T YWTCPIP_GetNet(U8*pMacBuff, U8 MacLen, U8 *pIPBuff, U8 *pNETMASKBuff, U8 *pGATEWAYBuff);                            

//YW_ErrorType_T YWTCPIP_SetNETMASK(U8* pIPBuff,U8 IPLen ,U8* pNETMASKBuff,U8 NETMASKLen);

YW_ErrorType_T YWTCPIP_SetDNS(U8* pDNSBuff, U8 DNSLen, U8 *pAltDNSBuff, U8 AltDNSLen);
YW_ErrorType_T YWTCPIP_GetDNSServerIP(U8* pDNSBuff, U8 DNSLen, U8* pAltDNSBuff, U8 AltDNSLen, U8 *DNSServerNum);

YW_ErrorType_T YWTCPIP_GetSocketName(YWTCPIP_SocketFD_T SocketFD,
                                        YWTCPIP_SOCKETADDRESS_T *pSocketAddress,
                                        S32 *pSocketNameLen);
YW_ErrorType_T YWTCPIP_SetDHCP(void);


void YWTCPIP_StopDHCP(void);
U32  YWTCPIP_GetVersion( S8 *pchVer, U32 nSize  );

#ifdef __cplusplus
}
#endif


#endif
