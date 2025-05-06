#include "ywgui_ext.h"
#include "res_layout.h"
#include "ywimg_ext.h"
#include "iptv_layout.h"


/*******************************************************************************************/


#define PATH_APPRES_PIC_INTERNETTV "/root/plugin/var/pic/iptv/"


YWMID_DibitmapData_T g_bmp_struct_Player_key_Nor;
YWMID_DibitmapData_T g_bmp_struct_Player_key_Cur;
YWMID_DibitmapData_T g_bmp_struct_Player_key_hide;

YWMID_DibitmapData_T g_bmp_struct_iptv;
//YWMID_DibitmapData_T g_bmp_struct_Key_PIP;
YWMID_DibitmapData_T g_bmp_struct_Youtube_HelpLine;
YWMID_DibitmapData_T g_bmp_struct_YoutubeProcess_black;
YWMID_DibitmapData_T g_bmp_struct_YoutubeProcess_yellow;
YWMID_DibitmapData_T g_bmp_struct_YoutubeProcessBK_L;
YWMID_DibitmapData_T g_bmp_struct_YoutubeProcessBK_R;
YWMID_DibitmapData_T g_bmp_struct_POP_Button_Cur;
YWMID_DibitmapData_T g_bmp_struct_POP_Button_Nor;


YWMID_DibitmapData_T g_bmp_struct_Vol_Cur_X110Y18;
YWMID_DibitmapData_T g_bmp_struct_Vol_L;
YWMID_DibitmapData_T g_bmp_struct_Vol_M;
YWMID_DibitmapData_T g_bmp_struct_Vol_R;

YWMID_DibitmapData_T g_bmp_struct_YoutubeWaiting;
YWMID_DibitmapData_T g_bmp_struct_YoutubeWaitingBK;




void APP_IpTVResLoad(void)
{
	YW_ErrorType_T error = YW_NO_ERROR;
	error |= YWIMG_LoadDiBitmap(&g_bmp_struct_Player_key_Nor, (const U8*)PATH_APPRES_PIC_INTERNETTV"Player_key_Nor.png");
	error |= YWIMG_LoadDiBitmap(&g_bmp_struct_Player_key_Cur, (const U8*)PATH_APPRES_PIC_INTERNETTV"Player_key_Cur.png");
	error |= YWIMG_LoadDiBitmap(&g_bmp_struct_Player_key_hide, (const U8*)PATH_APPRES_PIC_INTERNETTV"Player_key_hide.png");

	error |= YWIMG_LoadDiBitmap(&g_bmp_struct_iptv, (const U8*)PATH_APPRES_PIC_INTERNETTV"iptv.png");
	error |= YWIMG_LoadDiBitmap(&g_bmp_struct_Youtube_HelpLine, (const U8*)PATH_APPRES_PIC_INTERNETTV"Youtube_HelpLine.png");
	error |= YWIMG_LoadDiBitmap(&g_bmp_struct_YoutubeProcess_black, (const U8*)PATH_APPRES_PIC_INTERNETTV"YoutubeProcess_black.png");
	error |= YWIMG_LoadDiBitmap(&g_bmp_struct_YoutubeProcess_yellow, (const U8*)PATH_APPRES_PIC_INTERNETTV"YoutubeProcess_yellow.png");
	error |= YWIMG_LoadDiBitmap(&g_bmp_struct_YoutubeProcessBK_L, (const U8*)PATH_APPRES_PIC_INTERNETTV"YoutubeProcessBK_L.png");
	error |= YWIMG_LoadDiBitmap(&g_bmp_struct_YoutubeProcessBK_R, (const U8*)PATH_APPRES_PIC_INTERNETTV"YoutubeProcessBK_R.png");
	error |= YWIMG_LoadDiBitmap(&g_bmp_struct_POP_Button_Cur, (const U8*)PATH_APPRES_PIC_INTERNETTV"POP_Button_Cur.png");
	error |= YWIMG_LoadDiBitmap(&g_bmp_struct_POP_Button_Nor, (const U8*)PATH_APPRES_PIC_INTERNETTV"POP_Button_Nor.png");

	error |= YWIMG_LoadDiBitmap(&g_bmp_struct_Vol_Cur_X110Y18, (const U8*)PATH_APPRES_PIC_INTERNETTV"Vol_Cur_X110Y18.png");
	error |= YWIMG_LoadDiBitmap(&g_bmp_struct_Vol_L, (const U8*)PATH_APPRES_PIC_INTERNETTV"Vol_L.png");
	error |= YWIMG_LoadDiBitmap(&g_bmp_struct_Vol_M, (const U8*)PATH_APPRES_PIC_INTERNETTV"Vol_M.png");
	error |= YWIMG_LoadDiBitmap(&g_bmp_struct_Vol_R, (const U8*)PATH_APPRES_PIC_INTERNETTV"Vol_R.png");

	error |= YWIMG_LoadDiBitmap(&g_bmp_struct_YoutubeWaiting, (const U8*)PATH_APPRES_PIC_INTERNETTV"YoutubeWaiting.png");
	error |= YWIMG_LoadDiBitmap(&g_bmp_struct_YoutubeWaitingBK, (const U8*)PATH_APPRES_PIC_INTERNETTV"YoutubeWaitingBK.png");

//	printf("APP_IpTVResLoad: %d\n", error);
}

void APP_IpTVResUnLoad(void)
{
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_Player_key_Nor);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_Player_key_Cur);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_Player_key_hide);
	
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_iptv);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_Youtube_HelpLine);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_YoutubeProcess_black);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_YoutubeProcess_yellow);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_YoutubeProcessBK_L);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_YoutubeProcessBK_R);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_POP_Button_Cur);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_POP_Button_Nor);

	
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_Vol_Cur_X110Y18);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_Vol_L);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_Vol_M);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_Vol_R);

	YWIMG_UnLoadDiBitmap(&g_bmp_struct_YoutubeWaiting);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_YoutubeWaitingBK);

}





#define YWGUI_DEF_BMP_OPT   YWMID_DIBMP_OP_MODE_ALPHA|YWMID_DIBMP_COLOR_KEY_MODE_NONE|YWMID_DIBMP_OUTPUT_MODE_CENTER


YWGUI_GraphCell_T g_aIpTvGraphCellArray[IPTVCELL_NUM] =
{
	//normal icon
	//play
    {{YWGUI_DEF_BMP_OPT,{PLAYER_CTRL_ICON_W * 3, 0, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H},
         {0, 0, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H}},&g_bmp_struct_Player_key_Nor},

    //stop nor
    {{YWGUI_DEF_BMP_OPT,{PLAYER_CTRL_ICON_W * 4, 0, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H},
         {0, 0, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H}},&g_bmp_struct_Player_key_Nor},

    //pause nor
    {{YWGUI_DEF_BMP_OPT,{PLAYER_CTRL_ICON_W * 5, 0, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H},
         {0, 0, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H}},&g_bmp_struct_Player_key_Nor},

	//cur icon
	//play
	{{YWGUI_DEF_BMP_OPT,{PLAYER_CTRL_ICON_W * 3, 0, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H},
         {0, 0, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H}},&g_bmp_struct_Player_key_Cur},

    //stop
    {{YWGUI_DEF_BMP_OPT,{PLAYER_CTRL_ICON_W * 4, 0, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H},
         {0, 0, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H}},&g_bmp_struct_Player_key_Cur},

    //pause
    {{YWGUI_DEF_BMP_OPT,{PLAYER_CTRL_ICON_W * 5, 0, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H},
         {0, 0, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H}},&g_bmp_struct_Player_key_Cur},

	//hide icon
	//play
    {{YWGUI_DEF_BMP_OPT,{PLAYER_CTRL_ICON_W * 3, 0, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H},
         {0, 0, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H}},&g_bmp_struct_Player_key_hide},

    //stop
    {{YWGUI_DEF_BMP_OPT,{PLAYER_CTRL_ICON_W * 4, 0, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H},
         {0, 0, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H}},&g_bmp_struct_Player_key_hide},

    //pause
    {{YWGUI_DEF_BMP_OPT,{PLAYER_CTRL_ICON_W * 5, 0, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H},
         {0, 0, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H}},&g_bmp_struct_Player_key_hide},

	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_iptv},
	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_Youtube_HelpLine},
	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_YoutubeProcess_black},
	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_YoutubeProcess_yellow},
	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_YoutubeProcessBK_L},
	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_YoutubeProcessBK_R},
	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_POP_Button_Cur},
	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_POP_Button_Nor},

	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_Vol_Cur_X110Y18},
	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_Vol_L},
	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_Vol_M},
	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_Vol_R},

	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_YoutubeWaiting},
	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_YoutubeWaitingBK},
};




static YWGUI_GraphCell_T *gLineCell[] =
{
    &g_aIpTvGraphCellArray[YWCELL_HELP_LINE]
};

static YWGUI_GraphCollect_T gLineCollect =
{
    SPELL_GRAPH_REPEAT_H,
    1,
    gLineCell,
    0
};

static YWGUI_ShapeState_T gLineState =
{
    NULL,
    &gLineCollect,
    NULL,
    NULL
};

static YWGUI_ShapeInfo_T gLineInfo =
{
    {
        &gLineState,
        &gLineState,
        &gLineState,
        &gLineState
    }
};



#define WEBTV_ICON_START_X 48
#define WEBTV_ICON_START_Y 65
#define WEBTV_ICON_START_W 165
#define WEBTV_ICON_START_H 75


#define WEBTV_SMALL_WIN_START_X WEBTV_ICON_START_X
#define WEBTV_SMALL_WIN_START_Y 166
#define WEBTV_SMALL_WIN_W 590
#define WEBTV_SMALL_WIN_H 398

#define WEBTV_PLAYCTRL_START_Y (WEBTV_SMALL_WIN_START_Y+WEBTV_SMALL_WIN_H)

#define WEBTV_LIST_X 680
#define WEBTV_LIST_Y WEBTV_SMALL_WIN_START_Y
#define WEBTV_LIST_W 1148
#define WEBTV_LIST_H 780

//for second list

#define TABLE_X WEBTV_LIST_X//WEBTV_LIST_X+32
#define TABLE_Y WEBTV_LIST_Y//WEBTV_LIST_Y+33

#define TABLE_PIC_W 204
#define TABLE_PIC_H 126
#define TABLE_PIC_W_GAP 30
#define TABLE_PIC_H_GAP 15

#define TABLE_PIC_HL_W 268
#define TABLE_PIC_HL_H 176



#define BAR_START_Y    (950)

#define WEBTV_HELP_KEY_START_X    100
#define WEBTV_HELP_KEY_START_Y    (BAR_START_Y+20)

static YWGUI_LTShapeInfo_T *gWebTvColLTShapeInfo[] =
{
    &g_atColLTShapeInfo,
	NULL,
};

static U16 gWebTvLTColWidth[] = {10, 90, (WEBTV_LIST_W-10*2-90), 10};

static const YWGUI_LTAddData_T gWebTvLTAddData =
{
    4,
    15,
    gWebTvLTColWidth,
    gWebTvColLTShapeInfo,
    &g_tPosbarDef,
    0,
    NULL,
    NULL
};


static YWGUI_GraphCell_T*  g_aProgressGraphCellP[1]=
{
    //Progress P
    &g_aIpTvGraphCellArray[YWCELL_PROCESS_YELLOW],
};
static YWGUI_GraphCell_T*  g_aProgressGraphCellPBg[3]=
{
    //Progress P Bg
    &g_aIpTvGraphCellArray[YWCELL_PROCESS_BK_L],
    &g_aIpTvGraphCellArray[YWCELL_PROCESS_BLACK],
    &g_aIpTvGraphCellArray[YWCELL_PROCESS_BK_R],
};

static YWGUI_GraphCollect_T  g_tProgressGraphCellBg=
{
    SPELL_3GRAPH_H,
    3,
    g_aProgressGraphCellPBg,
    0,
};

static YWGUI_ShapeFrame_T g_tProgressGraphCellFrame =
{
    FRAME_GRAPH,
    &g_tProgressGraphCellBg,
    0,0,0,0,
    10,0,10,0
};

static YWGUI_GraphCollect_T  g_tProgressGraphCell=
{
    SPELL_GRAPH_REPEAT_H,
    1,
    g_aProgressGraphCellP ,
    0,
};
static YWGUI_ShapeState_T g_tProgressShapeState=
{
    &g_tProgressGraphCellFrame,
    NULL,
    &g_tProgressGraphCell,
    NULL,
};
YWGUI_ShapeInfo_T g_tProgressShapeInfo =
{
    {
        &g_tProgressShapeState,
        &g_tProgressShapeState,
        &g_tProgressShapeState,
        &g_tProgressShapeState
    }
};


/*
static YWGUI_LTShapeState_T gRssLTShapeState =
{
    NULL,
    &g_tWhiteShapeColor,
};


static YWGUI_LTShapeInfo_T gRssLTShapeInfo =
{
    &gRssLTShapeState,
    &gRssLTShapeState,
    &gRssLTShapeState,
    &gRssLTShapeState
};


static YWGUI_LTShapeInfo_T *gRssColLTShapeInfo[] =
{
    &gRssLTShapeInfo
};

static U16 gOkIconLTColWidth[] = {1};

static const YWGUI_LTAddData_T gOkIconLTAddData =
{
    1,
    4,
    gOkIconLTColWidth,
    gRssColLTShapeInfo,
    &g_tPosbarDef,
    0,
    NULL,
    NULL
};
*/



static YWGUI_CtrlTemplate_T g_ctrl_template_webtv[] =
{
	//icon
	{(const S8*)YWGUI_CTRL_PICTURE, YWGUI_WS_VISIBLE, YWGUI_WS_EX_NONE|YWGUI_WS_EX_TRANSPARENT,
        WEBTV_ICON_START_X, WEBTV_ICON_START_Y, WEBTV_ICON_START_W, WEBTV_ICON_START_H,
        IDC_PIC_IPTV_ICON, STR_EMPTY, (DWORD)&g_aIpTvGraphCellArray[YWCELL_IPTV_ICON],0},
	//page
	{(const S8*)YWGUI_CTRL_STATIC,YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE,
        WEBTV_LIST_X+880, WEBTV_LIST_Y-81, 200, 42,
        IDC_TXT_IPTV_PAGE, STR_EMPTY, 0, &g_tTxtBlackWhiteShapeInfo},

	//small win
	{(const S8*)YWGUI_CTRL_STATIC,YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
        WEBTV_SMALL_WIN_START_X, WEBTV_SMALL_WIN_START_Y,WEBTV_SMALL_WIN_W, WEBTV_SMALL_WIN_H,
        IDC_TXT_IPTV_SMALLWIN,STR_EMPTY,0, &gBkTranExShapInfo},

    //small win play control        
	{(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
        WEBTV_SMALL_WIN_START_X, WEBTV_PLAYCTRL_START_Y, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H,
		IDC_PIC_IPTV_SMALL_PLAY,STR_EMPTY,(DWORD)&g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_PLAY], 0},
  	{(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
        WEBTV_SMALL_WIN_START_X+PLAYER_CTRL_ICON_W, WEBTV_PLAYCTRL_START_Y,PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H,
        IDC_PIC_IPTV_SMALL_STOP,STR_EMPTY,(DWORD)&g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_STOP],0},
  	{(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
        WEBTV_SMALL_WIN_START_X+PLAYER_CTRL_ICON_W*2, WEBTV_PLAYCTRL_START_Y,PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H,
        IDC_PIC_IPTV_SMALL_PAUSE,STR_EMPTY,(DWORD)&g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_PAUSE],0},

	{(const S8*)YWGUI_CTRL_PROGRESSBAR, YWGUI_WS_VISIBLE|YWGUI_PBS_HORZ|YWGUI_PBS_STRETCH, YWGUI_WS_EX_TRANSPARENT,
       	WEBTV_SMALL_WIN_START_X+PLAYER_CTRL_ICON_W*3, WEBTV_PLAYCTRL_START_Y, WEBTV_SMALL_WIN_W-PLAYER_CTRL_ICON_W*3, PLAYER_CTRL_ICON_H,
       	IDC_PROGRESS_IPTV_SMALL, STR_EMPTY,0,&g_tProgressShapeInfo},
	/*{(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
        (WEBTV_SMALL_WIN_START_X+WEBTV_SMALL_WIN_W-PLAYER_CTRL_ICON_W), WEBTV_PLAYCTRL_START_Y,PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H,
        IDC_PIC_IPTV_PIP,STR_EMPTY,(DWORD)&g_aIpTvGraphCellArray[YWCELL_KEY_PIP],NULL},*/
	//detail info
	{(const S8*)YWGUI_CTRL_STATIC,YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_TOP,YWGUI_WS_EX_NONE,
        WEBTV_SMALL_WIN_START_X, (WEBTV_PLAYCTRL_START_Y+52)+20, WEBTV_SMALL_WIN_W, 52*1,
        IDC_TXT_IPTV_INFO_TITLE, STR_EMPTY, 0, &g_tTxtBlackWhiteShapeInfo},
	{(const S8*)YWGUI_CTRL_STATIC,YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_TOP|YWGUI_SS_WORDBREAK,YWGUI_WS_EX_NONE,
        WEBTV_SMALL_WIN_START_X, (WEBTV_PLAYCTRL_START_Y+52*2)+20, WEBTV_SMALL_WIN_W, 52*5,
        IDC_TXT_IPTV_INFO_DETAIL, STR_EMPTY, 0, &g_tTxtBlackWhiteShapeInfo},


	//list table
    {(const S8*)YWGUI_CTRL_LISTTABLE, YWGUI_WS_VISIBLE|YWGUI_LTS_ROLLDISP, YWGUI_WS_EX_NONE,
        WEBTV_LIST_X, WEBTV_LIST_Y, WEBTV_LIST_W, WEBTV_LIST_H,
        IDC_LT_IPTV,
        STR_EMPTY,
        (DWORD)&gWebTvLTAddData,
        &g_tListShapeInfo
    },


	//bar
	{(const S8*)YWGUI_CTRL_STATIC,YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
        0, BAR_START_Y, YWPUBLIC_OSD_W, 12,
        IDC_TXT_IPTV_BAR,STR_EMPTY,0, &gLineInfo},

 // help info
    {(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
        WEBTV_HELP_KEY_START_X, WEBTV_HELP_KEY_START_Y, 46, 46,
        IDC_PIC_IPTV_ADD_IPTV,STR_EMPTY,(DWORD)&g_aGraphCellArray[YWCELL_RED], 0},
    {(const S8*)YWGUI_CTRL_STATIC,YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE|YWGUI_WS_EX_TRANSPARENT,
        WEBTV_HELP_KEY_START_X + 46 + 10, WEBTV_HELP_KEY_START_Y, 200, 46,
		IDC_TXT_IPTV_ADD_IPTV,STR_ADD,0, &g_tTxtBlackWhiteShapeInfo},

	{(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
        WEBTV_HELP_KEY_START_X+280, WEBTV_HELP_KEY_START_Y, 46, 46,
        IDC_PIC_IPTV_EDIT_IPTV,STR_EMPTY,(DWORD)&g_aGraphCellArray[YWCELL_GREEN], 0},
    {(const S8*)YWGUI_CTRL_STATIC,YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE|YWGUI_WS_EX_TRANSPARENT,
        WEBTV_HELP_KEY_START_X + 280+46 + 10, WEBTV_HELP_KEY_START_Y, 200, 46,
		IDC_TXT_IPTV_EDIT_IPTV,STR_EDIT,0, &g_tTxtBlackWhiteShapeInfo},

	{(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
        WEBTV_HELP_KEY_START_X+560, WEBTV_HELP_KEY_START_Y, 46, 46,
        IDC_PIC_IPTV_FULL_SCREEN,STR_EMPTY,(DWORD)&g_aGraphCellArray[YWCELL_YELLOW], 0},
    {(const S8*)YWGUI_CTRL_STATIC,YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE|YWGUI_WS_EX_TRANSPARENT,
        WEBTV_HELP_KEY_START_X + 560+46 + 10, WEBTV_HELP_KEY_START_Y, 200, 46,
		IDC_TXT_IPTV_FULL_SCREEN,STR_FULL_SCREEN,0, &g_tTxtBlackWhiteShapeInfo},
	/*

	{(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
        WEBTV_HELP_KEY_START_X+840, WEBTV_HELP_KEY_START_Y, 46, 46,
        IDC_PIC_WEBTV_FACTORY_RESET,STR_EMPTY,(DWORD)&g_aGraphCellArray[YWCELL_PB_HELP_BLUE_KEY], 0},
    {(const S8*)YWGUI_CTRL_STATIC,YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE|YWGUI_WS_EX_TRANSPARENT,
        WEBTV_HELP_KEY_START_X + 840+46 + 10, WEBTV_HELP_KEY_START_Y, 300, 46,
		IDC_TXT_WEBTV_FACTORY_RESET, STR_LOAD_DEFAULT_DATA, 0, &g_tTxtWhiteShapInfo},

	{(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
        WEBTV_HELP_KEY_START_X+1150, WEBTV_HELP_KEY_START_Y, 46, 46,
        IDC_PIC_WEBTV_LOAD,STR_EMPTY,(DWORD)&g_aGraphCellArray[YWCELL_PB_HELP_FOLDER], 0},
    {(const S8*)YWGUI_CTRL_STATIC,YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE|YWGUI_WS_EX_TRANSPARENT,
        WEBTV_HELP_KEY_START_X + 1150+46 + 10, WEBTV_HELP_KEY_START_Y, 300, 46,
		IDC_TXT_WEBTV_LOAD, STR_LOAD_WEBTV_XML, 0, &g_tTxtWhiteShapInfo},

	{(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
        WEBTV_HELP_KEY_START_X+1430, WEBTV_HELP_KEY_START_Y, 46, 46,
        IDC_PIC_WEBTV_LIST,STR_EMPTY,(DWORD)&g_aGraphCellArray[YWCELL_PB_HELP_F1_KEY], 0},
    {(const S8*)YWGUI_CTRL_STATIC,YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE|YWGUI_WS_EX_TRANSPARENT,
        WEBTV_HELP_KEY_START_X + 1430+46 + 10, WEBTV_HELP_KEY_START_Y, 200, 46,
		IDC_TXT_WEBTV_LIST, STR_SWITCH, 0, &g_tTxtWhiteShapInfo},
*/

};

const YWGUI_DlgTemplate_T g_template_webtv =
{
    IDD_IPTV,
    YWGUI_WS_VISIBLE ,
    YWGUI_WS_EX_NONE,
    0,
    0,
    YWPUBLIC_OSD_W,
    YWPUBLIC_OSD_H,
    0,
    YWGUI_ARRAY_SIZE(g_ctrl_template_webtv),
    g_ctrl_template_webtv,
    0,
    NULL
};



#define WEBTV_POP_DLG_W 680
#define WEBTV_POP_DLG_H (530-156)//478

#define WEBTV_ADD_CTRL_W 660
#define WEBTV_ADD_CTRL_W_L 280

#define WEBTV_LRC_POP_H 78

static YWGUI_GraphCell_T*  g_tIpTvBtnGraphCell_Normal[1]=
{
    &g_aIpTvGraphCellArray[YWCELL_POP_BUTTON_NOR],
};
static YWGUI_GraphCell_T*  g_tIpTvBtnGraphCell_Afocus[1]=
{
    &g_aIpTvGraphCellArray[YWCELL_POP_BUTTON_CUR],
};

static YWGUI_GraphCollect_T  g_tIpTvBtnGraphCollect_Normal=
{
    SPELL_GRAPH,
    1,
    g_tIpTvBtnGraphCell_Normal,
    0
};

static YWGUI_GraphCollect_T  g_tIpTvBtnGraphCollect_AFOCUS=
{
    SPELL_GRAPH,
    1,
    g_tIpTvBtnGraphCell_Afocus,
    0
};
static YWGUI_ShapeColor_T  g_tIpTvBtnShapeColor_normal=
{
    DColor_transparency,
    DColor_white,
    DColor_transparency
};

static YWGUI_ShapeColor_T  g_tIpTvBtnShapeColor_Afocus=
{
    DColor_transparency,
    DColor_black,
    DColor_transparency
};
static YWGUI_ShapeState_T g_tIpTvBtnShapeState_Normal=
{
    NULL,
    &g_tIpTvBtnGraphCollect_Normal,
    NULL,
    &g_tIpTvBtnShapeColor_normal
};

static YWGUI_ShapeState_T g_tIpTvBtnShapeState_AFOCUS=
{
    NULL,
    &g_tIpTvBtnGraphCollect_AFOCUS,
    NULL,
    &g_tIpTvBtnShapeColor_Afocus
};

YWGUI_ShapeInfo_T g_tIpTvBtnShapeInfo =
{
    {
        &g_tIpTvBtnShapeState_Normal,
        &g_tIpTvBtnShapeState_Normal,
        &g_tIpTvBtnShapeState_AFOCUS,
        &g_tIpTvBtnShapeState_AFOCUS,
    }
};


//up list
static YWGUI_LRCombobox_AddData_T WebTvUp2LRCBAddData =
{
    //Edit的外形
    &g_tLRCBEditShapeInfo,

    //List的位置
    0, -(WEBTV_LRC_POP_H+CTRL_COMMON_HIGH*2), (WEBTV_ADD_CTRL_W-WEBTV_ADD_CTRL_W_L), (WEBTV_LRC_POP_H+CTRL_COMMON_HIGH*2),

    //List的外形
    &g_tPopDlgHaveHeadShapeInfo,
    &g_tLRCBListAddData
};

//down list
/*static YWGUI_LRCombobox_AddData_T WebTvDown2LRCBAddData =
{
    //Edit的外形
    &g_tCommLRCBEditShapeInfo,

    //List的位置
    0, APP_CTRL_DEFAULT_HEIGHT, (WEBTV_ADD_CTRL_W-WEBTV_ADD_CTRL_W_L), (WEBTV_LRC_POP_H+APP_CTRL_DEFAULT_HEIGHT*2),

    //List的外形
    &g_LRPopFrameShapeInfo,
    &g_tCommLRCBListAddData
};
*/



//TV title
static YWGUI_ContainerCtrlTemplate_T tWebTvTitleTplt[] =
{
    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_LEFT,YWGUI_WS_EX_NONE,
        0, 0, WEBTV_ADD_CTRL_W_L,CTRL_COMMON_HIGH,
        IDC_TXT_IPTV_ADD_TV_TITLE_L, STR_TITLE,0,&g_tCommItemCntShapeInfo},

    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_CENTER|YWGUI_SS_ROLLDISP,YWGUI_WS_EX_NONE,
        WEBTV_ADD_CTRL_W_L, 0, (WEBTV_ADD_CTRL_W-WEBTV_ADD_CTRL_W_L), CTRL_COMMON_HIGH,
        IDC_TXT_IPTV_ADD_TV_TITLE_R, STR_EMPTY, 0, &g_tCommItemCntShapeInfo},

};
static YWGUI_ContainerAddData_T tWebTvTitleAddData =
{
    2,
    tWebTvTitleTplt,
};

// url
static YWGUI_ContainerCtrlTemplate_T tWebTVUrlTplt[] =
{
    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_LEFT,YWGUI_WS_EX_NONE,
        0, 0, WEBTV_ADD_CTRL_W_L,CTRL_COMMON_HIGH,
        IDC_TXT_IPTV_ADD_TV_URL_L, STR_URL,0,&g_tCommItemCntShapeInfo},

    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_CENTER|YWGUI_SS_ROLLDISP,YWGUI_WS_EX_NONE,
        WEBTV_ADD_CTRL_W_L, 0, (WEBTV_ADD_CTRL_W-WEBTV_ADD_CTRL_W_L), CTRL_COMMON_HIGH,
        IDC_TXT_IPTV_ADD_TV_URL_R, STR_EMPTY, 0, &g_tCommItemCntShapeInfo},
};

static YWGUI_ContainerAddData_T tWebTvURLAddData =
{
    2,
    tWebTVUrlTplt,
};

//description
static YWGUI_ContainerCtrlTemplate_T tWebTvDescripTplt[] =
{
    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_LEFT,YWGUI_WS_EX_NONE,
        0, 0, WEBTV_ADD_CTRL_W_L,CTRL_COMMON_HIGH,
        IDC_TXT_IPTV_ADD_TV_DESCRIPTION_L, STR_DESCRIPTION,0,&g_tCommItemCntShapeInfo},

    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_CENTER|YWGUI_SS_ROLLDISP,YWGUI_WS_EX_NONE,
        WEBTV_ADD_CTRL_W_L, 0, (WEBTV_ADD_CTRL_W-WEBTV_ADD_CTRL_W_L), CTRL_COMMON_HIGH,
        IDC_TXT_IPTV_ADD_TV_DESCRIPTION_R, STR_EMPTY, 0, &g_tCommItemCntShapeInfo},
};

static YWGUI_ContainerAddData_T tWebTvDescripAddData =
{
    2,
    tWebTvDescripTplt,
};


//media type
static YWGUI_ContainerCtrlTemplate_T tWebTvMediaTypeTplt[] =
{
    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_LEFT,YWGUI_WS_EX_NONE,
        0, 0, WEBTV_ADD_CTRL_W_L,CTRL_COMMON_HIGH,
        IDC_TXT_IPTV_ADD_MEDIA_TYPE_L, STR_TYPE,0,&g_tCommItemCntShapeInfo},

    {(const S8*)YWGUI_CTRL_LRCOMBOBOX, YWGUI_WS_VISIBLE|YWGUI_LRCBS_ALWAYSSCROLL|YWGUI_LRCBS_CENTER|YWGUI_LRCBS_VCENTER|YWGUI_LRCBS_EXITKEYHIDELIST,YWGUI_WS_EX_NOTIFY,
        WEBTV_ADD_CTRL_W_L, 0, (WEBTV_ADD_CTRL_W-WEBTV_ADD_CTRL_W_L), CTRL_COMMON_HIGH,
        IDC_LRC_IPTV_ADD_MEDIA_TYPE_R, 0,(DWORD)&WebTvUp2LRCBAddData,0},
};

static YWGUI_ContainerAddData_T tWebTvMediaTypeAddData =
{
    2,
    tWebTvMediaTypeTplt,
};


static YWGUI_CtrlTemplate_T g_ctrl_template_webtvadd[] =
{

    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE | YWGUI_SS_CENTER | YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE |YWGUI_WS_EX_TRANSPARENT|YWGUI_WS_EX_TITLECTRL,
        (WEBTV_POP_DLG_W-400)/2, 0, 400, 64,
        IDC_TXT_IPTV_ADD_TITLE, STR_ADD, 0, 0},

    // TV title
    {(const S8*)YWGUI_CTRL_CONTAINER, YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
        0, 0, WEBTV_ADD_CTRL_W, CTRL_COMMON_HIGH,
        IDC_CTN_IPTV_ADD_TV_TITLE, STR_EMPTY, (DWORD)&tWebTvTitleAddData, NULL},

    // url
    {(const S8*)YWGUI_CTRL_CONTAINER, YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
        0, CTRL_COMMON_HIGH*1, WEBTV_ADD_CTRL_W,CTRL_COMMON_HIGH,
        IDC_CTN_IPTV_ADD_TV_URL, STR_EMPTY, (DWORD)&tWebTvURLAddData, NULL},

	//description
    {(const S8*)YWGUI_CTRL_CONTAINER, YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
        0, CTRL_COMMON_HIGH*2, WEBTV_ADD_CTRL_W,CTRL_COMMON_HIGH,
        IDC_CTN_IPTV_ADD_TV_DESCRIPTION, STR_EMPTY, (DWORD)&tWebTvDescripAddData, NULL},

	//media type
	{(const S8*)YWGUI_CTRL_CONTAINER, YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
        0, CTRL_COMMON_HIGH*3, WEBTV_ADD_CTRL_W,CTRL_COMMON_HIGH,
        IDC_CTN_IPTV_ADD_MEDIA_TYPE, STR_EMPTY, (DWORD)&tWebTvMediaTypeAddData, NULL},

	//add and exit
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE,
	    150, CTRL_COMMON_HIGH*4+20,116, 42,
	    IDC_BTN_IPTV_ADD, STR_ADD, 0, &g_tIpTvBtnShapeInfo},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE,
	    390, CTRL_COMMON_HIGH*4+20,116, 42,
	    IDC_BTN_IPTV_EXIT, STR_EXIT, 0, &g_tIpTvBtnShapeInfo},
};


const YWGUI_DlgTemplate_T g_template_webtvadd =
{
    IDD_IPTV_ADD,
    YWGUI_WS_VISIBLE,
    YWGUI_WS_EX_NONE,
    (YWPUBLIC_OSD_W - WEBTV_POP_DLG_W)/2,
    (YWPUBLIC_OSD_H - (WEBTV_POP_DLG_H))/2,
    WEBTV_POP_DLG_W,
    (WEBTV_POP_DLG_H),
    -1,
    YWGUI_ARRAY_SIZE(g_ctrl_template_webtvadd),
    g_ctrl_template_webtvadd,
    0,
    &g_tPopDlgHaveHeadShapeInfo
};



static YWGUI_CtrlTemplate_T g_ctrl_template_webtvedit[] =
{
	//title
    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE | YWGUI_SS_CENTER | YWGUI_SS_VCENTER, YWGUI_WS_EX_TITLECTRL | YWGUI_WS_EX_TRANSPARENT,
        (WEBTV_POP_DLG_W-400)/2, 0, 400, 64,
        IDC_TXT_IPTV_ADD_TITLE, STR_EDIT, 0, 0},

    // TV title
    {(const S8*)YWGUI_CTRL_CONTAINER, YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
        0, 0, WEBTV_ADD_CTRL_W,CTRL_COMMON_HIGH,
        IDC_CTN_IPTV_ADD_TV_TITLE, STR_EMPTY, (DWORD)&tWebTvTitleAddData, NULL},

    // url
    {(const S8*)YWGUI_CTRL_CONTAINER, YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
        0, CTRL_COMMON_HIGH*1, WEBTV_ADD_CTRL_W,CTRL_COMMON_HIGH,
        IDC_CTN_IPTV_ADD_TV_URL, STR_EMPTY, (DWORD)&tWebTvURLAddData, NULL},

	//description
    {(const S8*)YWGUI_CTRL_CONTAINER, YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
        0, CTRL_COMMON_HIGH*2, WEBTV_ADD_CTRL_W,CTRL_COMMON_HIGH,
        IDC_CTN_IPTV_ADD_TV_DESCRIPTION, STR_EMPTY, (DWORD)&tWebTvDescripAddData, NULL},

	//media type
	{(const S8*)YWGUI_CTRL_CONTAINER, YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
        0, CTRL_COMMON_HIGH*3, WEBTV_ADD_CTRL_W,CTRL_COMMON_HIGH,
        IDC_CTN_IPTV_ADD_MEDIA_TYPE, STR_EMPTY, (DWORD)&tWebTvMediaTypeAddData, NULL},

	//OK , exit , delete
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE,
	    80, CTRL_COMMON_HIGH*4+20,116, 42,
	    IDC_BTN_IPTV_ADD, STR_OK, 0, (YWGUI_ShapeInfo_T*)&g_tIpTvBtnShapeInfo},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE,
	    270, CTRL_COMMON_HIGH*4+20,116, 42,
	    IDC_BTN_IPTV_EXIT, STR_EXIT, 0, (YWGUI_ShapeInfo_T*)&g_tIpTvBtnShapeInfo},
	{(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE,
	    460, CTRL_COMMON_HIGH*4+20,116, 42,
	    IDC_BTN_IPTV_DELETE, STR_DEL, 0, (YWGUI_ShapeInfo_T*)&g_tIpTvBtnShapeInfo},


};

const YWGUI_DlgTemplate_T g_template_webtvedit =
{
    IDD_IPTV_EDIT,
    YWGUI_WS_VISIBLE,
    YWGUI_WS_EX_NONE,
    (YWPUBLIC_OSD_W - WEBTV_POP_DLG_W)/2,
    (YWPUBLIC_OSD_H - WEBTV_POP_DLG_H)/2,
    WEBTV_POP_DLG_W,
    WEBTV_POP_DLG_H,
    -1,
    YWGUI_ARRAY_SIZE(g_ctrl_template_webtvedit),
    g_ctrl_template_webtvedit,
    0,
    &g_tPopDlgHaveHeadShapeInfo
};



#define WEBTV_PLAY

#define WEBTV_PLAY_CTRL_W 1000
#define WEBTV_PLAY_CTRL_Y 900
#define WEBTV_PLAY_CTRL_X ((YWPUBLIC_OSD_W-WEBTV_PLAY_CTRL_W)/2)
//#define WEBTV_PLAY_TIME_W 300

static YWGUI_GraphCell_T *gVolBkGraphCell[] =
{
    &g_aIpTvGraphCellArray[YWCELL_VOL_L],
    &g_aIpTvGraphCellArray[YWCELL_VOL_M],
    &g_aIpTvGraphCellArray[YWCELL_VOL_R],
};

static YWGUI_GraphCollect_T gVolBkGraphCollect =
{
    SPELL_3GRAPH_H,
    3,
    gVolBkGraphCell,
    0
};

static YWGUI_ShapeFrame_T gVolBkShapeFrame =
{
    FRAME_GRAPH,
    &gVolBkGraphCollect,
    0, 0, 0, 0,
    0, 0, 0, 0
};

static YWGUI_ShapeState_T gVolBkShapeState =
{
    &gVolBkShapeFrame,
    NULL,
    NULL,
    NULL
};

YWGUI_ShapeInfo_T gVolBkShapeInfo =
{
    {
        &gVolBkShapeState,
        &gVolBkShapeState,
        &gVolBkShapeState,
        &gVolBkShapeState
    }
};

static YWGUI_GraphCell_T *gVolGraphCell[] =
{
    &g_aIpTvGraphCellArray[YWCELL_VOL_CUR]
};

static YWGUI_GraphCollect_T gVolGraphCollect =
{
    SPELL_GRAPH,
    1,
    gVolGraphCell,
    0
};

static YWGUI_ShapeState_T gVolShapeState =
{
    NULL,
    NULL,
    &gVolGraphCollect,
    NULL
};

YWGUI_ShapeInfo_T gVolShapeInfo =
{
    {
        &gVolShapeState,
        &gVolShapeState,
        &gVolShapeState,
        &gVolShapeState
    }
};



static YWGUI_CtrlTemplate_T g_ctrl_template_WebTvPlayWnd[] =
{
    // play ctrl
    {(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
        WEBTV_PLAY_CTRL_X, WEBTV_PLAY_CTRL_Y, PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H,
        IDC_PIC_IPTV_BIG_PLAY,STR_EMPTY,(DWORD)&g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_PLAY],NULL},

    {(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
        WEBTV_PLAY_CTRL_X+PLAYER_CTRL_ICON_W, WEBTV_PLAY_CTRL_Y,PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H,
        IDC_PIC_IPTV_BIG_STOP,STR_EMPTY,(DWORD)&g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_STOP],NULL},

	{(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
        WEBTV_PLAY_CTRL_X+PLAYER_CTRL_ICON_W*2, WEBTV_PLAY_CTRL_Y,PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H,
        IDC_PIC_IPTV_BIG_PAUSE,STR_EMPTY,(DWORD)&g_aIpTvGraphCellArray[YWCELL_PLAYER_HIDE_PAUSE],NULL},

    {(const S8*)YWGUI_CTRL_PROGRESSBAR, YWGUI_WS_VISIBLE|YWGUI_PBS_HORZ|YWGUI_PBS_STRETCH, YWGUI_WS_EX_TRANSPARENT,
       	WEBTV_PLAY_CTRL_X+PLAYER_CTRL_ICON_W*3, WEBTV_PLAY_CTRL_Y, (WEBTV_PLAY_CTRL_W-PLAYER_CTRL_ICON_W*3), PLAYER_CTRL_ICON_H,
       	IDC_PROGRESS_IPTV_BIG, STR_EMPTY,0,&g_tProgressShapeInfo},

/*	{(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
        (WEBTV_PLAY_CTRL_X+WEBTV_PLAY_CTRL_W-PLAYER_CTRL_ICON_W), WEBTV_PLAY_CTRL_Y,PLAYER_CTRL_ICON_W, PLAYER_CTRL_ICON_H,
        IDC_PIC_IPTV_BIG_PIP,STR_EMPTY,(DWORD)&g_aIpTvGraphCellArray[YWCELL_KEY_PIP],NULL},*/

/*    {YWGUI_CTRL_STATIC,YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER,YWGUI_WS_EX_TRANSPARENT,
        (WEBTV_PLAY_CTRL_X+WEBTV_PLAY_CTRL_W-WEBTV_PLAY_TIME_W),WEBTV_PLAY_CTRL_Y,
        WEBTV_PLAY_TIME_W, PLAYER_CTRL_ICON_H,
        IDC_TXT_WEBTV_BIG_TIME,STR_EMPTY,0,&g_tTxtBlackShapInfo},*/

    {(const S8*)YWGUI_CTRL_STATIC,YWGUI_SS_LEFT|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE|YWGUI_WS_EX_TRANSPARENT,
        1030, 190, 600, 64,
        IDC_TXT_IPTV_VOLUME_BK,STR_EMPTY,0,&gVolBkShapeInfo},
    {(const S8*)YWGUI_CTRL_PROGRESSBAR,YWGUI_PBS_HORZ|YWGUI_PBS_STRETCH,YWGUI_WS_EX_NONE|YWGUI_WS_EX_TRANSPARENT,
        1146, 210, 440, 28,
        IDC_PROGRRESS_IPTV_VOLUME,STR_EMPTY,0,&gVolShapeInfo},
};


const YWGUI_DlgTemplate_T g_template_webTvPlayWnd =
{
    IDD_IPTV_PLAY,
    YWGUI_WS_VISIBLE,
    YWGUI_WS_EX_NONE,
    0,
    0,
    YWPUBLIC_OSD_W,
    YWPUBLIC_OSD_H,
    -1,
    YWGUI_ARRAY_SIZE(g_ctrl_template_WebTvPlayWnd),
    g_ctrl_template_WebTvPlayWnd,
    0,
    NULL,
};


#define __G_WAIT_WND__
#ifdef __G_WAIT_WND__

#define WAIT_WND_W  (596)
#define WAIT_WND_H  (120)

#define WAIT_OFFSET (28)


static YWGUI_GraphCell_T *gWaitBkCellSpell[] =
{
    &g_aIpTvGraphCellArray[YWCELL_WAIT_BAR_BK],
};


static YWGUI_GraphCollect_T gWaitBkGraphCollect =
{
    SPELL_GRAPH,
    1,
    gWaitBkCellSpell,
    0,
};


static YWGUI_ShapeFrame_T gWaitBkShapeFrame =
{
    FRAME_GRAPH,
    &gWaitBkGraphCollect,
    0,0,0,0,
    36,46,38,46,
};


static YWGUI_ShapeState_T gWaitBkShapeState =
{
    &gWaitBkShapeFrame,
    NULL,
    NULL,
    &g_tBlackWhiteShapeColor,
};

static YWGUI_ShapeInfo_T gWaitBkShapeInfo =
{
    {
        &gWaitBkShapeState,
        &gWaitBkShapeState,
        &gWaitBkShapeState,
        &gWaitBkShapeState
    }
};



static YWGUI_CtrlTemplate_T gCtrlTemplateWaitWnd[] =
{
    
    // icon
    {(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
        //36, 46, 90, 28,
        0, 0, 90, 28,
        IDC_PIC_WAIT,STR_EMPTY,(DWORD)&g_aIpTvGraphCellArray[YWCELL_WAIT_BAR],0},
};


const YWGUI_DlgTemplate_T gTemplateWaitWnd =
{
    IDD_WAIT,
    YWGUI_WS_VISIBLE,
    YWGUI_WS_EX_IRREGULAR,
    (YWPUBLIC_OSD_W - WAIT_WND_W) / 2,
    (YWPUBLIC_OSD_H - WAIT_WND_H) / 2,
    WAIT_WND_W,
    WAIT_WND_H,
    -1,
    YWGUI_ARRAY_SIZE(gCtrlTemplateWaitWnd),
    gCtrlTemplateWaitWnd,
    0,
    &gWaitBkShapeInfo,
};

#endif // end of #ifdef __G_WAIT_WND__



/******************************************net client config edit*************************************************/










