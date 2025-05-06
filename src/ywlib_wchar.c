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
//    ����˵��:    ��menset()���ƣ�����YWLIB_WChar_TΪ��λ
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ��strlen()���ƣ����ؿ��ַ����ַ�����
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ��strcpy����
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ��strncpy()����
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ��menchr()���ƣ����ڴ���в��ҿ��ַ�
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ��strcat()���ƣ��ѿ��ַ���wstrsrc�ӵ�wstrdes����
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ��strncat()���ƣ���wstrstrcǰn���ַ��ӵ�wstrdes�ڲ�
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ��strcmp()���ƣ��Ƚ������ַ����������ʱ����0
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ��strncmp���ƣ��Ƚ������ַ���ǰn���ַ������ʱ����0
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ��strchr()���ƣ����ַ���wstr�в���wchar��λ��
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ��strcspn()���ƣ����ز�����wstrsrc���κ��ַ���wstrdes����󳤶�
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ��strpbrk()���ƣ�����һ��ָ�룬ָ��wstrdes�е�һ����wstrsrc���κ��ַ���ͬ���ַ�λ�ã����û���򷵻�NULL
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ��strrchr()���ƣ���wstrdes������wchar���һ�γ��ֵ�λ�ã����û���򷵻�NULL
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ��strspn()���ƣ�����wstrdes����ȫ��wstrsrc�е��ַ���ɵ������ʼ����
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ��strstr()���ƣ�����һ��ָ�룬ָ��wstrdes�е�һ�γ���wstrsrc��λ�ã����û���򷵻�NULL
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ��ASCII�ַ���ת��ΪWSTR
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ��strpbrk���ƣ�����һ��ָ�룬ָ��wstrdes�е�һ����wstrsrc���κ��ַ���ͬ���ַ�λ�ã����û���򷵻�NULL
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ����ͬsprintf()����ͨ����YWLIB_SWPRINTF_ENFLOATȷ�����Ƿ�֧��floatת�����
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
                    tmpargw=(YWLIB_WChar_T)va_arg(var_list,int);//x86����Ϊtmpargw=va_arg(var_list,YWLIB_WChar_T);
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
//    ����˵��:    ����ͬsprintf()����ͨ����YWLIB_SWPRINTF_ENFLOATȷ�����Ƿ�֧��floatת�����
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ��atoi()���ƣ��ѿ��ַ��������ӳ�����
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
//    ����˵��:    ��itoa()���ƣ�������ת���ɿ��ַ���
//    ����˵��:
//    
//    �޸ļ�¼:    ��       ��      ��      ��       �޶�
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
