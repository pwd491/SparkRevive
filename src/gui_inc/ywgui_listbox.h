/****************************************************************************************/
//
// Copyright (C), 2005-2010, FULAN Electronics Technology Development Co., Ltd.
//
// �ļ�����		ywgui_listbox.h
//
// �����ߣ�		ZDY
//
// �������ڣ�	2008/06/23
//
// �ļ�������	
//
// ��ǰά���ߣ�
//
// �����£�
//
/****************************************************************************************/
#ifndef _YWGUI_LISTBOX_H_20080623_
#define _YWGUI_LISTBOX_H_20080623_

#ifdef __cplusplus
extern "C" {
#endif 

//������Ĭ�Ͽ��
#define SCROLLBARWIDTH        24
//�б�Ĭ����ʾ������
#define LBITEMVISIBLES        5

//�б�Ĭ�Ϲ�����Thumb size
#define LBPOSBARTHUMBSIZE       10

#define  LB_FIRSTCOLUMN_XOFFSET      10  // ��һ������Ĭ������ƫ�Ƶ�����

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
    YWGUI_HWnd_T hScrollWnd;            // �������ؼ����
    S32 ScrollW;                        //���������
    S32 iCurEditRowIndex;               //��ǰ�༭�е�����,��Checked״̬�ı�ʱ����
    U32 XOffset;
    U32 YOffset;
    
}YWGUI_LBData_T;
typedef YWGUI_LBData_T* YWGUI_LBData_P; 


/**************************************
 YWGUI_LB_ADDSTRING
 ����:�����
 wParam:Ϊ��
 lParam(YWGUI_LBItem_P):��Item�ṹָ��
 ����ֵ:��
 **************************************/
#define YWGUI_LB_ADDSTRING           0x0351

/**************************************
 YWGUI_LB_DELETESTRING
 ����:ɾ��ָ����
 wParam(S32):ָ��������, ע����������0��ʼ
 lParam:��
 ����ֵ(S32):0�ɹ�����1ʧ��
 **************************************/
#define YWGUI_LB_DELETESTRING        0x0352


/**************************************
 YWGUI_LB_GETCOUNT
 ����:��ȡ�б�����
 wParam:��
 lParam:��
 ����ֵ(S32):�б������
 **************************************/
#define YWGUI_LB_GETCOUNT            0x0353

/**************************************
 YWGUI_LB_GETCURSEL
 ����:��ȡ��ǰ����������
 wParam:��
 lParam:��
 ����ֵ(S32):�б�Ľ���������, ������0��ʼ
 **************************************/
#define YWGUI_LB_GETCURSEL           0x0354

/**************************************
 YWGUI_LB_GETTEXTLEN
 ����:��ȡָ�����ı�����
 wParam(S32):������, ע����������0��ʼ
 lParam:��
 ����ֵ(S32):ָ�����ı�����
 Roger: ���ص��ǲ��������������ַ�����
 **************************************/
#define YWGUI_LB_GETTEXTLEN          0x0355

/**************************************
 YWGUI_LB_GETTEXT
 ����:��ȡָ�����ı�
 wParam(S32):������, ע����������0��ʼ
 lParam(YWGUI_Char_T*):��ָ�����ı�copy��lParam��ָ�ĵ�ַ�ռ�,(�������);
                       ע��˲�������Ϊ��
 ����ֵ(S32):0��ȡ�ɹ�����1��ȡʧ��
 **************************************/
#define YWGUI_LB_GETTEXT             0x0356

/**************************************
 YWGUI_LB_SETTEXT
 ����:����ָ�����ı�
 wParam(S32):������, ע����������0��ʼ
 lParam(YWGUI_Char_T*):���ı���ָ��
 ����ֵ(S32):0���óɹ�����1����ʧ��
 **************************************/
#define YWGUI_LB_SETTEXT             0x0357

/**************************************
 YWGUI_LB_SETCURSEL
 ����:���ý���������
 wParam(S32):�½���������, ע����������0��ʼ
 lParam:��
 ����ֵ(S32):������
 **************************************/
#define YWGUI_LB_SETCURSEL           0x0358

/**************************************
 YWGUI_LB_GETITEMVISIBLES
 ����:��ȡ�б�Ŀɼ�����
 wParam:��
 lParam:��
 ����ֵ(S32):�б�Ŀɼ�����
 **************************************/
#define YWGUI_LB_GETITEMVISIBLES     0x0359

/**************************************
 YWGUI_LB_SETITEMVISIBLES
 ����:�����б�Ŀɼ�����
 wParam(S32):�б���¿ɼ���
 lParam:��
 ����ֵ(S32):0���óɹ�, -1����ʧ��
 **************************************/
#define YWGUI_LB_SETITEMVISIBLES     0x035A

/**************************************
 YWGUI_LB_SETTOPINDEX
 ����:����Ҫ��ʾ���б�Ķ�������
 wParam(S32):�б���¿ɼ���
 lParam:��
 ����ֵ(S32):0���óɹ�, -1����ʧ��
 **************************************/
//#define YWGUI_LB_SETTOPINDEX         0x035B

/**************************************
 YWGUI_LB_GETTOPINDEX
 ����:��ȡҪ��ʾ���б�Ķ�������
 wParam:�� 
 lParam:��
 ����ֵ(S32):��������, ע������Ӱ��0��ʼ.
 **************************************/
#define YWGUI_LB_GETTOPINDEX         0x035C

/**************************************
 YWGUI_LB_PAGEDOWN
 ����:���·�ҳ
 wParam:�� 
 lParam:��
 ����ֵ:��
 **************************************/
#define YWGUI_LB_PAGEDOWN            0x035D

/**************************************
 YWGUI_LB_PAGEUP
 ����:���Ϸ�ҳ
 wParam:��
 lParam:��
 ����ֵ:��
 **************************************/
#define YWGUI_LB_PAGEUP              0x035E

#if 0
/**************************************
 YWGUI_LB_SETITEMSTATUS
 ����:�����е�status
 wParam(DWORD):״̬
 lParam(S32):������
 ����ֵ(S32):0���óɹ�,-1����ʧ��, ע��:һ����������������
 **************************************/
#define YWGUI_LB_SETITEMSTATUS        0x035F
#endif


/**************************************
 YWGUI_LB_SETSELECTALL
 ����:ѡ��ָ���л�ȡ��ѡ��ָ����
 wParam:��
 lParam(BOOL):TRUE��ʾ����Ϊѡ�У������ʾȡ��ѡ��
 ����ֵ(S32):0���óɹ�����1����ʧ��
 **************************************/
#define YWGUI_LB_SETSELECTALL               0x0360


/**************************************
 YWGUI_LB_SETSELECTOTHERS
 ����:����ѡ��
 wParam:��
 lParam:��
 ����ֵ(S32):0���óɹ�����1����ʧ��
 **************************************/
#define YWGUI_LB_SETSELECTOTHERS               0x0361


/**************************************
 YWGUI_LB_GETITEMSTATE
 ����:��ȡָ���е�״̬
 wParam(S32):Ҫ��ȡ���е�����
 lParam:Ϊ��
 ����ֵ(U32):0��ʾYWGUI_LVIF_NORMAL, 1��ʾYWGUI_LVIF_CHECKED, 2��ʾYWGUI_LVIF_SKIP
 **************************************/
#define YWGUI_LB_GETITEMSTATE                  0x0362

/**************************************
 YWGUI_LB_SETITEMSTATE
 ����:����ָ���е���״̬
 wParam(S32):Ҫ���õ��е�����
 lParam(U32):0��ʾYWGUI_LBIF_NORMAL, 1��ʾYWGUI_LBIF_CHECKED, 2��ʾYWGUI_LBIF_SKIP
 ����ֵ(S32):0���óɹ�����1����ʧ��
 **************************************/
#define YWGUI_LB_SETITEMSTATE                  0x0363

/**************************************
 YWGUI_LB_GETCUREDITROWINDEX
 ����:��ȡ��ǰ�༭���е�����,��Ҫ���¼�YWGUI_LBN_SELCHANGED��,��ȡ�ı�Checked״̬���е�����
 wParam:��
 lParam:��
 ����ֵ(S32):��ǰ�༭����
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
 ����:����ÿ�е�x��yƫ��
 wParam:offset
 lParam:��xƫ��?
 ����ֵ(S32):0���óɹ�����1����ʧ��
 **************************************/
#define YWGUI_LB_SETXYOFFSET                  0x036b

#ifdef __cplusplus
}
#endif 

#endif

