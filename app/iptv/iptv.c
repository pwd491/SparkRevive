
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

#include "mxml.h"
#include "ywgui_ext.h"
#include "res_layout.h"
#include "iptv_layout.h"
#include "gui.h"
#include "general.h"

#include "ywos.h"
#include "ywlib.h"
#include "ywlib_url.h"
#include "iptv.h"
#include "ywnative.h"


#define LIST_PAGE_NUM 15
#define DEF_URLKEY "0"

static U32 g_WebTvvolume = 0;

static BOOL g_bInit = FALSE;

//play info
static YW_WEBTV_Info_t g_WebTvInfo;
static YW_WEBTV_Node_t *g_pCurPlayWebTvInfo = NULL;
static S32 g_FocusIndex = -1;   //from 0...
static S32 g_CurPlayIndex = -1;

//for swicth play status;
static YW_WEBTV_PLAYSTATUS_T g_WebTvPlayStatus = WEBTV_STOP;


static U32 g_PlayHandle = 0;

/*static char* g_Container_str[] =
{
    "avi",
    "asf",
    "mov",
    "mpeg",
    "mpegts",
    "mpegvideo",
    "flv",
    "mkv",
    "mp3",
    "ac3",
    "wav",
    "lpcm",
    "cdxa",
    "ogg",
    "flac",
    "aac",
    "pdcf",
    "dcf",
    "mpls",
    "mp4",
    "webm",
    "3gp",
};
static char *g_stream_str[37]=
{
    "NULL",
    "MPEG1_VIDEO",
    "MPEG2_VIDEO",
    "MPEG4_VIDEO",
    "MPEG1 LAYER I",
    "MPEG1 LAYER II",
    "MP4_AUDIO",
    "PES_TTX",
    "PES_SUBTITLE",
    "PCR",
    "AC3",
    "H264",
    "MPEG4 PART II",
    "VC1",
    "AAC",
    "HEAAC",
    "WMA",
    "DDPLUS",
    "DTS",
    "MMV",
    "MMA",
    "AVS",
    "MP1A_AD",
    "MP2A_AD",
    "AC3_AD",
    "HEAAC",
    "LPCM",
    "MP1A_AUX",
    "MP2A_AUX",
    "MP4A_AUX",
    "AC3_AUX",
    "AAC_AUX",
    "HEAAC_AUX",
    "WMA_AUX",
    "DDPLUS_AUX",
    "DTS_AUX",
    "LPCM_AUX",
};
*/

static const YWMID_Rect_T g_OutRect[] =
{
    {48, 166, 590, 398},
    {0, 0, 1920, 1080}
};


#define _DATA_LIST_
//init webtv list
static void WebTvi_ListInit(void)
{
    if (!g_bInit)
    {
        YWLIB_INIT_LIST_HEAD(&(g_WebTvInfo.listhead));
        g_WebTvInfo.num = 0;
        g_bInit = TRUE;
    }
}


//add one item to tail
static S32 WebTvi_AddOneNode(YW_WEBTV_Node_t *pNode)
{
	YWLIB_ListAddTail(&pNode->list, &g_WebTvInfo.listhead);

	return 0;
}

//del one item by index
static S32 WebTvi_DelOneNodeByIndex(S32 index)
{
	S32 count = 0;
    YWLIB_ListHead_T *pPos = NULL, *n = NULL;
    YW_WEBTV_Node_t  *pIpTvNode = NULL;

	YWLIB_ListForEachSafe(pPos, n, &g_WebTvInfo.listhead)
	{
		if(count == index)
		{
			pIpTvNode = YWLIB_ListEntry(pPos, YW_WEBTV_Node_t, list);
			YWLIB_ListDel(pPos);
			YWOS_Free(pIpTvNode);
			return 0;
		}
		count++;
	}
	return -1;
}

// get one item by index
static YW_WEBTV_Node_t* WebTvi_GetOneNodeByIndex(S32 index)
{
	S32 count = 0;
    YWLIB_ListHead_T *pPos = NULL, *n = NULL;
    YW_WEBTV_Node_t  *pIpTvNode = NULL;

	YWLIB_ListForEachSafe(pPos, n, &g_WebTvInfo.listhead)
	{
		if(count == index)
		{
			pIpTvNode = YWLIB_ListEntry(pPos, YW_WEBTV_Node_t, list);
			return pIpTvNode;
		}
		count++;
	}

	return NULL;
}

//free webtv list
static void WebTvi_ListFree(void)
{
	YWLIB_ListHead_T *pPos = NULL, *n = NULL;
	YWLIB_ListHead_T *head = &g_WebTvInfo.listhead;
	YW_WEBTV_Node_t  *pIpTvNode = NULL;

	if(!YWLIB_ListEmpty(head))
	{
		YWLIB_ListForEachSafe(pPos, n, head)
		{
			pIpTvNode = YWLIB_ListEntry(pPos, YW_WEBTV_Node_t, list);
			YWLIB_ListDel(pPos);
			YWOS_Free(pIpTvNode);
		}
		head->Prev=head->Next=head;
	}
}



static BOOL WebTvi_IsUrlValid(S8 *url)
{
	S8 urltmp[URL_LEN];
	S8 *pstr = NULL;

	YWLIB_Memset(urltmp, 0, sizeof(urltmp));
	YWLIB_Strcpy(urltmp, url);

	pstr = YWLIB_Strstr(urltmp, (S8 *)"//");
	if(pstr == NULL)
	{
		return FALSE;
	}
	else
	{
		*(pstr+2) = 0;
		if(YWLIB_Strcmp(urltmp, (S8 *)"http://")==0 ||
			YWLIB_Strcmp(urltmp, (S8 *)"rtmp://")==0 ||
			YWLIB_Strcmp(urltmp, (S8 *)"rtsp://")==0 ||
			YWLIB_Strcmp(urltmp, (S8 *)"rtp://")==0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}




static int WebTvi_SaveXmlFile(void)
{
	int s32Ret = -1;

	FILE *fp = NULL;
	int ii;
	S8 buf[8];
	char path[256] = {0};
	YW_WEBTV_Node_t  *pWebTvNode = NULL;

    mxml_node_t *xml = NULL;
    mxml_node_t *webtvs = NULL;
	mxml_node_t *webtv = NULL;

	xml = mxmlNewXML("1.0");
	webtvs = mxmlNewElement(xml, XML_ELEMENT_WEBTVS);

	for(ii=0; ii<g_WebTvInfo.num; ii++)
	{
		webtv = mxmlNewElement(webtvs, (const char *)XML_ELEMENT_WEBTV);

		pWebTvNode = WebTvi_GetOneNodeByIndex(ii);

		mxmlElementSetAttr(webtv, ATTR_WEBTV_TITLE, (const char *)pWebTvNode->title);
		mxmlElementSetAttr(webtv, ATTR_WEBTV_URL, (const char *)pWebTvNode->url);
		mxmlElementSetAttr(webtv, ATTR_WEBTV_DESCRIPTION, (const char *)pWebTvNode->description);

		YWLIB_Memset(buf, 0, sizeof(buf));
		YWLIB_Sprintf(buf, (const S8*)"%d", pWebTvNode->mediatype);
		mxmlElementSetAttr(webtv, ATTR_WEBTV_TYPE, (const char *)buf);
	}

	YWLIB_Memset(path, 0, sizeof(path));
	YWLIB_Snprintf((S8 *)path, sizeof((path)), (const S8*)"%s%s", WEBTV_XML_PATH, WEBTV_XML_FILE);
    fp = fopen(path, "w");
	if(fp == NULL)
	{
		printf("Open file failed\n");
		s32Ret = -1;
	}
	else
	{
	 	s32Ret = mxmlSaveFile(xml, fp, MXML_NO_CALLBACK);
	    fclose(fp);
		if(s32Ret == -1)
		{
			printf("write file failed  s32Ret: %d\n", s32Ret);
		}
	}
	mxmlDelete(xml);

	return s32Ret;
}


#define _WEBTV_PLAY_PROC

static void VodListener(U32 event, void *info, U32 handle)
{
	YW_ErrorType_T error = YW_NO_ERROR;
	S32 state = 0;
	

	switch(event)
	{
		case 0:
		{
			error = YWNATIVE_AvGetState(handle, &state);
			if(error != YW_NO_ERROR)
			{
				return;
			}

			switch(state)
			{
				case 1: //playing
				{
					YWGUI_Handle_T hWnd;
					
					hWnd = YWGUI_GetMainWinById(IDD_IPTV_PLAY);
					if(hWnd != YWGUI_NULL_HANDLE)
					{
			        	YWGUI_PostMessage(YWGUI_GetMainWinById(IDD_IPTV_PLAY), YWPUBLIC_MSG_WEBTV_PLAY, 0, 0);
					}
					else
					{
			        	YWGUI_PostMessage(YWGUI_GetMainWinById(IDD_IPTV), YWPUBLIC_MSG_WEBTV_PLAY, 0, 0);
					}
				}
					break;
				case 3: //waiting for connecting 
				case 4: //buffering
					break;
				case 0:  //stop
				case 5: //finished
				{
					YWGUI_Handle_T hWnd = YWGUI_GetMainWinById(IDD_IPTV_PLAY);
					if(hWnd != YWGUI_NULL_HANDLE)
					{
						YWGUI_SendMessage(YWGUI_GetMainWinById(IDD_IPTV_PLAY), YWPUBLIC_MSG_END_OF_FILE, 0, 0);
					}
					else
					{
		            	YWGUI_SendMessage(YWGUI_GetMainWinById(IDD_IPTV), YWPUBLIC_MSG_END_OF_FILE, 0, 0);
					}
        		}
					break;
				case 6: //error
				{
					YWGUI_Handle_T hWnd;
					hWnd = YWGUI_GetMainWinById(IDD_IPTV_PLAY);
					if(hWnd != YWGUI_NULL_HANDLE)
					{
			        	YWGUI_PostMessage(YWGUI_GetMainWinById(IDD_IPTV_PLAY), YWPUBLIC_MSG_WEBTV_PLAY, 1, 0);
					}
					else
					{
			        	YWGUI_PostMessage(YWGUI_GetMainWinById(IDD_IPTV), YWPUBLIC_MSG_WEBTV_PLAY, 1, 0);
					}
				}
					break;
				default:
					break;
			}
			
		}
			break;
		case 1:
		case 2:
		case 3:
		case 4:
			break;
		default:
			break;
		
	}
}

static S32 WebTvi_PlayInit(U32 *handle)
{
	YW_ErrorType_T error = YW_NO_ERROR;

	error = YWNATIVE_Init();

	if(YW_NO_ERROR != error)
	{
		printf("native init error. error = %d\n", error);
		YWNATIVE_Term();
		return -1;
	}

	error = YWNATIVE_GetFreeHandle((S8 *)"Vod", handle);
	if(error != YW_NO_ERROR)
	{
		printf("get free handle error. error=%d. \n", error);
		YWNATIVE_Term();
		return -1;
	}
	
	YWNATIVE_AddVodEventListener((void *)VodListener);

	return 0;
}

static S32 WebTvi_StartPlay(U32 handle, U8 *url)
{
/*	U8 videCodec[8];
	U8 container[8];

	YWLIB_Memset(videCodec, 0, sizeof(videCodec));
	YWLIB_Memset(container, 0, sizeof(container));*/

	U32 pos = 0;
	U32 speed = 100;
	
	YW_ErrorType_T error = YW_NO_ERROR;

	YWNATIVE_AvStop(handle);

	error = YWNATIVE_AvPLay(handle, url, NULL, NULL, NULL, &pos,
		&speed, NULL, NULL, NULL);
	if(YW_NO_ERROR != error)
	{
		printf("av play error: %d\n", error);
	}

	return error;
}

static YW_ErrorType_T WebTvi_StopPlay(U32 handle)
{
	return YWNATIVE_AvStop(handle);
}

static YW_ErrorType_T WebTvi_PausePlay(U32 handle)
{
	return YWNATIVE_AvPause(handle);
}

static YW_ErrorType_T WebTvi_ResumePlay(U32 handle)
{
	return YWNATIVE_AvResume(handle);
}


static void WebTvi_SetVolume(U32 handle, U32 volume)
{
    U8 volNum = volume;
    U8 vol;
    U8 iVolArray[] =
    {
        0, 38, 45, 48, 51, 63, 76, 89, 102, 114,
        127, 140, 153, 165, 178, 191, 204, 216, 229, 242, 255,
    };


    //0~255
    if(volNum >= 20)
    {
        volNum = 20;
        vol = 255;
    }
    else
    {
        vol = iVolArray[volNum];
    }

    if(YW_NO_ERROR == YWNATIVE_AvSetVol(handle, vol))
    {
        g_WebTvvolume = volNum;
        printf("set vol = %d\n", vol);
    }
    else
    {
        printf("set volume failed.\n");
    }
}


static void WebTvi_GetVolume(U32 handle, U32 *volume)
{
	U8 i=0;
    U8 vol;
    U8 iVolArray[] =
    {
        0, 38, 45, 48, 51, 63, 76, 89, 102, 114,
        127, 140, 153, 165, 178, 191, 204, 216, 229, 242, 255,
    };

    //0~255
    if(YW_NO_ERROR == YWNATIVE_AvGetVol(handle, &vol))
    {
		for(i=0; i<sizeof(iVolArray); i++)
		{
			if(vol == iVolArray[i])
			{
				break;
			}
		}

		if(i >= sizeof(iVolArray))
			i=20;
		
		*volume = i;
		
        printf("get vol = %d\n", vol);
    }
    else
    {
        printf("Get volume failed.\n");
    }
}



static void WebTvi_PlayTerm(U32 handle)
{
	YWNATIVE_ReleaseHandle(handle);
	YWNATIVE_Term();
}

static void WebTvi_SetVideoOutWindow(U32 handle, BOOL bSmallWind)
{
	S16 x;
	S16 y;
	S16 w;
	S16 h;

	U32 i;
	
	if(bSmallWind)
	{
		i = 0;	
		
	}
	else
	{
		i = 1;
	}

	x = (g_OutRect[i].X*1280)/1920;
	y = (g_OutRect[i].Y*720)/1080;
	w = (g_OutRect[i].W*1280)/1920;
	h = (g_OutRect[i].H*720)/1080;
/*	x = (g_OutRect[i].X);
	y = (g_OutRect[i].Y);
	w = (g_OutRect[i].W);
	h = (g_OutRect[i].H);*/
	
	YWNATIVE_AvSetWin(handle, x, y, w, h);
	
}



#define _WAIT_WND_
static S32 WAIT_WndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam, LPARAM lParam)
{
    static S32 mCount = 1;
    
    switch (message)
    {
        case YWGUI_MSG_NCCREATE:
        {
            YWGUI_SetWEColor(hWnd, YWGUI_MAINWND_BGC, Color_black);
            break;
        }
        case YWGUI_MSG_INITDIALOG:
        {
            mCount = 1;
            YWGUI_ResetTimer(hWnd, 54321, 300);
            break;
        }
        case YWGUI_MSG_KEYDOWN:
        {
			U16 scancode=YWGUI_LOWORD(wParam);
            if (scancode == YWGUI_SCANCODE_EXIT)
            {                
                YWGUI_SendMessage(hWnd, YWGUI_MSG_CLOSE, 0, 0);
            }
            break;
        }
        case YWGUI_MSG_TIMER:
        {
            YWGUI_MoveWindow(YWGUI_GetDlgItem(hWnd, IDC_PIC_WAIT),
                0+48*mCount, 0, 90, 28, TRUE, NULL);
            mCount = (mCount + 1) % 10;
            return 0;
        }
        case YWGUI_MSG_CLOSE:
        {
            YWGUI_KillTimer(hWnd, 54321);
            break;
        }
        default:
        {
            break;
        }
    }

    return YWGUI_DefaultDialogProc(hWnd,message,wParam,lParam);
}


YWGUI_HWnd_T WAIT_CreateWnd(YWGUI_HWnd_T hHost)
{
    YW_ErrorType_T stError = YW_NO_ERROR;
    YWGUI_HWnd_T hMainWnd = YWGUI_GetMainWinById(IDD_WAIT);

    if (YWGUI_NULL_HANDLE == hMainWnd)
    {
    
        stError = YWGUI_CreateDialog(IDD_WAIT, hHost, WAIT_WndProc, 0, &hMainWnd);
        if(stError != YW_NO_ERROR)
        {
            return YWGUI_NULL_HANDLE;
        }
    }
    
    return hMainWnd;
}



#define EDIT_WEBTV_DATA

static void WebTvi_SaveEditWindCtrl(YWGUI_HWnd_T hWnd, U32 EditIndex)
{
	YWGUI_Handle_T hCT = YWGUI_NULL_HANDLE;
	YWGUI_Handle_T hTXT = YWGUI_NULL_HANDLE;
	YWGUI_Handle_T hLRC = YWGUI_NULL_HANDLE;
	YWGUI_Char_T wstr[URL_LEN];

	YW_WEBTV_Node_t  *pWebTvNode = NULL;

	pWebTvNode = WebTvi_GetOneNodeByIndex(EditIndex);

	//title
	YWLIB_Memset(wstr, 0x0, sizeof(wstr));
	YWLIB_Memset(pWebTvNode->title, 0x0, sizeof(pWebTvNode->title));
	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_IPTV_ADD_TV_TITLE);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_TITLE_R);
	YWGUI_GetWindowText(hTXT, wstr, sizeof(wstr));
	YWPUBLIC_Utf16To8((S8*)wstr,
                    (YWLIB_Wstrlen(wstr)+1)*sizeof(YWLIB_WChar_T),
                    (S8*)pWebTvNode->title,
                    sizeof(pWebTvNode->title));

	//url
	YWLIB_Memset(wstr, 0x0, sizeof(wstr));
	YWLIB_Memset(pWebTvNode->url, 0x0, sizeof(pWebTvNode->url));
	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_IPTV_ADD_TV_URL);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_URL_R);
	YWGUI_GetWindowText(hTXT, wstr, sizeof(wstr));
	YWPUBLIC_Utf16To8((S8*)wstr,
                    (YWLIB_Wstrlen(wstr)+1)*sizeof(YWLIB_WChar_T),
                    (S8*)pWebTvNode->url,
                    sizeof(pWebTvNode->url));

	//description
	YWLIB_Memset(wstr, 0x0, sizeof(wstr));
	YWLIB_Memset(pWebTvNode->description, 0x0, sizeof(pWebTvNode->description));
	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_IPTV_ADD_TV_DESCRIPTION);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_DESCRIPTION_R);
	YWGUI_GetWindowText(hTXT, wstr, sizeof(wstr));
	YWPUBLIC_Utf16To8((S8*)wstr,
                    (YWLIB_Wstrlen(wstr)+1)*sizeof(YWLIB_WChar_T),
                    (S8*)pWebTvNode->description,
                    sizeof(pWebTvNode->description));

	//user name
/*	YWLIB_Memset(wstr, 0x0, sizeof(wstr));
	YWLIB_Memset(pWebTvNode->username, 0x0, sizeof(pWebTvNode->username));
	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_WEBTV_ADD_USER_NAME);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_WEBTV_ADD_USER_NAME_R);
	YWGUI_GetWindowText(hTXT, wstr, sizeof(wstr));
	YWPUBLIC_Utf16To8((S8*)wstr,
                    YWLIB_Wstrlen(wstr)*sizeof(YWLIB_WChar_T),
                    (S8*)pWebTvNode->username,
                    sizeof(pWebTvNode->username));*/

	//password
/*	YWLIB_Memset(wstr, 0x0, sizeof(wstr));
	YWLIB_Memset(pWebTvNode->psw, 0x0, sizeof(pWebTvNode->psw));
	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_WEBTV_ADD_PSW);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_WEBTV_ADD_PSW_R);
	YWGUI_GetWindowText(hTXT, wstr, sizeof(wstr));
	YWPUBLIC_Utf16To8((S8*)wstr,
                    YWLIB_Wstrlen(wstr)*sizeof(YWLIB_WChar_T),
                    (S8*)pWebTvNode->psw,
                    sizeof(pWebTvNode->psw));*/

	//account
/*	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_WEBTV_ADD_ACCOUNT);
	hLRC = YWGUI_CTGetCtrlHandleById(hCT, IDC_LRC_WEBTV_ADD_ACCOUNT_R);
	pWebTvNode->account = YWGUI_LRCBGetCurHotItemIndex(hLRC);*/


	//media type
	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_IPTV_ADD_MEDIA_TYPE);
	hLRC = YWGUI_CTGetCtrlHandleById(hCT, IDC_LRC_IPTV_ADD_MEDIA_TYPE_R);
	pWebTvNode->mediatype= YWGUI_LRCBGetCurHotItemIndex(hLRC);

}


static void WebTvi_InitEditWindCtrl(YWGUI_HWnd_T hWnd, U32 EditIndex)
{

	YWGUI_Handle_T hCT = YWGUI_NULL_HANDLE;
	YWGUI_Handle_T hTXT = YWGUI_NULL_HANDLE;
	YWGUI_Handle_T hLRC = YWGUI_NULL_HANDLE;
	YWGUI_Char_T wstr[URL_LEN];
	YWGUI_LRCBListItem_T stLbItem;
	YW_WEBTV_Node_t  *pWebTvNode = NULL;

	pWebTvNode = WebTvi_GetOneNodeByIndex(EditIndex);

	//title
	YWLIB_Memset(wstr, 0x0, sizeof(wstr));
	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_IPTV_ADD_TV_TITLE);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_TITLE_L);
	YWGUI_StaticSetXOffset(hTXT, 30);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_TITLE_R);
	YWPUBLIC_Utf8To16((S8 *)pWebTvNode->title,
			YWLIB_Strlen((S8 *)pWebTvNode->title)+1,
                        (S8*)wstr, sizeof(wstr));
	YWGUI_SetWindowText(hTXT, wstr);

	//url
	YWLIB_Memset(wstr, 0x0, sizeof(wstr));
	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_IPTV_ADD_TV_URL);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_URL_L);
	YWGUI_StaticSetXOffset(hTXT, 30);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_URL_R);
	YWPUBLIC_Utf8To16((S8 *)pWebTvNode->url,
			YWLIB_Strlen((S8 *)pWebTvNode->url)+1,
                        (S8*)wstr, sizeof(wstr));
	YWGUI_SetWindowText(hTXT, wstr);

	//description
	YWLIB_Memset(wstr, 0x0, sizeof(wstr));
	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_IPTV_ADD_TV_DESCRIPTION);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_DESCRIPTION_L);
	YWGUI_StaticSetXOffset(hTXT, 30);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_DESCRIPTION_R);
	YWPUBLIC_Utf8To16((S8 *)pWebTvNode->description,
			YWLIB_Strlen((S8 *)pWebTvNode->description)+1,
                        (S8*)wstr, sizeof(wstr));
	YWGUI_SetWindowText(hTXT, wstr);

	//media type
	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_IPTV_ADD_MEDIA_TYPE);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_MEDIA_TYPE_L);
	YWGUI_StaticSetXOffset(hTXT, 30);
	stLbItem.dwFlags = 0;
    stLbItem.dwAddData = 0;
    stLbItem.dwImage = 0;
	hLRC = YWGUI_CTGetCtrlHandleById(hCT, IDC_LRC_IPTV_ADD_MEDIA_TYPE_R);
	YWGUI_LRCBSetListVisibleCount(hLRC, 2);
    stLbItem.pszText = YWSTR_GetString(STR_FILE);
    YWGUI_LRCBAddItem(hLRC, &stLbItem);
    stLbItem.pszText = YWSTR_GetString(STR_LIVE);
    YWGUI_LRCBAddItem(hLRC, &stLbItem);
	YWGUI_LRCBSetCurHotItemIndex(hLRC, pWebTvNode->mediatype);

}

//
static S32 WebTvi_EditWndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
{
    switch (message)
    {
        case YWGUI_MSG_NCCREATE:
        {
            YWGUI_SetWEColor(hWnd, YWGUI_MAINWND_BGC, Color_black);
            break;
        }

        case YWGUI_MSG_INITDIALOG:
		{
			U32 EditIndex = (U32)lParam;
			YWGUI_SetWindowAdditionalData(hWnd, EditIndex);
			WebTvi_InitEditWindCtrl(hWnd, EditIndex);
    	}
            return 0;
		case YWPUBLIC_MSG_RENAME:
		{
			if(lParam)
			{
				S8 url[URL_LEN];
				YWGUI_Handle_T hCT= YWGUI_NULL_HANDLE;
				YWGUI_Handle_T hTXT = YWGUI_NULL_HANDLE;

				hCT = YWGUI_GetFocus(hWnd);
				if(YWGUI_GetDlgCtrlID(hCT) == IDC_CTN_IPTV_ADD_TV_TITLE)
				{
					hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_TITLE_R);
				}
				else if(YWGUI_GetDlgCtrlID(hCT) == IDC_CTN_IPTV_ADD_TV_URL)
				{
					YWLIB_Memset(url, 0, sizeof(url));
					YWPUBLIC_Utf16To8((S8*)wParam,
                    	(YWLIB_Wstrlen((YWLIB_WChar_T*)wParam)+1)*sizeof(YWLIB_WChar_T),
                    	url, sizeof(url));
					if(WebTvi_IsUrlValid(url))
					{
						hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_URL_R);
					}
					else
					{
						YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_INDEX), 3000);
						break;
					}
				}
				else if(YWGUI_GetDlgCtrlID(hCT) == IDC_CTN_IPTV_ADD_TV_DESCRIPTION)
				{
					hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_DESCRIPTION_R);
				}
				YWGUI_SetWindowText(hTXT, (YWGUI_Char_T*)wParam);
			}
		}
			break;
        case YWGUI_MSG_COMMAND:
        {
			U16 id = (U16)YWGUI_LOWORD (wParam);
            U16 notifyCode= (U16)YWGUI_HIWORD (wParam);
			YWGUI_Handle_T hDlg = YWGUI_NULL_HANDLE;
            if(notifyCode == YWGUI_NONE_CODE)
            {
                if(id == IDC_BTN_IPTV_ADD)   //save edit
                {
					WebTvi_SaveEditWindCtrl(hWnd, YWGUI_GetWindowAdditionalData(hWnd));

					hDlg = YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_SAVING_DATA), 0xffff);

					YWGUI_UpdateWindow(hDlg);

					if(WebTvi_SaveXmlFile() == -1)
					{
						//save xml file failed
						hDlg = YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_SAVE_FAIL), 2000);
						YWGUI_UpdateWindow(hDlg);
					}
					else
					{
						//save xml file success
						hDlg = YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_SAVE_SUC), 2000);
						YWGUI_UpdateWindow(hDlg);
					}
					YWOS_TaskSleep(1500);
               		YWGUI_PostMessage(YWGUI_GetHosting(hWnd), YWPUBLIC_MSG_WEBTV_LIST_REFRESH, 0, 0);
                }
				else if(id == IDC_BTN_IPTV_DELETE)    //delete
				{
					S32 ret = -1;
					//isDelLastOne = WebTv_DelOneItem(YWGUI_GetWindowAdditionalData(hWnd));
					ret = WebTvi_DelOneNodeByIndex(YWGUI_GetWindowAdditionalData(hWnd));
					if(ret == -1)
					{
						YWGUI_SendMessage(hWnd, YWGUI_MSG_CLOSE, 0, 0);
						break;
					}
					g_WebTvInfo.num--;

					hDlg = YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_SAVING_DATA), 0xffff);
					YWGUI_UpdateWindow(hDlg);

					if(WebTvi_SaveXmlFile() == -1)
					{
						//save xml file failed
						hDlg = YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_SAVE_FAIL), 2000);
						YWGUI_UpdateWindow(hDlg);
					}
					else
					{
						//save xml file success
						hDlg = YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_SAVE_SUC), 2000);
						YWGUI_UpdateWindow(hDlg);
					}
					YWOS_TaskSleep(1500);
					YWGUI_PostMessage(YWGUI_GetHosting(hWnd), YWPUBLIC_MSG_WEBTV_LIST_REFRESH, 2, 0);
				}
                else if(id == IDC_BTN_IPTV_EXIT)
                {
                    ;
                }
				YWGUI_SendMessage(hWnd, YWGUI_MSG_CLOSE, 0, 0);
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
					break;

                case YWGUI_SCANCODE_UP:
                case YWGUI_SCANCODE_DOWN:
                    break;

                case YWGUI_SCANCODE_OK:
				{
					YWGUI_Handle_T hFocus = YWGUI_GetFocus(hWnd);
					YWGUI_Char_T wstr[URL_LEN];
					YWPLUGINREAME_Param_T RenameParam;

					if(YWGUI_GetDlgCtrlID(hFocus) == IDC_CTN_IPTV_ADD_TV_TITLE)
					{
						YWGUI_GetWindowText(YWGUI_CTGetCtrlHandleById(hFocus, IDC_TXT_IPTV_ADD_TV_TITLE_R), wstr, sizeof(wstr));

						RenameParam.hHosting = hWnd;
                        RenameParam.pStrContent = wstr;
                        RenameParam.nEditLimitLen = TITLE_LEN-1;
						RenameParam.pStrTitle = NULL;
                        YWPlugin_CreateRenameWindow(&RenameParam);
						
					}
					else if(YWGUI_GetDlgCtrlID(hFocus) == IDC_CTN_IPTV_ADD_TV_URL)
					{
						YWGUI_GetWindowText(YWGUI_CTGetCtrlHandleById(hFocus, IDC_TXT_IPTV_ADD_TV_URL_R), wstr, sizeof(wstr));

						RenameParam.hHosting = hWnd;
                        RenameParam.pStrContent = wstr;
                        RenameParam.nEditLimitLen = URL_LEN-1;
						RenameParam.pStrTitle = NULL;
                        YWPlugin_CreateRenameWindow(&RenameParam);
					}
					else if(YWGUI_GetDlgCtrlID(hFocus) == IDC_CTN_IPTV_ADD_TV_DESCRIPTION)
					{
						YWGUI_GetWindowText(YWGUI_CTGetCtrlHandleById(hFocus, IDC_TXT_IPTV_ADD_TV_DESCRIPTION_R), wstr, sizeof(wstr));

						RenameParam.hHosting = hWnd;
                        RenameParam.pStrContent = wstr;
                        RenameParam.nEditLimitLen = DESCRIPTION_LEN-1;
						RenameParam.pStrTitle = NULL;
                        YWPlugin_CreateRenameWindow(&RenameParam);
					}
                }
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



static YWGUI_HWnd_T WebTvi_CreateEditItemWindow(YWGUI_HWnd_T hHost, U32 index)
{
    YWGUI_HWnd_T hWebTvEdit = YWGUI_NULL_HANDLE;
    YW_ErrorType_T Error = YW_NO_ERROR;

    Error = YWGUI_CreateDialog(IDD_IPTV_EDIT, hHost, WebTvi_EditWndProc, (LPARAM)index, &hWebTvEdit);

    return (YW_NO_ERROR == Error) ? hWebTvEdit : YWGUI_NULL_HANDLE;
}

#define ADD_WEBTV_DATA


static S32 WebTvi_AddItem(YWGUI_Handle_T hWnd)
{
	YWGUI_Handle_T hCT = YWGUI_NULL_HANDLE;
	YWGUI_Handle_T hTXT = YWGUI_NULL_HANDLE;
	YWGUI_Handle_T hLRC = YWGUI_NULL_HANDLE;
	char title[TITLE_LEN];
	char url[URL_LEN];
	char description[DESCRIPTION_LEN];
	//char username[USRNAME_LEN];
	//char psw[PSW_LEN];
	char mediatype = 0;
	//char account = 0;
	YWLIB_WChar_T wstr[URL_LEN];
	YW_WEBTV_Node_t *pwebTvNode = NULL;

	YWLIB_Memset(title, 0, sizeof(title));
	YWLIB_Memset(url, 0, sizeof(url));
	YWLIB_Memset(description, 0, sizeof(description));
//	YWLIB_Memset(username, 0, sizeof(username));
//	YWLIB_Memset(psw, 0, sizeof(psw));

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_IPTV_ADD_TV_TITLE);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_TITLE_R);
	YWGUI_GetWindowText(hTXT, wstr, sizeof(wstr));
	YWPUBLIC_Utf16To8((S8*)wstr,
                    (YWLIB_Wstrlen(wstr)+1)*sizeof(YWLIB_WChar_T),
                    (S8*)title,
                    sizeof(title));

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_IPTV_ADD_TV_URL);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_URL_R);
	YWGUI_GetWindowText(hTXT, wstr, sizeof(wstr));
	YWPUBLIC_Utf16To8((S8*)wstr,
                    (YWLIB_Wstrlen(wstr)+1)*sizeof(YWLIB_WChar_T),
                    (S8*)url,
                    sizeof(url));

	YWLIB_Memset(wstr, 0, sizeof(wstr));
	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_IPTV_ADD_TV_DESCRIPTION);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_DESCRIPTION_R);
	YWGUI_GetWindowText(hTXT, wstr, sizeof(wstr));
	YWPUBLIC_Utf16To8((S8*)wstr,
                    (YWLIB_Wstrlen(wstr)+1)*sizeof(YWLIB_WChar_T),
                    (S8*)description,
                    sizeof(description));



	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_IPTV_ADD_MEDIA_TYPE);
	hLRC = YWGUI_CTGetCtrlHandleById(hCT, IDC_LRC_IPTV_ADD_MEDIA_TYPE_R);
	mediatype = YWGUI_LRCBGetCurHotItemIndex(hLRC);

	pwebTvNode = (YW_WEBTV_Node_t *)malloc(sizeof(YW_WEBTV_Node_t));
	if(pwebTvNode == NULL)
	{
		printf("YWAPP_Calloc failed\n");
		return -1;
	}
	YWLIB_Memset(pwebTvNode, 0, sizeof(YW_WEBTV_Node_t));
	YWLIB_Strcpy((S8*)pwebTvNode->title, (const S8*)title);
	YWLIB_Strcpy((S8*)pwebTvNode->url, (const S8*)url);
	YWLIB_Strcpy((S8*)pwebTvNode->description, (const S8*)description);
	pwebTvNode->mediatype = mediatype;
	WebTvi_AddOneNode(pwebTvNode);
	g_WebTvInfo.num++;

	return 0;
}


static void WebTvi_InitAddWindCtrl(YWGUI_HWnd_T hWnd)
{
	YWGUI_Handle_T hCT = YWGUI_NULL_HANDLE;
	YWGUI_Handle_T hTXT = YWGUI_NULL_HANDLE;
	YWGUI_Handle_T hLRC = YWGUI_NULL_HANDLE;
	YWGUI_LRCBListItem_T stLbItem;

	//title
	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_IPTV_ADD_TV_TITLE);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_TITLE_L);
	YWGUI_StaticSetXOffset(hTXT, 30);

	//url
	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_IPTV_ADD_TV_URL);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_URL_L);
	YWGUI_StaticSetXOffset(hTXT, 30);

	//description
	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_IPTV_ADD_TV_DESCRIPTION);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_DESCRIPTION_L);
	YWGUI_StaticSetXOffset(hTXT, 30);

	//media type
	stLbItem.dwFlags = 0;
    stLbItem.dwAddData = 0;
    stLbItem.dwImage = 0;
	hCT = YWGUI_GetDlgItem(hWnd, IDC_CTN_IPTV_ADD_MEDIA_TYPE);
	hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_MEDIA_TYPE_L);
	YWGUI_StaticSetXOffset(hTXT, 30);
	hLRC = YWGUI_CTGetCtrlHandleById(hCT, IDC_LRC_IPTV_ADD_MEDIA_TYPE_R);
	YWGUI_LRCBSetListVisibleCount(hLRC, 2);

    stLbItem.pszText = YWSTR_GetString(STR_FILE);
    YWGUI_LRCBAddItem(hLRC, &stLbItem);

    stLbItem.pszText = YWSTR_GetString(STR_LIVE);
    YWGUI_LRCBAddItem(hLRC, &stLbItem);
	YWGUI_LRCBSetCurHotItemIndex(hLRC, 0);

}


static S32 YWWEBTVi_AddWndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
{
    switch (message)
    {
        case YWGUI_MSG_NCCREATE:
        {
            YWGUI_SetWEColor(hWnd, YWGUI_MAINWND_BGC, Color_black);
            break;
        }

        case YWGUI_MSG_INITDIALOG:
		{
			WebTvi_InitAddWindCtrl(hWnd);
    	}
            return 0;
		case YWPUBLIC_MSG_RENAME:
		{
			if(lParam)
			{
				S8 url[URL_LEN];
				YWGUI_Handle_T hCT= YWGUI_NULL_HANDLE;
				YWGUI_Handle_T hTXT = YWGUI_NULL_HANDLE;

				hCT = YWGUI_GetFocus(hWnd);
				if(YWGUI_GetDlgCtrlID(hCT) == IDC_CTN_IPTV_ADD_TV_TITLE)
				{
					hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_TITLE_R);
				}
				else if(YWGUI_GetDlgCtrlID(hCT) == IDC_CTN_IPTV_ADD_TV_URL)
				{
					YWLIB_Memset(url, 0, sizeof(url));
					YWPUBLIC_Utf16To8((S8*)wParam,
                    	(YWLIB_Wstrlen((YWLIB_WChar_T*)wParam)+1)*sizeof(YWLIB_WChar_T),
                    	url, sizeof(url));
					if(WebTvi_IsUrlValid(url))
					{
						hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_URL_R);
					}
					else
					{
						YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_INVALID_URL), 3000);
						break;
					}
				}
				else if(YWGUI_GetDlgCtrlID(hCT) == IDC_CTN_IPTV_ADD_TV_DESCRIPTION)
				{
					hTXT = YWGUI_CTGetCtrlHandleById(hCT, IDC_TXT_IPTV_ADD_TV_DESCRIPTION_R);
				}
				
				YWGUI_SetWindowText(hTXT, (YWGUI_Char_T*)wParam);
			}
		}
			break;
        case YWGUI_MSG_COMMAND:
        {
			U16 id = (U16)YWGUI_LOWORD (wParam);
            U16 notifyCode= (U16)YWGUI_HIWORD (wParam);
            if(notifyCode == YWGUI_NONE_CODE)
            {
                if(id == IDC_BTN_IPTV_ADD)
                {
                	if(WebTvi_AddItem(hWnd) == 0)
                   	{
                   		//add success
						YWGUI_Handle_T hDlg = YWGUI_NULL_HANDLE;
						hDlg = YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_SAVING_DATA), 0xffff);

						YWGUI_UpdateWindow(hDlg);

						if(WebTvi_SaveXmlFile() == -1)
						{
							//save xml file failed
							hDlg = YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_SAVE_FAIL), 2000);

							YWGUI_UpdateWindow(hDlg);
						}
						else
						{
							//save xml file success
							hDlg = YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_SAVE_SUC), 2000);
							YWGUI_UpdateWindow(hDlg);
						}
						YWOS_TaskSleep(1500);
                   		YWGUI_PostMessage(YWGUI_GetHosting(hWnd), YWPUBLIC_MSG_WEBTV_LIST_REFRESH, 1, 0);
                   		YWGUI_SendMessage(hWnd, YWGUI_MSG_CLOSE, 0, 0);
                   	}
				   	else
					{
						//add failed
					//	YWGUI_Char_T wstr[URL_LEN];
						YWGUI_Handle_T hDlg = YWGUI_NULL_HANDLE;

					//	YWLIB_Memset(wstr, 0, sizeof(wstr));
					//	YWLIB_Astr2wstr(wstr, (S8 *)"Add IPTv failed!");   //need make string to ywstring.c
						//hDlg = YWGENERAL_DispInfoForMoment2(hWnd, YWSTR_GetString(STR_INFORMATION), wstr, 3000);
						hDlg = YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_INDEX), 2000);

						YWGUI_UpdateWindow(hDlg);
				   	}
                }
                else if(id == IDC_BTN_IPTV_EXIT)
                {
                    YWGUI_SendMessage(hWnd, YWGUI_MSG_CLOSE, 0, 0);
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
					break;

                case YWGUI_SCANCODE_UP:
                case YWGUI_SCANCODE_DOWN:
                    break;

                case YWGUI_SCANCODE_OK:
				{
					YWGUI_Handle_T hFocus = YWGUI_GetFocus(hWnd);
					YWGUI_Char_T wstr[URL_LEN];
					YWPLUGINREAME_Param_T RenameParam;

					if(YWGUI_GetDlgCtrlID(hFocus) == IDC_CTN_IPTV_ADD_TV_TITLE)
					{
						YWGUI_GetWindowText(YWGUI_CTGetCtrlHandleById(hFocus, IDC_TXT_IPTV_ADD_TV_TITLE_R), wstr, sizeof(wstr));

						RenameParam.hHosting = hWnd;
						RenameParam.pStrContent = wstr;
						RenameParam.nEditLimitLen = TITLE_LEN-1;
						RenameParam.pStrTitle = NULL;
						YWPlugin_CreateRenameWindow(&RenameParam);
					}
					else if(YWGUI_GetDlgCtrlID(hFocus) == IDC_CTN_IPTV_ADD_TV_URL)
					{
						YWGUI_GetWindowText(YWGUI_CTGetCtrlHandleById(hFocus, IDC_TXT_IPTV_ADD_TV_URL_R), wstr, sizeof(wstr));

						RenameParam.hHosting = hWnd;
                        RenameParam.pStrContent = wstr;
                        RenameParam.nEditLimitLen = URL_LEN-1;
						RenameParam.pStrTitle = NULL;
                        YWPlugin_CreateRenameWindow(&RenameParam);
					}
					else if(YWGUI_GetDlgCtrlID(hFocus) == IDC_CTN_IPTV_ADD_TV_DESCRIPTION)
					{
						YWGUI_GetWindowText(YWGUI_CTGetCtrlHandleById(hFocus, IDC_TXT_IPTV_ADD_TV_DESCRIPTION_R), wstr, sizeof(wstr));

						RenameParam.hHosting = hWnd;
						RenameParam.pStrContent = wstr;
						RenameParam.nEditLimitLen = DESCRIPTION_LEN-1;
						RenameParam.pStrTitle = NULL;
						YWPlugin_CreateRenameWindow(&RenameParam);
					}
					
                }
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



static YWGUI_HWnd_T YWWEBTVi_CreateAddItemWindow(YWGUI_HWnd_T hHost)
{
    YWGUI_HWnd_T hWebTvAdd = YWGUI_NULL_HANDLE;
    YW_ErrorType_T Error = YW_NO_ERROR;

    Error = YWGUI_CreateDialog(IDD_IPTV_ADD, hHost, YWWEBTVi_AddWndProc, 0, &hWebTvAdd);

    return (YW_NO_ERROR == Error) ? hWebTvAdd : YWGUI_NULL_HANDLE;
}





#define _PLAY_WIN_


static void WebTvi_ShowPlayCtrl(YWGUI_HWnd_T hWnd, S32 iCmdShow)
{
    YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_BIG_PLAY), iCmdShow);
    YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_BIG_STOP), iCmdShow);
    YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_BIG_PAUSE), iCmdShow);
    YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_PROGRESS_IPTV_BIG), iCmdShow);
//    YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_BIG_PIP), iCmdShow);
}


static void WebTvi_ShowVolumeCtrl(YWGUI_HWnd_T hWnd, S32 iCmdShow)
{
    YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_IPTV_VOLUME_BK), iCmdShow);
    YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_PROGRRESS_IPTV_VOLUME), iCmdShow);
}



static void WebTvi_Volume(YWGUI_HWnd_T hWnd, WPARAM wParam)
{

    if (YWGUI_SCANCODE_VOL_UP == wParam)
    {
        if (g_WebTvvolume > 0)
        {
        	U32 tmpVol = g_WebTvvolume;
            WebTvi_SetVolume(g_PlayHandle, tmpVol - 1);
        }
    }
    else if (YWGUI_SCANCODE_VOL_DOWN == wParam)
    {
    	if (g_WebTvvolume < 20)
        {
        	U32 tmpVol = g_WebTvvolume;
            WebTvi_SetVolume(g_PlayHandle, tmpVol + 1);
        }
    }

    YWGUI_SetProgressBarPosVal(YWGUI_GetDlgItem(hWnd, IDC_PROGRRESS_IPTV_VOLUME), g_WebTvvolume*22);

	WebTvi_ShowVolumeCtrl(hWnd, YWGUI_SW_SHOW);
    YWGUI_ResetTimer(hWnd, TIMER_WEBTV_VOLUME, 3000);
}


static void WebTvi_DrawBigPlayCtrl(YWGUI_HWnd_T hWnd)
{
	if(g_WebTvPlayStatus == WEBTV_PLAY)
	{
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_BIG_PLAY), &g_aIpTvGraphCellArray[YWCELL_PLAYER_CUR_PLAY], TRUE);
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_BIG_STOP), &g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_STOP], TRUE);
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_BIG_PAUSE), &g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_PAUSE], TRUE);
	}
	else if(g_WebTvPlayStatus == WEBTV_STOP)
	{
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_BIG_PLAY), &g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_PLAY], TRUE);
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_BIG_STOP), &g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_STOP], TRUE);
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_BIG_PAUSE), &g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_PAUSE], TRUE);
	}
	else if(g_WebTvPlayStatus == WEBTV_PAUSE)
	{
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_BIG_PLAY), &g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_PLAY], TRUE);
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_BIG_STOP), &g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_STOP], TRUE);
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_BIG_PAUSE), &g_aIpTvGraphCellArray[YWCELL_PLAYER_CUR_PAUSE], TRUE);
	}
}



static S32 YWWEBTV_PlayWndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
{
    switch (message)
    {
        case YWGUI_MSG_NCCREATE:
        {
            YWGUI_SetWEColor(hWnd, YWGUI_MAINWND_BGC, Color_transparency);
            break;
        }

        case YWGUI_MSG_INITDIALOG:
		{
			YWGUI_HWnd_T hDlg;

			WebTvi_SetVideoOutWindow(g_PlayHandle, FALSE);

			WebTvi_DrawBigPlayCtrl(hWnd);
			WebTvi_ShowPlayCtrl(hWnd, YWGUI_SW_SHOW);
			WebTvi_ShowVolumeCtrl(hWnd, YWGUI_SW_HIDE);

            hDlg = YWGUI_GetDlgItem(hWnd, IDC_PROGRRESS_IPTV_VOLUME);
            YWGUI_SetProgressBarRange(hDlg, 440);
            YWGUI_SetProgressBarStepSize(hDlg, 22, 22);
            YWGUI_SetProgressBarPosVal(hDlg, g_WebTvvolume*22);

			if(g_WebTvPlayStatus == WEBTV_PLAY)
			{
				YWGUI_SetTimer(hWnd, TIMER_WEBTV_PLAY_PROGRESS, 1000);
			}
			YWGUI_SetTimer(hWnd, TIMER_WEBTV_INFO, 5000);
			YWGUI_SetTimer(hWnd, TIMER_WEBTV_VOLUME, 3000);
    	}
            break;

		case YWGUI_MSG_TIMER:
        {
            switch((S32)wParam)
            {
                case TIMER_WEBTV_INFO:
                {
                    YWGUI_KillTimer(hWnd, TIMER_WEBTV_INFO);
					YWGUI_KillTimer(hWnd, TIMER_WEBTV_PLAY_PROGRESS);
                    WebTvi_ShowPlayCtrl(hWnd, YWGUI_SW_HIDE);
                    break;
                }
                case TIMER_WEBTV_PLAY_PROGRESS:
                {
					
                   	U32 duration;
					U32 pos;

                    if (YW_NO_ERROR != YWNATIVE_AvGetDuration(g_PlayHandle, &duration))
                    {
                        printf("Get duration Failed!\n");
                        return -1;
                    }
					if (YW_NO_ERROR != YWNATIVE_AvGetPos(g_PlayHandle, &pos))
                    {
                        printf("Get pos Failed!\n");
                        return -1;
                    }
					
					if(duration == 0)
					{
						YWGUI_SetProgressBarPosVal(YWGUI_GetDlgItem(hWnd, IDC_PROGRESS_IPTV_BIG),0);
					}
					else
					{
                    	YWGUI_SetProgressBarPosVal(YWGUI_GetDlgItem(hWnd, IDC_PROGRESS_IPTV_BIG),
                        	(pos * 100) / duration);
					}
                    break;
                }
                case TIMER_WEBTV_VOLUME:
                {
                    YWGUI_KillTimer(hWnd, TIMER_WEBTV_VOLUME);
                    WebTvi_ShowVolumeCtrl(hWnd, YWGUI_SW_HIDE);
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }

		case YWPUBLIC_MSG_END_OF_FILE:
		{
			printf("-----------------YWPUBLIC_MSG_END_OF_FILE!\n--------");
			if(YWGUI_GetMainWinById(IDD_WAIT) != YWGUI_NULL_HANDLE)
			{
				YWGUI_SendMessage(YWGUI_GetMainWinById(IDD_WAIT), YWGUI_MSG_CLOSE, 0, 0);
			}
			g_WebTvPlayStatus = WEBTV_STOP;
			YWGUI_SendMessage(hWnd, YWGUI_MSG_KEYDOWN, YWGUI_SCANCODE_EXIT, 0);
		}
			break;

		case YWPUBLIC_MSG_START_WAIT:
        {
            WAIT_CreateWnd(hWnd);
            break;
        }

		case YWPUBLIC_MSG_WEBTV_PLAY:
		{
			YW_ErrorType_T retCode = (YW_ErrorType_T)wParam;
			if(retCode == YW_NO_ERROR)
			{
				g_WebTvPlayStatus = WEBTV_PLAY;
				WebTvi_DrawBigPlayCtrl(hWnd);
				WebTvi_ShowPlayCtrl(hWnd, YWGUI_SW_SHOW);
                YWGUI_ResetTimer(hWnd, TIMER_WEBTV_INFO, 5000);
				YWGUI_ResetTimer(hWnd, TIMER_WEBTV_PLAY_PROGRESS, 1000);
				YWGUI_SendMessage(YWGUI_GetMainWinById(IDD_WAIT), YWGUI_MSG_CLOSE, 0, 0);
			}
			else
			{
				g_WebTvPlayStatus = WEBTV_STOP;
				WebTvi_DrawBigPlayCtrl(hWnd);
				WebTvi_ShowPlayCtrl(hWnd, YWGUI_SW_SHOW);
				YWGUI_ResetTimer(hWnd, TIMER_WEBTV_INFO, 5000);
				YWGUI_SendMessage(YWGUI_GetMainWinById(IDD_WAIT), YWGUI_MSG_CLOSE, 0, 0);
				YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_START_PLAY_FAILED), 2000);
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
					WebTvi_SetVideoOutWindow(g_PlayHandle, TRUE);
					YWGUI_PostMessage(YWGUI_GetHosting(hWnd), YWPUBLIC_MSG_WEBTV_EXIT_BIG, 0, 0);
                    YWGUI_SendMessage(hWnd, YWGUI_MSG_CLOSE, 0, 0);
                }
                    break;

                case YWGUI_SCANCODE_LEFT:
                case YWGUI_SCANCODE_VOL_UP:
                case YWGUI_SCANCODE_RIGHT:
                case YWGUI_SCANCODE_VOL_DOWN:
				{
                    if (YWGUI_SCANCODE_RIGHT == wParam)
                    {
                        wParam = YWGUI_SCANCODE_VOL_DOWN;
                    }
                    else if (YWGUI_SCANCODE_LEFT == wParam)
                    {
                        wParam = YWGUI_SCANCODE_VOL_UP;
                    }
                    WebTvi_Volume(hWnd, wParam);
                }
					break;

                case YWGUI_SCANCODE_UP:
                case YWGUI_SCANCODE_DOWN:
                    break;

                case YWGUI_SCANCODE_INFO:
				{
					WebTvi_ShowPlayCtrl(hWnd, YWGUI_SW_SHOW);
                    YWGUI_ResetTimer(hWnd, TIMER_WEBTV_INFO, 5000);
                    if(g_WebTvPlayStatus == WEBTV_PLAY)
					{
						YWGUI_ResetTimer(hWnd, TIMER_WEBTV_PLAY_PROGRESS, 1000);
					}
                }
                    break;

				case YWGUI_SCANCODE_PLAY:
				{
					if(g_WebTvPlayStatus == WEBTV_STOP || g_WebTvPlayStatus == WEBTV_PAUSE)
					{
						if(g_WebTvPlayStatus == WEBTV_PAUSE)
						{
							if(YW_NO_ERROR == WebTvi_ResumePlay(g_PlayHandle))
							{
								g_WebTvPlayStatus = WEBTV_PLAY;
								WebTvi_DrawBigPlayCtrl(hWnd);
								WebTvi_ShowPlayCtrl(hWnd, YWGUI_SW_SHOW);
			                    YWGUI_ResetTimer(hWnd, TIMER_WEBTV_INFO, 5000);
								YWGUI_ResetTimer(hWnd, TIMER_WEBTV_PLAY_PROGRESS, 1000);
							}
							else
							{
								YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_START_PLAY_FAILED), 2000);
							}
						}
						else if(g_WebTvPlayStatus == WEBTV_STOP)
						{
							S8 url[URL_LEN];

							YWLIB_Memset(url, 0, sizeof(url));
							YWLIB_Strcpy(url, (S8*)g_pCurPlayWebTvInfo->url);

							if(WebTvi_IsUrlValid(url))
							{
								YWGUI_SendMessage(hWnd, YWPUBLIC_MSG_START_WAIT, 0, 0);
								WebTvi_StartPlay(g_PlayHandle, (U8 *)g_pCurPlayWebTvInfo->url);
							}
							else
							{
								YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_INVALID_URL), 2000);
							}
						}
					}
				}
					break;
				case YWGUI_SCANCODE_STOP:
				{
					if(g_WebTvPlayStatus == WEBTV_PLAY || g_WebTvPlayStatus == WEBTV_PAUSE)
					{
						g_WebTvPlayStatus = WEBTV_STOP;
						WebTvi_StopPlay(g_PlayHandle);
						WebTvi_DrawBigPlayCtrl(hWnd);
						WebTvi_ShowPlayCtrl(hWnd, YWGUI_SW_SHOW);
	                    YWGUI_ResetTimer(hWnd, TIMER_WEBTV_INFO, 5000);
						YWGUI_KillTimer(hWnd, TIMER_WEBTV_PLAY_PROGRESS);
						YWGUI_SendMessage(hWnd, YWGUI_MSG_KEYDOWN, YWGUI_SCANCODE_EXIT, 0);
					}
				}
					break;
				case YWGUI_SCANCODE_PAUSE:
				{
					if(g_WebTvPlayStatus == WEBTV_PLAY)
					{
						g_WebTvPlayStatus = WEBTV_PAUSE;
						WebTvi_PausePlay(g_PlayHandle);
						WebTvi_DrawBigPlayCtrl(hWnd);
						WebTvi_ShowPlayCtrl(hWnd, YWGUI_SW_SHOW);
	                    YWGUI_ResetTimer(hWnd, TIMER_WEBTV_INFO, 5000);
						YWGUI_KillTimer(hWnd, TIMER_WEBTV_PLAY_PROGRESS);
					}
				}
					break;


                default:
                    break;
            }
		}
            break;


        case YWGUI_MSG_CLOSE:
            break;

        case YWGUI_MSG_DESTROY:
		{
			YWGUI_KillTimer(hWnd, TIMER_WEBTV_INFO);
			YWGUI_KillTimer(hWnd, TIMER_WEBTV_PLAY_PROGRESS);
			YWGUI_KillTimer(hWnd, TIMER_WEBTV_VOLUME);
        }
            break;

        default:
            break;
    }

    return YWGUI_DefaultDialogProc(hWnd,message,wParam,lParam);
}



static YWGUI_HWnd_T YWWEBTV_CreatePlayWindow(YWGUI_HWnd_T hHost)
{
    YWGUI_HWnd_T hWnd = YWGUI_GetMainWinById(IDD_IPTV_PLAY);
    YW_ErrorType_T Error = YW_NO_ERROR;

    if (YWGUI_NULL_HANDLE == hWnd)
    {
        Error = YWGUI_CreateDialog(IDD_IPTV_PLAY, hHost, YWWEBTV_PlayWndProc, 0, &hWnd);
    }
    else if (!YWGUI_IsWindowVisible(hWnd))
    {
        YWGUI_ShowWindow(hWnd, YWGUI_SW_SHOW);
    }

    return (YW_NO_ERROR == Error) ? hWnd : YWGUI_NULL_HANDLE;
}





#define _MAIN_WIN_



static void WebTvi_RefreshPlayCtrl(YWGUI_HWnd_T hWnd)
{
	if(g_WebTvPlayStatus == WEBTV_PLAY)
	{
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_SMALL_PLAY), &g_aIpTvGraphCellArray[YWCELL_PLAYER_CUR_PLAY], TRUE);
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_SMALL_STOP), &g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_STOP], TRUE);
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_SMALL_PAUSE), &g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_PAUSE], TRUE);
	}
	else if(g_WebTvPlayStatus == WEBTV_STOP)
	{
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_SMALL_PLAY), &g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_PLAY], TRUE);
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_SMALL_STOP), &g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_STOP], TRUE);
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_SMALL_PAUSE), &g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_PAUSE], TRUE);
	}
	else if(g_WebTvPlayStatus == WEBTV_PAUSE)
	{
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_SMALL_PLAY), &g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_PLAY], TRUE);
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_SMALL_STOP), &g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_STOP], TRUE);
		YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_SMALL_PAUSE), &g_aIpTvGraphCellArray[YWCELL_PLAYER_CUR_PAUSE], TRUE);
	}
}


static void WebTvi_RefreshPage(YWGUI_HWnd_T hWnd, S32 iFocusIndex)
{
	YWLIB_WChar_T awstr[256];
	YWLIB_WChar_T wstr[256];
	int pagenumber = 0;

	YWLIB_Memset(awstr, 0x0, sizeof(awstr));
	YWLIB_Memset(wstr, 0x0, sizeof(wstr));
	YWLIB_Wstrcpy(awstr, YWSTR_GetString(STR_ADD));
	if(g_WebTvInfo.num == 0)
	{
		YWLIB_SwprintfA(wstr, (const S8 *)" 001/001");
		YWLIB_Wstrcat(awstr, wstr);
		YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_IPTV_PAGE), awstr);

		return ;
	}

	if(g_WebTvInfo.num%LIST_PAGE_NUM == 0)
	{
		pagenumber = g_WebTvInfo.num/LIST_PAGE_NUM;
	}
	else
	{
		pagenumber = g_WebTvInfo.num/LIST_PAGE_NUM + 1;
	}
	YWLIB_SwprintfA(wstr, (const S8 *)" %03d/%03d", (iFocusIndex/LIST_PAGE_NUM + 1), pagenumber);
	YWLIB_Wstrcat(awstr, wstr);
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_IPTV_PAGE), wstr);

}


static void WebTvi_RefreshPlayInfo(YWGUI_HWnd_T hWnd, S32 index)
{
	YWGUI_Char_T wstr[256];
	YW_WEBTV_Node_t  *pWebTvNode = NULL;

	if(index == -1 )
		return;

	pWebTvNode = WebTvi_GetOneNodeByIndex(index);

	YWLIB_Memset(wstr, 0x0, sizeof(wstr));
	YWPUBLIC_Utf8To16((S8 *)pWebTvNode->title, YWLIB_Strlen((S8 *)pWebTvNode->title)+1,
                        (S8*)wstr, sizeof(wstr));
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_IPTV_INFO_TITLE), wstr);

	YWLIB_Memset(wstr, 0x0, sizeof(wstr));
	YWPUBLIC_Utf8To16((S8 *)pWebTvNode->description, YWLIB_Strlen((S8 *)pWebTvNode->description)+1,
                        (S8*)wstr, sizeof(wstr));
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_IPTV_INFO_DETAIL), wstr);

}

static void WebTvi_RestartPlay(YWGUI_HWnd_T hWnd)
{
	S8 url[URL_LEN];

	YWLIB_Memset(url, 0, sizeof(url));
	YWLIB_Strcpy(url, (S8 *)g_pCurPlayWebTvInfo->url);

	if(WebTvi_IsUrlValid(url))
	{
		YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_IPTV_SMALLWIN), TRUE);
		YWGUI_SendMessage(hWnd, YWPUBLIC_MSG_START_WAIT, 0, 0);
		WebTvi_StartPlay(g_PlayHandle, (U8 *)g_pCurPlayWebTvInfo->url);
	}
	else
	{
		YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_INVALID_URL), 2000);
	}
}

static int WebTvi_PlayProc(YWGUI_HWnd_T hWnd, S32 iFocusIndex)
{
	g_pCurPlayWebTvInfo = WebTvi_GetOneNodeByIndex(iFocusIndex);

	if(g_WebTvPlayStatus == WEBTV_STOP)
	{
		WebTvi_RestartPlay(hWnd);
	}
	else if(g_WebTvPlayStatus == WEBTV_PAUSE)
	{
		if(iFocusIndex == g_CurPlayIndex)
		{
			//resume
			if(YW_NO_ERROR == WebTvi_ResumePlay(g_PlayHandle))
			{
				YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_IPTV_SMALLWIN), FALSE);
				g_WebTvPlayStatus = WEBTV_PLAY;
				WebTvi_RefreshPlayCtrl(hWnd);
				YWGUI_ResetTimer(hWnd, TIMER_WEBTV_REFRESH, 1000);
			}
			else
			{
				YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_IPTV_SMALLWIN), TRUE);
				YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_START_PLAY_FAILED), 2000);
			}
		}
		else
		{
			//restart play
			WebTvi_RestartPlay(hWnd);
		}
	}
	else if(g_WebTvPlayStatus == WEBTV_PLAY)
	{
		YWGUI_KillTimer(hWnd, TIMER_WEBTV_REFRESH);
		if(iFocusIndex == g_CurPlayIndex)
		{
			//enter fullscreen
			YWWEBTV_CreatePlayWindow(hWnd);
		}
		else
		{
			//restart play
			WebTvi_RestartPlay(hWnd);
		}
	}

	return 0;
}

static void WebTvi_StopProc(YWGUI_HWnd_T hWnd)
{
	YWGUI_KillTimer(hWnd, TIMER_WEBTV_REFRESH);
	g_WebTvPlayStatus = WEBTV_STOP;
	WebTvi_RefreshPlayCtrl(hWnd);
	YWGUI_SetProgressBarPosVal(YWGUI_GetDlgItem(hWnd, IDC_PROGRESS_IPTV_SMALL),0);
	YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_IPTV_SMALLWIN), TRUE);
	WebTvi_StopPlay(g_PlayHandle);
}

static void WebTvi_PauseProc(YWGUI_HWnd_T hWnd)
{
	YWGUI_KillTimer(hWnd, TIMER_WEBTV_REFRESH);
	g_WebTvPlayStatus = WEBTV_PAUSE;
	WebTvi_RefreshPlayCtrl(hWnd);
	WebTvi_PausePlay(g_PlayHandle);
}



static void WebTvi_WndMsgCommandProc(YWGUI_HWnd_T hWnd, WPARAM wParam, LPARAM lParam)
{
    U16 id = YWGUI_LOWORD(wParam);
    U16 notifyCode = YWGUI_HIWORD(wParam);
    YWGUI_HWnd_T hLT = YWGUI_NULL_HANDLE;

    switch (notifyCode)
    {
        case YWGUI_LTN_NEEDDATA:
        {
            U16 nStartIndex = YWGUI_LOWORD(lParam);
            U16 nEndIndex = YWGUI_HIWORD(lParam);
            U16 i;
            YWGUI_Char_T wStr[URL_LEN];
            YWGUI_LTItemInfo_T tItemInfo;

            switch (id)
            {
                case IDC_LT_IPTV:
                {
					YW_WEBTV_Node_t *pWebTvNode = NULL;

					hLT = YWGUI_GetDlgItem(hWnd, id);
                    for (i=nStartIndex; i<nEndIndex; i++)
                    {
                        pWebTvNode = WebTvi_GetOneNodeByIndex(i);

                        YWLIB_Memset(wStr, 0, sizeof(wStr));
                        YWLIB_SwprintfA(wStr, (const S8 *)" %04d", i+1);
                        tItemInfo.Type = YWGUI_LTINFO_TEXT;
                        tItemInfo.Info.pText = wStr;
                        YWGUI_LTSetItemInfo(hLT, i, 1, &tItemInfo);

                        tItemInfo.Type = YWGUI_LTINFO_TEXT;
						YWLIB_Memset(wStr, 0, sizeof(wStr));
						YWPUBLIC_Utf8To16((S8 *)pWebTvNode->title, YWLIB_Strlen((S8 *)pWebTvNode->title)+1,
                        			(S8*)wStr, sizeof(wStr));
                        tItemInfo.Info.pText = wStr;
                        YWGUI_LTSetItemInfo(hLT, i, 2, &tItemInfo);
                    }

					WebTvi_RefreshPage(hWnd, YWGUI_LTGetCurLine(hLT));
                    break;
                }

                default:
                {
                    break;
                }
            }
            break;
        }
        case YWGUI_LTN_CURCHANGE:
        {
            switch(id)
            {
                case IDC_LT_IPTV:
                {

					if(g_WebTvPlayStatus == WEBTV_STOP)
					{
						hLT = YWGUI_GetDlgItem(hWnd, id);
						g_FocusIndex = YWGUI_LTGetCurLine(hLT);
						WebTvi_RefreshPlayInfo(hWnd, g_FocusIndex);
					}
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        default:
        {
            break;
        }
    }
}



static int WebTvi_InitDataList(void)
{
 	mxml_node_t *webtv_xml = NULL;
 	mxml_node_t *webtvs = NULL;
	mxml_node_t *webtv = NULL;
	mxml_node_t *tmpnode = NULL;
	FILE *fp = NULL;
	int number =0;
	char path[256];
	YW_WEBTV_Node_t *pWebTvNode = NULL;

	WebTvi_ListInit();

	YWLIB_Memset(path, 0, sizeof(path));
	YWLIB_Snprintf((S8 *)path, sizeof((path)), (const S8*)"%s%s", WEBTV_XML_PATH, WEBTV_XML_FILE);
	fp = fopen(path, "r+");
   	if(NULL == fp)
    {
    	printf("open webtv.xml file fail!\n");
        return -1;
    }

	webtv_xml = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK);
	fclose(fp);
	if(webtv_xml == NULL)
	{
		printf("load webtv xml file fialed\n");
		return -1;
	}
	webtvs = mxmlFindElement(webtv_xml, webtv_xml,
                       	XML_ELEMENT_WEBTVS, NULL, NULL, MXML_DESCEND);
	if(webtvs == NULL)
	{
		printf("can not find webtvs!\n");
		return -1;
	}

    webtv = mxmlFindElement(webtvs, webtv_xml,
						XML_ELEMENT_WEBTV, NULL, NULL, MXML_DESCEND);

	while(webtv != NULL)
	{
		if(webtv->type != MXML_ELEMENT)
		{
			tmpnode = webtv;
			webtv = mxmlWalkNext(tmpnode, webtvs, MXML_NO_DESCEND);
			continue;
		}

		pWebTvNode = (YW_WEBTV_Node_t *)malloc(sizeof(YW_WEBTV_Node_t));
		if(pWebTvNode == NULL)
		{
			printf("YWAPP_Calloc failed!\n");
			return -1;
		}
		YWLIB_Memset(pWebTvNode, 0, sizeof(YW_WEBTV_Node_t));

		YWLIB_Strcpy((S8 *)pWebTvNode->title, (S8 *)mxmlElementGetAttr(webtv, ATTR_WEBTV_TITLE));
		pWebTvNode->title[TITLE_LEN-1] = 0;

		YWLIB_Strcpy((S8 *)pWebTvNode->url, (S8 *)mxmlElementGetAttr(webtv, ATTR_WEBTV_URL));
		pWebTvNode->url[URL_LEN-1] = 0;

		YWLIB_Strcpy((S8 *)pWebTvNode->description, (S8 *)mxmlElementGetAttr(webtv, ATTR_WEBTV_DESCRIPTION));
		pWebTvNode->description[DESCRIPTION_LEN-1] = 0;

		pWebTvNode->mediatype = YWLIB_Atoi((S8 *)mxmlElementGetAttr(webtv, ATTR_WEBTV_TYPE));

		WebTvi_AddOneNode(pWebTvNode);

		number++;

		tmpnode = webtv;
		webtv = mxmlWalkNext(tmpnode, webtvs, MXML_NO_DESCEND);
	}
	mxmlDelete(webtv_xml);

	g_WebTvInfo.num = number;

	return 0;
}


static void WebTvi_InitVariable(void)
{
	g_bInit = FALSE;
	g_pCurPlayWebTvInfo = NULL;
	g_WebTvPlayStatus = WEBTV_STOP;
	g_FocusIndex = -1;
	g_CurPlayIndex = -1;
}

static S32 YWWEBTVi_WndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
{
    switch (message)
    {
        case YWGUI_MSG_NCCREATE:
        {
            YWGUI_SetWEColor(hWnd, YWGUI_MAINWND_BGC, Color_black);
            break;
        }

        case YWGUI_MSG_INITDIALOG:
		{
			YWGUI_Handle_T hDlg = YWGUI_NULL_HANDLE;
			YWGUI_Handle_T hLT = YWGUI_NULL_HANDLE;

			WebTvi_InitVariable();
			if(WebTvi_InitDataList() == -1)
			{
				WebTvi_ListFree();
			}

			WebTvi_RefreshPlayCtrl(hWnd);
			
			YWGUI_ShowWindow(YWGUI_GetDlgItem(hWnd, IDC_LT_IPTV), YWGUI_SW_SHOW);

			hLT = YWGUI_GetDlgItem(hWnd, IDC_LT_IPTV);
			if(g_WebTvInfo.num > 0)
			{
				WebTvi_RefreshPlayInfo(hWnd, 0);
				g_FocusIndex = 0;
			}
			YWGUI_LTSetTotalLine(hLT, g_WebTvInfo.num, 0);
			YWGUI_SetFocus(hLT);
		

			hDlg = YWGUI_GetDlgItem(hWnd, IDC_PROGRESS_IPTV_SMALL);
            YWGUI_SetProgressBarRange(hDlg, 100);

			WebTvi_PlayInit(&g_PlayHandle);

			WebTvi_SetVideoOutWindow(g_PlayHandle, TRUE);
    	}
            return 0;

		case YWPUBLIC_MSG_WEBTV_LIST_REFRESH:
		{
			YWGUI_Handle_T hLT = YWGUI_GetDlgItem(hWnd, IDC_LT_IPTV);

			if((U32)wParam == 1)  //add
			{
 				g_FocusIndex = g_WebTvInfo.num-1;
				
				YWGUI_LTSetTotalLine(hLT, g_WebTvInfo.num, g_FocusIndex);
				WebTvi_RefreshPage(hWnd, g_FocusIndex);
				
				
			}
			else if((U32)wParam == 2) //delete
			{
				if(g_FocusIndex >= g_WebTvInfo.num)
				{
					g_FocusIndex = g_WebTvInfo.num-1;
				}
				YWGUI_LTSetTotalLine(hLT, g_WebTvInfo.num, (U16)g_FocusIndex);
				WebTvi_RefreshPage(hWnd, g_FocusIndex);
				
			}
			else if((U32)wParam == 0) //save edit
			{
				YWGUI_LTRefreshCurPageData(hLT);
				
				if(g_WebTvPlayStatus == WEBTV_STOP)
				{
					WebTvi_RefreshPlayInfo(hWnd, g_FocusIndex);
				}
			}

		}
			return 0;

		/*case YWPUBLIC_MSG_EXIT_FILE_BROWSE:
        {
			char cmd[512];
			YWGUI_Handle_T hDlg = YWGUI_NULL_HANDLE;
			int ret = -1;

            if(0 != lParam)
            {
   				hDlg = YWGENERAL_DispInfoForMoment1(hWnd, STR_DOWNLOADING, 0xffff);
				YWGUI_UpdateWindow(hDlg);

            	YWLIB_Memset(cmd, 0, sizeof(cmd));
				YWLIB_Sprintf(cmd, "mv -f %s%s %swebtv_usr_back.xml", WEBTV_XML_PATH, WEBTV_XML_USR_FILE, WEBTV_XML_PATH);
				YWPUBLIC_System(cmd);


            	YWLIB_Memset(cmd, 0, sizeof(cmd));
				YWLIB_Sprintf(cmd, "cp -f \"%s\" "WEBTV_XML_PATH, (char*)lParam);
				ret = YWPUBLIC_System(cmd);
				if(ret == 0)
				{
					WebTVi_ResumeFocusSize(hWnd, g_FocusIndex);
					WebTvi_ListFree();
					WebTvi_InitVariable();
					if(WebTvi_InitDataList() == -1)
					{
						YWGENERAL_DispInfoForMoment1(hWnd, STR_LOAD_FILE_FAIL, 3000);
		            	YWLIB_Memset(cmd, 0, sizeof(cmd));
						YWLIB_Sprintf(cmd, "mv -f %swebtv_usr_back.xml %s%s", WEBTV_XML_PATH, WEBTV_XML_PATH, WEBTV_XML_USR_FILE);
						YWPUBLIC_System(cmd);
						if(WebTvi_InitDataList() == -1)
						{
							WebTvi_ListFree();
						}
					}
					else
					{
						YWGENERAL_DispInfoForMoment1(hWnd, STR_LOAD_FILE_SUC, 2000);
					}
				}
				else
				{
					YWGENERAL_DispInfoForMoment1(hWnd, STR_LOAD_FILE_FAIL, 3000);
					YWLIB_Memset(cmd, 0, sizeof(cmd));
					YWLIB_Sprintf(cmd, "mv -f %swebtv_usr_back.xml %s%s", WEBTV_XML_PATH, WEBTV_XML_PATH, WEBTV_XML_USR_FILE);
					YWPUBLIC_System(cmd);
					if(WebTvi_InitDataList() == -1)
					{
						WebTvi_ListFree();
					}
				}
				WebTvi_RefreshWinAfterLoadFile(hWnd);
            }
        }
           break;*/

		case YWPUBLIC_MSG_END_OF_FILE:
		{
			if(YWGUI_GetMainWinById(IDD_WAIT) != YWGUI_NULL_HANDLE)
			{
				YWGUI_SendMessage(YWGUI_GetMainWinById(IDD_WAIT), YWGUI_MSG_CLOSE, 0, 0);
			}
			WebTvi_StopProc(hWnd);
		}
			break;

		case YWPUBLIC_MSG_WEBTV_EXIT_BIG:   //return from big win
		{
			if(g_WebTvPlayStatus == WEBTV_PLAY)
			{
				YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_IPTV_SMALLWIN), FALSE);
				YWGUI_ResetTimer(hWnd, TIMER_WEBTV_REFRESH, 1000);
				WebTvi_RefreshPlayCtrl(hWnd);
				WebTvi_RefreshPlayInfo(hWnd, g_CurPlayIndex);
			}
			else if(g_WebTvPlayStatus == WEBTV_STOP)
			{
				WebTvi_StopProc(hWnd);
			}
			else if(g_WebTvPlayStatus == WEBTV_PAUSE)
			{
				WebTvi_PauseProc(hWnd);
			}
		}
			break;

        case YWPUBLIC_MSG_START_WAIT:
        {
            WAIT_CreateWnd(hWnd);
            break;
        }

		case YWPUBLIC_MSG_WEBTV_PLAY:
		{
			YW_ErrorType_T retCode = (YW_ErrorType_T)wParam;
			if(retCode == YW_NO_ERROR)
			{
				g_WebTvPlayStatus = WEBTV_PLAY;
				g_CurPlayIndex = g_FocusIndex;
				YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_IPTV_SMALLWIN), FALSE);
				WebTvi_RefreshPlayCtrl(hWnd);
				WebTvi_RefreshPlayInfo(hWnd, g_CurPlayIndex);
				YWGUI_ResetTimer(hWnd, TIMER_WEBTV_REFRESH, 1000);
				YWGUI_SendMessage(YWGUI_GetMainWinById(IDD_WAIT), YWGUI_MSG_CLOSE, 0, 0);
				WebTvi_GetVolume(g_PlayHandle, &g_WebTvvolume);
			}
			else
			{
				g_WebTvPlayStatus = WEBTV_STOP;
				WebTvi_RefreshPlayCtrl(hWnd);
				YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_TXT_IPTV_SMALLWIN), TRUE);
				YWGUI_SendMessage(YWGUI_GetMainWinById(IDD_WAIT), YWGUI_MSG_CLOSE, 0, 0);
				YWGeneralPopInfo_CreateWindow(hWnd, YWSTR_GetString(STR_START_PLAY_FAILED), 2000);
			}
		}
			break;

        case YWGUI_MSG_COMMAND:
        {
            WebTvi_WndMsgCommandProc(hWnd, wParam, lParam);
        }
         break;

		case YWGUI_MSG_TIMER:
        {
            switch (wParam)
            {
                case TIMER_WEBTV_REFRESH:
                {
                   	U32 duration;
					U32 pos;

                    if (YW_NO_ERROR != YWNATIVE_AvGetDuration(g_PlayHandle, &duration))
                    {
                        printf("Get duration Failed!\n");
                        return -1;
                    }
					if (YW_NO_ERROR != YWNATIVE_AvGetPos(g_PlayHandle, &pos))
                    {
                        printf("Get pos Failed!\n");
                        return -1;
                    }

					printf("duration: %d, pos: %d\n", duration, pos);
					
					if(duration == 0)
					{
						YWGUI_SetProgressBarPosVal(YWGUI_GetDlgItem(hWnd, IDC_PROGRESS_IPTV_SMALL),0);
					}
					else
					{
                    	YWGUI_SetProgressBarPosVal(YWGUI_GetDlgItem(hWnd, IDC_PROGRESS_IPTV_SMALL),
                        	(pos * 100) / duration);
					}
                    break;
                }

                default:
                {
                    break;
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
				{					
					YWGUI_SendMessage(hWnd, YWGUI_MSG_CLOSE, 0, 0);
                }
                    break;
				case YWGUI_SCANCODE_RECEDE:
				case YWGUI_SCANCODE_PGUP:
				{
					YWGUI_Handle_T hLT = YWGUI_NULL_HANDLE;
					hLT = YWGUI_GetDlgItem(hWnd, IDC_LT_IPTV);
					YWGUI_LTScrollPage(hLT, FALSE);
					WebTvi_RefreshPage(hWnd, g_FocusIndex);
					break;
				}
				case YWGUI_SCANCODE_FORWARD:
				case YWGUI_SCANCODE_PGDN:
				{
					YWGUI_Handle_T hLT = YWGUI_NULL_HANDLE;
					hLT = YWGUI_GetDlgItem(hWnd, IDC_LT_IPTV);
					YWGUI_LTScrollPage(hLT, TRUE);
					WebTvi_RefreshPage(hWnd, g_FocusIndex);
					break;
				}


                case YWGUI_SCANCODE_UP:
				{
					if(g_WebTvInfo.num == 0)
						return 0;
            	}
					break;
                case YWGUI_SCANCODE_DOWN:
				{
					if(g_WebTvInfo.num == 0)
						return 0;
            	}
                    break;

				case YWGUI_SCANCODE_VOL_UP:
				case YWGUI_SCANCODE_LEFT:
				{
                    if(g_WebTvvolume > 0)
                    {
                    	U32 tmpVol = g_WebTvvolume;
                        WebTvi_SetVolume(g_PlayHandle, tmpVol - 1);
                    }
                    break;
                }

				case YWGUI_SCANCODE_VOL_DOWN:
                case YWGUI_SCANCODE_RIGHT:
				{
                    if (g_WebTvvolume < 20)
                    {
                    	U32 tmpVol = g_WebTvvolume;
                        WebTvi_SetVolume(g_PlayHandle, tmpVol + 1);
                    }
				
                    break;
                }
				

				case YWGUI_SCANCODE_PLAY:
                case YWGUI_SCANCODE_OK:
				{
					if(g_WebTvInfo.num == 0)
						return 0;
					
					g_FocusIndex = YWGUI_LTGetCurLine(YWGUI_GetDlgItem(hWnd, IDC_LT_IPTV));
					WebTvi_PlayProc(hWnd, g_FocusIndex);
                }
                    break;
                case YWGUI_SCANCODE_RED:  //add
					YWWEBTVi_CreateAddItemWindow(hWnd);
                    return 0;
			    case YWGUI_SCANCODE_GREEN:  //edit
			    {
					if(g_WebTvInfo.num == 0)
						return 0;

					g_FocusIndex = YWGUI_LTGetCurLine(YWGUI_GetDlgItem(hWnd, IDC_LT_IPTV));
					WebTvi_CreateEditItemWindow(hWnd, g_FocusIndex);
			    }
                    return 0;
                case YWGUI_SCANCODE_YELLOW:  //fuscreen
                {
					if(g_WebTvInfo.num == 0)
						return 0;

					g_FocusIndex = YWGUI_LTGetCurLine(YWGUI_GetDlgItem(hWnd, IDC_LT_IPTV));
					
					if(g_WebTvPlayStatus == WEBTV_STOP)
					{
						g_pCurPlayWebTvInfo = WebTvi_GetOneNodeByIndex(g_FocusIndex);
					}
					YWGUI_KillTimer(hWnd, TIMER_WEBTV_REFRESH);
					YWWEBTV_CreatePlayWindow(hWnd);
                }
                    return 0;
				/*case YWGUI_SCANCODE_BLUE: //factory reset
				{
					YW_ErrorType_T stRet = YW_NO_ERROR;
					S32 iRetId;

					stRet = YWGENERAL_CreateSyncConfirmBox(hWnd,
                              STR_WEBTV_USR_DATA_ERASE,
                              &iRetId,
                              0,
                              FALSE);
                    if(stRet != YW_NO_ERROR)
                    {
                        break;
                    }
                    if(iRetId == STR_YES)
                    {
                    	char cmd[512];
						YWGUI_Handle_T hLT = YWGUI_NULL_HANDLE;
						S32 tmpFocusIndex = -1;

						WebTvi_StopProc(hWnd);

						YWLIB_Memset(cmd, 0, sizeof(cmd));
						YWLIB_Sprintf((S8 *)cmd, (const S8*)"%s%s", WEBTV_XML_PATH, WEBTV_XML_DEF_FILE);
						if(0 != access(cmd, F_OK))
						{
							YWGENERAL_DispInfoForMoment1(hWnd, YWGUI_MAKEDWORD(STR_LOAD_FILE_FAIL, STR_INFORMATION), 2000);
							break;
						}


						YWLIB_Memset(cmd, 0, sizeof(cmd));
						YWLIB_Sprintf((S8 *)cmd, (const S8*)"rm -f %s%s", WEBTV_XML_PATH, WEBTV_XML_USR_FILE);
						YWPUBLIC_System(cmd);

						WebTvi_ListFree();
						tmpFocusIndex = g_FocusIndex;
						WebTvi_InitVariable();
						if(WebTvi_InitDataList() == 0)
						{
							if(g_ListType == WEBTV_LIST_TYPE_LIST)
							{
								hLT = YWGUI_GetDlgItem(hWnd, IDC_LT_WEBTV);
								YWGUI_LTSetTotalLine(hLT, g_WebTvInfo.num, 0);
								YWGUI_SetFocus(YWGUI_GetDlgItem(hWnd, IDC_LT_WEBTV));
								if(g_WebTvInfo.num > 0)
								{
									WebTvi_RefreshPlayInfo(hWnd, 0);
									g_FocusIndex = 0;
								}
								WebTvi_RefreshPage(hWnd, g_FocusIndex);
							}
							else
							{
								if(g_WebTvInfo.num > 0)
								{
									WebTvi_RefreshPlayInfo(hWnd, 0);
									g_FocusIndex = 0;
								}
								WebTVi_RefreshList(hWnd, g_FocusIndex);
								WebTvi_RefreshFocus(hWnd, g_FocusIndex, tmpFocusIndex);
								WebTvi_MatrixListRefreshPage(hWnd, g_FocusIndex);
								WebTvi_SetvMatrixListTotal(hWnd, g_FocusIndex);
							}
						}
						else
						{

							if(g_ListType == WEBTV_LIST_TYPE_LIST)
							{
								hLT = YWGUI_GetDlgItem(hWnd, IDC_LT_WEBTV);
								YWGUI_LTSetTotalLine(hLT, g_WebTvInfo.num, 0);
							}
							else
							{
								g_FocusIndex = -1;
								WebTVi_RefreshList(hWnd, g_FocusIndex);
								WebTvi_RefreshFocus(hWnd, g_FocusIndex, g_FocusIndex);
								WebTvi_MatrixListRefreshPage(hWnd, g_FocusIndex);
								WebTvi_SetvMatrixListTotal(hWnd, g_FocusIndex);
							}
							YWGENERAL_DispInfoForMoment1(hWnd, STR_LOAD_FILE_FAIL, 2000);
						}
                    }
				}
					break;
				case YWGUI_SCANCODE_FOLDER: //load
				{
					YWFB_Info_T stInfo;
					YW_ErrorType_T Error = YW_NO_ERROR;
				    U32 nNumRecs;
				    BOOL bIsMount = FALSE;
					YWLIB_WChar_T awcRootPath[YWFILE_MAX_PATH_LENGTH] = {0};

					Error = YW_NO_ERROR;
				    if(YWGUI_NULL_HANDLE != YWGUI_GetMainWinById(IDD_FILE_SCAN))
				    {
				        YWGENERAL_DispInfoForMoment1(hWnd, YWGUI_MAKEDWORD(STR_SCANING_DISK_NOW, STR_INFORMATION), 2*1000);
				        return 0;
				    }

    				#ifdef _YWAPP_NET_HDD_
    				bIsMount = TRUE;
				    #else
				    bIsMount = YWOS_HDDIsMounted();
				    #endif

				    YWLIB_Memset(awcRootPath, 0, sizeof(awcRootPath));
				    YWPUBLIC_Utf8To16((S8 *)PATH_EXT_STORAGE_ROOT,
				                        YWLIB_Strlen((S8 *)PATH_EXT_STORAGE_ROOT)+1,
				                        (S8*)awcRootPath,
				                        sizeof(awcRootPath));
					#ifdef _YWAPP_DYNAMIC_FLIST_
				    nNumRecs = YWFLISTi_GetEntryNum((S8*)PATH_EXT_STORAGE_ROOT);
					#else
				    Error = YWDBL_PvrFileGetNumByPath(awcRootPath, &nNumRecs);
					#endif

				    if(!bIsMount || YW_NO_ERROR != Error || nNumRecs == 0)
				    {
				        YWGENERAL_DispInfoForMoment1(hWnd, YWGUI_MAKEDWORD(STR_NO_FILE, STR_INFORMATION), 2*1000);
				        return 0;
				    }

                    YWLIB_Memset(&stInfo, 0, sizeof(stInfo));
                    stInfo.eType = YWFB_SEL_WEBTV_XML;
                    YWFILEBROWSER_CreateWnd(hWnd, &stInfo);
				}
					return 0;*/

				case YWGUI_SCANCODE_STOP:
				{
					if(g_WebTvInfo.num == 0)
						return 0;
					if(g_WebTvPlayStatus != WEBTV_STOP)
					{
						YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_SMALL_PLAY), &g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_PLAY], TRUE);
						YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_SMALL_STOP), &g_aIpTvGraphCellArray[YWCELL_PLAYER_CUR_STOP], TRUE);
						YWGUI_SetPicture(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_SMALL_PAUSE), &g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_PAUSE], TRUE);
						YWGUI_UpdateWindow(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_SMALL_PLAY));
						YWGUI_UpdateWindow(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_SMALL_STOP));
						YWGUI_UpdateWindow(YWGUI_GetDlgItem(hWnd, IDC_PIC_IPTV_SMALL_PAUSE));
						YWOS_TaskSleep(200);
						YWGUI_PostMessage(hWnd, YWPUBLIC_MSG_END_OF_FILE, 0, 0);
					}
				}
					break;
				case YWGUI_SCANCODE_PAUSE:
				{
					if(g_WebTvInfo.num == 0)
						return 0;
					if(g_WebTvPlayStatus == WEBTV_PLAY)
					{
						WebTvi_PauseProc(hWnd);
					}
				}
					break;
				
				case YWGUI_SCANCODE_VIDEO_FORMAT:
                {
                 //   WebTv_SetVideoOutWindow();
                }
					return 0;
                default:
                    break;
            }
		}
            break;


        case YWGUI_MSG_CLOSE:
		{

        }
            break;

        case YWGUI_MSG_DESTROY:
		{
			YWGUI_KillTimer(hWnd, TIMER_WEBTV_REFRESH);
			WebTvi_ListFree();
			WebTvi_StopPlay(g_PlayHandle);
			WebTvi_PlayTerm(g_PlayHandle);
			
			APP_IpTVResUnLoad();
        }
            break;

        default:
            break;
    }

    return YWGUI_DefaultDialogProc(hWnd,message,wParam,lParam);
}


YWGUI_HWnd_T YWPLUGIN_CreateMainMenuWindow(void)
{
    YWGUI_HWnd_T hIpTv = YWGUI_NULL_HANDLE;
    YW_ErrorType_T Error = YW_NO_ERROR;

	char cmd[128];
	
	if(0 != access("/var/etc", F_OK))
	{
		YWLIB_Memset(cmd, 0, sizeof(cmd));
		YWLIB_Sprintf((S8 *)cmd, (const S8 *)"mkdir -p /var/etc");
		if(0 != system(cmd))
		{
			return YWGUI_NULL_HANDLE;
		}
	}

	APP_IpTVResLoad();

    Error = YWGUI_CreateDialog(IDD_IPTV, YWGUI_NULL_HANDLE, YWWEBTVi_WndProc, 0, &hIpTv);

    return (YW_NO_ERROR == Error) ? hIpTv : YWGUI_NULL_HANDLE;
}


void YWPLUGIN_InitGuiTemplate(void)
{
    YWGUI_AddTempletNode(&g_template_webtv);
    YWGUI_AddTempletNode(&g_template_webtvadd);
    YWGUI_AddTempletNode(&g_template_webtvedit);
    YWGUI_AddTempletNode(&g_template_webTvPlayWnd);
    YWGUI_AddTempletNode(&gTemplateWaitWnd);
}

void YWPLUGIN_Init(void)
{
}

S8* YWPLUGIN_GetVersion(void)
{
    return (S8*)"1.0.00";
}

void YWPLUGIN_Term(void)
{
}





