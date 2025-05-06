/**********************************文件头部注释************************************


                      Copyright (C), 2005-2010,


 文件名：      ywgui_wrap.c

 创建者：      Roger

 创建时间：    2008.8.22

 文件描述：   1)此文件存放的是 ywgui在yw平台下运行时，为支持平台差异需要实现的一些函数
              2)支持win32虚拟运行环境的类似文件是win32.c

 修改记录：   日       期      作      者       版本      修定
               ---------       -----------      -----     -----

*****************************************************************************************/

/************************************文件包含****************************************/
#include "ywdefs.h"
#include "ywos.h"
#include "ywlib.h"
#include "ywmid.h"

#include "ywgui_common.h"
#include "ywgui_list.h"
#include "ywgui_blockheap.h"
#include "ywgui_cliprect.h"
#include "ywgui_gdi.h"
#include "ywgui_internals.h"
#include "ywgui_desktop.h"

#include "directfb.h"

#ifdef YWGUI_ENABLE_TIMER
#include"ywevt.h"
#include"ywtimer_ext.h"
#endif

/*************************************************************************
* Function name:   YWMID_BmpDeasilRotate90Degrees
* Description:
* 1.  函数实现图片位图数据旋转的功能, 顺时针旋转90 度
* 2.  转换后的数据保存在 pRotateResult 指向的空间
* Input:
*  1.  U8* pRotateResult       转换后的数据存放指针
*  2.  U8* pRotateOriginal     转换前的数据存放指针
*  3.  U8 uBytesPerPixel      每个像素所占用的字节数,即位值除以8
*  4.  U32 uOriginalWidth   原始图片的宽度
*  5.  U32 uOriginalHeight  原始图片的高度
*  6.  U32 uOriginalPitch    每个扫描行的字节
*  7.  U32 uResultPitch    每个扫描行的字节
* return:  S32
**************************************************************************/
#define  YWMID_BmpDeasilRotate90Degrees( pRotateResult,  pRotateOriginal, uBytesPerPixel, uOriginalWidth, uOriginalHeight,uOriginalPitch, uResultPitch)\
{\
    S32 nWidthIndex;\
    S32 nDstIndex;\
    for( nWidthIndex=0; nWidthIndex<uOriginalWidth; nWidthIndex++ )\
    {\
    	for( nDstIndex=0; nDstIndex<uOriginalHeight; nDstIndex++ )\
    	{\
            YWLIB_Memcpy( (void*)((U8*)pRotateResult + nWidthIndex*uResultPitch + nDstIndex*uBytesPerPixel ),\
                        (void*)((U8*)pRotateOriginal + (uOriginalHeight-1-nDstIndex)*uOriginalPitch + nWidthIndex*uBytesPerPixel),\
                        uBytesPerPixel);\
    	}\
    }\
}

/*************************************************************************
* Function name:   YWMID_BmpDeasilRotate180Degrees
* Description:
* 1.  函数实现图片位图数据旋转的功能, 顺时针旋转180 度
* 2.  转换后的数据保存在 pRotateResult 指向的空间
* Input:
*  1.  U8* pRotateResult       转换后的数据存放指针
*  2.  U8* pRotateOriginal     转换前的数据存放指针
*  3.  U8 uBytesPerPixel      每个像素所占用的字节数,即位值除以8
*  4.  U32 uOriginalWidth   原始图片的宽度
*  5.  U32 uOriginalHeight  原始图片的高度
*  6.  U32 uOriginalPitch    每个扫描行的字节数
**************************************************************************/
#define YWMID_BmpDeasilRotate180Degrees(pRotateResult, pRotateOriginal,uBytesPerPixel, uOriginalWidth, uOriginalHeight, uOriginalPitch )\
{\
    S32 nHeightIndex, nWidthIndex;\
    U8 * pucRotSrc;\
    U8 * pucRotDst;\
    U8 * pRotSrcTemp;\
    U8 * pRotDstTemp;\
    U32 nBmpPitch  =  uOriginalPitch;\
    U32 uValidDataPerLine = uOriginalWidth*uBytesPerPixel;\
    pucRotDst = (U8*)pRotateResult;\
    pucRotSrc = (U8*)pRotateOriginal+(uOriginalHeight-1)*nBmpPitch+ uValidDataPerLine-uBytesPerPixel;\
    for( nHeightIndex=0; nHeightIndex<uOriginalHeight; nHeightIndex++)\
    {\
        pRotSrcTemp = pucRotSrc;\
        pRotDstTemp = pucRotDst;\
     	for (nWidthIndex=0; nWidthIndex< uOriginalWidth; nWidthIndex++)\
     	{\
            YWLIB_Memcpy(pRotDstTemp, pRotSrcTemp, uBytesPerPixel);\
            pRotDstTemp += uBytesPerPixel;\
            pRotSrcTemp -= uBytesPerPixel;\
     	}\
        pucRotSrc -= nBmpPitch;\
        pucRotDst += nBmpPitch;\
    }\
}
/*************************************************************************
* Function name:   YWMID_BmpDeasilRotate270Degrees
* Description:
* 1.  函数实现图片位图数据旋转的功能, 顺时针旋转90 度
* 2.  转换后的数据保存在 pRotateResult 指向的空间
* Input:
*  1.  U8* pRotateResult       转换后的数据存放指针
*  2.  U8* pRotateOriginal     转换前的数据存放指针
*  3.  U8 uBytesPerPixel      每个像素所占用的字节数,即位值除以8
*  4.  U32 uOriginalWidth   原始图片的宽度
*  5.  U32 uOriginalHeight  原始图片的高度
*  6.  U32 uOriginalPitch    每个扫描行的字节数
*  7.  U32 uResultPitch    每个扫描行的字节
**************************************************************************/
#define YWMID_BmpDeasilRotate270Degrees( pRotateResult, pRotateOriginal,uBytesPerPixel, uOriginalWidth, uOriginalHeight, uOriginalPitch, uResultPitch)\
{\
    S32 nWidthIndex, nHeightIndex;\
    for( nWidthIndex=0; nWidthIndex<uOriginalWidth; nWidthIndex++ )\
    {\
        for( nHeightIndex=0; nHeightIndex<uOriginalHeight; nHeightIndex++ )\
        {\
            YWLIB_Memcpy( (void*)((U8*)pRotateResult + nWidthIndex*uResultPitch + nHeightIndex*uBytesPerPixel),\
                        (void*)((U8*) pRotateOriginal + (1+nHeightIndex)*uOriginalPitch -(nWidthIndex+1)*uBytesPerPixel -(uOriginalPitch-uOriginalWidth*uBytesPerPixel)),\
                        uBytesPerPixel);\
        }\
    }\
}

/*************************************************************************
* Function name:   YWMID_BmpHFlip
* Description:
* 1.  函数实现图片位图数据水平翻转的功能
* 2.  转换后的数据保存在 pRotateResult 指向的空间
* Input:
*  1.  U8* pRotateResult       转换后的数据存放指针
*  2.  U8* pRotateOriginal     转换前的数据存放指针
*  3.  U8 uBytesPerPixel      每个像素所占用的字节数,即位值除以8
*  4.  U32 uOriginalWidth   原始图片的宽度
*  5.  U32 uOriginalHeight  原始图片的高度
*  6.  U32 uOriginalPitch    每个扫描行的字节数
**************************************************************************/
#define YWMID_BmpHFlip( pRotateResult, pRotateOriginal, uBytesPerPixel, uOriginalWidth, uOriginalHeight , uOriginalPitch)\
{\
    S32 nHeightIndex, nWidthIndex;\
    U8 * pucRotSrc;\
    U8 * pucRotDst;\
    U8 * pRotSrcTemp;\
    U8 * pRotDstTemp;\
    U32 nBmpPitch  =  uOriginalPitch;\
    U32 uValidDataPerLine = uOriginalWidth*uBytesPerPixel;\
    pucRotDst = (U8*)pRotateResult;\
    pucRotSrc = (U8*)pRotateOriginal+uValidDataPerLine-uBytesPerPixel;\
    for( nHeightIndex=0; nHeightIndex<uOriginalHeight; nHeightIndex++)\
    {\
        pRotSrcTemp = pucRotSrc;\
        pRotDstTemp = pucRotDst;\
        for (nWidthIndex=0; nWidthIndex< uOriginalWidth; nWidthIndex++)\
        {\
            YWLIB_Memcpy(pRotDstTemp, pRotSrcTemp, uBytesPerPixel);\
            pRotDstTemp += uBytesPerPixel;\
            pRotSrcTemp -= uBytesPerPixel;\
        }\
        pucRotSrc += nBmpPitch;\
        pucRotDst += nBmpPitch;\
    }\
}


/*************************************************************************
* Function name:   YWMID_BmpVFlip
* Description:
* 1.  函数实现图片位图数据垂直翻转的功能
* 2.  转换后的数据保存在 pRotateResult 指向的空间
* Input:
*  1.  U8* pRotateResult       转换后的数据存放指针
*  2.  U8* pRotateOriginal     转换前的数据存放指针
*  3.  U8 uBytesPerPixel      每个像素所占用的字节数,即位值除以8
*  4.  U32 uOriginalWidth   原始图片的宽度
*  5.  U32 uOriginalHeight  原始图片的高度
*  6.  U32 uOriginalPitch    每个扫描行的字节数
**************************************************************************/
#define YWMID_BmpVFlip( pRotateResult, pRotateOriginal, uBytesPerPixel, uOriginalWidth, uOriginalHeight, uOriginalPitch )\
{\
    S32 nHeightIndex;\
    U8 * pucRotSrc;\
    U8 * pucRotDst;\
    U32 nBmpPitch  =  uOriginalPitch;\
    U32 uValidDataPerLine = uOriginalWidth*uBytesPerPixel;\
    pucRotDst = (U8*)pRotateResult;\
    pucRotSrc = (U8*)pRotateOriginal+(uOriginalHeight-1)*nBmpPitch;\
    for( nHeightIndex=0; nHeightIndex<uOriginalHeight; nHeightIndex++)\
    {\
        YWLIB_Memcpy(pucRotDst,pucRotSrc, uValidDataPerLine);\
        pucRotDst += nBmpPitch;\
        pucRotSrc -= nBmpPitch;\
    }\
}

#define YWMID_PIX2BYTES(n)    (((n)+7)/8)
#define YWMID_BmpComputePitch( BitPerPixel,  BmpWidth, pitchOut)\
{\
    S32 linesize;\
    if(BitPerPixel == 1)\
        linesize = YWMID_PIX2BYTES (BmpWidth);\
    else if(BitPerPixel <= 4)\
        linesize = YWMID_PIX2BYTES (BmpWidth << 2);\
    else if (BitPerPixel <= 8)\
        linesize = BmpWidth;\
    else if(BitPerPixel <= 16) \
    {\
        linesize = BmpWidth * 2;\
    }\
    else if(BitPerPixel <= 24) \
    {\
        linesize = BmpWidth * 3;\
    }\
    else \
    {\
        linesize = BmpWidth * 4;\
    }\
    pitchOut = (linesize + 3) & -4;\
}


/************************************宏定义*******************************************/
//#define _YWGUI_TRACE_WRAP_
//#define  YWPIE 3.14159265358979323846

#define DFBCHECK(x...)                                         \
{                                                            \
    DFBResult err = x;                                         \
                                                           \
    if (err != DFB_OK)                                         \
    {                                                        \
        fprintf( stderr, "%s <%d>:\n\t", __FILE__, __LINE__ ); \
        DirectFBErrorFatal( #x, err );                         \
    }                                                        \
}


#ifdef _YWGUI_TRACE_WRAP_
//#define YWGUI_WRAP_DBGINFO          YWGUI_DBGINFO
#else
//#define YWGUI_WRAP_DBGINFO(x)
#endif

#define Wrap_LockSurface(pSurface)      YWGUI_SemaWait((pSurface)->lock)
#define Wrap_UnlockSurface(pSurface)    YWGUI_SemaSend((pSurface)->lock)

#define WRAP_DEFAULT_PIXEL_TYPE         YWGUI_PIXEL_TYPE_BGR888

#define YWGUI_REPEAT_SPEED                       (50)

/************************************常量定义****************************************/
#define WRAP_SURFACE_NUM            2
#define WRAP_VISIBLE_SURFACE        0
#define WRAP_INVISIBLE_SURFACE      1

#define DEF_NR_TIMERS               32

#define TIMER_EVENT_BEGIN_ID        0xa300

/************************************类型定义*******************************************/
typedef struct WrapSurface_s
{
    YWGUI_SemaID_T lock;
    YWGUI_Handle_T hLayer;
    BOOL bIsVisible;
    S32 count;
    IDirectFBSurface * pstDfbSurface;
}WrapSurface_T;

typedef struct WrapKeyMsg_s
{
    YWGUI_SemaID_T lock;
    U32 message;
    U32 scan_code;
    U32 lparam;
    BOOL bHaveData;
}WrapKeyMsg_T;

typedef struct WrapInfo_s
{
    YWGUI_SemaID_T lock;
    YWGUI_SemaID_T sinkWake;
    YWGUI_Handle_T hVisibleLayer;
    YWGUI_Handle_T hInvisibleLayer; //Rogertest
    YWGUI_Handle_T hPanel;
    BOOL           bStartAcceptKey;
    BOOL           bTimerTrigger[DEF_NR_TIMERS];
    WrapSurface_T *ptSurface[WRAP_SURFACE_NUM];
    IDirectFB * pstDfb;
    //IDirectFBDisplayLayer * pstDspLayer;
    //IDirectFBWindow     * pstWindow;
    IDirectFBEventBuffer * pstEventBuf;
}WrapInfo_T;

static WrapInfo_T    g_tWrapInfo;
static WrapSurface_T g_tWrapSurface[WRAP_SURFACE_NUM];
static WrapKeyMsg_T  g_tWrapKeyMsg;
static YWGUI_ThreadID_T  ywKeyScanThreadID;

/************************************变量定义****************************************/


/************************************变量引用****************************************/



/************************************函数引用****************************************/



/************************************内部函数****************************************/
/*added by sly, 2009-11-3*/

static DFBSurfaceBlittingFlags YWGUI_WrapReviseOpMode(YWGUI_CANVAS_OpMode_T OpMode)
{
    DFBSurfaceBlittingFlags CanvasOpMode;
    switch(OpMode)
    {
        case  YWGUI_CANVAS_OP_MODE_NORMAL:
            CanvasOpMode = DSBLIT_NOFX;
            break;
        case  YWGUI_CANVAS_OP_MODE_XOR :
            CanvasOpMode = DSBLIT_XOR;
            break;
        case  YWGUI_CANVAS_OP_MODE_COLORKEY:
            CanvasOpMode = DSBLIT_SRC_COLORKEY;
            break;
        case  YWGUI_CANVAS_OP_MODE_ALPHA:
            CanvasOpMode = DSBLIT_BLEND_ALPHACHANNEL;
            break;

        default :
            CanvasOpMode = DSBLIT_NOFX;
            break;
    }
    return CanvasOpMode;
}

/*end of added*/
static BOOL YWGUI_WrapSurfaceIsValid(YWGUI_HSurface_T  hSurface)
{
    WrapSurface_T * ptSurface = (WrapSurface_T *)hSurface;
    BOOL bRet= TRUE;

    if(ptSurface==NULL)
    {
        return FALSE;
    }

    Wrap_LockSurface(ptSurface);
    if(ptSurface->count<=0 || ptSurface->hLayer==(YWGUI_Handle_T)0)
    {
        bRet = FALSE;
    }
    Wrap_UnlockSurface(ptSurface);

    return bRet;
}
static YWGUI_Handle_T YWGUI_WrapGetSurfaceLayer(YWGUI_HSurface_T  hSurface)
{
    WrapSurface_T * ptSurface = (WrapSurface_T *)hSurface;
    YWGUI_Handle_T hLayer=(YWGUI_Handle_T)0;

    if(ptSurface==NULL)
    {
        return hLayer;
    }

    Wrap_LockSurface(ptSurface);
    hLayer= ptSurface->hLayer;
    Wrap_UnlockSurface(ptSurface);

    return hLayer;
}

static YWGUI_PixelType_E YWGUI_WrapGetOsdLayerPixelType(YWGUI_Handle_T hLayer)
{
    DFBSurfacePixelFormat PixelFormat;
    YW_ErrorType_T errCode=YW_NO_ERROR;
    IDirectFBSurface  * pSurface = (IDirectFBSurface * )hLayer;

    YWGUI_MemSet(&PixelFormat,0,sizeof(DFBSurfacePixelFormat));

    //errCode = YWCANVAS_GetPixelFormat(hLayer,&PixelFormat);
    DFBCHECK( pSurface->GetPixelFormat(pSurface, &PixelFormat));
    if(errCode!=YW_NO_ERROR)
    {
        YWMID_Trace((YWOS_TRACE_ERROR,"[GetOsdLayerPixelType] YWCANVAS_GetPixelFormat failure,return!error code=%#x\n",errCode));
        return YWGUI_PIXEL_TYPE_INVALID;
    }

    switch(PixelFormat)
    {
        case DSPF_RGB24:
            return YWGUI_PIXEL_TYPE_BGR888;

        case DSPF_ARGB:
            return YWGUI_PIXEL_TYPE_BGRA8888;

        case DSPF_ARGB1555:
            return YWGUI_PIXEL_TYPE_BGRA5551;

        case DSPF_RGB555:
            return YWGUI_PIXEL_TYPE_BGR565;

        case DSPF_ARGB4444:
            return YWGUI_PIXEL_TYPE_BGRA4444;
        default:
            break;
    }

    return YWGUI_PIXEL_TYPE_INVALID;
}


static BOOL YWGUI_WrapIsNeedConvDibData(const YWMID_DibitmapData_T * ptDibmp,YWGUI_HSurface_T hSurface)
{
    YWGUI_PixelType_E     ePixelType=YWGUI_PIXEL_TYPE_INVALID;


    if((ptDibmp->Flags & YWMID_DIBMP_FLOW_MASK) !=YWMID_DIBMP_FLOW_DOWN)
    {
        return TRUE;
    }
    if((ptDibmp->Flags & YWMID_DIBMP_COMPRESS_MASK) !=YWMID_DIBMP_COMPRESS_NO)
    {
        YWMID_ASSERT((0));
        return TRUE;
    }
    #if 0//delete by sly, 2010-03-15
    if(ptDibmp->pPalette!=NULL && ptDibmp->PaletteColors>0)
    {
        //使用了私有调色板
        return TRUE;
    }

    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[IsNeedConvDibData] Surface is invalid,return!\n"));
        YWMID_ASSERT((0));
        return FALSE;
    }

    ePixelType = YWGUI_WrapGetOsdLayerPixelType(YWGUI_WrapGetSurfaceLayer(hSurface));
    switch(ePixelType)
    {
        case YWGUI_PIXEL_TYPE_RGB888:
            if((ptDibmp->Flags & YWMID_DIBMP_FORMAT_MASK)!=YWMID_DIBMP_FORMAT_RGB_888 ||
                (ptDibmp->Flags & YWMID_DIBMP_SIZE_MASK)!=YWMID_DIBMP_SIZE_3)
            {
                return TRUE;
            }
            break;
        case YWGUI_PIXEL_TYPE_BGR888:
            if((ptDibmp->Flags & YWMID_DIBMP_FORMAT_MASK)!=YWMID_DIBMP_FORMAT_BGR_888 ||
                (ptDibmp->Flags & YWMID_DIBMP_SIZE_MASK)!=YWMID_DIBMP_SIZE_3)
            {
                return TRUE;
            }
            break;
        case YWGUI_PIXEL_TYPE_BGRA8888:
             if((ptDibmp->Flags & YWMID_DIBMP_FORMAT_MASK)!=YWMID_DIBMP_FORMAT_BGRA_8888 ||
                (ptDibmp->Flags & YWMID_DIBMP_SIZE_MASK)!=YWMID_DIBMP_SIZE_4)
            {
                return TRUE;
            }
            break;
        default:
            YWMID_Trace((YWOS_TRACE_ERROR,"[IsNeedConvDibData] ePixelType is invalid(=%d)!\n",ePixelType));
            YWMID_ASSERT((0));
            break;
    }
    #else/*这里不转，利用硬件来转*/
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[IsNeedConvDibData] Surface is invalid,return!\n"));
        YWMID_ASSERT((0));
        return FALSE;
    }

    ePixelType = YWGUI_WrapGetOsdLayerPixelType(YWGUI_WrapGetSurfaceLayer(hSurface));
    switch(ePixelType)
    {
        case YWGUI_PIXEL_TYPE_RGB888:
            switch((ptDibmp->Flags & YWMID_DIBMP_FORMAT_MASK))
            {
                case YWMID_DIBMP_FORMAT_RGB_888:
                case YWMID_DIBMP_FORMAT_ARGB_8888:
                    break;
                default:
                    return TRUE;
            }
            break;
        case YWGUI_PIXEL_TYPE_BGR888:
            switch((ptDibmp->Flags & YWMID_DIBMP_FORMAT_MASK))
            {
                case YWMID_DIBMP_FORMAT_BGR_888:
                case YWMID_DIBMP_FORMAT_BGRA_8888:
                case YWMID_DIBMP_FORMAT_CLUT_8:
                case YWMID_DIBMP_FORMAT_BGR_565:
                case YWMID_DIBMP_FORMAT_BGRA_4444:
                case YWMID_DIBMP_FORMAT_BGRA_5551:
                    break;
                default:
                    return TRUE;
            }
            break;
        case YWGUI_PIXEL_TYPE_BGRA8888:
            switch((ptDibmp->Flags & YWMID_DIBMP_FORMAT_MASK))
            {
                case YWMID_DIBMP_FORMAT_BGR_888:
                case YWMID_DIBMP_FORMAT_BGRA_8888:
                case YWMID_DIBMP_FORMAT_CLUT_8:
                case YWMID_DIBMP_FORMAT_BGR_565:
                case YWMID_DIBMP_FORMAT_BGRA_4444:
                case YWMID_DIBMP_FORMAT_BGRA_5551:
                    break;
                default:
                    return TRUE;
            }
            break;
        case YWGUI_PIXEL_TYPE_BGRA5551:
        case YWGUI_PIXEL_TYPE_BGR565:
        case YWGUI_PIXEL_TYPE_BGRA4444:
            switch((ptDibmp->Flags & YWMID_DIBMP_FORMAT_MASK))
            {
                case YWMID_DIBMP_FORMAT_BGR_888:
                case YWMID_DIBMP_FORMAT_BGRA_8888:
                case YWMID_DIBMP_FORMAT_CLUT_8:
                case YWMID_DIBMP_FORMAT_BGR_565:
                case YWMID_DIBMP_FORMAT_BGRA_4444:
                case YWMID_DIBMP_FORMAT_BGRA_5551:
                    break;
                default:
                    return TRUE;
            }
            break;
        default:
            YWMID_Trace((YWOS_TRACE_ERROR,"[IsNeedConvDibData] ePixelType is invalid(=%d)!\n",ePixelType));
            YWMID_ASSERT((0));
            break;
    }
    #endif

    return FALSE;
}




static  U8* YWGUI_WrapSetMemPixel(U8* pMem, U8 bpp, YWGUI_Pixel_T pixel)
{
    U8 *p= (U8*)pixel;
    YWMID_ASSERT(pixel!=NULL);
    YWGUI_MemCpy(pMem,p,bpp);

    return pMem+bpp;
}

static  BOOL YWGUI_WrapGetAcceptKeyStatus()
{
    BOOL bStaus=FALSE;

    YWGUI_SemaWait(g_tWrapInfo.lock);
    bStaus = g_tWrapInfo.bStartAcceptKey;
    YWGUI_SemaSend(g_tWrapInfo.lock);

    return bStaus;
}

#if 0
static void YWGUI_WrapReviseParam(YWCANVAS_OpenParams_T *ptOpenParam,YWGUI_LayerInfo_T* ptLayerInfo)
{
    YWMID_ASSERT((ptOpenParam!=NULL && ptLayerInfo!=NULL));
    YWMID_ASSERT((ptLayerInfo->ePixelType>YWGUI_PIXEL_TYPE_INVALID && ptLayerInfo->ePixelType<YWGUI_PIXEL_TYPE_MAX));
    U8 *p = ptOpenParam->PixelFormat.Colorkey;
    U8 * pValue = (U8*)ptLayerInfo->colorKey;
    switch (ptLayerInfo->ePixelType)
    {
        case YWGUI_PIXEL_TYPE_RGB888:
            YWMID_ASSERT((ptOpenParam->PixelFormat.BitsPerPixel==24));

            ptOpenParam->PixelFormat.ColorType = DSPF_RGB24;
            if(ptLayerInfo->dwFlags & YWGUI_COLORKEY_VALID)
            {
                p[0]=pValue[2];
                p[1]=pValue[1];
                p[2]=pValue[0];
            }
            break;
        case YWGUI_PIXEL_TYPE_BGR888:
            YWMID_ASSERT((ptOpenParam->PixelFormat.BitsPerPixel==24));

            ptOpenParam->PixelFormat.ColorType = DSPF_RGB24;
            if(ptLayerInfo->dwFlags & YWGUI_COLORKEY_VALID)
            {
                p[0]=pValue[0];
                p[1]=pValue[1];
                p[2]=pValue[2];
            }
            break;
        case YWGUI_PIXEL_TYPE_BGRA8888:
            YWMID_ASSERT((ptOpenParam->PixelFormat.BitsPerPixel==32));

            ptOpenParam->PixelFormat.ColorType = DSPF_ARGB;
            if(ptLayerInfo->dwFlags & YWGUI_COLORKEY_VALID)
            {
                p[0]=pValue[0];
                p[1]=pValue[1];
                p[2]=pValue[2];
                p[3]=pValue[3];
            }
            break;

        case YWGUI_PIXEL_TYPE_BGRA5551:
            YWMID_ASSERT((ptOpenParam->PixelFormat.BitsPerPixel==16));

            ptOpenParam->PixelFormat.ColorType = DSPF_ARGB1555;
            if(ptLayerInfo->dwFlags & YWGUI_COLORKEY_VALID)
            {
                p[0]=((pValue[0]>>3)&0x1F)|((pValue[1]<<2)&0xE0);
                p[1]= ((pValue[1]>>6)&0x3)|((pValue[2]>>1)&0x7C);

                if(pValue[3]!=0)/*只要不是全透明就认为是不透明*/
                {
                    p[1]|=0x80;
                }
            }
            break;
        case YWGUI_PIXEL_TYPE_BGR565:
            YWMID_ASSERT((ptOpenParam->PixelFormat.BitsPerPixel==16));

            ptOpenParam->PixelFormat.ColorType = DSPF_RGB555;
            if(ptLayerInfo->dwFlags & YWGUI_COLORKEY_VALID)
            {
                p[0] = ((pValue[0]>>3)&0x1F)|(((pValue[1])<<3)&0xE0);
                p[1] = ((pValue[1]>>5)&0x7)|(pValue[2]&0xF8);
            }
            break;
        case YWGUI_PIXEL_TYPE_BGRA4444:
            YWMID_ASSERT((ptOpenParam->PixelFormat.BitsPerPixel==16));

            ptOpenParam->PixelFormat.ColorType = DSPF_ARGB4444;
            if(ptLayerInfo->dwFlags & YWGUI_COLORKEY_VALID)
            {
                p[0]=((pValue[0]>>4)&0xF)|(pValue[1]&0xF0);
                p[1]=((pValue[2]>>4)&0xF)|(pValue[3]&0xF0);
            }
            break;

        default:
            YWMID_ASSERT((0));
            break;
    }
}
#endif

static void  YWGUI_WrapSetDefLayerInfo(YWGUI_PixelType_E epixelType,YWGUI_LayerInfo_T* ptLayerInfo)
{
    YWMID_ASSERT((ptLayerInfo!=NULL));

    switch(epixelType)
    {
        case YWGUI_PIXEL_TYPE_RGB888:
        case YWGUI_PIXEL_TYPE_BGR888:
            ptLayerInfo->ePixelType=epixelType;
            ptLayerInfo->bitsPerPixel=24;
            ptLayerInfo->left=0;
            ptLayerInfo->top =0;
            ptLayerInfo->width=720;
            ptLayerInfo->height=576;
            //ptLayerInfo->alphaBlendingMode= YWGUI_ALPHA_MODE_LOCAL;
            ptLayerInfo->transparence = 0xFF;
            ptLayerInfo->dwFlags = YWGUI_HARDWARE_ACCEL |YWGUI_ANTI_FLICKER;
            break;
        default:
            YWMID_ASSERT((0));
            break;
    }
}

static WrapSurface_T* YWGUI_WrapGetSurfaceByIndex(U8 index)
{
    WrapSurface_T*pSurface;

    YWMID_ASSERT((index<WRAP_SURFACE_NUM));

    YWGUI_SemaWait(g_tWrapInfo.lock);
    pSurface = g_tWrapInfo.ptSurface[index];
    YWGUI_SemaSend(g_tWrapInfo.lock);

    return pSurface;
}

static void YWGUI_WrapSetSurfaceByIndex(U8 index,WrapSurface_T* ptSurface)
{
    YWMID_ASSERT((index<WRAP_SURFACE_NUM));

    YWGUI_SemaWait(g_tWrapInfo.lock);
    g_tWrapInfo.ptSurface[index] = ptSurface;
    YWGUI_SemaSend(g_tWrapInfo.lock);
}


void YWGUI_WrapSinkWake()
{
    S32 sem_value=0;

    YWGUI_GetSemaVal(g_tWrapInfo.sinkWake, &sem_value);

    if (sem_value <= 0)
    {
        YWGUI_SemaSend(g_tWrapInfo.sinkWake);
    }
}



static void YWGUI_WrapSetTimerTrigger(S32 slot)
{
    YWGUI_SemaWait(g_tWrapInfo.lock);
    g_tWrapInfo.bTimerTrigger[slot] = TRUE;
    YWGUI_SemaSend(g_tWrapInfo.lock);

    YWGUI_WrapSinkWake();
}

/*添加了前面板的配置参数,modified by sly, 2009-7-17*/
static BOOL YWGUI_WrapRegisterPanel(YWGUI_Handle_T hPanel,
                                                                                                U8  uRemoteNum,
                                                                                                const YWGUI_KeyboardParams_T* ptRemoteParamHead,
                                                                                                const YWGUI_FrontPanelParams_T* ptFrontPanelParam,
                                                                                                YWGUI_LbdParams_T * ptLbdParam)
{
    return TRUE;
}

BOOL  YWGUI_WrapAddEqupment(YWGUI_PanelEquipmentList_T* pstEquList)
{
    return TRUE;
}
BOOL  YWGUI_WrapDeleteEquiment(YWGUI_PanelEquipmentList_T* pstEquList)
{
    return TRUE;
}
BOOL YWGUI_WrapPanelGetFeature(YWGUI_PanelFeature_T* pstFeature)
{
    return TRUE;
}
BOOL YWGUI_WrapPanelGetLoopState(BOOL *bLoop)
{
    return TRUE;
}
BOOL YWGUI_WrapPanelSetLoopState(BOOL  bLoop)
{
    return TRUE;
}
BOOL YWGUI_WrapSetPanelLEDStr(U8* pcLEDStr, U16 uStrLen)
{

    return TRUE;
}

BOOL YWGUI_WrapDispPanelLEDStr(void)
{
    return TRUE;
}


BOOL YWGUI_WrapDispPanelLEDTime(void)
{
    return TRUE;
}

BOOL YWGUI_WrapPanelLEDClear(void)
{
    return TRUE;
}

BOOL YWGUI_WrapSetPanelLBDStatus(YWGUI_PanelLBDType_T  LBDType, YWGUI_PanelLBDStatus_T  eLBDStatus)
{
    return TRUE;
}


BOOL YWGUI_WrapPanelVFDIoControl(YWGUI_PanelVFDIoControlType_T  eIoCtlType, void * pvParam)
{
    return TRUE;
}


BOOL YWGUI_WrapPanelSetStbyKey(YWGUI_PanelStandByKeyParam_T  *ptParam)
{
    return TRUE;
}

BOOL YWGUI_WrapPanelGetStbyKey(YWGUI_PanelStandByKeyParam_T  *ptParam)
{
    return TRUE;
}


BOOL YWGUI_WrapPanelSetBlueKey(YWGUI_PanelBlueKeyParam_T  *ptParam)
{
    return TRUE;
}

BOOL YWGUI_WrapPanelGetBlueKey(YWGUI_PanelBlueKeyParam_T  *ptParam)
{
    return TRUE;
}

BOOL YWGUI_WrapPanelSetVfdStandbyState(BOOL  IsStandby)
{
    return TRUE;
}
BOOL YWGUI_WrapPanelGetVfdStandbyState(BOOL  *IsStandby)
{
    return TRUE;
}

BOOL YWGUI_WrapPanelGetPowerOnState(BOOL  *pIsCheck)
{
    return TRUE;
}


BOOL YWGUI_WrapPanelSetPowerOnState(BOOL  IsCheck)
{
    return TRUE;
}

BOOL YWGUI_WrapPanelGetStartUpState(YWGUI_PanelStartUpStat_T * pstState)
{
    return TRUE;
}
BOOL YWGUI_WrapPanelControlTime(BOOL bStart)
{
    return TRUE;
}

BOOL YWGUI_WrapPanelSetKeyRepeatSpeed(U32 uSpeed)
{
    return TRUE;
}

BOOL YWGUI_WrapRemoteDisable(void)
{
    return TRUE;
}
BOOL YWGUI_WrapRemoteEnable(void)
{
    return TRUE;
}
BOOL YWGUI_WrapFrontPanelDisable(void)
{
    return TRUE;
}
BOOL YWGUI_WrapFrontPanelEnable(void)
{
    return TRUE;
}
/*end of added*/


static YWGUI_Handle_T YWGUI_WrapRegisterOsdLayer(BOOL bVisibled)
{

    YWGUI_Handle_T hOsdLayer;
    //YWCANVAS_OpenParams_T OpenParam;
    YWGUI_LayerInfo_T* ptLayerInfo=NULL;
    YW_ErrorType_T errCode = YW_NO_ERROR;
    YWGUI_Pixel_T aucColorKey = {0};
    int i=0;

    //YWGUI_MemSet(&OpenParam,0,sizeof(OpenParam));
    //OpenParam.OpMode      = YWCANVAS_OP_MODE_NORMAL;
    //OpenParam.CanVisual   = bVisibled;


    ptLayerInfo=YWGUI_TakeoutLayerInfo();
    if((ptLayerInfo->ePixelType<=YWGUI_PIXEL_TYPE_INVALID) ||
        (ptLayerInfo->ePixelType>=YWGUI_PIXEL_TYPE_MAX))
    {
        //无效格式(出于健壮性考虑填默认值)
        YWMID_Trace((YWOS_TRACE_ERROR,"[ERROR][OpenOsdLayer] ePixelType Invalid,set default ePixelType\n"));
        YWGUI_WrapSetDefLayerInfo(WRAP_DEFAULT_PIXEL_TYPE,ptLayerInfo);
    }


    //OpenParam.PixelFormat.BitsPerPixel = ptLayerInfo->bitsPerPixel;
    //OpenParam.PixelFormat.BytesPerPixel= (ptLayerInfo->bitsPerPixel+7)/8;

    #if 0/*delete by sly*/
    OpenParam.VisualRect.Left      = ptLayerInfo->left;
    OpenParam.VisualRect.Top       = ptLayerInfo->top;
    OpenParam.VisualRect.Width     = ptLayerInfo->width;
    OpenParam.VisualRect.Height    = ptLayerInfo->height;
    #endif
    //OpenParam.CanvasRegion.Width   = ptLayerInfo->width;
    //OpenParam.CanvasRegion.Height  = ptLayerInfo->height;
#if 0
    if(NULL == g_tWrapInfo.pstWindow)//
    {
        DFBWindowDescription wdesc;
        wdesc.flags = ( DWDESC_CAPS | DWDESC_SURFACE_CAPS |
                                DWDESC_POSX | DWDESC_POSY |
                                DWDESC_WIDTH | DWDESC_HEIGHT );

        wdesc.caps = DWCAPS_ALPHACHANNEL;
        wdesc.surface_caps = DSCAPS_VIDEOONLY;

        wdesc.posx   = ptLayerInfo->left;
        wdesc.posy   = ptLayerInfo->top;
        wdesc.width  = ptLayerInfo->width;
        wdesc.height = ptLayerInfo->height;
        printf("******************x=%d,y=%d,w=%d,h=%d\n", wdesc.posx, wdesc.posy, wdesc.width, wdesc.height);
        DFBCHECK((g_tWrapInfo.pstDspLayer->CreateWindow(g_tWrapInfo.pstDspLayer, &wdesc, &g_tWrapInfo.pstWindow)));
    }
#endif
    if(bVisibled)
    {
        DFBSurfaceDescription dsc;
        //DFBCHECK((g_tWrapInfo.pstDspLayer->GetSurface(g_tWrapInfo.pstDspLayer, (IDirectFBSurface **)&hOsdLayer)));
        dsc.flags = DSDESC_CAPS|DSDESC_WIDTH |DSDESC_HEIGHT | DSDESC_PIXELFORMAT;
        dsc.caps   = DSCAPS_PRIMARY;
        dsc.width  = 1920;//ptLayerInfo->width;
        dsc.height = 1080;//ptLayerInfo->height;
        dsc.pixelformat = DSPF_ARGB;

        DFBCHECK (g_tWrapInfo.pstDfb->CreateSurface( g_tWrapInfo.pstDfb, &dsc, (IDirectFBSurface **)&hOsdLayer));

    }
    else
    {
        DFBSurfaceDescription dsc;
        IDirectFBSurface * pVisbleSurface = (IDirectFBSurface *)g_tWrapInfo.hVisibleLayer;
        dsc.flags = DSDESC_CAPS|DSDESC_WIDTH |DSDESC_HEIGHT | DSDESC_PIXELFORMAT;

        dsc.caps   = DSCAPS_SYSTEMONLY ;
        dsc.width = /*ptLayerInfo->width*/1920;
        dsc.height = /*ptLayerInfo->height*/1080;
        dsc.pixelformat = DSPF_ARGB;
        //从可见surface获取pixelformat和宽高
        DFBCHECK(pVisbleSurface->GetPixelFormat(pVisbleSurface, &dsc.pixelformat));
        //DFBCHECK(pVisbleSurface->GetSize (pVisbleSurface, &dsc.width, &dsc.height));
        DFBCHECK(g_tWrapInfo.pstDfb->CreateSurface (g_tWrapInfo.pstDfb, &dsc, (IDirectFBSurface **)&hOsdLayer));
    }
    //DFBCHECK((g_tWrapInfo.pstDspLayer->GetSurface(g_tWrapInfo.pstDspLayer, (IDirectFBSurface **)&hOsdLayer)));
    YWGUI_ReturnLayerInfo();
    return hOsdLayer;

}

static BOOL YWGUI_WrapCloseOsdLayer(YWGUI_Handle_T hOsdLayer)
{
    IDirectFBSurface* surface;

    if(hOsdLayer==(YWGUI_Handle_T)0)
    {
        return TRUE;
    }
    surface = (IDirectFBSurface*)hOsdLayer;
    DFBCHECK(surface->Release(surface));
    return TRUE;
}

static void YWGUI_WrapExpandMonoDIBitmap(YWGUI_HDc_T hdc, S32 widthDIB, S32 heightDIB, const U8* bitsDIB,
                             S32 pitchDIB,U32 flag_flow, const YWMID_Palette_T*palDIB, S32 pitchDDB,U8* bitsDDB)
{
    S32  bpp;//每象素字节数
    const U8 *buf;
    S32 y;
    S32 x;
    U8 *dst_line;
    U32 b = 0;
    YWGUI_Pixel_T pixelArray[2];
    //YWGUI_Pixel_T cur_pixel;
    YWGUI_DeviceContext_P pdc=YWGUI_Hdc2Pdc (hdc);

    YWMID_ASSERT((heightDIB>0 && palDIB!=NULL));

    bpp = YWGUI_GetBytesPerPixel (pdc->hSurface);


    //pixelArray[0] = YWGUI_AColorMap2Pixel(pdc->hSurface, YWGUI_MAKE_RGBA(palDIB[0].Alpha,palDIB[0].Red,palDIB[0].Green,palDIB[0].Blue));
    //pixelArray[1] = YWGUI_AColorMap2Pixel(pdc->hSurface,YWGUI_MAKE_RGBA(palDIB[1].Alpha,palDIB[1].Red,palDIB[1].Green,palDIB[1].Blue));

    YWGUI_AColorMap2Pixel(pdc->hSurface, YWGUI_MAKE_RGBA(palDIB[0].Alpha,palDIB[0].Red,palDIB[0].Green,palDIB[0].Blue), pixelArray[0]);
    YWGUI_AColorMap2Pixel(pdc->hSurface,YWGUI_MAKE_RGBA(palDIB[1].Alpha,palDIB[1].Red,palDIB[1].Green,palDIB[1].Blue), pixelArray[1]);

    if (flag_flow == YWMID_DIBMP_FLOW_UP)
    {
        buf = bitsDIB + pitchDIB * (heightDIB-1);//指到最后一行行头
    }
    else
    {
        buf = bitsDIB;
    }

    for (y = 0; y < heightDIB; y++)
    {
        dst_line = bitsDDB;
        bitsDIB = buf;

        for (x = 0; x < widthDIB; x++)
        {
            if (x % 8 == 0)
            {
                b = *bitsDIB++;
            }

            if ((b & (128 >> (x % 8))))
            {
                //cur_pixel = pixelArray[1];
                dst_line=YWGUI_WrapSetMemPixel(dst_line,bpp,pixelArray[1]);
            }
            else
            {
                //cur_pixel = pixelArray[0];
                dst_line=YWGUI_WrapSetMemPixel(dst_line,bpp,pixelArray[0]);
            }

            //dst_line=YWGUI_WrapSetMemPixel(dst_line,bpp,cur_pixel);
        }

        if (flag_flow == YWMID_DIBMP_FLOW_UP)
        {
            buf-=pitchDIB;
        }
        else
        {
            buf +=pitchDIB;
        }

        bitsDDB += pitchDDB;
    }
}
static void YWGUI_WrapExpand16DIBitmap(YWGUI_HDc_T hdc, S32 widthDIB, S32 heightDIB, const U8* bitsDIB,
                             S32 pitchDIB,U32 flag_flow, const YWMID_Palette_T*palDIB, S32 pitchDDB,U8* bitsDDB)
{
    YWGUI_DeviceContext_P pdc=YWGUI_Hdc2Pdc (hdc);
    S32 bpp;
    S32 x;
    S32 y;
    const U8*buf;
    U8* dst_line;
    U32 b = 0;
    //U32 c=0;
    YWGUI_Pixel_T c={0};
    U32 uPalIndex;


    YWMID_ASSERT((heightDIB>0 && palDIB!=NULL));

    bpp = YWGUI_GetBytesPerPixel (pdc->hSurface);

    if (flag_flow == YWMID_DIBMP_FLOW_UP)
    {
        buf = bitsDIB + pitchDIB * (heightDIB-1);//指到最后一行行头
    }
    else
    {
        buf = bitsDIB;
    }


    for (y = 0; y < heightDIB; y++)
    {
        dst_line = bitsDDB;
        bitsDIB = buf;

        for (x = 0; x < widthDIB; x++)
        {
            if (x % 2 == 0)
            {
                b = *bitsDIB++;
            }

            if (x % 2 == 0)
            {
                //c = (b >> 4) & 0x0f;
                uPalIndex = (b >> 4) & 0x0f;
            }
            else
            {
                //c = b & 0x0f;
                uPalIndex = b & 0x0f;
            }

            //c = YWGUI_AColorMap2Pixel(pdc->hSurface,YWGUI_MAKE_RGBA(palDIB[c].Alpha,palDIB[c].Red,palDIB[c].Green,palDIB[c].Blue));
            YWGUI_AColorMap2Pixel(pdc->hSurface,YWGUI_MAKE_RGBA(palDIB[uPalIndex].Alpha,palDIB[uPalIndex].Red,palDIB[uPalIndex].Green,palDIB[uPalIndex].Blue), c);
            dst_line=YWGUI_WrapSetMemPixel(dst_line,bpp,c);
        }

        if (flag_flow == YWMID_DIBMP_FLOW_UP)
        {
            buf-=pitchDIB;
        }
        else
        {
            buf +=pitchDIB;
        }

        bitsDDB += pitchDDB;
    }
}

static void YWGUI_WrapExpand256DIBitmap(YWGUI_HDc_T hdc, S32 widthDIB, S32 heightDIB, const U8* bitsDIB,
                             S32 pitchDIB,U32 flag_flow, const YWMID_Palette_T*palDIB, S32 pitchDDB,U8* bitsDDB)
{
    YWGUI_DeviceContext_P pdc=YWGUI_Hdc2Pdc (hdc);
    S32 bpp;
    S32 x;
    S32 y;
    const U8*buf;
    U8* dst_line;
    //U32 c=0;
    YWGUI_Pixel_T c={0};
    U32 uPalIndex;


    YWMID_ASSERT((heightDIB>0 && palDIB!=NULL));

    bpp = YWGUI_GetBytesPerPixel (pdc->hSurface);

    if (flag_flow == YWMID_DIBMP_FLOW_UP)
    {
        buf = bitsDIB + pitchDIB * (heightDIB-1);//指到最后一行行头
    }
    else
    {
        buf = bitsDIB;
    }


    for (y = 0; y < heightDIB; y++)
    {
        dst_line = bitsDDB;
        bitsDIB = buf;

        for (x = 0; x < widthDIB; x++)
        {
            //c = *bitsDIB++;
            uPalIndex = *bitsDIB++;
            //c = YWGUI_AColorMap2Pixel(pdc->hSurface,YWGUI_MAKE_RGBA(palDIB[c].Alpha,palDIB[c].Red,palDIB[c].Green,palDIB[c].Blue));
            YWGUI_AColorMap2Pixel(pdc->hSurface,YWGUI_MAKE_RGBA(palDIB[uPalIndex].Alpha,palDIB[uPalIndex].Red,palDIB[uPalIndex].Green,palDIB[uPalIndex].Blue), c);
            dst_line=YWGUI_WrapSetMemPixel(dst_line,bpp,c);

        }

        if (flag_flow == YWMID_DIBMP_FLOW_UP)
        {
            buf-=pitchDIB;
        }
        else
        {
            buf +=pitchDIB;
        }

        bitsDDB += pitchDDB;
    }
}

static void YWGUI_WrapRegroup24DIBitmap(YWGUI_HDc_T hdc, S32 widthDIB, S32 heightDIB, const U8* bitsDIB,
                             S32 pitchDIB,U32 flag_flow,U32 flag_type, S32 pitchDDB,U8* bitsDDB)
{
    YWGUI_DeviceContext_P pdc=YWGUI_Hdc2Pdc (hdc);
    S32 bpp;
    S32 x;
    S32 y;
    const U8*buf;
    U8* dst_line;
    YWGUI_Pixel_T  c={0};
    YWGUI_Argb_T     argb;


    YWMID_ASSERT((heightDIB>0));

    bpp = YWGUI_GetBytesPerPixel (pdc->hSurface);

    if (flag_flow == YWMID_DIBMP_FLOW_UP)
    {
        buf = bitsDIB + pitchDIB * (heightDIB-1);//指到最后一行行头
    }
    else
    {
        buf = bitsDIB;
    }

    for (y = 0; y < heightDIB; y++)
    {
        dst_line = bitsDDB;
        bitsDIB = buf;

        for (x = 0; x < widthDIB; x++)
        {
            if (flag_type == YWMID_DIBMP_FORMAT_BGR_888)
            {
                argb.b= *bitsDIB++;
                argb.g= *bitsDIB++;
                argb.r= *bitsDIB++;
            }
            else
            {
                YWMID_ASSERT((flag_type == YWMID_DIBMP_FORMAT_RGB_888));
                argb.r = *bitsDIB++;
                argb.g = *bitsDIB++;
                argb.b= *bitsDIB++;
            }

            YWGUI_ColorMap2Pixel (pdc->hSurface, YWGUI_MAKE_RGB(argb.r,argb.g,argb.b),  c, FALSE);
            dst_line=YWGUI_WrapSetMemPixel(dst_line,bpp,c);
        }

        if (flag_flow == YWMID_DIBMP_FLOW_UP)
        {
            buf-=pitchDIB;
        }
        else
        {
            buf +=pitchDIB;
        }

        bitsDDB += pitchDDB;
    }
}

static void YWGUI_WrapRegroup32DIBitmap(YWGUI_HDc_T hdc, S32 widthDIB, S32 heightDIB, const U8* bitsDIB,
                             S32 pitchDIB,U32 flag_flow,U32 flag_type, S32 pitchDDB,U8* bitsDDB)
{
    YWGUI_DeviceContext_P pdc=YWGUI_Hdc2Pdc (hdc);
    S32 bpp;
    S32 x;
    S32 y;
    const U8*buf;
    U8* dst_line;
    //U32 c=0;
    YWGUI_Pixel_T c={0};
    YWGUI_Argb_T     argb={0};


    YWMID_ASSERT((heightDIB>0));

    bpp = YWGUI_GetBytesPerPixel (pdc->hSurface);

    if (flag_flow == YWMID_DIBMP_FLOW_UP)
    {
        buf = bitsDIB + pitchDIB * (heightDIB-1);//指到最后一行行头
    }
    else
    {
        buf = bitsDIB;
    }

    for (y = 0; y < heightDIB; y++)
    {
        dst_line = bitsDDB;
        bitsDIB = buf;

        for (x = 0; x < widthDIB; x++)
        {
            switch(flag_type)
            {
                case YWMID_DIBMP_FORMAT_ABGR_8888:
                    argb.a = *bitsDIB++;
                    argb.b= *bitsDIB++;
                    argb.g= *bitsDIB++;
                    argb.r= *bitsDIB++;
                    break;
                 case YWMID_DIBMP_FORMAT_BGRA_8888:
                    argb.b= *bitsDIB++;
                    argb.g= *bitsDIB++;
                    argb.r= *bitsDIB++;
                    argb.a = *bitsDIB++;
                    break;
                 case YWMID_DIBMP_FORMAT_BGR0_8888:
                    argb.b= *bitsDIB++;
                    argb.g= *bitsDIB++;
                    argb.r= *bitsDIB++;
                    argb.a = 0xff;
                    break;
                 case YWMID_DIBMP_FORMAT_ARGB_8888:
                    argb.a = *bitsDIB++;
                    argb.r= *bitsDIB++;
                    argb.g= *bitsDIB++;
                    argb.b= *bitsDIB++;
                    break;
                 case YWMID_DIBMP_FORMAT_RGBA_8888:
                    argb.r= *bitsDIB++;
                    argb.g= *bitsDIB++;
                    argb.b= *bitsDIB++;
                    argb.a = *bitsDIB++;
                    break;
                 default:
                    YWMID_ASSERT((0));
                    break;
            }


            //c = YWGUI_AColorMap2Pixel(pdc->hSurface, YWGUI_MAKE_RGBA(argb.a,argb.r ,argb.g,argb.b));
            YWGUI_AColorMap2Pixel(pdc->hSurface, YWGUI_MAKE_RGBA(argb.a,argb.r ,argb.g,argb.b), c);
            dst_line=YWGUI_WrapSetMemPixel(dst_line,bpp,c);
        }

        if (flag_flow == YWMID_DIBMP_FLOW_UP)
        {
            buf-=pitchDIB;
        }
        else
        {
            buf +=pitchDIB;
        }

        bitsDDB += pitchDDB;
    }
}

/************************************全局函数*********************************************/
YWGUI_Handle_T YWGUI_WrapGetVisibleLayer()
{
    YWGUI_Handle_T hVisibleLayer ;

    YWGUI_SemaWait(g_tWrapInfo.lock);
    hVisibleLayer = g_tWrapInfo.hVisibleLayer;
    YWGUI_SemaSend(g_tWrapInfo.lock);

    return hVisibleLayer;
}

//Rogertest
YWGUI_Handle_T YWGUI_WrapGetInvisibleLayer()
{
    YWGUI_Handle_T hInvisibleLayer ;

    YWGUI_SemaWait(g_tWrapInfo.lock);
    hInvisibleLayer = g_tWrapInfo.hInvisibleLayer;
    YWGUI_SemaSend(g_tWrapInfo.lock);

    return hInvisibleLayer;
}

void YWGUI_WrapStartAcceptKey()
{
    YWGUI_SemaWait(g_tWrapInfo.lock);
    g_tWrapInfo.bStartAcceptKey=TRUE;
    YWGUI_SemaSend(g_tWrapInfo.lock);
}


void YWGUI_WrapSinkWait()
{
    YWGUI_SemaWait(g_tWrapInfo.sinkWake);
}




S32 YWGUI_WrapGetKeyEvent(U32 *pMessage,U32 *pScanCode,U32 *pLParam)
{
    S32 iRet = -1;

    YWMID_ASSERT((pMessage !=NULL && pScanCode!=NULL));

    YWGUI_SemaWait(g_tWrapKeyMsg.lock);

    if(g_tWrapKeyMsg.bHaveData)
    {
        *pMessage = g_tWrapKeyMsg.message;
        *pScanCode = g_tWrapKeyMsg.scan_code;
        if(pLParam!=NULL)
        {
            *pLParam = g_tWrapKeyMsg.lparam;
        }
        g_tWrapKeyMsg.bHaveData = FALSE;
        iRet =0;
    }
    YWGUI_SemaSend(g_tWrapKeyMsg.lock);
    return iRet;
}


void YWGUI_WrapKeyScanProc(void* param)
{
    DFBInputEvent evt;
    BOOL bGotKey = FALSE;
    IDirectFBEventBuffer *events = (IDirectFBEventBuffer *)param;
    while(!YWOS_ThreadIsCancel(ywKeyScanThreadID))
    {
        if((events->GetEvent( events, DFB_EVENT(&evt) ) == DFB_OK))
        {
            bGotKey = FALSE;
            YWGUI_SemaWait(g_tWrapKeyMsg.lock);
            switch(evt.type)
            {
                case DIET_KEYRELEASE:
                    bGotKey = TRUE;
                    g_tWrapKeyMsg.message = YWGUI_MSG_KEYUP;
                    break;
                case DIET_KEYPRESS:
                    bGotKey = TRUE;
                    g_tWrapKeyMsg.message = YWGUI_MSG_KEYDOWN;
                    break;
                default:
                    break;
            }
            if ((evt.key_symbol & 0xFF00) == DIKT_SPECIAL)
            {
                switch(evt.key_symbol)
                {
                    case DIKS_CURSOR_LEFT:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_LEFT;
                        break;
                    case DIKS_CURSOR_RIGHT:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_RIGHT;
                        break;

                    case DIKS_CURSOR_UP:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_UP;
                        break;
                    case DIKS_CURSOR_DOWN:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_DOWN;
                        break;

                    case DIKS_OK:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_OK;
                        break;
                    case DIKS_EXIT:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_EXIT;
                        break;
                    case DIKS_0:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_0;
                        break;
                    case DIKS_1:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_1;
                        break;
                    case DIKS_2:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_2;
                        break;
                    case DIKS_3:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_3;
                        break;
                    case DIKS_4:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_4;
                        break;
                    case DIKS_5:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_5;
                        break;
                    case DIKS_6:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_6;
                        break;
                    case DIKS_7:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_7;
                        break;
                     case DIKS_8:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_8;
                        break;
                    case DIKS_9:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_9;
                        break;
                     default:
                        g_tWrapKeyMsg.scan_code = evt.key_symbol;
                        break;
                }
            }
            else
            {
                switch(evt.key_id)
                {
                    case DIKI_LEFT:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_LEFT;
                        break;
                    case DIKI_RIGHT:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_RIGHT;
                        break;
                    case DIKI_UP:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_UP;
                        break;
                    case DIKI_DOWN:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_DOWN;
                        break;
                    case DIKI_ENTER:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_OK;
                        break;
                    case DIKI_ESCAPE:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_EXIT;
                        break;
                    case DIKI_0:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_0;
                        break;
                    case DIKI_1:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_1;
                        break;
                    case DIKI_2:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_2;
                        break;
                    case DIKI_3:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_3;
                        break;
                    case DIKI_4:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_4;
                        break;
                    case DIKI_5:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_5;
                        break;
                    case DIKI_6:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_6;
                        break;
                    case DIKI_7:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_7;
                        break;
                     case DIKI_8:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_8;
                        break;
                    case DIKI_9:
                        g_tWrapKeyMsg.scan_code = YWGUI_SCANCODE_9;
                        break;
                     default:
                        g_tWrapKeyMsg.scan_code = evt.key_symbol;
                        break;
                }
            }
            if(bGotKey)
            {
                g_tWrapKeyMsg.lparam =0;
                g_tWrapKeyMsg.bHaveData = TRUE;
                YWGUI_WrapSinkWake();
            }
            YWGUI_SemaSend(g_tWrapKeyMsg.lock);
        }
        events->WaitForEventWithTimeout(events, 1, 0);
    }
}

void YWGUI_WrapInit()
{
    YW_ErrorType_T errCode = YW_NO_ERROR;
    S32 i=0;
    //YWGUI_Handle_T PanelHandle;

    YWGUI_MemSet(&g_tWrapInfo,0,sizeof(g_tWrapInfo));
    YWGUI_SemaCreate(&(g_tWrapInfo.lock),1);
    YWGUI_SemaCreate(&(g_tWrapInfo.sinkWake),0);


    YWGUI_MemSet(&g_tWrapSurface,0,sizeof(g_tWrapSurface));
    for(i=0;i<WRAP_SURFACE_NUM;i++)
    {
        YWGUI_SemaCreate(&(g_tWrapSurface[i].lock),1);
    }


    YWGUI_MemSet(&g_tWrapKeyMsg,0,sizeof(WrapKeyMsg_T));
    YWGUI_SemaCreate(&(g_tWrapKeyMsg.lock),1);
    //g_tWrapInfo.hPanel = (YWGUI_Handle_T)&PanelHandle;

    g_tWrapInfo.hPanel = (YWGUI_Handle_T)0;
    DFBCHECK (DirectFBInit (0, NULL));
    DFBCHECK (DirectFBCreate(&g_tWrapInfo.pstDfb));
    DFBCHECK (g_tWrapInfo.pstDfb->SetCooperativeLevel (g_tWrapInfo.pstDfb, DFSCL_FULLSCREEN));
    DFBCHECK (g_tWrapInfo.pstDfb->CreateInputEventBuffer(g_tWrapInfo.pstDfb,DICAPS_KEYS,DFB_FALSE,&g_tWrapInfo.pstEventBuf));
    g_tWrapInfo.hPanel = (YWGUI_Handle_T)g_tWrapInfo.pstEventBuf;//有点多余,尽量少改动原来的,还是这样写吧

    //DFBCHECK(g_tWrapInfo.pstDfb->GetDisplayLayer(g_tWrapInfo.pstDfb, DLID_PRIMARY, &g_tWrapInfo.pstDspLayer));
    //DFBCHECK(g_tWrapInfo.pstDspLayer->SetCooperativeLevel(g_tWrapInfo.pstDspLayer,DFSCL_FULLSCREEN));
    //创建按键扫描线程
    YWGUI_ThreadCreate((S8*)"ywkeyscan", YWGUI_WrapKeyScanProc, (void*)g_tWrapInfo.pstEventBuf, NULL, 8*YW_K, 3,TRUE,&ywKeyScanThreadID);
}

void YWGUI_WrapTerm(void)
{
    S32 i=0;
    YWOS_ThreadDelete(ywKeyScanThreadID);
    //DFBCHECK (g_tWrapInfo.pstDspLayer->Release(g_tWrapInfo.pstDspLayer));
    DFBCHECK (g_tWrapInfo.pstEventBuf->Release(g_tWrapInfo.pstEventBuf));
    DFBCHECK (g_tWrapInfo.pstDfb->Release(g_tWrapInfo.pstDfb));
    for(i=0;i<WRAP_SURFACE_NUM;i++)
    {
        YWGUI_SemaDelete(g_tWrapSurface[i].lock);
    }
    YWGUI_MemSet(&g_tWrapSurface,0,sizeof(g_tWrapSurface));

    YWGUI_SemaDelete(g_tWrapInfo.sinkWake);
    YWGUI_SemaDelete(g_tWrapInfo.lock);
    YWGUI_MemSet(&g_tWrapInfo,0,sizeof(g_tWrapInfo));

    YWGUI_SemaDelete(g_tWrapKeyMsg.lock);
    YWGUI_MemSet(&g_tWrapKeyMsg,0,sizeof(WrapKeyMsg_T));
}

void YWGUI_WrapRegister(void* param)
{
    YWGUI_ImportParams_T* ptImportParam=(YWGUI_ImportParams_T*)param;
    BOOL bOK = TRUE;
    int width, height;
    IDirectFBSurface * localSurface;
    #if 0
    if(ptImportParam!=NULL/* && ptImportParam->ptRemoteParamHead!=NULL*/)
    {
        bOK = YWGUI_WrapRegisterPanel(g_tWrapInfo.hPanel,
                                                                    ptImportParam->uRemoteNum,
                                                                    ptImportParam->ptRemoteParamHead,
                                                                    ptImportParam->ptFrontPanelParam,
                                                                    ptImportParam->ptLbdParam);
    }
    #endif
    g_tWrapInfo.hVisibleLayer = YWGUI_WrapRegisterOsdLayer(TRUE);
    g_tWrapInfo.hInvisibleLayer = YWGUI_WrapRegisterOsdLayer(FALSE);//Rogertest
    //g_tWrapInfo.hInvisibleLayer = g_tWrapInfo.hVisibleLayer;

    localSurface = (IDirectFBSurface *)g_tWrapInfo.hVisibleLayer;
    DFBCHECK(localSurface->GetSize(localSurface, &width, &height));
    printf("*********visable : w=%d, h=%d\n", width, height);

    localSurface = (IDirectFBSurface *)g_tWrapInfo.hInvisibleLayer;
    DFBCHECK(localSurface->GetSize(localSurface, &width, &height));
    printf("*********invisible: w=%d, h=%d\n", width, height);
    //g_tWrapInfo.ptSurface[WRAP_VISIBLE_SURFACE]->pstDfbSurface = (IDirectFBSurface*)g_tWrapInfo.hVisibleLayer;
    //g_tWrapInfo.ptSurface[WRAP_INVISIBLE_SURFACE]->pstDfbSurface = (IDirectFBSurface*)g_tWrapInfo.hInvisibleLayer;
}

void YWGUI_WrapUnregister(void)
{
    YWGUI_WrapCloseOsdLayer(g_tWrapInfo.hInvisibleLayer);//Rogertest
    YWGUI_WrapCloseOsdLayer(g_tWrapInfo.hVisibleLayer);
}


YW_ErrorType_T YWGUI_WrapThreadCreate(S8* Name,  void(*Function)(void *Param), void* Param,
            void* Stack, U32 StackSize, U32 Priority, BOOL Start, YWGUI_ThreadID_T * ThreadID )
{
    YW_ErrorType_T errCode = YW_NO_ERROR;

    if(Priority==0)
    {
        Priority = 9;
    }

    errCode=YWOS_ThreadCreate(Name,Function,Param,Stack,StackSize,Priority,Start,ThreadID);
    if(errCode!=YW_NO_ERROR)
    {
        YWMID_ASSERT((0));

        return errCode;
    }
    return errCode;
}
YW_ErrorType_T YWGUI_WrapThreadDelete(YWGUI_ThreadID_T  ThreadID )
{
    YW_ErrorType_T errCode = YW_NO_ERROR;

    errCode=YWOS_ThreadDelete(ThreadID);
    if(errCode!=YW_NO_ERROR)
    {
        YWMID_ASSERT((0));

        return errCode;
    }
    return errCode;
}

BOOL YWGUI_WrapThreadIsCancel(YWGUI_ThreadID_T  ThreadID )
{
    return YWOS_ThreadIsCancel(ThreadID);
}


YW_ErrorType_T YWGUI_WrapSemaCreate(YWGUI_SemaID_T* SemaphoreID,U32 Count)
{
    static S32 count=1;
    S8 szSemaName[25];

    ASCII_sprintf(szSemaName,(S8*)"YWGUI_Sema%d",count);
    count++;

    if(YWOS_SemaphoreCreate(szSemaName,Count,SemaphoreID)!=YW_NO_ERROR)
    {
        return YWGUI_ERROR;
    }

    return YW_NO_ERROR;
}


S32 YWGUI_WrapAbs(S32 val)
{
    return YWGUI_ABS(val);
}


YWGUI_ThreadID_T YWGUI_WrapThreadSelf()
{
    YWGUI_ThreadID_T idThread=0;

    if(YWOS_ThreadId((YWOS_ThreadID_T*)&idThread)==YW_NO_ERROR)
    {
        return idThread;
    }
    else
    {
        YWMID_ASSERT((0));
        return 0;
    }
}


YWGUI_HSurface_T  YWGUI_WrapInitSurface(BOOL bVisibled)
{
    WrapSurface_T* pSurface=NULL;

    if(bVisibled)
    {
        pSurface = YWGUI_WrapGetSurfaceByIndex(WRAP_VISIBLE_SURFACE);
        if(pSurface==NULL)
        {
            pSurface = &(g_tWrapSurface[WRAP_VISIBLE_SURFACE]);
            Wrap_LockSurface(pSurface);
            pSurface->bIsVisible = TRUE;
            pSurface->hLayer = YWGUI_WrapGetVisibleLayer();
            pSurface->count=1;
            Wrap_UnlockSurface(pSurface);

            YWGUI_WrapSetSurfaceByIndex(WRAP_VISIBLE_SURFACE,pSurface);
        }
        else
        {
            Wrap_LockSurface(pSurface);
            ++pSurface->count;
            Wrap_UnlockSurface(pSurface);
        }

    }
    else
    {
        //Rogertest
        pSurface = YWGUI_WrapGetSurfaceByIndex(WRAP_INVISIBLE_SURFACE);
        if(pSurface==NULL)
        {
            pSurface = &(g_tWrapSurface[WRAP_INVISIBLE_SURFACE]);
            Wrap_LockSurface(pSurface);
            pSurface->bIsVisible = FALSE;
            pSurface->hLayer = YWGUI_WrapGetInvisibleLayer();
            pSurface->count=1;
            Wrap_UnlockSurface(pSurface);

            YWGUI_WrapSetSurfaceByIndex(WRAP_INVISIBLE_SURFACE,pSurface);
        }
        else
        {
            Wrap_LockSurface(pSurface);
            ++pSurface->count;
            Wrap_UnlockSurface(pSurface);
        }
    }

    return (YWGUI_HSurface_T)pSurface;
}


BOOL YWGUI_WrapTermSurface(YWGUI_HSurface_T hSurface)
{
    WrapSurface_T* pSurface=(WrapSurface_T *)hSurface;

    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        return TRUE;
    }

    Wrap_LockSurface(pSurface);
    --pSurface->count;
    YWMID_ASSERT((pSurface->count>=0));
    if(pSurface->count==0)
    {
        pSurface->hLayer=(YWGUI_Handle_T)0;

        if(pSurface->bIsVisible)
        {
            YWGUI_WrapSetSurfaceByIndex(WRAP_VISIBLE_SURFACE,NULL);
        }
        else
        {
            YWGUI_WrapSetSurfaceByIndex(WRAP_INVISIBLE_SURFACE,NULL);
        }
    }
    Wrap_UnlockSurface(pSurface);
    return TRUE;
}

void YWGUI_WrapCopySurface(YWGUI_HSurface_T hDestSurface,YWGUI_HSurface_T hSrcSurface)
{

    WrapSurface_T* pDestSurface=(WrapSurface_T *)hDestSurface;
    WrapSurface_T* pSrcSurface=(WrapSurface_T *)hSrcSurface;
    YWGUI_Rect_T DstRect;
    YWGUI_Rect_T SrcRect;
    YWGUI_LayerInfo_T*ptLayerInfo;
    IDirectFBSurface * pDstDfb = (IDirectFBSurface *)pDestSurface->hLayer;
    IDirectFBSurface * pSrcDfb = (IDirectFBSurface *)pSrcSurface->hLayer;

    DFBRectangle       source_rect={0, 0, 1920, 1080};
    DFBRectangle       destination_rect = {0, 0, 1920, 1080};

    //YWGUI_Pixel_T     colorKey;
    ptLayerInfo=YWGUI_TakeoutLayerInfo();

    #if 0
    SrcRect.Left = 0;
    SrcRect.Top= 0;
    SrcRect.Width = ptLayerInfo->width;
    SrcRect.Height = ptLayerInfo->height;
    #endif
    YWGUI_MemCpy(&DstRect,&SrcRect,sizeof(YWGUI_Rect_T));
    //colorKey = ptLayerInfo->colorKey;
    //YWCANVAS_CopyCanvasRect((YWCANVAS_Handle_T)pDestSurface->hLayer,&DstRect,(YWCANVAS_Handle_T)pSrcSurface->hLayer,&SrcRect,NULL, YWCANVAS_OP_MODE_COPY);
    //surface->Flip(surface, NULL, 0);
    //DFBCHECK(pDstDfb->Blit (pDstDfb, pSrcDfb, NULL, 0, 0));
    DFBCHECK(pDstDfb->StretchBlit (pDstDfb, pSrcDfb, &source_rect, &destination_rect));

    YWGUI_ReturnLayerInfo();
}


//color(0bgr) YWGUI_MAKE_RGB
void  YWGUI_WrapColorMap2Pixel (YWGUI_HSurface_T hSurface,U32 color, YWGUI_Pixel_T pixel, BOOL b32BitResult)
{
    YWGUI_PixelType_E ePixelType=YWGUI_PIXEL_TYPE_INVALID;
    U8 *p= (U8*)pixel;
    YWMID_ASSERT(pixel!=NULL);
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[ColorMap2Pixel] Surface is invalid,return!\n"));
        YWMID_ASSERT((0));
        return /*pixel*/;
    }

    ePixelType=YWGUI_WrapGetOsdLayerPixelType(YWGUI_WrapGetSurfaceLayer(hSurface));
    switch(ePixelType)
    {
        case YWGUI_PIXEL_TYPE_RGB888:
            p[0]=YWGUI_GetRValue(color);
            p[1]=YWGUI_GetGValue(color);
            p[2]=YWGUI_GetBValue(color);
            break;
        case YWGUI_PIXEL_TYPE_BGR888:
            p[0]=YWGUI_GetBValue(color);
            p[1]=YWGUI_GetGValue(color);
            p[2]=YWGUI_GetRValue(color);
            break;
        case YWGUI_PIXEL_TYPE_BGRA8888:
            p[0]=YWGUI_GetBValue(color);
            p[1]=YWGUI_GetGValue(color);
            p[2]=YWGUI_GetRValue(color);
            p[3]=0xff;
            break;
       //added by sly for 16 bit, 2010-8-25:为了app改动较小,上面传下来的颜色仍然是32位的
        case YWGUI_PIXEL_TYPE_BGR565:
            //p[0]=(YWGUI_GetBValue(color)&0xF8) |((YWGUI_GetGValue(color)>>5)&0x7);
            //p[1]=((YWGUI_GetGValue(color)<<3)&0xE0) | ((YWGUI_GetRValue(color)>>3)&0x1F);
            if(b32BitResult)
            {
                p[0]=YWGUI_GetBValue(color);
                p[1]=YWGUI_GetGValue(color);
                p[2]=YWGUI_GetRValue(color);
            }
            else
            {
                p[0] = ((YWGUI_GetBValue(color)>>3)&0x1F)|(((YWGUI_GetGValue(color))<<3)&0xE0);
                p[1] = ((YWGUI_GetGValue(color)>>5)&0x7)|(YWGUI_GetRValue(color)&0xF8);
            }
            break;
        case YWGUI_PIXEL_TYPE_BGRA5551:
            //p[0]=(YWGUI_GetBValue(color)&0xF8) |((YWGUI_GetGValue(color)>>5)&0x7);
            //p[1]=((YWGUI_GetGValue(color)<<3)&0xC0) | (((YWGUI_GetRValue(color)>>2)&0x3E)|0x80);
            if(b32BitResult)
            {
                p[0]=YWGUI_GetBValue(color);
                p[1]=YWGUI_GetGValue(color);
                p[2]=YWGUI_GetRValue(color);
                p[3]=0xff;
            }
            else
            {
                p[0]=((YWGUI_GetBValue(color)>>3)&0x1F)|((YWGUI_GetGValue(color)<<2)&0xE0);
                p[1]= ((YWGUI_GetGValue(color)>>6)&0x3)|((YWGUI_GetRValue(color)>>1)&0x7C);
                p[1]|= 0x80;
            }
            break;
       case YWGUI_PIXEL_TYPE_BGRA4444:
            //p[0]=(YWGUI_GetBValue(color)&0xF0) |((YWGUI_GetGValue(color)>>4)&0xF);
            //p[1]=(YWGUI_GetRValue(color)&0xF0) | 0xF;
            if(b32BitResult)
            {
                p[0]=YWGUI_GetBValue(color);
                p[1]=YWGUI_GetGValue(color);
                p[2]=YWGUI_GetRValue(color);
                p[3]=0xff;
            }
            else
            {
                p[0]=((YWGUI_GetBValue(color)>>4)&0xF) |(YWGUI_GetGValue(color)&0xF0);
                p[1]=((YWGUI_GetRValue(color)>>4)&0xF) |0xF0;
            }
            break;
       /*end of added*/
        default:
            YWMID_Trace((YWOS_TRACE_ERROR,"[ColorMap2Pixel] ePixelType is invalid(=%d)!\n",ePixelType));
            break;
    }

    //return pixel;
}

//color(abgr) YWGUI_MAKE_RGBA
void YWGUI_WrapAColorMap2Pixel (YWGUI_HSurface_T hSurface,U32 color, YWGUI_Pixel_T pixel)
{
    YWGUI_PixelType_E ePixelType=YWGUI_PIXEL_TYPE_INVALID;
    *(U32*) pixel=0;
    U8 *p= (U8*)pixel;
    YWMID_ASSERT(pixel!=NULL);
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[AColorMap2Pixel] Surface is invalid,return!\n"));
        //YWMID_ASSERT((0));
        //return pixel;
    }

    ePixelType=YWGUI_WrapGetOsdLayerPixelType(YWGUI_WrapGetSurfaceLayer(hSurface));
    switch(ePixelType)
    {
        case YWGUI_PIXEL_TYPE_RGB888:
            p[0]=YWGUI_GetRValue(color);
            p[1]=YWGUI_GetGValue(color);
            p[2]=YWGUI_GetBValue(color);
            break;
        case YWGUI_PIXEL_TYPE_BGR888:
            p[0]=YWGUI_GetBValue(color);
            p[1]=YWGUI_GetGValue(color);
            p[2]=YWGUI_GetRValue(color);
            break;
        case YWGUI_PIXEL_TYPE_BGRA8888:
            p[0]=YWGUI_GetBValue(color);
            p[1]=YWGUI_GetGValue(color);
            p[2]=YWGUI_GetRValue(color);
            p[3]=YWGUI_GetAValue(color);
            break;
         //added by sly for 16 bit, 2010-8-25:为了app改动较小,上面传下来的颜色仍然是32位的
        case YWGUI_PIXEL_TYPE_BGR565:
            //p[0]=(YWGUI_GetBValue(color)&0xF8) |((YWGUI_GetGValue(color)>>5)&0x7);
            //p[1]=((YWGUI_GetGValue(color)<<3)&0xE0) | ((YWGUI_GetRValue(color)>>3)&0x1F);
            p[0] = ((YWGUI_GetBValue(color)>>3)&0x1F)|(((YWGUI_GetGValue(color))<<3)&0xE0);
            p[1] = ((YWGUI_GetGValue(color)>>5)&0x7)|(YWGUI_GetRValue(color)&0xF8);
            break;
        case YWGUI_PIXEL_TYPE_BGRA5551:
            //p[0]=(YWGUI_GetBValue(color)&0xF8) |((YWGUI_GetGValue(color)>>5)&0x7);
            //p[1]=((YWGUI_GetGValue(color)<<3)&0xC0) |((YWGUI_GetRValue(color)>>2)&0x3E);
            p[0]=((YWGUI_GetBValue(color)>>3)&0x1F)|((YWGUI_GetGValue(color)<<2)&0xE0);
            p[1]= ((YWGUI_GetGValue(color)>>6)&0x3)|((YWGUI_GetRValue(color)>>1)&0x7C);

            if(YWGUI_GetAValue(color)!=0)/*只要不是全透明就认为是不透明*/
            {
                p[1]|= 0x80;
            }
            break;
       case YWGUI_PIXEL_TYPE_BGRA4444:
            //p[0]=(YWGUI_GetBValue(color)&0xF0) |((YWGUI_GetGValue(color)>>4)&0xF);
            //p[1]=(YWGUI_GetRValue(color)&0xF0) |((YWGUI_GetAValue(color)>>4)&0xF);
            p[0]=((YWGUI_GetBValue(color)>>4)&0xF) |(YWGUI_GetGValue(color)&0xF0);
            p[1]=((YWGUI_GetRValue(color)>>4)&0xF) |(YWGUI_GetAValue(color)&0xF0);
            break;
       /*end of added*/
        default:
            YWMID_Trace((YWOS_TRACE_ERROR,"[AColorMap2Pixel] ePixelType is invalid(=%d)!\n",ePixelType));
            break;
    }

    //return pixel;
}

//返回值(0bgr)
U32 YWGUI_WrapPixelMap2Color (YWGUI_HSurface_T hSurface,YWGUI_Pixel_T pixel)
{
    U32 color=0;
    YWGUI_PixelType_E ePixelType=YWGUI_PIXEL_TYPE_INVALID;
    U8 *p= (U8*)pixel;
    YWMID_ASSERT(pixel!=NULL);
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[PixelMap2Color] Surface is invalid,return!\n"));
        //YWMID_ASSERT((0));
        return color;
    }

    ePixelType=YWGUI_WrapGetOsdLayerPixelType(YWGUI_WrapGetSurfaceLayer(hSurface));
    switch(ePixelType)
    {
        case YWGUI_PIXEL_TYPE_RGB888:
            color = YWGUI_MAKE_RGB(p[0], p[1], p[2]);
            break;
        case YWGUI_PIXEL_TYPE_BGR888:
            color = YWGUI_MAKE_RGB(p[2], p[1], p[0]);
            break;
        case YWGUI_PIXEL_TYPE_BGRA8888:
            color = YWGUI_MAKE_RGB(p[2], p[1], p[0]);
        default:
            YWMID_Trace((YWOS_TRACE_ERROR,"[PixelMap2Color] ePixelType is invalid(=%d)!\n",ePixelType));
            break;
    }

    return color;
}
void YWGUI_WrapDCAttrValue2Pixel (YWGUI_HSurface_T hSurface,U8 * pValue, YWGUI_Pixel_T pixel)
{
    YWGUI_PixelType_E ePixelType=YWGUI_PIXEL_TYPE_INVALID;
    *(U32*) pixel=0;
    U8 *p= (U8*)pixel;
    YWMID_ASSERT(pixel!=NULL);
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[AColorMap2Pixel] Surface is invalid,return!\n"));
        //YWMID_ASSERT((0));
        //return pixel;
    }
    ePixelType=YWGUI_WrapGetOsdLayerPixelType(YWGUI_WrapGetSurfaceLayer(hSurface));
    switch(ePixelType)
    {
        case YWGUI_PIXEL_TYPE_RGB888:
            p[0]=pValue[2];
            p[1]=pValue[1];
            p[2]=pValue[0];
            break;
        case YWGUI_PIXEL_TYPE_BGR888:
            p[0]=pValue[0];
            p[1]=pValue[1];
            p[2]=pValue[2];
            break;
        case YWGUI_PIXEL_TYPE_BGRA8888:
            p[0]=pValue[0];
            p[1]=pValue[1];
            p[2]=pValue[2];
            p[3]=pValue[3];
            break;
         //added by sly for 16 bit, 2010-8-25:为了app改动较小,上面传下来的颜色仍然是32位的
        case YWGUI_PIXEL_TYPE_BGR565:
            p[0] = ((pValue[0]>>3)&0x1F)|(((pValue[1])<<3)&0xE0);
            p[1] = ((pValue[1]>>5)&0x7)|(pValue[2]&0xF8);
            break;
        case YWGUI_PIXEL_TYPE_BGRA5551:
            p[0]=((pValue[0]>>3)&0x1F)|((pValue[1]<<2)&0xE0);
            p[1]= ((pValue[1]>>6)&0x3)|((pValue[2]>>1)&0x7C);

            if(pValue[3]!=0)/*只要不是全透明就认为是不透明*/
            {
                p[1]|=0x80;
            }
            break;
       case YWGUI_PIXEL_TYPE_BGRA4444:
            //p[1]=(pValue[3]&0xF0) |((pValue[2]>>4)&0xF);
            //p[0]=(pValue[1]&0xF0) |((pValue[0]>>4)&0xF);
            p[0]=((pValue[0]>>4)&0xF)|(pValue[1]&0xF0);
            p[1]=((pValue[2]>>4)&0xF)|(pValue[3]&0xF0);
            break;
       /*end of added*/
        default:
            YWMID_Trace((YWOS_TRACE_ERROR,"[YWGUI_DCAttrValue2Pixel] ePixelType is invalid(=%d)!\n",ePixelType));
            break;
    }

}
void YWGUI_WrapDCAttrPixel2Value (YWGUI_HSurface_T hSurface,YWGUI_Pixel_T pixel, U8 * pValue)
{
    YWGUI_PixelType_E ePixelType=YWGUI_PIXEL_TYPE_INVALID;
    U8 *p= (U8*)pixel;
    YWMID_ASSERT(pixel!=NULL);
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[AColorMap2Pixel] Surface is invalid,return!\n"));
        //YWMID_ASSERT((0));
        //return pixel;
    }
    ePixelType=YWGUI_WrapGetOsdLayerPixelType(YWGUI_WrapGetSurfaceLayer(hSurface));
    switch(ePixelType)
    {
        case YWGUI_PIXEL_TYPE_RGB888:
            pValue[2]=p[0];
            pValue[1]=p[1];
            pValue[0]=p[2];
            break;
        case YWGUI_PIXEL_TYPE_BGR888:
            pValue[0]=p[0];
            pValue[1]=p[1];
            pValue[2]=p[2];
            break;
        case YWGUI_PIXEL_TYPE_BGRA8888:
            pValue[0]=p[0];
            pValue[1]=p[1];
            pValue[2]=p[2];
            pValue[3]=p[3];
            break;
         //added by sly for 16 bit, 2010-8-25:为了app改动较小,上面传下来的颜色仍然是32位的
        case YWGUI_PIXEL_TYPE_BGR565:
            pValue[0]=(p[0]<<3)&0x1F;
            pValue[1]=((p[1]<<5)&0xE0) | ((p[0]>>3)&0x1C);
            pValue[2]=p[1]&0xF8;
            break;
        case YWGUI_PIXEL_TYPE_BGRA5551:
            pValue[0]=(p[0]<<3)&0xF8;
            pValue[1]=((p[1]<<6)&0xC0) |((p[0]>>2)&0x38);
            pValue[2]=(p[1]<<1)&0xF8;
            pValue[3]=p[1]&0x80;
            break;
       case YWGUI_PIXEL_TYPE_BGRA4444:

            pValue[0]=(p[0]<<4)&0xF0;
            pValue[1]= p[0]&0xF0;
            pValue[2]=(p[1]<<4)&0xF0;
            pValue[3]= p[1]&0xF0;
            break;
       /*end of added*/
        default:
            YWMID_Trace((YWOS_TRACE_ERROR,"[YWGUI_DCAttrValue2Pixel] ePixelType is invalid(=%d)!\n",ePixelType));
            break;
    }

}
void YWGUI_WrapArgb2Pixel (YWGUI_HSurface_T hSurface, YWGUI_Argb_T* pArgb, YWGUI_Pixel_T pixel, U32 * pFlag)
{
    YWGUI_PixelType_E ePixelType=YWGUI_PIXEL_TYPE_INVALID;
    *(U32*) pixel=0;
    U8 *p= (U8*)pixel;
    YWMID_ASSERT(pixel!=NULL);
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[AColorMap2Pixel] Surface is invalid,return!\n"));
        //YWMID_ASSERT((0));
        //return pixel;
    }
    if(pFlag)
    {
        ePixelType = (YWGUI_PixelType_E)(*pFlag);
    }
    else
    {
        ePixelType=YWGUI_WrapGetOsdLayerPixelType(YWGUI_WrapGetSurfaceLayer(hSurface));
    }
    switch(ePixelType)
    {
        case YWGUI_PIXEL_TYPE_RGB888:
            p[0] = pArgb->r;
            p[1] = pArgb->g;
            p[2] = pArgb->b;
            break;
        case YWGUI_PIXEL_TYPE_BGR888:
            p[0] = pArgb->b;
            p[1] = pArgb->g;
            p[2] = pArgb->r;
            break;
        case YWGUI_PIXEL_TYPE_BGRA8888:
            p[0] = pArgb->b;
            p[1] = pArgb->g;
            p[2] = pArgb->r;
            p[3] = pArgb->a;
            break;
         //added by sly for 16 bit, 2010-8-25:为了app改动较小,上面传下来的颜色仍然是32位的
        case YWGUI_PIXEL_TYPE_BGR565:
            p[0] = (pArgb->b&0x1F)|(((pArgb->g)<<5)&0xE0);
            p[1] = ((pArgb->g>>3)&0x7)|((pArgb->r<<3)&0xF8);
            break;
        case YWGUI_PIXEL_TYPE_BGRA5551:
            p[0] = (pArgb->b&0x1F)|((pArgb->g<<5)&0xE0);
            p[1] = ((pArgb->g>>3)&0x3)|((pArgb->r<<2)&0x7C);
            if(pArgb->a!=0)/*只要不是全透明就认为是不透明*/
            {
                p[1]|=0x80;
            }
            break;
       case YWGUI_PIXEL_TYPE_BGRA4444:
            //p[1]=((pArgb->a<<4)&0xF0) |(pArgb->r&0xF);
            //p[0]=((pArgb->g<<4)&0xF0) |(pArgb->b&0xF);
            p[0] = (pArgb->b&0xF) | ((pArgb->g<<4)&0xF0);
            p[1] = (pArgb->r&0xF) | ((pArgb->a<<4)&0xF0);
            break;
       /*end of added*/
        default:
            YWMID_Trace((YWOS_TRACE_ERROR,"[YWGUI_WrapArgb2Pixel] ePixelType is invalid(=%d)!\n",ePixelType));
            break;
    }

}

void YWGUI_WrapPixel2Argb (YWGUI_HSurface_T hSurface,YWGUI_Pixel_T pixel, YWGUI_Argb_T* pArgb, U32 *pFlag)
{
    YWGUI_PixelType_E ePixelType=YWGUI_PIXEL_TYPE_INVALID;
    U8 *p= (U8*)pixel;
    YWMID_ASSERT(pixel!=NULL);
    if(pFlag)
    {
        ePixelType = (YWGUI_PixelType_E)(*pFlag);
    }
    else
    {
        ePixelType=YWGUI_WrapGetOsdLayerPixelType(YWGUI_WrapGetSurfaceLayer(hSurface));
    }
    switch(ePixelType)
    {
        case YWGUI_PIXEL_TYPE_RGB888:
            pArgb->r = p[0];
            pArgb->g = p[1];
            pArgb->b = p[2];
            break;
        case YWGUI_PIXEL_TYPE_BGR888:
            pArgb->b = p[0];
            pArgb->g = p[1];
            pArgb->r = p[2];
            break;
        case YWGUI_PIXEL_TYPE_BGRA8888:
            pArgb->b = p[0] ;
            pArgb->g = p[1] ;
            pArgb->r = p[2] ;
            pArgb->a = p[3] ;
            break;
         //added by sly for 16 bit, 2010-8-25:为了app改动较小,上面传下来的颜色仍然是32位的
        case YWGUI_PIXEL_TYPE_BGR565:
            pArgb->b = p[0] & 0x1F;
            pArgb->g = (((p[0] & 0xE0) >> 5) | ((p[1] & 0x7) << 3)) & 0x3F;
            pArgb->r  = (p[1] & 0xF8) >> 3;
            break;
        case YWGUI_PIXEL_TYPE_BGRA5551:
            pArgb->b = p[0] & 0x1F;
            pArgb->g = (((p[0] & 0xE0) >> 5) | ((p[1] & 0x3) << 3)) & 0x1F;
            pArgb->r = (p[1] & 0x7C) >> 2;
            pArgb->a = (p[1] & 0x80) >> 7;
            break;
       case YWGUI_PIXEL_TYPE_BGRA4444:
            pArgb->b= p[0] & 0xF;
            pArgb->g = (p[0] & 0xF0) >> 4;
            pArgb->r= p[1] & 0xF;
            pArgb->a = (p[1] & 0xF0) >> 4;
            break;
        default:
            YWMID_Trace((YWOS_TRACE_ERROR,"[YWGUI_WrapPixel2Argb] ePixelType is invalid(=%d)!\n",ePixelType));
            break;
    }

}
U8 YWGUI_WrapGetBitsPerPixel(YWGUI_HSurface_T hSurface)
{
    YWGUI_Handle_T hLayer;
    DFBSurfacePixelFormat PixelFormat;
    YW_ErrorType_T errCode=YW_NO_ERROR;
    IDirectFBSurface *pSurface;
    U8 BitsPerPixel = 0;
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[GetBitsPerPixel] Surface is invalid,return!\n"));
        //YWMID_ASSERT((0));
        return 0;
    }

    hLayer=YWGUI_WrapGetSurfaceLayer(hSurface);
    pSurface = (IDirectFBSurface * )hLayer;
    YWGUI_MemSet(&PixelFormat,0,sizeof(DFBSurfacePixelFormat));
    DFBCHECK( pSurface->GetPixelFormat(pSurface, &PixelFormat));
    switch(PixelFormat)
    {
        case DSPF_RGB24:
            BitsPerPixel = 24;
            break;
        case DSPF_ARGB:
            BitsPerPixel = 32;
            break;
        case DSPF_ARGB1555:
            BitsPerPixel = 16;
            break;
        case DSPF_ARGB4444:
            BitsPerPixel = 16;
            break;
    }
    return BitsPerPixel;
}

U8 YWGUI_WrapGetBytesPerPixel(YWGUI_HSurface_T hSurface)
{
    YWGUI_Handle_T hLayer;
    DFBSurfacePixelFormat PixelFormat;
    YW_ErrorType_T errCode=YW_NO_ERROR;
    IDirectFBSurface *pSurface;
    U8 BytesPerPixel = 0;
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[GetBitsPerPixel] Surface is invalid,return!\n"));
        //YWMID_ASSERT((0));
        return 0;
    }

    hLayer=YWGUI_WrapGetSurfaceLayer(hSurface);
    pSurface = (IDirectFBSurface * )hLayer;
    YWGUI_MemSet(&PixelFormat,0,sizeof(DFBSurfacePixelFormat));
    DFBCHECK( pSurface->GetPixelFormat(pSurface, &PixelFormat));
    switch(PixelFormat)
    {
        case DSPF_RGB24:
            BytesPerPixel = 3;
            break;
        case DSPF_ARGB:
            BytesPerPixel = 4;
            break;
        case DSPF_ARGB1555:
            BytesPerPixel = 2;
            break;
        case DSPF_ARGB4444:
            BytesPerPixel = 2;
            break;
    }
    return BytesPerPixel;
}



void YWGUI_WrapSetClipping(YWGUI_HSurface_T hSurface,S32 xPos1, S32 yPos1, S32 xPos2, S32 yPos2)
{

    YWGUI_Handle_T hLayer;
    IDirectFBSurface *pSurface = NULL;
    DFBRegion	clip;
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[SetClipping] Surface is invalid,return!\n"));
        return;
    }

    clip.x1= xPos1;
    clip.y1= yPos1;
    clip.x2= xPos2;
    clip.y2= yPos2;

    hLayer=YWGUI_WrapGetSurfaceLayer(hSurface);
    pSurface = (IDirectFBSurface *)hLayer;
    DFBCHECK(pSurface->SetClip(pSurface, &clip));
}




void YWGUI_WrapFillBox(YWGUI_HSurface_T hSurface,S32 xPos1, S32 yPos1, S32 xPos2, S32 yPos2,YWGUI_Pixel_T color, YWGUI_CANVAS_OpMode_T OpMode)
{
    YWGUI_Handle_T hLayer;
    IDirectFBSurface *pSurface;
    YWMID_ASSERT(color!=NULL);
    //YWMID_Trace((YWOS_TRACE_ERROR,"[FillBox] left=%d,top=%d,width=%d,height=%d,color=%#x\n",xPos1,yPos1,YWGUI_GET_WIDTH(xPos1,xPos2),YWGUI_GET_HEIGHT(yPos1,yPos2),color));
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[FillBox] Surface is invalid,return!\n"));
        return;
    }

    hLayer=YWGUI_WrapGetSurfaceLayer(hSurface);
    if(hLayer!=(YWGUI_Handle_T)0)
    {
        YWGUI_Argb_T argb;
        pSurface = (IDirectFBSurface *)hLayer;
        //YWCANVAS_FillRect(hLayer, xPos1,yPos1,(U32)YWGUI_GET_WIDTH(xPos1, xPos2),(U32)YWGUI_GET_HEIGHT(yPos1, yPos2), (U8*)color, YWGUI_WrapReviseOpMode(OpMode));
        YWGUI_Pixel2Argb(hSurface, color, &argb, NULL);
        DFBCHECK(pSurface->SetColor(pSurface, argb.r, argb.g, argb.b, argb.a ));//r,g,b,a
        //printf("color: 0x %x,%x,%x,%x\n", color[1], color[2], color[3], color[0]);
        //printf("*************YWGUI_WrapFillBox: %d,%d,%d,%d\n", xPos1,yPos1, (U32)YWGUI_GET_WIDTH(xPos1, xPos2),(U32)YWGUI_GET_HEIGHT(yPos1, yPos2));
        DFBCHECK(pSurface->FillRectangle(pSurface, xPos1,yPos1, (U32)YWGUI_GET_WIDTH(xPos1, xPos2),(U32)YWGUI_GET_HEIGHT(yPos1, yPos2)));
    }
}

void YWGUI_WrapFillPie(YWGUI_HSurface_T hSurface, S32 x0, S32 y0, S32 r, S32 endAngle, S32 startAngle, YWGUI_Pixel_T color, YWGUI_CANVAS_OpMode_T OpMode)
{
#if 0
    YWGUI_Handle_T hLayer;
    S32 LineWidth =3;
    IDirectFBSurface *pSurface;
    YWMID_ASSERT(color!=NULL);
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[FillBox] Surface is invalid,return!\n"));
        return;
    }
    if (startAngle%360 == endAngle%360)
    {
        return;
    }
    if(r==0)
        return;
    //printf("*****************YWGUI_WrapFillPie: x0=%d, y0=%d, r=%d, start =%d, end=%d\n", x0, y0, r, startAngle, endAngle);
    hLayer=YWGUI_WrapGetSurfaceLayer(hSurface);
    pSurface = (IDirectFBSurface *)hLayer;
    if(hLayer!=(YWGUI_Handle_T)0)
    {
        S32  draw_x, draw_y;					// 画图坐标变量
        S32  op_x, op_y;						// 操作坐标
        S32  op_2rr;							// 2*r*r值变量

        S32  pno_angle;						// 度角点的个数
        U8  draw_on;							// 画点开关，为1时画点，为0时不画
        /* 参数过滤 */


        op_2rr = 2*r*r;							// 计算r平方乖以2
        pno_angle = 0;
        /* 先计算出在此半径下的45度的圆弧的点数 */
        op_x = r;
        op_y = 0;
        while(1)
        {
            pno_angle++; 							// 画点计数
            /* 计算下一点 */
            op_y++;
            if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// 使用逐点比较法实现画圆弧
            {
                op_x--;
            }
            if(op_y>=op_x)
                break;
        }

        draw_on = 0;								// 最开始关画点开关
        /* 设置起始点及终点 */
        if(endAngle>startAngle)
            draw_on = 1;		// 若终点大于起点，则从一开始即画点(359)
        startAngle = (360-startAngle)*pno_angle/45;
        endAngle = (360-endAngle)*pno_angle/45;
        if(startAngle==0)
            startAngle=1;
        if(endAngle==0)
            endAngle=1;

        /* 开始顺时针画弧，从359度开始(第4像限) */
        pno_angle = 0;

        draw_x = x0+r;
        draw_y = y0;
        op_x = r;
        op_y = 0;
        while(1)
        {
            /* 计算下一点 */
            op_y++;
            draw_y--;
            if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// 使用逐点比较法实现画圆弧
            {
                op_x--;
                draw_x--;
            }
            if(draw_on==1)
                YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
            pno_angle++;
            if( (pno_angle==startAngle)||(pno_angle==endAngle) )			// 若遇到起点或终点，画点开关取反
            {
                draw_on = 1-draw_on;
                if(draw_on==1)
                    YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
            }
            if(op_y>=op_x)
            {
                if(draw_on==1)
                    YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
                break;
            }
        }

        while(1)
        {
            /* 计算下一点 */
            op_x--;
            draw_x--;
            if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) // 使用逐点比较法实现画圆弧
            {
                op_y++;
                draw_y--;
            }
            if(draw_on==1)
                YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
            pno_angle++;
            if( (pno_angle==startAngle)||(pno_angle==endAngle) )			// 若遇到起点或终点，画点开关取反
            {
                draw_on = 1-draw_on;
                if(draw_on==1)
                    YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
            }

            if(op_x<=0)
            {
                if(draw_on==1)
                    YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
                break;
            }
        }


       /* 开始顺时针画弧，从269度开始(第3像限) */
       draw_y = y0-r;
       draw_x = x0;
       op_y = r;
       op_x = 0;
        while(1)
        {
            /* 计算下一点 */
            op_x++;
            draw_x--;
            if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_y +1)>0 ) // 使用逐点比较法实现画圆弧
            {
                op_y--;
                draw_y++;
            }
            if(draw_on==1)
                YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
            pno_angle++;
            if( (pno_angle==startAngle)||(pno_angle==endAngle) )			// 若遇到起点或终点，画点开关取反
            {
                draw_on = 1-draw_on;
                if(draw_on==1)
                    YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
            }

            if(op_x>=op_y)
            {
                if(draw_on==1)
                    YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
                break;
            }
        }

        while(1)
        {
            /* 计算下一点 */
            op_y--;
            draw_y++;
            if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_x +1)<=0 ) // 使用逐点比较法实现画圆弧
            {
                op_x++;
                draw_x--;
            }
            if(draw_on==1)
                YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
            pno_angle++;
            if( (pno_angle==startAngle)||(pno_angle==endAngle) )			// 若遇到起点或终点，画点开关取反
            {
                draw_on = 1-draw_on;
                if(draw_on==1)
                    YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
            }
            if(op_y<=0)
            {
                if(draw_on==1)
                    YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
                break;
            }
        }


        /* 开始顺时针画弧，从179度开始(第2像限) */
        draw_x = x0-r;
        draw_y = y0;
        op_x = r;
        op_y = 0;
        while(1)
        {
            /* 计算下一点 */
            op_y++;
            draw_y++;
            if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// 使用逐点比较法实现画圆弧
            {
                op_x--;
                draw_x++;
            }
            if(draw_on==1)
                YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
            pno_angle++;
            if( (pno_angle==startAngle)||(pno_angle==endAngle) )			// 若遇到起点或终点，画点开关取反
            {
                draw_on = 1-draw_on;
                if(draw_on==1)
                    YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
            }
            if(op_y>=op_x)
            {
                if(draw_on==1)
                    YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
                break;
            }
        }

        while(1)
        {
            /* 计算下一点 */
            op_x--;
            draw_x++;
            if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) // 使用逐点比较法实现画圆弧
            {
                op_y++;
                draw_y++;
            }
            if(draw_on==1)
                YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
            pno_angle++;
            if( (pno_angle==startAngle)||(pno_angle==endAngle) )			// 若遇到起点或终点，画点开关取反
            {
                draw_on = 1-draw_on;
                if(draw_on==1)
                    YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
            }

            if(op_x<=0)
            {
                if(draw_on==1)
                    YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
                break;
            }
        }


       /* 开始顺时针画弧，从89度开始(第1像限) */
       draw_y = y0+r;
       draw_x = x0;
       op_y = r;
       op_x = 0;
        while(1)
        {
            /* 计算下一点 */
            op_x++;
            draw_x++;
            if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_y +1)>0 ) // 使用逐点比较法实现画圆弧
            {
                op_y--;
                draw_y--;
            }
            if(draw_on==1)
                YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
            pno_angle++;
            if( (pno_angle==startAngle)||(pno_angle==endAngle) )			// 若遇到起点或终点，画点开关取反
            {
                draw_on = 1-draw_on;
                if(draw_on==1)
                    YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
            }

            if(op_x>=op_y)
            {
                if(draw_on==1)
                    YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
                break;
            }
        }

        while(1)
        {  /* 计算下一点 */
            op_y--;
            draw_y--;
            if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_x +1)<=0 ) // 使用逐点比较法实现画圆弧
            {
                op_x++;
                draw_x++;
            }
            if(draw_on==1)
                YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
            pno_angle++;
            if( (pno_angle==startAngle)||(pno_angle==endAngle) )			// 若遇到起点或终点，画点开关取反
            {
                draw_on = 1-draw_on;
                if(draw_on==1)
                    YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
            }
            if(op_y<=0)
            {
                if(draw_on==1)
                    YWCANVAS_DrawLine(hLayer ,draw_x, draw_y, x0, y0, LineWidth,(U8*)color, YWGUI_WrapReviseOpMode(OpMode));
                break;
            }
        }
    }
 #endif
}

void YWGUI_WrapFillCircle(YWGUI_HSurface_T hSurface, S32 x0, S32 y0, S32 r, YWGUI_Pixel_T color, YWGUI_CANVAS_OpMode_T OpMode)
{
#if 0
    YWCANVAS_Handle_T hLayer;
    YWMID_ASSERT((color!=NULL) && (r>0));
    //YWMID_Trace((YWOS_TRACE_ERROR,"[FillBox] left=%d,top=%d,width=%d,height=%d,color=%#x\n",xPos1,yPos1,YWGUI_GET_WIDTH(xPos1,xPos2),YWGUI_GET_HEIGHT(yPos1,yPos2),color));
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[FillBox] Surface is invalid,return!\n"));
        return;
    }

    hLayer=YWGUI_WrapGetSurfaceLayer(hSurface);
    if(hLayer!=(YWCANVAS_Handle_T)0)
    {
        YWCANVAS_FillCircularity(hLayer, x0, y0, r, (U8*)color, YWGUI_WrapReviseOpMode(OpMode));
    }
#endif
}

void YWGUI_WrapFillTriangle(YWGUI_HSurface_T hSurface, S32 x1, S32 y1, S32 x2, S32 y2, S32 x3, S32 y3,YWGUI_Pixel_T color, YWGUI_CANVAS_OpMode_T OpMode)
{
    YWGUI_Handle_T hLayer;
    IDirectFBSurface *pSurface;
    YWMID_ASSERT((color!=NULL));
    //YWMID_Trace((YWOS_TRACE_ERROR,"[FillBox] left=%d,top=%d,width=%d,height=%d,color=%#x\n",xPos1,yPos1,YWGUI_GET_WIDTH(xPos1,xPos2),YWGUI_GET_HEIGHT(yPos1,yPos2),color));
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[FillBox] Surface is invalid,return!\n"));
        return;
    }

    hLayer=YWGUI_WrapGetSurfaceLayer(hSurface);
    if(hLayer!=(YWGUI_Handle_T)0)
    {
        YWGUI_Argb_T argb;
        YWGUI_Pixel2Argb(hSurface, color, &argb, NULL);
        pSurface = (IDirectFBSurface *)hLayer;
        DFBCHECK(pSurface->SetColor(pSurface, argb.r, argb.g, argb.b, argb.a));//r,g,b,a
        pSurface->FillTriangle(pSurface, x1, y1,  x2, y2, x3, y3);
    }
}

void YWGUI_WrapRectangle(YWGUI_HSurface_T hSurface,S32 xPos1, S32 yPos1, S32 xPos2, S32 yPos2,YWGUI_Pixel_T color,U32 penWidth, YWGUI_CANVAS_OpMode_T OpMode)
{

    YWGUI_Handle_T hLayer;
    U32 i=0;
    YWMID_ASSERT(color!=NULL);
    //YWMID_Trace((YWOS_TRACE_ERROR,"[Rectangle] left=%d,top=%d,width=%d,height=%d,penWidth=%d,color=%#x\n",xPos1,yPos1,YWGUI_GET_WIDTH(xPos1,xPos2),YWGUI_GET_HEIGHT(yPos1,yPos2),penWidth,color));
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[Rectangle] Surface is invalid,return!\n"));
        return;
    }


    if(penWidth==0)
    {
        return;
    }

    hLayer=YWGUI_WrapGetSurfaceLayer(hSurface);

    --xPos2;
    --yPos2;

    for(i=0;i<penWidth;i++)
    {
        //顶线
        YWGUI_WrapDrawLine(hSurface ,xPos1,yPos1,xPos2,yPos1, (U8*)color, penWidth,YWGUI_WrapReviseOpMode(OpMode));
        //右线
        YWGUI_WrapDrawLine(hSurface ,xPos2,yPos1,xPos2,yPos2, (U8*)color, penWidth,YWGUI_WrapReviseOpMode(OpMode));

        //底线
        YWGUI_WrapDrawLine(hSurface ,xPos2,yPos2,xPos1,yPos2, (U8*)color, penWidth,YWGUI_WrapReviseOpMode(OpMode));
        //左线
        YWGUI_WrapDrawLine(hSurface ,xPos1,yPos2,xPos1,yPos1, (U8*)color, penWidth,YWGUI_WrapReviseOpMode(OpMode));

        ++xPos1;
        ++yPos1;
        --xPos2;
        --yPos2;

        if(xPos1>xPos2 || yPos1 >yPos2)
        {
            break;
        }
    }
}

void YWGUI_WrapDrawCircle(YWGUI_HSurface_T hSurface,S32 x0, S32 y0, S32 r, YWGUI_Pixel_T color,U32 penWidth, YWGUI_CANVAS_OpMode_T OpMode)
{
#if 0
    YWCANVAS_Handle_T hLayer;
    U32 i=0;
    YWMID_ASSERT(color!=NULL);
    //YWMID_Trace((YWOS_TRACE_ERROR,"[Rectangle] left=%d,top=%d,width=%d,height=%d,penWidth=%d,color=%#x\n",xPos1,yPos1,YWGUI_GET_WIDTH(xPos1,xPos2),YWGUI_GET_HEIGHT(yPos1,yPos2),penWidth,color));
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[Rectangle] Surface is invalid,return!\n"));
        return;
    }
    if(0== penWidth || 0 == r)
    {
        return;
    }

    hLayer=YWGUI_WrapGetSurfaceLayer(hSurface);
    for(i=0;i<penWidth;i++)
    {
        if(r  <= i)
            break;
        YWCANVAS_DrawCircularity(hLayer, x0, y0, r-i, color, OpMode);
    }
#endif
}

void YWGUI_WrapDrawTriangle(YWGUI_HSurface_T hSurface,S32 x1, S32 y1, S32 x2, S32 y2, S32 x3, S32 y3, YWGUI_Pixel_T color,U32 penWidth, YWGUI_CANVAS_OpMode_T OpMode)
{
#if 0
    YWCANVAS_Handle_T hLayer;
    U32 i=0;
    YWMID_ASSERT(color!=NULL);
    //YWMID_Trace((YWOS_TRACE_ERROR,"[Rectangle] left=%d,top=%d,width=%d,height=%d,penWidth=%d,color=%#x\n",xPos1,yPos1,YWGUI_GET_WIDTH(xPos1,xPos2),YWGUI_GET_HEIGHT(yPos1,yPos2),penWidth,color));
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[Rectangle] Surface is invalid,return!\n"));
        return;
    }
    if(0== penWidth)
    {
        return;
    }

    hLayer=YWGUI_WrapGetSurfaceLayer(hSurface);
    for(i=0;i<penWidth;i++)
    {
        YWCANVAS_DrawTriangle(hLayer, x1, y1, x2, y2, x3, y3, color, OpMode);
    }
#endif
}
void YWGUI_WrapDrawLine(YWGUI_HSurface_T hSurface,S32 xPos1, S32 yPos1, S32 xPos2, S32 yPos2, YWGUI_Pixel_T color,U32 penWidth, YWGUI_CANVAS_OpMode_T OpMode)
{
    U32 i=0;
    YWGUI_Handle_T hLayer;
    IDirectFBSurface *pSurface;
    YWGUI_Argb_T argb;
    YWMID_ASSERT(color!=NULL);
    //YWMID_Trace((YWOS_TRACE_ERROR,"[DrawLine] point(%d,%d) to (%d,%d),penWidth=%d,color=%#x\n",xPos1,yPos1,xPos2,yPos2,penWidth,color));
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[DrawLine] Surface is invalid,return!\n"));
        return;
    }
    if(penWidth==0)
    {
        return;
    }

    hLayer=YWGUI_WrapGetSurfaceLayer(hSurface);

    pSurface = (IDirectFBSurface *)hLayer;
    YWGUI_Pixel2Argb(hSurface, color, &argb, NULL);
    DFBCHECK(pSurface->SetColor(pSurface, argb.r, argb.g, argb.b, argb.a ));//r,g,b,a

    if (xPos1==xPos2)
    {
        //竖线
        for (i=0;i<penWidth;i++)
        {
            pSurface->DrawLine (pSurface , xPos1+i,yPos1,xPos2+i,yPos2);
        }
    }
    else if(yPos1 == yPos2)
    {
        //横线
        for (i=0;i<penWidth;i++)
        {
            pSurface->DrawLine (pSurface , xPos1,yPos1+i,xPos2,yPos2+i);
        }
    }
    else
    {
        //斜线
        for (i=0;i<penWidth;i++)
        {
            pSurface->DrawLine (pSurface, xPos1+i,yPos1,xPos2+i,yPos2);
        }
    }
}

void YWGUI_WrapDrawPixel( YWGUI_HSurface_T hSurface, S32 x, S32 y,YWGUI_Pixel_T pixel)
{
#if 0
    YWCANVAS_Handle_T hLayer;
    YWMID_ASSERT(pixel!=NULL);
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[DrawPixel] Surface is invalid,return!\n"));
        return;
    }

    hLayer=YWGUI_WrapGetSurfaceLayer(hSurface);

    YWCANVAS_SetPixel(hLayer,x,y,(U8*)pixel);
#endif
}

void*  YWGUI_WrapVMemMalloc(U32 Size)
{

    void *pMem;
    #if 0
    pMem = YWGUI_Malloc(Size);

    if(pMem!=NULL)
    {
        pMem = (void *)(0xa0000000|(U32)pMem);
    }
    #endif
     pMem = YWOS_CallocNcache(1, Size);
    return pMem;
}

void YWGUI_WrapVMemFree(void *pMem)
{
#if 0
    U32 addr = (U32)pMem;

    if(addr>0xa0000000)
    {
        addr &= 0x0fffffff;
        addr |= 0x80000000;

        pMem = (void*)addr;
    }
        /**/
    YWGUI_MemFree(pMem);
#endif
    YWOS_FreeNcache(pMem);
}
/*参数说明:
x:输出区域的x坐标
y:输出区域的y坐标
w:输出区域的宽度
h:输出区域的高度
*/
void YWGUI_WrapPutBox( YWGUI_HSurface_T hSurface, S32 x, S32 y, S32 w, S32 h, S32 pitch, void *buf, YWGUI_GraphCell_T* ptGraphCell)
{
    YWGUI_WrapPutBoxMask (hSurface, x, y, w, h, pitch, buf, NULL, ptGraphCell);
}

void YWGUI_WrapPutBoxMask ( YWGUI_HSurface_T hSurface, S32 x, S32 y, S32 w, S32 h, S32 pitch, void *buf,YWGUI_Pixel_T pixelMask, YWGUI_GraphCell_T* ptGraphCell)
{
    YW_ErrorType_T errCode=YW_NO_ERROR;
    U8     * pDst;
    S32   nTempSize;
    YWGUI_Handle_T hLayer;
    DFBRectangle   SrcRect={0,0,0,0};
    DFBRectangle   DstRect={0,0,0,0};
    //YWMID_DibitmapOp_T tOp;
    U8  bpp=0;
    YWMID_DibitmapOp_T* pOp = NULL;
    DFBSurfacePixelFormat PixelFormat;
    IDirectFBSurface  * pSurface;
    IDirectFBSurface * pImgSurface = NULL;
    DFBSurfaceDescription dsc;
    IDirectFB  *dfb   = g_tWrapInfo.pstDfb;
    U32 uImgWidth, uImgHeight, uImgPitch, uImgSize;
    U8 * pImgData;
    U8 * pPalette = NULL;
    U32 bitsPerPixel;
    U32 uBltFlag = DSBLIT_BLEND_ALPHACHANNEL;
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[DrawBitmap] Surface is invalid,return!\n"));
        return;
    }
    bitsPerPixel = YWGUI_GetBitsPerPixel(hSurface);
    hLayer=YWGUI_WrapGetSurfaceLayer(hSurface);
    if(hLayer==(YWGUI_Handle_T)0)
    {
        return;
    }

    if (w <= 0 || h<=0)
    {
        return;
    }


    pSurface = (IDirectFBSurface * )hLayer;

    YWGUI_MemSet(&PixelFormat,0,sizeof(DFBSurfacePixelFormat));

    //errCode = YWCANVAS_GetPixelFormat(hLayer,&PixelFormat);
    DFBCHECK( pSurface->GetPixelFormat(pSurface, &PixelFormat));
    if(NULL != ptGraphCell)
    {
        YWGUI_BitmapData_T * ptBmpData = (YWGUI_BitmapData_T *) ptGraphCell->ptBmp;
        pOp = &(ptGraphCell->Op);

        bpp = ptBmpData->bmBytesPerPixel;
        bitsPerPixel = ptBmpData->bmBitsPerPixel;
        switch(ptBmpData->bmType&YWGUI_BMP_FORMAT_MASK)
        {
            case YWGUI_BMP_FORMAT_BGRA_8888:
                PixelFormat = DSPF_ARGB;
                break;
           case YWGUI_BMP_FORMAT_BGR_888:
                PixelFormat= DSPF_RGB24;
                break;
           case YWGUI_BMP_FORMAT_CLUT_8:
                PixelFormat = DSPF_LUT8;
                //Bitmap.PixelFormat.Palette = (YWCANVAS_Palette_T*)ptBmpData->bmpPalette;
                pPalette = ptBmpData->bmpPalette;
                break;
           case YWGUI_BMP_FORMAT_BGR_565:
                PixelFormat= DSPF_RGB555;
                break;
            case YWGUI_BMP_FORMAT_BGRA_5551:
                PixelFormat= DSPF_ARGB1555;
                break;
            case YWGUI_BMP_FORMAT_BGRA_4444:
                PixelFormat= DSPF_ARGB4444;
                break;
            default:
                return;
        }

    }
    else
    {

        bpp = (bitsPerPixel+7)>>3;
    }


    uImgWidth = (U32)w;
    uImgHeight   = (U32)h;
    if(pitch!=0)
    {
        uImgPitch = pitch;
    }
    else
    {
        uImgPitch = w*bpp;
    }
    uImgSize = uImgHeight*uImgPitch;
    pImgData    = (void *)buf;
    //Bitmap.Size1    = Bitmap.Pitch*h;

    if ( x <= 0 )
    {
        SrcRect.x  = (-x);
        DstRect.x  = 0;

        if(w < (-x))
        {
            return;
        }

        SrcRect.w = (U32)(w+x);//注意,此时x<0,相当于w-|x|
        DstRect.w = SrcRect.w;
    }
    else
    {
        SrcRect.x  = 0;
        DstRect.x  = x;

        SrcRect.w = (U32)w;
        DstRect.w = SrcRect.w;
    }

    if ( y < 0 )
    {
        SrcRect.y  = (-y);
        DstRect.y  = 0;

        if(h <= (-y))
        {
            return;
        }

        SrcRect.h = (U32)(h+y);//注意,此时y<0,相当于h-|y|
        DstRect.h =SrcRect.h /**/;
    }
    else
    {
        SrcRect.y  = 0;
        DstRect.y  = y;

        SrcRect.h = (U32)h;
        DstRect.h = SrcRect.h;
    }

    if ((S32)SrcRect.w <= 0 || (S32)SrcRect.h<=0)
    {
        return;
    }

    /*added by sly, 2009-11-11*/
    pDst = (U8*)pImgData;
    if(NULL!=pOp)
    {
        U32 uNewPitch;
        //OpMode = 1<<(pOp->Flags&YWMID_DIBMP_OP_MODE_MASK);
        //ColorKeyMode = (pOp->Flags&YWMID_DIBMP_COLOR_KEY_MODE_MASK) >> 8;

        SrcRect.x = pOp->SrcRect.X;
        SrcRect.y = pOp->SrcRect.Y;
        SrcRect.w = pOp->SrcRect.W;
        SrcRect.h = pOp->SrcRect.H;

        DstRect.x = pOp->DstRect.X+x;
        DstRect.y = pOp->DstRect.Y+y;
        DstRect.w = pOp->DstRect.W;
        DstRect.h = pOp->DstRect.H;

        #if 1
        switch( pOp->Flags&YWMID_DIBMP_OUTPUT_ROTATE_MASK)
        {
            case YWMID_DIBMP_OUTPUT_ROTATE_90:
                YWMID_BmpComputePitch(bitsPerPixel, uImgHeight, uNewPitch);
                uImgSize = uImgWidth*uNewPitch;
                pDst = YWGUI_WrapVMemMalloc(uImgSize);
                if(NULL==pDst)
                    return;
                YWMID_BmpDeasilRotate90Degrees(pDst, (U8*)pImgData, bpp, uImgWidth, uImgHeight, uImgPitch, uNewPitch);
                pImgData = (void*)pDst;
                uImgPitch = uNewPitch;
                nTempSize= uImgWidth;
                uImgWidth = uImgHeight;
                uImgHeight = nTempSize;

                SrcRect.x = pOp->SrcRect.Y;
                SrcRect.y = pOp->SrcRect.X;
                SrcRect.w = pOp->SrcRect.H;
                SrcRect.h = pOp->SrcRect.W;
                /*uBltFlag |= DSBLIT_ROTATE90;*/
                break;
            case YWMID_DIBMP_OUTPUT_ROTATE_180:
                pDst = YWGUI_WrapVMemMalloc(uImgSize);
                if(NULL==pDst)
                    return;
                YWMID_BmpDeasilRotate180Degrees(pDst,  (U8*)pImgData, bpp, uImgWidth, uImgHeight, uImgPitch);
                pImgData = (void*)pDst;
                /*uBltFlag |= DSBLIT_ROTATE180;*/
                break;
            case YWMID_DIBMP_OUTPUT_ROTATE_270:
                 YWMID_BmpComputePitch(bitsPerPixel, uImgHeight, uNewPitch);
                uImgSize = uImgWidth*uNewPitch;
                pDst = YWGUI_WrapVMemMalloc(uImgSize);
                if(NULL==pDst)
                    return;
                YWMID_BmpDeasilRotate270Degrees(pDst, (U8*)pImgData, bpp, uImgWidth, uImgHeight, uImgPitch, uNewPitch);
                pImgData = (void*)pDst;
                uImgPitch = uNewPitch;
                nTempSize= uImgWidth;
                uImgWidth = uImgHeight;
                uImgHeight = nTempSize;

                SrcRect.x = pOp->SrcRect.Y;
                SrcRect.y = pOp->SrcRect.X;
                SrcRect.w = pOp->SrcRect.H;
                SrcRect.h = pOp->SrcRect.W;
                /*uBltFlag |= DSBLIT_ROTATE270;*/
                break;
            default:
                break;
        }

         if( pOp->Flags&YWMID_DIBMP_OUTPUT_VFLIP)
        {
            pDst = YWGUI_WrapVMemMalloc(uImgSize);
            if(NULL==pDst)
            {
                 if((U32)pImgData!= (U32)buf)
                {
                    YWGUI_WrapVMemFree(pImgData);
                }
                return;
            }
            YWMID_BmpVFlip(pDst, (U8*)pImgData, bpp, uImgWidth, uImgHeight, uImgPitch);
            if((U32)pImgData!= (U32)buf)
            {
                YWGUI_WrapVMemFree(pImgData);
            }
            pImgData = (void *)pDst;
            /*uBltFlag |= DSBLIT_FLIP_VERTICAL;*/
        }

        if( pOp->Flags&YWMID_DIBMP_OUTPUT_HFLIP)
        {

            uImgSize= uImgWidth*uImgHeight*bpp;
            pDst = YWGUI_WrapVMemMalloc(uImgSize);
            if(NULL==pDst)
            {
                 if((U32)pImgData!= (U32)buf)
                {
                    YWGUI_WrapVMemFree(pImgData);
                }
                return;
            }
            YWMID_BmpHFlip(pDst, (U8*)pImgData, bpp, uImgWidth, uImgHeight, uImgPitch);
            if((U32)pImgData!= (U32)buf)
            {
                YWGUI_WrapVMemFree(pImgData);
            }
            pImgData = (void*)pDst;
            uImgPitch = uImgWidth*bpp;
           /*uBltFlag |= DSBLIT_FLIP_HORIZONTAL;*/
        }

   #endif

        switch( pOp->Flags&YWMID_DIBMP_OUTPUT_MODE_MASK)
        {
            case YWMID_DIBMP_OUTPUT_MODE_CENTER:/*根据GraphCell居中而不是根据输出区域居中*/

                DstRect.w = SrcRect.w;
                DstRect.h = SrcRect.h;
                if((U32)pOp->DstRect.W >  SrcRect.w)
                {
                    DstRect.x += (pOp->DstRect.W - SrcRect.w)>>1;
                }
                if((U32)pOp->DstRect.H > SrcRect.h)
                {
                    DstRect.y += (pOp->DstRect.H-SrcRect.h)>>1;
                }
                break;
            case YWMID_DIBMP_OUTPUT_MODE_ZOOM:/*缩放*/
                DstRect.w = pOp->DstRect.W;
                DstRect.h = pOp->DstRect.H;
                break;
            case YWMID_DIBMP_OUTPUT_MODE_AUTOZOOM:
            {
                if (SrcRect.w > pOp->DstRect.W)
                {
                    //宽超出
                    if (SrcRect.h > pOp->DstRect.H)
                    {
                        //宽高都超出
                        U32 uZoomHeight = (SrcRect.h * pOp->DstRect.W) / SrcRect.w;
                        if (uZoomHeight > pOp->DstRect.H)
                        {
                            //高超出比较多，所以高满屏，宽较窄
                            U32 uZoomWidth = (SrcRect.w * pOp->DstRect.H) / SrcRect.h;
                            DstRect.x = x + (pOp->DstRect.W - uZoomWidth) / 2;
                            DstRect.y = y + 0;
                            DstRect.w = uZoomWidth;
                            DstRect.h = pOp->DstRect.H;
                        }
                        else
                        {
                            //宽超出比较多，所以宽满屏，高较扁
                            DstRect.x = x + 0;
                            DstRect.h = y + (pOp->DstRect.H - uZoomHeight) / 2;
                            DstRect.w = pOp->DstRect.W;
                            DstRect.h = uZoomHeight;
                        }
                    }
                    else
                    {
                        //宽超出，高不足，所以宽满屏，高较扁
                        U32 uZoomHeight = (SrcRect.h * pOp->DstRect.W) / SrcRect.w;
                        DstRect.x = x + 0;
                        DstRect.y = y + (pOp->DstRect.H - uZoomHeight) / 2;
                        DstRect.w = pOp->DstRect.W;
                        DstRect.h = uZoomHeight;
                    }
                }
                else
                {
                    //宽不足
                    if (SrcRect.h > pOp->DstRect.H)
                    {
                        //宽不足，高超出，所以高满屏，宽较窄
                        U32 uZoomWidth = (SrcRect.w * pOp->DstRect.H) / SrcRect.h;
                        DstRect.x = x + (pOp->DstRect.W - uZoomWidth) / 2;
                        DstRect.y = y + 0;
                        DstRect.w = uZoomWidth;
                        DstRect.h = pOp->DstRect.H;
                    }
                    else
                    {
                        //宽高都不足
                        U32 uZoomHeight = (SrcRect.h * pOp->DstRect.W) / SrcRect.w;
                        if (uZoomHeight > pOp->DstRect.H)
                        {
                            //宽不足比较多，所以高满屏，宽较窄
                            U32 uZoomWidth = (SrcRect.w * pOp->DstRect.H) / SrcRect.h;
                            DstRect.x = x + (pOp->DstRect.W - uZoomWidth) / 2;
                            DstRect.y = y + 0;
                            DstRect.w = uZoomWidth;
                            DstRect.h = pOp->DstRect.H;
                        }
                        else
                        {
                            //高不足比较多，所以宽满屏，高较扁
                            DstRect.x = x + 0;
                            DstRect.y = y + (pOp->DstRect.H - uZoomHeight) / 2;
                            DstRect.w = pOp->DstRect.W;
                            DstRect.h = uZoomHeight;
                        }
                    }
                }
                break;
            }
            case YWMID_DIBMP_OUTPUT_MODE_TILE:
                {
                    S32 widthPer=0;
                    S32 heightPer=0;
                    S32 widthLine=0;
                    S32 xPos=DstRect.x;
                    S32 boxH = pOp->DstRect.H;
                    S32 boxW= pOp->DstRect.W;
                    S32 bmpWidth=SrcRect.w;
                    S32 bmpHeight=SrcRect.h;
                    DstRect.w = bmpWidth;
                    DstRect.h = bmpHeight;

                    dsc.flags = DSDESC_CAPS|DSDESC_PREALLOCATED|DSDESC_WIDTH |DSDESC_HEIGHT | DSDESC_PIXELFORMAT;
                    dsc.caps = DSCAPS_SYSTEMONLY;
                    dsc.preallocated[0].data = pImgData;
                    dsc.preallocated[0].pitch = uImgPitch;
                    dsc.preallocated[1].data = NULL;
                    dsc.preallocated[1].pitch = 0;
                    dsc.width = uImgWidth;
                    dsc.height = uImgHeight;
                    dsc.pixelformat = PixelFormat;
                    if(pPalette)
                    {
                        dsc.palette.entries = (DFBColor *)pPalette;
                        dsc.flags|=DSDESC_PALETTE;
                        dsc.palette.size = 256;
                    }
                    DFBCHECK(dfb->CreateSurface(dfb, &dsc, &pImgSurface));

                    while(boxH>0)
                    {
                        if((S32)bmpHeight>=boxH)
                        {
                            heightPer = boxH;
                        }
                        else
                        {
                            heightPer = (S32)bmpHeight;
                        }

                        widthLine=boxW;

                        DstRect.x = xPos;/*复位x坐标*/
                        while(widthLine>0)
                        {
                            if((S32)bmpWidth>=widthLine)
                            {
                                widthPer = widthLine;
                            }
                            else
                            {
                                widthPer = (S32)bmpWidth;
                            }

                           // YWGUI_GalFillBoxWithBitmap(hdc,xPos,y,widthPer,heightPer,hBitmap);
                            //errCode =YWCANVAS_DrawBitmap(hLayer,&Bitmap, &SrcRect,&DstRect, OpMode, ColorKeyMode);
                            //xPos+=widthPer;
                            if(NULL!=pixelMask)
                            {
                                YWGUI_Argb_T argb;
                                YWGUI_Pixel2Argb(hSurface, pixelMask, &argb, NULL);
                                DFBCHECK(pImgSurface->SetSrcColorKey (pImgSurface, argb.r, argb.g, argb.b ));//r,g,b
                            }

                            pSurface->SetBlittingFlags(pSurface, uBltFlag);
                            //DFBCHECK(pSurface->StretchBlit (pSurface, pImgSurface, &SrcRect, &DstRect));
                            DFBCHECK(pSurface->Blit (pSurface, pImgSurface, &SrcRect, DstRect.x, DstRect.y));
                            DstRect.x  +=widthPer;
                            widthLine-=widthPer;
                        }

                        //y+=heightPer;
                        DstRect.y +=heightPer;
                        boxH-=heightPer;
                }

                pImgSurface->Release(pImgSurface);
              }
                if((U32)pImgData!= (U32)buf)
                {
                    YWGUI_WrapVMemFree(pImgData);
                }
                    return;
            case YWMID_DIBMP_OUTPUT_MODE_CLIP:
            default:
                break;
        }
    }

    dsc.flags = DSDESC_CAPS|DSDESC_PREALLOCATED|DSDESC_WIDTH |DSDESC_HEIGHT | DSDESC_PIXELFORMAT;
    dsc.caps = DSCAPS_SYSTEMONLY;
    dsc.preallocated[0].data = pImgData;
    dsc.preallocated[0].pitch = uImgPitch;
    dsc.preallocated[1].data = NULL;
    dsc.preallocated[1].pitch = 0;
    dsc.width = uImgWidth;
    dsc.height = uImgHeight;
    dsc.pixelformat = PixelFormat;
    if(pPalette)
    {
        dsc.palette.entries = (DFBColor *)pPalette;
        dsc.palette.size = 256;
        dsc.flags|=DSDESC_PALETTE;
    }

    DFBCHECK(dfb->CreateSurface(dfb, &dsc, &pImgSurface));
    if(NULL!=pixelMask)
    {
        YWGUI_Argb_T argb;
        YWGUI_Pixel2Argb(hSurface, pixelMask, &argb, NULL);
        DFBCHECK(pImgSurface->SetSrcColorKey (pImgSurface, argb.r, argb.g, argb.b ));//r,g,b
    }
    pSurface->SetBlittingFlags(pSurface, uBltFlag);
    DFBCHECK(pSurface->StretchBlit (pSurface, pImgSurface, &SrcRect, &DstRect));
    pImgSurface->Release(pImgSurface);
    if((U32)pImgData != (U32)buf)
    {
        YWGUI_WrapVMemFree(pImgData);
    }
}

void YWGUI_WrapGetBox( YWGUI_HSurface_T hSurface, S32 x, S32 y, S32 w, S32 h, void *buf)
{
    YWGUI_Handle_T hLayer;
    YW_ErrorType_T errCode=YW_NO_ERROR;
    IDirectFBSurface  * pSurface;
    IDirectFBSurface * pImgSurface = NULL;
    DFBSurfaceDescription dsc;
    IDirectFB  *dfb   = g_tWrapInfo.pstDfb;
    DFBRectangle 	rect;
    S32 pitch;
    U32 bitsPerPixel;

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    if(!YWGUI_WrapSurfaceIsValid(hSurface))
    {
        //YWMID_Trace((YWOS_TRACE_ERROR,"[DrawBitmapMask] Surface is invalid,return!\n"));
        return;
    }

    hLayer=YWGUI_WrapGetSurfaceLayer(hSurface);
    if(hLayer==(YWGUI_Handle_T)0)
    {
        return;
    }
    pSurface = (IDirectFBSurface *)hLayer;
    bitsPerPixel = YWGUI_GetBitsPerPixel(hSurface);
    pitch = ((bitsPerPixel+7)>>3)*w;

    DFBCHECK(pSurface->Read (pSurface,	&rect, buf, pitch));

}





/***********************************************************************
函数名称: YWGUI_WrapDib2Ddbitmap
函数功能: 设备无关位图向设备相关位图转换
参    数:   hdc[in] -- 设备DC
            ptDibmp[in] -- 设备无关位图结构指针
            hBitmap[out] -- 设备相关位图句柄(即其结构指针)
返 回 值:   YW_NO_ERROR -- OK
            否则返回YWGUI_ERROR_MEM_NO_ENOUGH/YWGUI_ERROR_NO_SUPPORTED
说    明:
修改记录:
************************************************************************/
YW_ErrorType_T YWGUI_WrapDib2DdbGraphCell (YWGUI_HDc_T hdc,  const YWGUI_GraphCell_T * ptDibGraphCell,YWGUI_GraphCell_T* ptDdbGraphCell)
{
    YWGUI_DeviceContext_P pdc=YWGUI_Hdc2Pdc (hdc);
    YWMID_Palette_T      *pDIBPalette = NULL;
    const U8*             pDIBitsData=NULL;
    U32                   bpp;//每象素多少位
    const YWMID_DibitmapData_T * ptDibmp;
    YWGUI_BitmapData_T * ptBitmap;
    S32 nPaletteBytes = 0;

    YWMID_ASSERT((pdc!=NULL && ptDibGraphCell!=NULL && ptDdbGraphCell!=NULL));

    ptDdbGraphCell->Op = ptDibGraphCell->Op;

    ptDibmp = (YWMID_DibitmapData_T *)ptDibGraphCell->ptBmp;
    ptBitmap = (YWGUI_BitmapData_T *)ptDdbGraphCell->ptBmp;
    YWMID_ASSERT((ptDibmp!=NULL)&&(ptBitmap!=NULL));

    if((ptDdbGraphCell->Op.DstRect.W ==0) || (ptDdbGraphCell->Op.DstRect.H ==0))
    {
        ptDdbGraphCell->Op.DstRect.W = ptDibmp->W;
        ptDdbGraphCell->Op.DstRect.H = ptDibmp->H;
    }

    bpp = YWGUI_GetBitsPerPixel(pdc->hSurface);
    YWMID_ASSERT((bpp>0));

    //判断位图数据部分是否需要转换
    if(!YWGUI_WrapIsNeedConvDibData(ptDibmp,pdc->hSurface))
    {
        //不需要转换，设备无关位图实际上已是设备相关
        //YWMID_Trace((YWOS_TRACE_ERROR,"[Dib2Ddbitmap] do not convert bitmap(w=%d,h=%d,Depth=%d)\n",ptDibmp->W,ptDibmp->H,ptDibmp->Depth));

        bpp = ptDibmp->Depth;
        //ptBitmap->bIsNewBits = FALSE;
        //ptBitmap->bmBits =  (U8*)ptDibmp->pData;
        ptBitmap->bmType = YWGUI_BMP_TYPE_NORMAL;
        ptBitmap->bmBitsPerPixel = bpp;
        ptBitmap->bmBytesPerPixel = (bpp+7)/8;

        ptBitmap->bmWidth = ptDibmp->W;
        ptBitmap->bmHeight = ptDibmp->H;

        ptBitmap->bmType &= ~YWMID_DIBMP_FORMAT_MASK;
        switch(ptDibmp->Flags&YWMID_DIBMP_FORMAT_MASK)
        {
            case YWMID_DIBMP_FORMAT_BGRA_8888:
                ptBitmap->bmType |= YWGUI_BMP_FORMAT_BGRA_8888;
                break;
           case YWMID_DIBMP_FORMAT_BGR_888:
                ptBitmap->bmType |= YWGUI_BMP_FORMAT_BGR_888;
                break;
           case YWMID_DIBMP_FORMAT_CLUT_8:
                ptBitmap->bmType |= YWGUI_BMP_FORMAT_CLUT_8;
                nPaletteBytes = 256* sizeof(YWMID_Palette_T);
                break;
           case YWMID_DIBMP_FORMAT_BGR_565:
                ptBitmap->bmType |= YWGUI_BMP_FORMAT_BGR_565;
                break;
           case YWMID_DIBMP_FORMAT_BGRA_5551:
                ptBitmap->bmType |= YWGUI_BMP_FORMAT_BGRA_5551;
                break;
           case YWMID_DIBMP_FORMAT_BGRA_4444:
                ptBitmap->bmType |= YWGUI_BMP_FORMAT_BGRA_4444;
                break;
            default:
                return YWMID_ERROR_FEATURE_NOT_SUPPORTED;
        }

        if((ptDdbGraphCell->Op.Flags&YWMID_DIBMP_COPY_BMPDATA) == YWMID_DIBMP_COPY_BMPDATA)
        {
            ptBitmap->bIsNewBits = TRUE;
            ptBitmap->bmBits = YWGUI_VMemMalloc(ptDibmp->Bytes + nPaletteBytes);
            ptBitmap->bmpPalette = NULL;
            if(NULL!= ptBitmap->bmBits)
            {
                YWLIB_Memcpy(ptBitmap->bmBits, ptDibmp->pData, ptDibmp->Bytes);

                if(0!= nPaletteBytes)
                {
                    ptBitmap->bmpPalette = ptBitmap->bmBits+ptDibmp->Bytes;
                    YWLIB_Memcpy(ptBitmap->bmpPalette, ptDibmp->pPalette, nPaletteBytes);

                }
            }
        }
        else
        {
              ptBitmap->bIsNewBits = FALSE;
              ptBitmap->bmpPalette =(U8*) ptDibmp->pPalette;
              ptBitmap->bmBits = (U8*)ptDibmp->pData;
        }

        if(ptDibmp->Pitch!=0)
        {
            ptBitmap->bmPitch = ptDibmp->Pitch;
        }
        else
        {
            ptBitmap->bmPitch = ptDibmp->W * ptBitmap->bmBytesPerPixel;
        }


        ptBitmap->bmAlpha = 0xFF;/*这个位经常没赋值，强制不透明*/

        switch(ptDibmp->Flags & YWMID_DIBMP_ALPHA_MASK)
        {
            case YWMID_DIBMP_ALPHA_GLOBAL:
                ptBitmap->bmType |= YWGUI_BMP_TYPE_GLOBALALPHA;
                ptBitmap->bmAlpha = ptDibmp->Alpha;
                break;
            case YWMID_DIBMP_ALPHA_LOCAL:
                ptBitmap->bmType |= YWGUI_BMP_TYPE_LOCALALPHA;
                break;
            default:
                break;

        }

        if(ptDibmp->Flags &YWMID_DIBMP_COLOR_KEY_MASK)
        {
            //有透明色标识
            if(ptDibmp->Depth<=8)
            {
                U32 nQuadColors=0;
                YWMID_Palette_P pQuad=NULL;

                //断定不是私有的调色板
                YWMID_ASSERT((ptDibmp->pPalette ==NULL));

                //ptBitmap->bmColorKey = ptDibmp->transparent;

                YWGUI_GetGlobalQuad(&nQuadColors, &pQuad);
                YWMID_ASSERT((nQuadColors>0 && nQuadColors>ptDibmp->ColorKey[0]));

                YWGUI_AColorMap2Pixel(pdc->hSurface,
                    YWGUI_MAKE_RGBA( pQuad[ptDibmp->ColorKey[0]].Alpha,
                                    pQuad[ptDibmp->ColorKey[0]].Red,
                                    pQuad[ptDibmp->ColorKey[0]].Green,
                                    pQuad[ptDibmp->ColorKey[0]].Blue),
                                    ptBitmap->bmColorKey);
            }
            else
            {
                YWGUI_ColorMap2Pixel(pdc->hSurface,YWGUI_MAKE_RGBA(ptDibmp->ColorKey[0], ptDibmp->ColorKey[1],ptDibmp->ColorKey[2],ptDibmp->ColorKey[3]), ptBitmap->bmColorKey, FALSE);
            }

            ptBitmap->bmType|=YWGUI_BMP_TYPE_COLORKEY;
        }

        return YW_NO_ERROR;
    }

    YWMID_Trace((YWOS_TRACE_ERROR,"[Dib2Ddbitmap] convert bitmap(w=%d,h=%d,Depth=%d)\n",ptDibmp->W,ptDibmp->H,ptDibmp->Depth));

    //需要转换
    ptBitmap->bmBits =  YWGUI_VMemMalloc(ptDibmp->W *ptDibmp->H*((bpp+7)/8));
    if(ptBitmap->bmBits==NULL)
    {
        return YWGUI_ERROR_MEM_NO_ENOUGH;
    }
    ptBitmap->bIsNewBits = TRUE;

    ptBitmap->bmType = YWGUI_BMP_TYPE_NORMAL;
    ptBitmap->bmBitsPerPixel = bpp;
    ptBitmap->bmBytesPerPixel = (bpp+7)/8;

    ptBitmap->bmWidth = ptDibmp->W;
    ptBitmap->bmHeight = ptDibmp->H;
    //ptBitmap->bmPitch = ptDibmp->W * ptBitmap->bmBytesPerPixel;

   ptBitmap->bmPitch = ptDibmp->W * ptBitmap->bmBytesPerPixel;


    if(ptDibmp->Depth<=8)
    {
        if(ptDibmp->pPalette!=NULL)
        {
            pDIBPalette = ptDibmp->pPalette;
        }
        else
        {
            //获取全局调色板
            YWGUI_GetGlobalQuad(NULL, &pDIBPalette);
        }
    }

    switch(ptDibmp->Flags & YWMID_DIBMP_ALPHA_MASK)
    {
        case YWMID_DIBMP_ALPHA_GLOBAL:
            ptBitmap->bmType |= YWGUI_BMP_TYPE_GLOBALALPHA;
            ptBitmap->bmAlpha = ptDibmp->Alpha;
            break;
        case YWMID_DIBMP_ALPHA_LOCAL:
            ptBitmap->bmType |= YWGUI_BMP_TYPE_LOCALALPHA;
            break;
        default:
            break;
    }



    if(ptDibmp->Flags &YWMID_DIBMP_COLOR_KEY_MASK)
    {
        //有透明色标识
        if(ptDibmp->Depth<=8)
        {
            YWMID_ASSERT((pDIBPalette !=NULL));

            //使用了调色板
            YWGUI_ColorMap2Pixel(pdc->hSurface,
                YWGUI_MAKE_RGB( pDIBPalette[ptDibmp->ColorKey[0]].Red,
                                pDIBPalette[ptDibmp->ColorKey[0]].Green,
                                pDIBPalette[ptDibmp->ColorKey[0]].Blue),
                                ptBitmap->bmColorKey, FALSE);
        }
        else
        {
            YWGUI_ColorMap2Pixel(pdc->hSurface,YWGUI_MAKE_RGB(ptDibmp->ColorKey[1],ptDibmp->ColorKey[2],ptDibmp->ColorKey[3]), ptBitmap->bmColorKey, FALSE);
        }

        ptBitmap->bmType|=YWGUI_BMP_TYPE_COLORKEY;
    }

    pDIBitsData = ptDibmp->pData;

    switch (ptDibmp->Depth)
    {
        case 1:
            YWGUI_WrapExpandMonoDIBitmap (hdc, ptDibmp->W, ptDibmp->H,
                            pDIBitsData,ptDibmp->Pitch, ptDibmp->Flags & YWMID_DIBMP_FLOW_MASK,
                            pDIBPalette,ptBitmap->bmPitch,ptBitmap->bmBits);
            break;
        case 4:
            YWGUI_WrapExpand16DIBitmap (hdc, ptDibmp->W, ptDibmp->H,
                            pDIBitsData,ptDibmp->Pitch, ptDibmp->Flags& YWMID_DIBMP_FLOW_MASK,
                            pDIBPalette,ptBitmap->bmPitch,ptBitmap->bmBits);
            break;
        case 8:
            YWGUI_WrapExpand256DIBitmap (hdc, ptDibmp->W, ptDibmp->H,
                           pDIBitsData,ptDibmp->Pitch, ptDibmp->Flags & YWMID_DIBMP_FLOW_MASK,
                           pDIBPalette,ptBitmap->bmPitch,ptBitmap->bmBits);
            break;
        case 24:
            YWGUI_WrapRegroup24DIBitmap (hdc, ptDibmp->W, ptDibmp->H,
                           pDIBitsData,ptDibmp->Pitch, ptDibmp->Flags & YWMID_DIBMP_FLOW_MASK,
                           ptDibmp->Flags & YWMID_DIBMP_FORMAT_MASK,ptBitmap->bmPitch,ptBitmap->bmBits);
            break;
        case 32:
            YWGUI_WrapRegroup32DIBitmap(hdc, ptDibmp->W, ptDibmp->H,
                           pDIBitsData,ptDibmp->Pitch, ptDibmp->Flags & YWMID_DIBMP_FLOW_MASK,
                           ptDibmp->Flags & YWMID_DIBMP_FORMAT_MASK,ptBitmap->bmPitch,ptBitmap->bmBits);
            break;
        default:
            YWMID_ASSERT((0));
            YWGUI_VMemFree(ptBitmap->bmBits);
            YWGUI_MemSet(ptBitmap,0,sizeof(YWGUI_BitmapData_T));
            return YWGUI_ERROR_NO_SUPPORTED;
    }

    return YW_NO_ERROR;
}


/***********************************************************************
函数名称: YWGUI_WrapFillBoxWithBmp
函数功能: 用设备相关位图对象填充矩形框(默认居中)
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
修改记录:
                添加了各种风格的处理, added by sly, 2009-11-10
************************************************************************/
YW_ErrorType_T  YWGUI_WrapFillBoxWithGraphCell (YWGUI_HDc_T hdc, S32 x, S32 y, S32 w, S32 h,
                              YWGUI_HGraphCell_T hDdbGraphCell)
{
    YWGUI_GraphCell_T*  ptDdbGraphCell = (YWGUI_GraphCell_T*)hDdbGraphCell;
    YWGUI_BitmapData_T * ptBmpData;
    S32 widthBitmap;
    S32 heightBitmap;
    YWGUI_DeviceContext_P pdc=YWGUI_Hdc2Pdc (hdc);
    YWGUI_Rect_T    rcOutput;
    YWGUI_GraphCell_T  tGraphCell;

    if(hdc==YWGUI_NULL_HANDLE)
    {
        return YWGUI_ERROR_INVALID_HANDLE;
    }

    if (ptDdbGraphCell==NULL)
    {
        return YW_NO_ERROR;
    }
    ptBmpData = (YWGUI_BitmapData_T *) ptDdbGraphCell->ptBmp;
    if( ptBmpData->bmBits == NULL||ptBmpData->bmWidth <= 0 || ptBmpData->bmHeight <= 0 )
    {
        return YW_NO_ERROR;
    }
    tGraphCell.ptBmp = ptDdbGraphCell->ptBmp;
    tGraphCell.Op = ptDdbGraphCell->Op;
    widthBitmap = ptBmpData->bmWidth;
    heightBitmap = ptBmpData->bmHeight;
    if(w<=0)
    {
        w = widthBitmap;
    }
    if (h <= 0)
    {
        h = heightBitmap;
    }
    /*added by sly, 2009-11-10*/
    if((tGraphCell.Op.SrcRect.W==0) || (tGraphCell.Op.SrcRect.H==0))
    {
        tGraphCell.Op.SrcRect.X =0;
        tGraphCell.Op.SrcRect.Y=0;
        tGraphCell.Op.SrcRect.W = widthBitmap;
        tGraphCell.Op.SrcRect.H = heightBitmap;
    }

    if((tGraphCell.Op.DstRect.W==0) || (tGraphCell.Op.DstRect.H==0))/*如果w或h无效，则只画一张图*/
    {
        //tBmpOp.DstRect.X = x;
        //tBmpOp.DstRect.Y = y;
        tGraphCell.Op.DstRect.W = tGraphCell.Op.SrcRect.W;
        tGraphCell.Op.DstRect.H = tGraphCell.Op.SrcRect.H;
    }
    /*由逻辑坐标转为屏幕坐标*/
    //YWGUI_POINT_LP2SP(pdc, &tBmpOp.DstRect.X, &tBmpOp.DstRect.Y);
    /*end of added*/

    YWGUI_LockEcrgn(hdc);

    // Transfer logical to device to screen here.
    YWGUI_SetRect(&rcOutput,x,y,YWGUI_RECT_RIGHT(x,w),YWGUI_RECT_BOTTOM(y,h));
    YWGUI_POINT_LP2SP(pdc, &rcOutput.left, &rcOutput.top);
    YWGUI_POINT_LP2SP(pdc, &rcOutput.right, &rcOutput.bottom);
    YWGUI_NormalizeRect (&rcOutput);

    //w = YWGUI_RECT_WIDTH(&rcOutput);
    //h = YWGUI_RECT_HEIGHT(&rcOutput);
    #if 0
    switch( tBmpOp.Flags&YWMID_DIBMP_OUTPUT_MODE_MASK)
    {
        case YWMID_DIBMP_OUTPUT_MODE_CENTER:
            if((U32)YWGUI_RECT_HEIGHT(&rcOutput) > ptBmpData->bmHeight)
            {
                rcOutput.top += (YWGUI_RECT_HEIGHT(&rcOutput)-ptBmpData->bmHeight)>>1;
                rcOutput.bottom = rcOutput.top+ptBmpData->bmHeight;
            }
            if((U32)YWGUI_RECT_WIDTH(&rcOutput) > ptBmpData->bmWidth)
            {
                rcOutput.left += (YWGUI_RECT_WIDTH(&rcOutput)- ptBmpData->bmWidth)>>1;
                rcOutput.right= rcOutput.left+ ptBmpData->bmWidth;
            }
            break;
        case YWMID_DIBMP_OUTPUT_MODE_ZOOM:/*缩放*/
        case YWMID_DIBMP_OUTPUT_MODE_TILE:
         default:
            break;

    }
    #endif
    if(YWGUI_IsRectIntersect (&rcOutput, &pdc->ecrgn.rcBound))
    {
        YWGUI_ClipRect_P pClipRect=NULL;
        YWGUI_Rect_T    rcClipping;


        pClipRect = pdc->ecrgn.pHead;
        while (pClipRect)
        {
            if (YWGUI_IntersectRect(&rcClipping,&rcOutput, &pClipRect->rc))
            {
                YWGUI_GalSetClipping(pdc->hSurface,rcClipping.left,rcClipping.top,rcClipping.right,rcClipping.bottom);

                if (ptBmpData->bmType & YWGUI_BMP_TYPE_COLORKEY)
                {
                    YWGUI_GalPutBoxMask (pdc->hSurface, rcOutput.left, rcOutput.top,widthBitmap, heightBitmap, ptBmpData->bmPitch, ptBmpData->bmBits, ptBmpData->bmColorKey, &tGraphCell);
                }
                else
                {
                    YWGUI_GalPutBox (pdc->hSurface, rcOutput.left, rcOutput.top, widthBitmap, heightBitmap, ptBmpData->bmPitch, ptBmpData->bmBits, &tGraphCell);
                }
            }

            pClipRect = pClipRect->next;
        }

    }

    YWGUI_UnlockEcrgn(hdc);
    return YW_NO_ERROR;
}

#ifdef YWGUI_ENABLE_TIMER
static void YWGUI_WrapTimerProc(U32 DrvHandle, YW_EventType_T EventType, void* EventData,  void * UserData)
{
    YWTIMER_EventAppData_T *TimerEvent = NULL;
    S32 slot = 0;

    TimerEvent = (YWTIMER_EventAppData_T *)EventData;
    slot = (S32)(TimerEvent->uiEventID-TIMER_EVENT_BEGIN_ID);
    YWMID_ASSERT((slot>=0 && slot < DEF_NR_TIMERS));

    YWGUI_WrapSetTimerTrigger(slot);
}
#endif
YWGUI_Handle_T YWGUI_WrapOpenTimer()
{
    YW_ErrorType_T errCode = YW_NO_ERROR;
    YWGUI_Handle_T hTimer = 0;
#ifdef YWGUI_ENABLE_TIMER
    errCode =  YWTIMER_Open(&hTimer);
    if(errCode!=YW_NO_ERROR)
    {
        YWMID_Trace((YWOS_TRACE_ERROR,"[ERROR][OpenTimer] YWTIMER_Open Error! errCode=%#x\n",errCode));
        return (YWGUI_Handle_T)0;
    }

    errCode = YWEVT_SubscribeEvent(hTimer, YWTIMER_EVENT_APPLICATION, (YWEVT_EventPoc_T)YWGUI_WrapTimerProc, NULL);
    if(errCode != YW_NO_ERROR )
    {
        YWMID_Trace((YWOS_TRACE_ERROR,"[ERROR][OpenTimer] YWEVT_SubscribeEvent Error! errCode=%#x\n",errCode));
        YWTIMER_Close(hTimer);
        return (YWGUI_Handle_T)0;
    }
#endif
    return (YWGUI_Handle_T)hTimer;
}

BOOL YWGUI_WrapCloseTimer(YWGUI_Handle_T hTimer)
{
    if(hTimer==(YWGUI_Handle_T)0)
    {
        return TRUE;
    }
#ifdef YWGUI_ENABLE_TIMER
    YWEVT_UnSubscribeEvent((YWTIMER_Hdl_T)hTimer, YWTIMER_EVENT_APPLICATION, (YWEVT_EventPoc_T)YWGUI_WrapTimerProc);

    if(YWTIMER_Close((YWTIMER_Hdl_T)hTimer)!=YW_NO_ERROR)
    {
        return FALSE;
    }
#endif
    return TRUE;
}


BOOL YWGUI_WrapGetTimerTrigger(S32 slot)
{
    BOOL bStatus = FALSE;

    YWGUI_SemaWait(g_tWrapInfo.lock);
    bStatus = g_tWrapInfo.bTimerTrigger[slot];
    g_tWrapInfo.bTimerTrigger[slot] = FALSE;
    YWGUI_SemaSend(g_tWrapInfo.lock);

    return bStatus;
}


BOOL YWGUI_WrapStartTimer(YWGUI_Handle_T hTimer,S32 slot,U32 elapse)
{
    U32 TimerEventID = slot+TIMER_EVENT_BEGIN_ID;
    U64 timeout;
    YW_ErrorType_T errCode = YW_NO_ERROR;

    YWGUI_SemaWait(g_tWrapInfo.lock);
    g_tWrapInfo.bTimerTrigger[slot] = FALSE;
    YWGUI_SemaSend(g_tWrapInfo.lock);
#ifdef YWGUI_ENABLE_TIMER
    timeout.MSW=0;
    timeout.LSW=elapse;

    errCode = YWTIMER_RegistAppEvent((YWTIMER_Hdl_T)hTimer, TimerEventID);
    if(errCode!=YW_NO_ERROR)
    {
        YWMID_Trace((YWOS_TRACE_ERROR,"[ERROR][StartTimer] YWTIMER_RegistAppEvent Error!,errCode=%#x\n",errCode));
        return FALSE;
    }

    errCode = YWTIMER_AppEventStart((YWTIMER_Hdl_T)hTimer, TimerEventID, timeout, YWGUI_U32_MAX);
    if(errCode!=YW_NO_ERROR)
    {
        YWMID_Trace((YWOS_TRACE_ERROR,"[ERROR][StartTimer] YWTIMER_AppEventStart Error!,errCode=%#x\n",errCode));
        return FALSE;
    }
#endif
    return TRUE;

}

BOOL YWGUI_WrapStopTimer(YWGUI_Handle_T hTimer,S32 slot)
{
    U32 TimerEventID = slot+TIMER_EVENT_BEGIN_ID;
#ifdef YWGUI_ENABLE_TIMER
    YWTIMER_AppEventStop((YWTIMER_Hdl_T)hTimer, TimerEventID);
    YWTIMER_UnRegistAppEvent((YWTIMER_Hdl_T)hTimer, TimerEventID);
#endif
    YWGUI_SemaWait(g_tWrapInfo.lock);
    g_tWrapInfo.bTimerTrigger[slot] = FALSE;
    YWGUI_SemaSend(g_tWrapInfo.lock);

    return TRUE;

}

