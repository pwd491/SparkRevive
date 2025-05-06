#ifndef _YWGUI_RAMBITMAP_H_20080506_
#define  _YWGUI_RAMBITMAP_H_20080506_

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct _RBFINFO
{
    YWGUI_CharSetOps_T* charset_ops;
    S32 nr_chars;//对应字符集的字符个数(也就是字体个数)
    S32 width;   //定宽
    S32 height;
    U8* font;
    S32  font_size;//Roger: long -> int 
} RBFINFO;



#ifdef __cplusplus
}
#endif 

#endif

