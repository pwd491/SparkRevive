#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

#include "mxml.h"
#include "ywgui_ext.h"
#include "res_layout.h"
#include "tuner_layout.h"
#include "gui.h"
#include "general.h"
#include "ywpublic.h"

#include "ywos.h"
#include "ywlib.h"
#include "frontend.h"
#include "tuner.h"


static void YWTUNER_Init(YWGUI_HWnd_T hWnd)
{
    YWGUI_Char_T wStr[256];
	YWGUI_Handle_T hCT = YWGUI_NULL_HANDLE;
	YWGUI_Handle_T hTXT = YWGUI_NULL_HANDLE;
	YWGUI_Handle_T hLRCB = YWGUI_NULL_HANDLE;
    int ii = 0;
	YWGUI_LRCBListItem_T stLbItem;
    
	char *pstr_tuner[] =
	{
		"0",
		"1",
	};

	char *pstr_22k[] =
	{
		"ON",
		"OFF",
	};

	char *pstr_diseqc[] =
	{
		"A",
		"B",
		"C",
		"D",
	};

	char *pstr_pol[] =
	{
		"H",
		"V",
	};

	//title
    YWLIB_Memset(wStr, 0, sizeof(wStr));
    YWLIB_Astr2wstr(wStr,"Tuner demo");
    //YWLIB_SwprintfA(wStr, (const S8*)"%s", (S8*)"Tuner demo");
	hTXT = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_TITLE);
    YWGUI_SetWindowText(hTXT, wStr);

	//tuner
    YWLIB_Memset(wStr, 0, sizeof(wStr));
    YWLIB_Astr2wstr(wStr,"Tuner");
	hTXT = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_SAT_L);
    YWGUI_SetWindowText(hTXT, wStr);

    hLRCB = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_SAT_R);
    for(ii = 0; ii < YWGUI_ARRAY_SIZE(pstr_tuner); ii++)
    {
        YWLIB_Astr2wstr(wStr, pstr_tuner[ii]);
        stLbItem.pszText = wStr;
        YWGUI_LRCBAddItem(hLRCB, &stLbItem);
    }
    YWGUI_LRCBSetListVisibleCount(hLRCB, 2);
    YWGUI_LRCBSetCurHotItemIndex(hLRCB, 0);

    YWLIB_Memset(wStr, 0, sizeof(wStr));
    YWLIB_Astr2wstr(wStr,"Satellite test");
	hTXT = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_SAT_R);
    YWGUI_SetWindowText(hTXT, wStr);

	//lnb
    YWLIB_Memset(wStr, 0, sizeof(wStr));
    YWLIB_Astr2wstr(wStr,"Lnb");
	hTXT = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_LNB_L);
    YWGUI_SetWindowText(hTXT, wStr);

    YWLIB_Memset(wStr, 0, sizeof(wStr));
    YWLIB_Astr2wstr(wStr,"C-BAND");
	hTXT = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_LNB_R);
    YWGUI_SetWindowText(hTXT, wStr);

	//22k
    YWLIB_Memset(wStr, 0, sizeof(wStr));
    YWLIB_Astr2wstr(wStr,"22K");
	hTXT = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_22k_L);
    YWGUI_SetWindowText(hTXT, wStr);

    hLRCB = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_22k_R);
    for(ii = 0; ii < YWGUI_ARRAY_SIZE(pstr_22k); ii++)
    {
        YWLIB_Astr2wstr(wStr, pstr_22k[ii]);
        stLbItem.pszText = wStr;
        YWGUI_LRCBAddItem(hLRCB, &stLbItem);
    }
    YWGUI_LRCBSetListVisibleCount(hLRCB, 2);
    YWGUI_LRCBSetCurHotItemIndex(hLRCB, 0);


	//diseqc
    YWLIB_Memset(wStr, 0, sizeof(wStr));
    YWLIB_Astr2wstr(wStr,"Diseqc");
	hTXT = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_DISEQC_L);
    YWGUI_SetWindowText(hTXT, wStr);

    hLRCB = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_DISEQC_R);
    for(ii = 0; ii < YWGUI_ARRAY_SIZE(pstr_diseqc); ii++)
    {
        YWLIB_Astr2wstr(wStr, pstr_diseqc[ii]);
        stLbItem.pszText = wStr;
        YWGUI_LRCBAddItem(hLRCB, &stLbItem);
    }
    YWGUI_LRCBSetListVisibleCount(hLRCB, 4);
    YWGUI_LRCBSetCurHotItemIndex(hLRCB, 0);

	//pol
    YWLIB_Memset(wStr, 0, sizeof(wStr));
    YWLIB_Astr2wstr(wStr,"Polarization");
	hTXT = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_POL_L);
    YWGUI_SetWindowText(hTXT, wStr);

    hLRCB = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_POL_R);
    for(ii = 0; ii < YWGUI_ARRAY_SIZE(pstr_pol); ii++)
    {
        YWLIB_Astr2wstr(wStr, pstr_pol[ii]);
        stLbItem.pszText = wStr;
        YWGUI_LRCBAddItem(hLRCB, &stLbItem);
    }
    YWGUI_LRCBSetListVisibleCount(hLRCB, 2);
    YWGUI_LRCBSetCurHotItemIndex(hLRCB, 0);

	//freq
    YWLIB_Memset(wStr, 0, sizeof(wStr));
    YWLIB_Astr2wstr(wStr,"Frequency");
	hTXT = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_FREQ_L);
    YWGUI_SetWindowText(hTXT, wStr);

    YWLIB_Memset(wStr, 0, sizeof(wStr));
    YWLIB_Astr2wstr(wStr,"3840");
	hTXT = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_FREQ_R);
    YWGUI_SetWindowText(hTXT, wStr);

    //Symbol_rate
    YWLIB_Memset(wStr, 0, sizeof(wStr));
    YWLIB_Astr2wstr(wStr,"Symbol rate");
	hTXT = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_SYMRATE_L);
    YWGUI_SetWindowText(hTXT, wStr);

    YWLIB_Memset(wStr, 0, sizeof(wStr));
    YWLIB_Astr2wstr(wStr,"27500");
	hTXT = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_SYMRATE_R);
    YWGUI_SetWindowText(hTXT, wStr);

	//red icon
    YWLIB_Memset(wStr, 0, sizeof(wStr));
    YWLIB_Astr2wstr(wStr,"Start");
	hTXT = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_RED_R);
    YWGUI_SetWindowText(hTXT, wStr);
}

static void YWTUNER_RedKeyProcess(YWGUI_HWnd_T hWnd)
{
    int fd = 0;
    U32 adapter = 1;
    U32 frontend = 0;

    char* lnb; /*UNIVERSAL, C-BAND*/
    fe_sec_tone_mode_t e22K;
    res_tuner_diseqc_T eDiseqc;
    int freq;  /*MHZ*/
    int sym;
    int pol_vert;/*horizontal=0,vertical=1*/
    int lock = 0;

    YWGUI_HWnd_T hControl = YWGUI_NULL_HANDLE;
    YWGUI_Char_T wstr[64] = {0};
    S8 str[64] = {0};

    /*frontend*/
    hControl = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_SAT_R);
    frontend = YWGUI_LRCBGetCurHotItemIndex(hControl);
    /*LNB*/
    hControl = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_LNB_R);
	YWGUI_GetWindowText(hControl, wstr, sizeof(wstr));
	YWLIB_Wstr2AscStr(str, wstr);
    lnb = str;
    /*22k*/
    hControl = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_22k_R);
    e22K = YWGUI_LRCBGetCurHotItemIndex(hControl);
    /*Diseqc*/
    hControl = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_DISEQC_R);
    eDiseqc = YWGUI_LRCBGetCurHotItemIndex(hControl);
    /*freq*/
    hControl = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_FREQ_R);
	YWGUI_GetWindowText(hControl, wstr, sizeof(wstr));
	freq = YWLIB_Watoi(wstr);
    /*Sym*/
    hControl = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_SYMRATE_R);
	YWGUI_GetWindowText(hControl, wstr, sizeof(wstr));
	sym = YWLIB_Watoi(wstr);
    /*pol*/
    hControl = YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_POL_R);
    pol_vert = YWGUI_LRCBGetCurHotItemIndex(hControl);

    printf("--new tune parameter:\n");
    printf("frontend: %d LNB: %s 22k: %d diseqc: %d freq: %d sym: %d pol: %d\n",
        frontend, lnb, e22K, eDiseqc, freq, sym, pol_vert);

    if(!YWPUBLIC_isTunerAllow(frontend))
    {
        YWLIB_Memset(wstr, 0, sizeof(wstr));
        YWLIB_Snprintf(str, sizeof(str), "the tuner is invalid.");
        YWPUBLIC_Utf8To16(str, YWLIB_Strlen(str), (S8 *)wstr, sizeof(wstr));
        YWGeneralPopInfo_CreateWindow(hWnd, wstr, 2000);
        return;
    }

    fd = open_frontend(adapter, frontend);
    if(fd <= 0)
    {
        printf("open frontend error.\n");
        YWLIB_Memset(wstr, 0, sizeof(wstr));
        YWLIB_Snprintf(str, sizeof(str), "open frontend error");
        YWPUBLIC_Utf8To16(str, YWLIB_Strlen(str), (S8 *)wstr, sizeof(wstr));
        YWGeneralPopInfo_CreateWindow(hWnd, wstr, 2000);    
        return;
    }
    if(!start_frontend(fd, lnb, e22K, eDiseqc, freq, sym*1000, pol_vert))
    {
        YWLIB_Memset(wstr, 0, sizeof(wstr));
        YWLIB_Snprintf(str, sizeof(str), "Invalid argument");
        YWPUBLIC_Utf8To16(str, YWLIB_Strlen(str), (S8 *)wstr, sizeof(wstr));
        YWGeneralPopInfo_CreateWindow(hWnd, wstr, 2000);    
    }
    else
    {
        lock = check_frontend(fd);
        if(1 == lock)
        {
            YWLIB_Memset(wstr, 0, sizeof(wstr));
            YWLIB_Snprintf(str, sizeof(str), "the signal is lock!");
            YWPUBLIC_Utf8To16(str, YWLIB_Strlen(str), (S8 *)wstr, sizeof(wstr));
            YWGeneralPopInfo_CreateWindow(hWnd, wstr, 2000);
        }
        else
        {
            YWLIB_Memset(wstr, 0, sizeof(wstr));
            YWLIB_Snprintf(str, sizeof(str), "the signal is unlock!");
            YWPUBLIC_Utf8To16(str, YWLIB_Strlen(str), (S8 *)wstr, sizeof(wstr));
            YWGeneralPopInfo_CreateWindow(hWnd, wstr, 2000);
        }
    }
    close_frontend(fd);
    return 0;

}

static S32 YWTUNER_WndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
{
    switch (message)
    {
        case YWGUI_MSG_NCCREATE:
        {
            YWGUI_SetWEColor(hWnd, YWGUI_MAINWND_BGC, Color_black);
            YWGUI_SetWEShapeState(hWnd, YWGUI_STATUS_NORMAL, &g_tSubMenuFrameShapeState);
            break;
        }

        case YWGUI_MSG_INITDIALOG:
		{
            YWGUI_SetFocus(YWGUI_GetDlgItem(hWnd, IDC_TXT_TUNER_DEMO_SAT_R));
            YWTUNER_Init(hWnd);
    	}

        case YWGUI_MSG_PAINT:
		{
			YWGUI_HDc_T hdc;
			YWGUI_Pixel_T OldColor;

            hdc = YWGUI_BeginPaint(hWnd);

			//divid bar
            YWGUI_SetBrushColor(hdc, Color_grayblue, OldColor);
        	YWGUI_FillBox(hdc, 0, 610, 1220,4);

            YWGUI_EndPaint(hWnd,hdc);
    	}
        break;


        case YWGUI_MSG_COMMAND:
        {
            U16 id = (U16)YWGUI_LOWORD (wParam);
            U16 notifyCode= (U16)YWGUI_HIWORD (wParam);
            if(notifyCode == YWGUI_NONE_CODE)
            {
                switch(id)
                {
                    case IDC_TXT_TUNER_DEMO_LNB_R:
                    {
                        YWGUI_Char_T wstr[128];
                        YWPLUGINREAME_Param_T tPluginRenameParam;
                        YWLIB_Memset(wstr, 0, sizeof(wstr));
                        tPluginRenameParam.hHosting = hWnd;
                        tPluginRenameParam.pStrContent = wstr;
                        tPluginRenameParam.nEditLimitLen = 16;
                        tPluginRenameParam.pStrTitle = NULL;
                        YWPlugin_CreateRenameWindow(&tPluginRenameParam);
                    }
                    break;
                    case IDC_TXT_TUNER_DEMO_FREQ_R:
                    {
                        YWGUI_Char_T wstr[128];
                        YWPLUGINREAME_Param_T tPluginRenameParam;
                        YWLIB_Memset(wstr, 0, sizeof(wstr));
                        tPluginRenameParam.hHosting = hWnd;
                        tPluginRenameParam.pStrContent = wstr;
                        tPluginRenameParam.nEditLimitLen = 4;
                        tPluginRenameParam.pStrTitle = NULL;
                        YWPlugin_CreateRenameWindow(&tPluginRenameParam);
                    }
                    break;
                    case IDC_TXT_TUNER_DEMO_SYMRATE_R:
                    {
                        YWGUI_Char_T wstr[128];
                        YWPLUGINREAME_Param_T tPluginRenameParam;
                        YWLIB_Memset(wstr, 0, sizeof(wstr));
                        tPluginRenameParam.hHosting = hWnd;
                        tPluginRenameParam.pStrContent = wstr;
                        tPluginRenameParam.nEditLimitLen = 5;
                        tPluginRenameParam.pStrTitle = NULL;
                        YWPlugin_CreateRenameWindow(&tPluginRenameParam);
                    }
                    break;
                    default:
                        break;
                }
            }
        }
        break;


		case YWPUBLIC_MSG_RENAME:
        {

			if(lParam)
			{
				U16 ctrid = 0;
				YWGUI_Handle_T hFocus = YWGUI_NULL_HANDLE;
				hFocus = YWGUI_GetFocus(hWnd);
				YWGUI_SetWindowText(hFocus, (YWGUI_Char_T*)wParam);
			}
        }
        break;
        case YWGUI_MSG_KEYDOWN:
    	{
            U16 scancode=YWGUI_LOWORD(wParam);

            switch(scancode)
            {
                case YWGUI_SCANCODE_EXIT:
                    YWGUI_SendMessage(hWnd, YWGUI_MSG_CLOSE, 0, 0);
                    break;

                case YWGUI_SCANCODE_LEFT:
                case YWGUI_SCANCODE_RIGHT:
                case YWGUI_SCANCODE_UP:
                case YWGUI_SCANCODE_DOWN:
                    break;
                case YWGUI_SCANCODE_OK:
                    break;
                case YWGUI_SCANCODE_RED:
                    YWTUNER_RedKeyProcess(hWnd);
                    break;
			    case YWGUI_SCANCODE_GREEN:
                    break;
                default:
                    break;
            }
		}
            break;

        case YWGUI_MSG_CLOSE:
            break;

        case YWGUI_MSG_DESTROY:
            break;

        default:
            break;
    }
    return YWGUI_DefaultDialogProc(hWnd,message,wParam,lParam);
}


YWGUI_HWnd_T YWPLUGIN_CreateMainMenuWindow(void)
{
    YWGUI_HWnd_T htuner = YWGUI_NULL_HANDLE;
    YW_ErrorType_T Error = YW_NO_ERROR;
    Error = YWGUI_CreateDialog(IDD_TUNER_DEMO_ENTRY, YWGUI_NULL_HANDLE, YWTUNER_WndProc, 0, &htuner);
    return (YW_NO_ERROR == Error) ? htuner : YWGUI_NULL_HANDLE;
}


void YWPLUGIN_InitGuiTemplate(void)
{
    YWGUI_AddTempletNode(&g_template_tuner_demo);
}

void YWPLUGIN_Init(void)
{
    YWPLUGIN_SetGuiShowDirect(TRUE);
    YWPLUGIN_SetAppCloseWithGui(TRUE);
}

S8* YWPLUGIN_GetVersion(void)
{
    return (S8*)"1.0.00";
}

void YWPLUGIN_Term(void)
{
}

