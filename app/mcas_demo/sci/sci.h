#ifndef __sci_h__
#define __sci_h__

#include <stdbool.h>
#include <sys/time.h>
#include <sys/types.h>


#define SCI_SLOT_NUM	2


typedef struct sci_parameters
{
	unsigned char T;
	unsigned long f;
	unsigned long ETU;
	unsigned long WWT;
	unsigned long CWT;
	unsigned long BWT;
	unsigned long EGT;
	unsigned long clock_stop_polarity;
	unsigned char check;
	unsigned char P;
	unsigned char I;
	unsigned char U;
}SCI_PARAMETERS;

#define SCI_IOW_MAGIC	's'

#define IOCTL_SET_RESET							_IOW(SCI_IOW_MAGIC,1  , unsigned long)
#define IOCTL_SET_PARAMETERS				_IOW(SCI_IOW_MAGIC,4  , SCI_PARAMETERS)
#define IOCTL_GET_PARAMETERS				_IOW(SCI_IOW_MAGIC,5  , SCI_PARAMETERS)
#define IOCTL_GET_IS_CARD_PRESENT		_IOW(SCI_IOW_MAGIC,8  , unsigned long)
#define IOCTL_SET_ATR_READY					_IOW(SCI_IOW_MAGIC,11 , unsigned long)


typedef struct smart_card_t {
	int taskrunning;
	char *name;
	int type; // READER_TYPE_xxx
	int fd;
	int state; // READER_STATE_xxx
	int atrlen;
	int id;
	int convention; //Convention of this ICC
	int protocol_type;
	unsigned long current_baudrate;
	unsigned short BWT,CWT;
	 	int       mhz;      //actual clock rate of reader in 10khz steps
 	int	    cardmhz;	    //standard clock speed your card should have in 10khz steps; normally 357 but for Irdeto cards 600
 	unsigned int read_timeout; // Max timeout (ms) to receive characters
	unsigned int block_delay; // Delay (ms) after starting to transmit
	unsigned int char_delay; // Delay (ms) after transmiting each sucesive char
	unsigned char atr[33];
	struct {
		int (*reset)(struct smart_card_t *);
		int (*read)(struct smart_card_t *, unsigned char *, int);
		int (*write)(struct smart_card_t *, unsigned char *, int);
		int (*status)(struct smart_card_t *);
	} fops;
	pthread_t taskmanager;

}smart_card_t;


enum {
	READER_TYPE_SCI,
	READER_TYPE_PHOENIX
};
enum {
	READER_STATE_UNKNOWN = 0,
	READER_STATE_NOCARD,
	READER_STATE_CARDDETECTED,
	READER_STATE_CARDATR,
	READER_STATE_CARDINITED,
};


int sci_init(void);
int sci_term(void);

#endif




