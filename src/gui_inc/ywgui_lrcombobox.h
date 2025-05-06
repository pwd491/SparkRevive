/****************************************************************************************/
//
// Copyright (C), 2005-2010, FULAN Electronics Technology Development Co., Ltd.
//
// �ļ�����		ywgui_lrcombobox.h
//
// �����ߣ�		ZDY
//
// �������ڣ�	2008/06/16
//
// �ļ�������	
//
// ��ǰά���ߣ�
//
// �����£�
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
    S32            iListVisibleCount;       //list ÿҳ������
    S32            iListCurSelRow;          //ListBox�ĵ�ǰѡ����
    S32            iListOldSelRow;          //ListBox����һѡ����
    S32            iListOffsetX;            //MoveWindow��List��Xƫ��
    S32            iListOffsetY;            //MoveWindow��List��Yƫ��

    ListNode       ItemHead;               //List��item����head
    
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
    //������۷���

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
    YWGUI_ShapeState_T* ptShape[YWGUI_LRCBEDIT_WES_STATUS_NUM];//ָ������
}YWGUI_LRCBEditShapeInfo_T;

typedef struct YWGUI_LRCombobox_AddData_s
{
    YWGUI_LRCBEditShapeInfo_T* pEditShape;
    YWGUI_Rect_T rcListBox;//�����LRCombobox�ؼ���λ�ã�����Ϊ����
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
 ����:�����
 wParam:Ϊ��
 lParam(YWGUI_LBItem_P):Ҫ�����нṹָ��
 ����ֵ:0�ɹ�, -1ʧ��
 **************************************/
#define YWGUI_LRCB_ADDSTRING         0x0351


/**************************************
 YWGUI_LRCB_DELETESTRING
 ����:ɾ��ָ����
 wParam(S32):Ҫɾ�����е�����
 lParam:��
 ����ֵ:0�ɹ�, -1ʧ��
 **************************************/
#define YWGUI_LRCB_DELETESTRING      0x0352

/**************************************
 YWGUI_LRCB_GETCURSEL
 ����:��ȡ��ǰ����������
 wParam:��
 lParam:��
 ����ֵ(S32):�б�Ľ���������, ������0��ʼ
 **************************************/
#define YWGUI_LRCB_GETCURSEL         0x0353

/**************************************
 YWGUI_LRCB_SETCURSEL
 ����:���ý���������
 wParam(S32):�½���������, ע����������0��ʼ
 lParam:��
 ����ֵ(S32):0�ɹ�, -1ʧ��
 **************************************/
#define YWGUI_LRCB_SETCURSEL         0x0354

/**************************************
 YWGUI_LRCB_GETCOUNT
 ����:��ȡ�б�����
 wParam:��
 lParam:��
 ����ֵ(S32):�б������
 **************************************/
#define YWGUI_LRCB_GETCOUNT          0x0355

/**************************************
 YWGUI_LRCB_FINDSTRING
 ����:����ָ���ַ������б��еĵ�һ��λ�õ�������(�Ǿ�ȷ����)
 wParam(S32):��ʼ���ҵ��е�����, ���Ǵӵڼ��п�ʼ����
 lParam(YWGUI_Char_T*):Ҫ���ҵ��ַ�����ָ��
 ����ֵ(S32):�ҵ��ĵ�һ���ַ������ڵ�������,���Ϊ-1��ʾ����ʧ��
 **************************************/
#define YWGUI_LRCB_FINDSTRING        0x0356

/**************************************
 YWGUI_LRCB_FINDSTRING
 ����:����ָ���ַ������б��еĵ�һ��λ�õ�������(��ȷ����,�ַ�������ҲҪһ��)
 wParam(S32):��ʼ���ҵ��е�����, ���Ǵӵڼ��п�ʼ����
 lParam(YWGUI_Char_T*):Ҫ���ҵ��ַ�����ָ��
 ����ֵ(S32):�ҵ��ĵ�һ���ַ������ڵ�������,���Ϊ-1��ʾ����ʧ��
 **************************************/
#define YWGUI_LRCB_FINDSTRINGEXACT   0x0357

/**************************************
 YWGUI_LRCB_GETLBTEXT
 ����:��ȡָ�����ı�
 wParam(S32):������, ע����������0��ʼ
 lParam(YWGUI_Char_T*):��ָ�����ı�copy��lParam��ָ�ĵ�ַ�ռ�,(�������);
                       ע��˲�������Ϊ��
 ����ֵ(S32):0��ȡ�ɹ���-1��ȡʧ��
 **************************************/
#define YWGUI_LRCB_GETLBTEXT         0x0358

/**************************************
 YWGUI_LRCB_GETLBTEXTLEN
 ����:��ȡָ�����ı�����
 wParam(S32):������, ע����������0��ʼ
 lParam:��
 ����ֵ(S32):ָ�����ı�����
 **************************************/
#define YWGUI_LRCB_GETLBTEXTLEN      0x0359


//LREdit message
/**************************************
 YWGUI_LRCB_GETTEXT
 ����:��ȡָ�����ı�����
 wParam(S32):������, ע����������0��ʼ
 lParam:��
 ����ֵ(S32):ָ�����ı�����
 **************************************/
#define YWGUI_LRCB_GETTEXT           0x035A


/**************************************
 YWGUI_LRCB_SETITEMVISIBLES
 ����:�����б�Ŀɼ�����
 wParam(S32):�б���¿ɼ���
 lParam:��
 ����ֵ(S32):0���óɹ�, -1����ʧ��
 **************************************/
#define YWGUI_LRCB_SETITEMVISIBLES   0x035B


/**************************************
 YWGUI_LRCB_SETTEXT
 ����:����Combobox���ı�
 wParam(YWGUI_Char_T*):Ҫ���õ��ı��ĵ�ַ
 lParam:��
 ����ֵ(S32):0���óɹ�, -1����ʧ��
 **************************************/
#define YWGUI_LRCB_SETTEXT           0x035C


//LRCombobox message
#if 0
/**************************************
 YWGUI_LRCB_GETCHILDREN
 ����:�����б�Ŀɼ�����
 wParam(YWGUI_HWnd_T*):����Combobox�е�Edit�ľ���ĵ�ַ
 lParam(YWGUI_HWnd_T*):����Combobox�е�Listbox�ľ���ĵ�ַ
 ����ֵ(S32):0���óɹ�, -1����ʧ��
 **************************************/
#define YWGUI_LRCB_GETCHILDREN       0x035D

/**************************************
 YWGUI_LRCB_GETEDITHWND
 ����:��ȡCombobox�е�Edit�ľ��
 wParam:��
 lParam:��
 ����ֵ(YWGUI_HWnd_T):����Combobox�е�Edit�ľ��
 **************************************/
#define YWGUI_LRCB_GETEDITHWND       0x035E


/**************************************
 YWGUI_LRCB_GETLISTBOXHWND
 ����:��ȡCombobox�е�Listbox�ľ��
 wParam:��
 lParam:��
 ����ֵ(YWGUI_HWnd_T):����Combobox�е�Listbox�ľ��
 **************************************/
 #define YWGUI_LRCB_GETLISTBOXHWND    0x035F
#endif
 
/**************************************
 YWGUI_LRCB_GETITEMSTATE
 ����:��ȡָ���е�״̬
 wParam(S32):Ҫ��ȡ���е�����
 lParam:Ϊ��
 ����ֵ(U32):0��ʾYWGUI_CBIF_NORMAL, 1��ʾYWGUI_CBIF_CHECKED, 2��ʾYWGUI_CBIF_SKIP
 **************************************/
#define YWGUI_LRCB_GETITEMSTATE                  0x0362

/**************************************
 YWGUI_LRCB_SETITEMSTATE
 ����:����ָ���е���״̬
 wParam(S32):Ҫ���õ��е�����
 lParam(U32):0��ʾYWGUI_CBIF_NORMAL, 1��ʾYWGUI_CBIF_CHECKED, 2��ʾYWGUI_CBIF_SKIP
 ����ֵ(S32):0���óɹ�����1����ʧ��
 **************************************/
#define YWGUI_LRCB_SETITEMSTATE                  0x0363

/**************************************
 YWGUI_LRCB_PAGEDOWN
 ����:���·�ҳ
 wParam:��
 lParam:��
 ����ֵ:��
 **************************************/
#define YWGUI_LRCB_PAGEDOWN                  0x0364

/**************************************
 YWGUI_LRCB_PAGEUP
 ����:���Ϸ�ҳ
 wParam:��
 lParam:��
 ����ֵ:��
 **************************************/
#define YWGUI_LRCB_PAGEUP                  0x0365


/**************************************
 YWGUI_LRCB_SETXYOFFSET
 ����:����ÿ�е�x��yƫ��
 wParam:offset
 lParam:��xƫ��?
 ����ֵ(S32):0���óɹ�����1����ʧ��
 **************************************/
#define YWGUI_LRCB_SETXYOFFSET             0x0366

/**************************************
 YWGUI_LRCB_HIDELISTDLG
 ����:����lrcombobox�ĵ����б�
 wParam:offset
 lParam:��xƫ��?
 ����ֵ(S32):0���óɹ�����1����ʧ��
 **************************************/
#define YWGUI_LRCB_HIDELISTDLG             0x0367

#ifdef __cplusplus
}
#endif 

#endif


