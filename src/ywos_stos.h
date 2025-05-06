/******************************************************************************/
/*                                                                            */
/* File name   : STAPP_OS.H                                                   */
/*                                                                            */
/* Description : Operating system layer adaptation                            */
/*                                                                            */
/* COPYRIGHT (C) ST-Microelectronics 2005                                     */
/*                                                                            */
/* Date               Modification                 Name                       */
/* ----               ------------                 ----                       */
/* 02/03/05           Created                      M.CHAPPELLIER              */
/*                                                                            */
/******************************************************************************/

#ifndef _YWOS_STOS_H_
#define _YWOS_STOS_H_

/* C++ support */
/* ----------- */
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================
   OS21
   ======================================================================== */

#if defined(ST_OS21)
#include "os21/partition.h"
#include "os21/semaphore.h"
#include "os21/mutex.h"
#include "os21/kernel.h"
#include "os21/task.h"
#include "os21/ostime.h"
#include "os21/message.h"
#include "os21/event.h"
#include "os21/interrupt.h"
#include "os21/mutex.h"

/* Misc */
/* ---- */
#define Kernel_Version() kernel_version()

/* Timers */
/* ------ */
#define TimerHighGet(_value_)      _value_=time_now()
#define TimerLowGet(_value_)       _value_=time_now()
#define TimerHighSet(_value_)
#define TimerLowSet(_value_)
#define Clock_t                    osclock_t
#define Time_Now()                 time_now()
#define Time_Plus(_time1_,_time2_) time_plus(_time1_,_time2_)

/* Task creation */
/* ------------- */
#define TASK_DEF  void
#define TASK_EXIT
#define Task_t                                                         task_t *
#define Task_Delay(x)                                                  task_delay(x)
#if 1
#define Task_Create(_func_,_param_,_stack_,_pri_,_name_,_flag_,_task_) task_create(_func_,_param_,((_stack_)>16384?(_stack_):(_stack_)+16384),_pri_,_name_,_flag_)
#else
#define Task_Create(_func_,_param_,_stack_,_pri_,_name_,_flag_,_task_) task_create(_func_,_param_,_stack_,_pri_,_name_,(_flag_)|task_flags_no_min_stack_size)
#endif
#define Task_Lock()                                                    task_lock()
#define Task_Unlock()                                                  task_unlock()
#define Task_Delete(_task_id_)                                         task_delete(_task_id_)
#define Task_Priority_Set(_task_id_,_pri_)                             task_priority_set(_task_id_,_pri_)
#define Task_Wait(_task_id_)                                           task_wait(&_task_id_,1,TIMEOUT_INFINITY);
#define Task_Suspend(_task_id_)                                        task_suspend(_task_id_)
#define Task_Resume(_task_id_)                                         task_resume(_task_id_)
#define Task_Name(_task_id_)                                           task_name(_task_id_)
#define Task_Id()                                                      task_id()
#define Task_Context                                                   task_context
#define Task_Context_Task                                              task_context_task

/* Semaphores */
/* ---------- */
#define Semaphore_t                                   semaphore_t *
#define Semaphore_Init_Fifo(_sem_,_value_)            _sem_=semaphore_create_fifo         (_value_)
#define Semaphore_Init_Fifo_TimeOut(_sem_,_value_)    _sem_=semaphore_create_fifo         (_value_)
#define Semaphore_Create_Fifo(_sem_,_value_)          _sem_=semaphore_create_fifo         (_value_)
#define Semaphore_Create_Fifo_TimeOut(_sem_,_value_)  _sem_=semaphore_create_fifo_timeout (_value_)
#define Semaphore_Delete(_sem_)                       semaphore_delete                    (_sem_)
#define Semaphore_Wait_Timeout(_sem_,_time_)          semaphore_wait_timeout              (_sem_,_time_)
#define Semaphore_Signal(_sem_)                       semaphore_signal                    (_sem_)
#define Semaphore_Wait(_sem_)                         semaphore_wait                      (_sem_)

/* Mutex */
/* ----- */
#define Mutex_t                                      mutex_t *
#define Mutex_Init_Fifo(_mutex_)                     _mutex_=mutex_create_fifo           ()
#define Mutex_Create_Fifo(_mutex_,_value_)           _mutex_=mutex_create_fifo           ()
#define Mutex_Delete(_mutex_)                        mutex_delete                        (_mutex_)
#define Mutex_Lock(_mutex_)                          mutex_lock                          (_mutex_)
#define Mutex_Unlock(_mutex_)                        mutex_release                       (_mutex_)

/* Message queues */
/* -------------- */
#define Message_Queue_t                              message_queue_t *
#define Message_Create_Queue(_msg_size_,_nb_msg_)    message_create_queue                (_msg_size_,_nb_msg_)
#define Message_Delete_Queue(_msg_queue_)            message_delete_queue                (_msg_queue_)
#define Message_Claim(_msg_queue_)                   message_claim                       (_msg_queue_)
#define Message_Release(_msg_queue_,_msg_)           message_release                     (_msg_queue_,_msg_)
#define Message_Send(_msg_queue_,_msg_)              message_send                        (_msg_queue_,_msg_)
#define Message_Receive(_msg_queue_)                 message_receive                     (_msg_queue_)

/* Memory partitions */
/* ----------------- */
#define Partition_t                                        partition_t *
#define Partition_Init_Simple(_partition_,_memory_,_size_) _partition_=partition_create_simple (_memory_,_size_)
#define Partition_Init_Heap(_partition_,_memory_,_size_)   _partition_=partition_create_heap   (_memory_,_size_)
#define Memory_Allocate(_partition_,_size_)                memory_allocate(_partition_,_size_)
#define Memory_Deallocate(_partition_,_ptr_)               memory_deallocate(_partition_,_ptr_)
#define Memory_Reallocate(_partition_,_ptr_,_size_)        memory_reallocate(_partition_,_ptr_,_size_)
#define Memory_Allocate_Clear(_partition_,_nmemb_,_size_)  memory_allocate_clear(_partition_,_nmemb_,_size_)

/* Interrupts */
/* ---------- */
#define IT_DEF  int
#define IT_EXIT return(OS21_SUCCESS);
#define Interrupt_Install(_number_,_level_,_handler_,_param_) interrupt_install(_number_,_level_,(int(*)(void*))_handler_, _param_)
#define Interrupt_Uninstall(_number_,_level_)                 interrupt_uninstall(_number_,_level_)
#define Interrupt_Enable(_number_,_level_)                    interrupt_enable(interrupt_handle(_number_))
#define Interrupt_Disable(_number_,_level_)                   interrupt_disable(interrupt_handle(_number_))
#define Interrupt_Lock()                                      interrupt_lock()
#define Interrupt_Unlock()                                    interrupt_unlock()
#endif

/* ========================================================================
   LINUX
   ======================================================================== */
#define ST_OSLINUX
#if defined(ST_OSLINUX)
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <sys/poll.h>
#include <stdarg.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "stos.h"

/* Misc */
/* ---- */
#define Kernel_Version() UTS_RELEASE

/* Timers */
/* ------ */
#define Clock_t                    STOS_Clock_t
#define TimerHighGet(_value_)      _value_=STOS_time_now()
#define TimerLowGet(_value_)       _value_=STOS_time_now()
#define Time_Now()                 STOS_time_now()
#define Time_Plus(_time1_,_time2_) STOS_time_plus(_time1_,_time2_)

/* Task creation */
/* ------------- */
#define TASK_DEF  void
#define TASK_EXIT
#define Task_t                                                         pthread_t
#define Task_Delay(x)                                                  STOS_TaskDelay(x)
#define Task_Create(_func_,_param_,_stack_,_pri_,_name_,_flag_,_task_) ((pthread_create(&(_task_),NULL,(void*)(_func_),(void*)(_param_))==0)?(_task_):0)
#define Task_Lock()                                                    /* No task lock   in user space */
#define Task_Unlock()                                                  /* No task unlock in user space */
#define Task_Delete(_task_id_)                                         pthread_cancel(_task_id_)
#define Task_Priority_Set(_task_id_,_pri_)                             {struct sched_param p; p.sched_priority=(_pri_==0)?1:_pri_; pthread_setschedparam(_task_id_,SCHED_RR,&p);}
#define Task_Wait(_task_id_)                                           pthread_join(_task_id_,NULL);
#define Task_Name(_task_id_)                                           task_name(_task_id_)
#define Task_Id()                                                      pthread_self()
#define Task_Context                                                   task_context
#define Task_Context_Task                                              task_context_task

/* Semaphores */
/* ---------- */
#define Semaphore_t                                  semaphore_t *
#define Semaphore_Init_Fifo(_sem_,_value_)           _sem_=STOS_SemaphoreCreateFifo       (NULL,_value_)
#define Semaphore_Init_Fifo_TimeOut(_sem_,_value_)   _sem_=STOS_SemaphoreCreateFifoTimeOut(NULL,_value_)
#define Semaphore_Create_Fifo(_sem_,_value_)         _sem_=STOS_SemaphoreCreateFifo       (NULL,_value_)
#define Semaphore_Create_Fifo_TimeOut(_sem_,_value_) _sem_=STOS_SemaphoreCreateFifoTimeOut(NULL,_value_)
#define Semaphore_Delete(_sem_)                      STOS_SemaphoreDelete                 (NULL,_sem_)
#define Semaphore_Wait_Timeout(_sem_,_time_)         STOS_SemaphoreWaitTimeOut            (_sem_,_time_)
#define Semaphore_Signal(_sem_)                      STOS_SemaphoreSignal                 (_sem_)
#define Semaphore_Wait(_sem_)                        STOS_SemaphoreWait                   (_sem_)

/* Mutex */
/* ----- */
#define Mutex_t                            STOS_Mutex_t *
#define Mutex_Init_Fifo(_mutex_)           _mutex_=STOS_MutexCreateFifo()
#define Mutex_Create_Fifo(_mutex_,_value_) _mutex_=STOS_MutexCreateFifo()
#define Mutex_Delete(_mutex_)              STOS_MutexDelete            (_mutex_)
#define Mutex_Lock(_mutex_)                STOS_MutexLock              (_mutex_)
#define Mutex_Unlock(_mutex_)              STOS_MutexRelease           (_mutex_)

/* Memory partitions */
/* ----------------- */
#define Memory_Allocate(_partition_,_size_)               STOS_MemoryAllocate     (_partition_,_size_)
#define Memory_Deallocate(_partition_,_ptr_)              STOS_MemoryDeallocate   (_partition_,_ptr_)
#define Memory_Reallocate(_partition_,_ptr_,_size_)       STOS_MemoryReallocate   (_partition_,_ptr_,_size_)
#define Memory_Allocate_Clear(_partition_,_nmemb_,_size_) STOS_MemoryAllocateClear(_partition_,_nmemb_,_size_)

/* Interrupts */
/* ---------- */
/* On Linux, no interrupt support in user mode */
#endif

/* C++ support */
/* ----------- */
#ifdef __cplusplus
}
#endif
#endif

