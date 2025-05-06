/**********************************文件头部注释************************************/
//
//
//                      Copyright (C), 2005-2010, AV Frontier Tech. Co., Ltd.
//
//
// 文件名：        ywos.c
//
// 创建者：        詹翰明
//
// 创建时间：    2008.04.04
//
// 文件描述：    完成对ST / NEC / ALI 操作系统的封装
//
// 修改记录：   日       期      作      者       版本      修定
//              ---------            -----------           -----           -----
//              2008.04.04        詹翰明       0.01           新建      加入stos20 支持
//
/*****************************************************************************************/


/************************************文件包含****************************************/




#define         YWOS_YES     1
#define         YWOS_NO    0

#define         YWOS_TRACE_FORM_CONSOLE     (YWOS_YES)
#define         YWOS_TRACE_FORM_UART        (YWOS_NO)
//d48zm 2010.07.06 modify begin
#define 		YWOS_TRACE_TO_LOG			(YWOS_NO)
#define 		YWOS_LOG_MAX_SIZE			(1*YW_M)
//d48zm 2010.07.06 modify end
#define         YWOS_TRACE_ONCE_BUF         (512)



#define         YWOS_STOS20        (YWOS_NO)
#define         YWOS_STOS21        (YWOS_NO)
#define         YWOS_NECITRON      (YWOS_NO)
#define         YWOS_ALI3329       (YWOS_NO)
#define         YWOS_STLINUX       (YWOS_YES)


#define         YWOS_MEMORY_INFO_CHECK  (YWOS_NO)


#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#include <time.h>

#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <termios.h>
#include <sys/poll.h>
#include <stdarg.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>

#include "ywdefs.h"
#include "ywos_stos.h"

//#include "stddefs.h"

#include "ywos.h"

#if (  YWOS_STLINUX == YWOS_YES )
//#include "stevt.h"
//#include "ywos_stos.h"
//#include "ywsystem_def.h"
#include "ywlib.h"
//#include "ywsystem.h"
//#include "ywpanel_def.h"
//#include "ywos_systemmsg.h"
#include "ywevt.h" //for systemmmsg.h usb auto mount
#include <fcntl.h>

#include <netinet/in.h>         /* For struct sockaddr_in */
#include <netinet/if_ether.h>
#include <sys/socket.h>			/* for "struct sockaddr" et al	*/
#include <ctype.h>
#include <net/if.h>
//#include "ywos_flash_setmode.h"

#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>

#endif



/************************************宏定义*******************************************/
#define       YWOS_PARTITION_MAX        5
#define       YWOS_THREAD_MAX           64
#define       YWOS_MESSAGE_MAX          32
#define       YWOS_SEMAPHORE_MAX        256
#define       YWOS_MUTEX_MAX            512
#define       YWOS_MEMORY_INFO_MAX      (20 * YW_K)

#define YWOS_THREAD_PRIORITY_STUB (15+8)
/************************************常量定义****************************************/

#if (YWOS_TRACE_TO_LOG == YWOS_YES)
enum{	LOG_FILE_NUM = 1	};
static char * LogFileName[LOG_FILE_NUM] = {"/root/ywlog.lg"};
#endif


/************************************变量定义****************************************/


#if ( YWOS_STLINUX == YWOS_YES )
#define Task_Create(_func_,_param_,_stack_,_pri_,_name_,_flag_,_task_) ((pthread_create(&(_task_),NULL,(void*)(_func_),(void*)(_param_))==0)?(_task_):0)
#define MAX_USER_PRIORITY    99
#define MIN_USER_PRIORITY    1
#define PTHREAD_MUTEX_RECURSIVE    1
#define PTHREAD_MUTEX_RECURSIVE_NP 1

#define Task_t                                                         pthread_t
#define Task_Priority_Set(_task_id_,_pri_)                             {struct sched_param p; p.sched_priority=(_pri_==0)?1:_pri_; pthread_setschedparam(_task_id_,SCHED_RR,&p);}
#define Task_Wait(_task_id_)                                           pthread_join(_task_id_,NULL);
#define Task_Id()                                                      pthread_self()

#define TIMEOUT_INFINITY    ((POSIX_Clock_t *)NULL)
#define TIMEOUT_IMMEDIATE   ((POSIX_Clock_t *)-1)


typedef    struct                                     /*st os,  task table define*/
{
    U8              Used;
    Task_t          ThreadT;
    BOOL            IsCancel;
    void*           ThreadStack;
}YWOS_ThreadTable_T;

typedef    struct                                     /*st os,  msg table define*/
{
    U8                      Used;
    message_queue_t*        MsgT;
    U32                     MsgElementSize;
    U8                      MsgElementNo;
}YWOS_MessageTable_T;


typedef    struct                                     /*st os,  semaphore table define*/
{
    U8              Used;
    sem_t*    SemT;

}YWOS_SemaphoreTable_T;

typedef    struct                                     /*st os,  mutex table define*/
{
    U8           Used;
    pthread_mutex_t*     MutT;

}YWOS_MutexTable_T;


static pthread_mutex_t* Mutex_Partition = NULL;
static pthread_mutex_t* Mutex_Thread = NULL;
static pthread_mutex_t* Mutex_Msg = NULL;
static pthread_mutex_t* Mutex_Sem = NULL;
static pthread_mutex_t* Mutex_MUTEX = NULL;
#endif

#if(YWOS_MEMORY_INFO_CHECK  == YWOS_YES)
typedef    struct                                     /*nec os,  semaphore table define*/
{
    U8       Used;
    void*    AddrPtr;
    void*    AddrBase;
    void*    AddrEnd;
    S8*      FileName;
    U32      Line;
}YWOS_MemoryInfo_T;


static YWOS_MutexID_T   MutexMemoryLock = YW_INVALID_HANDLE;
YWOS_MemoryInfo_T   MemoryInfo[YWOS_MEMORY_INFO_MAX];

static U32 MemoryInfoIndexCur = 0;
#endif

YWOS_ThreadTable_T       astThreadTable[YWOS_THREAD_MAX];
YWOS_MessageTable_T      astMsgTable[YWOS_MESSAGE_MAX];
YWOS_SemaphoreTable_T    astSemTable[YWOS_SEMAPHORE_MAX];
YWOS_MutexTable_T        astMutTable[YWOS_MUTEX_MAX];

static BOOL     bYWOS_Init = FALSE;

#if (YWOS_TRACE_TO_LOG == YWOS_YES)
static S8 LogFd[LOG_FILE_NUM];
static S8 LogFdCur = -1;
static U32 LogPos;
static U32 LogIndex;
#endif

/************************************全局函数*********************************************/

#define   KERNEL_PART


POSIX_Clock_t  POSIX_TimeNow (void)
{
    struct timeval   tv;
    POSIX_Clock_t          Clk = 1;	    /* Default value */
    int              USecPerClk;    /* Micro seconds per clock (typically 64) */

    USecPerClk = 1000000/POSIX_GetClocksPerSecond();

    if (gettimeofday(&tv, NULL) == 0)
    {
        Clk =  (POSIX_Clock_t)tv.tv_sec*POSIX_GetClocksPerSecond()
             + (POSIX_Clock_t)tv.tv_usec/USecPerClk;
    }
    else
    {
        printf( "%s() Failed: gettimeofday failed !!!!\n", __FUNCTION__);
    }

    return (Clk);
}

/*
 * time_after
 */
int POSIX_TimeAfter (POSIX_Clock_t Time1, POSIX_Clock_t Time2)
{
    return ((Time1 > Time2) ? 1 : 0);
}

/*
 * time_minus
 */
POSIX_Clock_t POSIX_TimeMinus (POSIX_Clock_t Time1, POSIX_Clock_t Time2)
{
    return (POSIX_Clock_t)(Time1 - Time2);
}

/*
 * time_plus
 */
POSIX_Clock_t POSIX_TimePlus (POSIX_Clock_t Time1, POSIX_Clock_t Time2)
{
    return (POSIX_Clock_t)(Time1 + Time2); /* roundup needed ? */
}

struct timeval POSIX_Clockt2Timeval(POSIX_Clock_t clock)
{
    struct timeval	tval;
    int	USecPerClk;    /* Micro seconds per clock */

    USecPerClk = 1000000/POSIX_GetClocksPerSecond();

    tval.tv_sec  = (unsigned long)(clock / POSIX_GetClocksPerSecond());
    tval.tv_usec = (unsigned long)(clock % POSIX_GetClocksPerSecond() * USecPerClk);

    return(tval);
}


pthread_mutex_t * mutex_create_fifo(void)
{
    pthread_mutexattr_t     MutAttr;
    int                     ret;
    pthread_mutex_t *mutex = NULL;
    mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutexattr_init(&MutAttr);
    ret = pthread_mutexattr_settype(&MutAttr, PTHREAD_MUTEX_RECURSIVE_NP);
    if (ret == 0)
    {
        ret = pthread_mutex_init(mutex, &MutAttr);
        pthread_mutexattr_destroy(&MutAttr);
        if (ret != 0)
        {
            printf("pthread_mutex_init failed\n\n");
            pthread_mutex_destroy(mutex);
        }
    }
    else
    {
        free(mutex);
        mutex = NULL;
        printf("pthread_mutexattr_init failed\n");
    }
    return mutex;
}

int mutex_lockit(pthread_mutex_t * mutex)
{
    return(pthread_mutex_lock(mutex) == 0 ? 0 : -1);
}

int mutex_delete(pthread_mutex_t * mutex)
{
    int ret;
    while((ret=pthread_mutex_trylock(mutex)) != 0)
    {
        if (pthread_mutex_unlock(mutex) != 0)
        {
            printf("%s(): Unable to unlock a mutex (loop) !\n", __FUNCTION__);
        }
    }

    if (pthread_mutex_unlock(mutex) != 0)
    {
        printf( "%s(): Unable to unlock a mutex !\n", __FUNCTION__);
    }

    ret = pthread_mutex_destroy(mutex);

    if (ret != 0)
    {
        printf( "%s(): Unable to delete a mutex !\n", __FUNCTION__);
    }

    free(mutex);

    return(0);
}

int mutex_release(pthread_mutex_t *mutex)
{
    int ret;
    ret = pthread_mutex_unlock(mutex);
    sched_yield();

    return(ret == 0 ? 0 : -1);
}
/*
sem_t * semaphore_create_fifo_timeout(int count)
{
    sem_t     * sem_p = NULL;
    sem_p = malloc(sizeof(sem_t));

    if (sem_p != NULL)
    {
        int ret = 0;
        ret = sem_init(sem_p, 0, count);
        if (ret != 0)
        {
            printf( "%s(): Unable to create a semaphore, sem_init(count=%d) returns 0x%08x\n",__FUNCTION__, count, ret);
            free(sem_p);
            sem_p = NULL;
        }
    }
    return sem_p;
}


int semaphore_delete (sem_t *sem)
{
    int ret;
    ret = sem_destroy(sem);
    free(sem);
    return 0;
}
int semaphore_wait(sem_t *sem)
{
    int ret;
    do
    {
        ret = sem_wait(sem);
    } while((ret == -1) && (errno == EINTR));

    return(ret==0 ? 0 : -1);
}
int semaphore_wait_timeout(sem_t *sem, POSIX_Clock_t* timeout_p)
{

    int             ret = -1;
    struct timespec abstime;
    struct timeval  tval_timeout;

    if (timeout_p == (POSIX_Clock_t *)TIMEOUT_IMMEDIATE)
    {
        do
        {
            ret = sem_trywait(sem);
        } while((ret == -1) && (errno == EINTR));
        goto end;
    }

    if (timeout_p == (POSIX_Clock_t *)TIMEOUT_INFINITY)
    {
        do
        {
           ret = sem_wait(sem);
        } while((ret == -1) && (errno == EINTR));
        goto end;
    }


    tval_timeout = POSIX_Clockt2Timeval(*timeout_p);
    if ((tval_timeout.tv_sec == 0) && (tval_timeout.tv_usec == 0))
    {
        do
        {
            ret = sem_trywait(sem);
        } while((ret == -1) && (errno == EINTR));
        goto end;
    }
    abstime.tv_sec  = tval_timeout.tv_sec;
    abstime.tv_nsec = ((long)tval_timeout.tv_usec*1000);


    do
    {
        ret = sem_timedwait(sem, &abstime);
    } while((ret == -1) && (errno == EINTR));


end:

    if (   (ret != 0)
        && (errno != ETIMEDOUT)
        && (errno != EBUSY))
    {
       printf("%s() pb:%d !!!!\n", __FUNCTION__, ret);    }

    return((ret==0) ? 0 : -1);
}

int semaphore_signal(sem_t *sem)
{
    sem_post(sem);
}
*/

/***********************************************************************
    函数说明:    操作系统的初始化
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2008.04.03         詹翰明       新建
************************************************************************/

YW_ErrorType_T YWOS_Init(void)
{

    YW_ErrorType_T     Result = YW_NO_ERROR;
    int                iPartitionIndex;
    int                iTaskIndex;
    int                iMsgIndex;
    int                iSemIndex;
#if(YWOS_MEMORY_INFO_CHECK  == YWOS_YES)
    int                iMemInfoIndex;
#endif
#if (YWOS_TRACE_TO_LOG == YWOS_YES)
	int FileIndex;
	BOOL FdFindFlag = FALSE;
	S32 SeekRet;
#endif
    if(!bYWOS_Init)
    {
        for( iTaskIndex = 0; iTaskIndex < YWOS_THREAD_MAX; iTaskIndex ++ )
        {
            astThreadTable[iTaskIndex].Used = YWOS_NO;
            astThreadTable[iTaskIndex].IsCancel = TRUE;
        }

        for( iSemIndex = 0; iSemIndex < YWOS_SEMAPHORE_MAX; iSemIndex ++ )
        {
            astSemTable[iSemIndex].Used = YWOS_NO;
        }

        for( iMsgIndex = 0; iMsgIndex < YWOS_MESSAGE_MAX; iMsgIndex ++ )
        {
            astMsgTable[iMsgIndex].Used = YWOS_NO;
        }

        for( iSemIndex = 0; iSemIndex < YWOS_MUTEX_MAX; iSemIndex ++ )
        {
            astMutTable[iSemIndex].Used = YWOS_NO;
        }

#if(YWOS_MEMORY_INFO_CHECK  == YWOS_YES)
        for( iMemInfoIndex = 0; iMemInfoIndex < YWOS_MEMORY_INFO_MAX; iMemInfoIndex ++ )
        {
            MemoryInfo[iMemInfoIndex].Used     = YWOS_NO;
            MemoryInfo[iMemInfoIndex].AddrBase = NULL;
            MemoryInfo[iMemInfoIndex].AddrPtr  = NULL;
            MemoryInfo[iMemInfoIndex].AddrEnd  = NULL;
        }
 #endif
        Mutex_Thread = mutex_create_fifo();
	if( Mutex_Thread == NULL )
	{
            Result = YWOS_ERROR;
	}

	Mutex_Msg = mutex_create_fifo();
	if( Mutex_Msg == NULL )
	{
		Result = YWOS_ERROR;
	}

	Mutex_Sem = mutex_create_fifo();
	if( Mutex_Sem == NULL )
	{
		Result = YWOS_ERROR;
	}

	Mutex_MUTEX= mutex_create_fifo();
	if( Mutex_MUTEX == NULL )
	{
		Result = YWOS_ERROR;
	}

        Result = YW_NO_ERROR;
        bYWOS_Init = 1;

#if (YWOS_TRACE_TO_LOG == YWOS_YES)
		for (FileIndex = 0; FileIndex < LOG_FILE_NUM; ++FileIndex)
		{
			LogFd[FileIndex] = open((const char*)LogFileName[FileIndex],
							O_RDWR|O_SYNC|O_CREAT,
							S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
			/* if (-1 == LogFd[FileIndex]) just ignore */
			if (-1 != LogFd[FileIndex])
			{
				SeekRet = lseek(LogFd[FileIndex], 0, SEEK_END);
				if (SeekRet > YWOS_LOG_MAX_SIZE)
				{
					ftruncate(LogFd[FileIndex], YWOS_LOG_MAX_SIZE);
					lseek(LogFd[FileIndex], 0, SEEK_SET);
				}
				/* find latest been modified log which size less than YWOS_LOG_MAX_SIZE */
				else if (!FdFindFlag)
				{
					if (SeekRet == YWOS_LOG_MAX_SIZE)
					{
						lseek(LogFd[FileIndex], 0, SEEK_SET);
					}
					else if (SeekRet >= 0 && SeekRet < YWOS_LOG_MAX_SIZE)
					{
						LogFdCur = LogFd[FileIndex];
						LogIndex = FileIndex;
						LogPos = SeekRet;
						FdFindFlag = TRUE;
					}
				}
			}
		}

		/* just find first valid fd */
		if (!FdFindFlag)
		{
			LogFdCur = -1;
			for (FileIndex = 0; FileIndex < LOG_FILE_NUM; ++FileIndex)
			{
				if (-1 != LogFd[FileIndex])
				{
					LogFdCur = LogFd[FileIndex];
					LogIndex = FileIndex;
					LogPos = 0;
					FdFindFlag = TRUE;
					break;
				}
			}
		}
#endif

#if(YWOS_MEMORY_INFO_CHECK  == YWOS_YES)
        Result = YWOS_MutexCreate(&MutexMemoryLock);
        if( Result != YW_NO_ERROR )
        {
            return Result;
        }
#endif
    }
    else
    {
        Result = YWOS_ERROR_ALREADY_INITIALIZED;
    }
    return Result;

}

/***********************************************************************
    函数说明:

    调用说明:

    修改记录:    日       期      作      者       修定
                ---------         ---------         -----
                2005.10.20         詹翰明       新建
************************************************************************/
YW_ErrorType_T YWOS_Term(void)
{
    YW_ErrorType_T   Result = YW_NO_ERROR;
#if (YWOS_TRACE_TO_LOG == YWOS_YES)
    int FileIndex;
#endif
#if(YWOS_MEMORY_INFO_CHECK  == YWOS_YES)
    YWOS_MutexDelete(MutexMemoryLock);
#endif
#if (YWOS_TRACE_TO_LOG == YWOS_YES)
	LogFdCur = -1;
	for (FileIndex = 0; FileIndex < LOG_FILE_NUM; ++FileIndex)
	{
		if (-1 != LogFd[FileIndex])
		{
			close(LogFd[FileIndex]);
		}
	}
#endif
    //d48zm modify for testtool exit failed bug
    mutex_delete(Mutex_MUTEX);
    Mutex_MUTEX = NULL;
    mutex_delete(Mutex_Sem);
    Mutex_Sem = NULL;
    mutex_delete(Mutex_Msg);
    Mutex_Msg = NULL;
    mutex_delete(Mutex_Thread);
    Mutex_Thread = NULL;
#if 0
    mutex_delete(Mutex_Partition);
    Mutex_Partition = NULL;
#endif
    //modify end

    bYWOS_Init = 0;
    return Result;
}

#define    MEORY_PART
/***********************************************************************
    函数说明:    分配一部分内存

    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/
#if(YWOS_MEMORY_INFO_CHECK  == YWOS_YES)
BOOL  YWOSi_GetMemoryInfoIndex( U32 *MemoryInfoIndex)
{
    U32 iMemInfoIndex;
    BOOL IsExistNull = FALSE;
    *MemoryInfoIndex = YWOS_MEMORY_INFO_MAX;
    YWOS_MutexWait(MutexMemoryLock, YWOS_WAIT_INFINITY);
    for( iMemInfoIndex = MemoryInfoIndexCur ; iMemInfoIndex < YWOS_MEMORY_INFO_MAX ; iMemInfoIndex ++ )
    {

        if( MemoryInfo[iMemInfoIndex].Used == YWOS_NO )
        {
            MemoryInfo[iMemInfoIndex].Used = YWOS_YES;
            *MemoryInfoIndex =  iMemInfoIndex;
            /*
            MemoryInfoIndexCur = iMemInfoIndex;
            if(iMemInfoIndex >= (YWOS_MEMORY_INFO_MAX -1))
            {
                MemoryInfoIndexCur = 0;
            }
             */
            IsExistNull = TRUE;
            break;
        }

    }
    if(!IsExistNull)
    {
        for( iMemInfoIndex = 0 ; iMemInfoIndex < MemoryInfoIndexCur ; iMemInfoIndex ++ )
        {

            if( MemoryInfo[iMemInfoIndex].Used == YWOS_NO )
            {
                MemoryInfo[iMemInfoIndex].Used = YWOS_YES;
                *MemoryInfoIndex =  iMemInfoIndex;
                /*
                MemoryInfoIndexCur = iMemInfoIndex;
                if(iMemInfoIndex >= (YWOS_MEMORY_INFO_MAX -1))
                {
                    MemoryInfoIndexCur = 0;
                }
*/
                IsExistNull = TRUE;
                break;
            }
        }
    }

    YWOS_MutexSend(MutexMemoryLock);

    return  IsExistNull;

}
#endif
/***********************************************************************
    函数说明:    分配一部分内存

    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/
void*  YWOS_MallocCheck( U32 Size ,S8* FileName, U32 Line)
{
#if 1
    void *NewBlock;

    U32 NewSize;
    NewSize = Size;
    if(bYWOS_Init)
    {

#if(YWOS_MEMORY_INFO_CHECK  == YWOS_YES)
        U32 iMemInfoIndex;
        BOOL IsGetMemInfo = FALSE;
        IsGetMemInfo = YWOSi_GetMemoryInfoIndex(&iMemInfoIndex);
        NewSize = (NewSize + 3)/ 4 *4   + 8;
        if( IsGetMemInfo )
        {

#endif
#if (  YWOS_STLINUX == YWOS_YES )
            NewBlock = (U8 *)malloc( NewSize );

#endif
#if(YWOS_MEMORY_INFO_CHECK  == YWOS_YES)
            if(NewBlock != NULL)
            {

                if(iMemInfoIndex >= (YWOS_MEMORY_INFO_MAX -1))
                {
                    MemoryInfoIndexCur = 0;
                }
                else
                {
                    MemoryInfoIndexCur = iMemInfoIndex;
                }
                MemoryInfo[iMemInfoIndex].AddrBase  = NewBlock;
                MemoryInfo[iMemInfoIndex].AddrPtr   = (void *)((U32)NewBlock + 4);
                MemoryInfo[iMemInfoIndex].AddrEnd   = (void *)((U32)NewBlock + NewSize - 4);
                MemoryInfo[iMemInfoIndex].FileName  = FileName;
                MemoryInfo[iMemInfoIndex].Line      = Line;
                *((U32 *)MemoryInfo[iMemInfoIndex].AddrBase) = (U32)&MemoryInfo[iMemInfoIndex];
                *((U32 *)MemoryInfo[iMemInfoIndex].AddrEnd)  = NewSize;
                NewBlock = MemoryInfo[iMemInfoIndex].AddrPtr;
            }
        }
        else
        {
            MemoryInfo[iMemInfoIndex].Used = YWOS_NO;
            NewBlock = NULL;
        }
#endif
    }
    else
    {
        NewBlock = NULL;
    }

    return  NewBlock;
#else
    return YWOS_MallocNcache( Size) ;
#endif
}

/***********************************************************************
    函数说明:    分配num * Size内存

    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/
void* YWOS_CallocCheck( U32 num,U32 Size,S8* FileName, U32 Line)
{
#if 1
    void *NewBlock;

    U32 NewSize;
    NewSize = Size * num;
    if(bYWOS_Init)
    {

#if(YWOS_MEMORY_INFO_CHECK  == YWOS_YES)
        U32 iMemInfoIndex;
        BOOL IsGetMemInfo = FALSE;
        IsGetMemInfo = YWOSi_GetMemoryInfoIndex(&iMemInfoIndex);
        NewSize = (NewSize + 3)/ 4 *4   + 8;
        if( IsGetMemInfo )
        {

#endif
#if (  YWOS_STLINUX == YWOS_YES )

            NewBlock = (U8 *)malloc( NewSize );
            if(NULL==NewBlock)
            {
                return NULL;
            }
            memset(NewBlock, 0, NewSize);

#endif
#if(YWOS_MEMORY_INFO_CHECK  == YWOS_YES)
            if(NewBlock != NULL)
            {
                if(iMemInfoIndex >= (YWOS_MEMORY_INFO_MAX -1))
                {
                    MemoryInfoIndexCur = 0;
                }
                else
                {
                    MemoryInfoIndexCur = iMemInfoIndex;
                }
                MemoryInfo[iMemInfoIndex].AddrBase  = NewBlock;
                MemoryInfo[iMemInfoIndex].AddrPtr   = (void *)((U32)NewBlock + 4);
                MemoryInfo[iMemInfoIndex].AddrEnd   = (void *)((U32)NewBlock + NewSize - 4);
                MemoryInfo[iMemInfoIndex].FileName  = FileName;
                MemoryInfo[iMemInfoIndex].Line      = Line;
                *(U32 *)MemoryInfo[iMemInfoIndex].AddrBase = (U32)&MemoryInfo[iMemInfoIndex];
                *(U32 *)MemoryInfo[iMemInfoIndex].AddrEnd  = NewSize;
                NewBlock = MemoryInfo[iMemInfoIndex].AddrPtr;
            }
        }
        else
        {
            MemoryInfo[iMemInfoIndex].Used = YWOS_NO;
            NewBlock = NULL;
        }
#endif
    }
    else
    {
        NewBlock = NULL;
    }

    return  NewBlock;
#else
    return YWOS_CallocNcache(num,Size);
#endif
}
/***********************************************************************
    函数说明:    分配num * Size内存

    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/
void* YWOS_CallocNcacheCheck( U32 num,U32 Size,S8* FileName, U32 Line)
{
    return YWOS_CallocCheck( num, Size, FileName, Line);
}
/***********************************************************************
    函数说明:    分配一部分内存

    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/
void*  YWOS_MallocNcacheCheck( U32 Size,S8* FileName, U32 Line)
{
    return YWOS_MallocCheck(Size , FileName, Line);
}

/***********************************************************************
    函数说明:    释放一部分内存

    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/
YW_ErrorType_T YWOS_FreeNcache( void *Block)
{
    return YWOS_Free(Block);
}

/***********************************************************************
    函数说明:    释放一部分内存

    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/
YW_ErrorType_T YWOS_Free( void *Block)
{
#if 1
    YW_ErrorType_T       Result = YW_NO_ERROR;
    if(NULL == Block)
    {
        return YWHAL_ERROR_BAD_PARAMETER;
    }

    if(bYWOS_Init)
    {
#if(YWOS_MEMORY_INFO_CHECK  == YWOS_YES)
//        U32 iMemInfoIndex;
        YWOS_MemoryInfo_T *iMemoryInfo;
        void * NewBlock;
        U32 BaseMemAddr, EndSize;
        YWOS_MutexWait(MutexMemoryLock, YWOS_WAIT_INFINITY);
        NewBlock =(void*)((U32)Block - 4);
        iMemoryInfo = (YWOS_MemoryInfo_T *)(*((U32*)NewBlock));
        if(! YW_HandleValid(MemoryInfo, YWOS_MEMORY_INFO_MAX, *((U32*)NewBlock)) )
        {
            YWOS_MutexSend(MutexMemoryLock);
            return YWHAL_ERROR_UNKNOWN_DEVICE;
        }
        BaseMemAddr = *(U32 *)iMemoryInfo->AddrBase;
        EndSize = *(U32 *)iMemoryInfo->AddrEnd;
        if( BaseMemAddr != (U32)iMemoryInfo)
        {
            YWOS_Trace(YWOS_TRACE_ERROR,
                "\n[error][YWOS_Free]-------------- Start is Overflow---------------\n");
            YWOS_MutexSend(MutexMemoryLock);
            return YWHAL_ERROR_UNKNOWN_DEVICE;
        }
        else if(( (U32)iMemoryInfo->AddrBase + EndSize - 4)
            != ((U32)iMemoryInfo->AddrEnd))
        {
            YWOS_Trace(YWOS_TRACE_ERROR,
                "\n[error][YWOS_Free]-------------- End is Overflow---------------\n");
            YWOS_MutexSend(MutexMemoryLock);
            return YWHAL_ERROR_UNKNOWN_DEVICE;
        }
        if( iMemoryInfo->Used == YWOS_YES
            && iMemoryInfo->AddrBase != NULL
            && iMemoryInfo->AddrEnd != NULL
            && iMemoryInfo->AddrPtr != NULL
            && iMemoryInfo->AddrPtr == Block)
        {

          Block = iMemoryInfo->AddrBase;
#endif
#if (  YWOS_STLINUX == YWOS_YES )

            free( Block );

#endif
#if(YWOS_MEMORY_INFO_CHECK  == YWOS_YES)
            YWOS_MutexSend(MutexMemoryLock);
            iMemoryInfo->Used       = YWOS_NO;
            iMemoryInfo->AddrBase   = NULL;
            iMemoryInfo->AddrPtr    = NULL;
            iMemoryInfo->AddrEnd    = NULL;
            iMemoryInfo->FileName   = NULL;
            iMemoryInfo->Line       = 0;

        }
        else
        {
            Result = YWOS_ERROR_INVALID_INSTANCE;
            YWOS_Trace(YWOS_TRACE_ERROR,
                "{-------Error-----}[YWOS_Free]---- MemoryInfo [0x%x]---\n", Result);

        }
        YWOS_MutexSend(MutexMemoryLock);
#endif
    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }
    return  Result;
#else
    return YWOS_FreeNcache(Block) ;
#endif
}

#define   TASK_PART

/***********************************************************************
    函数说明:    生成一个进程，包含两种方式task_create,
                    task_init.
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2008.04.03         詹翰明       新建
************************************************************************/

YW_ErrorType_T YWOS_ThreadCreate(   S8* Name,  void(*Function)(void *Param), void* Param, void* Stack, U32 StackSize, U32 Priority, BOOL Start, YWOS_ThreadID_T * ThreadID )
{

    YW_ErrorType_T       Result = YW_NO_ERROR;
    int    iTaskIndex;
    YWOS_ThreadTable_T    *Thread;
	U32	PriorityTemp;
    if(NULL == Function || NULL == ThreadID )
    {
        return YWHAL_ERROR_BAD_PARAMETER;
    }
    if(bYWOS_Init)
    {
        mutex_lockit(Mutex_Thread);
        * ThreadID = 0;
        for( iTaskIndex = 0 ; iTaskIndex < YWOS_THREAD_MAX ; iTaskIndex ++ )
        {
            if( astThreadTable[iTaskIndex].Used == YWOS_NO )
            {
                Thread = &astThreadTable[iTaskIndex];
                astThreadTable[iTaskIndex].IsCancel = FALSE;
                break;
            }
        }
        if( iTaskIndex < YWOS_THREAD_MAX )
        {
#if (  YWOS_STLINUX == YWOS_YES )
 #if 1
            //U8 IsSuspended = task_flags_no_min_stack_size;
            PriorityTemp = Priority;
    		if(StackSize<16*YW_K)
    		{
    			StackSize = 16*YW_K + StackSize;
    		}
    		Priority = ((MAX_USER_PRIORITY-YWOS_THREAD_PRIORITY_STUB) + Priority);
            if( !Start )
            {
                //IsSuspended = task_flags_suspended;
            }
            Task_Create(Function,
                Param,
                StackSize,
                Priority,
                (char *)Name,
                0,
                Thread->ThreadT);
    		if( Thread->ThreadT ==(Task_t)NULL )
    		{
    			Result = YWOS_ERROR ;
    		}
    		else
    		{
                Thread->Used = YWOS_YES;
                Thread->IsCancel = FALSE;
                /*
                if( !Start )
                {
                    task_suspend( Thread->ThreadT );
                }
                */		if(PriorityTemp > 2)
                Task_Priority_Set(Thread->ThreadT,Priority)
                *ThreadID = (U32)Thread;
    		}

  #else
   {
		int 	nRetVal;
		int	nNewPrio;
		struct sched_param 	param;
		pthread_attr_t  attr;
		Priority = ((MAX_USER_PRIORITY-15) + Priority);
		Result = pthread_attr_init(&attr);
		if(StackSize<0x4000)
		{
			StackSize = 0x4000;
		}
		Result = pthread_attr_setstacksize(&attr,StackSize);

		Result = pthread_create (&Thread->ThreadT, &attr, Function, Param);

		Result = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);

	    	if ( Thread->ThreadT != 0)
	    	{
                Thread->Used = YWOS_YES;
                printf("YWOS_ThreadCreate ThreadT = 0x%x",Thread->ThreadT);
	    		int nPolicy = SCHED_RR;
	    		param.sched_priority = Priority;

    			Result = pthread_setschedparam (Thread->ThreadT, nPolicy, &param);
	    	}
	}
  #endif


#endif
        }
        else
        {
            Result = YWOS_ERROR_NO_FREE_INSTANCE ;
        }
        mutex_release(Mutex_Thread);
    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }

    return  Result;
}



/***********************************************************************
    函数说明:    删除一个进程
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2008.04.03         詹翰明       新建
************************************************************************/

YW_ErrorType_T YWOS_ThreadDelete( YWOS_ThreadID_T  ThreadID)
{

    YW_ErrorType_T       Result = YW_NO_ERROR;
    YWOS_ThreadTable_T    *Thread = (YWOS_ThreadTable_T    *)ThreadID;

    if(bYWOS_Init)
    {
        if(YW_HandleValid(astThreadTable, YWOS_THREAD_MAX, ThreadID))
        {
#if (  YWOS_STLINUX == YWOS_YES )

        	int    iTemp;

        	if( Thread->Used == YWOS_YES )
        	{
                    //        		iTemp = Task_Delete(Thread->ThreadT);
                    Thread->IsCancel = TRUE;
                    iTemp = Task_Wait( Thread->ThreadT);

                    if( iTemp == YWOS_NO )
                    {
                        Thread->Used = YWOS_NO;
                    }
                    else
                    {
                        printf("************YWOS_ThreadDelete failed*******\n");
                    }
        	}
        	else
        	{
        		Result = YWOS_ERROR_INVALID_INSTANCE;
        	}
#endif
        }
        else
        {
            Result = YWOS_ERROR_INVALID_INSTANCE;
        }
    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }
    return  Result;
}


 /***********************************************************************
    函数说明:    设置线程的优先级
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2008.04.03         詹翰明       新建
************************************************************************/
YW_ErrorType_T YWOS_ThreadPriority(  YWOS_ThreadID_T  ThreadID , U32 Priority)
{


    YW_ErrorType_T       Result = YW_NO_ERROR;
    YWOS_ThreadTable_T    *Thread = (YWOS_ThreadTable_T    *)ThreadID;

    if(bYWOS_Init)
    {
        if(YW_HandleValid(astThreadTable, YWOS_THREAD_MAX, ThreadID))
        {
            if( Thread->Used == YWOS_YES )
            {
#if (  YWOS_STLINUX == YWOS_YES )


                int    iTemp = 0;
               Priority = ((MAX_USER_PRIORITY-YWOS_THREAD_PRIORITY_STUB) + Priority);
                Task_Priority_Set(Thread->ThreadT,  Priority);

                if( iTemp == 0 )
                {
                    Result = YW_NO_ERROR;
                }
                else
                {
                    Result = YWOS_ERROR_INVALID_INSTANCE;
                }
#endif
            }

            else
            {
                Result = YWOS_ERROR_INVALID_INSTANCE;
            }

        }

#if (  YWOS_STLINUX == YWOS_YES )
        else if ((ThreadID == 0))
        {
                int    iTemp = 0;
                Priority = ((MAX_USER_PRIORITY-YWOS_THREAD_PRIORITY_STUB) + Priority);
                Task_Priority_Set(Task_Id() ,  Priority);

                if( iTemp == 0 )
                {
                    Result = YW_NO_ERROR;
                }
                else
                {
                    Result = YWOS_ERROR_INVALID_INSTANCE;
                }
        }

#endif


        else
        {
            Result = YWOS_ERROR_INVALID_INSTANCE;
        }
    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }

    return  Result;
}
 /***********************************************************************
    函数说明:   获取线程的优先级
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2008.04.03         詹翰明       新建
************************************************************************/
YW_ErrorType_T YWOS_ThreadGetPriority(  YWOS_ThreadID_T  ThreadID , U32* Priority)
{


    YW_ErrorType_T       Result = YW_NO_ERROR;
    YWOS_ThreadTable_T    *Thread = (YWOS_ThreadTable_T    *)ThreadID;

    if(bYWOS_Init)
    {
        if(YW_HandleValid(astThreadTable, YWOS_THREAD_MAX, ThreadID))
        {
            if( Thread->Used == YWOS_YES )
            {
#if (  YWOS_STLINUX == YWOS_YES )

 //               *Priority = Task_Priority(Thread->ThreadT);
                int nPolicy;
                struct sched_param 	param;
        		if (pthread_getschedparam(Thread->ThreadT, &nPolicy, &param) == 0)
    	        {
    			    *Priority = (U32)param.sched_priority;
                   *Priority =  *Priority-(MAX_USER_PRIORITY-YWOS_THREAD_PRIORITY_STUB) ;
                    Result = YW_NO_ERROR;
    	        }
                else
                {
                    Result = YWOS_ERROR_INVALID_INSTANCE;
                }
#endif
            }

            else
            {
                Result = YWOS_ERROR_INVALID_INSTANCE;
            }

        }

#if (  YWOS_STLINUX == YWOS_YES )

         else if ((ThreadID == 0))
        {
                int nPolicy;
                struct sched_param 	param;
        		if (pthread_getschedparam(Task_Id(), &nPolicy, &param) == 0)
    	        {
    			    *Priority = (U32)param.sched_priority;
                    *Priority =  *Priority-(MAX_USER_PRIORITY-YWOS_THREAD_PRIORITY_STUB) ;
                    Result = YW_NO_ERROR;
    	        }
                else
                {
                    Result = YWOS_ERROR_INVALID_INSTANCE;
                }

        }

#endif


        else
        {
            Result = YWOS_ERROR_INVALID_INSTANCE;
        }
    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }

    return  Result;
}
 /***********************************************************************
    函数说明:   获取线程的退出状态
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2008.04.03         詹翰明       新建
************************************************************************/
BOOL YWOS_ThreadIsCancel(YWOS_ThreadID_T  ThreadID)
{
    BOOL IsCancel = FALSE;
    YWOS_ThreadTable_T    *Thread = (YWOS_ThreadTable_T    *)ThreadID;

    if(bYWOS_Init)
    {
        mutex_lockit(Mutex_Thread);
        if(YW_HandleValid(astThreadTable, YWOS_THREAD_MAX, ThreadID))
        {

#if (  YWOS_STLINUX == YWOS_YES )

                IsCancel = Thread->IsCancel;
#endif

        }
        mutex_release(Mutex_Thread);
    }

    return  IsCancel;
}
 /***********************************************************************
    函数说明:    启动一个进程
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2008.04.03         詹翰明       新建
************************************************************************/

YW_ErrorType_T YWOS_ThreadStart(  YWOS_ThreadID_T  ThreadID )
{


    YW_ErrorType_T       Result = YW_NO_ERROR;
    YWOS_ThreadTable_T    *Thread = (YWOS_ThreadTable_T    *)ThreadID;

    if(bYWOS_Init)
    {
        if(YW_HandleValid(astThreadTable, YWOS_THREAD_MAX, ThreadID))
        {
            if( Thread->Used == YWOS_YES )
            {
#if (  YWOS_STLINUX == YWOS_YES )
                int    iTemp;
                iTemp = pthread_kill(Thread->ThreadT, SIGCONT);
                if( iTemp == YWOS_NO )
                {
                    Result = YW_NO_ERROR;
                }
                else
                {
                    Result = YWOS_ERROR_INVALID_INSTANCE;
                }
#endif
            }
            else
            {
                Result = YWOS_ERROR_INVALID_INSTANCE;
            }

        }
        else
        {
            Result = YWOS_ERROR_INVALID_INSTANCE;
        }
    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }

    return  Result;
}


 /***********************************************************************
    函数说明:    停止一个进程
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2008.04.03         詹翰明       新建
************************************************************************/

YW_ErrorType_T YWOS_ThreadStop( YWOS_ThreadID_T  ThreadID  )
{


    YW_ErrorType_T       Result = YW_NO_ERROR;
    YWOS_ThreadTable_T    *Thread = (YWOS_ThreadTable_T    *)ThreadID;

    if(bYWOS_Init)
    {
        if(YW_HandleValid(astThreadTable, YWOS_THREAD_MAX, ThreadID))
        {
            if( Thread->Used == YWOS_YES )
            {
#if (  YWOS_STLINUX == YWOS_YES )
                int    iTemp;
                iTemp = pthread_kill(Thread->ThreadT,SIGSTOP);
                if( iTemp == YWOS_NO )
                {
                    Result = YW_NO_ERROR;
                }
                else
                {
                    Result = YWOS_ERROR;
                }

#endif
            }
            else
            {
                Result = YWOS_ERROR_INVALID_INSTANCE;
            }
        }
        else
        {
            Result = YWOS_ERROR_INVALID_INSTANCE;
        }
    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }

    return  Result;

}

 /***********************************************************************
    函数说明:    获取当前task id
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2008.04.03         詹翰明       新建
************************************************************************/

YW_ErrorType_T YWOS_ThreadId( YWOS_ThreadID_T  *ThreadID  )
{


   YW_ErrorType_T       Result = YW_NO_ERROR;
    int    iTaskIndex;
//    YWOS_ThreadTable_T    *Thread;
    if(NULL == ThreadID )
    {
        return YWHAL_ERROR_BAD_PARAMETER;
    }

    * ThreadID = 0;

    if(bYWOS_Init)
    {


#if (  YWOS_STLINUX == YWOS_YES )
        mutex_lockit(Mutex_Thread);
        pthread_t TaskId = Task_Id();
        //printf("YWOS_ThreadId TaskId = 0x%x",TaskId);
        for( iTaskIndex = 0 ; iTaskIndex < YWOS_THREAD_MAX ; iTaskIndex ++ )
        {
            if( astThreadTable[iTaskIndex].Used == YWOS_YES )
            {
                if(TaskId == astThreadTable[iTaskIndex].ThreadT)
                {
                    *ThreadID =(YWOS_ThreadID_T) &astThreadTable[iTaskIndex];
                    break;
                }
            }
        }

        mutex_release(Mutex_Thread);
#endif



    }
    return  Result;
}

#define   MESSAGE_PART


 /***********************************************************************
    函数说明:    生成一个消息队列
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/

YW_ErrorType_T YWOS_MessageQueueCreate( S8* Name, U32 ElementSize, U32 ElementNo, YWOS_MessageID_T * MessageID)
{


    YW_ErrorType_T       Result = YW_NO_ERROR;
    YWOS_MessageTable_T    *Message;
    int    iMsgIndex;
    if(NULL == MessageID )
    {
        return YWHAL_ERROR_BAD_PARAMETER;
    }
    if(bYWOS_Init)
    {
        mutex_lockit(Mutex_Msg);
        * MessageID = 0;
        for( iMsgIndex = 0; iMsgIndex < YWOS_MESSAGE_MAX; iMsgIndex ++ )
        {
            if( astMsgTable[iMsgIndex].Used == YWOS_NO )
            {
                Message = &astMsgTable[iMsgIndex];
                Message->Used = YWOS_YES;
                break;
            }
        }
        mutex_release(Mutex_Msg);
        if( iMsgIndex < YWOS_MESSAGE_MAX )
        {
#if (  YWOS_STLINUX == YWOS_YES )

		message_queue_t  *     MsgTempT;

		MsgTempT = message_create_queue_timeout( ElementSize, ElementNo );

		if( MsgTempT == NULL )
		{
            Message->Used = YWOS_NO;
			Result = YWOS_ERROR;
		}
		else
		{
            Message->MsgT = MsgTempT;
            Message->MsgElementSize = ElementSize;
            Message->MsgElementNo = ElementNo;

            *MessageID = (U32)Message;
            Result = YW_NO_ERROR ;
		}
#endif

        }
        else
        {
            Result = YWOS_ERROR_NO_FREE_INSTANCE ;
        }

    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }

    return  Result;
}


 /***********************************************************************
    函数说明:    删除一个消息队列
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/

YW_ErrorType_T YWOS_MessageQueueDelete( YWOS_MessageID_T MessageID  )
{

    YW_ErrorType_T       Result = YW_NO_ERROR;
    YWOS_MessageTable_T    *Message = (YWOS_MessageTable_T    *)MessageID;

    if(bYWOS_Init)
    {
        if(YW_HandleValid(astMsgTable, YWOS_MESSAGE_MAX, MessageID))
        {
            if( Message->Used == YWOS_YES )
            {
#if (  YWOS_STLINUX == YWOS_YES )


                message_delete_queue(  Message->MsgT );
                Message->Used = YWOS_NO ;
                Result = YW_NO_ERROR;

#elif  (  YWOS_NECITRON == YWOS_YES )

#elif  (  YWOS_ALI3329 == YWOS_YES )

#endif
            }
            else
            {

                Result = YWOS_ERROR_INVALID_INSTANCE;
            }
        }
        else
        {
            Result = YWOS_ERROR_INVALID_INSTANCE;
        }
    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }
    return  Result;
}



 /***********************************************************************
    函数说明:    向一个消息队列发送消息
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/

YW_ErrorType_T YWOS_MessageQueueSend( YWOS_MessageID_T MessageID , YWOS_ClockMsec_T TimeOut, void* MsgContent )
{

    YW_ErrorType_T       Result = YW_NO_ERROR;
    YWOS_MessageTable_T    *Message = (YWOS_MessageTable_T    *)MessageID;
    if(NULL == MsgContent )
    {
        return YWHAL_ERROR_BAD_PARAMETER;
    }
    if(bYWOS_Init)
    {
        if(YW_HandleValid(astMsgTable, YWOS_MESSAGE_MAX, MessageID))
        {

            if( Message->Used == YWOS_YES )
            {
#if (  YWOS_STLINUX == YWOS_YES )


                void*   msg_p;
                STOS_Clock_t time_wait;


		if( TimeOut ==  YWOS_WAIT_INFINITY )
		{
			if ( ( msg_p = message_claim_timeout (  Message->MsgT , TIMEOUT_INFINITY ) ) != NULL )
			{
				memcpy(  msg_p , MsgContent , Message->MsgElementSize );
				message_send ( Message->MsgT , msg_p );
				Result = YW_NO_ERROR;
			}
			else
			{
				Result = YWOS_ERROR_TIMEOUT;
			}

		}
		else if (  TimeOut ==  YWOS_WAIT_IMMEDIATE   )
		{
			if ( ( msg_p = message_claim_timeout (  Message->MsgT , TIMEOUT_IMMEDIATE ) ) != NULL )
			{
				memcpy(  msg_p , MsgContent , Message->MsgElementSize );
				message_send ( Message->MsgT , msg_p );
				Result = YW_NO_ERROR;
			}
			else
			{
				Result = YWOS_ERROR_TIMEOUT;
			}

		}
		else
		{
			time_wait = time_plus( time_now ( ), ST_GetClocksPerSecond()/1000*TimeOut);

			if ( ( msg_p = message_claim_timeout (  Message->MsgT  , &time_wait ) ) != NULL )
			{
				memcpy(  msg_p , MsgContent , Message->MsgElementSize );
				message_send ( Message->MsgT , msg_p );
				Result = YW_NO_ERROR;
			}
			else
			{
				Result = YWOS_ERROR_TIMEOUT;
			}
		}



#endif
            }
            else
            {
                Result = YWOS_ERROR_INVALID_INSTANCE;
            }
        }
        else
        {
            Result = YWOS_ERROR_INVALID_INSTANCE;
        }

    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }

    return  Result;
}


 /***********************************************************************
    函数说明:    从一个消息队列接收消息
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/

YW_ErrorType_T YWOS_MessageQueueReceive( YWOS_MessageID_T MessageID , YWOS_ClockMsec_T TimeOut, void* MsgContent )
{

    YW_ErrorType_T          Result  = YW_NO_ERROR;
    YWOS_MessageTable_T    *Message = (YWOS_MessageTable_T *)MessageID;

    if(NULL == MsgContent )
    {
        return YWHAL_ERROR_BAD_PARAMETER;
    }
    if(bYWOS_Init)
    {
        if(YW_HandleValid(astMsgTable, YWOS_MESSAGE_MAX, MessageID))
        {
            if( Message->Used == YWOS_YES )
            {
#if (  YWOS_STLINUX == YWOS_YES )


                void* MsgTemp ;
                STOS_Clock_t     			time_wait;

                if( TimeOut ==  YWOS_WAIT_INFINITY )
                {
                    if ( ( MsgTemp = message_receive_timeout (  Message->MsgT, TIMEOUT_INFINITY ) ) != NULL )
        			{
        				memcpy(  MsgContent, MsgTemp, Message->MsgElementSize );

        				message_release( Message->MsgT, MsgTemp);

        				Result = YW_NO_ERROR;
        			}
        			else
        			{
        				Result = YWOS_ERROR_TIMEOUT;
        			}

                 }
                 else if (  TimeOut ==  YWOS_WAIT_IMMEDIATE   )
                 {

        			if ( ( MsgTemp = message_receive_timeout (  Message->MsgT  , TIMEOUT_IMMEDIATE ) ) != NULL )
        			{
        				memcpy(  MsgContent, MsgTemp, Message->MsgElementSize );

        				message_release( Message->MsgT,  MsgTemp );

        				Result = YW_NO_ERROR;
        			}
        			else
        			{
        				Result = YWOS_ERROR_TIMEOUT;
        			}

                }
                else
                {
        			time_wait = time_plus( time_now ( ), ST_GetClocksPerSecond()/1000*TimeOut);

        			if ( ( MsgTemp = message_receive_timeout (  Message->MsgT, &time_wait ) ) != NULL )
        			{
        				memcpy(MsgContent, MsgTemp, Message->MsgElementSize);

        				message_release( Message->MsgT, MsgTemp );

        				Result = YW_NO_ERROR;
        			}
        			else
        			{
        				Result = YWOS_ERROR_TIMEOUT;
        			}

                }


#endif

            }
            else
            {
                Result = YWOS_ERROR_INVALID_INSTANCE;
            }
        }
        else
        {
            Result = YWOS_ERROR_INVALID_INSTANCE;
        }
    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }
    return  Result;
}



#define  SEMAPHORE_PART


 /***********************************************************************
    函数说明:    生成一个信号量
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/


YW_ErrorType_T YWOS_SemaphoreCreate( S8* Name, U32 Count,  YWOS_SemaphoreID_T* SemaphoreID )
{

    YW_ErrorType_T       Result = YW_NO_ERROR;
    YWOS_SemaphoreTable_T    *Semaphore;
    int        iSemIndex;
    if(NULL == SemaphoreID )
    {
        return YWHAL_ERROR_BAD_PARAMETER;
    }
    if(bYWOS_Init)
    {
        mutex_lockit(Mutex_Sem);
        * SemaphoreID = 0;
        for( iSemIndex = 0 ; iSemIndex < YWOS_SEMAPHORE_MAX ; iSemIndex ++ )
        {
            if( astSemTable[iSemIndex].Used == YWOS_NO )
            {
                Semaphore = &astSemTable[iSemIndex];
                Semaphore->Used = YWOS_YES;
                break;
            }
        }
        mutex_release(Mutex_Sem);
        if( iSemIndex < YWOS_SEMAPHORE_MAX )
        {

#if (YWOS_STLINUX == YWOS_YES)

            Semaphore->SemT = semaphore_create_fifo_timeout(Count);
            if(Semaphore->SemT != NULL)
            {
                *SemaphoreID = (U32)Semaphore;
                Result = YW_NO_ERROR ;
            }
            else
            {
                Semaphore->Used = YWOS_NO;
                Result = YWOS_ERROR_NO_FREE_INSTANCE ;
            }
#endif
        }
        else
        {
            Result = YWOS_ERROR_NO_FREE_INSTANCE ;
        }

    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }

    return  Result;
}


 /***********************************************************************
    函数说明:    删除一个信号量
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/


YW_ErrorType_T YWOS_SemaphoreDelete(  YWOS_SemaphoreID_T  SemaphoreID )
{

    YW_ErrorType_T       Result = YW_NO_ERROR;
    YWOS_SemaphoreTable_T    *Semaphore = (YWOS_SemaphoreTable_T    *)SemaphoreID;

    if(bYWOS_Init)
    {
        if(YW_HandleValid(astSemTable, YWOS_SEMAPHORE_MAX, SemaphoreID))
        {
            if( Semaphore->Used == YWOS_YES )
            {
#if (  YWOS_STLINUX == YWOS_YES )

                semaphore_delete ( Semaphore->SemT );

               Semaphore->Used = YWOS_NO;
                Result = YW_NO_ERROR ;

#endif
            }
            else
            {
                Result = YWOS_ERROR_INVALID_INSTANCE ;
            }
        }
        else
        {
            Result = YWOS_ERROR_INVALID_INSTANCE;
        }
    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }

    return  Result;
}



 /***********************************************************************
    函数说明:    发送一个信号量
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/


YW_ErrorType_T YWOS_SemaphoreSend(  YWOS_SemaphoreID_T  SemaphoreID )
{

    YW_ErrorType_T            Result = YW_NO_ERROR;
    YWOS_SemaphoreTable_T    *Semaphore = (YWOS_SemaphoreTable_T *)SemaphoreID;

    if(bYWOS_Init)
    {
        if(YW_HandleValid(astSemTable, YWOS_SEMAPHORE_MAX, SemaphoreID))
        {
            if( Semaphore->Used == YWOS_YES )
            {
#if (YWOS_STLINUX == YWOS_YES)
          semaphore_signal ( Semaphore->SemT );
		  Result = YW_NO_ERROR ;
#endif
            }
            else
            {
                Result = YWOS_ERROR_INVALID_INSTANCE ;
            }
        }
        else
        {
            Result = YWOS_ERROR_INVALID_INSTANCE;
        }
    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }

    return  Result;
}


 /***********************************************************************
    函数说明:    在要求的时间内接收一个信号量
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/


YW_ErrorType_T YWOS_SemaphoreWait( YWOS_SemaphoreID_T  SemaphoreID , YWOS_ClockMsec_T TimeOut )
{

    YW_ErrorType_T       Result = YW_NO_ERROR;
    YWOS_SemaphoreTable_T    *Semaphore = (YWOS_SemaphoreTable_T    *)SemaphoreID;

    if(bYWOS_Init)
    {
        if(YW_HandleValid(astSemTable, YWOS_SEMAPHORE_MAX, SemaphoreID))
        {
            if( Semaphore->Used == YWOS_YES )
            {
#if (  YWOS_STLINUX == YWOS_YES )

                POSIX_Clock_t     			time_wait;
                int					iRet;

                if( TimeOut == YWOS_WAIT_INFINITY )
                {
                    iRet = semaphore_wait_timeout ( Semaphore->SemT , TIMEOUT_INFINITY );
                }
                else if( TimeOut == YWOS_WAIT_IMMEDIATE )
                {
                    iRet = semaphore_wait_timeout ( Semaphore->SemT , TIMEOUT_IMMEDIATE );
                }
                else
                {
                    time_wait = POSIX_TimePlus(POSIX_TimeNow ( ), POSIX_GetClocksPerSecond()/1000*TimeOut);

                    iRet = semaphore_wait_timeout ( Semaphore->SemT , &time_wait );
                }

                if ( iRet >= 0 )
                    Result = YW_NO_ERROR ;
                else
                    Result = YWOS_ERROR_TIMEOUT ;


#endif

            }
            else
            {
                Result = YWOS_ERROR_INVALID_INSTANCE ;
            }
        }
        else
        {
            Result = YWOS_ERROR_INVALID_INSTANCE;
        }
    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }

    return  Result;
}


 /***********************************************************************
    函数说明:    获取信号量的值
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/


YW_ErrorType_T YWOS_SemaphoreCount( YWOS_SemaphoreID_T  SemaphoreID , S32* Count  )
{

    YW_ErrorType_T       Result = YW_NO_ERROR;
    YWOS_SemaphoreTable_T    *Semaphore = (YWOS_SemaphoreTable_T    *)SemaphoreID;
    if(NULL == Count )
    {
        return YWHAL_ERROR_BAD_PARAMETER;
    }
    if(bYWOS_Init)
    {
        if(YW_HandleValid(astSemTable, YWOS_SEMAPHORE_MAX, SemaphoreID))
        {
            if( Semaphore->Used == YWOS_YES )
            {
#if (  YWOS_STLINUX == YWOS_YES )


                *Count = 0  ;

                Result = YW_NO_ERROR ;
#endif
            }
            else
            {
                Result = YWOS_ERROR_INVALID_INSTANCE ;
            }
        }
        else
        {
            Result = YWOS_ERROR_INVALID_INSTANCE;
        }
    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }

    return  Result;
}



#define  MUTEX_PART

// mutex
YW_ErrorType_T YWOS_MutexCreate(  YWOS_MutexID_T* MutexID )
{

    YW_ErrorType_T       Result = YW_NO_ERROR;
    int        iMutexIndex;
    YWOS_MutexTable_T* Mutex;
    if(NULL == MutexID)
    {
        return YWHAL_ERROR_BAD_PARAMETER;
    }
    if(bYWOS_Init)
    {
        * MutexID = 0;
        mutex_lockit(Mutex_MUTEX);
        for( iMutexIndex = 0 ; iMutexIndex < YWOS_MUTEX_MAX ; iMutexIndex ++ )
        {
            if( astMutTable[iMutexIndex].Used == YWOS_NO )
            {
                Mutex = &astMutTable[iMutexIndex];
                astMutTable[iMutexIndex].Used = YWOS_YES;
                break;
            }
        }
       mutex_release(Mutex_MUTEX);
        if( iMutexIndex < YWOS_MUTEX_MAX )
        {
#if (  YWOS_STLINUX == YWOS_YES )

            Mutex->MutT = mutex_create_fifo();

            if( Mutex->MutT != NULL )
            {

                 *MutexID = (U32)Mutex;
                Result = YW_NO_ERROR ;
            }
            else
            {
                Mutex->Used = YWOS_NO;
                Result = YWOS_ERROR;
            }

#endif
        }
        else
        {
            Result = YWOS_ERROR_NO_FREE_INSTANCE ;
        }

    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }

    return  Result;
}

YW_ErrorType_T YWOS_MutexDelete(  YWOS_MutexID_T  MutexID )
{

    YW_ErrorType_T       Result = YW_NO_ERROR;
    YWOS_MutexTable_T* Mutex = (YWOS_MutexTable_T*)MutexID;

    if(bYWOS_Init)
    {
        if(YW_HandleValid(astMutTable, YWOS_MUTEX_MAX, MutexID))
        {
            if( Mutex->Used == YWOS_YES )
            {
#if (  YWOS_STLINUX == YWOS_YES )
                mutex_delete(Mutex->MutT);
                Mutex->Used = YWOS_NO;
                Result = YW_NO_ERROR ;


#endif
            }
            else
            {
                Result = YWOS_ERROR_INVALID_INSTANCE ;
            }

        }
        else
        {
            Result = YWOS_ERROR_INVALID_INSTANCE;
        }
    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }

    return  Result;
}

YW_ErrorType_T YWOS_MutexSend( YWOS_MutexID_T  MutexID )
{

    YW_ErrorType_T       Result = YW_NO_ERROR;
    YWOS_MutexTable_T* Mutex = (YWOS_MutexTable_T*)MutexID;

    if(bYWOS_Init)
    {
        if(YW_HandleValid(astMutTable, YWOS_MUTEX_MAX, MutexID))
        {
            if(Mutex->Used == YWOS_YES )
            {
#if (  YWOS_STLINUX == YWOS_YES )

                mutex_release(Mutex->MutT);
                Result = YW_NO_ERROR;

#endif
            }
            else
            {
                Result = YWOS_ERROR_INVALID_INSTANCE ;
            }
        }
        else
        {
            Result = YWOS_ERROR_INVALID_INSTANCE;
        }
    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }
    return  Result;
}


YW_ErrorType_T YWOS_MutexWait( YWOS_MutexID_T  MutexID , YWOS_ClockMsec_T TimeOut )
{

    YW_ErrorType_T       Result = YW_NO_ERROR;
    YWOS_MutexTable_T* Mutex = (YWOS_MutexTable_T*)MutexID;

    if(bYWOS_Init)
    {
        if(YW_HandleValid(astMutTable, YWOS_MUTEX_MAX, MutexID))
        {
            if( Mutex->Used == YWOS_YES )
            {
#if (  YWOS_STLINUX == YWOS_YES )

                mutex_lockit(Mutex->MutT);
                Result = YW_NO_ERROR ;

#endif
            }
            else
            {
                Result = YWOS_ERROR_INVALID_INSTANCE ;
            }
        }
        else
        {
            Result = YWOS_ERROR_INVALID_INSTANCE;
        }
    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }
    return  Result;
}



#define  TIME_PART

/***********************************************************************
    函数说明:    延时,  单位毫秒
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2008.04.03         詹翰明       新建
************************************************************************/

YW_ErrorType_T  YWOS_TaskSleep(YWOS_ClockMsec_T Time)
{
    YW_ErrorType_T       Result = YW_NO_ERROR;
    if(bYWOS_Init)
    {
#if (  YWOS_STLINUX == YWOS_YES )
        usleep (Time*1000);
#endif
    }
    else
    {
        Result = YWOS_ERROR_NOT_INITIALIZED;
    }
    return  Result;
}

void YWOS_Exit(S32 ExitParam)
{
    if(bYWOS_Init)
    {

        #if ( YWOS_STLINUX == YWOS_YES )
        {
            exit(ExitParam);
        }

        #endif
    }
}

#define  NET_PART

static char *YWOS_IwGetIfname(char *name, int nsize, char *buf)
{
    char *	end;

    /* Skip leading spaces */
    while(isspace(*buf))
    {
        buf++;
    }
    /* Get name up to the last ':'. Aliases may contain ':' in them,
    * but the last one should be the separator */
    end = strrchr(buf, ':');

    /* Not found ??? To big ??? */
    if((end == NULL) || (((end - buf) + 1) > nsize))
    return(NULL);

    /* Copy */
    memcpy(name, buf, (end - buf));
    name[end - buf] = '\0';

    /* Return value currently unused, just make sure it's non-NULL */
    return(end);
}


/***********************************************************************
    函数说明:    获取无线网卡的interface
    调用说明:

    修改记录:    日       期      作      者       修定
                 ---------         ---------       -----
                 2010.10.10      LWJ              新建
************************************************************************/
void YWOS_GetWirelessName(char *ifname)
{
    char   buff[1024];
    FILE * fh;
    int    i = 0;

    /* Check if /proc/net/wireless is available */
    fh = fopen("/proc/net/dev", "r");
	if(fh != NULL)
    {
    	/* Success : use data from /proc/net/wireless */
    	/* Eat 2 lines of header */
    	fgets(buff, sizeof(buff), fh);
    	fgets(buff, sizeof(buff), fh);

    	/* Read each device line */
    	while(fgets(buff, sizeof(buff), fh))
    	{
    		char name[IFNAMSIZ + 1];
    		char *s;
    		/* Skip empty or almost empty lines. It seems that in some
    		* cases fgets return a line with only a newline. */
    		if((buff[0] == '\0') || (buff[1] == '\0'))
    		{
    		    continue;
    		}
    		i++;
    		/* Extract interface name */
    		s = YWOS_IwGetIfname(name, sizeof(name), buff);
    		if(s)
    		{
    			if(i >= 3 && (YWLIB_Strncmp((S8 *)name, (S8 *)"ppp", 3) != 0)) //只获取接入盒子的第一个可识别的wifi的名字
    			{
    				memcpy(ifname, name, IFNAMSIZ+1);
    				break;
    			}
    		}
    	}
    	fclose(fh);
    }
	else
	{
		printf("open /proc/net/dev failed\n");
		return;
	}
}


/***********************************************************************
    函数说明:    根据输入的Index设置指定网卡的MAC
    调用说明:    当前只支持最多2个网卡。可扩展。

    修改记录:    日       期      作      者       修定
                 ---------         ---------       -----
                 2010.02.25        LWJ              新建
************************************************************************/
YW_ErrorType_T YWOS_GetMACAddr( U8 EthCardIndex, U8* pMacBuff, U8 MacLen )
{
#if 1
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	U8     i = 0;
    int    sock;
    struct sockaddr_in sin;
    struct ifreq ifr;
	char   ifname[17] = {0};

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1)
    {
        perror("socket");
        YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWOS_GetMACAddr] SOCK_DGRAM failed.\n");
        return YWHAL_ERROR_NO_INITIALIZED;
    }
    /* Prepare request */
    YWLIB_Memset(&ifr, 0, sizeof(struct ifreq));
    if (EthCardIndex == 0)
    {
        YWLIB_Strncpy(ifr.ifr_name, "eth0", IFNAMSIZ);
        ifr.ifr_name[IFNAMSIZ-1] = 0;
    }
    else
    {
       YWOS_GetWirelessName(ifname);
       if (ifname[0] == '\0')
       {
            return YWHAL_ERROR_NO_INITIALIZED;
       }
       YWLIB_Strncpy(ifr.ifr_name, ifname, IFNAMSIZ);
       ifr.ifr_name[IFNAMSIZ-1] = 0;
    }

    YWLIB_Memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
    if(ioctl(sock, SIOCGIFHWADDR, &ifr) < 0)
    {
        perror("ioctl");
        YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWOS_GetMACAddr] ioctl SIOCGIFHWADDR failed.\n");
        return YWHAL_ERROR_NO_INITIALIZED;
    }

    for (i = 0; i < 6; i++)
    {
        *(pMacBuff+i) = (U8)ifr.ifr_hwaddr.sa_data[i];
    }
    return YW_ErrorCode;

#else //use system call
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	U8     i = 0;

	S8  MACAddr[18]={0};
    int pMacBuffTmp[6]={0};
    FILE *MacFileFp = NULL;
    struct stat StatBuff;
	char ifname[17] = {0};
    char cmd[100] = {0};


    YWLIB_Memset(cmd, 0, sizeof(cmd));
	if( EthCardIndex > 2 || MacLen !=  6)
	{
        YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWOS_GetMACAddr] Invalid Parameter.\n");
		return YWHAL_ERROR_BAD_PARAMETER;
	}
    if (pMacBuff == NULL)
    {
        YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWOS_GetMACAddr] Invalid Parameter.\n");
        return YWHAL_ERROR_BAD_PARAMETER;
    }

    YWLIB_Memset(pMacBuff, 0, MacLen);

    if( EthCardIndex == 0 )
    {
        system("ifconfig eth0 up");
        system("ifconfig eth0 | grep HWaddr | awk '{print $5}' > getmac.txt");
    }
    else //wifi
    {
        YWOS_GetWirelessName(ifname);
        if (ifname[0] == '\0')
            return YWHAL_ERROR_NO_INITIALIZED;

        YWLIB_Snprintf((S8*)cmd, sizeof(cmd), (S8*)"ifconfig %s up", ifname);
	    system(cmd);

        YWLIB_Memset(cmd, 0, sizeof(cmd));
        YWLIB_Snprintf((S8*)cmd, sizeof(cmd), (S8*)"ifconfig %s | grep HWaddr | awk '{print $5}' > getmac.txt", ifname);
	    system(cmd);

    }
    if( ( MacFileFp = fopen("getmac.txt" ,"rb+") ) == NULL )
    {
    	YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWOS_GetMACAddr] Can not open getmac.txt.\n");
        system("rm -rf getmac.txt");
        return YWHAL_ERROR_UNKNOWN_DEVICE;
	}

	stat("getmac.txt",&StatBuff);
	if( StatBuff.st_size == 0)
	{
    	YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWOS_GetMACAddr] Can not find the MAC Addr.\n");
        fclose(MacFileFp);
        system("rm -rf getmac.txt");
        return YWHAL_ERROR_UNKNOWN_DEVICE;
	}

	fread(MACAddr, StatBuff.st_size-1, 1, MacFileFp);
    fclose(MacFileFp);
    system("rm -rf getmac.txt");

    sscanf((const char*)MACAddr, "%X:%X:%X:%X:%X:%X", pMacBuffTmp, pMacBuffTmp+1, pMacBuffTmp+2, pMacBuffTmp+3,pMacBuffTmp+4,pMacBuffTmp+5);

    for (i = 0; i < 6; i++)
    {
        *(pMacBuff+i) = (U8)pMacBuffTmp[i];
    }
	return YW_ErrorCode;
 #endif

}

#if 0
/***********************************************************************
    函数说明:    根据输入的Index设置指定网卡的MAC
    调用说明:    当前只支持最多2个网卡。可扩展。

    修改记录:    日       期      作      者       修定
                 ---------         ---------       -----
                 2009.10.20        CS              新建
                 2010.02.25        LWJ             修改
************************************************************************/
YW_ErrorType_T YWOS_SetMACAddr( U8 EthCardIndex, U8* pMacBuff, U8 MacLen )
{
	YW_ErrorType_T YW_ErrorCode = YW_NO_ERROR;
	U8   i            = 0;
	S8   String[50]   = {0};
    S8   Temp[3]      = {0};
	char ifname[17]   = {0};
	S8   cmd[30]      = {0};


    YWLIB_Memset(cmd, 0, sizeof(cmd));
	if( EthCardIndex > 2 || MacLen != 6)
	{
        YWOS_Trace(YWOS_TRACE_ERROR, "[ERROR][YWOS_SetMAC] Invalid Parameter.\n");
		return YWHAL_ERROR_BAD_PARAMETER;
	}

	if( EthCardIndex == 0 )
	{
		YWLIB_Sprintf((S8*)String, (S8*)"ifconfig eth0 hw ether ");
	}
	else
	{
        YWOS_GetWirelessName(ifname);
        if (ifname[0] == '\0')
            return YWHAL_ERROR_NO_INITIALIZED;
        YWLIB_Snprintf((S8*)String, sizeof(String), (S8*)"ifconfig %s hw ether ", ifname);
	}

	for(i = 0; i < MacLen; i++)
	{
        YWLIB_Memset(Temp, 0, sizeof(Temp));
		YWLIB_Sprintf((S8*)Temp, (S8*)"%02X", (U32)(*pMacBuff));
		YWLIB_Strcat((S8*)String, (const S8 *)Temp);
		if(i != MacLen - 1)
		{
			YWLIB_Strcat((S8*)String, (const S8*)":");
		}
		pMacBuff++;
	}

	//printf("-----Dest Str is %s--StrLen is %d---\n",String,strlen(String));

    if( EthCardIndex == 0 )
    {
    	YWOS_SystemCmd("ifconfig eth0 down");
    	YWOS_SystemCmd((char*)String);
    	YWOS_SystemCmd("ifconfig eth0 up");
    }
    else
    {
        YWLIB_Memset(cmd, 0 ,sizeof(cmd));
        YWLIB_Snprintf((S8*)cmd, sizeof(cmd), (S8*)"ifconfig %s down", ifname);
	    YWOS_SystemCmd((char*)cmd);

        YWOS_SystemCmd((char*)String);

        YWLIB_Memset(cmd, 0, sizeof(cmd));
        YWLIB_Snprintf((S8*)cmd, sizeof(cmd), (S8*)"ifconfig %s up", ifname);
	    YWOS_SystemCmd((char*)cmd);
    }


	return YW_ErrorCode;
}
#endif

#define  DEBUG_PART

U32 g_TraceLevel = YWOS_TRACE_INFO;
void YWOS_SetTraceLevel( U32 Level)
{
    g_TraceLevel = Level;
}

/***********************************************************************
    函数说明:    debug内存信息

    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/

void YWOS_Trace( U32 Level,  const char  Format[ ], ... )
{
    if(bYWOS_Init)
    {
        if(Level >= g_TraceLevel)
        {
#if (YWOS_TRACE_TO_LOG != YWOS_YES)
            char  StringBuffer[YWOS_TRACE_ONCE_BUF] = {0};     /* Send String Buffer */
            va_list  List;                                     /* Argument Pointer */

            //memset(StringBuffer, 0, sizeof(StringBuffer));
            va_start( List, Format );                          /* Get Argument Pointer */
            vsnprintf( StringBuffer,YWOS_TRACE_ONCE_BUF-1, (char *)Format, List );                        /* Make Display String */
            va_end(List);

			#if (YWOS_TRACE_FORM_CONSOLE == YWOS_YES)
			printf(StringBuffer);
			#endif

			#if (YWOS_TRACE_FORM_UART == YWOS_YES)
            //printf(StringBuffer);
            YWOSi_ttyAS0Write((S8*)StringBuffer);//modify by zdy 2011.03.17
			#endif

#elif (YWOS_TRACE_TO_LOG == YWOS_YES)
			S32 Len;
			char  StringBuffer[YWOS_TRACE_ONCE_BUF] = {0};     /* Send String Buffer */
            va_list  List;                                     /* Argument Pointer */

            va_start( List, Format );                          /* Get Argument Pointer */
            Len = vsnprintf( StringBuffer,YWOS_TRACE_ONCE_BUF-1, (char *)Format, List );  /* Make Display String */
            va_end(List);
			if (Len < 0)
			{
				return;
			}
			#if (YWOS_TRACE_FORM_CONSOLE == YWOS_YES)
			printf(StringBuffer);
			#endif

			#if (YWOS_TRACE_FORM_UART == YWOS_YES)
            //printf(StringBuffer);
            YWOSi_ttyAS0Write((S8*)StringBuffer);//modify by zdy 2011.03.17
			#endif

			if (-1 != LogFdCur)
			{
				S32 SpareLen = YWOS_LOG_MAX_SIZE - LogPos;
				char *Buf = StringBuffer;
				S32 WLen;

				if (SpareLen < Len && SpareLen > 0)
				{
					WLen = write(LogFdCur, StringBuffer, SpareLen);
					if (-1 != WLen)
					{
						fsync(LogFdCur);
						LogPos += WLen;
					}

					Len -= SpareLen;
					Buf = StringBuffer+SpareLen;
				}
				else if (SpareLen < 0)
				{
					//printf("Bug %s %d\n", __FUNCTION__, __LINE__);
                    //modify by zdy 2011.03.17
                    //{
                    char  StringBufferTmp[YWOS_TRACE_ONCE_BUF] = {0};

                    snprintf(StringBufferTmp,YWOS_TRACE_ONCE_BUF-1,"Bug %s %d",, __FUNCTION__, __LINE__);
					//YWOSi_ttyAS0Write((S8*)StringBuffer);
					#if (YWOS_TRACE_FORM_CONSOLE == YWOS_YES)
        			printf(StringBufferTmp);
        			#endif

        			#if (YWOS_TRACE_FORM_UART == YWOS_YES)
                    //printf(StringBuffer);
                    YWOSi_ttyAS0Write((S8*)StringBufferTmp);
        			#endif
                    //} end
					LogPos = YWOS_LOG_MAX_SIZE;
				}

				if (LogPos >= YWOS_LOG_MAX_SIZE)
				{
					int i = LogIndex+1;

					if (i >= LOG_FILE_NUM)
					{
						i = 0;
					}
					/* search new valid fd from [LogIndex+1] to end */
					while (i<LOG_FILE_NUM && (-1==LogFd[i] || LogFdCur==LogFd[i]))
					{
						++i;
					}
					if (i < LOG_FILE_NUM) /* have new valid fd */
					{
						LogFdCur = LogFd[i];
						LogIndex = i;
					}
					else /* search new valid fd from begin to  [LogIndex-1]*/
					{
						i = 0;
						while (i<LogIndex && (-1==LogFd[i] || LogFdCur==LogFd[i]))
						{
							++i;
						}
						if (i < LogIndex)
						{
							LogFdCur = LogFd[i]; /* have new valid fd */
							LogIndex = i;
						}
					}
					/*
					 * if no new valid fd
					 * just use old valid fd
					 */
					LogPos = 0;
					if (-1 == lseek(LogFdCur, 0, SEEK_SET))
					{
						//printf("lseek error\n");
						return;
					}
				}

				WLen = write(LogFdCur, Buf, Len);
				if (-1 != WLen)
				{
					LogPos += WLen;
					fsync(LogFdCur);
				}
			}
#endif
        }
    }

}
/***********************************************************************
    函数说明:    debug内存信息

    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/
void YWOS_TracePartitionInfo( YWOS_PartitionID_T partion )
{
#if (  YWOS_STOS20 == YWOS_YES )

#elif  (  YWOS_STOS21== YWOS_YES )

#elif  (  YWOS_NECITRON == YWOS_YES )

#elif  (  YWOS_ALI3329 == YWOS_YES )

#endif
}

/***********************************************************************
    函数说明:    检查内存是否使用越界

    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2005.10.20         詹翰明       新建
************************************************************************/
#if(YWOS_MEMORY_INFO_CHECK  == YWOS_YES)
void YWOS_MemoryCheck(void)
{
    U32 iMemInfoIndex;
    U32 MemInfoUseNum = 0;

    for( iMemInfoIndex = 0 ; iMemInfoIndex < YWOS_MEMORY_INFO_MAX ; iMemInfoIndex ++ )
    {
        YWOS_MutexWait(MutexMemoryLock, YWOS_WAIT_INFINITY);
        if( MemoryInfo[iMemInfoIndex].Used == YWOS_YES)
        {
            if(MemoryInfo[iMemInfoIndex].FileName != NULL)
            {
                //YWOS_Trace(YWOS_TRACE_ERROR,
                //      "[YWOS_MemoryCheck]-The Index[%d]-IsMalloced--in--LINE [%8d] FILE [%s]-----\n",
                //      iMemInfoIndex,MemoryInfo[iMemInfoIndex].Line,MemoryInfo[iMemInfoIndex].FileName);
            }
            if(MemoryInfo[iMemInfoIndex].AddrBase != NULL
                && MemoryInfo[iMemInfoIndex].AddrPtr != NULL
                && MemoryInfo[iMemInfoIndex].AddrEnd != NULL )
            {
                U32 BaseMemAddr, EndSize;
                BaseMemAddr = *(U32 *)MemoryInfo[iMemInfoIndex].AddrBase;
                EndSize = *(U32 *)MemoryInfo[iMemInfoIndex].AddrEnd;
                if( BaseMemAddr != (U32)&MemoryInfo[iMemInfoIndex])
                {
                    YWOS_Trace(YWOS_TRACE_ERROR,
                        "[YWOS_MemoryCheck]-------------- Start is Overflow----print start-----------\n");
                    YWOS_Trace(YWOS_TRACE_ERROR,
                        "[YWOS_MemoryCheck]----MemInfo Index[%d] AddrBase [0x%x] Start is Overflow---\n",
                        iMemInfoIndex , MemoryInfo[iMemInfoIndex].AddrBase);
                    YWOS_Trace(YWOS_TRACE_ERROR ,
                        "[YWOS_MemoryCheck]----MemInfo Index[%d] AddrPtr  [0x%x] Start is Overflow---\n",
                        iMemInfoIndex , MemoryInfo[iMemInfoIndex].AddrPtr);
                    YWOS_Trace(YWOS_TRACE_ERROR ,
                        "[YWOS_MemoryCheck]----MemInfo Index[%d] AddrEnd  [0x%x] Start is Overflow---\n",
                        iMemInfoIndex , MemoryInfo[iMemInfoIndex].AddrEnd);
                    YWOS_Trace(YWOS_TRACE_ERROR,
                        "[YWOS_MemoryCheck]-------------- Start is Overflow-----print end   ---------\n");
                }
                else if(( (U32)MemoryInfo[iMemInfoIndex].AddrBase + EndSize - 4)
                    != ((U32)MemoryInfo[iMemInfoIndex].AddrEnd))
                {
                    YWOS_Trace(YWOS_TRACE_ERROR,
                        "[YWOS_MemoryCheck]-------------- End is Overflow----print start-----------\n");
                    YWOS_Trace(YWOS_TRACE_ERROR,
                        "[YWOS_MemoryCheck]----MemInfo Index[%d] AddrBase [0x%x] End is Overflow---\n",
                        iMemInfoIndex , MemoryInfo[iMemInfoIndex].AddrBase);
                    YWOS_Trace(YWOS_TRACE_ERROR ,
                        "[YWOS_MemoryCheck]----MemInfo Index[%d] AddrPtr  [0x%x] End is Overflow---\n",
                        iMemInfoIndex , MemoryInfo[iMemInfoIndex].AddrPtr);
                    YWOS_Trace(YWOS_TRACE_ERROR ,
                        "[YWOS_MemoryCheck]----MemInfo Index[%d] AddrEnd  [0x%x] End is Overflow---\n",
                        iMemInfoIndex , MemoryInfo[iMemInfoIndex].AddrEnd);
                    YWOS_Trace(YWOS_TRACE_ERROR,
                        "[YWOS_MemoryCheck]-------------- End is Overflow----print End-------------\n");
                }
                MemInfoUseNum ++;


            }
            else
            {
                if(MemoryInfo[iMemInfoIndex].AddrBase == NULL
                    || MemoryInfo[iMemInfoIndex].AddrPtr == NULL
                    || MemoryInfo[iMemInfoIndex].AddrEnd == NULL)
                {
                    YWOS_Trace(YWOS_TRACE_ERROR,
                        "[YWOS_MemoryCheck]-------------- No Malloc Succes----print start----------------\n");
                    YWOS_Trace(YWOS_TRACE_ERROR,
                        "[YWOS_MemoryCheck]---MemInfo Index[%d] Not Malloc Succes AddrBase [0x%x] -------\n",
                        iMemInfoIndex , MemoryInfo[iMemInfoIndex].AddrBase);
                    YWOS_Trace(YWOS_TRACE_ERROR ,
                        "[YWOS_MemoryCheck]---MemInfo Index[%d] Not Malloc Succes AddrPtr  [0x%x] -------\n",
                        iMemInfoIndex , MemoryInfo[iMemInfoIndex].AddrPtr);
                    YWOS_Trace(YWOS_TRACE_ERROR ,
                        "[YWOS_MemoryCheck]---MemInfo Index[%d] Not Malloc Succes AddrEnd  [0x%x] -------\n",
                        iMemInfoIndex , MemoryInfo[iMemInfoIndex].AddrEnd);
                    YWOS_Trace(YWOS_TRACE_ERROR,
                        "[YWOS_MemoryCheck]-------------- No Malloc Succes----print End-------------------\n");
                }
            }
        }
        else
        {
            if(MemoryInfo[iMemInfoIndex].AddrBase != NULL
                || MemoryInfo[iMemInfoIndex].AddrPtr != NULL
                || MemoryInfo[iMemInfoIndex].AddrEnd != NULL)
            {
                YWOS_Trace(YWOS_TRACE_ERROR,
                    "[YWOS_MemoryCheck]-------------- No Free----print start----------------\n");
                YWOS_Trace(YWOS_TRACE_ERROR,
                    "[YWOS_MemoryCheck]---MemInfo Index[%d] Not Free  AddrBase [0x%x] -------\n",
                    iMemInfoIndex , MemoryInfo[iMemInfoIndex].AddrBase);
                YWOS_Trace(YWOS_TRACE_ERROR ,
                    "[YWOS_MemoryCheck]---MemInfo Index[%d] Not Free  AddrPtr  [0x%x] -------\n",
                    iMemInfoIndex , MemoryInfo[iMemInfoIndex].AddrPtr);
                YWOS_Trace(YWOS_TRACE_ERROR ,
                    "[YWOS_MemoryCheck]---MemInfo Index[%d] Not Free  AddrEnd  [0x%x] -------\n",
                    iMemInfoIndex , MemoryInfo[iMemInfoIndex].AddrEnd);
                YWOS_Trace(YWOS_TRACE_ERROR,
                    "[YWOS_MemoryCheck]-------------- No Free----print End-------------------\n");
            }
        }
       YWOS_MutexSend(MutexMemoryLock);
    }

    YWOS_Trace(YWOS_TRACE_ERROR ,
                    "[YWOS_MemoryCheck]##################----MemInfo the [%d]  is usd---################\n",
                    MemInfoUseNum);

}
#endif

#define  VERSION_PART

/***********************************************************************
    函数说明:    获取操作系统的版本
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
                               2008.04.03         詹翰明       新建
************************************************************************/

S8* YWOS_GetRevision(void)
{
#if (YWOS_STOS20 == YWOS_YES)
    static const S8 Revision[] = "YWOS_REL_1.0.0";
    return((S8*) Revision);

#elif (YWOS_STOS21== YWOS_YES)
    static const S8 Revision[] = "YWOS_REL_1.0.0";
    return((S8*) Revision);

#elif (YWOS_NECITRON == YWOS_YES)
    static const S8 Revision[] = "YWOS_REL_1.0.0";
    return((S8*) Revision);

#elif  (YWOS_ALI3329 == YWOS_YES)
    static const S8 Revision[] = "YWOS_REL_1.0.0";
    return((S8*) Revision);

#else
    static const S8 Revision[] = "YWOS_REL_1.0.0";
    return((S8*) Revision);
#endif
}
/*EOF-------------------------------------------------------------------------------------*/
