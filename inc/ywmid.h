/*****************************************************************************************/
//  					Copyright (C), 2005-2010, AV Frontier Tech. Co., Ltd.
//
//
// �ļ�����		ywmid.h
//
// �����ߣ�		YYH
//
// ����ʱ�䣺	2008.05.05
//
// �ļ�������	MID��ͷ�ļ���
//
// �޸ļ�¼��   ��       ��      ��      ��       �汾      �޶�
//				---------        ---------        -----     -----
//              2008.05.12         YYH            0.01      �½�
//
/*****************************************************************************************/
#ifndef _YWMID_H
#define _YWMID_H

#ifdef DEBUG_TRACE
#define YWMID_Trace(x) YWOS_Trace x
#define YWMID_ASSERT(X) 	do{\
                                if (!(X))\
                                {\
                                    YWOS_Trace(YWOS_TRACE_ERROR,"ASSERT!! %s (%d)\n",__FILE__, __LINE__);\
                                    YWOS_Exit(1);\
                                }\
                            }while(0)
#else
#define YWMID_Trace(x)
#define YWMID_ASSERT(X)
#endif


#define YWMID_DIBMP_FLOW_DOWN           0x00000000//���ϵ���(Ĭ��)
#define YWMID_DIBMP_FLOW_UP                0x00000001 //���µ���
#define YWMID_DIBMP_FLOW_MASK            0x0000000F

#define YWMID_DIBMP_COMPRESS_NO         0x00000000 //��ѹ��(Ĭ��)
#define YWMID_DIBMP_COMPRESS_RLE4       0x00000010
#define YWMID_DIBMP_COMPRESS_RLE8       0x00000020
#define YWMID_DIBMP_COMPRESS_MASK      0x000000F0

#define YWMID_DIBMP_SIZE_4                    0x00000000
#define YWMID_DIBMP_SIZE_3                    0x00000100
#define YWMID_DIBMP_SIZE_2                    0x00000200
#define YWMID_DIBMP_SIZE_1                    0x00000300
#define YWMID_DIBMP_SIZE_MASK              0x00000F00

#define YWMID_DIBMP_FORMAT_BGR0_8888            0x00000000
#define YWMID_DIBMP_FORMAT_BGRA_8888            0x00001000
#define YWMID_DIBMP_FORMAT_RGBA_8888            0x00002000
#define YWMID_DIBMP_FORMAT_ABGR_8888            0x00003000
#define YWMID_DIBMP_FORMAT_ARGB_8888            0x00004000

#define YWMID_DIBMP_FORMAT_RGB_888              0x00020000
#define YWMID_DIBMP_FORMAT_BGR_888              0x00021000

//#define YWMID_DIBMP_FORMAT_RGB_565              0x00040000
#define YWMID_DIBMP_FORMAT_BGR_565              0x00040000
//#define YWMID_DIBMP_FORMAT_ARGB_4444              0x00041000
#define YWMID_DIBMP_FORMAT_BGRA_4444              0x00041000
#define YWMID_DIBMP_FORMAT_BGRA_5551              0x00042000

#define YWMID_DIBMP_FORMAT_CLUT_8                0x00060000

#define YWMID_DIBMP_FORMAT_YCBCR888_444 0x00080000
#define YWMID_DIBMP_FORMAT_CBYCR888_444 0x00081000
#define YWMID_DIBMP_FORMAT_YCBYCR8888_422 0x00082000
#define YWMID_DIBMP_FORMAT_CBYCRY8888_422 0x00083000

#define YWMID_DIBMP_FORMAT_MASK                    0x000FF000


#define YWMID_DIBMP_ALPHA_NO                        0x00000000
#define YWMID_DIBMP_ALPHA_GLOBAL                 0x10000000
#define YWMID_DIBMP_ALPHA_LOCAL                   0x20000000
#define YWMID_DIBMP_ALPHA_MASK                    0x30000000

#define YWMID_DIBMP_COLOR_KEY                        0x40000000
#define YWMID_DIBMP_COLOR_KEY_MASK              0x40000000

 /*added by sly for bitmapt op mode*/

#define YWMID_DIBMP_OP_MODE_NORMAL                    0x00000000
#define YWMID_DIBMP_OP_MODE_XOR                             0x00000001
#define YWMID_DIBMP_OP_MODE_TRANS                         0x00000002
#define YWMID_DIBMP_OP_MODE_COPY                           0x00000003
#define YWMID_DIBMP_OP_MODE_OR                                0x00000004
#define YWMID_DIBMP_OP_MODE_AND                              0x00000005
#define YWMID_DIBMP_OP_MODE_CLEAR                         0x00000006
#define YWMID_DIBMP_OP_MODE_SET                               0x00000007
#define YWMID_DIBMP_OP_MODE_EQUIV                          0x00000008
#define YWMID_DIBMP_OP_MODE_NOR                              0x00000009
#define YWMID_DIBMP_OP_MODE_NAND                            0x0000000A
#define YWMID_DIBMP_OP_MODE_INVERT                        0x0000000B
#define YWMID_DIBMP_OP_MODE_COPYINVERTED        0x0000000C
#define YWMID_DIBMP_OP_MODE_ORINVERTED             0x0000000D
#define YWMID_DIBMP_OP_MODE_ANDINVERTED           0x0000000E
#define YWMID_DIBMP_OP_MODE_ORREVERSE                0x0000000F
#define YWMID_DIBMP_OP_MODE_ANDREVERSE             0x00000010
#define YWMID_DIBMP_OP_MODE_COLORKEY                  0x00000011
#define YWMID_DIBMP_OP_MODE_ALPHA                           0x00000012
#define YWMID_DIBMP_OP_MODE_NOOP                            0x00000013

#define YWMID_DIBMP_OP_MODE_MASK                            0x0000001F

/*color key cp mode*/
#define YWMID_DIBMP_COLOR_KEY_MODE_NONE         0x00000000
#define YWMID_DIBMP_COLOR_KEY_MODE_SRC            0x00000100
#define YWMID_DIBMP_COLOR_KEY_MODE_DST            0x00000200

#define YWMID_DIBMP_COLOR_KEY_MODE_MASK         0x00000300

/*���ģʽ*/
#define YWMID_DIBMP_OUTPUT_MODE_CENTER            0x00000000      /*����*/
#define YWMID_DIBMP_OUTPUT_MODE_ZOOM                0x00001000      /*����*/
#define YWMID_DIBMP_OUTPUT_MODE_TILE                   0x00002000      /*ƽ��*/
#define YWMID_DIBMP_OUTPUT_MODE_CLIP                   0x00003000      /*�ü�*/
#define YWMID_DIBMP_OUTPUT_MODE_AUTOZOOM                0x00004000      /*�Զ�����*/
#define YWMID_DIBMP_OUTPUT_MODE_MASK                 0x00007000

/*��ת*/
#define YWMID_DIBMP_OUTPUT_ROTATE_90                  0x00010000  /*˳ʱ����ת90��*/
#define YWMID_DIBMP_OUTPUT_ROTATE_180                0x00020000  /*˳ʱ����ת180��*/
#define YWMID_DIBMP_OUTPUT_ROTATE_270                0x00030000   /*˳ʱ����ת270��*/
#define YWMID_DIBMP_OUTPUT_ROTATE_MASK           0x00030000

/*ˮƽ��ֱ��ת, ע��:����ͬʱˮƽ�ʹ�ֱ��ת,
    YWMID_DIBMP_OUTPUT_HFLIP|YWMID_DIBMP_OUTPUT_VFLIP����,
    ����ת�ͷ�ת���е�ʱ��,����ת��ת*/
#define YWMID_DIBMP_OUTPUT_HFLIP                             0x00040000  /*ˮƽ��ת*/
#define YWMID_DIBMP_OUTPUT_VFLIP                             0x00080000  /*��ֱ��ת*/
#define YWMID_DIBMP_OUTPUT_FLIP_MASK                  0x000C0000

/*YWMID_DIBMP_COPY_BMPDATA:
   ����BMP����,������ܱ�֤��ͼʱ   bmp���ݻ����ڣ�
   ����ϸ�ѡ������ͼʱ��ȷ�����ݻ�����
   �Ͳ�Ҫ�ӣ���ʡ�ڴ�*/
#define YWMID_DIBMP_COPY_BMPDATA                0x80000000

typedef struct YWMID_Rect_s
{
    S32 X;
    S32 Y;
    U32 W;
    U32 H;
}YWMID_Rect_T;

typedef struct YWMID_Palette_s
{
    U8      Alpha;
    U8      Red;
    U8      Green;
    U8      Blue;
} YWMID_Palette_T;

//YWGUI_Dibitmap_T: �豸�޹�λͼ�ṹ

/*modefied by sly, 2009-11-4, λͼ��Ϣ�����ݺͶ����ݵĲ������,�����ݺͲ�������*/
typedef struct YWMID_DibitmapData_s
{
    U32  Flags;

    /**ɫ��:1/4/8/16/24/32 */
    U8 Depth;

    /** The alpha channel value. */
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

    /*Bits ���ֽ�����ʾ��λͼ���ݵĴ�С*/
    U32 Bytes;

    //ָ��λͼ����ʹ��ʱ����ÿ�����ֽ����������������ͣ�
    const void* pData;
} YWMID_DibitmapData_T;
typedef struct YWMID_DibitmapOp_s
{
    U32  Flags;
    YWMID_Rect_T SrcRect; /*x, y,w,h����ԭʼλͼ�ϵĲü�*/
    YWMID_Rect_T DstRect; /*x,y ��ͼ���������������ƫ��*/
} YWMID_DibitmapOp_T;

/*end of modify*/


/*���ģ����Ҫʹ�ã����ڹ����ĵط�*/
typedef enum
{
    YWMID_STREAMTYPE_INVALID =  0, /* None  : Invalid type      */
    YWMID_STREAMTYPE_MP1V    =  1, /* Video : MPEG1             */
    YWMID_STREAMTYPE_MP2V    =  2, /* Video : MPEG2             */
    YWMID_STREAMTYPE_MP4V    =  3, /* Video : H264              */
    YWMID_STREAMTYPE_MP1A    =  4, /* Audio : MPEG 1 Layer I    */
    YWMID_STREAMTYPE_MP2A    =  5, /* Audio : MPEG 1 Layer II   */
    YWMID_STREAMTYPE_MP4A    =  6, /* Audio : like HEAAC,Decoder LOAS / LATM - AAC */
    YWMID_STREAMTYPE_PESTTXT        =  7, /* Teletext : Teletext pid                         */
    YWMID_STREAMTYPE_PESSUBTITLE    =  8, /* Subtitle : Subtitle pid                         */
    YWMID_STREAMTYPE_PCR     =  9, /* Synchro  : PCR pid  */
    YWMID_STREAMTYPE_AC3     = 10, /* Audio : AC3       */
    YWMID_STREAMTYPE_H264    = 11, /* Video : H264                */
    YWMID_STREAMTYPE_MPEG4P2 = 12, /* Video : MPEG4 Part II          */
    YWMID_STREAMTYPE_VC1     = 13, /* Video : Decode Simple/Main/Advanced profile */
    YWMID_STREAMTYPE_AAC     = 14, /* Audio : Decode ADTS - AAC      */
    YWMID_STREAMTYPE_HEAAC   = 15, /* Audio : Decoder LOAS / LATM - AAC  */
    YWMID_STREAMTYPE_WMA     = 16, /* Audio : WMA,WMAPRO        */
    YWMID_STREAMTYPE_DDPLUS  = 17, /* Audio : DD+ Dolby digital      */
    YWMID_STREAMTYPE_DTS     = 18, /* Audio : DTS               */
    YWMID_STREAMTYPE_MMV     = 19, /* Video : Multimedia content  */
    YWMID_STREAMTYPE_MMA     = 20, /* Audio : Multimedia content */
    YWMID_STREAMTYPE_AVS            = 21, /* Video : AVS Video format     */
    YWMID_STREAMTYPE_MP1A_AD        =  22,/* AudioDes : MPEG 1 Layer I                       */
    YWMID_STREAMTYPE_MP2A_AD        =  23,/* AudioDes : MPEG 1 Layer II                      */
    YWMID_STREAMTYPE_AC3_AD         =  24,/* AudioDes : AC3                                  */
    YWMID_STREAMTYPE_HEAAC_AD       =  25,/* AudioDes : HEAAC                                */


    YWMID_STREAMTYPE_LPCM       =  26, /* Audio    : LPCM                                 */
    YWMID_STREAMTYPE_MP1A_AUX   =  27, /* AuxAudio : MPEG 1 Layer I                       */
    YWMID_STREAMTYPE_MP2A_AUX   =  28, /* AuxAudio : MPEG 1 Layer II                      */
    YWMID_STREAMTYPE_MP4A_AUX   =  29, /* AuxAudio : like HEAAC,Decoder LOAS / LATM - AAC */
    YWMID_STREAMTYPE_AC3_AUX    =  30, /* AuxAudio : AC3                                  */
    YWMID_STREAMTYPE_AAC_AUX    =  31, /* AuxAudio : Decode ADTS - AAC                    */
    YWMID_STREAMTYPE_HEAAC_AUX  =  32, /* AuxAudio : Decoder LOAS / LATM - AAC            */
    YWMID_STREAMTYPE_WMA_AUX    =  33, /* AuxAudio : WMA,WMAPRO                           */
    YWMID_STREAMTYPE_DDPLUS_AUX =  34, /* AuxAudio : DD+ Dolby digital                    */
    YWMID_STREAMTYPE_DTS_AUX    =  35, /* AuxAudio : DTS                                  */
    YWMID_STREAMTYPE_LPCM_AUX   =  36, /* AuxAudio : LPCM                                 */

    YWMID_STREAMTYPE_SECTION        = 243, /* Section : Section content */
    YWMID_STREAMTYPE_PES            = 244, /* PES : PES content */
    YWMID_STREAMTYPE_PESMP2V        = 245, /* PES : PES mpeg 2 content */
    YWMID_STREAMTYPE_PESMP1A        = 246, /* PES : PES mpeg 2 content */
    YWMID_STREAMTYPE_ESMP2V         = 247, /* ES : ES mpeg 2 content */
    YWMID_STREAMTYPE_ESMP1A         = 248, /* ES : ES mpeg 2 content */
    YWMID_STREAMTYPE_DVBSUBTITLE    = 249, /* SUBTITLE : DVB SUBTITLE format     */
    YWMID_STREAMTYPE_DVDSUBTITLE    = 250, /* SUBTITLE : DVD SUBTITLE format     */
    YWMID_STREAMTYPE_TEXT           = 251, /* SUBTITLE : Text SUBTITLE format     */
    YWMID_STREAMTYPE_XSUB           = 252, /* SUBTITLE : Text SUB SUBTITLE format     */
    YWMID_STREAMTYPE_SSA            = 253, /* SUBTITLE : SSA SUBTITLE format     */
    YWMID_STREAMTYPE_MOV_TEXT       = 254, /* SUBTITLE : MOV_TEXT SUBTITLE format     */
    YWMID_STREAMTYPE_BDPGS              = 255,
    YWMID_STREAMTYPE_H263    = 256, /* Video : H263                */
    YWMID_STREAMTYPE_VP8    = 257,/* video : VP8  */
    YWMID_STREAMTYPE_MP3    = 258,/* Audio : MPEG 1 Layer III   */
    YWMID_STREAMTYPE_VORBIS    = 259,    
    YWMID_STREAMTYPE_OTHER   = 65535, /* Misc  : Non identified pid */
} YWMID_StreamType_T;

typedef enum YWMID_ContainerType_e
{
    YWMID_CONTAINERTYPE_INVALID, // 0
    YWMID_CONTAINERTYPE_AVI,
    YWMID_CONTAINERTYPE_ASF,
    YWMID_CONTAINERTYPE_MOV,	  	/* Include MP4 */
    YWMID_CONTAINERTYPE_MPEG,
    YWMID_CONTAINERTYPE_MPEGTS,	 //5
    YWMID_CONTAINERTYPE_MPEGVIDEO,
    YWMID_CONTAINERTYPE_FLV,
    YWMID_CONTAINERTYPE_MP3,
    YWMID_CONTAINERTYPE_WAV,
    YWMID_CONTAINERTYPE_LPCM,
    YWMID_CONTAINERTYPE_CDXA, // fix codex 49958
    YWMID_CONTAINERTYPE_MP4,
    YWMID_CONTAINERTYPE_WEBM,
    YWMID_CONTAINERTYPE_3GP,
    YWMID_CONTAINERTYPE_OTHER
} YWMID_ContainerType_T;

typedef enum YWMID_BitmapType_s
{
    YWMID_BITMAP_BMP,
    YWMID_BITMAP_PCX,
    YWMID_BITMAP_TGA,
    YWMID_BITMAP_GIF,
    YWMID_BITMAP_JPG,
    YWMID_BITMAP_JPEG,
    YWMID_BITMAP_PNG,
    YWMID_BITMAP_ICO,
    YWMID_BITMAP_CUR,
    YWMID_BITMAP_TIF,
    YWMID_BITMAP_PBM,
    YWMID_BITMAP_PGM,
    YWMID_BITMAP_PPM,
    YWMID_BITMAP_PNM,
    YWMID_BITMAP_NUMS,
} YWMID_BitmapType_T;
#endif

