#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#ifndef TYPEDEF_H
#define TYPEDEF_H

typedef enum _Ret
{
    RET_OK,
    RET_OOM,
    RET_STOP,
    RET_INVALID_PARAMS,
    RET_FAIL
}Ret;


#ifdef __cplusplus
#define DECLS_BEGIN extern "C" {
#define DECLS_END   }
#else
#define DECLS_BEGIN
#define DECLS_END
#endif/*__cplusplus*/

#ifndef NULL
#define NULL            ((void *)0)
#endif

#ifndef BOOL
#define BOOL unsigned char
#endif
#ifndef TRUE
#define TRUE (BOOL) 1
#endif
#ifndef FALSE
#define FALSE (BOOL) 0
#endif

#define return_if_fail(p) if(!(p)) \
	{printf("%s:%d Warning: "#p" failed.\n", \
		__func__, __LINE__); return;}
#define return_val_if_fail(p, ret) if(!(p)) \
	{printf("%s:%d Warning: "#p" failed.\n",\
	__func__, __LINE__); return (ret);}

#define debug(x...)   do \
    { \
        printf("\e[31;4m[*info*]\e[m[%s:%d]", __FILE__, __LINE__); \
        printf(x); \
    }while(0)

#define SAFE_FREE(p) if(p != NULL) {free(p); p = NULL;}

#endif/*TYPEDEF_H*/

