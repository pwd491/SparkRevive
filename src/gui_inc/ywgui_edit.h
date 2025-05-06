/****************************************************************************************/
//
// Copyright (C), 2005-2010, FULAN Electronics Technology Development Co., Ltd.
//
// 文件名：		ywgui_edit.h
//
// 创建者：		ZDY
//
// 创建日期：	2008/07/08
//
// 文件描述：
//
// 当前维护者：
//
// 最后更新：
//
/****************************************************************************************/
#ifndef _YWGUI_EDIT_H_20080708_
#define _YWGUI_EDIT_H_20080708_

#ifdef __cplusplus
extern "C" {
#endif


//光标的宽度
#define EDIT_CURSORWIDTH      2
//默认光标颜色
#define EDIT_DEFAULT_CURSORCOLOR PIXEL_black;

//字符间距和行间距
#define EDIT_DEFCHAREXTRA         3
#define EDIT_DEFCHAREXTRA_READONLY 0
#define EDIT_DEFABOVEEXTRA        1
#define EDIT_DEFBELOWEXTRA        1

//滚动条宽度
#define EDIT_SCROLLBAR_WIDTH  24

//列表默认滚动条Thumb size
#define EDITPOSBARTHUMBSIZE   10

//行结构
typedef struct YWGUI_EditLine_s
{
    S32           iLineStrLen;             // 行字符的个数
    //S32           iLineHeight;             // 行文本的高度
    BOOL          bNewLine;                // 尾部是否有换行符\n
    BOOL          bNeedIndent;             // 是否为缩进行
    YWGUI_Char_T* pLineText;               // 行文本

    //struct  YWGUI_EditLine_s * pNext;    // 后一行
    ListNode      list;

}YWGUI_EditLine_T;
typedef YWGUI_EditLine_T* YWGUI_EditLine_P;

typedef struct YWGUI_Cursor_s
{
    S32     x;              // position of caret
    S32     y;

    S32     nWidth;         // original size of caret
    S32     nHeight;

    YWGUI_Pixel_T BgColor;  // 光标背景色

    BOOL    fBlink;         // does blink?
    BOOL    fShow;          // show or hide currently.

    //YWGUI_HWnd_T    hOwner;         // the window owns the caret.
    U32     uTime;          // the blink time.
}YWGUI_Cursor_T;
typedef YWGUI_Cursor_T* YWGUI_Cursor_P;


typedef struct YWGUI_Edit_s
{
    DWORD              dwStatus;           // status

    //光标信息
    S32                iCursorPos;         // 当前光标在总文本中的位置 \n也算一个字符
    S32                iCursorShowPos;     // 光标在编辑框中实际显示的位置
    YWGUI_Cursor_T     stCursor;           // 光标
    S32                iCursorLineNO;      // 光标行行号

    //行信息
    //YWGUI_EditLine_P   pLineHead;          // 行头节点
    ListNode           stListHead;
    S32                iLineHeight;        // 行高
    S32                iTopLineNO;         // 顶行索引
    S32                iVisibleLineCount;  // 可见行数
    S32                iTotalLineCount;    // 总行数

    S32                iTotalTextLimitLen; // 总文本限制长度     \n算在内, -1表示不限制
    S32                iNowTextLen;        // 当前文本长度       \n算在内

    YWGUI_Char_T       cPasswdChar;        // 密码字符, 默认为'*'
    //YWGUI_Char_T*      pContent;           // 编辑框文本

    BOOL               bEditStatus;        // 是否为编辑状态, 按Enter键设置
    BOOL               bContChanged;       // 内容是否改变
    BOOL               bIsRightToLeftRW;   // 是否从右向左读写

    DWORD              dwAddData;

}YWGUI_Edit_T;
typedef YWGUI_Edit_T* YWGUI_Edit_P;


/**************************************
 YWGUI_EM_GETTEXTLEN
 功能:获取文本长度
 wParam:空
 lParam:空
 返回值(S32):文本长度,不包含\0
 **************************************/
#define YWGUI_EM_GETTEXTLEN       0x0351

/**************************************
 YWGUI_EM_SETPASSWORDCHAR
 功能:设置密码显示字符
 wParam(YWGUI_Char_T):密码显示字符
 lParam:空
 返回值:无
 **************************************/
#define YWGUI_EM_SETPASSWORDCHAR  0x0352

/**************************************
 YWGUI_EM_GETPASSWORDCHAR
 功能:获取密码显示字符
 wParam:空
 lParam:空
 返回值(YWGUI_Char_T):密码显示字符
 **************************************/
#define YWGUI_EM_GETPASSWORDCHAR  0x0353

/**************************************
 YWGUI_EM_GETMAXLIMIT
 功能:获取Edit的字符限制数(包含\n)
 wParam:空
 lParam:空
 返回值(S32):Edit的字符限制数
 **************************************/
#define YWGUI_EM_GETMAXLIMIT      0x0354

/**************************************
 YWGUI_EM_SETMAXLIMIT
 功能:设置Edit的字符限制数(包含\n)
 wParam(S32):新字符限制数
 lParam:空
 返回值:无
 **************************************/
#define YWGUI_EM_SETMAXLIMIT      0x0355


/**************************************
 YWGUI_EM_SETEDITSTATUS
 功能:设置Edit的编辑状态
 wParam(BOOL):FALSE表示非编辑状态,否则表示进入编辑状态
 lParam:空
 返回值(S32):-1 设置失败(当前焦点不在当前要设置的Edit上), 0设置成功.
 注意: 只有当前焦点在当前设置的Edit上才可以设置成功.
 **************************************/
#define YWGUI_EM_SETEDITSTATUS    0x0356

/**************************************
 YWGUI_EM_GETEDITSTATUS
 功能:获取Edit的编辑状态
 wParam:空
 lParam:空
 返回值(BOOL):FALSE表示非编辑状态,否则表示进入编辑状态
 **************************************/
#define YWGUI_EM_GETEDITSTATUS    0x0357

/**************************************
 YWGUI_EM_GETCURSORPOS
 功能:获取Edit中光标的位置(0为起始)
 wParam:空
 lParam:空
 返回值(S32):光标的位置
 **************************************/
#define YWGUI_EM_GETCURSORPOS    0x0358

/**************************************
 YWGUI_EM_SETCURSORPOS
 功能:设置Edit中光标的位置(0为起始)
 wParam(S32):光标的新位置
 lParam:空
 返回值:空
 **************************************/
#define YWGUI_EM_SETCURSORPOS    0x0359

/**************************************
 YWGUI_EM_PAGEUP
 功能:向上翻页
 wParam:空
 lParam:空
 返回值:空
 **************************************/
#define YWGUI_EM_PAGEUP          0x035a

/**************************************
 YWGUI_EM_PAGEDOWN
 功能:向上翻页
 wParam:空
 lParam:空
 返回值:空
 **************************************/
#define YWGUI_EM_PAGEDOWN        0x035b

/**************************************
 YWGUI_EM_GETTOTALLINECOUNT
 功能:获取总行数
 wParam:空
 lParam:空
 返回值(S32):返回总行数
 **************************************/
#define YWGUI_EM_GETTOTALLINECOUNT 0x035c

/**************************************
 YWGUI_EM_TOPLINENO
 功能:获取首行的索引
 wParam:空
 lParam:空
 返回值(S32):返回首行的索引(索引以0开始计算)
 **************************************/
#define YWGUI_EM_TOPLINENO        0x035d

/**************************************
 YWGUI_EM_VISIBLELINECOUNT
 功能:获取可见行数
 wParam:空
 lParam:空
 返回值(S32):返回可见行数
 **************************************/
#define YWGUI_EM_VISIBLELINECOUNT 0x035e

/**************************************
 YWGUI_EM_SCROLLPAGE
 功能:翻到指定页，0表示翻到最后一页
 wParam:PageIndex[in] --  翻页的索引，0表示翻到最后一页
 lParam:空
 返回值:空
 **************************************/
#define YWGUI_EM_SCROLLPAGE        0x035f



//单文本结构
typedef struct YWGUI_SEdit_s
{
    DWORD              dwStatus;           // status

    //光标信息
    S32                iCursorPos;         // 当前光标在总文本中的位置 \n也算一个字符
    S32                iCursorShowPos;     // 光标在编辑框中实际显示的位置
    S32                iCursorFristPos;    // 当前可显示光标的第一个位置
    YWGUI_Cursor_T     stCursor;           // 光标

    S32                iLineHeight;        // 行高

    S32                iTotalTextLimitLen; // 总文本限制长度     \n算在内
    S32                iNowTextLen;        // 当前文本长度       \n算在内

    YWGUI_Char_T       cPasswdChar;        // 密码字符, 默认为'*'
    //YWGUI_Char_T*      pContent;           // 编辑框文本

    BOOL               bEditStatus;        // 是否为编辑状态, 按Enter键设置
    BOOL               bContChanged;       // 内容是否改变

    DWORD              dwAddData;

}YWGUI_SEdit_T;
typedef YWGUI_SEdit_T* YWGUI_SEdit_P;


/**************************************
 YWGUI_EM_GETTEXTLEN
 功能:获取文本长度
 wParam:空
 lParam:空
 返回值(S32):文本长度,不包含\0
 **************************************/
#define YWGUI_SEM_GETTEXTLEN       0x0351

/**************************************
 YWGUI_EM_SETPASSWORDCHAR
 功能:设置密码显示字符
 wParam(YWGUI_Char_T):密码显示字符
 lParam:空
 返回值:无
 **************************************/
#define YWGUI_SEM_SETPASSWORDCHAR  0x0352

/**************************************
 YWGUI_EM_GETPASSWORDCHAR
 功能:获取密码显示字符
 wParam:空
 lParam:空
 返回值(YWGUI_Char_T):密码显示字符
 **************************************/
#define YWGUI_SEM_GETPASSWORDCHAR  0x0353

/**************************************
 YWGUI_EM_GETMAXLIMIT
 功能:获取Edit的字符限制数(包含\n)
 wParam:空
 lParam:空
 返回值(S32):Edit的字符限制数
 **************************************/
#define YWGUI_SEM_GETMAXLIMIT      0x0354

/**************************************
 YWGUI_EM_SETMAXLIMIT
 功能:设置Edit的字符限制数(包含\n)
 wParam(S32):新字符限制数
 lParam:空
 返回值:无
 **************************************/
#define YWGUI_SEM_SETMAXLIMIT      0x0355


/**************************************
 YWGUI_EM_SETEDITSTATUS
 功能:设置Edit的编辑状态
 wParam(BOOL):FALSE表示非编辑状态,否则表示进入编辑状态
 lParam:空
 返回值(S32):-1 设置失败(当前焦点不在当前要设置的Edit上), 0设置成功.
 注意: 只有当前焦点在当前设置的Edit上才可以设置成功.
 **************************************/
#define YWGUI_SEM_SETEDITSTATUS    0x0356

/**************************************
 YWGUI_EM_GETEDITSTATUS
 功能:获取Edit的编辑状态
 wParam:空
 lParam:空
 返回值(BOOL):FALSE表示非编辑状态,否则表示进入编辑状态
 **************************************/
#define YWGUI_SEM_GETEDITSTATUS    0x0357

/**************************************
 YWGUI_EM_GETCURSORPOS
 功能:获取Edit中光标的位置(0为起始)
 wParam:空
 lParam:空
 返回值(S32):光标的位置
 **************************************/
#define YWGUI_SEM_GETCURSORPOS    0x0358

/**************************************
 YWGUI_EM_SETCURSORPOS
 功能:设置Edit中光标的位置(0为起始)
 wParam(S32):光标的新位置
 lParam:空
 返回值:空
 **************************************/
#define YWGUI_SEM_SETCURSORPOS    0x0359

/**************************************
 YWGUI_EM_PAGEUP
 功能:向上翻页
 wParam:空
 lParam:空
 返回值:空
 **************************************/
#define YWGUI_SEM_PAGEUP          0x035a

/**************************************
 YWGUI_EM_PAGEDOWN
 功能:向上翻页
 wParam:空
 lParam:空
 返回值:空
 **************************************/
#define YWGUI_SEM_PAGEDOWN        0x035b

/**************************************
 YWGUI_EM_GETTOTALLINECOUNT
 功能:获取总行数
 wParam:空
 lParam:空
 返回值(S32):返回总行数
 **************************************/
#define YWGUI_SEM_GETTOTALLINECOUNT 0x035c

/**************************************
 YWGUI_EM_TOPLINENO
 功能:获取首行的索引
 wParam:空
 lParam:空
 返回值(S32):返回首行的索引(索引以0开始计算)
 **************************************/
#define YWGUI_SEM_TOPLINENO        0x035d

/**************************************
 YWGUI_EM_VISIBLELINECOUNT
 功能:获取可见行数
 wParam:空
 lParam:空
 返回值(S32):返回可见行数
 **************************************/
#define YWGUI_SEM_VISIBLELINECOUNT 0x035e



#ifdef __cplusplus
}
#endif

#endif

