/*
 * File: res_layout.c
 * Author:
 * Brief: the definition of common window style,  the general window template.
 *
 */

/*
 * History:
 * ================================================================
 *
 */

#include <stdio.h>
#include "ywdefs.h"
#include "ywos.h"
#include "ywlib.h"
#include "ywmid.h"
#include "ywgui_ext.h"
#include "ywstr_id.h"
#include "res_layout.h"
#include "ywimg_ext.h"
//#include "pic.h"


#define PATH_APPRES_PIC_COMMON "/root/plugin/var/pic/common/"


YWMID_DibitmapData_T g_bmp_struct_Sign_FatherFolder;
YWMID_DibitmapData_T g_bmp_struct_Sign_Folder;

YWMID_DibitmapData_T g_bmp_struct_M_SubMenu_BK01_L;
YWMID_DibitmapData_T g_bmp_struct_M_SubMenu_BK01_M;
YWMID_DibitmapData_T g_bmp_struct_M_SubMenu_BK01_R;
YWMID_DibitmapData_T g_bmp_struct_M_SubMenu_BK02;
YWMID_DibitmapData_T g_bmp_struct_M_SubMenu_BK03;
YWMID_DibitmapData_T g_bmp_struct_M_SubMenu_BK04_L;
YWMID_DibitmapData_T g_bmp_struct_M_SubMenu_BK04_M;
YWMID_DibitmapData_T g_bmp_struct_M_SubMenu_BK04_R;

YWMID_DibitmapData_T g_bmp_struct_HelpKey_red;
YWMID_DibitmapData_T g_bmp_struct_HelpKey_green;
YWMID_DibitmapData_T g_bmp_struct_HelpKey_yellow;
YWMID_DibitmapData_T g_bmp_struct_HelpKey_blue;

YWMID_DibitmapData_T g_bmp_struct_POPFrame_01Title;
YWMID_DibitmapData_T g_bmp_struct_POPFrame_02Title;
YWMID_DibitmapData_T g_bmp_struct_POPFrame_03Title;
YWMID_DibitmapData_T g_bmp_struct_POPFrame_01;
YWMID_DibitmapData_T g_bmp_struct_POPFrame_02;
YWMID_DibitmapData_T g_bmp_struct_POPFrame_03;
YWMID_DibitmapData_T g_bmp_struct_POPFrame_04;
YWMID_DibitmapData_T g_bmp_struct_POPFrame_05;
YWMID_DibitmapData_T g_bmp_struct_POPFrame_06;
YWMID_DibitmapData_T g_bmp_struct_POPFrame_07;
YWMID_DibitmapData_T g_bmp_struct_POPFrame_08;

YWMID_DibitmapData_T g_bmp_struct_highlightlist01;
YWMID_DibitmapData_T g_bmp_struct_highlightlist_LeftKey_B;
YWMID_DibitmapData_T g_bmp_struct_highlightlist_RightKey_B;

YWMID_DibitmapData_T g_bmp_struct_Scoll_B;
YWMID_DibitmapData_T g_bmp_struct_Scoll_bk;
YWMID_DibitmapData_T g_bmp_struct_Scoll_block;
YWMID_DibitmapData_T g_bmp_struct_Scoll_T;



YWGUI_Pixel_T Color_black           = DColor_black;
YWGUI_Pixel_T Color_white           = DColor_white;
YWGUI_Pixel_T Color_blue            = DColor_blue;
YWGUI_Pixel_T Color_red             = DColor_red;
YWGUI_Pixel_T Color_green           = DColor_green;
YWGUI_Pixel_T Color_transparency    = DColor_transparency;
YWGUI_Pixel_T Color_cyan            = DColor_cyan;

YWGUI_Pixel_T Color_blue_frame_bg   = DColor_blue_frame_bg;
YWGUI_Pixel_T Color_grayblue        = DColor_grayblue;
YWGUI_Pixel_T Color_grayyellow      = DColor_grayyellow;
YWGUI_Pixel_T Color_smallviewframe  = DColor_smallviewframe;
YWGUI_Pixel_T Color_editbg          = DColor_editbg;

YWGUI_Pixel_T Color_gray            = DColor_gray;
YWGUI_Pixel_T Color_EPGLV_blue      = DColor_EPGLV_blue;
YWGUI_Pixel_T Color_EPGWeek_blue    = DColor_EPGWeek_blue;
YWGUI_Pixel_T Color_GameVALUE_black = DColor_GameVALUE_black;
YWGUI_Pixel_T Color_TetrisFrame_blue= DColor_TetrisFrame_blue;
YWGUI_Pixel_T Color_yellow          = DColor_yellow;
YWGUI_Pixel_T Color_magenta         = DColor_magenta;

YWGUI_Pixel_T Color_orange          = DColor_orange;
YWGUI_Pixel_T Color_tv_black        = DColor_tv_black;
YWGUI_Pixel_T Color_list_txt        = DColor_list_txt;
YWGUI_Pixel_T Color_find_line       = DColor_find_line;




void APP_CommonResLoad(void)
{
	YW_ErrorType_T ret = YW_NO_ERROR;

	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_Sign_FatherFolder, (const U8*)PATH_APPRES_PIC_COMMON"Sign_FatherFolder.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_Sign_Folder, (const U8*)PATH_APPRES_PIC_COMMON"Sign_Folder.png");

	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_M_SubMenu_BK01_L, (const U8*)PATH_APPRES_PIC_COMMON"M_SubMenu_BK01_L.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_M_SubMenu_BK01_M, (const U8*)PATH_APPRES_PIC_COMMON"M_SubMenu_BK01_M.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_M_SubMenu_BK01_R, (const U8*)PATH_APPRES_PIC_COMMON"M_SubMenu_BK01_R.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_M_SubMenu_BK02, (const U8*)PATH_APPRES_PIC_COMMON"M_SubMenu_BK02.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_M_SubMenu_BK03, (const U8*)PATH_APPRES_PIC_COMMON"M_SubMenu_BK03.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_M_SubMenu_BK04_L, (const U8*)PATH_APPRES_PIC_COMMON"M_SubMenu_BK04_L.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_M_SubMenu_BK04_M, (const U8*)PATH_APPRES_PIC_COMMON"M_SubMenu_BK04_M.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_M_SubMenu_BK04_R, (const U8*)PATH_APPRES_PIC_COMMON"M_SubMenu_BK04_R.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_HelpKey_red, (const U8*)PATH_APPRES_PIC_COMMON"HelpKey_red.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_HelpKey_green, (const U8*)PATH_APPRES_PIC_COMMON"HelpKey_green.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_HelpKey_yellow, (const U8*)PATH_APPRES_PIC_COMMON"HelpKey_yellow.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_HelpKey_blue, (const U8*)PATH_APPRES_PIC_COMMON"HelpKey_blue.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_POPFrame_01Title, (const U8*)PATH_APPRES_PIC_COMMON"POPFrame_01Title.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_POPFrame_02Title, (const U8*)PATH_APPRES_PIC_COMMON"POPFrame_02Title.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_POPFrame_03Title, (const U8*)PATH_APPRES_PIC_COMMON"POPFrame_03Title.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_POPFrame_01, (const U8*)PATH_APPRES_PIC_COMMON"POPFrame_01.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_POPFrame_02, (const U8*)PATH_APPRES_PIC_COMMON"POPFrame_02.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_POPFrame_03, (const U8*)PATH_APPRES_PIC_COMMON"POPFrame_03.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_POPFrame_04, (const U8*)PATH_APPRES_PIC_COMMON"POPFrame_04.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_POPFrame_05, (const U8*)PATH_APPRES_PIC_COMMON"POPFrame_05.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_POPFrame_06, (const U8*)PATH_APPRES_PIC_COMMON"POPFrame_06.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_POPFrame_07, (const U8*)PATH_APPRES_PIC_COMMON"POPFrame_07.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_POPFrame_08, (const U8*)PATH_APPRES_PIC_COMMON"POPFrame_08.png");

	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_highlightlist01, (const U8*)PATH_APPRES_PIC_COMMON"highlightlist01.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_highlightlist_LeftKey_B, (const U8*)PATH_APPRES_PIC_COMMON"highlightlist_LeftKey_B.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_highlightlist_RightKey_B, (const U8*)PATH_APPRES_PIC_COMMON"highlightlist_RightKey_B.png");

	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_Scoll_B, (const U8*)PATH_APPRES_PIC_COMMON"Scoll_B.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_Scoll_bk, (const U8*)PATH_APPRES_PIC_COMMON"Scoll_bk.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_Scoll_block, (const U8*)PATH_APPRES_PIC_COMMON"Scoll_block.png");
	ret |= YWIMG_LoadDiBitmap(&g_bmp_struct_Scoll_T, (const U8*)PATH_APPRES_PIC_COMMON"Scoll_T.png");



/*	printf("loadbitmap ret: %d\n", ret);

{
	int i = 0;

	printf("g_bmp_struct_M_SubMenu_BK01_L \n");
	printf("flag:%d \n", g_bmp_struct_M_SubMenu_BK01_L.Flags);
	printf("Depth:%d \n", g_bmp_struct_M_SubMenu_BK01_L.Depth);
	printf("Alpha:%d \n", g_bmp_struct_M_SubMenu_BK01_L.Alpha);
	printf("w:%d \n", g_bmp_struct_M_SubMenu_BK01_L.W);
	printf("h:%d \n", g_bmp_struct_M_SubMenu_BK01_L.H);
	printf("bityes:%d \n", g_bmp_struct_M_SubMenu_BK01_L.Bytes);

	for(i=0;i<=g_bmp_struct_M_SubMenu_BK01_L.Bytes; i++)
	{

		if(i%12 == 0)
			printf("\n");
		printf(" 0x%02x,", (U8)(*(U8*)(g_bmp_struct_M_SubMenu_BK01_L.pData+i)));
	}

	}*/

}

void APP_CommonResUnLoad(void)
{
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_Sign_FatherFolder);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_Sign_Folder);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_M_SubMenu_BK01_L);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_M_SubMenu_BK01_M);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_M_SubMenu_BK01_R);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_M_SubMenu_BK02);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_M_SubMenu_BK03);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_M_SubMenu_BK04_L);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_M_SubMenu_BK04_M);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_M_SubMenu_BK04_R);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_HelpKey_red);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_HelpKey_green);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_HelpKey_yellow);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_HelpKey_blue);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_POPFrame_01Title);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_POPFrame_02Title);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_POPFrame_03Title);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_POPFrame_01);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_POPFrame_02);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_POPFrame_03);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_POPFrame_04);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_POPFrame_05);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_POPFrame_06);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_POPFrame_07);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_POPFrame_08);

	YWIMG_UnLoadDiBitmap(&g_bmp_struct_highlightlist01);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_highlightlist_LeftKey_B);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_highlightlist_RightKey_B);

	YWIMG_UnLoadDiBitmap(&g_bmp_struct_Scoll_B);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_Scoll_bk);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_Scoll_block);
	YWIMG_UnLoadDiBitmap(&g_bmp_struct_Scoll_T);


}



/*--------------------------picture--------------------------*/

#define YWGUI_DEF_BMP_OPT   YWMID_DIBMP_OP_MODE_ALPHA|YWMID_DIBMP_COLOR_KEY_MODE_NONE|YWMID_DIBMP_OUTPUT_MODE_CENTER
YWGUI_GraphCell_T g_aGraphCellArray[YWCELL_NUM] =
{
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, (void*)&g_bmp_struct_Sign_FatherFolder},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, (void*)&g_bmp_struct_Sign_Folder},

    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_M_SubMenu_BK01_L},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_M_SubMenu_BK01_M},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_M_SubMenu_BK01_R},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_M_SubMenu_BK02},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_M_SubMenu_BK03},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_M_SubMenu_BK04_L},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_M_SubMenu_BK04_M},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_M_SubMenu_BK04_R},

    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_HelpKey_red},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_HelpKey_green},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_HelpKey_yellow},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_HelpKey_blue},


    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_POPFrame_01Title},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_POPFrame_02Title},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_POPFrame_03Title},
	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_POPFrame_01},
	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_POPFrame_02},
	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_POPFrame_03},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_POPFrame_04},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_POPFrame_05},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_POPFrame_06},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_POPFrame_07},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_POPFrame_08},

    {{YWGUI_DEF_BMP_OPT, {0,0,1200,52},{0,0,1200,52}}, &g_bmp_struct_highlightlist01},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_highlightlist_LeftKey_B},
    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_highlightlist_RightKey_B},

    {{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_Scoll_B},
	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_Scoll_bk},
	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_Scoll_block},
	{{YWGUI_DEF_BMP_OPT, {0,0,0,0},{0,0,0,0}}, &g_bmp_struct_Scoll_T},


};



/*--------------------------menu shape sate begin--------------------------*/
static YWGUI_GraphCell_T* g_aSubMenuFrameCellSpell[8] =
{
    /*top*/
    &g_aGraphCellArray[YWCELL_MENU_BK01L],
    &g_aGraphCellArray[YWCELL_MENU_BK01M],
    &g_aGraphCellArray[YWCELL_MENU_BK01R],

    /*left*/
    &g_aGraphCellArray[YWCELL_MENU_BK02],

    /*right*/
    &g_aGraphCellArray[YWCELL_MENU_BK03],

    /*bottom*/
    &g_aGraphCellArray[YWCELL_MENU_BK04L],
    &g_aGraphCellArray[YWCELL_MENU_BK04M],
    &g_aGraphCellArray[YWCELL_MENU_BK04R],

};

static YWGUI_GraphCollect_T g_tSubMenuFrameGraphCollect =
{
    SPELL_8GRAPH,
    8,
    g_aSubMenuFrameCellSpell,
    0,
};

static YWGUI_ShapeFrame_T g_tSubMenuFrameShapeFrame =
{
    FRAME_GRAPH,
    &g_tSubMenuFrameGraphCollect,
    0,0,0,0,
    50,124,50,62,
};

YWGUI_ShapeState_T g_tSubMenuFrameShapeState =
{
   &g_tSubMenuFrameShapeFrame,
   NULL,
   NULL,
   NULL,
};
/*--------------------------menu shape sate end--------------------------*/


YWGUI_ShapeColor_T g_tBlackWhiteShapeColor=
{
    DColor_black,
    DColor_white,
    DColor_black,
};
static YWGUI_ShapeColor_T g_tBlackYellowShapeColor=
{
    DColor_black,
    DColor_yellow,
    DColor_black,
};
static YWGUI_ShapeColor_T g_tBlackGrayShapeColor=
{
    DColor_black,
    DColor_gray,
    DColor_black,
};
static YWGUI_ShapeColor_T g_tBlackGrayblueShapeColor=
{
    DColor_black,
    DColor_grayblue,
    DColor_black,
};
static YWGUI_ShapeColor_T g_tGrayBlackShapeColor=
{
    DColor_gray,
    DColor_black,
    DColor_gray,
};
static YWGUI_ShapeColor_T g_tBlueBlackShapeColor=
{
    DColor_blue,
    DColor_black,
    DColor_blue,
};
YWGUI_ShapeColor_T g_tBlackBlueShapeColor=
{
    DColor_black,
    DColor_blue,
    DColor_black,
};
YWGUI_ShapeColor_T g_tBlackBlackShapeColor=
{
    DColor_black,
    DColor_black,
    DColor_black,
};

static YWGUI_ShapeColor_T g_tGrayBlueFrameBlackShapeColor=
{
    DColor_grayblue,
    DColor_black,
    DColor_grayblue,
};
static YWGUI_ShapeColor_T  g_tTransBlackShapeColor=
{
    DColor_transparency,
    DColor_black,
    DColor_transparency
};
static YWGUI_ShapeColor_T  g_tTransWhiteShapeColor=
{
    DColor_transparency,
    DColor_white,
    DColor_transparency
};

static YWGUI_ShapeColor_T  g_tOrangeBlackShapeColor=
{
    DColor_orange,
    DColor_black,
    DColor_black
};
static YWGUI_ShapeColor_T  g_tBlackRedShapeColor=
{
    DColor_black,
    DColor_red,
    DColor_black
};
static YWGUI_ShapeColor_T g_tGrayWhiteShapeColor=
{
    DColor_gray,
    DColor_white,
    DColor_gray,
};
static YWGUI_ShapeColor_T g_tYellowBlackShapeColor=
{
    IPTV_COLOR_YELLOW,
    DColor_black,
    IPTV_COLOR_YELLOW,
};

static YWGUI_ShapeColor_T g_tYellowBlackExShapeColor=
{
    IPTV_COLOR_YELLOW_EX,
    DColor_black,
    IPTV_COLOR_YELLOW_EX,
};

static YWGUI_ShapeColor_T g_tBlueWhiteShapeColor=
{
    IPTV_COLOR_BLUE,
    DColor_white,
    IPTV_COLOR_BLUE,
};

static YWGUI_ShapeColor_T g_tBlueWhiteExShapeColor=
{
    IPTV_COLOR_BLUE_EX,
    DColor_white,
    IPTV_COLOR_BLUE_EX,
};
static YWGUI_ShapeColor_T g_tIpTvBlackWhiteShapeColor=
{
    IPTV_COLOR_BLACK,
    DColor_white,
    IPTV_COLOR_BLACK,
};


static YWGUI_ShapeColor_T g_tGreyWhiteShapeColor=
{
    DColor_grey,
    DColor_white,
    DColor_grey,
};


static YWGUI_GraphCell_T*  g_aItemGraphCellP[1]=
{
    &g_aGraphCellArray[YWCELL_HIGHLIGHT_01],
};


static YWGUI_GraphCollect_T  g_tItemGraphCell=
{
    SPELL_GRAPH,
    1,
    g_aItemGraphCellP ,
    0,
};

YWGUI_ShapeState_T g_tItemShapeState_Normal =
{
    NULL,
    NULL,
    NULL,
    &g_tBlackWhiteShapeColor
};
YWGUI_ShapeState_T g_tItemShapeState_Disable =
{
    NULL,
    NULL,
    NULL,
    &g_tBlackGrayblueShapeColor
};
YWGUI_ShapeState_T g_tItemShapeState_AFocus =
{
    NULL,
    NULL,
    NULL,
    &g_tOrangeBlackShapeColor
};


YWGUI_LTShapeState_T g_atLTItemShapeStateNor=
{
    NULL,
    &g_tBlackWhiteShapeColor,
};

YWGUI_LTShapeInfo_T g_atLTItemShapeInfo_NoFocus =
{
    &g_atLTItemShapeStateNor,
    &g_atLTItemShapeStateNor,
    &g_atLTItemShapeStateNor,
    &g_atLTItemShapeStateNor
};

#define _RES_LAYOUT_BUTTON_
#ifdef _RES_LAYOUT_BUTTON_
/*button common ShapeInfo*/
YWGUI_ShapeInfo_T g_tButtonShapeInfo =
{
    {
        &g_tItemShapeState_Normal,                //YWGUI_LISTITEM_STATUS_NORMAL
        &g_tItemShapeState_Disable,                //YWGUI_LISTITEM_STATUS_DISABLE
        &g_tItemShapeState_AFocus,      		//YWGUI_LISTITEM_STATUS_AFOCUS
        &g_tItemShapeState_AFocus,     		 //YWGUI_LISTITEM_STATUS_SFOCUS
    }
};

static YWGUI_ShapeColor_T  g_tBtnShapeColor_normal_Ex=
{
    DColor_blue_frame_bg,
    DColor_white,
    DColor_transparency
};
static YWGUI_ShapeColor_T  g_tBtnShapeColor_disable_Ex=
{
    DColor_blue_frame_bg,
    DColor_gray,
    DColor_transparency
};


static YWGUI_ShapeState_T g_tBtnShapeState_Normal_Ex=
{
    NULL,
    NULL,
    NULL,
    &g_tBtnShapeColor_normal_Ex
};
static YWGUI_ShapeState_T g_tBtnShapeState_Disable_Ex=
{
    NULL,
    NULL,
    NULL,
    &g_tBtnShapeColor_disable_Ex
};
/*
static YWGUI_ShapeState_T g_tBtnShapeState_AFOCUS_Ex=
{
    NULL,
    NULL,
    NULL,
    &g_tBtnShapeColor_Afocus_Ex
};*/


YWGUI_ShapeInfo_T g_tButtonShapeInfo_Ex =
{
    {
        &g_tBtnShapeState_Normal_Ex,
        &g_tBtnShapeState_Disable_Ex,
        &g_tItemShapeState_AFocus,
        &g_tItemShapeState_AFocus,
    }
};

#endif

#define _RES_LAYOUT_LIST_TABLE_
#ifdef _RES_LAYOUT_LIST_TABLE_
/*list table ShapeInfo*/
static YWGUI_ShapeState_T g_tListFrameShapeState =
{
    NULL,
    NULL,
    NULL,
    &g_tBlackWhiteShapeColor,
};

YWGUI_ShapeInfo_T g_tListShapeInfo =
{
    {
        &g_tListFrameShapeState, //YWGUI_STATUS_NORMAL
        &g_tListFrameShapeState, //YWGUI_STATUS_DISABLED
        &g_tListFrameShapeState,  //YWGUI_STATUS_AFOCUS
        &g_tListFrameShapeState, //YWGUI_STATUS_SFOCUS
    }
};
#endif

#define _RES_LAYOUT_LIST_POSBAR_
#ifdef _RES_LAYOUT_LIST_POSBAR_
static YWGUI_GraphCell_T g_aScrollGraphCell[] =
{
    {{YWMID_DIBMP_OP_MODE_ALPHA|YWMID_DIBMP_COLOR_KEY_MODE_NONE|YWMID_DIBMP_OUTPUT_MODE_CENTER,
        {0,0,0,0},{0,0,28,28}},&g_bmp_struct_Scoll_T},
    {{YWMID_DIBMP_OP_MODE_ALPHA|YWMID_DIBMP_COLOR_KEY_MODE_NONE|YWMID_DIBMP_OUTPUT_MODE_CENTER,
        {0,0,0,0},{0,0,28,28}},&g_bmp_struct_Scoll_bk},
    {{YWMID_DIBMP_OP_MODE_ALPHA|YWMID_DIBMP_COLOR_KEY_MODE_NONE|YWMID_DIBMP_OUTPUT_MODE_CENTER,
        {0,0,0,0},{0,0,28,28}},&g_bmp_struct_Scoll_B},
    {{YWMID_DIBMP_OP_MODE_ALPHA|YWMID_DIBMP_COLOR_KEY_MODE_NONE|YWMID_DIBMP_OUTPUT_MODE_CENTER,
        {0,0,0,0},{0,0,28,28}},&g_bmp_struct_Scoll_block}
};

static YWGUI_GraphCell_T* g_aScrollGraphCellSpell[3] =
{
    //上
    &g_aScrollGraphCell[0],
    //中
    &g_aScrollGraphCell[1],
    //下
    &g_aScrollGraphCell[2]
};
static YWGUI_GraphCell_T* g_aScrollBKGraphCellSpell[1] =
{
    //中
    &g_aScrollGraphCell[1],
};

static YWGUI_GraphCell_T*  g_aScrollframeM[1]=
{
    &g_aScrollGraphCell[3]
};
static YWGUI_GraphCollect_T g_tScrollCollectframe =
{
    SPELL_3GRAPH_V,
    3,
    g_aScrollGraphCellSpell,
    0,
};
static YWGUI_GraphCollect_T g_tScrollCollectBK =
{
    SPELL_GRAPH_REPEAT_V,
    1,
    g_aScrollBKGraphCellSpell,
    0,
};

static YWGUI_GraphCollect_T g_tScrollCollectfck =
{
    SPELL_GRAPH_REPEAT_V,
    1,
    g_aScrollframeM,
    0,
};
static YWGUI_ShapeFrame_T g_tScrollShapeFrame =
{
    FRAME_GRAPH,
    &g_tScrollCollectframe,
    0,0,0,0,
    0,28,0,28
};

static YWGUI_ShapeState_T  g_tScrollShapeState =
{
    &g_tScrollShapeFrame,
    &g_tScrollCollectBK,
    &g_tScrollCollectfck,
    &g_tBlackWhiteShapeColor,
};

YWGUI_ShapeInfo_T g_tScrollShapeInfo =
{
    {
        &g_tScrollShapeState,//YWGUI_STATUS_NORMAL
        &g_tScrollShapeState,//YWGUI_STATUS_DISABLED
        &g_tScrollShapeState,//YWGUI_STATUS_AFOCUS
        &g_tScrollShapeState //NULL,//YWGUI_STATUS_SFOCUS
    }
};
YWGUI_PosbarDef_T  g_tPosbarDef =
{
    28,
    &g_tScrollShapeInfo,
    28
};
#endif

#define _RES_LAYOUT_LIST_COL_SHAPEINFO_
#ifdef _RES_LAYOUT_LIST_COL_SHAPEINFO_
static YWGUI_LTShapeState_T gLTShapeStateNormal =
{
	NULL,
	&g_tBlackWhiteShapeColor,
};

static YWGUI_LTShapeState_T gLTShapeStateAFocus =
{
	NULL,
	&g_tOrangeBlackShapeColor,
};

static YWGUI_LTShapeState_T gLTShapeStateDisable =
{
	NULL,
	&g_tBlackGrayShapeColor,
};
YWGUI_LTShapeInfo_T g_atColLTShapeInfo =
{
    &gLTShapeStateNormal,
    &gLTShapeStateAFocus,
    &gLTShapeStateAFocus,
    &gLTShapeStateDisable,
};
#endif

#define _RES_LAYOUT_STATIC_BLUE_BLACK_
#ifdef _RES_LAYOUT_STATIC_BLUE_BLACK_
/*static blue black table ShapeInfo*/
static YWGUI_ShapeState_T g_tTxtBlueBlackShapeState=
{
    NULL,
    NULL,
    NULL,
    &g_tBlueBlackShapeColor
};

YWGUI_ShapeInfo_T g_tTxtBlueBlackShapeInfo=
{
    {
        &g_tTxtBlueBlackShapeState,
        NULL,
        NULL,
        NULL,
    }
};
#endif

#define _RES_LAYOUT_STATIC_BLACK_BLUE_
#ifdef _RES_LAYOUT_STATIC_BLACK_BLUE_
/*static blue black table ShapeInfo*/
static YWGUI_ShapeState_T g_tTxtBlackBlueGrayShapeState=
{
    NULL,
    NULL,
    NULL,
    &g_tBlackGrayblueShapeColor
};

YWGUI_ShapeInfo_T g_tTxtBlackGrayBlueShapeInfo=
{
    {
        &g_tTxtBlackBlueGrayShapeState,
        NULL,
        NULL,
        NULL,
    }
};
#endif


#define _RES_LAYOUT_STATIC_BLACK_WHITE_
#ifdef _RES_LAYOUT_STATIC_BLACK_WHITE_
/*static black white table ShapeInfo*/

static YWGUI_ShapeState_T g_tTxtWhiteShapeState=
{
    NULL,
    NULL,
    NULL,
    &g_tBlackWhiteShapeColor
};
YWGUI_ShapeInfo_T g_tTxtBlackWhiteShapeInfo=
{
    {
        &g_tTxtWhiteShapeState,
        &g_tItemShapeState_Disable,
        NULL,
        NULL,
    }
};
#endif



#define _RES_LAYOUT_STATIC_BLACK_BLACK_
#ifdef _RES_LAYOUT_STATIC_BLACK_BLACK_
/*static black white table ShapeInfo*/

static YWGUI_ShapeState_T g_tTxtBlackShapeState=
{
    NULL,
    NULL,
    NULL,
    &g_tBlackBlackShapeColor
};
YWGUI_ShapeInfo_T g_tTxtBlackBlackShapeInfo=
{
    {
        &g_tTxtBlackShapeState,
        NULL,
        NULL,
        NULL,
    }
};
#endif


#define _RES_LAYOUT_STATIC_BLACK_BLACK_
#ifdef _RES_LAYOUT_STATIC_BLACK_BLACK_
/*static black white table ShapeInfo*/

static YWGUI_ShapeState_T g_tTxtGreyWhiteShapeState=
{
    NULL,
    NULL,
    NULL,
    &g_tGreyWhiteShapeColor
};
YWGUI_ShapeInfo_T g_tTxtGreyWhiteShapeInfo=
{
    {
        &g_tTxtGreyWhiteShapeState,
        NULL,
        NULL,
        NULL,
    }
};
#endif





#define _RES_LAYOUT_STATIC_TRAS_BLACK_
#ifdef _RES_LAYOUT_STATIC_TRAS_BLACK_
/*static black white table ShapeInfo*/

YWGUI_ShapeState_T g_tTxtTransBlackShapeState=
{
    NULL,
    NULL,
    NULL,
    &g_tTransBlackShapeColor
};

YWGUI_ShapeState_T g_tTxtTransWhiteShapeState=
{
    NULL,
    NULL,
    NULL,
    &g_tTransWhiteShapeColor
};


YWGUI_ShapeInfo_T g_tTxtTransBlackShapeInfo=
{
    {
        &g_tTxtTransBlackShapeState,
        NULL,
        NULL,
        NULL,
    }
};

YWGUI_ShapeInfo_T g_tTxtTransWhitShapeInfo=
{
    {
        &g_tTxtTransWhiteShapeState,
        NULL,
        NULL,
        NULL,
    }
};

#endif



#define _RES_LAYOUT_STATIC_BLACK_YELLOW_
#ifdef _RES_LAYOUT_STATIC_BLACK_YELLOW_
/*static black yellow table ShapeInfo*/

static YWGUI_ShapeState_T g_tTxtYellowShapeState=
{
    NULL,
    NULL,
    NULL,
    &g_tBlackYellowShapeColor
};
YWGUI_ShapeInfo_T g_tTxtBlackYellowShapeInfo=
{
    {
        &g_tTxtYellowShapeState,
        &g_tTxtYellowShapeState,
        &g_tTxtYellowShapeState,
        &g_tTxtYellowShapeState,
    }
};
#endif


#define _RES_LAYOUT_STATIC_GRAY_BLACK_
#ifdef _RES_LAYOUT_STATIC_GRAY_BLACK_
static YWGUI_ShapeState_T g_tTxtGrayBlackShapeState=
{
    NULL,
    NULL,
    NULL,
    &g_tGrayBlackShapeColor
};

YWGUI_ShapeInfo_T g_tTxtGrayBlackShapeInfo =
{
    {
        &g_tTxtGrayBlackShapeState,
        NULL,
        NULL,
        NULL,
    }
};
#endif

#define _RES_LAYOUT_STATIC_BLUEFRAME_BLACK_
#ifdef _RES_LAYOUT_STATIC_BLUEFRAME_BLACK_
static YWGUI_ShapeState_T g_tTxtGrayBlueFrameBlackShapeState=
{
    NULL,
    NULL,
    NULL,
    &g_tGrayBlueFrameBlackShapeColor
};

YWGUI_ShapeInfo_T g_tTxtGrayBlueFrameBlackShapeInfo =
{
    {
        &g_tTxtGrayBlueFrameBlackShapeState,
        NULL,
        NULL,
        NULL,
    }
};
#endif

#define _RES_LAYOUT_STATIC_ORANGE_BLACK_
#ifdef _RES_LAYOUT_STATIC_ORANGE_BLACK_
static YWGUI_ShapeState_T g_tTxtOrangeBlackShapeState=
{
    NULL,
    NULL,
    NULL,
    &g_tOrangeBlackShapeColor
};
YWGUI_ShapeInfo_T g_tTxtOrangeBlackShapeInfo =
{
    {
        &g_tTxtOrangeBlackShapeState,
        NULL,
        NULL,
        NULL,
    }
};
#endif

#define _RES_LAYOUT_STATIC_RED_BLACK_
#ifdef _RES_LAYOUT_STATIC_RED_BLACK_
static YWGUI_ShapeState_T g_tTxtBlackRedShapeState=
{
    NULL,
    NULL,
    NULL,
    &g_tBlackRedShapeColor
};
YWGUI_ShapeInfo_T g_tTxtBlackRedShapeInfo =
{
    {
        &g_tTxtBlackRedShapeState,
        NULL,
        NULL,
        NULL,
    }
};
#endif


/*************************IPTV******************************/
#define _RES_LAYOUT_IPTV_SHAPE_INFO_
#ifdef _RES_LAYOUT_IPTV_SHAPE_INFO_

YWGUI_ShapeState_T g_tIpTvItemNormalShapeState =
{
   NULL,
   NULL,
   NULL,
   &g_tBlueWhiteShapeColor
};
YWGUI_ShapeState_T g_tIpTvItemNormalExShapeState =
{
   NULL,
   NULL,
   NULL,
   &g_tBlueWhiteExShapeColor
};

static YWGUI_ShapeState_T g_tIpTvItemDisableShapeState =
{
   NULL,
   NULL,
   NULL,
   &g_tGrayWhiteShapeColor
};

YWGUI_ShapeState_T g_tIpTvItemFocusShapeState =
{
   NULL,
   NULL,
   NULL,
   &g_tYellowBlackShapeColor
};
YWGUI_ShapeState_T g_tIpTvItemFocusExShapeState =
{
   NULL,
   NULL,
   NULL,
   &g_tYellowBlackExShapeColor
};


YWGUI_ContainerShapeInfo_T g_tIpTvCntTxtShapeInfo =
{
    {
        &g_tIpTvItemNormalShapeState,//YWGUI_CONTAINER_STATUS_NORMAL
        &g_tIpTvItemDisableShapeState,//YWGUI_CONTAINER_STATUS_DISABLED
        &g_tIpTvItemFocusShapeState,//YWGUI_CONTAINER_STATUS_AFOCUS
        &g_tIpTvItemFocusShapeState,//YWGUI_CONTAINER_STATUS_SFOCUS
        &g_tIpTvItemFocusShapeState,//YWGUI_CONTAINER_STATUS_ANORMAL
        &g_tIpTvItemFocusShapeState //YWGUI_CONTAINER_STATUS_SNORMAL
    }
};
YWGUI_ContainerShapeInfo_T g_tIpTvCntTxtExShapeInfo =
{
    {
        &g_tIpTvItemNormalExShapeState,//YWGUI_CONTAINER_STATUS_NORMAL
        &g_tIpTvItemDisableShapeState,//YWGUI_CONTAINER_STATUS_DISABLED
        &g_tIpTvItemFocusExShapeState,//YWGUI_CONTAINER_STATUS_AFOCUS
        &g_tIpTvItemFocusExShapeState,//YWGUI_CONTAINER_STATUS_SFOCUS
        &g_tIpTvItemFocusExShapeState,//YWGUI_CONTAINER_STATUS_ANORMAL
        &g_tIpTvItemFocusExShapeState //YWGUI_CONTAINER_STATUS_SNORMAL
    }
};
static YWGUI_ShapeState_T g_tTpTvBlackWhiteShapeState=
{
    NULL,
    NULL,
    NULL,
    &g_tIpTvBlackWhiteShapeColor
};
static YWGUI_ShapeState_T g_tBkTranShapeState=
{
    NULL,
    NULL,
    NULL,
    &g_tTransWhiteShapeColor
};
YWGUI_ShapeInfo_T gBkTranExShapInfo=
{
    {
        &g_tTpTvBlackWhiteShapeState,
        &g_tBkTranShapeState,
        &g_tBkTranShapeState,
        &g_tBkTranShapeState,
    }
};

YWGUI_ShapeInfo_T gBkTranWhiteShapInfo=
{
    {
        &g_tBkTranShapeState,
        &g_tBkTranShapeState,
        &g_tBkTranShapeState,
        &g_tBkTranShapeState,
    }
};


#endif

YWGUI_ShapeState_T g_tSubMenuItemNormalShapeState =
{
   NULL,
   NULL,
   NULL,
   &g_tBlackWhiteShapeColor
};

YWGUI_ShapeState_T g_tSubMenuItemFocusShapeState =
{
   NULL,
   &g_tItemGraphCell,
   NULL,
   &g_tBlackBlackShapeColor
};


static YWGUI_ShapeState_T g_tSubMenuItemDisableShapeState =
{
   NULL,
   NULL,
   NULL,
   &g_tBlackBlueShapeColor
};


YWGUI_ContainerShapeInfo_T g_tCommTxtCntShapeInfo =
{
    {
        &g_tSubMenuItemNormalShapeState,//YWGUI_CONTAINER_STATUS_NORMAL
        &g_tSubMenuItemDisableShapeState,//YWGUI_CONTAINER_STATUS_DISABLED
        &g_tSubMenuItemFocusShapeState,//YWGUI_CONTAINER_STATUS_AFOCUS
        &g_tSubMenuItemFocusShapeState,//YWGUI_CONTAINER_STATUS_SFOCUS
        &g_tSubMenuItemFocusShapeState,//YWGUI_CONTAINER_STATUS_ANORMAL
        &g_tSubMenuItemFocusShapeState //YWGUI_CONTAINER_STATUS_SNORMAL

    }
};






#define _RES_LAYOUT_SEDIT_SHAPE_INFO_
#ifdef _RES_LAYOUT_SEDIT_SHAPE_INFO_
static YWGUI_ShapeFrame_T g_aEditShapeFrame =
{
    FRAME_NO,
    NULL,
    0,0,0,0,
    0,0,0,0
};
static YWGUI_ShapeColor_T  g_tEditNormalShapeColor=
{
    DColor_black,
    DColor_white,
    DColor_transparency
};
static YWGUI_ShapeColor_T  g_tEditDisableShapeColor=
{
    DColor_editbg,
    DColor_white,
    DColor_transparency
};

static YWGUI_ShapeColor_T  g_tOscamRenameEditDisableShapeColor=
{
    DColor_oscameditbg,
    DColor_white,
    DColor_transparency
};

static YWGUI_ShapeColor_T  g_tEditAfocusShapeColor=
{
    DColor_orange,
    DColor_black,
    DColor_transparency
};
static YWGUI_ShapeColor_T  g_tEditAfocusShapeColor_Ex=
{
    DColor_orange,
    DColor_red,
    DColor_transparency
};
YWGUI_ShapeState_T g_tEditShapeState_Normal =
{
    &g_aEditShapeFrame,
    NULL,
    NULL,
    &g_tEditNormalShapeColor
};
YWGUI_ShapeState_T g_tEditShapeState_Disable =
{
    &g_aEditShapeFrame,
    NULL,
    NULL,
    &g_tEditDisableShapeColor
};

YWGUI_ShapeState_T g_tOscamRenameEditShapeState_Disable =
{
    &g_aEditShapeFrame,
    NULL,
    NULL,
    &g_tOscamRenameEditDisableShapeColor
};


YWGUI_ShapeState_T g_tEditShapeState_AFocus=
{
    &g_aEditShapeFrame,
    NULL,
    NULL,
    &g_tEditAfocusShapeColor
};
YWGUI_ShapeState_T g_tEditShapeState_AFocus_EX=
{
    &g_aEditShapeFrame,
    NULL,
    NULL,
    &g_tEditAfocusShapeColor_Ex
};
YWGUI_ShapeInfo_T g_tEditShapeInfo =
{
    {
        &g_tEditShapeState_Normal,//YWGUI_STATUS_NORMAL
        &g_tEditShapeState_Disable,//YWGUI_STATUS_DISABLED
        &g_tEditShapeState_AFocus,//YWGUI_STATUS_AFOCUS
        &g_tEditShapeState_AFocus//NULL,//YWGUI_STATUS_SFOCUS

    }
};
YWGUI_ShapeInfo_T g_tOscamRenameEditShapeInfo =
{
    {
        &g_tEditShapeState_Normal,//YWGUI_STATUS_NORMAL
        &g_tOscamRenameEditShapeState_Disable,//YWGUI_STATUS_DISABLED
        &g_tEditShapeState_AFocus,//YWGUI_STATUS_AFOCUS
        &g_tEditShapeState_AFocus//NULL,//YWGUI_STATUS_SFOCUS

    }
};

YWGUI_ShapeInfo_T g_tEditShapeInfo_Ex =
{
    {
        &g_tItemShapeState_Normal,                //YWGUI_LISTITEM_STATUS_NORMAL
        &g_tItemShapeState_Disable,                //YWGUI_LISTITEM_STATUS_DISABLE
        &g_tItemShapeState_AFocus,      		//YWGUI_LISTITEM_STATUS_AFOCUS
        &g_tItemShapeState_AFocus,     		 //YWGUI_LISTITEM_STATUS_SFOCUS
    }
};

#endif

#define _RES_LAYOUT_POPDLG_SHAPE_INFO_
#ifdef _RES_LAYOUT_POPDLG_SHAPE_INFO_

/*****************************PopFrame1(have head) 公用图形结构 start******************************/

static YWGUI_GraphCell_T* g_aPopDlg1CellSpell[8] =
{
    //上边
    &g_aGraphCellArray[YWCELL_POPFRAME_01TITLE],
    &g_aGraphCellArray[YWCELL_POPFRAME_02TITLE],
    &g_aGraphCellArray[YWCELL_POPFRAME_03TITLE],

    //左
    &g_aGraphCellArray[YWCELL_POPFRAME_04],

    //右
    &g_aGraphCellArray[YWCELL_POPFRAME_05],

    //下边
    &g_aGraphCellArray[YWCELL_POPFRAME_06],
    &g_aGraphCellArray[YWCELL_POPFRAME_07],
    &g_aGraphCellArray[YWCELL_POPFRAME_08],
};
static YWGUI_GraphCollect_T g_tPopDlg1GraphCollect =
{
    SPELL_8GRAPH,
    8,
    g_aPopDlg1CellSpell,
    0,
};
static YWGUI_ShapeFrame_T g_tPopDlg1ShapeFrame =
{
    FRAME_GRAPH,
    &g_tPopDlg1GraphCollect,
    0,0,0,0,
    10,64,10,14,
};
/**************************YWGUI_ShapeState_T(for user)结构***********************/
YWGUI_ShapeState_T g_tPopDlgHaveHeadShapeState =
{
   &g_tPopDlg1ShapeFrame,
   NULL,
   NULL,
   &g_tBlackWhiteShapeColor,
};

YWGUI_ShapeInfo_T g_tPopDlgHaveHeadShapeInfo =
{
    {
        &g_tPopDlgHaveHeadShapeState,
        &g_tPopDlgHaveHeadShapeState,
        &g_tPopDlgHaveHeadShapeState,
        &g_tPopDlgHaveHeadShapeState
    }
};
/*****************************PopFrame(have head) 公用图形结构 end******************************/
#endif


#define _RES_LAYOUT_POPDLG_NOHEAD_SHAPE_INFO_
#ifdef _RES_LAYOUT_POPDLG_NOHEAD_SHAPE_INFO_

/*****************************PopFrame2(no head) 公用图形结构 start******************************/
static YWGUI_GraphCell_T* g_aPopDlg2CellSpell[8] =
{
    //上边
    &g_aGraphCellArray[YWCELL_POPFRAME_01],
    &g_aGraphCellArray[YWCELL_POPFRAME_02],
    &g_aGraphCellArray[YWCELL_POPFRAME_03],

    //左
    &g_aGraphCellArray[YWCELL_POPFRAME_04],

    //右
    &g_aGraphCellArray[YWCELL_POPFRAME_05],

    //下边
    &g_aGraphCellArray[YWCELL_POPFRAME_06],
    &g_aGraphCellArray[YWCELL_POPFRAME_07],
    &g_aGraphCellArray[YWCELL_POPFRAME_08],
};
static YWGUI_GraphCollect_T g_tPopDlg2GraphCollect =
{
    SPELL_8GRAPH,
    8,
    g_aPopDlg2CellSpell,
    0,
};
static YWGUI_ShapeFrame_T g_tPopDlg2ShapeFrame =
{
    FRAME_GRAPH,
    &g_tPopDlg2GraphCollect,
    0,0,0,0,
    18,22,18,22,
};
/**************************YWGUI_ShapeState_T(for user)结构***********************/
YWGUI_ShapeState_T g_tPopDlgNoheadShapeState =
{
   &g_tPopDlg2ShapeFrame,
   NULL,
   NULL,
   &g_tBlackWhiteShapeColor,
};

/*LJF 2009/12/31 add*/
YWGUI_ShapeInfo_T g_tPopDlgNoheadShapeInfo =
{
    {
        &g_tPopDlgNoheadShapeState,
        &g_tPopDlgNoheadShapeState,
        &g_tPopDlgNoheadShapeState,
        &g_tPopDlgNoheadShapeState
    }
};
/*****************************PopFrame(no head) 公用图形结构 end******************************/
#endif


#define _RES_LAYOUT_LRCB_SHAPE_INFO_
#ifdef _RES_LAYOUT_LRCB_SHAPE_INFO_

static YWGUI_GraphCell_T*  g_aLRCBItemGraphCellP[3]=
{
    //Progress P Bg
    &g_aGraphCellArray[YWCELL_HIGHLIGHT_LEFTKEY],
    &g_aGraphCellArray[YWCELL_HIGHLIGHT_01],
    &g_aGraphCellArray[YWCELL_HIGHLIGHT_RIGHTKEY],
};

static YWGUI_GraphCollect_T  g_tLRCBItemGraphCell=
{
    SPELL_3GRAPH_H,
    3,
    g_aLRCBItemGraphCellP ,
    0,
};
static YWGUI_ShapeState_T g_tLRCBItemShapeState_Afocus=
{
    NULL,
    &g_tLRCBItemGraphCell,
    NULL,
    &g_tTransBlackShapeColor,
};



YWGUI_ListItemShapeInfo_T g_tListItemShapeInfo =
{
    {
        &g_tItemShapeState_Normal,                //YWGUI_LISTITEM_STATUS_NORMAL
        &g_tItemShapeState_Normal,                //YWGUI_LISTITEM_STATUS_DISABLE
        &g_tItemShapeState_AFocus,      		//YWGUI_LISTITEM_STATUS_AFOCUS
        &g_tItemShapeState_AFocus,     		 //YWGUI_LISTITEM_STATUS_SFOCUS
        &g_tItemShapeState_Normal,               	// YWGUI_LISTITEM_STATUS_CHECKED
        &g_tItemShapeState_AFocus,          		//YWGUI_LISTITEM_STATUS_SKIP
    }
};



YWGUI_LRCBListAddData_T g_tLRCBListAddData =
{
    &g_tListItemShapeInfo,
    &g_tPosbarDef
};




//edit
static YWGUI_ShapeState_T g_tLRCDisableShapeState =
{
   NULL,
   NULL,
   NULL,
   &g_tBlackGrayblueShapeColor
};
YWGUI_ShapeState_T g_tLRCNormalShapeState =
{
   NULL,
   NULL,
   NULL,
   &g_tBlackWhiteShapeColor
};
YWGUI_LRCBTextShapeInfo_T g_tLRCBEditShapeInfo =
{
    {
        &g_tLRCNormalShapeState,     //YWGUI_LRCBEDIT_STATUS_NORMAL
        &g_tLRCDisableShapeState, //YWGUI_LRCBEDIT_STATUS_DISABLED
        &g_tLRCBItemShapeState_Afocus,  //YWGUI_LRCBEDIT_STATUS_NOLIST_AFOCUS
        &g_tLRCBItemShapeState_Afocus,  //YWGUI_LRCBEDIT_STATUS_LIST_AFOCUS
        &g_tLRCBItemShapeState_Afocus,  //YWGUI_LRCBEDIT_STATUS_NOLIST_SFOCUS
        &g_tLRCBItemShapeState_Afocus,  //YWGUI_LRCBEDIT_STATUS_LIST_SFOCUS
    }
};
#endif

#define _CONTAINER_ITEM_CTRL_SHAPE_INFO_
#ifdef _CONTAINER_ITEM_CTRL_SHAPE_INFO_

YWGUI_ContainerShapeInfo_T g_tCommItemCntShapeInfo =
{
    {
        &g_tItemShapeState_Normal,//YWGUI_CONTAINER_STATUS_NORMAL
        &g_tItemShapeState_Disable,//YWGUI_CONTAINER_STATUS_DISABLED
        &g_tItemShapeState_AFocus,//YWGUI_CONTAINER_STATUS_AFOCUS
        &g_tItemShapeState_AFocus,//YWGUI_CONTAINER_STATUS_SFOCUS
        &g_tItemShapeState_AFocus,//YWGUI_CONTAINER_STATUS_ANORMAL
        &g_tItemShapeState_AFocus //YWGUI_CONTAINER_STATUS_SNORMAL

    }
};

#endif



#define _COMMON_DLG_
#ifdef _COMMON_DLG_

//entry dlg
const YWGUI_DlgTemplate_T g_template_mcasentry=
{
    IDD_MCAS_ENTRY,
	YWGUI_WS_VISIBLE,
	YWGUI_WS_EX_NONE,
	0,
	0,
    1,
    1,
    STR_EMPTY,
    0,
    NULL,
    0,
    NULL
};

//rename dlg

#define BTN_START_X 210
#define BTN_START_Y 120
#define BTN_W 52
#define BTN_H 52
#define BTN_GAP 62
#define KEYBOARD_RAW_NUM 7
#define KEYBOARD_COL_NUM 13


static YWGUI_CtrlTemplate_T g_ctrl_template_pluginrename[] =
{
	//list table title
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_TITLECTRL|YWGUI_WS_EX_TRANSPARENT,
        (YWPUBLIC_COMM_DLG_W - 400) / 2, 38, 400, 64,
        IDC_TXT_PLUGIN_RENAME_TITLE, STR_EMPTY,0,0},

	{(const S8*)YWGUI_CTRL_SEDIT, YWGUI_WS_VISIBLE|YWGUI_ES_LEFT|YWGUI_ES_VCENTER,YWGUI_WS_EX_NOTIFY,
       200, 50, 820,52,
       IDC_EDIT_PLUGIN_RENAME_CONTENT,
       STR_EMPTY,
       0,
       &g_tEditShapeInfo },

	  //keyboard
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X, BTN_START_Y, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_1_1, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*1, BTN_START_Y, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_1_2, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*2, BTN_START_Y, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_1_3, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*3, BTN_START_Y, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_1_4, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*4, BTN_START_Y, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_1_5, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*5, BTN_START_Y, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_1_6, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*6, BTN_START_Y, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_1_7, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*7, BTN_START_Y, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_1_8, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*8, BTN_START_Y, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_1_9, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*9, BTN_START_Y, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_1_10, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*10, BTN_START_Y, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_1_11, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*11, BTN_START_Y, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_1_12, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*12, BTN_START_Y, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_1_13, 0, 0, &g_tButtonShapeInfo_Ex},

    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X, BTN_START_Y+BTN_GAP, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_2_1, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*1, BTN_START_Y+BTN_GAP, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_2_2, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*2, BTN_START_Y+BTN_GAP, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_2_3, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*3, BTN_START_Y+BTN_GAP, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_2_4, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*4, BTN_START_Y+BTN_GAP, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_2_5, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*5, BTN_START_Y+BTN_GAP, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_2_6, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*6, BTN_START_Y+BTN_GAP, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_2_7, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*7, BTN_START_Y+BTN_GAP, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_2_8, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*8, BTN_START_Y+BTN_GAP, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_2_9, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*9, BTN_START_Y+BTN_GAP, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_2_10, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*10, BTN_START_Y+BTN_GAP, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_2_11, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*11, BTN_START_Y+BTN_GAP, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_2_12, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*12, BTN_START_Y+BTN_GAP, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_2_13, 0, 0, &g_tButtonShapeInfo_Ex},

    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X, BTN_START_Y+BTN_GAP*2, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_3_1, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*1, BTN_START_Y+BTN_GAP*2, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_3_2, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*2, BTN_START_Y+BTN_GAP*2, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_3_3, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*3, BTN_START_Y+BTN_GAP*2, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_3_4, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*4, BTN_START_Y+BTN_GAP*2, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_3_5, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*5, BTN_START_Y+BTN_GAP*2, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_3_6, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*6, BTN_START_Y+BTN_GAP*2, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_3_7, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*7, BTN_START_Y+BTN_GAP*2, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_3_8, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*8, BTN_START_Y+BTN_GAP*2, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_3_9, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*9, BTN_START_Y+BTN_GAP*2, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_3_10, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*10, BTN_START_Y+BTN_GAP*2, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_3_11, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*11, BTN_START_Y+BTN_GAP*2, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_3_12, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*12, BTN_START_Y+BTN_GAP*2, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_3_13, 0, 0, &g_tButtonShapeInfo_Ex},

	{(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X, BTN_START_Y+BTN_GAP*3, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_4_1, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*1, BTN_START_Y+BTN_GAP*3, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_4_2, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*2, BTN_START_Y+BTN_GAP*3, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_4_3, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*3, BTN_START_Y+BTN_GAP*3, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_4_4, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*4, BTN_START_Y+BTN_GAP*3, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_4_5, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*5, BTN_START_Y+BTN_GAP*3, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_4_6, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*6, BTN_START_Y+BTN_GAP*3, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_4_7, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*7, BTN_START_Y+BTN_GAP*3, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_4_8, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*8, BTN_START_Y+BTN_GAP*3, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_4_9, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*9, BTN_START_Y+BTN_GAP*3, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_4_10, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*10, BTN_START_Y+BTN_GAP*3, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_4_11, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*11, BTN_START_Y+BTN_GAP*3, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_4_12, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*12, BTN_START_Y+BTN_GAP*3, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_4_13, 0, 0, &g_tButtonShapeInfo_Ex},

    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X, BTN_START_Y+BTN_GAP*4, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_5_1, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*1, BTN_START_Y+BTN_GAP*4, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_5_2, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*2, BTN_START_Y+BTN_GAP*4, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_5_3, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*3, BTN_START_Y+BTN_GAP*4, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_5_4, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*4, BTN_START_Y+BTN_GAP*4, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_5_5, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*5, BTN_START_Y+BTN_GAP*4, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_5_6, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*6, BTN_START_Y+BTN_GAP*4, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_5_7, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*7, BTN_START_Y+BTN_GAP*4, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_5_8, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*8, BTN_START_Y+BTN_GAP*4, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_5_9, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*9, BTN_START_Y+BTN_GAP*4, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_5_10, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*10, BTN_START_Y+BTN_GAP*4, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_5_11, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*11, BTN_START_Y+BTN_GAP*4, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_5_12, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*12, BTN_START_Y+BTN_GAP*4, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_5_13, 0, 0, &g_tButtonShapeInfo_Ex},

    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X, BTN_START_Y+BTN_GAP*5, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_6_1, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*1, BTN_START_Y+BTN_GAP*5, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_6_2, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*2, BTN_START_Y+BTN_GAP*5, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_6_3, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*3, BTN_START_Y+BTN_GAP*5, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_6_4, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*4, BTN_START_Y+BTN_GAP*5, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_6_5, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*5, BTN_START_Y+BTN_GAP*5, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_6_6, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*6, BTN_START_Y+BTN_GAP*5, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_6_7, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*7, BTN_START_Y+BTN_GAP*5, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_6_8, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*8, BTN_START_Y+BTN_GAP*5, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_6_9, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*9, BTN_START_Y+BTN_GAP*5, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_6_10, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*10, BTN_START_Y+BTN_GAP*5, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_6_11, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*11, BTN_START_Y+BTN_GAP*5, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_6_12, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*12, BTN_START_Y+BTN_GAP*5, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_6_13, 0, 0, &g_tButtonShapeInfo_Ex},

    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X, BTN_START_Y+BTN_GAP*6, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_7_1, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*1, BTN_START_Y+BTN_GAP*6, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_7_2, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*2, BTN_START_Y+BTN_GAP*6, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_7_3, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*3, BTN_START_Y+BTN_GAP*6, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_7_4, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*4, BTN_START_Y+BTN_GAP*6, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_7_5, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*5, BTN_START_Y+BTN_GAP*6, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_7_6, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*6, BTN_START_Y+BTN_GAP*6, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_7_7, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*7, BTN_START_Y+BTN_GAP*6, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_7_8, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*8, BTN_START_Y+BTN_GAP*6, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_7_9, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*9, BTN_START_Y+BTN_GAP*6, BTN_W*2+10, BTN_H, IDC_BTN_PLUGIN_RENAME_7_10, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*11, BTN_START_Y+BTN_GAP*6, BTN_W*2+10, BTN_H, IDC_BTN_PLUGIN_RENAME_7_11, 0, 0, &g_tButtonShapeInfo_Ex},
   /* {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*11, BTN_START_Y+BTN_GAP*6, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_7_12, 0, 0, &g_tBtnShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        BTN_START_X+BTN_GAP*12, BTN_START_Y+BTN_GAP*6, BTN_W, BTN_H, IDC_BTN_PLUGIN_RENAME_7_13, 0, 0, &g_tBtnShapeInfo_Ex},
*/

	/*function ctrl*/
    {(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
       HOTKEY_START_X, HOTKEY_START_Y,46,46,
       IDC_PIC_PLUGIN_RENAME_CONFIRM,
       STR_EMPTY,
       (DWORD)&g_aGraphCellArray[YWCELL_RED],
       0},
    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_LEFT, YWGUI_WS_EX_TRANSPARENT,
        HOTKEY_START_X+50, HOTKEY_START_Y, 150, CTRL_COMMON_HIGH,
        IDC_TXT_PLUGIN_RENAME_CONFIRM,
        STR_EMPTY,
        0,
        &g_tTxtBlackWhiteShapeInfo},
    {(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
       HOTKEY_START_X+200, HOTKEY_START_Y,46,46,
       IDC_PIC_PLUGIN_RENAME_PREV,
       STR_EMPTY,
       (DWORD)&g_aGraphCellArray[YWCELL_GREEN],
       0},
   {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_LEFT, YWGUI_WS_EX_TRANSPARENT,
        HOTKEY_START_X+250, HOTKEY_START_Y, 150, CTRL_COMMON_HIGH,
        IDC_TXT_PLUGIN_RENAME_PREV,
        STR_EMPTY,
        0,
        &g_tTxtBlackWhiteShapeInfo},
    {(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
       HOTKEY_START_X+400, HOTKEY_START_Y,46,46,
       IDC_PIC_PLUGIN_RENAME_NEXT,
       STR_EMPTY,
       (DWORD)&g_aGraphCellArray[YWCELL_YELLOW],
       0},
    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_LEFT, YWGUI_WS_EX_TRANSPARENT,
        HOTKEY_START_X+450, HOTKEY_START_Y, 150, CTRL_COMMON_HIGH,
        IDC_TXT_PLUGIN_RENAME_NEXT,
        STR_EMPTY,
        0,
        &g_tTxtBlackWhiteShapeInfo},
    {(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
       HOTKEY_START_X+600, HOTKEY_START_Y,46,46,
       IDC_PIC_PLUGIN_RENAME_CLEAR,
       STR_EMPTY,
       (DWORD)&g_aGraphCellArray[YWCELL_BLUE],
       0},
    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_LEFT, YWGUI_WS_EX_TRANSPARENT,
        HOTKEY_START_X+650, HOTKEY_START_Y, 150, CTRL_COMMON_HIGH,
        IDC_TXT_PLUGIN_RENAME_CLEAR,
        STR_EMPTY,
        0,
        &g_tTxtBlackWhiteShapeInfo},
};

const YWGUI_DlgTemplate_T g_template_pluginrename =
{
    IDD_PLUGIN_RENAME,
    YWGUI_WS_VISIBLE,
    YWGUI_WS_EX_NONE,
    (YWPUBLIC_OSD_W - YWPUBLIC_COMM_DLG_W)/2,
    (YWPUBLIC_OSD_H - YWPUBLIC_COMM_DLG_H)/2,
	YWPUBLIC_COMM_DLG_W,
	YWPUBLIC_COMM_DLG_H,
    -1,
    YWGUI_ARRAY_SIZE(g_ctrl_template_pluginrename),
    g_ctrl_template_pluginrename,
    0,
    NULL
};



#endif

#define _POP_INFO_
#ifdef _POP_INFO_
static YWGUI_CtrlTemplate_T g_ctrl_template_popinfocfg[] =
{

	//title
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_TITLECTRL|YWGUI_WS_EX_TRANSPARENT,
        (POP_DLG_W-400)/2, 0, 400, 64,
        IDC_TXT_POP_INFO_TITLE, STR_EMPTY, 0,0},


    /* text*/
    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_CENTER, YWGUI_WS_EX_TRANSPARENT,
        10, 10, (POP_DLG_W-20), POP_DLG_H-78-20, IDC_TXT_POP_INFO, STR_EMPTY, 0, &g_tTxtBlackWhiteShapeInfo},

};

const YWGUI_DlgTemplate_T g_template_popinfocfg =
{
    IDD_POP_INFO,
    YWGUI_WS_VISIBLE,
    YWGUI_WS_EX_NONE,
    (YWPUBLIC_OSD_W - POP_DLG_W)/2,
    (YWPUBLIC_OSD_H - POP_DLG_H)/2,
    POP_DLG_W,
    POP_DLG_H,
    -1,
    YWGUI_ARRAY_SIZE(g_ctrl_template_popinfocfg),
    g_ctrl_template_popinfocfg,
    0,
    NULL
};
#endif


#define _CONFIRM_INFO_
#ifdef _CONFIRM_INFO_
static YWGUI_CtrlTemplate_T g_ctrl_template_confirminfocfg[] =
{

	//title
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_TITLECTRL|YWGUI_WS_EX_TRANSPARENT,
        (POP_DLG_W-400)/2, 0, 400, 64,
        IDC_TXT_CONFIRM_INFO_TITLE, STR_EMPTY, 0,0},


    /* text*/
    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_CENTER, YWGUI_WS_EX_TRANSPARENT,
        10, 20, (POP_DLG_W-20), 52*2, IDC_TXT_CONFIRM_INFO, STR_EMPTY, 0, &g_tTxtBlackWhiteShapeInfo},



    /* BTN*/
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        80, 110, 104, 52,
        IDC_BTN_CONFIRM_YES, 0, 0, &g_tButtonShapeInfo_Ex},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_NONE|YWGUI_WS_EX_NOTIFY,
        (80+104+140), 110, 104, 52,
        IDC_BTN_CONFIRM_NO, 0, 0, &g_tButtonShapeInfo_Ex},
};

const YWGUI_DlgTemplate_T g_template_confirminfocfg =
{
    IDD_CONFIRM_INFO,
    YWGUI_WS_VISIBLE,
    YWGUI_WS_EX_NONE,
    (YWPUBLIC_OSD_W - POP_DLG_W)/2,
    (YWPUBLIC_OSD_H - POP_DLG_H)/2,
    POP_DLG_W,
    POP_DLG_H,
    -1,
    YWGUI_ARRAY_SIZE(g_ctrl_template_confirminfocfg),
    g_ctrl_template_confirminfocfg,
    0,
    NULL
};
#endif




#define _CONFIRM_INFO_
#ifdef _CONFIRM_INFO_
#define LANGUAGE_SET_W 254
static YWGUI_LRCombobox_AddData_T LanguageSetDown4LRCBAddData =
{
    //Edit的外形
    &g_tLRCBEditShapeInfo,

    //List的位置
    0, 52, LANGUAGE_SET_W, (52*4+78),

    //List的外形
    &g_tPopDlgHaveHeadShapeInfo,
    &g_tLRCBListAddData
};


static YWGUI_CtrlTemplate_T g_ctrl_template_languageset[] =
{

	//title
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_TITLECTRL|YWGUI_WS_EX_TRANSPARENT,
        (POP_DLG_W-400)/2, 0, 400, 64,
        IDC_TXT_LANGUAGE_SET_TITLE, STR_LANGUAGE_SET, 0,0},

    /* text*/
    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_LEFT, YWGUI_WS_EX_TRANSPARENT,
        10, 0, LANGUAGE_SET_W, CTRL_COMMON_HIGH,
        IDC_TXT_LANGUAGE_SET, STR_LANGUAGE_SET, 0, &g_tTxtBlackWhiteShapeInfo},

    /* LRC*/
    {(const S8*)YWGUI_CTRL_LRCOMBOBOX, YWGUI_WS_VISIBLE|YWGUI_LRCBS_AUTOSCROLL|YWGUI_LRCBS_CENTER|YWGUI_LRCBS_VCENTER|YWGUI_LRCBS_EXITKEYHIDELIST,YWGUI_WS_EX_NOTIFY,
        10+LANGUAGE_SET_W, 0, LANGUAGE_SET_W, CTRL_COMMON_HIGH,
        IDC_LRC_LANGUAGE_LIST, 0, (DWORD)&LanguageSetDown4LRCBAddData, 0},
};

const YWGUI_DlgTemplate_T g_template_languageset =
{
    IDD_LANGUAGE_SET,
    YWGUI_WS_VISIBLE,
    YWGUI_WS_EX_NONE,
    (YWPUBLIC_OSD_W - (POP_DLG_W))/2,
    (YWPUBLIC_OSD_H - 172)/2,
    (POP_DLG_W),
    172,
    -1,
    YWGUI_ARRAY_SIZE(g_ctrl_template_languageset),
    g_ctrl_template_languageset,
    0,
    NULL
};


#endif


