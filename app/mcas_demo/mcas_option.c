
#include <stdio.h>
#include <stdlib.h>

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


//static int ssspon = 1;



static S32 YWMCASi_OptionWndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
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
			char *str[] =
			{
				"OFF",
				"ON",					
			};
			S32 ii = 0;
			YWGUI_HWnd_T hLRCB = YWGUI_NULL_HANDLE;
			YWGUI_LRCBListItem_T stLbItem;
			int sssp = 1;


			YWLIB_Memset(wstr, 0, sizeof(wstr));
			YWLIB_Astr2wstr(wstr, "Option");
            YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_MCAS_OPTION_TITLE), wstr);

			YWLIB_Memset(wstr, 0, sizeof(wstr));
			YWLIB_Astr2wstr(wstr, "SSSP");
            YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_MCAS_OPTION), wstr);

		    stLbItem.dwFlags = 0;
		    stLbItem.dwAddData = 0;
		    stLbItem.dwImage = 0;
			hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_MCAS_OPTION);
	        for(ii = 0; ii < 2; ii++)
	        {
	        	YWLIB_Astr2wstr(wstr, str[ii]);
	            stLbItem.pszText = wstr;
	            YWGUI_LRCBAddItem(hLRCB, &stLbItem);
	        }
	        YWGUI_LRCBSetListVisibleCount(hLRCB, 2);
			//YWCASi_ReadSsspData(&sssp);
			//YWGUI_LRCBSetCurHotItemIndex(hLRCB, sssp);
	        YWGUI_LRCBSetCurHotItemIndex(hLRCB, 1);

            break;
		}
		case YWGUI_MSG_PAINT:
		{
			YWGUI_HDc_T hdc;
			YWGUI_Pixel_T OldColor;
			hdc = YWGUI_BeginPaint(hWnd);

			//divid bar
            YWGUI_SetBrushColor(hdc, Color_gray, OldColor);
        	YWGUI_FillBox(hdc, 0, 610, 1220,4);

            YWGUI_EndPaint(hWnd,hdc);

		}
			break;

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
				int sssp = 1;
	            YWGUI_HWnd_T hCT = YWGUI_NULL_HANDLE;
	            YWGUI_HWnd_T hLRC = YWGUI_NULL_HANDLE;

	            hLRC = YWGUI_GetDlgItem(hWnd, IDC_LRC_MCAS_OPTION);
				sssp = YWGUI_LRCBGetCurHotItemIndex(hLRC);

				//YWCASi_WriteSsspData(sssp);
				//sssp_writecontrolflag(sssp);
				//printf("sssp_writecontrolflag------------>sssp flag [%d]\n", sssp);
	            break;
        	}

        case YWGUI_MSG_DESTROY:
            break;

        default:
            break;
    }

    return YWGUI_DefaultDialogProc(hWnd,message,wParam,lParam);
}

YWGUI_HWnd_T YWMCAS_CreateOptionWindow(YWGUI_HWnd_T hHost)
{
    YWGUI_HWnd_T hPluginMain = YWGUI_NULL_HANDLE;
    YW_ErrorType_T Error = YW_NO_ERROR;

    Error = YWGUI_CreateDialog(IDD_MCAS_OPTION, hHost, YWMCASi_OptionWndProc, 0, &hPluginMain);

    return (YW_NO_ERROR == Error) ? hPluginMain : YWGUI_NULL_HANDLE;
}
/*
int YWMCAS_GetSsspOnFlag(void)
{
	return ssspon;
}
*/



