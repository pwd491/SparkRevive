/****************************************************************************************/
//
// Copyright (C), 2005-2010, FULAN Electronics Technology Development Co., Ltd.
//
// 文件名：	    ywgui_listtable.h
//
// 创建者：	    Eagle
//
// 创建日期：   2009/07/09
//
// 文件描述：
//
// 当前维护者：
//
// 最后更新：
//
/****************************************************************************************/

#ifndef _YWGUI_LISTTABLE_H_
#define  _YWGUI_LISTTABLE_H_

#ifdef __cplusplus
extern "C" {
#endif 


#define YWGUI_LT_THUMB_DEFSIZE     (10)

//特定控件的消息从0x0300开始定义
//其中0x0300~0x034F是内部消息
//0x0350~0x03AF 是向应用开放的消息

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

//标记管理数据
typedef struct YWGUIi_LTMarkInfo_s
{
    U32 *   pInfo;      //具体标记数据
    U16     InfoLen;    //信息长度
    U16     CurMark;    //当前标记行
    U16     MarkNum;    //标记行数量
}YWGUIi_LTMarkInfo_T;

//无效行管理数据
typedef struct YWGUIi_LTDisInfo_s
{
    U32 *   pInfo;      //具体无效数据
    U16     InfoLen;    //信息长度
    U16     CurDis;     //当前无效行
    U16     DisNum;     //无效行数量
}YWGUIi_LTDisInfo_T;

//滚动管理数据
typedef struct YWGUIi_LTRollMana_s
{
    U16     StartCnt;       //当该值等于 0 时开始滚动
    U16     CurOffset;      //当前偏移量
    U16     MaxOffset;      //最大偏移量
    U16 *   pRollLen;       //指向每列实际需要的偏移量
}YWGUIi_LTRollMana_T;

//LT管理数据
typedef struct YWGUIi_LTManageData_s
{
    YWGUI_LTAddData_T *     pLTAddData;     //指向控件附加数据
    YWGUI_LTItemInfo_T **   pLTItemInfo;    //动态二维数组的首地址,该数组用于存放每一项的信息
    YWGUI_HWnd_T            hPosBar;        //滚动条的句柄
    U16                     MaxLine;        //总行数
    U16                     CurLine;        //当前行数,当总行数为 0 的时候,该成员的值没有意义
    U16                     CurPgFstLine;   //当前页的首行,当总行数为 0 的时候,该成员的值没有意义
    U16                     LineHigh;       //行高度
    YWGUIi_LTMarkInfo_T *   pMarkInfo;      //指向标记信息,仅当有 YWGUI_LTS_MARK 风格时不为 NULL
    YWGUIi_LTDisInfo_T *    pDisInfo;       //指向无效行信息,仅当有 YWGUI_LTS_DISABLE 风格时不为 NULL
    YWGUIi_LTRollMana_T *   pRollInfo;      //指向滚动信息,仅当有 YWGUI_LTS_ROLLDISP 风格时不为 NULL
}YWGUIi_LTManageData_T;

/***********************************************************************
宏 名 称: YWGUI_Malloc2DArray
宏 功 能: 创建动态二维数组
参    数: nRow -- 数组行数, nCol -- 数组列数, ElementType -- 元素类型(如:int,float,U32...)
返 回 值: 强制类型转换后的指向动态二维数组的指针
说    明: 1.释放时调用YWGUI_Free2DArray
修改记录: 
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
