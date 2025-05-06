



#ifndef ___YWNETCLIENTCFG__H___
#define ___YWNETCLIENTCFG__H___
#if 0
#define MG_CC_CFG_PATH    "/home/d60nxf/spark/plugin"
#define OSCAM_SERVER_PATH "/home/d60nxf/spark/plugin"
#else
#define MG_CC_CFG_PATH    "/var/keys"
#define OSCAM_SERVER_PATH "/var/tuxbox/config"
#endif

#define PROTOCOL_CC "cccam"
#define PROTOCOL_NEW "newcamd"


typedef enum Cfg_Type_e
{
   CFG_TYPE_OSCAM = 0,
   CFG_TYPE_MG_CCCAMD,
   CFG_TYPE_MG_NEWCAMD,
   CFG_TYPE_CCCAMCFG,

   CFG_TYPE_NUM,
}Cfg_Type_T;



YWGUI_HWnd_T YWNetClientActivInfo_CreateWindow(YWGUI_HWnd_T hHost);
void YWNetClientEdit_SetCfgType(Cfg_Type_T Type);


YWGUI_HWnd_T YWNetClientEdit_CreateWindow(YWGUI_HWnd_T hHost);
YWGUI_HWnd_T YWNetClientPing_CreateWindow(YWGUI_HWnd_T hHost, int idx);



#endif



