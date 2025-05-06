#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdarg.h>
#include <time.h>
#include <sys/timeb.h>
#include <limits.h>
#include <pwd.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>

#include "sparkid.h"


char  spark_stbid[SPARK_ID_LEN];
char  spark_chipid[SPARK_ID_LEN];
char  spark_macid[SPARK_ID_LEN];
char  spark_version[SPARK_ID_LEN];

#define SPARK_VERSION_FILE "/tmp/.spark_version"

void spk_strncpy(char * destination, const char * source, size_t num)
{
	unsigned int l, size = strlen(source);
	if(size > num - 1) l = num - 1;
	else l = size;
	memcpy(destination, source, l);
	destination[l] = '\0';
}

void spark_get_sysinfo(char *name,char *value)
{
	char buf[512] = {0};
	int i = 0;
	int k = 0;
	int flag = 0;
	int start = 0,end = 0;
	int len = 0;
	char temp[128] = {0};
	char strtemp[128] = {0};
	FILE *fp = fopen("//proc//sparkid","r");
	if(NULL == fp)
	{
		printf("Can not open //proc//sparkid\r\n");
	}
	fread(buf,1,sizeof(buf),fp);
	fclose(fp);
	//len = strlen(name);
	len = strlen(name);
	for (i = 0;i<sizeof(buf);i++)
	{
		if (buf[i] == '\t' && 0 == flag)
		{
			//memcpy(strtemp,buf+i+1,len);
			memcpy(strtemp,buf+i+1,len);
			strtemp[len+1] = '\0';
			//if (0 == strcmp(strtemp,name))
			if (0 == strcmp(strtemp,name))
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
			//memset(temp,0,sizeof(temp));
			memset(temp,0,sizeof(temp));
			//memcpy(temp,buf+start,(end-start));
			memcpy(temp,buf+start,(end-start));
			start = 0;
			end = 0;
			break;
		}
	}
	//strcpy(value,temp);
	spk_strncpy(value,temp, SPARK_ID_LEN);
}

char* spark_get_stbid(void)
{
	char name[256];
	char stbidraw[SPARK_ID_LEN];

	memset(name, 0, sizeof(name));
	memset(stbidraw, 0, sizeof(stbidraw));

	spk_strncpy(name, "stb id",  sizeof(name));
	spark_get_sysinfo(name,stbidraw);

	memset(spark_stbid, 0, sizeof(spark_stbid));

	snprintf(spark_stbid, SPARK_ID_LEN, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
		stbidraw[0], stbidraw[1], stbidraw[2], stbidraw[3], stbidraw[4], stbidraw[5],stbidraw[6], stbidraw[7],\
		stbidraw[9], stbidraw[10], stbidraw[11], stbidraw[12], stbidraw[13], stbidraw[14]);

	return (char*)spark_stbid;

}

char* spark_get_chipid(void)
{
	char name[256];
	char chipidraw[SPARK_ID_LEN];

	memset(name, 0, sizeof(name));
	memset(chipidraw, 0, sizeof(chipidraw));

	spk_strncpy(name, "chip id", sizeof(name));
	spark_get_sysinfo(name,chipidraw);

	memset(spark_chipid, 0, sizeof(spark_chipid));
	spk_strncpy(spark_chipid, chipidraw, sizeof(spark_chipid));


	return (char*)spark_chipid;
}

char* spark_get_macid(void)
{
	int i=0;
	char name[256];
	char macidraw[SPARK_ID_LEN];

	memset(name, 0, sizeof(name));
	memset(macidraw, 0, sizeof(macidraw));

	spk_strncpy(name, "mac address", sizeof(name));
	spark_get_sysinfo(name,macidraw);

	memset(spark_macid, 0, sizeof(spark_macid));
	snprintf(spark_macid, SPARK_ID_LEN, "%c%c%c%c%c%c%c%c%c%c%c%c",
		macidraw[0], macidraw[1], macidraw[3], macidraw[4], macidraw[6], macidraw[7],macidraw[9], macidraw[10],\
		macidraw[12], macidraw[13], macidraw[15], macidraw[16]);


	return (char*)spark_macid;
}

char* spark_get_version(void)
{
    struct stat ftype;
	char buf[SPARK_ID_LEN] = {0};
	FILE *fp;

	memset(spark_version, 0, sizeof(spark_version));
	memset(buf, 0, sizeof(buf));

	
    if(stat(SPARK_VERSION_FILE, &ftype) == 0)
    {
		fp = fopen(SPARK_VERSION_FILE,"r");
		if(NULL == fp)
		{
			printf("Can not open %s\r\n", SPARK_VERSION_FILE);
		}		
		 fread(buf,1,sizeof(buf),fp);
		fclose(fp);		
		memcpy(spark_version, buf, 6);
		
    }
	else
	{
		strcpy(spark_version, "1.2.44");
	}
	printf("%s\n", spark_version);

	return (char*)spark_version;
	
}





