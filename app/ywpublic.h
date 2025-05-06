

#ifndef __YWPUBLIC_H__
#define __YWPUBLIC_H__


void YWPublic_GetSystemInfo(char *name,char *value);
/*u32TunerIdx 0,1,2*/
/*return true for valid*/
BOOL YWPUBLIC_isTunerAllow(U32 u32TunerIdx);

/*GUI show with the App start, do not need press red key */
void YWPLUGIN_SetGuiShowDirect(BOOL bShow);

/*if GUI is destroyed, the App close immediately*/
void YWPLUGIN_SetAppCloseWithGui(BOOL bSync);



#endif

