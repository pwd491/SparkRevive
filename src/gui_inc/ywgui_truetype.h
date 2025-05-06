#ifndef _YWGUI_TRUETYPE_H_20081127_
#define  _YWGUI_TRUETYPE_H_20081127_

//包含主要的FreeType2 API头文件
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_SIZES_H

#include FT_CACHE_H
#include FT_CACHE_SMALL_BITMAPS_H
#include FT_CACHE_CHARMAP_H

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct YWGUI_TTFaceData_s
{
    FT_Face     face;
    BOOL        bIsUsed;
    U8*         source;
    U32         source_bytes;
    FTC_ScalerRec tScaler;
    FTC_Manager        ptFtCacheManager ;
    FTC_SBitCache     ptFtSBitCache ;     /*  位图cache的句柄*/
    FTC_CMapCache  ptFtCMapCache;	   /*  编码转字符索引的cache的句柄*/
}YWGUI_TTFaceData_T;
typedef YWGUI_TTFaceData_T * YWGUI_TTFaceData_P;




//创建逻辑字体时，根据原始设备字体 (YWGUI_TTFaceData_T) 生成新的设备字体对象
typedef struct YWGUI_TTFontObject_s 
{
    YWGUI_TTFaceData_P  ptFaceData;
    FT_Size             size;

    S32                 max_width;
    S32                 ave_width;
    S32                 height;
    S32                 ascent;
    S32                 descent;

    S32                 xadvance;
    S32                 yadvance;
}YWGUI_TTFontObject_T;
typedef YWGUI_TTFontObject_T* YWGUI_TTFontObject_P;


#ifdef __cplusplus
}
#endif 

#endif


