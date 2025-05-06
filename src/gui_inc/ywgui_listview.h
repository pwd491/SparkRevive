/****************************************************************************************/
//
// Copyright (C), 2005-2010, FULAN Electronics Technology Development Co., Ltd.
//
// 文件名：		ywgui_listview.h
//
// 创建者：		ZDY
//
// 创建日期：	2008/06/24
//
// 文件描述：	
//
// 当前维护者：
//
// 最后更新：
//
/****************************************************************************************/
#ifndef _YWGUI_LISTVIEW_H_20080624_
#define _YWGUI_LISTVIEW_H_20080624_

#include "ywgui_ext.h"

#ifdef __cplusplus
extern "C" {
#endif 


#define LV_COLW_DEF	            62  // 默认列宽
#define COLWIDTHMIN             10  // 最小列宽
#define SCROLLBARWIDTH          24  // 滚动条默认宽度
//列表默认滚动条Thumb size
#define LVPOSBARTHUMBSIZE         10

#define  LV_FIRSTCOLUMN_XOFFSET      4  // 第一列文字默认向右偏移的象素

#define YWGUI_LV_CHECKFLAG_COLOR    (PIXEL_black)

#define YWGUI_LV_TEXTSUB        0
#define YWGUI_LV_IMAGESUB       1

#define SCANCODE_PAGEDOWN         YWGUI_SCANCODE_RIGHT
#define SCANCODE_PAGEUP           YWGUI_SCANCODE_LEFT


typedef struct YWGUI_LVSubItemData_s
{
    ListNode        list;
    DWORD           dwFlags;      // subitem flags
    //S32             nCol;       // 子项的垂直索引值
    //S32             nRow;       // 子项的水平索引值

    YWGUI_Char_T    *pszInfo;   // 子项的文字内容
    DWORD           image;      // 子项的图片 //为YWGUI_GraphCollect_T类型指针

} YWGUI_LVSubItemData_T;
typedef YWGUI_LVSubItemData_T *   YWGUI_LVSubItemData_P;

typedef struct YWGUI_LVItemData_s
{
    ListNode subqueue;  
    ListNode list;
    DWORD dwFlags;                           
    S32    nItem;                        //行索引
    //DWORD dwImage;                       //行背景图片可由几张图片拼成 YWGUI_Graph_T
}YWGUI_LVItemData_T;
typedef YWGUI_LVItemData_T *YWGUI_LVItemData_P;


/* column header struct */
typedef struct YWGUI_LVHdr_s
{
    ListNode      list;
    S32           x;             // x position of the header
    S32           width;         // width of the header/column/subitem
    YWGUI_Char_T  *pTitle;       // title text of the column header
    DWORD         Image;         // image of the header
    DWORD         flags;         // header and column flags
    
} YWGUI_LVHdr_T;
typedef YWGUI_LVHdr_T *YWGUI_LVHdr_P;

// listview object struct  
typedef struct YWGUI_LVData_s
{ 
    DWORD      dwFlags;    
    S32        nHeadHeight;         // header height
    S32        nHeadWidth;          // header width
    S32        iTopItemIndex;       // 顶部行索引
    S32        iVisibleCount;       // 一页显示的行数
    S32        nItemHeight;         // Height of the item
    //S32        bkc_selected;      // background color of the selected item
    S32        nColsCount;          // current column number
    S32        nRowsCount;          // current item number
    S32        nColCurSel;	        // current column selected.
    S32        nRowCurSel;	        // current Row selected.
    ListNode   hdrqueue;            // header list
    ListNode   itemqueue;           // item list
    //YWGUI_HWnd_T       hWnd;        // the control handle
    YWGUI_HWnd_T       hScrollWnd;  // 滚动条窗口句柄
    YWGUI_LVItemData_T rootitem;    // root item, not visible

    S32        iSortMode;           // 排序方式
    S32        iSortColumn;         // 要排序的列索引

    S32        iCurEditRowIndex;    //当前编辑行的索引,在Checked状态改变时设置
    S32        ScrollW;             //滚动条宽度

} YWGUI_LVData_T;
typedef YWGUI_LVData_T *YWGUI_LVData_P;

YWGUI_HWnd_T YWGUI_LVGetScrollHWnd(YWGUI_HWnd_T hWnd);


/*****************************ListView控件消息*******************************/
/**************************************
 YWGUI_LVM_ADDCOLUMN
 功能:添加列
 wParam:为空
 lParam(YWGUI_LVColumn_P):传列结构指针
 返回值:无
 **************************************/
#define YWGUI_LVM_ADDCOLUMN            0x0350

/**************************************
 YWGUI_LVM_ADDITEM
 功能:添加行
 wParam(int):要插入的行的索引
 lParam:为空
 返回值(int):-1失败，0成功
 **************************************/
#define YWGUI_LVM_ADDITEM              0x0351


/**************************************
 YWGUI_LVM_SETSUBITEM
 功能:设置各个子项的具体数据
 wParam:为空
 lParam(YWGUI_LVSubItem_P):传行结构指针
 返回值:无
 **************************************/
#define YWGUI_LVM_SETSUBITEM           0x0352
//#define LVM_GETITEM              0xD004

/**************************************
 YWGUI_LVM_GETITEMCOUNT
 功能:得到列表的总行数
 wParam:为空
 lParam:为空
 返回值(S32):列表的总行数
 **************************************/
#define YWGUI_LVM_GETITEMCOUNT         0x0353

/**************************************
 YWGUI_LVM_GETCOLUMNWIDTH
 功能:得到列表的指定列的列宽
 wParam(S32):为要得到的列的索引，注意:列索引以0开始
 lParam:为空
 返回值(S32):列宽
 **************************************/
#define YWGUI_LVM_GETCOLUMNWIDTH       0x0354

/**************************************
 YWGUI_LVM_GETSUBITEMLEN
 功能:得到列表的指定行列的文本长度
 wParam(S32):为行索引,以0开始
 lParam(S32):为列索引,以0开始
 返回值(S32):该子项的文本长度
 **************************************/
#define YWGUI_LVM_GETSUBITEMLEN        0x0355

/**************************************
 YWGUI_LVM_GETSUBITEMTEXT
 功能:得到列表的指定行列的文本
 wParam(S32):为行索引,以0开始
 lParam(S32):为列索引,以0开始
 返回值(YWGUI_Char_T *):该子项的文本
 **************************************/
#define YWGUI_LVM_GETSUBITEMTEXT       0x0356

/**************************************
 YWGUI_LVM_SETHEADHEIGHT
 功能:设置列的高度
 wParam(S32):新的高度
 lParam:为空
 返回值:无
 **************************************/
#define YWGUI_LVM_SETHEADHEIGHT        0x0357

/**************************************
 YWGUI_LVM_DELITEM
 功能:删除指定行
 wParam(S32):指定的行的索引,以0开始
 lParam:为空
 返回值(S32):0为删除成功, -1为删除失败
 **************************************/
#define YWGUI_LVM_DELITEM              0x0358

/**************************************
 YWGUI_LVM_DELALLITEM
 功能:删除所有行
 wParam:为空
 lParam:为空
 返回值(S32):0为删除成功, -1为删除失败
 **************************************/
#define YWGUI_LVM_DELALLITEM           0x0359

/**************************************
 YWGUI_LVM_DELCOLUMN
 功能:删除指定列
 wParam(S32):指定的列索引
 lParam:为空
 返回值(S32):0为删除成功, -1为删除失败
 **************************************/
#define YWGUI_LVM_DELCOLUMN            0x035a
//#define YWGUI_LVM_SELECTITEM           0xD010

/**************************************
 YWGUI_LVM_PAGEDOWN
 功能:向下翻页
 wParam:为空
 lParam:为空
 返回值:无
 **************************************/
#define YWGUI_LVM_PAGEDOWN             0x035b

/**************************************
 YWGUI_LVM_PAGEUP
 功能:向上翻页
 wParam:为空
 lParam:为空
 返回值:无
 **************************************/
#define YWGUI_LVM_PAGEUP               0x035c

/**************************************
 YWGUI_LVM_GETCOLUMNCOUNT
 功能:得到列的个数
 wParam:为空
 lParam:为空
 返回值(S32):列的个数
 **************************************/
#define YWGUI_LVM_GETCOLUMNCOUNT       0x035d


/**************************************
 YWGUI_LVM_SETCURSEL
 功能:设置当前焦点项
 wParam(S32):新焦点项索引
 lParam:为空
 返回值(S32):0设置成功，－1设置失败
 **************************************/
#define YWGUI_LVM_SETCURSEL            0x035e

/**************************************
 YWGUI_LVM_GETCURSEL
 功能:获取当前焦点项索引
 wParam:为空
 lParam:为空
 返回值(S32):当前焦点项索引
 **************************************/
#define YWGUI_LVM_GETCURSEL            0x035f

#if 0
/**************************************
 YWGUI_LVM_GETSELSTATE
 功能:获取指定行选中的状态
 wParam(S32):要获取的行的索引
 lParam:为空
 返回值(DWORD):YWGUI_LVIF_CHECKED表示已被选中，其他表示未被选中
 **************************************/
#define YWGUI_LVM_GETSELSTATE          0x0360

/**************************************
 YWGUI_LVM_SETSEL
 功能:选中指定行或取消选中指定行
 wParam(S32):要设置的行的索引
 lParam(BOOL):TRUE表示设置为选中，否则表示取消选中
 返回值(S32):0设置成功，－1设置失败
 **************************************/
#define YWGUI_LVM_SETSEL               0x0361
#endif

/**************************************
 YWGUI_LVM_GETITEMSTATE
 功能:获取指定行的状态
 wParam(S32):要获取的行的索引
 lParam:为空
 返回值(U32):0表示YWGUI_LVIF_NORMAL, 1表示YWGUI_LVIF_CHECKED, 2表示YWGUI_LVIF_SKIP
 **************************************/
#define YWGUI_LVM_GETITEMSTATE          0x0360

/**************************************
 YWGUI_LVM_SETITEMSTATE
 功能:设置指定行的行状态
 wParam(S32):要设置的行的索引
 lParam(U32):0表示YWGUI_LVIF_NORMAL, 1表示YWGUI_LVIF_CHECKED, 2表示YWGUI_LVIF_SKIP
 返回值(S32):0设置成功，－1设置失败
 **************************************/
#define YWGUI_LVM_SETITEMSTATE               0x0361

/**************************************
 YWGUI_LVM_SETHOTITEMSEL
 功能:选中指定行或取消选中指定行
 wParam(S32):要设置的行的索引
 lParam(BOOL):TRUE表示设置为选中，否则表示取消选中
 返回值(S32):0设置成功，－1设置失败
 **************************************/
//#define YWGUI_LVM_SETHOTITEMSEL        0x0362

/**************************************
 YWGUI_LVM_SETSUBITEMSHAPE
 功能:设置Subitem的外形，这里只设置其背景颜色
 wParam(S32):指定的subitem位置
 lParam(DWORD):外形指针(YWGUI_ShapeStruct_T*)
 返回值(S32):0设置成功，－1设置失败
 **************************************/
#define YWGUI_LVM_SETSUBITEMSHAPE      0x0363

/**************************************
 YWGUI_LVM_SORT
 功能:对列表的制定列进行升降序排列
 wParam(S32):iSortMode  排序的模式 0 YWGUI_LVSORT_NOTSORT, 1 YWGUI_LVSORT_ASC, 2 YWGUI_LVSORT_DESC
 lParam(S32):iSortCol   要排序的列,以0开始
 返回值(S32):0设置成功，－1设置失败
 **************************************/
#define YWGUI_LVM_SORT                 0x0364


/**************************************
 YWGUI_LVM_SETVISIBLECOUNT
 功能:设置ListView控件可见项个数
 wParam(S32):指定的可见项个数
 lParam:为空
 返回值:0设置成功，－1设置失败
 **************************************/
#define YWGUI_LVM_SETVISIBLECOUNT      0x0365


/**************************************
 YWGUI_LVM_GETVISIBLECOUNT
 功能:获取ListView控件可见项个数
 wParam:为空
 lParam:为空
 返回值(S32):控件项个数
 **************************************/
#define YWGUI_LVM_GETVISIBLECOUNT      0x0366


#if 0
/**************************************
 YWGUI_LVM_SETITEMSTATUS
 功能:设置行的status
 wParam(DWORD):状态
 lParam(S32):行索引
 返回值(S32):0设置成功,-1设置失败, 注意:一般用于设置跳过项
 **************************************/
#define YWGUI_LVM_SETITEMSTATUS        0x0367
#endif

/**************************************
 YWGUI_LVM_SETSELECTALL
 功能:选中指定行或取消选中指定行
 wParam:空
 lParam(BOOL):TRUE表示设置为选中，否则表示取消选中
 返回值(S32):0设置成功，－1设置失败
 **************************************/
#define YWGUI_LVM_SETSELECTALL               0x0368


/**************************************
 YWGUI_LVM_SETSELECTOTHERS
 功能:反向选择
 wParam:空
 lParam:空
 返回值(S32):0设置成功，－1设置失败
 **************************************/
#define YWGUI_LVM_SETSELECTOTHERS               0x0369


/**************************************
 YWGUI_LVM_GETCUREDITROWINDEX
 功能:获取当前编辑的行的所以,主要在事件YWGUI_LVN_SELCHANGED后,获取改变Checked状态的行的索引
 wParam:空
 lParam:空
 返回值(S32):当前编辑的行
 **************************************/
#define YWGUI_LVM_GETCUREDITROWINDEX                 0x0372


/**************************************
 YWGUI_LVM_GETSUBITEMHAVEIMAGE
 功能:得到列表的指定行列的是否存在图片
 wParam(S32):为行索引,以0开始
 lParam(S32):为列索引,以0开始
 返回值(U32):1表示已经存在,0表示不存在,如果指定列为文本列则返回-1
 **************************************/
#define YWGUI_LVM_GETSUBITEMHAVEIMAGE               0x0373


/**************************************
 YWGUI_LVM_GETSCROLLHWND
 功能:获取滚动条的句柄
 wParam:空
 lParam:空
 返回值(YWGUI_HWnd_T):返回滚动条句柄
 **************************************/
#define YWGUI_LVM_GETSCROLLHWND        0x0374


#ifdef __cplusplus
}
#endif 

#endif

