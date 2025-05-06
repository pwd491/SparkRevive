#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <ctype.h>
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

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>

#include "ywdefs.h"
#include "ywos.h"

#include "dvbapi.h"



static cat_struct dmx_cat_data[MAX_DEMUX];
static DEMUXTYPE demux[MAX_DEMUX];
static descrambler_s desc_devices[MAX_DESCRAMBLERS];
static pthread_t dvbapi_thread;


unsigned char dvbapi_ca_setcw(unsigned char *cw,unsigned char device, unsigned char index,unsigned char parity);
void dvbapi_stop_descrambling(int demux_id);
void dvbapi_start_descrambling(unsigned char dmx);
int dvbapi_open_device(int index_demux, int type);
int dvbapi_stop_filter(int demux_index, int type);
void dvbapi_parse_cat(int demux_index, unsigned char *buf, int len);
void dvbapi_start_cat(int dmx);
#ifdef SUPPORT_SETPID
void dvbapi_set_pid(int ca_id, int pid, int index);
#endif



static unsigned int UINT24(unsigned char *ptr)
{
	return	(ptr[0] << 16) | (ptr[1]  <<  8) | (ptr[2]);
}

static unsigned short UINT16(unsigned char *ptr)
{
	return (ptr[0]  <<  8) | (ptr[1]);
}

static unsigned short DVB_LENGTH(unsigned char *ptr)
{
	return UINT16(ptr) & 0x0fff;
}

static unsigned short DVB_PID(unsigned char *ptr)
{
	return UINT16(ptr) & 0x1fff;
}

void cs_ftime(struct timeb *tp)
{
#ifdef NO_FTIME
  struct timeval tv;
  gettimeofday(&tv, (struct timezone *)0);
  tp->time=tv.tv_sec;
  tp->millitm=tv.tv_usec/1000;
#else
  ftime(tp);
#endif
}


void cw_adjust(unsigned char *cw)
{
	cw[7] = cw[6] + cw[5] + cw[4];
	cw[3] = cw[2] + cw[1] + cw[0];
}

static  descrambler_s *getcadev(unsigned char device)
{
	int i;
	
	for (i=0;i<MAX_DESCRAMBLERS;i++) 
	{
		if (device & (1 << i))
		{
			break;
		}
	}
					
	if (i >= MAX_DESCRAMBLERS)
	{
		YWOS_Trace(YWOS_TRACE_ERROR, "Error:[%s] invalid device: 0x%x\n", __FUNCTION__, device);
		return NULL;
	}


	if (desc_devices[i].fd == -1) {
		YWOS_Trace(YWOS_TRACE_ERROR, "Error:[%s] device  0x%x   not available\n", __FUNCTION__, device);
		return 0;
	}

	return &desc_devices[i];
}


unsigned char session_data_parse_length(const unsigned char *src, struct length_field *dest)
{
	int i;

	if (src[0] & 0x80) {
		dest->size = src[0] & 0x7f;
		if (dest->size > 3) {
			YWOS_Trace(YWOS_TRACE_ERROR, "overflow\n");
			return 0;
		}
		dest->value = 0;
		for (i = 0; i < dest->size; i++)
			dest->value = (dest->value << 8) | src[i + 1];
		dest->size++;
	}
	else {
		dest->size = 1;
		dest->value = src[0];
	}

	return 1;
}

static void parse_pmt_sec(int descriptorLength, unsigned char *sec_buf, int *ecmcount, unsigned short *ecmpid, int demux_id )
{

  	int bytesLeft = descriptorLength;
  	int descriptorTag;
	ushort added,n;

  	while (bytesLeft > 0)
	{
    	if (sec_buf[0] == 0x09)
		{
			unsigned char descriptor_length = sec_buf[1];
			unsigned short descriptor_ca_system_id =  (sec_buf[2] << 8) | sec_buf[3];
			int descriptor_ca_pid       = ((sec_buf[4] & 0x1F) << 8) | sec_buf[5];
			added=0;

			ecmpid[*ecmcount] = descriptor_ca_pid;
			(*ecmcount)++;

			for (n=0;n<demux[demux_id].ECMpidcount;n++)
			{
				if (demux[demux_id].ECMpids[n].CAID==descriptor_ca_system_id && demux[demux_id].ECMpids[n].ECM_PID==descriptor_ca_pid)
					added=1;
			}
			if (added==0)
			{
				demux[demux_id].ECMpids[demux[demux_id].ECMpidcount].ECM_PID=descriptor_ca_pid;
				demux[demux_id].ECMpids[demux[demux_id].ECMpidcount].pid=descriptor_ca_pid;
				demux[demux_id].ECMpids[demux[demux_id].ECMpidcount].CAID=descriptor_ca_system_id;
				demux[demux_id].ECMpids[demux[demux_id].ECMpidcount].checked=0;
				demux[demux_id].ECMpids[demux[demux_id].ECMpidcount].notfound=0;
				demux[demux_id].ECMpids[demux[demux_id].ECMpidcount].table=0;
				memcpy(demux[demux_id].ECMpids[demux[demux_id].ECMpidcount].descriptor, sec_buf,  descriptor_length + 2);
				demux[demux_id].ECMpids[demux[demux_id].ECMpidcount++].EMM_PID=0;
			}
    	}
    	descriptorTag 		= *sec_buf++;
    	descriptorLength 	= *sec_buf++;

		bytesLeft -= (2 + descriptorLength);
		sec_buf   +=      descriptorLength;
  	}
}


int enigma_parse_pmt(unsigned char *data, int len, int connfd)
{
	unsigned char cw[16];
	unsigned short programInfoLength;
	unsigned int elementaryPid;
	unsigned short esInfoLength;
	 descriptor *d;

	int program_level_descr_cnt = 0;
	int es_level_descr_cnt;
	int i, j, k;
	int ca_pmt_list_management;
	int demux_id = -1;

	//unsigned short ca_mask=0x01;
	//int dmx_dst;
	//unsigned char *buffer = pmtdat+2;
	//int ca_pmt_list_management = buffer[0];
	unsigned char *buffer = data ;
	unsigned int program_number = (buffer[1] << 8) | buffer[2];
	//int program_info_length = ((buffer[4] & 0x0F) << 8) | buffer[5];
	//unsigned int es_info_length=0;
	unsigned char dmx_dst = 0, dmx_src = 0;
	unsigned short service_pmt_pid;
//#ifdef SUPPORT_SSSP
	unsigned short SatDegree = 0;
	unsigned short TpFreq = 0;
//#endif

int ecmnum=0;
unsigned short ecmpid[ECM_PIDS];

#ifdef SUPPORT_SETPID
	int Mappidcount = 0;
	unsigned short ChlevelEcmPidcount = 0;
	unsigned short ChlevelEcmPid[ECM_PIDS];
#endif

	//plugin_httpmsg("spark-plugin: Get CAPMT!", 1, 1);


	ca_pmt_list_management = data[0];

	for (i = 0; i < MAX_DEMUX; i++)
	{
		if (connfd>0 && demux[i].socket_fd == connfd)
		{
			//PMT Update
			if (ca_pmt_list_management == 0x03 || ca_pmt_list_management == 0x01 || ca_pmt_list_management == 0x05)
				dvbapi_stop_descrambling(i);
			if (ca_pmt_list_management == 0x02)
				demux_id=i;
		}
	}

	if (demux_id==-1)
	{
		for (demux_id=0; demux_id<MAX_DEMUX && demux[demux_id].program_number>0; demux_id++);
	}

	if (demux_id>=MAX_DEMUX)
	{
		YWOS_Trace(YWOS_TRACE_INFO, "error no free id (MAX_DEMUX)");
		return -1;
	}


	programInfoLength = DVB_LENGTH(&data[4]);

	if (programInfoLength)
	{
		for (i = 7; i < programInfoLength + 6; i += d->length + 2)
		{
			d = (descriptor *)&data[i];
			switch (d->tag)
			{
			case 0x09:
				parse_pmt_sec(d->length + 2, &data[i], &ecmnum, ecmpid, demux_id);
				program_level_descr_cnt++;
				break;

			case 0x81:
				if (d->length == 8)
				{
//#ifdef SUPPORT_SSSP
				SatDegree = (data[i+2]	<< 8) | data[i+3];//UINT16(&buf[1]);
				TpFreq = (data[i+4]  << 8) | data[i+5];//UINT16(&buf[1]);
//#endif
				}
				break;

			case 0x82:
				if ( d->length == 2)
				{
					dmx_dst = data[i + 2];
					dmx_src = data[i + 3];

#ifdef SUPPORT_SETPID
					demux[demux_id].SetPid=0;
#endif
					demux[demux_id].ECMpidcount=0;
					demux[demux_id].STREAMpidcount=0;
					demux[demux_id].program_number = program_number;
					demux[demux_id].socket_fd= connfd;
					demux[demux_id].demux_index= dmx_src;
					demux[demux_id].cadev_index= dmx_dst;
//#ifdef SUPPORT_SSSP
					demux[demux_id].SatDegree= SatDegree;
					demux[demux_id].TpFreq= TpFreq;
//#endif
					//YWOS_Trace(YWOS_TRACE_INFO, "dvbapi_start_desc --------------------->[%d] [%d] [%d]\n",demux_id, dmx_dst, dmx_src);
					//YWOS_Trace(YWOS_TRACE_INFO, "dmx_dst %02x dmx_src %02x\n", dmx_dst, dmx_src);
				}
				break;

			case 0x84:
				if (d->length == 2)
				{
					service_pmt_pid = (data[i + 2]  << 8) | data[i + 3]; // UINT16(&data[i + 2]);
				}
				break;
			}
		}
	}

#ifdef SUPPORT_SETPID
	if (program_level_descr_cnt)
	{
		ChlevelEcmPidcount = demux[demux_id].ECMpidcount;
		for (k=0; k<ChlevelEcmPidcount; k++)
		{
			ChlevelEcmPid[k] =  demux[demux_id].ECMpids[k].ECM_PID;
		}
		//YWOS_Trace(YWOS_TRACE_INFO, "program_level_descr_cnt --------------------->[%d] \n",ChlevelEcmPidcount);
	}
#endif


	for (i = programInfoLength + 6; i < len; i += esInfoLength + 5)
	{
		elementaryPid = DVB_PID(&data[i + 1]);
		esInfoLength = DVB_LENGTH(&data[i + 3]);
		es_level_descr_cnt = 0;
		ecmnum=0;

		demux[demux_id].STREAMpids[demux[demux_id].STREAMpidcount].pid = elementaryPid;

#ifdef SUPPORT_SETPID

		demux[demux_id].STREAMpids[demux[demux_id].STREAMpidcount].MapEcmPidcount = 0;
		if (program_level_descr_cnt)
		{
			for (k=0; k<ChlevelEcmPidcount;k++)
			{
				Mappidcount = demux[demux_id].STREAMpids[demux[demux_id].STREAMpidcount].MapEcmPidcount;
				demux[demux_id].STREAMpids[demux[demux_id].STREAMpidcount].MapECMpids[Mappidcount] =ChlevelEcmPid[k];
				demux[demux_id].STREAMpids[demux[demux_id].STREAMpidcount].MapEcmPidcount++;
				//YWOS_Trace(YWOS_TRACE_INFO, "set pid map PS level --------------------->[%d] [%d] [%d] \n",elementaryPid, ChlevelEcmPid[k],demux[demux_id].STREAMpids[demux[demux_id].STREAMpidcount].MapEcmPidcount);
			}
		}
#endif

		if (esInfoLength)
		{
			for (j = i + 6; j < i + esInfoLength + 5; j += d->length + 2)
			{
				d = (descriptor *)&data[j];
				if (d->tag == 0x09)
				{
					parse_pmt_sec(d->length + 2, &data[j], &ecmnum, ecmpid, demux_id);
					es_level_descr_cnt++;
				}
			}
		}
#ifdef SUPPORT_SETPID
		if (ecmnum)
		{
			demux[demux_id].STREAMpids[demux[demux_id].STREAMpidcount].MapEcmPidcount = 0;
			for (k=0; k<ecmnum;k++)
			{
				Mappidcount = demux[demux_id].STREAMpids[demux[demux_id].STREAMpidcount].MapEcmPidcount;

				demux[demux_id].STREAMpids[demux[demux_id].STREAMpidcount].MapECMpids[Mappidcount] =ecmpid[k];
				demux[demux_id].STREAMpids[demux[demux_id].STREAMpidcount].MapEcmPidcount++;
				//YWOS_Trace(YWOS_TRACE_INFO, "set pid map ES level--------------------->[%d] [%d] [%d] \n",elementaryPid, ecmpid[k],demux[demux_id].STREAMpids[demux[demux_id].STREAMpidcount].MapEcmPidcount);
			}
		}
#endif

		demux[demux_id].STREAMpidcount++;

	}

	demux[demux_id].program_number=program_number;






	return demux_id;

}

#ifdef SUPPORT_SETPID

int dvbapi_setdesc(int demux_id, int streamidx, unsigned short pid)
{
	int i, j;

	for (i=0; i <demux[demux_id].STREAMpids[streamidx].MapEcmPidcount; i++)
	{
		for(j=0; j<demux[demux_id].Mcaspidcount; j++)
		{
			if (demux[demux_id].STREAMpids[streamidx].MapECMpids[i] == demux[demux_id].McasPids[j].pid &&\
				 demux[demux_id].McasPids[j].pid == pid)
			{
				dvbapi_set_pid(demux[demux_id].cadev_index, demux[demux_id].STREAMpids[streamidx].pid, demux[demux_id].McasPids[j].Descindex-1);
				return 1;
			}
		}
	}

	return 0;
}


void dvbapi_set_pid(int ca_id, int pid, int index)
{
	descrambler_s *d;
	ca_pid_t ca_pid2;

	if (!(d = getcadev(ca_id)))
		return ;

	memset(&ca_pid2,0,sizeof(ca_pid2));
	ca_pid2.pid = pid;
	ca_pid2.index = index;
	if (ioctl(d->fd, CA_SET_PID, &ca_pid2)==-1)
		YWOS_Trace(YWOS_TRACE_ERROR, "Error CA_SET_PID pid=0x%04x index=%d errno=%d", ca_pid2.pid, ca_pid2.index, errno);
	else
		YWOS_Trace(YWOS_TRACE_ERROR, "dvbapi_set_pid -------------->ca_id=[%d] pid=[%d] index=[%d]\n", ca_id, ca_pid2.pid, ca_pid2.index);

	return;
}


int dvbapi_get_descindex(void)
{
	int i,j,idx=1,fail=1;

	while (fail)
	{
		fail=0;
		for (i=0;i<MAX_DEMUX;i++)
		{
			for (j=0;j<demux[i].Mcaspidcount;j++)
			{
				if (demux[i].McasPids[j].Descindex==idx)
				{
					idx++;
					fail=1;
					break;
				}
			}
		}
	}
	return idx;
}

#endif

unsigned char dvbapi_convert_filter(section_filter *sf, unsigned char *filter, unsigned char *mask)
{
	if (sf->size >18)
	{
		YWOS_Trace(YWOS_TRACE_ERROR, "dvbapi_convert_filter------------->what's this???? [%d]\n", sf->size);
		return 0;
	}

	filter[0] = sf->filter[0];
	mask[0] = sf->mask[0];
	if (sf->size > 1) {
		memcpy(filter+1, sf->filter+3, sf->size -3);
		memcpy(mask+1, sf->mask+3, sf->size -3);
	}
/*	if (sf->size > 8)
		return 1;*/
	if (sf->size > 3)
		return sf->size - 2;
	return sf->size;
}

unsigned char dvbapi_ca_setcw(unsigned char *cw,unsigned char device, unsigned char index,unsigned char parity)
{
	descrambler_s *d;
	size_t offset;
	ca_descr_t cd;

	cw_adjust(cw);

	if (!(d = getcadev(device)))
		return 0;

	if (d->key_num <= index)
	{
		//return 0;
	}

	cd.index = index;
	cd.parity = parity & 0x01;

	offset = ((cd.index * 2) + cd.parity) * 8;

	memcpy(&d->cw_table[offset], cw, 8);
	memcpy(cd.cw, cw, 8);

	//YWOS_Trace(YWOS_TRACE_INFO, "dvbapi_ca_setcw-------------------->%d %d\n", device, index);
	//YWOS_Trace(YWOS_TRACE_INFO, "[0x%x] [0x%x] [0x%x] [0x%x] [0x%x] [0x%x] [0x%x] [0x%x]\n", cw[0],  cw[1], cw[2],cw[3],cw[4],cw[5],cw[6],cw[7]);

	if (ioctl(d->fd, CA_SET_DESCR, &cd) == -1)
		YWOS_Trace(YWOS_TRACE_ERROR, "[%s] CA_SET_DESCR\n", __FUNCTION__);


	return 0;
}

int dvbapi_ca_init(void)
{
	char path[32];
	int count = 0;
	int i = 0;
	int desindex = 0;
	int descr_num = 8;

	for (i=0; i<MAX_DESCRAMBLERS;i++)
	{
		desc_devices[i].fd = -1;
		desc_devices[i].cw_table= NULL;
	}

	i=0;
	for (i = 0; i < MAX_DESCRAMBLERS; i++)
	{
		desindex = 0+i;
		sprintf(path, DVBAPI3_CADEV_PATH, desindex);

		if ((desc_devices[i].fd = open(path, O_RDWR)) == -1)
		{
			YWOS_Trace(YWOS_TRACE_ERROR, "[%s] %s\n", __FUNCTION__, path);
		}
		YWOS_Trace(YWOS_TRACE_INFO, "dvbapi_ca_init------------->Opened %s [%d]\n", path, desc_devices[i].fd);

		desc_devices[i].cw_table = malloc(descr_num * 16);
		desc_devices[i].key_num = descr_num;
		memset(desc_devices[i].cw_table, 0xff, descr_num * 16);
		count++;
	}
	return count;
}

void dvbapi_ca_term(void)
{
	int i = 0;

	for (i = 0; i < MAX_DESCRAMBLERS; i++)
	{
		if (desc_devices[i].fd != -1)
		{
			YWOS_Trace(YWOS_TRACE_INFO, "dvbapi_ca_term------------->close[%d]\n", desc_devices[i].fd);
			close(desc_devices[i].fd);
		}
		if (desc_devices[i].cw_table != NULL)
		{
			free(desc_devices[i].cw_table);
			desc_devices[i].cw_table = NULL;
		}
	}
	return ;
}


int dvbapi_set_filter(int demux_id, int api, unsigned short pid, unsigned char *filt, unsigned char *mask, int timeout, int pidindex, int count, int type)
{
	int ret=-1,n=-1,i;

	for (i=0; i<MAX_FILTER && demux[demux_id].demux_fd[i].fd>0; i++);

	if (i>=MAX_FILTER)
	{
		YWOS_Trace(YWOS_TRACE_INFO, "no free filter");
		return -1;
	}
	n=i;

	demux[demux_id].demux_fd[n].pidindex = pidindex;
	demux[demux_id].demux_fd[n].pid      = pid;
	demux[demux_id].demux_fd[n].type     = type;
	demux[demux_id].demux_fd[n].count    = count;

//	YWOS_Trace(YWOS_TRACE_INFO, "dvbapi_start_filter--------------------> Pid[0x%x]\n", demux[demux_id].demux_fd[n].pid);

	switch(api) {
		case DVBAPI_3:
			demux[demux_id].demux_fd[n].fd = dvbapi_open_device(demux_id, 0);
			struct dmx_sct_filter_params sFP2;

			memset(&sFP2,0,sizeof(sFP2));

			sFP2.pid			= pid;
			sFP2.timeout			= timeout;
			sFP2.flags			= DMX_IMMEDIATE_START;
			memcpy(sFP2.filter.filter,filt,16);
			memcpy(sFP2.filter.mask,mask,16);
			ret=ioctl(demux[demux_id].demux_fd[n].fd, DMX_SET_FILTER, &sFP2);

			break;
		case DVBAPI_1:
			break;

		default:
			break;
	}

	if (ret < 0)
		YWOS_Trace(YWOS_TRACE_INFO, "could not start demux filter (Errno: %d)", errno);

	return ret;
}


void dvbapi_stop_dmx(int demux_id)
{


	dvbapi_stop_filter(demux_id, TYPE_ECM);
	dvbapi_stop_filter(demux_id, TYPE_EMM);
	dvbapi_stop_filter(demux_id, TYPE_CAT);

}

void dvbapi_start_descrambling(unsigned char dmx)
{
	unsigned char n, i;
	unsigned char d, a;
	section_filter *sf;
	unsigned short pid;
	unsigned char channel = dmx;
	unsigned char last_filter;
	unsigned int emm_ecm_filter_id = 2;
	int sflen;
	unsigned char filter[16];
	unsigned char mask[16];
	unsigned char sfcount;

	if (demux[dmx].socket_fd <=0 || demux[dmx].ECMpidcount <=0)
	{
		return;
	}

	//YWOS_Trace(YWOS_TRACE_INFO, "dvbapi_start_desc --------------------->demux_id [%d]\n",dmx);

	for (i = 0; i < demux[dmx].ECMpidcount; i++)
	{
		if (demux[dmx].ECMpids[ i ].pid != 1)
		{

		}
	}

	if (dmx_cat_data[dmx].length)
	{
		//YWOS_Trace(YWOS_TRACE_INFO, "dvbapi_parse_cat------------------------>\n");
		dvbapi_parse_cat(dmx, dmx_cat_data[dmx].data, dmx_cat_data[dmx].length);
	}

	dvbapi_start_cat(dmx);


}

void dvbapi_stop_descrambling(int demux_id)
{
	int i;

	//YWOS_Trace(YWOS_TRACE_INFO, "dvbapi: closing socket (demux_index: %d)\n", demux_id);
	DEMUXTYPE *dmx;

	mcas_debug( "dvbapi_stop_desc --------------------->demux_id [%d]\n",demux_id);

	dmx = &demux[demux_id];

	dmx->demux_index=-1;
	dmx->program_number=0;
	dmx->socket_fd=0;
	dmx->pidindex=-1;


	dvbapi_stop_dmx(demux_id);

	return;
}

void dvbapi_start_cat(int dmx)
{
	unsigned char filter[16];
	unsigned char mask[16];

	memset(filter, 0, 16);
	memset(mask, 0, 16);
	filter[0] = 0x01;
	mask[0] = 0xFF;
	dvbapi_stop_filter(dmx,TYPE_CAT);
	dvbapi_set_filter(dmx, DVBAPI_3, 1, filter, mask, 0, -1, 0, TYPE_CAT);

}

int dvbapi_read_device(int dmx_fd, unsigned char *buf, int length)
{
	int len, rc;
	struct pollfd pfd[1];

	pfd[0].fd = dmx_fd;
	pfd[0].events = (POLLIN | POLLPRI);

	rc = poll(pfd, 1, 1000);
	if (rc<1)
		return -1;

	len = read(dmx_fd, buf, length);

	if (len==-1)
		YWOS_Trace(YWOS_TRACE_INFO, "dvbapi: read error %d on fd %d\n", errno, dmx_fd);

	return len;
}



int dvbapi_open_device(int index_demux, int type)
{
	int dmx_fd;
	char device_path[128];

	if (type==0)
	{
		sprintf(device_path, DVBAPI3_DMXDEV_PATH, demux[index_demux].demux_index);
	}

	if ((dmx_fd = open(device_path, O_RDWR | O_NONBLOCK)) < 0)
	{
		YWOS_Trace(YWOS_TRACE_INFO, "dvbapi: error opening device %s (Errno: %d)\n", device_path, errno);
		return -1;
	}

	return dmx_fd;
}

int dvbapi_stop_filternum(int demux_index, int num)
{
	int ret=-1;
	if (demux[demux_index].demux_fd[num].fd>0)
	{
		ret=ioctl(demux[demux_index].demux_fd[num].fd,DMX_STOP);
		close(demux[demux_index].demux_fd[num].fd);
		demux[demux_index].demux_fd[num].fd=-1;
	}
	return ret;
}


int dvbapi_stop_filter(int demux_index, int type)
{
	int g;

	for (g=0;g<MAX_FILTER;g++)
	{
		if (demux[demux_index].demux_fd[g].fd>0 && demux[demux_index].demux_fd[g].type==type)
		{
			//YWOS_Trace(YWOS_TRACE_INFO, "dvbapi_stop_filter-------------------->Remove Pid[0x%x]\n", demux[demux_index].demux_fd[g].pid);

			ioctl(demux[demux_index].demux_fd[g].fd,DMX_STOP);
			close(demux[demux_index].demux_fd[g].fd);
			demux[demux_index].demux_fd[g].fd=0;
		}
	}

	return 1;
}

void dvbapi_parse_cat(int demux_index, unsigned char *buf, int len)
{
	unsigned short i, j;

	for (i = 8; i < (((buf[1] & 0x0F) << 8) | buf[2]) - 1; i += buf[i + 1] + 2)
	{
		if (buf[i] != 0x09) continue;
		//unsigned short cat_sys_id=(((buf[i + 2] & 0x1F) << 8) | buf[i + 3]);
		unsigned short emm_pid=(((buf[i + 4] & 0x1F) << 8) | buf[i + 5]);
		//YWOS_Trace(YWOS_TRACE_INFO, "cat: CAID: %04x\temm_pid %04x\n", cat_sys_id, emm_pid);
		for (j=0;j<demux[demux_index].ECMpidcount;j++)
		{
			if (demux[demux_index].ECMpids[j].CAID == (((buf[i + 2] & 0x1F) << 8) | buf[i + 3]))
			{
				demux[demux_index].ECMpids[j].EMM_PID=emm_pid;
			}
		}



	}
	return;
}

unsigned char dvbapi_handle_msg(unsigned char *data, int len, int connfd)
{
	unsigned int apdu_tag = UINT24(data);
	struct length_field lf;
	unsigned char *buf;

	if ((apdu_tag & 0xff8080) != 0x9f8000) {
		YWOS_Trace(YWOS_TRACE_INFO, "unknown data format\n");
		return 0;
	}
	if (!session_data_parse_length(&data[3], &lf))
		return 0;

	if (len != (lf.size + lf.value + 3)) {
		YWOS_Trace(YWOS_TRACE_INFO, "incomplete data\n");
		return 0;
	}

	buf = &data[lf.size + 3];
	switch (apdu_tag) {
		case 0x9F8032:	/* ca_pmt */
			enigma_parse_pmt(buf, lf.value, connfd);
			break;

		case 0x9F803F:	/* reserved: descriptor loop */
			break;
	}
	return 0;
}

void dvbapi_handlesockmsg (unsigned char *buffer, unsigned int len, int connfd)
{
	unsigned int val=0, size=0, i, k;

	for (k = 0; k < len; k += 3 + size + val) {
		if (buffer[0+k] != 0x9F || buffer[1+k] != 0x80) {
			YWOS_Trace(YWOS_TRACE_INFO, "dvbapi: unknown socket command: %02x\n", buffer[0+k]);
			return;
		}

		if (k>0) {
			YWOS_Trace(YWOS_TRACE_INFO, "dvbapi: Unsupported capmt. Please report\n");
		}

		if (buffer[3+k] & 0x80) {
			val = 0;
			size = buffer[3+k] & 0x7F;
			for (i = 0; i < size; i++)
				val = (val << 8) | buffer[i + 1 + 3 + k];
			size++;
		} else	{
			val = buffer[3+k] & 0x7F;
			size = 1;
		}
		switch(buffer[2+k]) {
			case 0x32:
				dvbapi_handle_msg(buffer, len, connfd);
				break;
			case 0x3f:

				break;
			default:
				YWOS_Trace(YWOS_TRACE_INFO, "dvbapi: handlesockmsg() unknown command\n");
				//plugin_dump(buffer, "unknown command:", len );
				break;
		}
	}
}

int dvbapi_init_listenfd() {
	int clilen,listenfd;
	struct sockaddr_un servaddr;

	memset(&servaddr, 0, sizeof(struct sockaddr_un));
	servaddr.sun_family = AF_UNIX;
	strcpy(servaddr.sun_path, DVBAPI3_CAPMT_PATH);
	clilen = sizeof(servaddr.sun_family) + strlen(servaddr.sun_path);
//	YWOS_Trace(YWOS_TRACE_INFO, "dvbapi_init_listenfd 1.\n");
	if ((unlink(DVBAPI3_CAPMT_PATH) < 0) && (errno != ENOENT))
		return 0;
//	YWOS_Trace(YWOS_TRACE_INFO, "dvbapi_init_listenfd 2.\n");
	if ((listenfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
		return 0;
//	YWOS_Trace(YWOS_TRACE_INFO, "dvbapi_init_listenfd 3.\n");
	if (bind(listenfd, (struct sockaddr *) &servaddr, clilen) < 0)
		return 0;
//	YWOS_Trace(YWOS_TRACE_INFO, "dvbapi_init_listenfd 4.\n");
	if (listen(listenfd, 5) < 0)
		return 0;
//	YWOS_Trace(YWOS_TRACE_INFO, "dvbapi_init_listenfd 5.\n");

	return listenfd;
}

void dvbapi_process_input(int demux_id, int filter_num, unsigned char *buffer, int len)
{
	int i;
	unsigned short pid;
	unsigned short caid = 0;
	static int ecm_num=0;
	static unsigned char dcw[16], rc;

	rc = 0;
	pid = demux[demux_id].demux_fd[filter_num].pid;

	if (demux[demux_id].demux_fd[filter_num].type == TYPE_ECM)
	{

		//YWOS_Trace(YWOS_TRACE_INFO, "Get ECM ----------------> [%d]\n",pid);


	}
	else if(demux[demux_id].demux_fd[filter_num].type == TYPE_EMM)
	{


	}
	else if (demux[demux_id].demux_fd[filter_num].type == TYPE_CAT)
	{
		dmx_cat_data[demux_id].length = len;
		memcpy(dmx_cat_data[demux_id].data, buffer, len);
		dvbapi_stop_filternum(demux_id, filter_num);
	}
	else
	{

	}

}

void dvbapi_main_local(void * arg)
{
	int maxpfdsize=(MAX_DEMUX*MAX_FILTER)+MAX_DEMUX+2;
	struct pollfd pfd2[maxpfdsize];
	int i,rc,pfdcount,g,connfd,clilen,j;
	int ids[maxpfdsize], fdn[maxpfdsize], type[maxpfdsize];
	struct timeb tp;
	struct sockaddr_un servaddr;
	ssize_t len=0;
  	int listenfd = -1;
	 unsigned char mbuf[4096];


	for (i=0; i<MAX_DEMUX;i++)
	{
		dmx_cat_data[i].length = 0;
	}

	for (i=0;i<MAX_DEMUX;i++)
	{
		memset(&demux[i], 0, sizeof(DEMUXTYPE));

#ifdef SUPPORT_SETPID
		demux[i].Mcaspidcount=0;
#endif

		demux[i].ECMpidcount=0;
		demux[i].program_number=0;
		demux[i].pidindex=-1;
		demux[i].cadev_index=-1;
		demux[i].ca_fd=0;
		demux[i].demux_index=-1;
		demux[i].socket_fd=0;
		demux[i].emm_filter=0;

		for (rc=0;rc<MAX_FILTER;rc++)
		{
			demux[i].demux_fd[rc].fd=0;
			demux[i].demux_fd[rc].pid=0x1fff;
			demux[i].demux_fd[rc].type=-1;
			demux[i].demux_fd[rc].pidindex=-1;
			demux[i].demux_fd[rc].count=0;
		}

		for (rc=0;rc<ECM_PIDS;rc++)
		{
			demux[i].STREAMhandle[rc] = 0;
		}

	}


  //enable listen on camd.socket if we have one, aston
   listenfd = dvbapi_init_listenfd();
   if (listenfd < 1)
	{
	   YWOS_Trace(YWOS_TRACE_INFO, "dvbapi: could not init camd.socket.\n");
	   return;
   }

	if (listenfd == -1)
	{
		YWOS_Trace(YWOS_TRACE_INFO, "dvbapi/stapi: box does not support camd.socket and could not find tmp folder for pmt reading!");
		return;
	}

	cs_ftime(&tp);
	tp.time+=500;

	pfd2[1].fd = listenfd;
	pfd2[1].events = (POLLIN | POLLPRI);
	type[1]=1;

	/*start CAT*/
	demux[0].demux_index = 0;
	dvbapi_start_cat(0);
	demux[0].demux_index = -1;

	while (1)
	{
		//YWOS_TaskSleep(5);

		//if we have no camd.socket do not listen, aston
		pfdcount = (listenfd > 0) ? 2 : 1;
		for (i=0;i<MAX_DEMUX;i++)
		{
			for (g=0;g<MAX_FILTER;g++)
			{
				if (demux[i].demux_fd[g].fd>0)
				{
					pfd2[pfdcount].fd = demux[i].demux_fd[g].fd;
					pfd2[pfdcount].events = (POLLIN | POLLPRI);
					ids[pfdcount]=i;
					fdn[pfdcount]=g;
					type[pfdcount++]=0;
				}
			}

			if (demux[i].socket_fd>0)
			{
				pfd2[pfdcount].fd=demux[i].socket_fd;
				pfd2[pfdcount].events = (POLLIN | POLLPRI | POLLHUP);
				type[pfdcount++]=1;
			}
		}

		rc = poll(pfd2, pfdcount, 500);
		if (rc<1)
		{
			continue;
		}


		for (i = 0; i < pfdcount; i++)
		{
			if (pfd2[i].revents & (POLLHUP | POLLNVAL))
			{
				if (type[i]==1)
				{
					for (j=0;j<MAX_DEMUX;j++)
					{
						if (demux[j].socket_fd==pfd2[i].fd)
						{
							mcas_debug( "dvbapi_stop_socket--------------------------->%d\n", pfd2[i].fd);
							dvbapi_stop_descrambling(j);
						}
					}
					close(pfd2[i].fd);
					continue;
				}
			}
			if (pfd2[i].revents & (POLLIN | POLLPRI))
			{
				if (type[i]==1)
				{
					if (pfd2[i].fd==listenfd)
					{
						connfd = accept(listenfd, (struct sockaddr *)&servaddr, (socklen_t *)&clilen);
						mcas_debug( "dvbapi_start_socket--------------------------->%d\n", pfd2[i].fd);

						if (connfd <= 0)
						{
							mcas_debug( "dvbapi: accept() returns error %d, fd event %d\n", errno, pfd2[i].revents);
							continue;
						}
					}
					else
					{
						mcas_debug( "dvbapi: New capmt on old socket. Please report.\n");
						connfd = pfd2[i].fd;
					}

					len = read(connfd, mbuf, sizeof(mbuf));
					if (len < 3)
					{
						mcas_debug( "dvbapi: camd.socket: too short message received\n");
						continue;
					}

					dvbapi_handlesockmsg(mbuf, len, connfd);

				}
				else
				{
					if ((len=dvbapi_read_device(pfd2[i].fd, mbuf, sizeof(mbuf))) <= 0)
						continue;

					int demux_index=ids[i];
					int n=fdn[i];

					if (pfd2[i].fd==demux[demux_index].demux_fd[n].fd)
					{
						dvbapi_process_input(demux_index,n,mbuf,len);
					}
				}
			}
		}


	}
	mcas_debug( "return...\n");
	return;
}

void dvbapi_init(void)
{
	dvbapi_ca_init();
	pthread_create(&dvbapi_thread, NULL, (void*)dvbapi_main_local, (void*)NULL);
	
}

void dvbapi_term(void)
{
	int id = -1;

	id = pthread_kill(dvbapi_thread,  0);
	printf("dvbapi_term--------------->kill dvbapi_thread result [%d]\n", id);

	for (id=0;id<MAX_DEMUX;id++)
	{
		//if (demux[id].socket_fd >0)
		{
			dvbapi_stop_descrambling(id);
			close(demux[id].socket_fd);
		}
	}
	dvbapi_ca_term();

}


