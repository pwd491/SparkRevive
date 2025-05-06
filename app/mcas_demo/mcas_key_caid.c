#include "stdio.h"
#include "ywdefs.h"
#include "ywos.h"
#include "ywlib.h"
#include "ywmid.h"
#include "ywgui_ext.h"
#include "res_layout.h"
#include "mcas_layout.h"
#include "gui.h"
#include "mcas_key.h"
#include "general.h"

void mcas_keyeditor_getmenuinfo(YWGUI_HWnd_T hWnd)
{
	int max_count;

	max_count = 8;
	//mcas_debug("mcas_get_max_caid_count[%d] \n", max_count);

    YWGUI_LTSetTotalLine(YWGUI_GetDlgItem(hWnd, IDC_LT_MCAS_KEYEDITOR), max_count,0);
}

void mcas_keyeditor_getmenulist(YWGUI_HWnd_T hWnd)
{
	int i;
	char *saveptr;
	int max_count;
	U16 caid;
    YWGUI_LTItemInfo_T tItemInfo;

	YWGUI_Char_T wstr[64];

	YWLIB_Memset(wstr, 0, sizeof(wstr));

	max_count = 8;

	for(i = 0; i < max_count; i++)
	{
		tItemInfo.Type = YWGUI_LTINFO_TEXT;

		YWLIB_Astr2wstr(wstr, "demo");
        tItemInfo.Info.pText = wstr;

		//mcas_debug("choice[%d]  : %x %s\n", i, mcas_get_caid_from_count(i),  saveptr);
		YWGUI_LTSetItemInfo(YWGUI_GetDlgItem(hWnd, IDC_LT_MCAS_KEYEDITOR), i, 0, &tItemInfo);
	}


}



static S32 YWPLUGINi_KeyEditorWndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
{
	int reflesh = 0;
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
			YWGUI_Char_T wstr[100] = {0};
			YWGUI_HWnd_T hTextWnd;

			YWLIB_Memset(wstr, 0, sizeof(wstr));
#ifdef SLOT_2
			YWLIB_Astr2wstr(wstr, (char *)YWPLUGINi_GetMainMenuTxt(2));
#else
			YWLIB_Astr2wstr(wstr, (char *)YWPLUGINi_GetMainMenuTxt(1));
#endif
			 hTextWnd = YWGUI_GetDlgItem(hWnd, IDC_TTX_MCAS_KEYEDITOR_TITLE);
			YWGUI_SetWindowText(hTextWnd, wstr);
			mcas_keyeditor_getmenuinfo(hWnd);

            break;
		}

        case YWGUI_MSG_COMMAND:
        {
            unsigned short id = (unsigned short)YWGUI_LOWORD(wParam);
            unsigned short notifyCode = (unsigned short)YWGUI_HIWORD(wParam);

			//mcas_debug("+++++++++++++++++++++++++++\n");
            if(notifyCode == YWGUI_LTN_NEEDDATA)
            {
				if (id == IDC_LT_MCAS_KEYEDITOR)
				{
					mcas_keyeditor_getmenulist(hWnd);
				}
            }
			break;
        }

        case YWGUI_MSG_KEYDOWN:
    	{
            U16 scancode=YWGUI_LOWORD(wParam);

            switch(scancode)
            {
                case YWGUI_SCANCODE_EXIT:
                    YWGUI_SendMessage(hWnd, YWGUI_MSG_CLOSE, 0, 0);
                    return 0;

                case YWGUI_SCANCODE_OK:
					{
						U16 lineno, caid;

						lineno = YWGUI_LTGetCurLine(YWGUI_GetDlgItem(hWnd, IDC_LT_MCAS_KEYEDITOR));
						caid = 0x2600;
						YWMCAS_CreatKeyInfoWindow(hWnd, caid);
                	}
                    break;
				case YWGUI_SCANCODE_0:
				{
                        YWPLUGINREAME_Param_T tPluginRenameParam;

                        tPluginRenameParam.hHosting = hWnd;
                        tPluginRenameParam.pStrContent = NULL;
                        tPluginRenameParam.nEditLimitLen = 60;
                        YWPlugin_CreateRenameWindow(&tPluginRenameParam);

				}
					break;



				default:
                    break;
            }
            break;
		}

      case YWGUI_MSG_USER:
			mcas_keyeditor_getmenuinfo(hWnd);
			break;
			
        case YWGUI_MSG_CLOSE:
            break;

        case YWGUI_MSG_DESTROY:
            YWOS_Trace(YWOS_TRACE_INFO, "msg quit.\n");
            YWGUI_SendMessage(hWnd, YWGUI_MSG_QUIT, 0, 0);
            break;

        default:
            break;
    }

    return YWGUI_DefaultDialogProc(hWnd,message,wParam,lParam);
}


YWGUI_HWnd_T YWMCAS_CreateKeyEditorWindow(YWGUI_HWnd_T hHost)
{
    YWGUI_HWnd_T hPluginMain = YWGUI_NULL_HANDLE;
    YW_ErrorType_T Error = YW_NO_ERROR;

    Error = YWGUI_CreateDialog(IDC_MCAS_KEYEDITOR, hHost, YWPLUGINi_KeyEditorWndProc, 0, &hPluginMain);

    return (YW_NO_ERROR == Error) ? hPluginMain : YWGUI_NULL_HANDLE;
}

