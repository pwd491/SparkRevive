/****************************************************************************************/
//
// Copyright (C), 2005-2010, FULAN Electronics Technology Development Co., Ltd.
//
// �ļ�����		ywgui_edit.h
//
// �����ߣ�		ZDY
//
// �������ڣ�	2008/07/08
//
// �ļ�������
//
// ��ǰά���ߣ�
//
// �����£�
//
/****************************************************************************************/
#ifndef _YWGUI_EDIT_H_20080708_
#define _YWGUI_EDIT_H_20080708_

#ifdef __cplusplus
extern "C" {
#endif


//���Ŀ��
#define EDIT_CURSORWIDTH      2
//Ĭ�Ϲ����ɫ
#define EDIT_DEFAULT_CURSORCOLOR PIXEL_black;

//�ַ������м��
#define EDIT_DEFCHAREXTRA         3
#define EDIT_DEFCHAREXTRA_READONLY 0
#define EDIT_DEFABOVEEXTRA        1
#define EDIT_DEFBELOWEXTRA        1

//���������
#define EDIT_SCROLLBAR_WIDTH  24

//�б�Ĭ�Ϲ�����Thumb size
#define EDITPOSBARTHUMBSIZE   10

//�нṹ
typedef struct YWGUI_EditLine_s
{
    S32           iLineStrLen;             // ���ַ��ĸ���
    //S32           iLineHeight;             // ���ı��ĸ߶�
    BOOL          bNewLine;                // β���Ƿ��л��з�\n
    BOOL          bNeedIndent;             // �Ƿ�Ϊ������
    YWGUI_Char_T* pLineText;               // ���ı�

    //struct  YWGUI_EditLine_s * pNext;    // ��һ��
    ListNode      list;

}YWGUI_EditLine_T;
typedef YWGUI_EditLine_T* YWGUI_EditLine_P;

typedef struct YWGUI_Cursor_s
{
    S32     x;              // position of caret
    S32     y;

    S32     nWidth;         // original size of caret
    S32     nHeight;

    YWGUI_Pixel_T BgColor;  // ��걳��ɫ

    BOOL    fBlink;         // does blink?
    BOOL    fShow;          // show or hide currently.

    //YWGUI_HWnd_T    hOwner;         // the window owns the caret.
    U32     uTime;          // the blink time.
}YWGUI_Cursor_T;
typedef YWGUI_Cursor_T* YWGUI_Cursor_P;


typedef struct YWGUI_Edit_s
{
    DWORD              dwStatus;           // status

    //�����Ϣ
    S32                iCursorPos;         // ��ǰ��������ı��е�λ�� \nҲ��һ���ַ�
    S32                iCursorShowPos;     // ����ڱ༭����ʵ����ʾ��λ��
    YWGUI_Cursor_T     stCursor;           // ���
    S32                iCursorLineNO;      // ������к�

    //����Ϣ
    //YWGUI_EditLine_P   pLineHead;          // ��ͷ�ڵ�
    ListNode           stListHead;
    S32                iLineHeight;        // �и�
    S32                iTopLineNO;         // ��������
    S32                iVisibleLineCount;  // �ɼ�����
    S32                iTotalLineCount;    // ������

    S32                iTotalTextLimitLen; // ���ı����Ƴ���     \n������, -1��ʾ������
    S32                iNowTextLen;        // ��ǰ�ı�����       \n������

    YWGUI_Char_T       cPasswdChar;        // �����ַ�, Ĭ��Ϊ'*'
    //YWGUI_Char_T*      pContent;           // �༭���ı�

    BOOL               bEditStatus;        // �Ƿ�Ϊ�༭״̬, ��Enter������
    BOOL               bContChanged;       // �����Ƿ�ı�
    BOOL               bIsRightToLeftRW;   // �Ƿ���������д

    DWORD              dwAddData;

}YWGUI_Edit_T;
typedef YWGUI_Edit_T* YWGUI_Edit_P;


/**************************************
 YWGUI_EM_GETTEXTLEN
 ����:��ȡ�ı�����
 wParam:��
 lParam:��
 ����ֵ(S32):�ı�����,������\0
 **************************************/
#define YWGUI_EM_GETTEXTLEN       0x0351

/**************************************
 YWGUI_EM_SETPASSWORDCHAR
 ����:����������ʾ�ַ�
 wParam(YWGUI_Char_T):������ʾ�ַ�
 lParam:��
 ����ֵ:��
 **************************************/
#define YWGUI_EM_SETPASSWORDCHAR  0x0352

/**************************************
 YWGUI_EM_GETPASSWORDCHAR
 ����:��ȡ������ʾ�ַ�
 wParam:��
 lParam:��
 ����ֵ(YWGUI_Char_T):������ʾ�ַ�
 **************************************/
#define YWGUI_EM_GETPASSWORDCHAR  0x0353

/**************************************
 YWGUI_EM_GETMAXLIMIT
 ����:��ȡEdit���ַ�������(����\n)
 wParam:��
 lParam:��
 ����ֵ(S32):Edit���ַ�������
 **************************************/
#define YWGUI_EM_GETMAXLIMIT      0x0354

/**************************************
 YWGUI_EM_SETMAXLIMIT
 ����:����Edit���ַ�������(����\n)
 wParam(S32):���ַ�������
 lParam:��
 ����ֵ:��
 **************************************/
#define YWGUI_EM_SETMAXLIMIT      0x0355


/**************************************
 YWGUI_EM_SETEDITSTATUS
 ����:����Edit�ı༭״̬
 wParam(BOOL):FALSE��ʾ�Ǳ༭״̬,�����ʾ����༭״̬
 lParam:��
 ����ֵ(S32):-1 ����ʧ��(��ǰ���㲻�ڵ�ǰҪ���õ�Edit��), 0���óɹ�.
 ע��: ֻ�е�ǰ�����ڵ�ǰ���õ�Edit�ϲſ������óɹ�.
 **************************************/
#define YWGUI_EM_SETEDITSTATUS    0x0356

/**************************************
 YWGUI_EM_GETEDITSTATUS
 ����:��ȡEdit�ı༭״̬
 wParam:��
 lParam:��
 ����ֵ(BOOL):FALSE��ʾ�Ǳ༭״̬,�����ʾ����༭״̬
 **************************************/
#define YWGUI_EM_GETEDITSTATUS    0x0357

/**************************************
 YWGUI_EM_GETCURSORPOS
 ����:��ȡEdit�й���λ��(0Ϊ��ʼ)
 wParam:��
 lParam:��
 ����ֵ(S32):����λ��
 **************************************/
#define YWGUI_EM_GETCURSORPOS    0x0358

/**************************************
 YWGUI_EM_SETCURSORPOS
 ����:����Edit�й���λ��(0Ϊ��ʼ)
 wParam(S32):������λ��
 lParam:��
 ����ֵ:��
 **************************************/
#define YWGUI_EM_SETCURSORPOS    0x0359

/**************************************
 YWGUI_EM_PAGEUP
 ����:���Ϸ�ҳ
 wParam:��
 lParam:��
 ����ֵ:��
 **************************************/
#define YWGUI_EM_PAGEUP          0x035a

/**************************************
 YWGUI_EM_PAGEDOWN
 ����:���Ϸ�ҳ
 wParam:��
 lParam:��
 ����ֵ:��
 **************************************/
#define YWGUI_EM_PAGEDOWN        0x035b

/**************************************
 YWGUI_EM_GETTOTALLINECOUNT
 ����:��ȡ������
 wParam:��
 lParam:��
 ����ֵ(S32):����������
 **************************************/
#define YWGUI_EM_GETTOTALLINECOUNT 0x035c

/**************************************
 YWGUI_EM_TOPLINENO
 ����:��ȡ���е�����
 wParam:��
 lParam:��
 ����ֵ(S32):�������е�����(������0��ʼ����)
 **************************************/
#define YWGUI_EM_TOPLINENO        0x035d

/**************************************
 YWGUI_EM_VISIBLELINECOUNT
 ����:��ȡ�ɼ�����
 wParam:��
 lParam:��
 ����ֵ(S32):���ؿɼ�����
 **************************************/
#define YWGUI_EM_VISIBLELINECOUNT 0x035e

/**************************************
 YWGUI_EM_SCROLLPAGE
 ����:����ָ��ҳ��0��ʾ�������һҳ
 wParam:PageIndex[in] --  ��ҳ��������0��ʾ�������һҳ
 lParam:��
 ����ֵ:��
 **************************************/
#define YWGUI_EM_SCROLLPAGE        0x035f



//���ı��ṹ
typedef struct YWGUI_SEdit_s
{
    DWORD              dwStatus;           // status

    //�����Ϣ
    S32                iCursorPos;         // ��ǰ��������ı��е�λ�� \nҲ��һ���ַ�
    S32                iCursorShowPos;     // ����ڱ༭����ʵ����ʾ��λ��
    S32                iCursorFristPos;    // ��ǰ����ʾ���ĵ�һ��λ��
    YWGUI_Cursor_T     stCursor;           // ���

    S32                iLineHeight;        // �и�

    S32                iTotalTextLimitLen; // ���ı����Ƴ���     \n������
    S32                iNowTextLen;        // ��ǰ�ı�����       \n������

    YWGUI_Char_T       cPasswdChar;        // �����ַ�, Ĭ��Ϊ'*'
    //YWGUI_Char_T*      pContent;           // �༭���ı�

    BOOL               bEditStatus;        // �Ƿ�Ϊ�༭״̬, ��Enter������
    BOOL               bContChanged;       // �����Ƿ�ı�

    DWORD              dwAddData;

}YWGUI_SEdit_T;
typedef YWGUI_SEdit_T* YWGUI_SEdit_P;


/**************************************
 YWGUI_EM_GETTEXTLEN
 ����:��ȡ�ı�����
 wParam:��
 lParam:��
 ����ֵ(S32):�ı�����,������\0
 **************************************/
#define YWGUI_SEM_GETTEXTLEN       0x0351

/**************************************
 YWGUI_EM_SETPASSWORDCHAR
 ����:����������ʾ�ַ�
 wParam(YWGUI_Char_T):������ʾ�ַ�
 lParam:��
 ����ֵ:��
 **************************************/
#define YWGUI_SEM_SETPASSWORDCHAR  0x0352

/**************************************
 YWGUI_EM_GETPASSWORDCHAR
 ����:��ȡ������ʾ�ַ�
 wParam:��
 lParam:��
 ����ֵ(YWGUI_Char_T):������ʾ�ַ�
 **************************************/
#define YWGUI_SEM_GETPASSWORDCHAR  0x0353

/**************************************
 YWGUI_EM_GETMAXLIMIT
 ����:��ȡEdit���ַ�������(����\n)
 wParam:��
 lParam:��
 ����ֵ(S32):Edit���ַ�������
 **************************************/
#define YWGUI_SEM_GETMAXLIMIT      0x0354

/**************************************
 YWGUI_EM_SETMAXLIMIT
 ����:����Edit���ַ�������(����\n)
 wParam(S32):���ַ�������
 lParam:��
 ����ֵ:��
 **************************************/
#define YWGUI_SEM_SETMAXLIMIT      0x0355


/**************************************
 YWGUI_EM_SETEDITSTATUS
 ����:����Edit�ı༭״̬
 wParam(BOOL):FALSE��ʾ�Ǳ༭״̬,�����ʾ����༭״̬
 lParam:��
 ����ֵ(S32):-1 ����ʧ��(��ǰ���㲻�ڵ�ǰҪ���õ�Edit��), 0���óɹ�.
 ע��: ֻ�е�ǰ�����ڵ�ǰ���õ�Edit�ϲſ������óɹ�.
 **************************************/
#define YWGUI_SEM_SETEDITSTATUS    0x0356

/**************************************
 YWGUI_EM_GETEDITSTATUS
 ����:��ȡEdit�ı༭״̬
 wParam:��
 lParam:��
 ����ֵ(BOOL):FALSE��ʾ�Ǳ༭״̬,�����ʾ����༭״̬
 **************************************/
#define YWGUI_SEM_GETEDITSTATUS    0x0357

/**************************************
 YWGUI_EM_GETCURSORPOS
 ����:��ȡEdit�й���λ��(0Ϊ��ʼ)
 wParam:��
 lParam:��
 ����ֵ(S32):����λ��
 **************************************/
#define YWGUI_SEM_GETCURSORPOS    0x0358

/**************************************
 YWGUI_EM_SETCURSORPOS
 ����:����Edit�й���λ��(0Ϊ��ʼ)
 wParam(S32):������λ��
 lParam:��
 ����ֵ:��
 **************************************/
#define YWGUI_SEM_SETCURSORPOS    0x0359

/**************************************
 YWGUI_EM_PAGEUP
 ����:���Ϸ�ҳ
 wParam:��
 lParam:��
 ����ֵ:��
 **************************************/
#define YWGUI_SEM_PAGEUP          0x035a

/**************************************
 YWGUI_EM_PAGEDOWN
 ����:���Ϸ�ҳ
 wParam:��
 lParam:��
 ����ֵ:��
 **************************************/
#define YWGUI_SEM_PAGEDOWN        0x035b

/**************************************
 YWGUI_EM_GETTOTALLINECOUNT
 ����:��ȡ������
 wParam:��
 lParam:��
 ����ֵ(S32):����������
 **************************************/
#define YWGUI_SEM_GETTOTALLINECOUNT 0x035c

/**************************************
 YWGUI_EM_TOPLINENO
 ����:��ȡ���е�����
 wParam:��
 lParam:��
 ����ֵ(S32):�������е�����(������0��ʼ����)
 **************************************/
#define YWGUI_SEM_TOPLINENO        0x035d

/**************************************
 YWGUI_EM_VISIBLELINECOUNT
 ����:��ȡ�ɼ�����
 wParam:��
 lParam:��
 ����ֵ(S32):���ؿɼ�����
 **************************************/
#define YWGUI_SEM_VISIBLELINECOUNT 0x035e



#ifdef __cplusplus
}
#endif

#endif

