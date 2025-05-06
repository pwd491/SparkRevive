
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

#include "ywgui_ext.h"
#include "res_layout.h"
#include "camcfg_layout.h"
#include "gui.h"
#include "general.h"
#include "ywos.h"
#include "ywlib.h"
#include "camcfg.h"
#include "cfgfile_parse.h"
#include "ywimg_ext.h"



//Information window
static S32 YWNetClientMgCfgi_InforWndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
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
			YWGUI_Char_T awstr[64];
			YWGUI_Handle_T hTxt = YWGUI_NULL_HANDLE;

			//visit us
			hTxt = YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_INFOR_VISITUS_L);
			YWGUI_StaticSetXOffset(hTxt, 100);

		    YWLIB_Memset(awstr, 0x0, sizeof(awstr));
			YWLIB_Astr2wstr(awstr, "http://www.sparkfans.net");
		    YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_INFOR_VISITUS_R), awstr);

			YWLIB_Memset(awstr, 0x0, sizeof(awstr));
			YWLIB_Astr2wstr(awstr, "http://www.sat-ulc.eu/");
		    YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_INFOR_VISITUS_R1), awstr);

			YWLIB_Memset(awstr, 0x0, sizeof(awstr));
			YWLIB_Astr2wstr(awstr, "http://gisclub.tv/");
		    YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_INFOR_VISITUS_R2), awstr);

			YWLIB_Memset(awstr, 0x0, sizeof(awstr));
			YWLIB_Astr2wstr(awstr, "http://sateliti.info/");
		    YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_INFOR_VISITUS_R3), awstr);

			YWLIB_Memset(awstr, 0x0, sizeof(awstr));
			YWLIB_Astr2wstr(awstr, "http://www.satbox4all.nl");
		    YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_INFOR_VISITUS_R4), awstr);


    	}
            return 0;
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


        case YWGUI_MSG_COMMAND:
        {
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



//
static int YWNetClientMgCfgi_ReadMgCfgData(YWGUI_HWnd_T hWnd)
{
	char fullpath[512] = {0};
	char value[16] = {0};
	int ret = 0;

	YWLIB_Memset(fullpath, 0, sizeof(fullpath));
	YWLIB_Memset(value, 0, sizeof(value));

	YWLIB_Snprintf(fullpath, sizeof(fullpath), "%s/%s", MG_CC_CFG_PATH, "mg_cfg");
 	ret = mgcfg_readinfo(fullpath, "G", value,
		 sizeof(value), NULL, ':');

	if(ret == -1)
	{
		printf("mg_cfg has no G: {} data info!\n");
		return ret;
	}
	else
	{
		if(YWLIB_Strncmp(value, "01", 2) == 0)    //load newcamd.list file
		{
			if(YWGUI_IsWindowEnabled(YWGUI_GetDlgItem(hWnd, IDC_BTN_MG_CONFIG_NEWCAMD)))
			{
				YWGUI_SetFocus(YWGUI_GetDlgItem(hWnd, IDC_BTN_MG_CONFIG_NEWCAMD));
			}
			else
			{
				YWGUI_SetFocus(YWGUI_GetDlgItem(hWnd, IDC_BTN_MG_CONFIG_CCCAMD));
			}
		}
		else if(YWLIB_Strncmp(value, "32", 2) == 0)  //load cccamd.list
		{
			if(YWGUI_IsWindowEnabled(YWGUI_GetDlgItem(hWnd, IDC_BTN_MG_CONFIG_CCCAMD)))
			{
				YWGUI_SetFocus(YWGUI_GetDlgItem(hWnd, IDC_BTN_MG_CONFIG_CCCAMD));
			}
			else
			{
				YWGUI_SetFocus(YWGUI_GetDlgItem(hWnd, IDC_BTN_MG_CONFIG_NEWCAMD));
			}
		}
		else
		{
			printf("Unknow cfg file!\n");
		}
	}

	return 0;
}


static int YWNetClientMgCfgi_WriteMgCfgData(YWGUI_HWnd_T hWnd)
{
	char fullpath[512] = {0};
	char value[16] = {0};
	int ret = 0;
	YWGUI_Handle_T hCtrl;

	YWLIB_Memset(fullpath, 0, sizeof(fullpath));
	YWLIB_Memset(value, 0, sizeof(value));

	hCtrl = YWGUI_GetFocus(hWnd);
	if(YWGUI_GetDlgCtrlID(hCtrl) == IDC_BTN_MG_CONFIG_NEWCAMD)
	{
		YWLIB_Sprintf(value, (const S8 *)"01");
	}
	else
	{
		YWLIB_Sprintf(value, (const S8 *)"32");
	}

	YWLIB_Snprintf(fullpath, sizeof(fullpath), "%s/%s", MG_CC_CFG_PATH, "mg_cfg");

	ret = mgcfg_writeinfo(fullpath, "G", value, ':');

	if(ret == -1)
	{
		printf("mg_cfg has no G: {} data info!\n");
		return ret;
	}
	return 0;
}


static int YWNetClientMgCfgi_InitCtrlStatus(YWGUI_HWnd_T hWnd)
{
	FILE *hfile = NULL;
	char fullpath[512] = {0};


	YWLIB_Snprintf(fullpath, sizeof(fullpath), "%s/%s", MG_CC_CFG_PATH, "cccamd.list");
	hfile = fopen(fullpath,"r");
	if( NULL != hfile)
	{
		fclose(hfile);
		YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_MG_CONFIG_CCCAMD), TRUE);
	}


	YWLIB_Snprintf(fullpath, sizeof(fullpath), "%s/%s", MG_CC_CFG_PATH, "newcamd.list");
	hfile = fopen(fullpath,"r");
	if( NULL != hfile)
	{
		fclose(hfile);
		YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_MG_CONFIG_NEWCAMD), TRUE);
	}


	return 0;
}


static S32 YWNetClientMgCfgi_WndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
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
			YWGUI_Handle_T hBtn;
			YWGUI_Char_T wstr[64];
			YWLIB_Memset(wstr, 0x0, sizeof(wstr));
			YWLIB_Astr2wstr(wstr, "Net Client MgCfg");
			YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_MG_CONFIG_TITLE), wstr);

			YWLIB_Memset(wstr, 0x0, sizeof(wstr));
			YWLIB_Astr2wstr(wstr, "cccamd");
			YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_BTN_MG_CONFIG_CCCAMD), wstr);

			YWLIB_Memset(wstr, 0x0, sizeof(wstr));
			YWLIB_Astr2wstr(wstr, "newcamd");
			YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_BTN_MG_CONFIG_NEWCAMD), wstr);

			YWNetClientMgCfgi_InitCtrlStatus(hWnd);
			YWNetClientMgCfgi_ReadMgCfgData(hWnd);


    	}
            break;
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


        case YWGUI_MSG_COMMAND:
        {
			char fullpath[512] = {0};
            U16 id = (U16)YWGUI_LOWORD (wParam);
	        U16 notifyCode= (U16)YWGUI_HIWORD (wParam);
            if(notifyCode == YWGUI_NONE_CODE)
            {
            	YWLIB_Memset(fullpath, 0, sizeof(fullpath));
            	YWNetClientMgCfgi_WriteMgCfgData(hWnd);
				CFGDataList_Init();

                switch(id)
                {
                    case IDC_BTN_MG_CONFIG_NEWCAMD:
                    {
						YWNetClientEdit_SetCfgType(CFG_TYPE_MG_NEWCAMD);
						YWLIB_Snprintf(fullpath, sizeof(fullpath), "%s/%s", MG_CC_CFG_PATH, "newcamd.list");
						if(read_newcamdinfo(fullpath) == -1)
							return 0;
						YWNetClientEdit_CreateWindow(hWnd);
                    }
                        break;

                    case IDC_BTN_MG_CONFIG_CCCAMD:
                    {
						YWNetClientEdit_SetCfgType(CFG_TYPE_MG_CCCAMD);
						YWLIB_Snprintf(fullpath, sizeof(fullpath), "%s/%s", MG_CC_CFG_PATH, "cccamd.list");
						if(read_cccamdinfo(fullpath) == -1)
							return 0;
						YWNetClientEdit_CreateWindow(hWnd);
                    }
                        break;

                    default:
                        break;
                }
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
				{
            	}
					return 0;

                case YWGUI_SCANCODE_UP:
                case YWGUI_SCANCODE_DOWN:
                    break;

                case YWGUI_SCANCODE_OK:
                    break;
                case YWGUI_SCANCODE_RED:
                    return 0;
			    case YWGUI_SCANCODE_GREEN:
                    return 0;
                case YWGUI_SCANCODE_YELLOW:
                    return 0;
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




YWGUI_HWnd_T YWNetClientMgCfg_CreateWindow(YWGUI_HWnd_T hHost)
{
    YWGUI_HWnd_T hNetClientMgCfg = YWGUI_NULL_HANDLE;
    YW_ErrorType_T Error = YW_NO_ERROR;

    Error = YWGUI_CreateDialog(IDD_MG_CONFIG, hHost, YWNetClientMgCfgi_WndProc, 0, &hNetClientMgCfg);

    return (YW_NO_ERROR == Error) ? hNetClientMgCfg : YWGUI_NULL_HANDLE;
}



static int YWNetClientCfgi_ReadOscamData()
{
	char fullpath[512] = {0};

	YWLIB_Memset(fullpath, 0, sizeof(fullpath));

	CFGDataList_Init();

	YWLIB_Memset(fullpath, 0, sizeof(fullpath));
	YWLIB_Snprintf(fullpath, sizeof(fullpath), "%s/%s", OSCAM_SERVER_PATH, "oscam.server");

	YWNetClientEdit_SetCfgType(CFG_TYPE_OSCAM);

	return read_oscaminfo(fullpath);

}




static int YWNetClientCfgi_ReadCCcamCfgData()
{
	char fullpath[512] = {0};

	YWLIB_Memset(fullpath, 0, sizeof(fullpath));

	CFGDataList_Init();

	YWLIB_Memset(fullpath, 0, sizeof(fullpath));
	YWLIB_Snprintf(fullpath, sizeof(fullpath), "%s/%s", MG_CC_CFG_PATH, "CCcam.cfg");

	YWNetClientEdit_SetCfgType(CFG_TYPE_CCCAMCFG);

	return read_cccamcfginfo(fullpath);

}

//
static int YWNetClientCfgi_InitCtrlStatus(YWGUI_HWnd_T hWnd)
{
	FILE *hfile = NULL;
	char fullpath[512] = {0};

	YWLIB_Snprintf(fullpath, sizeof(fullpath), "%s/%s", OSCAM_SERVER_PATH, "oscam.server");
	hfile = fopen(fullpath,"r");
	if( NULL != hfile)
	{
		fclose(hfile);
		YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_OSCAM), TRUE);
	}


	YWLIB_Snprintf(fullpath, sizeof(fullpath), "%s/%s", MG_CC_CFG_PATH, "mg_cfg");
	hfile = fopen(fullpath,"r");
	if( NULL != hfile)
	{
		fclose(hfile);
		YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_MGCFG), TRUE);
	}

	YWLIB_Snprintf(fullpath, sizeof(fullpath), "%s/%s", MG_CC_CFG_PATH, "CCcam.cfg");
	hfile = fopen(fullpath,"r");
	if( NULL != hfile)
	{
		fclose(hfile);
		YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_CCCAMCFG), TRUE);
	}

	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_INFOR), TRUE);

	return 0;

}

//
static int YWNetClientCfgi_InitBtnTxt(YWGUI_HWnd_T hWnd)
{
	int i = 0;
	YWGUI_Char_T wstr[16];


	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "Oscam");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_OSCAM), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "MgCfg");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_MGCFG), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "CccamCfg");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_CCCAMCFG), wstr);

	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_INFOR), YWSTR_GetString(STR_INFORMATION));


	return 0;

}
//
static int YWNetClientCfgi_UpdateServPic(YWGUI_HWnd_T hWnd)
{
	int i = 0;

	for(i = 0; i < 3; i++)
	{
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_NET_CFG_OSCAM+i),
				&g_aGraphCellArray[YWCELL_RED], TRUE);
	}

	return 0;
}
//

//
static S32 YWNetClientCfgi_WndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
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
			YWNetClientCfgi_InitBtnTxt(hWnd);

			YWNetClientCfgi_InitCtrlStatus(hWnd);

			YWGUI_SetFocus(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_OSCAM));

    	}
            return 0;
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


        case YWGUI_MSG_COMMAND:
        {
            U16 id = (U16)YWGUI_LOWORD (wParam);
	        U16 notifyCode= (U16)YWGUI_HIWORD (wParam);
            if(notifyCode == YWGUI_NONE_CODE)
            {
                switch(id)
                {
                    case IDC_BTN_NET_CFG_OSCAM:
                    {
						if(YWNetClientCfgi_ReadOscamData() == -1)
						{
							YWGUI_HWnd_T hDlg = YWGUI_NULL_HANDLE;
							YWGUI_Char_T wstrbuf[128];
							YWLIB_Memset(wstrbuf, 0, sizeof(wstrbuf));
							
							YWLIB_SwprintfA(wstrbuf, (const S8 *)"Read oscam file failed");
							hDlg = YWGeneralPopInfo_CreateWindow(hWnd, wstrbuf, 3000);
							YWGUI_UpdateWindow( hDlg);
							return 0;
						}
						YWNetClientEdit_CreateWindow(hWnd);
                    }
                        break;

                    case IDC_BTN_NET_CFG_MGCFG:
                    {
						YWNetClientMgCfg_CreateWindow(hWnd);
                    }
                        break;

                    case IDC_BTN_NET_CFG_CCCAMCFG:
                    {
						if(YWNetClientCfgi_ReadCCcamCfgData() == -1)
							return 0;
						YWNetClientEdit_CreateWindow(hWnd);
                    }
                        break;

                    case IDC_BTN_NET_CFG_INFOR:
                    {
						YWGUI_HWnd_T hNetCfgInforDlg = YWGUI_NULL_HANDLE;

						YWGUI_CreateDialog(IDD_NET_CFG_INFOR, YWGUI_NULL_HANDLE, YWNetClientMgCfgi_InforWndProc, 0, &hNetCfgInforDlg);
		    		}
                        break;

                    default:
                        break;
                }
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
				{
            	}
					return 0;

                case YWGUI_SCANCODE_UP:
                case YWGUI_SCANCODE_DOWN:
                    break;

                case YWGUI_SCANCODE_OK:
                    break;
                case YWGUI_SCANCODE_RED:
                    return 0;
			    case YWGUI_SCANCODE_GREEN:
					//YWNetClientActivInfo_CreateWindow(hWnd);
                    return 0;
                case YWGUI_SCANCODE_YELLOW:
					YWGeneralLanguageSet_CreateWindow(hWnd);
                    return 0;
                default:
                    break;
            }
		}
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




YWGUI_HWnd_T YWPLUGIN_CreateMainMenuWindow(void)
{
    YWGUI_HWnd_T hNetClientCfg = YWGUI_NULL_HANDLE;
    YW_ErrorType_T Error = YW_NO_ERROR;

	
    Error = YWGUI_CreateDialog(IDD_NET_CLIENT_CONFIG, YWGUI_NULL_HANDLE, YWNetClientCfgi_WndProc, 0, &hNetClientCfg);

    return (YW_NO_ERROR == Error) ? hNetClientCfg : YWGUI_NULL_HANDLE;
}


void YWPLUGIN_InitGuiTemplate(void)
{

    YWGUI_AddTempletNode(&g_template_netclntcfg);
    YWGUI_AddTempletNode(&g_template_mgcfg);
    YWGUI_AddTempletNode(&g_template_activeinfocfg);
    YWGUI_AddTempletNode(&g_template_pinginfocfg);
    YWGUI_AddTempletNode(&g_template_netclntcfgedit);
    YWGUI_AddTempletNode(&g_template_netclntcfgping);
    YWGUI_AddTempletNode(&g_template_netcfginfo);
}


void YWPLUGIN_Init(void)
{
}

S8* YWPLUGIN_GetVersion(void)
{
    return "1.0.00";
}

void YWPLUGIN_Term(void)
{
}





