#ifndef _YWGUI_TEXT_H_20080610_
#define  _YWGUI_TEXT_H_20080610_

#ifdef __cplusplus
extern "C" {
#endif 




extern BOOL YWGUI_InitTextBitmapBuffer (void);
extern void YWGUI_TermTextBitmapBuffer (void);



extern S32  YWGUi_TextOutLen (YWGUI_HDc_T hdc, S32 x, S32 y, const YWGUI_Char_T* spText, S32 len);

#ifdef __cplusplus
}
#endif 

#endif

