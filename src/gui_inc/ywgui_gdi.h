#ifndef _YWGUI_GDI_H_20080416_
#define  _YWGUI_GDI_H_20080416_

#ifdef __cplusplus
extern "C" {
#endif


/****************************宏定义*******************************/
typedef struct YWGUI_DeviceContext_s  YWGUI_DeviceContext_T;

extern YWGUI_DeviceContext_T  g_ScreenDC;
#define HDC_SCREEN          ((YWGUI_HDc_T)(&g_ScreenDC))
#define HSURFACE_SCREEN     ((YWGUI_HSurface_T)g_ScreenDC.hSurface)

//常用颜色定义
extern YWGUI_Pixel_T g_CommonColors[];
//#define PIXEL_transparent   g_CommonColors[0]
#define PIXEL_darkblue      g_CommonColors[1]
#define PIXEL_darkgreen     g_CommonColors[2]
#define PIXEL_darkcyan      g_CommonColors[3]
#define PIXEL_darkred       g_CommonColors[4]
#define PIXEL_darkmagenta   g_CommonColors[5]
#define PIXEL_darkyellow    g_CommonColors[6]
#define PIXEL_darkgray      g_CommonColors[7]
#define PIXEL_lightgray     g_CommonColors[8]
#define PIXEL_blue          g_CommonColors[9]
#define PIXEL_green         g_CommonColors[10]
#define PIXEL_cyan          g_CommonColors[11]
#define PIXEL_red           g_CommonColors[12]
#define PIXEL_magenta       g_CommonColors[13]
#define PIXEL_yellow        g_CommonColors[14]
#define PIXEL_lightwhite    g_CommonColors[15]
#define PIXEL_black         g_CommonColors[16]


#define MM_TEXT                 0
#define MM_ANISOTROPIC          1



#define FONT_CHARSET_US_ASCII       "US-ASCII"
#define FONT_CHARSET_ISO8859_1      "ISO8859-1"
#define FONT_CHARSET_UCS2           "UCS-2"
#define FONT_CHARSET_UTF8           "UTF-8"

//字体类型字符串
#define FONT_TYPE_NAME_BITMAP_RAW   "rbf"  //点阵字体
#define FONT_TYPE_NAME_BITMAP_VAR   "vbf"
#define FONT_TYPE_NAME_SCALE_TTF    "ttf"  //TrueType
#define FONT_TYPE_NAME_SCALE_T1F    "t1f"  //Adobe Type1
#define FONT_TYPE_NAME_ALL          "*"

//字体类型值
#define FONT_TYPE_BITMAP_RAW        0x0001  /* "rbf" */
#define FONT_TYPE_BITMAP_VAR        0x0002  /* "vbf" */
#define FONT_TYPE_SCALE_TTF         0x0010  /* "ttf" */
#define FONT_TYPE_SCALE_T1F         0x0011  /* "t1f" */
#define FONT_TYPE_ALL               0xFFFF  /* "all" */


//字体渲染风格值
#define FS_WEIGHT_REGULAR           0x00000000 //不作特殊处理
#define FS_WEIGHT_BOLD              0x00000001 //加粗显示
#define FS_WEIGHT_BOOK              0x00000002 //采用低通滤波算法处理字型边缘
#define FS_WEIGHT_DEMIBOLD          0x00000003 //加粗+低通滤波
#define FS_WEIGHT_MASK              0x000000FF

#define FS_SLANT_ROMAN              0x00000000 //不作特殊处理
#define FS_SLANT_ITALIC             0x00000100 //斜体
#define FS_SLANT_MASK               0x00000F00

#define FS_FLIP_NIL                 0x00000000 //不作特殊处理
#define FS_FLIP_HORZ                0x00001000 //水平翻转
#define FS_FLIP_VERT                0x00002000 //垂直翻转
#define FS_FLIP_HORZVERT            0x00003000 //水平+垂直翻转
#define FS_FLIP_MASK                0x0000F000


#define FS_OTHER_NIL                0x00000000 //不作处理
#define FS_OTHER_AUTOSCALE          0x00010000 //根据期望大小自动整数倍放大(仅用于点阵字体)
#define FS_OTHER_MASK               0x000F0000

#define FS_UNDERLINE_NONE           0x00000000 //无下划线
#define FS_UNDERLINE_LINE           0x00100000 //有下划线
#define FS_UNDERLINE_MASK           0x00F00000

#define FS_STRUCKOUT_NONE           0x00000000 //无删除线
#define FS_STRUCKOUT_LINE           0x01000000 //有删除线
#define FS_STRUCKOUT_MASK           0x0F000000



#define ROP_SET                 0
#define ROP_AND                 1
#define ROP_OR                  2
#define ROP_XOR                 3

/****************************常数定义*******************************/
//DC Type
#define TYPE_SCRDC      0x81 //屏幕DC
#define TYPE_GENDC      0x82 //窗口DC
#define TYPE_MEMDC      0x83 //内存DC

#define LEN_FONT_NAME               15
#define LEN_DEVFONT_NAME            79
#define LEN_UNIDEVFONT_NAME         127

#define MAX_LEN_MCHAR               4

#define NR_SYSLOGFONTMAPS               4
#define SYSLOGFONT_DEFAULT              0 //系统默认的单字节字符集逻辑字体(由RBF设备字体组成)
#define SYSLOGFONT_WINDOW               1 //用于普通窗口的逻辑字体
#define SYSLOGFONT_CAPTION              2 //用于显示标题的逻辑字体
#define SYSLOGFONT_CONTROL              3 //用于控件的逻辑字体

//字体最大/最小大小(高度)
#define FONT_MAX_SIZE               256
#define FONT_MIN_SIZE               4




/****************************宏函数定义*******************************/
#define YWGUI_Hdc2Pdc(hdc)      ((YWGUI_DeviceContext_P)(hdc))
#define YWGUI_Pdc2Hdc(pdc)      ((YWGUI_HDc_T)(pdc))




extern YWGUI_MutexID_T g_lockGdi;
#define YWGUI_LockGdi()              YWGUI_MutexWait(g_lockGdi)
#define YWGUI_UnlockGdi()            YWGUI_MutexSend(g_lockGdi)



/****************************类型定义*******************************/
#define YWGUI_BMP_TYPE_NORMAL                 0x00
#define YWGUI_BMP_TYPE_GLOBALALPHA            0x02
#define YWGUI_BMP_TYPE_LOCALALPHA             0x04
#define YWGUI_BMP_TYPE_COLORKEY               0x10

/*define of pixelformat*/
#define YWGUI_BMP_FORMAT_BGR0_8888             0x00000000
#define YWGUI_BMP_FORMAT_BGRA_8888             0x00001000
#define YWGUI_BMP_FORMAT_RGBA_8888             0x00002000
#define YWGUI_BMP_FORMAT_ABGR_8888             0x00003000
#define YWGUI_BMP_FORMAT_ARGB_8888             0x00004000

#define YWGUI_BMP_FORMAT_RGB_888                  0x00020000
#define YWGUI_BMP_FORMAT_BGR_888                  0x00021000

//#define YWGUI_BMP_FORMAT_RGB_565              0x00040000
#define YWGUI_BMP_FORMAT_BGR_565                   0x00040000
//#define YWGUI_BMP_FORMAT_ARGB_4444              0x00041000
#define YWGUI_BMP_FORMAT_BGRA_4444              0x00041000
#define YWGUI_BMP_FORMAT_BGRA_5551              0x00042000
#define YWGUI_BMP_FORMAT_CLUT_8                     0x00060000

#define YWGUI_BMP_FORMAT_YCBCR888_444        0x00080000
#define YWGUI_BMP_FORMAT_CBYCR888_444        0x00081000
#define YWGUI_BMP_FORMAT_YCBYCR8888_422    0x00082000
#define YWGUI_BMP_FORMAT_CBYCRY8888_422    0x00083000

#define YWGUI_BMP_FORMAT_MASK                         0x000FF000
/*end of pixelformat*/

//YWGUI_Bitmap_T: 设备相关位图结构
typedef struct YWGUI_BitmapData_s
{
    /**
     * Bitmap types:
     *  - YWGUI_BMP_TYPE_NORMAL
     *    A nomal bitmap, without alpha and color key.

     *  - BMP_TYPE_ALPHA
     *    位图中每个象素有alpha值

     *  - BMP_TYPE_ALPHACHANNEL
     *    bmAlpha有效

     *  - YWGUI_BMP_TYPE_COLORKEY
     *    bmColorKey有效

     *  - YWGUI_BMP_TYPE_PRIV_PIXEL
     *    The bitmap have a private pixel format.
     */

    U32   bmType;/*高位为像素类型*/
    /** The bits per piexel. */
    U8   bmBitsPerPixel;
    /** The bytes per piexel. */
    U8   bmBytesPerPixel;

    /** The alpha channel value. */
    U8   bmAlpha;

    /** The color key value. */
    YWGUI_Pixel_T  bmColorKey;

    /** The width of the bitmap */
    U32  bmWidth;
    /** The height of the bitmap */
    U32  bmHeight;

    /*一行所用内存宽度(字节数)*/
    U32  bmPitch;

    /** The bits of the bitmap */
    U8*  bmBits;
    U8*  bmpPalette;
    BOOL bIsNewBits;

}YWGUI_BitmapData_T;

/*end of modify*/

typedef struct YWGUI_WordInfo_s
{
    /*单词的字符个数*/
    S32 len;

    /*单词后的分割字符*/
    YWGUI_Char_T delimiter;

    /*单词后的分割字符个数*/
    S32 nr_delimiters;
}YWGUI_WordInfo_T;

typedef struct YWGUI_IncoreFontInfo_s
{
    const S8* name;
    const U8* data;
    const U32 data_bytes;
} YWGUI_IncoreFontInfo_T;

typedef struct YWGUI_CharSetOps_s
{
    //该字符集所包含的字符个数
    S32 nr_chars;

    S32 bytesPerChar;

    //该字符集各字符中最大的字节数
    S32 maxBytesOfChar;

    const S8* name;

    S8 def_char [MAX_LEN_MCHAR];

    //返回字符串mstr第一个字符使用的字节个数
    S32 (*pfnBytesOfFirstChar) (const U8* mstr, S32 mstrlen);

    //某字符相对于字符集首字符的偏移索引(从0开始)
    U32 (*pfnCharPosOffset) (const U8* mchar);

    S32 (*nr_chars_in_str) (const U8* mstr, S32 mstrlen);

    //传入的字符集字符串是否本字符集(该分量不能为NULL)
    //返回值0 -- 是;否则--不是
    S32 (*pfnIsSelfCharset) (const U8* pszCharset);

    S32 (*pfnGetFirstSubStrLen) (const U8* mstr, S32 mstrlen);

    YWGUI_ConstU8Ptr (*pfnGetNextWord) (const U8* mstr,  S32 strlen, YWGUI_WordInfo_T* ptWordInfo, BOOL bRightToLeft);

    //该分量不能为NULL (返回 0)
    S32 (*pfnGetFirstChPos) (const U8* mstr, S32 mstrlen);

    U16 (*conv_to_uc16) (const U8* mchar, S32 len);
    S32 (*conv_from_uc16) (U16 wc, U8* mchar);

} YWGUI_CharSetOps_T ;

typedef struct YWGUI_LogFont_s YWGUI_LogFont_T;
typedef struct YWGUI_DevFont_s YWGUI_DevFont_T;
typedef YWGUI_DevFont_T*    YWGUI_DevFont_P;

typedef struct YWGUI_FontOps_s
{
    //得到字体宽度(象素点数),该分量不能为NULL
    //len--该字符所用的字节个数
    S32 (*pfnGetCharWidth) (YWGUI_LogFont_T* logfont, YWGUI_DevFont_T* devfont,
                                    const U8* mchar, S32 len);

    //该分量不能为NULL
    S32 (*pfnGetAveWidth) (YWGUI_LogFont_T* logfont, YWGUI_DevFont_T* devfont);

    S32 (*pfnGetMaxWidth) (YWGUI_LogFont_T* logfont, YWGUI_DevFont_T* devfont);

    //得到字体高度,该分量不能为NULL
    S32 (*pfnGetFontHeight) (YWGUI_LogFont_T* logfont, YWGUI_DevFont_T* devfont);

    //得到字体大小,该分量不能为NULL
    S32 (*pfnGetFontSize) (YWGUI_LogFont_T* logfont, YWGUI_DevFont_T* devfont, S32 expect);

    //该分量不能为NULL
    S32 (*pfnSetFontSize)(YWGUI_LogFont_T* logfont, YWGUI_DevFont_T* devfont,S32 expect);

    //该分量不能为NULL
    S32 (*pfnGetFontAscent) (YWGUI_LogFont_T* logfont, YWGUI_DevFont_T* devfont);

    //该分量不能为NULL
    S32 (*pfnGetFontDescent) (YWGUI_LogFont_T* logfont, YWGUI_DevFont_T* devfont);

    YWGUI_ConstU8Ptr (*pfnGetCharBitmap) (YWGUI_LogFont_T* logfont, YWGUI_DevFont_T* devfont,
                                const U8* mchar, S32 len,S32* pitch,U16* scale);

    //该函数指针可以为NULL,如果为NULL，使用 pfnGetCharBitmap
    //低通滤波算法
    YWGUI_ConstU8Ptr (*pfnGetCharPixmap) (YWGUI_LogFont_T* logfont, YWGUI_DevFont_T* devfont,
                const U8* mchar, S32 len, S32* pitch, U16* scale);



    //字符串输出之前的准备,该函数指针可以为NULL
    void (*pfnPrepareOutput) (YWGUI_LogFont_T* logfont, YWGUI_DevFont_T* devfont);

    //该函数指针可以为NULL,如果为NULL,使用 pfnGetCharWidth
    /*modified by sly, 2009-5-26。增加了最后三个参数，减少加载字库的次数*/
    S32 (*pfnGetCharBox) (YWGUI_LogFont_T* logfont, YWGUI_DevFont_T* devfont,
            const U8* mchar, S32 len, S32* px, S32* py, S32* pwidth, S32* pheight, S32* pPitch, const U8 ** pBits, void ** ppvNode);

    //pfnGetCharAdvance 与 pfnGetCharBox 同时为NULL 或非NULL
    void (*pfnGetCharAdvance) (YWGUI_LogFont_T* logfont, YWGUI_DevFont_T* devfont,
            const U8* mchar, S32 len, S32* px, S32* py);

    //该函数指针可以为NULL
    YWGUI_DevFont_P (*pfnNewInstance)(YWGUI_LogFont_T* logfont,YWGUI_DevFont_T* devfont,BOOL need_sbc_font);

    //该函数指针可以为NULL
    void (*pfnDeleteInstance) (YWGUI_DevFont_T* devfont);

    /*Decrement a cache node's internal reference count*/
    void (*pfnNode_Unref) (void* data, void * node);/*added by sly, 2009-5-26*/

} YWGUI_FontOps_T;


struct YWGUI_DevFont_s
{
    S8                          name [LEN_UNIDEVFONT_NAME + 1];
    DWORD                       style;
    YWGUI_FontOps_T*            font_ops;
    YWGUI_CharSetOps_T*         charset_ops;
    struct YWGUI_DevFont_s*     sbc_next;//下一个单字节字符集设备字体
    struct YWGUI_DevFont_s*     mbc_next;//下一个多字节字符集设备字体
    void*                       data;
};



struct YWGUI_LogFont_s
{
    /** The type of the logical font. */
    S8 type [LEN_FONT_NAME + 1];

    /** The family name of the logical font. */
    S8 family [LEN_FONT_NAME + 1];

    /** The charset of the logical font. */
    S8 charset [LEN_FONT_NAME + 1];

    /** The styles of the logical font. */
    DWORD style;

    /** The size of the logical font. */
    S32 size;

    U16 width;  /*矢量字体的宽度*/

    /** The rotation angle of the logical font. */
    S32 rotation;

    /** The scale factor of sbc device font. */
    U16 sbc_scale;

    /** The scale factor of mbc device font. */
    U16 mbc_scale;

    /** Device font in single charset set */
    YWGUI_DevFont_T* sbc_devfont;

    /** Device font in multiply charset set */
    YWGUI_DevFont_T* mbc_devfont;
} ;



typedef YWGUI_LogFont_T*    YWGUI_LogFont_P;

// Device Context
struct YWGUI_DeviceContext_s
{
    U16  DCType;    /* the dc type */
    BOOL inuse;

    YWGUI_HWnd_T hWnd;
    YWGUI_HSurface_T hSurface;

    /* background color and mode */
    YWGUI_Pixel_T    bkcolor;
    S32 bkmode;


    YWGUI_Pixel_T pencolor;/* pen color */
    YWGUI_Pixel_T brushcolor;/* solid brush color */
    YWGUI_Pixel_T textcolor;

    U32 penwidth;

    S32 cExtra;     /* Character extra */
    S32 alExtra;    /* Above line extra */
    S32 blExtra;    /* Below line extra */

    YWGUI_CANVAS_OpMode_T opmode;    /* canvas op mode,added by sly, 2009-11-5 */

    S32 tabstop;   //每个 tab 所指示的字符个数(默认值为 8)

    S32 mapmode;    /* mappping mode:MM_TEXT/MM_ANISOTROPIC */

    YWGUI_Point_T CurPenPos;
    YWGUI_Point_T CurTextPos;

    YWGUI_LogFont_T* pLogFont;

    YWGUI_ClipRgn_T   lcrgn;//局部剪切域(内部矩形为相对于DC的坐标)
    YWGUI_ClipRgn_T  ecrgn; //实际的剪切域(内部矩形为屏幕坐标)

    BOOL bIsClient;
    YWGUI_Rect_T DevRC; //窗口的屏幕坐标

    YWGUI_GcrInfo_P  ptGcrInfo;

    //用来判断全局剪切域是否被修改,以决定是否需要更新ecrgn
    U32    oldage;



    S32 step;
    S32 rop;
    YWGUI_Pixel_T cur_pixel;
    YWGUI_Pixel_T skip_pixel;
    YWGUI_ClipRect_T* cur_ban;
    void* alpha_pixel_format;
    /* used by the text rendering for anti-aliasing fonts. */
    YWGUI_Pixel_T gray_pixels [17];
    /* used by the text rendering for low-pass filtering. */
    YWGUI_Pixel_T filter_pixels [17];
};

typedef YWGUI_DeviceContext_T *  YWGUI_DeviceContext_P;

typedef struct YWGUI_WedNode_s
{
    U16              type;       /* the item type */
    U16              item;       /* the item number */
    U32              data;       /* the data of the item */
    ListNode         node;
}YWGUI_WedNode_T;

extern YWGUI_HSurface_T g_hVisibleSurface;
extern YWGUI_HSurface_T g_hInvisibleSurface;

/****************************函数声明*******************************/
//ywgui_gdi.c
extern BOOL YWGUI_InitGDI (U8 uFontNum, YWGUI_FontInfo_T * pstFontInfo, U8 uLogFontNum, S8** ppcLogFontName);
extern void YWGUI_TermGDI( void );

extern BOOL YWGUI_InitScreenDc(void);
extern void YWGUI_TermScreenDc (void);


extern void  YWGUI_SelectClipRect (YWGUI_HDc_T hdc, const YWGUI_Rect_T* pRect);
extern void  YWGUI_SelectClipRegion (YWGUI_HDc_T hdc, const YWGUI_ClipRgn_T* pRgn);
extern void  YWGUI_ClipRectIntersect (YWGUI_HDc_T hdc, const YWGUI_Rect_T* prc);
extern void  YWGUI_ExcludeClipRect (YWGUI_HDc_T hdc, const YWGUI_Rect_T* prc);


//extern void  YWGUI_Rectangle(YWGUI_HDc_T hdc, S32 x, S32 y, S32 w, S32 h);
//extern void YWGUI_MoveTo(YWGUI_HDc_T hdc, S32 x, S32 y);
//extern void  YWGUI_LineTo (YWGUI_HDc_T hdc, S32 x, S32 y);
extern void  YWGUI_BitBlt (YWGUI_HDc_T hdcDest, const YWGUI_Rect_T * prcDest, YWGUI_HDc_T hdcSrc,const YWGUI_Rect_T *prcSrc, DWORD dwRop);


extern YW_ErrorType_T YWGUI_SetWedData(YWGUI_Wed_P * pptWed,U16 type,U16 item,U32 new_data,U32*pOldData);
extern YW_ErrorType_T YWGUI_FreeWedData(YWGUI_Wed_P * pptWed);
extern YW_ErrorType_T YWGUI_SetWedShapeData(YWGUI_Wed_P * pptWed, YWGUI_WesItem_E item, YWGUI_ShapeState_T* ptShapeState);
extern YW_ErrorType_T YWGUI_Wes2WecItem(BOOL bIsControl,YWGUI_WesItem_E itemWes,YWGUI_WecItem_E* pBgcItem,YWGUI_WecItem_E* pFgcItem,YWGUI_WecItem_E* pFramecItem);


extern  void YWGUI_GetDefaultColor(YWGUI_WecItem_E item, YWGUI_Pixel_T pixel);
extern YW_ErrorType_T YWGUI_FreeWindowWedData(YWGUI_HWnd_T hWnd );

extern S32   YWGUI_GetWEMetrics(YWGUI_HWnd_T hWnd, YWGUI_WemItem_E item);
extern  void YWGUI_GetWEColor (YWGUI_HWnd_T hWnd, YWGUI_WecItem_E item, YWGUI_Pixel_T pixel);
extern YWGUI_ShapeState_T*   YWGUI_GetWEShape(YWGUI_HWnd_T hWnd, YWGUI_WesItem_E item);





extern void YWGUI_POINT_LP2SP(YWGUI_DeviceContext_P pdc, S32* x, S32* y);
extern void YWGUI_POINT_SP2LP(YWGUI_DeviceContext_P pdc, S32* x, S32* y);
extern void YWGUI_ExtentX_SP2LP (YWGUI_DeviceContext_P pdc, S32* extent);


extern BOOL YWGUI_GenerateDcEcrgn(YWGUI_DeviceContext_P pdc, BOOL bForce);

extern BOOL  YWGUI_LockEcrgn(YWGUI_HDc_T hdc);
extern BOOL YWGUI_UnlockEcrgn(YWGUI_HDc_T hdc);



/*****************************************************************/
//ywgui_rect.c
extern void YWGUI_SetRectEmpty (YWGUI_Rect_T* pRect);
extern void YWGUI_CopyRect(YWGUI_Rect_T *prcDest,const YWGUI_Rect_T *prcSrc);
extern BOOL  YWGUI_IsRectEmpty (const YWGUI_Rect_T* pRect);
extern BOOL  YWGUI_IntersectRect(YWGUI_Rect_T* pDestRect, const YWGUI_Rect_T* pSrcRect1, const YWGUI_Rect_T* pSrcRect2);
extern S32  YWGUI_SubtractRect(YWGUI_Rect_T* rc, const YWGUI_Rect_T* psrc1, const YWGUI_Rect_T* psrc2);
extern BOOL  YWGUI_IsRectIntersect (const YWGUI_Rect_T* pSrcRect1, const YWGUI_Rect_T* pSrcRect2);
extern void YWGUI_OffsetRect (YWGUI_Rect_T* pRect, int x, int y);
extern void  YWGUI_InflateRect(YWGUI_Rect_T* pRect, int cx, int cy);
extern void  YWGUI_NormalizeRect(YWGUI_Rect_T* pRect);
extern BOOL  YWGUI_IsRectCover(const YWGUI_Rect_T* prc1, const YWGUI_Rect_T* prc2);
extern BOOL  YWGUI_IsRectEqual (const YWGUI_Rect_T* prc1, const YWGUI_Rect_T* prc2);
extern BOOL YWGUI_AdjustRectByBound(YWGUI_Rect_T* ptRect,const YWGUI_Rect_T *ptBoundRect);
extern void  YWGUI_GetBoundRect (YWGUI_Rect_T* ptDst,  const YWGUI_Rect_T* ptSrc1, const YWGUI_Rect_T* ptSrc2);

/*****************************************************************/
//ywgui_text.c


/*************************************************************/



extern BOOL YWGUI_InitSystemFont (U8 uLogFontNum, S8** ppcLogFontName);
extern void YWGUI_TermSystemFont (void);
extern YWGUI_LogFont_P  YWGUI_GetSystemFont (S32 font_id);
extern S32 YWGUI_FontTypeStr2Val (const S8* szFontType);
extern S32  YWGUI_GetFontTypeValFromName (const S8* szFontName);
extern BOOL YWGUI_GetCharsetStrFromName (const S8* szFontName, S8* pszCharset);
extern BOOL YWGUI_GetFontFamilyStrFromName (const S8* szFontName, S8* pszFontFamily);
extern S32 YWGUI_GetFontWidthFromName (const S8* szFontName);
extern DWORD YWGUI_GetFontStyleValFromName (const S8* szFontName);
extern S32  YWGUI_GetFontHeightFromName (const S8* szFontName);









extern YWGUI_CharSetOps_T* YWGUI_GetCharsetOps (const S8* charset);
extern YWGUI_CharSetOps_T* YWGUI_GetCharsetOpsEx (const S8* charset);
extern BOOL YWGUI_IsCompatibleCharset (const S8* charset, YWGUI_CharSetOps_T* ops);




#ifdef __cplusplus
}
#endif

#endif

