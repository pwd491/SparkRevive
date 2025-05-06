/****************************************************************************************/
//
// Copyright (C), 2005-2010, FULAN Electronics Technology Development Co., Ltd.
//
// 文件名：		ywgui_listbox.h
//
// 创建者：		ZDY
//
// 创建日期：	2008/06/23
//
// 文件描述：	
//
// 当前维护者：
//
// 最后更新：
//
/****************************************************************************************/
#ifndef _YWGUI_LISTBOX_H_20080623_
#define _YWGUI_LISTBOX_H_20080623_

#ifdef __cplusplus
extern "C" {
#endif 

//滚动条默认宽度
#define SCROLLBARWIDTH        24
//列表默认显示的行数
#define LBITEMVISIBLES        5

//列表默认滚动条Thumb size
#define LBPOSBARTHUMBSIZE       10

#define  LB_FIRSTCOLUMN_XOFFSET      10  // 第一列文字默认向右偏移的象素

typedef struct YWGUI_LBItemData_s
{
    DWORD   dwFlags;                        // item flags
    DWORD   dwImage;                        // item image
    YWGUI_Char_T*   pszText;                        // item Text
    DWORD   dwAddData;                      // item additional data
    struct  YWGUI_LBItemData_s *next;       // next item
    
}YWGUI_LBItemData_T;
typedef YWGUI_LBItemData_T* YWGUI_LBItemData_P; 


typedef struct YWGUI_LBData_s
{
    DWORD dwFlags;                      // listbox flags
    S32 itemCount;                      // items count
    S32 itemTop;                        // start display item
    S32 itemVisibles;                   // number of visible items
    S32 itemHilighted;                  // current hilighted item
    S32 itemHeight;                     // item height
    YWGUI_LBItemData_P pHead;           // items linked list head
    YWGUI_LBItemData_P pFreeItem;       // items linked list head
    //YWGUI_SBPolicyType_e sbPolicy;    // scrollbar policy type
    YWGUI_HWnd_T hScrollWnd;            // 滚动条控件句柄
    S32 ScrollW;                        //滚动条宽度
    S32 iCurEditRowIndex;               //当前编辑行的索引,在Checked状态改变时设置
    U32 XOffset;
    U32 YOffset;
    
}YWGUI_LBData_T;
typedef YWGUI_LBData_T* YWGUI_LBData_P; 


/**************************************
 YWGUI_LB_ADDSTRING
 功能:添加行
 wParam:为空
 lParam(YWGUI_LBItem_P):传Item结构指针
 返回值:无
 **************************************/
#define YWGUI_LB_ADDSTRING           0x0351

/**************************************
 YWGUI_LB_DELETESTRING
 功能:删除指定行
 wParam(S32):指定行索引, 注意行索引以0开始
 lParam:空
 返回值(S32):0成功，－1失败
 **************************************/
#define YWGUI_LB_DELETESTRING        0x0352


/**************************************
 YWGUI_LB_GETCOUNT
 功能:获取列表行数
 wParam:空
 lParam:空
 返回值(S32):列表的行数
 **************************************/
#define YWGUI_LB_GETCOUNT            0x0353

/**************************************
 YWGUI_LB_GETCURSEL
 功能:获取当前焦点行索引
 wParam:空
 lParam:空
 返回值(S32):列表的焦点行索引, 索引以0开始
 **************************************/
#define YWGUI_LB_GETCURSEL           0x0354

/**************************************
 YWGUI_LB_GETTEXTLEN
 功能:获取指定行文本长度
 wParam(S32):行索引, 注意行索引以0开始
 lParam:空
 返回值(S32):指定行文本长度
 Roger: 返回的是不包括结束符的字符个数
 **************************************/
#define YWGUI_LB_GETTEXTLEN          0x0355

/**************************************
 YWGUI_LB_GETTEXT
 功能:获取指定行文本
 wParam(S32):行索引, 注意行索引以0开始
 lParam(YWGUI_Char_T*):将指定行文本copy到lParam所指的地址空间,(输出参数);
                       注意此参数不可为空
 返回值(S32):0获取成功，－1获取失败
 **************************************/
#define YWGUI_LB_GETTEXT             0x0356

/**************************************
 YWGUI_LB_SETTEXT
 功能:设置指定行文本
 wParam(S32):行索引, 注意行索引以0开始
 lParam(YWGUI_Char_T*):新文本的指针
 返回值(S32):0设置成功，－1设置失败
 **************************************/
#define YWGUI_LB_SETTEXT             0x0357

/**************************************
 YWGUI_LB_SETCURSEL
 功能:设置焦点行索引
 wParam(S32):新焦点行索引, 注意行索引以0开始
 lParam:空
 返回值(S32):老索引
 **************************************/
#define YWGUI_LB_SETCURSEL           0x0358

/**************************************
 YWGUI_LB_GETITEMVISIBLES
 功能:获取列表的可见项数
 wParam:空
 lParam:空
 返回值(S32):列表的可见项数
 **************************************/
#define YWGUI_LB_GETITEMVISIBLES     0x0359

/**************************************
 YWGUI_LB_SETITEMVISIBLES
 功能:设置列表的可见项数
 wParam(S32):列表的新可见数
 lParam:空
 返回值(S32):0设置成功, -1设置失败
 **************************************/
#define YWGUI_LB_SETITEMVISIBLES     0x035A

/**************************************
 YWGUI_LB_SETTOPINDEX
 功能:设置要显示的列表的顶行索引
 wParam(S32):列表的新可见数
 lParam:空
 返回值(S32):0设置成功, -1设置失败
 **************************************/
//#define YWGUI_LB_SETTOPINDEX         0x035B

/**************************************
 YWGUI_LB_GETTOPINDEX
 功能:获取要显示的列表的顶行索引
 wParam:空 
 lParam:空
 返回值(S32):顶行索引, 注意行缩影以0开始.
 **************************************/
#define YWGUI_LB_GETTOPINDEX         0x035C

/**************************************
 YWGUI_LB_PAGEDOWN
 功能:向下翻页
 wParam:空 
 lParam:空
 返回值:无
 **************************************/
#define YWGUI_LB_PAGEDOWN            0x035D

/**************************************
 YWGUI_LB_PAGEUP
 功能:向上翻页
 wParam:空
 lParam:空
 返回值:无
 **************************************/
#define YWGUI_LB_PAGEUP              0x035E

#if 0
/**************************************
 YWGUI_LB_SETITEMSTATUS
 功能:设置行的status
 wParam(DWORD):状态
 lParam(S32):行索引
 返回值(S32):0设置成功,-1设置失败, 注意:一般用于设置跳过项
 **************************************/
#define YWGUI_LB_SETITEMSTATUS        0x035F
#endif


/**************************************
 YWGUI_LB_SETSELECTALL
 功能:选中指定行或取消选中指定行
 wParam:空
 lParam(BOOL):TRUE表示设置为选中，否则表示取消选中
 返回值(S32):0设置成功，－1设置失败
 **************************************/
#define YWGUI_LB_SETSELECTALL               0x0360


/**************************************
 YWGUI_LB_SETSELECTOTHERS
 功能:反向选择
 wParam:空
 lParam:空
 返回值(S32):0设置成功，－1设置失败
 **************************************/
#define YWGUI_LB_SETSELECTOTHERS               0x0361


/**************************************
 YWGUI_LB_GETITEMSTATE
 功能:获取指定行的状态
 wParam(S32):要获取的行的索引
 lParam:为空
 返回值(U32):0表示YWGUI_LVIF_NORMAL, 1表示YWGUI_LVIF_CHECKED, 2表示YWGUI_LVIF_SKIP
 **************************************/
#define YWGUI_LB_GETITEMSTATE                  0x0362

/**************************************
 YWGUI_LB_SETITEMSTATE
 功能:设置指定行的行状态
 wParam(S32):要设置的行的索引
 lParam(U32):0表示YWGUI_LBIF_NORMAL, 1表示YWGUI_LBIF_CHECKED, 2表示YWGUI_LBIF_SKIP
 返回值(S32):0设置成功，－1设置失败
 **************************************/
#define YWGUI_LB_SETITEMSTATE                  0x0363

/**************************************
 YWGUI_LB_GETCUREDITROWINDEX
 功能:获取当前编辑的行的所以,主要在事件YWGUI_LBN_SELCHANGED后,获取改变Checked状态的行的索引
 wParam:空
 lParam:空
 返回值(S32):当前编辑的行
 **************************************/
#define YWGUI_LB_GETCUREDITROWINDEX            0x0364


#define YWGUI_LB_GETITEMHEIGHT       0x0365
#define YWGUI_LB_GETITEMRECT         0x0366
#define YWGUI_LB_FINDSTRING          0x0367
#define YWGUI_LB_FINDSTRINGEXACT     0x0368
#define YWGUI_LRCB_GETITEMHEIGHT     0x0369
#define YWGUI_LRCB_SETITEMHEIGHT     0x036a

/**************************************
 YWGUI_LB_SETXYOFFSET
 功能:设置每行的x和y偏移
 wParam:offset
 lParam:是x偏移?
 返回值(S32):0设置成功，－1设置失败
 **************************************/
#define YWGUI_LB_SETXYOFFSET                  0x036b

#ifdef __cplusplus
}
#endif 

#endif

