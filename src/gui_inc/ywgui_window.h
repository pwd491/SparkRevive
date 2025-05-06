#ifndef _YWGUI_WINDOW_H_20080416_
#define  _YWGUI_WINDOW_H_20080416_

#ifdef __cplusplus
extern "C" {
#endif

/*********************************常数定义**************************/
enum
{
    YWGUI_PM_NOREMOVE=0,
    YWGUI_PM_REMOVE
};


//消息队列状态
#define QS_EMPTY                        0x00000000
#define QS_QUIT                         0x10000000
#define QS_SYNCMSG                      0x20000000
#define QS_NOTIFYMSG                    0x40000000
#define QS_POSTMSG                      0x80000000

#define QS_PAINT                        0x01000000



//#define QS_TIMER                      0x0000FFFF








#define DF_3DBOX_NORMAL                 0x0000
#define DF_3DBOX_PRESSED                0x0001
#define DF_3DBOX_STATEMASK              0x000F

#define DF_3DBOX_NOTFILL                0x0000
#define DF_3DBOX_FILL                   0x0010






#define RCTM_CLICK          1
#define RCTM_KEY            2
#define RCTM_MESSAGE        3
#define RCTM_SHOWCTRL       4



/*********************************宏定义***************************/


#define YWGUI_FIRSTINNERMSG                    0x0001
#define YWGUI_LASTINNERMSG                     0x00FF

//第一组内部消息:会话消息
#define YWGUI_FIRSTSESSIONMSG                    0x0001
#define YWGUI_LASTSESSIONMSG                     0x000F

#define YWGUI_MSG_STARTSESSION                   0x0001

#define YWGUI_MSG_ENDSESSION                     0x0002

//lParam--类名
#define YWGUI_MSG_GETCTRLCLASSINFO               0x0003


//lParam:指向 无效区矩形(屏幕坐标)
#define YWGUI_MSG_ERASEDESKTOP                   0x0004


/*
YWGUI_MSG_GETHMAINWNDBYID
说明:根据主窗口句柄得到窗口句柄
lParam : 主窗口ID
*/
#define YWGUI_MSG_GETHMAINWNDBYID                0x0005

//注册控件类型
//lParam : YWGUI_WndClass_P
#define YWGUI_MSG_REGISTERWNDCLASS               0x0006

//注销控件类型
//lParam : const S8* 控件类型名
#define YWGUI_MSG_UNREGISTERWNDCLASS             0x0007

//第二组内部消息:窗口管理消息(window manager)
#define YWGUI_FIRSTWNDMGRMSG                     0x0010
#define YWGUI_LASTWNDMGRMSG                      0x002F

/*
YWGUI_MSG_ADDNEWMAINWIN
wParam--指向YWGUI_MainWin_T结构 ;
lParam --保留
*/
#define YWGUI_MSG_ADDNEWMAINWIN                  0x0010

#define YWGUI_MSG_REMOVEMAINWIN                  0x0011

#define YWGUI_MSG_SHOWMAINWIN                    0x0012

#define YWGUI_MSG_HIDEMAINWIN                    0x0013

#define YWGUI_MSG_MOVETOTOPMOST                  0x0014

/*
YWGUI_MSG_NEWCTRLINSTANCE
wParam:父窗口
lParam:子窗口
*/
#define YWGUI_MSG_NEWCTRLINSTANCE                0x0015

/*
YWGUI_MSG_REMOVECTRLINSTANCE
wParam:父窗口
lParam:子窗口
*/
#define YWGUI_MSG_REMOVECTRLINSTANCE             0x0016


#define YWGUI_MSG_SHOWGLOBALCTRL                 0x0017

#define YWGUI_MSG_HIDEGLOBALCTRL                 0x0018

#define YWGUI_MSG_MOVEMAINWIN                    0x0019

#define YWGUI_MSG_ENABLEMAINWIN                  0x001A



#define YWGUI_MSG_IME_REGISTER                   0x0020

#define YWGUI_MSG_IME_UNREGISTER                 0x0021



#define YWGUI_FIRSTPOSTMSG                       0x0140
#define YWGUI_LASTPOSTMSG                        0x018F
//0x0140~0x014F 定义内部消息
/*
YWGUI_MSG_MEASURECSIZE
说明: 由窗口矩形算出客户区矩形的大小
wParam:传入窗口矩形(如果为NULL,使用窗口结构内的窗口矩形)
lParam: 未用*/
#define YWGUI_MSG_MEASURECSIZE                   0x0140

//失去焦点前消息
#define YWGUI_MSG_PREKILLFOCUS                   0x0141


//窗口扩展风格
//内部用来记录窗口状态使用: 高4位
//外部用来定义扩展风格使用: 低24位


#define YWGUI_WS_EX_MODALDISABLED         0x80000000L
#define YWGUI_WS_EX_INCLUDETITLECTRL      0x40000000L




/*********************************数据类型定义***************************/

/************************************变量声明****************************************/
extern YWGUI_HWnd_T         g_hHWndDesktop;
#define HWND_DESKTOP        (g_hHWndDesktop)

/************************************宏函数定义****************************************/





/************************************函数声明****************************************/
//ywgui_window.c

extern void YWGUI_DestroyAllChildWindows (YWGUI_HWnd_T hWnd);

extern S32 YWGUI_DefaultWindowProc (YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam, LPARAM lParam);






extern YWGUI_MainWin_P YWGUI_GetMainWndOfCtrl (YWGUI_HWnd_T hWnd);


extern YWGUI_GcrInfo_P YWGUI_GetWindowGcrRgnInfo(YWGUI_HWnd_T hWnd);
extern YWGUI_LogFont_P  YWGUI_GetWindowFont (YWGUI_HWnd_T hWnd);
extern YWGUI_Char_T*  YWGUI_GetWindowCaption (YWGUI_HWnd_T hWnd);
extern void YWGUI_GetWindowBackColor(YWGUI_HWnd_T hWnd, YWGUI_Pixel_T color);
extern void YWGUI_GetWindowForeColor(YWGUI_HWnd_T hWnd, YWGUI_Pixel_T color);
extern void YWGUI_GetWindowFrameColor(YWGUI_HWnd_T hWnd, YWGUI_Pixel_T color);
extern YWGUI_ShapeState_T *YWGUI_GetWindowShape(YWGUI_HWnd_T hWnd);



extern void  YWGUI_Draw3DThickFrameEx (YWGUI_HDc_T hdc, YWGUI_HWnd_T hWnd, S32 left, S32 top, S32 right, S32 bottom, DWORD flags, YWGUI_Pixel_T fillc);

extern YW_ErrorType_T YWGUI_InvalidateFrameRect (YWGUI_HWnd_T hWnd, const YWGUI_Rect_T* pRect);
extern YW_ErrorType_T YWGUI_EmptyInvRgn(YWGUI_HWnd_T hWnd,BOOL bClient);

extern YWGUI_HWnd_T YWGUI_GetMostActiveChildWindow(YWGUI_HWnd_T hMainWnd);

/*************************************************/
//ywgui_message.c

//判断调用者线程和窗口所附属的消息处理线程是否同一线程
extern BOOL YWGUI_BeThisThread (YWGUI_HWnd_T hWnd);

//extern BOOL YWGUI_PeekMessage (YWGUI_Msg_T *pMsg, YWGUI_HWnd_T hWnd, S32 iMsgFilterMin,
//                        S32 iMsgFilterMax, U32 uRemoveMsg);

extern BOOL  YWGUI_PeekQueuePostMessage (YWGUI_Msg_P pMsg, YWGUI_HWnd_T hWnd, S32 iMsgFilterMin,
                        S32 iMsgFilterMax, U32 uRemoveMsg);
extern YW_ErrorType_T YWGUI_ThrowAwayMessages (YWGUI_HWnd_T hWnd);
extern S32 YWGUI_DirectCallWindowProc(YWGUI_HWnd_T hWnd, S32 iMsg, WPARAM wParam, LPARAM lParam);
extern S32 YWGUI_CallWindowProc(YWGUI_HWnd_T hWnd, S32 iMsg, WPARAM wParam, LPARAM lParam);
extern void  YWGUI_CleanupThreadInfo (YWGUI_HWnd_T hWnd);

extern YWGUI_MsgQueue_P YWGUI_GetMsgQueue (YWGUI_HWnd_T hWnd);
extern YW_ErrorType_T  YWGUI_SendNotifyMessage (YWGUI_HWnd_T hWnd, S32 iMsg, WPARAM wParam, LPARAM lParam);

extern YWGUI_HWnd_T YWGUI_CheckInvalidRegionTree(YWGUI_MainWin_P pWin,S32* pMessage);
extern YWGUI_HWnd_T YWGUI_CheckInvalidRegion (YWGUI_MainWin_P pHosting,S32 *pMessage);


/*****************************************************/



#ifdef __cplusplus
}
#endif

#endif

