/**********************************文件头部注释************************************/
//
//
//  					Copyright (C), 2005-2010, AV Frontier Tech. Co., Ltd.
//
//
// 文件名：		ywos.h
//
// 创建者：		段海云
//
// 创建时间：	2005.10.13
//
// 文件描述：	操作系统的数据结构和函数声明
//
// 修改记录：   日       期      作      者       版本      修定
//				       ---------         ---------        -----        -----
//              		       2005.10.13         段海云       0.01           新建
/*****************************************************************************************/


#ifndef __YWOS_H__
#define __YWOS_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_HDD_NUM             (16)

enum{
	YWOS_ERROR_BAD_PARAMETER  = YW_MODULE_SET_ID(YWOS_MODULE_PUBLIC_ID ),
	YWOS_ERROR_NO_MEMORY,
	YWOS_ERROR_NOT_INITIALIZED,
	YWOS_ERROR_ALREADY_INITIALIZED,
	YWOS_ERROR_NO_FREE_INSTANCE,
	YWOS_ERROR_INVALID_INSTANCE,
	YWOS_ERROR_TIMEOUT,                   /* Timeout occured            */
	YWOS_ERROR_NOT_SUPPORT,
	YWOS_ERROR

};

//cs added for System Evt.20100106
enum
{
    YWOS_EVENT_USB_INSERT = YW_MODULE_SET_ID( YWOS_MODULE_SYSTEMEVT_ID ),                                                   //新帧到达
    YWOS_EVENT_USB_REMOVE,              //USB is removed.
    YWOS_EVENT_USB_MOUNT,               //USB is Mounted.
    YWOS_EVENT_NET_CONNECTED,           //Net is Connected.
    YWOS_EVENT_NET_DISCONNECTED,        //Net is Disconnected.
    YWOS_EVENT_DISK_FULL,               //lwj add
    YWOS_EVENT_DISK_AVAILABLE,
    YWOS_EVENT_CP_PROGRESS,             //D26lf add for cp
    YWOS_EVENT_CP_FINISH,               //D26lf add for cp
    YWOS_EVENT_TAR_CREATE_PROGRESS,     //D26lf add for tar
    YWOS_EVENT_TAR_CREATE_FINISH,       //D26lf add for tar
    YWOS_EVENT_TAR_EXTRACT_PROGRESS,    //D26lf add for tar
    YWOS_EVENT_TAR_EXTRACT_FINISH,      //D26lf add for tar

    YWOS_EVENT_FLASHCP_ERASE,
    YWOS_EVENT_FLASHCP_WRITE,
    YWOS_EVENT_FLASHCP_VERIFY,

    YWOS_EVENT_USB_WIFI_CARD_REMOVE,    //USB wifi card is removed.
    YWOS_EVENT_USB_WIFI_CARD_INSERT,    //USB wifi card is insert.

    YWOS_EVENT_HDD_INSERT,  //包括USB HDD or SATA HDD insert
    YWOS_EVENT_HDD_REMOVE,  //包括USB HDD or SATA HDD removed

};

#define   YWOS_COMMON_HANDLE			(0xffffffff)

typedef enum YWOS_USB_State_e
{
    YWOS_USB_STATE_INSERT = 0,
    YWOS_USB_STATE_REMOVED
}YWOS_USB_State_T;


typedef struct YWOS_USB_Data_s
{
    U8 USB_Index;
    YWOS_USB_State_T USB_State;
}YWOS_USB_Data_T;  //之前用于7111上的结构体定义，以后不再使用


typedef struct YWOS_DISK_Size_Data_s
{
    S32 DiskSize;
    S8  DiskName[16];
}YWOS_DISK_Size_Data_T;

typedef enum YWOS_DISK_Charset_e
{
    YWOS_DISK_CHARSET_DEFAULT = 0, //iso8859-1
    YWOS_DISK_CHARSET_UTF8,
    YWOS_DISK_CHARSET_GB2312,
    YWOS_DISK_CHARSET_BIG5  //not support
}YWOS_DISK_Charset_T;

typedef enum YWOS_ETH_State_e
{
    YWOS_ETH_STATE_LINK = 0,
    YWOS_ETH_STATE_UNLINK
}YWOS_ETH_State_T;

typedef enum YWOS_ETH_Speed_e
{
    YWOS_ETH_SPEED_100M = 0,
    YWOS_ETH_SPEED_10M,
    YWOS_ETH_SPEED_UNKNOWN
}YWOS_ETH_Speed_T;


typedef struct YWOS_ETH_Data_s
{
    U8 Eth_Index;
    YWOS_ETH_Speed_T Eth_Speed;
    YWOS_ETH_State_T Eth_State;
}YWOS_ETH_Data_T;


/********************************/
typedef enum YWOS_Hotplug_Type_e
{
    YWOS_HOTPLUG_UNKNOWN = 0,
    YWOS_HOTPLUG_SATA,
    YWOS_HOTPLUG_REAR_USB, //back usb 
    YWOS_HOTPLUG_FRONT_USB, //front usb
}YWOS_Hotplug_Type_T;

typedef enum YWOS_Hotplug_State_e
{
    YWOS_HOTPLUG_INSERT = 0,
    YWOS_HOTPLUG_REMOVED
}YWOS_Hotplug_State_T;

typedef struct YWOS_Hotplug_Event_s
{
    YWOS_Hotplug_State_T Hotplug_State;
    YWOS_Hotplug_Type_T  Hotplug_Interface_Type; 
    S8  Device_Name[4];
}YWOS_Hotplug_Event_T;

typedef struct YWOS_HDD_DEV_Info_Tmp_s
{
    char HDD_DevName[4]; //"sda","sdb","sdc" .....
    YWOS_Hotplug_Type_T  Hotplug_Interface_Type; 
}YWOS_HDD_DEV_Info_Tmp_T;

typedef struct YWOS_HDD_DEV_Info_s
{
    U8   Total_HDD_Num;
    YWOS_HDD_DEV_Info_Tmp_T  HDD_DevInfo[MAX_HDD_NUM];
}YWOS_HDD_DEV_Info_T;

/**********************************/


//宏及常量

#define   YWOS_WAIT_INFINITY		(0xFFFFFFFF)
#define   YWOS_WAIT_IMMEDIATE		(0x00000000)
#define   YWOS_1_SEC			1000

#define   YWOS_INVALID_ID			0xffffffff


#define YWOS_TRACE_INFO 		1
#define YWOS_TRACE_WARN 		2
#define YWOS_TRACE_ERROR 		3

//数据结构
typedef   U32    YWOS_ClockMsec_T;
//typedef   S32    YWOS_ClockMsec_T;

typedef   U32    YWOS_PartitionID_T;
typedef   U32    YWOS_ThreadID_T;
typedef   U32    YWOS_MessageID_T;
typedef   U32    YWOS_SemaphoreID_T;
typedef   U32    YWOS_MutexID_T;
typedef   U32    YWOS_MonitorID_T;

/*
typedef struct YWOS_Config_s
{
    U32      ClkA_MHZ;
    U32      ClkB_MHZ;
    U32      MemorySize_MB;
}YWOS_Config_T;
*/

YW_ErrorType_T YWOS_Init(void);
YW_ErrorType_T YWOS_Term(void);
YW_ErrorType_T YWOS_PartitionCreate(S8* Name, void* Start,  U32 Size, YWOS_PartitionID_T* Partion);
YW_ErrorType_T YWOS_PartitionDelete( YWOS_PartitionID_T Partion  ) ;
void*   YWOS_PartitionMalloc( YWOS_PartitionID_T Partion,  U32 Size  )  ;
YW_ErrorType_T 	YWOS_PartitionFree( YWOS_PartitionID_T Partion, void* Block  ) ;

void*   YWOS_MallocCheck( U32 Size,S8* FileName, U32 Line) ;
void*   YWOS_CallocCheck( U32 num,U32 Size,S8* FileName, U32 Line);
YW_ErrorType_T YWOS_Free( void *Block) ;
void*   YWOS_CallocNcacheCheck( U32 num,U32 Size,S8* FileName, U32 Line);
void*   YWOS_MallocNcacheCheck( U32 Size,S8* FileName, U32 Line) ;
YW_ErrorType_T YWOS_FreeNcache( void *Block) ;

YW_ErrorType_T YWOS_ThreadCreate(   S8* Name,  void(*Function)(void *Param), void* Param, void* Stack, U32 StackSize, U32 Priority, BOOL Start, YWOS_ThreadID_T * ThreadID ) ;
YW_ErrorType_T YWOS_ThreadDelete( YWOS_ThreadID_T  ThreadID);
YW_ErrorType_T YWOS_ThreadStart(  YWOS_ThreadID_T  ThreadID ) ;
YW_ErrorType_T YWOS_ThreadStop( YWOS_ThreadID_T  ThreadID  ) ;
YW_ErrorType_T YWOS_ThreadPriority(  YWOS_ThreadID_T  ThreadID , U32 Priority) ;
YW_ErrorType_T YWOS_ThreadGetPriority(  YWOS_ThreadID_T  ThreadID , U32* Priority) ;
YW_ErrorType_T YWOS_ThreadId( YWOS_ThreadID_T  *ThreadID  ) ;
YW_ErrorType_T YWOS_TaskSleep(YWOS_ClockMsec_T Time);
BOOL YWOS_ThreadIsCancel(YWOS_ThreadID_T  ThreadID);

YW_ErrorType_T YWOS_MessageQueueCreate( S8* Name, U32 ElementSize, U32 ElementNo, YWOS_MessageID_T * MessageID) ;
YW_ErrorType_T YWOS_MessageQueueDelete( YWOS_MessageID_T MessageID  ) ;
YW_ErrorType_T YWOS_MessageQueueSend( YWOS_MessageID_T MessageID , YWOS_ClockMsec_T TimeOut, void* Message ) ;
YW_ErrorType_T YWOS_MessageQueueReceive( YWOS_MessageID_T MessageID , YWOS_ClockMsec_T TimeOut, void* Message ) ;

YW_ErrorType_T YWOS_SemaphoreCreate( S8* Name, U32 Count,  YWOS_SemaphoreID_T* SemaphoreID ) ;
YW_ErrorType_T YWOS_SemaphoreDelete(  YWOS_SemaphoreID_T  SemaphoreID ) ;
YW_ErrorType_T YWOS_SemaphoreSend(  YWOS_SemaphoreID_T  SemaphoreID ) ;
YW_ErrorType_T YWOS_SemaphoreWait( YWOS_SemaphoreID_T  SemaphoreID , YWOS_ClockMsec_T TimeOut ) ;
YW_ErrorType_T YWOS_SemaphoreCount( YWOS_SemaphoreID_T  SemaphoreID , S32* Count  ) ;

YW_ErrorType_T YWOS_MutexCreate(  YWOS_MutexID_T* MutexID ) ;
YW_ErrorType_T YWOS_MutexDelete(  YWOS_MutexID_T  MutexID ) ;
YW_ErrorType_T YWOS_MutexSend( YWOS_MutexID_T  MutexID ) ;
YW_ErrorType_T YWOS_MutexWait( YWOS_MutexID_T  MutexID , YWOS_ClockMsec_T TimeOut ) ;


YWOS_ClockMsec_T YWOS_TimeNow( void );
YWOS_ClockMsec_T YWOS_TimeMinus( YWOS_ClockMsec_T time1, YWOS_ClockMsec_T time2 );
YWOS_ClockMsec_T YWOS_TimePlus( YWOS_ClockMsec_T time1, YWOS_ClockMsec_T time2  ) ;
S32 YWOS_TimeAfter( YWOS_ClockMsec_T time1, YWOS_ClockMsec_T time2  );

YW_ErrorType_T YWOS_ModuleRegister( S8* Name, void(*InitFunction)(void),void(*TermFunction)(void ), U32 DependNum,S8**DependModule) ;
YW_ErrorType_T YWOS_ModuleUnregister( S8* Name) ;
YW_ErrorType_T YWOS_ModuleLoadAll( void) ;
YW_ErrorType_T YWOS_ModuleUnloadAll( void) ;
YW_ErrorType_T YWOS_ModuleLoad( S8 *Name) ;
YW_ErrorType_T YWOS_ModuleUnload( S8 *Name) ;

void YWOS_SetTraceLevel( U32 Level);
void YWOS_Trace( U32 Level, const char  Format[ ], ... );
void YWOS_TracePartitionInfo( YWOS_PartitionID_T partion );
void YWOS_TraceCpuStart( void );
void YWOS_TraceCpuEnd( void );

YW_ErrorType_T  YWOS_MonitorCreate(S8* Name,  YWOS_ThreadID_T ThreadID, YWOS_ClockMsec_T TimeOut,  YWOS_MonitorID_T *MonitorID);
YW_ErrorType_T  YWOS_MonitorDelete(YWOS_MonitorID_T MonitorID);
YW_ErrorType_T  YWOS_MonitorSet(YWOS_MonitorID_T MonitorID);

void YWOS_MemoryCheck(void);
//#define YWOS_MEMLEAK_CHECK
#ifdef YWOS_MEMLEAK_CHECK


#define YWOS_Malloc(n)          YWOS_MallocCheck((n),(S8 *)__FILE__,__LINE__)
#define YWOS_Calloc(n,Size)     YWOS_CallocCheck((n),(Size),(S8 *)__FILE__,__LINE__)
#define YWOS_MallocNcache(n)    YWOS_MallocNcacheCheck((n),(S8 *)__FILE__,__LINE__)
#define YWOS_CallocNcache(n,Size)    YWOS_CallocNcacheCheck((n),(Size),(S8 *)__FILE__,__LINE__)
#else
#define YWOS_Malloc(n)          YWOS_MallocCheck((n),(S8 *)NULL,0)
#define YWOS_Calloc(n,Size)     YWOS_CallocCheck((n),(Size),(S8 *)NULL,0)
#define YWOS_MallocNcache(n)    YWOS_MallocNcacheCheck((n),(S8 *)NULL,0)
#define YWOS_CallocNcache(n,Size)    YWOS_CallocNcacheCheck((n),(Size),(S8 *)NULL,0)

#endif

YW_ErrorType_T YWOS_Boot( void * PrivateData );

YW_ErrorType_T YWOS_Reboot( void * PrivateData );

YW_ErrorType_T YWOS_Halt( void * PrivateData );

YW_ErrorType_T YWOS_Standby( U32 AutoStartUpTime );

void YWOS_Exit(S32 ExitParam);

/* Set the MacAddr of the aim Ethernet Card. */
YW_ErrorType_T YWOS_SetMACAddr( U8 EthCardIndex,U8* pMacBuff,U8 MacLen );
YW_ErrorType_T YWOS_GetMACAddr( U8 EthCardIndex, U8* pMacBuff, U8 MacLen);

void YWOS_DiskMonitorEnable(S8 *diskname, S32 ksize);
void YWOS_DiskMonitorDisable(S8 *diskname);



void YWOS_EthIsLinked(U8 EthIndex, YWOS_ETH_Data_T *EthInfo);

YW_ErrorType_T YWOS_SetFlashRoMode(U8 MtdIndex);
YW_ErrorType_T YWOS_SetFlashRWMode(U8 MtdIndex);

YW_ErrorType_T YWOS_SmbMount(S8 *ipaddr,
            S8 *samba_share_folder_name, S8 *username, S8 *password);
YW_ErrorType_T YWOS_SmbUMount(S8 *ipaddr, S8 *samba_share_folder_name);
YW_ErrorType_T YWOS_NFSMount(S8 *ipaddr, S8 *nfs_folder_path, S8 mount_name_lastnum); //nfs_folder_path要以"/"开头
YW_ErrorType_T YWOS_NFSUMount(S8 *ipaddr, S8 *nfs_path, S8 mount_name_lastnum);            
void YWOS_GetWirelessName(char *ifname);



BOOL YWOS_USBWifiCardIsInserted(void);
YW_ErrorType_T YWOS_SetPassword(S8 *username, S8 *OldPasswd, S8 *NewPasswd);


#if 1 //this will remove for next revision
BOOL YWOS_USBIsMounted(void);
BOOL YWOS_USBIsInserted(void);
YW_ErrorType_T YWOS_USBMount(S8* DevName, U8 USBIndex, YWOS_DISK_Charset_T DiskCharSet);
YW_ErrorType_T YWOS_USBUmount(S8* DevName,U8 USBIndex);
YW_ErrorType_T YWOS_USBFsck(S8* DevName, U8 USBIndex);
#endif

/************************************************************************/
BOOL YWOS_HDDIsMounted(void);
BOOL YWOS_HDDIsInserted(void);
void YWOS_HDDGetDevInfo(YWOS_HDD_DEV_Info_T *DiskDevInfo, U8 *TotalHddNum);
YW_ErrorType_T YWOS_HDDMount(S8* DevName, YWOS_DISK_Charset_T DiskCharSet);
YW_ErrorType_T YWOS_HDDUmount(S8* DevName);
YW_ErrorType_T YWOS_HDDFsck(S8* DevName);
/*************************************************************************/

#define POSIX_GetClocksPerSecond() /*15625*/1000

/*
YW_ErrorType_T YWOS_GetConfig(YWOS_Config_T *config);
YW_ErrorType_T YWOS_Config(YWOS_Config_T *config);
*/

#ifdef __cplusplus
}
#endif

#endif
