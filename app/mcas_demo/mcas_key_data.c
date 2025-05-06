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
#include "general.h"

#define KEYNUM_ONECAID (512)

typedef struct YWPLUGINi_KeyInfo_s
{
	U8		biss;

	U16		current_cas_id;
	U16		current_key_idx;
	U16		current_key_num;
	U16		key_index[KEYNUM_ONECAID];

	U16		current_line_num;
	U16		current_line_numcheck;

	U16		line_map_keyidx[KEYNUM_ONECAID*2];
	U8		line_map_keydataidx[KEYNUM_ONECAID*2];

}YWPLUGINi_KeyInfo_T;

static  YWPLUGINi_KeyInfo_T keyinfor;


static char demostr[24];
static U8  demokey[96];

static cakey_t  democakey = {0x0000, 0x2600, SYS__8B_KEY, 1,  demokey, {0,0,0,0,0,0,0,0,0},};

static void YWMCASi_KeyInfoSetLTNum(YWGUI_HWnd_T hLT, U16 curline)
{
	int i, k, keysize;
	int max_count;
	cakey_t *cakey;
	YWPLUGINi_KeyInfo_T *pstkeyinfo;

	pstkeyinfo = (YWPLUGINi_KeyInfo_T *)YWGUI_GetWindowAdditionalData(hLT);


	pstkeyinfo->current_key_num = 0;
	pstkeyinfo->current_key_idx = 0;
	pstkeyinfo->current_line_numcheck= 0;

	max_count = 4;
	//YWOS_Trace(YWOS_TRACE_INFO, "YWMCASi_KeyInfoSetLTNum---------->%d\n", max_count);

	for (i=0; i<max_count; i++)
	{
		cakey = &democakey;
		if(cakey != NULL)
		{
			if  ((pstkeyinfo->current_cas_id &0xff00) == (cakey->system_id&0xff00) )
			{
				pstkeyinfo->key_index[pstkeyinfo->current_key_num ++] = i;
				if (pstkeyinfo->current_key_num >= KEYNUM_ONECAID-1)
				{
					YWOS_Trace(YWOS_TRACE_ERROR, "YWMCASi_KeyInfoSetLTNum---------->Too Much Key !!!!\n");
					break;
				}

				keysize = 8;
				pstkeyinfo->current_line_numcheck += (keysize/8);
			}
		}
	}

    YWGUI_LTSetTotalLine(YWGUI_GetDlgItem(hLT, IDC_LT_PLUGIN_KEY_INFO), pstkeyinfo->current_line_numcheck, curline);

}


static void YWMCASi_KeyInfoSetLTData(YWGUI_HWnd_T hLT)
{
	int k_idx, keysize, k;
    YWGUI_LTItemInfo_T tItemInfo;
	U8	str[64];
	YWGUI_Char_T wstr[64];
	YWPLUGINi_KeyInfo_T *pstkeyinfo;
	cakey_t *cakey;

	pstkeyinfo = (YWPLUGINi_KeyInfo_T *)YWGUI_GetWindowAdditionalData(hLT);


	tItemInfo.Type = YWGUI_LTINFO_TEXT;
	pstkeyinfo->current_line_num = 0;

	for(k_idx = 0; k_idx < pstkeyinfo->current_key_num; k_idx++)
    {

		cakey = &democakey;
		if (cakey!=NULL)
		{
			//YWOS_Trace(YWOS_TRACE_ERROR, "YWMCASi_KeyInfoSetLTData---------->Get Key[%d] [%d] [%d]\n", k_idx, pstkeyinfo->key_index[k_idx], pstkeyinfo->current_line_num);

/*--------->Set NO---------------*/
			YWLIB_Memset(str, 0, sizeof(str));
			YWLIB_Memset(wstr, 0, sizeof(wstr));

			YWLIB_Sprintf((S8*)str, "%04d", k_idx+1);
			YWLIB_Astr2wstr(wstr, (S8*)str);
			tItemInfo.Info.pText = wstr;
	        YWGUI_LTSetItemInfo(YWGUI_GetDlgItem(hLT, IDC_LT_PLUGIN_KEY_INFO), pstkeyinfo->current_line_num, 0, &tItemInfo);

/*--------->Set CAID---------------*/
			YWLIB_Memset(str, 0, sizeof(str));
			YWLIB_Memset(wstr, 0, sizeof(wstr));

			YWLIB_Sprintf((S8*)str, "%04X", cakey->system_id);
			YWLIB_Astr2wstr(wstr, (S8*)str);
			tItemInfo.Info.pText = wstr;
	        YWGUI_LTSetItemInfo(YWGUI_GetDlgItem(hLT, IDC_LT_PLUGIN_KEY_INFO), pstkeyinfo->current_line_num, 1, &tItemInfo);

/*--------->Set ProviderID---------------*/
			YWLIB_Memset((S8*)str, 0, sizeof(str));
			YWLIB_Memset(wstr, 0, sizeof(wstr));

			if (IS_BISS(pstkeyinfo->current_cas_id))
			{
				U16 TPfreq;
				U16 Temp=0;

				Temp = (cakey->keyid <<8);
				
				TPfreq = GET_HIWORD(cakey->provider);
				printf("-----------------------%d\n", TPfreq);
				
				TPfreq &= 0x00FF;
				printf("-----------------------%d\n", TPfreq);
				
				TPfreq  |= Temp;
				printf("-----------------------%d %d %d\n",cakey->keyid, Temp, TPfreq);
				
				YWLIB_Sprintf((S8*)str, "%06d", TPfreq);			
				printf("-----------------------%d\n", TPfreq);
				//YWLIB_Strcpy((S8*)str, cakey->comment);			
			}
			else
			{
				YWLIB_Sprintf((S8*)str, "%06X", cakey->provider);
			}

			YWLIB_Astr2wstr(wstr, (S8*)str);
			tItemInfo.Info.pText = wstr;
	        YWGUI_LTSetItemInfo(YWGUI_GetDlgItem(hLT, IDC_LT_PLUGIN_KEY_INFO), pstkeyinfo->current_line_num, 2, &tItemInfo);

/*--------->Set KeyType---------------*/
			YWLIB_Memset((S8*)str, 0, sizeof(str));
			YWLIB_Memset(wstr, 0, sizeof(wstr));

			YWLIB_Strcpy((S8*)str, "key8");

			YWLIB_Astr2wstr(wstr, (S8*)str);
			tItemInfo.Info.pText = wstr;
	        YWGUI_LTSetItemInfo(YWGUI_GetDlgItem(hLT, IDC_LT_PLUGIN_KEY_INFO), pstkeyinfo->current_line_num, 3, &tItemInfo);

/*--------->Set KeyID---------------*/
			YWLIB_Memset((S8*)str, 0, sizeof(str));
			YWLIB_Memset(wstr, 0, sizeof(wstr));
			if (IS_BISS(pstkeyinfo->current_cas_id))
			{
				YWLIB_Sprintf((S8*)str, "%04X", GET_LOWWORD(cakey->provider));
			}
			else
			{
				YWLIB_Sprintf((S8*)str, "%02X", cakey->keyid);
			}
			YWLIB_Astr2wstr(wstr, (S8*)str);
			tItemInfo.Info.pText = wstr;
	        YWGUI_LTSetItemInfo(YWGUI_GetDlgItem(hLT, IDC_LT_PLUGIN_KEY_INFO), pstkeyinfo->current_line_num, 4, &tItemInfo);

/*--------->Set KeyData---------------*/
			keysize = 8;
			for (k=0; k<keysize; k +=8)
			{
				YWLIB_Memset((S8*)str, 0, sizeof(str));
				YWLIB_Memset(wstr, 0, sizeof(wstr));

				YWLIB_Sprintf((S8*)str, "%02X %02X %02X %02X %02X %02X %02X %02X",
											cakey->key[k],
											cakey->key[k+1],
											cakey->key[k+2],
											cakey->key[k+3],
											cakey->key[k+4],
											cakey->key[k+5],
											cakey->key[k+6],
											cakey->key[k+7]);

				//converttoCapital(str);
				YWLIB_Astr2wstr(wstr, (S8*)str);
				tItemInfo.Info.pText = wstr;
		        YWGUI_LTSetItemInfo(YWGUI_GetDlgItem(hLT, IDC_LT_PLUGIN_KEY_INFO), pstkeyinfo->current_line_num, 5, &tItemInfo);

				pstkeyinfo->line_map_keyidx[pstkeyinfo->current_line_num] = pstkeyinfo->key_index[k_idx];
				pstkeyinfo->line_map_keydataidx[pstkeyinfo->current_line_num++] = k/8;

				if (pstkeyinfo->current_line_num == KEYNUM_ONECAID*2-1)
				{
					YWOS_Trace(YWOS_TRACE_ERROR, "YWMCASi_KeyInfoSetLTData---------->Too Much Line !!!!\n");
					break;
				}
				//if (k<keysize)
				{
					tItemInfo.Info.pText = NULL;
			        YWGUI_LTSetItemInfo(YWGUI_GetDlgItem(hLT, IDC_LT_PLUGIN_KEY_INFO), pstkeyinfo->current_line_num, 0, &tItemInfo);
			        YWGUI_LTSetItemInfo(YWGUI_GetDlgItem(hLT, IDC_LT_PLUGIN_KEY_INFO), pstkeyinfo->current_line_num, 1, &tItemInfo);
			        YWGUI_LTSetItemInfo(YWGUI_GetDlgItem(hLT, IDC_LT_PLUGIN_KEY_INFO), pstkeyinfo->current_line_num, 2, &tItemInfo);
			        YWGUI_LTSetItemInfo(YWGUI_GetDlgItem(hLT, IDC_LT_PLUGIN_KEY_INFO), pstkeyinfo->current_line_num, 3, &tItemInfo);
				    YWGUI_LTSetItemInfo(YWGUI_GetDlgItem(hLT, IDC_LT_PLUGIN_KEY_INFO), pstkeyinfo->current_line_num, 4, &tItemInfo);
			        YWGUI_LTSetItemInfo(YWGUI_GetDlgItem(hLT, IDC_LT_PLUGIN_KEY_INFO), pstkeyinfo->current_line_num, 5, &tItemInfo);
				}
			}

		}

    }


	YWOS_Trace(YWOS_TRACE_ERROR, "YWMCASi_KeyInfoSetLTData---------->Key Num[%d] LineNumCheck[%d] LineNum[%d]\n",
		pstkeyinfo->current_key_num, pstkeyinfo->current_line_num, pstkeyinfo->current_line_numcheck);



}


static S32 YWMCASi_KeyInfoInitTxt(YWGUI_HWnd_T hWnd)
{
	YWGUI_Char_T wstr[64];
	YWPLUGINi_KeyInfo_T *pstkeyinfo;

	pstkeyinfo = (YWPLUGINi_KeyInfo_T *)YWGUI_GetWindowAdditionalData(hWnd);
	
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr,  "No");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_PLUGIN_KEY_INFO_NO), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr,  "CAID");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_PLUGIN_KEY_INFO_CAID), wstr);
	
	YWLIB_Memset(wstr, 0, sizeof(wstr));
	if (IS_BISS(pstkeyinfo->current_cas_id))
	{
		YWLIB_Astr2wstr(wstr,  "TP Freq");
	}
	else
	{
		YWLIB_Astr2wstr(wstr,  "Provider");
	}
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_PLUGIN_KEY_INFO_PROVIDER), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr,  "Type");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_PLUGIN_KEY_INFO_TYPE), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	if (IS_BISS(pstkeyinfo->current_cas_id))
	{
		YWLIB_Astr2wstr(wstr,  "SeviceID");
	}
	else
	{
		YWLIB_Astr2wstr(wstr,  "Index");
	}
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_PLUGIN_KEY_INFO_INDEX), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr,  "Key Data");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_PLUGIN_KEY_INFO_KEY_DATA), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr,  "Edit");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_PLUGIN_KEY_INFO_EDIT), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr,  "Add");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_PLUGIN_KEY_INFO_ADD), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr,  "Delete");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_PLUGIN_KEY_INFO_DELETE), wstr);

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	YWLIB_Astr2wstr(wstr,  "Reset");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_PLUGIN_KEY_INFO_RESET), wstr);

	return 0;

}



static S32 YWMCASi_KeyInfoWndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
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
			YWGUI_Rect_T rcWin;

			YWGUI_SetWindowAdditionalData(hWnd, (DWORD)&keyinfor);
			YWMCASi_KeyInfoInitTxt(hWnd);
			YWGUI_SetRect(&rcWin, 50, 10, 52, 1120);
			YWGUI_InvalidateRect(hWnd, &rcWin, TRUE);
			YWMCASi_KeyInfoSetLTNum(hWnd, 0);

		}
            break;
		case YWGUI_MSG_PAINT:
		{
			YWGUI_HDc_T hdc;
			YWGUI_Pixel_T OldColor;
			hdc = YWGUI_BeginPaint(hWnd);
//dlg	rect {0,0,1220,670}
			//list table title
            YWGUI_SetBrushColor(hdc, Color_grayblue, OldColor);
        	YWGUI_FillBox(hdc, 50, 10, 1120,52);


			//divid bar
            YWGUI_SetBrushColor(hdc, Color_gray, OldColor);
        	YWGUI_FillBox(hdc, 0, 610, 1220,4);

			//
            YWGUI_EndPaint(hWnd,hdc);

		}
			break;
        case YWGUI_MSG_COMMAND:
        {
            unsigned short id = (unsigned short)YWGUI_LOWORD(wParam);
            unsigned short notifyCode = (unsigned short)YWGUI_HIWORD(wParam);

            switch(notifyCode)
            {
                case YWGUI_LTN_NEEDDATA:
                {
                    if(IDC_LT_PLUGIN_KEY_INFO == id)
                    {
                    	YWMCASi_KeyInfoSetLTData(hWnd);
						//YWMCASi_KeyInfoSetLTData(YWGUI_GetDlgItem(hWnd, IDC_LT_PLUGIN_KEY_INFO), lParam);
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }


        case YWGUI_MSG_KEYDOWN:
    	{
            U16 scancode=YWGUI_LOWORD(wParam);
					printf("got scancode [%x]---------------------------------------->\n", scancode);

            switch(scancode)
            {
                case YWGUI_SCANCODE_EXIT:
   					YWGUI_PostMessage(YWGUI_GetMainWinById(IDC_MCAS_KEYEDITOR), YWGUI_MSG_USER, 0x01,0);
                    YWGUI_SendMessage(hWnd, YWGUI_MSG_CLOSE, 0, 0);
                    return 0;


                case YWGUI_SCANCODE_UP:
                case YWGUI_SCANCODE_DOWN:
                    break;

                case YWGUI_SCANCODE_PGUP:
                        YWGUI_LTScrollPage(YWGUI_GetDlgItem(hWnd, IDC_LT_PLUGIN_KEY_INFO), FALSE);
					break;

                case YWGUI_SCANCODE_PGDN:
                        YWGUI_LTScrollPage(YWGUI_GetDlgItem(hWnd, IDC_LT_PLUGIN_KEY_INFO), TRUE);
                    break;

                case YWGUI_SCANCODE_OK:
                    return 0;

                case YWGUI_SCANCODE_RED:
					{
						U32 curline, para ;
						YWPLUGINi_KeyInfo_T *pstkeyinfo;

						printf("got red key---------------------------------------->\n");
						pstkeyinfo = (YWPLUGINi_KeyInfo_T *)YWGUI_GetWindowAdditionalData(hWnd);
						curline = YWGUI_LTGetCurLine(YWGUI_GetDlgItem(hWnd, IDC_LT_PLUGIN_KEY_INFO));
						para = (pstkeyinfo->line_map_keyidx[curline] <<16) |pstkeyinfo->line_map_keydataidx[curline];
						//YWOS_Trace(YWOS_TRACE_INFO, "[%d] [0x%x]\n", curline, para);
						//YWMCAS_CreateKeyEditWindow(hWnd, para );
                	}
                    return 0;
			    case YWGUI_SCANCODE_GREEN:

					{
						U32 curline, para ;
						YWPLUGINi_KeyInfo_T *pstkeyinfo;

						pstkeyinfo = (YWPLUGINi_KeyInfo_T *)YWGUI_GetWindowAdditionalData(hWnd);
						curline = YWGUI_LTGetCurLine(YWGUI_GetDlgItem(hWnd, IDC_LT_PLUGIN_KEY_INFO));
						para = (pstkeyinfo->line_map_keyidx[curline]<<16) |pstkeyinfo->current_cas_id;
						YWOS_Trace(YWOS_TRACE_INFO, "[%d] [0x%x]\n", curline, para);
						//YWMCAS_CreateKeyAddWindow(hWnd, para);
                	}

                    return 0;
                case YWGUI_SCANCODE_YELLOW:
					{
						U32 curline, para;
						YWPLUGINi_KeyInfo_T *pstkeyinfo;

						pstkeyinfo = (YWPLUGINi_KeyInfo_T *)YWGUI_GetWindowAdditionalData(hWnd);
						curline = YWGUI_LTGetCurLine(YWGUI_GetDlgItem(hWnd, IDC_LT_PLUGIN_KEY_INFO));
						para = pstkeyinfo->line_map_keyidx[curline];
						YWOS_Trace(YWOS_TRACE_INFO, "[%d] [0x%x]\n", curline, para);
						//mcas_del_key_db(para);

						if (curline >=2)
							YWMCASi_KeyInfoSetLTNum(hWnd, curline-1);
						else
							YWMCASi_KeyInfoSetLTNum(hWnd, 0);
                	}
                    break;

                case YWGUI_SCANCODE_BLUE:
					{
						YWPLUGINi_KeyInfo_T *pstkeyinfo;

						//mcas_default_keydb();
						//mcas_init_key_db();
						pstkeyinfo = (YWPLUGINi_KeyInfo_T *)YWGUI_GetWindowAdditionalData(hWnd);

						pstkeyinfo->current_cas_id = 0x0500;
						YWMCASi_KeyInfoSetLTNum(hWnd, 0);
                	}
                    break;

                default:
						//printf("unkown key---------------------------------------->0x%x\n", scancode);
									
                    break;
            }
            break;
		}

        case YWGUI_MSG_USER:
			{
				U32 curline;
				curline = YWGUI_LTGetCurLine(YWGUI_GetDlgItem(hWnd, IDC_LT_PLUGIN_KEY_INFO));
				YWMCASi_KeyInfoSetLTNum(hWnd, curline);
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




YWGUI_HWnd_T YWMCAS_CreatKeyInfoWindow(YWGUI_HWnd_T hHost, U16 caid)
{
    YWGUI_HWnd_T hKeyInfo = YWGUI_NULL_HANDLE;
    YW_ErrorType_T Error = YW_NO_ERROR;

		
	printf("YWMCAS_CreatKeyInfoWindow---------------------------------------->\n");

	keyinfor.current_cas_id= caid;

    Error = YWGUI_CreateDialog(IDD_PLUGIN_KEY_INFO, hHost, YWMCASi_KeyInfoWndProc, 0, &hKeyInfo);

    return (YW_NO_ERROR == Error) ? hKeyInfo : YWGUI_NULL_HANDLE;
}


