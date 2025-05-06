#include "stdio.h"
#include "ywdefs.h"
#include "ywos.h"
#include "ywlib.h"
#include "ywmid.h"
#include "ywgui_ext.h"
#include "res_layout.h"
#include "mcas_layout.h"
#include "gui.h"
#include "key_db.h"
#include "mcas_key.h"
#include "general.h"

#define TIMER_REFLESH_DATA 0x0001
#define MAX_SLOT 5

static BOOL menuon = FALSE;

#ifdef SLOT_2
static	char mainmenu_text[5][50] =
	{
	    "Slot 0 - Not Inserted",
		"Slot 1 - Not Inserted",
	    "Key Editor",
	    "Options",
	    "Information",
	};
#else
static	char mainmenu_text[4][50] =
	{
	    "Slot 0 - Not Inserted",
	    "Key Editor",
	    "Options",
	    "Information",
	};
#endif



S8* YWPLUGINi_GetMainMenuTxt(int item)
{
	return mainmenu_text[item];
}

static void YWPLUGINi_MainMenuInitBtnTxt(YWGUI_HWnd_T hWnd)
{
	YWGUI_Char_T wstr[100] = {0};
	int i = 0;
#ifdef MCAS_LITE
	int menunum = 1;
#else
	int menunum = 5;
#endif

		sprintf(mainmenu_text[0],"Slot 0 - %s", "Not Inserted");

 
#ifdef SLOT_2

		sprintf(mainmenu_text[1],"Slot 1 - %s", "Not Inserted");

#endif

	YWLIB_Memset(wstr, 0, sizeof(wstr));

	for(i = 0; i < menunum; i++)
	{
		YWLIB_Astr2wstr(wstr, mainmenu_text[i]);
		YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_BTN_MCAS_MAIN_SLOTSTATUS+i), wstr);
	}

}



static S32 YWPLUGINi_MainMenuWndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
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
			YWGUI_Char_T wstr[30] = {0};
			YWGUI_HWnd_T hTextWnd = YWGUI_NULL_HANDLE;

			menuon = TRUE;
			YWPLUGINi_MainMenuInitBtnTxt(hWnd);

			YWLIB_Memset(wstr, 0, sizeof(wstr));
			YWLIB_Astr2wstr(wstr, "Mcas Menu");
            hTextWnd = YWGUI_GetDlgItem(hWnd, IDC_BTN_MCAS_MAIN_TITLE);

            YWGUI_SetWindowText(hTextWnd, wstr);
			YWGUI_SetTimer(hWnd, TIMER_REFLESH_DATA, 1000);
            break;
		}

        case YWGUI_MSG_COMMAND:
        {
            unsigned short id = (unsigned short)YWGUI_LOWORD(wParam);
            unsigned short notifyCode = (unsigned short)YWGUI_HIWORD(wParam);

            if(notifyCode == YWGUI_NONE_CODE)
            {
            	switch(id)
        		{
					case IDC_BTN_MCAS_MAIN_SLOTSTATUS:

						break;
#ifdef SLOT_2						
					case IDC_BTN_MCAS_MAIN_SLOTSTATUS1:

						break;
#endif
					case IDC_BTN_MCAS_MAIN_KEYEDITOR:
						YWMCAS_CreateKeyEditorWindow(hWnd);

						break;

					case IDC_BTN_MCAS_MAIN_OPTION:
						YWMCAS_CreateOptionWindow(hWnd);
						break;

					case IDC_BTN_MCAS_MAIN_INFORMATION:
						YWMCAS_CreateSysInfoWindow(hWnd);
						break;
					default:
						break;
        		}
            }
			break;
        }

		case YWGUI_MSG_TIMER:
			if(TIMER_REFLESH_DATA == (S32)wParam)
			{
				YWPLUGINi_MainMenuInitBtnTxt(hWnd);
			}
		break;

        case YWGUI_MSG_KEYDOWN:
    	{
            U16 scancode=YWGUI_LOWORD(wParam);


            switch(scancode)
            {
                case YWGUI_SCANCODE_EXIT:
					menuon = FALSE;
                    YWGUI_DestroyMainWindow(hWnd);
                    break;

				case YWGUI_SCANCODE_0:
					break;

                case YWGUI_SCANCODE_OK:
                    break;

                default:
                    break;
            }
            break;
		}

        case YWGUI_MSG_CLOSE:
            break;

        case YWGUI_MSG_DESTROY:
            YWOS_Trace(YWOS_TRACE_INFO, "msg quit.\n");
            YWGUI_SendMessage(hWnd, YWGUI_MSG_QUIT, 0, 0);
            break;

        default:
            break;
    }
	//printf("----------------------------->YWPLUGINi_CardInfoWndProc\n");

    return YWGUI_DefaultDialogProc(hWnd,message,wParam,lParam);
}

YWGUI_HWnd_T YWPLUGIN_CreateMainMenuWindow(void)
{
    YWGUI_HWnd_T hPluginMain = YWGUI_NULL_HANDLE;
    YW_ErrorType_T Error = YW_NO_ERROR;

    Error = YWGUI_CreateDialog(IDD_MCAS_MAIN, YWGUI_NULL_HANDLE, YWPLUGINi_MainMenuWndProc, 0, &hPluginMain);

    return (YW_NO_ERROR == Error) ? hPluginMain : YWGUI_NULL_HANDLE;
}

void YWPLUGIN_InitGuiTemplate(void)
{

    YWGUI_AddTempletNode(&g_template_mcascardinfo);
    YWGUI_AddTempletNode(&g_template_mcaskeyeditorentry);

    YWGUI_AddTempletNode(&g_template_mcasmain);
    //YWGUI_AddTempletNode(&g_template_pluginmain);
    YWGUI_AddTempletNode(&g_template_pluginkeyinfo);
    YWGUI_AddTempletNode(&g_template_pluginkeyedit);
    YWGUI_AddTempletNode(&g_template_pluginkeyadd);
    YWGUI_AddTempletNode(&g_template_mcasoption);
    YWGUI_AddTempletNode(&g_template_mcassysinfo);

}
S8*YWPLUGIN_GetVersion()
{
    return (S8*)"1.0.00";

}

void YWPLUGIN_Init(void)
{
	int keycount;


#ifdef SUPPORT_DVBAPI
	dvbapi_init();
	sci_init();
#endif

}

void YWPLUGIN_Term(void)
{

#ifdef SUPPORT_DVBAPI
	sci_term();
	dvbapi_term();
#endif




}

