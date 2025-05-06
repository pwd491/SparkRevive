/**
 * @file
 * @brief initialization file read and write API
 * @author Deng Yangjun
 * @date 2007-1-9
 * @version 0.1
 */

#ifndef INI_FILE_H_
#define INI_FILE_H_

#ifdef __cplusplus
extern "C"
{
#endif


#define SECTION_LEN 16
#define LABEL_LEN 16
#define KEY_LEN 16
#define SERVNAME_LEN 48
#define SERVICEPORT_LEN 16
#define USERNAME_LEN 48
#define PASSWORD_LEN 48
#define DESKEY_LEN 48
#define PROTOCOL_LEN 16
#define GROUP_LEN 8

typedef struct CFGInfo_s
{
	char     section[SECTION_LEN];
    char     label[LABEL_LEN];
	char     key[KEY_LEN];
	char     servname[SERVNAME_LEN];
	char     serviceport[SERVICEPORT_LEN];
	char     serviceport_end[SERVICEPORT_LEN];
	char     username[USERNAME_LEN];
	char     password[PASSWORD_LEN];
	char	 encrypt[2];
	char     deskey[DESKEY_LEN];
	char     protocol[PROTOCOL_LEN];
	char     group[GROUP_LEN];
	char     reserv2[8];
	struct CFGInfo_s *next;
}CFGInfo_T;



#define _LIST_OPERATE_
//cfg data list
void CFGDataList_Init();
void CFGDataList_Release();
int CFGDataList_AddNode(CFGInfo_T *node);
int CFGDataList_DeleteNode(int idx);
int CFGDataList_GetNode(int idx, CFGInfo_T *node);
int CFGDataList_UpdateNode(CFGInfo_T *node, int idx);
int CFGDataList_GetNumber();


//mg_cfg data is not list
#define _FILE_OPERATE_
/*oscam.server
[reader]
label      = remote5
protocol   = newcamd
device     = 91.194.76.159,4000
key        = 0102030405060708091011121314
account    = 584gisky,332255
group = 1
*/
int read_oscaminfo(const char *file);
int write_oscaminfo(const char *file);



/*  mg_cfg
# network mode, use summ for several clients
#    00 no network (default)
#    01 newcamd netclient
#    02 radegast netclient
#    04 camd3 netclient
#    08 gbox netclient
#    32 cccam netclient
G: { 01 }*/
int mgcfg_readinfo(const char *file, const char *key,char *value, int size,
	const char *default_value, char eval_ch);
int mgcfg_writeinfo(const char *file, const char *key,
					const char *value, char eval_ch);


/*cccamd.list
C: server_address port username password
*/
int read_cccamdinfo(const char *file);
int write_cccamdinfo(const char *file);


/*newcamd.list
CWS_KEEPALIVE = 300
CWS_INCOMING_PORT = 21000
CWS = 192.168.1.186 15050 dummy dummy 01 02 03 04 05 06 07 08 09 10 11 12 13 14 wan
*/
int read_newcamdinfo(const char *file);
int write_newcamdinfo(const char *file);


/*cccam.cfg
C: 192.168.88.88 8888 account password
N: 192.168.88.88 8888 account password 01 02 03 04 05 06 07 08 09 10 11 12 13 14
*/
int read_cccamcfginfo(const char *file);
int write_cccamcfginfo(const char *file);


#ifdef __cplusplus
}; //end of extern "C" {
#endif

#endif //end of INI_FILE_H_

