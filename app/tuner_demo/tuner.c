#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/poll.h>
#include <sys/param.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

#include <stdint.h>
#include <sys/time.h>

#include "frontend.h"
//#include "../include/dmx.h"
//#include "../include/audio.h"
//#include "../include/version.h"
#include "typedef.h"
#include "lnb.h"
#include "tuner.h"

#ifndef TRUE
#define TRUE (1==1)
#endif
#ifndef FALSE
#define FALSE (1==0)
#endif


#define DVB_API_VERSION 5
#define DVB_API_VERSION_MINOR 1


#define FRONTENDDEVICE "/dev/dvb/adapter%d/frontend%d"


struct diseqc_cmd {
	struct dvb_diseqc_master_cmd cmd;
	uint32_t wait;
};

#define DVBS	0
#define DSS	1
#define DVBS2	2

static int do_tune(int fefd, unsigned int ifreq, unsigned int sr, unsigned int delsys)
    {
        /*  API Major=3, Minor=1    */
        struct dvb_frontend_parameters tuneto;
        struct dvb_frontend_event ev;
        /*  API Major=3, Minor=2    */
#if ((DVB_API_VERSION == 3) && (DVB_API_VERSION_MINOR == 3))
        struct dvbfe_params fe_params;
#endif
    
        /* discard stale QPSK events */
        while (1) {
            if (ioctl(fefd, FE_GET_EVENT, &ev) == -1)
            break;
        }
    
        if ((DVB_API_VERSION == 3) && (DVB_API_VERSION_MINOR == 3)) {
            printf("\n%s: API version=%d, delivery system = %d\n", __func__, DVB_API_VERSION_MINOR, delsys);
    
#if ((DVB_API_VERSION == 3) && (DVB_API_VERSION_MINOR == 3))
            fe_params.frequency = ifreq;
            fe_params.inversion = INVERSION_AUTO;
    
            switch (delsys) {
            case DVBS:
                fe_params.delsys.dvbs.symbol_rate = sr;
                fe_params.delsys.dvbs.fec = FEC_AUTO;
                printf("%s: Frequency = %d, Srate = %d\n",
                    __func__, fe_params.frequency, fe_params.delsys.dvbs.symbol_rate);
                break;
            case DSS:
                fe_params.delsys.dss.symbol_rate = sr;
                fe_params.delsys.dss.fec = FEC_AUTO;
                printf("%s: Frequency = %d, Srate = %d\n",
                    __func__, fe_params.frequency, fe_params.delsys.dss.symbol_rate);
                break;
            case DVBS2:
                fe_params.delsys.dvbs2.symbol_rate = sr;
                fe_params.delsys.dvbs2.fec = FEC_AUTO;
                printf("%s: Frequency = %d, Srate = %d\n",
                    __func__, fe_params.frequency, fe_params.delsys.dvbs2.symbol_rate);
                break;
            default:
                return -EINVAL;
            }
            printf("%s: Frequency = %d, Srate = %d\n\n\n",
                __func__, fe_params.frequency, fe_params.delsys.dvbs.symbol_rate);
    
            if (ioctl(fefd, DVBFE_SET_PARAMS, &fe_params) == -1) {
                perror("DVBFE_SET_PARAMS failed");
                return FALSE;
            }
#endif
    
        } else if ((DVB_API_VERSION == 3) && (DVB_API_VERSION_MINOR == 1)){
            tuneto.frequency = ifreq;
            tuneto.inversion = INVERSION_AUTO;
            tuneto.u.qpsk.symbol_rate = sr;
            tuneto.u.qpsk.fec_inner = FEC_AUTO;
            if (ioctl(fefd, FE_SET_FRONTEND, &tuneto) == -1) {
                perror("FE_SET_FRONTEND failed");
                return FALSE;
            }
        } else if (DVB_API_VERSION == 5){
            tuneto.frequency = ifreq;
            tuneto.inversion = INVERSION_AUTO;
            tuneto.u.qpsk.symbol_rate = sr;
            tuneto.u.qpsk.fec_inner = FEC_AUTO;
            if (ioctl(fefd, FE_SET_FRONTEND, &tuneto) == -1) {
                perror("FE_SET_FRONTEND failed");
                return FALSE;
            }
        }
        return TRUE;
    }


/**
    *return 1  lock
    *return 0  unlock
    */
int check_frontend (int fe_fd)
{
    int ret = 0;
	fe_status_t status;
	uint16_t snr, signal;
	uint32_t ber, uncorrected_blocks;
	int timeout = 0;

	do 
    {
		if (ioctl(fe_fd, FE_READ_STATUS, &status) == -1)
			perror("FE_READ_STATUS failed");
		/* some frontends might not support all these ioctls, thus we
		 * avoid printing errors
		 */
		if (ioctl(fe_fd, FE_READ_SIGNAL_STRENGTH, &signal) == -1)
			signal = -2;
		if (ioctl(fe_fd, FE_READ_SNR, &snr) == -1)
			snr = -2;
		if (ioctl(fe_fd, FE_READ_BER, &ber) == -1)
			ber = -2;
		if (ioctl(fe_fd, FE_READ_UNCORRECTED_BLOCKS, &uncorrected_blocks) == -1)
			uncorrected_blocks = -2;

		printf ("status %02x | signal %04x | snr %04x | ber %08x | unc %08x | ",
			status, signal, snr, ber, uncorrected_blocks);

		if (status & FE_HAS_LOCK)
        {
            ret = 1;
			printf("FE_HAS_LOCK");
        }
		printf("\n");

		if ((status & FE_HAS_LOCK) || (++timeout >= 10))
			break;

		usleep(100000);
	} 
    while (1);

	return ret;
}

static struct lnb_types_st lnb_type;

void diseqc_send_msg(int fd, fe_sec_voltage_t v, struct diseqc_cmd *cmd,
		     fe_sec_tone_mode_t t)
{
	if (ioctl(fd, FE_SET_TONE, SEC_TONE_OFF) == -1)
		perror("FE_SET_TONE failed");
	if (ioctl(fd, FE_SET_VOLTAGE, v) == -1)
		perror("FE_SET_VOLTAGE failed");
		usleep(15 * 1000);
	if (ioctl(fd, FE_DISEQC_SEND_MASTER_CMD, &cmd->cmd) == -1)
		perror("FE_DISEQC_SEND_MASTER_CMD failed");
		usleep(cmd->wait * 1000);
		usleep(15 * 1000);
	if (ioctl(fd, FE_SET_TONE, t) == -1)
		perror("FE_SET_TONE failed");
}

/* digital satellite equipment control,
 * specification is available from http://www.eutelsat.com/
 */

static int set_peripheral(int fd, 
            res_tuner_diseqc_T eDiseqc,
            int pol_vert, 
            fe_sec_tone_mode_t e22K
    )
{
    struct diseqc_cmd cmd =
        { {{0xe0, 0x10, 0x38, 0xf0, 0x00, 0x00}, 4}, 0 };

    /**
     * param: high nibble: reset bits, low nibble set bits,
     * bits are: option, position, polarizaion, band
     */
    cmd.cmd.msg[3] =
        0xf0 | (((eDiseqc * 4) & 0x0f) | ((SEC_TONE_ON == e22K) ? 1 : 0) | (pol_vert ? 0 : 2));

    diseqc_send_msg(fd, pol_vert ? SEC_VOLTAGE_13 : SEC_VOLTAGE_18,
            &cmd, e22K);

    return TRUE;
}


BOOL start_frontend(int fd,
    char* lnb, /*UNIVERSAL, C-BAND*/
    fe_sec_tone_mode_t e22K,
    res_tuner_diseqc_T eDiseqc,
    int freq  /*MHZ*/,
    int sym,
    int pol_vert/*horizontal=0,vertical=1*/
    )
{
    int ret = 0;
    int hiband = 0;
    int ifreq = 0; /*KHZ*/
    fe_sec_tone_mode_t e22K_temp = SEC_TONE_ON;
    
    lnb_type = *lnb_enum(0);
    ret = lnb_decode(lnb, &lnb_type);
    if(ret < 0)
    {
        printf("LNB Error.\n");
        return ret;
    }
	lnb_type.low_val *= 1000;	 /* convert to kiloherz */
	lnb_type.high_val *= 1000;	 /* convert to kiloherz */
	lnb_type.switch_val *= 1000; /* convert to kiloherz */

    freq *= 1000;
    
    if(0 == lnb_type.switch_val)
    {
        if (freq < lnb_type.low_val)
            ifreq = lnb_type.low_val - freq;
        else
            ifreq = freq - lnb_type.low_val;
        hiband = 0;
        e22K_temp = e22K;
    }
    else
    {
    	if (lnb_type.switch_val && lnb_type.high_val &&
    		freq >= lnb_type.switch_val)
    		hiband = 1;

    	if (hiband)
    		ifreq = freq - lnb_type.high_val;
    	else 
        {
    		if (freq < lnb_type.low_val)
    			ifreq = lnb_type.low_val - freq;
        	else
        		ifreq = freq - lnb_type.low_val;
    	}
        e22K_temp = hiband ? SEC_TONE_ON : SEC_TONE_OFF;
    }
    if(set_peripheral(fd, eDiseqc, pol_vert, e22K_temp))
    {
        ret = do_tune(fd, ifreq, sym, 0);
    }
    return ret;
    //check_frontend (fd);
    
}

/**
  *get frontend handle.
  *return -1 for error
  */
int open_frontend(int adapter, int frontend)
{
    char fedev[128] = {0};
    int fd = 0;

    snprintf(fedev, sizeof(fedev), FRONTENDDEVICE, adapter, frontend);
    printf("open %s\n", fedev);
	if ((fd = open(fedev, O_RDWR | O_NONBLOCK)) < 0) 
    {
		perror("opening frontend failed");
		return -1;
	}
    return fd;
}

void close_frontend(int fd)
{
    close(fd);
}




//#define _FRONTEND_TEST_
#ifdef _FRONTEND_TEST_
int main(void)
{
    int fd = 0;

    fd = open_frontend(1, 0);
    //start_frontend(fd, "C-BAND", SEC_TONE_OFF, TUNER_LNB_DISEQC_A,3840,27500000,0);
    start_frontend(fd, "C-BAND", SEC_TONE_OFF, TUNER_LNB_DISEQC_A,3807,6000000,1);
    return 0;
}
#endif





