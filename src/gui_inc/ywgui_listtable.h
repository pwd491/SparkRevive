/****************************************************************************************/
//
// Copyright (C), 2005-2010, FULAN Electronics Technology Development Co., Ltd.
//
// �ļ�����	    ywgui_listtable.h
//
// �����ߣ�	    Eagle
//
// �������ڣ�   2009/07/09
//
// �ļ�������
//
// ��ǰά���ߣ�
//
// �����£�
//
/****************************************************************************************/

#ifndef _YWGUI_LISTTABLE_H_
#define  _YWGUI_LISTTABLE_H_

#ifdef __cplusplus
extern "C" {
#endif 


#define YWGUI_LT_THUMB_DEFSIZE     (10)

//�ض��ؼ�����Ϣ��0x0300��ʼ����
//����0x0300~0x034F���ڲ���Ϣ
//0x0350~0x03AF ����Ӧ�ÿ��ŵ���Ϣ

#define YWGUI_LTM_SETTOTALLINE  0x0300
#define YWGUI_LTM_SETITEMINFO   0x0301
#define YWGUI_LTM_GETTOTALLINE  0x0302
#define YWGUI_LTM_SCROLL        0x0303
#define YWGUI_LTM_SETCURLINE    0x0304
#define YWGUI_LTM_GETCURLINE    0x0305
#define YWGUI_LTM_REFRESHDATA   0x0306

//Message Code for ListTable with YWGUI_LTS_MARK style
#define YWGUI_LTM_MARKLINE      0x0307
#define YWGUI_LTM_CHECKMARK     0x0308
#define YWGUI_LTM_MARKALL       0x0309
#define YWGUI_LTM_SWITCHALLMARK 0x030a
#define YWGUI_LTM_GETFIRSTMARK  0x030b
#define YWGUI_LTM_GETNEXTMARK   0x030c
/*added by sly, 2009-7-24*/
#define YWGUI_LTM_GETLASTMARK  0x030d
#define YWGUI_LTM_GETPREVMARK   0x030e
/*end of added*/
#define YWGUI_LTM_GETTOTALMARK  0x030f

//Message Code for ListTable with YWGUI_LTS_DISABLE style
#define YWGUI_LTM_DISABLELINE   0x0310
#define YWGUI_LTM_CHECKDISABLE  0x0311
#define YWGUI_LTM_DISABLEALL    0x0312
//#define YWGUI_LTM_SWITCHALLDIS  0x0313
#define YWGUI_LTM_GETFIRSTDIS   0x0314
#define YWGUI_LTM_GETNEXTDIS    0x0315
#define YWGUI_LTM_GETTOTALDIS   0x0316

#define YWGUI_LTM_GETLINEHEIGHT 0x0317
#define YWGUI_LTM_VIEWLINENUM   0x0318

#define LUCKY_SEVEN             7//just for fun

//��ǹ�������
typedef struct YWGUIi_LTMarkInfo_s
{
    U32 *   pInfo;      //����������
    U16     InfoLen;    //��Ϣ����
    U16     CurMark;    //��ǰ�����
    U16     MarkNum;    //���������
}YWGUIi_LTMarkInfo_T;

//��Ч�й�������
typedef struct YWGUIi_LTDisInfo_s
{
    U32 *   pInfo;      //������Ч����
    U16     InfoLen;    //��Ϣ����
    U16     CurDis;     //��ǰ��Ч��
    U16     DisNum;     //��Ч������
}YWGUIi_LTDisInfo_T;

//������������
typedef struct YWGUIi_LTRollMana_s
{
    U16     StartCnt;       //����ֵ���� 0 ʱ��ʼ����
    U16     CurOffset;      //��ǰƫ����
    U16     MaxOffset;      //���ƫ����
    U16 *   pRollLen;       //ָ��ÿ��ʵ����Ҫ��ƫ����
}YWGUIi_LTRollMana_T;

//LT��������
typedef struct YWGUIi_LTManageData_s
{
    YWGUI_LTAddData_T *     pLTAddData;     //ָ��ؼ���������
    YWGUI_LTItemInfo_T **   pLTItemInfo;    //��̬��ά������׵�ַ,���������ڴ��ÿһ�����Ϣ
    YWGUI_HWnd_T            hPosBar;        //�������ľ��
    U16                     MaxLine;        //������
    U16                     CurLine;        //��ǰ����,��������Ϊ 0 ��ʱ��,�ó�Ա��ֵû������
    U16                     CurPgFstLine;   //��ǰҳ������,��������Ϊ 0 ��ʱ��,�ó�Ա��ֵû������
    U16                     LineHigh;       //�и߶�
    YWGUIi_LTMarkInfo_T *   pMarkInfo;      //ָ������Ϣ,������ YWGUI_LTS_MARK ���ʱ��Ϊ NULL
    YWGUIi_LTDisInfo_T *    pDisInfo;       //ָ����Ч����Ϣ,������ YWGUI_LTS_DISABLE ���ʱ��Ϊ NULL
    YWGUIi_LTRollMana_T *   pRollInfo;      //ָ�������Ϣ,������ YWGUI_LTS_ROLLDISP ���ʱ��Ϊ NULL
}YWGUIi_LTManageData_T;

/***********************************************************************
�� �� ��: YWGUI_Malloc2DArray
�� �� ��: ������̬��ά����
��    ��: nRow -- ��������, nCol -- ��������, ElementType -- Ԫ������(��:int,float,U32...)
�� �� ֵ: ǿ������ת�����ָ��̬��ά�����ָ��
˵    ��: 1.�ͷ�ʱ����YWGUI_Free2DArray
�޸ļ�¼: 
************************************************************************/
#define YWGUI_Malloc2DArray(nRow, nCol, ElementType) (ElementType **)YWGUI_Malloc2DSpace(nRow,nCol,sizeof(ElementType))
#define YWGUI_Copy2DArray(pDes, pSrc, nRow, nCol, ElementType) (ElementType **)YWGUI_Copy2DSpace((void **)(pDes), (void **)(pSrc), nRow, nCol, sizeof(ElementType))
#define YWGUI_Free2DArray(p2DSpace) \
{\
    YWGUI_Free2DSpace((void **)(p2DSpace));\
    p2DSpace=NULL;\
}

static void **YWGUI_Malloc2DSpace(U32 nRow, U32 nCol, U32 ElementSize);
static void YWGUI_Free2DSpace(void **p2DSpace);
//static void **YWGUI_Copy2DSpace(void **pDes, void **pSrc, U32 nRow, U32 nCol, U32 ElementSize);

#ifdef __cplusplus
}
#endif 

#endif
