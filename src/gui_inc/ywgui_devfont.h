#ifndef _YWGUI_DEVFONT_H_20080506_
#define  _YWGUI_DEVFONT_H_20080506_

#ifdef __cplusplus
extern "C" {
#endif 

#define YWGUI_GetDevfontScale(logfont, devfont) \
        ((U16)(((devfont)->charset_ops->bytesPerChar > 1)?(logfont)->sbc_scale:(logfont)->mbc_scale))

#define YWGUI_SetDevfontScale(logfont, devfont, scale) \
        (((devfont)->charset_ops->bytesPerChar > 1)?((logfont)->sbc_scale = (scale)):((logfont)->mbc_scale = (scale)))

extern U16 YWGUI_GetBestScaleFactor(S32 height, S32 expect);


extern YWGUI_DevFont_T* YWGUI_GetMatchedSBDevFont (YWGUI_LogFont_T* pLogFont);
extern YWGUI_DevFont_T* YWGUI_GetMatchedMBDevFont (YWGUI_LogFont_T* pLogFont);
extern void YWGUI_InitDevFont(void);
extern void YWGUI_AddMBDevFont (YWGUI_DevFont_T* pDevFont);
extern void YWGUI_AddSBDevFont (YWGUI_DevFont_T* pDevFont);

extern BOOL YWGUI_InitIncoreRBFonts (void);
extern void YWGUI_TermIncoreRBFonts(void);

extern BOOL YWGUI_InitTrueTypeFonts(U8 uFontNum, YWGUI_FontInfo_T * pstFontInfo);
extern void YWGUI_TermTrueTypeFonts (void);

#ifdef __cplusplus
}
#endif 

#endif

