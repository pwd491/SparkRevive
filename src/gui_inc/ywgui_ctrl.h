#ifndef _YWGUI_CTRL_H_20080504_
#define  _YWGUI_CTRL_H_20080504_


#ifdef __cplusplus
extern "C" {
#endif

#ifndef YWGUI_CTRL_INVALID_EXTRA
#define YWGUI_CTRL_INVALID_EXTRA   (-1)
#endif

extern BOOL YWGUI_InitControlClass (U32 uOffsetInfoNum,YWGUI_CtrlOffsetInfo_P pOffsetInfo);
extern void YWGUI_TermControlClass(void);

extern S32 YWGUI_AddNewControlClass (YWGUI_WndClass_P pWndClass);
S32 YWGUI_DeleteControlClass (const S8* szClassName);

extern YWGUI_CtrlClassInfo_P  YWGUI_GetControlClassInfo (const S8* szClassName);



extern BOOL YWGUI_RegisterStaticControl (U32 XOffset, U32 YOffset);
extern BOOL YWGUI_RegisterPictureControl (void);
extern BOOL YWGUI_RegisterButtonControl (U32 XOffset, U32 YOffset);
extern BOOL YWGUI_RegisterPosBarControl (void);
extern BOOL YWGUI_RegisterProgressBarControl(void);

extern BOOL YWGUI_RegisterEditControl(void);
extern BOOL YWGUI_RegisterSEditControl(void);
extern BOOL YWGUI_RegisterListboxControl (U32 XOffset, U32 YOffset);
extern BOOL YWGUI_RegisterListViewControl(void);
extern BOOL YWGUI_RegisterLRComboboxControl(U32 XOffset, U32 YOffset);
extern BOOL YWGUI_RegisterContainerControl(void);

extern BOOL YWGUI_RegisterListTableControl(void);

extern S32 YWGUI_NotifyParentEx (YWGUI_HWnd_T hWnd, U16 id, U16 code, DWORD add_data);


#define YWGUI_NotifyParent(hWnd, id, code) \
                YWGUI_NotifyParentEx(hWnd, id, code, 0)


#ifdef __cplusplus
}
#endif

#endif

