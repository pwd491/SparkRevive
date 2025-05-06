#ifndef _YWGUI_RAMBITMAP_H_20080506_
#define  _YWGUI_RAMBITMAP_H_20080506_

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct _RBFINFO
{
    YWGUI_CharSetOps_T* charset_ops;
    S32 nr_chars;//��Ӧ�ַ������ַ�����(Ҳ�����������)
    S32 width;   //����
    S32 height;
    U8* font;
    S32  font_size;//Roger: long -> int 
} RBFINFO;



#ifdef __cplusplus
}
#endif 

#endif

