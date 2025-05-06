





#include "ywdefs.h"
#include "ywos.h"
#include "ywlib.h"
#include "ywmid.h"
#include "ywgui_ext.h"
#include "res_layout.h"
#include "mcas_layout.h"
#include "gui.h"
#include "mcas_key.h"

#define MCAS_VERSION "1.0.05"
static S32 YWMCASi_SysInfoWndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
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
		    YWLIB_WChar_T awstr[64];
		    S8 astr[64];
			YWGUI_Handle_T hTxt = YWGUI_NULL_HANDLE;

			//title
			YWLIB_Memset(awstr, 0, sizeof(awstr));
			YWLIB_Astr2wstr(awstr, "Information");
            YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_MCAS_SYSINFO_TITLE), awstr);

			//software version
			YWLIB_Memset(awstr, 0, sizeof(awstr));
			YWLIB_Astr2wstr(awstr, "Software Version");
			hTxt = YWGUI_GetDlgItem(hWnd, IDC_TXT_MCAS_SYSINFO_VERSION_L);
			YWGUI_StaticSetXOffset(hTxt, 100);
            YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_MCAS_SYSINFO_VERSION_L), awstr);

			YWLIB_Memset(awstr, 0, sizeof(awstr));
			YWLIB_Astr2wstr(awstr, MCAS_VERSION);
            YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_MCAS_SYSINFO_VERSION_R), awstr);

			//compiled time
			YWLIB_Memset(awstr, 0, sizeof(awstr));
			YWLIB_Astr2wstr(awstr, "Compiled Time");
			hTxt = YWGUI_GetDlgItem(hWnd, IDC_TXT_MCAS_SYSINFO_COMPILEDT_L);
			YWGUI_StaticSetXOffset(hTxt, 100);
            YWGUI_SetWindowText(hTxt, awstr);

		    YWLIB_Memset(astr, 0x0, sizeof(astr));
		    YWLIB_Memset(awstr, 0x0, sizeof(awstr));
		    YWLIB_Sprintf(astr, (S8 *)"%s %s",__DATE__,__TIME__);
		    YWLIB_Astr2wstr(awstr, astr);
		    YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_MCAS_SYSINFO_COMPILEDT_R), awstr);

			//visit us
			YWLIB_Memset(awstr, 0, sizeof(awstr));
			YWLIB_Astr2wstr(awstr, "Visit us:");
			hTxt = YWGUI_GetDlgItem(hWnd, IDC_TXT_MCAS_SYSINFO_VISITUS_L);
			YWGUI_StaticSetXOffset(hTxt, 100);
            YWGUI_SetWindowText(hTxt, awstr);

		    YWLIB_Memset(awstr, 0x0, sizeof(awstr));
			YWLIB_Astr2wstr(awstr, "http://www.sparkfans.net");
		    YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_MCAS_SYSINFO_VISITUS_R), awstr);

		    YWLIB_Memset(awstr, 0x0, sizeof(awstr));
			YWLIB_Astr2wstr(awstr, "http://www.sat-ulc.eu/");
		    YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_MCAS_SYSINFO_VISITUS_R1), awstr);

		    YWLIB_Memset(awstr, 0x0, sizeof(awstr));
			YWLIB_Astr2wstr(awstr, "http://gisclub.tv/");
		    YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_MCAS_SYSINFO_VISITUS_R2), awstr);

		    YWLIB_Memset(awstr, 0x0, sizeof(awstr));
			YWLIB_Astr2wstr(awstr, "http://sateliti.info/");
		    YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_MCAS_SYSINFO_VISITUS_R3), awstr);

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
                    break;

                default:
                    break;
            }
            break;
		}

        case YWGUI_MSG_CLOSE:
			{
	            break;
        	}

        case YWGUI_MSG_DESTROY:
            break;

        default:
            break;
    }

    return YWGUI_DefaultDialogProc(hWnd,message,wParam,lParam);
}

YWGUI_HWnd_T YWMCAS_CreateSysInfoWindow(YWGUI_HWnd_T hHost)
{
    YWGUI_HWnd_T hPluginMain = YWGUI_NULL_HANDLE;
    YW_ErrorType_T Error = YW_NO_ERROR;

    Error = YWGUI_CreateDialog(IDD_MCAS_SYSINFO, hHost, YWMCASi_SysInfoWndProc, 0, &hPluginMain);

    return (YW_NO_ERROR == Error) ? hPluginMain : YWGUI_NULL_HANDLE;
}





