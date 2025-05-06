

#define MAX_DEMUX 5
#define MAX_DESCRAMBLERS 4

#define MAX_CAID 50
#define ECM_PIDS 20
#define MAX_FILTER 20

#define TYPE_ECM 0
#define TYPE_EMM 1
#define TYPE_CAT 2

#define DVBAPI_3	0
#define DVBAPI_1	1


#define DVBAPI3_CADEV_PATH "/dev/dvb/adapter0/ca%u"
#define DVBAPI3_DMXDEV_PATH "/dev/dvb/adapter0/demux%d"
#define DVBAPI3_CAPMT_PATH "/tmp/camd.socket.mcas"


#define DMX_START		 _IO('o', 41)
#define DMX_STOP		 _IO('o', 42)
#define DMX_SET_FILTER		 _IOW('o', 43, struct dmx_sct_filter_params)
#define CA_RESET          _IO ('o', 128)
#define CA_GET_CAP        _IOR('o', 129, ca_caps_t)
#define CA_GET_SLOT_INFO  _IOR('o', 130, ca_slot_info_t)
#define CA_GET_DESCR_INFO _IOR('o', 131, ca_descr_info_t)
#define CA_GET_MSG        _IOR('o', 132, ca_msg_t)
#define CA_SEND_MSG       _IOW('o', 133, ca_msg_t)
#define CA_SET_DESCR      _IOW('o', 134, ca_descr_t)
#define CA_SET_PID        _IOW('o', 135, ca_pid_t)


typedef struct ECMPIDS
{
	unsigned short CAID;
	unsigned short ECM_PID;
	unsigned short pid;
	unsigned short EMM_PID;
	int checked;
	int notfound;
	unsigned char table;
	unsigned char descriptor[255];
} ECMPIDSTYPE;

typedef struct MCASPID
{
	unsigned short pid;
	int Descindex;

} MCASPIDTYPE;


typedef struct STREAMPIDPID
{
	unsigned short pid;
	unsigned short MapEcmPidcount;
	unsigned short MapECMpids[10];

} STREAMPIDTYPE;


typedef struct filter_s
{
	int fd;
	int pidindex;
	int pid;
	int type;
	int count;

} FILTERTYPE;

typedef struct demux_s
{
	unsigned short demux_index;
	FILTERTYPE demux_fd[MAX_FILTER];
	unsigned short cadev_index;
	int ca_fd;
	int socket_fd;

//#ifdef SUPPORT_SSSP
	unsigned short SatDegree;
	unsigned short TpFreq;
//#endif

	unsigned short ECMpidcount;
	ECMPIDSTYPE ECMpids[ECM_PIDS];

#ifdef SUPPORT_SETPID
	int SetPid;
	unsigned short Mcaspidcount;
	MCASPIDTYPE McasPids[ECM_PIDS];
#endif

	int pidindex;
	unsigned short program_number;
	unsigned short STREAMpidcount;
	STREAMPIDTYPE STREAMpids[ECM_PIDS];
	int emm_filter;
	int STREAMhandle[ECM_PIDS];

} DEMUXTYPE;

#define DMX_FILTER_SIZE 16



//dbox2+ufs
typedef struct dmx_filter
{
	uint8_t  filter[DMX_FILTER_SIZE];
	uint8_t  mask[DMX_FILTER_SIZE];
	uint8_t  mode[DMX_FILTER_SIZE];
} dmx_filter_t;


struct dmx_sct_filter_params
{
	uint16_t	    pid;
	dmx_filter_t	    filter;
	uint32_t	    timeout;
	uint32_t	    flags;
#define DMX_CHECK_CRC	    1
#define DMX_ONESHOT	    2
#define DMX_IMMEDIATE_START 4
#define DMX_KERNEL_CLIENT   0x8000
};

typedef struct ca_descr {
	unsigned int index;
	unsigned int parity;	/* 0 == even, 1 == odd */
	unsigned char cw[8];
} ca_descr_t;

typedef struct ca_pid {
	unsigned int pid;
	int index;		/* -1 == disable*/
} ca_pid_t;

struct length_field {
	unsigned size			: 8;
	unsigned value			: 24;
};

typedef struct descriptor_t {
	unsigned tag	: 8;
	unsigned length	: 8;
}descriptor;


typedef struct cat_struct_t {
	unsigned char data[1024];
	unsigned char length;
}cat_struct;

typedef struct {
	unsigned int		channel;
	unsigned short		caid;
	unsigned short		pid;
	unsigned char		filter[32];
	unsigned char		mask  [32];
	unsigned char		size;
	unsigned char		handler;				// sc emu etc...
	void*					cb;
	void* 			*sc;
	void*					*parent;
} section_filter; // dummy

typedef struct descrambler_t {
	int fd;
	int key_num;
	unsigned char *cw_table;
}descrambler_s;








