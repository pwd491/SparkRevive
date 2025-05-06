/*
 * File: ywpublic.c    
 * Author:  
 * Brief: the definition of global and miscellaneous functions
 * 
 */

/*
 * History:
 * ================================================================
 *
 */

#include <stdio.h>
//#include "ywlib.h"
#include "fifo_client.h"

/**
  *get system info
  *name: (stb id, chip id, mac address)
  *value: return the info
  *value: the lenght of value
  *for example: get system stb id call YWPublic_GetSystemInfo("stb id", value);
  */

void YWPUBLIC_GetSystemInfo(char *name, char *value, int value_len)
{
	char buf[512] = {0};
	int i = 0;
	int k = 0;
	int flag = 0;
	int start = 0,end = 0;
	int len = 0;
	char temp[128] = {0};
	char strtemp[128] = {0};
    FILE *fp = NULL;

    if((name == NULL) || (value == NULL))
    {
        printf("name or value parameters error.\n");
        return;
    }
    fp = fopen("//proc//sparkid","r");
	if(NULL == fp)
	{
		printf("Can not open //proc//sparkid\r\n");
	}
	fread(buf,1,sizeof(buf),fp);
	fclose(fp);
	len = strlen(name);
	for (i = 0;i<sizeof(buf);i++)
	{
		if (buf[i] == '\t' && 0 == flag)
		{
			memcpy(strtemp, buf+i+1, len);
			strtemp[len+1] = '\0';
			if (0 == strcmp(strtemp, name))
			{
    			i = i+len;
    			flag = 1;
			}
		}
		if (0 == flag)
		{
			continue;
		}
		if (buf[i] == ':' && buf[i+1] == ' ')
		{
			start = i+2;
		}
		if (buf[i] == '\t' && start != 0)
		{
			end = i - 1;
			memset(temp,0,sizeof(temp));
			memcpy(temp,buf+start,(end-start));
			start = 0;
			end = 0;
			break;
		}
	}
	strncpy(value, temp, value_len);
}

/**
  *u32TunerIdx 0,1,2
  *return true for valid
  */
BOOL YWPUBLIC_isTunerAllow(int u32TunerIdx)
{
    int u32Ret = 0;
    int u32Manage = 0;

    u32Manage = get_tuner_info();
    
    switch(u32TunerIdx)
    {
        case 0:
            u32Ret = u32Manage & 1;
            break;
        case 1:
            u32Ret = u32Manage & 2;
            break;
        case 2:
            u32Ret = u32Manage & 4;
            break;
        default:
            printf("tuner index error.%d\n", u32TunerIdx);
            break;
    }
    return (u32Ret != 0) ? TRUE : FALSE;
}

/*GUI show with the App start, do not need press red key */
void YWPLUGIN_SetGuiShowDirect(BOOL bShow)
{
    set_gui_diretc_show(bShow);
}

/*if GUI is destroyed, the App close immediately*/
void YWPLUGIN_SetAppCloseWithGui(BOOL bSync)
{
    set_app_close_with_gui(bSync);
}


