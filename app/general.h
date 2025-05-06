
#ifndef _GENERAL_H_20080416_
#define  _GENERAL_H_20080416_

typedef struct YWPLUGINREAME_Param_s
{
    YWGUI_HWnd_T                hHosting;
    YWGUI_Char_T*               pStrContent;
	YWGUI_Char_T* 				pStrTitle;
    U16                         nEditLimitLen;    //max is 80 char , 0 means  80
}YWPLUGINREAME_Param_T;

/*Create a rename window to modify the strings*/
YWGUI_HWnd_T YWPlugin_CreateRenameWindow(YWPLUGINREAME_Param_T *pPluginRenameParam);
/*Create a message window*/
YWGUI_HWnd_T YWGeneralPopInfo_CreateWindow(YWGUI_HWnd_T hHost, YWGUI_Char_T *pwstr, int timeout);
/*Close the message window*/
YW_ErrorType_T YWGeneralPopInfo_CloseWindow(void);
/*Create a confirm widow, return YWPUBLIC_MSG_CONFIRM_INFO message to indicate the selection*/
YWGUI_HWnd_T YWGeneralConfirmInfo_CreateConfirmBox(YWGUI_HWnd_T hHost,YWGUI_Char_T *pwstr);
/*Close the confirm window*/
YW_ErrorType_T YWGeneralConfirmInfo_CloseConfirmBox(void);
/*Create a language select widow*/
YWGUI_HWnd_T YWGeneralLanguageSet_CreateWindow(YWGUI_HWnd_T hHost);

#endif


