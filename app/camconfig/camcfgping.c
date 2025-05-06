

#include <stdio.h>

#include "ywgui_ext.h"
#include "res_layout.h"
#include "camcfg_layout.h"
#include "gui.h"
#include "general.h"
#include "cfgfile_parse.h"


#define PING_FINLE_NAME "ping.txt"
#define TIMER_PING_OPERAT 0x7777
#define TIMER_READ_DATA 0x8888
#define MAX_PING_DATA   1024

static int       g_timeout = 0;
static int       g_packetsize = 0;
static int       g_serverindex = 0;


static int YWNetClientPingInfoi_file(const char *file, char *buf,int *file_size)
{
	FILE *in = NULL;
	int i=0;
	int iBigfile = 0;

	*file_size =0;

	in = fopen(file,"rt");
	if( NULL == in) {
		printf("can not open file!\n");
		return -1;
	}

	buf[i]=fgetc(in);

	//load initialization file
	while( buf[i]!= (char)EOF) {
		i++;
		if( i >= MAX_PING_DATA) //file too big
		{
			printf("file too big!\n");
			iBigfile = 1;
			break;
		}
		buf[i]=fgetc(in);
	/*	if(buf[i] == '\r')
		{
			i--;
			continue;
		}*/
	}
	fclose(in);
	if(iBigfile == 1)
	{
		buf[MAX_PING_DATA-1]='\0';
		*file_size = MAX_PING_DATA;

		return -1;
	}
	else
	{
		buf[i]='\0';
		*file_size = i;
		return 0;
	}
}

static S32 YWNetClientPingInfoi_WndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
{
    switch (message)
    {
        case YWGUI_MSG_NCCREATE:
        {
            YWGUI_SetWEColor(hWnd, YWGUI_MAINWND_BGC, Color_black);
            YWGUI_SetWEShapeState(hWnd, YWGUI_STATUS_NORMAL, &g_tPopDlgHaveHeadShapeState);
            break;
        }

        case YWGUI_MSG_INITDIALOG:
		{
			FILE *hfile = NULL;
			char cmd[128];

			hfile = fopen("./"PING_FINLE_NAME, "r");
			if( NULL != hfile)
			{
				fclose(hfile);
				printf("rm ping file!\n");
				YWLIB_Memset(cmd, 0, sizeof(cmd));
				YWLIB_Sprintf(cmd, (const S8 *)"rm -f ./"PING_FINLE_NAME);
				system(cmd);
			}

			YWGUI_SetTimer(hWnd, TIMER_PING_OPERAT, 100);
    	}
            break;

		case YWGUI_MSG_TIMER:
		{
            if(TIMER_READ_DATA == (S32)wParam)
            {
            	YWGUI_Handle_T hTxt;
				char buf[MAX_PING_DATA]={0};
				YWGUI_Char_T wbuf[MAX_PING_DATA]={0};
				int file_size;

				YWLIB_Memset(buf, 0, sizeof(buf));
				YWLIB_Memset(wbuf, 0, sizeof(wbuf));

				if(0 != YWNetClientPingInfoi_file("./"PING_FINLE_NAME,buf,&file_size))
				{
					printf("load file failed\n");
					return -1;
				}
				hTxt = YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_PING_INFO);

				YWLIB_Astr2wstr(wbuf, buf);
				YWGUI_SetWindowText(hTxt, wbuf);
				YWGUI_ResetTimer(hWnd, TIMER_READ_DATA, 1000*1);
            }
			else if(TIMER_PING_OPERAT == (S32)wParam)
			{
				char str[128];
				CFGInfo_T node;
				YWGUI_Handle_T hDlg;
				
				YWGUI_Char_T wstr[512];
				YWLIB_Memset(wstr, 0, sizeof(wstr));

				YWLIB_Memset(str, 0, sizeof(str));
				CFGDataList_GetNode(g_serverindex, &node);

				YWLIB_Sprintf(str, (const S8 *)"Ping [ %s ] , please wait...", node.servname);
				YWLIB_Astr2wstr(wstr, str);
				hDlg = YWGeneralPopInfo_CreateWindow(hWnd, wstr, -1);
				YWGUI_UpdateWindow(hDlg);

				YWLIB_Memset(str, 0, sizeof(str));
				YWLIB_Sprintf(str, (const S8 *)"ping -c 4 -W %d -s %d %s >>./%s", g_timeout, g_packetsize,
										node.servname, PING_FINLE_NAME);
				system(str);

				YWGUI_SetTimer(hWnd, TIMER_READ_DATA, 200*1);
				YWGUI_KillTimer(hWnd, TIMER_PING_OPERAT);
				YWGeneralPopInfo_CloseWindow();
			}
		}
			break;

        case YWGUI_MSG_KEYDOWN:
    	{
            U16 scancode=YWGUI_LOWORD(wParam);

            switch(scancode)
            {
                case YWGUI_SCANCODE_EXIT:
					YWGUI_KillTimer(hWnd, TIMER_READ_DATA);
                    YWGUI_SendMessage(hWnd, YWGUI_MSG_CLOSE, 0, 0);
                    break;

                case YWGUI_SCANCODE_LEFT:
				{
            	}
					return 0;

                case YWGUI_SCANCODE_RIGHT:
				{
            	}
					return 0;

                case YWGUI_SCANCODE_UP:
					break;

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
		{
			char cmd[128];

			YWLIB_Memset(cmd, 0, sizeof(cmd));
			YWLIB_Sprintf(cmd, (const S8 *)"rm -f ./"PING_FINLE_NAME);
			system(cmd);

    	}
            break;

        case YWGUI_MSG_DESTROY:
            break;

        default:
            break;
    }

    return YWGUI_DefaultDialogProc(hWnd,message,wParam,lParam);
}

YWGUI_HWnd_T YWNetClientPingInfo_CreateWindow(YWGUI_HWnd_T hHost)
{
    YWGUI_HWnd_T hNetClientCfg = YWGUI_NULL_HANDLE;
    YW_ErrorType_T Error = YW_NO_ERROR;

	hNetClientCfg = YWGUI_GetMainWinById(IDD_NET_CLIENT_CONFIG_PING_INFO);
	if(hNetClientCfg != YWGUI_NULL_HANDLE)
	{
		YWGUI_SendMessage(hNetClientCfg, YWGUI_MSG_CLOSE, 0 ,0);
	}


    Error = YWGUI_CreateDialog(IDD_NET_CLIENT_CONFIG_PING_INFO, YWGUI_NULL_HANDLE, YWNetClientPingInfoi_WndProc, 0, &hNetClientCfg);

    return (YW_NO_ERROR == Error) ? hNetClientCfg : YWGUI_NULL_HANDLE;
}

static int YWNetClientPingi_GetPacketSizebyidx(int idx)
{
	int ipackesize;

	switch(idx)
	{
		case 0:
			ipackesize = 32;
			break;
		case 1:
			ipackesize = 64;
			break;
		case 2:
			ipackesize = 128;
			break;
		case 3:
			ipackesize = 256;
			break;
		case 4:
			ipackesize = 512;
			break;
		default:
			ipackesize = 64;
			break;
	}

	return (ipackesize-8);
}

static void YWNetClientPingi_IniLRC(YWGUI_HWnd_T hWnd)
{
	YWGUI_Char_T wstr[64];
	S32 ii = 0;
	YWGUI_HWnd_T hLRCB = YWGUI_NULL_HANDLE;
	YWGUI_LRCBListItem_T stLbItem;

    stLbItem.dwFlags = 0;
    stLbItem.dwAddData = 0;
    stLbItem.dwImage = 0;

/*	{
		char *pstr[] =
		{
			"Forever",
			"5 Times",
		};


		hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_PING_MODE);
        for(ii = 0; ii < 2; ii++)
        {
        	YWLIB_Astr2wstr(wstr, pstr[ii]);
            stLbItem.pszText = wstr;
            YWGUI_LRCBAddItem(hLRCB, &stLbItem);
        }
        YWGUI_LRCBSetListVisibleCount(hLRCB, 4);
        YWGUI_LRCBSetCurHotItemIndex(hLRCB, 0);
	}*/

	{
		char *pstr[] =
		{
			"1sec",
			"2sec",
			"3sec",
			"4sec",
			"5sec",
			"6sec",
			"7sec",
			"8sec",
			"9sec",
			"10sec",
		};


		hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_PING_TIMEOUT);
        for(ii = 0; ii < 10; ii++)
        {
        	YWLIB_Astr2wstr(wstr, pstr[ii]);
            stLbItem.pszText = wstr;
            YWGUI_LRCBAddItem(hLRCB, &stLbItem);
        }
        YWGUI_LRCBSetListVisibleCount(hLRCB, 4);
        YWGUI_LRCBSetCurHotItemIndex(hLRCB, 0);
	}

	{
		char *pstr[] =
		{
			"32 Bytes",
			"64 Bytes",
			"128 Bytes",
			"256 Bytes",
			"512 Bytes",
		};


		hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_PING_PACKET);
        for(ii = 0; ii < 5; ii++)
        {
        	YWLIB_Astr2wstr(wstr, pstr[ii]);
            stLbItem.pszText = wstr;
            YWGUI_LRCBAddItem(hLRCB, &stLbItem);
        }
        YWGUI_LRCBSetListVisibleCount(hLRCB, 4);
        YWGUI_LRCBSetCurHotItemIndex(hLRCB, 1);
	}

/*	{
		char *pstr[] =
		{
			"Server 1",
			"Server 2",
			"Server 3",
			"Server 4",
			"Server 5",
			"Server 6",
			"Server 7",
			"Server 8",
		};


		hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_PING_TARGET);
        for(ii = 0; ii < 8; ii++)
        {
        	YWLIB_Astr2wstr(wstr, pstr[ii]);
            stLbItem.pszText = wstr;
            YWGUI_LRCBAddItem(hLRCB, &stLbItem);
        }
        YWGUI_LRCBSetListVisibleCount(hLRCB, 4);
        YWGUI_LRCBSetCurHotItemIndex(hLRCB, 0);
	}*/


}


static void YWNetClientPingi_IniTxt(YWGUI_HWnd_T hWnd)
{
	YWGUI_Char_T wstr[64];

	YWLIB_Memset(wstr, 0x0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "Net Client Config Ping");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_PING_TITLE), wstr);

/*	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "Ping Mode");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_PING_MODE), wstr);
*/
	/*YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "Ping Timeout");*/
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_PING_TIMEOUT), YWSTR_GetString(STR_PING_TIMEOUT));

	/*YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "Ping Packet");*/
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_PING_PACKET), YWSTR_GetString(STR_PING_PACKET));
/*
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "Ping Target");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_PING_TARGET), wstr);
*/
	/*YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "Ping Run Ping");*/
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_PING_RUN), YWSTR_GetString(STR_PING_RUN_PING));

	/*YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "ok");*/
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_PING_RUN), YWSTR_GetString(STR_OK));


}
static S32 YWNetClientPingi_WndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
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
			YWNetClientPingi_IniTxt(hWnd);
			YWNetClientPingi_IniLRC(hWnd);
			g_serverindex = (int)lParam;
            break;

        case YWGUI_MSG_KEYDOWN:
    	{
            U16 scancode=YWGUI_LOWORD(wParam);

            switch(scancode)
            {
                case YWGUI_SCANCODE_EXIT:
                    YWGUI_SendMessage(hWnd, YWGUI_MSG_CLOSE, 0, 0);
                    return 0;

                case YWGUI_SCANCODE_LEFT:
                case YWGUI_SCANCODE_RIGHT:
                    break;

                case YWGUI_SCANCODE_UP:
                case YWGUI_SCANCODE_DOWN:
                    break;

                case YWGUI_SCANCODE_OK:
                    break;
                case YWGUI_SCANCODE_RED:
                    return 0;

                case YWGUI_SCANCODE_YELLOW:
                    break;
                default:
                    break;
            }
		}
            break;

        case YWGUI_MSG_COMMAND:
        {
            U16 id = YWGUI_LOWORD(wParam);
            U16 notifyCode= YWGUI_HIWORD(wParam);
			YWGUI_Char_T wstr[64];

			YWLIB_Memset(wstr, 0, sizeof(wstr));

            if (YWGUI_NONE_CODE == notifyCode)
            {
				switch(id)
				{
					case IDC_BTN_NET_CFG_PING_RUN:
					{
						YWGUI_Handle_T hLRC = YWGUI_NULL_HANDLE;
						int idx;

						g_timeout = 0;
						g_packetsize = 0;


						hLRC = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_PING_TIMEOUT);
						idx = YWGUI_LRCBGetCurHotItemIndex(hLRC);
						g_timeout = idx+1;

						hLRC = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_PING_PACKET);
						idx = YWGUI_LRCBGetCurHotItemIndex(hLRC);
						g_packetsize= YWNetClientPingi_GetPacketSizebyidx(idx);

						YWNetClientPingInfo_CreateWindow(hWnd);
					}
						break;
				}
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




YWGUI_HWnd_T YWNetClientPing_CreateWindow(YWGUI_HWnd_T hHost, int idx)
{
    YWGUI_HWnd_T hNetClientPing=YWGUI_NULL_HANDLE;
    YW_ErrorType_T Error = YW_NO_ERROR;

    Error = YWGUI_CreateDialog(IDD_NET_CLIENT_CONFIG_PING, hHost, YWNetClientPingi_WndProc, (LPARAM)idx, &hNetClientPing);

    return (YW_NO_ERROR == Error) ? hNetClientPing : YWGUI_NULL_HANDLE;
}



