/****************************************************************************************/
//
// Copyright (C), 2005-2010, FULAN Electronics Technology Development Co., Ltd.
//
// �ļ�����		ywgui_listview.h
//
// �����ߣ�		ZDY
//
// �������ڣ�	2008/06/24
//
// �ļ�������	
//
// ��ǰά���ߣ�
//
// �����£�
//
/****************************************************************************************/
#ifndef _YWGUI_LISTVIEW_H_20080624_
#define _YWGUI_LISTVIEW_H_20080624_

#include "ywgui_ext.h"

#ifdef __cplusplus
extern "C" {
#endif 


#define LV_COLW_DEF	            62  // Ĭ���п�
#define COLWIDTHMIN             10  // ��С�п�
#define SCROLLBARWIDTH          24  // ������Ĭ�Ͽ��
//�б�Ĭ�Ϲ�����Thumb size
#define LVPOSBARTHUMBSIZE         10

#define  LV_FIRSTCOLUMN_XOFFSET      4  // ��һ������Ĭ������ƫ�Ƶ�����

#define YWGUI_LV_CHECKFLAG_COLOR    (PIXEL_black)

#define YWGUI_LV_TEXTSUB        0
#define YWGUI_LV_IMAGESUB       1

#define SCANCODE_PAGEDOWN         YWGUI_SCANCODE_RIGHT
#define SCANCODE_PAGEUP           YWGUI_SCANCODE_LEFT


typedef struct YWGUI_LVSubItemData_s
{
    ListNode        list;
    DWORD           dwFlags;      // subitem flags
    //S32             nCol;       // ����Ĵ�ֱ����ֵ
    //S32             nRow;       // �����ˮƽ����ֵ

    YWGUI_Char_T    *pszInfo;   // �������������
    DWORD           image;      // �����ͼƬ //ΪYWGUI_GraphCollect_T����ָ��

} YWGUI_LVSubItemData_T;
typedef YWGUI_LVSubItemData_T *   YWGUI_LVSubItemData_P;

typedef struct YWGUI_LVItemData_s
{
    ListNode subqueue;  
    ListNode list;
    DWORD dwFlags;                           
    S32    nItem;                        //������
    //DWORD dwImage;                       //�б���ͼƬ���ɼ���ͼƬƴ�� YWGUI_Graph_T
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
    S32        iTopItemIndex;       // ����������
    S32        iVisibleCount;       // һҳ��ʾ������
    S32        nItemHeight;         // Height of the item
    //S32        bkc_selected;      // background color of the selected item
    S32        nColsCount;          // current column number
    S32        nRowsCount;          // current item number
    S32        nColCurSel;	        // current column selected.
    S32        nRowCurSel;	        // current Row selected.
    ListNode   hdrqueue;            // header list
    ListNode   itemqueue;           // item list
    //YWGUI_HWnd_T       hWnd;        // the control handle
    YWGUI_HWnd_T       hScrollWnd;  // ���������ھ��
    YWGUI_LVItemData_T rootitem;    // root item, not visible

    S32        iSortMode;           // ����ʽ
    S32        iSortColumn;         // Ҫ�����������

    S32        iCurEditRowIndex;    //��ǰ�༭�е�����,��Checked״̬�ı�ʱ����
    S32        ScrollW;             //���������

} YWGUI_LVData_T;
typedef YWGUI_LVData_T *YWGUI_LVData_P;

YWGUI_HWnd_T YWGUI_LVGetScrollHWnd(YWGUI_HWnd_T hWnd);


/*****************************ListView�ؼ���Ϣ*******************************/
/**************************************
 YWGUI_LVM_ADDCOLUMN
 ����:�����
 wParam:Ϊ��
 lParam(YWGUI_LVColumn_P):���нṹָ��
 ����ֵ:��
 **************************************/
#define YWGUI_LVM_ADDCOLUMN            0x0350

/**************************************
 YWGUI_LVM_ADDITEM
 ����:�����
 wParam(int):Ҫ������е�����
 lParam:Ϊ��
 ����ֵ(int):-1ʧ�ܣ�0�ɹ�
 **************************************/
#define YWGUI_LVM_ADDITEM              0x0351


/**************************************
 YWGUI_LVM_SETSUBITEM
 ����:���ø�������ľ�������
 wParam:Ϊ��
 lParam(YWGUI_LVSubItem_P):���нṹָ��
 ����ֵ:��
 **************************************/
#define YWGUI_LVM_SETSUBITEM           0x0352
//#define LVM_GETITEM              0xD004

/**************************************
 YWGUI_LVM_GETITEMCOUNT
 ����:�õ��б��������
 wParam:Ϊ��
 lParam:Ϊ��
 ����ֵ(S32):�б��������
 **************************************/
#define YWGUI_LVM_GETITEMCOUNT         0x0353

/**************************************
 YWGUI_LVM_GETCOLUMNWIDTH
 ����:�õ��б��ָ���е��п�
 wParam(S32):ΪҪ�õ����е�������ע��:��������0��ʼ
 lParam:Ϊ��
 ����ֵ(S32):�п�
 **************************************/
#define YWGUI_LVM_GETCOLUMNWIDTH       0x0354

/**************************************
 YWGUI_LVM_GETSUBITEMLEN
 ����:�õ��б��ָ�����е��ı�����
 wParam(S32):Ϊ������,��0��ʼ
 lParam(S32):Ϊ������,��0��ʼ
 ����ֵ(S32):��������ı�����
 **************************************/
#define YWGUI_LVM_GETSUBITEMLEN        0x0355

/**************************************
 YWGUI_LVM_GETSUBITEMTEXT
 ����:�õ��б��ָ�����е��ı�
 wParam(S32):Ϊ������,��0��ʼ
 lParam(S32):Ϊ������,��0��ʼ
 ����ֵ(YWGUI_Char_T *):��������ı�
 **************************************/
#define YWGUI_LVM_GETSUBITEMTEXT       0x0356

/**************************************
 YWGUI_LVM_SETHEADHEIGHT
 ����:�����еĸ߶�
 wParam(S32):�µĸ߶�
 lParam:Ϊ��
 ����ֵ:��
 **************************************/
#define YWGUI_LVM_SETHEADHEIGHT        0x0357

/**************************************
 YWGUI_LVM_DELITEM
 ����:ɾ��ָ����
 wParam(S32):ָ�����е�����,��0��ʼ
 lParam:Ϊ��
 ����ֵ(S32):0Ϊɾ���ɹ�, -1Ϊɾ��ʧ��
 **************************************/
#define YWGUI_LVM_DELITEM              0x0358

/**************************************
 YWGUI_LVM_DELALLITEM
 ����:ɾ��������
 wParam:Ϊ��
 lParam:Ϊ��
 ����ֵ(S32):0Ϊɾ���ɹ�, -1Ϊɾ��ʧ��
 **************************************/
#define YWGUI_LVM_DELALLITEM           0x0359

/**************************************
 YWGUI_LVM_DELCOLUMN
 ����:ɾ��ָ����
 wParam(S32):ָ����������
 lParam:Ϊ��
 ����ֵ(S32):0Ϊɾ���ɹ�, -1Ϊɾ��ʧ��
 **************************************/
#define YWGUI_LVM_DELCOLUMN            0x035a
//#define YWGUI_LVM_SELECTITEM           0xD010

/**************************************
 YWGUI_LVM_PAGEDOWN
 ����:���·�ҳ
 wParam:Ϊ��
 lParam:Ϊ��
 ����ֵ:��
 **************************************/
#define YWGUI_LVM_PAGEDOWN             0x035b

/**************************************
 YWGUI_LVM_PAGEUP
 ����:���Ϸ�ҳ
 wParam:Ϊ��
 lParam:Ϊ��
 ����ֵ:��
 **************************************/
#define YWGUI_LVM_PAGEUP               0x035c

/**************************************
 YWGUI_LVM_GETCOLUMNCOUNT
 ����:�õ��еĸ���
 wParam:Ϊ��
 lParam:Ϊ��
 ����ֵ(S32):�еĸ���
 **************************************/
#define YWGUI_LVM_GETCOLUMNCOUNT       0x035d


/**************************************
 YWGUI_LVM_SETCURSEL
 ����:���õ�ǰ������
 wParam(S32):�½���������
 lParam:Ϊ��
 ����ֵ(S32):0���óɹ�����1����ʧ��
 **************************************/
#define YWGUI_LVM_SETCURSEL            0x035e

/**************************************
 YWGUI_LVM_GETCURSEL
 ����:��ȡ��ǰ����������
 wParam:Ϊ��
 lParam:Ϊ��
 ����ֵ(S32):��ǰ����������
 **************************************/
#define YWGUI_LVM_GETCURSEL            0x035f

#if 0
/**************************************
 YWGUI_LVM_GETSELSTATE
 ����:��ȡָ����ѡ�е�״̬
 wParam(S32):Ҫ��ȡ���е�����
 lParam:Ϊ��
 ����ֵ(DWORD):YWGUI_LVIF_CHECKED��ʾ�ѱ�ѡ�У�������ʾδ��ѡ��
 **************************************/
#define YWGUI_LVM_GETSELSTATE          0x0360

/**************************************
 YWGUI_LVM_SETSEL
 ����:ѡ��ָ���л�ȡ��ѡ��ָ����
 wParam(S32):Ҫ���õ��е�����
 lParam(BOOL):TRUE��ʾ����Ϊѡ�У������ʾȡ��ѡ��
 ����ֵ(S32):0���óɹ�����1����ʧ��
 **************************************/
#define YWGUI_LVM_SETSEL               0x0361
#endif

/**************************************
 YWGUI_LVM_GETITEMSTATE
 ����:��ȡָ���е�״̬
 wParam(S32):Ҫ��ȡ���е�����
 lParam:Ϊ��
 ����ֵ(U32):0��ʾYWGUI_LVIF_NORMAL, 1��ʾYWGUI_LVIF_CHECKED, 2��ʾYWGUI_LVIF_SKIP
 **************************************/
#define YWGUI_LVM_GETITEMSTATE          0x0360

/**************************************
 YWGUI_LVM_SETITEMSTATE
 ����:����ָ���е���״̬
 wParam(S32):Ҫ���õ��е�����
 lParam(U32):0��ʾYWGUI_LVIF_NORMAL, 1��ʾYWGUI_LVIF_CHECKED, 2��ʾYWGUI_LVIF_SKIP
 ����ֵ(S32):0���óɹ�����1����ʧ��
 **************************************/
#define YWGUI_LVM_SETITEMSTATE               0x0361

/**************************************
 YWGUI_LVM_SETHOTITEMSEL
 ����:ѡ��ָ���л�ȡ��ѡ��ָ����
 wParam(S32):Ҫ���õ��е�����
 lParam(BOOL):TRUE��ʾ����Ϊѡ�У������ʾȡ��ѡ��
 ����ֵ(S32):0���óɹ�����1����ʧ��
 **************************************/
//#define YWGUI_LVM_SETHOTITEMSEL        0x0362

/**************************************
 YWGUI_LVM_SETSUBITEMSHAPE
 ����:����Subitem�����Σ�����ֻ�����䱳����ɫ
 wParam(S32):ָ����subitemλ��
 lParam(DWORD):����ָ��(YWGUI_ShapeStruct_T*)
 ����ֵ(S32):0���óɹ�����1����ʧ��
 **************************************/
#define YWGUI_LVM_SETSUBITEMSHAPE      0x0363

/**************************************
 YWGUI_LVM_SORT
 ����:���б���ƶ��н�������������
 wParam(S32):iSortMode  �����ģʽ 0 YWGUI_LVSORT_NOTSORT, 1 YWGUI_LVSORT_ASC, 2 YWGUI_LVSORT_DESC
 lParam(S32):iSortCol   Ҫ�������,��0��ʼ
 ����ֵ(S32):0���óɹ�����1����ʧ��
 **************************************/
#define YWGUI_LVM_SORT                 0x0364


/**************************************
 YWGUI_LVM_SETVISIBLECOUNT
 ����:����ListView�ؼ��ɼ������
 wParam(S32):ָ���Ŀɼ������
 lParam:Ϊ��
 ����ֵ:0���óɹ�����1����ʧ��
 **************************************/
#define YWGUI_LVM_SETVISIBLECOUNT      0x0365


/**************************************
 YWGUI_LVM_GETVISIBLECOUNT
 ����:��ȡListView�ؼ��ɼ������
 wParam:Ϊ��
 lParam:Ϊ��
 ����ֵ(S32):�ؼ������
 **************************************/
#define YWGUI_LVM_GETVISIBLECOUNT      0x0366


#if 0
/**************************************
 YWGUI_LVM_SETITEMSTATUS
 ����:�����е�status
 wParam(DWORD):״̬
 lParam(S32):������
 ����ֵ(S32):0���óɹ�,-1����ʧ��, ע��:һ����������������
 **************************************/
#define YWGUI_LVM_SETITEMSTATUS        0x0367
#endif

/**************************************
 YWGUI_LVM_SETSELECTALL
 ����:ѡ��ָ���л�ȡ��ѡ��ָ����
 wParam:��
 lParam(BOOL):TRUE��ʾ����Ϊѡ�У������ʾȡ��ѡ��
 ����ֵ(S32):0���óɹ�����1����ʧ��
 **************************************/
#define YWGUI_LVM_SETSELECTALL               0x0368


/**************************************
 YWGUI_LVM_SETSELECTOTHERS
 ����:����ѡ��
 wParam:��
 lParam:��
 ����ֵ(S32):0���óɹ�����1����ʧ��
 **************************************/
#define YWGUI_LVM_SETSELECTOTHERS               0x0369


/**************************************
 YWGUI_LVM_GETCUREDITROWINDEX
 ����:��ȡ��ǰ�༭���е�����,��Ҫ���¼�YWGUI_LVN_SELCHANGED��,��ȡ�ı�Checked״̬���е�����
 wParam:��
 lParam:��
 ����ֵ(S32):��ǰ�༭����
 **************************************/
#define YWGUI_LVM_GETCUREDITROWINDEX                 0x0372


/**************************************
 YWGUI_LVM_GETSUBITEMHAVEIMAGE
 ����:�õ��б��ָ�����е��Ƿ����ͼƬ
 wParam(S32):Ϊ������,��0��ʼ
 lParam(S32):Ϊ������,��0��ʼ
 ����ֵ(U32):1��ʾ�Ѿ�����,0��ʾ������,���ָ����Ϊ�ı����򷵻�-1
 **************************************/
#define YWGUI_LVM_GETSUBITEMHAVEIMAGE               0x0373


/**************************************
 YWGUI_LVM_GETSCROLLHWND
 ����:��ȡ�������ľ��
 wParam:��
 lParam:��
 ����ֵ(YWGUI_HWnd_T):���ع��������
 **************************************/
#define YWGUI_LVM_GETSCROLLHWND        0x0374


#ifdef __cplusplus
}
#endif 

#endif

