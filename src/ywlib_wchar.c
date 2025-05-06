#include <stdio.h>
#include <string.h>
#include <stdarg.h>


#include "ywdefs.h"
#include "ywos.h"
#include "ywlib.h"

#ifdef USE_LINUX
#include<netinet/in.h>
#include<arpa/inet.h> 
#endif

#define YWLIB_ASSERT(x)

#define YWLIB_SWPRINTF_ENFLOAT 1
#if YWLIB_SWPRINTF_ENFLOAT
#define YWLIB_SWPRINTF_BUFSIZE 64
#else
#define YWLIB_SWPRINTF_BUFSIZE 32
#endif

/**********************************************************************/
//    函数说明:    与menset()相似，但以YWLIB_WChar_T为单位
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
void *YWLIB_Memwset(void *wstr,YWLIB_WChar_T wchr,U32 n)
{
    YWLIB_WChar_T *ptmp=(YWLIB_WChar_T *)wstr;
    YWLIB_ASSERT(wstr!=NULL);
    while(n--)
    {
        *ptmp++=wchr;
    }
    return wstr;
}

/**********************************************************************/
//    函数说明:    与strlen()相似，返回宽字符串字符个数
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
S32 YWLIB_Wstrlen(const YWLIB_WChar_T *wstr)
{
    S32 lenth=0;
    YWLIB_ASSERT(wstr!=NULL);
    while(*wstr++)
    {
        lenth++;
    }
    return lenth;
}

/**********************************************************************/
//    函数说明:    与strcpy相似
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
YWLIB_WChar_T *YWLIB_Wstrcpy(YWLIB_WChar_T * YWLIB_RESTRICT wstrdes,const YWLIB_WChar_T * YWLIB_RESTRICT wstrsrc)
{
    YWLIB_WChar_T *tmp=wstrdes;
    YWLIB_ASSERT(wstrdes!=NULL && wstrsrc!=NULL);
    while((*wstrdes++=*wstrsrc++)||0)
    {
        ;
    }
    return tmp;
}

/**********************************************************************/
//    函数说明:    与strncpy()相似
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
YWLIB_WChar_T *YWLIB_Wstrncpy(YWLIB_WChar_T * YWLIB_RESTRICT wstrdes,const YWLIB_WChar_T * YWLIB_RESTRICT wstrsrc,U32 n)
{
    YWLIB_WChar_T *tmp=wstrdes;
    YWLIB_ASSERT(wstrdes!=NULL && wstrsrc!=NULL);
    if(!n)
    {
        return tmp;
    }
    while((*wstrdes++=*wstrsrc++) && --n)
    {
        ;
    }
    while(n-->1)
    {
        *wstrdes++=0;
    }
    return tmp;
}

/**********************************************************************/
//    函数说明:    与menchr()相似，在内存段中查找宽字符
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
void *YWLIB_Memwchr(const void *wstr,YWLIB_WChar_T wchr,U32 n)
{
    YWLIB_WChar_T *ptmp=(YWLIB_WChar_T *)wstr;
    YWLIB_ASSERT(wstr != NULL);
    while(n--)
    {
        if(wchr==*ptmp++)
        {
            return --ptmp;
        }
    }
    return NULL;
}

/**********************************************************************/
//    函数说明:    与strcat()相似，把宽字符串wstrsrc接到wstrdes后面
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
YWLIB_WChar_T *YWLIB_Wstrcat(YWLIB_WChar_T * YWLIB_RESTRICT wstrdes,const YWLIB_WChar_T * YWLIB_RESTRICT wstrsrc)
{
    YWLIB_WChar_T *tmp=wstrdes;
    YWLIB_ASSERT(wstrdes!=NULL && wstrsrc!=NULL);
    while(*wstrdes++)
    {
        ;
    }
    wstrdes--;
    while((*wstrdes++=*wstrsrc++)||0)
    {
        ;
    }
    return tmp;
}

/**********************************************************************/
//    函数说明:    与strncat()相似，把wstrstrc前n个字符接到wstrdes内部
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
YWLIB_WChar_T *YWLIB_Wstrncat(YWLIB_WChar_T * YWLIB_RESTRICT wstrdes,const YWLIB_WChar_T * YWLIB_RESTRICT wstrsrc,U32 n)
{
    YWLIB_WChar_T *tmp=wstrdes;
    YWLIB_ASSERT(wstrdes!=NULL && wstrsrc!=NULL);
    if(!n)
    {
        return tmp;
    }
    while(*wstrdes++)
    {
        ;
    }
    wstrdes--;
    while((*wstrdes++=*wstrsrc++) && --n)
    {
        ;
    }
    while(n-->1)
    {
        *wstrdes++=0;
    }
    return tmp;
}

/**********************************************************************/
//    函数说明:    与strcmp()相似，比较两个字符串，当相等时返回0
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
S32 YWLIB_Wstrcmp(const YWLIB_WChar_T *wstr1,const YWLIB_WChar_T *wstr2)
{
    YWLIB_ASSERT(wstr1!=NULL && wstr2!=NULL);
    while((*wstr1==*wstr2) && ((*wstr1!=0) && (*wstr2!=0)))
    {
        wstr1++;
        wstr2++;
    }
    return *wstr1-*wstr2;
}

/**********************************************************************/
//    函数说明:    与strncmp相似，比较两个字符串前n个字符，相等时返回0
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
S32 YWLIB_Wstrncmp(const YWLIB_WChar_T *wstr1,const YWLIB_WChar_T *wstr2,U32 n)
{
    YWLIB_ASSERT(wstr1!=NULL && wstr2!=NULL);
    if(!n)
    {
        return 0;
    }
    while((*wstr1==*wstr2) && ((*wstr1!=0) && (*wstr2!=0)) && --n)
    {
        wstr1++;
        wstr2++;
    }
    return *wstr1-*wstr2;
}

/**********************************************************************/
//    函数说明:    与strchr()相似，在字符串wstr中查找wchar的位子
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
YWLIB_WChar_T *YWLIB_Wstrchr(const YWLIB_WChar_T *wstr,YWLIB_WChar_T wchar)
{
    YWLIB_ASSERT(wstr!=NULL);
    while(*wstr!=wchar && *wstr++!=0)
    {
        ;
    }
    if(*wstr==wchar)
    {
        return (YWLIB_WChar_T *)wstr;
    }
    else 
    {
        return NULL;
    }
}

/**********************************************************************/
//    函数说明:    与strcspn()相似，返回不包含wstrsrc中任何字符的wstrdes的最大长度
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
U32 YWLIB_Wstrcspn(const YWLIB_WChar_T *wstrdes,const YWLIB_WChar_T *wstrsrc)
{
    U32 cntrst=0;
    const YWLIB_WChar_T * ptmp=wstrsrc;
    YWLIB_ASSERT(wstrdes!=NULL && wstrsrc!=NULL);
    while(*wstrdes)
    {
        while(*wstrsrc)
        {
            if(*wstrsrc++==*wstrdes)
            {
                goto wstrcspn_outloop;
            }
        }
        wstrdes++;
        wstrsrc=ptmp;
        cntrst++;
    }
wstrcspn_outloop:
    return cntrst;
}

/**********************************************************************/
//    函数说明:    与strpbrk()相似，返回一个指针，指向wstrdes中第一个与wstrsrc中任何字符相同的字符位置，如果没有则返回NULL
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
YWLIB_WChar_T *YWLIB_Wstrpbrk(const YWLIB_WChar_T *wstrdes,const YWLIB_WChar_T *wstrsrc)
{
    const YWLIB_WChar_T * ptmp=wstrsrc;
    YWLIB_ASSERT(wstrdes!=NULL && wstrsrc!=NULL);
    while(*wstrdes)
    {
        while(*wstrsrc)
        {
            if(*wstrdes==*wstrsrc++)
            {
                return (YWLIB_WChar_T *)wstrdes;
            }
        }
        wstrdes++;
        wstrsrc=ptmp;
    }
    return NULL;
}

/**********************************************************************/
//    函数说明:    与strrchr()相似，在wstrdes中搜索wchar最后一次出现的位置，如果没有则返回NULL
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
YWLIB_WChar_T *YWLIB_Wstrrchr(const YWLIB_WChar_T *wstrdes,YWLIB_WChar_T wchar)
{
    YWLIB_WChar_T *rst=NULL;
    YWLIB_ASSERT(wstrdes!=NULL && wstrsrc!=NULL);
    if(wchar)
    {
        while(*wstrdes)
        {
            if(*wstrdes==wchar)
            {
                rst=(YWLIB_WChar_T *)wstrdes;
            }
			wstrdes++;
        }
        return rst;
    }
    else
    {
        while(*wstrdes++)
        {
            ;//do nothing
        }
        return (YWLIB_WChar_T *)--wstrdes;
    }
}

/**********************************************************************/
//    函数说明:    与strspn()相似，返回wstrdes中完全由wstrsrc中的字符组成的最大起始长度
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
U32 YWLIB_Wstrspn(const YWLIB_WChar_T *wstrdes,const YWLIB_WChar_T *wstrsrc)
{
    U32 cntrst=0;
    const YWLIB_WChar_T * ptmp=wstrsrc;
    YWLIB_ASSERT(wstrdes!=NULL && wstrsrc!=NULL);
    while(*wstrdes)
    {
        while(*wstrsrc)
        {
            if(*wstrdes==*wstrsrc)
            {
                cntrst++;
                break;
            }
            else
            {
                if(!*++wstrsrc)
                {
                    goto wstrspn_outloop;
                }
            }
        }
        wstrdes++;
        wstrsrc=ptmp;
    }
wstrspn_outloop:
    return cntrst;
}

/**********************************************************************/
//    函数说明:    与strstr()相似，返回一个指针，指向wstrdes中第一次出现wstrsrc的位置，如果没有则返回NULL
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
YWLIB_WChar_T *YWLIB_Wstrstr(const YWLIB_WChar_T *wstrdes,const YWLIB_WChar_T *wstrsrc)
{
    U32 srclen;
    YWLIB_ASSERT(wstrdes!=NULL && wstrsrc!=NULL);
    srclen=YWLIB_Wstrlen(wstrsrc);
    while(*wstrdes)
    {
        if(!YWLIB_Wstrncmp(wstrdes, wstrsrc, srclen))
        {
            return (YWLIB_WChar_T *)wstrdes;
        }
        else
        {
            wstrdes++;
        }
    }
    return NULL;
}


/*new append*/

/**********************************************************************/
//    函数说明:    把ASCII字符串转换为WSTR
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
YWLIB_WChar_T * YWLIB_Astr2wstr(YWLIB_WChar_T *wstrdes,const S8 *strsrc)
{
    YWLIB_WChar_T *tmp=wstrdes;
    YWLIB_ASSERT(wstrdes!=NULL && strsrc!=NULL);
    while((*wstrdes++=*strsrc++)||0)
    {
        ;//do nothing
    }
    return tmp;
}
 
S32 YWLIB_Wstr2AscStr(S8 * YWLIB_RESTRICT pDes, const YWLIB_WChar_T * YWLIB_RESTRICT pSrc)
{
    S32 ret = 0;
    while(*pSrc != 0)
    {
        if(*pSrc>127)
        {
            *pDes = ' ';
        }
        else
        {
            *pDes = (S8)*pSrc;
        }
        pSrc++;
        pDes++;
        ret++;
    }
    *pDes = 0;
    return ret;
}
/**********************************************************************/
//    函数说明:    与strpbrk相似，返回一个指针，指向wstrdes中第一个与wstrsrc中任何字符相同的字符位置，如果没有则返回NULL
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
YWLIB_WChar_T *YWLIB_WstrApbrk(const YWLIB_WChar_T *wstrdes,const S8 *wstrsrc)
{
    const S8 * ptmp=wstrsrc;
    YWLIB_ASSERT(wstrdes!=NULL && wstrsrc!=NULL);
    while(*wstrdes)
    {
        while(*wstrsrc)
        {
            if(*wstrdes==*wstrsrc++)
            {
                return (YWLIB_WChar_T *)wstrdes;
            }
        }
        wstrdes++;
        wstrsrc=ptmp;
    }
    return NULL;
}

/**********************************************************************/
//    函数说明:    基本同sprintf()，可通过宏YWLIB_SWPRINTF_ENFLOAT确定其是否支持float转换输出
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
S32 YWLIB_Swprintf(YWLIB_WChar_T *wstrdes,const YWLIB_WChar_T *format,...)
{
    S32 countrst=0;
    S32 tmpcount;
    YWLIB_WChar_T * ptmpfmt=NULL;
    YWLIB_WChar_T * wstrsrc=NULL;
    YWLIB_WChar_T tmpargw;
    int tmpargi;
#if YWLIB_SWPRINTF_ENFLOAT
    float tmpargf;
#endif
    S8 cntbuf[YWLIB_SWPRINTF_BUFSIZE]={0};
    S8 formatbuf[12]={0};
    S8 *pbuf=NULL;
    va_list var_list;
    va_start(var_list,format);
    while(*format!=0)
    {
        while(*format!='%' && *format!=0)
        {
            *wstrdes++=*format++;
            countrst++;
        }
        if(*format=='%')
        {
#if YWLIB_SWPRINTF_ENFLOAT
            ptmpfmt=YWLIB_WstrApbrk(++format, (const S8*)"cdefgiopsuxEGX%");
#else
            ptmpfmt=YWLIB_WstrApbrk(++format, (const S8*)"cdiopsuxX%");
#endif
            YWLIB_ASSERT(ptmpfmt!=NULL);
            switch(*ptmpfmt)
            {
                case '%':
                    *wstrdes++='%';
                    countrst++;
                    break;
                case 's':
                    wstrsrc=va_arg(var_list,YWLIB_WChar_T *);
                    while(*wstrsrc)
                    {
                        *wstrdes++=*wstrsrc++;
                        countrst++;
                    }
                    break;
                case 'c':
                    tmpargw=(YWLIB_WChar_T)va_arg(var_list,int);//x86环境为tmpargw=va_arg(var_list,YWLIB_WChar_T);
                    *wstrdes++=tmpargw;
                    countrst++;
                    break;
                default:
                    pbuf=formatbuf;
                    formatbuf[0]='%';
                    while(format<=ptmpfmt)
                    {
                        *++pbuf=(S8)(*format++);
                    }
#if YWLIB_SWPRINTF_ENFLOAT
                    switch(*ptmpfmt)
                    {
                        case 'd'://go on
                        case 'i'://go on
                        case 'o'://go on
                        case 'u'://go on
                        case 'x'://go on
                        case 'X':
#endif
                            tmpargi=va_arg(var_list,int);
                            tmpcount=sprintf((char *)cntbuf,(char *)formatbuf,tmpargi);
                            YWLIB_Astr2wstr(wstrdes,cntbuf);
                            wstrdes+=tmpcount;
                            countrst+=tmpcount;
                            memset(formatbuf,0,sizeof(formatbuf));
                            memset(cntbuf,0,sizeof(cntbuf));
                            break;
#if YWLIB_SWPRINTF_ENFLOAT
                        case 'e'://go on
                        case 'f'://go on
                        case 'g'://go on
                        case 'E'://go on
                        case 'G':
                            tmpargf=(float)va_arg(var_list,double);
                            tmpcount=sprintf((char *)cntbuf, (char*)formatbuf,tmpargf);
                            YWLIB_Astr2wstr(wstrdes,cntbuf);
                            wstrdes+=tmpcount;
                            countrst+=tmpcount;
                            memset(formatbuf,0,sizeof(formatbuf));
                            memset(cntbuf,0,sizeof(cntbuf));
                            break;
                        default:
                            break;
                    }
#endif
                    break;
            }
            format=++ptmpfmt;
        }
    }
    *wstrdes = 0;
    return countrst;
}


/**********************************************************************/
//    函数说明:    基本同sprintf()，可通过宏YWLIB_SWPRINTF_ENFLOAT确定其是否支持float转换输出
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
S32 YWLIB_SwprintfA(YWLIB_WChar_T *wstrdes,const S8 *format,...)
{
    S32 countrst=0;
    S32 tmpcount;
    S8 *ptmpfmt=NULL;
    YWLIB_WChar_T *wstrsrc=NULL;
    YWLIB_WChar_T tmpargw;
    int tmpargi;
#if YWLIB_SWPRINTF_ENFLOAT
    float tmpargf;
#endif
    S8 cntbuf[YWLIB_SWPRINTF_BUFSIZE]={0};
    S8 formatbuf[12]={0};
    S8 *pbuf=NULL;
    va_list var_list;
    va_start(var_list,format);
    while(*format!=0)
    {
        while(*format!='%' && *format!=0)
        {
            *wstrdes++=*format++;
            countrst++;
        }
        if(*format=='%')
        {
#if YWLIB_SWPRINTF_ENFLOAT
            ptmpfmt=strpbrk((const char*)++format, "cdefgiopsuxEGX%");
#else
            ptmpfmt=strpbrk(++format, "cdiopsuxX%");
#endif
            YWLIB_ASSERT(ptmpfmt!=NULL);
            switch(*ptmpfmt)
            {
                case '%':
                    *wstrdes++='%';
                    countrst++;
                    break;
                case 's':
                    wstrsrc=va_arg(var_list,YWLIB_WChar_T *);
                    while(*wstrsrc)
                    {
                        *wstrdes++=*wstrsrc++;
                        countrst++;
                    }
                    break;
                case 'c':
                    tmpargw=(YWLIB_WChar_T)va_arg(var_list,int);
                    *wstrdes++=tmpargw;
                    countrst++;
                    break;
                default:
                    pbuf=formatbuf;
                    formatbuf[0]='%';
                    while(format<=ptmpfmt)
                    {
                        *++pbuf=(S8)(*format++);
                    }
#if YWLIB_SWPRINTF_ENFLOAT
                    switch(*ptmpfmt)
                    {
                        case 'd'://go on
                        case 'i'://go on
                        case 'o'://go on
                        case 'u'://go on
                        case 'x'://go on
                        case 'X':
#endif
                            tmpargi=va_arg(var_list,int);
                            tmpcount=sprintf((char *)cntbuf,(char *)formatbuf,tmpargi);
                            YWLIB_Astr2wstr(wstrdes,cntbuf);
                            wstrdes+=tmpcount;
                            countrst+=tmpcount;
                            memset(formatbuf,0,sizeof(formatbuf));
                            memset(cntbuf,0,sizeof(cntbuf));
                            break;
#if YWLIB_SWPRINTF_ENFLOAT
                        case 'e'://go on
                        case 'f'://go on
                        case 'g'://go on
                        case 'E'://go on
                        case 'G':
                            tmpargf=(float)va_arg(var_list,double);
                            tmpcount=sprintf((char*)cntbuf,(char*)formatbuf,tmpargf);
                            YWLIB_Astr2wstr(wstrdes,cntbuf);
                            wstrdes+=tmpcount;
                            countrst+=tmpcount;
                            memset(formatbuf,0,sizeof(formatbuf));
                            memset(cntbuf,0,sizeof(cntbuf));
                            break;
                        default:
                            break;
                    }
#endif
                    break;
            }
            format=++ptmpfmt;
        }
    }
    *wstrdes = 0;
    return countrst;
}

/*second append*/

/**********************************************************************/
//    函数说明:    与atoi()相似，把宽字符数组连接成整数
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
S32 YWLIB_Watoi(const YWLIB_WChar_T *wstrsrc)
{
    S32 result=0;
    BOOL sFlag=0;
    while(*wstrsrc==' ')
    {
        wstrsrc++;
    }
    if(*wstrsrc=='-')
    {
        sFlag=1;
        wstrsrc++;
    }
    while(*wstrsrc>='0' && *wstrsrc<='9')
    {
        result=(result<<1)+(result<<3);
        result+=((*wstrsrc++)-'0');
    }
    if(sFlag)
    {
        result=0-result;
    }
    return result;
}

/**********************************************************************/
//    函数说明:    与itoa()相似，把整数转换成宽字符串
//    调用说明:
//    
//    修改记录:    日       期      作      者       修定
//                  ---------        --------        ----
/**********************************************************************/
YWLIB_WChar_T *YWLIB_Witoa(S32 srcarg,YWLIB_WChar_T *wstrdes,const S32 radix)
{
    S8 buf[64];
    S8 *pbuf=buf;
    BOOL sFlag=0;
    YWLIB_WChar_T *ptmpdes = wstrdes;
    U32 ussrcarg=(U32)srcarg;
    if(radix<2 && radix>36)
    {
        *wstrdes = 0;
        return wstrdes;
    }
    if(srcarg == 0)
    {
        *wstrdes++ = '0';
        *wstrdes = 0;
        return wstrdes;
    }
    if(radix == 10)
    {
        if(srcarg < 0)
        {
            sFlag = 1;
            srcarg = 0-srcarg;
        }
        while(srcarg != 0)
        {
            *pbuf++ = srcarg%radix+'0';
            srcarg/=radix;
        }
        if(sFlag)
        {
            *ptmpdes++='-';
        }
    }
    else
    {
        while(ussrcarg != 0)
        {
            *pbuf=ussrcarg%radix+'0';
            if(*pbuf>'9')
            {
                *pbuf+=39;
            }
            ussrcarg/=radix;
            pbuf++;
        };
    }
    while(pbuf != buf)
    {
        *ptmpdes++=*--pbuf;
    }
    *ptmpdes=0;
    return wstrdes;
}

#ifdef USE_LINUX
/*Host to network long*/
U32 YWLIB_HtoNL(U32 HostLong)
{
	return(htonl(HostLong));
}

/*Host to network short*/
U16 YWLIB_HtoNS(U16 HostShort)
{
	return(htons(HostShort));
}

/*Network to Host long*/
U32 YWLIB_NtoHL(U32 NetLong)
{
	return(ntohl(NetLong));
}

/*Network to Host short*/
U16 YWLIB_NtoHS(U16 NetShort)
{
	return(ntohs(NetShort));
}
/* Converts the Internet host address cp from numbers-and-dots notation into
binary data in network byte  order.*/
U32 YWLIB_Inet_Addr(const S8* Addr)
{
	return((U32)inet_addr((const char*)Addr));  //lwj change
}
#endif
