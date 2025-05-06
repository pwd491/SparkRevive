/*
 * File: general_info.c    
 * Author:  
 * Brief: the definitions of general window.
 * 
 */

/*
 * History:
 * ================================================================
 *
 */

#include <stdio.h>
#include "ywgui_ext.h"
#include "ywstr_id.h"

#include "res_layout.h"
#include "gui.h"
#include "general.h"

#include "ywos.h"
#include "ywlib.h"

//




#define _POP_INFO_
#define TIMER_SHOWINFO_MOMENT 0x8811

typedef struct DispInfoParam_s
{
    YWGUI_Char_T * pStrContent;
	int timeout;

}DispInfoParam_T;


#define POPINFO_DLG

static S32 YWGeneralPopInfoi_WndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
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
			YWGUI_Char_T wstr[64];
			DispInfoParam_T *pinfor;

			pinfor=(DispInfoParam_T *)lParam;

			YWGUI_SetWindowAdditionalData( hWnd, lParam);

			//YWLIB_Memset(wstr, 0x0, sizeof(wstr));
			//YWLIB_Astr2wstr(wstr, (S8 *)"Information");
			YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_POP_INFO_TITLE), YWSTR_GetString(STR_INFORMATION));

			//YWLIB_Memset(wstr, 0x0, sizeof(wstr));
			//YWLIB_Astr2wstr(wstr, pinfor->pStrContent);
			YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_POP_INFO), pinfor->pStrContent);

			if (pinfor->timeout !=-1)
			{
                YWGUI_SetTimer(hWnd,TIMER_SHOWINFO_MOMENT, pinfor->timeout);
			}
    	}
           return 0;

        case YWGUI_MSG_TIMER:
        {
            switch((U32)wParam)
            {
                case TIMER_SHOWINFO_MOMENT:
                {
                	YWGUI_SendMessage(hWnd, YWGUI_MSG_CLOSE, 0, 0);
                }
                break;

                default:
                    break;
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

YWGUI_HWnd_T YWGeneralPopInfo_CreateWindow(YWGUI_HWnd_T hHost, YWGUI_Char_T *pwstr, int timeout)
{
    YWGUI_HWnd_T hPopDlg = YWGUI_NULL_HANDLE;
    YW_ErrorType_T Error = YW_NO_ERROR;
	DispInfoParam_T infor;

	hPopDlg = YWGUI_GetMainWinById(IDD_POP_INFO);
	if(hPopDlg != YWGUI_NULL_HANDLE)
	{
		YWGUI_SendMessage(hPopDlg, YWGUI_MSG_CLOSE, 0 ,0);
	}

	infor.timeout = timeout;
	infor.pStrContent= pwstr;

    Error = YWGUI_CreateDialog(IDD_POP_INFO, hHost, YWGeneralPopInfoi_WndProc, (LPARAM)(&infor), &hPopDlg);

    return (YW_NO_ERROR == Error) ? hPopDlg : YWGUI_NULL_HANDLE;
}

YW_ErrorType_T YWGeneralPopInfo_CloseWindow(void)
{
    YW_ErrorType_T ErrCode = YW_NO_ERROR;
    YWGUI_HWnd_T hPopDlg = YWGUI_GetMainWinById(IDD_POP_INFO);

    if(hPopDlg != YWGUI_NULL_HANDLE)
    {
         YWGUI_SendMessage(hPopDlg, YWGUI_MSG_CLOSE, 0 ,0);
    }
    return ErrCode;

}


#define CONFIRM_DLG
static S32 YWGeneralConfirmInfoi_ConfirmBoxProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
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
			YWGUI_Char_T wstr[64];

			YWGUI_SetWindowAdditionalData( hWnd, lParam);

			//YWLIB_Memset(wstr, 0x0, sizeof(wstr));
			//YWLIB_Astr2wstr(wstr, "Confirm Information");
			YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_CONFIRM_INFO_TITLE), YWSTR_GetString(STR_CONFIRM_INFOR));

			YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_CONFIRM_INFO), (YWGUI_Char_T *)lParam);

			//YWLIB_Memset(wstr, 0x0, sizeof(wstr));
			//YWLIB_Astr2wstr(wstr, "YES");
			YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_BTN_CONFIRM_YES), YWSTR_GetString(STR_YES));

			//YWLIB_Memset(wstr, 0x0, sizeof(wstr));
			//YWLIB_Astr2wstr(wstr, "NO");
			YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_BTN_CONFIRM_NO), YWSTR_GetString(STR_NO));

			YWGUI_SetFocus(YWGUI_GetDlgItem(hWnd, IDC_BTN_CONFIRM_YES));

    	}
           break;

		case YWGUI_MSG_COMMAND:
		{
		    unsigned short id = (unsigned short)YWGUI_LOWORD(wParam);
            unsigned short notifyCode = (unsigned short)YWGUI_HIWORD(wParam);

            if(notifyCode == YWGUI_NONE_CODE)
            {
            	switch(id)
        		{
					case IDC_BTN_CONFIRM_YES:
					{
						YWGUI_PostMessage(YWGUI_GetHosting(hWnd), YWPUBLIC_MSG_CONFIRM_INFO, 0, 1);

						YWGUI_SendMessage(hWnd, YWGUI_MSG_CLOSE, 0, 0);
					}
						break;
					case IDC_BTN_CONFIRM_NO:
					{
						YWGUI_PostMessage(YWGUI_GetHosting(hWnd), YWPUBLIC_MSG_CONFIRM_INFO, 0, 0);

						YWGUI_SendMessage(hWnd, YWGUI_MSG_CLOSE, 0, 0);
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
                    return 0;

                case YWGUI_SCANCODE_OK:
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



YW_ErrorType_T YWGeneralConfirmInfo_CloseConfirmBox(void)
{
    YW_ErrorType_T ErrCode = YW_NO_ERROR;
    YWGUI_HWnd_T hPopDlg = YWGUI_GetMainWinById(IDD_CONFIRM_INFO);

    if(hPopDlg != YWGUI_NULL_HANDLE)
    {
         YWGUI_SendMessage(hPopDlg, YWGUI_MSG_CLOSE, 0 ,0);
    }
    return ErrCode;

}


YWGUI_HWnd_T YWGeneralConfirmInfo_CreateConfirmBox(YWGUI_HWnd_T hHost,
                                            YWGUI_Char_T *pwstr)
{
    YWGUI_HWnd_T hPopDlg = YWGUI_NULL_HANDLE;
    YW_ErrorType_T Error = YW_NO_ERROR;

	hPopDlg = YWGUI_GetMainWinById(IDD_CONFIRM_INFO);
	if(hPopDlg != YWGUI_NULL_HANDLE)
	{
		YWGUI_SendMessage(hPopDlg, YWGUI_MSG_CLOSE, 0 ,0);
	}


    Error = YWGUI_CreateDialog(IDD_CONFIRM_INFO, hHost, YWGeneralConfirmInfoi_ConfirmBoxProc, (LPARAM)(pwstr), &hPopDlg);

    return (YW_NO_ERROR == Error) ? hPopDlg : YWGUI_NULL_HANDLE;
}


#define LANGUAGE_SET_DLG
static S32 YWLanguageSeti_WndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
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
			YWGUI_Handle_T hLRCB = YWGUI_NULL_HANDLE;
			YWGUI_LRCBListItem_T stLbItem;
			U32 ii;
			U32 LangNum = LANGUAGE_COUNT-1;

            stLbItem.dwFlags = 0;
            stLbItem.dwAddData = 0;
            stLbItem.dwImage = 0;

			hLRCB = YWGUI_GetDlgItem(hWnd, IDC_LRC_LANGUAGE_LIST);
			LangNum = LANGUAGE_COUNT - 1;
			for(ii = 0; ii < LangNum; ii++)
			{
				stLbItem.pszText = YWSTR_GetMenuLangString(LANGUAGE_ENGLISH+ii);
				YWGUI_LRCBAddItem(hLRCB, &stLbItem);
			}
			YWGUI_LRCBSetListVisibleCount(hLRCB, 4);
			YWGUI_LRCBSetCurHotItemIndex(hLRCB, (U32)YWSTR_GetLanguage()-1);

			YWGUI_SetFocus(hLRCB);
    	}
           break;

		case YWGUI_MSG_COMMAND:
		{
		    unsigned short id = (unsigned short)YWGUI_LOWORD(wParam);
            unsigned short notifyCode = (unsigned short)YWGUI_HIWORD(wParam);

            if(notifyCode == YWGUI_LRCBN_CBCHANGE)     //LRC 内容改变引发的消息
			{
                if(id == IDC_LRC_LANGUAGE_LIST) // 菜单语言
                {
                	int idex;
					idex = YWGUI_LRCBGetCurHotItemIndex(YWGUI_GetDlgItem(hWnd, IDC_LRC_LANGUAGE_LIST));
                	YWSTR_SetLanguage(idex+1);
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
                    return 0;

                case YWGUI_SCANCODE_OK:
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


YWGUI_HWnd_T YWGeneralLanguageSet_CreateWindow(YWGUI_HWnd_T hHost)
{
    YWGUI_HWnd_T hPopDlg = YWGUI_NULL_HANDLE;
    YW_ErrorType_T Error = YW_NO_ERROR;

	hPopDlg = YWGUI_GetMainWinById(IDD_LANGUAGE_SET);
	if(hPopDlg != YWGUI_NULL_HANDLE)
	{
		YWGUI_SendMessage(hPopDlg, YWGUI_MSG_CLOSE, 0 ,0);
	}


    Error = YWGUI_CreateDialog(IDD_LANGUAGE_SET, hHost, YWLanguageSeti_WndProc, 0, &hPopDlg);

    return (YW_NO_ERROR == Error) ? hPopDlg : YWGUI_NULL_HANDLE;
}




