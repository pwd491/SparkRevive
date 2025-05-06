#ifndef _YWGUI_EXT_H_20080416_
#define  _YWGUI_EXT_H_20080416_

/*******************************************************************************
**********************************编译开关*************************************
*******************************************************************************/

#ifndef YWGUI_WITHIN
//ywgui外部

#endif

#define _YWGUI_WCHAR_DEF_                    1

/*******************************************************************************
***********************************平台差异*************************************
*******************************************************************************/

#ifdef WIN32
    //win32平台
    #define _YWGUI_CHECK_MEM_LEAK_
    #ifdef _YWGUI_CHECK_MEM_LEAK_
    #define _CRTDBG_MAP_ALLOC
    #include<stdlib.h>
    #include<crtdbg.h>
    #else
    #include<stdlib.h>
    #endif
    #include <stdio.h>
    #include <memory.h>
    #include <assert.h>
    #include <string.h>

    #define YWMID_MODULE_GUI_ID          613
    #define YW_MODULE_SET_ID(a)          ((a) << 16)
    #define YW_NO_ERROR                  0
    #define TRUE                         1
    #define FALSE                        0

    typedef     signed char              S8;
    typedef     unsigned char            U8;
    typedef     signed short             S16;
    typedef     unsigned short           U16;
    typedef     signed int               S32;
    typedef     unsigned int             U32;
    typedef     U32                      BOOL;
    typedef     U32                      DWORD;
    typedef     U32                      WPARAM;
    typedef     U32                      LPARAM;
    typedef     U32                      YW_ErrorType_T;

    #if _YWGUI_WCHAR_DEF_
        //宽字符
        typedef wchar_t            YWGUI_Char_T;
    #else
        typedef char               YWGUI_Char_T;
    #endif

    #if (defined _YWGUI_CHECK_MEM_LEAK_ && defined  _DEBUG)
        #define  YWGUI_MEMLEAK_OUTPUT()  \
                        do{ \
                        _CrtDumpMemoryLeaks(); \
                       }while(0)

    #else
        #define  YWGUI_MEMLEAK_OUTPUT()
    #endif

    #ifdef YWGUI_WITHIN
        #define YWGUI_API  __declspec(dllexport)
    #else
        #define YWGUI_API  __declspec(dllimport)
    #endif
#else
    #include "ywdefs.h"
//    #define YWMID_MODULE_GUI_ID           613
    typedef     U32                       DWORD;
    typedef     U32                       WPARAM;
    typedef     U32                       LPARAM;

    #if _YWGUI_WCHAR_DEF_
        //宽字符
        //typedef S16            YWGUI_Char_T;
        typedef U16            YWGUI_Char_T;
    #else
        typedef S8               YWGUI_Char_T;
    #endif

    #define YWGUI_MEMLEAK_OUTPUT()
    #define YWGUI_API
#endif
#include "ywmid.h"


#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
***********************************句柄定义*************************************
*******************************************************************************/


typedef     U32                     YWGUI_HWnd_T;
typedef     U32                     YWGUI_HDc_T;
//typedef     U32                     YWGUI_HBitmap_T;
typedef     U32                     YWGUI_HGraphCell_T;
typedef     U32                     YWGUI_Handle_T;
typedef     U32                     YWGUI_HFont_T;


/*******************************************************************************
***************************简单数据类型定义*************************************
*******************************************************************************/

typedef U32                  YWGUI_Size_T;

typedef U8                  YWGUI_Pixel_T[4];

//函数指针类型
typedef  void (*YWGUI_InitDlgTLinkFunc_P)(void);

typedef  YWGUI_Char_T *(*YWGUI_LoadStringFunc_P)(S32);


typedef  void (*YWGUI_ModifyDefScheFunc_P)(void);

typedef  void (*YWGUI_ModifyCtrlDefScheFunc_P)(void);


typedef  S32 (*YWGUI_WindowProc_P)(YWGUI_HWnd_T, S32, WPARAM, LPARAM);

typedef void (*YWGUI_KeyPreProcess_P)(U32 *, U32*); /*added by sly, 2009-6-8, 按键预处理函数*/
//枚举类型

enum
{
    //YWGUI 错误类型定义
    YWGUI_ERROR =YW_MODULE_SET_ID (YWMID_MODULE_GUI_ID ) ,
    YWGUI_ERROR_INVALID_HANDLE,/*无效句柄*/
    YWGUI_ERROR_BAD_PARAMETER, /*非法参数*/
    YWGUI_ERROR_LAWLESS_CALL,  /*非法调用*/
    YWGUI_ERROR_BUF_FULL,      /*缓存已满*/
    YWGUI_ERROR_MEM_NO_ENOUGH, /*内存不够*/
    YWGUI_ERROR_RES_NO_ENOUGH, /*资源不够*/
    YWGUI_ERROR_CHECK,          /*校验错误*/
    YWGUI_ERROR_TERMINATE,      /*强制终止操作*/
    YWGUI_ERROR_NO_USE,         /*未使用*/
    YWGUI_ERROR_NO_SUPPORTED,   /*不支持*/
    YWGUI_ERROR_NOT_FOUND       /*没有找到*/
};

enum
{
    YWGUI_ALPHA_MODE_GLOBAL=0,
    YWGUI_ALPHA_MODE_LOCAL
};



typedef  enum YWGUI_RemoteProtocol_e
{
    YWGUI_PROTOCOL_NONE                       = 0,
    YWGUI_PROTOCOL_NEC                        = ( 1 << 0 ),        /* NEC协议 */
    YWGUI_PROTOCOL_PHILIPS_RC6                = ( 1 << 1 ),        /* Philips_RC6协议*/
    YWGUI_PROTOCOL_PHILIPS_RC5                = ( 1 << 2 ),        /* Philips_RC6协议*/
    YWGUI_PROTOCOL_PHILIPS                    = ( 1 << 3 ),        /* Philips协议 */
    YWGUI_PROTOCOL_USEDEFINE_YW_C03F          = ( 1 << 4 ),
    YWGUI_PROTOCOL_USEDEFINE_YW_40BD          = ( 1 << 5 ),
    YWGUI_PROTOCOL_USEDEFINE_YW_807F          = ( 1 << 6 ),
    YWGUI_PROTOCOL_USEDEFINE_YW_0202          = ( 1 << 7 )
}YWGUI_RemoteProtocol_E;


typedef enum YWGUI_FrameType_e
{
    //边框类型

    FRAME_NO,     //无边框
    FRAME_RECT,   //矩形边框
    FRAME_GRAPH   //图形边框
}YWGUI_FrameType_E;

typedef enum YWGUI_SpellType_e
{
    //图形拼凑类型

    SPELL_GRAPH,          //一张图
    SPELL_GRAPH_REPEAT_H, //一张图反复横向拼凑
    SPELL_GRAPH_REPEAT_V, //一张图反复纵向拼凑
    SPELL_GRAPH_REPEAT_HV, //一张图反复横向纵向拼凑
    SPELL_3GRAPH_H,       //三张图横向拼凑(左中右,中间横向循环)
    SPELL_3GRAPH_V,       //三张图纵向拼凑(上中下,中间纵向循环)
    SPELL_5GRAPH_H,       //五张图横向拼凑(左、次左、中、次右、右，中间横向循环)
    SPELL_5GRAPH_V,       //五张图纵向拼凑(上、次上、中、次下、下，中间纵向循环)
    SPELL_8GRAPH,		  //8张图拼凑(左上角,上边(横向循环),右上角,左边(纵向循环),右边(纵向循环),左下角,下边(横向循环),右下角)
    SPELL_16GRAPH,        //16张图拼凑(与8张图拼凑比较，每条边可由3张图构成，最中间的那张图片循环)
    SPELL_24GRAPH         //24张图拼凑(与8张图拼凑比较，每条边可由5张图构成，最中间的那张图片循环)
}YWGUI_SpellType_E;


typedef enum YWGUI_DcAttr_e
{
    //YWGUI_GetDCAttr / YWGUI_SetDCAttr 参数使用

   DC_ATTR_BK_COLOR=0,
   DC_ATTR_BK_MODE,
   DC_ATTR_PEN_COLOR,
   DC_ATTR_BRUSH_COLOR,
   DC_ATTR_PEN_WIDTH,
   DC_ATTR_TEXT_COLOR,
   DC_ATTR_CHAR_EXTRA,
   DC_ATTR_ALINE_EXTRA,
   DC_ATTR_BLINE_EXTRA,
   DC_ATTR_OP_MODE      /*added by sly for canvas op mode, 2009-11-5*/
}YWGUI_DcAttr_E;

typedef enum YWGUI_WecItem_e
{
    //窗口颜色方案

    YWGUI_DESKTOP_BGCOLOR=0,//桌面背景色

    //主窗口(normal)
    YWGUI_MAINWND_BGC ,     //背景色
    YWGUI_MAINWND_FGC,      //前景色
    YWGUI_MAINWND_FRAMEC,   //边框色

    //主窗口(disable)
    YWGUI_MAINWND_DISABLE_BGC ,     //背景色
    YWGUI_MAINWND_DISABLE_FGC,      //前景色
    YWGUI_MAINWND_DISABLE_FRAMEC,   //边框色

    //主窗口(focus)
    YWGUI_MAINWND_FOCUS_BGC ,       //背景色
    YWGUI_MAINWND_FOCUS_FGC,        //前景色
    YWGUI_MAINWND_FOCUS_FRAMEC,     //边框色

    //控件(normal)
    YWGUI_NORMAL_CTRL_BGC,          //背景色
    YWGUI_NORMAL_CTRL_FGC,          //前景色(文本颜色)
    YWGUI_NORMAL_CTRL_FRAMEC,       //边框色

    //控件(disable)
    YWGUI_DISABLE_CTRL_BGC,
    YWGUI_DISABLE_CTRL_FGC,
    YWGUI_DISABLE_CTRL_FRAMEC ,

    //控件(active focus)
    YWGUI_AFOCUS_CTRL_BGC,
    YWGUI_AFOCUS_CTRL_FGC,
    YWGUI_AFOCUS_CTRL_FRAMEC,

    //控件(sleep focus)
    YWGUI_SFOCUS_CTRL_BGC,
    YWGUI_SFOCUS_CTRL_FGC,
    YWGUI_SFOCUS_CTRL_FRAMEC,


    YWGUI_3DBOX_NORMALC,
    YWGUI_3DBOX_REVERSEC,
    YWGUI_3DBOX_LIGHTC,
    YWGUI_3DBOX_DARKC,

    YWGUI_WEC_SCEME_ITEM_NUM
}YWGUI_WecItem_E;

typedef enum YWGUI_WemItem_e
{
    //窗口线条方案
    YWGUI_WEM_BORDER_WIDTH,
    YWGUI_WEM_THICKFRAME_WIDTH,
    YWGUI_WEM_THINFRAME_WIDTH,
    YWGUI_WEM_BAR_BORDER, // 横向 posbar 头端的宽度 或 纵向 posbar 头端的高度

    YWGUI_WEM_SCEME_ITEM_NUM
}YWGUI_WemItem_E;

typedef enum YWGUI_WesItem_e
{
    //窗口外观方案

    YWGUI_STATUS_NORMAL=0,
    YWGUI_STATUS_DISABLED,
    YWGUI_STATUS_AFOCUS,
    YWGUI_STATUS_SFOCUS,

    YWGUI_WES_STATUS_NUM
}YWGUI_WesItem_E;

typedef enum YWGUI_BkMode_e
{
    //YWGUI_SetBkMode 参数使用

    YWGUI_BM_OPAQUE = 0,     //不透明
    YWGUI_BM_TRANSPARENT      //透明
}YWGUI_BkMode_E;

typedef enum YWGUI_PixelType_e
{
    YWGUI_PIXEL_TYPE_INVALID=0,
    YWGUI_PIXEL_TYPE_RGB888,
    YWGUI_PIXEL_TYPE_BGR888,
    YWGUI_PIXEL_TYPE_BGRA8888,
    YWGUI_PIXEL_TYPE_BGRA5551, //16bit
    YWGUI_PIXEL_TYPE_BGRA4444, //16bit
    YWGUI_PIXEL_TYPE_BGR565,     //16bit
    YWGUI_PIXEL_TYPE_MAX
} YWGUI_PixelType_E;

typedef enum YWGUI_ImeType_e
{
    YWGUI_IME_TYPE_INVALID=0,
    YWGUI_IME_TYPE_DIRECT,   //直接输入
    YWGUI_IME_TYPE_REUSE     //按键复用输入
}YWGUI_ImeType_E;

typedef enum YWGUI_ImeEvent_e
{
    YWGUI_IME_EVENT_BACKSPACE =0
}YWGUI_ImeEvent_E;

/*added by sly, 2009-11-3*/
typedef enum YWGUI_CANVAS_OpMode_e
{
    YWGUI_CANVAS_OP_MODE_NORMAL             = (1 << 0), /* src*/
    YWGUI_CANVAS_OP_MODE_XOR                = (1 << 1), /* src ^ dst*/
    YWGUI_CANVAS_OP_MODE_TRANS            = (1 << 2), /* dst*/
    YWGUI_CANVAS_OP_MODE_COPY            = (1 << 3), /* src*/
    YWGUI_CANVAS_OP_MODE_OR                = (1 << 4), /* src | dst*/
    YWGUI_CANVAS_OP_MODE_AND                = (1 << 5), /* src & dst*/
    YWGUI_CANVAS_OP_MODE_CLEAR            = (1 << 6), /* 0*/
    YWGUI_CANVAS_OP_MODE_SET                = (1 << 7), /* 11111111*/
    YWGUI_CANVAS_OP_MODE_EQUIV            = (1 << 8), /* ~(src ^ dst)*/
    YWGUI_CANVAS_OP_MODE_NOR                = (1 << 9), /* ~(src | dst)*/
    YWGUI_CANVAS_OP_MODE_NAND            = (1 << 10), /* ~(src & dst)*/
    YWGUI_CANVAS_OP_MODE_INVERT            = (1 << 11), /* ~dst*/
    YWGUI_CANVAS_OP_MODE_COPYINVERTED    = (1 << 12), /* ~src*/
    YWGUI_CANVAS_OP_MODE_ORINVERTED        = (1 << 13), /* ~src | dst*/
    YWGUI_CANVAS_OP_MODE_ANDINVERTED    = (1 << 14), /* ~src & dst*/
    YWGUI_CANVAS_OP_MODE_ORREVERSE        = (1 << 15), /* src | ~dst*/
    YWGUI_CANVAS_OP_MODE_ANDREVERSE        = (1 << 16), /* src & ~dst*/
    YWGUI_CANVAS_OP_MODE_COLORKEY        = (1 << 17),/*color mode --- 当使用此模式时， YWGUI_CANVAS_PixelFormat_T中Colorkey 所指示的颜色不画（ 目前仅要求DrawImage对此模式的支持） */
    YWGUI_CANVAS_OP_MODE_ALPHA            = (1 << 18),/*Alpha mode*/
    YWGUI_CANVAS_OP_MODE_NOOP            = (1 << 19) /* dst*/
} YWGUI_CANVAS_OpMode_T;

/*typedef enum YWGUI_ColorKeyCopyMode_e
{
    YWGUI_COLOR_KEY_MODE_NONE =0,
    YWGUI_COLOR_KEY_MODE_SRC,
    YWGUI_COLOR_KEY_MODE_DST
} YWGUI_ColorKeyCopyMode_T;*/
/*end of added*/
/*******************************************************************************
***********************************常数定义*************************************
*******************************************************************************/
#define YWGUI_INVALID_STRING_ID     (0xFFFFFFFF)

#define YWGUI_NULL_HANDLE               (0)

#define YWGUI_CLASSNAME_MAX             15


/*******************************************************************************
************************************宏定义**************************************
*******************************************************************************/
#define YWGUI_3DFRAME_LEFT_INNERC         YWGUI_3DBOX_DARKC
#define YWGUI_3DFRAME_RIGHT_INNERC        YWGUI_3DBOX_NORMALC
#define YWGUI_3DFRAME_LEFT_OUTERC         YWGUI_3DBOX_REVERSEC
#define YWGUI_3DFRAME_RIGHT_OUTERC        YWGUI_3DBOX_LIGHTC


#define YWGUI_SW_HIDE                   0x0000
#define YWGUI_SW_SHOW                   0x0010
#define YWGUI_SW_SHOWTOP                0x0100

//YWGUI_DrawText 使用
#define YWGUI_DT_LEFT                   0x00000000
#define YWGUI_DT_TOP                    0x00000000
#define YWGUI_DT_CENTER                 0x00000001
#define YWGUI_DT_RIGHT                  0x00000002
#define YWGUI_DT_VCENTER                0x00000004
#define YWGUI_DT_BOTTOM                 0x00000008

/*YWGUI_DT_WORDBREAK:
一行显示不下时，以单词为单位自动分行
*/
#define YWGUI_DT_WORDBREAK              0x00000010
#define YWGUI_DT_SINGLELINE             0x00000020

/*YWGUI_DT_EXPANDTABS:
如果具备该风格，'\t' 扩展成空白区,否则忽略它
*/
#define YWGUI_DT_EXPANDTABS             0x00000040

/*YWGUI_DT_TABSTOP:
具备该风格时，高16位为每个 tab 所代表的字符个数;
不具备该风格时，每个 tab 所代表的字符个数由 DC 确定(默认为8)
*/
#define YWGUI_DT_TABSTOP                0x00000080

#define YWGUI_DT_NOCLIP                 0x00000100
#define YWGUI_DT_CALCRECT               0x00000200 //暂不支持

#define YWGUI_DT_NEGINDENT               0x00000400 //支持负的缩进

/*YWGUI_DT_CHARBREAK:
一行显示不下时，以字符为单位自动分行
*/
#define YWGUI_DT_CHARBREAK             0x00000800

#if 0
//设备无关位图
//注:设备无关位图的宏要与位图转换工具定义一致
#define YWMID_DIBMP_FLOW_DOWN           0x00000000//由上到下(默认)
#define YWMID_DIBMP_FLOW_UP             0x00000001 //由下到上
#define YWMID_DIBMP_FLOW_MASK           0x0000000F

#define YWMID_DIBMP_COMPRESS_NO         0x00000000 //无压缩(默认)
#define YWMID_DIBMP_COMPRESS_RLE4       0x00000010
#define YWMID_DIBMP_COMPRESS_RLE8       0x00000020
#define YWMID_DIBMP_COMPRESS_MASK       0x000000F0

#define YWMID_DIBMP_SIZE_4              0x00000000
#define YWMID_DIBMP_SIZE_3              0x00000100
#define YWMID_DIBMP_SIZE_2              0x00000200
#define YWMID_DIBMP_SIZE_1              0x00000300
#define YWMID_DIBMP_SIZE_MASK           0x00000F00

#define YWMID_DIBMP_FORMAT_BGR0_8888    0x00000000
#define YWMID_DIBMP_FORMAT_BGRA_8888    0x00001000
#define YWMID_DIBMP_FORMAT_RGBA_8888    0x00002000
#define YWMID_DIBMP_FORMAT_ABGR_8888    0x00003000
#define YWMID_DIBMP_FORMAT_ARGB_8888    0x00004000

#define YWMID_DIBMP_FORMAT_RGB_888      0x00020000
#define YWMID_DIBMP_FORMAT_BGR_888      0x00021000

#define YWMID_DIBMP_FORMAT_RGB_565      0x00040000
#define YWMID_DIBMP_FORMAT_ARGB_4444    0x00041000

#define YWMID_DIBMP_FORMAT_CLUT_8       0x00060000

#define YWMID_DIBMP_FORMAT_MASK         0x000FF000


#define YWMID_DIBMP_ALPHA_NO            0x00000000
#define YWMID_DIBMP_ALPHA_GLOBAL        0x10000000
#define YWMID_DIBMP_ALPHA_LOCAL         0x20000000
#define YWMID_DIBMP_ALPHA_MASK          0x30000000

#define YWMID_DIBMP_COLOR_KEY           0x40000000
#define YWMID_DIBMP_COLOR_KEY_MASK      0x40000000
#endif

/*******************************************************************************
********************************消息宏定义**************************************
*******************************************************************************/

//因历史原因,保留了0x0220-0x029F


//第一组(ywgui内部消息)
#define YWGUI_FIRSTINNERMSG                    0x0001
#define YWGUI_LASTINNERMSG                     0x00FF

//第二组
//定义鼠标(感应笔)消息,预留给将来扩展,但目前并不真正支持
#define YWGUI_FIRSTMOUSEMSG                    0x0100
#define YWGUI_LASTMOUSEMSG                     0x011F
//0x0100~0x010F 定义内部消息

#define YWGUI_MSG_MOUSEMOVE                    0x0110

//第三组
#define YWGUI_FIRSTKEYMSG                      0x0120
#define YWGUI_LASTKEYMSG                       0x013F
//0x0120~0x012F 定义内部消息

#define YWGUI_MSG_KEYDOWN                      0x0130

/*
YWGUI_MSG_CHAR
wParam: unicode 字符码
*/
#define YWGUI_MSG_CHAR                         0x0131

#define YWGUI_MSG_KEYUP                        0x0132

#define YWGUI_MSG_SYSKEYDOWN                   0x0133

#define YWGUI_MSG_SYSKEYUP                     0x0134

//第四组
#define YWGUI_FIRSTPOSTMSG                     0x0140
#define YWGUI_LASTPOSTMSG                      0x018F
//0x0140~0x014F 定义内部消息

/*
YWGUI_MSG_SIZING通知
说明: 窗口尺寸将要发生变化(如创建窗口/移动窗口)时发送该消息;
      应用处理该消息,可以重新指定窗口位置;
wParam: 预期的窗口矩形(相对于父窗口客户区坐标)
lParam: 重新指定的窗口矩形(相对于父窗口客户区坐标),
*/
#define YWGUI_MSG_SIZING                        0x0150

/*
YWGUI_MSG_CSIZING通知
说明: 窗口客户区尺寸发生变化时发送该消息;
      应用处理该消息,可以重新指定窗口客户区大小(修改lParam所指向的矩形);
wParam: 指向窗口矩形(相对于父窗口客户区坐标)
lParam: 指向客户区矩形(相对于父窗口客户区坐标)
*/
#define YWGUI_MSG_CSIZING                       0x0151

/*
YWGUI_MSG_CSIZE通知
该消息用来通知用户窗口客户区大小已改变。
wParam： 客户区宽度
lParam: 客户区高度
*/
#define YWGUI_MSG_CSIZE                         0x152


/*YWGUI_MSG_SETFOCUS
说明: 窗口得到焦点之后发送该消息
wParam: 失去焦点的窗口句柄
*/
#define YWGUI_MSG_SETFOCUS                      0x0160

/*YWGUI_MSG_KILLFOCUS
说明: 窗口失去焦点之后发送该消息
wParam: 获得焦点的窗口句柄
*/
#define YWGUI_MSG_KILLFOCUS                     0x0161

/*YWGUI_MSG_ACTIVE通知
wParam: TRUE--激活;FALSE--失活
lParam: 未用
*/
#define YWGUI_MSG_ACTIVE                        0x0162

/*
YWGUI_MSG_CHILDHIDDEN通知
说明:YWGUI_WS_EX_CTRLASMAINWIN风格的控件被隐藏后,发送该通知到其父窗口
*/
#define YWGUI_MSG_CHILDHIDDEN                   0x0163

//第五组
#define YWGUI_FIRSTCREATEMSG                    0x0190
#define YWGUI_LASTCREATEMSG                     0x01DF
//0x0190~0x019F 定义内部消息


/*YWGUI_MSG_CREATE通知
主窗口:wParam--未用; lParam--指向YWGUI_MainWinCreate_T结构
子窗口:wParam--父窗口句柄;lParam --YWGUI_CreateWidgetWindow 传入的dwAddData
返回值:非零，窗口将被立即销毁.
*/
#define YWGUI_MSG_CREATE                        0x01A0

/*YWGUI_MSG_NCCREATE 通知
在窗口被创建,但尚未注册到系统时发送此消息；
该消息先于MSG_CREATE发送,接收到此消息时,尚不能创建子窗口，
也不能得到画图的设备上下文句柄. 如果返回值非零，窗口将被立即销毁.

主窗口: wParam -- 未用; lParam--指向YWGUI_MainWinCreate_T结构
子窗口: wParam -- 未用; lParam--指向 YWGUI_Control_T 结构
返回值:非零，窗口将被立即销毁.
*/
#define YWGUI_MSG_NCCREATE                       0x01A1

#define YWGUI_MSG_DESTROY                        0x01A2

#define YWGUI_MSG_CLOSE                          0x01A3

//第六组
#define YWGUI_FIRSTPAINTMSG                      0x01E0
#define YWGUI_LASTPAINTMSG                       0x021F
//0x01E0~0x01EF 定义内部消息


#define YWGUI_MSG_NCACTIVATE                     0x01F0

/*
YWGUI_MSG_NCPAINT
说明: 窗口绘图顺序(框架->背景->前景)
wParam:未用
lParam:未用
*/
#define YWGUI_MSG_NCPAINT                        0x01F1

/*YWGUI_MSG_ERASEBKGND
wParam --DC句柄
lParam -- 未用
*/
#define YWGUI_MSG_ERASEBKGND                     0x01F2

/*YWGUI_MSG_PAINT
说明:
wParam : 未用
lParam : 未用
*/
#define YWGUI_MSG_PAINT                          0x01F3




//保留0x0220-0x029F


//第七组

#define YWGUI_FIRSTCONTROLMSG                    0x02A0
#define YWGUI_LASTCONTROLMSG                     0x03AF
//0x02A0~0x2AF 定义内部消息


/**YWGUI_MSG_COMMAND通知
wParam: 低16位控件ID,高16位通知码
lParam: 控件窗口句柄*/
#define YWGUI_MSG_COMMAND                        0x02B0

#define YWGUI_MSG_NOTIFY                         0x02B1

/*
YWGUI_MSG_NOTIFY_NCCREATE通知

控件收到YWGUI_MSG_NCCREATE后,往父窗口发送该通知
wParam:低16位控件ID,高16位保留(0)
lParam:控件窗口句柄
*/

#define YWGUI_MSG_NOTIFY_NCCREATE                 0x02B2

/*YWGUI_MSG_INITDIALOG通知
wParam : 将设置的默认焦点窗口句柄
lParam: 创建对话框时传入的参数值
返回值:1--如果返回1,将设置wParam所指定的窗口获得按键焦点,
                  否则不设置默认的焦点窗口
*/
#define YWGUI_MSG_INITDIALOG                      0x02B3

#define YWGUI_MSG_ENABLE                          0x02B4


/*YWGUI_MSG_SETTEXT
wParam: 未用 (0)
lParam: 设置的文本字符串
返回值:
*/

#define YWGUI_MSG_SETTEXT                         0x02C0

/*YWGUI_MSG_GETTEXTLENGTH
wParam: 未用 (0)
lParam: 未用 (0)
返回值: 文本字符串长度(即字符个数),不包括结束符
注意:   UCS2 一个字符占两个字节
*/
#define YWGUI_MSG_GETTEXTLENGTH                   0x02C1

/*YWGUI_MSG_GETTEXT
wParam: 指定缓存区的大小(字节个数)
lParam: 缓存区指针
返回值: 拷贝到缓存区的字符数,不包括结束符
注意:   UCS2 一个字符占两个字节
*/
#define YWGUI_MSG_GETTEXT                         0x02C2

/*YWGUI_MSG_GETCTRLCODE
wParam: 0
lParam: 0
返回值: 控件所需的键值
*/
#define YWGUI_MSG_GETCTRLCODE                0x02C3

//特定控件的消息从0x0300开始定义
//其中0x0300~0x034F是内部消息
//0x0350~0x03AF 是向应用开放的消息

//第八组

#define YWGUI_FIRSTSYSTEMMSG                      0x03B0
#define YWGUI_LASTSYSTEMMSG                       0x03FF

//0x03B0~0x3BF 定义内部消息


#define YWGUI_MSG_QUIT                            0x03C0


/*YWGUI_MSG_TIMER
wParam: 定时器ID (YWGUI 封装的定时器ID)
lParam: 未用
注意: 1) YWGUI最多支持 32 个定时器
      2) 所有窗口加起来最多可使用32个定时器 (其中保留7个给GUI系统自己使用)
*/
#define YWGUI_MSG_TIMER                           0x03C1


#define YWGUI_MSG_IME_OPEN                        0x03C2

#define YWGUI_MSG_IME_CLOSE                       0x03C3

#define YWGUI_MSG_IME_SETTARGET                   0x03C4

#define YWGUI_MSG_IME_SETPROMPT                   0x03c5

//append by Eagle 2009-06-01
#define YWGUI_MSG_IME_CURCHAR                     0x03c6


//第九组
#define YWGUI_MSG_USER                           0x0800

/*******************************************************************************
************************YWGUI_MSG_COMMAND通知码定义****************************
*******************************************************************************/
//16位表示
//控件通用的通知码:  0x0001--0x0200
//各特定控件的通知码:0x0201--0xFFFF
#define YWGUI_NONE_CODE                         0x0000

#define YWGUI_NC_KILLFOCUS                      0x0100
#define YWGUI_NC_SETFOCUS                       0x0101

/*******************************************************************************
*******************************按键扫描码定义***********************************
*******************************************************************************/
#if 0
#define YWGUI_SCANCODE_OK                        0x01
#define YWGUI_SCANCODE_EXIT                      0x02
#define YWGUI_SCANCODE_LEFT                      0x03
#define YWGUI_SCANCODE_UP                        0x04
#define YWGUI_SCANCODE_RIGHT                     0x05
#define YWGUI_SCANCODE_DOWN                      0x06

#define YWGUI_SCANCODE_0                         0x10
#define YWGUI_SCANCODE_1                         0x11
#define YWGUI_SCANCODE_2                         0x12
#define YWGUI_SCANCODE_3                         0x13
#define YWGUI_SCANCODE_4                         0x14
#define YWGUI_SCANCODE_5                         0x15
#define YWGUI_SCANCODE_6                         0x16
#define YWGUI_SCANCODE_7                         0x17
#define YWGUI_SCANCODE_8                         0x18
#define YWGUI_SCANCODE_9                         0x19
#else/*按照linux input的标准按键来定义*/
#define YWGUI_SCANCODE_OK                        28        //KEY_ENTER
#define YWGUI_SCANCODE_EXIT                      1         //KEY_ESC
#define YWGUI_SCANCODE_LEFT                     105     //KEY_LEFT
#define YWGUI_SCANCODE_UP                         103     //KEY_UP
#define YWGUI_SCANCODE_RIGHT                   106     //KEY_RIGHT
#define YWGUI_SCANCODE_DOWN                   108     //KEY_DOWN

#define YWGUI_SCANCODE_0                         11 //KEY_0
#define YWGUI_SCANCODE_1                         2   //KEY_1
#define YWGUI_SCANCODE_2                         3  //KEY_2
#define YWGUI_SCANCODE_3                         4  //KEY_3
#define YWGUI_SCANCODE_4                         5  //KEY_4
#define YWGUI_SCANCODE_5                         6  //KEY_5
#define YWGUI_SCANCODE_6                         7  //KEY_6
#define YWGUI_SCANCODE_7                         8  //KEY_7
#define YWGUI_SCANCODE_8                         9  //KEY_8
#define YWGUI_SCANCODE_9                         10 //KEY_9
#endif

//用户自定义键开始地址
#define YWGUI_SCANCODE_USER                      0x20


/*******************************************************************************
*******************************窗口风格定义***********************************
*******************************************************************************/
//窗口风格(使用高16位,留下低16位定义控件风格)
#define YWGUI_WS_NONE                         0x00000000L

#define YWGUI_WS_TABSTOP                      0x00010000L
#define YWGUI_WS_HSCROLL                      0x00040000L
#define YWGUI_WS_VSCROLL                      0x00080000L

#define YWGUI_WS_THINFRAME                    0x00100000L  //细边框
#define YWGUI_WS_THICKFRAME                   0x00200000L  //粗边框
#define YWGUI_WS_BORDER                       0x00400000L
#define YWGUI_WS_DLGFRAME                     0x00800000L


#define YWGUI_WS_DISABLED                     0x04000000L
#define YWGUI_WS_VISIBLE                      0x08000000L

#define YWGUI_WS_CAPTION                      0x20000000L
#define YWGUI_WS_CHILD                        0x40000000L

/*******************************************************************************
*******************************窗口扩展风格定义***********************************
*******************************************************************************/
//窗口扩展风格
//内部用来记录窗口状态使用: 高4位
//外部用来定义扩展风格使用: 低24位
#define YWGUI_WS_EX_NONE                  0x00000000L

#define YWGUI_WS_EX_TOPMOST               0x00000001L
#define YWGUI_WS_EX_TRANSPARENT           0x00000002L
#define YWGUI_WS_EX_TOOLWINDOW            0x00000004L

/*
YWGUI_WS_EX_USEPARENTFONT
说明: 1)该风格提供给控件使用;
      2)当控件文本使用其父窗口字体时，使用该风格
*/
#define YWGUI_WS_EX_USEPARENTFONT            0x00000008L

/*
YWGUI_WS_EX_USEPARENTFONT
说明: 1)该风格提供给主窗口和控件使用;
      2)当窗口未销毁之前,该ID对应的字符串要一直存在,否则可能会造成使用非法地址
      3)该风格主要用于动态加载字符串,比如实现多语言切换
*/
#define YWGUI_WS_EX_USECAPTIONID     0x00000010L

/*
YWGUI_WS_EX_IRREGULAR
说明: 1)该风格提供给不规则主窗口使用;
      2)当主窗口是不规则窗口且存在刷新不到的区域时，使用该风格
*/
#define YWGUI_WS_EX_IRREGULAR             0x00100000L


/*
YWGUI_WS_EX_TITLECTRL
说明: 1)该风格提供给 static 控件使用
      2)当控件需要放置到其父窗口框架上时，使用该风格
      2)使用该风格后，控件的窗口矩形及客户区矩形是
        相对于父窗口窗口矩形(非相对父窗口客户区矩形)的坐标
*/
#define YWGUI_WS_EX_TITLECTRL             0x00200000L

/*
YWGUI_WS_EX_FORCEERASEBG
说明: 1)该风格提供给主窗口和控件使用
      2)当同时给窗口指定了背景图集和背景色时，
        如果背景图集不能覆盖整个客户区，使用该风格
*/
#define YWGUI_WS_EX_FORCEERASEBG          0x00400000L

/*
YWGUI_WS_EX_NOTIFY
说明: 1)该风格提供给控件使用
      2)当需要控件发送通知消息给父窗口时,使用该风格
      3)如控件得到焦点,失去焦点时,若控件有该风格,将通知父窗口
*/
#define YWGUI_WS_EX_NOTIFY                0x00800000L




/* The control can be displayed out of the main window which contains the control. */
#define YWGUI_WS_EX_CTRLASMAINWIN         0x04000000L



/** When paint the window, the children areas will be clipped. */
#define YWGUI_WS_EX_CLIPCHILDREN          0x08000000L


/*******************************************************************************
*******************************标准控件 ID定义***********************************
*******************************************************************************/

#define YWGUI_IDC_STATIC                    0
#define YWGUI_IDOK                          1
#define YWGUI_IDCANCEL                      2
#define YWGUI_IDABORT                       3
#define YWGUI_IDRETRY                       4
#define YWGUI_IDIGNORE                      5
#define YWGUI_IDYES                         6
#define YWGUI_IDNO                          7

/*******************************************************************************
*******************************控件类名定义***********************************
*******************************************************************************/
#define YWGUI_CTRL_STATIC             ("STATIC")
#define YWGUI_CTRL_PICTURE            ("PICTURE")
#define YWGUI_CTRL_BUTTON             ("BUTTON")
#define YWGUI_CTRL_POSBAR             ("POSBAR")
#define YWGUI_CTRL_PROGRESSBAR        ("PROGRESSBAR")
#define YWGUI_CTRL_EDIT               ("EDIT")
#define YWGUI_CTRL_SEDIT              ("SEDIT")
#define YWGUI_CTRL_LRCOMBOBOX         ("LRCOMBOBOX")
#define YWGUI_CTRL_LISTBOX            ("LISTBOX")
#define YWGUI_CTRL_LISTVIEW           ("LISTVIEW")
#define YWGUI_CTRL_LISTTABLE          ("LISTTABLE")
#define YWGUI_CTRL_CONTAINER          ("CONTAINER")


/*******************************************************************************
*******************************具体控件类定义***********************************
*******************************************************************************/

/*=============================控件风格定义=================================*/

//控件风格可用低16位

/*****************************static 控件风格*******************************/

#define YWGUI_SS_TYPEMASK          0x00000003L //类型掩码(2bit)
#define YWGUI_SS_SIMPLE            0x00000000L //默认
#define YWGUI_SS_GROUPBOX          0x00000001L

#define YWGUI_SS_HALIGNMASK        0x0000000CL //横向对齐方式掩码(2bit)
#define YWGUI_SS_LEFT              0x00000000L //默认(靠左)
#define YWGUI_SS_CENTER            0x00000004L //横向居中
#define YWGUI_SS_RIGHT             0x00000008L //靠右

#define YWGUI_SS_VALIGNMASK        0x00000030L //纵向对齐方式掩码(2bit)
#define YWGUI_SS_TOP               0x00000000L //默认(靠顶)
#define YWGUI_SS_VCENTER           0x00000010L //纵向居中
#define YWGUI_SS_BOTTOM            0x00000020L //靠底
//#define YWGUI_SS_NOAUTOBREAK       0x00001000L //不自动换行(默认：自动换行)
/*默认按不换行*/
#define YWGUI_SS_WORDBREAK         0x00001000L //按单词换行
#define YWGUI_SS_CHARBREAK         0x00002000L //按字母换行
#define YWGUI_SS_ROLLDISP          0x0004000L //滚动显示(从左向右滚动)(只能单行,滚动显示时不换行)
#define YWGUI_SS_ROLLDISP_REVERSE  0x0008000L //滚动显示(从右向左滚动)(只能单行,滚动显示时不换行)

/*****************************button 控件风格*******************************/
#define YWGUI_BS_TYPEMASK          0x00000003L //类型掩码(2bit)

#define YWGUI_BS_HALIGNMASK        0x0000000CL//横向对齐方式掩码(2bit)
#define YWGUI_BS_LEFT              0x00000000L //默认
#define YWGUI_BS_CENTER            0x00000004L
#define YWGUI_BS_RIGHT             0x00000008L

#define YWGUI_BS_VALIGNMASK        0x00000030L//纵向对齐方式掩码(2bit)
#define YWGUI_BS_TOP               0x00000000L//默认
#define YWGUI_BS_VCENTER           0x00000010L
#define YWGUI_BS_BOTTOM            0x00000020L

/*****************************picture 控件风格*******************************/
#define YWGUI_PS_TYPEMASK          0x00000003L //类型掩码(2bit)
#define YWGUI_PS_BITMAP            0x00000000L //默认(位图)
#define YWGUI_PS_ICON              0x00000001L //暂不支持

#define YWGUI_PS_ALIGNMASK         0x0000000CL //排列方式掩码(2bit)
#define YWGUI_PS_CENTER            0x00000000L //居中方式（默认）
#define YWGUI_PS_STRETCH           0x00000004L //拉伸或缩小以适应控件大小(暂不支持)



/*****************************posbar 控件风格*******************************/
#define YWGUI_POS_TYPEMASK          0x00000003L //类型掩码(2bit)
#define YWGUI_POS_VERT              0x00000000L //默认(纵向 posbar)
#define YWGUI_POS_HORZ              0x00000001L //横向 posbar

/*****************************progress bar  控件风格*******************************/
#define YWGUI_PBS_TYPEMASK          0x00000003L //类型掩码(2bit)
#define YWGUI_PBS_HORZ              0x00000000L //默认(横向)
#define YWGUI_PBS_VERT              0x00000001L //纵向

#define YWGUI_PBS_STRETCH           0x00001000L

/*********************************编辑控件风格*******************************/

//固定Thumb size
#define YWGUI_ES_PEGTHUMBSIZE       0x00000000L
//自动改变Thumb size0000
#define YWGUI_ES_AUTOTHUMBSIZE      0x00000001L

//add by Eagle 2009-06-04
//support SEDIT only
#define YWGUI_ES_REPLACE            0x00000002L

#define YWGUI_ES_HALIGNMASK         0x0000000CL //横向对齐方式掩码(2bit)
#define YWGUI_ES_LEFT               0x00000000L //默认(靠左)
#define YWGUI_ES_CENTER             0x00000004L //横向居中
#define YWGUI_ES_RIGHT              0x00000008L //靠右

#define YWGUI_ES_VALIGNMASK        0x00000030L //纵向对齐方式掩码(2bit)
#define YWGUI_ES_TOP               0x00000000L //默认(靠顶)
#define YWGUI_ES_VCENTER           0x00000010L //纵向居中
#define YWGUI_ES_BOTTOM            0x00000020L //靠底

#define YWGUI_ES_MULTILINE          0x00000040L
#define YWGUI_ES_UPPERCASE          0x00000080L
#define YWGUI_ES_LOWERCASE          0x00000100L
#define YWGUI_ES_PASSWORD           0x00000200L

#define YWGUI_ES_READONLY           0x00000400L
#define YWGUI_ES_NUMBER             0x00000800L

#define YWGUI_ES_SCROLLMASK         0x00003000L //纵向对齐方式掩码(2bit)
#define YWGUI_ES_AUTOSCROLL         0x00000000L
#define YWGUI_ES_NOSCROLL           0x00001000L
#define YWGUI_ES_ALWAYSSCROLL       0x00002000L

//不自动换行
#define YWGUI_ES_NOAUTOBREAK        0x00004000L
#define YWGUI_ES_AUTOWORDBREAK  0x00008000L

/*********************************Listbox控件风格*******************************/
#define YWGUI_LBS_NOTIFY             0x0001L
#define YWGUI_LBS_MULTIPLESEL        0x0002L
#define YWGUI_LBS_CHECKBOX           0x0010L
#define YWGUI_LBS_USEICON            0x0020L
//#define YWGUI_LBS_AUTOCHECK          0x0040L
//#define YWGUI_LBS_AUTOCHECKBOX       (YWGUI_LBS_CHECKBOX | YWGUI_LBS_AUTOCHECK)

#define YWGUI_LBS_AUTOSCROLL          0x0100L
#define YWGUI_LBS_NOSCROLL            0x0200L
#define YWGUI_LBS_ALWAYSSCROLL        0x0400L

//固定Thumb size
#define YWGUI_LBS_PEGTHUMBSIZE        0x1000L
//自动改变Thumb size
#define YWGUI_LBS_AUTOTHUMBSIZE       0x2000L
//列表项不循环切换
#define YWGUI_LBS_ITEMNOTLOOPMOVE     0x4000L
/*********************************Listview控件风格*******************************/
//brief Displays a check box in an item.
#define YWGUI_LVS_CHECKBOX            0x0001L
//#define YWGUI_LVS_AUTOCHECK           0x0002L
//#define YWGUI_LVS_AUTOCHECKBOX        (YWGUI_LVS_CHECKBOX | YWGUI_LVS_AUTOCHECK)
#define YWGUI_LVS_MULTIPLESEL         0x0004L

#define YWGUI_LVS_DRAWITEMLINE        0x0008L
#define YWGUI_LVS_DRAWCOLMUNLINE      0x0010L

#define YWGUI_LVS_AUTOSCROLL          0x0100L
#define YWGUI_LVS_NOSCROLL            0x0200L
#define YWGUI_LVS_ALWAYSSCROLL        0x0400L

//固定Thumb size
#define YWGUI_LVS_PEGTHUMBSIZE        0x1000L
//自动改变Thumb size
#define YWGUI_LVS_AUTOTHUMBSIZE       0x2000L
//列表项不循环切换
#define YWGUI_LVS_ITEMNOTLOOPMOVE     0x4000L
/*********************************lrcombobox控件风格*******************************/
#define YWGUI_LRCBS_HALIGNMASK         0x0000000CL //横向对齐方式掩码(2bit)
#define YWGUI_LRCBS_LEFT               0x00000000L //默认(靠左)
#define YWGUI_LRCBS_CENTER             0x00000004L //横向居中
#define YWGUI_LRCBS_RIGHT              0x00000008L //靠右

#define YWGUI_LRCBS_VALIGNMASK         0x00000030L //纵向对齐方式掩码(2bit)
#define YWGUI_LRCBS_TOP                0x00000000L //默认(靠顶)
#define YWGUI_LRCBS_VCENTER            0x00000010L //纵向居中
#define YWGUI_LRCBS_BOTTOM             0x00000020L //靠底

//如果选中此风格表示如果combobox中的list显示则按退出键只会隐藏list,
//否则走默认处理(交给父窗口处理)
#define YWGUI_LRCBS_EXITKEYHIDELIST     0x0040L
#define YWGUI_LRCBS_AUTOSCROLL        0x0080L
#define YWGUI_LRCBS_NOSCROLL          0x0100L
#define YWGUI_LRCBS_ALWAYSSCROLL      0x0200L


//固定Thumb size
#define YWGUI_LRCBS_PEGTHUMBSIZE        0x0400L
//自动改变Thumb size
#define YWGUI_LRCBS_AUTOTHUMBSIZE       0x0800L
//列表项不循环切换和左右键也不循环切换项
#define YWGUI_LRCBS_ITEMNOTLOOPMOVE     0x1000L
#define YWGUI_LRCBS_HIDELISTBOXALWAY    0x2000L


//add by Eagle 2009-05-06
//ListTable Style Marco
/*********************************ListTable控件风格********************************/
#define YWGUI_LTS_MARK              0x0001L
#define YWGUI_LTS_MUTISHAPE         0x0002L
#define YWGUI_LTS_MARKSTAY          0x0004L
#define YWGUI_LTS_DISABLE           0x0008L

//TP(透明)
#define YWGUI_LTS_TPMASK            0x0030L
#define YWGUI_LTS_NORMALTP          0x0010L
#define YWGUI_LTS_FOCUSTP           0x0020L

#define YWGUI_LTS_ROLLDISP          0x0040L
#define YWGUI_LTS_ROLLDISP_REVERSE  0x0080L

/*对齐方式*/
#define YWGUI_LTS_CENTER            0x0100L/*横向居中*/

//Disable不跳过选项的风格,当焦点在Disable行时此时焦点行的前景色为Disable的前景色，背景为Afocus的背景
#define YWGUI_LTS_DISABLE_NOTJUMP   0x0200L

//container
/*********************************Container控件风格********************************/
//水平方式
#define YWGUI_CTS_HORIZONTAL        0x0
//垂直方式
#define YWGUI_CTS_VERTICAL          0x1

/*=============================控件消息定义=================================*/
//特定控件的消息从0x0300开始定义
//其中0x0300~0x034F是内部消息
//0x0350~0x03AF 是向应用开放的消息


/*=============================控件通知码定义=================================*/

//各特定控件的通知码:0x0201--0xFFFF

/*****************************ListView控件通知码*******************************/


//ListView控件
//{
/**************************************
 YWGUI_LVN_SELCHANGED
 功能:表示选中状态已经改变
 **************************************/
#define YWGUI_LVN_SELCHANGED           0x0201

/**************************************
 YWGUI_LVN_FOCUSITEMCHANGED
 功能:表示焦点项已经改变
 **************************************/
 #define YWGUI_LVN_FOCUSITEMCHANGED     0x0202
//}

/*****************************Listbox控件通知码*******************************/
//Listbox控件
//{
/****************************************************
 多行选择时, 选中或取消选中则会向父窗口发送此消息
 (发送到YWGUI_MSG_COMMAND中)
 ****************************************************/
#define YWGUI_LBN_SELCHANGED         0x0203

/****************************************************
 焦点行改变后会向父窗口发送此消息,
 一般为上下移动,或翻页的时候才会向父窗口发送此消息
 (发送到YWGUI_MSG_COMMAND中)
 ****************************************************/
#define YWGUI_LBN_FOCUSITEMCHANGED   0x0204
//}

/*****************************combobox控件通知码*******************************/
//选中的内容发生改变
#define YWGUI_LRCBN_CBCHANGE        0x0205

/*****************************Edit控件通知码***********************************/
/****************************************************
 当Edit中有字符改变就会向父窗口发送此事件
 (发送到YWGUI_MSG_COMMAND中)
 ****************************************************/
#define YWGUI_EN_CHANGE           0x0206

/****************************************************
 当Edit进入编辑状态后会向父窗口发送此事件
 (发送到YWGUI_MSG_COMMAND中)
 ****************************************************/
#define YWGUI_EN_ENTEREDITSTATUS  0x0207

/****************************************************
 当Edit退出编辑状态后会向父窗口发送此事件
 (发送到YWGUI_MSG_COMMAND中)
 ****************************************************/
#define YWGUI_EN_EXITEDITSTATUS   0x0208

/****************************************************
 当Edit内容改变(真实改变)并退出了编辑状态后会向父窗口发送此事件
 (发送到YWGUI_MSG_COMMAND中)
 ****************************************************/
#define YWGUI_EN_CONTCHANGE       0x0209
/****************************************************
 当光标在最左边的时候在按左键会出发此消息
 (发送到YWGUI_MSG_COMMAND中)
 ****************************************************/
#define YWGUI_EN_HOME_LEFT        0x020a
/****************************************************
 当光标在最右边的时候在右按键会出发此消息
 (发送到YWGUI_MSG_COMMAND中)
 ****************************************************/
#define YWGUI_EN_END_RIGHT        0x020b

/*****************************container控件通知码*******************************/
//上下左右按键
#define YWGUI_CTN_UPKEY           0x020c
#define YWGUI_CTN_DOWNKEY         0x020d
#define YWGUI_CTN_LEFTKEY         0x020e
#define YWGUI_CTN_RIGHTKEY        0x020f

//add by Eagle 2009-05-06
//ListTable Notify
/*****************************ListTable控件通知码**********************************/
/**************************************
 YWGUI_LTN_NEEDDATA
 功  能: 通知应用需要获取数据(以页为单位)
 lParam: 低16位 -- 需要获取数据的起始索引
         高16位 -- 需要获取数据的结束索引(不包括本索引)
 说  明: 应用根据索引号调用 YWGUI_LTSetItemInfo
         完成数据刷新
 **************************************/
#define YWGUI_LTN_NEEDDATA      0x250


/**************************************
 YWGUI_LTN_CURCHANGE
 功  能: 通知应用当前焦点行改变
 lParam: 当前焦点行索引
 说  明:
 **************************************/
#define YWGUI_LTN_CURCHANGE     0x251


/**************************************
 YWGUI_LTN_MARKCHANGE
 功  能: 通知应用 Check 状态改变
 lParam: 状态改变行的索引
 说  明:
 **************************************/
#define YWGUI_LTN_MARKCHANGE    0x252


/* 主窗口向控件查询控件所需要的按键 */

/**************************************
 YWGUI_CTRLCODE_WANTUD
 功  能: 控件告诉主窗口自己需要上下键
 说  明: 主窗口向控件发送YWGUI_MSG_GETCTRLCODE消息获取控件所需要的按键
 **************************************/
#define YWGUI_CTRLCODE_WANTUD     0x0001
/**************************************
 YWGUI_CTRLCODE_WANTLR
 功  能: 控件告诉主窗口自己需要左右键
 说  明: 主窗口向控件发送YWGUI_MSG_GETCTRLCODE消息获取控件所需要的按键
 **************************************/
#define YWGUI_CTRLCODE_WANTLR    0x0002
/**************************************
 YWGUI_CTRLCODE_WANTALLKEYS
 功  能: 控件告诉主窗口自己需要所有按键
 说  明: 主窗口向控件发送YWGUI_MSG_GETCTRLCODE消息获取控件所需要的按键
 **************************************/
#define YWGUI_CTRLCODE_WANTALLKEYS    0x0004
/**************************************
 YWGUI_CTRLCODE_WANTOK
 功  能: 控件告诉主窗口自己需要确认(OK)键
 说  明: 主窗口向控件发送YWGUI_MSG_GETCTRLCODE消息获取控件所需要的按键
 **************************************/
#define YWGUI_CTRLCODE_WANTOK      0x0008

/*******************************************************************************
***********************************结构体定义*************************************
*******************************************************************************/
typedef struct YWGUI_Rgb_s
{
    U8 r;
    U8 g;
    U8 b;
}YWGUI_Rgb_T;

typedef struct YWGUI_Argb_s
{
    U8 a;
    U8 r;
    U8 g;
    U8 b;
}YWGUI_Argb_T;

typedef struct YWGUI_Point_s
{
    S32 x;
    S32 y;
} YWGUI_Point_T;

typedef struct YWGUI_Rect_s
{
    S32 left;
    S32 top;
    S32 right;
    S32 bottom;
} YWGUI_Rect_T;
typedef YWGUI_Rect_T* YWGUI_Rect_P;

typedef struct YWGUI_Extent_s
{
        /*** The extent in x coordinate of a 2D object.     */
    S32 cx;

        /*** The extent in y coordinate of a 2D object.     */
    S32 cy;
} YWGUI_Extent_T;

typedef struct YWGUI_LineInfo_s
{
    S32 nr_chars;
    S32 startx;
    S32 starty;
    S32 width;
    S32 height;
} YWGUI_LineInfo_T;

#if 0
    typedef struct YWMID_Palette_s
    {
        U8      Alpha;
        U8      Red;
        U8      Green;
        U8      Blue;
    } YWMID_Palette_T;

    //YWMID_Dibitmap_T: 设备无关位图结构
    typedef struct YWMID_Dibitmap_s
    {
        U32  Flags;

        /**色深:1/4/8/16/24/32 */
        U8 Depth;

        /** The global alpha value. */
        U8 Alpha;

        //U8 Reserved[2];

        /** Flags & YWMID_DIBMP_COLOR_KEY : ColorKey有效;
        如果有颜色表，该值是相对颜色表的索引;*/
        U8 ColorKey[4];

        /** The width of the bitmap. */
        U32 W;

        /** The height of the bitmap. */
        U32 H;

        //每行使用的字节数
        U32 Pitch;

        /*nPaletteColors: 颜色表所用颜色数*/
        U32 PaletteColors;

        //指向颜色表
        YWMID_Palette_T* pPalette;

        /*Bytes 用字节数表示的位图数据的大小*/
        U32 Bytes;

        //指向位图数据使用时根据每象素字节数来决定访问类型，
        const void* pData;
    } YWMID_Dibitmap_T;

#endif


typedef YWMID_Palette_T* YWMID_Palette_P;


typedef struct YWGUI_ShapeColor_s
{
    YWGUI_Pixel_T backColor;
    YWGUI_Pixel_T foreColor;
    YWGUI_Pixel_T frameColor;
}YWGUI_ShapeColor_T;

#if 0/*modified by sly, 2009-11-13*/
typedef struct YWGUI_GraphCell_s
{

    /*对于一组拼凑图片来说，有一个基础宽高，
    leftOffset和topOffset是相对于基础宽高的偏移,
    这样不需强制一组图片要有相同的高度(横向拼凑)或度度(纵向拼凑)

    (rightGraphCell-leftOffset)/(bottomGraphCell-topOffset)描述GraphCell的大小，
    若实际图片小于该大小，则循环调用图片铺满该区域，
    若实际图片大于该大小，图片将会被裁剪以适应它.
    */

    U32 leftOffset;
    U32 topOffset;
    U32 rightGraphCell;
    U32 bottomGraphCell;
    void* ptBmp;//指向设备无关或设备相关位图结构
}YWGUI_GraphCell_T;
#else
typedef struct YWGUI_GraphCell_s
{
  /*对于一组拼凑图片来说，有一个基础宽高，
    DstRect.X和DstRect.Y是相对于基础宽高的偏移,
    (DstRect.W)/(DstRect.H)描述GraphCell的大小，
    若DstRect.W或DstRect.H为0,则认为GraphCell大小无效，用图片宽高代替,只在指定位置输出一幅图片
    若DstRect.W或DstRect.H大于图片宽高,则可平铺，居中或拉伸
    若DstRect.W和DstRect.H小于图片宽高,则除缩小外，其他操作均被裁减
    */
    YWMID_DibitmapOp_T Op;          /*对数据的操作*/
    void* ptBmp;/*注意:该结构在GUI外部使用时指向(YWMID_BitmapData_T *)类型,
                         在GUI内部使用时指向(YWGUI_BitmapData_T*) 类型*/
} YWGUI_GraphCell_T;
#endif
/*end of modify*/

typedef YWGUI_GraphCell_T* YWGUI_GraphCell_P;

typedef struct YWGUI_GraphCollect_s
{
    YWGUI_SpellType_E       eSpellType;
    S32                     nGraph;           //图片数
    YWGUI_GraphCell_T **    pptGraphArray;     //指向YWGUI_GraphCell_T*指针数组

    //nLoadCnt内部使用
    U32                     nLoadCnt;         //0--设备无关图集，每装载一次(装载成设备相关位图)，计数加1
}YWGUI_GraphCollect_T;

typedef struct YWGUI_ShapeFrame_s
{
    YWGUI_FrameType_E eFrameType;

    //ptFrameGraph可为NULL,故定义为指针
    YWGUI_GraphCollect_T *  ptFrameGraph;//边框图集


    /*leftOffsetFrame--bottomOffsetFrame是边框相对于窗口四条边的偏移,
      leftOffsetClient --bottomOffsetClient是客户区相对于边框四条边的偏移,
      由窗口矩形可算出边框矩形,再算出客户区矩形，
      从而可支持到客户矩形随窗口矩形缩放

      修改记录:
      leftOffsetFrame--bottomOffsetFrame四个成员无效,
      为了应用程序的兼容,仍保留在此
      leftOffsetClient --bottomOffsetClient变成客户区相对于窗口四条边的偏移
    */
    #if 1
    U32 leftOffsetFrame;
    U32 topOffsetFrame;
    U32 rightOffsetFrame;
    U32 bottomOffsetFrame;
    #endif

    /*leftOffsetClient --bottomOffsetClient 成员是否有效如下：
        FRAME_NO / FRAME_RECT ：无效
        FRAME_GRAPH :有效
    */
    U32 leftOffsetClient;
    U32 topOffsetClient;
    U32 rightOffsetClient;
    U32 bottomOffsetClient;

}YWGUI_ShapeFrame_T;

typedef struct YWGUI_ShapeState_s
{

    YWGUI_ShapeFrame_T*    ptShapeFrame;

    //ptBackGraph可为NULL，故定义为指针
    YWGUI_GraphCollect_T *  ptBackGraph; //背景图集

    //ptForeGraph可为NULL，故定义为指针
    YWGUI_GraphCollect_T * ptForeGraph;//前景图集

    //ptShapeColor可为NULL,故定义为指针
    YWGUI_ShapeColor_T* ptShapeColor;

}YWGUI_ShapeState_T;

typedef struct YWGUI_ShapeInfo_s
{
    YWGUI_ShapeState_T* ptShape[YWGUI_WES_STATUS_NUM];//指针数组
}YWGUI_ShapeInfo_T;

typedef struct tagListNode
{
    struct tagListNode *pNext;
    struct tagListNode *pPrev;
}ListNode;

typedef struct YWGUI_Wed_s
{
    ListNode         head;
}YWGUI_Wed_T;
typedef YWGUI_Wed_T* YWGUI_Wed_P;

//注册控件类使用
typedef struct YWGUI_WndClass_s
{
    /** The class name */
    S8*         spClassName;

    /** Window style for all instances of this window class */
    DWORD       dwStyle;

    /** Extended window style for all instances of this window class */
    DWORD       dwExStyle;

    /** Window callback procedure of all instances of this window class */
    YWGUI_WindowProc_P      pfnWndProc;

    YWGUI_Wed_P             ptWed;

    /** The private additional data associated with this window class */
    DWORD       dwAddData;

    U32 XOffset;
    U32 YOffset;
} YWGUI_WndClass_T;

typedef YWGUI_WndClass_T*   YWGUI_WndClass_P;

typedef struct YWGUI_MainWinCreate_s
{
    U16 id;
    YWGUI_Char_T *spCaption;
    S32  idStr;/** Dialog  caption id , for dynamic loading string*/
    DWORD dwStyle;
    DWORD dwExStyle;
    YWGUI_HWnd_T  hHosting;//属主窗口句柄
    YWGUI_WindowProc_P  pfnMainWindowProc;
    S32 left;
    S32 top;
    S32 width;
    S32 height;//屏幕坐标
    YWGUI_Pixel_T backColor;
    DWORD dwAddData;
    YWGUI_ShapeInfo_T*  ptShapeInfo;
}YWGUI_MainWinCreate_T;
typedef YWGUI_MainWinCreate_T* YWGUI_MainWinCreate_P;

typedef enum YWGUI_CtrlTextExtra_e
{
    YWGUI_CTRL_CHAR_EXTRA,
    YWGUI_CTRL_ABOVE_EXTRA,
    YWGUI_CTRL_BELLOW_EXTRA,
    YWGUI_CTRL_INDENT_EXTRA     
}YWGUI_CtrlTextExtra_E;

typedef struct  YWGUI_CtrlTemplate_s
{
    /** Class name of the control */
    const S8* class_name;

    /** Control style */
    DWORD       dwStyle;

    /** Control extended style */
    DWORD       dwExStyle;

    /** Control position in dialog */
    S32         x, y, w, h;

    /** Control identifier */
    U16         id;

    /** Control caption id*/
    S32  idStr;

    /** Additional data */
    DWORD       dwAddData;

    YWGUI_ShapeInfo_T*  ptShapeInfo;

} YWGUI_CtrlTemplate_T;
typedef YWGUI_CtrlTemplate_T* YWGUI_CtrlTemplate_P;

typedef struct YWGUI_DlgTemplate_s
{
    /*Dialog identifier*/
    U16 id;

    /** Dialog box style */
    DWORD       dwStyle;

    /** Dialog box extended style */
    DWORD       dwExStyle;

    /** Dialog box position */
    S32         x, y, w, h;

    /** Dialog  caption id*/
    S32  idStr;

    /** Number of controls */
    S32         controlnr;

    /** Poiter to control array */
    YWGUI_CtrlTemplate_T*   controls;

    /** Addtional data, must be zero */
    DWORD       dwAddData;

    YWGUI_ShapeInfo_T*  ptShapeInfo;
} YWGUI_DlgTemplate_T;
typedef YWGUI_DlgTemplate_T* YWGUI_DlgTemplate_P;

typedef struct  YWGUI_Msg_s
{
    YWGUI_HWnd_T         hWnd;
    S32                  message;
    WPARAM               wParam;
    LPARAM               lParam;

    void*                pAdd; //同步消息使用
} YWGUI_Msg_T;
typedef YWGUI_Msg_T* YWGUI_Msg_P;


typedef struct YWGUI_LayerParams_s
{
    YWGUI_PixelType_E       ePixelType; //象素类型

    S32                     left;
    S32                     top;
    U32                     width;
    U32                     height;

    YWGUI_Pixel_T           colorKey;
    YWGUI_Pixel_T           DeskTopColor;
    U8           transparence;/*0~0xFF, 0:透明,0xFF:不透明*/

    U8                      bitsPerPixel; //每象素占多少内存(单位:bit)
    //U8                      alphaBlendingMode;


    BOOL                    bIsHideDesktop;//是否隐藏桌面(需要隐藏桌面时，transparence 必须有效)
    BOOL                    bHaveColorKey; //colorKey 有效
    BOOL                    bHaveTransparence; //transparence 有效
    /*added by sly, 2009-8-17*/
    U32                        uAssociateLayerNum;
    U32*                      puAssociateLayerIndex;
    /*end of added*/
    //BOOL                    bHighDefinition;//是否开成高清图层//delete by sly
}YWGUI_LayerParams_T;


typedef struct YWGUI_KeyItem_s
{
    U16            dataCode;        /*功能码*/
    U16            scanCode;       /* 逻辑码*/
    BOOL        bRepeat;    /*是否重复键*/
}YWGUI_KeyItem_T;

typedef struct YWGUI_KeyboardParams_s
{
    YWGUI_RemoteProtocol_E eRemoteProtocol;
    U16                    customCode;      /*客户码*/
    U32                    keyCnt;
    YWGUI_KeyItem_T*       keyTable;
}YWGUI_KeyboardParams_T;

/*added by sly, 2009-7-17*/
typedef struct YWGUI_FrontPanelParams_s
{
    U32                    uFrontKeyCnt;
    YWGUI_KeyItem_T*       FrontKeyTable;
}YWGUI_FrontPanelParams_T;
/*end of added*/

/*added by sly, 2009-8-5*/
typedef struct YWGUI_LbdItem_s
{
    U16         DataCode;                                   /* 实际值*/
    U16         Reserve;                                    /* 保留*/
    U32         LogicValue;                                 /* 逻辑码（logic value） */
}YWGUI_LbdItem_T;
typedef struct YWGUI_LbdParams_s
{
    U32                          uLbdNumber;                 /*  lbd数 */
    YWGUI_LbdItem_T  *LbdTable;           /*  注册表 */
}YWGUI_LbdParams_T;
/*end of added*/
/*
字体渲染风格字符
    第一位
        'r' --不作特殊处理
        'b' --加粗显示
        'k' --采用低通滤波算法处理字型边缘
        'd' --加粗+低通滤波

    第二位
        'r' --不作特殊处理
        'i' --斜体

    第三位
        'n' --不作特殊处理
        'h' --水平翻转
        'v' --垂直翻转
        't'  --水平+垂直翻转

    第四位
        'c' --不作处理
        's' --根据期望大小自动缩放(仅用于点阵字体)

    第五位
        'n' --无下划线
        'u' --有下划线

    第六位
        'n' --无删除线
        's' --有删除线
*/
typedef struct YWGUI_FontInfo_s
{
    const S8* pcFontAttr;/*字体属性:type-family-style-width-height-charset 如"ttf-arial-rrncnn-10-10-UCS-2"*/
    const S8* pcFontFile; /*字体文件路径*/
} YWGUI_FontInfo_T;

typedef struct YWGUI_CtrlOffsetInfo_s
{
    const S8* CtrlName;

    U32 XOffset;
    U32 YOffset;
}YWGUI_CtrlOffsetInfo_T;

typedef  YWGUI_CtrlOffsetInfo_T* YWGUI_CtrlOffsetInfo_P;

//YWGUI_Start传入的参数结构
typedef struct YWGUI_ImportParams_s
{
    YWGUI_LayerParams_T*             ptLayerParam;
    U8                                                  uRemoteNum;    /*需要支持多少个遥控器*/
    //YWGUI_KeyboardParams_T*          ptKeyboardParam;
    YWGUI_KeyboardParams_T*          ptRemoteParamHead; /*指向remote参数的头指针*/

    YWGUI_FrontPanelParams_T*          ptFrontPanelParam;
    YWGUI_LbdParams_T*                  ptLbdParam;
    //用来传递初始化对话框模板链表的回调函数
    YWGUI_InitDlgTLinkFunc_P        pfnInitDlgTLink;

    //用来传递装载字符串资源的回调函数
    YWGUI_LoadStringFunc_P          pfnLoadString;

    //用来传递修改系统默认绘图属性(配色和素材)的回调函数
    YWGUI_ModifyDefScheFunc_P       pfnModifyDefScheme;

    //用来传递修改控件默认绘图属性的回调函数
    YWGUI_ModifyCtrlDefScheFunc_P   pfnModifyCtrlDefSche;

    YWGUI_KeyPreProcess_P   pfKeyPreProcess;
    U8 uFontNum;/*字体个数*/
    YWGUI_FontInfo_T * pstFontInfo;/*字体信息*/
    U8 uLogFontNum;   /*需要创建的逻辑字体的个数*/
    S8 ** ppcLogFontName;/*需要创建的逻辑字体名称列表*/

    U32 uOffsetInfoNum;
    YWGUI_CtrlOffsetInfo_P pOffsetInfo;
}YWGUI_ImportParams_T;


typedef struct YWGUI_ImeMap_s
{
    S32             reuseCnt;
    YWGUI_Char_T *  pszFact;
}YWGUI_ImeMap_T;

typedef YWGUI_ImeMap_T YWGUI_ImeMapTable_T[10];





//============================ListView控件的结构定义==================

#define YWGUI_LISTITEM_STATUS_NUM                6

#define  YWGUI_LISTITEM_STATUS_NORMAL            0
#define  YWGUI_LISTITEM_STATUS_DISABLE           1
#define  YWGUI_LISTITEM_STATUS_AFOCUS            2
#define  YWGUI_LISTITEM_STATUS_SFOCUS            3
#define  YWGUI_LISTITEM_STATUS_CHECKED           4
#define  YWGUI_LISTITEM_STATUS_SKIP              5

//一列子项的类型
#define YWGUI_LV_TEXTSUB        0            //文本
#define YWGUI_LV_IMAGESUB       1            //图片

//行的状态
#define YWGUI_LVIF_NORMAL             0x0000L
#define YWGUI_LVIF_CHECKED            0x0001L     //选中
#define YWGUI_LVIF_SKIP               0x0002L     //跳过

enum
{
    YWGUI_LVSORT_NOTSORT,
    YWGUI_LVSORT_ASC,
    YWGUI_LVSORT_DESC
};

typedef struct YWGUI_ListItemShapeCollect_s
{
    YWGUI_ShapeState_T* ptShape[YWGUI_LISTITEM_STATUS_NUM];//指针数组
}YWGUI_ListItemShapeInfo_T;

//行背景结构
typedef struct YWGUI_LVItem_BG_s
{
    S32 iStartCol;                          // 画行背景开始的索引
    S32 iEndCol;                            // 画行背景结束的索引

    YWGUI_ListItemShapeInfo_T* pShapeItemBg;  // 行结构指针
}YWGUI_LVItem_BG_T;
typedef YWGUI_LVItem_BG_T* YWGUI_LVItem_BG_P;


typedef struct YWGUI_PosbarDef_s
{
    S32 iThumbSize;                         // Posbar的Thumb Size,Thumb size为固定size的时候
                                            // 才有效，否则这个Size无效

    YWGUI_ShapeInfo_T* pPosbarShape;        // 滚动条外形

    S32 Size;                               //当为水平滚动的时候为滚动条的高度，垂直的时候为滚动条的宽带
                                            //小于0使用控件默认滚动条高度或宽带
}YWGUI_PosbarDef_T;
typedef YWGUI_PosbarDef_T* YWGUI_PosbarDef_P;

typedef struct YWGUI_LVAddData_s
{
    YWGUI_LVItem_BG_P pLVItemBg;            // 行背景

    //YWGUI_ShapeInfo_T* pScrollShape;        // 滚动条外形
    YWGUI_PosbarDef_T* pPosbarDef;          // Listview的Posbar的默认结构

}YWGUI_LVAddData_T;
typedef YWGUI_LVAddData_T* YWGUI_LVAddData_P;

typedef struct YWGUI_LVColumn_S
{
    S32            nCol;    // 新增列的位置
    S32            width;        // 列宽
    YWGUI_Char_T   *pszHeadText; // 列的标题
    //S32            nTextMax;   // 列标题的最大长度
    DWORD          image;        // 列表头的图象指针
                                 // 为YWGUI_ShapeUnit_T类型指针,因为背景可为单色的也可为组合图片
    DWORD          colFlags;   // 列标志文字或图片

} YWGUI_LVColumn_T;
typedef YWGUI_LVColumn_T *YWGUI_LVColumn_P;


typedef struct YWGUI_LVSubItem_s
{
    //DWORD           flags;      // 子项的标志 //LVFLAG_BITMAP or LVFLAG_ICON
    S32             nCol;       // 子项的垂直索引值
    S32             nRow;       // 子项的水平索引值

    YWGUI_Char_T    *pszText;   // 子项的文字内容
    DWORD           image;      // 子项的图片 //为YWGUI_ListItemShapeInfo_T类型指针

} YWGUI_LVSubItem_T;
typedef YWGUI_LVSubItem_T *YWGUI_LVSubItem_P;



//===================================Listbox结构定义=========================================
//行状态
#define YWGUI_LBIF_NORMAL           0x0000L
#define YWGUI_LBIF_CHECKED         0x0001L    //选中
#define YWGUI_LBIF_SKIP             0x0002L    //跳过

typedef struct YWGUI_LBItem_s
{
    DWORD   dwFlags;                        // item flags
    DWORD   dwImage;                        // item image
    YWGUI_Char_T*   pszText;                        // item Text
    DWORD   dwAddData;                      // item additional data
}YWGUI_LBItem_T;
typedef YWGUI_LBItem_T* YWGUI_LBItem_P;


typedef struct YWGUI_LBAddData_s
{
    YWGUI_ListItemShapeInfo_T* pLBItemBgShape;            // 行背景

    //YWGUI_ShapeInfo_T* pScrollShape;                    // 滚动条外形
    YWGUI_PosbarDef_T* pPosbarDef;                        // Listbox的Posbar的默认结构

}YWGUI_LBAddData_T;
typedef YWGUI_LBAddData_T* YWGUI_LBAddData_P;

//===================================LRCombobox结构定义=======================================
//行状态
#define YWGUI_CBIF_NORMAL           0x0000L
#define YWGUI_CBIF_CHECKED          0x0001L    //选中
#define YWGUI_CBIF_SKIP             0x0002L    //跳过

typedef enum YWGUI_LRCBTextWesItem_e
{
    //窗口外观方案
    YWGUI_LRCB_TEXT_STATUS_NORMAL=0,
    YWGUI_LRCB_TEXT_STATUS_DISABLED,
    YWGUI_LRCB_TEXT_STATUS_NOLIST_AFOCUS,
    YWGUI_LRCB_TEXT_STATUS_LIST_AFOCUS,
    YWGUI_LRCB_TEXT_STATUS_NOLIST_SFOCUS,
    YWGUI_LRCB_TEXT_STATUS_LIST_SFOCUS,

    YWGUI_LRCB_TEXT_WES_STATUS_NUM
}YWGUI_LRCBTextWesItem_E;

typedef struct YWGUI_LRCBTextShapeInfo_s
{
    YWGUI_ShapeState_T* ptShape[YWGUI_LRCB_TEXT_WES_STATUS_NUM];//指针数组
}YWGUI_LRCBTextShapeInfo_T;

typedef struct YWGUI_LRCBListItem_s
{
    DWORD   dwFlags;                        // item flags
    DWORD   dwImage;                        // item image
    YWGUI_Char_T*   pszText;                // item Text
    DWORD   dwAddData;                      // item additional data
}YWGUI_LRCBListItem_T;
typedef YWGUI_LRCBListItem_T* YWGUI_LRCBListItem_P;

typedef struct YWGUI_LRCBListAddData_s
{
    YWGUI_ListItemShapeInfo_T* pListItemBgShape;            // 行背景
    YWGUI_PosbarDef_T* pPosbarDef;                          // Listbox的Posbar的默认结构

}YWGUI_LRCBListAddData_T;
typedef YWGUI_LRCBListAddData_T* YWGUI_LRCBListAddData_P;

typedef struct YWGUI_LRCombobox_AddData_s
{
    YWGUI_LRCBTextShapeInfo_T* pTextShape;
    //List信息
    S32 Offsetx;//list相对于LRCombobox控件的x偏移，可以为负数
    S32 Offsety;//list相对于LRCombobox控件的y偏移，可以为负数
    S32 w;//List的宽
    S32 h;//List的高
    YWGUI_ShapeInfo_T* pListShape;
    YWGUI_LRCBListAddData_T* pListAddData;
}YWGUI_LRCombobox_AddData_T;
typedef YWGUI_LRCombobox_AddData_T* YWGUI_LRCombobox_AddData_P;

//add by Eagle 2009-05-06
//ListTable Structure
//===================================ListTable结构定义========================================
typedef struct YWGUI_LTShapeState_s
{
    YWGUI_GraphCollect_T *  pShapeGraph;
    YWGUI_ShapeColor_T *    pShapeColor;
}YWGUI_LTShapeState_T;

typedef struct YWGUI_LTMarkIcon_s
{
    YWGUI_GraphCell_T* pNormal;
    YWGUI_GraphCell_T * pAFocus;
    YWGUI_GraphCell_T * pSFocus;
    YWGUI_GraphCell_T * pDisable;
}YWGUI_LTMarkIcon_T;

typedef struct YWGUI_LTShapeInfo_s
{
    YWGUI_LTShapeState_T * pNormal;
    YWGUI_LTShapeState_T * pAFocus;
    YWGUI_LTShapeState_T * pSFocus;
    YWGUI_LTShapeState_T * pDisable;
}YWGUI_LTShapeInfo_T;

typedef struct YWGUI_LTAddData_s
{
    U16                    ColNum;
    U16                    ViewLineNum;
    U16 *                  pColWidth;
    YWGUI_LTShapeInfo_T ** pColShapeInfo;
    //YWGUI_ShapeInfo_T *    pPOBShapeInfo;
    //U16                    POBThumbSize;
    YWGUI_PosbarDef_T*     pPosbarDef;
    U16                    MarkWidth;
    YWGUI_LTShapeInfo_T *  pMarkShapeInfo;
    YWGUI_LTMarkIcon_T *   pMarkIcon;
}YWGUI_LTAddData_T;

typedef enum YWGUI_LTItemType_e
{
    YWGUI_LTINFO_TEXT = 0,
    YWGUI_LTINFO_PIC,
}YWGUI_LTItemType_T;

typedef struct YWGUI_LTItemInfo_s
{
    YWGUI_LTItemType_T      Type;
    union
    {
        YWGUI_Char_T *      pText;
        YWGUI_GraphCell_T *  pDibmp;
    }Info;
}YWGUI_LTItemInfo_T;

#if 1
typedef enum YWGUI_ContainerWesItem_e
{
    //窗口外观方案

    YWGUI_CONTAINER_STATUS_NORMAL=0,
    YWGUI_CONTAINER_STATUS_DISABLED,
    YWGUI_CONTAINER_STATUS_AFOCUS,
    YWGUI_CONTAINER_STATUS_SFOCUS,
    YWGUI_CONTAINER_STATUS_ANORMAL,
    YWGUI_CONTAINER_STATUS_SNORMAL,

    YWGUI_CONTAINER_WES_STATUS_NUM
}YWGUI_ContainerWesItem_E;

typedef struct YWGUI_ContainerShapeInfo_s
{
    YWGUI_ShapeState_T* ptShape[YWGUI_CONTAINER_WES_STATUS_NUM];//指针数组
}YWGUI_ContainerShapeInfo_T;


typedef struct  YWGUI_ContainerCtrlTemplate_s
{
    /** Class name of the control */
    const S8* class_name;

    /** Control style */
    DWORD       dwStyle;

    /** Control extended style */
    DWORD       dwExStyle;

    //相对于容器控件的偏移
    S32         x, y, w, h;

    /** Control identifier */
    U16         id;

    /** Control caption id*/
    S32  idStr;

    /** Additional data */
    DWORD       dwAddData;

    YWGUI_ContainerShapeInfo_T*  ptShapeInfo;

}YWGUI_ContainerCtrlTemplate_T;

typedef struct YWGUI_ContainerAddData_s
{
    U32                             ControlNum;
    YWGUI_ContainerCtrlTemplate_T * pCtrlTemplate;

}YWGUI_ContainerAddData_T;
#endif

/*******************************************************************************
***********************************宏函数定义*************************************
*******************************************************************************/

#define YWGUI_GetErrorCode(code)   (((code) ==YW_NO_ERROR )?YW_NO_ERROR: ((code) - YW_MODULE_SET_ID (YWMID_MODULE_GUI_ID )+1))

#define YWGUI_LOWORD(l)             ((U16)((U32)(l)))
#define YWGUI_HIWORD(l)             ((U16)((((U32)(l)) >> 16) & 0xFFFF))
#define YWGUI_MAKEDWORD(low,high)   ((DWORD)(((U16)(low)) | (((DWORD)((U16)(high))) << 16)))

#define YWGUI_ARRAY_SIZE(a)         (sizeof((a))/sizeof((a)[0])) //返回数组元素个数

#define YWGUI_RECT_WIDTH(pRect)       ((pRect)->right - (pRect)->left)
#define YWGUI_RECT_HEIGHT(pRect)      ((pRect)->bottom - (pRect)->top)
#define YWGUI_GET_WIDTH(left,right)   ((right)-(left))
#define YWGUI_GET_HEIGHT(top,bottom)  ((bottom)-(top))
#define YWGUI_RECT_LEFT(right,width)  ((right)-(width))
#define YWGUI_RECT_RIGHT(left,width)  ((left)+(width))
#define YWGUI_RECT_TOP(bottom,height) ((bottom)-(height))
#define YWGUI_RECT_BOTTOM(top,height) ((top)+(height))

#define YWGUI_LOOP_PLUS1(pos,limit)     (((pos)+1)%(limit))
#define YWGUI_LOOP_MINUS1(pos,limit)    (((pos)+(limit)-1)%(limit))

#define YWGUI_MAX(x, y)           (((x) > (y))?(x):(y))
#define YWGUI_MIN(x, y)           (((x) < (y))?(x):(y))

/*前面板数据类型封装*/
/*VFD Io Control Type*/
typedef enum YWGUI_PanelVFDIoControlType_e
{
    YWGUI_PANEL_VFD_IO_CLEAN_ALL = 0,

    /*12G*/
    YWGUI_PANEL_VFD_IO_MP3,
    YWGUI_PANEL_VFD_IO_AC3,
    YWGUI_PANEL_VFD_IO_TVMODE,
    YWGUI_PANEL_VFD_IO_AUDIO,
    YWGUI_PANEL_VFD_IO_ALERT,
    YWGUI_PANEL_VFD_IO_HDD_A1,
    YWGUI_PANEL_VFD_IO_HDD_A2,
    YWGUI_PANEL_VFD_IO_HDD_A3,
    YWGUI_PANEL_VFD_IO_HDD_A4,
    YWGUI_PANEL_VFD_IO_HDD_A5,
    YWGUI_PANEL_VFD_IO_HDD_A6,
    YWGUI_PANEL_VFD_IO_HDD_A7,
    YWGUI_PANEL_VFD_IO_HDD_A8,
    YWGUI_PANEL_VFD_IO_HDD_A9,
    YWGUI_PANEL_VFD_IO_HDD_FULL,
    /*12G*/

    /*11G*/
    YWGUI_PANEL_VFD_IO_PLAY_FASTBAKEWARD,
    YWGUI_PANEL_VFD_IO_PLAY_HEAD,
    YWGUI_PANEL_VFD_IO_PLAY,
    YWGUI_PANEL_VFD_IO_PLAY_TAIL,
    YWGUI_PANEL_VFD_IO_PLAY_FASTFORWARD,
    YWGUI_PANEL_VFD_IO_PLAY_PAUSE,
    YWGUI_PANEL_VFD_IO_REC1,
    YWGUI_PANEL_VFD_IO_MUTE,
    YWGUI_PANEL_VFD_IO_PLAYORDER,
    YWGUI_PANEL_VFD_IO_DUBI,
    YWGUI_PANEL_VFD_IO_CA,
    YWGUI_PANEL_VFD_IO_CI,
    YWGUI_PANEL_VFD_IO_USB,
    YWGUI_PANEL_VFD_IO_DOUBLESCREEN,
    YWGUI_PANEL_VFD_IO_REC2,
    /*11G*/



    /*13G*/
    YWGUI_PANEL_VFD_IO_CLOCK_PM,
    YWGUI_PANEL_VFD_IO_CLOCK_AM,
    YWGUI_PANEL_VFD_IO_CLOCK,
    YWGUI_PANEL_VFD_IO_TIME_SECOND, /*时与分之间的点*/
    YWGUI_PANEL_VFD_IO_DOT2,
    YWGUI_PANEL_VFD_IO_STANDBY,
    YWGUI_PANEL_VFD_IO_TER,
    YWGUI_PANEL_VFD_IO_DISK_S3,
    YWGUI_PANEL_VFD_IO_DISK_S2,
    YWGUI_PANEL_VFD_IO_DISK_S1,
    YWGUI_PANEL_VFD_IO_DISK_S0,
    YWGUI_PANEL_VFD_IO_SAT,
    YWGUI_PANEL_VFD_IO_TIMESHIFT,
    YWGUI_PANEL_VFD_IO_DOT1,
    YWGUI_PANEL_VFD_IO_CAB,
    /*13G*/

    /*10G*/
    YWGUI_PANEL_VFD_IO_TIME_1,
    /*10G*/

    /*9G*/
    YWGUI_PANEL_VFD_IO_TIME_2,
    /*9G*/

    /*1G~8G*/
    YWGUI_PANEL_VFD_IO_STRING,

    YWGUI_PANEL_VFD_SET_DISPLAYMODE, /*设置显示模式*/
    YWGUI_PANEL_VFD_SET_OPERATION_MODE, /*设置操作模式*/
    YWGUI_PANEL_VFD_SET_DISPLAYCONTROL, /*设置显示控制*/

    YWGUI_PANEL_VFD_GET_VFDKEY,
    YWGUI_PANEL_VFD_IO_NUM
}YWGUI_PanelVFDIoControlType_T;

typedef struct YWGUI_PanelStandByKeyParam_s
{
    U32     Num;
    U32     StandByKey[5];
}YWGUI_PanelStandByKeyParam_T;


typedef struct YWGUI_PanelBlueKeyParam_s
{
    U32     Num;
    U32     BlueKey[5];
}YWGUI_PanelBlueKeyParam_T;

/*Front Panel LBD Type*/
typedef enum YWGUI_PanelLBDType_e
{
    YWGUI_PANEL_LBD_TYPE_POWER          =  ( 1 << 0 ),         /*  前面板Power灯 */
    YWGUI_PANEL_LBD_TYPE_SIGNAL         =  ( 1 << 1 ),         /*  前面板 Signal灯 */
    YWGUI_PANEL_LBD_TYPE_MAIL           =  ( 1 << 2 ),         /*  前面板Mail灯 */
    YWGUI_PANEL_LBD_TYPE_AUDIO          =  ( 1 << 3 )          /*  前面板Audio灯 */
}YWGUI_PanelLBDType_T;

/*Front Panel LBD Status*/
typedef enum YWGUI_PanelLBDStatus_e
{
    YWGUI_PANEL_LBD_STATUS_OFF,           /*  LBD灯灭 */
    YWGUI_PANEL_LBD_STATUS_ON,            /*  LBD灯亮     */
    //YWGUI_PANEL_LBD_STATUS_FL             /*  LBD灯闪烁 */
}YWGUI_PanelLBDStatus_T;

/***********************前面板类型封装end*************************/

/*******************************************************************************
***********************************接口函数声明*************************************
*******************************************************************************/

//在定义相关宏函数时需用到的函数声明
//(应用不直接调用这些函数，而是使用包装后的宏函数)
YWGUI_API U32  YWGUI_SetDCAttr (YWGUI_HDc_T hdc, YWGUI_DcAttr_E attr, U32 value);
YWGUI_API U32  YWGUI_GetDCAttr (YWGUI_HDc_T hdc, YWGUI_DcAttr_E attr);


/**********************************init函数*********************************/

/***********************************************************************
函数名称: YWGUI_Init
函数功能: ywgui 初始化
参    数: 无
返 回 值: YW_NO_ERROR -- 初始化成功;YWGUI_ERROR -- 初始化失败
说    明: 1)对应函数是 YWGUI_Term
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_Init(void);

/***********************************************************************
函数名称: YWGUI_Term
函数功能:
参    数: 无
返 回 值: YW_NO_ERROR
说    明: 1) 对应函数是 YWGUI_Init
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_Term(void);


/***********************************************************************
函数名称: YWGUI_Start
函数功能: 启动GUI
参    数: ptCustomParam[in] -- APP传入参数
返 回 值: YW_NO_ERROR -- OK;YWGUI_ERROR -- Failure
说    明: 1) 对应函数是 YWGUI_Stop
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_Start(YWGUI_ImportParams_T* ptImportParam);

/***********************************************************************
函数名称: YWGUI_Stop
函数功能: 停止GUI
参    数: 无
返 回 值: YW_NO_ERROR
说    明: 1) 对应函数是 YWGUI_Start
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_Stop(void);


YWGUI_API YW_ErrorType_T YWGUI_GetOsdLayer(YWGUI_Handle_T*pHandle);

/***********************************************************************
函数名称: YWGUI_SetOsdLayerAlpha
函数功能: 设置OSD layer Alpha值
参    数: pHandle[in]   --
          alphaVal[in]  -- 范围(0-255)
                        0 --    全透明
                        255 --  全显示
返 回 值: YW_NO_ERROR -- OK;
          否则 -- Failure
说    明:
修改记录:
************************************************************************/
//YWGUI_API YW_ErrorType_T YWGUI_SetOsdLayerAlpha(YWGUI_Handle_T pHandle,U32 alphaVal);

/***********************************************************************
函数名称: YWGUI_SetIORect
函数功能: 传入输入输出矩形,完成OSD层的缩放
参    数: prcIn [in] -- 输入矩形(相对OSD画布的坐标)
          prcOut[in] -- 输出矩形(相对屏幕的坐标)
返 回 值: YW_NO_ERROR -- OK;
          否则 -- Failure
说    明:
修改记录:
************************************************************************/
//YWGUI_API YW_ErrorType_T YWGUI_SetIORect(const YWGUI_Rect_T*prcIn, const YWGUI_Rect_T *prcOut);


/**********************************定制ywgui的函数***************************/

/***********************************************************************
函数名称: YWGUI_AddTempletNode
函数功能: 插入对话框模板资源到对话框模板链
参    数: ptTemplate -- 对话框模板结构
返 回 值: YW_NO_ERROR
说    明: 1) 该函数仅限在初始化对话框模板链表的回调函数中调用(即 YWGUI_CustomParams_T::pfnInitDlgTLink)
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_AddTempletNode(const YWGUI_DlgTemplate_T *ptTemplate);


/***********************************************************************
函数名称: YWGUI_SetDefaultColor
函数功能: 修改系统默认的配色方案
参    数: item -- 配色方案项
          pixel -- 颜色值
返 回 值: 配色方案项老的颜色值
说    明: 1) 该函数仅限在定制gui的回调函数中调用(即 YWGUI_CustomParams_T::pfnModifyDefScheme)
************************************************************************/
YWGUI_API   void YWGUI_SetDefaultColor (YWGUI_WecItem_E item, YWGUI_Pixel_T pixel, YWGUI_Pixel_T oldPixel);


/***********************************************************************
函数名称: YWGUI_SetDefaultMetrics
函数功能: 修改系统默认的素材方案
参    数: item -- 素材方案项
          size -- 值
返 回 值: 素材方案项老的值
说    明: 1) 该函数仅限在定制gui的回调函数中调用(即 YWGUI_CustomParams_T::pfnModifyDefScheme)
修改记录:
************************************************************************/
YWGUI_API S32   YWGUI_SetDefaultMetrics(YWGUI_WemItem_E item, S32 size);


/***********************************************************************
函数名称: YWGUI_SetCtrlDefColor
函数功能: 修改控件默认的配色方案
参    数: szClassName [in]--控件类名
          item [in] -- 配色方案项
          pixel [in]-- 颜色值
返 回 值: 控件类配色方案项老的值
说    明: 1) 该函数仅限在定制gui的回调函数中调用(即 YWGUI_CustomParams_T::pfnModifyCtrlDefSche)
************************************************************************/
YWGUI_API void  YWGUI_SetCtrlDefColor (const S8* szClassName,YWGUI_WecItem_E item, YWGUI_Pixel_T new_value, YWGUI_Pixel_T oldValue);

/***********************************************************************
函数名称: YWGUI_SetCtrlDefShapeState
函数功能: 修改控件类默认的外观及配色方案
参    数: szClassName [in]--控件类名
          item[in] --外观方案项(即状态)
          ptShapeState[in] --某状态对应的外观结构,
                            如果为NULL,将把该状态下外观结构置NULL
返 回 值:  YW_NO_ERROR-- 设置成功; 否则--设置失败
说    明: 1) 该函数仅限在定制gui的回调函数中调用(即 YWGUI_CustomParams_T::pfnModifyCtrlDefSche)
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_SetCtrlDefShapeState(const S8* szClassName,YWGUI_WesItem_E item, YWGUI_ShapeState_T* ptShapeState);

/***********************************************************************
函数名称: YWGUI_SetCtrlTextExtra
函数功能: 设置控件字符的缩进，上间距，下间距，字符间距
参    数: hCtrl [in] -- 控件的句柄
                extra [in] --哪个extra属性
                value [in] -- extra 值
返 回 值: YW_NO_ERROR
说    明: indent 在 YWGUI_SS_ROLLDISP  风格 下无效
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetCtrlTextExtra(YWGUI_HWnd_T hCtrl, YWGUI_CtrlTextExtra_E extra, S16 value);

/***********************************************************************
函数名称: YWGUI_SetCtrlTextFormat
函数功能: 设置控件字符format
参    数: hCtrl [in] -- 控件的句柄
                format [in]
返 回 值: YW_NO_ERROR
说    明: 
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetCtrlTextFormat(YWGUI_HWnd_T hCtrl, DWORD format);

/**********************************window函数***************************************/

//创建主窗口
YWGUI_API YW_ErrorType_T YWGUI_CreateMainWindow (YWGUI_MainWinCreate_T* pCreateInfo, YWGUI_HWnd_T* phWnd);


//销毁主窗口
YWGUI_API YW_ErrorType_T YWGUI_DestroyMainWindow(YWGUI_HWnd_T hWnd);

//默认的控件过程函数
YWGUI_API S32  YWGUI_DefaultControlProc (YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam, LPARAM lParam);

//默认的主窗口过程函数
YWGUI_API S32 YWGUI_DefaultMainWinProc (YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam, LPARAM lParam);

/***********************************************************************
函数名称: YWGUI_SetWinProc
函数功能: 设置窗口(主窗口，控件)过程函数
参    数: hWnd[in] -- 窗口句柄
          pfNewProc[in] -- 新的窗口过程函数

返 回 值: 老的窗口过程函数,如果注册失败返回NULL
说    明:
修改记录:
************************************************************************/
YWGUI_API YWGUI_WindowProc_P YWGUI_SetWinProc (YWGUI_HWnd_T hWnd, YWGUI_WindowProc_P pfNewProc);

/***********************************************************************
函数名称: YWGUI_GetWinProc
函数功能: 获取窗口(主窗口，控件)过程函数
参    数: hWnd[in] -- 窗口句柄
返 回 值: 当前窗口过程函数,如果获取失败返回NULL
说    明:
修改记录:
************************************************************************/
YWGUI_API  YWGUI_WindowProc_P YWGUI_GetWinProc (YWGUI_HWnd_T hWnd);

//显示窗口(主窗口/子窗口)
YWGUI_API YW_ErrorType_T  YWGUI_ShowWindow (YWGUI_HWnd_T hWnd, S32 iCmdShow);

/***********************************************************************
函数名称: YWGUI_UpdateShapeState
函数功能: 设置窗口(主窗口/子窗口)某状态下的外观方案及颜色值,
          如果修改的是当前状态的外观方案，将重新计算客户区,并无效整个窗口
参    数:   hWnd[in] -- 窗口句柄
            item[in] --外观方案项(即状态)
            ptShapeState[in] --某状态对应的外观结构
返 回 值:  YW_NO_ERROR-- 设置成功; 否则--设置失败
说    明:   1)该函数只能在指定窗口所附属的消息处理线程中调用


修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T   YWGUI_UpdateShapeState(YWGUI_HWnd_T hWnd, YWGUI_WesItem_E item, YWGUI_ShapeState_T* ptShapeState);


/***********************************************************************
函数名称: YWGUI_UpdateWindow
函数功能: 马上重绘窗口(包括客户区和非客户区)
参    数:   hWnd[in] -- 窗口句柄
返 回 值:  无
说    明:  1)该函数只能在该窗口所附属的消息处理线程中调用

修改记录:
************************************************************************/
YWGUI_API void  YWGUI_UpdateWindow (YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_MoveWindow
函数功能: 移动窗口(主窗口/子窗口)
参    数:   hWnd[in] -- 窗口句柄
            x[in] --相对于父窗口客户区的x坐标(主窗口则是屏幕坐标)
            y[in] --相对于父窗口客户区的y坐标(主窗口则是屏幕坐标)
            w[in] --宽度
            h[in] -- 高度
            bPaint[in] --
            ptShapeInfo[in] -- 移动窗口后原来的外观结构可能不适应，需要重传外观结构
                                如果ptShapeInfo为NULL,不改变原来的外观结构;
                                如果ptshapeInfo结构内部某状态的外观为NULL，不改变该状态的外观结构
返 回 值:
说    明:   1)该函数只能在该窗口所附属的消息处理线程中调用
            2)如果ptShapeInfo为NULL并且窗口位置未改变，没有移动效果
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_MoveWindow (YWGUI_HWnd_T hWnd, S32 x, S32 y, S32 w, S32 h, BOOL bPaint,YWGUI_ShapeInfo_T *ptShapeInfo);

//使能或disabled 窗口
YWGUI_API BOOL  YWGUI_EnableWindow (YWGUI_HWnd_T hWnd, BOOL bEnable);

/***********************************************************************
函数名称: YWGUI_InvalidateRect
函数功能: 无效客户区矩形
参    数:   hWnd[in] -- 窗口句柄
            pRect[in] -- 相对于本窗口客户区的坐标，如为NULL,则无效整个客户区
            bEraseBkgnd[in] -- 是否擦除背景
返 回 值:
说    明:

修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_InvalidateRect (YWGUI_HWnd_T hWnd, const YWGUI_Rect_T* pRect, BOOL bEraseBkgnd);

/***********************************************************************
函数名称: YWGUI_Invalidate
函数功能: 无效整个窗口(包括窗口框架区和客户区)
参    数:   hWnd[in] -- 窗口句柄
            bEraseBkgnd[in] -- 是否擦除背景
返 回 值:
说    明:

修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_Invalidate (YWGUI_HWnd_T hWnd, BOOL bEraseBkgnd);

/***********************************************************************
函数名称: YWGUI_IsModeDialog
函数功能: 判断主窗口是否模态对话框
参    数:   hWnd[in] -- 传入主窗口句柄
返 回 值:   TRUE -- 模态对话框; FALSE -- 非模态对话框
说    明:

修改记录:
************************************************************************/
YWGUI_API BOOL  YWGUI_IsModeDialog (YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_GetActiveMainHWnd
函数功能: 得到当前活动的主窗口
参    数:   无
返 回 值:   返回当前活动的主窗口句柄
说    明:

修改记录:
************************************************************************/
YWGUI_API YWGUI_HWnd_T YWGUI_GetActiveMainHWnd(void);




/***********************************************************************
函数名称: YWGUI_IsWindowVisible
函数功能: 得到窗口是否可见
参    数:   hWnd[in] -- 窗口句柄
返 回 值:   TRUE -- 可见
            FALSE -- 不可见
说    明:  只要其祖先窗口有一个不可见，则为不可见
************************************************************************/
YWGUI_API BOOL  YWGUI_IsWindowVisible (YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_IsWindowEnabled
函数功能: 得到窗口是否使能状态
参    数:   hWnd[in] -- 窗口句柄
返 回 值:   TRUE -- enable
            FALSE -- disable
说    明:  1)只要其祖先窗口有一个disabled，则为disabled
修改记录:
************************************************************************/
YWGUI_API BOOL  YWGUI_IsWindowEnabled (YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_GetWindowCurrentStatus
函数功能: 得到窗口当前的状态
参    数:   hWnd[in] -- 窗口句柄
返 回 值:   YWGUI_STATUS_NORMAL(=0) -- 窗口当前是非焦点状态
            YWGUI_STATUS_DISABLED(=1) -- disable状态
            YWGUI_STATUS_AFOCUS(=2) -- 窗口当前拥有活动焦点
            YWGUI_STATUS_SFOCUS(=3) -- 窗口当前拥有失活的焦点
            -1 -- 窗口是隐藏状态(或窗口句柄无效)
说    明:  主窗口状态有:YWGUI_STATUS_NORMAL/YWGUI_STATUS_DISABLED/YWGUI_STATUS_AFOCUS/-1
           控件窗口状态有:YWGUI_STATUS_NORMAL/YWGUI_STATUS_DISABLED/YWGUI_STATUS_AFOCUS/YWGUI_STATUS_SFOCUS/-1
************************************************************************/
YWGUI_API S32 YWGUI_GetWindowCurrentStatus(YWGUI_HWnd_T hWnd);


//根据主窗口ID得到主窗口句柄
YWGUI_API YWGUI_HWnd_T YWGUI_GetMainWinById(U16 id);

//根据主窗口句柄得到主窗口ID
YWGUI_API U16 YWGUI_GetMainWinId(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_SetFocus
函数功能: 设置按键焦点到指定的控件窗口
参    数: hWnd[in] -- 指定的控件窗口句柄
返 回 值: 返回先前的焦点窗口 或 YWGUI_NULL_HANDLE(先前没有焦点窗口或异常)
说    明: 1)若hWnd不是控件窗口，该函数没有效果
          2)若控件及其祖先控件是隐藏/disabled/"得不到焦点"的状态，
            该函数没有效果
          3)该函数只能在该控件所附属的消息处理线程中调用
修改记录:
************************************************************************/
YWGUI_API YWGUI_HWnd_T  YWGUI_SetFocus(YWGUI_HWnd_T hWnd);

YWGUI_API YWGUI_HWnd_T YWGUI_SetActiveChild(YWGUI_HWnd_T hParent,YWGUI_HWnd_T hChild);

//得到hParent的按键焦点窗口
YWGUI_API YWGUI_HWnd_T YWGUI_GetFocus(YWGUI_HWnd_T hParent);

/***********************************************************************
函数名称: YWGUI_GetParent
函数功能: 得到父窗口句柄
参    数:   hWnd[in] -- 窗口句柄
返 回 值:   父窗口句柄或 YWGUI_NULL_HANDLE
说    明:   1)主窗口的父窗口是 HWND_DESKTOP
            2)传入的窗口句柄无效返回YWGUI_NULL_HANDLE
************************************************************************/
YWGUI_API YWGUI_HWnd_T  YWGUI_GetParent (YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_GetHosting
函数功能: 得到属主窗口句柄
参    数:   hWnd[in] -- 主窗口句柄
返 回 值:   属主窗口句柄或 YWGUI_NULL_HANDLE
说    明:   1)第一个属主窗口的属主窗口是YWGUI_NULL_HANDLE
            2)传入无效的主窗口句柄返回YWGUI_NULL_HANDLE
************************************************************************/
YWGUI_API YWGUI_HWnd_T  YWGUI_GetHosting (YWGUI_HWnd_T hWnd);

//得到窗口风格
YWGUI_API DWORD YWGUI_GetWindowStyle(YWGUI_HWnd_T hWnd);

//得到窗口扩展风格
YWGUI_API DWORD YWGUI_GetWindowExStyle (YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_SetWindowExStyle
函数功能: 设置窗口扩展风格
参    数:   hWnd[in] -- 窗口句柄
            dwExStyle[in] -- 窗口扩展风格
返 回 值:
说    明:   1)在使用YWGUI_SetWindowExStyle之前应该调用
              YWGUI_GetWindowExStyle获取原来的扩展风格，
              在此基础上进行位逻辑运算得到新扩展风格,
              不应直接随意设置一个扩展风格
            2)该函数只能在该窗口所附属的消息处理线程中调用
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_SetWindowExStyle(YWGUI_HWnd_T hWnd,DWORD dwExStyle);

/***********************************************************************
函数名称: YWGUI_SetWindowStyle
函数功能: 设置窗口风格
参    数:   hWnd[in] -- 窗口句柄
            dwStyle[in] -- 窗口风格
返 回 值:
说    明:   1)在使用YWGUI_SetWindowStyle之前应该调用
              YWGUI_GetWindowStyle获取原来的风格，
              在此基础上进行位逻辑运算得到新风格,
              不应直接随意设置一个风格
            2)该函数只能在该窗口所附属的消息处理线程中调用
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_SetWindowStyle(YWGUI_HWnd_T hWnd,DWORD dwStyle);

/***********************************************************************
函数名称: YWGUI_SetWindowText
函数功能: 设置窗口文本
参    数:   hWnd[in] -- 窗口句柄
            spString[in] -- 文本字符串
返 回 值:
说    明:
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_SetWindowText (YWGUI_HWnd_T hWnd, const YWGUI_Char_T* spString);

/***********************************************************************
函数名称: YWGUI_GetWindowTextLength
函数功能: 得到窗口文本长度(单位: 字符个数)
参    数:   hWnd[in] -- 窗口句柄
返 回 值:   返回窗口文本字符串字符个数(不包括结束符)
说    明:
************************************************************************/
YWGUI_API S32   YWGUI_GetWindowTextLength (YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_GetWindowText
函数功能: 得到窗口文本
参    数:   hWnd[in] -- 窗口句柄
            textBuf[out]--指向文本缓存区
            buf_size[in]-- 缓存区大小(字节个数)
返 回 值:   拷贝到缓存区的字符数,不包括结束符(UCS2 一个字符占两个字节)
说    明:
************************************************************************/
YWGUI_API S32   YWGUI_GetWindowText(YWGUI_HWnd_T hWnd, YWGUI_Char_T* textBuf, U32 buf_size);

//得到窗口的dwAddData数据
YWGUI_API DWORD  YWGUI_GetWindowAdditionalData(YWGUI_HWnd_T hWnd);

//设置窗口的dwAddData数据,返回值为老的dwAddData
YWGUI_API DWORD  YWGUI_SetWindowAdditionalData(YWGUI_HWnd_T hWnd, DWORD newData);

YWGUI_API DWORD  YWGUI_GetWindowAdditionalData2 (YWGUI_HWnd_T hWnd);
YWGUI_API DWORD  YWGUI_SetWindowAdditionalData2 (YWGUI_HWnd_T hWnd, DWORD newData);


YWGUI_API void YWGUI_DumpWindow (YWGUI_HWnd_T hWnd);



/***********************************************************************
函数名称: YWGUI_SetTimer
函数功能: 设置一个定时器
参    数: hWnd[in] --定时器所属窗口句柄
          idTimer[in] -- 定时器ID,该值必须大于0
          elapse [in] -- 定时器触发时间(单位:毫秒)
返 回 值: YW_NO_ERROR -- OK ; 其他 -- 失败
说    明:  1)所有窗口加起来最多可使用32个定时器 (其中保留7个给GUI系统自己使用)
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_SetTimer (YWGUI_HWnd_T hWnd, S32 idTimer, U32 elapse);

/***********************************************************************
函数名称: YWGUI_KillTimer
函数功能: 关闭定时器
参    数: hWnd[in] --定时器所属窗口句柄
          idTimer[in] -- 定时器ID,该值<=0时，关闭该窗口的所有定时器
返 回 值: 可忽略返回值(YW_NO_ERROR/YWGUI_ERROR_NOT_FOUND/YWGUI_ERROR_INVALID_HANDLE)
说    明:
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_KillTimer(YWGUI_HWnd_T hWnd, S32 idTimer);

/***********************************************************************
函数名称: YWGUI_ResetTimer
函数功能: 重设定时器
参    数: hWnd[in] --定时器所属窗口句柄
          idTimer[in] -- 定时器ID,该值必须大于0
          elapse [in] -- 定时器触发时间(单位:毫秒)
返 回 值: YW_NO_ERROR -- OK ; 其他 -- 失败
说    明: 1)若该定时器从未被设置，设置定时器;若已设置该定时器，重设定时器
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_ResetTimer(YWGUI_HWnd_T hWnd, S32 idTimer, U32 elapse);


YWGUI_API YW_ErrorType_T  YWGUI_RegisterImeWindow(S32 id,YWGUI_HWnd_T hOwner,YWGUI_WindowProc_P ImeWindowProc);

YWGUI_API YW_ErrorType_T  YWGUI_UnregisterImeWindow(void);

YWGUI_API YW_ErrorType_T  YWGUI_AddImeGroup(U16 idImeGroup,YWGUI_ImeType_E eImeType,U16 pageCnt,YWGUI_ImeMapTable_T *ptImeMapTblArray);

YWGUI_API YW_ErrorType_T  YWGUI_DelImeGroup(U16 idImeGroup);

//YWGUI_API YW_ErrorType_T  YWGUI_SetDefaultIme(U16 idImeGroup,U16 pageNo);

YWGUI_API S32 YWGUI_DefaultImeWinProc (YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam, LPARAM lParam);

YWGUI_API YW_ErrorType_T  YWGUI_OpenImeWindow(S32 x,S32 y);

YWGUI_API YW_ErrorType_T  YWGUI_CloseImeWindow(void);

/***********************************************************************
函数名称: YWGUI_MoveImeWindow
函数功能:
参    数:  x[in] -- 屏幕坐标(<0 不改变x坐标)
           y[in] -- 屏幕坐标(<0 不改变y坐标)
           w[in] -- 屏幕坐标(<=0 不改变宽度)
           h[in] -- 屏幕坐标(<=0 不改变高度)
返 回 值:
说    明:
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_MoveImeWindow(S32 x, S32 y, S32 w, S32 h);

YWGUI_API YW_ErrorType_T YWGUI_NextImeGroup(void);

YWGUI_API YW_ErrorType_T YWGUI_PrevImeGroup(void);

YWGUI_API YW_ErrorType_T YWGUI_NextImePage(void);

YWGUI_API YW_ErrorType_T  YWGUI_GetCurrentIme(U16* pImeGroupId,U16 *pPageNo);

YWGUI_API YW_ErrorType_T  YWGUI_ProcessImeEvent(YWGUI_ImeEvent_E eEvent);


/**********************************dialog/ctrl函数***************************/

//注册控件类型
YWGUI_API BOOL YWGUI_RegisterWindowClass (YWGUI_WndClass_P pWndClass);

//注销控件类型
YWGUI_API BOOL YWGUI_UnregisterWindowClass (const S8* szClassName);

//创建无模态对话框(对话框是使用资源模板创建的主窗口)
YWGUI_API YW_ErrorType_T  YWGUI_CreateDialog(S32 id,
                    YWGUI_HWnd_T hOwner, YWGUI_WindowProc_P DlgProc, LPARAM lParam,YWGUI_HWnd_T*phDlg);

//创建模态对话框(对话框是使用资源模板创建的主窗口)
YWGUI_API YW_ErrorType_T YWGUI_DialogBox (S32 id, YWGUI_HWnd_T hOwner, YWGUI_WindowProc_P DlgProc, LPARAM lParam,S32 *pRetCode);

//创建控件窗口(即子窗口)
YWGUI_API YW_ErrorType_T  YWGUI_CreateWidgetWindow (const S8* spClassName, const YWGUI_Char_T* spCaption, S32 idStr, DWORD dwStyle, DWORD dwExStyle, U16 id,
                  S32 x, S32 y, S32 w, S32 h, YWGUI_HWnd_T hParentWnd,DWORD dwAddData,YWGUI_ShapeInfo_T* ptShapeInfo,YWGUI_HWnd_T *phWnd);

//销毁模态对话框
YWGUI_API YW_ErrorType_T  YWGUI_EndDialog (YWGUI_HWnd_T hDlg, S32 endCode);

//销毁控件窗口(即子窗口)
YWGUI_API YW_ErrorType_T YWGUI_DestroyWidgetWindow (YWGUI_HWnd_T hWnd);

//默认的对话框过程函数
YWGUI_API S32  YWGUI_DefaultDialogProc (YWGUI_HWnd_T hWnd, S32 message,WPARAM wParam, LPARAM lParam);


//根据TAB 序(TAB序是子窗口的创建顺序),得到对话框(主窗口)内下一个将要获得按键焦点窗口
YWGUI_API YWGUI_HWnd_T  YWGUI_GetNextDlgTabItem (YWGUI_HWnd_T hDlg, YWGUI_HWnd_T hCtl, BOOL bPrevious);

//根据控件ID得到控件窗口句柄
YWGUI_API YWGUI_HWnd_T  YWGUI_GetDlgItem (YWGUI_HWnd_T hDlg, S32 nIDDlgItem);

//根据控件窗口句柄得到控件ID
YWGUI_API U16  YWGUI_GetDlgCtrlID (YWGUI_HWnd_T hCtrl);

//add by Eagle 2009-6-8
/***********************************************************************
函数名称: YWGUI_StaticSetXOffset
函数功能: 设置static控件字符的横向偏移
参    数: hCtrl [in] -- static控件的句柄
          offset [in] -- 偏移量,以像素为单位
返 回 值: YW_NO_ERROR
说    明: 仅在 YWGUI_SS_LEFT 或 默认风格 下才生效
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_StaticSetXOffset(YWGUI_HWnd_T hCtrl, U16 offset);

/***********************************************************************
函数名称: YWGUI_StaticSetYOffset
函数功能: 设置static控件字符的纵向偏移
参    数: hCtrl [in] -- static控件的句柄
          offset [in] -- 偏移量,以像素为单位
返 回 值: YW_NO_ERROR
说    明: 仅在 YWGUI_SS_TOP 或 默认风格 下才生效
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_StaticSetYOffset(YWGUI_HWnd_T hCtrl, U16 offset);

/***********************************************************************
函数名称: YWGUI_ButtonSetXOffset
函数功能: 设置 button 控件字符的横向偏移
参    数: hCtrl [in] -- button 控件的句柄
          offset [in] -- 偏移量,以像素为单位
返 回 值: YW_NO_ERROR
说    明: 仅在 YWGUI_BS_LEFT 或 默认风格 下才生效
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_ButtonSetXOffset(YWGUI_HWnd_T hCtrl, U16 offset);

/***********************************************************************
函数名称: YWGUI_ButtonSetYOffset
函数功能: 设置 button 控件字符的横向偏移
参    数: hCtrl [in] -- button 控件的句柄
          offset [in] -- 偏移量,以像素为单位
返 回 值: YW_NO_ERROR
说    明: 仅在 YWGUI_BS_TOP 或 默认风格 下才生效
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_ButtonSetYOffset(YWGUI_HWnd_T hCtrl, U16 offset);

/***********************************************************************
函数名称: YWGUI_SetPicture
函数功能:   设置picture控件的位图
参    数:   hWnd [in] -- picture控件的句柄
            pDibmp [in] -- 设备无关位图结构指针
            bUpdate [in] -- 是否马上更新显示
返 回 值:
说    明:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetPicture(YWGUI_HWnd_T hWnd,const YWGUI_GraphCell_T* pDibmp,BOOL bUpdate);

/***********************************************************************
函数名称: YWGUI_SetPosbarRange
函数功能:   设置 posbar 控件的 range 值
参    数:   hWnd [in] -- posbar 控件的句柄
            range[in] -- (max - min) ,其中 min 为常数0 ,故实际为 max 值
返 回 值:
说    明:
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetPosbarRange(YWGUI_HWnd_T hWnd,U32 range);


/***********************************************************************
函数名称: YWGUI_SetPosbarPosVal
函数功能:   设置 posbar 控件的 pos 值
参    数:   hWnd [in] -- posbar 控件的句柄
            posVal[in]
返 回 值:
说    明:
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetPosbarPosVal(YWGUI_HWnd_T hWnd,U32 posVal);


/***********************************************************************
函数名称: YWGUI_GetPosbarPos
函数功能:   获得 posbar 控件的 pos 值和 range 值
参    数:   hWnd [in] -- posbar 控件的句柄
            pPos[out] -- 返回 pos 值
            pRange[out]--返回 (max-min),因min 为常数0,实际返回的是 max 值
返 回 值:
说    明:
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_GetPosbarPos(YWGUI_HWnd_T hWnd,U32* pPos,U32 *pRange);

/***********************************************************************
函数名称: YWGUI_SetPosbarThumbSize
函数功能:   设置 posbar 控件的 thumb size 值
参    数:   hWnd [in] -- posbar 控件的句柄
            thumbSize[in]
返 回 值:
说    明:
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetPosbarThumbSize(YWGUI_HWnd_T hWnd,U32 thumbSize);

/***********************************************************************
函数名称: YWGUI_GetPosBarThumbRect
函数功能:   获取滑块的位置
参    数:   hWnd [in] -- posbar 控件的句柄
                     prcThumb[in]
返 回 值:
说    明:
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_GetPosBarThumbRect(YWGUI_HWnd_T  hWnd,YWGUI_Rect_T *prcThumb);


/***********************************************************************
函数名称: YWGUI_SetProgressBarRange
函数功能:   设置 Progress bar 控件的 range 值
参    数:   hWnd [in] -- Progress 控件的句柄
            range[in] -- (max - min) ,其中 min 为常数0 ,故实际为 max 值
返 回 值:
说    明:
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetProgressBarRange(YWGUI_HWnd_T hWnd,U32 range);


/***********************************************************************
函数名称: YWGUI_SetProgressBarPosVal
函数功能:   设置 ProgressBar 控件的 pos 值
参    数:   hWnd [in] -- ProgressBar 控件的句柄
            posVal[in]
返 回 值:
说    明:
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetProgressBarPosVal(YWGUI_HWnd_T hWnd,U32 posVal);


/***********************************************************************
函数名称: YWGUI_GetProgressBarPos
函数功能:   获得 ProgressBar 控件的 pos 值和 range 值
参    数:   hWnd [in] -- ProgressBar 控件的句柄
            pPos[out] -- 返回 pos 值
            pRange[out]--返回 (max-min),因min 为常数0,实际返回的是 max 值
返 回 值:
说    明:
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_GetProgressBarPos(YWGUI_HWnd_T hWnd,U32* pPos,U32 *pRange);

/***********************************************************************
函数名称: YWGUI_SetProgressBarStepSize
函数功能:   设置 posbar 控件的 thumb size 值
参    数:   hWnd [in] -- posbar 控件的句柄
            stepSize[in] -- 步进大小(单位:象素)
            thumbSize[in]-- 填充块的大小(单位:象素)
返 回 值:
说    明:
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetProgressBarStepSize(YWGUI_HWnd_T hWnd,U32 stepSize,U32 thumbSize);

/***********************************************************************
函数名称: YWGUI_GetProgressBarRect
函数功能:   获得 ProgressBar 控件的画图的范围
参    数:   hWnd [in] -- ProgressBar 控件的句柄
            pRect[out] --  获取进度条的绘图区域
返 回 值:
说    明:
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_GetProgressBarRect(YWGUI_HWnd_T hWnd, YWGUI_Rect_T *pRect);
//Listview 空间接口函数
/***********************************************************************
函数名称: YWGUI_LVAddColumn
函数功能: 添加列
参    数:   hWnd[in] --  控件句柄
            pLVColumn[in] -- 行结构
返 回 值:   -1失败，0成功
说    明:
           YWGUI_LVM_ADDCOLUMN
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVAddColumn(YWGUI_HWnd_T hWnd, YWGUI_LVColumn_P pLVColumn);

/***********************************************************************
函数名称: YWGUI_LVAddItem
函数功能: 添加行
参    数:   hWnd[in] --  控件句柄
            ItemIndex[in] -- 要插入的行的索引
返 回 值:   -1失败，0成功
说    明:
           YWGUI_LVM_ADDITEM
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVAddItem(YWGUI_HWnd_T hWnd, U32 ItemIndex);


/***********************************************************************
函数名称: YWGUI_LVSetSubItem
函数功能: 设置各个子项的具体数据
参    数:   hWnd[in] --  控件句柄
            pLVSubItem[in] -- 子项结构
返 回 值:   -1失败，0成功
说    明:
           YWGUI_LVM_SETSUBITEM
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVSetSubItem(YWGUI_HWnd_T hWnd, YWGUI_LVSubItem_P pLVSubItem);

/***********************************************************************
函数名称: YWGUI_LVGetItemCount
函数功能: 得到列表的总行数
参    数:   hWnd[in] --  控件句柄

返 回 值:   总行数
说    明:
           YWGUI_LVM_GETITEMCOUNT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVGetItemCount(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_LVGetColumnWidth
函数功能: 得到列表的指定列的列宽
参    数:   hWnd[in] --  控件句柄
            ColumnIndex[in] -- 列的索引，注意:列索引以0开始
返 回 值:   -1失败，0成功
说    明:
           YWGUI_LVM_GETCOLUMNWIDTH
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVGetColumnWidth(YWGUI_HWnd_T hWnd, U32 ColumnIndex);

/***********************************************************************
函数名称: YWGUI_LVGetSubItemTextLen
函数功能: 得到列表的指定行列的文本长度
参    数:   hWnd[in] --  控件句柄
            ItemIndex[in] -- 行的索引，注意:行索引以0开始
            ColumnIndex[in] -- 列的索引，注意:列索引以0开始
返 回 值:   该子项的文本长度,-1表示出错
说    明:
           YWGUI_LVM_GETSUBITEMLEN
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVGetSubItemTextLen(YWGUI_HWnd_T hWnd,U32 ItemIndex, U32 ColumnIndex);

/***********************************************************************
函数名称: YWGUI_LVGetSubItemText
函数功能: 得到列表的指定行列的文本
参    数:   hWnd[in] --  控件句柄
            ItemIndex[in] -- 行的索引，注意:行索引以0开始
            ColumnIndex[in] -- 列的索引，注意:列索引以0开始
返 回 值:   该子项的文本(YWGUI_Char_T*),-1表示出错
说    明:
           YWGUI_LVM_GETSUBITEMTEXT
修改记录:
************************************************************************/
YWGUI_API YWGUI_Char_T* YWGUI_LVGetSubItemText(YWGUI_HWnd_T hWnd,U32 ItemIndex, U32 ColumnIndex);

/***********************************************************************
函数名称: YWGUI_LVSetHeadHeight
函数功能: 设置列头的高度
参    数:   hWnd[in] --  控件句柄
            HeadHeight[in] -- 列头的高度，注意:列索引以0开始
返 回 值:   -1失败，0成功
说    明:
           YWGUI_LVM_SETHEADHEIGHT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVSetHeadHeight(YWGUI_HWnd_T hWnd, U32 HeadHeight);

/***********************************************************************
函数名称: YWGUI_LVDeleteItem
函数功能: 删除指定行
参    数:   hWnd[in] --  控件句柄
            ItemIndex[in] -- 指定的行的索引,以0开始
返 回 值:   0为删除成功, -1为删除失败
说    明:
           YWGUI_LVM_DELITEM
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVDeleteItem(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
函数名称: YWGUI_LVDeleteAllItem
函数功能: 删除所有定行
参    数:   hWnd[in] --  控件句柄
返 回 值:   0为删除成功, -1为删除失败
说    明:
           YWGUI_LVM_DELALLITEM
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVDeleteAllItem(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_LVDeleteColumn
函数功能: 删除指定列
参    数:   hWnd[in] --  控件句柄
            ColumnIndex[in] -- 指定的列的索引,以0开始
返 回 值:   0为删除成功, -1为删除失败
说    明:
           YWGUI_LVM_DELCOLUMN
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVDeleteColumn(YWGUI_HWnd_T hWnd, U32 ColumnIndex);

/***********************************************************************
函数名称: YWGUI_LVPageDown
函数功能: 向下翻页
参    数:   hWnd[in] --  控件句柄
返 回 值:   0为删除成功, -1为删除失败
说    明:
           YWGUI_LVM_PAGEDOWN
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVPageDown(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_LVPageUp
函数功能: 向上翻页
参    数:   hWnd[in] --  控件句柄
返 回 值:   0为删除成功, -1为删除失败
说    明:
           YWGUI_LVM_PAGEUP
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVPageUp(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_LVGetColumnCount
函数功能: 得到列数
参    数:   hWnd[in] --  控件句柄
返 回 值:   列数
说    明:
           YWGUI_LVM_GETCOLUMNCOUNT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVGetColumnCount(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_LVGetCurHotItemIndex
函数功能: 获取当前焦点项索引
参    数:   hWnd[in] --  控件句柄
返 回 值:   当前焦点项索引
说    明:
           YWGUI_LVM_GETCURSEL
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVGetCurHotItemIndex(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_LVSetCurHotItemIndex
函数功能: 设置当前焦点项索引
参    数:   hWnd[in] --  控件句柄
            HotItemIndex[in] --  新焦点行索引
返 回 值:   当前焦点项索引
说    明:
           YWGUI_LVM_SETCURSEL
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVSetCurHotItemIndex(YWGUI_HWnd_T hWnd, U32 HotItemIndex);

/***********************************************************************
函数名称: YWGUI_LVGetItemState
函数功能: 获取指定行的状态
参    数:   hWnd[in] --  控件句柄
            ItemIndex[in] --  要获取的行的索引
返 回 值:   0表示YWGUI_LVIF_NORMAL, 1表示YWGUI_LVIF_CHECKED, 2表示YWGUI_LVIF_SKIP
说    明:
           YWGUI_LVM_GETITEMSTATE
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVGetItemState(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
函数名称: YWGUI_LVSetItemState
函数功能: 设置指定行的行状态
参    数:   hWnd[in] --  控件句柄
            ItemIndex[in] --  要设置的行的索引
            ItemState[in] --  0表示YWGUI_LVIF_NORMAL, 1表示YWGUI_LVIF_CHECKED, 2表示YWGUI_LVIF_SKIP
返 回 值:   0设置成功，-1设置失败
说    明:
           YWGUI_LVM_SETITEMSTATE
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVSetItemState(YWGUI_HWnd_T hWnd, U32 ItemIndex, U32 ItemState);

/***********************************************************************
函数名称: YWGUI_LVSort
函数功能: 对列表的指定列进行升降序排列
参    数:   hWnd[in] --  控件句柄
            SortMode[in] --  排序的模式 0 YWGUI_LVSORT_NOTSORT, 1 YWGUI_LVSORT_ASC, 2 YWGUI_LVSORT_DESC
            SortColumnIndex[in] --  要排序的列,以0开始
返 回 值:   0设置成功，-1设置失败
说    明:
           YWGUI_LVM_SORT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVSort(YWGUI_HWnd_T hWnd, U32 SortMode, U32 SortColumnIndex);

/***********************************************************************
函数名称: YWGUI_LVGetVisibleCount
函数功能: 设置ListView控件可见行数
参    数:   hWnd[in] --  控件句柄
返 回 值:   可见行数
说    明:
           YWGUI_LVM_GETVISIBLECOUNT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVGetVisibleCount(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_LVSetVisibleCount
函数功能: 设置ListView控件可见行数
参    数:   hWnd[in] --  控件句柄
            VisibleCount[in] --  指定的可见行数
返 回 值:   0设置成功，-1设置失败
说    明:
           YWGUI_LVM_SETVISIBLECOUNT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVSetVisibleCount(YWGUI_HWnd_T hWnd, U32 VisibleCount);

/***********************************************************************
函数名称: YWGUI_LVSelectAll
函数功能: 选中指定行或取消选中指定行
参    数:   hWnd[in] --  控件句柄
            bSelectAll[in] --  True表示选中所有行, False表示取消选中所有行
返 回 值:   0设置成功，-1设置失败
说    明:
           YWGUI_LVM_SETSELECTALL
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVSelectAll(YWGUI_HWnd_T hWnd, BOOL bSelectAll);

/***********************************************************************
函数名称: YWGUI_LVSelectOthers
函数功能: 反向选择
参    数:   hWnd[in] --  控件句柄
返 回 值:   0设置成功，-1设置失败
说    明:
           YWGUI_LVM_SETSELECTOTHERS
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LVSelectOthers(YWGUI_HWnd_T hWnd);


//sedit 控件接口函数
/***********************************************************************
函数名称: YWGUI_SEditGetTextLen
函数功能: 获取文本长度
参    数:   hWnd[in] --  控件句柄
返 回 值:   文本长度,不包含\0
说    明:
           YWGUI_SEM_GETTEXTLEN
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_SEditGetTextLen(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_SEditSetPasswordChar
函数功能: 设置密码显示字符
参    数:   hWnd[in] --  控件句柄
            cChar[in] --  密码显示字符
返 回 值:
说    明:
           YWGUI_SEM_SETPASSWORDCHAR
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_SEditSetPasswordChar(YWGUI_HWnd_T hWnd, YWGUI_Char_T cChar);

/***********************************************************************
函数名称: YWGUI_SEditGetPasswordChar
函数功能: 获取密码显示字符
参    数:   hWnd[in] --  控件句柄
返 回 值:   密码显示字符(YWGUI_Char_T)
说    明:
           YWGUI_SEM_GETPASSWORDCHAR
修改记录:
************************************************************************/
YWGUI_API YWGUI_Char_T YWGUI_SEditGetPasswordChar(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_SEditGetMaxLimit
函数功能: 获取Edit的字符限制数(包含\n)
参    数:   hWnd[in] --  控件句柄
返 回 值:   Edit的字符限制数
说    明:
           YWGUI_SEM_GETMAXLIMIT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_SEditGetMaxLimit(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_SEditSetMaxLimit
函数功能: 设置Edit的字符限制数(包含\n)
参    数:   hWnd[in] --  控件句柄
返 回 值:
说    明:
           YWGUI_SEM_GETMAXLIMIT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_SEditSetMaxLimit(YWGUI_HWnd_T hWnd, U32 MaxLimit);

/***********************************************************************
函数名称: YWGUI_SEditSetEditStatus
函数功能: 设置Edit的编辑状态
参    数:   hWnd[in] --  控件句柄
            bEnterEditStatus[in] --  FALSE表示非编辑状态,否则表示进入编辑状态
返 回 值:   :-1 设置失败(当前焦点不在当前要设置的Edit上), 0设置成功.
说    明:  只有当前焦点在当前设置的Edit控件上才可以设置成功.
           YWGUI_SEM_SETEDITSTATUS
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_SEditSetEditStatus(YWGUI_HWnd_T hWnd, BOOL bEnterEditStatus);

/***********************************************************************
函数名称: YWGUI_SEditGetEditStatus
函数功能: 获取Edit的编辑状态
参    数:   hWnd[in] --  控件句柄
返 回 值:   FALSE表示非编辑状态,否则表示进入编辑状态
说    明:
           YWGUI_SEM_GETEDITSTATUS
修改记录:
************************************************************************/
YWGUI_API BOOL YWGUI_SEditGetEditStatus(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_SEditGetCursorPos
函数功能: 获取Edit中光标的位置(0为起始)
参    数:   hWnd[in] --  控件句柄
返 回 值:   光标的位置
说    明:
           YWGUI_SEM_GETCURSORPOS
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_SEditGetCursorPos(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_SEditSetCursorPos
函数功能: 设置Edit中光标的位置(0为起始)
参    数:   hWnd[in] --  控件句柄
            NewPos[in] --  光标的新位置
返 回 值:   光标的位置
说    明:
           YWGUI_SEM_SETCURSORPOS
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_SEditSetCursorPos(YWGUI_HWnd_T hWnd, U32 NewPos);

//Edit 接口函数
/***********************************************************************
函数名称: YWGUI_EditGetTextLen
函数功能: 获取文本长度
参    数:   hWnd[in] --  控件句柄
返 回 值:   文本长度,不包含\0
说    明:
           YWGUI_EM_GETTEXTLEN
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_EditGetTextLen(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_EditSetPasswordChar
函数功能: 设置密码显示字符
参    数:   hWnd[in] --  控件句柄
            cChar[in] --  密码显示字符
返 回 值:
说    明:
           YWGUI_EM_SETPASSWORDCHAR
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_EditSetPasswordChar(YWGUI_HWnd_T hWnd, YWGUI_Char_T cChar);

/***********************************************************************
函数名称: YWGUI_EditGetPasswordChar
函数功能: 获取密码显示字符
参    数:   hWnd[in] --  控件句柄
返 回 值:   密码显示字符(YWGUI_Char_T)
说    明:
           YWGUI_EM_GETPASSWORDCHAR
修改记录:
************************************************************************/
YWGUI_API YWGUI_Char_T YWGUI_EditGetPasswordChar(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_EditGetMaxLimit
函数功能: 获取Edit的字符限制数(包含\n)
参    数:   hWnd[in] --  控件句柄
返 回 值:   Edit的字符限制数
说    明:
           YWGUI_EM_GETMAXLIMIT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_EditGetMaxLimit(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_EditSetMaxLimit
函数功能: 设置Edit的字符限制数(包含\n)
参    数:   hWnd[in] --  控件句柄
返 回 值:
说    明:
           YWGUI_EM_SETMAXLIMIT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_EditSetMaxLimit(YWGUI_HWnd_T hWnd, U32 MaxLimit);

/***********************************************************************
函数名称: YWGUI_EditSetEditStatus
函数功能: 设置Edit的编辑状态
参    数:   hWnd[in] --  控件句柄
            bEnterEditStatus[in] --  FALSE表示非编辑状态,否则表示进入编辑状态
返 回 值:   :-1 设置失败(当前焦点不在当前要设置的Edit上), 0设置成功.
说    明:  只有当前焦点在当前设置的Edit控件上才可以设置成功.
           YWGUI_EM_SETEDITSTATUS
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_EditSetEditStatus(YWGUI_HWnd_T hWnd, BOOL bEnterEditStatus);

/***********************************************************************
函数名称: YWGUI_EditGetEditStatus
函数功能: 获取Edit的编辑状态
参    数:   hWnd[in] --  控件句柄
返 回 值:   FALSE表示非编辑状态,否则表示进入编辑状态
说    明:
           YWGUI_EM_GETEDITSTATUS
修改记录:
************************************************************************/
YWGUI_API BOOL YWGUI_EditGetEditStatus(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_EditGetCursorPos
函数功能: 获取Edit中光标的位置(0为起始)
参    数:   hWnd[in] --  控件句柄
返 回 值:   光标的位置
说    明:
           YWGUI_EM_GETCURSORPOS
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_EditGetCursorPos(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_EditSetCursorPos
函数功能: 设置Edit中光标的位置(0为起始)
参    数:   hWnd[in] --  控件句柄
            NewPos[in] --  光标的新位置
返 回 值:   光标的位置
说    明:
           YWGUI_EM_SETCURSORPOS
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_EditSetCursorPos(YWGUI_HWnd_T hWnd, U32 NewPos);

/***********************************************************************
函数名称: YWGUI_EditPageUp
函数功能: 向上翻页
参    数:   hWnd[in] --  控件句柄
返 回 值:   光标的位置
说    明:  仅限多行文本风格时使用
           YWGUI_EM_PAGEUP
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_EditPageUp(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_EditPageDown
函数功能: 向下翻页
参    数:   hWnd[in] --  控件句柄
返 回 值:   光标的位置
说    明:  仅限多行文本风格时使用
           YWGUI_EM_PAGEDOWN
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_EditPageDown(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_EditScrollPage
函数功能: 翻到指定页，0表示翻到最后一页
参    数:   hWnd[in] --  控件句柄
            PageIndex[in] --  翻页的索引，0表示翻到最后一页
返 回 值:   无
说    明: 仅限多行文本风格时使用

修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_EditScrollPage(YWGUI_HWnd_T hWnd, U32 PageIndex);

/***********************************************************************
函数名称: YWGUI_EditGetTotalLineCount
函数功能: 获取总行数
参    数:   hWnd[in] --  控件句柄
返 回 值:   返回总行数
说    明: 仅限多行文本风格时使用
           YWGUI_EM_GETTOTALLINECOUNT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_EditGetTotalLineCount(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_EditGetTopLineNo
函数功能: 获取首行的索引
参    数:   hWnd[in] --  控件句柄
返 回 值:   返回首行的索引(索引以0开始计算)
说    明: 仅限多行文本风格时使用
           YWGUI_EM_TOPLINENO
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_EditGetTopLineNo(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_EditGetVisibleLineCount
函数功能: 获取可见行数
参    数:   hWnd[in] --  控件句柄
返 回 值:   返回可见行数
说    明: 仅限多行文本风格时使用
           YWGUI_EM_VISIBLELINECOUNT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_EditGetVisibleLineCount(YWGUI_HWnd_T hWnd);

//listbox 接口函数
/***********************************************************************
函数名称: YWGUI_LBAddItem
函数功能: 添加行
参    数:   hWnd[in] --  控件句柄
            pLBItem[in] --  传Item结构指针
返 回 值:
说    明:
           YWGUI_LB_ADDSTRING
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBAddItem(YWGUI_HWnd_T hWnd, YWGUI_LBItem_P pLBItem);


/***********************************************************************
函数名称: YWGUI_LBDeleteItem
函数功能: 删除指定行
参    数:   hWnd[in] --  控件句柄
            ItemIndex[in] --  指定行索引, 注意行索引以0开始
返 回 值: 0成功，－1失败
说    明:
           YWGUI_LB_DELETESTRING
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBDeleteItem(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
函数名称: YWGUI_LBGetItemCount
函数功能: 获取列表行数
参    数:   hWnd[in] --  控件句柄
返 回 值: 0成功，－1失败
说    明:
           YWGUI_LB_GETCOUNT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBGetItemCount(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_LBGetCurHotItemIndex
函数功能: 获取当前焦点行索引
参    数:   hWnd[in] --  控件句柄
返 回 值: 列表的焦点行索引, 索引以0开始
说    明:
           YWGUI_LB_GETCURSEL
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBGetCurHotItemIndex(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_LBSetCurHotItemIndex
函数功能: 设置焦点行索引
参    数:   hWnd[in] --  控件句柄
            ItemIndex[in] --  新焦点行索引, 注意行索引以0开始
返 回 值: 老索引
说    明:
           YWGUI_LB_SETCURSEL
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBSetCurHotItemIndex(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
函数名称: YWGUI_LBGetItemTextLen
函数功能: 获取指定行文本长度
参    数:   hWnd[in] --  控件句柄
            ItemIndex[in] --  行索引, 注意行索引以0开始
返 回 值: 指定行文本长度
说    明: 返回的是不包括结束符的字符个数
           YWGUI_LB_GETTEXTLEN
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBGetItemTextLen(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
函数名称: YWGUI_LBGetItemText
函数功能: 获取指定行文本
参    数:   hWnd[in] --  控件句柄
            ItemIndex[in] --  行索引, 注意行索引以0开始
            pStr[out] --  将指定行文本copy到lParam所指的地址空间,(输出参数);
                       注意此参数不可为空
返 回 值: 0获取成功，-1获取失败
说    明:
           YWGUI_LB_GETTEXT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBGetItemText(YWGUI_HWnd_T hWnd, U32 ItemIndex, YWGUI_Char_T* pStr);


/***********************************************************************
函数名称: YWGUI_LBSetItemText
函数功能: 设置指定行文本
参    数:   hWnd[in] --  控件句柄
            ItemIndex[in] --  行索引, 注意行索引以0开始
            pStr[in] --  新文本的指针
返 回 值: 0获取成功，-1获取失败
说    明:
           YWGUI_LB_SETTEXT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBSetItemText(YWGUI_HWnd_T hWnd, U32 ItemIndex, YWGUI_Char_T* pStr);

/***********************************************************************
函数名称: YWGUI_LBSetItemVisibleCount
函数功能: 设置列表的可见项数
参    数:   hWnd[in] --  控件句柄
            VisibleCount[in] --  列表的新可见数
返 回 值: 0设置成功, -1设置失败
说    明:
           YWGUI_LB_SETITEMVISIBLES
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBSetItemVisibleCount(YWGUI_HWnd_T hWnd, U32 VisibleCount);


/***********************************************************************
函数名称: YWGUI_LBGetItemVisibleCount
函数功能: 获取列表的可见项数
参    数:   hWnd[in] --  控件句柄
返 回 值: 列表的可见项数
说    明:
           YWGUI_LB_GETITEMVISIBLES
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBGetItemVisibleCount(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_LBGetTopIndex
函数功能: 获取要显示的列表的顶行索引
参    数:   hWnd[in] --  控件句柄
返 回 值: 顶行索引, 注意行缩影以0开始.
说    明:
           YWGUI_LB_GETTOPINDEX
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBGetTopIndex(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_LBPageDown
函数功能: 向下翻页
参    数:   hWnd[in] --  控件句柄
返 回 值:
说    明:
           YWGUI_LB_PAGEDOWN
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBPageDown(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_LBPageUp
函数功能: 向上翻页
参    数:   hWnd[in] --  控件句柄
返 回 值:
说    明:
           YWGUI_LB_PAGEUP
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBPageUp(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_LBSelectAll
函数功能: 选中或取消选中所有行
参    数:   hWnd[in] --  控件句柄
            bSelect[in] --  TRUE表示设置为选中，否则表示取消选中
返 回 值: 0设置成功，-1设置失败
说    明:
           YWGUI_LB_SETSELECTALL
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBSelectAll(YWGUI_HWnd_T hWnd, BOOL bSelect);

/***********************************************************************
函数名称: YWGUI_LBSelectOthers
函数功能: 反向选择
参    数:   hWnd[in] --  控件句柄
返 回 值: 0设置成功，-1设置失败
说    明:
           YWGUI_LB_SETSELECTOTHERS
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBSelectOthers(YWGUI_HWnd_T hWnd, BOOL bSelect);

/***********************************************************************
函数名称: YWGUI_LBGetItemState
函数功能: 获取指定行的状态
参    数:   hWnd[in] --  控件句柄
            ItemIndex[in] --  要获取的行的索引
返 回 值: 0表示YWGUI_LVIF_NORMAL, 1表示YWGUI_LVIF_CHECKED, 2表示YWGUI_LVIF_SKIP
说    明:
           YWGUI_LB_GETITEMSTATE
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBGetItemState(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
函数名称: YWGUI_LBGetItemState
函数功能: 设置指定行的行状态
参    数:   hWnd[in] --  控件句柄
            ItemIndex[in] --  要获取的行的索引
            ItemState[in] --  0表示YWGUI_LBIF_NORMAL, 1表示YWGUI_LBIF_CHECKED, 2表示YWGUI_LBIF_SKIP
返 回 值: 0设置成功，－1设置失败
说    明:
           YWGUI_LB_SETITEMSTATE
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBSetItemState(YWGUI_HWnd_T hWnd, U32 ItemIndex, U32 ItemState);

/***********************************************************************
函数名称: YWGUI_LBCurEditItemIndex
函数功能: 获取当前编辑的行的所以,主要在事件YWGUI_LBN_SELCHANGED后,获取改变Checked状态的行的索引
参    数:   hWnd[in] --  控件句柄
返 回 值: 当前编辑的行
说    明:
           YWGUI_LB_GETCUREDITROWINDEX
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBCurEditItemIndex(YWGUI_HWnd_T hWnd);
#if 0
/***********************************************************************
函数名称: YWGUI_LRFindString
函数功能: 查找指定字符串在列表中的第一个位置的行索引(非精确查找)
参    数:   hWnd[in] --  控件句柄
            StartRowIndex[in] --  开始查找的行的索引, 就是从第几行开始查找
            pFindStr[in] --  要查找的字符串的指针
返 回 值: 找到的第一个字符串所在的行索引,如果为-1表示查找失败
说    明:
           YWGUI_LB_FINDSTRING
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBFindString(YWGUI_HWnd_T hWnd, U32 StartRowIndex,YWGUI_Char_T* pFindStr);

/***********************************************************************
函数名称: YWGUI_LBFindStringExact
函数功能: 查找指定字符串在列表中的第一个位置的行索引(精确查找,字符串长度也要一样)
参    数:   hWnd[in] --  控件句柄
            StartRowIndex[in] --  开始查找的行的索引, 就是从第几行开始查找
            pFindStr[in] --  要查找的字符串的指针
返 回 值: 找到的第一个字符串所在的行索引,如果为-1表示查找失败
说    明:
           YWGUI_LB_FINDSTRINGEXACT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LBFindStringExact(YWGUI_HWnd_T hWnd, U32 StartRowIndex,YWGUI_Char_T* pFindStr);
#endif
/***********************************************************************
函数名称: YWGUI_ListBoxSetXOffset
函数功能: 设置static控件字符的横向偏移
参    数: hWnd [in] -- listbox控件的句柄
          XOffset [in] -- 偏移量,以像素为单位
返 回 值: YW_NO_ERROR
说    明: 
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_ListBoxSetXOffset(YWGUI_HWnd_T hWnd, U16 XOffset);

/***********************************************************************
函数名称: YWGUI_ListBoxSetYOffset
函数功能: 设置listbox控件字符的纵向偏移
参    数: hWnd [in] -- listbox控件的句柄
          YOffset [in] -- 偏移量,以像素为单位
返 回 值: YW_NO_ERROR
说    明: 
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_ListBoxSetYOffset(YWGUI_HWnd_T hWnd, U16 YOffset);

//lrcombobox 接口函数
/***********************************************************************
函数名称: YWGUI_LRCBAddItem
函数功能: 添加行
参    数:   hWnd[in] --  控件句柄
            pListItem[in] --  要插入行结构指针
返 回 值: 0成功, -1失败
说    明:
           YWGUI_LRCB_ADDSTRING
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBAddItem(YWGUI_HWnd_T hWnd, YWGUI_LRCBListItem_P pListItem);

/***********************************************************************
函数名称: YWGUI_LRCBDeleteItem
函数功能: 删除指定行
参    数:   hWnd[in] --  控件句柄
            ItemIndex[in] --  要删除的行的索引
返 回 值: 0成功, -1失败
说    明:
           YWGUI_LRCB_DELETESTRING
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBDeleteItem(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
函数名称: YWGUI_LRCBGetCurHotItemIndex
函数功能: 获取当前焦点行索引
参    数:   hWnd[in] --  控件句柄
返 回 值: 列表的焦点行索引, 索引以0开始
说    明:
           YWGUI_LRCB_GETCURSEL
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBGetCurHotItemIndex(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_LRCBSetCurHotItemIndex
函数功能: 设置焦点行索引
参    数:   hWnd[in] --  控件句柄
            ItemIndex[in] --  新焦点行索引, 注意行索引以0开始
返 回 值: 0成功, -1失败
说    明:
           YWGUI_LRCB_SETCURSEL
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBSetCurHotItemIndex(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
函数名称: YWGUI_LRCBGetItemCount
函数功能: 获取列表总行数
参    数:   hWnd[in] --  控件句柄
返 回 值: 列表的行数
说    明:
           YWGUI_LRCB_GETCOUNT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBGetItemCount(YWGUI_HWnd_T hWnd);
#if 0
/***********************************************************************
函数名称: YWGUI_LRCBFindString
函数功能: 查找指定字符串在列表中的第一个位置的行索引(非精确查找)
参    数:   hWnd[in] --  控件句柄
            StartRowIndex[in] --  开始查找的行的索引, 就是从第几行开始查找
            pFindStr[in] --  要查找的字符串的指针
返 回 值: 找到的第一个字符串所在的行索引,如果为-1表示查找失败
说    明:
           YWGUI_LRCB_FINDSTRING
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBFindString(YWGUI_HWnd_T hWnd, U32 StartRowIndex,YWGUI_Char_T* pFindStr);

/***********************************************************************
函数名称: YWGUI_LRCBFindStringExact
函数功能: 查找指定字符串在列表中的第一个位置的行索引(精确查找,字符串长度也要一样)
参    数:   hWnd[in] --  控件句柄
            StartRowIndex[in] --  开始查找的行的索引, 就是从第几行开始查找
            pFindStr[in] --  要查找的字符串的指针
返 回 值: 找到的第一个字符串所在的行索引,如果为-1表示查找失败
说    明:
           YWGUI_LRCB_FINDSTRINGEXACT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBFindStringExact(YWGUI_HWnd_T hWnd, U32 StartRowIndex,YWGUI_Char_T* pFindStr);
#endif

/***********************************************************************
函数名称: YWGUI_LRCBGetListItemText
函数功能: 获取指定行文本
参    数:   hWnd[in] --  控件句柄
            ItemIndex[in] --  行索引, 注意行索引以0开始
            pStr[out] --  将指定行文本copy到lParam所指的地址空间,(输出参数);
                       注意此参数不可为空
返 回 值: 0获取成功，-1获取失败
说    明:
           YWGUI_LRCB_GETLBTEXT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBGetListItemText(YWGUI_HWnd_T hWnd, U32 ItemIndex,YWGUI_Char_T* pStr);

/***********************************************************************
函数名称: YWGUI_LRCBGetListItemTextLen
函数功能: 获取指定行文本长度
参    数:   hWnd[in] --  控件句柄
            ItemIndex[in] --  行索引, 注意行索引以0开始
返 回 值: 指定行文本长度
说    明:
           YWGUI_LRCB_GETLBTEXTLEN
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBGetListItemTextLen(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
函数名称: YWGUI_LRCBGetText
函数功能: 获取显示的文本
参    数:   hWnd[in] --  控件句柄
            Size[in] --  指定缓存区的大小(字节个数)
            pStr[out] --  缓存区指针
返 回 值: 拷贝到缓存区的字符数,不包括结束符
说    明:  注意:   UCS2 一个字符占两个字节
           YWGUI_LRCB_GETTEXT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBGetText(YWGUI_HWnd_T hWnd, U32 Size,YWGUI_Char_T* pStr);

/***********************************************************************
函数名称: YWGUI_LRCBSetText
函数功能: 设置显示的文本
参    数:   hWnd[in] --  控件句柄
            pStr[in] --  设置的文本字符串
返 回 值:
说    明:
           YWGUI_LRCB_SETTEXT
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBSetText(YWGUI_HWnd_T hWnd, YWGUI_Char_T* pStr);

/***********************************************************************
函数名称: YWGUI_LRCBSetListVisibleCount
函数功能: 设置列表的可见项数
参    数:   hWnd[in] --  控件句柄
            VisibleCount[in] --  列表的新可见数
返 回 值: 0设置成功, -1设置失败
说    明:
           YWGUI_LRCB_SETITEMVISIBLES
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBSetListVisibleCount(YWGUI_HWnd_T hWnd, U32 VisibleCount);

#if 0
/***********************************************************************
函数名称: YWGUI_LRCBGetChildrenControlHandle
函数功能: 获取LRcombobox中子控件的句柄
参    数:   hWnd[in] --  控件句柄
            phLRCBEdit[out] --  传出Combobox中的Edit的句柄的地址
            phLRCBList[out] --  传出Combobox中的Listbox的句柄的地址
返 回 值: 0设置成功, -1设置失败
说    明:
           YWGUI_LRCB_GETCHILDREN
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBGetChildrenControlHandle(YWGUI_HWnd_T hWnd, YWGUI_HWnd_T* phLRCBEdit,YWGUI_HWnd_T* phLRCBList);

/***********************************************************************
函数名称: YWGUI_LRCBGetEditHandle
函数功能: 获取LRcombobox中Edit控件的句柄
参    数:   hWnd[in] --  控件句柄
返 回 值: 返回Combobox中的Edit的句柄
说    明:
           YWGUI_LRCB_GETEDITHWND
修改记录:
************************************************************************/
YWGUI_API YWGUI_HWnd_T YWGUI_LRCBGetEditHandle(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_LRCBGetListHandle
函数功能: 获取LRcombobox中listbox控件的句柄
参    数:   hWnd[in] --  控件句柄
返 回 值: 返回Combobox中的listbox的句柄
说    明:
           YWGUI_LRCB_GETLISTBOXHWND
修改记录:
************************************************************************/
YWGUI_API YWGUI_HWnd_T YWGUI_LRCBGetListHandle(YWGUI_HWnd_T hWnd);
#endif
/***********************************************************************
函数名称: YWGUI_LRCBGetListItemState
函数功能: 获取list指定行的状态
参    数:   hWnd[in] --  控件句柄
            ItemIndex[in] --  要获取的行的索引
返 回 值: 0表示YWGUI_CBIF_NORMAL, 1表示YWGUI_CBIF_CHECKED, 2表示YWGUI_CBIF_SKIP
说    明:
           YWGUI_LRCB_GETITEMSTATE
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBGetListItemState(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
函数名称: YWGUI_LRCBPageDown
函数功能: 向下翻页
参    数:   hWnd[in] --  控件句柄
返 回 值:
说    明:
           YWGUI_LRCB_PAGEDOWN
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBPageDown(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_LRCBPageUp
函数功能: 向上翻页
参    数:   hWnd[in] --  控件句柄
返 回 值:
说    明:
           YWGUI_LRCB_PAGEUP
修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBPageUp(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_LRCBListSetXOffset
函数功能: 设置lrcombobox控件的列表字符的横向偏移
参    数: hWnd [in] -- lrcombobox控件的句柄
          XOffset [in] -- 偏移量,以像素为单位
返 回 值: YW_NO_ERROR
说    明: 
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LRCBListSetXOffset(YWGUI_HWnd_T hWnd, U16 XOffset);

/***********************************************************************
函数名称: YWGUI_LRCBListSetYOffset
函数功能: 设置lrcombobox控件的列表字符的纵向偏移
参    数: hWnd [in] -- lrcombobox控件的句柄
          YOffset [in] -- 偏移量,以像素为单位
返 回 值: YW_NO_ERROR
说    明: 
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LRCBListSetYOffset(YWGUI_HWnd_T hWnd, U16 YOffset);

/***********************************************************************
函数名称: YWGUI_LRCBListSetYOffset
函数功能: 关闭lrcombobox的弹出列表框
参    数: hWnd [in] -- lrcombobox控件的句柄
返 回 值: YW_NO_ERROR
说    明: 
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LRCBCloseListDlg(YWGUI_HWnd_T hWnd);


//容器控件 container
/***********************************************************************
函数名称: YWGUI_CTSetNextFocus
函数功能: 在容器控件中向后切换焦点
参    数:   hCT[in] --  容器控件控件句柄
返 回 值: 返回-1表示失败
说    明: 此函数只适用于容器控件

修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_CTSetNextFocus(YWGUI_HWnd_T hCT);

/***********************************************************************
函数名称: YWGUI_CTSetPrevFocus
函数功能: 在容器控件中向前切换焦点
参    数:   hCT[in] --  容器控件控件句柄
返 回 值: 返回-1表示失败
说    明: 此函数只适用于容器控件

修改记录:
************************************************************************/
YWGUI_API S32 YWGUI_CTSetPrevFocus(YWGUI_HWnd_T hCT);

/***********************************************************************
函数名称: YWGUI_CTGetCtrlHandleById
函数功能: 通过控件ID找到控件的句柄
参    数:   hCT[in] --  容器控件控件句柄
            CtrlId[in] --  控件ID
返 回 值: 返回ID对应的控件句柄
说    明: 此函数只适用于容器控件中的控件

修改记录:
************************************************************************/
YWGUI_API YWGUI_HWnd_T YWGUI_CTGetCtrlHandleById(YWGUI_HWnd_T hCT, U16 CtrlId);


//add by Eagle 2009-05-06
//ListTable Interface
/***********************************************************************
函数名称: YWGUI_LTSetTotalLine
函数功能: 设置 ListTable 的总行数
参    数: hCtrl[in] -- ListTable 句柄
          LineNum[in] -- ListTable 总行数
          CurLine[in] -- 焦点行
返 回 值: YW_NO_ERROR
说    明: 总行数主要用于控件对 PosBar/Check , 以及翻页管理
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTSetTotalLine(YWGUI_HWnd_T hCtrl, U16 LineNum, U16 CurLine);

/***********************************************************************
函数名称: YWGUI_LTGetTotalLine
函数功能: 获取 ListTable 的总行数
参    数: hCtrl[in] -- ListTable 句柄
返 回 值: ListTable 总行数
说    明: 总行数主要用于控件对 PosBar/Check , 以及翻页管理
************************************************************************/
YWGUI_API U16 YWGUI_LTGetTotalLine(YWGUI_HWnd_T hCtrl);

/***********************************************************************
函数名称: YWGUI_LTSetItemInfo
函数功能: 设置Item要显示的信息
参    数: hCtrl[in] -- ListTable 句柄
          Line[in] -- ListTable 行数
          Col[in] -- ListTable 列数
          pItemInfo[in] -- 需要设置的 ItemInfo
返 回 值: YW_NO_ERROR
说    明:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTSetItemInfo(YWGUI_HWnd_T hCtrl, U16 Line, U16 Col, const YWGUI_LTItemInfo_T *pItemInfo);

/***********************************************************************
函数名称: YWGUI_LTScrollPage
函数功能: 设置Item要显示的信息
参    数: hCtrl[in] -- ListTable 句柄
          IsPageDown[in] -- TRUE - 下翻一页 FALSE - 上翻一页
返 回 值: YW_NO_ERROR
说    明: 当翻页成功时,会产生 YWGUI_LTN_NEEDDATA 通知
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTScrollPage(YWGUI_HWnd_T hCtrl, BOOL IsPageDown);

/***********************************************************************
函数名称: YWGUI_LTSetCurLine
函数功能: 设置当前焦点行
参    数: hCtrl[in] -- ListTable 句柄
          LineNum[in] -- 需要设置的行索引
返 回 值: YW_NO_ERROR
说    明: 当需要翻页时,会产生 YWGUI_LTN_NEEDDATA 通知
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTSetCurLine(YWGUI_HWnd_T hCtrl, U16 LineNum);

/***********************************************************************
函数名称: YWGUI_LTGetCurLine
函数功能: 得到当前焦点行
参    数: hCtrl[in] -- ListTable 句柄
返 回 值: 焦点行索引,若为-1则没有焦点行
说    明:
************************************************************************/
YWGUI_API S32 YWGUI_LTGetCurLine(YWGUI_HWnd_T hCtrl);

/***********************************************************************
函数名称: YWGUI_LTMarkLine
函数功能: 设置选中或非选中状态
参    数: hCtrl[in] -- ListTable 句柄
          LineNum[in] -- 目标行索引
          IsMark[in] -- TRUE - 选中 FALSE - 不选中
返 回 值: YW_NO_ERROR
说    明: 被操作的 ListTable 必须有 Mark 风格
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTMarkLine(YWGUI_HWnd_T hCtrl, U16 LineNum, BOOL IsMark);

/***********************************************************************
函数名称: YWGUI_LTMarkAll
函数功能: 设置选中或非选中所有行
参    数: hCtrl[in] -- ListTable 句柄
          IsMark[in] -- TRUE - 选中 FALSE - 不选中
返 回 值: YW_NO_ERROR
说    明: 被操作的 ListTable 必须有 Mark 风格
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTMarkAll(YWGUI_HWnd_T hCtrl, BOOL IsMark);

/***********************************************************************
函数名称: YWGUI_LTSwitchAllMark
函数功能: 反选所有行
参    数: hCtrl[in] -- ListTable 句柄
返 回 值: YW_NO_ERROR
说    明: 被操作的 ListTable 必须有 Mark 风格
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTSwitchAllMark(YWGUI_HWnd_T hCtrl);

/***********************************************************************
函数名称: YWGUI_LTGetMarkState
函数功能: 获取目标行的选中状态
参    数: hCtrl[in] -- ListTable 句柄
          LineNum[in] -- 目标行索引
返 回 值: TRUE - 目标行被选中
说    明: 被操作的 ListTable 必须有 Mark 风格
************************************************************************/
YWGUI_API BOOL YWGUI_LTGetMarkState(YWGUI_HWnd_T hCtrl, U16 LineNum);

/***********************************************************************
函数名称: YWGUI_LTGetFirstMarkLine
函数功能: 获取第一个选中行
参    数: hCtrl[in] -- ListTable 句柄
          pLine[out] -- 返回第一个选中行.如果没有,则返回 -1
返 回 值: YW_NO_ERROR
说    明: 被操作的 ListTable 必须有 Mark 风格,与 YWGUI_LTGetNextMarkLine
          配合使用可获取到所有 Mark 行
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTGetFirstMarkLine(YWGUI_HWnd_T hCtrl, S32 *pLine);

/***********************************************************************
函数名称: YWGUI_LTGetNextMarkLine
函数功能: 获取下一个选中行
参    数: hCtrl[in] -- ListTable 句柄
          pLine[out] -- 返回下一个选中行.如果没有,则返回 -1
返 回 值: YW_NO_ERROR
说    明: 被操作的 ListTable 必须有 Mark 风格
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTGetNextMarkLine(YWGUI_HWnd_T hCtrl, S32 *pLine);

/***********************************************************************
函数名称: YWGUI_LTGetLastMarkLine
函数功能: 获取第一个选中行
参    数: hCtrl[in] -- ListTable 句柄
          pLine[out] -- 返回第一个选中行.如果没有,则返回 -1
返 回 值: YW_NO_ERROR
说    明: 被操作的 ListTable 必须有 Mark 风格,与 YWGUI_LTGetPrevMarkLine
          配合使用可获取到所有 Mark 行
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTGetLastMarkLine(YWGUI_HWnd_T hCtrl, S32 *pLine);

/***********************************************************************
函数名称: YWGUI_LTGetPrevMarkLine
函数功能: 获取下一个选中行
参    数: hCtrl[in] -- ListTable 句柄
          pLine[out] -- 返回下一个选中行.如果没有,则返回 -1
返 回 值: YW_NO_ERROR
说    明: 被操作的 ListTable 必须有 Mark 风格
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTGetPrevMarkLine(YWGUI_HWnd_T hCtrl, S32 *pLine);

/***********************************************************************
函数名称: YWGUI_LTGetTotalMarkLineNum
函数功能: 获取总选中行数
参    数: hCtrl[in] -- ListTable 句柄
          pNum[out] -- 返回总选中行数
返 回 值: YW_NO_ERROR
说    明: 被操作的 ListTable 必须有 Mark 风格
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTGetTotalMarkLineNum(YWGUI_HWnd_T hCtrl, S32 *pNum);

/***********************************************************************
函数名称: YWGUI_LTRefreshCurPageData
函数功能: 刷新当前页数据
参    数: hCtrl[in] -- ListTable 句柄
返 回 值: YW_NO_ERROR
说    明: 调用成功后会产生 YWGUI_LTN_NEEDDATA 通知
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTRefreshCurPageData(YWGUI_HWnd_T hCtrl);

/***********************************************************************
函数名称: YWGUI_LTDisableLine
函数功能: 设置 Disable 状态
参    数: hCtrl[in] -- ListTable 句柄
          LineNum[in] -- 目标行索引
          IsDisable[in] -- TRUE - Disable FALSE - Enable
返 回 值: YW_NO_ERROR
说    明: 被操作的 ListTable 必须有 Disable 风格
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTDisableLine(YWGUI_HWnd_T hCtrl, U16 LineNum, BOOL IsDisable);

/***********************************************************************
函数名称: YWGUI_LTDisableAll
函数功能: 设置选中或非选中所有行
参    数: hCtrl[in] -- ListTable 句柄
          IsDisable[in] -- TRUE - Disable FALSE - Enable
返 回 值: YW_NO_ERROR
说    明: 被操作的 ListTable 必须有 Disable 风格
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTDisableAll(YWGUI_HWnd_T hCtrl, BOOL IsDisable);

/***********************************************************************
函数名称: YWGUI_LTGetDisableState
函数功能: 获取目标行的选中状态
参    数: hCtrl[in] -- ListTable 句柄
          LineNum[in] -- 目标行索引
返 回 值: TRUE - 目标行 Disable
说    明: 被操作的 ListTable 必须有 Disable 风格
************************************************************************/
YWGUI_API BOOL YWGUI_LTGetDisableState(YWGUI_HWnd_T hCtrl, U16 LineNum);

/***********************************************************************
函数名称: YWGUI_LTGetFirstDisableLine
函数功能: 获取第一个选中行
参    数: hCtrl[in] -- ListTable 句柄
          pLine[out] -- 返回第一个 Disable 行.如果没有,则返回 -1
返 回 值: YW_NO_ERROR
说    明: 被操作的 ListTable 必须有 Disable 风格,与 YWGUI_LTGetNextDisableLine
          配合使用可获取到所有 Disable 行
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTGetFirstDisableLine(YWGUI_HWnd_T hCtrl, S32 *pLine);

/***********************************************************************
函数名称: YWGUI_LTGetNextDisableLine
函数功能: 获取下一个选中行
参    数: hCtrl[in] -- ListTable 句柄
          pLine[out] -- 返回下一个 Disable 行.如果没有,则返回 -1
返 回 值: YW_NO_ERROR
说    明: 被操作的 ListTable 必须有 Disable 风格
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTGetNextDisableLine(YWGUI_HWnd_T hCtrl, S32 *pLine);

/***********************************************************************
函数名称: YWGUI_LTGetItemHeight
函数功能: 获取行高
参    数: hCtrl[in] -- ListTable 句柄
          LineHeight[out] -- 返回行高.-1表示出错
返 回 值: 无
说    明:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTGetItemHeight(YWGUI_HWnd_T hCtrl, S32 *LineHeight);

/***********************************************************************
函数名称: YWGUI_LTGetViewLineNum
函数功能: 获取第一个选中行
参    数: hCtrl[in] -- ListTable 句柄
          pViewLineNum[out] -- 返回每页的可见行数
返 回 值: YW_NO_ERROR
说    明: 被操作的 ListTable 必须有 Disable 风格,与 YWGUI_LTGetNextDisableLine
          配合使用可获取到所有 Disable 行
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTGetViewLineNum(YWGUI_HWnd_T hCtrl, S32 *pViewLineNum);

/***********************************************************************
函数名称: YWGUI_SEDITSetReplaceMode
函数功能: 改变 SEdit 的编辑方式 Replace 和 Insert
参    数: hCtrl[in] -- SEdit 句柄
返 回 值: YW_NO_ERROR
说    明:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SEDITSetReplaceMode(YWGUI_HWnd_T hCtrl, BOOL IsReplace);

/**********************************coordinate函数***************************/

/***********************************************************************
函数名称: YWGUI_ClientToScreen
函数功能: 客户区坐标矩形转成屏幕坐标矩形
参    数: hWnd[in] -- 窗口句柄
          rcClient[in] -- 输入矩形,坐标是相对于hWnd窗口客户区的坐标
          rcScreen[out] -- 输出矩形，屏幕坐标
返 回 值:
说    明:
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_ClientToScreen(YWGUI_HWnd_T hWnd, const YWGUI_Rect_T* rcClient, YWGUI_Rect_T* rcScreen);

/***********************************************************************
函数名称: YWGUI_WindowToScreen
函数功能: 窗口坐标矩形转成屏幕坐标矩形
参    数: hWnd[in] -- 窗口句柄
          rcWindow[in] -- 输入矩形,坐标是相对于hWnd窗口的坐标
          rcScreen[out] -- 输出矩形，屏幕坐标
返 回 值:
说    明:
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_WindowToScreen(YWGUI_HWnd_T hWnd, const YWGUI_Rect_T* rcWindow, YWGUI_Rect_T* rcScreen);

/***********************************************************************
函数名称: YWGUI_ScreenToClient
函数功能: 屏幕坐标矩形转成客户区坐标矩形
参    数: hWnd[in] -- 窗口句柄
          rcScreen[in] -- 输入矩形,屏幕坐标
          rcClient[out] -- 输出矩形，坐标是相对于hWnd窗口客户区的坐标
返 回 值:
说    明:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_ScreenToClient (YWGUI_HWnd_T hWnd, const YWGUI_Rect_T* rcScreen, YWGUI_Rect_T* rcClient);

//屏幕坐标矩形转成窗口坐标矩形
/***********************************************************************
函数名称: YWGUI_ScreenToWindow
函数功能: 屏幕坐标矩形转成窗口坐标矩形
参    数: hWnd[in] -- 窗口句柄
          rcScreen[in] -- 输入矩形,屏幕坐标
          rcWindow[out] -- 输出矩形，坐标是相对于hWnd窗口的坐标
返 回 值:
说    明:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_ScreenToWindow (YWGUI_HWnd_T hWnd, const YWGUI_Rect_T* rcScreen, YWGUI_Rect_T* rcWindow);

/***********************************************************************
函数名称: YWGUI_GetWindowRectInScreen
函数功能: 得到窗口的屏幕坐标
参    数: hWnd[in] -- 窗口句柄
          pRect[out] -- 输出矩形，hWnd窗口的屏幕坐标
返 回 值:
说    明:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_GetWindowRectInScreen (YWGUI_HWnd_T hWnd, YWGUI_Rect_T* pRect);

/***********************************************************************
函数名称: YWGUI_GetClientRectInScreen
函数功能: 得到窗口客户区的屏幕坐标
参    数: hWnd[in] -- 窗口句柄
          pRect[out] -- 输出矩形，hWnd窗口客户区的屏幕坐标
返 回 值:
说    明:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_GetClientRectInScreen(YWGUI_HWnd_T hWnd, YWGUI_Rect_T* pRect);


/***********************************************************************
函数名称: YWGUI_GetWindowRectInParent
函数功能: 得到窗口相对于父窗口客户区的坐标矩形
参    数: hWnd[in] -- 窗口句柄
          pRect[out] -- 输出矩形，相对于父窗口客户区的坐标
返 回 值:
说    明:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_GetWindowRectInParent(YWGUI_HWnd_T hWnd, YWGUI_Rect_T* pRect);

/***********************************************************************
函数名称: YWGUI_GetClientRectInParent
函数功能: 得到窗口客户区相对于父窗口客户区的坐标矩形
参    数: hWnd[in] -- 窗口句柄
          pRect[out] -- 输出矩形，相对于父窗口客户区的坐标
返 回 值:
说    明:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_GetClientRectInParent(YWGUI_HWnd_T hWnd, YWGUI_Rect_T* pRect);

/***********************************************************************
函数名称: YWGUI_GetWindowRect
函数功能: 得到窗口的矩形(相对于本窗口的坐标,即矩形的左上角坐标为(0,0))
参    数: hWnd[in] -- 窗口句柄
          pRect[out]-- 输出矩形(左上角坐标为(0,0))
返 回 值:
说    明:
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_GetWindowRect (YWGUI_HWnd_T hWnd, YWGUI_Rect_T* pRect);

/***********************************************************************
函数名称: YWGUI_GetClientRect
函数功能: 得到窗口客户区的矩形(相对于本窗口客户区的坐标,即矩形的左上角坐标为(0,0))
参    数: hWnd[in] -- 窗口句柄
          pRect[out]-- 输出矩形(左上角坐标为(0,0))
返 回 值:
说    明:
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_GetClientRect (YWGUI_HWnd_T hWnd, YWGUI_Rect_T* pRect);

//得到窗口的宽度
YWGUI_API S32 YWGUI_GetWindowWidth(YWGUI_HWnd_T hWnd);

//得到窗口的高度
YWGUI_API S32 YWGUI_GetWindowHeight(YWGUI_HWnd_T hWnd);

//得到窗口客户区的宽度
YWGUI_API S32 YWGUI_GetClientWidth(YWGUI_HWnd_T hWnd);

//得到窗口客户区的高度
YWGUI_API S32 YWGUI_GetClientHeight(YWGUI_HWnd_T hWnd);


YWGUI_API void YWGUI_SetRect(YWGUI_Rect_T *pRect,S32 left,S32 top,S32 right,S32 bottom);

/**********************************message函数***************************/
/***********************************************************************
函数名称: YWGUI_GetMessage
函数功能: 获取消息
参    数:  pMsg[out] -- 返回得到的消息
           hWnd[in] -- 窗口句柄 (属主窗口)
返 回 值:  TRUE --得到非退出消息; FALSE --得到退出消息
说    明:  1)该函数从 hWnd 所依附的消息队列获取消息，
             如果消息队列没有消息，一直等待到得到消息为止
修改记录:
************************************************************************/
YWGUI_API BOOL  YWGUI_GetMessage (YWGUI_Msg_T *pMsg, YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_PeekPostMessage
函数功能: 检测指定窗口的邮寄消息,检测到消息后从消息队列移除该消息
参    数:  pMsg[out] -- 返回检测到的消息
           hWnd[in] -- 指定窗口句柄
           iMsgFilterMin[in] -- 检测消息范围的最小值(含)
           iMsgFilterMax[in] -- 检测消息范围的最大值(含)
返 回 值:   TRUE -- 检测到消息; FALSE: 没有检测到消息
说    明:

修改记录:
************************************************************************/
YWGUI_API BOOL  YWGUI_PeekPostMessage (YWGUI_Msg_P pMsg, YWGUI_HWnd_T hWnd, S32 iMsgFilterMin,
                        S32 iMsgFilterMax);

YWGUI_API YW_ErrorType_T YWGUI_TranslateMessage(YWGUI_Msg_T* pMsg);

YWGUI_API S32 YWGUI_DispatchMessage (YWGUI_Msg_T* pMsg);

YWGUI_API YW_ErrorType_T  YWGUI_PostQuitMessage (YWGUI_HWnd_T hWnd);

YWGUI_API YW_ErrorType_T  YWGUI_PostMessage (YWGUI_HWnd_T hWnd, S32 iMsg, WPARAM wParam, LPARAM lParam);

YWGUI_API S32 YWGUI_SendMessage (YWGUI_HWnd_T hWnd, S32 iMsg, WPARAM wParam, LPARAM lParam);



/****************************************gdi函数*********************************/
/***********************************************************************
函数名称: YWGUI_GetDC
函数功能: 获取窗口DC
参    数:   hWnd[in] -- 窗口句柄
返 回 值:   返回获得的窗口DC
说    明:   1)该函数需要和YWGUI_ReleaseDC成对使用
            2)如果没有空闲的DC，返回YWGUI_NULL_HANDLE
************************************************************************/
YWGUI_API YWGUI_HDc_T  YWGUI_GetDC(YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_GetClientDC
函数功能: 获取窗口客户区DC
参    数:   hWnd[in] -- 窗口句柄
返 回 值:   返回获得的窗口客户区DC
说    明:   1)该函数需要和YWGUI_ReleaseDC成对使用
            2)如果没有空闲的DC，返回YWGUI_NULL_HANDLE
************************************************************************/
YWGUI_API YWGUI_HDc_T  YWGUI_GetClientDC (YWGUI_HWnd_T hWnd);

/***********************************************************************
函数名称: YWGUI_ReleaseDC
函数功能: 释放窗口或客户区DC
参    数:   hDC[in] -- DC
返 回 值:   无
说    明:
************************************************************************/
YWGUI_API void  YWGUI_ReleaseDC (YWGUI_HDc_T hDC);

YWGUI_API YWGUI_HDc_T  YWGUI_BeginPaint (YWGUI_HWnd_T hWnd);

YWGUI_API void  YWGUI_EndPaint (YWGUI_HWnd_T hWnd, YWGUI_HDc_T hdc);


/***********************************************************************
函数名称: YWGUI_GetDcEx
函数功能: 得到窗口DC
参    数:   hWnd[in] -- 窗口句柄
返 回 值:   无
说    明:  1)该函数需与 YWGUI_ReleaseDC 配套使用
           2)该函数扩展 YWGUI_GetDc ,提供给 YWGUI_MSG_NCPAINT 消息响应调用

修改记录:
************************************************************************/
YWGUI_API YWGUI_HDc_T  YWGUI_GetDcEx(YWGUI_HWnd_T hWnd);



//得到画笔宽度
#define YWGUI_GetPenWidth(hdc)  (U32)YWGUI_GetDCAttr(hdc,DC_ATTR_PEN_WIDTH)

//得到字符之间间距
#define YWGUI_GetTextCharExtra(hdc)  (S32)YWGUI_GetDCAttr (hdc, DC_ATTR_CHAR_EXTRA)

//得到文本行上面的间距
#define YWGUI_GetTextAboveExtra(hdc)  (S32)YWGUI_GetDCAttr (hdc, DC_ATTR_ALINE_EXTRA)

//得到文本行下面的间距
#define YWGUI_GetTextBellowExtra(hdc) (S32)YWGUI_GetDCAttr (hdc, DC_ATTR_BLINE_EXTRA)


//设置背景色
#define YWGUI_SetBkColor(hdc,newColor, oldColor)  \
                do{ U32* pValue =(U32*)oldColor; U32 value =YWGUI_SetDCAttr (hdc, DC_ATTR_BK_COLOR, (U32)newColor); if(pValue) *pValue = value ;}while(0)

//设置背景模式
#define YWGUI_SetBkMode(hdc, mode)\
                YWGUI_SetDCAttr(hdc, DC_ATTR_BK_MODE, (U32)mode)

//设置层的操作模式，added by sly, 2009-11-5
#define YWGUI_SetOpMode(hdc, mode)\
                (YWGUI_CANVAS_OpMode_T)YWGUI_SetDCAttr(hdc, DC_ATTR_OP_MODE, (U32)mode)

//设置画刷的颜色
#define YWGUI_SetBrushColor(hdc,newColor, oldColor)   \
                 do{ U32* pValue =(U32*)oldColor; U32 value =YWGUI_SetDCAttr (hdc, DC_ATTR_BRUSH_COLOR, (U32)newColor); if(pValue) *pValue = value ;}while(0)

//设置画笔的颜色
#define YWGUI_SetPenColor(hdc,newColor, oldColor) \
               do{ U32* pValue =(U32*)oldColor; U32 value =YWGUI_SetDCAttr (hdc, DC_ATTR_PEN_COLOR, (U32)newColor); if(pValue) *pValue = value ;}while(0)

//设置画笔的宽度
#define YWGUI_SetPenWidth(hdc,width) \
        (U32)YWGUI_SetDCAttr (hdc, DC_ATTR_PEN_WIDTH, (U32)width)

//设置文本的颜色
#define YWGUI_SetTextColor(hdc,newColor, oldColor) \
              do{ U32* pValue =(U32*)oldColor; U32 value =YWGUI_SetDCAttr (hdc, DC_ATTR_TEXT_COLOR, (U32)newColor); if(pValue) *pValue = value ;}while(0)

//设置字符之间间距
#define YWGUI_SetTextCharExtra(hdc, extra)       \
                YWGUI_SetDCAttr (hdc, DC_ATTR_CHAR_EXTRA, (U32)extra)

//设置文本行上面的间距
#define YWGUI_SetTextAboveExtra(hdc, extra)  \
                YWGUI_SetDCAttr (hdc, DC_ATTR_ALINE_EXTRA, (U32)extra)

//设置文本行下面的间距
#define YWGUI_SetTextBellowExtra(hdc, extra) \
                YWGUI_SetDCAttr (hdc, DC_ATTR_BLINE_EXTRA, (U32)extra)

/***********************************************************************
函数名称: YWGUI_GetCurFont
函数功能: 得到DC当前有使用的逻辑字体的字体句柄
参    数:  hdc[in] -- 设备DC
返 回 值:  当前使用的逻辑字体句柄
说    明:
修改记录:
************************************************************************/
YWGUI_API YWGUI_HFont_T YWGUI_GetCurFont (YWGUI_HDc_T hdc);

/***********************************************************************
函数名称: YWGUI_SelectFont
函数功能: 设置DC 使用新的逻辑字体
参    数:  hdc[in] -- 设备DC
           hFont[in] -- 新的逻辑字体的字体句柄
返 回 值:  以前使用的逻辑字体句柄
说    明:
修改记录:
************************************************************************/
YWGUI_API YWGUI_HFont_T YWGUI_SelectFont (YWGUI_HDc_T hdc, YWGUI_HFont_T hFont);

/***********************************************************************
函数名称: YWGUI_CreateLogFont
函数功能: 销毁调用 YWGUI_CreateLogFont 创建的逻辑字体
参    数:  szFontType [in] -- 字体类型 (支持"ttf"/"rbf")
           szFontFamily [in] -- 字体簇 (支持"fulan"/"arial")
           szCharset [in] -- 字符集(支持"UCS-2")
           szFontStyle [in] -- 字体风格(支持"rrncnn")
           width [in] --  字体宽度(仅对矢量字体有效)
           height [in]--字体的高度(就是原来的size参数)
           rotation [in] -- 保留(填0)
返 回 值:  创建的逻辑字体句柄
           如果为 YWGUI_NULL_HANDLE ，创建逻辑字体失败
说    明:  1)该函数必须与 YWGUI_DestroyLogFont 配套使用
修改记录:
                    1) 为了使用一些特殊的字体(比如细长型字体)做了相应修改,
                    去掉了原来的size参数，增加了width, height参数
************************************************************************/
YWGUI_API YWGUI_HFont_T  YWGUI_CreateLogFont (const S8* szFontType, const S8* szFontFamily,
    const S8* szCharset, const S8 * szFontStyle, U16 width, U16 height, S32 rotation);

/***********************************************************************
函数名称: YWGUI_DestroyLogFont
函数功能: 销毁调用 YWGUI_CreateLogFont 创建的逻辑字体
参    数:  hFont[in] -- 逻辑字体句柄
返 回 值:  无
说    明:
修改记录:
************************************************************************/
YWGUI_API void  YWGUI_DestroyLogFont (YWGUI_HFont_T hFont);

YWGUI_API YW_ErrorType_T YWGUI_SetWindowFont(YWGUI_HWnd_T hWnd,YWGUI_HFont_T hFont);

//返回的宽高包含间距
YWGUI_API void YWGUI_GetTextExtent (YWGUI_HDc_T hdc, const YWGUI_Char_T* spText, S32 len, YWGUI_Extent_T* ptSize);

//返回的宽高包含间距(宽=字体宽+cExtra,高=字体高+alExtra+blExtra)
YWGUI_API void YWGUI_GetCharExtent(YWGUI_HDc_T hdc,YWGUI_Char_T character,S32 *pWidth,S32 *pHeight);


YWGUI_API S32  YWGUI_TextOutLen (YWGUI_HDc_T hdc, S32 x, S32 y, const YWGUI_Char_T* spText, S32 len);

#define YWGUI_TextOut(hdc, x, y, text)    YWGUI_TextOutLen (hdc, x, y, text, -1)

/***********************************************************************
函数名称: YWGUI_DrawText
函数功能: 在指定矩形区域内按格式输出文本
参    数:  hdc[in] --
           spText[in] -- 输出字符串
           len[in] -- 输出字符个数(<0 则输出整个字符串)
           pRect[in] -- 指定的矩形区域 (相对DC的矩形坐标)
           format[in] --
返 回 值:  返回输出文本占用屏幕高度(象素个数)
说    明:
修改记录:
************************************************************************/
YWGUI_API S32  YWGUI_DrawText(YWGUI_HDc_T hdc, const YWGUI_Char_T* spText, S32 len,YWGUI_Rect_T *pRect,U32 format);
/***********************************************************************
函数名称: YWGUI_DrawTextEx
函数功能: 在指定矩形区域内按格式输出文本
参    数:  hdc[in] --
           spText[in] -- 输出字符串
           len[in] -- 输出字符个数(<0 则输出整个字符串)
           pRect[in] -- 指定的矩形区域(相对DC的矩形坐标)
           indent[in] --缩进值
           format[in] --
返 回 值:  返回输出文本占用屏幕高度(象素个数)
说    明:  默认都是正的缩进，如果需要负缩进，
                  需要指定YWGUI_DT_NEGINDENT风格
修改记录:
************************************************************************/
YWGUI_API S32  YWGUI_DrawTextEx(YWGUI_HDc_T hdc, const YWGUI_Char_T* spText, S32 len,YWGUI_Rect_T *pRect, S32 indent, U32 format);


/***********************************************************************
函数名称: YWGUI_GetTextLineHightAndLineNum
函数功能: 在指定矩形区域内获取文本的行高和行数
参    数:  hdc[in] --
           spText[in] -- 字符串
           len[in] -- 字符个数(<0 则输出整个字符串)
           pRect[in] -- 指定的矩形区域(相对DC的矩形坐标)
           format[in] --
           puLineNum[out] --文本的行数
返 回 值:  返回单行文字的高度(象素个数)
说    明:
修改记录:
************************************************************************/
YWGUI_API S32  YWGUI_GetTextLineHightAndLineNum(YWGUI_HDc_T hdc, const YWGUI_Char_T* spText, S32 len,YWGUI_Rect_T *pRect,U32 format, U16 * puLineNum);

YWGUI_API void YWGUI_DTGetFirstLineInfo(YWGUI_HDc_T hdc, const YWGUI_Char_T* spText, S32 len,YWGUI_Rect_T *pRect,U32 format,YWGUI_LineInfo_T *ptFirstLine);


YWGUI_API void YWGUI_MoveTo(YWGUI_HDc_T hdc, S32 x, S32 y);

YWGUI_API void  YWGUI_LineTo (YWGUI_HDc_T hdc, S32 x, S32 y);

YWGUI_API void  YWGUI_Rectangle(YWGUI_HDc_T hdc, S32 x, S32 y, S32 w, S32 h);

YWGUI_API void  YWGUI_Circle(YWGUI_HDc_T hdc, S32 x0, S32 y0, S32 r);

YWGUI_API void  YWGUI_Triangle(YWGUI_HDc_T hdc, S32 x1, S32 y1, S32 x2, S32 y2, S32 x3, S32 y3);


YWGUI_API void  YWGUI_FillBox (YWGUI_HDc_T hdc, S32 x, S32 y, S32 w, S32 h);

YWGUI_API void  YWGUI_FillPie(YWGUI_HDc_T hdc, S32 x0, S32 y0, S32 r, S32 startAngle, S32 endAngle);

YWGUI_API void  YWGUI_FillCircle(YWGUI_HDc_T hdc, S32 x0, S32 y0, S32 r);

YWGUI_API void  YWGUI_FillTriangle(YWGUI_HDc_T hdc, S32 x1, S32 y1, S32 x2, S32 y2, S32 x3, S32 y3);

/***********************************************************************
函数名称: YWGUI_CreateBitmap
函数功能: 该函数依据设备无关位图(ptDibmp)和hdc生成设备相关位图
参    数:   hdc[in] -- 设备DC
            ptDibmp[in] -- 设备无关位图结构指针
返 回 值: 返向新建的设备相关位图句柄
说    明: 1)该函数内部动态分配了内存，需与YWGUI_DeleteBitmap配套使用
          2)在yw平台,为节约内存，如设备无关位图的属性和设备一致，
            仍然使用设备无关位图的位图数据，故要求该数据在使用过程中一直存在
************************************************************************/
YWGUI_API YWGUI_HGraphCell_T  YWGUI_CreateGraphCell(YWGUI_HDc_T hdc,const YWGUI_GraphCell_T* ptDibGraphCell);

YWGUI_API void YWGUI_DeleteGraphCell(YWGUI_HGraphCell_T hGraphCell);

/***********************************************************************
函数名称: YWGUI_FillBoxWithBitmap
函数功能: 用设备相关位图对象填充矩形区域(不进行缩放)
参    数:   hdc[in] -- 设备DC
            x[in] -- x坐标
            y[in] -- y坐标
            w[in] -- 填充矩形宽度
            h[in] -- 填充矩形高度
            hBitmap[in] -- 设备相关位图句柄
返 回 值:   YW_NO_ERROR -- OK
            否则 --fail
说    明:  如果传入的w,h值<=0,填充矩形设成位图实际大小 ;
           如果位图大小大于w*h,裁剪位图的w*h区域显示;
           如果位图大小小于w*h,显示位图实际大小;
           各情况都受hdc裁剪
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_FillBoxWithGraphCell (YWGUI_HDc_T hdc, S32 x, S32 y, S32 w, S32 h,
                              YWGUI_HGraphCell_T  hGraphCell);

/***********************************************************************
函数名称: YWGUI_CreateGraphCollect
函数功能: 该函数生成新的设备相关图集
参    数:   ptSrcGraphCollect[in] -- 源图集
返 回 值:   返回新的图集结构指针
说    明:   1)该函数与YWGUI_DeleteGraphCollect配套使用
            2)如果源图集是设备无关，生成新的设备相关图集
            3)如果源图集是设备相关，直接返回源图集，并将图集内部计数+1
************************************************************************/
YWGUI_API YWGUI_GraphCollect_T* YWGUI_CreateGraphCollect(YWGUI_GraphCollect_T* ptSrcGraphCollect);

/***********************************************************************
函数名称: YWGUI_DeleteGraphCollect
函数功能: 该函数与YWGUI_CreateGraphCollect配套使用,用于释放
参    数: ptGraphCollect[in] -- 图集
返 回 值: YW_NO_ERROR
说    明: 1)该函数与YWGUI_CreateGraphCollect配套使用
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_DeleteGraphCollect(YWGUI_GraphCollect_T* ptGraphCollect);


/***********************************************************************
函数名称: YWGUI_SpellGraphAndPadding
函数功能: 画拼图
参    数:   hdc[in] -- 设备DC
            x[in] -- x坐标
            y[in] -- y坐标
            w[in] -- 绘画区域宽度
            h[in] -- 绘画区域高度
            ptGraphCollect[in] --图集
            bPadding[in]--是否填充空隙
返 回 值:
说    明: 1)图集横向拼凑时高度不一致，纵向拼凑时宽度不一致，会留下一些空隙，
            该函数考虑用DC的画刷色来填充一些空隙
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SpellGraphAndPadding(YWGUI_HDc_T hdc, S32 x, S32 y, S32 w, S32 h, const YWGUI_GraphCollect_T* ptGraphCollect,BOOL bPadding);

/*画拼图函数（该函数不填充空隙）*/
#define YWGUI_SpellGraphCollect(hdc,x,y,w,h,ptGraphCollect)   YWGUI_SpellGraphAndPadding(hdc,x,y,w,h,ptGraphCollect,FALSE)




/***********************************************************************
函数名称: YWGUI_SetWEColor
函数功能: 设置窗口(主窗口/子窗口)某项颜色方案
参    数:   hWnd[in] -- 窗口句柄
            item[in] --颜色方案项
            pixel[in] --颜色值
返 回 值:  YW_NO_ERROR-- 设置成功; 否则--设置失败
说    明:  1)该函数只能在指定窗口所附属的消息处理线程中调用
           2)建议应用在 YWGUI_MSG_NCCREATE/YWGUI_MSG_NOTIFY_NCCREATE
             消息响应中调用
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetWEColor (YWGUI_HWnd_T hWnd, YWGUI_WecItem_E item, YWGUI_Pixel_T pixel);


/***********************************************************************
函数名称: YWGUI_SetWEMetrics
函数功能: 设置窗口(主窗口/子窗口)某项颜色方案
参    数:   hWnd[in] -- 窗口句柄
            item[in] --颜色方案项
            pixel[in] --颜色值
返 回 值:  YW_NO_ERROR-- 设置成功; 否则--设置失败
说    明:  1)该函数只能在指定窗口所附属的消息处理线程中调用
           2)建议应用在 YWGUI_MSG_NCCREATE/YWGUI_MSG_NOTIFY_NCCREATE
             消息响应中调用
************************************************************************/
YWGUI_API YW_ErrorType_T   YWGUI_SetWEMetrics(YWGUI_HWnd_T hWnd, YWGUI_WemItem_E item, S32 size);

/***********************************************************************
函数名称: YWGUI_SetWEShapeState
函数功能: 设置窗口(主窗口/子窗口)某状态下的外观方案及颜色值
参    数:   hWnd[in] -- 窗口句柄
            item[in] --外观方案项(即状态)
            ptShapeState[in] --某状态对应的外观结构
返 回 值:  YW_NO_ERROR-- 设置成功; 否则--设置失败
说    明:   1)该函数只能在指定窗口所附属的消息处理线程中调用
            2)建议应用在 YWGUI_MSG_NCCREATE/YWGUI_MSG_NOTIFY_NCCREATE
             消息响应中调用

************************************************************************/
YWGUI_API YW_ErrorType_T   YWGUI_SetWEShapeState(YWGUI_HWnd_T hWnd, YWGUI_WesItem_E item, YWGUI_ShapeState_T* ptShapeState);


/***********************************************************************
函数名称: YWGUI_SetGlobalQuad
函数功能: 设置全局调色板
参    数:
返 回 值:
说    明: 1)ptQuad 所指向的内存未被拷贝，必须全局存在
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetGlobalQuad(U32 nQuadColors,const YWMID_Palette_T*ptQuad);

/*操作前面板的接口封装,added by sly, 2009-4-23*/
#ifndef WIN32
typedef enum YWGUI_PanelStartUpStat_e
{
    YWGUI_PANEL_STARTUP_STATE_UNKNOW,
    YWGUI_PANEL_STARTUP_STATE_ELECTRIFY =0x01,   /*上电启动*/
    YWGUI_PANEL_STARTUP_STATE_STANDBY,           /*待机启动*/
    YWGUI_PANEL_STARTUP_STATE_TIMER,		/*定时启动*/
}YWGUI_PanelStartUpStat_T;
typedef enum YWGUI_PanelEquipmentType_e
{
    YWGUI_PANEL_EQUIPTYPE_REMOTE,
    YWGUI_PANEL_EQUIPTYPE_FRONTPANEL,
    YWGUI_PANEL_EQUIPTYPE_LBD
}YWGUI_PanelEquipmentType_T;

/*Panel Display Type*/
typedef enum YWGUI_PANEL_DisplayType_e
{
    YWGUI_PANEL_DISPLAY_TYPE_UNKNOWN = 0x00,
    YWGUI_PANEL_DISPLAY_TYPE_VFD = ( 1 << 0 ),       /*  VFD显示 */
    YWGUI_PANEL_DISPLAY_TYPE_LCD = ( 1 << 1 ),       /*  液晶显示 */ 
    YWGUI_PANEL_DISPLAY_TYPE_LED = ( 1 << 2 ),       /*  数码管显示 */
    YWGUI_PANEL_DISPLAY_TYPE_LBD = ( 1 << 3 )        /*  二级管显示灯 */
}YWGUI_PANEL_DisplayType_T;

/*Front Panel Key Value Enum*/
typedef enum YWGUI_PANEL_FrontKeyValue_e
{
    YWGUI_PANEL_FRONT_INVALID_KEY   = 0,
    YWGUI_PANEL_FRONT_POWER  ,
    YWGUI_PANEL_FRONT_MENU   ,
    YWGUI_PANEL_FRONT_ENTER  ,
    YWGUI_PANEL_FRONT_UP     ,
    YWGUI_PANEL_FRONT_DOWN   ,
    YWGUI_PANEL_FRONT_LEFT   ,
    YWGUI_PANEL_FRONT_RIGHT  ,
    YWGUI_PANEL_FRONT_MAX
}YWGUI_PANEL_FrontKeyValue_T;

/*Panel Input Type*/
typedef enum YWGUI_PANEL_InputType_e
{
    YWGUI_PANEL_INPUT_TYPE_UNKNOW           =  0,
    YWGUI_PANEL_INPUT_TYPE_PANEL            = ( 1 << 0 ),           /*  前面板按键 */
    YWGUI_PANEL_INPUT_TYPE_REMOTE           = ( 1 << 1 ),           /*  红外遥控输入 */
    YWGUI_PANEL_INPUT_TYPE_JOYSTICK         = ( 1 << 2 ),           /*  游戏杆输入 */
    YWGUI_PANEL_INPUT_TYPE_KEYBOARD         = ( 1 << 3 )            /*  无线键盘输入 */
}YWGUI_PANEL_InputType_T;

typedef struct YWGUI_PanelEquipmentList_s
{
    YWGUI_PanelEquipmentType_T   eEquipType;
    union
    {
        YWGUI_KeyboardParams_T       RemoteList;
        YWGUI_FrontPanelParams_T      FpList;
        YWGUI_LbdParams_T                LbdList;
    }Entity;
} YWGUI_PanelEquipmentList_T;

typedef struct YWGUI_PanelDeviceList_s
{
    U32                    DisplayTypeCap;              /* 支持显示类型 */
    U32                    InputTypeCap;                /* 支持输入类型 */
    U32                    RemoteNumCap;                /* 最多支持遥控器数 */
    U32                    LBDTypeCap;                  /* 支持的lbd */
    U32                    LEDNum;                      /* led数量 */
    U32                    FrontInputKeyCap;            /* 支持的前面板按键类型 */
    void *                 PrivateData;
    U32                 PanelIndex;
}YWGUI_PanelDeviceList_T;

/*Panel Feature*/
typedef struct YWGUI_PanelFeature_s
{
    U32                     PanelNum;            /* Panel数量 */
    YWGUI_PanelDeviceList_T        *PanelListHead;             /* Panel链表头指针*/
} YWGUI_PanelFeature_T;

YWGUI_API YW_ErrorType_T   YWGUI_PanelGetFeature(YWGUI_PanelFeature_T *PanelFeature);
YWGUI_API YW_ErrorType_T  YWGUI_SetPanelLEDStr(U8* pcLEDStr, U16 uStrLen);
YWGUI_API YW_ErrorType_T  YWGUI_DispPanelLEDStr(void);
YWGUI_API YW_ErrorType_T  YWGUI_DispPanelLEDTime(void);
YWGUI_API YW_ErrorType_T  YWGUI_ClearPanelLED(void);
YWGUI_API YW_ErrorType_T  YWGUI_SetPanelLBDStatus(YWGUI_PanelLBDType_T  eLBDType, YWGUI_PanelLBDStatus_T  eLBDStatus);
YWGUI_API YW_ErrorType_T  YWGUI_PanelVFDIoControl(YWGUI_PanelVFDIoControlType_T  eIoCtlType, void * pvParam);
YWGUI_API YW_ErrorType_T  YWGUI_SetPanelStbyKey(YWGUI_PanelStandByKeyParam_T  *ptParam);
YWGUI_API YW_ErrorType_T  YWGUI_GetPanelStbyKey(YWGUI_PanelStandByKeyParam_T  *ptParam);
YWGUI_API YW_ErrorType_T  YWGUI_SetPanelBlueKey(YWGUI_PanelBlueKeyParam_T  *ptParam);
YWGUI_API YW_ErrorType_T  YWGUI_GetPanelBlueKey(YWGUI_PanelBlueKeyParam_T  *ptParam);
YWGUI_API YW_ErrorType_T  YWGUI_SetPanelVfdStandbyState(BOOL  IsStandby);
YWGUI_API YW_ErrorType_T  YWGUI_GetPanelVfdStandbyState(BOOL  *IsStandby);
YWGUI_API YW_ErrorType_T  YWGUI_GetPanelPowerOnState(BOOL  *pIsCheck);
YWGUI_API YW_ErrorType_T  YWGUI_SetPanelPowerOnState(BOOL  IsCheck);
YWGUI_API YW_ErrorType_T  YWGUI_GetPanelLoopState(BOOL  *pIsCheck);
YWGUI_API YW_ErrorType_T  YWGUI_SetPanelLoopState(BOOL  IsCheck);
YWGUI_API YW_ErrorType_T  YWGUI_GetPanelStartUpState(YWGUI_PanelStartUpStat_T * pstState);
YWGUI_API YW_ErrorType_T  YWGUI_PanelControlTime(BOOL bStart);
YWGUI_API YW_ErrorType_T  YWGUI_PanelAddEqupment(YWGUI_PanelEquipmentList_T* pstEquList);
YWGUI_API YW_ErrorType_T  YWGUI_PanelDeleteEquiment(YWGUI_PanelEquipmentList_T* pstEquList);
YWGUI_API YW_ErrorType_T  YWGUI_SetPanelKeyRepeatSpeed(U32 uSpeed);

YWGUI_API YW_ErrorType_T YWGUI_RemoteDisable(void);
YWGUI_API YW_ErrorType_T YWGUI_RemoteEnable(void);
YWGUI_API YW_ErrorType_T YWGUI_FrontPanelDisable(void);
YWGUI_API YW_ErrorType_T YWGUI_FrontPanelEnable(void);

#endif
/*end of added*/
/*下面几个接口用于从文字创建位图*/

/***********************************************************************
函数名称: YWGUI_SelectBitmapTextFont
函数功能: 为位图选择字体
参    数:          hFont   字体句柄
返 回 值:    前一个字体的句柄
修改记录:
************************************************************************/
YWGUI_API YWGUI_HFont_T  YWGUI_SelectBitmapTextFont(YWGUI_HFont_T hFont);
/***********************************************************************
函数名称: YWGUI_CreatBitmapFromText
函数功能: 从文本创建位图
参    数:          spText 文本字符串
                            len   需要转换的长度
                            textColor 文本的颜色
                            bkColor   背景色
                            Flags  需要转换成的位图的格式,参见ywmid.h
                            ptBmp 转换的到的位图数据
                            ptBoundRect 限定矩形,如果转换的文本较长时用于自动换行，可传NULL
返 回 值:    错误码
相关函数:YWGUI_DeleteBitmap

修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_CreatBitmapFromText(const YWGUI_Char_T* spText, S32 len, YWGUI_Pixel_T textColor, YWGUI_Pixel_T bkColor, U32 format, U32 Flags, YWMID_DibitmapData_T * ptBmp, YWMID_Rect_T * ptBoundRect);
/***********************************************************************
函数名称: YWGUI_DeleteBitmap
函数功能: 删除通过YWGUI_CreatBitmapFromText创建的文图
参    数:          ptBmp 位图数据
返 回 值:    错误码
相关函数:YWGUI_CreatBitmapFromText
修改记录:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_DeleteBitmap(YWMID_DibitmapData_T * ptBmp);
YWGUI_API void  YWGUI_GetDeskTopHdl(YWGUI_HWnd_T *hWnd);//added by jhy

//是否启用定时器,如果不需要就不 启用
//LZ: move to ywplugin.mak for global useage
//#define YWGUI_ENABLE_TIMER

#ifdef __cplusplus
}
#endif

#endif


