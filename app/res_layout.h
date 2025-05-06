#ifndef _RES_LAYOUT_H_20080416_
#define  _RES_LAYOUT_H_20080416_

#include "ywstr_id.h"
#include "ywstring.h"


#define LZ_ADD_WINDOW

#define CTRL_COMMON_HIGH (52)
#define STR_EMPTY (0)

#define YWPUBLIC_OSD_W             1920
#define YWPUBLIC_OSD_H             1080

#define YWPUBLIC_COMM_DLG_W        1320
#define YWPUBLIC_COMM_DLG_H        856

#define POP_DLG_W 548
#define POP_DLG_H 272




#define HOTKEY_START_Y 				618
#define HOTKEY_START_X 				50


#define PLAYER_CTRL_ICON_W      (68)
#define PLAYER_CTRL_ICON_H      (42)


extern YWMID_DibitmapData_T g_bmp_struct_Load;


/*the ID of window*/
typedef enum
{
    IDD_MCAS_ENTRY = 1,


	//pop info
	IDD_POP_INFO,
	IDC_TXT_POP_INFO_TITLE,
	IDC_TXT_POP_INFO,

	IDD_CONFIRM_INFO,
	IDC_TXT_CONFIRM_INFO_TITLE,
	IDC_TXT_CONFIRM_INFO,
	IDC_BTN_CONFIRM_YES,
	IDC_BTN_CONFIRM_NO,

	//language setting
	IDD_LANGUAGE_SET,
	IDC_TXT_LANGUAGE_SET_TITLE,
	IDC_TXT_LANGUAGE_SET,
	IDC_LRC_LANGUAGE_LIST,


	//plugin rename
	IDD_PLUGIN_RENAME,
	IDC_TXT_PLUGIN_RENAME_TITLE,
	IDC_EDIT_PLUGIN_RENAME_CONTENT,
	IDC_BTN_PLUGIN_RENAME_1_1,
	IDC_BTN_PLUGIN_RENAME_1_2,
	IDC_BTN_PLUGIN_RENAME_1_3,
	IDC_BTN_PLUGIN_RENAME_1_4,
	IDC_BTN_PLUGIN_RENAME_1_5,
	IDC_BTN_PLUGIN_RENAME_1_6,
	IDC_BTN_PLUGIN_RENAME_1_7,
	IDC_BTN_PLUGIN_RENAME_1_8,
	IDC_BTN_PLUGIN_RENAME_1_9,
	IDC_BTN_PLUGIN_RENAME_1_10,
	IDC_BTN_PLUGIN_RENAME_1_11,
	IDC_BTN_PLUGIN_RENAME_1_12,
	IDC_BTN_PLUGIN_RENAME_1_13,
	IDC_BTN_PLUGIN_RENAME_2_1,
	IDC_BTN_PLUGIN_RENAME_2_2,
	IDC_BTN_PLUGIN_RENAME_2_3,
	IDC_BTN_PLUGIN_RENAME_2_4,
	IDC_BTN_PLUGIN_RENAME_2_5,
	IDC_BTN_PLUGIN_RENAME_2_6,
	IDC_BTN_PLUGIN_RENAME_2_7,
	IDC_BTN_PLUGIN_RENAME_2_8,
	IDC_BTN_PLUGIN_RENAME_2_9,
	IDC_BTN_PLUGIN_RENAME_2_10,
	IDC_BTN_PLUGIN_RENAME_2_11,
	IDC_BTN_PLUGIN_RENAME_2_12,
	IDC_BTN_PLUGIN_RENAME_2_13,
	IDC_BTN_PLUGIN_RENAME_3_1,
	IDC_BTN_PLUGIN_RENAME_3_2,
	IDC_BTN_PLUGIN_RENAME_3_3,
	IDC_BTN_PLUGIN_RENAME_3_4,
	IDC_BTN_PLUGIN_RENAME_3_5,
	IDC_BTN_PLUGIN_RENAME_3_6,
	IDC_BTN_PLUGIN_RENAME_3_7,
	IDC_BTN_PLUGIN_RENAME_3_8,
	IDC_BTN_PLUGIN_RENAME_3_9,
	IDC_BTN_PLUGIN_RENAME_3_10,
	IDC_BTN_PLUGIN_RENAME_3_11,
	IDC_BTN_PLUGIN_RENAME_3_12,
	IDC_BTN_PLUGIN_RENAME_3_13,
	IDC_BTN_PLUGIN_RENAME_4_1,
	IDC_BTN_PLUGIN_RENAME_4_2,
	IDC_BTN_PLUGIN_RENAME_4_3,
	IDC_BTN_PLUGIN_RENAME_4_4,
	IDC_BTN_PLUGIN_RENAME_4_5,
	IDC_BTN_PLUGIN_RENAME_4_6,
	IDC_BTN_PLUGIN_RENAME_4_7,
	IDC_BTN_PLUGIN_RENAME_4_8,
	IDC_BTN_PLUGIN_RENAME_4_9,
	IDC_BTN_PLUGIN_RENAME_4_10,
	IDC_BTN_PLUGIN_RENAME_4_11,
	IDC_BTN_PLUGIN_RENAME_4_12,
	IDC_BTN_PLUGIN_RENAME_4_13,
	IDC_BTN_PLUGIN_RENAME_5_1,
	IDC_BTN_PLUGIN_RENAME_5_2,
	IDC_BTN_PLUGIN_RENAME_5_3,
	IDC_BTN_PLUGIN_RENAME_5_4,
	IDC_BTN_PLUGIN_RENAME_5_5,
	IDC_BTN_PLUGIN_RENAME_5_6,
	IDC_BTN_PLUGIN_RENAME_5_7,
	IDC_BTN_PLUGIN_RENAME_5_8,
	IDC_BTN_PLUGIN_RENAME_5_9,
	IDC_BTN_PLUGIN_RENAME_5_10,
	IDC_BTN_PLUGIN_RENAME_5_11,
	IDC_BTN_PLUGIN_RENAME_5_12,
	IDC_BTN_PLUGIN_RENAME_5_13,
	IDC_BTN_PLUGIN_RENAME_6_1,
	IDC_BTN_PLUGIN_RENAME_6_2,
	IDC_BTN_PLUGIN_RENAME_6_3,
	IDC_BTN_PLUGIN_RENAME_6_4,
	IDC_BTN_PLUGIN_RENAME_6_5,
	IDC_BTN_PLUGIN_RENAME_6_6,
	IDC_BTN_PLUGIN_RENAME_6_7,
	IDC_BTN_PLUGIN_RENAME_6_8,
	IDC_BTN_PLUGIN_RENAME_6_9,
	IDC_BTN_PLUGIN_RENAME_6_10,
	IDC_BTN_PLUGIN_RENAME_6_11,
	IDC_BTN_PLUGIN_RENAME_6_12,
	IDC_BTN_PLUGIN_RENAME_6_13,
	IDC_BTN_PLUGIN_RENAME_7_1,
	IDC_BTN_PLUGIN_RENAME_7_2,
	IDC_BTN_PLUGIN_RENAME_7_3,
	IDC_BTN_PLUGIN_RENAME_7_4,
	IDC_BTN_PLUGIN_RENAME_7_5,
	IDC_BTN_PLUGIN_RENAME_7_6,
	IDC_BTN_PLUGIN_RENAME_7_7,
	IDC_BTN_PLUGIN_RENAME_7_8,
	IDC_BTN_PLUGIN_RENAME_7_9,
	IDC_BTN_PLUGIN_RENAME_7_10,
	IDC_BTN_PLUGIN_RENAME_7_11,
	/*IDC_BTN_PLUGIN_RENAME_7_12,
	IDC_BTN_PLUGIN_RENAME_7_13,*/
	IDC_TXT_PLUGIN_RENAME_CONFIRM,
	IDC_TXT_PLUGIN_RENAME_PREV,
	IDC_TXT_PLUGIN_RENAME_NEXT,
	IDC_TXT_PLUGIN_RENAME_CLEAR,
	IDC_PIC_PLUGIN_RENAME_CONFIRM,
	IDC_PIC_PLUGIN_RENAME_PREV,
	IDC_PIC_PLUGIN_RENAME_NEXT,
	IDC_PIC_PLUGIN_RENAME_CLEAR,

    IDD_NUM,

}YWRES_CTRL_ID;

enum
{
	YWCELL_FATHER_FOLDER,
	YWCELL_FOLDER,

    YWCELL_MENU_BK01L,
    YWCELL_MENU_BK01M,
    YWCELL_MENU_BK01R,
    YWCELL_MENU_BK02,
    YWCELL_MENU_BK03,
    YWCELL_MENU_BK04L,
    YWCELL_MENU_BK04M,
    YWCELL_MENU_BK04R,

    YWCELL_RED,
    YWCELL_GREEN,
    YWCELL_YELLOW,
    YWCELL_BLUE,

    YWCELL_POPFRAME_01TITLE,
    YWCELL_POPFRAME_02TITLE,
    YWCELL_POPFRAME_03TITLE,
	YWCELL_POPFRAME_01,
	YWCELL_POPFRAME_02,
	YWCELL_POPFRAME_03,
    YWCELL_POPFRAME_04,
    YWCELL_POPFRAME_05,
    YWCELL_POPFRAME_06,
    YWCELL_POPFRAME_07,
    YWCELL_POPFRAME_08,

    YWCELL_HIGHLIGHT_01,
    YWCELL_HIGHLIGHT_LEFTKEY,
    YWCELL_HIGHLIGHT_RIGHTKEY,

    YWCELL_SCOLL_B,
	YWCELL_SCOLL_BK,
	YWCELL_SCOLL_BLOCK,
	YWCELL_SCOLL_T,

    YWCELL_NUM,
};
extern YWGUI_GraphCell_T g_aGraphCellArray[YWCELL_NUM];

extern YWGUI_ShapeState_T g_tSubMenuFrameShapeState;

#define YWRES_MAKE_RGBA(a,r,g,b)      {(b),(g),(r),(a)}
#define YWRES_MAKE_RGB(r,g,b)         YWRES_MAKE_RGBA(0xff,r,g,b)
#define YWRES_GetBValue(rgb)          ((rgb)[0])
#define YWRES_GetGValue(rgb)          ((rgb)[1])
#define YWRES_GetRValue(rgb)          ((rgb)[2])
#define YWRES_GetAValue(rgba)         ((rgba)[3])

#define  DColor_black            YWRES_MAKE_RGB(16,16,16)
#define  DColor_white            YWRES_MAKE_RGB(254,254,254)
#define  DColor_blue             YWRES_MAKE_RGB(3,77,138)//(129,195,255) //(0,0,255)
//#define  DColor_blue             YWRES_MAKE_RGB(12,47,69)
#define  DColor_red              YWRES_MAKE_RGB(255,0,0)
#define  DColor_green            YWRES_MAKE_RGB(0,255,0)
#define  DColor_transparency     YWRES_MAKE_RGBA(0,0,0,0)
#define  DColor_cyan             YWRES_MAKE_RGB(115,185,211)

#define  DColor_blue_frame_bg    YWRES_MAKE_RGB(12,47,69)
#define  DColor_grayblue         YWRES_MAKE_RGB(99,167,230)
#define  DColor_grayyellow       YWRES_MAKE_RGB(242,192,36)
#define  DColor_smallviewframe   YWRES_MAKE_RGB(10,37,64)
#define  DColor_editbg           YWRES_MAKE_RGB(37,86,153)
#define  DColor_oscameditbg      YWRES_MAKE_RGB(85,84,84)

#define  DColor_gray             YWRES_MAKE_RGB(111,138,181)
#define  DColor_EPGLV_blue       YWRES_MAKE_RGB(42,69,114)
#define  DColor_EPGWeek_blue     YWRES_MAKE_RGB(100,168,231)
#define  DColor_GameVALUE_black  YWRES_MAKE_RGB(10,37,64)
#define  DColor_TetrisFrame_blue    YWRES_MAKE_RGB(100,168,231)
#define  DColor_yellow           YWRES_MAKE_RGB(245,126,32)
#define  DColor_magenta          YWRES_MAKE_RGB(101,131,183)
#define  DColor_ONLINE_blue       YWRES_MAKE_RGB(44,100,250)

#define  DColor_orange           YWRES_MAKE_RGB(255,187,2)
#define  DColor_tv_black         YWRES_MAKE_RGB(10,37,64)
#define  DColor_list_txt         YWRES_MAKE_RGB(100,128,231)
#define  DColor_find_line        YWRES_MAKE_RGB(51,92,146)

#define IPTV_COLOR_BLACK        YWRES_MAKE_RGB(0x00, 0x00, 0x00)
#define IPTV_COLOR_BLUE         YWRES_MAKE_RGB(39, 98, 158)
#define IPTV_COLOR_BLUE_EX      YWRES_MAKE_RGB(26, 91, 148)
#define IPTV_COLOR_YELLOW       YWRES_MAKE_RGB(216, 171, 30)
#define IPTV_COLOR_YELLOW_EX    YWRES_MAKE_RGB(201, 118, 36)


#define  DColor_oscam4spark_grey            YWRES_MAKE_RGB(124,124,124)
#define  DColor_oscam4spark_yellow          YWRES_MAKE_RGB(251,230,188)

#define  DColor_grey        YWRES_MAKE_RGB(33,33,33)


extern YWGUI_Pixel_T Color_black;
extern YWGUI_Pixel_T Color_white;
extern YWGUI_Pixel_T Color_blue;
extern YWGUI_Pixel_T Color_red;
extern YWGUI_Pixel_T Color_green;
extern YWGUI_Pixel_T Color_transparency;
extern YWGUI_Pixel_T Color_cyan;

extern YWGUI_Pixel_T Color_blue_frame_bg;
extern YWGUI_Pixel_T Color_grayblue;
extern YWGUI_Pixel_T Color_grayyellow;
extern YWGUI_Pixel_T Color_smallviewframe;
extern YWGUI_Pixel_T Color_editbg;

extern YWGUI_Pixel_T Color_gray;
extern YWGUI_Pixel_T Color_EPGLV_blue;
extern YWGUI_Pixel_T Color_EPGWeek_blue;
extern YWGUI_Pixel_T Color_GameVALUE_black;
extern YWGUI_Pixel_T Color_TetrisFrame_blue;
extern YWGUI_Pixel_T Color_yellow;
extern YWGUI_Pixel_T Color_magenta;

extern YWGUI_Pixel_T Color_orange;
extern YWGUI_Pixel_T Color_tv_black;
extern YWGUI_Pixel_T Color_list_txt;
extern YWGUI_Pixel_T Color_find_line;

extern YWGUI_ShapeColor_T g_tBlackWhiteShapeColor;
extern YWGUI_ShapeColor_T g_tBlackBlackShapeColor;
extern YWGUI_ShapeColor_T g_tBlackBlueShapeColor;



/*---------common shape info---------*/


extern YWGUI_ShapeState_T g_tItemShapeState_Disable;
extern YWGUI_LTShapeInfo_T g_atLTItemShapeInfo_NoFocus;

/*button common ShapeInfo*/
extern YWGUI_ShapeInfo_T g_tButtonShapeInfo;
extern YWGUI_ShapeInfo_T g_tButtonShapeInfo_Ex;
/*list table ShapeInfo*/
extern YWGUI_ShapeInfo_T g_tListShapeInfo;
/*list table posbar*/
extern YWGUI_ShapeInfo_T g_tScrollShapeInfo;
extern YWGUI_PosbarDef_T  g_tPosbarDef;
/*list table col*/
extern YWGUI_LTShapeInfo_T g_atColLTShapeInfo;
/*static blue black table ShapeInfo*/
extern YWGUI_ShapeInfo_T g_tTxtBlueBlackShapeInfo;
/*static black blue table ShapeInfo*/
extern YWGUI_ShapeInfo_T g_tTxtBlackGrayBlueShapeInfo;
/*static black white table ShapeInfo*/
extern YWGUI_ShapeInfo_T g_tTxtBlackWhiteShapeInfo;

extern YWGUI_ShapeInfo_T g_tTxtBlackBlackShapeInfo;

extern YWGUI_ShapeInfo_T g_tTxtBlackYellowShapeInfo;

extern YWGUI_ShapeState_T g_tTxtTransBlackShapeState;
extern YWGUI_ShapeState_T g_tTxtTransWhiteShapeState;
extern YWGUI_ShapeInfo_T g_tTxtGreyWhiteShapeInfo;
extern YWGUI_ShapeInfo_T g_tTxtTransBlackShapeInfo;
extern YWGUI_ShapeInfo_T g_tTxtTransWhitShapeInfo;


/*static gray black table ShapeInfo*/
extern YWGUI_ShapeInfo_T g_tTxtGrayBlackShapeInfo;
/*static blue_fram black table ShapeInfo*/
extern YWGUI_ShapeInfo_T g_tTxtGrayBlueFrameBlackShapeInfo;
/*static yellow black table ShapeInfo*/
extern YWGUI_ShapeInfo_T g_tTxtOrangeBlackShapeInfo;
/*static black red table ShapeInfo*/
extern YWGUI_ShapeInfo_T g_tTxtBlackRedShapeInfo;

/*for IpTv*/
extern YWGUI_ContainerShapeInfo_T g_tIpTvCntTxtShapeInfo;
extern YWGUI_ContainerShapeInfo_T g_tIpTvCntTxtExShapeInfo;
extern YWGUI_ShapeInfo_T gBkTranExShapInfo;
extern YWGUI_ShapeInfo_T gBkTranWhiteShapInfo;

/*sedit ShapeInfo*/
extern YWGUI_ShapeState_T g_tEditShapeState_Normal;
extern YWGUI_ShapeState_T g_tEditShapeState_Disable;
extern YWGUI_ShapeState_T g_tEditShapeState_AFocus;
extern YWGUI_ShapeState_T g_tEditShapeState_AFocus_EX;
extern YWGUI_ShapeInfo_T g_tEditShapeInfo;
extern YWGUI_ShapeInfo_T g_tOscamRenameEditShapeInfo;
extern YWGUI_ShapeInfo_T g_tEditShapeInfo_Ex;
extern YWGUI_ShapeInfo_T g_tPopDlgHaveHeadShapeInfo;
extern YWGUI_ShapeInfo_T g_tPopDlgNoheadShapeInfo;
extern YWGUI_ShapeState_T g_tSubMenuFrameShapeState;
extern YWGUI_ShapeState_T g_tPopDlgHaveHeadShapeState;
extern YWGUI_ShapeInfo_T g_tPopDlgHaveHeadShapeInfo;
extern YWGUI_LRCBListAddData_T g_tLRCBListAddData;
extern YWGUI_LRCBTextShapeInfo_T g_tLRCBEditShapeInfo;
extern YWGUI_ContainerShapeInfo_T g_tCommItemCntShapeInfo;

extern YWGUI_ContainerShapeInfo_T g_tCommTxtCntShapeInfo;

/*-------------------------------------------------------*/
extern const YWGUI_DlgTemplate_T g_template_mcasentry;
extern const YWGUI_DlgTemplate_T g_template_pluginrename;
extern const YWGUI_DlgTemplate_T g_template_popinfocfg;
extern const YWGUI_DlgTemplate_T g_template_confirminfocfg;
extern const YWGUI_DlgTemplate_T g_template_languageset;


void APP_CommonResLoad(void);
void APP_CommonResUnLoad(void);


#endif

