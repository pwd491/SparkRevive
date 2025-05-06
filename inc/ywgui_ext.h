#ifndef _YWGUI_EXT_H_20080416_
#define  _YWGUI_EXT_H_20080416_

/*******************************************************************************
**********************************���뿪��*************************************
*******************************************************************************/

#ifndef YWGUI_WITHIN
//ywgui�ⲿ

#endif

#define _YWGUI_WCHAR_DEF_                    1

/*******************************************************************************
***********************************ƽ̨����*************************************
*******************************************************************************/

#ifdef WIN32
    //win32ƽ̨
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
        //���ַ�
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
        //���ַ�
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
***********************************�������*************************************
*******************************************************************************/


typedef     U32                     YWGUI_HWnd_T;
typedef     U32                     YWGUI_HDc_T;
//typedef     U32                     YWGUI_HBitmap_T;
typedef     U32                     YWGUI_HGraphCell_T;
typedef     U32                     YWGUI_Handle_T;
typedef     U32                     YWGUI_HFont_T;


/*******************************************************************************
***************************���������Ͷ���*************************************
*******************************************************************************/

typedef U32                  YWGUI_Size_T;

typedef U8                  YWGUI_Pixel_T[4];

//����ָ������
typedef  void (*YWGUI_InitDlgTLinkFunc_P)(void);

typedef  YWGUI_Char_T *(*YWGUI_LoadStringFunc_P)(S32);


typedef  void (*YWGUI_ModifyDefScheFunc_P)(void);

typedef  void (*YWGUI_ModifyCtrlDefScheFunc_P)(void);


typedef  S32 (*YWGUI_WindowProc_P)(YWGUI_HWnd_T, S32, WPARAM, LPARAM);

typedef void (*YWGUI_KeyPreProcess_P)(U32 *, U32*); /*added by sly, 2009-6-8, ����Ԥ������*/
//ö������

enum
{
    //YWGUI �������Ͷ���
    YWGUI_ERROR =YW_MODULE_SET_ID (YWMID_MODULE_GUI_ID ) ,
    YWGUI_ERROR_INVALID_HANDLE,/*��Ч���*/
    YWGUI_ERROR_BAD_PARAMETER, /*�Ƿ�����*/
    YWGUI_ERROR_LAWLESS_CALL,  /*�Ƿ�����*/
    YWGUI_ERROR_BUF_FULL,      /*��������*/
    YWGUI_ERROR_MEM_NO_ENOUGH, /*�ڴ治��*/
    YWGUI_ERROR_RES_NO_ENOUGH, /*��Դ����*/
    YWGUI_ERROR_CHECK,          /*У�����*/
    YWGUI_ERROR_TERMINATE,      /*ǿ����ֹ����*/
    YWGUI_ERROR_NO_USE,         /*δʹ��*/
    YWGUI_ERROR_NO_SUPPORTED,   /*��֧��*/
    YWGUI_ERROR_NOT_FOUND       /*û���ҵ�*/
};

enum
{
    YWGUI_ALPHA_MODE_GLOBAL=0,
    YWGUI_ALPHA_MODE_LOCAL
};



typedef  enum YWGUI_RemoteProtocol_e
{
    YWGUI_PROTOCOL_NONE                       = 0,
    YWGUI_PROTOCOL_NEC                        = ( 1 << 0 ),        /* NECЭ�� */
    YWGUI_PROTOCOL_PHILIPS_RC6                = ( 1 << 1 ),        /* Philips_RC6Э��*/
    YWGUI_PROTOCOL_PHILIPS_RC5                = ( 1 << 2 ),        /* Philips_RC6Э��*/
    YWGUI_PROTOCOL_PHILIPS                    = ( 1 << 3 ),        /* PhilipsЭ�� */
    YWGUI_PROTOCOL_USEDEFINE_YW_C03F          = ( 1 << 4 ),
    YWGUI_PROTOCOL_USEDEFINE_YW_40BD          = ( 1 << 5 ),
    YWGUI_PROTOCOL_USEDEFINE_YW_807F          = ( 1 << 6 ),
    YWGUI_PROTOCOL_USEDEFINE_YW_0202          = ( 1 << 7 )
}YWGUI_RemoteProtocol_E;


typedef enum YWGUI_FrameType_e
{
    //�߿�����

    FRAME_NO,     //�ޱ߿�
    FRAME_RECT,   //���α߿�
    FRAME_GRAPH   //ͼ�α߿�
}YWGUI_FrameType_E;

typedef enum YWGUI_SpellType_e
{
    //ͼ��ƴ������

    SPELL_GRAPH,          //һ��ͼ
    SPELL_GRAPH_REPEAT_H, //һ��ͼ��������ƴ��
    SPELL_GRAPH_REPEAT_V, //һ��ͼ��������ƴ��
    SPELL_GRAPH_REPEAT_HV, //һ��ͼ������������ƴ��
    SPELL_3GRAPH_H,       //����ͼ����ƴ��(������,�м����ѭ��)
    SPELL_3GRAPH_V,       //����ͼ����ƴ��(������,�м�����ѭ��)
    SPELL_5GRAPH_H,       //����ͼ����ƴ��(�󡢴����С����ҡ��ң��м����ѭ��)
    SPELL_5GRAPH_V,       //����ͼ����ƴ��(�ϡ����ϡ��С����¡��£��м�����ѭ��)
    SPELL_8GRAPH,		  //8��ͼƴ��(���Ͻ�,�ϱ�(����ѭ��),���Ͻ�,���(����ѭ��),�ұ�(����ѭ��),���½�,�±�(����ѭ��),���½�)
    SPELL_16GRAPH,        //16��ͼƴ��(��8��ͼƴ�ձȽϣ�ÿ���߿���3��ͼ���ɣ����м������ͼƬѭ��)
    SPELL_24GRAPH         //24��ͼƴ��(��8��ͼƴ�ձȽϣ�ÿ���߿���5��ͼ���ɣ����м������ͼƬѭ��)
}YWGUI_SpellType_E;


typedef enum YWGUI_DcAttr_e
{
    //YWGUI_GetDCAttr / YWGUI_SetDCAttr ����ʹ��

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
    //������ɫ����

    YWGUI_DESKTOP_BGCOLOR=0,//���汳��ɫ

    //������(normal)
    YWGUI_MAINWND_BGC ,     //����ɫ
    YWGUI_MAINWND_FGC,      //ǰ��ɫ
    YWGUI_MAINWND_FRAMEC,   //�߿�ɫ

    //������(disable)
    YWGUI_MAINWND_DISABLE_BGC ,     //����ɫ
    YWGUI_MAINWND_DISABLE_FGC,      //ǰ��ɫ
    YWGUI_MAINWND_DISABLE_FRAMEC,   //�߿�ɫ

    //������(focus)
    YWGUI_MAINWND_FOCUS_BGC ,       //����ɫ
    YWGUI_MAINWND_FOCUS_FGC,        //ǰ��ɫ
    YWGUI_MAINWND_FOCUS_FRAMEC,     //�߿�ɫ

    //�ؼ�(normal)
    YWGUI_NORMAL_CTRL_BGC,          //����ɫ
    YWGUI_NORMAL_CTRL_FGC,          //ǰ��ɫ(�ı���ɫ)
    YWGUI_NORMAL_CTRL_FRAMEC,       //�߿�ɫ

    //�ؼ�(disable)
    YWGUI_DISABLE_CTRL_BGC,
    YWGUI_DISABLE_CTRL_FGC,
    YWGUI_DISABLE_CTRL_FRAMEC ,

    //�ؼ�(active focus)
    YWGUI_AFOCUS_CTRL_BGC,
    YWGUI_AFOCUS_CTRL_FGC,
    YWGUI_AFOCUS_CTRL_FRAMEC,

    //�ؼ�(sleep focus)
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
    //������������
    YWGUI_WEM_BORDER_WIDTH,
    YWGUI_WEM_THICKFRAME_WIDTH,
    YWGUI_WEM_THINFRAME_WIDTH,
    YWGUI_WEM_BAR_BORDER, // ���� posbar ͷ�˵Ŀ�� �� ���� posbar ͷ�˵ĸ߶�

    YWGUI_WEM_SCEME_ITEM_NUM
}YWGUI_WemItem_E;

typedef enum YWGUI_WesItem_e
{
    //������۷���

    YWGUI_STATUS_NORMAL=0,
    YWGUI_STATUS_DISABLED,
    YWGUI_STATUS_AFOCUS,
    YWGUI_STATUS_SFOCUS,

    YWGUI_WES_STATUS_NUM
}YWGUI_WesItem_E;

typedef enum YWGUI_BkMode_e
{
    //YWGUI_SetBkMode ����ʹ��

    YWGUI_BM_OPAQUE = 0,     //��͸��
    YWGUI_BM_TRANSPARENT      //͸��
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
    YWGUI_IME_TYPE_DIRECT,   //ֱ������
    YWGUI_IME_TYPE_REUSE     //������������
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
    YWGUI_CANVAS_OP_MODE_COLORKEY        = (1 << 17),/*color mode --- ��ʹ�ô�ģʽʱ�� YWGUI_CANVAS_PixelFormat_T��Colorkey ��ָʾ����ɫ������ Ŀǰ��Ҫ��DrawImage�Դ�ģʽ��֧�֣� */
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
***********************************��������*************************************
*******************************************************************************/
#define YWGUI_INVALID_STRING_ID     (0xFFFFFFFF)

#define YWGUI_NULL_HANDLE               (0)

#define YWGUI_CLASSNAME_MAX             15


/*******************************************************************************
************************************�궨��**************************************
*******************************************************************************/
#define YWGUI_3DFRAME_LEFT_INNERC         YWGUI_3DBOX_DARKC
#define YWGUI_3DFRAME_RIGHT_INNERC        YWGUI_3DBOX_NORMALC
#define YWGUI_3DFRAME_LEFT_OUTERC         YWGUI_3DBOX_REVERSEC
#define YWGUI_3DFRAME_RIGHT_OUTERC        YWGUI_3DBOX_LIGHTC


#define YWGUI_SW_HIDE                   0x0000
#define YWGUI_SW_SHOW                   0x0010
#define YWGUI_SW_SHOWTOP                0x0100

//YWGUI_DrawText ʹ��
#define YWGUI_DT_LEFT                   0x00000000
#define YWGUI_DT_TOP                    0x00000000
#define YWGUI_DT_CENTER                 0x00000001
#define YWGUI_DT_RIGHT                  0x00000002
#define YWGUI_DT_VCENTER                0x00000004
#define YWGUI_DT_BOTTOM                 0x00000008

/*YWGUI_DT_WORDBREAK:
һ����ʾ����ʱ���Ե���Ϊ��λ�Զ�����
*/
#define YWGUI_DT_WORDBREAK              0x00000010
#define YWGUI_DT_SINGLELINE             0x00000020

/*YWGUI_DT_EXPANDTABS:
����߱��÷��'\t' ��չ�ɿհ���,���������
*/
#define YWGUI_DT_EXPANDTABS             0x00000040

/*YWGUI_DT_TABSTOP:
�߱��÷��ʱ����16λΪÿ�� tab ��������ַ�����;
���߱��÷��ʱ��ÿ�� tab ��������ַ������� DC ȷ��(Ĭ��Ϊ8)
*/
#define YWGUI_DT_TABSTOP                0x00000080

#define YWGUI_DT_NOCLIP                 0x00000100
#define YWGUI_DT_CALCRECT               0x00000200 //�ݲ�֧��

#define YWGUI_DT_NEGINDENT               0x00000400 //֧�ָ�������

/*YWGUI_DT_CHARBREAK:
һ����ʾ����ʱ�����ַ�Ϊ��λ�Զ�����
*/
#define YWGUI_DT_CHARBREAK             0x00000800

#if 0
//�豸�޹�λͼ
//ע:�豸�޹�λͼ�ĺ�Ҫ��λͼת�����߶���һ��
#define YWMID_DIBMP_FLOW_DOWN           0x00000000//���ϵ���(Ĭ��)
#define YWMID_DIBMP_FLOW_UP             0x00000001 //���µ���
#define YWMID_DIBMP_FLOW_MASK           0x0000000F

#define YWMID_DIBMP_COMPRESS_NO         0x00000000 //��ѹ��(Ĭ��)
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
********************************��Ϣ�궨��**************************************
*******************************************************************************/

//����ʷԭ��,������0x0220-0x029F


//��һ��(ywgui�ڲ���Ϣ)
#define YWGUI_FIRSTINNERMSG                    0x0001
#define YWGUI_LASTINNERMSG                     0x00FF

//�ڶ���
//�������(��Ӧ��)��Ϣ,Ԥ����������չ,��Ŀǰ��������֧��
#define YWGUI_FIRSTMOUSEMSG                    0x0100
#define YWGUI_LASTMOUSEMSG                     0x011F
//0x0100~0x010F �����ڲ���Ϣ

#define YWGUI_MSG_MOUSEMOVE                    0x0110

//������
#define YWGUI_FIRSTKEYMSG                      0x0120
#define YWGUI_LASTKEYMSG                       0x013F
//0x0120~0x012F �����ڲ���Ϣ

#define YWGUI_MSG_KEYDOWN                      0x0130

/*
YWGUI_MSG_CHAR
wParam: unicode �ַ���
*/
#define YWGUI_MSG_CHAR                         0x0131

#define YWGUI_MSG_KEYUP                        0x0132

#define YWGUI_MSG_SYSKEYDOWN                   0x0133

#define YWGUI_MSG_SYSKEYUP                     0x0134

//������
#define YWGUI_FIRSTPOSTMSG                     0x0140
#define YWGUI_LASTPOSTMSG                      0x018F
//0x0140~0x014F �����ڲ���Ϣ

/*
YWGUI_MSG_SIZING֪ͨ
˵��: ���ڳߴ罫Ҫ�����仯(�紴������/�ƶ�����)ʱ���͸���Ϣ;
      Ӧ�ô������Ϣ,��������ָ������λ��;
wParam: Ԥ�ڵĴ��ھ���(����ڸ����ڿͻ�������)
lParam: ����ָ���Ĵ��ھ���(����ڸ����ڿͻ�������),
*/
#define YWGUI_MSG_SIZING                        0x0150

/*
YWGUI_MSG_CSIZING֪ͨ
˵��: ���ڿͻ����ߴ緢���仯ʱ���͸���Ϣ;
      Ӧ�ô������Ϣ,��������ָ�����ڿͻ�����С(�޸�lParam��ָ��ľ���);
wParam: ָ�򴰿ھ���(����ڸ����ڿͻ�������)
lParam: ָ��ͻ�������(����ڸ����ڿͻ�������)
*/
#define YWGUI_MSG_CSIZING                       0x0151

/*
YWGUI_MSG_CSIZE֪ͨ
����Ϣ����֪ͨ�û����ڿͻ�����С�Ѹı䡣
wParam�� �ͻ������
lParam: �ͻ����߶�
*/
#define YWGUI_MSG_CSIZE                         0x152


/*YWGUI_MSG_SETFOCUS
˵��: ���ڵõ�����֮���͸���Ϣ
wParam: ʧȥ����Ĵ��ھ��
*/
#define YWGUI_MSG_SETFOCUS                      0x0160

/*YWGUI_MSG_KILLFOCUS
˵��: ����ʧȥ����֮���͸���Ϣ
wParam: ��ý���Ĵ��ھ��
*/
#define YWGUI_MSG_KILLFOCUS                     0x0161

/*YWGUI_MSG_ACTIVE֪ͨ
wParam: TRUE--����;FALSE--ʧ��
lParam: δ��
*/
#define YWGUI_MSG_ACTIVE                        0x0162

/*
YWGUI_MSG_CHILDHIDDEN֪ͨ
˵��:YWGUI_WS_EX_CTRLASMAINWIN���Ŀؼ������غ�,���͸�֪ͨ���丸����
*/
#define YWGUI_MSG_CHILDHIDDEN                   0x0163

//������
#define YWGUI_FIRSTCREATEMSG                    0x0190
#define YWGUI_LASTCREATEMSG                     0x01DF
//0x0190~0x019F �����ڲ���Ϣ


/*YWGUI_MSG_CREATE֪ͨ
������:wParam--δ��; lParam--ָ��YWGUI_MainWinCreate_T�ṹ
�Ӵ���:wParam--�����ھ��;lParam --YWGUI_CreateWidgetWindow �����dwAddData
����ֵ:���㣬���ڽ�����������.
*/
#define YWGUI_MSG_CREATE                        0x01A0

/*YWGUI_MSG_NCCREATE ֪ͨ
�ڴ��ڱ�����,����δע�ᵽϵͳʱ���ʹ���Ϣ��
����Ϣ����MSG_CREATE����,���յ�����Ϣʱ,�в��ܴ����Ӵ��ڣ�
Ҳ���ܵõ���ͼ���豸�����ľ��. �������ֵ���㣬���ڽ�����������.

������: wParam -- δ��; lParam--ָ��YWGUI_MainWinCreate_T�ṹ
�Ӵ���: wParam -- δ��; lParam--ָ�� YWGUI_Control_T �ṹ
����ֵ:���㣬���ڽ�����������.
*/
#define YWGUI_MSG_NCCREATE                       0x01A1

#define YWGUI_MSG_DESTROY                        0x01A2

#define YWGUI_MSG_CLOSE                          0x01A3

//������
#define YWGUI_FIRSTPAINTMSG                      0x01E0
#define YWGUI_LASTPAINTMSG                       0x021F
//0x01E0~0x01EF �����ڲ���Ϣ


#define YWGUI_MSG_NCACTIVATE                     0x01F0

/*
YWGUI_MSG_NCPAINT
˵��: ���ڻ�ͼ˳��(���->����->ǰ��)
wParam:δ��
lParam:δ��
*/
#define YWGUI_MSG_NCPAINT                        0x01F1

/*YWGUI_MSG_ERASEBKGND
wParam --DC���
lParam -- δ��
*/
#define YWGUI_MSG_ERASEBKGND                     0x01F2

/*YWGUI_MSG_PAINT
˵��:
wParam : δ��
lParam : δ��
*/
#define YWGUI_MSG_PAINT                          0x01F3




//����0x0220-0x029F


//������

#define YWGUI_FIRSTCONTROLMSG                    0x02A0
#define YWGUI_LASTCONTROLMSG                     0x03AF
//0x02A0~0x2AF �����ڲ���Ϣ


/**YWGUI_MSG_COMMAND֪ͨ
wParam: ��16λ�ؼ�ID,��16λ֪ͨ��
lParam: �ؼ����ھ��*/
#define YWGUI_MSG_COMMAND                        0x02B0

#define YWGUI_MSG_NOTIFY                         0x02B1

/*
YWGUI_MSG_NOTIFY_NCCREATE֪ͨ

�ؼ��յ�YWGUI_MSG_NCCREATE��,�������ڷ��͸�֪ͨ
wParam:��16λ�ؼ�ID,��16λ����(0)
lParam:�ؼ����ھ��
*/

#define YWGUI_MSG_NOTIFY_NCCREATE                 0x02B2

/*YWGUI_MSG_INITDIALOG֪ͨ
wParam : �����õ�Ĭ�Ͻ��㴰�ھ��
lParam: �����Ի���ʱ����Ĳ���ֵ
����ֵ:1--�������1,������wParam��ָ���Ĵ��ڻ�ð�������,
                  ��������Ĭ�ϵĽ��㴰��
*/
#define YWGUI_MSG_INITDIALOG                      0x02B3

#define YWGUI_MSG_ENABLE                          0x02B4


/*YWGUI_MSG_SETTEXT
wParam: δ�� (0)
lParam: ���õ��ı��ַ���
����ֵ:
*/

#define YWGUI_MSG_SETTEXT                         0x02C0

/*YWGUI_MSG_GETTEXTLENGTH
wParam: δ�� (0)
lParam: δ�� (0)
����ֵ: �ı��ַ�������(���ַ�����),������������
ע��:   UCS2 һ���ַ�ռ�����ֽ�
*/
#define YWGUI_MSG_GETTEXTLENGTH                   0x02C1

/*YWGUI_MSG_GETTEXT
wParam: ָ���������Ĵ�С(�ֽڸ���)
lParam: ������ָ��
����ֵ: ���������������ַ���,������������
ע��:   UCS2 һ���ַ�ռ�����ֽ�
*/
#define YWGUI_MSG_GETTEXT                         0x02C2

/*YWGUI_MSG_GETCTRLCODE
wParam: 0
lParam: 0
����ֵ: �ؼ�����ļ�ֵ
*/
#define YWGUI_MSG_GETCTRLCODE                0x02C3

//�ض��ؼ�����Ϣ��0x0300��ʼ����
//����0x0300~0x034F���ڲ���Ϣ
//0x0350~0x03AF ����Ӧ�ÿ��ŵ���Ϣ

//�ڰ���

#define YWGUI_FIRSTSYSTEMMSG                      0x03B0
#define YWGUI_LASTSYSTEMMSG                       0x03FF

//0x03B0~0x3BF �����ڲ���Ϣ


#define YWGUI_MSG_QUIT                            0x03C0


/*YWGUI_MSG_TIMER
wParam: ��ʱ��ID (YWGUI ��װ�Ķ�ʱ��ID)
lParam: δ��
ע��: 1) YWGUI���֧�� 32 ����ʱ��
      2) ���д��ڼ���������ʹ��32����ʱ�� (���б���7����GUIϵͳ�Լ�ʹ��)
*/
#define YWGUI_MSG_TIMER                           0x03C1


#define YWGUI_MSG_IME_OPEN                        0x03C2

#define YWGUI_MSG_IME_CLOSE                       0x03C3

#define YWGUI_MSG_IME_SETTARGET                   0x03C4

#define YWGUI_MSG_IME_SETPROMPT                   0x03c5

//append by Eagle 2009-06-01
#define YWGUI_MSG_IME_CURCHAR                     0x03c6


//�ھ���
#define YWGUI_MSG_USER                           0x0800

/*******************************************************************************
************************YWGUI_MSG_COMMAND֪ͨ�붨��****************************
*******************************************************************************/
//16λ��ʾ
//�ؼ�ͨ�õ�֪ͨ��:  0x0001--0x0200
//���ض��ؼ���֪ͨ��:0x0201--0xFFFF
#define YWGUI_NONE_CODE                         0x0000

#define YWGUI_NC_KILLFOCUS                      0x0100
#define YWGUI_NC_SETFOCUS                       0x0101

/*******************************************************************************
*******************************����ɨ���붨��***********************************
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
#else/*����linux input�ı�׼����������*/
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

//�û��Զ������ʼ��ַ
#define YWGUI_SCANCODE_USER                      0x20


/*******************************************************************************
*******************************���ڷ����***********************************
*******************************************************************************/
//���ڷ��(ʹ�ø�16λ,���µ�16λ����ؼ����)
#define YWGUI_WS_NONE                         0x00000000L

#define YWGUI_WS_TABSTOP                      0x00010000L
#define YWGUI_WS_HSCROLL                      0x00040000L
#define YWGUI_WS_VSCROLL                      0x00080000L

#define YWGUI_WS_THINFRAME                    0x00100000L  //ϸ�߿�
#define YWGUI_WS_THICKFRAME                   0x00200000L  //�ֱ߿�
#define YWGUI_WS_BORDER                       0x00400000L
#define YWGUI_WS_DLGFRAME                     0x00800000L


#define YWGUI_WS_DISABLED                     0x04000000L
#define YWGUI_WS_VISIBLE                      0x08000000L

#define YWGUI_WS_CAPTION                      0x20000000L
#define YWGUI_WS_CHILD                        0x40000000L

/*******************************************************************************
*******************************������չ�����***********************************
*******************************************************************************/
//������չ���
//�ڲ�������¼����״̬ʹ��: ��4λ
//�ⲿ����������չ���ʹ��: ��24λ
#define YWGUI_WS_EX_NONE                  0x00000000L

#define YWGUI_WS_EX_TOPMOST               0x00000001L
#define YWGUI_WS_EX_TRANSPARENT           0x00000002L
#define YWGUI_WS_EX_TOOLWINDOW            0x00000004L

/*
YWGUI_WS_EX_USEPARENTFONT
˵��: 1)�÷���ṩ���ؼ�ʹ��;
      2)���ؼ��ı�ʹ���丸��������ʱ��ʹ�ø÷��
*/
#define YWGUI_WS_EX_USEPARENTFONT            0x00000008L

/*
YWGUI_WS_EX_USEPARENTFONT
˵��: 1)�÷���ṩ�������ںͿؼ�ʹ��;
      2)������δ����֮ǰ,��ID��Ӧ���ַ���Ҫһֱ����,������ܻ����ʹ�÷Ƿ���ַ
      3)�÷����Ҫ���ڶ�̬�����ַ���,����ʵ�ֶ������л�
*/
#define YWGUI_WS_EX_USECAPTIONID     0x00000010L

/*
YWGUI_WS_EX_IRREGULAR
˵��: 1)�÷���ṩ��������������ʹ��;
      2)���������ǲ����򴰿��Ҵ���ˢ�²���������ʱ��ʹ�ø÷��
*/
#define YWGUI_WS_EX_IRREGULAR             0x00100000L


/*
YWGUI_WS_EX_TITLECTRL
˵��: 1)�÷���ṩ�� static �ؼ�ʹ��
      2)���ؼ���Ҫ���õ��丸���ڿ����ʱ��ʹ�ø÷��
      2)ʹ�ø÷��󣬿ؼ��Ĵ��ھ��μ��ͻ���������
        ����ڸ����ڴ��ھ���(����Ը����ڿͻ�������)������
*/
#define YWGUI_WS_EX_TITLECTRL             0x00200000L

/*
YWGUI_WS_EX_FORCEERASEBG
˵��: 1)�÷���ṩ�������ںͿؼ�ʹ��
      2)��ͬʱ������ָ���˱���ͼ���ͱ���ɫʱ��
        �������ͼ�����ܸ��������ͻ�����ʹ�ø÷��
*/
#define YWGUI_WS_EX_FORCEERASEBG          0x00400000L

/*
YWGUI_WS_EX_NOTIFY
˵��: 1)�÷���ṩ���ؼ�ʹ��
      2)����Ҫ�ؼ�����֪ͨ��Ϣ��������ʱ,ʹ�ø÷��
      3)��ؼ��õ�����,ʧȥ����ʱ,���ؼ��и÷��,��֪ͨ������
*/
#define YWGUI_WS_EX_NOTIFY                0x00800000L




/* The control can be displayed out of the main window which contains the control. */
#define YWGUI_WS_EX_CTRLASMAINWIN         0x04000000L



/** When paint the window, the children areas will be clipped. */
#define YWGUI_WS_EX_CLIPCHILDREN          0x08000000L


/*******************************************************************************
*******************************��׼�ؼ� ID����***********************************
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
*******************************�ؼ���������***********************************
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
*******************************����ؼ��ඨ��***********************************
*******************************************************************************/

/*=============================�ؼ������=================================*/

//�ؼ������õ�16λ

/*****************************static �ؼ����*******************************/

#define YWGUI_SS_TYPEMASK          0x00000003L //��������(2bit)
#define YWGUI_SS_SIMPLE            0x00000000L //Ĭ��
#define YWGUI_SS_GROUPBOX          0x00000001L

#define YWGUI_SS_HALIGNMASK        0x0000000CL //������뷽ʽ����(2bit)
#define YWGUI_SS_LEFT              0x00000000L //Ĭ��(����)
#define YWGUI_SS_CENTER            0x00000004L //�������
#define YWGUI_SS_RIGHT             0x00000008L //����

#define YWGUI_SS_VALIGNMASK        0x00000030L //������뷽ʽ����(2bit)
#define YWGUI_SS_TOP               0x00000000L //Ĭ��(����)
#define YWGUI_SS_VCENTER           0x00000010L //�������
#define YWGUI_SS_BOTTOM            0x00000020L //����
//#define YWGUI_SS_NOAUTOBREAK       0x00001000L //���Զ�����(Ĭ�ϣ��Զ�����)
/*Ĭ�ϰ�������*/
#define YWGUI_SS_WORDBREAK         0x00001000L //�����ʻ���
#define YWGUI_SS_CHARBREAK         0x00002000L //����ĸ����
#define YWGUI_SS_ROLLDISP          0x0004000L //������ʾ(�������ҹ���)(ֻ�ܵ���,������ʾʱ������)
#define YWGUI_SS_ROLLDISP_REVERSE  0x0008000L //������ʾ(�����������)(ֻ�ܵ���,������ʾʱ������)

/*****************************button �ؼ����*******************************/
#define YWGUI_BS_TYPEMASK          0x00000003L //��������(2bit)

#define YWGUI_BS_HALIGNMASK        0x0000000CL//������뷽ʽ����(2bit)
#define YWGUI_BS_LEFT              0x00000000L //Ĭ��
#define YWGUI_BS_CENTER            0x00000004L
#define YWGUI_BS_RIGHT             0x00000008L

#define YWGUI_BS_VALIGNMASK        0x00000030L//������뷽ʽ����(2bit)
#define YWGUI_BS_TOP               0x00000000L//Ĭ��
#define YWGUI_BS_VCENTER           0x00000010L
#define YWGUI_BS_BOTTOM            0x00000020L

/*****************************picture �ؼ����*******************************/
#define YWGUI_PS_TYPEMASK          0x00000003L //��������(2bit)
#define YWGUI_PS_BITMAP            0x00000000L //Ĭ��(λͼ)
#define YWGUI_PS_ICON              0x00000001L //�ݲ�֧��

#define YWGUI_PS_ALIGNMASK         0x0000000CL //���з�ʽ����(2bit)
#define YWGUI_PS_CENTER            0x00000000L //���з�ʽ��Ĭ�ϣ�
#define YWGUI_PS_STRETCH           0x00000004L //�������С����Ӧ�ؼ���С(�ݲ�֧��)



/*****************************posbar �ؼ����*******************************/
#define YWGUI_POS_TYPEMASK          0x00000003L //��������(2bit)
#define YWGUI_POS_VERT              0x00000000L //Ĭ��(���� posbar)
#define YWGUI_POS_HORZ              0x00000001L //���� posbar

/*****************************progress bar  �ؼ����*******************************/
#define YWGUI_PBS_TYPEMASK          0x00000003L //��������(2bit)
#define YWGUI_PBS_HORZ              0x00000000L //Ĭ��(����)
#define YWGUI_PBS_VERT              0x00000001L //����

#define YWGUI_PBS_STRETCH           0x00001000L

/*********************************�༭�ؼ����*******************************/

//�̶�Thumb size
#define YWGUI_ES_PEGTHUMBSIZE       0x00000000L
//�Զ��ı�Thumb size0000
#define YWGUI_ES_AUTOTHUMBSIZE      0x00000001L

//add by Eagle 2009-06-04
//support SEDIT only
#define YWGUI_ES_REPLACE            0x00000002L

#define YWGUI_ES_HALIGNMASK         0x0000000CL //������뷽ʽ����(2bit)
#define YWGUI_ES_LEFT               0x00000000L //Ĭ��(����)
#define YWGUI_ES_CENTER             0x00000004L //�������
#define YWGUI_ES_RIGHT              0x00000008L //����

#define YWGUI_ES_VALIGNMASK        0x00000030L //������뷽ʽ����(2bit)
#define YWGUI_ES_TOP               0x00000000L //Ĭ��(����)
#define YWGUI_ES_VCENTER           0x00000010L //�������
#define YWGUI_ES_BOTTOM            0x00000020L //����

#define YWGUI_ES_MULTILINE          0x00000040L
#define YWGUI_ES_UPPERCASE          0x00000080L
#define YWGUI_ES_LOWERCASE          0x00000100L
#define YWGUI_ES_PASSWORD           0x00000200L

#define YWGUI_ES_READONLY           0x00000400L
#define YWGUI_ES_NUMBER             0x00000800L

#define YWGUI_ES_SCROLLMASK         0x00003000L //������뷽ʽ����(2bit)
#define YWGUI_ES_AUTOSCROLL         0x00000000L
#define YWGUI_ES_NOSCROLL           0x00001000L
#define YWGUI_ES_ALWAYSSCROLL       0x00002000L

//���Զ�����
#define YWGUI_ES_NOAUTOBREAK        0x00004000L
#define YWGUI_ES_AUTOWORDBREAK  0x00008000L

/*********************************Listbox�ؼ����*******************************/
#define YWGUI_LBS_NOTIFY             0x0001L
#define YWGUI_LBS_MULTIPLESEL        0x0002L
#define YWGUI_LBS_CHECKBOX           0x0010L
#define YWGUI_LBS_USEICON            0x0020L
//#define YWGUI_LBS_AUTOCHECK          0x0040L
//#define YWGUI_LBS_AUTOCHECKBOX       (YWGUI_LBS_CHECKBOX | YWGUI_LBS_AUTOCHECK)

#define YWGUI_LBS_AUTOSCROLL          0x0100L
#define YWGUI_LBS_NOSCROLL            0x0200L
#define YWGUI_LBS_ALWAYSSCROLL        0x0400L

//�̶�Thumb size
#define YWGUI_LBS_PEGTHUMBSIZE        0x1000L
//�Զ��ı�Thumb size
#define YWGUI_LBS_AUTOTHUMBSIZE       0x2000L
//�б��ѭ���л�
#define YWGUI_LBS_ITEMNOTLOOPMOVE     0x4000L
/*********************************Listview�ؼ����*******************************/
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

//�̶�Thumb size
#define YWGUI_LVS_PEGTHUMBSIZE        0x1000L
//�Զ��ı�Thumb size
#define YWGUI_LVS_AUTOTHUMBSIZE       0x2000L
//�б��ѭ���л�
#define YWGUI_LVS_ITEMNOTLOOPMOVE     0x4000L
/*********************************lrcombobox�ؼ����*******************************/
#define YWGUI_LRCBS_HALIGNMASK         0x0000000CL //������뷽ʽ����(2bit)
#define YWGUI_LRCBS_LEFT               0x00000000L //Ĭ��(����)
#define YWGUI_LRCBS_CENTER             0x00000004L //�������
#define YWGUI_LRCBS_RIGHT              0x00000008L //����

#define YWGUI_LRCBS_VALIGNMASK         0x00000030L //������뷽ʽ����(2bit)
#define YWGUI_LRCBS_TOP                0x00000000L //Ĭ��(����)
#define YWGUI_LRCBS_VCENTER            0x00000010L //�������
#define YWGUI_LRCBS_BOTTOM             0x00000020L //����

//���ѡ�д˷���ʾ���combobox�е�list��ʾ���˳���ֻ������list,
//������Ĭ�ϴ���(���������ڴ���)
#define YWGUI_LRCBS_EXITKEYHIDELIST     0x0040L
#define YWGUI_LRCBS_AUTOSCROLL        0x0080L
#define YWGUI_LRCBS_NOSCROLL          0x0100L
#define YWGUI_LRCBS_ALWAYSSCROLL      0x0200L


//�̶�Thumb size
#define YWGUI_LRCBS_PEGTHUMBSIZE        0x0400L
//�Զ��ı�Thumb size
#define YWGUI_LRCBS_AUTOTHUMBSIZE       0x0800L
//�б��ѭ���л������Ҽ�Ҳ��ѭ���л���
#define YWGUI_LRCBS_ITEMNOTLOOPMOVE     0x1000L
#define YWGUI_LRCBS_HIDELISTBOXALWAY    0x2000L


//add by Eagle 2009-05-06
//ListTable Style Marco
/*********************************ListTable�ؼ����********************************/
#define YWGUI_LTS_MARK              0x0001L
#define YWGUI_LTS_MUTISHAPE         0x0002L
#define YWGUI_LTS_MARKSTAY          0x0004L
#define YWGUI_LTS_DISABLE           0x0008L

//TP(͸��)
#define YWGUI_LTS_TPMASK            0x0030L
#define YWGUI_LTS_NORMALTP          0x0010L
#define YWGUI_LTS_FOCUSTP           0x0020L

#define YWGUI_LTS_ROLLDISP          0x0040L
#define YWGUI_LTS_ROLLDISP_REVERSE  0x0080L

/*���뷽ʽ*/
#define YWGUI_LTS_CENTER            0x0100L/*�������*/

//Disable������ѡ��ķ��,��������Disable��ʱ��ʱ�����е�ǰ��ɫΪDisable��ǰ��ɫ������ΪAfocus�ı���
#define YWGUI_LTS_DISABLE_NOTJUMP   0x0200L

//container
/*********************************Container�ؼ����********************************/
//ˮƽ��ʽ
#define YWGUI_CTS_HORIZONTAL        0x0
//��ֱ��ʽ
#define YWGUI_CTS_VERTICAL          0x1

/*=============================�ؼ���Ϣ����=================================*/
//�ض��ؼ�����Ϣ��0x0300��ʼ����
//����0x0300~0x034F���ڲ���Ϣ
//0x0350~0x03AF ����Ӧ�ÿ��ŵ���Ϣ


/*=============================�ؼ�֪ͨ�붨��=================================*/

//���ض��ؼ���֪ͨ��:0x0201--0xFFFF

/*****************************ListView�ؼ�֪ͨ��*******************************/


//ListView�ؼ�
//{
/**************************************
 YWGUI_LVN_SELCHANGED
 ����:��ʾѡ��״̬�Ѿ��ı�
 **************************************/
#define YWGUI_LVN_SELCHANGED           0x0201

/**************************************
 YWGUI_LVN_FOCUSITEMCHANGED
 ����:��ʾ�������Ѿ��ı�
 **************************************/
 #define YWGUI_LVN_FOCUSITEMCHANGED     0x0202
//}

/*****************************Listbox�ؼ�֪ͨ��*******************************/
//Listbox�ؼ�
//{
/****************************************************
 ����ѡ��ʱ, ѡ�л�ȡ��ѡ������򸸴��ڷ��ʹ���Ϣ
 (���͵�YWGUI_MSG_COMMAND��)
 ****************************************************/
#define YWGUI_LBN_SELCHANGED         0x0203

/****************************************************
 �����иı����򸸴��ڷ��ʹ���Ϣ,
 һ��Ϊ�����ƶ�,��ҳ��ʱ��Ż��򸸴��ڷ��ʹ���Ϣ
 (���͵�YWGUI_MSG_COMMAND��)
 ****************************************************/
#define YWGUI_LBN_FOCUSITEMCHANGED   0x0204
//}

/*****************************combobox�ؼ�֪ͨ��*******************************/
//ѡ�е����ݷ����ı�
#define YWGUI_LRCBN_CBCHANGE        0x0205

/*****************************Edit�ؼ�֪ͨ��***********************************/
/****************************************************
 ��Edit�����ַ��ı�ͻ��򸸴��ڷ��ʹ��¼�
 (���͵�YWGUI_MSG_COMMAND��)
 ****************************************************/
#define YWGUI_EN_CHANGE           0x0206

/****************************************************
 ��Edit����༭״̬����򸸴��ڷ��ʹ��¼�
 (���͵�YWGUI_MSG_COMMAND��)
 ****************************************************/
#define YWGUI_EN_ENTEREDITSTATUS  0x0207

/****************************************************
 ��Edit�˳��༭״̬����򸸴��ڷ��ʹ��¼�
 (���͵�YWGUI_MSG_COMMAND��)
 ****************************************************/
#define YWGUI_EN_EXITEDITSTATUS   0x0208

/****************************************************
 ��Edit���ݸı�(��ʵ�ı�)���˳��˱༭״̬����򸸴��ڷ��ʹ��¼�
 (���͵�YWGUI_MSG_COMMAND��)
 ****************************************************/
#define YWGUI_EN_CONTCHANGE       0x0209
/****************************************************
 �����������ߵ�ʱ���ڰ�������������Ϣ
 (���͵�YWGUI_MSG_COMMAND��)
 ****************************************************/
#define YWGUI_EN_HOME_LEFT        0x020a
/****************************************************
 ����������ұߵ�ʱ�����Ұ������������Ϣ
 (���͵�YWGUI_MSG_COMMAND��)
 ****************************************************/
#define YWGUI_EN_END_RIGHT        0x020b

/*****************************container�ؼ�֪ͨ��*******************************/
//�������Ұ���
#define YWGUI_CTN_UPKEY           0x020c
#define YWGUI_CTN_DOWNKEY         0x020d
#define YWGUI_CTN_LEFTKEY         0x020e
#define YWGUI_CTN_RIGHTKEY        0x020f

//add by Eagle 2009-05-06
//ListTable Notify
/*****************************ListTable�ؼ�֪ͨ��**********************************/
/**************************************
 YWGUI_LTN_NEEDDATA
 ��  ��: ֪ͨӦ����Ҫ��ȡ����(��ҳΪ��λ)
 lParam: ��16λ -- ��Ҫ��ȡ���ݵ���ʼ����
         ��16λ -- ��Ҫ��ȡ���ݵĽ�������(������������)
 ˵  ��: Ӧ�ø��������ŵ��� YWGUI_LTSetItemInfo
         �������ˢ��
 **************************************/
#define YWGUI_LTN_NEEDDATA      0x250


/**************************************
 YWGUI_LTN_CURCHANGE
 ��  ��: ֪ͨӦ�õ�ǰ�����иı�
 lParam: ��ǰ����������
 ˵  ��:
 **************************************/
#define YWGUI_LTN_CURCHANGE     0x251


/**************************************
 YWGUI_LTN_MARKCHANGE
 ��  ��: ֪ͨӦ�� Check ״̬�ı�
 lParam: ״̬�ı��е�����
 ˵  ��:
 **************************************/
#define YWGUI_LTN_MARKCHANGE    0x252


/* ��������ؼ���ѯ�ؼ�����Ҫ�İ��� */

/**************************************
 YWGUI_CTRLCODE_WANTUD
 ��  ��: �ؼ������������Լ���Ҫ���¼�
 ˵  ��: ��������ؼ�����YWGUI_MSG_GETCTRLCODE��Ϣ��ȡ�ؼ�����Ҫ�İ���
 **************************************/
#define YWGUI_CTRLCODE_WANTUD     0x0001
/**************************************
 YWGUI_CTRLCODE_WANTLR
 ��  ��: �ؼ������������Լ���Ҫ���Ҽ�
 ˵  ��: ��������ؼ�����YWGUI_MSG_GETCTRLCODE��Ϣ��ȡ�ؼ�����Ҫ�İ���
 **************************************/
#define YWGUI_CTRLCODE_WANTLR    0x0002
/**************************************
 YWGUI_CTRLCODE_WANTALLKEYS
 ��  ��: �ؼ������������Լ���Ҫ���а���
 ˵  ��: ��������ؼ�����YWGUI_MSG_GETCTRLCODE��Ϣ��ȡ�ؼ�����Ҫ�İ���
 **************************************/
#define YWGUI_CTRLCODE_WANTALLKEYS    0x0004
/**************************************
 YWGUI_CTRLCODE_WANTOK
 ��  ��: �ؼ������������Լ���Ҫȷ��(OK)��
 ˵  ��: ��������ؼ�����YWGUI_MSG_GETCTRLCODE��Ϣ��ȡ�ؼ�����Ҫ�İ���
 **************************************/
#define YWGUI_CTRLCODE_WANTOK      0x0008

/*******************************************************************************
***********************************�ṹ�嶨��*************************************
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

    //YWMID_Dibitmap_T: �豸�޹�λͼ�ṹ
    typedef struct YWMID_Dibitmap_s
    {
        U32  Flags;

        /**ɫ��:1/4/8/16/24/32 */
        U8 Depth;

        /** The global alpha value. */
        U8 Alpha;

        //U8 Reserved[2];

        /** Flags & YWMID_DIBMP_COLOR_KEY : ColorKey��Ч;
        �������ɫ����ֵ�������ɫ�������;*/
        U8 ColorKey[4];

        /** The width of the bitmap. */
        U32 W;

        /** The height of the bitmap. */
        U32 H;

        //ÿ��ʹ�õ��ֽ���
        U32 Pitch;

        /*nPaletteColors: ��ɫ��������ɫ��*/
        U32 PaletteColors;

        //ָ����ɫ��
        YWMID_Palette_T* pPalette;

        /*Bytes ���ֽ�����ʾ��λͼ���ݵĴ�С*/
        U32 Bytes;

        //ָ��λͼ����ʹ��ʱ����ÿ�����ֽ����������������ͣ�
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

    /*����һ��ƴ��ͼƬ��˵����һ��������ߣ�
    leftOffset��topOffset������ڻ�����ߵ�ƫ��,
    ��������ǿ��һ��ͼƬҪ����ͬ�ĸ߶�(����ƴ��)��ȶ�(����ƴ��)

    (rightGraphCell-leftOffset)/(bottomGraphCell-topOffset)����GraphCell�Ĵ�С��
    ��ʵ��ͼƬС�ڸô�С����ѭ������ͼƬ����������
    ��ʵ��ͼƬ���ڸô�С��ͼƬ���ᱻ�ü�����Ӧ��.
    */

    U32 leftOffset;
    U32 topOffset;
    U32 rightGraphCell;
    U32 bottomGraphCell;
    void* ptBmp;//ָ���豸�޹ػ��豸���λͼ�ṹ
}YWGUI_GraphCell_T;
#else
typedef struct YWGUI_GraphCell_s
{
  /*����һ��ƴ��ͼƬ��˵����һ��������ߣ�
    DstRect.X��DstRect.Y������ڻ�����ߵ�ƫ��,
    (DstRect.W)/(DstRect.H)����GraphCell�Ĵ�С��
    ��DstRect.W��DstRect.HΪ0,����ΪGraphCell��С��Ч����ͼƬ��ߴ���,ֻ��ָ��λ�����һ��ͼƬ
    ��DstRect.W��DstRect.H����ͼƬ���,���ƽ�̣����л�����
    ��DstRect.W��DstRect.HС��ͼƬ���,�����С�⣬�������������ü�
    */
    YWMID_DibitmapOp_T Op;          /*�����ݵĲ���*/
    void* ptBmp;/*ע��:�ýṹ��GUI�ⲿʹ��ʱָ��(YWMID_BitmapData_T *)����,
                         ��GUI�ڲ�ʹ��ʱָ��(YWGUI_BitmapData_T*) ����*/
} YWGUI_GraphCell_T;
#endif
/*end of modify*/

typedef YWGUI_GraphCell_T* YWGUI_GraphCell_P;

typedef struct YWGUI_GraphCollect_s
{
    YWGUI_SpellType_E       eSpellType;
    S32                     nGraph;           //ͼƬ��
    YWGUI_GraphCell_T **    pptGraphArray;     //ָ��YWGUI_GraphCell_T*ָ������

    //nLoadCnt�ڲ�ʹ��
    U32                     nLoadCnt;         //0--�豸�޹�ͼ����ÿװ��һ��(װ�س��豸���λͼ)��������1
}YWGUI_GraphCollect_T;

typedef struct YWGUI_ShapeFrame_s
{
    YWGUI_FrameType_E eFrameType;

    //ptFrameGraph��ΪNULL,�ʶ���Ϊָ��
    YWGUI_GraphCollect_T *  ptFrameGraph;//�߿�ͼ��


    /*leftOffsetFrame--bottomOffsetFrame�Ǳ߿�����ڴ��������ߵ�ƫ��,
      leftOffsetClient --bottomOffsetClient�ǿͻ�������ڱ߿������ߵ�ƫ��,
      �ɴ��ھ��ο�����߿����,������ͻ������Σ�
      �Ӷ���֧�ֵ��ͻ������洰�ھ�������

      �޸ļ�¼:
      leftOffsetFrame--bottomOffsetFrame�ĸ���Ա��Ч,
      Ϊ��Ӧ�ó���ļ���,�Ա����ڴ�
      leftOffsetClient --bottomOffsetClient��ɿͻ�������ڴ��������ߵ�ƫ��
    */
    #if 1
    U32 leftOffsetFrame;
    U32 topOffsetFrame;
    U32 rightOffsetFrame;
    U32 bottomOffsetFrame;
    #endif

    /*leftOffsetClient --bottomOffsetClient ��Ա�Ƿ���Ч���£�
        FRAME_NO / FRAME_RECT ����Ч
        FRAME_GRAPH :��Ч
    */
    U32 leftOffsetClient;
    U32 topOffsetClient;
    U32 rightOffsetClient;
    U32 bottomOffsetClient;

}YWGUI_ShapeFrame_T;

typedef struct YWGUI_ShapeState_s
{

    YWGUI_ShapeFrame_T*    ptShapeFrame;

    //ptBackGraph��ΪNULL���ʶ���Ϊָ��
    YWGUI_GraphCollect_T *  ptBackGraph; //����ͼ��

    //ptForeGraph��ΪNULL���ʶ���Ϊָ��
    YWGUI_GraphCollect_T * ptForeGraph;//ǰ��ͼ��

    //ptShapeColor��ΪNULL,�ʶ���Ϊָ��
    YWGUI_ShapeColor_T* ptShapeColor;

}YWGUI_ShapeState_T;

typedef struct YWGUI_ShapeInfo_s
{
    YWGUI_ShapeState_T* ptShape[YWGUI_WES_STATUS_NUM];//ָ������
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

//ע��ؼ���ʹ��
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
    YWGUI_HWnd_T  hHosting;//�������ھ��
    YWGUI_WindowProc_P  pfnMainWindowProc;
    S32 left;
    S32 top;
    S32 width;
    S32 height;//��Ļ����
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

    void*                pAdd; //ͬ����Ϣʹ��
} YWGUI_Msg_T;
typedef YWGUI_Msg_T* YWGUI_Msg_P;


typedef struct YWGUI_LayerParams_s
{
    YWGUI_PixelType_E       ePixelType; //��������

    S32                     left;
    S32                     top;
    U32                     width;
    U32                     height;

    YWGUI_Pixel_T           colorKey;
    YWGUI_Pixel_T           DeskTopColor;
    U8           transparence;/*0~0xFF, 0:͸��,0xFF:��͸��*/

    U8                      bitsPerPixel; //ÿ����ռ�����ڴ�(��λ:bit)
    //U8                      alphaBlendingMode;


    BOOL                    bIsHideDesktop;//�Ƿ���������(��Ҫ��������ʱ��transparence ������Ч)
    BOOL                    bHaveColorKey; //colorKey ��Ч
    BOOL                    bHaveTransparence; //transparence ��Ч
    /*added by sly, 2009-8-17*/
    U32                        uAssociateLayerNum;
    U32*                      puAssociateLayerIndex;
    /*end of added*/
    //BOOL                    bHighDefinition;//�Ƿ񿪳ɸ���ͼ��//delete by sly
}YWGUI_LayerParams_T;


typedef struct YWGUI_KeyItem_s
{
    U16            dataCode;        /*������*/
    U16            scanCode;       /* �߼���*/
    BOOL        bRepeat;    /*�Ƿ��ظ���*/
}YWGUI_KeyItem_T;

typedef struct YWGUI_KeyboardParams_s
{
    YWGUI_RemoteProtocol_E eRemoteProtocol;
    U16                    customCode;      /*�ͻ���*/
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
    U16         DataCode;                                   /* ʵ��ֵ*/
    U16         Reserve;                                    /* ����*/
    U32         LogicValue;                                 /* �߼��루logic value�� */
}YWGUI_LbdItem_T;
typedef struct YWGUI_LbdParams_s
{
    U32                          uLbdNumber;                 /*  lbd�� */
    YWGUI_LbdItem_T  *LbdTable;           /*  ע��� */
}YWGUI_LbdParams_T;
/*end of added*/
/*
������Ⱦ����ַ�
    ��һλ
        'r' --�������⴦��
        'b' --�Ӵ���ʾ
        'k' --���õ�ͨ�˲��㷨�������ͱ�Ե
        'd' --�Ӵ�+��ͨ�˲�

    �ڶ�λ
        'r' --�������⴦��
        'i' --б��

    ����λ
        'n' --�������⴦��
        'h' --ˮƽ��ת
        'v' --��ֱ��ת
        't'  --ˮƽ+��ֱ��ת

    ����λ
        'c' --��������
        's' --����������С�Զ�����(�����ڵ�������)

    ����λ
        'n' --���»���
        'u' --���»���

    ����λ
        'n' --��ɾ����
        's' --��ɾ����
*/
typedef struct YWGUI_FontInfo_s
{
    const S8* pcFontAttr;/*��������:type-family-style-width-height-charset ��"ttf-arial-rrncnn-10-10-UCS-2"*/
    const S8* pcFontFile; /*�����ļ�·��*/
} YWGUI_FontInfo_T;

typedef struct YWGUI_CtrlOffsetInfo_s
{
    const S8* CtrlName;

    U32 XOffset;
    U32 YOffset;
}YWGUI_CtrlOffsetInfo_T;

typedef  YWGUI_CtrlOffsetInfo_T* YWGUI_CtrlOffsetInfo_P;

//YWGUI_Start����Ĳ����ṹ
typedef struct YWGUI_ImportParams_s
{
    YWGUI_LayerParams_T*             ptLayerParam;
    U8                                                  uRemoteNum;    /*��Ҫ֧�ֶ��ٸ�ң����*/
    //YWGUI_KeyboardParams_T*          ptKeyboardParam;
    YWGUI_KeyboardParams_T*          ptRemoteParamHead; /*ָ��remote������ͷָ��*/

    YWGUI_FrontPanelParams_T*          ptFrontPanelParam;
    YWGUI_LbdParams_T*                  ptLbdParam;
    //�������ݳ�ʼ���Ի���ģ������Ļص�����
    YWGUI_InitDlgTLinkFunc_P        pfnInitDlgTLink;

    //��������װ���ַ�����Դ�Ļص�����
    YWGUI_LoadStringFunc_P          pfnLoadString;

    //���������޸�ϵͳĬ�ϻ�ͼ����(��ɫ���ز�)�Ļص�����
    YWGUI_ModifyDefScheFunc_P       pfnModifyDefScheme;

    //���������޸Ŀؼ�Ĭ�ϻ�ͼ���ԵĻص�����
    YWGUI_ModifyCtrlDefScheFunc_P   pfnModifyCtrlDefSche;

    YWGUI_KeyPreProcess_P   pfKeyPreProcess;
    U8 uFontNum;/*�������*/
    YWGUI_FontInfo_T * pstFontInfo;/*������Ϣ*/
    U8 uLogFontNum;   /*��Ҫ�������߼�����ĸ���*/
    S8 ** ppcLogFontName;/*��Ҫ�������߼����������б�*/

    U32 uOffsetInfoNum;
    YWGUI_CtrlOffsetInfo_P pOffsetInfo;
}YWGUI_ImportParams_T;


typedef struct YWGUI_ImeMap_s
{
    S32             reuseCnt;
    YWGUI_Char_T *  pszFact;
}YWGUI_ImeMap_T;

typedef YWGUI_ImeMap_T YWGUI_ImeMapTable_T[10];





//============================ListView�ؼ��Ľṹ����==================

#define YWGUI_LISTITEM_STATUS_NUM                6

#define  YWGUI_LISTITEM_STATUS_NORMAL            0
#define  YWGUI_LISTITEM_STATUS_DISABLE           1
#define  YWGUI_LISTITEM_STATUS_AFOCUS            2
#define  YWGUI_LISTITEM_STATUS_SFOCUS            3
#define  YWGUI_LISTITEM_STATUS_CHECKED           4
#define  YWGUI_LISTITEM_STATUS_SKIP              5

//һ�����������
#define YWGUI_LV_TEXTSUB        0            //�ı�
#define YWGUI_LV_IMAGESUB       1            //ͼƬ

//�е�״̬
#define YWGUI_LVIF_NORMAL             0x0000L
#define YWGUI_LVIF_CHECKED            0x0001L     //ѡ��
#define YWGUI_LVIF_SKIP               0x0002L     //����

enum
{
    YWGUI_LVSORT_NOTSORT,
    YWGUI_LVSORT_ASC,
    YWGUI_LVSORT_DESC
};

typedef struct YWGUI_ListItemShapeCollect_s
{
    YWGUI_ShapeState_T* ptShape[YWGUI_LISTITEM_STATUS_NUM];//ָ������
}YWGUI_ListItemShapeInfo_T;

//�б����ṹ
typedef struct YWGUI_LVItem_BG_s
{
    S32 iStartCol;                          // ���б�����ʼ������
    S32 iEndCol;                            // ���б�������������

    YWGUI_ListItemShapeInfo_T* pShapeItemBg;  // �нṹָ��
}YWGUI_LVItem_BG_T;
typedef YWGUI_LVItem_BG_T* YWGUI_LVItem_BG_P;


typedef struct YWGUI_PosbarDef_s
{
    S32 iThumbSize;                         // Posbar��Thumb Size,Thumb sizeΪ�̶�size��ʱ��
                                            // ����Ч���������Size��Ч

    YWGUI_ShapeInfo_T* pPosbarShape;        // ����������

    S32 Size;                               //��Ϊˮƽ������ʱ��Ϊ�������ĸ߶ȣ���ֱ��ʱ��Ϊ�������Ŀ��
                                            //С��0ʹ�ÿؼ�Ĭ�Ϲ������߶Ȼ���
}YWGUI_PosbarDef_T;
typedef YWGUI_PosbarDef_T* YWGUI_PosbarDef_P;

typedef struct YWGUI_LVAddData_s
{
    YWGUI_LVItem_BG_P pLVItemBg;            // �б���

    //YWGUI_ShapeInfo_T* pScrollShape;        // ����������
    YWGUI_PosbarDef_T* pPosbarDef;          // Listview��Posbar��Ĭ�Ͻṹ

}YWGUI_LVAddData_T;
typedef YWGUI_LVAddData_T* YWGUI_LVAddData_P;

typedef struct YWGUI_LVColumn_S
{
    S32            nCol;    // �����е�λ��
    S32            width;        // �п�
    YWGUI_Char_T   *pszHeadText; // �еı���
    //S32            nTextMax;   // �б������󳤶�
    DWORD          image;        // �б�ͷ��ͼ��ָ��
                                 // ΪYWGUI_ShapeUnit_T����ָ��,��Ϊ������Ϊ��ɫ��Ҳ��Ϊ���ͼƬ
    DWORD          colFlags;   // �б�־���ֻ�ͼƬ

} YWGUI_LVColumn_T;
typedef YWGUI_LVColumn_T *YWGUI_LVColumn_P;


typedef struct YWGUI_LVSubItem_s
{
    //DWORD           flags;      // ����ı�־ //LVFLAG_BITMAP or LVFLAG_ICON
    S32             nCol;       // ����Ĵ�ֱ����ֵ
    S32             nRow;       // �����ˮƽ����ֵ

    YWGUI_Char_T    *pszText;   // �������������
    DWORD           image;      // �����ͼƬ //ΪYWGUI_ListItemShapeInfo_T����ָ��

} YWGUI_LVSubItem_T;
typedef YWGUI_LVSubItem_T *YWGUI_LVSubItem_P;



//===================================Listbox�ṹ����=========================================
//��״̬
#define YWGUI_LBIF_NORMAL           0x0000L
#define YWGUI_LBIF_CHECKED         0x0001L    //ѡ��
#define YWGUI_LBIF_SKIP             0x0002L    //����

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
    YWGUI_ListItemShapeInfo_T* pLBItemBgShape;            // �б���

    //YWGUI_ShapeInfo_T* pScrollShape;                    // ����������
    YWGUI_PosbarDef_T* pPosbarDef;                        // Listbox��Posbar��Ĭ�Ͻṹ

}YWGUI_LBAddData_T;
typedef YWGUI_LBAddData_T* YWGUI_LBAddData_P;

//===================================LRCombobox�ṹ����=======================================
//��״̬
#define YWGUI_CBIF_NORMAL           0x0000L
#define YWGUI_CBIF_CHECKED          0x0001L    //ѡ��
#define YWGUI_CBIF_SKIP             0x0002L    //����

typedef enum YWGUI_LRCBTextWesItem_e
{
    //������۷���
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
    YWGUI_ShapeState_T* ptShape[YWGUI_LRCB_TEXT_WES_STATUS_NUM];//ָ������
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
    YWGUI_ListItemShapeInfo_T* pListItemBgShape;            // �б���
    YWGUI_PosbarDef_T* pPosbarDef;                          // Listbox��Posbar��Ĭ�Ͻṹ

}YWGUI_LRCBListAddData_T;
typedef YWGUI_LRCBListAddData_T* YWGUI_LRCBListAddData_P;

typedef struct YWGUI_LRCombobox_AddData_s
{
    YWGUI_LRCBTextShapeInfo_T* pTextShape;
    //List��Ϣ
    S32 Offsetx;//list�����LRCombobox�ؼ���xƫ�ƣ�����Ϊ����
    S32 Offsety;//list�����LRCombobox�ؼ���yƫ�ƣ�����Ϊ����
    S32 w;//List�Ŀ�
    S32 h;//List�ĸ�
    YWGUI_ShapeInfo_T* pListShape;
    YWGUI_LRCBListAddData_T* pListAddData;
}YWGUI_LRCombobox_AddData_T;
typedef YWGUI_LRCombobox_AddData_T* YWGUI_LRCombobox_AddData_P;

//add by Eagle 2009-05-06
//ListTable Structure
//===================================ListTable�ṹ����========================================
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
    //������۷���

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
    YWGUI_ShapeState_T* ptShape[YWGUI_CONTAINER_WES_STATUS_NUM];//ָ������
}YWGUI_ContainerShapeInfo_T;


typedef struct  YWGUI_ContainerCtrlTemplate_s
{
    /** Class name of the control */
    const S8* class_name;

    /** Control style */
    DWORD       dwStyle;

    /** Control extended style */
    DWORD       dwExStyle;

    //����������ؼ���ƫ��
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
***********************************�꺯������*************************************
*******************************************************************************/

#define YWGUI_GetErrorCode(code)   (((code) ==YW_NO_ERROR )?YW_NO_ERROR: ((code) - YW_MODULE_SET_ID (YWMID_MODULE_GUI_ID )+1))

#define YWGUI_LOWORD(l)             ((U16)((U32)(l)))
#define YWGUI_HIWORD(l)             ((U16)((((U32)(l)) >> 16) & 0xFFFF))
#define YWGUI_MAKEDWORD(low,high)   ((DWORD)(((U16)(low)) | (((DWORD)((U16)(high))) << 16)))

#define YWGUI_ARRAY_SIZE(a)         (sizeof((a))/sizeof((a)[0])) //��������Ԫ�ظ���

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

/*ǰ����������ͷ�װ*/
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
    YWGUI_PANEL_VFD_IO_TIME_SECOND, /*ʱ���֮��ĵ�*/
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

    YWGUI_PANEL_VFD_SET_DISPLAYMODE, /*������ʾģʽ*/
    YWGUI_PANEL_VFD_SET_OPERATION_MODE, /*���ò���ģʽ*/
    YWGUI_PANEL_VFD_SET_DISPLAYCONTROL, /*������ʾ����*/

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
    YWGUI_PANEL_LBD_TYPE_POWER          =  ( 1 << 0 ),         /*  ǰ���Power�� */
    YWGUI_PANEL_LBD_TYPE_SIGNAL         =  ( 1 << 1 ),         /*  ǰ��� Signal�� */
    YWGUI_PANEL_LBD_TYPE_MAIL           =  ( 1 << 2 ),         /*  ǰ���Mail�� */
    YWGUI_PANEL_LBD_TYPE_AUDIO          =  ( 1 << 3 )          /*  ǰ���Audio�� */
}YWGUI_PanelLBDType_T;

/*Front Panel LBD Status*/
typedef enum YWGUI_PanelLBDStatus_e
{
    YWGUI_PANEL_LBD_STATUS_OFF,           /*  LBD���� */
    YWGUI_PANEL_LBD_STATUS_ON,            /*  LBD����     */
    //YWGUI_PANEL_LBD_STATUS_FL             /*  LBD����˸ */
}YWGUI_PanelLBDStatus_T;

/***********************ǰ������ͷ�װend*************************/

/*******************************************************************************
***********************************�ӿں�������*************************************
*******************************************************************************/

//�ڶ�����غ꺯��ʱ���õ��ĺ�������
//(Ӧ�ò�ֱ�ӵ�����Щ����������ʹ�ð�װ��ĺ꺯��)
YWGUI_API U32  YWGUI_SetDCAttr (YWGUI_HDc_T hdc, YWGUI_DcAttr_E attr, U32 value);
YWGUI_API U32  YWGUI_GetDCAttr (YWGUI_HDc_T hdc, YWGUI_DcAttr_E attr);


/**********************************init����*********************************/

/***********************************************************************
��������: YWGUI_Init
��������: ywgui ��ʼ��
��    ��: ��
�� �� ֵ: YW_NO_ERROR -- ��ʼ���ɹ�;YWGUI_ERROR -- ��ʼ��ʧ��
˵    ��: 1)��Ӧ������ YWGUI_Term
�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_Init(void);

/***********************************************************************
��������: YWGUI_Term
��������:
��    ��: ��
�� �� ֵ: YW_NO_ERROR
˵    ��: 1) ��Ӧ������ YWGUI_Init
�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_Term(void);


/***********************************************************************
��������: YWGUI_Start
��������: ����GUI
��    ��: ptCustomParam[in] -- APP�������
�� �� ֵ: YW_NO_ERROR -- OK;YWGUI_ERROR -- Failure
˵    ��: 1) ��Ӧ������ YWGUI_Stop
�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_Start(YWGUI_ImportParams_T* ptImportParam);

/***********************************************************************
��������: YWGUI_Stop
��������: ֹͣGUI
��    ��: ��
�� �� ֵ: YW_NO_ERROR
˵    ��: 1) ��Ӧ������ YWGUI_Start
�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_Stop(void);


YWGUI_API YW_ErrorType_T YWGUI_GetOsdLayer(YWGUI_Handle_T*pHandle);

/***********************************************************************
��������: YWGUI_SetOsdLayerAlpha
��������: ����OSD layer Alphaֵ
��    ��: pHandle[in]   --
          alphaVal[in]  -- ��Χ(0-255)
                        0 --    ȫ͸��
                        255 --  ȫ��ʾ
�� �� ֵ: YW_NO_ERROR -- OK;
          ���� -- Failure
˵    ��:
�޸ļ�¼:
************************************************************************/
//YWGUI_API YW_ErrorType_T YWGUI_SetOsdLayerAlpha(YWGUI_Handle_T pHandle,U32 alphaVal);

/***********************************************************************
��������: YWGUI_SetIORect
��������: ���������������,���OSD�������
��    ��: prcIn [in] -- �������(���OSD����������)
          prcOut[in] -- �������(�����Ļ������)
�� �� ֵ: YW_NO_ERROR -- OK;
          ���� -- Failure
˵    ��:
�޸ļ�¼:
************************************************************************/
//YWGUI_API YW_ErrorType_T YWGUI_SetIORect(const YWGUI_Rect_T*prcIn, const YWGUI_Rect_T *prcOut);


/**********************************����ywgui�ĺ���***************************/

/***********************************************************************
��������: YWGUI_AddTempletNode
��������: ����Ի���ģ����Դ���Ի���ģ����
��    ��: ptTemplate -- �Ի���ģ��ṹ
�� �� ֵ: YW_NO_ERROR
˵    ��: 1) �ú��������ڳ�ʼ���Ի���ģ������Ļص������е���(�� YWGUI_CustomParams_T::pfnInitDlgTLink)
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_AddTempletNode(const YWGUI_DlgTemplate_T *ptTemplate);


/***********************************************************************
��������: YWGUI_SetDefaultColor
��������: �޸�ϵͳĬ�ϵ���ɫ����
��    ��: item -- ��ɫ������
          pixel -- ��ɫֵ
�� �� ֵ: ��ɫ�������ϵ���ɫֵ
˵    ��: 1) �ú��������ڶ���gui�Ļص������е���(�� YWGUI_CustomParams_T::pfnModifyDefScheme)
************************************************************************/
YWGUI_API   void YWGUI_SetDefaultColor (YWGUI_WecItem_E item, YWGUI_Pixel_T pixel, YWGUI_Pixel_T oldPixel);


/***********************************************************************
��������: YWGUI_SetDefaultMetrics
��������: �޸�ϵͳĬ�ϵ��زķ���
��    ��: item -- �زķ�����
          size -- ֵ
�� �� ֵ: �زķ������ϵ�ֵ
˵    ��: 1) �ú��������ڶ���gui�Ļص������е���(�� YWGUI_CustomParams_T::pfnModifyDefScheme)
�޸ļ�¼:
************************************************************************/
YWGUI_API S32   YWGUI_SetDefaultMetrics(YWGUI_WemItem_E item, S32 size);


/***********************************************************************
��������: YWGUI_SetCtrlDefColor
��������: �޸Ŀؼ�Ĭ�ϵ���ɫ����
��    ��: szClassName [in]--�ؼ�����
          item [in] -- ��ɫ������
          pixel [in]-- ��ɫֵ
�� �� ֵ: �ؼ�����ɫ�������ϵ�ֵ
˵    ��: 1) �ú��������ڶ���gui�Ļص������е���(�� YWGUI_CustomParams_T::pfnModifyCtrlDefSche)
************************************************************************/
YWGUI_API void  YWGUI_SetCtrlDefColor (const S8* szClassName,YWGUI_WecItem_E item, YWGUI_Pixel_T new_value, YWGUI_Pixel_T oldValue);

/***********************************************************************
��������: YWGUI_SetCtrlDefShapeState
��������: �޸Ŀؼ���Ĭ�ϵ���ۼ���ɫ����
��    ��: szClassName [in]--�ؼ�����
          item[in] --��۷�����(��״̬)
          ptShapeState[in] --ĳ״̬��Ӧ����۽ṹ,
                            ���ΪNULL,���Ѹ�״̬����۽ṹ��NULL
�� �� ֵ:  YW_NO_ERROR-- ���óɹ�; ����--����ʧ��
˵    ��: 1) �ú��������ڶ���gui�Ļص������е���(�� YWGUI_CustomParams_T::pfnModifyCtrlDefSche)
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_SetCtrlDefShapeState(const S8* szClassName,YWGUI_WesItem_E item, YWGUI_ShapeState_T* ptShapeState);

/***********************************************************************
��������: YWGUI_SetCtrlTextExtra
��������: ���ÿؼ��ַ����������ϼ�࣬�¼�࣬�ַ����
��    ��: hCtrl [in] -- �ؼ��ľ��
                extra [in] --�ĸ�extra����
                value [in] -- extra ֵ
�� �� ֵ: YW_NO_ERROR
˵    ��: indent �� YWGUI_SS_ROLLDISP  ��� ����Ч
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetCtrlTextExtra(YWGUI_HWnd_T hCtrl, YWGUI_CtrlTextExtra_E extra, S16 value);

/***********************************************************************
��������: YWGUI_SetCtrlTextFormat
��������: ���ÿؼ��ַ�format
��    ��: hCtrl [in] -- �ؼ��ľ��
                format [in]
�� �� ֵ: YW_NO_ERROR
˵    ��: 
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetCtrlTextFormat(YWGUI_HWnd_T hCtrl, DWORD format);

/**********************************window����***************************************/

//����������
YWGUI_API YW_ErrorType_T YWGUI_CreateMainWindow (YWGUI_MainWinCreate_T* pCreateInfo, YWGUI_HWnd_T* phWnd);


//����������
YWGUI_API YW_ErrorType_T YWGUI_DestroyMainWindow(YWGUI_HWnd_T hWnd);

//Ĭ�ϵĿؼ����̺���
YWGUI_API S32  YWGUI_DefaultControlProc (YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam, LPARAM lParam);

//Ĭ�ϵ������ڹ��̺���
YWGUI_API S32 YWGUI_DefaultMainWinProc (YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam, LPARAM lParam);

/***********************************************************************
��������: YWGUI_SetWinProc
��������: ���ô���(�����ڣ��ؼ�)���̺���
��    ��: hWnd[in] -- ���ھ��
          pfNewProc[in] -- �µĴ��ڹ��̺���

�� �� ֵ: �ϵĴ��ڹ��̺���,���ע��ʧ�ܷ���NULL
˵    ��:
�޸ļ�¼:
************************************************************************/
YWGUI_API YWGUI_WindowProc_P YWGUI_SetWinProc (YWGUI_HWnd_T hWnd, YWGUI_WindowProc_P pfNewProc);

/***********************************************************************
��������: YWGUI_GetWinProc
��������: ��ȡ����(�����ڣ��ؼ�)���̺���
��    ��: hWnd[in] -- ���ھ��
�� �� ֵ: ��ǰ���ڹ��̺���,�����ȡʧ�ܷ���NULL
˵    ��:
�޸ļ�¼:
************************************************************************/
YWGUI_API  YWGUI_WindowProc_P YWGUI_GetWinProc (YWGUI_HWnd_T hWnd);

//��ʾ����(������/�Ӵ���)
YWGUI_API YW_ErrorType_T  YWGUI_ShowWindow (YWGUI_HWnd_T hWnd, S32 iCmdShow);

/***********************************************************************
��������: YWGUI_UpdateShapeState
��������: ���ô���(������/�Ӵ���)ĳ״̬�µ���۷�������ɫֵ,
          ����޸ĵ��ǵ�ǰ״̬����۷����������¼���ͻ���,����Ч��������
��    ��:   hWnd[in] -- ���ھ��
            item[in] --��۷�����(��״̬)
            ptShapeState[in] --ĳ״̬��Ӧ����۽ṹ
�� �� ֵ:  YW_NO_ERROR-- ���óɹ�; ����--����ʧ��
˵    ��:   1)�ú���ֻ����ָ����������������Ϣ�����߳��е���


�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T   YWGUI_UpdateShapeState(YWGUI_HWnd_T hWnd, YWGUI_WesItem_E item, YWGUI_ShapeState_T* ptShapeState);


/***********************************************************************
��������: YWGUI_UpdateWindow
��������: �����ػ洰��(�����ͻ����ͷǿͻ���)
��    ��:   hWnd[in] -- ���ھ��
�� �� ֵ:  ��
˵    ��:  1)�ú���ֻ���ڸô�������������Ϣ�����߳��е���

�޸ļ�¼:
************************************************************************/
YWGUI_API void  YWGUI_UpdateWindow (YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_MoveWindow
��������: �ƶ�����(������/�Ӵ���)
��    ��:   hWnd[in] -- ���ھ��
            x[in] --����ڸ����ڿͻ�����x����(������������Ļ����)
            y[in] --����ڸ����ڿͻ�����y����(������������Ļ����)
            w[in] --���
            h[in] -- �߶�
            bPaint[in] --
            ptShapeInfo[in] -- �ƶ����ں�ԭ������۽ṹ���ܲ���Ӧ����Ҫ�ش���۽ṹ
                                ���ptShapeInfoΪNULL,���ı�ԭ������۽ṹ;
                                ���ptshapeInfo�ṹ�ڲ�ĳ״̬�����ΪNULL�����ı��״̬����۽ṹ
�� �� ֵ:
˵    ��:   1)�ú���ֻ���ڸô�������������Ϣ�����߳��е���
            2)���ptShapeInfoΪNULL���Ҵ���λ��δ�ı䣬û���ƶ�Ч��
�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_MoveWindow (YWGUI_HWnd_T hWnd, S32 x, S32 y, S32 w, S32 h, BOOL bPaint,YWGUI_ShapeInfo_T *ptShapeInfo);

//ʹ�ܻ�disabled ����
YWGUI_API BOOL  YWGUI_EnableWindow (YWGUI_HWnd_T hWnd, BOOL bEnable);

/***********************************************************************
��������: YWGUI_InvalidateRect
��������: ��Ч�ͻ�������
��    ��:   hWnd[in] -- ���ھ��
            pRect[in] -- ����ڱ����ڿͻ��������꣬��ΪNULL,����Ч�����ͻ���
            bEraseBkgnd[in] -- �Ƿ��������
�� �� ֵ:
˵    ��:

�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_InvalidateRect (YWGUI_HWnd_T hWnd, const YWGUI_Rect_T* pRect, BOOL bEraseBkgnd);

/***********************************************************************
��������: YWGUI_Invalidate
��������: ��Ч��������(�������ڿ�����Ϳͻ���)
��    ��:   hWnd[in] -- ���ھ��
            bEraseBkgnd[in] -- �Ƿ��������
�� �� ֵ:
˵    ��:

�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_Invalidate (YWGUI_HWnd_T hWnd, BOOL bEraseBkgnd);

/***********************************************************************
��������: YWGUI_IsModeDialog
��������: �ж��������Ƿ�ģ̬�Ի���
��    ��:   hWnd[in] -- ���������ھ��
�� �� ֵ:   TRUE -- ģ̬�Ի���; FALSE -- ��ģ̬�Ի���
˵    ��:

�޸ļ�¼:
************************************************************************/
YWGUI_API BOOL  YWGUI_IsModeDialog (YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_GetActiveMainHWnd
��������: �õ���ǰ���������
��    ��:   ��
�� �� ֵ:   ���ص�ǰ��������ھ��
˵    ��:

�޸ļ�¼:
************************************************************************/
YWGUI_API YWGUI_HWnd_T YWGUI_GetActiveMainHWnd(void);




/***********************************************************************
��������: YWGUI_IsWindowVisible
��������: �õ������Ƿ�ɼ�
��    ��:   hWnd[in] -- ���ھ��
�� �� ֵ:   TRUE -- �ɼ�
            FALSE -- ���ɼ�
˵    ��:  ֻҪ�����ȴ�����һ�����ɼ�����Ϊ���ɼ�
************************************************************************/
YWGUI_API BOOL  YWGUI_IsWindowVisible (YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_IsWindowEnabled
��������: �õ������Ƿ�ʹ��״̬
��    ��:   hWnd[in] -- ���ھ��
�� �� ֵ:   TRUE -- enable
            FALSE -- disable
˵    ��:  1)ֻҪ�����ȴ�����һ��disabled����Ϊdisabled
�޸ļ�¼:
************************************************************************/
YWGUI_API BOOL  YWGUI_IsWindowEnabled (YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_GetWindowCurrentStatus
��������: �õ����ڵ�ǰ��״̬
��    ��:   hWnd[in] -- ���ھ��
�� �� ֵ:   YWGUI_STATUS_NORMAL(=0) -- ���ڵ�ǰ�Ƿǽ���״̬
            YWGUI_STATUS_DISABLED(=1) -- disable״̬
            YWGUI_STATUS_AFOCUS(=2) -- ���ڵ�ǰӵ�л����
            YWGUI_STATUS_SFOCUS(=3) -- ���ڵ�ǰӵ��ʧ��Ľ���
            -1 -- ����������״̬(�򴰿ھ����Ч)
˵    ��:  ������״̬��:YWGUI_STATUS_NORMAL/YWGUI_STATUS_DISABLED/YWGUI_STATUS_AFOCUS/-1
           �ؼ�����״̬��:YWGUI_STATUS_NORMAL/YWGUI_STATUS_DISABLED/YWGUI_STATUS_AFOCUS/YWGUI_STATUS_SFOCUS/-1
************************************************************************/
YWGUI_API S32 YWGUI_GetWindowCurrentStatus(YWGUI_HWnd_T hWnd);


//����������ID�õ������ھ��
YWGUI_API YWGUI_HWnd_T YWGUI_GetMainWinById(U16 id);

//���������ھ���õ�������ID
YWGUI_API U16 YWGUI_GetMainWinId(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_SetFocus
��������: ���ð������㵽ָ���Ŀؼ�����
��    ��: hWnd[in] -- ָ���Ŀؼ����ھ��
�� �� ֵ: ������ǰ�Ľ��㴰�� �� YWGUI_NULL_HANDLE(��ǰû�н��㴰�ڻ��쳣)
˵    ��: 1)��hWnd���ǿؼ����ڣ��ú���û��Ч��
          2)���ؼ��������ȿؼ�������/disabled/"�ò�������"��״̬��
            �ú���û��Ч��
          3)�ú���ֻ���ڸÿؼ�����������Ϣ�����߳��е���
�޸ļ�¼:
************************************************************************/
YWGUI_API YWGUI_HWnd_T  YWGUI_SetFocus(YWGUI_HWnd_T hWnd);

YWGUI_API YWGUI_HWnd_T YWGUI_SetActiveChild(YWGUI_HWnd_T hParent,YWGUI_HWnd_T hChild);

//�õ�hParent�İ������㴰��
YWGUI_API YWGUI_HWnd_T YWGUI_GetFocus(YWGUI_HWnd_T hParent);

/***********************************************************************
��������: YWGUI_GetParent
��������: �õ������ھ��
��    ��:   hWnd[in] -- ���ھ��
�� �� ֵ:   �����ھ���� YWGUI_NULL_HANDLE
˵    ��:   1)�����ڵĸ������� HWND_DESKTOP
            2)����Ĵ��ھ����Ч����YWGUI_NULL_HANDLE
************************************************************************/
YWGUI_API YWGUI_HWnd_T  YWGUI_GetParent (YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_GetHosting
��������: �õ��������ھ��
��    ��:   hWnd[in] -- �����ھ��
�� �� ֵ:   �������ھ���� YWGUI_NULL_HANDLE
˵    ��:   1)��һ���������ڵ�����������YWGUI_NULL_HANDLE
            2)������Ч�������ھ������YWGUI_NULL_HANDLE
************************************************************************/
YWGUI_API YWGUI_HWnd_T  YWGUI_GetHosting (YWGUI_HWnd_T hWnd);

//�õ����ڷ��
YWGUI_API DWORD YWGUI_GetWindowStyle(YWGUI_HWnd_T hWnd);

//�õ�������չ���
YWGUI_API DWORD YWGUI_GetWindowExStyle (YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_SetWindowExStyle
��������: ���ô�����չ���
��    ��:   hWnd[in] -- ���ھ��
            dwExStyle[in] -- ������չ���
�� �� ֵ:
˵    ��:   1)��ʹ��YWGUI_SetWindowExStyle֮ǰӦ�õ���
              YWGUI_GetWindowExStyle��ȡԭ������չ���
              �ڴ˻����Ͻ���λ�߼�����õ�����չ���,
              ��Ӧֱ����������һ����չ���
            2)�ú���ֻ���ڸô�������������Ϣ�����߳��е���
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_SetWindowExStyle(YWGUI_HWnd_T hWnd,DWORD dwExStyle);

/***********************************************************************
��������: YWGUI_SetWindowStyle
��������: ���ô��ڷ��
��    ��:   hWnd[in] -- ���ھ��
            dwStyle[in] -- ���ڷ��
�� �� ֵ:
˵    ��:   1)��ʹ��YWGUI_SetWindowStyle֮ǰӦ�õ���
              YWGUI_GetWindowStyle��ȡԭ���ķ��
              �ڴ˻����Ͻ���λ�߼�����õ��·��,
              ��Ӧֱ����������һ�����
            2)�ú���ֻ���ڸô�������������Ϣ�����߳��е���
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_SetWindowStyle(YWGUI_HWnd_T hWnd,DWORD dwStyle);

/***********************************************************************
��������: YWGUI_SetWindowText
��������: ���ô����ı�
��    ��:   hWnd[in] -- ���ھ��
            spString[in] -- �ı��ַ���
�� �� ֵ:
˵    ��:
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_SetWindowText (YWGUI_HWnd_T hWnd, const YWGUI_Char_T* spString);

/***********************************************************************
��������: YWGUI_GetWindowTextLength
��������: �õ������ı�����(��λ: �ַ�����)
��    ��:   hWnd[in] -- ���ھ��
�� �� ֵ:   ���ش����ı��ַ����ַ�����(������������)
˵    ��:
************************************************************************/
YWGUI_API S32   YWGUI_GetWindowTextLength (YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_GetWindowText
��������: �õ������ı�
��    ��:   hWnd[in] -- ���ھ��
            textBuf[out]--ָ���ı�������
            buf_size[in]-- ��������С(�ֽڸ���)
�� �� ֵ:   ���������������ַ���,������������(UCS2 һ���ַ�ռ�����ֽ�)
˵    ��:
************************************************************************/
YWGUI_API S32   YWGUI_GetWindowText(YWGUI_HWnd_T hWnd, YWGUI_Char_T* textBuf, U32 buf_size);

//�õ����ڵ�dwAddData����
YWGUI_API DWORD  YWGUI_GetWindowAdditionalData(YWGUI_HWnd_T hWnd);

//���ô��ڵ�dwAddData����,����ֵΪ�ϵ�dwAddData
YWGUI_API DWORD  YWGUI_SetWindowAdditionalData(YWGUI_HWnd_T hWnd, DWORD newData);

YWGUI_API DWORD  YWGUI_GetWindowAdditionalData2 (YWGUI_HWnd_T hWnd);
YWGUI_API DWORD  YWGUI_SetWindowAdditionalData2 (YWGUI_HWnd_T hWnd, DWORD newData);


YWGUI_API void YWGUI_DumpWindow (YWGUI_HWnd_T hWnd);



/***********************************************************************
��������: YWGUI_SetTimer
��������: ����һ����ʱ��
��    ��: hWnd[in] --��ʱ���������ھ��
          idTimer[in] -- ��ʱ��ID,��ֵ�������0
          elapse [in] -- ��ʱ������ʱ��(��λ:����)
�� �� ֵ: YW_NO_ERROR -- OK ; ���� -- ʧ��
˵    ��:  1)���д��ڼ���������ʹ��32����ʱ�� (���б���7����GUIϵͳ�Լ�ʹ��)
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_SetTimer (YWGUI_HWnd_T hWnd, S32 idTimer, U32 elapse);

/***********************************************************************
��������: YWGUI_KillTimer
��������: �رն�ʱ��
��    ��: hWnd[in] --��ʱ���������ھ��
          idTimer[in] -- ��ʱ��ID,��ֵ<=0ʱ���رոô��ڵ����ж�ʱ��
�� �� ֵ: �ɺ��Է���ֵ(YW_NO_ERROR/YWGUI_ERROR_NOT_FOUND/YWGUI_ERROR_INVALID_HANDLE)
˵    ��:
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_KillTimer(YWGUI_HWnd_T hWnd, S32 idTimer);

/***********************************************************************
��������: YWGUI_ResetTimer
��������: ���趨ʱ��
��    ��: hWnd[in] --��ʱ���������ھ��
          idTimer[in] -- ��ʱ��ID,��ֵ�������0
          elapse [in] -- ��ʱ������ʱ��(��λ:����)
�� �� ֵ: YW_NO_ERROR -- OK ; ���� -- ʧ��
˵    ��: 1)���ö�ʱ����δ�����ã����ö�ʱ��;�������øö�ʱ�������趨ʱ��
�޸ļ�¼:
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
��������: YWGUI_MoveImeWindow
��������:
��    ��:  x[in] -- ��Ļ����(<0 ���ı�x����)
           y[in] -- ��Ļ����(<0 ���ı�y����)
           w[in] -- ��Ļ����(<=0 ���ı���)
           h[in] -- ��Ļ����(<=0 ���ı�߶�)
�� �� ֵ:
˵    ��:
�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_MoveImeWindow(S32 x, S32 y, S32 w, S32 h);

YWGUI_API YW_ErrorType_T YWGUI_NextImeGroup(void);

YWGUI_API YW_ErrorType_T YWGUI_PrevImeGroup(void);

YWGUI_API YW_ErrorType_T YWGUI_NextImePage(void);

YWGUI_API YW_ErrorType_T  YWGUI_GetCurrentIme(U16* pImeGroupId,U16 *pPageNo);

YWGUI_API YW_ErrorType_T  YWGUI_ProcessImeEvent(YWGUI_ImeEvent_E eEvent);


/**********************************dialog/ctrl����***************************/

//ע��ؼ�����
YWGUI_API BOOL YWGUI_RegisterWindowClass (YWGUI_WndClass_P pWndClass);

//ע���ؼ�����
YWGUI_API BOOL YWGUI_UnregisterWindowClass (const S8* szClassName);

//������ģ̬�Ի���(�Ի�����ʹ����Դģ�崴����������)
YWGUI_API YW_ErrorType_T  YWGUI_CreateDialog(S32 id,
                    YWGUI_HWnd_T hOwner, YWGUI_WindowProc_P DlgProc, LPARAM lParam,YWGUI_HWnd_T*phDlg);

//����ģ̬�Ի���(�Ի�����ʹ����Դģ�崴����������)
YWGUI_API YW_ErrorType_T YWGUI_DialogBox (S32 id, YWGUI_HWnd_T hOwner, YWGUI_WindowProc_P DlgProc, LPARAM lParam,S32 *pRetCode);

//�����ؼ�����(���Ӵ���)
YWGUI_API YW_ErrorType_T  YWGUI_CreateWidgetWindow (const S8* spClassName, const YWGUI_Char_T* spCaption, S32 idStr, DWORD dwStyle, DWORD dwExStyle, U16 id,
                  S32 x, S32 y, S32 w, S32 h, YWGUI_HWnd_T hParentWnd,DWORD dwAddData,YWGUI_ShapeInfo_T* ptShapeInfo,YWGUI_HWnd_T *phWnd);

//����ģ̬�Ի���
YWGUI_API YW_ErrorType_T  YWGUI_EndDialog (YWGUI_HWnd_T hDlg, S32 endCode);

//���ٿؼ�����(���Ӵ���)
YWGUI_API YW_ErrorType_T YWGUI_DestroyWidgetWindow (YWGUI_HWnd_T hWnd);

//Ĭ�ϵĶԻ�����̺���
YWGUI_API S32  YWGUI_DefaultDialogProc (YWGUI_HWnd_T hWnd, S32 message,WPARAM wParam, LPARAM lParam);


//����TAB ��(TAB�����Ӵ��ڵĴ���˳��),�õ��Ի���(������)����һ����Ҫ��ð������㴰��
YWGUI_API YWGUI_HWnd_T  YWGUI_GetNextDlgTabItem (YWGUI_HWnd_T hDlg, YWGUI_HWnd_T hCtl, BOOL bPrevious);

//���ݿؼ�ID�õ��ؼ����ھ��
YWGUI_API YWGUI_HWnd_T  YWGUI_GetDlgItem (YWGUI_HWnd_T hDlg, S32 nIDDlgItem);

//���ݿؼ����ھ���õ��ؼ�ID
YWGUI_API U16  YWGUI_GetDlgCtrlID (YWGUI_HWnd_T hCtrl);

//add by Eagle 2009-6-8
/***********************************************************************
��������: YWGUI_StaticSetXOffset
��������: ����static�ؼ��ַ��ĺ���ƫ��
��    ��: hCtrl [in] -- static�ؼ��ľ��
          offset [in] -- ƫ����,������Ϊ��λ
�� �� ֵ: YW_NO_ERROR
˵    ��: ���� YWGUI_SS_LEFT �� Ĭ�Ϸ�� �²���Ч
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_StaticSetXOffset(YWGUI_HWnd_T hCtrl, U16 offset);

/***********************************************************************
��������: YWGUI_StaticSetYOffset
��������: ����static�ؼ��ַ�������ƫ��
��    ��: hCtrl [in] -- static�ؼ��ľ��
          offset [in] -- ƫ����,������Ϊ��λ
�� �� ֵ: YW_NO_ERROR
˵    ��: ���� YWGUI_SS_TOP �� Ĭ�Ϸ�� �²���Ч
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_StaticSetYOffset(YWGUI_HWnd_T hCtrl, U16 offset);

/***********************************************************************
��������: YWGUI_ButtonSetXOffset
��������: ���� button �ؼ��ַ��ĺ���ƫ��
��    ��: hCtrl [in] -- button �ؼ��ľ��
          offset [in] -- ƫ����,������Ϊ��λ
�� �� ֵ: YW_NO_ERROR
˵    ��: ���� YWGUI_BS_LEFT �� Ĭ�Ϸ�� �²���Ч
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_ButtonSetXOffset(YWGUI_HWnd_T hCtrl, U16 offset);

/***********************************************************************
��������: YWGUI_ButtonSetYOffset
��������: ���� button �ؼ��ַ��ĺ���ƫ��
��    ��: hCtrl [in] -- button �ؼ��ľ��
          offset [in] -- ƫ����,������Ϊ��λ
�� �� ֵ: YW_NO_ERROR
˵    ��: ���� YWGUI_BS_TOP �� Ĭ�Ϸ�� �²���Ч
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_ButtonSetYOffset(YWGUI_HWnd_T hCtrl, U16 offset);

/***********************************************************************
��������: YWGUI_SetPicture
��������:   ����picture�ؼ���λͼ
��    ��:   hWnd [in] -- picture�ؼ��ľ��
            pDibmp [in] -- �豸�޹�λͼ�ṹָ��
            bUpdate [in] -- �Ƿ����ϸ�����ʾ
�� �� ֵ:
˵    ��:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetPicture(YWGUI_HWnd_T hWnd,const YWGUI_GraphCell_T* pDibmp,BOOL bUpdate);

/***********************************************************************
��������: YWGUI_SetPosbarRange
��������:   ���� posbar �ؼ��� range ֵ
��    ��:   hWnd [in] -- posbar �ؼ��ľ��
            range[in] -- (max - min) ,���� min Ϊ����0 ,��ʵ��Ϊ max ֵ
�� �� ֵ:
˵    ��:
�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetPosbarRange(YWGUI_HWnd_T hWnd,U32 range);


/***********************************************************************
��������: YWGUI_SetPosbarPosVal
��������:   ���� posbar �ؼ��� pos ֵ
��    ��:   hWnd [in] -- posbar �ؼ��ľ��
            posVal[in]
�� �� ֵ:
˵    ��:
�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetPosbarPosVal(YWGUI_HWnd_T hWnd,U32 posVal);


/***********************************************************************
��������: YWGUI_GetPosbarPos
��������:   ��� posbar �ؼ��� pos ֵ�� range ֵ
��    ��:   hWnd [in] -- posbar �ؼ��ľ��
            pPos[out] -- ���� pos ֵ
            pRange[out]--���� (max-min),��min Ϊ����0,ʵ�ʷ��ص��� max ֵ
�� �� ֵ:
˵    ��:
�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_GetPosbarPos(YWGUI_HWnd_T hWnd,U32* pPos,U32 *pRange);

/***********************************************************************
��������: YWGUI_SetPosbarThumbSize
��������:   ���� posbar �ؼ��� thumb size ֵ
��    ��:   hWnd [in] -- posbar �ؼ��ľ��
            thumbSize[in]
�� �� ֵ:
˵    ��:
�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetPosbarThumbSize(YWGUI_HWnd_T hWnd,U32 thumbSize);

/***********************************************************************
��������: YWGUI_GetPosBarThumbRect
��������:   ��ȡ�����λ��
��    ��:   hWnd [in] -- posbar �ؼ��ľ��
                     prcThumb[in]
�� �� ֵ:
˵    ��:
�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_GetPosBarThumbRect(YWGUI_HWnd_T  hWnd,YWGUI_Rect_T *prcThumb);


/***********************************************************************
��������: YWGUI_SetProgressBarRange
��������:   ���� Progress bar �ؼ��� range ֵ
��    ��:   hWnd [in] -- Progress �ؼ��ľ��
            range[in] -- (max - min) ,���� min Ϊ����0 ,��ʵ��Ϊ max ֵ
�� �� ֵ:
˵    ��:
�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetProgressBarRange(YWGUI_HWnd_T hWnd,U32 range);


/***********************************************************************
��������: YWGUI_SetProgressBarPosVal
��������:   ���� ProgressBar �ؼ��� pos ֵ
��    ��:   hWnd [in] -- ProgressBar �ؼ��ľ��
            posVal[in]
�� �� ֵ:
˵    ��:
�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetProgressBarPosVal(YWGUI_HWnd_T hWnd,U32 posVal);


/***********************************************************************
��������: YWGUI_GetProgressBarPos
��������:   ��� ProgressBar �ؼ��� pos ֵ�� range ֵ
��    ��:   hWnd [in] -- ProgressBar �ؼ��ľ��
            pPos[out] -- ���� pos ֵ
            pRange[out]--���� (max-min),��min Ϊ����0,ʵ�ʷ��ص��� max ֵ
�� �� ֵ:
˵    ��:
�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_GetProgressBarPos(YWGUI_HWnd_T hWnd,U32* pPos,U32 *pRange);

/***********************************************************************
��������: YWGUI_SetProgressBarStepSize
��������:   ���� posbar �ؼ��� thumb size ֵ
��    ��:   hWnd [in] -- posbar �ؼ��ľ��
            stepSize[in] -- ������С(��λ:����)
            thumbSize[in]-- ����Ĵ�С(��λ:����)
�� �� ֵ:
˵    ��:
�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetProgressBarStepSize(YWGUI_HWnd_T hWnd,U32 stepSize,U32 thumbSize);

/***********************************************************************
��������: YWGUI_GetProgressBarRect
��������:   ��� ProgressBar �ؼ��Ļ�ͼ�ķ�Χ
��    ��:   hWnd [in] -- ProgressBar �ؼ��ľ��
            pRect[out] --  ��ȡ�������Ļ�ͼ����
�� �� ֵ:
˵    ��:
�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_GetProgressBarRect(YWGUI_HWnd_T hWnd, YWGUI_Rect_T *pRect);
//Listview �ռ�ӿں���
/***********************************************************************
��������: YWGUI_LVAddColumn
��������: �����
��    ��:   hWnd[in] --  �ؼ����
            pLVColumn[in] -- �нṹ
�� �� ֵ:   -1ʧ�ܣ�0�ɹ�
˵    ��:
           YWGUI_LVM_ADDCOLUMN
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVAddColumn(YWGUI_HWnd_T hWnd, YWGUI_LVColumn_P pLVColumn);

/***********************************************************************
��������: YWGUI_LVAddItem
��������: �����
��    ��:   hWnd[in] --  �ؼ����
            ItemIndex[in] -- Ҫ������е�����
�� �� ֵ:   -1ʧ�ܣ�0�ɹ�
˵    ��:
           YWGUI_LVM_ADDITEM
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVAddItem(YWGUI_HWnd_T hWnd, U32 ItemIndex);


/***********************************************************************
��������: YWGUI_LVSetSubItem
��������: ���ø�������ľ�������
��    ��:   hWnd[in] --  �ؼ����
            pLVSubItem[in] -- ����ṹ
�� �� ֵ:   -1ʧ�ܣ�0�ɹ�
˵    ��:
           YWGUI_LVM_SETSUBITEM
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVSetSubItem(YWGUI_HWnd_T hWnd, YWGUI_LVSubItem_P pLVSubItem);

/***********************************************************************
��������: YWGUI_LVGetItemCount
��������: �õ��б��������
��    ��:   hWnd[in] --  �ؼ����

�� �� ֵ:   ������
˵    ��:
           YWGUI_LVM_GETITEMCOUNT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVGetItemCount(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_LVGetColumnWidth
��������: �õ��б��ָ���е��п�
��    ��:   hWnd[in] --  �ؼ����
            ColumnIndex[in] -- �е�������ע��:��������0��ʼ
�� �� ֵ:   -1ʧ�ܣ�0�ɹ�
˵    ��:
           YWGUI_LVM_GETCOLUMNWIDTH
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVGetColumnWidth(YWGUI_HWnd_T hWnd, U32 ColumnIndex);

/***********************************************************************
��������: YWGUI_LVGetSubItemTextLen
��������: �õ��б��ָ�����е��ı�����
��    ��:   hWnd[in] --  �ؼ����
            ItemIndex[in] -- �е�������ע��:��������0��ʼ
            ColumnIndex[in] -- �е�������ע��:��������0��ʼ
�� �� ֵ:   ��������ı�����,-1��ʾ����
˵    ��:
           YWGUI_LVM_GETSUBITEMLEN
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVGetSubItemTextLen(YWGUI_HWnd_T hWnd,U32 ItemIndex, U32 ColumnIndex);

/***********************************************************************
��������: YWGUI_LVGetSubItemText
��������: �õ��б��ָ�����е��ı�
��    ��:   hWnd[in] --  �ؼ����
            ItemIndex[in] -- �е�������ע��:��������0��ʼ
            ColumnIndex[in] -- �е�������ע��:��������0��ʼ
�� �� ֵ:   ��������ı�(YWGUI_Char_T*),-1��ʾ����
˵    ��:
           YWGUI_LVM_GETSUBITEMTEXT
�޸ļ�¼:
************************************************************************/
YWGUI_API YWGUI_Char_T* YWGUI_LVGetSubItemText(YWGUI_HWnd_T hWnd,U32 ItemIndex, U32 ColumnIndex);

/***********************************************************************
��������: YWGUI_LVSetHeadHeight
��������: ������ͷ�ĸ߶�
��    ��:   hWnd[in] --  �ؼ����
            HeadHeight[in] -- ��ͷ�ĸ߶ȣ�ע��:��������0��ʼ
�� �� ֵ:   -1ʧ�ܣ�0�ɹ�
˵    ��:
           YWGUI_LVM_SETHEADHEIGHT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVSetHeadHeight(YWGUI_HWnd_T hWnd, U32 HeadHeight);

/***********************************************************************
��������: YWGUI_LVDeleteItem
��������: ɾ��ָ����
��    ��:   hWnd[in] --  �ؼ����
            ItemIndex[in] -- ָ�����е�����,��0��ʼ
�� �� ֵ:   0Ϊɾ���ɹ�, -1Ϊɾ��ʧ��
˵    ��:
           YWGUI_LVM_DELITEM
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVDeleteItem(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
��������: YWGUI_LVDeleteAllItem
��������: ɾ�����ж���
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   0Ϊɾ���ɹ�, -1Ϊɾ��ʧ��
˵    ��:
           YWGUI_LVM_DELALLITEM
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVDeleteAllItem(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_LVDeleteColumn
��������: ɾ��ָ����
��    ��:   hWnd[in] --  �ؼ����
            ColumnIndex[in] -- ָ�����е�����,��0��ʼ
�� �� ֵ:   0Ϊɾ���ɹ�, -1Ϊɾ��ʧ��
˵    ��:
           YWGUI_LVM_DELCOLUMN
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVDeleteColumn(YWGUI_HWnd_T hWnd, U32 ColumnIndex);

/***********************************************************************
��������: YWGUI_LVPageDown
��������: ���·�ҳ
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   0Ϊɾ���ɹ�, -1Ϊɾ��ʧ��
˵    ��:
           YWGUI_LVM_PAGEDOWN
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVPageDown(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_LVPageUp
��������: ���Ϸ�ҳ
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   0Ϊɾ���ɹ�, -1Ϊɾ��ʧ��
˵    ��:
           YWGUI_LVM_PAGEUP
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVPageUp(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_LVGetColumnCount
��������: �õ�����
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   ����
˵    ��:
           YWGUI_LVM_GETCOLUMNCOUNT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVGetColumnCount(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_LVGetCurHotItemIndex
��������: ��ȡ��ǰ����������
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   ��ǰ����������
˵    ��:
           YWGUI_LVM_GETCURSEL
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVGetCurHotItemIndex(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_LVSetCurHotItemIndex
��������: ���õ�ǰ����������
��    ��:   hWnd[in] --  �ؼ����
            HotItemIndex[in] --  �½���������
�� �� ֵ:   ��ǰ����������
˵    ��:
           YWGUI_LVM_SETCURSEL
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVSetCurHotItemIndex(YWGUI_HWnd_T hWnd, U32 HotItemIndex);

/***********************************************************************
��������: YWGUI_LVGetItemState
��������: ��ȡָ���е�״̬
��    ��:   hWnd[in] --  �ؼ����
            ItemIndex[in] --  Ҫ��ȡ���е�����
�� �� ֵ:   0��ʾYWGUI_LVIF_NORMAL, 1��ʾYWGUI_LVIF_CHECKED, 2��ʾYWGUI_LVIF_SKIP
˵    ��:
           YWGUI_LVM_GETITEMSTATE
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVGetItemState(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
��������: YWGUI_LVSetItemState
��������: ����ָ���е���״̬
��    ��:   hWnd[in] --  �ؼ����
            ItemIndex[in] --  Ҫ���õ��е�����
            ItemState[in] --  0��ʾYWGUI_LVIF_NORMAL, 1��ʾYWGUI_LVIF_CHECKED, 2��ʾYWGUI_LVIF_SKIP
�� �� ֵ:   0���óɹ���-1����ʧ��
˵    ��:
           YWGUI_LVM_SETITEMSTATE
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVSetItemState(YWGUI_HWnd_T hWnd, U32 ItemIndex, U32 ItemState);

/***********************************************************************
��������: YWGUI_LVSort
��������: ���б��ָ���н�������������
��    ��:   hWnd[in] --  �ؼ����
            SortMode[in] --  �����ģʽ 0 YWGUI_LVSORT_NOTSORT, 1 YWGUI_LVSORT_ASC, 2 YWGUI_LVSORT_DESC
            SortColumnIndex[in] --  Ҫ�������,��0��ʼ
�� �� ֵ:   0���óɹ���-1����ʧ��
˵    ��:
           YWGUI_LVM_SORT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVSort(YWGUI_HWnd_T hWnd, U32 SortMode, U32 SortColumnIndex);

/***********************************************************************
��������: YWGUI_LVGetVisibleCount
��������: ����ListView�ؼ��ɼ�����
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   �ɼ�����
˵    ��:
           YWGUI_LVM_GETVISIBLECOUNT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVGetVisibleCount(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_LVSetVisibleCount
��������: ����ListView�ؼ��ɼ�����
��    ��:   hWnd[in] --  �ؼ����
            VisibleCount[in] --  ָ���Ŀɼ�����
�� �� ֵ:   0���óɹ���-1����ʧ��
˵    ��:
           YWGUI_LVM_SETVISIBLECOUNT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVSetVisibleCount(YWGUI_HWnd_T hWnd, U32 VisibleCount);

/***********************************************************************
��������: YWGUI_LVSelectAll
��������: ѡ��ָ���л�ȡ��ѡ��ָ����
��    ��:   hWnd[in] --  �ؼ����
            bSelectAll[in] --  True��ʾѡ��������, False��ʾȡ��ѡ��������
�� �� ֵ:   0���óɹ���-1����ʧ��
˵    ��:
           YWGUI_LVM_SETSELECTALL
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVSelectAll(YWGUI_HWnd_T hWnd, BOOL bSelectAll);

/***********************************************************************
��������: YWGUI_LVSelectOthers
��������: ����ѡ��
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   0���óɹ���-1����ʧ��
˵    ��:
           YWGUI_LVM_SETSELECTOTHERS
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LVSelectOthers(YWGUI_HWnd_T hWnd);


//sedit �ؼ��ӿں���
/***********************************************************************
��������: YWGUI_SEditGetTextLen
��������: ��ȡ�ı�����
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   �ı�����,������\0
˵    ��:
           YWGUI_SEM_GETTEXTLEN
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_SEditGetTextLen(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_SEditSetPasswordChar
��������: ����������ʾ�ַ�
��    ��:   hWnd[in] --  �ؼ����
            cChar[in] --  ������ʾ�ַ�
�� �� ֵ:
˵    ��:
           YWGUI_SEM_SETPASSWORDCHAR
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_SEditSetPasswordChar(YWGUI_HWnd_T hWnd, YWGUI_Char_T cChar);

/***********************************************************************
��������: YWGUI_SEditGetPasswordChar
��������: ��ȡ������ʾ�ַ�
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   ������ʾ�ַ�(YWGUI_Char_T)
˵    ��:
           YWGUI_SEM_GETPASSWORDCHAR
�޸ļ�¼:
************************************************************************/
YWGUI_API YWGUI_Char_T YWGUI_SEditGetPasswordChar(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_SEditGetMaxLimit
��������: ��ȡEdit���ַ�������(����\n)
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   Edit���ַ�������
˵    ��:
           YWGUI_SEM_GETMAXLIMIT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_SEditGetMaxLimit(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_SEditSetMaxLimit
��������: ����Edit���ַ�������(����\n)
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:
˵    ��:
           YWGUI_SEM_GETMAXLIMIT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_SEditSetMaxLimit(YWGUI_HWnd_T hWnd, U32 MaxLimit);

/***********************************************************************
��������: YWGUI_SEditSetEditStatus
��������: ����Edit�ı༭״̬
��    ��:   hWnd[in] --  �ؼ����
            bEnterEditStatus[in] --  FALSE��ʾ�Ǳ༭״̬,�����ʾ����༭״̬
�� �� ֵ:   :-1 ����ʧ��(��ǰ���㲻�ڵ�ǰҪ���õ�Edit��), 0���óɹ�.
˵    ��:  ֻ�е�ǰ�����ڵ�ǰ���õ�Edit�ؼ��ϲſ������óɹ�.
           YWGUI_SEM_SETEDITSTATUS
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_SEditSetEditStatus(YWGUI_HWnd_T hWnd, BOOL bEnterEditStatus);

/***********************************************************************
��������: YWGUI_SEditGetEditStatus
��������: ��ȡEdit�ı༭״̬
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   FALSE��ʾ�Ǳ༭״̬,�����ʾ����༭״̬
˵    ��:
           YWGUI_SEM_GETEDITSTATUS
�޸ļ�¼:
************************************************************************/
YWGUI_API BOOL YWGUI_SEditGetEditStatus(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_SEditGetCursorPos
��������: ��ȡEdit�й���λ��(0Ϊ��ʼ)
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   ����λ��
˵    ��:
           YWGUI_SEM_GETCURSORPOS
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_SEditGetCursorPos(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_SEditSetCursorPos
��������: ����Edit�й���λ��(0Ϊ��ʼ)
��    ��:   hWnd[in] --  �ؼ����
            NewPos[in] --  ������λ��
�� �� ֵ:   ����λ��
˵    ��:
           YWGUI_SEM_SETCURSORPOS
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_SEditSetCursorPos(YWGUI_HWnd_T hWnd, U32 NewPos);

//Edit �ӿں���
/***********************************************************************
��������: YWGUI_EditGetTextLen
��������: ��ȡ�ı�����
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   �ı�����,������\0
˵    ��:
           YWGUI_EM_GETTEXTLEN
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_EditGetTextLen(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_EditSetPasswordChar
��������: ����������ʾ�ַ�
��    ��:   hWnd[in] --  �ؼ����
            cChar[in] --  ������ʾ�ַ�
�� �� ֵ:
˵    ��:
           YWGUI_EM_SETPASSWORDCHAR
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_EditSetPasswordChar(YWGUI_HWnd_T hWnd, YWGUI_Char_T cChar);

/***********************************************************************
��������: YWGUI_EditGetPasswordChar
��������: ��ȡ������ʾ�ַ�
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   ������ʾ�ַ�(YWGUI_Char_T)
˵    ��:
           YWGUI_EM_GETPASSWORDCHAR
�޸ļ�¼:
************************************************************************/
YWGUI_API YWGUI_Char_T YWGUI_EditGetPasswordChar(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_EditGetMaxLimit
��������: ��ȡEdit���ַ�������(����\n)
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   Edit���ַ�������
˵    ��:
           YWGUI_EM_GETMAXLIMIT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_EditGetMaxLimit(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_EditSetMaxLimit
��������: ����Edit���ַ�������(����\n)
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:
˵    ��:
           YWGUI_EM_SETMAXLIMIT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_EditSetMaxLimit(YWGUI_HWnd_T hWnd, U32 MaxLimit);

/***********************************************************************
��������: YWGUI_EditSetEditStatus
��������: ����Edit�ı༭״̬
��    ��:   hWnd[in] --  �ؼ����
            bEnterEditStatus[in] --  FALSE��ʾ�Ǳ༭״̬,�����ʾ����༭״̬
�� �� ֵ:   :-1 ����ʧ��(��ǰ���㲻�ڵ�ǰҪ���õ�Edit��), 0���óɹ�.
˵    ��:  ֻ�е�ǰ�����ڵ�ǰ���õ�Edit�ؼ��ϲſ������óɹ�.
           YWGUI_EM_SETEDITSTATUS
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_EditSetEditStatus(YWGUI_HWnd_T hWnd, BOOL bEnterEditStatus);

/***********************************************************************
��������: YWGUI_EditGetEditStatus
��������: ��ȡEdit�ı༭״̬
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   FALSE��ʾ�Ǳ༭״̬,�����ʾ����༭״̬
˵    ��:
           YWGUI_EM_GETEDITSTATUS
�޸ļ�¼:
************************************************************************/
YWGUI_API BOOL YWGUI_EditGetEditStatus(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_EditGetCursorPos
��������: ��ȡEdit�й���λ��(0Ϊ��ʼ)
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   ����λ��
˵    ��:
           YWGUI_EM_GETCURSORPOS
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_EditGetCursorPos(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_EditSetCursorPos
��������: ����Edit�й���λ��(0Ϊ��ʼ)
��    ��:   hWnd[in] --  �ؼ����
            NewPos[in] --  ������λ��
�� �� ֵ:   ����λ��
˵    ��:
           YWGUI_EM_SETCURSORPOS
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_EditSetCursorPos(YWGUI_HWnd_T hWnd, U32 NewPos);

/***********************************************************************
��������: YWGUI_EditPageUp
��������: ���Ϸ�ҳ
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   ����λ��
˵    ��:  ���޶����ı����ʱʹ��
           YWGUI_EM_PAGEUP
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_EditPageUp(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_EditPageDown
��������: ���·�ҳ
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   ����λ��
˵    ��:  ���޶����ı����ʱʹ��
           YWGUI_EM_PAGEDOWN
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_EditPageDown(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_EditScrollPage
��������: ����ָ��ҳ��0��ʾ�������һҳ
��    ��:   hWnd[in] --  �ؼ����
            PageIndex[in] --  ��ҳ��������0��ʾ�������һҳ
�� �� ֵ:   ��
˵    ��: ���޶����ı����ʱʹ��

�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_EditScrollPage(YWGUI_HWnd_T hWnd, U32 PageIndex);

/***********************************************************************
��������: YWGUI_EditGetTotalLineCount
��������: ��ȡ������
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   ����������
˵    ��: ���޶����ı����ʱʹ��
           YWGUI_EM_GETTOTALLINECOUNT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_EditGetTotalLineCount(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_EditGetTopLineNo
��������: ��ȡ���е�����
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   �������е�����(������0��ʼ����)
˵    ��: ���޶����ı����ʱʹ��
           YWGUI_EM_TOPLINENO
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_EditGetTopLineNo(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_EditGetVisibleLineCount
��������: ��ȡ�ɼ�����
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:   ���ؿɼ�����
˵    ��: ���޶����ı����ʱʹ��
           YWGUI_EM_VISIBLELINECOUNT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_EditGetVisibleLineCount(YWGUI_HWnd_T hWnd);

//listbox �ӿں���
/***********************************************************************
��������: YWGUI_LBAddItem
��������: �����
��    ��:   hWnd[in] --  �ؼ����
            pLBItem[in] --  ��Item�ṹָ��
�� �� ֵ:
˵    ��:
           YWGUI_LB_ADDSTRING
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBAddItem(YWGUI_HWnd_T hWnd, YWGUI_LBItem_P pLBItem);


/***********************************************************************
��������: YWGUI_LBDeleteItem
��������: ɾ��ָ����
��    ��:   hWnd[in] --  �ؼ����
            ItemIndex[in] --  ָ��������, ע����������0��ʼ
�� �� ֵ: 0�ɹ�����1ʧ��
˵    ��:
           YWGUI_LB_DELETESTRING
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBDeleteItem(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
��������: YWGUI_LBGetItemCount
��������: ��ȡ�б�����
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ: 0�ɹ�����1ʧ��
˵    ��:
           YWGUI_LB_GETCOUNT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBGetItemCount(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_LBGetCurHotItemIndex
��������: ��ȡ��ǰ����������
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ: �б�Ľ���������, ������0��ʼ
˵    ��:
           YWGUI_LB_GETCURSEL
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBGetCurHotItemIndex(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_LBSetCurHotItemIndex
��������: ���ý���������
��    ��:   hWnd[in] --  �ؼ����
            ItemIndex[in] --  �½���������, ע����������0��ʼ
�� �� ֵ: ������
˵    ��:
           YWGUI_LB_SETCURSEL
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBSetCurHotItemIndex(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
��������: YWGUI_LBGetItemTextLen
��������: ��ȡָ�����ı�����
��    ��:   hWnd[in] --  �ؼ����
            ItemIndex[in] --  ������, ע����������0��ʼ
�� �� ֵ: ָ�����ı�����
˵    ��: ���ص��ǲ��������������ַ�����
           YWGUI_LB_GETTEXTLEN
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBGetItemTextLen(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
��������: YWGUI_LBGetItemText
��������: ��ȡָ�����ı�
��    ��:   hWnd[in] --  �ؼ����
            ItemIndex[in] --  ������, ע����������0��ʼ
            pStr[out] --  ��ָ�����ı�copy��lParam��ָ�ĵ�ַ�ռ�,(�������);
                       ע��˲�������Ϊ��
�� �� ֵ: 0��ȡ�ɹ���-1��ȡʧ��
˵    ��:
           YWGUI_LB_GETTEXT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBGetItemText(YWGUI_HWnd_T hWnd, U32 ItemIndex, YWGUI_Char_T* pStr);


/***********************************************************************
��������: YWGUI_LBSetItemText
��������: ����ָ�����ı�
��    ��:   hWnd[in] --  �ؼ����
            ItemIndex[in] --  ������, ע����������0��ʼ
            pStr[in] --  ���ı���ָ��
�� �� ֵ: 0��ȡ�ɹ���-1��ȡʧ��
˵    ��:
           YWGUI_LB_SETTEXT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBSetItemText(YWGUI_HWnd_T hWnd, U32 ItemIndex, YWGUI_Char_T* pStr);

/***********************************************************************
��������: YWGUI_LBSetItemVisibleCount
��������: �����б�Ŀɼ�����
��    ��:   hWnd[in] --  �ؼ����
            VisibleCount[in] --  �б���¿ɼ���
�� �� ֵ: 0���óɹ�, -1����ʧ��
˵    ��:
           YWGUI_LB_SETITEMVISIBLES
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBSetItemVisibleCount(YWGUI_HWnd_T hWnd, U32 VisibleCount);


/***********************************************************************
��������: YWGUI_LBGetItemVisibleCount
��������: ��ȡ�б�Ŀɼ�����
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ: �б�Ŀɼ�����
˵    ��:
           YWGUI_LB_GETITEMVISIBLES
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBGetItemVisibleCount(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_LBGetTopIndex
��������: ��ȡҪ��ʾ���б�Ķ�������
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ: ��������, ע������Ӱ��0��ʼ.
˵    ��:
           YWGUI_LB_GETTOPINDEX
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBGetTopIndex(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_LBPageDown
��������: ���·�ҳ
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:
˵    ��:
           YWGUI_LB_PAGEDOWN
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBPageDown(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_LBPageUp
��������: ���Ϸ�ҳ
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:
˵    ��:
           YWGUI_LB_PAGEUP
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBPageUp(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_LBSelectAll
��������: ѡ�л�ȡ��ѡ��������
��    ��:   hWnd[in] --  �ؼ����
            bSelect[in] --  TRUE��ʾ����Ϊѡ�У������ʾȡ��ѡ��
�� �� ֵ: 0���óɹ���-1����ʧ��
˵    ��:
           YWGUI_LB_SETSELECTALL
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBSelectAll(YWGUI_HWnd_T hWnd, BOOL bSelect);

/***********************************************************************
��������: YWGUI_LBSelectOthers
��������: ����ѡ��
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ: 0���óɹ���-1����ʧ��
˵    ��:
           YWGUI_LB_SETSELECTOTHERS
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBSelectOthers(YWGUI_HWnd_T hWnd, BOOL bSelect);

/***********************************************************************
��������: YWGUI_LBGetItemState
��������: ��ȡָ���е�״̬
��    ��:   hWnd[in] --  �ؼ����
            ItemIndex[in] --  Ҫ��ȡ���е�����
�� �� ֵ: 0��ʾYWGUI_LVIF_NORMAL, 1��ʾYWGUI_LVIF_CHECKED, 2��ʾYWGUI_LVIF_SKIP
˵    ��:
           YWGUI_LB_GETITEMSTATE
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBGetItemState(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
��������: YWGUI_LBGetItemState
��������: ����ָ���е���״̬
��    ��:   hWnd[in] --  �ؼ����
            ItemIndex[in] --  Ҫ��ȡ���е�����
            ItemState[in] --  0��ʾYWGUI_LBIF_NORMAL, 1��ʾYWGUI_LBIF_CHECKED, 2��ʾYWGUI_LBIF_SKIP
�� �� ֵ: 0���óɹ�����1����ʧ��
˵    ��:
           YWGUI_LB_SETITEMSTATE
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBSetItemState(YWGUI_HWnd_T hWnd, U32 ItemIndex, U32 ItemState);

/***********************************************************************
��������: YWGUI_LBCurEditItemIndex
��������: ��ȡ��ǰ�༭���е�����,��Ҫ���¼�YWGUI_LBN_SELCHANGED��,��ȡ�ı�Checked״̬���е�����
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ: ��ǰ�༭����
˵    ��:
           YWGUI_LB_GETCUREDITROWINDEX
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBCurEditItemIndex(YWGUI_HWnd_T hWnd);
#if 0
/***********************************************************************
��������: YWGUI_LRFindString
��������: ����ָ���ַ������б��еĵ�һ��λ�õ�������(�Ǿ�ȷ����)
��    ��:   hWnd[in] --  �ؼ����
            StartRowIndex[in] --  ��ʼ���ҵ��е�����, ���Ǵӵڼ��п�ʼ����
            pFindStr[in] --  Ҫ���ҵ��ַ�����ָ��
�� �� ֵ: �ҵ��ĵ�һ���ַ������ڵ�������,���Ϊ-1��ʾ����ʧ��
˵    ��:
           YWGUI_LB_FINDSTRING
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBFindString(YWGUI_HWnd_T hWnd, U32 StartRowIndex,YWGUI_Char_T* pFindStr);

/***********************************************************************
��������: YWGUI_LBFindStringExact
��������: ����ָ���ַ������б��еĵ�һ��λ�õ�������(��ȷ����,�ַ�������ҲҪһ��)
��    ��:   hWnd[in] --  �ؼ����
            StartRowIndex[in] --  ��ʼ���ҵ��е�����, ���Ǵӵڼ��п�ʼ����
            pFindStr[in] --  Ҫ���ҵ��ַ�����ָ��
�� �� ֵ: �ҵ��ĵ�һ���ַ������ڵ�������,���Ϊ-1��ʾ����ʧ��
˵    ��:
           YWGUI_LB_FINDSTRINGEXACT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LBFindStringExact(YWGUI_HWnd_T hWnd, U32 StartRowIndex,YWGUI_Char_T* pFindStr);
#endif
/***********************************************************************
��������: YWGUI_ListBoxSetXOffset
��������: ����static�ؼ��ַ��ĺ���ƫ��
��    ��: hWnd [in] -- listbox�ؼ��ľ��
          XOffset [in] -- ƫ����,������Ϊ��λ
�� �� ֵ: YW_NO_ERROR
˵    ��: 
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_ListBoxSetXOffset(YWGUI_HWnd_T hWnd, U16 XOffset);

/***********************************************************************
��������: YWGUI_ListBoxSetYOffset
��������: ����listbox�ؼ��ַ�������ƫ��
��    ��: hWnd [in] -- listbox�ؼ��ľ��
          YOffset [in] -- ƫ����,������Ϊ��λ
�� �� ֵ: YW_NO_ERROR
˵    ��: 
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_ListBoxSetYOffset(YWGUI_HWnd_T hWnd, U16 YOffset);

//lrcombobox �ӿں���
/***********************************************************************
��������: YWGUI_LRCBAddItem
��������: �����
��    ��:   hWnd[in] --  �ؼ����
            pListItem[in] --  Ҫ�����нṹָ��
�� �� ֵ: 0�ɹ�, -1ʧ��
˵    ��:
           YWGUI_LRCB_ADDSTRING
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBAddItem(YWGUI_HWnd_T hWnd, YWGUI_LRCBListItem_P pListItem);

/***********************************************************************
��������: YWGUI_LRCBDeleteItem
��������: ɾ��ָ����
��    ��:   hWnd[in] --  �ؼ����
            ItemIndex[in] --  Ҫɾ�����е�����
�� �� ֵ: 0�ɹ�, -1ʧ��
˵    ��:
           YWGUI_LRCB_DELETESTRING
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBDeleteItem(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
��������: YWGUI_LRCBGetCurHotItemIndex
��������: ��ȡ��ǰ����������
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ: �б�Ľ���������, ������0��ʼ
˵    ��:
           YWGUI_LRCB_GETCURSEL
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBGetCurHotItemIndex(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_LRCBSetCurHotItemIndex
��������: ���ý���������
��    ��:   hWnd[in] --  �ؼ����
            ItemIndex[in] --  �½���������, ע����������0��ʼ
�� �� ֵ: 0�ɹ�, -1ʧ��
˵    ��:
           YWGUI_LRCB_SETCURSEL
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBSetCurHotItemIndex(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
��������: YWGUI_LRCBGetItemCount
��������: ��ȡ�б�������
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ: �б������
˵    ��:
           YWGUI_LRCB_GETCOUNT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBGetItemCount(YWGUI_HWnd_T hWnd);
#if 0
/***********************************************************************
��������: YWGUI_LRCBFindString
��������: ����ָ���ַ������б��еĵ�һ��λ�õ�������(�Ǿ�ȷ����)
��    ��:   hWnd[in] --  �ؼ����
            StartRowIndex[in] --  ��ʼ���ҵ��е�����, ���Ǵӵڼ��п�ʼ����
            pFindStr[in] --  Ҫ���ҵ��ַ�����ָ��
�� �� ֵ: �ҵ��ĵ�һ���ַ������ڵ�������,���Ϊ-1��ʾ����ʧ��
˵    ��:
           YWGUI_LRCB_FINDSTRING
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBFindString(YWGUI_HWnd_T hWnd, U32 StartRowIndex,YWGUI_Char_T* pFindStr);

/***********************************************************************
��������: YWGUI_LRCBFindStringExact
��������: ����ָ���ַ������б��еĵ�һ��λ�õ�������(��ȷ����,�ַ�������ҲҪһ��)
��    ��:   hWnd[in] --  �ؼ����
            StartRowIndex[in] --  ��ʼ���ҵ��е�����, ���Ǵӵڼ��п�ʼ����
            pFindStr[in] --  Ҫ���ҵ��ַ�����ָ��
�� �� ֵ: �ҵ��ĵ�һ���ַ������ڵ�������,���Ϊ-1��ʾ����ʧ��
˵    ��:
           YWGUI_LRCB_FINDSTRINGEXACT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBFindStringExact(YWGUI_HWnd_T hWnd, U32 StartRowIndex,YWGUI_Char_T* pFindStr);
#endif

/***********************************************************************
��������: YWGUI_LRCBGetListItemText
��������: ��ȡָ�����ı�
��    ��:   hWnd[in] --  �ؼ����
            ItemIndex[in] --  ������, ע����������0��ʼ
            pStr[out] --  ��ָ�����ı�copy��lParam��ָ�ĵ�ַ�ռ�,(�������);
                       ע��˲�������Ϊ��
�� �� ֵ: 0��ȡ�ɹ���-1��ȡʧ��
˵    ��:
           YWGUI_LRCB_GETLBTEXT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBGetListItemText(YWGUI_HWnd_T hWnd, U32 ItemIndex,YWGUI_Char_T* pStr);

/***********************************************************************
��������: YWGUI_LRCBGetListItemTextLen
��������: ��ȡָ�����ı�����
��    ��:   hWnd[in] --  �ؼ����
            ItemIndex[in] --  ������, ע����������0��ʼ
�� �� ֵ: ָ�����ı�����
˵    ��:
           YWGUI_LRCB_GETLBTEXTLEN
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBGetListItemTextLen(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
��������: YWGUI_LRCBGetText
��������: ��ȡ��ʾ���ı�
��    ��:   hWnd[in] --  �ؼ����
            Size[in] --  ָ���������Ĵ�С(�ֽڸ���)
            pStr[out] --  ������ָ��
�� �� ֵ: ���������������ַ���,������������
˵    ��:  ע��:   UCS2 һ���ַ�ռ�����ֽ�
           YWGUI_LRCB_GETTEXT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBGetText(YWGUI_HWnd_T hWnd, U32 Size,YWGUI_Char_T* pStr);

/***********************************************************************
��������: YWGUI_LRCBSetText
��������: ������ʾ���ı�
��    ��:   hWnd[in] --  �ؼ����
            pStr[in] --  ���õ��ı��ַ���
�� �� ֵ:
˵    ��:
           YWGUI_LRCB_SETTEXT
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBSetText(YWGUI_HWnd_T hWnd, YWGUI_Char_T* pStr);

/***********************************************************************
��������: YWGUI_LRCBSetListVisibleCount
��������: �����б�Ŀɼ�����
��    ��:   hWnd[in] --  �ؼ����
            VisibleCount[in] --  �б���¿ɼ���
�� �� ֵ: 0���óɹ�, -1����ʧ��
˵    ��:
           YWGUI_LRCB_SETITEMVISIBLES
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBSetListVisibleCount(YWGUI_HWnd_T hWnd, U32 VisibleCount);

#if 0
/***********************************************************************
��������: YWGUI_LRCBGetChildrenControlHandle
��������: ��ȡLRcombobox���ӿؼ��ľ��
��    ��:   hWnd[in] --  �ؼ����
            phLRCBEdit[out] --  ����Combobox�е�Edit�ľ���ĵ�ַ
            phLRCBList[out] --  ����Combobox�е�Listbox�ľ���ĵ�ַ
�� �� ֵ: 0���óɹ�, -1����ʧ��
˵    ��:
           YWGUI_LRCB_GETCHILDREN
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBGetChildrenControlHandle(YWGUI_HWnd_T hWnd, YWGUI_HWnd_T* phLRCBEdit,YWGUI_HWnd_T* phLRCBList);

/***********************************************************************
��������: YWGUI_LRCBGetEditHandle
��������: ��ȡLRcombobox��Edit�ؼ��ľ��
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ: ����Combobox�е�Edit�ľ��
˵    ��:
           YWGUI_LRCB_GETEDITHWND
�޸ļ�¼:
************************************************************************/
YWGUI_API YWGUI_HWnd_T YWGUI_LRCBGetEditHandle(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_LRCBGetListHandle
��������: ��ȡLRcombobox��listbox�ؼ��ľ��
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ: ����Combobox�е�listbox�ľ��
˵    ��:
           YWGUI_LRCB_GETLISTBOXHWND
�޸ļ�¼:
************************************************************************/
YWGUI_API YWGUI_HWnd_T YWGUI_LRCBGetListHandle(YWGUI_HWnd_T hWnd);
#endif
/***********************************************************************
��������: YWGUI_LRCBGetListItemState
��������: ��ȡlistָ���е�״̬
��    ��:   hWnd[in] --  �ؼ����
            ItemIndex[in] --  Ҫ��ȡ���е�����
�� �� ֵ: 0��ʾYWGUI_CBIF_NORMAL, 1��ʾYWGUI_CBIF_CHECKED, 2��ʾYWGUI_CBIF_SKIP
˵    ��:
           YWGUI_LRCB_GETITEMSTATE
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBGetListItemState(YWGUI_HWnd_T hWnd, U32 ItemIndex);

/***********************************************************************
��������: YWGUI_LRCBPageDown
��������: ���·�ҳ
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:
˵    ��:
           YWGUI_LRCB_PAGEDOWN
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBPageDown(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_LRCBPageUp
��������: ���Ϸ�ҳ
��    ��:   hWnd[in] --  �ؼ����
�� �� ֵ:
˵    ��:
           YWGUI_LRCB_PAGEUP
�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_LRCBPageUp(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_LRCBListSetXOffset
��������: ����lrcombobox�ؼ����б��ַ��ĺ���ƫ��
��    ��: hWnd [in] -- lrcombobox�ؼ��ľ��
          XOffset [in] -- ƫ����,������Ϊ��λ
�� �� ֵ: YW_NO_ERROR
˵    ��: 
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LRCBListSetXOffset(YWGUI_HWnd_T hWnd, U16 XOffset);

/***********************************************************************
��������: YWGUI_LRCBListSetYOffset
��������: ����lrcombobox�ؼ����б��ַ�������ƫ��
��    ��: hWnd [in] -- lrcombobox�ؼ��ľ��
          YOffset [in] -- ƫ����,������Ϊ��λ
�� �� ֵ: YW_NO_ERROR
˵    ��: 
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LRCBListSetYOffset(YWGUI_HWnd_T hWnd, U16 YOffset);

/***********************************************************************
��������: YWGUI_LRCBListSetYOffset
��������: �ر�lrcombobox�ĵ����б��
��    ��: hWnd [in] -- lrcombobox�ؼ��ľ��
�� �� ֵ: YW_NO_ERROR
˵    ��: 
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LRCBCloseListDlg(YWGUI_HWnd_T hWnd);


//�����ؼ� container
/***********************************************************************
��������: YWGUI_CTSetNextFocus
��������: �������ؼ�������л�����
��    ��:   hCT[in] --  �����ؼ��ؼ����
�� �� ֵ: ����-1��ʾʧ��
˵    ��: �˺���ֻ�����������ؼ�

�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_CTSetNextFocus(YWGUI_HWnd_T hCT);

/***********************************************************************
��������: YWGUI_CTSetPrevFocus
��������: �������ؼ�����ǰ�л�����
��    ��:   hCT[in] --  �����ؼ��ؼ����
�� �� ֵ: ����-1��ʾʧ��
˵    ��: �˺���ֻ�����������ؼ�

�޸ļ�¼:
************************************************************************/
YWGUI_API S32 YWGUI_CTSetPrevFocus(YWGUI_HWnd_T hCT);

/***********************************************************************
��������: YWGUI_CTGetCtrlHandleById
��������: ͨ���ؼ�ID�ҵ��ؼ��ľ��
��    ��:   hCT[in] --  �����ؼ��ؼ����
            CtrlId[in] --  �ؼ�ID
�� �� ֵ: ����ID��Ӧ�Ŀؼ����
˵    ��: �˺���ֻ�����������ؼ��еĿؼ�

�޸ļ�¼:
************************************************************************/
YWGUI_API YWGUI_HWnd_T YWGUI_CTGetCtrlHandleById(YWGUI_HWnd_T hCT, U16 CtrlId);


//add by Eagle 2009-05-06
//ListTable Interface
/***********************************************************************
��������: YWGUI_LTSetTotalLine
��������: ���� ListTable ��������
��    ��: hCtrl[in] -- ListTable ���
          LineNum[in] -- ListTable ������
          CurLine[in] -- ������
�� �� ֵ: YW_NO_ERROR
˵    ��: ��������Ҫ���ڿؼ��� PosBar/Check , �Լ���ҳ����
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTSetTotalLine(YWGUI_HWnd_T hCtrl, U16 LineNum, U16 CurLine);

/***********************************************************************
��������: YWGUI_LTGetTotalLine
��������: ��ȡ ListTable ��������
��    ��: hCtrl[in] -- ListTable ���
�� �� ֵ: ListTable ������
˵    ��: ��������Ҫ���ڿؼ��� PosBar/Check , �Լ���ҳ����
************************************************************************/
YWGUI_API U16 YWGUI_LTGetTotalLine(YWGUI_HWnd_T hCtrl);

/***********************************************************************
��������: YWGUI_LTSetItemInfo
��������: ����ItemҪ��ʾ����Ϣ
��    ��: hCtrl[in] -- ListTable ���
          Line[in] -- ListTable ����
          Col[in] -- ListTable ����
          pItemInfo[in] -- ��Ҫ���õ� ItemInfo
�� �� ֵ: YW_NO_ERROR
˵    ��:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTSetItemInfo(YWGUI_HWnd_T hCtrl, U16 Line, U16 Col, const YWGUI_LTItemInfo_T *pItemInfo);

/***********************************************************************
��������: YWGUI_LTScrollPage
��������: ����ItemҪ��ʾ����Ϣ
��    ��: hCtrl[in] -- ListTable ���
          IsPageDown[in] -- TRUE - �·�һҳ FALSE - �Ϸ�һҳ
�� �� ֵ: YW_NO_ERROR
˵    ��: ����ҳ�ɹ�ʱ,����� YWGUI_LTN_NEEDDATA ֪ͨ
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTScrollPage(YWGUI_HWnd_T hCtrl, BOOL IsPageDown);

/***********************************************************************
��������: YWGUI_LTSetCurLine
��������: ���õ�ǰ������
��    ��: hCtrl[in] -- ListTable ���
          LineNum[in] -- ��Ҫ���õ�������
�� �� ֵ: YW_NO_ERROR
˵    ��: ����Ҫ��ҳʱ,����� YWGUI_LTN_NEEDDATA ֪ͨ
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTSetCurLine(YWGUI_HWnd_T hCtrl, U16 LineNum);

/***********************************************************************
��������: YWGUI_LTGetCurLine
��������: �õ���ǰ������
��    ��: hCtrl[in] -- ListTable ���
�� �� ֵ: ����������,��Ϊ-1��û�н�����
˵    ��:
************************************************************************/
YWGUI_API S32 YWGUI_LTGetCurLine(YWGUI_HWnd_T hCtrl);

/***********************************************************************
��������: YWGUI_LTMarkLine
��������: ����ѡ�л��ѡ��״̬
��    ��: hCtrl[in] -- ListTable ���
          LineNum[in] -- Ŀ��������
          IsMark[in] -- TRUE - ѡ�� FALSE - ��ѡ��
�� �� ֵ: YW_NO_ERROR
˵    ��: �������� ListTable ������ Mark ���
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTMarkLine(YWGUI_HWnd_T hCtrl, U16 LineNum, BOOL IsMark);

/***********************************************************************
��������: YWGUI_LTMarkAll
��������: ����ѡ�л��ѡ��������
��    ��: hCtrl[in] -- ListTable ���
          IsMark[in] -- TRUE - ѡ�� FALSE - ��ѡ��
�� �� ֵ: YW_NO_ERROR
˵    ��: �������� ListTable ������ Mark ���
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTMarkAll(YWGUI_HWnd_T hCtrl, BOOL IsMark);

/***********************************************************************
��������: YWGUI_LTSwitchAllMark
��������: ��ѡ������
��    ��: hCtrl[in] -- ListTable ���
�� �� ֵ: YW_NO_ERROR
˵    ��: �������� ListTable ������ Mark ���
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTSwitchAllMark(YWGUI_HWnd_T hCtrl);

/***********************************************************************
��������: YWGUI_LTGetMarkState
��������: ��ȡĿ���е�ѡ��״̬
��    ��: hCtrl[in] -- ListTable ���
          LineNum[in] -- Ŀ��������
�� �� ֵ: TRUE - Ŀ���б�ѡ��
˵    ��: �������� ListTable ������ Mark ���
************************************************************************/
YWGUI_API BOOL YWGUI_LTGetMarkState(YWGUI_HWnd_T hCtrl, U16 LineNum);

/***********************************************************************
��������: YWGUI_LTGetFirstMarkLine
��������: ��ȡ��һ��ѡ����
��    ��: hCtrl[in] -- ListTable ���
          pLine[out] -- ���ص�һ��ѡ����.���û��,�򷵻� -1
�� �� ֵ: YW_NO_ERROR
˵    ��: �������� ListTable ������ Mark ���,�� YWGUI_LTGetNextMarkLine
          ���ʹ�ÿɻ�ȡ������ Mark ��
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTGetFirstMarkLine(YWGUI_HWnd_T hCtrl, S32 *pLine);

/***********************************************************************
��������: YWGUI_LTGetNextMarkLine
��������: ��ȡ��һ��ѡ����
��    ��: hCtrl[in] -- ListTable ���
          pLine[out] -- ������һ��ѡ����.���û��,�򷵻� -1
�� �� ֵ: YW_NO_ERROR
˵    ��: �������� ListTable ������ Mark ���
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTGetNextMarkLine(YWGUI_HWnd_T hCtrl, S32 *pLine);

/***********************************************************************
��������: YWGUI_LTGetLastMarkLine
��������: ��ȡ��һ��ѡ����
��    ��: hCtrl[in] -- ListTable ���
          pLine[out] -- ���ص�һ��ѡ����.���û��,�򷵻� -1
�� �� ֵ: YW_NO_ERROR
˵    ��: �������� ListTable ������ Mark ���,�� YWGUI_LTGetPrevMarkLine
          ���ʹ�ÿɻ�ȡ������ Mark ��
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTGetLastMarkLine(YWGUI_HWnd_T hCtrl, S32 *pLine);

/***********************************************************************
��������: YWGUI_LTGetPrevMarkLine
��������: ��ȡ��һ��ѡ����
��    ��: hCtrl[in] -- ListTable ���
          pLine[out] -- ������һ��ѡ����.���û��,�򷵻� -1
�� �� ֵ: YW_NO_ERROR
˵    ��: �������� ListTable ������ Mark ���
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTGetPrevMarkLine(YWGUI_HWnd_T hCtrl, S32 *pLine);

/***********************************************************************
��������: YWGUI_LTGetTotalMarkLineNum
��������: ��ȡ��ѡ������
��    ��: hCtrl[in] -- ListTable ���
          pNum[out] -- ������ѡ������
�� �� ֵ: YW_NO_ERROR
˵    ��: �������� ListTable ������ Mark ���
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTGetTotalMarkLineNum(YWGUI_HWnd_T hCtrl, S32 *pNum);

/***********************************************************************
��������: YWGUI_LTRefreshCurPageData
��������: ˢ�µ�ǰҳ����
��    ��: hCtrl[in] -- ListTable ���
�� �� ֵ: YW_NO_ERROR
˵    ��: ���óɹ������� YWGUI_LTN_NEEDDATA ֪ͨ
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTRefreshCurPageData(YWGUI_HWnd_T hCtrl);

/***********************************************************************
��������: YWGUI_LTDisableLine
��������: ���� Disable ״̬
��    ��: hCtrl[in] -- ListTable ���
          LineNum[in] -- Ŀ��������
          IsDisable[in] -- TRUE - Disable FALSE - Enable
�� �� ֵ: YW_NO_ERROR
˵    ��: �������� ListTable ������ Disable ���
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTDisableLine(YWGUI_HWnd_T hCtrl, U16 LineNum, BOOL IsDisable);

/***********************************************************************
��������: YWGUI_LTDisableAll
��������: ����ѡ�л��ѡ��������
��    ��: hCtrl[in] -- ListTable ���
          IsDisable[in] -- TRUE - Disable FALSE - Enable
�� �� ֵ: YW_NO_ERROR
˵    ��: �������� ListTable ������ Disable ���
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTDisableAll(YWGUI_HWnd_T hCtrl, BOOL IsDisable);

/***********************************************************************
��������: YWGUI_LTGetDisableState
��������: ��ȡĿ���е�ѡ��״̬
��    ��: hCtrl[in] -- ListTable ���
          LineNum[in] -- Ŀ��������
�� �� ֵ: TRUE - Ŀ���� Disable
˵    ��: �������� ListTable ������ Disable ���
************************************************************************/
YWGUI_API BOOL YWGUI_LTGetDisableState(YWGUI_HWnd_T hCtrl, U16 LineNum);

/***********************************************************************
��������: YWGUI_LTGetFirstDisableLine
��������: ��ȡ��һ��ѡ����
��    ��: hCtrl[in] -- ListTable ���
          pLine[out] -- ���ص�һ�� Disable ��.���û��,�򷵻� -1
�� �� ֵ: YW_NO_ERROR
˵    ��: �������� ListTable ������ Disable ���,�� YWGUI_LTGetNextDisableLine
          ���ʹ�ÿɻ�ȡ������ Disable ��
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTGetFirstDisableLine(YWGUI_HWnd_T hCtrl, S32 *pLine);

/***********************************************************************
��������: YWGUI_LTGetNextDisableLine
��������: ��ȡ��һ��ѡ����
��    ��: hCtrl[in] -- ListTable ���
          pLine[out] -- ������һ�� Disable ��.���û��,�򷵻� -1
�� �� ֵ: YW_NO_ERROR
˵    ��: �������� ListTable ������ Disable ���
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTGetNextDisableLine(YWGUI_HWnd_T hCtrl, S32 *pLine);

/***********************************************************************
��������: YWGUI_LTGetItemHeight
��������: ��ȡ�и�
��    ��: hCtrl[in] -- ListTable ���
          LineHeight[out] -- �����и�.-1��ʾ����
�� �� ֵ: ��
˵    ��:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTGetItemHeight(YWGUI_HWnd_T hCtrl, S32 *LineHeight);

/***********************************************************************
��������: YWGUI_LTGetViewLineNum
��������: ��ȡ��һ��ѡ����
��    ��: hCtrl[in] -- ListTable ���
          pViewLineNum[out] -- ����ÿҳ�Ŀɼ�����
�� �� ֵ: YW_NO_ERROR
˵    ��: �������� ListTable ������ Disable ���,�� YWGUI_LTGetNextDisableLine
          ���ʹ�ÿɻ�ȡ������ Disable ��
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_LTGetViewLineNum(YWGUI_HWnd_T hCtrl, S32 *pViewLineNum);

/***********************************************************************
��������: YWGUI_SEDITSetReplaceMode
��������: �ı� SEdit �ı༭��ʽ Replace �� Insert
��    ��: hCtrl[in] -- SEdit ���
�� �� ֵ: YW_NO_ERROR
˵    ��:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SEDITSetReplaceMode(YWGUI_HWnd_T hCtrl, BOOL IsReplace);

/**********************************coordinate����***************************/

/***********************************************************************
��������: YWGUI_ClientToScreen
��������: �ͻ����������ת����Ļ�������
��    ��: hWnd[in] -- ���ھ��
          rcClient[in] -- �������,�����������hWnd���ڿͻ���������
          rcScreen[out] -- ������Σ���Ļ����
�� �� ֵ:
˵    ��:
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_ClientToScreen(YWGUI_HWnd_T hWnd, const YWGUI_Rect_T* rcClient, YWGUI_Rect_T* rcScreen);

/***********************************************************************
��������: YWGUI_WindowToScreen
��������: �����������ת����Ļ�������
��    ��: hWnd[in] -- ���ھ��
          rcWindow[in] -- �������,�����������hWnd���ڵ�����
          rcScreen[out] -- ������Σ���Ļ����
�� �� ֵ:
˵    ��:
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_WindowToScreen(YWGUI_HWnd_T hWnd, const YWGUI_Rect_T* rcWindow, YWGUI_Rect_T* rcScreen);

/***********************************************************************
��������: YWGUI_ScreenToClient
��������: ��Ļ�������ת�ɿͻ����������
��    ��: hWnd[in] -- ���ھ��
          rcScreen[in] -- �������,��Ļ����
          rcClient[out] -- ������Σ������������hWnd���ڿͻ���������
�� �� ֵ:
˵    ��:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_ScreenToClient (YWGUI_HWnd_T hWnd, const YWGUI_Rect_T* rcScreen, YWGUI_Rect_T* rcClient);

//��Ļ�������ת�ɴ����������
/***********************************************************************
��������: YWGUI_ScreenToWindow
��������: ��Ļ�������ת�ɴ����������
��    ��: hWnd[in] -- ���ھ��
          rcScreen[in] -- �������,��Ļ����
          rcWindow[out] -- ������Σ������������hWnd���ڵ�����
�� �� ֵ:
˵    ��:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_ScreenToWindow (YWGUI_HWnd_T hWnd, const YWGUI_Rect_T* rcScreen, YWGUI_Rect_T* rcWindow);

/***********************************************************************
��������: YWGUI_GetWindowRectInScreen
��������: �õ����ڵ���Ļ����
��    ��: hWnd[in] -- ���ھ��
          pRect[out] -- ������Σ�hWnd���ڵ���Ļ����
�� �� ֵ:
˵    ��:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_GetWindowRectInScreen (YWGUI_HWnd_T hWnd, YWGUI_Rect_T* pRect);

/***********************************************************************
��������: YWGUI_GetClientRectInScreen
��������: �õ����ڿͻ�������Ļ����
��    ��: hWnd[in] -- ���ھ��
          pRect[out] -- ������Σ�hWnd���ڿͻ�������Ļ����
�� �� ֵ:
˵    ��:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_GetClientRectInScreen(YWGUI_HWnd_T hWnd, YWGUI_Rect_T* pRect);


/***********************************************************************
��������: YWGUI_GetWindowRectInParent
��������: �õ���������ڸ����ڿͻ������������
��    ��: hWnd[in] -- ���ھ��
          pRect[out] -- ������Σ�����ڸ����ڿͻ���������
�� �� ֵ:
˵    ��:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_GetWindowRectInParent(YWGUI_HWnd_T hWnd, YWGUI_Rect_T* pRect);

/***********************************************************************
��������: YWGUI_GetClientRectInParent
��������: �õ����ڿͻ�������ڸ����ڿͻ������������
��    ��: hWnd[in] -- ���ھ��
          pRect[out] -- ������Σ�����ڸ����ڿͻ���������
�� �� ֵ:
˵    ��:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_GetClientRectInParent(YWGUI_HWnd_T hWnd, YWGUI_Rect_T* pRect);

/***********************************************************************
��������: YWGUI_GetWindowRect
��������: �õ����ڵľ���(����ڱ����ڵ�����,�����ε����Ͻ�����Ϊ(0,0))
��    ��: hWnd[in] -- ���ھ��
          pRect[out]-- �������(���Ͻ�����Ϊ(0,0))
�� �� ֵ:
˵    ��:
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_GetWindowRect (YWGUI_HWnd_T hWnd, YWGUI_Rect_T* pRect);

/***********************************************************************
��������: YWGUI_GetClientRect
��������: �õ����ڿͻ����ľ���(����ڱ����ڿͻ���������,�����ε����Ͻ�����Ϊ(0,0))
��    ��: hWnd[in] -- ���ھ��
          pRect[out]-- �������(���Ͻ�����Ϊ(0,0))
�� �� ֵ:
˵    ��:
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_GetClientRect (YWGUI_HWnd_T hWnd, YWGUI_Rect_T* pRect);

//�õ����ڵĿ��
YWGUI_API S32 YWGUI_GetWindowWidth(YWGUI_HWnd_T hWnd);

//�õ����ڵĸ߶�
YWGUI_API S32 YWGUI_GetWindowHeight(YWGUI_HWnd_T hWnd);

//�õ����ڿͻ����Ŀ��
YWGUI_API S32 YWGUI_GetClientWidth(YWGUI_HWnd_T hWnd);

//�õ����ڿͻ����ĸ߶�
YWGUI_API S32 YWGUI_GetClientHeight(YWGUI_HWnd_T hWnd);


YWGUI_API void YWGUI_SetRect(YWGUI_Rect_T *pRect,S32 left,S32 top,S32 right,S32 bottom);

/**********************************message����***************************/
/***********************************************************************
��������: YWGUI_GetMessage
��������: ��ȡ��Ϣ
��    ��:  pMsg[out] -- ���صõ�����Ϣ
           hWnd[in] -- ���ھ�� (��������)
�� �� ֵ:  TRUE --�õ����˳���Ϣ; FALSE --�õ��˳���Ϣ
˵    ��:  1)�ú����� hWnd ����������Ϣ���л�ȡ��Ϣ��
             �����Ϣ����û����Ϣ��һֱ�ȴ����õ���ϢΪֹ
�޸ļ�¼:
************************************************************************/
YWGUI_API BOOL  YWGUI_GetMessage (YWGUI_Msg_T *pMsg, YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_PeekPostMessage
��������: ���ָ�����ڵ��ʼ���Ϣ,��⵽��Ϣ�����Ϣ�����Ƴ�����Ϣ
��    ��:  pMsg[out] -- ���ؼ�⵽����Ϣ
           hWnd[in] -- ָ�����ھ��
           iMsgFilterMin[in] -- �����Ϣ��Χ����Сֵ(��)
           iMsgFilterMax[in] -- �����Ϣ��Χ�����ֵ(��)
�� �� ֵ:   TRUE -- ��⵽��Ϣ; FALSE: û�м�⵽��Ϣ
˵    ��:

�޸ļ�¼:
************************************************************************/
YWGUI_API BOOL  YWGUI_PeekPostMessage (YWGUI_Msg_P pMsg, YWGUI_HWnd_T hWnd, S32 iMsgFilterMin,
                        S32 iMsgFilterMax);

YWGUI_API YW_ErrorType_T YWGUI_TranslateMessage(YWGUI_Msg_T* pMsg);

YWGUI_API S32 YWGUI_DispatchMessage (YWGUI_Msg_T* pMsg);

YWGUI_API YW_ErrorType_T  YWGUI_PostQuitMessage (YWGUI_HWnd_T hWnd);

YWGUI_API YW_ErrorType_T  YWGUI_PostMessage (YWGUI_HWnd_T hWnd, S32 iMsg, WPARAM wParam, LPARAM lParam);

YWGUI_API S32 YWGUI_SendMessage (YWGUI_HWnd_T hWnd, S32 iMsg, WPARAM wParam, LPARAM lParam);



/****************************************gdi����*********************************/
/***********************************************************************
��������: YWGUI_GetDC
��������: ��ȡ����DC
��    ��:   hWnd[in] -- ���ھ��
�� �� ֵ:   ���ػ�õĴ���DC
˵    ��:   1)�ú�����Ҫ��YWGUI_ReleaseDC�ɶ�ʹ��
            2)���û�п��е�DC������YWGUI_NULL_HANDLE
************************************************************************/
YWGUI_API YWGUI_HDc_T  YWGUI_GetDC(YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_GetClientDC
��������: ��ȡ���ڿͻ���DC
��    ��:   hWnd[in] -- ���ھ��
�� �� ֵ:   ���ػ�õĴ��ڿͻ���DC
˵    ��:   1)�ú�����Ҫ��YWGUI_ReleaseDC�ɶ�ʹ��
            2)���û�п��е�DC������YWGUI_NULL_HANDLE
************************************************************************/
YWGUI_API YWGUI_HDc_T  YWGUI_GetClientDC (YWGUI_HWnd_T hWnd);

/***********************************************************************
��������: YWGUI_ReleaseDC
��������: �ͷŴ��ڻ�ͻ���DC
��    ��:   hDC[in] -- DC
�� �� ֵ:   ��
˵    ��:
************************************************************************/
YWGUI_API void  YWGUI_ReleaseDC (YWGUI_HDc_T hDC);

YWGUI_API YWGUI_HDc_T  YWGUI_BeginPaint (YWGUI_HWnd_T hWnd);

YWGUI_API void  YWGUI_EndPaint (YWGUI_HWnd_T hWnd, YWGUI_HDc_T hdc);


/***********************************************************************
��������: YWGUI_GetDcEx
��������: �õ�����DC
��    ��:   hWnd[in] -- ���ھ��
�� �� ֵ:   ��
˵    ��:  1)�ú������� YWGUI_ReleaseDC ����ʹ��
           2)�ú�����չ YWGUI_GetDc ,�ṩ�� YWGUI_MSG_NCPAINT ��Ϣ��Ӧ����

�޸ļ�¼:
************************************************************************/
YWGUI_API YWGUI_HDc_T  YWGUI_GetDcEx(YWGUI_HWnd_T hWnd);



//�õ����ʿ��
#define YWGUI_GetPenWidth(hdc)  (U32)YWGUI_GetDCAttr(hdc,DC_ATTR_PEN_WIDTH)

//�õ��ַ�֮����
#define YWGUI_GetTextCharExtra(hdc)  (S32)YWGUI_GetDCAttr (hdc, DC_ATTR_CHAR_EXTRA)

//�õ��ı�������ļ��
#define YWGUI_GetTextAboveExtra(hdc)  (S32)YWGUI_GetDCAttr (hdc, DC_ATTR_ALINE_EXTRA)

//�õ��ı�������ļ��
#define YWGUI_GetTextBellowExtra(hdc) (S32)YWGUI_GetDCAttr (hdc, DC_ATTR_BLINE_EXTRA)


//���ñ���ɫ
#define YWGUI_SetBkColor(hdc,newColor, oldColor)  \
                do{ U32* pValue =(U32*)oldColor; U32 value =YWGUI_SetDCAttr (hdc, DC_ATTR_BK_COLOR, (U32)newColor); if(pValue) *pValue = value ;}while(0)

//���ñ���ģʽ
#define YWGUI_SetBkMode(hdc, mode)\
                YWGUI_SetDCAttr(hdc, DC_ATTR_BK_MODE, (U32)mode)

//���ò�Ĳ���ģʽ��added by sly, 2009-11-5
#define YWGUI_SetOpMode(hdc, mode)\
                (YWGUI_CANVAS_OpMode_T)YWGUI_SetDCAttr(hdc, DC_ATTR_OP_MODE, (U32)mode)

//���û�ˢ����ɫ
#define YWGUI_SetBrushColor(hdc,newColor, oldColor)   \
                 do{ U32* pValue =(U32*)oldColor; U32 value =YWGUI_SetDCAttr (hdc, DC_ATTR_BRUSH_COLOR, (U32)newColor); if(pValue) *pValue = value ;}while(0)

//���û��ʵ���ɫ
#define YWGUI_SetPenColor(hdc,newColor, oldColor) \
               do{ U32* pValue =(U32*)oldColor; U32 value =YWGUI_SetDCAttr (hdc, DC_ATTR_PEN_COLOR, (U32)newColor); if(pValue) *pValue = value ;}while(0)

//���û��ʵĿ��
#define YWGUI_SetPenWidth(hdc,width) \
        (U32)YWGUI_SetDCAttr (hdc, DC_ATTR_PEN_WIDTH, (U32)width)

//�����ı�����ɫ
#define YWGUI_SetTextColor(hdc,newColor, oldColor) \
              do{ U32* pValue =(U32*)oldColor; U32 value =YWGUI_SetDCAttr (hdc, DC_ATTR_TEXT_COLOR, (U32)newColor); if(pValue) *pValue = value ;}while(0)

//�����ַ�֮����
#define YWGUI_SetTextCharExtra(hdc, extra)       \
                YWGUI_SetDCAttr (hdc, DC_ATTR_CHAR_EXTRA, (U32)extra)

//�����ı�������ļ��
#define YWGUI_SetTextAboveExtra(hdc, extra)  \
                YWGUI_SetDCAttr (hdc, DC_ATTR_ALINE_EXTRA, (U32)extra)

//�����ı�������ļ��
#define YWGUI_SetTextBellowExtra(hdc, extra) \
                YWGUI_SetDCAttr (hdc, DC_ATTR_BLINE_EXTRA, (U32)extra)

/***********************************************************************
��������: YWGUI_GetCurFont
��������: �õ�DC��ǰ��ʹ�õ��߼������������
��    ��:  hdc[in] -- �豸DC
�� �� ֵ:  ��ǰʹ�õ��߼�������
˵    ��:
�޸ļ�¼:
************************************************************************/
YWGUI_API YWGUI_HFont_T YWGUI_GetCurFont (YWGUI_HDc_T hdc);

/***********************************************************************
��������: YWGUI_SelectFont
��������: ����DC ʹ���µ��߼�����
��    ��:  hdc[in] -- �豸DC
           hFont[in] -- �µ��߼������������
�� �� ֵ:  ��ǰʹ�õ��߼�������
˵    ��:
�޸ļ�¼:
************************************************************************/
YWGUI_API YWGUI_HFont_T YWGUI_SelectFont (YWGUI_HDc_T hdc, YWGUI_HFont_T hFont);

/***********************************************************************
��������: YWGUI_CreateLogFont
��������: ���ٵ��� YWGUI_CreateLogFont �������߼�����
��    ��:  szFontType [in] -- �������� (֧��"ttf"/"rbf")
           szFontFamily [in] -- ����� (֧��"fulan"/"arial")
           szCharset [in] -- �ַ���(֧��"UCS-2")
           szFontStyle [in] -- ������(֧��"rrncnn")
           width [in] --  ������(����ʸ��������Ч)
           height [in]--����ĸ߶�(����ԭ����size����)
           rotation [in] -- ����(��0)
�� �� ֵ:  �������߼�������
           ���Ϊ YWGUI_NULL_HANDLE �������߼�����ʧ��
˵    ��:  1)�ú��������� YWGUI_DestroyLogFont ����ʹ��
�޸ļ�¼:
                    1) Ϊ��ʹ��һЩ���������(����ϸ��������)������Ӧ�޸�,
                    ȥ����ԭ����size������������width, height����
************************************************************************/
YWGUI_API YWGUI_HFont_T  YWGUI_CreateLogFont (const S8* szFontType, const S8* szFontFamily,
    const S8* szCharset, const S8 * szFontStyle, U16 width, U16 height, S32 rotation);

/***********************************************************************
��������: YWGUI_DestroyLogFont
��������: ���ٵ��� YWGUI_CreateLogFont �������߼�����
��    ��:  hFont[in] -- �߼�������
�� �� ֵ:  ��
˵    ��:
�޸ļ�¼:
************************************************************************/
YWGUI_API void  YWGUI_DestroyLogFont (YWGUI_HFont_T hFont);

YWGUI_API YW_ErrorType_T YWGUI_SetWindowFont(YWGUI_HWnd_T hWnd,YWGUI_HFont_T hFont);

//���صĿ�߰������
YWGUI_API void YWGUI_GetTextExtent (YWGUI_HDc_T hdc, const YWGUI_Char_T* spText, S32 len, YWGUI_Extent_T* ptSize);

//���صĿ�߰������(��=�����+cExtra,��=�����+alExtra+blExtra)
YWGUI_API void YWGUI_GetCharExtent(YWGUI_HDc_T hdc,YWGUI_Char_T character,S32 *pWidth,S32 *pHeight);


YWGUI_API S32  YWGUI_TextOutLen (YWGUI_HDc_T hdc, S32 x, S32 y, const YWGUI_Char_T* spText, S32 len);

#define YWGUI_TextOut(hdc, x, y, text)    YWGUI_TextOutLen (hdc, x, y, text, -1)

/***********************************************************************
��������: YWGUI_DrawText
��������: ��ָ�����������ڰ���ʽ����ı�
��    ��:  hdc[in] --
           spText[in] -- ����ַ���
           len[in] -- ����ַ�����(<0 ����������ַ���)
           pRect[in] -- ָ���ľ������� (���DC�ľ�������)
           format[in] --
�� �� ֵ:  ��������ı�ռ����Ļ�߶�(���ظ���)
˵    ��:
�޸ļ�¼:
************************************************************************/
YWGUI_API S32  YWGUI_DrawText(YWGUI_HDc_T hdc, const YWGUI_Char_T* spText, S32 len,YWGUI_Rect_T *pRect,U32 format);
/***********************************************************************
��������: YWGUI_DrawTextEx
��������: ��ָ�����������ڰ���ʽ����ı�
��    ��:  hdc[in] --
           spText[in] -- ����ַ���
           len[in] -- ����ַ�����(<0 ����������ַ���)
           pRect[in] -- ָ���ľ�������(���DC�ľ�������)
           indent[in] --����ֵ
           format[in] --
�� �� ֵ:  ��������ı�ռ����Ļ�߶�(���ظ���)
˵    ��:  Ĭ�϶������������������Ҫ��������
                  ��Ҫָ��YWGUI_DT_NEGINDENT���
�޸ļ�¼:
************************************************************************/
YWGUI_API S32  YWGUI_DrawTextEx(YWGUI_HDc_T hdc, const YWGUI_Char_T* spText, S32 len,YWGUI_Rect_T *pRect, S32 indent, U32 format);


/***********************************************************************
��������: YWGUI_GetTextLineHightAndLineNum
��������: ��ָ�����������ڻ�ȡ�ı����иߺ�����
��    ��:  hdc[in] --
           spText[in] -- �ַ���
           len[in] -- �ַ�����(<0 ����������ַ���)
           pRect[in] -- ָ���ľ�������(���DC�ľ�������)
           format[in] --
           puLineNum[out] --�ı�������
�� �� ֵ:  ���ص������ֵĸ߶�(���ظ���)
˵    ��:
�޸ļ�¼:
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
��������: YWGUI_CreateBitmap
��������: �ú��������豸�޹�λͼ(ptDibmp)��hdc�����豸���λͼ
��    ��:   hdc[in] -- �豸DC
            ptDibmp[in] -- �豸�޹�λͼ�ṹָ��
�� �� ֵ: �����½����豸���λͼ���
˵    ��: 1)�ú����ڲ���̬�������ڴ棬����YWGUI_DeleteBitmap����ʹ��
          2)��ywƽ̨,Ϊ��Լ�ڴ棬���豸�޹�λͼ�����Ժ��豸һ�£�
            ��Ȼʹ���豸�޹�λͼ��λͼ���ݣ���Ҫ���������ʹ�ù�����һֱ����
************************************************************************/
YWGUI_API YWGUI_HGraphCell_T  YWGUI_CreateGraphCell(YWGUI_HDc_T hdc,const YWGUI_GraphCell_T* ptDibGraphCell);

YWGUI_API void YWGUI_DeleteGraphCell(YWGUI_HGraphCell_T hGraphCell);

/***********************************************************************
��������: YWGUI_FillBoxWithBitmap
��������: ���豸���λͼ��������������(����������)
��    ��:   hdc[in] -- �豸DC
            x[in] -- x����
            y[in] -- y����
            w[in] -- �����ο��
            h[in] -- �����θ߶�
            hBitmap[in] -- �豸���λͼ���
�� �� ֵ:   YW_NO_ERROR -- OK
            ���� --fail
˵    ��:  ��������w,hֵ<=0,���������λͼʵ�ʴ�С ;
           ���λͼ��С����w*h,�ü�λͼ��w*h������ʾ;
           ���λͼ��СС��w*h,��ʾλͼʵ�ʴ�С;
           ���������hdc�ü�
************************************************************************/
YWGUI_API YW_ErrorType_T  YWGUI_FillBoxWithGraphCell (YWGUI_HDc_T hdc, S32 x, S32 y, S32 w, S32 h,
                              YWGUI_HGraphCell_T  hGraphCell);

/***********************************************************************
��������: YWGUI_CreateGraphCollect
��������: �ú��������µ��豸���ͼ��
��    ��:   ptSrcGraphCollect[in] -- Դͼ��
�� �� ֵ:   �����µ�ͼ���ṹָ��
˵    ��:   1)�ú�����YWGUI_DeleteGraphCollect����ʹ��
            2)���Դͼ�����豸�޹أ������µ��豸���ͼ��
            3)���Դͼ�����豸��أ�ֱ�ӷ���Դͼ��������ͼ���ڲ�����+1
************************************************************************/
YWGUI_API YWGUI_GraphCollect_T* YWGUI_CreateGraphCollect(YWGUI_GraphCollect_T* ptSrcGraphCollect);

/***********************************************************************
��������: YWGUI_DeleteGraphCollect
��������: �ú�����YWGUI_CreateGraphCollect����ʹ��,�����ͷ�
��    ��: ptGraphCollect[in] -- ͼ��
�� �� ֵ: YW_NO_ERROR
˵    ��: 1)�ú�����YWGUI_CreateGraphCollect����ʹ��
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_DeleteGraphCollect(YWGUI_GraphCollect_T* ptGraphCollect);


/***********************************************************************
��������: YWGUI_SpellGraphAndPadding
��������: ��ƴͼ
��    ��:   hdc[in] -- �豸DC
            x[in] -- x����
            y[in] -- y����
            w[in] -- �滭������
            h[in] -- �滭����߶�
            ptGraphCollect[in] --ͼ��
            bPadding[in]--�Ƿ�����϶
�� �� ֵ:
˵    ��: 1)ͼ������ƴ��ʱ�߶Ȳ�һ�£�����ƴ��ʱ��Ȳ�һ�£�������һЩ��϶��
            �ú���������DC�Ļ�ˢɫ�����һЩ��϶
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SpellGraphAndPadding(YWGUI_HDc_T hdc, S32 x, S32 y, S32 w, S32 h, const YWGUI_GraphCollect_T* ptGraphCollect,BOOL bPadding);

/*��ƴͼ�������ú���������϶��*/
#define YWGUI_SpellGraphCollect(hdc,x,y,w,h,ptGraphCollect)   YWGUI_SpellGraphAndPadding(hdc,x,y,w,h,ptGraphCollect,FALSE)




/***********************************************************************
��������: YWGUI_SetWEColor
��������: ���ô���(������/�Ӵ���)ĳ����ɫ����
��    ��:   hWnd[in] -- ���ھ��
            item[in] --��ɫ������
            pixel[in] --��ɫֵ
�� �� ֵ:  YW_NO_ERROR-- ���óɹ�; ����--����ʧ��
˵    ��:  1)�ú���ֻ����ָ����������������Ϣ�����߳��е���
           2)����Ӧ���� YWGUI_MSG_NCCREATE/YWGUI_MSG_NOTIFY_NCCREATE
             ��Ϣ��Ӧ�е���
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetWEColor (YWGUI_HWnd_T hWnd, YWGUI_WecItem_E item, YWGUI_Pixel_T pixel);


/***********************************************************************
��������: YWGUI_SetWEMetrics
��������: ���ô���(������/�Ӵ���)ĳ����ɫ����
��    ��:   hWnd[in] -- ���ھ��
            item[in] --��ɫ������
            pixel[in] --��ɫֵ
�� �� ֵ:  YW_NO_ERROR-- ���óɹ�; ����--����ʧ��
˵    ��:  1)�ú���ֻ����ָ����������������Ϣ�����߳��е���
           2)����Ӧ���� YWGUI_MSG_NCCREATE/YWGUI_MSG_NOTIFY_NCCREATE
             ��Ϣ��Ӧ�е���
************************************************************************/
YWGUI_API YW_ErrorType_T   YWGUI_SetWEMetrics(YWGUI_HWnd_T hWnd, YWGUI_WemItem_E item, S32 size);

/***********************************************************************
��������: YWGUI_SetWEShapeState
��������: ���ô���(������/�Ӵ���)ĳ״̬�µ���۷�������ɫֵ
��    ��:   hWnd[in] -- ���ھ��
            item[in] --��۷�����(��״̬)
            ptShapeState[in] --ĳ״̬��Ӧ����۽ṹ
�� �� ֵ:  YW_NO_ERROR-- ���óɹ�; ����--����ʧ��
˵    ��:   1)�ú���ֻ����ָ����������������Ϣ�����߳��е���
            2)����Ӧ���� YWGUI_MSG_NCCREATE/YWGUI_MSG_NOTIFY_NCCREATE
             ��Ϣ��Ӧ�е���

************************************************************************/
YWGUI_API YW_ErrorType_T   YWGUI_SetWEShapeState(YWGUI_HWnd_T hWnd, YWGUI_WesItem_E item, YWGUI_ShapeState_T* ptShapeState);


/***********************************************************************
��������: YWGUI_SetGlobalQuad
��������: ����ȫ�ֵ�ɫ��
��    ��:
�� �� ֵ:
˵    ��: 1)ptQuad ��ָ����ڴ�δ������������ȫ�ִ���
�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_SetGlobalQuad(U32 nQuadColors,const YWMID_Palette_T*ptQuad);

/*����ǰ���Ľӿڷ�װ,added by sly, 2009-4-23*/
#ifndef WIN32
typedef enum YWGUI_PanelStartUpStat_e
{
    YWGUI_PANEL_STARTUP_STATE_UNKNOW,
    YWGUI_PANEL_STARTUP_STATE_ELECTRIFY =0x01,   /*�ϵ�����*/
    YWGUI_PANEL_STARTUP_STATE_STANDBY,           /*��������*/
    YWGUI_PANEL_STARTUP_STATE_TIMER,		/*��ʱ����*/
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
    YWGUI_PANEL_DISPLAY_TYPE_VFD = ( 1 << 0 ),       /*  VFD��ʾ */
    YWGUI_PANEL_DISPLAY_TYPE_LCD = ( 1 << 1 ),       /*  Һ����ʾ */ 
    YWGUI_PANEL_DISPLAY_TYPE_LED = ( 1 << 2 ),       /*  �������ʾ */
    YWGUI_PANEL_DISPLAY_TYPE_LBD = ( 1 << 3 )        /*  ��������ʾ�� */
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
    YWGUI_PANEL_INPUT_TYPE_PANEL            = ( 1 << 0 ),           /*  ǰ��尴�� */
    YWGUI_PANEL_INPUT_TYPE_REMOTE           = ( 1 << 1 ),           /*  ����ң������ */
    YWGUI_PANEL_INPUT_TYPE_JOYSTICK         = ( 1 << 2 ),           /*  ��Ϸ������ */
    YWGUI_PANEL_INPUT_TYPE_KEYBOARD         = ( 1 << 3 )            /*  ���߼������� */
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
    U32                    DisplayTypeCap;              /* ֧����ʾ���� */
    U32                    InputTypeCap;                /* ֧���������� */
    U32                    RemoteNumCap;                /* ���֧��ң������ */
    U32                    LBDTypeCap;                  /* ֧�ֵ�lbd */
    U32                    LEDNum;                      /* led���� */
    U32                    FrontInputKeyCap;            /* ֧�ֵ�ǰ��尴������ */
    void *                 PrivateData;
    U32                 PanelIndex;
}YWGUI_PanelDeviceList_T;

/*Panel Feature*/
typedef struct YWGUI_PanelFeature_s
{
    U32                     PanelNum;            /* Panel���� */
    YWGUI_PanelDeviceList_T        *PanelListHead;             /* Panel����ͷָ��*/
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
/*���漸���ӿ����ڴ����ִ���λͼ*/

/***********************************************************************
��������: YWGUI_SelectBitmapTextFont
��������: Ϊλͼѡ������
��    ��:          hFont   ������
�� �� ֵ:    ǰһ������ľ��
�޸ļ�¼:
************************************************************************/
YWGUI_API YWGUI_HFont_T  YWGUI_SelectBitmapTextFont(YWGUI_HFont_T hFont);
/***********************************************************************
��������: YWGUI_CreatBitmapFromText
��������: ���ı�����λͼ
��    ��:          spText �ı��ַ���
                            len   ��Ҫת���ĳ���
                            textColor �ı�����ɫ
                            bkColor   ����ɫ
                            Flags  ��Ҫת���ɵ�λͼ�ĸ�ʽ,�μ�ywmid.h
                            ptBmp ת���ĵ���λͼ����
                            ptBoundRect �޶�����,���ת�����ı��ϳ�ʱ�����Զ����У��ɴ�NULL
�� �� ֵ:    ������
��غ���:YWGUI_DeleteBitmap

�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_CreatBitmapFromText(const YWGUI_Char_T* spText, S32 len, YWGUI_Pixel_T textColor, YWGUI_Pixel_T bkColor, U32 format, U32 Flags, YWMID_DibitmapData_T * ptBmp, YWMID_Rect_T * ptBoundRect);
/***********************************************************************
��������: YWGUI_DeleteBitmap
��������: ɾ��ͨ��YWGUI_CreatBitmapFromText��������ͼ
��    ��:          ptBmp λͼ����
�� �� ֵ:    ������
��غ���:YWGUI_CreatBitmapFromText
�޸ļ�¼:
************************************************************************/
YWGUI_API YW_ErrorType_T YWGUI_DeleteBitmap(YWMID_DibitmapData_T * ptBmp);
YWGUI_API void  YWGUI_GetDeskTopHdl(YWGUI_HWnd_T *hWnd);//added by jhy

//�Ƿ����ö�ʱ��,�������Ҫ�Ͳ� ����
//LZ: move to ywplugin.mak for global useage
//#define YWGUI_ENABLE_TIMER

#ifdef __cplusplus
}
#endif

#endif


