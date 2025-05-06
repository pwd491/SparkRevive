#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <semaphore.h>

#include "ywdefs.h"
#include "ywos.h"

#include "sci.h"

#define SCI_SLOT_NUM	2
#define ATR_TIMEOUT 5000	/* 5 seconds */
#define MAX_ATR_LEN 33

#define call(arg) \
	if (arg) { \
		YWOS_Trace(YWOS_TRACE_INFO, "ERROR, function call %s returns error.",#arg); \
		return 0; \
	}


#define SCI_LOCK(id) sem_wait(&sem_sci[id])
#define SCI_UNLOCK(id) sem_post(&sem_sci[id])

static smart_card_t smartcards[SCI_SLOT_NUM];
static sem_t sem_sci[SCI_SLOT_NUM];
unsigned char sci_count= 0;


static size_t hweight4(unsigned char v)
{
	size_t r = 0;

	if (v & 8) r++;
	if (v & 4) r++;
	if (v & 2) r++;
	if (v & 1) r++;

	return r;
}

int sci_reset(smart_card_t *sc)
{
	int ret;
	SCI_PARAMETERS sci_param;

	memset(&sci_param,0,sizeof(SCI_PARAMETERS));
	sci_param.ETU = 372;
	//sci_param.fs = 9;
	sci_param.EGT = 3; //not sure why this value is chosen
	sci_param.T = 0;
	ioctl( sc->fd,IOCTL_SET_PARAMETERS,&sci_param);
	ret = ioctl( sc->fd, IOCTL_SET_RESET, NULL);
	ioctl( sc->fd, IOCTL_SET_ATR_READY, NULL);
	return ret;
}

int sci_read (smart_card_t *sc, unsigned char *buf, int len)
{
	int card=0;
	ioctl( sc->fd, IOCTL_GET_IS_CARD_PRESENT, &card);
	if(card==1)
		return read( sc->fd, buf, len);
	else
	{
		//r->state=READER_STATE_NOCARD;
		return 0;
	}
}

int sci_write(smart_card_t *sc,unsigned char *buf, int len)
{
	int card=0;
	ioctl( sc->fd, IOCTL_GET_IS_CARD_PRESENT, &card);
	if(card==1)
		return write( sc->fd, buf, len);
	else
	{
		//r->state=READER_STATE_NOCARD;
		return 0;
	}
}

int sci_status(smart_card_t *sc)
{
	int iscard = 0;
	int rv;

	rv = ioctl(sc->fd, IOCTL_GET_IS_CARD_PRESENT, &iscard);

//  	return rv == 0 ? iscard : rv;
	if(rv==0)
		return iscard;
	else
		return rv;
}

int sci_write_setings (smart_card_t *sc, unsigned char T, unsigned long fs, unsigned long ETU, unsigned long WWT, unsigned long BWT, unsigned long CWT, unsigned long EGT, unsigned char P, unsigned char I)
{
	//int n;
	SCI_PARAMETERS params;
	//memset(&params,0,sizeof(SCI_PARAMETERS));
	ioctl(sc->fd, IOCTL_GET_PARAMETERS, &params);
	params.T = T;
	params.f = fs;

	//for Irdeto T14 cards, do not set ETU
	if (ETU)
		params.ETU = ETU;
	params.EGT = EGT;
	params.WWT = WWT;
	params.BWT = BWT;
	params.CWT = CWT;
	if (P)
		params.P = P;
	if (I)
		params.I = I;

	call (ioctl(sc->fd, IOCTL_SET_PARAMETERS, &params)!=0);
	return 1;
}


static int sci_read_multi(smart_card_t *r, unsigned char *buf, int len, int tmout)
{
	int rv, i;

	//TRACE_F_ENTER;
	if(r->fops.read == NULL)
		return 0; // read cmd unsupported (a bit strange, isn't it? ;)

	i = 0;
	rv = r->fops.read(r, buf, len);
	return rv;

	while(i < len) {

		if(r->state==READER_STATE_NOCARD) {

			return 0;
		}
		if((rv = r->fops.read(r, buf + i, len - i)) < 0)
		{
			return i; // so few bytes, so possibly error
		}
		i += rv;
		if(i < len)
			YWOS_TaskSleep(5); //FIXME
	}

	return i;
}

static int sci_write_multi(smart_card_t *r, unsigned char *buf, int len, int tmout)
{
	int rv;

	if(r->fops.write == NULL)
		return 0; // write cmd unsupported (a bit strange, isn't it? ;)
	rv = r->fops.write(r, buf, len);
	YWOS_TaskSleep(1); //FIXME
	return rv;
}


static unsigned char sci_parse_atr(unsigned char *atr, unsigned char len, unsigned char *ret)
{
	unsigned char  nhist, tdi;
	unsigned char crc = 0;
	unsigned char pos;

	if (len < 2)
		return 0;

	switch (atr[0]) {	// TS
	case 0x3b:
	case 0x3f:
		break;

// irdeto workarounds
	case 0xce:		// irdeto acs1.6
		((unsigned char *)atr)[0] = 0x3b;
		*ret = 17;
		return true;

	case 0xee:		// premiere
	case 0xfc:		// irdeto acs2.x
	case 0xfd:		// irdeto acs2.x
		atr[0] = 0x3b;
		*ret = 20;
		return 0;

	default:
		YWOS_Trace(YWOS_TRACE_INFO, "invalid TS=%02x (irdeto?)\n", atr[0]);
		*ret = 20;
		return 0;

	}

	nhist = (atr[1] & 0x0f);

	if ((pos = hweight4(atr[1] >> 4) + 1) >= len)
		return 0;

	if (atr[1] & 0x80) {	// Td1 present
		for (;;) {
			tdi = atr[pos];

			if ((pos += hweight4(tdi >> 4)) >= len - crc)
				return false;

			if (tdi & 0x0f)
				crc = 1;

			if (!(tdi & 0x80)) {
				pos++;
				break;
			}
		}
	} else {
		pos++;
	}

	if (pos >= len - crc)
		return 0;

	//YWOS_Trace(YWOS_TRACE_INFO, "pos = %d, len = %d, nhist = %d, crc = %d, result = %d\n", pos, len, nhist, crc,pos + nhist + crc);

	*ret = pos + nhist + crc;

	return 1;
}


int sci_read_atr(smart_card_t  *r)
{
	int  n = 0;
	unsigned char atr[MAX_ATR_LEN];


	int atr_size = 2, TDi_exists = 0;
	unsigned char need_size = 0;
	//TRACE_F_ENTER;

	//FIXME: change that dirty ATR read to generalized one

	//for(i = 0; i < 33; i++) {
	while(n<atr_size) {
		if (sci_read_multi(r, atr+n, 1, ATR_TIMEOUT)) {
			//YWOS_Trace(YWOS_TRACE_INFO, "Reset -> %02x\n",atr[n]);
			n++;
		}
		YWOS_TaskSleep( 4 );
		if(n==2) // format character
		{
			// high nibble = TA1 , TB1 , TC1 , TD1
			if(atr[n-1] & 0x10)
				atr_size++;
			if(atr[n-1] & 0x20)
				atr_size++;
			if(atr[n-1] & 0x40)
				atr_size++;
			if(atr[n-1] & 0x80)
			{
				atr_size++;
				TDi_exists=atr_size;
			}
			atr_size+=(atr[n-1] & 0x0F); // historical bytes
		}
		if( (TDi_exists>0) && (n==TDi_exists) )
		{
			TDi_exists=0;
			// high nibble = TA1 , TB1 , TC1 , TD1
			if(atr[n-1] & 0x10)
				atr_size++;
			if(atr[n-1] & 0x20)
				atr_size++;
			if(atr[n-1] & 0x40)
				atr_size++;
			if(atr[n-1] & 0x80)
			{
				atr_size++;
				TDi_exists=atr_size;
			}
			//if (atr[1] == 0x9F) atr_size++;
		}
	}
	/*
	if((i = sci_read_multi(r, atr, 4, ATR_TIMEOUT)) < 3)
	{
		YWOS_Trace(YWOS_TRACE_INFO, "[2LCAMD] No full ATR can be read in device '%s' (Bad ATR)\n", r->name);
		return -1;

	}
	*/



	if (sci_parse_atr(atr, atr_size, &need_size) ) {
		if(atr_size < need_size) {
			n = sci_read_multi(r, atr+atr_size, need_size - atr_size, ATR_TIMEOUT);
			atr_size += n;
		}
	}
	r->state = READER_STATE_CARDATR;
	r->atrlen = atr_size;
	memcpy(r->atr, atr, atr_size);

	return atr_size;
}


int sci_set_fops(smart_card_t *sc)
{
	switch(sc->type)
	{
		case READER_TYPE_SCI:
			sc->fops.reset = sci_reset;
			sc->fops.read = sci_read;
			sc->fops.write =sci_write;
			sc->fops.status = sci_status;
			break;

		case READER_TYPE_PHOENIX:
			return 0;

			break;

		default:
			break;
	}
	return -1;
}

static void* sci_process( void *ptr )
{
	int st,rv = 0;
	smart_card_t *r  = (smart_card_t *)ptr;

	r->state = READER_STATE_NOCARD;

	while (r->taskrunning)
	{
		YWOS_TaskSleep( 100);

		st = r->fops.status(r);
		if((st == 0) && (r->state != READER_STATE_NOCARD))
		{

			r->state = READER_STATE_NOCARD;

			r->atrlen = 0;
			continue;
		}

		if((st == 1) && (r->state == READER_STATE_NOCARD))
		{
			r->state = READER_STATE_CARDDETECTED;
		}
		else
			continue;

		// RESET
		if((rv = r->fops.reset(r)) != 0)
		{
			//once more...
			if((rv = r->fops.reset(r)) != 0)
			{

				r->state = READER_STATE_UNKNOWN;
				YWOS_Trace(YWOS_TRACE_INFO, "TRY Reset Fail\n");
				continue;
			}
		}
		YWOS_TaskSleep(100);
		if((rv = sci_read_atr(r)) < 4) {
			r->state = READER_STATE_UNKNOWN;
			continue;
		}

		if (r->atr[0] == 0x3F && r->atr[1] == 0xFF && r->atr[2] == 0x95)
		{
		//	SCI_PARAMETERS sci_param;
		//	ioctl(r->fd, IOCTL_GET_PARAMETERS, &sci_param);
		//	sci_param.T = 1;
		//	sci_param.ETU = 31;
		//	sci_param.EGT = 5;	// oh oh
		//	ioctl(r->fd, IOCTL_SET_PARAMETERS, &sci_param);
		}
#if 1
		if (r->atr[0] == 0x3b && r->atr[1] == 0x9F && r->atr[2] == 0x21)
		{
			r->cardmhz = 600;
			//SCI_PARAMETERS sci_param;
			//ioctl(r->fd, IOCTL_GET_PARAMETERS, &sci_param);
			//sci_param.T = 1;
			//sci_param.ETU = 31;
			//sci_param.EGT = 5;	// oh oh
			//ioctl(r->fd, IOCTL_SET_PARAMETERS, &sci_param);

		} else
		{
			r->cardmhz = 357;
		}

		//sci_process_atr (r,  r->atr, r->atrlen);

		if (r->atr[0] == 0x3b && r->atr[1] == 0x9F && r->atr[2] == 0x21)
		{
			YWOS_Trace(YWOS_TRACE_ERROR, "set etu...\n");
			r->cardmhz = 600;
			SCI_PARAMETERS sci_param;
			SCI_PARAMETERS params;
			ioctl(r->fd, IOCTL_GET_PARAMETERS, &sci_param);
			sci_param.T = 14;
			sci_param.ETU = 625;
			sci_param.EGT = 30;	// oh oh
			ioctl(r->fd, IOCTL_SET_PARAMETERS, &sci_param);
			//memset (params, 0, sizeof(SCI_PARAMETERS));
			ioctl(r->fd, IOCTL_GET_PARAMETERS, &params);
			//YWOS_Trace(YWOS_TRACE_ERROR, "Setting T=%d ETU=%d WWT=%d CWT=%d BWT=%d EGT=%d clock=%d check=%d P=%d I=%d U=%d\n", (int)params.T, (int)params.ETU, (int)params.WWT, (int)params.CWT, (int)params.BWT, (int)params.EGT, (int)params.clock_stop_polarity, (int)params.check, (int)params.P, (int)params.I, (int)params.U);

		}
#endif


		r->state = READER_STATE_CARDINITED;


	}

	return (void*)0;

}

#define EXTERNAL_FUNCTION

unsigned char sci_read_data(unsigned short sci_id, unsigned char *data, unsigned int len)
{
	unsigned char rc = 0;
	smart_card_t  *r = &smartcards[sci_id];
	
	SCI_LOCK(sci_id);
	
	rc = sci_read_multi(r ,data, len, ATR_TIMEOUT) ;
	
	SCI_UNLOCK(sci_id);

	return rc;
}

unsigned char sci_write_data(unsigned short sci_id, unsigned char *data, unsigned int len) 
{
	unsigned char rc = 0;
	smart_card_t  *r = &smartcards[sci_id];
	
	SCI_LOCK(sci_id);
	
	rc = sci_write_multi(r, data, len, ATR_TIMEOUT) ;
	
	SCI_UNLOCK(sci_id);
	
	return rc;
}

int sci_init(void)
{
	int i;
	int fd;
	int  iret;
	int iscard;
	
	char devname[128] = "/dev/sc0";

	for(i = 0; i < SCI_SLOT_NUM/*FIXME*/; i++)
	{
		struct stat st_info;
		sprintf(devname, "/dev/sci%d", i);

		if(stat(devname, &st_info) != 0)
			continue; //return global_readers_count;

		if(S_ISCHR(st_info.st_mode) == 0)
		{
			continue; //return global_readers_count;
		}
		if((fd = open(devname, O_RDWR|O_NONBLOCK )) < 0)
		{
			YWOS_Trace(YWOS_TRACE_INFO, "[sci_init] Device can't be opened [%s]\n", devname);
			continue;
		}

		if( ioctl(fd, IOCTL_GET_IS_CARD_PRESENT, &iscard) <0)
		{
			YWOS_Trace(YWOS_TRACE_INFO, "[sci_init] Check card present failed on [%s]\n", devname);
			continue;
		}

		// good, we found device (hopefully)
		smartcards[sci_count].type = READER_TYPE_SCI;
		smartcards[sci_count].state = READER_STATE_UNKNOWN;
		smartcards[sci_count].atrlen = 0;
		sci_set_fops(&smartcards[sci_count]);
		memset(smartcards[sci_count].atr, 0 ,sizeof(smartcards[sci_count].atr));
		smartcards[sci_count].name = strdup(devname);
		
		smartcards[sci_count].fd = fd;
		smartcards[sci_count].id = sci_count;
		smartcards[sci_count].taskrunning = 1;
		sem_init(&sem_sci[sci_count], 0, 1);
		
		pthread_create( &smartcards[sci_count].taskmanager, NULL, &sci_process, (void *)&smartcards[sci_count]);
		
		sci_count++;
		YWOS_Trace(YWOS_TRACE_INFO, "[sci_init]------------------->open [%s] [%d]\n", devname, sci_count);

	}
	return sci_count;
}



int sci_term(void)
{
	int i, iret;

	for(i = 0; i < sci_count; i++)
	{
		if (smartcards[i].taskmanager > -1)
		{
			smartcards[i].taskrunning = 0;
			iret = pthread_kill(smartcards[i].taskmanager, 0);
			YWOS_Trace(YWOS_TRACE_INFO, "[sci_term]--------------->kill sci task [%d]\n", iret);
			
			smartcards[i].taskmanager = -1;
		}

		if(smartcards[i].fd > -1)
		{
			close(smartcards[i].fd);
			smartcards[i].fd = -1;
		}
		sem_destroy(&sem_sci[i]);
		YWOS_Trace(YWOS_TRACE_INFO, "[sci_term]--------------->close [%s]\n", smartcards[i].name);
	}

	return 0;
}

