#ifndef _SPARKID_H_
#define  _SPARKID_H_



#define SPARK_ID_LEN	32

void spark_get_sysinfo(char *name,char *value);
char* spark_get_stbid(void);
char* spark_get_chipid(void);
char* spark_get_macid(void);
char* spark_get_version(void);



#endif

