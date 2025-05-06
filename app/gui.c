/*
 * File: gui.c    
 * Author:  
 * Brief: the gui system initialization fucntions.
 * 
 */

/*
 * History:
 * ================================================================
 *
 */

#include<stdio.h>
#include <pthread.h>

#include"ywdefs.h"
#include"ywos.h"
#include"ywlib.h"
#include"ywgui_ext.h"
#ifdef YWGUI_ENABLE_TIMER
#include"ywevt.h"
#endif
#include "res_layout.h"


#define _PIXEL_TYPE_BGR888_         1
#define _PIXEL_TYPE_BGRA8888_       2
#define _PIXEL_TYPE_BGRA4444_       3
#define _PIXEL_TYPE_BGR565_         4
#define _PIXEL_TYPE_BGRA5551_       5
#define _USE_PIXEL_TYPE_      _PIXEL_TYPE_BGRA8888_

S8* pszLoadLogFontName[]=
{
	#if 0
	(S8*)"rbf-fulan-rrncnn-6-12-ISO8859-1",/*系统默认的单字节字符集逻辑字体*/
	(S8*)"ttf-arial-rrncnn-20-12-UCS-2",
	(S8*)"ttf-arial-rrncnn-20-24-UCS-2",	  /*控件和窗口标题使用的字体*/
	(S8*)"ttf-arial-rrncnn-20-36-UCS-2" 	  /*普通窗口使用的默认字体*/
	#else
	(S8*)"rbf-fulan-rrncnn-6-12-ISO8859-1",/*系统默认的单字节字符集逻辑字体*/
	(S8*)"ttf-arial-rrncnn-20-11-UCS-2",
	(S8*)"ttf-arial-rrncnn-20-22-UCS-2",		/*控件和窗口标题使用的字体*/
	//(S8*)"ttf-arial-rrncnn-20-30-UCS-2",	  /*控件和窗口标题使用的字体*/
	(S8*)"ttf-arial-rrncnn-20-32-UCS-2" 	  /*普通窗口使用的默认字体*/
	#endif
};


void client_term(void);
extern YWGUI_HWnd_T YWPLUGIN_CreateMainMenuWindow(void);
extern void YWPLUGIN_InitGuiTemplate(void);



static void APP_InitDlgTemplateLink(void)
{
    YWGUI_AddTempletNode(&g_template_mcasentry);
    YWGUI_AddTempletNode(&g_template_pluginrename);
    YWGUI_AddTempletNode(&g_template_popinfocfg);
    YWGUI_AddTempletNode(&g_template_confirminfocfg);
    YWGUI_AddTempletNode(&g_template_languageset);

	YWPLUGIN_InitGuiTemplate();

}


static void App_ModifyDefScheme(void)
{
    return;
}

static void App_ModifyCtrlClassScheme(void)
{
    YWGUI_Pixel_T pixel;
    *(U32*)pixel = 0xFF000000;
    YWGUI_SetCtrlDefColor((const S8*)"Static",YWGUI_NORMAL_CTRL_FGC, pixel, NULL);
}

static void APP_InitLayerParam(YWGUI_LayerParams_T* ptLayerParam)
{
    YWGUI_Pixel_T           colorKey = {0,0,0xFF,0xFF};
    YWLIB_Memset(ptLayerParam,0,sizeof(YWGUI_LayerParams_T));
    U32 LayerOsd = 3;

#if (_USE_PIXEL_TYPE_==_PIXEL_TYPE_BGR888_)
    ptLayerParam->ePixelType =YWGUI_PIXEL_TYPE_BGR888;
    ptLayerParam->bitsPerPixel=24;
#elif (_USE_PIXEL_TYPE_==_PIXEL_TYPE_BGRA8888_)
    ptLayerParam->ePixelType =YWGUI_PIXEL_TYPE_BGRA8888;
    ptLayerParam->bitsPerPixel=32;
    ptLayerParam->bHaveTransparence = TRUE;
    ptLayerParam->transparence = 0xFF;
    ptLayerParam->bIsHideDesktop = TRUE;
    *(U32*)ptLayerParam->colorKey = 0;
#elif (_USE_PIXEL_TYPE_== _PIXEL_TYPE_BGR565_)
    ptLayerParam->ePixelType =YWGUI_PIXEL_TYPE_BGR565;
    ptLayerParam->bitsPerPixel=16;
    ptLayerParam->bHaveTransparence = FALSE;
    ptLayerParam->transparence = 0xFF;
    ptLayerParam->bIsHideDesktop = TRUE;
    *(U32*)ptLayerParam->colorKey = 0;
#elif (_USE_PIXEL_TYPE_== _PIXEL_TYPE_BGRA4444_)
    ptLayerParam->ePixelType =YWGUI_PIXEL_TYPE_BGRA4444;
    ptLayerParam->bitsPerPixel=16;
    ptLayerParam->bHaveTransparence = TRUE;
    ptLayerParam->transparence = 0xFF;
    ptLayerParam->bIsHideDesktop = TRUE;
    //*(U32*)ptLayerParam->colorKey = 0;
    ptLayerParam->bHaveColorKey = FALSE;
    ptLayerParam->colorKey[0] = 0xFF;
    ptLayerParam->colorKey[1] = 0;
    ptLayerParam->colorKey[2] = 0;
    ptLayerParam->colorKey[3] = 0;
#elif (_USE_PIXEL_TYPE_== _PIXEL_TYPE_BGRA5551_)
    ptLayerParam->ePixelType =YWGUI_PIXEL_TYPE_BGRA5551;
    ptLayerParam->bitsPerPixel=16;
    ptLayerParam->bHaveTransparence = TRUE;
    ptLayerParam->transparence = 0xFF;
    ptLayerParam->bIsHideDesktop = TRUE;

    ptLayerParam->bHaveColorKey = TRUE;
    *(U32*)ptLayerParam->colorKey = 0;
    *(U32*)ptLayerParam->colorKey = *(U32*)colorKey;
    *(U32*)ptLayerParam->DeskTopColor = *(U32*)colorKey;

#endif

    ptLayerParam->left=0;
    ptLayerParam->top = 0;
    ptLayerParam->width=1920;
    ptLayerParam->height=1080;
    // ptLayerParam->alphaBlendingMode= YWGUI_ALPHA_MODE_LOCAL;
    ptLayerParam->uAssociateLayerNum = 1;
    ptLayerParam->puAssociateLayerIndex = &LayerOsd;
    //ptLayerParam->bHighDefinition = TRUE;
}

void APP_ModifyFontSize(S8 *fontatrr)
{
	pszLoadLogFontName[2] = fontatrr;
}

static YW_ErrorType_T APP_GUIOpen(void)
{
    YW_ErrorType_T ErrorCode = YW_NO_ERROR;
    YWGUI_LayerParams_T     tLayerParam;
    YWGUI_KeyboardParams_T  tKeyboardParam[3];
    YWGUI_FrontPanelParams_T          ptFrontPanelParam;
    YWGUI_LbdParams_T                  tLbdParam;
    YWGUI_ImportParams_T    tImportParam;
    YWGUI_FontInfo_T  stFontInfo;

    APP_InitLayerParam(&tLayerParam);

    YWLIB_Memset(tKeyboardParam,0,sizeof(tKeyboardParam));

    YWLIB_Memset(&ptFrontPanelParam,0,sizeof(YWGUI_FrontPanelParams_T));

    /*Lbd*/
    YWLIB_Memset(&tLbdParam,0,sizeof(YWGUI_LbdParams_T));

    YWLIB_Memset(&tImportParam,0,sizeof(YWGUI_ImportParams_T));
    tImportParam.ptLayerParam=&tLayerParam;
    tImportParam.uRemoteNum = 0;
    tImportParam.ptRemoteParamHead = tKeyboardParam;
    tImportParam.ptFrontPanelParam = &ptFrontPanelParam;
    tImportParam.ptLbdParam = &tLbdParam;
    tImportParam.pfnInitDlgTLink = APP_InitDlgTemplateLink;
    tImportParam.pfnLoadString = YWSTR_GetString;
    tImportParam.pfnModifyDefScheme = App_ModifyDefScheme;
    tImportParam.pfnModifyCtrlDefSche = App_ModifyCtrlClassScheme;
    tImportParam.pfKeyPreProcess = NULL;
    tImportParam.uFontNum = 1;
    stFontInfo.pcFontAttr = (const S8*)"ttf-arial-rrncnn-10-10-UCS-2";
    stFontInfo.pcFontFile = (const S8*)"/root/spark/AppRes/arial.ttf";
   // stFontInfo.pcFontFile = (const S8*)"./AppRes/arial.ttf";
    tImportParam.pstFontInfo = &stFontInfo;

    tImportParam.uLogFontNum = 4;
    tImportParam.ppcLogFontName = (S8**)pszLoadLogFontName;
    if(YWGUI_Start(&tImportParam) != YW_NO_ERROR)
    {
        YWGUI_Stop();
        YWGUI_Term();
        printf("[YWTEST_WINDOW] YWGUI_Start error\n");
        return YWMID_ERROR_BAD_PARAMETER;
    }
    return ErrorCode;

}

void APP_MsgProc(void * para)
{
	//int iCount=0;
    YWGUI_Msg_T    Msg;
    YWGUI_HWnd_T  hMainWnd = YWGUI_NULL_HANDLE;

	APP_CommonResLoad();

    hMainWnd = YWPLUGIN_CreateMainMenuWindow();
    if(YWGUI_NULL_HANDLE == hMainWnd)
    {
        YWGUI_Term();
        printf("[YWTEST_WINDOW] error-----------------> APP_MsgProc\n");
        YWGUI_MEMLEAK_OUTPUT();
        return ;
    }
    while(YWGUI_GetMessage(&Msg, hMainWnd))
    {
        YWGUI_TranslateMessage(&Msg);
        YWGUI_DispatchMessage(&Msg);
    }
	
}


void APP_GuiInit(void)
{
    printf("-------------------------->APP_GuiInit\n");

    YWGUI_Init();
    APP_GUIOpen();
    return;
}



void APP_GuiTerm(void)
{
    printf("-------------------------->APP_GuiTerm\n");
	APP_CommonResUnLoad();

	client_term();
    YWGUI_Stop();
    YWGUI_Term();
    return;
}

