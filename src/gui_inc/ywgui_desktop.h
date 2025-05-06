#ifndef _YWGUI_DESKTOP_H_20080512_
#define  _YWGUI_DESKTOP_H_20080512_

#ifdef __cplusplus
extern "C" {
#endif 


enum
{
    YWGUI_DESKTOP_HIDE       = ( 1 << 0 ), //隐藏桌面
    YWGUI_HIGH_DEFINITION    = ( 1 << 7 ),
    YWGUI_HARDWARE_ACCEL     = ( 1 << 8 ), //硬件加速
    YWGUI_ANTI_FLICKER       = ( 1 << 9 ), //抗闪烁
    YWGUI_COLORKEY_VALID     = ( 1 << 16), //colorKey 有效
    YWGUI_TRANSPARENCE_VALID = ( 1 << 17)  //transparence 有效
};

typedef struct YWGUI_LayerInfo_s
{
    U32                     dwFlags;
    YWGUI_PixelType_E       ePixelType; //象素类型

    S32                     left;
    S32                     top;
    U32                     width;  
    U32                     height; 

    YWGUI_Pixel_T           colorKey;
    YWGUI_Pixel_T           DeskTopColor;
    //YWGUI_Pixel_T           transparence;
    U8  transparence; //0~0xFF, 0:透明，0xFF:不透明;
    U8                      bitsPerPixel; //每象素占多少内存(单位:bit)
    //U8                      alphaBlendingMode;
     /*added by sly, 2009-8-17*/
    U32                        uAssociateLayerNum;
    U32*                      puAssociateLayerIndex; 
    /*end of added*/
}YWGUI_LayerInfo_T;

extern BOOL YWGUI_StartupServiceThreads(void);
extern BOOL YWGUI_DestroyServiceRes(void);
extern void YWGUI_SetImportParams(YWGUI_ImportParams_T* ptImportParam);
extern BOOL YWGUI_InitGlobalData(void);
extern BOOL YWGUI_CleanGlobalData(void);
extern YWGUI_DlgTemplate_T* YWGUI_GetDlgTemplate(S32 id);
extern void YWGUI_FreeWindowInvRgnInfo (YWGUI_HWnd_T hWnd);






//全局变量读写函数
extern BOOL YWGUI_GetDesktopRect(YWGUI_Rect_T *pRect);
extern BOOL YWGUI_SetDesktopRect(S32 left,S32 top,S32 right,S32 bottom);

extern YWGUI_ThreadInfo_T* YWGUI_GetDesktopThreadInfo(void);
extern void YWGUI_SetDesktopThreadInfo(YWGUI_ThreadInfo_T* pThreadInfo);
extern void YWGUI_SetDesktopThreadID(YWGUI_ThreadID_T threadid);
extern YWGUI_ThreadID_T YWGUI_GetDesktopThreadID(void);
extern YWGUI_ThreadID_T YWGUI_GetEventThreadID(void);
extern void YWGUI_SetEventThreadID(YWGUI_ThreadID_T threadid);
extern YWGUI_HWnd_T YWGUI_GetImeHWnd(void);
extern void YWGUI_SetImeHWnd(YWGUI_HWnd_T hIme);




extern void YWGUI_SetActiveMainHWnd(YWGUI_HWnd_T hActive);

extern YWGUI_LayerInfo_T* YWGUI_TakeoutLayerInfo(void);
extern void YWGUI_ReturnLayerInfo(void);

extern YW_ErrorType_T YWGUI_GetGlobalQuad(U32 *pQuadColors,YWMID_Palette_P* pptGlobalQuad);


extern BOOL YWGUI_MWndIsMultiShape(void);


extern void YWGUI_ModifyDefaultScheme(void);
extern void YWGUI_ModifyCtrlClassScheme(void);
extern void YWGUI_InitTempletLink(void);
extern YWGUI_Char_T *YWGUI_LoadString(S32 idStr);
extern YW_ErrorType_T YWGUI_InvalidateUpperWindows (YWGUI_HWnd_T hWnd, const YWGUI_Rect_T* pRect);
//extern void YWGUI_SetKeyTargetHWnd(YWGUI_HWnd_T hWnd);
extern void YWGUI_KeyEnable(BOOL bEnable);
#ifdef __cplusplus
}
#endif 

#endif

