#ifndef _YWGUI_INTERNALS_H_20080416_
#define  _YWGUI_INTERNALS_H_20080416_

#ifdef __cplusplus
extern "C" {
#endif 

/*************************宏定义***************************/

#define TYPE_HWND                   0x01
#define TYPE_WINTODEL               0xF1

#define TYPE_MAINWIN                0x11
#define TYPE_CONTROL                0x12
#define TYPE_ROOTWIN                0x13



/*************************常数定义***************************/
//私有堆
#define SIZE_CLIPRECTHEAP           256
#define SIZE_NOTIFYMSG_HEAP         64


//GUI 线程哈希表容量
#define DEF_NR_THREADS              32 


#define DEF_MSGQUEUE_LEN            /*64*/128 

#define DEF_NR_TIMERS               32

/*************************数据类型定义***********************/
enum
{
    WED_METRICS=1,  /* the metrics of element */
    WED_COLOR,      /* the color of element */
    WED_SHAPE
};




typedef struct YWGUI_CaretInfo_s
{
    S32     x;              // position of caret
    S32     y;
    void*   pNormal;        // normal bitmap.
    void*   pXored;         // bit-Xored bitmap.

    //PBITMAP pBitmap;        // user defined caret bitmap.

    S32     nWidth;         // original size of caret
    S32     nHeight;
    S32     nBytesNr;       // number of bitmap bytes.


    //S32     nEffWidth;      // effective width
    //S32     nEffHeight;     // effective height;


    BOOL    fBlink;         // does blink?
    BOOL    fShow;          // show or hide currently.

    YWGUI_HWnd_T    hOwner;         // the window owns the caret.
    U32    uTime;          // the blink time.
}YWGUI_CaretInfo_T;
typedef YWGUI_CaretInfo_T* YWGUI_CaretInfo_P;



#define SBS_NORMAL      0x00
#define SBS_DISABLED    0x01
#define SBS_HIDE        0x02

typedef struct YWGUI_ScrollBarInfo_s
{
//    S32  minPos;        // min value of scroll range.
//    S32  maxPos;        // max value of scroll range.
//    S32  curPos;        // current scroll pos.
//    S32  pageStep;      // steps per page.
//    S32  barStart;      // start pixel of bar.
//    S32  barLen;        // length of bar.
//    U8 status;        // status of scroll bar.
    YWGUI_HWnd_T hScroll;       // 滚动条句柄
    BOOL bShowScroll;   // 是否显示滚动条
}YWGUI_ScrollBarInfo_T;
typedef YWGUI_ScrollBarInfo_T* YWGUI_ScrollBarInfo_P;

typedef struct YWGUI_ThreadInfo_s YWGUI_ThreadInfo_T;

typedef struct YWGUI_ZorderNode_s
{
     YWGUI_HWnd_T  hWnd; /* Handle of window */
     ListNode       node;  
}YWGUI_ZorderNode_T;
typedef YWGUI_ZorderNode_T* YWGUI_ZorderNode_P;

typedef struct YWGUI_ZorderAxis_s
{
    S32         nNumber;      
    ListNode    head;
}YWGUI_ZorderAxis_T;
typedef YWGUI_ZorderAxis_T* YWGUI_ZorderAxis_P;

//通知消息链节点
typedef struct YWGUI_NotifyMsg_s
{
    YWGUI_Msg_T                 Msg;
    struct YWGUI_NotifyMsg_s*       next;
}YWGUI_NotifyMsg_T;
typedef YWGUI_NotifyMsg_T* YWGUI_NotifyMsg_P;

//同步消息链节点
typedef struct YWGUI_SyncMsg_s
{
    YWGUI_Msg_T                      Msg;
    S32                      retval;
    YWGUI_SemaID_T            sem_handle; //for 消息同步
    struct YWGUI_SyncMsg_s* pNext;
}YWGUI_SyncMsg_T;
typedef YWGUI_SyncMsg_T* YWGUI_SyncMsg_P;

//消息队列结构
typedef struct YWGUI_MsgQueue_s
{
    DWORD dwState;              //消息队列状态

    // 互斥锁:实现不同线程(:收发)对消息队列的互斥访问 
    YWGUI_MutexID_T lock;      
    YWGUI_SemaID_T wait;                 

    //通知消息链
    YWGUI_NotifyMsg_P  pFirstNotifyMsg;     
    YWGUI_NotifyMsg_P  pLastNotifyMsg;     

    //同步消息链
    YWGUI_SyncMsg_P pFirstSyncMsg;    
    YWGUI_SyncMsg_P pLastSyncMsg; 

    //邮寄消息队列
    YWGUI_Msg_T* msg;                  
    S32 len;                   
    S32 readpos, writepos; 

    U32 TimerMask;       
    U32 uCurSlot;
    //考虑消息循环内嵌消息循环的情况  
    S32 loop_depth;          
    
}YWGUI_MsgQueue_T;

typedef YWGUI_MsgQueue_T* YWGUI_MsgQueue_P;

typedef struct YWGUI_CtrlClassInfo_s
{
    S8          name[YWGUI_CLASSNAME_MAX + 1];

    /* * common properties of this class     */
    DWORD       dwStyle;          // Default control styles.
    DWORD       dwExStyle;        // Default control extended styles.

    YWGUI_WindowProc_P      pfnCtrlClassProc;

    YWGUI_Wed_P             ptWed;

    DWORD       dwAddData;   // the additional data.

    U32 XOffset;
    U32 YOffset;
    
    S32         nUseCount;   // use count.

    struct YWGUI_CtrlClassInfo_s*  next;    
}YWGUI_CtrlClassInfo_T;

typedef YWGUI_CtrlClassInfo_T* YWGUI_CtrlClassInfo_P;



/*left,top,right,bottom: 主窗口的位置or 控件在父窗口客户区的位置
cl,ct,cr,cb: 主窗口客户区的位置or 控件客户区在父窗口客户区的位置
hMainWin: 主窗口是自己的窗口句柄,若是控件,是包含该控件的主窗口句柄
hParent: 主窗口总是HWND_DESKTOP 值or 控件父窗口句柄
ptGcrInfo:主窗口指向其tGcrInfo结构，子窗口指向其主窗口的tGcrInfo结构
hFirstChild,hActiveChild:桌面窗口该值为0
*/
#define COMM_WINDOW_ELEMENT                   \
    S16     DataType;                         \
    S16     WinType;                          \
    U16     id;                               \
    S32     left,top;                         \
    S32     right,bottom;                     \
    S32     cl,ct;                            \
    S32     cr,cb;                            \
    DWORD   dwStyle;                          \
    DWORD   dwExStyle;                        \
    YWGUI_WindowProc_P      pfnWindowProc;    \
    YWGUI_ZorderNode_P      pZOrderNode;      \
    YWGUI_InvInfo_T         tInvRgnInfo;      \
    YWGUI_LogFont_P         ptLogFont;        \
    YWGUI_GcrInfo_P         ptGcrInfo;        \
    YWGUI_Wed_P             ptWed;            \
    DWORD                   dwAddData;        \
    DWORD                   dwAddData2;       \
    YWGUI_Char_T*           spCaption;        \
    S32   idStr;                      \
    YWGUI_HWnd_T            hMainWin;         \
    YWGUI_HWnd_T            hParent;          \
    YWGUI_HWnd_T            hFirstChild;      \
    YWGUI_HWnd_T            hActiveChild;  

    

typedef struct YWGUI_MainWin_s
{
    COMM_WINDOW_ELEMENT

    struct YWGUI_MainWin_s* pHosting;//指向属主窗口(如自己是第一个属主窗口，为NULL)
    struct YWGUI_MainWin_s* pFirstHosted;//挂靠到该窗口的第一个主窗口
    struct YWGUI_MainWin_s* pNextHosted; //与该窗口一起挂靠到属主窗口的下一个主窗口

                    
    YWGUI_MsgQueue_P pMessages;             // 指向线程消息队列

    YWGUI_GcrInfo_T  tGcrInfo;    //内部矩形为屏幕坐标       
                                           
    YWGUI_ThreadID_T               threadId;  //创建本主窗口的线程ID
    YWGUI_ThreadInfo_T *pThreadInfo;         // 指向线程信息结构

}YWGUI_MainWin_T;

typedef YWGUI_MainWin_T* YWGUI_MainWin_P;

typedef struct YWGUI_ControlTextExtra_s
{
    S16     nCharExtra;       //字符间距
    S16     nAboveExtra;     //上间距
    S16     nBellowExtra;     //下间距
    S16     nIndent;     //下间距
}YYWGUI_ControlTextExtra_T;

typedef struct YWGUI_Control_s
{
    COMM_WINDOW_ELEMENT

    YWGUI_CaretInfo_P ptCaretInfo;
    YWGUI_ScrollBarInfo_T vscroll;   // the vertical scroll bar information.
    
    struct YWGUI_Control_s* next;// 下一个兄弟控件
    struct YWGUI_Control_s* prev;//上一个兄弟控件


    YWGUI_CtrlClassInfo_P pcci;// pointer to Control Class Info struct.
    YYWGUI_ControlTextExtra_T  stTextExtra;
}YWGUI_Control_T;

typedef YWGUI_Control_T* YWGUI_Control_P;



struct YWGUI_ThreadInfo_s
{
    YWGUI_MsgQueue_P           pMsgQueue;        /* pointer to message queue of the thread */
    YWGUI_ThreadID_T           threadId;               /* the thread id */
    YWGUI_MainWin_P            pMainWin;         //指向第一个属主窗口

    DWORD               dwState;          /* current thread status */
    YWGUI_MutexID_T     lock;             /* access lock */

    struct YWGUI_ThreadInfo_s  *next;

};

typedef YWGUI_ThreadInfo_T* YWGUI_ThreadInfo_P;

/*********************宏函数定义*************************/
//任何窗口(包括桌面窗口，主窗口，控件)
#define YWGUI_IsWindow(hWnd)        \
        (((YWGUI_HWnd_T)(hWnd)) != YWGUI_NULL_HANDLE && ((YWGUI_MainWin_P)(hWnd))->DataType == TYPE_HWND)

//除桌面窗口外的窗口(包括主窗口，控件)
#define YWGUI_IsNormalWindow(hWnd)       \
        (((YWGUI_HWnd_T)(hWnd)) != HWND_DESKTOP && YWGUI_IsWindow(hWnd))

//除桌面窗口外的主窗口
#define YWGUI_IsNormalMainWin(hWnd)  \
    (YWGUI_IsWindow(hWnd) && ((YWGUI_MainWin_P)(hWnd))->WinType == TYPE_MAINWIN)

//包括桌面窗口的主窗口
#define YWGUI_IsMainWin(hWnd)  \
    (YWGUI_IsNormalMainWin(hWnd) ||((YWGUI_HWnd_T)(hWnd)) == HWND_DESKTOP)

#define YWGUI_IsControl(hWnd) \
    (YWGUI_IsNormalWindow(hWnd) && ((YWGUI_MainWin_P)(hWnd))->WinType == TYPE_CONTROL )


#define YWGUI_GetMainWinPtr(hWnd)   ((YWGUI_MainWin_P)(hWnd))
#define YWGUI_GetCtrlPtr(hWnd)      ((YWGUI_Control_P)(hWnd))

#define YWGUI_GetWndProc(hWnd) (((YWGUI_MainWin_P)(hWnd))->pfnWindowProc)

#define YWGUI_IncludeWindowExStyle(hWnd,dwExStyleVal)  do{\
                    if(YWGUI_IsNormalWindow(hWnd))\
                    {\
                        YWGUI_GetCtrlPtr(hWnd)->dwExStyle |= (dwExStyleVal);\
                    }\
                  }while(0)

#define YWGUI_ExcludeWindowExStyle(hWnd,dwExStyleVal)   do{\
                    if(YWGUI_IsNormalWindow(hWnd))\
                    {\
                        YWGUI_GetCtrlPtr(hWnd)->dwExStyle &= ~(dwExStyleVal);\
                    }\
                  }while(0)







#define WAKE_MSGQUE(pMsgQueue)  do{\
                                        S32 sem_value=0; \
                                        YWGUI_GetSemaVal((pMsgQueue)->wait, &sem_value); \
                                        if (sem_value <= 0) \
                                            YWGUI_SemaSend(pMsgQueue->wait); \
                                      }while(0)

#if 1
    #define YWGUI_LockMsgQueue(pMsgQueue)     YWGUI_MutexWait((pMsgQueue)->lock)
    #define YWGUI_UnlockMsgQueue(pMsgQueue)   YWGUI_MutexSend((pMsgQueue)->lock) 
#else
    #define YWGUI_LockMsgQueue(pMsgQueue)   do{YWGUI_MutexWait((pMsgQueue)->lock);YWGUI_PRINT((YWGUI_TRACE_PARAM,"LockMsgQueue \n"));}while(0)
    #define YWGUI_UnlockMsgQueue(pMsgQueue)   do{YWGUI_MutexSend((pMsgQueue)->lock);YWGUI_PRINT((YWGUI_TRACE_PARAM,"UnlockMsgQueue \n"));}while(0)
#endif



/*********************函数声明*************************/

//ywgui_internals.c
extern BOOL InitThreadHash (void);
extern void DestroyThreadHash (void);


extern BOOL InitNotifyMsgBlockHeap (void);
extern  void DestroyNotifyMsgBlockHeap (void);
extern YWGUI_NotifyMsg_P MallocNotifyMsg (void);
extern void FreeNotifyMsg (YWGUI_NotifyMsg_P pNotifyMsg);

extern YWGUI_ThreadInfo_T* YWGUI_InitThreadInfo (void);
extern void YWGUI_FreeThreadInfo (YWGUI_ThreadInfo_P pThreadInfo);
extern YWGUI_ThreadInfo_T* YWGUI_GetThreadInfo (YWGUI_ThreadID_T threadId);
extern YWGUI_ThreadInfo_T* YWGUI_QueryThreadInfo (S32 index);
extern U32  YWGUI_GetUIThreadCnt(void);
extern U32 YWGUI_GetCharIndexByScanCode(U32 uScanCode);

#ifdef __cplusplus
}
#endif 

#endif

