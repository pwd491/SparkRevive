#ifndef __MCAS_H__
#define  __MCAS_H__



#define SC_NUM_OF_SLOT		2
typedef unsigned char (*dcw_callback)(unsigned char *cw,unsigned char device, unsigned char index,unsigned char parity);

typedef struct
{
	dcw_callback	dcw_cb;

}mcas_config_t;

enum
{
	MCAS_SC_OK = 5,
	MCAS_SC_NOK,
	MCAS_SC_INIT,
	MCAS_SC_REMOVE,
	MCAS_SC_INSERT,
	MCAS_SC_POPUP,
	MCAS_SC_MANUAL,

};

void mcas_debug(const char *format, ...);
char *mcas_get_cas_info( unsigned short caid );
void mcas_dump( void *data, int len );

int mcas_handle_descriptor(unsigned char channel, unsigned short caid, unsigned short pid, unsigned char * desc, unsigned char len);
int mcas_handle_cat_desc(unsigned short caid, unsigned short pid, unsigned char* desc, unsigned char len);

unsigned char mcas_handle_ca_descriptor(unsigned char *descriptor, unsigned char type, unsigned char channel);	// type : 0 = CAT, 1 = PMT

int mcas_handle_ecm(unsigned char channel, unsigned char* data, unsigned short pid, unsigned short ca_id, unsigned char* dcw);
void mcas_handle_emm(unsigned char* data, unsigned short caid, unsigned short pid);

void mcas_card_init(unsigned short sc, unsigned char* atr, unsigned char len, void *io_callback);
void mcas_card_deinit(unsigned short sc);

int mcas_get_pid_count();
int mcas_get_pidf_from_count( int );
int mcas_filter_count( int, int );
void *mcas_get_sf( int, int , int );

void chmgr_try_change_channel( int, int );
int chmgr_get_curr_logic_channel();
void mcas_clear_ecm_pid( int );
void mcas_filter_list();

int mcas_have_mmi(int);

void mcas_free_flash();
int mcas_close();

void monitor_startEMM(unsigned short pid,  unsigned char dmx);
void SleepMS(int msec);
void mcas_stop(void);
void mcas_init(unsigned char , unsigned char);

int reader_boot(int id);
int sci_setup(void);
int st_sci_setup(void);

int descrambler_init(void);

void dvbapi_main_local(void * arg);

#endif

