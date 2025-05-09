#include "ywgui_ext.h"
#include "res_layout.h"
#include "camcfg_layout.h"




#define INFO_DLG_W 840
#define INFO_DLG_H 460



/******************************************net client config*************************************************/
#define _NET_CLIENT_CFG_

/*#define _PIC_START_X 46
#define _PIC_START_Y 72*/

#define _PIC_START_X 250
#define _PIC_START_Y 100
#define _BTN_W_ 720
#define _BTN_GAP_ 68


static YWGUI_CtrlTemplate_T g_ctrl_template_netcfginfo[] =
{
    /*title text*/
    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE | YWGUI_SS_CENTER,YWGUI_WS_EX_TITLECTRL | YWGUI_WS_EX_TRANSPARENT,
        (YWPUBLIC_COMM_DLG_W - 400) / 2, 38, 400, 64, IDC_TXT_NET_CFG_INFOR_TITLE, STR_INFORMATION, 0, 0},

	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
        100, 50, 510, CTRL_COMMON_HIGH,
        IDC_TXT_NET_CFG_INFOR_VISITUS_L, STR_VISIT_US, 0, &g_tTxtBlackGrayBlueShapeInfo},

	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
        100+510, 50, 510, CTRL_COMMON_HIGH,
        IDC_TXT_NET_CFG_INFOR_VISITUS_R, STR_EMPTY, 0, &g_tTxtBlackGrayBlueShapeInfo},
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
        100+510, 50+CTRL_COMMON_HIGH*1, 510, CTRL_COMMON_HIGH,
        IDC_TXT_NET_CFG_INFOR_VISITUS_R1, STR_EMPTY, 0, &g_tTxtBlackGrayBlueShapeInfo},
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
        100+510, 50+CTRL_COMMON_HIGH*2, 510, CTRL_COMMON_HIGH,
        IDC_TXT_NET_CFG_INFOR_VISITUS_R2, STR_EMPTY, 0, &g_tTxtBlackGrayBlueShapeInfo},
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
        100+510, 50+CTRL_COMMON_HIGH*3, 510, CTRL_COMMON_HIGH,
        IDC_TXT_NET_CFG_INFOR_VISITUS_R3, STR_EMPTY, 0, &g_tTxtBlackGrayBlueShapeInfo},

	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
        100+510, 50+CTRL_COMMON_HIGH*4, 510, CTRL_COMMON_HIGH,
        IDC_TXT_NET_CFG_INFOR_VISITUS_R4, STR_EMPTY, 0, &g_tTxtBlackGrayBlueShapeInfo},

};

const YWGUI_DlgTemplate_T g_template_netcfginfo =
{
    IDD_NET_CFG_INFOR,
    YWGUI_WS_VISIBLE |YWGUI_WS_BORDER,
    YWGUI_WS_EX_NONE/*|YWGUI_WS_EX_IRREGULAR*/|YWGUI_WS_EX_TRANSPARENT,
    (YWPUBLIC_OSD_W - YWPUBLIC_COMM_DLG_W)/2,
    (YWPUBLIC_OSD_H - YWPUBLIC_COMM_DLG_H)/2,
    YWPUBLIC_COMM_DLG_W,
    YWPUBLIC_COMM_DLG_H,
    0,
    YWGUI_ARRAY_SIZE(g_ctrl_template_netcfginfo),
    g_ctrl_template_netcfginfo,
    0,
    NULL
};


static YWGUI_CtrlTemplate_T g_ctrl_template_netclntcfg[] =
{

    /*title text*/
    {(const S8*)YWGUI_CTRL_STATIC,YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE |YWGUI_WS_EX_TRANSPARENT|YWGUI_WS_EX_TITLECTRL,
       (YWPUBLIC_COMM_DLG_W-400)/2, 36, 400, 52,
       IDC_TXT_NET_CFG_TITLE, STR_NET_CLIENT_CONFIG,0,0},

    /*button*/
//	{(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
//       _PIC_START_X, _PIC_START_Y, 46,46,IDC_PIC_NET_CFG_OSCAM,STR_EMPTY,(DWORD)&g_aGraphCellArray[YWCELL_RED], 0},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_WS_DISABLED|YWGUI_BS_CENTER|YWGUI_BS_VCENTER, YWGUI_WS_EX_NONE |YWGUI_WS_EX_NOTIFY,
       _PIC_START_X, _PIC_START_Y, _BTN_W_, CTRL_COMMON_HIGH, IDC_BTN_NET_CFG_OSCAM, 0, 0, &g_tButtonShapeInfo},


//	{(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
//       _PIC_START_X, _PIC_START_Y+_BTN_GAP_*2,46,46,IDC_PIC_NET_CFG_MGCFG,STR_EMPTY,(DWORD)&g_aGraphCellArray[YWCELL_RED], 0},
	{(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_WS_DISABLED|YWGUI_BS_CENTER|YWGUI_BS_VCENTER, YWGUI_WS_EX_NONE |YWGUI_WS_EX_NOTIFY,
       _PIC_START_X, _PIC_START_Y+_BTN_GAP_*1, _BTN_W_, CTRL_COMMON_HIGH, IDC_BTN_NET_CFG_MGCFG, 0, 0, &g_tButtonShapeInfo},

//	{(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_NONE,
//       _PIC_START_X, _PIC_START_Y+_BTN_GAP_,46,46,IDC_PIC_NET_CFG_CCCAMD,STR_EMPTY,(DWORD)&g_aGraphCellArray[YWCELL_RED], 0},
	{(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_WS_DISABLED|YWGUI_BS_CENTER|YWGUI_BS_VCENTER, YWGUI_WS_EX_NONE |YWGUI_WS_EX_NOTIFY,
       _PIC_START_X, _PIC_START_Y+_BTN_GAP_*2, _BTN_W_, CTRL_COMMON_HIGH, IDC_BTN_NET_CFG_CCCAMCFG, 0, 0, &g_tButtonShapeInfo},

	//information
	{(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_WS_DISABLED|YWGUI_BS_CENTER|YWGUI_BS_VCENTER, YWGUI_WS_EX_NONE |YWGUI_WS_EX_NOTIFY,
       _PIC_START_X, _PIC_START_Y+_BTN_GAP_*3, _BTN_W_, CTRL_COMMON_HIGH, IDC_BTN_NET_CFG_INFOR, 0, 0, &g_tButtonShapeInfo},

	/*function ctrl*/
/*    {(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
       HOTKEY_START_X, HOTKEY_START_Y,46,46,
       IDC_PIC_NET_CFG_RED,STR_EMPTY,(DWORD)&g_aGraphCellArray[YWCELL_RED], 0},
    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_LEFT, YWGUI_WS_EX_TRANSPARENT,
        HOTKEY_START_X+50, HOTKEY_START_Y, 200, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_START_STORP, STR_EMPTY, 0, &g_tTxtBlackWhiteShapeInfo},
*/
};


const YWGUI_DlgTemplate_T g_template_netclntcfg =
{
    IDD_NET_CLIENT_CONFIG,
    YWGUI_WS_VISIBLE,
    YWGUI_WS_EX_NONE,
    (YWPUBLIC_OSD_W - YWPUBLIC_COMM_DLG_W)/2,
    (YWPUBLIC_OSD_H - YWPUBLIC_COMM_DLG_H)/2,
    YWPUBLIC_COMM_DLG_W,
    YWPUBLIC_COMM_DLG_H,
    -1,
    YWGUI_ARRAY_SIZE(g_ctrl_template_netclntcfg),
    g_ctrl_template_netclntcfg,
    0,
    NULL
};


/////////////////////////////////////////mg cfg//////////////////////////////////////

static YWGUI_CtrlTemplate_T g_ctrl_template_mgcfg[] =
{

    /*title text*/
    {(const S8*)YWGUI_CTRL_STATIC,YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE |YWGUI_WS_EX_TRANSPARENT|YWGUI_WS_EX_TITLECTRL,
       (YWPUBLIC_COMM_DLG_W-400)/2, 36, 400, 52,
       IDC_TXT_MG_CONFIG_TITLE, STR_EMPTY,0,0},

    /*button*/

	{(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_WS_DISABLED|YWGUI_BS_CENTER|YWGUI_BS_VCENTER, YWGUI_WS_EX_NONE |YWGUI_WS_EX_NOTIFY,
       _PIC_START_X, _PIC_START_Y, _BTN_W_,
       CTRL_COMMON_HIGH, IDC_BTN_MG_CONFIG_NEWCAMD, 0, 0, &g_tButtonShapeInfo},

    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_WS_DISABLED|YWGUI_BS_CENTER|YWGUI_BS_VCENTER, YWGUI_WS_EX_NONE |YWGUI_WS_EX_NOTIFY,
       _PIC_START_X, _PIC_START_Y+_BTN_GAP_*1, _BTN_W_, CTRL_COMMON_HIGH,
       IDC_BTN_MG_CONFIG_CCCAMD, 0, 0, &g_tButtonShapeInfo},
};


const YWGUI_DlgTemplate_T g_template_mgcfg =
{
    IDD_MG_CONFIG,
    YWGUI_WS_VISIBLE,
    YWGUI_WS_EX_NONE,
    (YWPUBLIC_OSD_W - YWPUBLIC_COMM_DLG_W)/2,
    (YWPUBLIC_OSD_H - YWPUBLIC_COMM_DLG_H)/2,
    YWPUBLIC_COMM_DLG_W,
    YWPUBLIC_COMM_DLG_H,
    -1,
    YWGUI_ARRAY_SIZE(g_ctrl_template_mgcfg),
    g_ctrl_template_mgcfg,
    0,
    NULL
};



/****************************************** info dlg*************************************************/

#define _ACTIVE_INFO_

#define _LT_W_ 620

static YWGUI_LTShapeInfo_T *g_apActiveShapeInfo_NoFocus[]=
{
    &g_atLTItemShapeInfo_NoFocus,
    &g_atLTItemShapeInfo_NoFocus,
    &g_atLTItemShapeInfo_NoFocus,
    &g_atLTItemShapeInfo_NoFocus,
};

U16 aActiveListWidth[]=
{
    360,
};

const YWGUI_LTAddData_T g_ActiveListAddData =
{
    1,
    8,
    aActiveListWidth,
    g_apActiveShapeInfo_NoFocus,
    NULL,
    0,//pic size 20*52
    NULL,//&g_atLTItemShapeInfo_NoFocus,
    NULL,//&g_tMarkIcon,
};


static YWGUI_CtrlTemplate_T g_ctrl_template_activeinfocfg[] =
{

    /* text*/
    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_LEFT, YWGUI_WS_EX_TRANSPARENT,
        50, 10, _LT_W_, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_ACTIVE_STATUS, STR_EMPTY, 0, &g_tTxtBlackWhiteShapeInfo},

    /*list table*/
    {(const S8*)YWGUI_CTRL_LISTTABLE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
      50,60,_LT_W_,320,
      IDC_LT_NET_CFG_ACTIVE_STATUS, STR_EMPTY,(DWORD)&g_ActiveListAddData,&g_tListShapeInfo},

};

const YWGUI_DlgTemplate_T g_template_activeinfocfg =
{
    IDD_NET_CLIENT_CONFIG_ACTIVE_INFO,
    YWGUI_WS_VISIBLE,
    YWGUI_WS_EX_NONE,
    (YWPUBLIC_OSD_W - INFO_DLG_W)/2,
    (YWPUBLIC_OSD_H - INFO_DLG_H)/2,
    INFO_DLG_W,
    INFO_DLG_H,
    -1,
    YWGUI_ARRAY_SIZE(g_ctrl_template_activeinfocfg),
    g_ctrl_template_activeinfocfg,
    0,
    NULL
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


static YWGUI_CtrlTemplate_T g_ctrl_template_pinginfocfg[] =
{

    /* text*/
    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_TOP|YWGUI_SS_LEFT|YWGUI_SS_WORDBREAK, YWGUI_WS_EX_TRANSPARENT,
        0, 10, (888-10), 420, IDC_TXT_NET_CFG_PING_INFO, STR_EMPTY, 0, &g_tTxtBlackWhiteShapeInfo},

};

const YWGUI_DlgTemplate_T g_template_pinginfocfg =
{
    IDD_NET_CLIENT_CONFIG_PING_INFO,
    YWGUI_WS_VISIBLE,
    YWGUI_WS_EX_NONE,
    (YWPUBLIC_OSD_W - 888)/2,
    (YWPUBLIC_OSD_H - 498)/2,
    888,
    498,
    -1,
    YWGUI_ARRAY_SIZE(g_ctrl_template_pinginfocfg),
    g_ctrl_template_pinginfocfg,
    0,
    NULL
};



/******************************************net client config edit*************************************************/
#define _NET_CLIENT_CFG_EDIT_
#define _TXT_START_X_ 100
#define _TXT_START_Y_ 50
#define _TXT_W_ 300
#define _EDIT_W_ (1220-_TXT_START_X_*2-_TXT_W_)


#define DOT_WIDTH 12
#define SERVERNAME_WIDTH 68
#define TXT_L_R_SERVNAMEW ((_EDIT_W_-(4*SERVERNAME_WIDTH)-(3*DOT_WIDTH))/2)


static YWGUI_LRCombobox_AddData_T NetClntDown4LRCBAddData =
{
    //Edit的外形
    &g_tLRCBEditShapeInfo,

    //List的位置
    0, 52, _EDIT_W_, (52*4+78),

    //List的外形
    &g_tPopDlgHaveHeadShapeInfo,
    &g_tLRCBListAddData
};


static YWGUI_LRCombobox_AddData_T NetClntUp4LRCBAddData =
{
    //Edit的外形
    &g_tLRCBEditShapeInfo,

    //List的位置
    0, -(52*4+78), _EDIT_W_, (52*4+78),

    //List的外形
    &g_tPopDlgHaveHeadShapeInfo,
    &g_tLRCBListAddData
};


//server name
/*static YWGUI_ContainerCtrlTemplate_T tServerNameCntLRCtrlTemplate[] =
{

    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER,YWGUI_WS_EX_NOTIFY,
        0,0,TXT_L_R_SERVNAMEW,CTRL_COMMON_HIGH,
        IDC_TXT_NET_CFG_EDIT_SERV_NAMEL, STR_EMPTY, 0, &g_tCommItemCntShapeInfo},

    {(const S8*)YWGUI_CTRL_SEDIT, YWGUI_WS_VISIBLE|YWGUI_ES_CENTER|YWGUI_ES_VCENTER|YWGUI_ES_NUMBER|YWGUI_ES_REPLACE,YWGUI_WS_EX_NOTIFY,
        TXT_L_R_SERVNAMEW,0,SERVERNAME_WIDTH,CTRL_COMMON_HIGH,
        IDC_EDIT_NET_CFG_EDIT_SERV_NAME1, STR_EMPTY, 0, &g_tCommItemCntShapeInfo},

    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE,
        (TXT_L_R_SERVNAMEW+SERVERNAME_WIDTH), 0, DOT_WIDTH, CTRL_COMMON_HIGH,
        IDC_TXT_NET_CFG_EDIT_SERV_DOT1, STR_EMPTY,0,&g_tCommItemCntShapeInfo},

    {(const S8*)YWGUI_CTRL_SEDIT, YWGUI_WS_VISIBLE|YWGUI_ES_CENTER|YWGUI_ES_VCENTER|YWGUI_ES_NUMBER|YWGUI_ES_REPLACE,YWGUI_WS_EX_NOTIFY,
        (TXT_L_R_SERVNAMEW+SERVERNAME_WIDTH+DOT_WIDTH),0,SERVERNAME_WIDTH,CTRL_COMMON_HIGH,
        IDC_EDIT_NET_CFG_EDIT_SERV_NAME2, STR_EMPTY, 0, &g_tCommItemCntShapeInfo},

    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE,
        (TXT_L_R_SERVNAMEW+SERVERNAME_WIDTH*2+DOT_WIDTH), 0, DOT_WIDTH,CTRL_COMMON_HIGH,
        IDC_TXT_NET_CFG_EDIT_SERV_DOT2, STR_EMPTY,0,&g_tCommItemCntShapeInfo},

    {(const S8*)YWGUI_CTRL_SEDIT, YWGUI_WS_VISIBLE|YWGUI_ES_CENTER|YWGUI_ES_VCENTER|YWGUI_ES_NUMBER|YWGUI_ES_REPLACE,YWGUI_WS_EX_NOTIFY,
        (TXT_L_R_SERVNAMEW+SERVERNAME_WIDTH*2+DOT_WIDTH*2),0,SERVERNAME_WIDTH,CTRL_COMMON_HIGH,
        IDC_EDIT_NET_CFG_EDIT_SERV_NAME3, STR_EMPTY, 0, &g_tCommItemCntShapeInfo},

    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE,
        (TXT_L_R_SERVNAMEW+SERVERNAME_WIDTH*3+DOT_WIDTH*2), 0, DOT_WIDTH,CTRL_COMMON_HIGH,
        IDC_TXT_NET_CFG_EDIT_SERV_DOT3, STR_EMPTY,0,&g_tCommItemCntShapeInfo},

    {(const S8*)YWGUI_CTRL_SEDIT, YWGUI_WS_VISIBLE|YWGUI_ES_CENTER|YWGUI_ES_VCENTER|YWGUI_ES_NUMBER|YWGUI_ES_REPLACE,YWGUI_WS_EX_NOTIFY,
        (TXT_L_R_SERVNAMEW+SERVERNAME_WIDTH*3+DOT_WIDTH*3),0,SERVERNAME_WIDTH,CTRL_COMMON_HIGH,
        IDC_EDIT_NET_CFG_EDIT_SERV_NAME4, STR_EMPTY, 0, &g_tCommItemCntShapeInfo},

    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER,YWGUI_WS_EX_NOTIFY,
        (TXT_L_R_SERVNAMEW+SERVERNAME_WIDTH*4+DOT_WIDTH*3),0,TXT_L_R_SERVNAMEW,CTRL_COMMON_HIGH,
        IDC_TXT_NET_CFG_EDIT_SERV_NAMER, STR_EMPTY, 0, &g_tCommItemCntShapeInfo},

};
YWGUI_ContainerAddData_T tServerNameCtnLRAddData =
{
    YWGUI_ARRAY_SIZE(tServerNameCntLRCtrlTemplate),
    tServerNameCntLRCtrlTemplate,
};
*/

static YWGUI_CtrlTemplate_T g_ctrl_template_netclntcfgedit[] =
{

    /*title text*/
    {(const S8*)YWGUI_CTRL_STATIC,YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE |YWGUI_WS_EX_TRANSPARENT|YWGUI_WS_EX_TITLECTRL,
       (YWPUBLIC_COMM_DLG_W-400)/2, 36, 400, CTRL_COMMON_HIGH,
       IDC_TXT_NET_CFG_EDIT_TITLE, STR_NET_CLIENT_CONFIG_EDIT,0,0},

	//index
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
        _TXT_START_X_, _TXT_START_Y_, _TXT_W_, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_EDIT_INDEX, STR_INDEX, 0, &g_tTxtBlackWhiteShapeInfo},
    {(const S8*)YWGUI_CTRL_LRCOMBOBOX, YWGUI_WS_VISIBLE|YWGUI_LRCBS_AUTOSCROLL|YWGUI_LRCBS_CENTER|YWGUI_LRCBS_VCENTER|YWGUI_LRCBS_EXITKEYHIDELIST,YWGUI_WS_EX_NOTIFY,
        _TXT_START_X_+_TXT_W_, _TXT_START_Y_, _EDIT_W_, CTRL_COMMON_HIGH,
        IDC_LRC_NET_CFG_EDIT_INDEX, 0, (DWORD)&NetClntDown4LRCBAddData, 0},

	//server name
    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
        _TXT_START_X_, _TXT_START_Y_+CTRL_COMMON_HIGH*1, _TXT_W_, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_EDIT_SERV_NAME, STR_SERVER_NAME, 0, &g_tTxtBlackWhiteShapeInfo},
 /*   {(const S8*)YWGUI_CTRL_CONTAINER, YWGUI_WS_VISIBLE,YWGUI_WS_EX_NOTIFY,
         (_TXT_START_X_+_TXT_W_), _TXT_START_Y_+CTRL_COMMON_HIGH*1, _EDIT_W_, CTRL_COMMON_HIGH,
        IDC_CTN_NET_CFG_EDIT_SERV_NAME, STR_EMPTY, (DWORD)&tServerNameCtnLRAddData, NULL},*/
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_BS_CENTER|YWGUI_BS_VCENTER, YWGUI_WS_EX_NONE |YWGUI_WS_EX_NOTIFY,
         (_TXT_START_X_+_TXT_W_), _TXT_START_Y_+CTRL_COMMON_HIGH*1, _EDIT_W_, CTRL_COMMON_HIGH,
         IDC_BTN_NET_CFG_EDIT_SERV_NAME, 0, 0, &g_tButtonShapeInfo},


	//service port
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
        _TXT_START_X_, _TXT_START_Y_+CTRL_COMMON_HIGH*2, _TXT_W_, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_EDIT_SERVICE_PORT, STR_SERVICE_PORT, 0, &g_tTxtBlackWhiteShapeInfo},
	{(const S8*)YWGUI_CTRL_SEDIT, YWGUI_WS_VISIBLE|YWGUI_ES_CENTER|YWGUI_ES_VCENTER|YWGUI_ES_NUMBER|YWGUI_ES_REPLACE,YWGUI_WS_EX_NOTIFY|YWGUI_WS_EX_NOTIFY,
        (_TXT_START_X_+_TXT_W_),_TXT_START_Y_+CTRL_COMMON_HIGH*2,_EDIT_W_,CTRL_COMMON_HIGH,
        IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT, STR_EMPTY, 0, &g_tEditShapeInfo_Ex},

	//service port end  for newcamd CWS_MULTIPLE
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
        _TXT_START_X_, _TXT_START_Y_+CTRL_COMMON_HIGH*7, _TXT_W_, CTRL_COMMON_HIGH, 
        IDC_TXT_NET_CFG_EDIT_SERVICE_PORT_END, STR_SERVICE_PORT, 0, &g_tTxtBlackWhiteShapeInfo},
	{(const S8*)YWGUI_CTRL_SEDIT, YWGUI_WS_VISIBLE|YWGUI_ES_CENTER|YWGUI_ES_VCENTER|YWGUI_ES_NUMBER|YWGUI_ES_REPLACE,YWGUI_WS_EX_NOTIFY|YWGUI_WS_EX_NOTIFY,
        (_TXT_START_X_+_TXT_W_),_TXT_START_Y_+CTRL_COMMON_HIGH*7,_EDIT_W_,CTRL_COMMON_HIGH,
        IDC_EDIT_NET_CFG_EDIT_SERVICE_PORT_END, STR_EMPTY, 0, &g_tEditShapeInfo_Ex},


	//user name
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
        _TXT_START_X_, _TXT_START_Y_+CTRL_COMMON_HIGH*3, _TXT_W_, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_EDIT_USER_NAME, STR_USR_NAME, 0, &g_tTxtBlackWhiteShapeInfo},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_BS_CENTER|YWGUI_BS_VCENTER, YWGUI_WS_EX_NONE |YWGUI_WS_EX_NOTIFY,
         (_TXT_START_X_+_TXT_W_), _TXT_START_Y_+CTRL_COMMON_HIGH*3, _EDIT_W_, CTRL_COMMON_HIGH,
         IDC_BTN_NET_CFG_EDIT_USER_NAME, 0, 0, &g_tButtonShapeInfo},

	//password
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
        _TXT_START_X_, _TXT_START_Y_+CTRL_COMMON_HIGH*4, _TXT_W_, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_EDIT_PASSWORD, STR_PSW, 0, &g_tTxtBlackWhiteShapeInfo},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_BS_CENTER|YWGUI_BS_VCENTER, YWGUI_WS_EX_NONE |YWGUI_WS_EX_NOTIFY,
         (_TXT_START_X_+_TXT_W_), _TXT_START_Y_+CTRL_COMMON_HIGH*4, _EDIT_W_, CTRL_COMMON_HIGH,
         IDC_BTN_NET_CFG_EDIT_PASSWORD, 0, 0, &g_tButtonShapeInfo},

	//des key
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
        _TXT_START_X_, _TXT_START_Y_+CTRL_COMMON_HIGH*5, _TXT_W_, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_EDIT_DES_KEY, STR_DES_KEY, 0, &g_tTxtBlackWhiteShapeInfo},
	{(const S8*)YWGUI_CTRL_SEDIT, YWGUI_WS_VISIBLE|YWGUI_ES_CENTER|YWGUI_ES_VCENTER|YWGUI_ES_REPLACE,YWGUI_WS_EX_NOTIFY|YWGUI_WS_EX_NOTIFY,
        (_TXT_START_X_+_TXT_W_), _TXT_START_Y_+CTRL_COMMON_HIGH*5,_EDIT_W_,CTRL_COMMON_HIGH,
        IDC_EDIT_NET_CFG_EDIT_DES_KEY, STR_EMPTY, 0, &g_tEditShapeInfo_Ex},

	//protocol
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
        _TXT_START_X_, _TXT_START_Y_+CTRL_COMMON_HIGH*6, _TXT_W_, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_EDIT_PROTOCOL, STR_PROTOCOL, 0, &g_tTxtBlackWhiteShapeInfo},
    {(const S8*)YWGUI_CTRL_LRCOMBOBOX, YWGUI_WS_VISIBLE|YWGUI_LRCBS_AUTOSCROLL|YWGUI_LRCBS_CENTER|YWGUI_LRCBS_VCENTER|YWGUI_LRCBS_EXITKEYHIDELIST,YWGUI_WS_EX_NOTIFY,
        _TXT_START_X_+_TXT_W_, _TXT_START_Y_+CTRL_COMMON_HIGH*6, _EDIT_W_, CTRL_COMMON_HIGH,
        IDC_LRC_NET_CFG_EDIT_PROTOCOL, 0, (DWORD)&NetClntUp4LRCBAddData, 0},




	//help info
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_LEFT, YWGUI_WS_EX_TRANSPARENT,
        HOTKEY_START_X, 610-CTRL_COMMON_HIGH-5, 880, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_EDIT_HELP, STR_EMPTY, 0, &g_tTxtBlackWhiteShapeInfo},

	/*function ctrl*/
    {(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
       HOTKEY_START_X, HOTKEY_START_Y,46,46,
       IDC_PIC_NET_CFG_EDIT_RED,STR_EMPTY,(DWORD)&g_aGraphCellArray[YWCELL_RED], 0},
    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_LEFT, YWGUI_WS_EX_TRANSPARENT,
        HOTKEY_START_X+50, HOTKEY_START_Y, 100, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_EDIT_ADD, STR_ADD, 0, &g_tTxtBlackWhiteShapeInfo},

    {(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
       HOTKEY_START_X+150, HOTKEY_START_Y,46,46,
		IDC_PIC_NET_CFG_EDIT_GREEN,STR_EMPTY, (DWORD)&g_aGraphCellArray[YWCELL_GREEN], 0},
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_LEFT, YWGUI_WS_EX_TRANSPARENT,
        HOTKEY_START_X+200, HOTKEY_START_Y, 100, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_EDIT_DELETE, STR_DEL, 0, &g_tTxtBlackWhiteShapeInfo},

    {(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
       HOTKEY_START_X+300, HOTKEY_START_Y,46,46,
       IDC_PIC_NET_CFG_EDIT_YELLOW,STR_EMPTY,(DWORD)&g_aGraphCellArray[YWCELL_YELLOW], 0},
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_LEFT, YWGUI_WS_EX_TRANSPARENT,
       HOTKEY_START_X+350, HOTKEY_START_Y, 100, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_EDIT_PING, STR_PING, 0, &g_tTxtBlackWhiteShapeInfo},

    {(const S8*)YWGUI_CTRL_PICTURE,YWGUI_WS_VISIBLE,YWGUI_WS_EX_TRANSPARENT,
       HOTKEY_START_X+450, HOTKEY_START_Y,46,46,
       IDC_PIC_NET_CFG_EDIT_BLUE,STR_EMPTY,(DWORD)&g_aGraphCellArray[YWCELL_BLUE], 0},
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_LEFT, YWGUI_WS_EX_TRANSPARENT,
        HOTKEY_START_X+500, HOTKEY_START_Y, 100, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_EDIT_F, STR_EMPTY, 0, &g_tTxtBlackWhiteShapeInfo},

	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_VCENTER|YWGUI_SS_LEFT, YWGUI_WS_EX_TRANSPARENT,
        HOTKEY_START_X+600, HOTKEY_START_Y, 350, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_EDIT_AB, STR_EMPTY, 0, &g_tTxtBlackWhiteShapeInfo},

};

const YWGUI_DlgTemplate_T g_template_netclntcfgedit =
{
    IDD_NET_CLIENT_CONFIG_EDIT,
    YWGUI_WS_VISIBLE,
    YWGUI_WS_EX_NONE,
    (YWPUBLIC_OSD_W - YWPUBLIC_COMM_DLG_W)/2,
    (YWPUBLIC_OSD_H - YWPUBLIC_COMM_DLG_H)/2,
    YWPUBLIC_COMM_DLG_W,
    YWPUBLIC_COMM_DLG_H,
    -1,
    YWGUI_ARRAY_SIZE(g_ctrl_template_netclntcfgedit),
    g_ctrl_template_netclntcfgedit,
    0,
    NULL
};

/******************************************net client config ping*************************************************/
#define _NET_CLIENT_CFG_PING_

static YWGUI_CtrlTemplate_T g_ctrl_template_netclntcfgping[] =
{

    /*title text*/
    {(const S8*)YWGUI_CTRL_STATIC,YWGUI_WS_VISIBLE|YWGUI_SS_CENTER|YWGUI_SS_VCENTER,YWGUI_WS_EX_NONE |YWGUI_WS_EX_TRANSPARENT|YWGUI_WS_EX_TITLECTRL,
       (YWPUBLIC_COMM_DLG_W-400)/2, 36, 400, 52,
       IDC_TXT_NET_CFG_PING_TITLE, STR_EMPTY,0,0},

	//ping mode
/*    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
		_TXT_START_X_, _TXT_START_Y_, _TXT_W_, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_PING_MODE, STR_EMPTY, 0, &g_tTxtBlackWhiteShapeInfo},
	{(const S8*)YWGUI_CTRL_LRCOMBOBOX, YWGUI_WS_VISIBLE|YWGUI_LRCBS_AUTOSCROLL|YWGUI_LRCBS_CENTER|YWGUI_LRCBS_VCENTER|YWGUI_LRCBS_EXITKEYHIDELIST,YWGUI_WS_EX_NOTIFY,
        (_TXT_START_X_+_TXT_W_), _TXT_START_Y_, _EDIT_W_, CTRL_COMMON_HIGH,
        IDC_LRC_NET_CFG_PING_MODE, 0, (DWORD)&NetClntDown4LRCBAddData, 0},
*/
	//ping timeout
    {(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
        _TXT_START_X_, _TXT_START_Y_, _TXT_W_, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_PING_TIMEOUT, STR_EMPTY, 0, &g_tTxtBlackWhiteShapeInfo},
	{(const S8*)YWGUI_CTRL_LRCOMBOBOX, YWGUI_WS_VISIBLE|YWGUI_LRCBS_AUTOSCROLL|YWGUI_LRCBS_CENTER|YWGUI_LRCBS_VCENTER|YWGUI_LRCBS_EXITKEYHIDELIST,YWGUI_WS_EX_NOTIFY,
        (_TXT_START_X_+_TXT_W_), _TXT_START_Y_, _EDIT_W_, CTRL_COMMON_HIGH,
        IDC_LRC_NET_CFG_PING_TIMEOUT, 0, (DWORD)&NetClntDown4LRCBAddData, 0},

	//ping packet
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
        _TXT_START_X_, _TXT_START_Y_+CTRL_COMMON_HIGH*1, _TXT_W_, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_PING_PACKET, STR_EMPTY, 0, &g_tTxtBlackWhiteShapeInfo},
	{(const S8*)YWGUI_CTRL_LRCOMBOBOX, YWGUI_WS_VISIBLE|YWGUI_LRCBS_AUTOSCROLL|YWGUI_LRCBS_CENTER|YWGUI_LRCBS_VCENTER|YWGUI_LRCBS_EXITKEYHIDELIST,YWGUI_WS_EX_NOTIFY,
        (_TXT_START_X_+_TXT_W_), _TXT_START_Y_+CTRL_COMMON_HIGH*1, _EDIT_W_, CTRL_COMMON_HIGH,
        IDC_LRC_NET_CFG_PING_PACKET, 0, (DWORD)&NetClntDown4LRCBAddData, 0},

	//ping target
/*	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
        _TXT_START_X_, _TXT_START_Y_+CTRL_COMMON_HIGH*2, _TXT_W_, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_PING_TARGET, STR_EMPTY, 0, &g_tTxtBlackWhiteShapeInfo},
	{(const S8*)YWGUI_CTRL_LRCOMBOBOX, YWGUI_WS_VISIBLE|YWGUI_LRCBS_AUTOSCROLL|YWGUI_LRCBS_CENTER|YWGUI_LRCBS_VCENTER|YWGUI_LRCBS_EXITKEYHIDELIST,YWGUI_WS_EX_NOTIFY,
        (_TXT_START_X_+_TXT_W_), _TXT_START_Y_+CTRL_COMMON_HIGH*2, _EDIT_W_, CTRL_COMMON_HIGH,
        IDC_LRC_NET_CFG_PING_TARGET, 0, (DWORD)&NetClntDown4LRCBAddData, 0},
*/
	//ping run ping
	{(const S8*)YWGUI_CTRL_STATIC, YWGUI_WS_VISIBLE|YWGUI_SS_LEFT|YWGUI_SS_VCENTER, YWGUI_WS_EX_TRANSPARENT,
        _TXT_START_X_, _TXT_START_Y_+CTRL_COMMON_HIGH*2, _TXT_W_, CTRL_COMMON_HIGH, IDC_TXT_NET_CFG_PING_RUN, STR_EMPTY, 0, &g_tTxtBlackWhiteShapeInfo},
    {(const S8*)YWGUI_CTRL_BUTTON, YWGUI_WS_VISIBLE|YWGUI_BS_CENTER|YWGUI_BS_VCENTER, YWGUI_WS_EX_NONE |YWGUI_WS_EX_NOTIFY,
        (_TXT_START_X_+_TXT_W_),_TXT_START_Y_+CTRL_COMMON_HIGH*2,_EDIT_W_,CTRL_COMMON_HIGH,
        IDC_BTN_NET_CFG_PING_RUN, STR_EMPTY, 0, &g_tButtonShapeInfo},

};

const YWGUI_DlgTemplate_T g_template_netclntcfgping =
{
    IDD_NET_CLIENT_CONFIG_PING,
    YWGUI_WS_VISIBLE,
    YWGUI_WS_EX_NONE,
    (YWPUBLIC_OSD_W - YWPUBLIC_COMM_DLG_W)/2,
    (YWPUBLIC_OSD_H - YWPUBLIC_COMM_DLG_H)/2,
    YWPUBLIC_COMM_DLG_W,
    YWPUBLIC_COMM_DLG_H,
    -1,
    YWGUI_ARRAY_SIZE(g_ctrl_template_netclntcfgping),
    g_ctrl_template_netclntcfgping,
    0,
    NULL
};













