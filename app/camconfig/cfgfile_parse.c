
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "cfgfile_parse.h"



#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_FILE_SIZE 1024*16
#define LEFT_BRACE '['
#define RIGHT_BRACE ']'
#define COMMENT_CHAR '#'

static CFGInfo_T *g_pCFGDataListHead = NULL;


//success :return 1
//fail : return 0
static int load_file(const char *file, char *buf,int *file_size)
{
	FILE *in = NULL;
	int i=0;
	int iBigfile = 0;

	*file_size =0;

	assert(file !=NULL);
	assert(buf !=NULL);

	in = fopen(file,"rt");
	if( NULL == in) {
		printf("can not open file!\n");
		return -1;
	}

	buf[i]=fgetc(in);

	//load initialization file
	while( buf[i]!= (char)EOF) {
		i++;
		if( i >= MAX_FILE_SIZE) //file too big
		{
			printf("file too big!\n");
			iBigfile = 1;
			break;
		}
		buf[i]=fgetc(in);
	}
	fclose(in);
	if(iBigfile == 1)
	{
		buf[MAX_FILE_SIZE-1]='\0';
		*file_size = MAX_FILE_SIZE;

		return -1;
	}
	else
	{
		buf[i]='\0';
		*file_size = i;
		return 0;
	}
}

//is space or tab key
static int IsspaceOrTab(char c)
{
	return (' '==c || 0x09==c )? 1 : 0;
}


static int iscomma(char c)
{
	return (','==c)? 1 : 0;
}

static int isnewline(char c)
{
	return ('\n' == c ||  '\r' == c )? 1 : 0;
}
static int isend(char c)
{
	return '\0'==c? 1 : 0;
}
static int isleftbrace(char c)
{
	return LEFT_BRACE == c? 1 : 0;
}
static int isrightbrace(char c )
{
	return RIGHT_BRACE == c? 1 : 0;
}



#define _LIST_FUNCTION_
//oscam.server
void CFGDataList_Init()
{
	CFGInfo_T *pcur = g_pCFGDataListHead;
	CFGInfo_T *pnext = g_pCFGDataListHead;
	while(pcur != NULL)
	{
		pnext = pcur->next;
		free(pcur);
		pcur = pnext;
	}
	g_pCFGDataListHead = NULL;

}
void CFGDataList_Release()
{
	CFGInfo_T *pcur = g_pCFGDataListHead;
	CFGInfo_T *pnext = g_pCFGDataListHead;
	while(pcur != NULL)
	{
		pnext = pcur->next;
		free(pcur);
		pcur = pnext;
	}
	g_pCFGDataListHead = NULL;
}

//add node to tail
int CFGDataList_AddNode(CFGInfo_T *node)
{
	CFGInfo_T *pcur = g_pCFGDataListHead;
	CFGInfo_T *pnext = g_pCFGDataListHead;
	CFGInfo_T *pnode = NULL;

	pnode = (CFGInfo_T *)malloc(sizeof(CFGInfo_T));
	assert(pnode != NULL);
	memset(pnode, 0, sizeof(CFGInfo_T));
	YWLIB_Memcpy(pnode, node, sizeof(CFGInfo_T));

	if(g_pCFGDataListHead == NULL)
	{
		g_pCFGDataListHead = pnode;
		g_pCFGDataListHead->next = NULL;
	}
	else
	{
		do{
			pcur = pnext;
			pnext = pcur->next;
		}while(pnext != NULL);

		pcur->next = pnode;
		pnode->next = NULL;
	}

	return 0;
}




//delete by idx
int CFGDataList_DeleteNode(int idx)
{
	CFGInfo_T *pcur = g_pCFGDataListHead;
	CFGInfo_T *pPrev = g_pCFGDataListHead;
	int ii = 0;

	if(g_pCFGDataListHead == NULL)
	{
		printf("List is empty list\n");
		return 0;
	}

	if(idx == 0)
	{
		pcur = g_pCFGDataListHead->next;
		free(g_pCFGDataListHead);
		g_pCFGDataListHead = pcur;
	}
	else
	{
		while(1)
		{
			pPrev = pcur;
			pcur = pcur->next;
			if(pcur == NULL)
			{
				printf("list can not find %d node", idx);
				return -1;
			}
			ii++;
			if(ii == idx)
			{
				pPrev->next = pcur->next;
				free(pcur);
				pcur = NULL;
				break;
			}
		}
	}
	return 0;
}

//get node by index
int CFGDataList_GetNode(int idx, CFGInfo_T *node)
{
	CFGInfo_T *pcur = g_pCFGDataListHead;
	int ii = 0;

	if(g_pCFGDataListHead == NULL)
	{
		printf("List is empty list\n");
		return 0;
	}

	if(idx == 0)
	{
		YWLIB_Memcpy(node, pcur, sizeof(CFGInfo_T));
	}
	else
	{
		while(1)
		{
			pcur = pcur->next;
			if(pcur == NULL)
			{
				printf("list can not find %d node", idx);
				return -1;
			}
			ii++;
			if(ii == idx)
			{
				YWLIB_Memcpy(node, pcur, sizeof(CFGInfo_T));
				break;
			}
		}
	}
	return 0;

}

//update node data by indx
int CFGDataList_UpdateNode(CFGInfo_T *node, int idx)
{
	CFGInfo_T *pcur = g_pCFGDataListHead;
	int ii = 0;
	if(g_pCFGDataListHead == NULL)
	{
		printf("List is empty list\n");
		return 0;
	}

	if(idx == 0)
	{
		pcur = g_pCFGDataListHead;
	}
	else
	{
		while(1)
		{
			pcur = pcur->next;
			if(pcur == NULL)
			{
				printf("list can not find %d node", idx);
				return -1;
			}
			ii++;
			if(ii == idx)
			{
				break;
			}
		}
	}

//	YWLIB_Strncpy(pcur->section, node->section, sizeof(node->section));  //only for oscam
//	YWLIB_Strncpy(pcur->label, node->label, sizeof(node->label));        //only for oscam
	YWLIB_Strncpy(pcur->key, node->key, sizeof(node->key));
	YWLIB_Strncpy(pcur->servname, node->servname, sizeof(node->servname));
	YWLIB_Strncpy(pcur->serviceport, node->serviceport, sizeof(node->serviceport));
	YWLIB_Strncpy(pcur->serviceport_end, node->serviceport_end, sizeof(node->serviceport_end));
	YWLIB_Strncpy(pcur->username, node->username, sizeof(node->username));
	YWLIB_Strncpy(pcur->password, node->password, sizeof(node->password));
	YWLIB_Strncpy(pcur->deskey, node->deskey, sizeof(node->deskey));
	YWLIB_Strncpy(pcur->protocol, node->protocol, sizeof(node->protocol));

	return 0;
}

int CFGDataList_GetNumber()
{
	CFGInfo_T *pcur = g_pCFGDataListHead;
	int count = 0;

	if(g_pCFGDataListHead == NULL)
	{
		printf("List is empty list\n");
		return count;
	}

	count = 1;
	while(pcur != NULL)
	{
		pcur = pcur->next;
		if(pcur == NULL)
		{
			break;
		}
		count++;
	}
	return count;
}





#define _OSCAM_SERVER_FILE_
/*
*psectionstart is '['
*psectionend   before '[' or '\0'
*/
static int oscamdata2node(char *psectionstart, int istrlen, CFGInfo_T *node)
{
	char *p = psectionstart;
	int i = 0;
	int j = 0;
	int k = 0;
	int count = 0;
	int newline_start = 0;
	int newline_end = 0;


	//get section head
	while(isleftbrace(p[i]))
	{     //Skip over '['char
		i++;
	}
	j = i;
	while(!isrightbrace(p[j])) {
		j++;
	}   //now j is point ']'
	YWLIB_Strncpy(node->section, p+i, j-i);
	node->section[SECTION_LEN-1] = 0;

	//skip space after ']'
/*	j++;
	while(IsspaceOrTab(p[j])) {
	j++;
	}
*/
	i = j;    //now i is point to ']'

	//get element
	while(i < istrlen)
	{
		while( !isnewline(p[i])) {  //move i to line end
			i++;
		}
		while(isnewline(p[i])) {  //move i to new line start
			i++;
		}

		newline_start = i;

		if(COMMENT_CHAR != p[i])
		{
			while( !isnewline(p[i])) {  //move i to line end
				i++;
			}
			newline_end = i;    //newline_end point to line end

			j = newline_start;
			while(j < newline_end && p[j] != '=')
			{
				j++;
				if('=' == p[j])    //now j point to '='
				{
					k = j-1;
					//Skip over space char before '='
					while(IsspaceOrTab(p[k])) {
						k--;
					}
					k++;

					//printf("Find node's element: %s\n", p+newline_start);
					if(strncmp("label",p+newline_start,k-newline_start) == 0)
					{
						//Skip over space char after '='
						k=j+1;
						while(IsspaceOrTab(p[k])) {
							k++;
						}
						YWLIB_Strncpy(node->label, p+k, newline_end-k);
						node->label[LABEL_LEN-1] = 0;
					}
					else if(strncmp("protocol",p+newline_start,k-newline_start)==0)
					{
						//Skip over space char after '='
						k=j+1;
						while(IsspaceOrTab(p[k])) {
							k++;
						}
						YWLIB_Strncpy(node->protocol, p+k, newline_end-k);
						node->protocol[PROTOCOL_LEN-1] = 0;
					}
					else if(strncmp("s-encrypt",p+newline_start,k-newline_start)==0)
					{
						//Skip over space char after '='
						k=j+1;
						while(IsspaceOrTab(p[k])) {
							k++;
						}

						node->encrypt[0] = *(p+k);
						node->encrypt[1] = 0;
						if(node->encrypt[0] == '1')
							return -1;
					}
					else if(strncmp("device",p+newline_start,k-newline_start)==0)
					{
						count = 0;
						//Skip over space char after '='
						k=j+1;
						while(IsspaceOrTab(p[k])) {
							k++;
						}

						count = k;
						while(!iscomma(p[count])) {
							count++;
							}
						YWLIB_Strncpy(node->servname, p+k, (count-k));   //service name
						node->servname[SERVNAME_LEN-1] = 0;
						YWLIB_Strncpy(node->serviceport, p+(count+1), newline_end-(count+1)); //service port
						node->serviceport[SERVICEPORT_LEN-1] = 0;
					}
					else if(strncmp("key",p+newline_start,k-newline_start)==0)
					{
						//Skip over space char after '='
						k=j+1;
						while(IsspaceOrTab(p[k])) {
							k++;
						}
						YWLIB_Strncpy(node->deskey, p+k, newline_end-k);
						node->deskey[DESKEY_LEN-1] = 0;
					}
					else if(strncmp("account",p+newline_start,k-newline_start)==0)
					{
						count = 0;
						//Skip over space char after '='
						k=j+1;
						while(IsspaceOrTab(p[k])) {
							k++;
						}

						count = k;
						while(!iscomma(p[count])) {
							count++;
							}

						YWLIB_Strncpy(node->username, p+k, (count-k));   //user name
						node->username[USERNAME_LEN-1] = 0;
						YWLIB_Strncpy(node->password, p+(count+1), newline_end-(count+1)); //password
						node->password[PASSWORD_LEN-1] = 0;

					}
					else if(strncmp("group",p+newline_start,k-newline_start)==0)
					{
						//Skip over space char after '='
						k=j+1;
						while(IsspaceOrTab(p[k])) {
							k++;
						}
						YWLIB_Strncpy(node->group, p+k, newline_end-k);
						node->group[GROUP_LEN-1] = 0;
					}

					else
					{
						printf("no useful element!!\n");
					}
				}
			}
		}
		else
		{
			i++;
		}
	}

	return 0;
}



static int oscamdata2list(char *buf)
{
	char *p = buf;
	int i=0;
	CFGInfo_T node;
	int ret = 0;

	assert(buf!=NULL);


	while(!isend(p[i]))
	{
		//find section start '['
		if( ( 0==i ||  isnewline(p[i-1]) ) && isleftbrace(p[i]) )
		{
			int section_start = i;
			//find next '[' or the end of file
			do {
				i++;
			} while( !isleftbrace(p[i]) && !isend(p[i]));

			memset(&node, 0, sizeof(CFGInfo_T));
			if(oscamdata2node((char *)(p+section_start), (i-section_start), &node) != 0)
			{
				ret = -1;
				break;
			}
			CFGDataList_AddNode(&node);
			printf("read file add node serverlabel: %s\n", node.label);
		}
		else
		{
			i++;
		}
	}
	return ret;
}




static int node2oscamdata(CFGInfo_T *node, char *str)
{
	int istrlen;

	YWLIB_Sprintf(str, (const char *)"[reader]\n");

	istrlen = YWLIB_Strlen(str);
	YWLIB_Sprintf(str+istrlen, (const char *)"label = %s\n",
		node->label);

	istrlen = YWLIB_Strlen(str);
	YWLIB_Sprintf(str+istrlen, (const char *)"protocol = %s\n",
		node->protocol);


	istrlen = YWLIB_Strlen(str);
	YWLIB_Sprintf(str+istrlen, (const char *)"device = %s,%s\n",
		node->servname, node->serviceport);

	if(YWLIB_Strcmp(node->protocol, "newcamd") == 0)
	{
		istrlen = YWLIB_Strlen(str);
		YWLIB_Sprintf(str+istrlen, (const char *)"key = %s\n", node->deskey);
	}

	istrlen = YWLIB_Strlen(str);
	YWLIB_Sprintf(str+istrlen, (const char *)"account = %s,%s\n",
		node->username, node->password);

	istrlen = YWLIB_Strlen(str);
	YWLIB_Sprintf(str+istrlen, (const char *)"group = %s\n",
		node->group);


	return 0;
}


static int list2oscamdata(char *buf, int *datalen)
{
	char *p = buf;
	int i=0;
	int nodenum = 0;
	int j = 0;
	CFGInfo_T node;
	char str[1024*2];

	assert(buf!=NULL);


	while(!isend(p[i]))
	{
		//find the line witch isn't start by '#'
		if( ( 0==i ||  isnewline(p[i-1]) ) && (p[i] != COMMENT_CHAR) &&  (!isnewline(p[i])) )
		{
			int istrlen = 0;

			nodenum = CFGDataList_GetNumber();

			for(j=0; j<nodenum; j++)
			{
				memset(&node, 0, sizeof(CFGInfo_T));
				memset(str, 0, sizeof(str));

				CFGDataList_GetNode(j, &node);
//				printf("save file section:%s, label:%s, protocol:%s, servername:%s,serviceport:%s, usrname:%s, pswd:%s, deskey:%s\n",
//						node.section, node.label, node.protocol, node.servname, node.serviceport,node.username, node.password, node.deskey);
				node2oscamdata(&node, str);

				YWLIB_Strcpy((char *)(p+i), str);
				istrlen = (int)strlen(str);
				i = i+istrlen;
			}

			*datalen = i;
			break;
		}
		else
		{
			i++;
		}
	}
	return 0;
}

int read_oscaminfo(const char *file)
{
	char buf[MAX_FILE_SIZE]={0};
	int file_size;

	if(0 != load_file(file,buf,&file_size))
	{
		printf("load oscam file failed\n");
		return -1;
	}
	if(0 != oscamdata2list((char*)buf))
	{
		printf("parse oscam file fail\n");
		return -1;
	}

	return 0;
}


int write_oscaminfo(const char *file)
{
	char buf[MAX_FILE_SIZE]={0};
	int file_size;
	FILE *out = NULL;
	int datalen = 0;

	if(0 != load_file(file,buf,&file_size))
	{
		printf("load oscam file failed\n");
		return -1;
	}
	if(0 != list2oscamdata(buf, &datalen))
	{
		printf("write list data to oscam bufer fail\n");
		return -1;
	}
	YWLIB_Memset(&buf[datalen], 0, MAX_FILE_SIZE-datalen);

	out = fopen(file,"wt");
	if(NULL == out)
	{
		printf("can not open oscam file !\n");
		return -1;
	}

	if(-1 == fputs(buf,out) )
	{
		printf("write oscam file error!\n");
		fclose(out);
		return -1;
	}

	fclose(out);
	return 0;
}




#define _MG_CFG_FILE_


static int parse_extra_file(const char *key, const char *buf,
								int *key_s,int *key_e, int *value_s, int *value_e, char eval_ch)
{
	const char *p = buf;
	int i = 0;

	assert(buf!=NULL);
	assert(key != NULL && YWLIB_Strlen(key));

	*key_e = *key_s = *value_s = *value_e = -1;

	while( !isend(p[i]) ) {
		//find the section
		if(0==i || isnewline(p[i]))
		{
			if(isnewline(p[i]))
				i++;

			while( !isnewline(p[i])
			&& !isend(p[i]) )
			{
				int newline_start=0;
				int j=0;

				//get a new line
				newline_start = i;

				//move i to line end
				while( !isnewline(p[i]) &&  !isend(p[i]) ) {
					i++;
				}

				//now i  is equal to end of the line
				j = newline_start;

				if(COMMENT_CHAR != p[j]) //skip over comment
				{
					while(j < i && p[j] != eval_ch)
					{
						j++;
						if(eval_ch == p[j])
						{
							int k = j-1;
							//Skip over space char before eval_ch
							while(IsspaceOrTab(p[k])) {
								k--;
							}
							k++;

							if(strncmp(key,p+newline_start,k-newline_start)==0)
							{
								//find the key
								*key_s = newline_start;
								*key_e = k-1;

								//Skip over space char after eval_ch '='
								k=j+1;
								while(IsspaceOrTab(p[k])) {
									k++;
								}

								//only for "G:"
								while(!IsspaceOrTab(p[k])) {   //skip '{'
									k++;
								}
								while(IsspaceOrTab(p[k])) {   //skip ' '
									k++;
								}

								while(!IsspaceOrTab(p[i])) {   //skip '}'
									i--;
								}

								*value_s = k;
								*value_e = i;

								return 1;
							}
						}
					}
				}

				i++;
			}
		}
		else
		{
			i++;
		}
	}
	return 0;
}
/**
*@brief read string in initialization file\n
* retrieves a string from the specified section in an initialization file
*@param key [in] name of the key pairs to value
*@param value [in] pointer to the buffer that receives the retrieved string
*@param size [in] size of value buffer
*@param default_value [in] defualt value of result
*@param file [in] path of the initialization file
*@eval_ch[in] the char between key and value
*@return 1 : read success; \n 0 : read fail
*/
static int read_extrafile_string(const char *key,char *value,
		 int size, const char *default_value, const char *file, char eval_ch)
{
	char buf[MAX_FILE_SIZE]={0};
	int file_size;
	int key_s,key_e, value_s, value_e;

	//check parameters
	assert(key != NULL && YWLIB_Strlen(key));
	assert(value != NULL);
	assert(size > 0);
	assert(file !=NULL &&YWLIB_Strlen(file));

	if(0 != load_file(file,buf,&file_size))
	{
		if(default_value!=NULL)
		{
			strncpy(value,default_value, size);
		}
		return -1;
	}

	if(!parse_extra_file(key,buf,&key_s,&key_e,&value_s,&value_e, eval_ch))
	{
		if(default_value!=NULL)
		{
			strncpy(value,default_value, size);
		}
		return -1; //not find the key
	}
	else
	{
		int cpcount = value_e -value_s;

		if( size-1 < cpcount)
		{
			cpcount =  size-1;
		}

		memset(value, 0, size);
		memcpy(value,buf+value_s, cpcount );
		value[cpcount] = '\0';

		return 0;
	}
}
/**
 * @brief write a profile string to a extra file
 * @param key [in] name of the key pairs to value, can't be NULL and empty string
 * @param value [in] profile string value
 * @param file [in] path of ini file
 * @return 1 : success\n 0 : failure
 */
static int write_extrafile_string(const char *key,
					const char *value, const char *file, char eval_ch)
{
	char buf[MAX_FILE_SIZE]={0};
	char w_buf[MAX_FILE_SIZE]={0};
	int key_s,key_e, value_s, value_e;
	int value_len = (int)YWLIB_Strlen(value);
	int file_size;
	FILE *out;

	//check parameters
	assert(key != NULL && YWLIB_Strlen(key));
	assert(value != NULL);
	assert(file !=NULL &&YWLIB_Strlen(file));

	if(0 != load_file(file,buf,&file_size))
	{
		return -1;
	}
	else
	{
		parse_extra_file(key,buf,&key_s,&key_e,&value_s,&value_e, eval_ch);
	}

	if(-1 == key_s)
	{
		//not find the key, then add the new key & value at end of the file
		memcpy(w_buf,buf,file_size);
		sprintf(w_buf+file_size,"\n%s=%s\n",key,value);
	}
	else
	{
		//update value with new value
		memcpy(w_buf,buf,value_s);
		memcpy(w_buf+value_s,value, value_len);
		memcpy(w_buf+value_s+value_len, buf+value_e, file_size - value_e);
	}

	out = fopen(file,"w");
	if(NULL == out)
	{
		return -1;
	}

	if(-1 == fputs(w_buf,out) )
	{
		fclose(out);
		return -1;
	}

	fclose(out);
	return 0;
}

/**/
int mgcfg_readinfo(const char *file, const char *key,char *value,
		 int size, const char *default_value, char eval_ch)
{
	return read_extrafile_string(key, value, size, default_value, file, eval_ch);
}
int mgcfg_writeinfo(const char *file, const char *key,
					const char *value, char eval_ch)
{
	return write_extrafile_string(key, value, file, eval_ch);

}


#define _CCCAMD_LIST


static int node2cccamddata(CFGInfo_T *node, char *str)
{
	YWLIB_Sprintf(str, (const char *)"%s: %s %s %s %s\n",
		node->key, node->servname, node->serviceport, node->username, node->password);
}
static int list2cccamddata(char *buf, int *datalen)
{
	char *p = buf;
	int i=0;
	int nodenum = 0;
	int j = 0;
	CFGInfo_T node;
	char str[1024*2];

	assert(buf!=NULL);

	while(!isend(p[i]))
	{
		//find the line witch isn't start by '#'
		if( ( 0==i ||  isnewline(p[i-1]) ) && (p[i] != COMMENT_CHAR) &&  (!isnewline(p[i])) )
		{
			int istrlen = 0;

			nodenum = CFGDataList_GetNumber();

			for(j=0; j<nodenum; j++)
			{
				memset(&node, 0, sizeof(CFGInfo_T));
				memset(str, 0, sizeof(str));

				CFGDataList_GetNode(j, &node);
				node2cccamddata(&node, str);

				YWLIB_Strcpy((char *)p+i, str);
				istrlen = YWLIB_Strlen(str);
				i = i+istrlen;
			}

			*datalen = i;
		}
		else
		{
			i++;
		}
	}

	return 0;
}


static int cccamddata2node(char *pline_start, int istrlen, CFGInfo_T *node)
{
	char *p = pline_start;
	int i = 0;
	int j = 0;


	if(p[i] == 'C'/* || p[i] == 'N' */)
	{
		YWLIB_Strncpy(node->key, p, 1);
	}
	else
	{
		printf("not valided elepment: %s \n", (p+i));
		return -1;
	}

	i++;
	while(IsspaceOrTab(p[i])&&i<istrlen) {
		i++;
	}
	if(i>=istrlen)
	{
		printf("this elepment has no data info %s\n", (p+i));
		return -1;
	}
	if(p[i] != ':')
	{
		printf("not valided elepment: %s \n", (p+i));
		return -1;
	}

	//skip space before server address
	i++;
	while(IsspaceOrTab(p[i])&&i<istrlen) {
		i++;
	}
	if(i>=istrlen)
	{
		printf("this elepment has no servname info %s\n", node->key);
		return -1;
	}

	//now i point to server address start
	j = i;
	while(!IsspaceOrTab(p[i])&&i<istrlen) {
		i++;
	}
	YWLIB_Strncpy(node->servname, p+j, i-j);
	node->servname[SERVNAME_LEN-1] = 0;
	if(i>=istrlen)
	{
		printf("this elepment has no port info %s\n", node->key);
		return -1;
	}

	//now i point to port start
	i++;
	j = i;
	while(!IsspaceOrTab(p[i])&&i<istrlen) {
		i++;
	}
	YWLIB_Strncpy(node->serviceport, p+j, i-j);
	node->serviceport[SERVICEPORT_LEN-1] = 0;
	if(i>=istrlen)
	{
		printf("this elepment has no user name info %s\n", node->key);
		return -1;
	}

	//now i point to user name start
	i++;
	j = i;
	while(!IsspaceOrTab(p[i])&&i<istrlen) {
		i++;
	}
	YWLIB_Strncpy(node->username, p+j, i-j);
	node->username[USERNAME_LEN-1] = 0;
	if(i>=istrlen)
	{
		printf("this elepment has no password info %s\n", node->key);
		return -1;
	}

	//now i point to password start
	i++;
	j = i;
	while(!IsspaceOrTab(p[i])&&i<istrlen) {
		i++;
	}
	YWLIB_Strncpy(node->password, p+j, i-j);
	node->password[PASSWORD_LEN-1] = 0;

	return 0;
}


static int cccamddata2list(char *buf)
{
	char *p = buf;
	int i=0;
	CFGInfo_T node;

	assert(buf!=NULL);


	while(!isend(p[i]))
	{
		//find a line start not by '#'
		if( ( 0==i ||  isnewline(p[i-1]) ) && (COMMENT_CHAR != p[i]) &&  (!isnewline(p[i])))
		{
			int line_start = i;

			//find the line end or the end of file
			do {
				i++;
			} while( !isnewline(p[i]) && !isend(p[i]));

			memset(&node, 0, sizeof(CFGInfo_T));
			cccamddata2node((char *)(p+line_start), (i-line_start), &node);
			CFGDataList_AddNode(&node);
		}
		else
		{
			i++;
		}
	}
	return 0;
}


int read_cccamdinfo(const char *file)
{
	char buf[MAX_FILE_SIZE]={0};
	int file_size;

	if(0 != load_file(file,buf,&file_size))
	{
		printf("load cccamd file failed\n");
		return -1;
	}
	if(0 != cccamddata2list((char*)buf))
	{
		printf("parse cccamd file fail\n");
		return -1;
	}

	return 0;
}
int write_cccamdinfo(const char *file)
{
	char buf[MAX_FILE_SIZE]={0};
	int file_size;
	FILE *out = NULL;
	int datalen = 0;

	if(0 != load_file(file,buf,&file_size))
	{
		printf("load cccamd file failed\n");
		return -1;
	}
	if(-1 == list2cccamddata((char *)buf, &datalen))
	{
		printf("write list data to cccamd bufer fail\n");
		return -1;
	}
	YWLIB_Memset(&buf[datalen], 0, MAX_FILE_SIZE-datalen);
	out = fopen(file,"wt");
	if(NULL == out)
	{
		printf("can not open cccamd file !\n");
		return -1;
	}

	if(-1 == fputs(buf,out) )
	{
		printf("write cccamd file !\n");
		fclose(out);
		return -1;
	}

	fclose(out);
	return 0;
}



#define _NEW_CAMD_LIST_

static int isnewcamddatastart(char *plinestart)
{
/*	if((plinestart[0] == 'C' && plinestart[1] == 'W' && plinestart[2] == 'S' &&
		plinestart[3] == ' ' && plinestart[4] == '=') ||
		(plinestart[0] == 'C' && plinestart[1] == 'W' && plinestart[2] == 'S' &&
		plinestart[3] == '_' && plinestart[4] == 'M' && plinestart[5] == 'U'
		 && plinestart[6] == 'L' && plinestart[7] == 'T' && plinestart[8] == 'I'
		  && plinestart[9] == 'P' && plinestart[10] == 'L' && plinestart[11] == 'E'))*/
	if((strncmp(plinestart, "CWS =", 5) == 0) || (strncmp(plinestart, "CWS_MULTIPLE", 12) == 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


static int node2newcamddata(CFGInfo_T *node, char *str)
{
	if(strcmp(node->key, "CWS_MULTIPLE") == 0)
	{
	//	printf("sav a  node key:%s, serviceport_end:%s\n", node->key, node->serviceport_end);
		
		YWLIB_Sprintf(str, (const char *)"%s = %s %s:%s %s %s %s\n",
			node->key, node->servname, node->serviceport, node->serviceport_end, node->username, node->password,node->deskey);
	}
	else
	{
		YWLIB_Sprintf(str, (const char *)"%s = %s %s %s %s %s\n",
		node->key, node->servname, node->serviceport, node->username, node->password,node->deskey);
	}
}


static int list2newcamddata(char *buf, int *datalen)
{
	char *p = buf;
	int i=0;
	int nodenum = 0;
	int j = 0;
	CFGInfo_T node;
	char str[1024*2];

	assert(buf!=NULL);

	while(!isend(p[i]))
	{
		//find the line witch isn't start by '#' and start by "CWS ="
		if( ( 0==i ||  isnewline(p[i-1]) ) && (p[i] != COMMENT_CHAR) &&
			(!isnewline(p[i])) && (isnewcamddatastart((char *)(p+i)) == 1) )
		{
			int istrlen = 0;

			nodenum = CFGDataList_GetNumber();

			for(j=0; j<nodenum; j++)
			{
				memset(&node, 0, sizeof(CFGInfo_T));
				memset(str, 0, sizeof(str));

				CFGDataList_GetNode(j, &node);
			//	printf("sav a  node key:%s\n", node.key);
				node2newcamddata(&node, str);

				YWLIB_Strcpy((char *)(p+i), str);
				istrlen = YWLIB_Strlen(str);
				i = i+istrlen;
			}

			*datalen = i;
		}
		else
		{
			i++;
		}
	}

	return 0;
}


static int  newcamddata2node(char *pline_start, int istrlen, CFGInfo_T *node)
{
	char *p = pline_start;
	int i = 0;
	int j = 0;
	char infotmp[256];
	char *pstrtmp = NULL;

	//get key = "CWS"
	j = i;
	while(!IsspaceOrTab(p[i]) && i<istrlen) {
		i++;
	}
	YWLIB_Strncpy(node->key, p+j, i-j);
	node->key[KEY_LEN-1] = 0;
	if(i>=istrlen)
	{
		printf("this elepment has no data info %s\n", (p+i));
		return -1;
	}

	//skip " = "
	i = i+3;
	while(IsspaceOrTab(p[i]) && i<istrlen) {
		i++;
	}

	//get server name
	j=i;
	while(!IsspaceOrTab(p[i]) && i<istrlen) {
		i++;
	}
	YWLIB_Strncpy(node->servname, p+j, i-j);
	node->servname[SERVNAME_LEN-1] = 0;
	if(i>=istrlen)
	{
		printf("this elepment has no servname info %s\n", node->key);
		return -1;
	}

	//now i point to service port
	i++;
	j = i;
	while(!IsspaceOrTab(p[i]) && i<istrlen) {
		i++;
	}
	if(strcmp(node->key, "CWS_MULTIPLE") == 0)
	{
		YWLIB_Memset(infotmp, 0, sizeof(infotmp));
		YWLIB_Strncpy(infotmp, p+j, i-j);
		pstrtmp = strstr(infotmp, ":");
		*pstrtmp = 0;
		pstrtmp++;
		YWLIB_Strcpy(node->serviceport, infotmp);
		YWLIB_Strcpy(node->serviceport_end, pstrtmp);
		node->serviceport[SERVICEPORT_LEN-1] = 0;
		node->serviceport_end[SERVICEPORT_LEN-1] = 0;
	}
	else
	{
		YWLIB_Strncpy(node->serviceport, p+j, i-j);
		node->serviceport[SERVICEPORT_LEN-1] = 0;
	}
	if(i>=istrlen)
	{
		printf("this elepment has no port info %s\n", node->key);
		return -1;
	}

	//now i point to user name start
	i++;
	j = i;
	while(!IsspaceOrTab(p[i]) && i<istrlen) {
		i++;
	}
	YWLIB_Strncpy(node->username, p+j, i-j);
	node->username[USERNAME_LEN-1] = 0;
	if(i>=istrlen)
	{
		printf("this elepment has no username info %s\n", node->key);
		return -1;
	}

	//now i point to password start
	i++;
	j = i;
	while(!IsspaceOrTab(p[i]) && i<istrlen) {
		i++;
	}
	YWLIB_Strncpy(node->password, p+j, i-j);
	node->password[PASSWORD_LEN-1] = 0;
	if(i>=istrlen)
	{
		printf("this elepment has no password info %s\n", node->key);
		return -1;
	}

	i++;  //now i point deskey start
	j = i;
	i = istrlen;
	YWLIB_Strncpy(node->deskey, p+j, i-j);
	node->deskey[41] = 0;
	//istrlen = YWLIB_Strlen(node->deskey);

	//label
/*	if(i+41 <= istrlen)
	{
		i = i+41;
		YWLIB_Strncpy(node->deskey, p+j, i-j);
	}
	else
	{
		printf("this elepment has no deskey info: %s\n", node->key);
		return -1;
	}*/

	/*
	while(i<istrlen) {
		i++;
	}
	while(!IsspaceOrTab(p[i])) {
		i--;
	}*/

	return 0;
}

static int  newcamddata2list(char *buf)
{
	char *p = buf;
	int i=0;
	CFGInfo_T node;

	assert(buf!=NULL);


	while(!isend(p[i]))
	{
		//find a line start not by '#' and start by "CWS ="
		if( ( 0==i ||  isnewline(p[i-1]) ) && (COMMENT_CHAR != p[i]) &&
			(!isnewline(p[i])) && (isnewcamddatastart((char *)(p+i)) == 1) )
		{
			int line_start = i;

			//find the line end or the end of file
			do {
				i++;
			} while( !isnewline(p[i]) && !isend(p[i]));

			memset(&node, 0, sizeof(CFGInfo_T));
			newcamddata2node((char *)(p+line_start), (i-line_start), &node);
			CFGDataList_AddNode(&node);
			printf("get a new node key:%s\n",node.key);
		}
		else
		{
			i++;
		}
	}
	return 0;

}

int read_newcamdinfo(const char *file)
{
	char buf[MAX_FILE_SIZE]={0};
	int file_size;

	if(0 != load_file(file,buf,&file_size))
	{
		printf("load newcamd file failed\n");
		return -1;
	}
	if(0 != newcamddata2list((char*)buf))
	{
		printf("parse newcamd file fail\n");
		return -1;
	}

	return 0;
}
int write_newcamdinfo(const char *file)
{
	char buf[MAX_FILE_SIZE]={0};
	int file_size;
	FILE *out = NULL;
	int datalen = 0;

	if(0 != load_file(file,buf,&file_size))
	{
		printf("load newcamd file failed\n");
		return -1;
	}
	if(-1 == list2newcamddata((char *)buf, &datalen))
	{
		printf("write list data to newcamd bufer fail\n");
		return -1;
	}
	YWLIB_Memset(&buf[datalen], 0, MAX_FILE_SIZE-datalen);
	out = fopen(file,"wt");
	if(NULL == out)
	{
		printf("can not open newcamd file !\n");
		return -1;
	}

	if(-1 == fputs(buf,out) )
	{
		printf("write newcamd file !\n");
		fclose(out);
		return -1;
	}

	fclose(out);
	return 0;
}

#define _CCCAM_CFG_FILE_

static int iscccamcfgdatastart(char *plinestart)
{
	if((plinestart[0] == 'C' || plinestart[0] == 'N') && plinestart[1] == ':' )
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

static int node2cccamcfgdata(CFGInfo_T *node, char *str)
{

	if(YWLIB_Strcmp(node->key, "N") == 0)
	{
		YWLIB_Sprintf(str, (const char *)"%s: %s %s %s %s %s\n",
			node->key, node->servname, node->serviceport, node->username, node->password,node->deskey);
	}
	else
	{
		YWLIB_Sprintf(str, (const char *)"%s: %s %s %s %s\n",
			node->key, node->servname, node->serviceport, node->username, node->password);
	}
}

static int list2cccamcfgdata(char *buf, int *datalen)
{
	char *p = buf;
	int i=0;
	int nodenum = 0;
	int j = 0;
	CFGInfo_T node;
	char str[1024*2];

	assert(buf!=NULL);

	while(!isend(p[i]))
	{
		//find the line witch isn't start by '#' and start by "C:"or"N:"
		if( ( 0==i ||  isnewline(p[i-1]) ) && (p[i] != COMMENT_CHAR) &&
			(!isnewline(p[i])) && (iscccamcfgdatastart((char *)(p+i)) == 1) )
		{
			int istrlen = 0;

			nodenum = CFGDataList_GetNumber();

			for(j=0; j<nodenum; j++)
			{
				memset(&node, 0, sizeof(CFGInfo_T));
				memset(str, 0, sizeof(str));

				CFGDataList_GetNode(j, &node);
				node2cccamcfgdata(&node, str);

				YWLIB_Strcpy((char *)(p+i), str);
				istrlen = YWLIB_Strlen(str);
				i = i+istrlen;
			}

			*datalen = i;
		}
		else
		{
			i++;
		}
	}

	return 0;
}

static int cccamcfgdata2node(char *pline_start, int istrlen, CFGInfo_T *node)
{
	char *p = pline_start;
	int i = 0;
	int j = 0;


	if(p[i] == 'C' || p[i] == 'N' )
	{
		YWLIB_Strncpy(node->key, p, 1);
	}
	else
	{
		printf("not valided elepment: %s \n", (p+i));
		return -1;
	}

	i++;
	while(IsspaceOrTab(p[i])&&i<istrlen) {
		i++;
	}
	if(i>=istrlen)
	{
		printf("this elepment has no data info %s\n", (p+i));
		return -1;
	}
	if(p[i] != ':')
	{
		printf("not valided elepment: %s \n", (p+i));
		return -1;
	}

	//skip space before server address
	i++;
	while(IsspaceOrTab(p[i])&&i<istrlen) {
		i++;
	}
	if(i>=istrlen)
	{
		printf("this elepment has no servname info %s\n", node->key);
		return -1;
	}

	//now i point to server address start
	j = i;
	while(!IsspaceOrTab(p[i]) && i<istrlen) {
		i++;
	}
	YWLIB_Strncpy(node->servname, p+j, i-j);
	node->servname[SERVNAME_LEN-1] = 0;
	if(i>=istrlen)
	{
		printf("this elepment has no port info %s\n", node->key);
		return -1;
	}

	//now i point to port start
	i++;
	j = i;
	while(!IsspaceOrTab(p[i])&&i<istrlen) {
		i++;
	}
	YWLIB_Strncpy(node->serviceport, p+j, i-j);
	node->serviceport[SERVICEPORT_LEN-1] = 0;
	if(i>=istrlen)
	{
		printf("this elepment has no user name info %s\n", node->key);
		return -1;
	}

	//now i point to user name start
	i++;
	j = i;
	while(!IsspaceOrTab(p[i])&&i<istrlen) {
		i++;
	}
	YWLIB_Strncpy(node->username, p+j, i-j);
	node->username[USERNAME_LEN-1] = 0;
	if(i>=istrlen)
	{
		printf("this elepment has no password info %s\n", node->key);
		return -1;
	}

	//now i point to password start
	i++;
	j = i;
	while(!IsspaceOrTab(p[i])&&i<istrlen) {
		i++;
	}
	YWLIB_Strncpy(node->password, p+j, i-j);
	node->password[PASSWORD_LEN-1] = 0;

	if(YWLIB_Strcmp(node->key, "C") == 0 || (i>=istrlen))
	{
		//printf("get an cccamd node it,s key is : %s\n", node->key);
		return 0;
	}
	else
	{
		//deskey
		i++;  //now i point deskey start
		j = i;
		i = istrlen;
		YWLIB_Strncpy(node->deskey, p+j, i-j);
		node->deskey[DESKEY_LEN-1] = 0;
	}

	return 0;
}

static int cccamcfgdata2list(char *buf)
{
	char *p = buf;
	int i=0;
	CFGInfo_T node;

	assert(buf!=NULL);


	while(!isend(p[i]))
	{
		//find a line start not by '#'
		if( ( 0==i ||  isnewline(p[i-1]) )&&  (!isnewline(p[i])) &&
			(COMMENT_CHAR != p[i]) && (1 == iscccamcfgdatastart((char *)(p+i))))
		{
			int line_start = i;

			//find the line end or the end of file
			do {
				i++;
			} while( !isnewline(p[i]) && !isend(p[i]));

			memset(&node, 0, sizeof(CFGInfo_T));
			cccamcfgdata2node((char *)(p+line_start), (i-line_start), &node);
			CFGDataList_AddNode(&node);
		}
		else
		{
			i++;
		}
	}
	return 0;
}

int read_cccamcfginfo(const char *file)
{
	char buf[MAX_FILE_SIZE]={0};
	int file_size;

	if(0 != load_file(file,buf,&file_size))
	{
		printf("load cccamcfg file failed\n");
		return -1;
	}
	if(0 != cccamcfgdata2list((char*)buf))
	{
		printf("parse cccamcfg file fail\n");
		return -1;
	}

	return 0;
}

int write_cccamcfginfo(const char *file)
{
	char buf[MAX_FILE_SIZE]={0};
	int file_size;
	FILE *out = NULL;
	int datalen = 0;

	if(0 != load_file(file,buf,&file_size))
	{
		printf("load cccamcfg file failed\n");
		return -1;
	}
	if(-1 == list2cccamcfgdata((char *)buf, &datalen))
	{
		printf("write list data to cccamcfg bufer fail\n");
		return -1;
	}
	YWLIB_Memset(&buf[datalen], 0, MAX_FILE_SIZE-datalen);
	out = fopen(file,"wt");
	if(NULL == out)
	{
		printf("can not open cccamcfg file !\n");
		return -1;
	}

	if(-1 == fputs(buf,out) )
	{
		printf("write cccamcfg file !\n");
		fclose(out);
		return -1;
	}

	fclose(out);
	return 0;
}


#ifdef __cplusplus
}; //end of extern "C" {
#endif
