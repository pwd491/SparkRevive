//#define MEM_DEBUG
//#define DEBUG
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ywdefs.h"
#include "key_db.h"
#include "ywos.h"


#define T0_CMD_LENGTH	5
#define T0_CLA_OFFSET	0
#define T0_INS_OFFSET	1
#define T0_P1_OFFSET	2
#define T0_P2_OFFSET	3
#define T0_P3_OFFSET	4
#define T0_RETRIES_DEFAULT		3
#define TIME_DELAY		10000


typedef enum
{
  	SC_OK,
  	SC_INIT_ERR,
  	SC_WRITE_ERR,
  	SC_READ_ERR,
  	SC_TIMEOUT_ERR,
  	SC_UNKOWN_ERR,
  	SC_NOMOREDATA,
} enSC_ERROR;



typedef void (* sc_callback)(void *);




void (* message_callback)(unsigned short, unsigned char, unsigned short, char *) = NULL;


U8 char2int(U8  src)
{
	if (src >=  '0'&& src <= '9')
		return src  - '0';
	else if (src >=  'A' && src <= 'F')
		return src  - 'A' + 10;
	else if (src >=  'a'&& src <= 'f')
		return src - 'a' + 10;
	else
		return 0;
}

void str2bytes(U8  *desc, U8  *src, U8  len)
{
	U16 i;

	if (len%2)
	{
		//error
		return;
	}
		
	for (i = 0; i < len/2; i++)
	{
		desc[i] = ((char2int(src[2*i])&0x0F)<<4)|(char2int(src[2*i+1])&0x0F);
	}

}

int str2hex(char *s)
{
	int i,n;

	n=0;
	for(i=0;s[i]!='\0';i++)
	{
		if(s[i]>='0'&&s[i]<='9')
			n=n*16+s[i]-'0';
		if(s[i]>='a'&&s[i]<='f')
			n=n*16+s[i]-'a'+10;
		if(s[i]>='A'&&s[i]<='F')
			n=n*16+s[i]-'A'+10;
	}
	return(n);
}

int str2decimal(char *s)
{
	int i,n;

	n=0;
	for(i=0;s[i]!='\0';i++)
	{
		if(s[i]>='0'&&s[i]<='9')
			n=n*10+s[i]-'0';
		if(s[i]>='a'&&s[i]<='f')
			n=n*10+s[i]-'a'+10;
		if(s[i]>='A'&&s[i]<='F')
			n=n*10+s[i]-'A'+10;
	}
	return(n);
}

void rmspaceinstr(U8 *src, U8*  dest)
{
	U16 i;

	while(*src)
	{
		if (*src != 0x20)
		{
			*dest  = *src;
			dest++;
		}
		src++;
	}
	*dest = 0;
}





//////////////////////////////////////////////////////////////////////////////////////////////

void SleepMS(int msec)
{
	usleep(msec*1000);
}


//////////////////////////////////////////////////////////////////////////////////////////////

void SCI_PRINT( unsigned char *buf, int ACK, unsigned char sw1, unsigned char sw2)
{
#if 1
		int i, j;

		mcas_debug( "-> ");
		for (i = 0; i < 5; i++)
			mcas_debug( "%02X ", buf[i]);
		if (ACK > 0)
			mcas_debug( "[%02X] ", ACK);
		if (buf[4] > 0)
			for (j = 0,i = 5; j < buf[4]; j++,i++)
				mcas_debug( "%02X ", buf[i]);
		mcas_debug( "(%02X %02X)\n", sw1, sw2);
#endif

}


void mcas_card_msg_event(unsigned short sc, unsigned short *caid, unsigned char insert)
{

}

/* //////////////////////////////////////////////////////////////////////////////////////////////////////
//		osd dirty show some info (Card insertion etc...)
/////////////////////////////////////////////////////////////////////////////////////////////////////// */



void mcas_draw_popup_msg(char* str1, char *str2)
{

}


void mcas_write_dcw(unsigned char *edcw, unsigned char *odcw)
{
	YWOS_Trace(YWOS_TRACE_ERROR, "DCW Comming form emu\n write them to Descrambler\n");
}



void db_read_key_data(unsigned char  *d)		/// 64 kbyte
{

	FILE * of = 0;
	if(NULL == d)
	{
		YWOS_Trace(YWOS_TRACE_ERROR, "%s, Error: the parameter is NULL\n", __func__);
		return;
	}
	of  = fopen( "/var/keys/keydata.bin", "rb");
	if (!of)
	{
		return;
	}
	fread( d, 1, 0x10000,  of);

	fclose(of);
}


void db_write_key_data(unsigned char *data)
{
	FILE * of = 0;
	YWOS_Trace(YWOS_TRACE_ERROR, "db_write_key_data(data = %08x)\n", data );
	//of  = fopen( "/var/keys/keydata.bin", "wb");
	//status = mkdirat("/var/", "keys" , 0777);

	of = fopen("/var/keys/keydata.bin", "wb");
	if (of) {
		fwrite( data, 1, 0x10000,  of);
	//WriteKeyDate( data );
		fclose(of);
	}
}

void mcas_debug(const char *format, ...)
{
#if defined(DEBUG)
	va_list argp;
	char printstr [4096];

	if( printstr == NULL )
	{
		YWOS_Trace(YWOS_TRACE_INFO, "Cannot alloc!!\n");
		return;
	}

	va_start(argp, format);
	vsprintf( printstr, (char *)format, argp );
	printf( printstr );
	//SaveLog(printstr);
	va_end(argp);
#endif

}




