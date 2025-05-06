
#include <stdio.h>
#include <stdlib.h>
#include "ywgui_ext.h"
#include "res_layout.h"
#include "camcfg_layout.h"
#include "cfgfile_parse.h"
#include "gui.h"
#include "general.h"
#include "camcfg.h"
#include "cfgfile_parse.h"

static Cfg_Type_T g_Cfg_Type = CFG_TYPE_OSCAM;


static BOOL YWNetClientEditi_NewCamdNodeIsMULTIPLE(char *key)
{
	BOOL ret = FALSE;

	if(strcmp(key, "CWS_MULTIPLE") == 0)
	{
		ret = TRUE;
	}
	return ret;
		
}

void YWNetClientEdit_SetCfgType(Cfg_Type_T Type)
{
	g_Cfg_Type = Type;
}


static void YWNetClientEditi_InsertSpaceToDesKey(char *pDeskey)
{
	char astrtmp[256];
	char *p = NULL;
	char *pkeytmp = pDeskey;

	YWLIB_Memset(astrtmp, 0, sizeof(astrtmp));
	p = astrtmp;
	while(*pDeskey != '\0')
	{
		*p++ = *pDeskey++;
		*p++ = *pDeskey++;
		*p = ' ';
		p++;
	}
	YWLIB_Strcpy(pkeytmp, astrtmp);
}

static void YWNetClientEditi_DeleteSpaceFromDesKey(char *pDeskey)
{
	while(*pDeskey != '\0')
	{
		if(*pDeskey == ' ')
			YWLIB_Strcpy(pDeskey, pDeskey+1);
		pDeskey++;
	}
}
/*
static void YWNetClientEditi_SetServerNameTxt(YWGUI_HWnd_T hWnd, char *pstr)
{
	YWGUI_Char_T wstr[4];
	char str[4];
	char *p = NULL;
	char *pend = NULL;
	int i;

	YWGUI_HWnd_T hCT = YWGUI_NULL_HANDLE;
	YWGUI_HWnd_T hCtrl = YWGUI_NULL_HANDLE;

	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_NET_CFG_EDIT_SERV_NAME);
	p = pstr;
	for(i=0; i<4; i++)
	{
		YWLIB_Memset(wstr, 0, sizeof(wstr));
		YWLIB_Memset(str, 0, sizeof(str));

		if(YWLIB_Strlen(pstr) > 0)
		{
			if(i<3)
			{
				pend = (char*)YWLIB_Strchr(p, '.');
				if(pend != NULL)
				{
					YWLIB_Strncpy(str, p, pend-p);
				}
				else
				{

				}
			}
			else
			{
				YWLIB_Strcpy(str, p);
			}
		}

		YWLIB_Astr2wstr(wstr, str);
		hCtrl = YWGUI_CTGetCtrlHandleById(hCT, IDC_EDIT_NET_CFG_EDIT_SERV_NAME1+i);
		YWGUI_SetWindowText(hCtrl, wstr);

		p = pend+1;
	}
}

static void YWNetClientEditi_GetServerNameTxt(YWGUI_HWnd_T hWnd, char *pstr)
{
	YWGUI_Char_T awstr[4];
	char astr[4];
	char str[16];
	int i;
	int ipdata;

	YWGUI_HWnd_T hCT = YWGUI_NULL_HANDLE;
	YWGUI_HWnd_T hCtrl = YWGUI_NULL_HANDLE;

	YWLIB_Memset(awstr, 0, sizeof(awstr));
	YWLIB_Memset(astr, 0, sizeof(astr));
	YWLIB_Memset(str, 0, sizeof(str));

	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_NET_CFG_EDIT_SERV_NAME);

	for(i=0; i<4; i++)
	{
		YWLIB_Memset(awstr, 0, sizeof(awstr));
		YWLIB_Memset(astr, 0, sizeof(astr));

		hCtrl = YWGUI_CTGetCtrlHandleById(hCT, IDC_EDIT_NET_CFG_EDIT_SERV_NAME1+i);
		YWGUI_GetWindowText(hCtrl, awstr, sizeof(awstr));
		ipdata = YWLIB_Watoi(awstr);
		YWLIB_Sprintf(astr, (const S8 *)"%d", ipdata);
		//YWLIB_Wstr2AscStr(astr, awstr);
		YWLIB_Strcat(str, astr);
		if(i < 3)
		{
			YWLIB_Strcat(str, ".");
		}
	}

	YWLIB_Strcpy(pstr, str);
}
*/
static void YWNetClientEditi_EditDesKey(YWGUI_HWnd_T hWnd, U16 scancode, S32 iFocusPos)
{
	YWGUI_Char_T Wchar = 0;
	YWGUI_Char_T wstr[64];

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWGUI_GetWindowText(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), wstr, sizeof(wstr));
	Wchar = wstr[iFocusPos];
	switch(scancode)
	{
		case YWGUI_SCANCODE_PGDN:
			Wchar = 'b';
			break;
		case YWGUI_SCANCODE_PGUP:
			Wchar = 'a';
			break;
		case YWGUI_SCANCODE_RED:
			Wchar = 'c';
			break;
		case YWGUI_SCANCODE_GREEN:
			Wchar = 'd';
			break;
		case YWGUI_SCANCODE_YELLOW:
			Wchar = 'e';
			break;
		case YWGUI_SCANCODE_BLUE:
			Wchar = 'f';
			break;
		default:
			break;
	}
	wstr[iFocusPos] = Wchar;

	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), wstr);
	if(iFocusPos%3 == 0)
	{
		YWGUI_SEditSetCursorPos(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), iFocusPos+1);
	}
	else
	{
		YWGUI_SEditSetCursorPos(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), iFocusPos);
	}
}



//except idx ctrl
static void YWNetClientEditi_DisableAllCtrl(YWGUI_HWnd_T hWnd)
{
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX), FALSE);
	//YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_CTN_NET_CFG_EDIT_SERV_NAME), FALSE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_SERV_NAME), FALSE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT), FALSE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME), FALSE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD), FALSE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), FALSE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_PROTOCOL), FALSE);

	YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_NO_CONFIG_INFO), -1);
}

static void YWNetClientEditi_UpdateFunctionKeyNormalText(YWGUI_HWnd_T hWnd)
{
/*	YWGUI_Char_T wstr[128];

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "Add");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_ADD), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "Delete");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_DELETE), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "Ping");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_PING), wstr);
*/

	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_PIC_NET_CFG_EDIT_BLUE), YWGUI_SW_HIDE);
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_F), YWGUI_SW_HIDE);


	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_AB), YWGUI_SW_HIDE);
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_HELP), YWGUI_SW_HIDE);
}

static void YWNetClientEditi_UpdateFunctionKeyDESText(YWGUI_HWnd_T hWnd)
{
	YWGUI_Char_T wstr[128];

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "C");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_ADD), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "D");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_DELETE), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "E");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_PING), wstr);

	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_PIC_NET_CFG_EDIT_BLUE), YWGUI_SW_SHOW);
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_F), YWGUI_SW_SHOW);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "F");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_F), wstr);

	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_AB), YWGUI_SW_SHOW);
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "PAGE+/- : A/B");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_AB), wstr);

	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_HELP), YWGUI_SW_SHOW);
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "Up+Down:Change Left+Right:Move");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_HELP), wstr);

}

/*
static void YWNetClientEditi_IniTxt(YWGUI_HWnd_T hWnd)
{
	YWGUI_Char_T wstr[64];

	YWLIB_Memset(wstr, 0x0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "Net Client Config Edit");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_TITLE), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "Index");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_INDEX), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "Server Name");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_SERV_NAME), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "Service Port");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_SERVICE_PORT), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "User Name");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_USER_NAME), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "Password");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_PASSWORD), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "DES Key");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_DES_KEY), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr, "Protocol");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_PROTOCOL), wstr);

}*/



static void	YWNetClientEditi_OscamSaveCurIndxData(YWGUI_HWnd_T hWnd, int indx)
{
	CFGInfo_T node;
	char str[128];
	YWGUI_Char_T wstr[128];
	YWGUI_Handle_T hCtrl = YWGUI_NULL_HANDLE;
	int iProtocolIdx = 0;

	YWLIB_Memset(&node, 0, sizeof(CFGInfo_T));
	CFGDataList_GetNode(indx, &node);

	//YWNetClientEditi_GetServerNameTxt(hWnd, node.servname);
	YWLIB_Memset(str, 0, sizeof(str));
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_SERV_NAME);
	YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
    //YWPUBLIC_Utf16To8((S8*)wstr, sizeof(wstr), str,sizeof(str));
	YWLIB_Wstr2AscStr(str, wstr);
	YWLIB_Strcpy(node.servname, str);

	YWLIB_Memset(str, 0, sizeof(str));
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT);
	YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
	YWLIB_Wstr2AscStr(str, wstr);
	YWLIB_Strcpy(node.serviceport, str);

	YWLIB_Memset(str, 0, sizeof(str));
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME);
	YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
	YWLIB_Wstr2AscStr(str, wstr);
	YWLIB_Strcpy(node.username, str);

	YWLIB_Memset(str, 0, sizeof(str));
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD);
	YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
	YWLIB_Wstr2AscStr(str, wstr);
	YWLIB_Strcpy(node.password, str);

	YWLIB_Memset(str, 0, sizeof(str));
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_PROTOCOL);
	iProtocolIdx = YWGUI_LRCBGetCurHotItemIndex(hCtrl);
	YWGUI_LRCBGetListItemText(hCtrl, iProtocolIdx, wstr);
	YWLIB_Wstr2AscStr(str, wstr);
	YWLIB_Strcpy(node.protocol, str);


	if(iProtocolIdx == 1)
	{
		YWLIB_Memset(str, 0, sizeof(str));
		YWLIB_Memset(wstr, 0, sizeof(wstr));
		hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY);
		YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
		YWLIB_Wstr2AscStr(str, wstr);
		YWNetClientEditi_DeleteSpaceFromDesKey(str);   	//need delete space
		YWLIB_Strcpy(node.deskey, str);
	}
	else
	{
		YWLIB_Memset(str, 0, sizeof(str));
		YWLIB_Strcpy(node.deskey, str);
	}

	CFGDataList_UpdateNode(&node, indx);

}

static void	YWNetClientEditi_MgCccamdSaveCurIndxData(YWGUI_HWnd_T hWnd, int indx)
{
	CFGInfo_T node;
	char str[128];
	YWGUI_Char_T wstr[128];
	YWGUI_Handle_T hCtrl = YWGUI_NULL_HANDLE;

	YWLIB_Memset(&node, 0, sizeof(CFGInfo_T));
	CFGDataList_GetNode(indx, &node);

	//YWNetClientEditi_GetServerNameTxt(hWnd, node.servname);
	YWLIB_Memset(str, 0, sizeof(str));
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_SERV_NAME);
	YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
	YWLIB_Wstr2AscStr(str, wstr);
	YWLIB_Strcpy(node.servname, str);

	YWLIB_Memset(str, 0, sizeof(str));
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT);
	YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
	YWLIB_Wstr2AscStr(str, wstr);
	YWLIB_Strcpy(node.serviceport, str);

	YWLIB_Memset(str, 0, sizeof(str));
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME);
	YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
	YWLIB_Wstr2AscStr(str, wstr);
	YWLIB_Strcpy(node.username, str);

	YWLIB_Memset(str, 0, sizeof(str));
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD);
	YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
	YWLIB_Wstr2AscStr(str, wstr);
	YWLIB_Strcpy(node.password, str);

	CFGDataList_UpdateNode(&node, indx);


}

static void	YWNetClientEditi_MgNewcamdSaveCurIndxData(YWGUI_HWnd_T hWnd, int indx)
{
	CFGInfo_T node;
	char str[128];
	YWGUI_Char_T wstr[128];
	YWGUI_Handle_T hCtrl = YWGUI_NULL_HANDLE;

	YWLIB_Memset(&node, 0, sizeof(CFGInfo_T));
	CFGDataList_GetNode(indx, &node);


	//YWNetClientEditi_GetServerNameTxt(hWnd, node.servname);
	YWLIB_Memset(str, 0, sizeof(str));
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_SERV_NAME);
	YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
	YWLIB_Wstr2AscStr(str, wstr);
	YWLIB_Strcpy(node.servname, str);


	YWLIB_Memset(str, 0, sizeof(str));
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT);
	YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
	YWLIB_Wstr2AscStr(str, wstr);
	YWLIB_Strcpy(node.serviceport, str);

	if(YWNetClientEditi_NewCamdNodeIsMULTIPLE(node.key))
	{
		YWLIB_Memset(str, 0, sizeof(str));
		YWLIB_Memset(wstr, 0, sizeof(wstr));
		hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT_END);
		YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
		YWLIB_Wstr2AscStr(str, wstr);
		YWLIB_Strcpy(node.serviceport_end, str);
		printf("sav a  node: %d serviceport_end:%s\n",indx, node.serviceport_end);
	}


	YWLIB_Memset(str, 0, sizeof(str));
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME);
	YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
	YWLIB_Wstr2AscStr(str, wstr);
	YWLIB_Strcpy(node.username, str);

	YWLIB_Memset(str, 0, sizeof(str));
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD);
	YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
	YWLIB_Wstr2AscStr(str, wstr);
	YWLIB_Strcpy(node.password, str);


	YWLIB_Memset(str, 0, sizeof(str));
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY);
	YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
	YWLIB_Wstr2AscStr(str, wstr);
	YWLIB_Strcpy(node.deskey, str);

	//printf("update oscam.server label: %s !\n", node.label);
	CFGDataList_UpdateNode(&node, indx);


}
static void	YWNetClientEditi_CccamCfgSaveCurIndxData(YWGUI_HWnd_T hWnd, int indx)
{
	CFGInfo_T node;
	char str[128];
	YWGUI_Char_T wstr[128];
	YWGUI_Handle_T hCtrl = YWGUI_NULL_HANDLE;
	int iProtocolIdx;

	YWLIB_Memset(&node, 0, sizeof(CFGInfo_T));
	CFGDataList_GetNode(indx, &node);

	//YWNetClientEditi_GetServerNameTxt(hWnd, node.servname);
	YWLIB_Memset(str, 0, sizeof(str));
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_SERV_NAME);
	YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
	YWLIB_Wstr2AscStr(str, wstr);
	YWLIB_Strcpy(node.servname, str);


	YWLIB_Memset(str, 0, sizeof(str));
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT);
	YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
	YWLIB_Wstr2AscStr(str, wstr);
	YWLIB_Strcpy(node.serviceport, str);

	YWLIB_Memset(str, 0, sizeof(str));
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME);
	YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
	YWLIB_Wstr2AscStr(str, wstr);
	YWLIB_Strcpy(node.username, str);

	YWLIB_Memset(str, 0, sizeof(str));
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD);
	YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));
	YWLIB_Wstr2AscStr(str, wstr);
	YWLIB_Strcpy(node.password, str);


	//save protocol
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_PROTOCOL);
	iProtocolIdx = YWGUI_LRCBGetCurHotItemIndex(hCtrl);
	if(iProtocolIdx == 1)
	{
		YWLIB_Strcpy(node.key, "N");
	}
	else
	{
		YWLIB_Strcpy(node.key, "C");
	}

	//deskey
	if(YWLIB_Strcmp(node.key, "N") == 0)
	{
		YWLIB_Memset(str, 0, sizeof(str));
		YWLIB_Memset(wstr, 0, sizeof(wstr));

		hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY);
		YWGUI_GetWindowText(hCtrl, wstr, sizeof(wstr));

		YWLIB_Wstr2AscStr(str, wstr);
		YWLIB_Strcpy(node.deskey, str);

	}
	else
	{
		YWLIB_Memset(str, 0, sizeof(str));
		YWLIB_Strcpy(node.deskey, str);
	}

	CFGDataList_UpdateNode(&node, indx);
}

static void YWNetClientEditi_SaveCurIndxData(YWGUI_HWnd_T hWnd, Cfg_Type_T type)
{
	YWGUI_HWnd_T hLRCB = YWGUI_NULL_HANDLE;
	int indx;

	hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX);
	indx = YWGUI_LRCBGetCurHotItemIndex(hLRCB);

	if(type == CFG_TYPE_OSCAM)
	{
		YWNetClientEditi_OscamSaveCurIndxData(hWnd, indx);
	}
	else if(type == CFG_TYPE_MG_CCCAMD)
	{
		YWNetClientEditi_MgCccamdSaveCurIndxData(hWnd, indx);
	}
	else if(type == CFG_TYPE_MG_NEWCAMD)
	{
		YWNetClientEditi_MgNewcamdSaveCurIndxData(hWnd, indx);
	}
	else if(type == CFG_TYPE_CCCAMCFG)
	{
		YWNetClientEditi_CccamCfgSaveCurIndxData(hWnd, indx);
	}
}





static int YWNetClientEditi_OscamRefreshCtrl(YWGUI_HWnd_T hWnd, int indx)
{
	YWGUI_Char_T wstr[128];
	char astr[128];
	S32 ii = 0;
	S32 jj = 0;
	int servNum = 0;

	YWGUI_HWnd_T hLRCB = YWGUI_NULL_HANDLE;
	YWGUI_HWnd_T hCtrl = YWGUI_NULL_HANDLE;
	CFGInfo_T node;
	char *pstr[] =
	{
		PROTOCOL_CC,
		PROTOCOL_NEW,
	};


	//index
	servNum = CFGDataList_GetNumber();
	if(servNum == 0)
	{
		YWNetClientEditi_DisableAllCtrl(hWnd);
		return -1;
	}
	hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX);
    YWGUI_LRCBSetCurHotItemIndex(hLRCB, indx);
	YWLIB_Memset(&node, 0, sizeof(CFGInfo_T));
	CFGDataList_GetNode(indx, &node);

	//server name
	//YWNetClientEditi_SetServerNameTxt(hWnd, node.servname);
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_SERV_NAME);
	YWLIB_Astr2wstr(wstr, node.servname);
	YWGUI_SetWindowText(hCtrl, wstr);

	//serviceport
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT);
	YWLIB_Astr2wstr(wstr, node.serviceport);
	YWGUI_SetWindowText(hCtrl, wstr);

	//username
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME);
	YWLIB_Astr2wstr(wstr, node.username);
	YWGUI_SetWindowText(hCtrl, wstr);

	//password
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD);
	YWLIB_Astr2wstr(wstr, node.password);
	YWGUI_SetWindowText(hCtrl, wstr);




	//deskey and protocol
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY);
	hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_PROTOCOL);
	if(YWLIB_Strcmp(node.protocol, PROTOCOL_NEW) == 0)
	{
		YWLIB_Memset(astr, 0, sizeof(astr));
		YWLIB_Memcpy(astr, node.deskey, sizeof(astr));
		YWNetClientEditi_InsertSpaceToDesKey(astr);     	//need insert space
		YWLIB_Astr2wstr(wstr, astr);
		YWGUI_SetWindowText(hCtrl, wstr);

	    YWGUI_LRCBSetCurHotItemIndex(hLRCB, 1);
	}
	else
	{
		YWLIB_Memset(wstr, 0, sizeof(wstr));
		YWGUI_SetWindowText(hCtrl, wstr);
	    YWGUI_LRCBSetCurHotItemIndex(hLRCB, 0);
	}

}

static int YWNetClientEditi_CccamdRefreshCtrl(YWGUI_HWnd_T hWnd, int indx)
{
	YWGUI_Char_T wstr[128];
	char astr[128];
	int servNum = 0;

	YWGUI_HWnd_T hLRCB = YWGUI_NULL_HANDLE;
	YWGUI_HWnd_T hCtrl = YWGUI_NULL_HANDLE;
	CFGInfo_T node;

	servNum = CFGDataList_GetNumber();
	if(servNum == 0)
	{
		YWNetClientEditi_DisableAllCtrl(hWnd);
		return -1;
	}
	hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX);
    YWGUI_LRCBSetCurHotItemIndex(hLRCB, indx);
	YWLIB_Memset(&node, 0, sizeof(CFGInfo_T));
	CFGDataList_GetNode(indx, &node);

	//YWNetClientEditi_SetServerNameTxt(hWnd, node.servname);
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_SERV_NAME);
	YWLIB_Astr2wstr(wstr, node.servname);
	YWGUI_SetWindowText(hCtrl, wstr);

	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT);
	YWLIB_Astr2wstr(wstr, node.serviceport);
	YWGUI_SetWindowText(hCtrl, wstr);

	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME);
	YWLIB_Astr2wstr(wstr, node.username);
	YWGUI_SetWindowText(hCtrl, wstr);

	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD);
	YWLIB_Astr2wstr(wstr, node.password);
	YWGUI_SetWindowText(hCtrl, wstr);
}

static int YWNetClientEditi_NewcamdRefreshCtrl(YWGUI_HWnd_T hWnd, int indx)
{
	YWGUI_Char_T wstr[128];
	char astr[128];
	int servNum = 0;

	YWGUI_HWnd_T hLRCB = YWGUI_NULL_HANDLE;
	YWGUI_HWnd_T hCtrl = YWGUI_NULL_HANDLE;
	CFGInfo_T node;

	servNum = CFGDataList_GetNumber();
	if(servNum == 0)
	{
		YWNetClientEditi_DisableAllCtrl(hWnd);
		return -1;
	}
	hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX);
    YWGUI_LRCBSetCurHotItemIndex(hLRCB, indx);
	YWLIB_Memset(&node, 0, sizeof(CFGInfo_T));
	CFGDataList_GetNode(indx, &node);

	//YWNetClientEditi_SetServerNameTxt(hWnd, node.servname);
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_SERV_NAME);
	YWLIB_Astr2wstr(wstr, node.servname);
	YWGUI_SetWindowText(hCtrl, wstr);

	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT);
	YWLIB_Astr2wstr(wstr, node.serviceport);
	YWGUI_SetWindowText(hCtrl, wstr);

	if(YWNetClientEditi_NewCamdNodeIsMULTIPLE(node.key))
	{
		hCtrl = YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_SERVICE_PORT);
		YWLIB_Astr2wstr(wstr, "Service Port Start");
		YWGUI_SetWindowText(hCtrl, wstr);

		hCtrl = YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_SERVICE_PORT_END);
		YWLIB_Astr2wstr(wstr, "Service Port End");
		YWGUI_SetWindowText(hCtrl, wstr);
	
		hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT_END);
		YWLIB_Astr2wstr(wstr, node.serviceport_end);
		YWGUI_SetWindowText(hCtrl, wstr);
	}
	else
	{
		hCtrl = YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_SERVICE_PORT);
		YWLIB_Astr2wstr(wstr, "Service Port");
		YWGUI_SetWindowText(hCtrl, wstr);
	}

	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME);
	YWLIB_Astr2wstr(wstr, node.username);
	YWGUI_SetWindowText(hCtrl, wstr);

	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD);
	YWLIB_Astr2wstr(wstr, node.password);
	YWGUI_SetWindowText(hCtrl, wstr);

	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY);
	YWLIB_Astr2wstr(wstr, node.deskey);
	YWGUI_SetWindowText(hCtrl, wstr);

}

static int YWNetClientEditi_CccamCfgRefreshCtrl(YWGUI_HWnd_T hWnd, int indx)
{
	YWGUI_Char_T wstr[128];
	char astr[128];
	int servNum = 0;

	YWGUI_HWnd_T hLRCB = YWGUI_NULL_HANDLE;
	YWGUI_HWnd_T hCtrl = YWGUI_NULL_HANDLE;
	CFGInfo_T node;

	servNum = CFGDataList_GetNumber();
	if(servNum == 0)
	{
		YWNetClientEditi_DisableAllCtrl(hWnd);
		return -1;
	}
	hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX);
    YWGUI_LRCBSetCurHotItemIndex(hLRCB, indx);
	YWLIB_Memset(&node, 0, sizeof(CFGInfo_T));
	CFGDataList_GetNode(indx, &node);

	//YWNetClientEditi_SetServerNameTxt(hWnd, node.servname);
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_SERV_NAME);
	YWLIB_Astr2wstr(wstr, node.servname);
	YWGUI_SetWindowText(hCtrl, wstr);


	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT);
	YWLIB_Astr2wstr(wstr, node.serviceport);
	YWGUI_SetWindowText(hCtrl, wstr);

	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME);
	YWLIB_Astr2wstr(wstr, node.username);
	YWGUI_SetWindowText(hCtrl, wstr);

	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD);
	YWLIB_Astr2wstr(wstr, node.password);
	YWGUI_SetWindowText(hCtrl, wstr);

	//deskey and protocol
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY);
	YWLIB_Astr2wstr(wstr, node.deskey);
	hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_PROTOCOL);
	if(YWLIB_Strcmp(node.key, "N") == 0)
	{
		YWGUI_SetWindowText(hCtrl, wstr);
	    YWGUI_LRCBSetCurHotItemIndex(hLRCB, 1);
	}
	else
	{
		YWLIB_Memset(wstr, 0, sizeof(wstr));
		YWGUI_SetWindowText(hCtrl, wstr);
	    YWGUI_LRCBSetCurHotItemIndex(hLRCB, 0);
	}

}

static void YWNetClientEditi_RefreshCtrl(YWGUI_HWnd_T hWnd, Cfg_Type_T type, int indx)
{
	if(type == CFG_TYPE_OSCAM)
	{
		YWNetClientEditi_OscamRefreshCtrl(hWnd, indx);
	}
	else if(type == CFG_TYPE_MG_CCCAMD)
	{
		YWNetClientEditi_CccamdRefreshCtrl(hWnd, indx);
	}
	else if(type == CFG_TYPE_MG_NEWCAMD)
	{
		YWNetClientEditi_NewcamdRefreshCtrl(hWnd, indx);
	}
	else if(type == CFG_TYPE_CCCAMCFG)
	{
		YWNetClientEditi_CccamCfgRefreshCtrl(hWnd, indx);
	}

}






static int YWNetClientEditi_OscamInitCtrl(YWGUI_HWnd_T hWnd, int indx)
{
	YWGUI_Char_T wstr[128];
	char astr[128];
	S32 ii = 0;
	int jj = 0;
	int servNum = 0;
	int idxnum = 0;
	char *pstr[] =
	{
		PROTOCOL_CC,
		PROTOCOL_NEW,
	};

	YWGUI_HWnd_T hLRCB = YWGUI_NULL_HANDLE;
	YWGUI_HWnd_T hCtrl = YWGUI_NULL_HANDLE;
	YWGUI_LRCBListItem_T stLbItem;
	CFGInfo_T node;

	//index
    stLbItem.dwFlags = 0;
    stLbItem.dwAddData = 0;
    stLbItem.dwImage = 0;
	hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX);
	servNum = CFGDataList_GetNumber();
	if(servNum > 0)
	{
	    for(ii = 0; ii < servNum; ii++)
		{
			YWLIB_SwprintfA(wstr, (const S8*)"%d", ii);
	        stLbItem.pszText = wstr;
	        YWGUI_LRCBAddItem(hLRCB, &stLbItem);
		}
	}
	else
	{
		YWNetClientEditi_DisableAllCtrl(hWnd);
		return -1;
	}
    YWGUI_LRCBSetListVisibleCount(hLRCB, 4);
    YWGUI_LRCBSetCurHotItemIndex(hLRCB, indx);
	YWLIB_Memset(&node, 0, sizeof(CFGInfo_T));
	CFGDataList_GetNode(indx, &node);
	printf("open section:%s, label:%s, protocol:%s, servername:%s,serviceport:%s, usrname:%s, pswd:%s, deskey:%s\n",
		node.section, node.label, node.protocol, node.servname, node.serviceport,node.username, node.password, node.deskey);

	//server name
	//YWNetClientEditi_SetServerNameTxt(hWnd, node.servname);
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_SERV_NAME);
	YWLIB_Astr2wstr(wstr, node.servname);
	YWGUI_SetWindowText(hCtrl, wstr);

	//serviceport
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT);
	YWLIB_Astr2wstr(wstr, node.serviceport);
	YWGUI_SetWindowText(hCtrl, wstr);

	//username
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME);
	YWLIB_Astr2wstr(wstr, node.username);
	YWGUI_SetWindowText(hCtrl, wstr);

	//password
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD);
	YWLIB_Astr2wstr(wstr, node.password);
	YWGUI_SetWindowText(hCtrl, wstr);

	//desk

	if(YWLIB_Strcmp(node.protocol, PROTOCOL_NEW) == 0)
	{
		hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY);
		YWLIB_Memset(astr, 0, sizeof(astr));
		YWLIB_Memcpy(astr, node.deskey, sizeof(astr));
		YWNetClientEditi_InsertSpaceToDesKey(astr);     	//need insert space
		YWLIB_Astr2wstr(wstr, astr);
		YWGUI_SetWindowText(hCtrl, wstr);

		//protocol
		hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_PROTOCOL);
	    for(ii = 0; ii < YWGUI_ARRAY_SIZE(pstr); ii++)
	    {
	    	YWLIB_Astr2wstr(wstr, pstr[ii]);
	        stLbItem.pszText = wstr;
	        YWGUI_LRCBAddItem(hLRCB, &stLbItem);
	    }
	    YWGUI_LRCBSetListVisibleCount(hLRCB, 4);
	    YWGUI_LRCBSetCurHotItemIndex(hLRCB, 1);
	}
	else
	{
		hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY);
		YWLIB_Memset(wstr, 0, sizeof(wstr));
		YWGUI_SetWindowText(hCtrl, wstr);

		//protocol
		hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_PROTOCOL);
	    for(ii = 0; ii < YWGUI_ARRAY_SIZE(pstr); ii++)
	    {
	    	YWLIB_Astr2wstr(wstr, pstr[ii]);
	        stLbItem.pszText = wstr;
	        YWGUI_LRCBAddItem(hLRCB, &stLbItem);
	    }
	    YWGUI_LRCBSetListVisibleCount(hLRCB, 4);
	    YWGUI_LRCBSetCurHotItemIndex(hLRCB, 0);
	}
}

static int YWNetClientEditi_CccamdInitCtrl(YWGUI_HWnd_T hWnd, int indx)
{
	YWGUI_Char_T wstr[128];
	char astr[128];
	S32 ii = 0;
	int jj = 0;
	int servNum = 0;
	int idxnum = 0;

	YWGUI_HWnd_T hLRCB = YWGUI_NULL_HANDLE;
	YWGUI_HWnd_T hCtrl = YWGUI_NULL_HANDLE;
	YWGUI_LRCBListItem_T stLbItem;
	CFGInfo_T node;
	char *pstr[] =
	{
		PROTOCOL_CC,
		PROTOCOL_NEW,
	};


    stLbItem.dwFlags = 0;
    stLbItem.dwAddData = 0;
    stLbItem.dwImage = 0;
	hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX);
	servNum = CFGDataList_GetNumber();
	if(servNum > 0)
	{
	    for(ii = 0; ii < servNum; ii++)
		{
			YWLIB_SwprintfA(wstr, (const S8*)"%d", ii);
	        stLbItem.pszText = wstr;
	        YWGUI_LRCBAddItem(hLRCB, &stLbItem);
		}
	}
	else
	{
		YWNetClientEditi_DisableAllCtrl(hWnd);
		return -1;
	}
    YWGUI_LRCBSetListVisibleCount(hLRCB, 4);
    YWGUI_LRCBSetCurHotItemIndex(hLRCB, indx);

	YWLIB_Memset(&node, 0, sizeof(CFGInfo_T));
	CFGDataList_GetNode(indx, &node);

	//YWNetClientEditi_SetServerNameTxt(hWnd, node.servname);
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_SERV_NAME);
	YWLIB_Astr2wstr(wstr, node.servname);
	YWGUI_SetWindowText(hCtrl, wstr);

	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT);
	YWLIB_Astr2wstr(wstr, node.serviceport);
	YWGUI_SetWindowText(hCtrl, wstr);

	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME);
	YWLIB_Astr2wstr(wstr, node.username);
	YWGUI_SetWindowText(hCtrl, wstr);

	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD);
	YWLIB_Astr2wstr(wstr, node.password);
	YWGUI_SetWindowText(hCtrl, wstr);

	//protocol
	hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_PROTOCOL);
    for(ii = 0; ii < YWGUI_ARRAY_SIZE(pstr); ii++)
    {
    	YWLIB_Astr2wstr(wstr, pstr[ii]);
        stLbItem.pszText = wstr;
        YWGUI_LRCBAddItem(hLRCB, &stLbItem);
    }
    YWGUI_LRCBSetListVisibleCount(hLRCB, 4);
    YWGUI_LRCBSetCurHotItemIndex(hLRCB, 0);

}

static int YWNetClientEditi_NewcamdInitCtrl(YWGUI_HWnd_T hWnd, int indx)
{
	YWGUI_Char_T wstr[128];
	char astr[128];
	S32 ii = 0;
	int jj = 0;
	int servNum = 0;
	int idxnum = 0;

	YWGUI_HWnd_T hLRCB = YWGUI_NULL_HANDLE;
	YWGUI_HWnd_T hCtrl = YWGUI_NULL_HANDLE;
	YWGUI_LRCBListItem_T stLbItem;
	CFGInfo_T node;
	char *pstr[] =
	{
		PROTOCOL_CC,
		PROTOCOL_NEW,
	};


    stLbItem.dwFlags = 0;
    stLbItem.dwAddData = 0;
    stLbItem.dwImage = 0;
	hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX);
	servNum = CFGDataList_GetNumber();
	if(servNum > 0)
	{
	    for(ii = 0; ii < servNum; ii++)
		{
			YWLIB_SwprintfA(wstr, (const S8*)"%d", ii);
	        stLbItem.pszText = wstr;
	        YWGUI_LRCBAddItem(hLRCB, &stLbItem);
		}
	}
	else
	{
		YWNetClientEditi_DisableAllCtrl(hWnd);
		return -1;
	}
    YWGUI_LRCBSetListVisibleCount(hLRCB, 4);
    YWGUI_LRCBSetCurHotItemIndex(hLRCB, indx);

	YWLIB_Memset(&node, 0, sizeof(CFGInfo_T));
	CFGDataList_GetNode(indx, &node);

	//YWNetClientEditi_SetServerNameTxt(hWnd, node.servname);
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_SERV_NAME);
	YWLIB_Astr2wstr(wstr, node.servname);
	YWGUI_SetWindowText(hCtrl, wstr);


	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT);
	YWLIB_Astr2wstr(wstr, node.serviceport);
	YWGUI_SetWindowText(hCtrl, wstr);

	if(YWNetClientEditi_NewCamdNodeIsMULTIPLE(node.key))
	{
		hCtrl = YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_SERVICE_PORT);
		YWLIB_Astr2wstr(wstr, "Service Port Start");
		YWGUI_SetWindowText(hCtrl, wstr);

		hCtrl = YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_SERVICE_PORT_END);
		YWLIB_Astr2wstr(wstr, "Service Port End");
		YWGUI_SetWindowText(hCtrl, wstr);

	
		hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT_END);
		YWLIB_Astr2wstr(wstr, node.serviceport_end);
		YWGUI_SetWindowText(hCtrl, wstr);
	}
	else
	{
		hCtrl = YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_SERVICE_PORT);
		YWLIB_Astr2wstr(wstr, "Service Port");
		YWGUI_SetWindowText(hCtrl, wstr);
	}

	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME);
	YWLIB_Astr2wstr(wstr, node.username);
	YWGUI_SetWindowText(hCtrl, wstr);

	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD);
	YWLIB_Astr2wstr(wstr, node.password);
	YWGUI_SetWindowText(hCtrl, wstr);

	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY);
	YWLIB_Astr2wstr(wstr, node.deskey);
	YWGUI_SetWindowText(hCtrl, wstr);

	//protocol
	hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_PROTOCOL);
    for(ii = 0; ii < YWGUI_ARRAY_SIZE(pstr); ii++)
    {
    	YWLIB_Astr2wstr(wstr, pstr[ii]);
        stLbItem.pszText = wstr;
        YWGUI_LRCBAddItem(hLRCB, &stLbItem);
    }
    YWGUI_LRCBSetListVisibleCount(hLRCB, 4);
    YWGUI_LRCBSetCurHotItemIndex(hLRCB, 1);

}

static int YWNetClientEditi_CccamCfgInitCtrl(YWGUI_HWnd_T hWnd, int indx)
{
	YWGUI_Char_T wstr[128];
	char astr[128];
	S32 ii = 0;
	int jj = 0;
	int servNum = 0;
	int idxnum = 0;
	char *pstr[] =
	{
		PROTOCOL_CC,
		PROTOCOL_NEW,
	};

	YWGUI_HWnd_T hLRCB = YWGUI_NULL_HANDLE;
	YWGUI_HWnd_T hCtrl = YWGUI_NULL_HANDLE;
	YWGUI_LRCBListItem_T stLbItem;
	CFGInfo_T node;


    stLbItem.dwFlags = 0;
    stLbItem.dwAddData = 0;
    stLbItem.dwImage = 0;
	hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX);
	servNum = CFGDataList_GetNumber();
	if(servNum > 0)
	{
	    for(ii = 0; ii < servNum; ii++)
		{
			YWLIB_SwprintfA(wstr, (const S8*)"%d", ii);
	        stLbItem.pszText = wstr;
	        YWGUI_LRCBAddItem(hLRCB, &stLbItem);
		}
	}
	else
	{
		YWNetClientEditi_DisableAllCtrl(hWnd);
		return -1;
	}
    YWGUI_LRCBSetListVisibleCount(hLRCB, 4);
    YWGUI_LRCBSetCurHotItemIndex(hLRCB, indx);

	YWLIB_Memset(&node, 0, sizeof(CFGInfo_T));
	CFGDataList_GetNode(indx, &node);

	//YWNetClientEditi_SetServerNameTxt(hWnd, node.servname);
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_SERV_NAME);
	YWLIB_Astr2wstr(wstr, node.servname);
	YWGUI_SetWindowText(hCtrl, wstr);


	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT);
	YWLIB_Astr2wstr(wstr, node.serviceport);
	YWGUI_SetWindowText(hCtrl, wstr);

	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME);
	YWLIB_Astr2wstr(wstr, node.username);
	YWGUI_SetWindowText(hCtrl, wstr);

	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD);
	YWLIB_Astr2wstr(wstr, node.password);
	YWGUI_SetWindowText(hCtrl, wstr);


	if(YWLIB_Strcmp(node.key, "N") == 0)
	{
		hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY);
		YWLIB_Astr2wstr(wstr, node.deskey);
		YWGUI_SetWindowText(hCtrl, wstr);

		//protocol
		hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_PROTOCOL);
	    for(ii = 0; ii < YWGUI_ARRAY_SIZE(pstr); ii++)
	    {
	    	YWLIB_Astr2wstr(wstr, pstr[ii]);
	        stLbItem.pszText = wstr;
	        YWGUI_LRCBAddItem(hLRCB, &stLbItem);
	    }
	    YWGUI_LRCBSetListVisibleCount(hLRCB, 4);
	    YWGUI_LRCBSetCurHotItemIndex(hLRCB, 1);
	}
	else
	{
		hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY);
		YWLIB_Memset(wstr, 0, sizeof(wstr));
		YWGUI_SetWindowText(hCtrl, wstr);

		//protocol
		hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_PROTOCOL);
	    for(ii = 0; ii < YWGUI_ARRAY_SIZE(pstr); ii++)
	    {
	    	YWLIB_Astr2wstr(wstr, pstr[ii]);
	        stLbItem.pszText = wstr;
	        YWGUI_LRCBAddItem(hLRCB, &stLbItem);
	    }
	    YWGUI_LRCBSetListVisibleCount(hLRCB, 4);
	    YWGUI_LRCBSetCurHotItemIndex(hLRCB, 0);
	}
}

static void YWNetClientEditi_InitCtrl(YWGUI_HWnd_T hWnd, Cfg_Type_T type, int indx)
{
	YWGUI_Handle_T hCtrl = YWGUI_NULL_HANDLE;
	YWGUI_Handle_T hCT  = YWGUI_NULL_HANDLE;
	YWGUI_Char_T wstr[2];
	int i;

	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT);
	YWGUI_EditSetMaxLimit(hCtrl, 5);
	hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY);
	YWGUI_EditSetMaxLimit(hCtrl, 41);

/*	YWLIB_Astr2wstr(wstr, ".");
	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_NET_CFG_EDIT_SERV_NAME);
	hCtrl = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_NET_CFG_EDIT_SERV_DOT1);
	YWGUI_SetWindowText(hCtrl, wstr);
	hCtrl = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_NET_CFG_EDIT_SERV_DOT2);
	YWGUI_SetWindowText(hCtrl, wstr);
	hCtrl = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_NET_CFG_EDIT_SERV_DOT3);
	YWGUI_SetWindowText(hCtrl, wstr);

	for(i=0; i<4;i++)
	{
		hCtrl = YWGUI_CTGetCtrlHandleById(hCT, IDC_EDIT_NET_CFG_EDIT_SERV_NAME1+i);
		YWGUI_SEditSetMaxLimit(hCtrl, 3);
	}*/

	if(type == CFG_TYPE_OSCAM)
	{
		YWNetClientEditi_OscamInitCtrl(hWnd, indx);
	}
	else if(type == CFG_TYPE_MG_CCCAMD)
	{
		YWNetClientEditi_CccamdInitCtrl(hWnd, indx);
	}
	else if(type == CFG_TYPE_MG_NEWCAMD)
	{
		YWNetClientEditi_NewcamdInitCtrl(hWnd, indx);
	}
	else if(type == CFG_TYPE_CCCAMCFG)
	{
		YWNetClientEditi_CccamCfgInitCtrl(hWnd, indx);
	}

}


static void YWNetClientEditi_DisplayOscamCtrl(YWGUI_HWnd_T hWnd, int indx)
{
	CFGInfo_T node;

	YWLIB_Memset(&node, 0, sizeof(CFGInfo_T));
	CFGDataList_GetNode(indx, &node);

	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX), TRUE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_SERV_NAME), TRUE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT), TRUE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME), TRUE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD), TRUE);

	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_DES_KEY), YWGUI_SW_SHOW);
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), YWGUI_SW_SHOW);
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_PROTOCOL), YWGUI_SW_SHOW);
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_PROTOCOL), YWGUI_SW_SHOW);

	if(YWLIB_Strcmp(node.protocol, PROTOCOL_NEW) == 0)
	{
		YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_DES_KEY), TRUE);
		YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), TRUE);
	}
	else
	{
		YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_DES_KEY), FALSE);
		YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), FALSE);
	}

	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_PROTOCOL), TRUE);
	
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_SERVICE_PORT_END), YWGUI_SW_HIDE);
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT_END), YWGUI_SW_HIDE);
}

static void YWNetClientEditi_DisplaycccamdCtrl(YWGUI_HWnd_T hWnd)
{
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX), TRUE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_SERV_NAME), TRUE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT), TRUE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME), TRUE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD), TRUE);

	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_DES_KEY), YWGUI_SW_HIDE);
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), YWGUI_SW_HIDE);
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_PROTOCOL), YWGUI_SW_HIDE);
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_PROTOCOL), YWGUI_SW_HIDE);

	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_SERVICE_PORT_END), YWGUI_SW_HIDE);
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT_END), YWGUI_SW_HIDE);
	
}

static void YWNetClientEditi_DisplayNewcamdCtrl(YWGUI_HWnd_T hWnd, int indx)
{
	CFGInfo_T node;

	YWLIB_Memset(&node, 0, sizeof(CFGInfo_T));
	CFGDataList_GetNode(indx, &node);

	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX), TRUE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_SERV_NAME), TRUE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT), TRUE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME), TRUE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD), TRUE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), TRUE);

	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_DES_KEY), YWGUI_SW_SHOW);
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), YWGUI_SW_SHOW);
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_PROTOCOL), YWGUI_SW_HIDE);
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_PROTOCOL), YWGUI_SW_HIDE);

	if(YWNetClientEditi_NewCamdNodeIsMULTIPLE(node.key))
	{
		YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_SERVICE_PORT_END), YWGUI_SW_SHOW);
		YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT_END), YWGUI_SW_SHOW);

		YWGUI_MoveWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_SERVICE_PORT_END),
								100, 50+52*3, 300, 52, TRUE, NULL);
		YWGUI_MoveWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT_END),
								(100+300), 50+52*3, 720, 52, TRUE, NULL);
		
		YWGUI_MoveWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_USER_NAME),
								100, 50+52*4, 300, 52, TRUE, NULL);
		YWGUI_MoveWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME),
								(100+300), 50+52*4, 720, 52, TRUE, NULL);
		
		YWGUI_MoveWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_PASSWORD),
								100, 50+52*5, 300, 52, TRUE, NULL);
		YWGUI_MoveWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD),
								(100+300), 50+52*5, 720, 52, TRUE, NULL);

		YWGUI_MoveWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_DES_KEY),
								100, 50+52*6, 300, 52, TRUE, NULL);
		YWGUI_MoveWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY),
								(100+300), 50+52*6, 720, 52,TRUE,NULL);
	}
	else
	{
		YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_SERVICE_PORT_END), YWGUI_SW_HIDE);
		YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT_END), YWGUI_SW_HIDE);

		
		YWGUI_MoveWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_USER_NAME),
								100, 50+52*3, 300, 52, TRUE, NULL);
		YWGUI_MoveWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME),
								(100+300), 50+52*3, 720, 52, TRUE, NULL);
		
		YWGUI_MoveWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_PASSWORD),
								100, 50+52*4, 300, 52, TRUE, NULL);
		YWGUI_MoveWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD),
								(100+300), 50+52*4, 720, 52, TRUE, NULL);

		YWGUI_MoveWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_DES_KEY),
								100, 50+52*5, 300, 52, TRUE, NULL);
		YWGUI_MoveWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY),
								(100+300), 50+52*5, 720, 52,TRUE,NULL);
	}

}

static void YWNetClientEditi_DisplayCCcamCfgCtrl(YWGUI_HWnd_T hWnd, int indx)
{
	CFGInfo_T node;

	YWLIB_Memset(&node, 0, sizeof(CFGInfo_T));
	CFGDataList_GetNode(indx, &node);

	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX), TRUE);
	//YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_CTN_NET_CFG_EDIT_SERV_NAME), TRUE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_SERV_NAME), TRUE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT), TRUE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_USER_NAME), TRUE);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_BTN_NET_CFG_EDIT_PASSWORD), TRUE);

	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_DES_KEY), YWGUI_SW_SHOW);
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), YWGUI_SW_SHOW);
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_PROTOCOL), YWGUI_SW_SHOW);
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_PROTOCOL), YWGUI_SW_SHOW);

	if(YWLIB_Strcmp(node.key, "N") == 0)
	{
		YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_DES_KEY), TRUE);
		YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), TRUE);
	}
	else
	{
		YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_DES_KEY), FALSE);
		YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), FALSE);
	}
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_PROTOCOL), TRUE);

	
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_SERVICE_PORT_END), YWGUI_SW_HIDE);
	YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT_END), YWGUI_SW_HIDE);
}

static void YWNetClientEditi_DisplayCtrl(YWGUI_HWnd_T hWnd, Cfg_Type_T type, int indx)
{
	if(type == CFG_TYPE_OSCAM)
	{
		YWNetClientEditi_DisplayOscamCtrl(hWnd, indx);
	}
	else if(type == CFG_TYPE_MG_CCCAMD)
	{
		YWNetClientEditi_DisplaycccamdCtrl(hWnd);
	}
	else if(type == CFG_TYPE_MG_NEWCAMD)
	{
		YWNetClientEditi_DisplayNewcamdCtrl(hWnd, indx);
	}
	else if(type == CFG_TYPE_CCCAMCFG)
	{
		YWNetClientEditi_DisplayCCcamCfgCtrl(hWnd, indx);
	}
}

static void YWNetClientEditi_ResetIndexLRCItem(YWGUI_HWnd_T hWnd)
{
	YWGUI_Handle_T hLRC;
	int itemcount;
	int i;
	int servNum;
	YWGUI_LRCBListItem_T stLbItem;
	YWGUI_Char_T wstr[8];


	hLRC = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX);
	itemcount = YWGUI_LRCBGetItemCount(hLRC);
	for(i=itemcount-1; i>=0; i--)
	{
		YWGUI_LRCBDeleteItem(hLRC, i);
	}

	itemcount = YWGUI_LRCBGetItemCount(hLRC);
	stLbItem.dwFlags = 0;
    stLbItem.dwAddData = 0;
    stLbItem.dwImage = 0;
	servNum = CFGDataList_GetNumber();

    for(i = 0; i < servNum; i++)
	{
		YWLIB_Memset(wstr, 0, sizeof(wstr));
		YWLIB_SwprintfA(wstr, (const S8*)"%d", i);
        stLbItem.pszText = wstr;
        YWGUI_LRCBAddItem(hLRC, &stLbItem);
	}
}

static int YWNetClientEditi_Addnode(YWGUI_HWnd_T hWnd, Cfg_Type_T type)
{
	int num = 0;
	char astr[128];
	CFGInfo_T node;

	YWLIB_Memset(&node, 0, sizeof(CFGInfo_T));
	YWLIB_Memset(astr, 0, sizeof(astr));

	YWLIB_Sprintf(astr, (const S8 *)"0.0.0.0");
	YWLIB_Strcpy(node.servname, astr);

	YWLIB_Sprintf(astr, (const S8 *)"80000");
	YWLIB_Strcpy(node.serviceport, astr);

	YWLIB_Sprintf(astr, (const S8 *)"dummy");
	YWLIB_Strcpy(node.username, astr);
	YWLIB_Strcpy(node.password, astr);

	if(g_Cfg_Type == CFG_TYPE_OSCAM)
	{
		YWLIB_Sprintf(astr, (const S8 *)"reader");
		YWLIB_Strcpy(node.section, astr);

		YWLIB_Sprintf(astr, (const S8 *)"label%d", random());
		YWLIB_Strcpy(node.label, astr);

		YWLIB_Sprintf(astr, (const S8 *)"1");
		YWLIB_Strcpy(node.group, astr);

		YWLIB_Sprintf(astr, (const S8 *)"%s", PROTOCOL_CC);
		YWLIB_Strcpy(node.protocol, astr);
	}
	else if(g_Cfg_Type == CFG_TYPE_MG_CCCAMD)
	{

		YWLIB_Sprintf(astr, (const S8 *)"C");
		YWLIB_Strcpy(node.key, astr);
	}
	else if(g_Cfg_Type == CFG_TYPE_MG_NEWCAMD)
	{
		YWLIB_Sprintf(astr, (const S8 *)"CWS");
		YWLIB_Strcpy(node.key, astr);

		YWLIB_Sprintf(astr, (const S8 *)"01 02 03 04 05 06 07 08 09 10 11 12 13 14");
		YWLIB_Strcpy(node.deskey, astr);
	}
	else if(g_Cfg_Type == CFG_TYPE_CCCAMCFG)
	{
		YWLIB_Sprintf(astr, (const S8 *)"C");
		YWLIB_Strcpy(node.key, astr);

		YWLIB_Memset(astr, 0, sizeof(astr));
		YWLIB_Strcpy(node.deskey, astr);
	}

	CFGDataList_AddNode(&node);
	num = CFGDataList_GetNumber();

	return num;
}


static void YWNetClientEditi_WriteFile(Cfg_Type_T type)
{
	char fullpath[512] = {0};

	YWLIB_Memset(fullpath, 0, sizeof(fullpath));

	if(type == CFG_TYPE_OSCAM)
	{
		YWLIB_Snprintf(fullpath, sizeof(fullpath), "%s/%s", OSCAM_SERVER_PATH, "oscam.server");
		write_oscaminfo(fullpath);
	}
	else if(type == CFG_TYPE_MG_CCCAMD)
	{
		YWLIB_Snprintf(fullpath, sizeof(fullpath), "%s/%s", MG_CC_CFG_PATH, "cccamd.list");
		write_cccamdinfo(fullpath);
	}
	else if(type == CFG_TYPE_MG_NEWCAMD)
	{
		YWLIB_Snprintf(fullpath, sizeof(fullpath), "%s/%s", MG_CC_CFG_PATH, "newcamd.list");
		write_newcamdinfo(fullpath);
	}
	else if(type == CFG_TYPE_CCCAMCFG)
	{
		YWLIB_Snprintf(fullpath, sizeof(fullpath), "%s/%s", MG_CC_CFG_PATH, "CCcam.cfg");
		write_cccamcfginfo(fullpath);
	}

}

static S32 YWNetClientEditi_WndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
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
			//YWNetClientEditi_IniTxt(hWnd);
			YWNetClientEditi_UpdateFunctionKeyNormalText(hWnd);
			YWNetClientEditi_DisplayCtrl(hWnd, g_Cfg_Type, 0);
			YWNetClientEditi_InitCtrl(hWnd, g_Cfg_Type, 0);
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

        case YWGUI_MSG_COMMAND:
        {
            U16 id = YWGUI_LOWORD(wParam);
            U16 notifyCode= YWGUI_HIWORD(wParam);
			YWGUI_Char_T wstr[48];

			YWLIB_Memset(wstr, 0, sizeof(wstr));

            if (YWGUI_NONE_CODE == notifyCode)
            {
				switch(id)
				{
					case IDC_BTN_NET_CFG_EDIT_SERV_NAME:
					{
                        YWPLUGINREAME_Param_T tPluginRenameParam;

						YWGUI_GetWindowText(YWGUI_GetDlgItem(hWnd, id), wstr, sizeof(wstr));
                        tPluginRenameParam.hHosting = hWnd;
                        tPluginRenameParam.pStrContent = wstr;
                        tPluginRenameParam.nEditLimitLen = 47;
						tPluginRenameParam.pStrTitle = NULL;
                        YWPlugin_CreateRenameWindow(&tPluginRenameParam);

					}
						break;

					case IDC_BTN_NET_CFG_EDIT_USER_NAME:
					case IDC_BTN_NET_CFG_EDIT_PASSWORD:
					{
                        YWPLUGINREAME_Param_T tPluginRenameParam;
						//g_Cfg_Type
						YWGUI_GetWindowText(YWGUI_GetDlgItem(hWnd, id), wstr, sizeof(wstr));
                        tPluginRenameParam.hHosting = hWnd;
                        tPluginRenameParam.pStrContent = wstr;
                        tPluginRenameParam.nEditLimitLen = 47;
						tPluginRenameParam.pStrTitle = NULL;
                        YWPlugin_CreateRenameWindow(&tPluginRenameParam);

					}
						break;
				}
        	}
			else if(YWGUI_LRCBN_CBCHANGE == notifyCode)
			{
                if (IDC_LRC_NET_CFG_EDIT_INDEX == id)
                {
					int indx = 0;
					YWGUI_Handle_T hLRC = YWGUI_GetDlgItem(hWnd, id);

					indx = YWGUI_LRCBGetCurHotItemIndex(hLRC);
					YWNetClientEditi_DisplayCtrl(hWnd, g_Cfg_Type, indx);
					YWNetClientEditi_RefreshCtrl(hWnd, g_Cfg_Type, indx);
            	}
				else if(IDC_LRC_NET_CFG_EDIT_PROTOCOL == id)
				{
					if(g_Cfg_Type == CFG_TYPE_CCCAMCFG)
					{
						int indx = 0;
						int iprotocolIdx = 0;
						CFGInfo_T node;
						YWGUI_Handle_T hCtrl;
						YWGUI_Handle_T hLRC = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX);

						YWLIB_Memset(&node, 0, sizeof(CFGInfo_T));
						indx = YWGUI_LRCBGetCurHotItemIndex(hLRC);
						CFGDataList_GetNode(indx, &node);

						hLRC = YWGUI_GetDlgItem(hWnd, id);
						iprotocolIdx = YWGUI_LRCBGetCurHotItemIndex(hLRC);
						if(iprotocolIdx ==1)
						{
							YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), TRUE);
							YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_DES_KEY), TRUE);

							hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY);
							if(YWLIB_Strcmp(node.key, "N") == 0)
							{
								YWLIB_Astr2wstr(wstr, node.deskey);
							}
							else
							{
								YWLIB_Astr2wstr(wstr, "01 02 03 04 05 06 07 08 09 10 11 12 13 14");
							}
							YWGUI_SetWindowText(hCtrl, wstr);
						}
						else
						{
							hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY);
							YWLIB_Memset(wstr, 0, sizeof(wstr));
							YWGUI_SetWindowText(hCtrl, wstr);

							YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), FALSE);
							YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_DES_KEY), FALSE);
						}
					}
					else if(g_Cfg_Type == CFG_TYPE_OSCAM)
					{
						int indx = 0;
						int iprotocolIdx = 0;
						CFGInfo_T node;
						YWGUI_Handle_T hCtrl;
						YWGUI_Handle_T hLRC = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX);

						YWLIB_Memset(&node, 0, sizeof(CFGInfo_T));
						indx = YWGUI_LRCBGetCurHotItemIndex(hLRC);
						CFGDataList_GetNode(indx, &node);

						hLRC = YWGUI_GetDlgItem(hWnd, id);
						iprotocolIdx = YWGUI_LRCBGetCurHotItemIndex(hLRC);
						if(iprotocolIdx ==1)
						{
							YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), TRUE);
							YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_DES_KEY), TRUE);

							hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY);
							if(YWLIB_Strcmp(node.protocol, PROTOCOL_NEW) == 0)
							{
								char  astr[64];

								YWLIB_Memset(astr, 0, sizeof(astr));
								YWLIB_Memcpy(astr, node.deskey, sizeof(astr));
								YWNetClientEditi_InsertSpaceToDesKey(astr);     	//need insert space
								YWLIB_Astr2wstr(wstr, astr);
							}
							else
							{
								YWLIB_Astr2wstr(wstr, "01 02 03 04 05 06 07 08 09 10 11 12 13 14");
							}
							YWGUI_SetWindowText(hCtrl, wstr);
						}
						else
						{
							hCtrl = YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY);
							YWLIB_Memset(wstr, 0, sizeof(wstr));
							YWGUI_SetWindowText(hCtrl, wstr);

							YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_NET_CFG_EDIT_DES_KEY), FALSE);
							YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), FALSE);
						}
					}
				}
			}

			else if (notifyCode == YWGUI_EN_CHANGE)
            {
                YWGUI_HWnd_T hFocusCT = YWGUI_GetFocus(hWnd);
                U16 FocId = YWGUI_GetDlgCtrlID(hFocusCT);

             /*   if(FocId == IDC_CTN_NET_CFG_EDIT_SERV_NAME)
                {
                    S32 LimitLen = YWGUI_SEditGetMaxLimit(YWGUI_GetFocus(hFocusCT));
                    S32 TxtLen = YWGUI_GetWindowTextLength(YWGUI_GetFocus(hFocusCT));
                    YWGUI_Char_T aTxt[4] = {0};

					YWLIB_Memset(aTxt, 0, sizeof(aTxt));

                    if(LimitLen == TxtLen)   //当前焦点编辑框，输入到最后一位
                    {
                        U32 TxtVal = 0;
                        YWGUI_GetWindowText((YWGUI_GetFocus(hFocusCT)), aTxt, sizeof(aTxt));

                        TxtVal = YWLIB_Watoi(aTxt);

                        if(TxtVal > 255)    //判断输入的数值是否合法
                        {
                            YWLIB_SwprintfA(aTxt, (S8*)"%d", 255);
                            YWGUI_SetWindowText(YWGUI_GetFocus(hFocusCT), aTxt);
                            YWGUI_CTSetNextFocus(hFocusCT);
                        }
                    }
					return 0;
                }
            	else */if (IDC_EDIT_NET_CFG_EDIT_DES_KEY == id)
        		{
					S32 iFocusPos = 0;
					iFocusPos = YWGUI_SEditGetCursorPos(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY));

					if(iFocusPos == 40)
					{
						YWGUI_SEditSetCursorPos(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), iFocusPos-1);
						return 0;
					}

					if((iFocusPos%3)==1)
					{
						YWGUI_SEditSetCursorPos(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), iFocusPos+1);
						return 0;
					}
        		}
				else if(id == IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT)
				{
					S32 iFocusPos = 0;
					iFocusPos = YWGUI_SEditGetCursorPos(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT));

					if(iFocusPos == 4)
					{
						YWGUI_SEditSetCursorPos(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT), 0);
						return 0;
					}
				}

                break;
            }
       /*     else if(notifyCode == YWGUI_EN_HOME_LEFT)
            {
                YWGUI_HWnd_T hFocusCT = YWGUI_GetFocus(hWnd);
                YWGUI_HWnd_T hEdit = YWGUI_NULL_HANDLE;
                U32 nNewFocusTxtLen = 0;

                YWGUI_CTSetPrevFocus(hFocusCT);
                hEdit = YWGUI_GetFocus(hFocusCT);
                nNewFocusTxtLen = YWGUI_GetWindowTextLength(hEdit);
                if(nNewFocusTxtLen > 0)
                {
                    YWGUI_SEditSetCursorPos(hEdit, nNewFocusTxtLen-1);
                }
            }
            else if(notifyCode == YWGUI_EN_END_RIGHT)
            {
                YWGUI_HWnd_T hFocusCT = YWGUI_GetFocus(hWnd);

                YWGUI_CTSetNextFocus(hFocusCT);
            }*/


			else if(YWGUI_NC_SETFOCUS == notifyCode)
			{
				if(id  == IDC_EDIT_NET_CFG_EDIT_DES_KEY)
				{
					YWNetClientEditi_UpdateFunctionKeyDESText(hWnd);
				}
			}
			else if(YWGUI_NC_KILLFOCUS == notifyCode)
			{
				if(id  == IDC_EDIT_NET_CFG_EDIT_DES_KEY)
				{
					YWNetClientEditi_UpdateFunctionKeyNormalText(hWnd);
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
				{
					YWGUI_HWnd_T hDlg;
					
					hDlg = YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_SAVING_DATA), -1);
					YWGUI_UpdateWindow(hDlg);
					YWNetClientEditi_SaveCurIndxData(hWnd, g_Cfg_Type);
					YWNetClientEditi_WriteFile(g_Cfg_Type);
					sleep(1);
                    YWGUI_SendMessage(hWnd, YWGUI_MSG_CLOSE, 0, 0);
            	}
                    return 0;

                case YWGUI_SCANCODE_OK:
				{
					YWGUI_Handle_T hFocus = YWGUI_GetFocus(hWnd);
					YWGUI_Handle_T hLRC = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX);

					if(YWGUI_GetDlgCtrlID(hFocus) == IDC_LRC_NET_CFG_EDIT_INDEX)
					{
						YWNetClientEditi_SaveCurIndxData(hWnd, g_Cfg_Type);
					}

            	}
                    break;

                case YWGUI_SCANCODE_LEFT:
				{
					YWGUI_Handle_T hFocus = YWGUI_GetFocus(hWnd);
					YWGUI_Handle_T hLRC = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX);

					if(YWGUI_GetDlgCtrlID(hFocus) == IDC_LRC_NET_CFG_EDIT_INDEX)
					{
						YWNetClientEditi_SaveCurIndxData(hWnd, g_Cfg_Type);
					}
					else if(YWGUI_GetDlgCtrlID(hFocus)  == IDC_EDIT_NET_CFG_EDIT_DES_KEY)
					{
						S32 iFocusPos = 0;
						iFocusPos = YWGUI_SEditGetCursorPos(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY));
						if(iFocusPos == 0)
						{
							YWGUI_SEditSetCursorPos(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), 40);
							return 0;
						}

						if((iFocusPos%3)==1)
						{
							break;
						}
						else
						{
							YWGUI_SEditSetCursorPos(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), iFocusPos-2);
							return 0;
						}
                	}

            	}
					break;
                case YWGUI_SCANCODE_RIGHT:
				{
					YWGUI_Handle_T hFocus = YWGUI_GetFocus(hWnd);
					YWGUI_Handle_T hLRC = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX);

					if(YWGUI_GetDlgCtrlID(hFocus) == IDC_LRC_NET_CFG_EDIT_INDEX)
					{
						YWNetClientEditi_SaveCurIndxData(hWnd, g_Cfg_Type);
					}
					else if(YWGUI_GetDlgCtrlID(hFocus) == IDC_EDIT_NET_CFG_EDIT_DES_KEY)
					{
						S32 iFocusPos = 0;
						iFocusPos = YWGUI_SEditGetCursorPos(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY));
						if(iFocusPos >= 40)
						{
							YWGUI_SEditSetCursorPos(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), 0);
							return 0;
						}

						if((iFocusPos%3)==0)
						{
							break;
						}
						else
						{
							YWGUI_SEditSetCursorPos(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY), iFocusPos+2);
							return 0;
						}

                	}
            	}
                    break;

                case YWGUI_SCANCODE_UP:
                case YWGUI_SCANCODE_DOWN:
				{
            	}
                    break;
				case YWGUI_SCANCODE_PGDN:
				case YWGUI_SCANCODE_PGUP:
					if(YWGUI_GetFocus(hWnd) == YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY))
					{
						S32 iFocusPos;

						iFocusPos = YWGUI_SEditGetCursorPos(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY));
						YWNetClientEditi_EditDesKey(hWnd, scancode, iFocusPos);
					}
					return 0;

                case YWGUI_SCANCODE_RED:
            	{
					if(YWGUI_GetFocus(hWnd) == YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY))
					{
						S32 iFocusPos;

						iFocusPos = YWGUI_SEditGetCursorPos(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY));
						YWNetClientEditi_EditDesKey(hWnd, scancode, iFocusPos);
						return 0;
					}
					else    //add
					{
						int num = 0;

						YWNetClientEditi_SaveCurIndxData(hWnd, g_Cfg_Type);

						num =YWNetClientEditi_Addnode(hWnd, g_Cfg_Type);

						YWNetClientEditi_ResetIndexLRCItem(hWnd);
						YWNetClientEditi_DisplayCtrl(hWnd, g_Cfg_Type, num-1);
						YWNetClientEditi_RefreshCtrl(hWnd, g_Cfg_Type, num-1);

					/*	YWNetClientEditi_SaveCurIndxData(hWnd, g_Cfg_Type);
						YWNetClientEditi_WriteFile(g_Cfg_Type);*/
					}
            	}
					break;
                case YWGUI_SCANCODE_GREEN:
				{
					if(YWGUI_GetFocus(hWnd) == YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY))
					{
						S32 iFocusPos;

						iFocusPos = YWGUI_SEditGetCursorPos(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY));
						YWNetClientEditi_EditDesKey(hWnd, scancode, iFocusPos);
						return 0;
					}
					else    //delete
					{
						int indx = 0;
						int servNum = 0;
						YWGUI_Handle_T hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX);

						indx = YWGUI_LRCBGetCurHotItemIndex(hLRCB);
						servNum = CFGDataList_GetNumber();
						if(servNum == 1)
						{
							YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_CAN_NOT_DEL_LAST_SERV), 3000);
							return 0;
						}

						CFGDataList_DeleteNode(indx);


						if(indx > 0)
						{
							indx--;
						}
						else
						{
							indx = 0;
						}

						YWNetClientEditi_ResetIndexLRCItem(hWnd);
						YWNetClientEditi_DisplayCtrl(hWnd, g_Cfg_Type, indx);
						YWNetClientEditi_RefreshCtrl(hWnd, g_Cfg_Type, indx);

					}
            	}
					break;
				case YWGUI_SCANCODE_YELLOW:
				{
					if(YWGUI_GetFocus(hWnd) == YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY))
					{
						S32 iFocusPos;

						iFocusPos = YWGUI_SEditGetCursorPos(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY));
						YWNetClientEditi_EditDesKey(hWnd, scancode, iFocusPos);
						return 0;
					}
					else   //create ping window
					{
						YWGUI_Handle_T hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_NET_CFG_EDIT_INDEX);
						int idx;

						idx = YWGUI_LRCBGetCurHotItemIndex(hLRCB);

						YWNetClientEditi_SaveCurIndxData(hWnd, g_Cfg_Type);
						YWNetClientPing_CreateWindow(hWnd, idx);

					}
				}
					break;
				case YWGUI_SCANCODE_BLUE:
					if(YWGUI_GetFocus(hWnd) == YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY))
					{
						S32 iFocusPos;

						iFocusPos = YWGUI_SEditGetCursorPos(YWGUI_GetDlgItem(hWnd, IDC_EDIT_NET_CFG_EDIT_DES_KEY));
						YWNetClientEditi_EditDesKey(hWnd, scancode, iFocusPos);
						return 0;
					}
					else
					{
					}
                    return 0;
                default:
                    break;
            }
		}
            break;


        case YWGUI_MSG_CLOSE:
		{
			YWGeneralPopInfo_CloseWindow();
			CFGDataList_Release();
		}
            break;

        case YWGUI_MSG_DESTROY:
            break;

        default:
            break;
    }

    return YWGUI_DefaultDialogProc(hWnd,message,wParam,lParam);
}



YWGUI_HWnd_T YWNetClientEdit_CreateWindow(YWGUI_HWnd_T hHost)
{
    YWGUI_HWnd_T hNetClientEdit=YWGUI_NULL_HANDLE;
    YW_ErrorType_T Error = YW_NO_ERROR;

    Error = YWGUI_CreateDialog(IDD_NET_CLIENT_CONFIG_EDIT, hHost, YWNetClientEditi_WndProc, 0, &hNetClientEdit);

    return (YW_NO_ERROR == Error) ? hNetClientEdit : YWGUI_NULL_HANDLE;
}



