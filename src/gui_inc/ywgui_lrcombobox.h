/****************************************************************************************/
//
// Copyright (C), 2005-2010, FULAN Electronics Technology Development Co., Ltd.
//
// 文件名：		ywgui_lrcombobox.h
//
// 创建者：		ZDY
//
// 创建日期：	2008/06/16
//
// 文件描述：	
//
// 当前维护者：
//
// 最后更新：
//
/****************************************************************************************/
#ifndef _YWGUI_LRCOMBOBOX_H_20080616_
#define _YWGUI_LRCOMBOBOX_H_20080616_

#ifdef __cplusplus
extern "C" {
#endif 


typedef struct YWGUI_LRCBItemData_s
{
    DWORD   dwFlags;                        // item flags
    DWORD   dwImage;                        // item image
    YWGUI_Char_T*   pszText;                // item Text
    DWORD   dwAddData;                      // item additional data
    ListNode list;     // next item
    
}YWGUI_LRCBItemData_T;

typedef YWGUI_LRCBItemData_T* YWGUI_LRCBItemData_P; 

typedef struct YWGUI_LRCOMBOBOX_s
{
    DWORD          dwStateFlags;            //combobox state flags
    DWORD          dwLBStyle;            //combobox state flags
    YWGUI_HWnd_T   hEditControl;            //edit/static control hWnd
    YWGUI_HWnd_T   hListBoxControl;         //listbox control hWnd
    YWGUI_HWnd_T   hListDlg;                //listbox Dlg hWnd
    YWGUI_HWnd_T   hLRCB;                   //lrcb hWnd
    S32            iListItems;              //ecw
    S32            iListVisibleCount;       //list 每页的行数
    S32            iListCurSelRow;          //ListBox的当前选择行
    S32            iListOldSelRow;          //ListBox的上一选择行
    S32            iListOffsetX;            //MoveWindow后List的X偏移
    S32            iListOffsetY;            //MoveWindow后List的Y偏移

    ListNode       ItemHead;               //List的item链表head
    
    YWGUI_Rect_T   rcEdit;
    YWGUI_Rect_T   rcListBox;

    DWORD          dwAddData;              //AddData
    U32 XOffset;
    U32 YOffset;

}YWGUI_LRCOMBOBOX_T;
typedef YWGUI_LRCOMBOBOX_T* YWGUI_LRCOMBOBOX_P;

#if 0
typedef enum YWGUI_LRCBEditWesItem_e
{
    //窗口外观方案

    YWGUI_LRCBEDIT_STATUS_NORMAL=0,
    YWGUI_LRCBEDIT_STATUS_DISABLED,
    YWGUI_LRCBEDIT_STATUS_NOLIST_AFOCUS,
    YWGUI_LRCBEDIT_STATUS_LIST_AFOCUS,
    YWGUI_LRCBEDIT_STATUS_NOLIST_SFOCUS,
    YWGUI_LRCBEDIT_STATUS_LIST_SFOCUS,

    YWGUI_LRCBEDIT_WES_STATUS_NUM
}YWGUI_LRCBEditWesItem_E;

typedef struct YWGUI_LRCBEditShapeInfo_s
{
    YWGUI_ShapeState_T* ptShape[YWGUI_LRCBEDIT_WES_STATUS_NUM];//指针数组
}YWGUI_LRCBEditShapeInfo_T;

typedef struct YWGUI_LRCombobox_AddData_s
{
    YWGUI_LRCBEditShapeInfo_T* pEditShape;
    YWGUI_Rect_T rcListBox;//相对于LRCombobox控件的位置，可以为负数
    YWGUI_ShapeInfo_T* pListBoxShape;  
    YWGUI_LBAddData_T* pListboxAddData;
}YWGUI_LRCombobox_AddData_T;
typedef YWGUI_LRCombobox_AddData_T* YWGUI_LRCombobox_AddData_P;
#endif

#define IDD_LBTMP                 0x399
#define IDC_LBTMP                 0x399f

//LRListbox message
#define YWGUI_LRCB_CREATELIST     0x0350
/**************************************
 YWGUI_LRCB_ADDSTRING
 功能:添加行
 wParam:为空
 lParam(YWGUI_LBItem_P):要插入行结构指针
 返回值:0成功, -1失败
 **************************************/
#define YWGUI_LRCB_ADDSTRING         0x0351


/**************************************
 YWGUI_LRCB_DELETESTRING
 功能:删除指定行
 wParam(S32):要删除的行的索引
 lParam:空
 返回值:0成功, -1失败
 **************************************/
#define YWGUI_LRCB_DELETESTRING      0x0352

/**************************************
 YWGUI_LRCB_GETCURSEL
 功能:获取当前焦点行索引
 wParam:空
 lParam:空
 返回值(S32):列表的焦点行索引, 索引以0开始
 **************************************/
#define YWGUI_LRCB_GETCURSEL         0x0353

/**************************************
 YWGUI_LRCB_SETCURSEL
 功能:设置焦点行索引
 wParam(S32):新焦点行索引, 注意行索引以0开始
 lParam:空
 返回值(S32):0成功, -1失败
 **************************************/
#define YWGUI_LRCB_SETCURSEL         0x0354

/**************************************
 YWGUI_LRCB_GETCOUNT
 功能:获取列表行数
 wParam:空
 lParam:空
 返回值(S32):列表的行数
 **************************************/
#define YWGUI_LRCB_GETCOUNT          0x0355

/**************************************
 YWGUI_LRCB_FINDSTRING
 功能:查找指定字符串在列表中的第一个位置的行索引(非精确查找)
 wParam(S32):开始查找的行的索引, 就是从第几行开始查找
 lParam(YWGUI_Char_T*):要查找的字符串的指针
 返回值(S32):找到的第一个字符串所在的行索引,如果为-1表示查找失败
 **************************************/
#define YWGUI_LRCB_FINDSTRING        0x0356

/**************************************
 YWGUI_LRCB_FINDSTRING
 功能:查找指定字符串在列表中的第一个位置的行索引(精确查找,字符串长度也要一样)
 wParam(S32):开始查找的行的索引, 就是从第几行开始查找
 lParam(YWGUI_Char_T*):要查找的字符串的指针
 返回值(S32):找到的第一个字符串所在的行索引,如果为-1表示查找失败
 **************************************/
#define YWGUI_LRCB_FINDSTRINGEXACT   0x0357

/**************************************
 YWGUI_LRCB_GETLBTEXT
 功能:获取指定行文本
 wParam(S32):行索引, 注意行索引以0开始
 lParam(YWGUI_Char_T*):将指定行文本copy到lParam所指的地址空间,(输出参数);
                       注意此参数不可为空
 返回值(S32):0获取成功，-1获取失败
 **************************************/
#define YWGUI_LRCB_GETLBTEXT         0x0358

/**************************************
 YWGUI_LRCB_GETLBTEXTLEN
 功能:获取指定行文本长度
 wParam(S32):行索引, 注意行索引以0开始
 lParam:空
 返回值(S32):指定行文本长度
 **************************************/
#define YWGUI_LRCB_GETLBTEXTLEN      0x0359


//LREdit message
/**************************************
 YWGUI_LRCB_GETTEXT
 功能:获取指定行文本长度
 wParam(S32):行索引, 注意行索引以0开始
 lParam:空
 返回值(S32):指定行文本长度
 **************************************/
#define YWGUI_LRCB_GETTEXT           0x035A


/**************************************
 YWGUI_LRCB_SETITEMVISIBLES
 功能:设置列表的可见项数
 wParam(S32):列表的新可见数
 lParam:空
 返回值(S32):0设置成功, -1设置失败
 **************************************/
#define YWGUI_LRCB_SETITEMVISIBLES   0x035B


/**************************************
 YWGUI_LRCB_SETTEXT
 功能:设置Combobox的文本
 wParam(YWGUI_Char_T*):要设置的文本的地址
 lParam:空
 返回值(S32):0设置成功, -1设置失败
 **************************************/
#define YWGUI_LRCB_SETTEXT           0x035C


//LRCombobox message
#if 0
/**************************************
 YWGUI_LRCB_GETCHILDREN
 功能:设置列表的可见项数
 wParam(YWGUI_HWnd_T*):传出Combobox中的Edit的句柄的地址
 lParam(YWGUI_HWnd_T*):传出Combobox中的Listbox的句柄的地址
 返回值(S32):0设置成功, -1设置失败
 **************************************/
#define YWGUI_LRCB_GETCHILDREN       0x035D

/**************************************
 YWGUI_LRCB_GETEDITHWND
 功能:获取Combobox中的Edit的句柄
 wParam:空
 lParam:空
 返回值(YWGUI_HWnd_T):返回Combobox中的Edit的句柄
 **************************************/
#define YWGUI_LRCB_GETEDITHWND       0x035E


/**************************************
 YWGUI_LRCB_GETLISTBOXHWND
 功能:获取Combobox中的Listbox的句柄
 wParam:空
 lParam:空
 返回值(YWGUI_HWnd_T):返回Combobox中的Listbox的句柄
 **************************************/
 #define YWGUI_LRCB_GETLISTBOXHWND    0x035F
#endif
 
/**************************************
 YWGUI_LRCB_GETITEMSTATE
 功能:获取指定行的状态
 wParam(S32):要获取的行的索引
 lParam:为空
 返回值(U32):0表示YWGUI_CBIF_NORMAL, 1表示YWGUI_CBIF_CHECKED, 2表示YWGUI_CBIF_SKIP
 **************************************/
#define YWGUI_LRCB_GETITEMSTATE                  0x0362

/**************************************
 YWGUI_LRCB_SETITEMSTATE
 功能:设置指定行的行状态
 wParam(S32):要设置的行的索引
 lParam(U32):0表示YWGUI_CBIF_NORMAL, 1表示YWGUI_CBIF_CHECKED, 2表示YWGUI_CBIF_SKIP
 返回值(S32):0设置成功，－1设置失败
 **************************************/
#define YWGUI_LRCB_SETITEMSTATE                  0x0363

/**************************************
 YWGUI_LRCB_PAGEDOWN
 功能:向下翻页
 wParam:空
 lParam:空
 返回值:无
 **************************************/
#define YWGUI_LRCB_PAGEDOWN                  0x0364

/**************************************
 YWGUI_LRCB_PAGEUP
 功能:向上翻页
 wParam:空
 lParam:空
 返回值:无
 **************************************/
#define YWGUI_LRCB_PAGEUP                  0x0365


/**************************************
 YWGUI_LRCB_SETXYOFFSET
 功能:设置每行的x和y偏移
 wParam:offset
 lParam:是x偏移?
 返回值(S32):0设置成功，－1设置失败
 **************************************/
#define YWGUI_LRCB_SETXYOFFSET             0x0366

/**************************************
 YWGUI_LRCB_HIDELISTDLG
 功能:隐藏lrcombobox的弹出列表
 wParam:offset
 lParam:是x偏移?
 返回值(S32):0设置成功，－1设置失败
 **************************************/
#define YWGUI_LRCB_HIDELISTDLG             0x0367

#ifdef __cplusplus
}
#endif 

#endif


