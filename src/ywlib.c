/**********************************文件头部注释************************************/
//
//
//                      Copyright (C), 2005-2010, AV Frontier Tech. Co., Ltd.
//
//
// 文件名：        ywlib.c
//
// 创建者：
//
// 创建时间：    2007.12.15
//
// 文件描述：    放在ywos目录下
//
// 修改记录：   日       期      作      者       版本      修定
//                       ---------            -----------           -----           -----
//
/*****************************************************************************************/


/************************************文件包含****************************************/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>

#include "ywdefs.h"
//#include "stddefs.h"
#include "ywos.h"
#include "ywlib.h"

/************************************宏定义*******************************************/
#define SPRINTF_ONE_TIME_MAX_CHAR              512


/************************************常量定义****************************************/



/************************************变量定义****************************************/


/************************************变量引用****************************************/



/************************************函数引用****************************************/



/************************************内部函数****************************************/



/************************************全局函数*********************************************/

#define STR_PART

/***********************************************************************
    函数说明:
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
************************************************************************/
S32 YWLIB_Strlen(const S8 *pStr)
{
    int iValue = 0;
    if (pStr != NULL)
    {
        iValue = strlen((char *)pStr);
    }
    return iValue;
}
#if 0
/***********************************************************************
    函数说明:
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
************************************************************************/

S32 YWLIB_Sprintf (S8 *pStr, const S8 * const format,...)
{
    va_list         list;
    unsigned int uiNoOfChar = 0;
    char *pcPrintBuffer=NULL;
    int iValue = 0;

    if (pStr != NULL)
    {
        pcPrintBuffer = YWOS_Malloc(SPRINTF_ONE_TIME_MAX_CHAR);
        if (pcPrintBuffer != NULL)
        {
            memset(pcPrintBuffer, 0, SPRINTF_ONE_TIME_MAX_CHAR);
            va_start (list, format);
            uiNoOfChar = vsprintf ( pcPrintBuffer , (char *)format, list);
            va_end (list);

            if (uiNoOfChar >0)
            {
                iValue = sprintf((char *)pStr, "%s", pcPrintBuffer);
            }
            else
            {
                memset(pStr, 0, 1);
            }

            YWOS_Free(pcPrintBuffer);
        }
    }
    return iValue;
}

#else
/***********************************************************************
    函数说明:
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
************************************************************************/
S32 YWLIB_Sprintf (S8 *pStr, const S8 * const format,...)
{
    va_list         list;
    unsigned int    uiNoOfChar = 0;

    if (pStr != NULL)
    {
        va_start (list, format);
        uiNoOfChar = vsprintf ( (char*)pStr, (char *)format, list);
        va_end (list);
    }
    return uiNoOfChar;
}
/***********************************************************************
    函数说明:
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
************************************************************************/
S32 YWLIB_Snprintf (S8 *pStr, S32 Size, const S8 * const format,...)
{
    va_list         list;
    unsigned int uiNoOfChar = 0;

    if (pStr != NULL)
    {
        va_start (list, format);
        uiNoOfChar = vsnprintf ((char*)pStr, Size, (char *)format, list);
        va_end (list);
    }
    return uiNoOfChar;
}


#endif
/***********************************************************************
    函数说明:
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
************************************************************************/
S8* YWLIB_Strcpy(S8 * pDstStr, const S8 *pSrcStr)
{
    S8 *pDest = NULL;
    if (pDstStr != NULL && pSrcStr != NULL)
    {
        pDest = (S8 *)strcpy((char *)pDstStr, (char *)pSrcStr);
    }
    return pDest;
}

/***********************************************************************
    函数说明:
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
************************************************************************/
S8* YWLIB_Strcat(S8 * pDstStr, const S8 *pSrcStr)
{
    S8 *pDest = NULL;
    if (pDstStr != NULL && pSrcStr != NULL)
    {
        pDest = (S8 *)strcat((char *)pDstStr, (char *)pSrcStr);
    }
    return pDest;
}

/***********************************************************************
    函数说明:
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
************************************************************************/
S32 YWLIB_Strcmp(S8 * str1, S8 *str2)
{
    int iValue = 0;

    if (str1 != NULL && str2 != NULL)
    {
        iValue = strcmp((char *)str1, (char *)str2);
    }
    return iValue;
}


/***********************************************************************
    函数说明:
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
************************************************************************/
S32 YWLIB_Strncmp(S8 * str1, S8 *str2, S32 count)
{
    int iValue = 0;

    if (str1 != NULL && str2 != NULL)
    {
        iValue = strncmp((char *)str1, (char *)str2 , (int)count);
    }
    return iValue;
}
/***********************************************************************
    函数说明:
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
************************************************************************/
S8* YWLIB_Strncpy(S8 * pDstStr, const S8 *pSrcStr, S32 count)
{


    if (pDstStr != NULL && pSrcStr != NULL)
    {
        return (S8*)strncpy((char *)pDstStr, (char *)pSrcStr,(int)count);
    }
    return NULL;
}

/***********************************************************************
    函数说明:
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
************************************************************************/
S8* YWLIB_Strchr(S8 * str, S8 ch)
{


    if (str != NULL)
    {
        return (S8*)strchr((char *)str, (char)ch);
    }
    return NULL;
}
/***********************************************************************
    函数说明:
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
************************************************************************/
S8* YWLIB_Strstr(const S8 * str1, const S8 *str2)
{


    if (str1 != NULL && str2 != NULL)
    {
        return (S8*)strstr((char *)str1, (char *)str2);
    }
    return NULL;
}

/***********************************************************************
    函数说明:
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
************************************************************************/
S8* YWLIB_Strtok(S8 * str1, const S8 *str2)
{


    if (str2 != NULL)
    {
        return (S8*)strtok((char *)str1, (char *)str2);
    }
    return NULL;
}

/***********************************************************************
    函数说明:
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
************************************************************************/
S32 YWLIB_Isalpha(S32 ch)
{

    return (S32)isalpha((int)ch);

}

/***********************************************************************
    函数说明:
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
************************************************************************/
S32 YWLIB_ToUpper(S32 ch)
{

    return (S32)toupper((int)ch);

}

/***********************************************************************
    函数说明:
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
************************************************************************/
S32 YWLIB_ToLower(S32 ch)
{

    return (S32)tolower((int)ch);

}


/***********************************************************************
    函数说明:
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
************************************************************************/

S32 YWLIB_Isalnum(S32 ch)
{

    return (S32)isalnum((int)ch);

}


S8 * YWLIB_Strrchr(const S8 * s, S32 c)
{
    return strrchr((const char *)s, c);
}
S32   YWLIB_Strcasecmp(const S8 * s1, const S8 * s2)
{
    while (*s1 != '\0' && tolower(*(char *)s1) == tolower(*(char *)s2))
    {
        s1++;
        s2++;
    }

    return tolower(*(unsigned char *) s1) - tolower(*(unsigned char *) s2);
}

S32   YWLIB_Strncasecmp(const S8 * s1, const S8 * s2, U32 n)
{
    if (n == 0)
        return 0;

    while (n-- != 0 && tolower(*(char *)s1) == tolower(*(char *)s2))
    {
        if (n == 0 || *s1 == '\0' || *s2 == '\0')
            break;
        s1++;
        s2++;
    }
    return tolower(*(unsigned char *) s1) - tolower(*(unsigned char *) s2);
}

S8 * YWLIB_Strdup(const S8 * s)
{
    S8 * pNew = (S8 *)YWOS_Calloc(1, YWLIB_Strlen(s)+1);
    if(NULL != pNew )
    {
        YWLIB_Strcpy(pNew, s);
    }
    return pNew;
}

YWLIB_WChar_T YWLIB_WToLower(YWLIB_WChar_T wChar)
{
    if ((wChar >= 65) && (wChar < 91))
    {
        return (wChar + 32);
    }
    else
    {
        return wChar;
    }
}

S32 YWLIB_Wstrcasecmp(const YWLIB_WChar_T * wstr1, YWLIB_WChar_T * wstr2)
{
    while((YWLIB_WToLower(*wstr1)==YWLIB_WToLower(*wstr2)) &&
            (((*wstr1) != 0) && ((*wstr2) != 0)))
    {
        wstr1++;
        wstr2++;
    }
    return (YWLIB_WToLower(*wstr1) - YWLIB_WToLower(*wstr2));
}


#define MATH_PART

/***********************************************************************
    函数说明:
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
************************************************************************/
S32 YWLIB_Atoi(const S8 * str)
{

    S32 RetValue = 0;
    if (str != NULL)
    {
        RetValue = (S32)atoi((char *)str);
    }
    return RetValue;
}
/***********************************************************************
    函数说明:
    调用说明:

       修改记录:    日       期      作      者       修定
                        ---------         ---------         -----
************************************************************************/
/*S8* YWLIB_Itoa(S32 value, S8 *str, U32 radix)
{


    if (str != NULL)
    {
        //return (S8*)itoa((int)value , (char*)str, (int)radix);
    }
    return NULL;
}
*/
S8* YWLIB_Itoa( S32 value, S8 *str, U32 radix )
{
    char *p;
    char *firstdig;
    char temp;
    U32 digval;

    p = (char*)str;

    if (value<0)
    {
        *p++ = '-';
        value = -value;
    }

    firstdig = p;

    do
    {
        digval = (U32) (value % radix);
        value /= radix;


        if (digval > 9)
        {
            *p++ = (char) (digval - 10 + 'a');
        }
        else
        {
            *p++ = (char) (digval + '0');
        }
    } while (value > 0);



    *p-- = '\0';

    do {
        temp = *p;
        *p = *firstdig;
        *firstdig = temp;
        --p;
        ++firstdig;
    } while (firstdig < p);

    return str;
}


#define MEMERY_PART

void * YWLIB_Memset( void *s, int c, U32 n)
{
    if (s == NULL)
    {
        return s;
    }

    return memset(s, c, n);
}


S32 YWLIB_Memcmp(const void *s1, const void *s2, U32 n)
{
    if (s1 == NULL || s2 == NULL)
    {
        return -1;
    }

    return memcmp(s1, s2, n);
}

void * YWLIB_Memcpy(void *dest, const void *src, U32 n)
{
    if (dest == NULL || src == NULL)
    {
        return dest;
    }

    return memcpy(dest, src, n);


}
#ifndef YWBOOT_ENABLE
void  *YWLIB_MemcpyFast( void  *Dest, void  *Src, U32  Size )
{
	void  *Result;												/* Result Pointer */
//	return YWLIB_Memcpy(Dest, Src, Size);
	if((Size < YW_K)||((U32)Dest&0x03)||((U32)Src&0x03)||((U32)Size&0x03))
	{
		Result = YWLIB_Memcpy(Dest, Src, Size);
	}
	else
	{
 //       if(YW_NO_ERROR == YWSYSTEMi_TransferByFDMA(Dest,Src, Size))
        {
            Result = Dest;
        }
//        else
		{
			Result = YWLIB_Memcpy(Dest, Src, Size);
		}
	}
	return( Result );
}
 #endif

void * YWLIB_Memmove(void * dst, const void * src, U32 count)
{
        void * ret = dst;


        if (dst <= src || (S8 *)dst >= ((S8 *)src + count)) {
                /*
                 * Non-Overlapping Buffers
                 * copy from lower addresses to higher addresses
                 */
                while (count--) {
                        *(S8 *)dst = *(S8 *)src;
                        dst = (S8 *)dst + 1;
                        src = (S8 *)src + 1;
                }
        }
        else {
                /*
                 * Overlapping Buffers
                 * copy from higher addresses to lower addresses
                 */
                dst = (S8 *)dst + count - 1;
                src = (S8 *)src + count - 1;

                while (count--) {
                        *(S8 *)dst = *(S8 *)src;
                        dst = (S8 *)dst - 1;
                        src = (S8 *)src - 1;
                }
        }


        return(ret);
}

void YWLIB_Bzero(void * s, S32 n)
{
    YWLIB_Memset(s, 0, n);
}
#define LIST_PART



/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
void LIB_ListAdd(YWLIB_ListHead_T * New,
                             YWLIB_ListHead_T * Prev,
                             YWLIB_ListHead_T * Next)
{
    Next->Prev = New;
    New->Next = Next;
    New->Prev = Prev;
    Prev->Next = New;
}

/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
void YWLIB_ListAdd(YWLIB_ListHead_T *New, YWLIB_ListHead_T *Head)
{
    LIB_ListAdd(New, Head, Head->Next);
}

/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
void YWLIB_ListAddTail(YWLIB_ListHead_T *New, YWLIB_ListHead_T *Head)
{
    LIB_ListAdd(New, Head->Prev, Head);
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
void LIB_ListDel(YWLIB_ListHead_T * Prev,
                              YWLIB_ListHead_T* Next)
{
    Next->Prev = Prev;
    Prev->Next = Next;
}

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty on entry does not return true after this, the entry is in an undefined state.
 */
void YWLIB_ListDel(YWLIB_ListHead_T *Entry)
{
    LIB_ListDel(Entry->Prev, Entry->Next);
}

/**
 * list_del_init - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 */
void YWLIB_ListDelInit(YWLIB_ListHead_T *Entry)
{
    LIB_ListDel(Entry->Prev, Entry->Next);
    YWLIB_INIT_LIST_HEAD(Entry);
}

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
BOOL YWLIB_ListEmpty(YWLIB_ListHead_T *Head)
{
    BOOL    isEmpty = FALSE;
    if( Head->Next == Head )
    {
        isEmpty = TRUE;
    }
    return isEmpty;
}


#define TIME_PART
#define  ONE_COMMON_YEAR    (365*24*60*60) //非闰年秒数
#define  ONE_DAY            (24*60*60) //一天的秒数
#define  START_YEAR         1970 

void YWLIB_ConvertSecondsToDateTime(U32 SecondCount, U16 *year, U8 *month, U8 *date,U8 *hour,U8 *minute,U8 *seconds)
{
    U8 common_year[]={31,28,31,30,31,30,31,31,30,31,30,31};//非闰年
    U8 leap_year[]={31,29,31,30,31,30,31,31,30,31,30,31};//闰年

    U32 circle_count=0;
    U32 spare_count=0;
    U32 leap_count = 0;
    S32 i=0;
    S32 cur_year=0;

  
    circle_count =SecondCount/ONE_COMMON_YEAR; //大致统计一下有多少年,再由闰年数调整
    spare_count=SecondCount%ONE_COMMON_YEAR;
    leap_count =((START_YEAR+circle_count-1)/4-(START_YEAR+circle_count-1)/100+(START_YEAR+circle_count-1)/400)-
    ((START_YEAR-1)/4-(START_YEAR-1)/100+(START_YEAR-1)/400);
    if(spare_count<leap_count*ONE_DAY)
    {
        circle_count--;
        if((((START_YEAR+circle_count)%4==0) && ((START_YEAR+circle_count)%100!=0) ) ||( (START_YEAR+circle_count)%400==0))
        {
            spare_count+= (366-leap_count)*ONE_DAY;
        }
        else
        {
            spare_count+= (365-leap_count)*ONE_DAY;
        }

        //DEG_ASSERT(spare_count>=0); //1000年里不会超过250个闰年
    }
    else
    {
        spare_count-=leap_count*ONE_DAY;
    }

   //DEG_ASSERT(spare_count<(ONE_COMMON_YEAR+ONE_DAY));
    cur_year = circle_count+START_YEAR;
    if(year!=NULL)
    {
        *year=cur_year;
    }
  
 
    if((cur_year%4==0 && cur_year%100!=0) || cur_year%400==0)
    {
        for(i=0;i<12;i++)
        {
            if((spare_count>=(unsigned int )leap_year[i]*ONE_DAY))
            {
                spare_count-=leap_year[i]*ONE_DAY;
            }
            else
            {
                if(month!=NULL)
                {
                    *month=i+1;
                }
                break;         
            }
        }
    }
    else
    {
        for(i=0;i<12;i++)
        {
            if((spare_count>=(unsigned int )common_year[i]*ONE_DAY))
            {
                spare_count-=common_year[i]*ONE_DAY;
            }
            else
            {
                if(month!=NULL)
                {
                    *month=i+1;
                }
                break;         
            }
        }
    }
 
    // DEG_ASSERT(spare_count<31*ONE_DAY);
    if(date!=NULL)
    {
        *date=1+spare_count/ONE_DAY;
    }
    spare_count=spare_count%ONE_DAY;

    if(hour!=NULL)
    {
        *hour=spare_count/3600;
    }
    spare_count=spare_count%3600;

    if(minute!=NULL)
    {
        *minute=spare_count/60;
    }
    if(seconds!=NULL)
    {
        *seconds=spare_count%60;
    }
}

U32 YWLIB_ConvertDateTimeToSeconds(S32 year, S32 month, S32 date,S32 hour,S32 minute,S32 seconds,U32*SecondCount)
{
    U32 leap_year_count = 0; //闰年个数(不包括当年)
    U32 year_total_count=0; //累积年数(闰年+平年,不包括当年)
    U32 second_count=0;
    S32 i=0;
    U8 common_year[]={31,28,31,30,31,30,31,31,30,31,30,31};//非闰年
    U8 leap_year[]={31,29,31,30,31,30,31,31,30,31,30,31};//闰年
    U8 cur_is_leap =0;
    if (SecondCount!=NULL)
    {
        *SecondCount =0;
    }
    if((year%4==0 && year%100!=0 ) || year%400==0)
    {
        cur_is_leap =1;
    }
    if(month<1 || month>13 || date<1 || hour<0 || hour>23 || minute<0 || minute>59 || seconds<0 || seconds>59)
    {
        return -1;
    }
    if(cur_is_leap)
    {
        if(date>leap_year[month-1])
        {
            return -1;
        }
    }
    else
    {
        if(date>common_year[month-1])
        {
            return -1;
        }
    }
    
    leap_year_count =((year-1)/4-(year-1)/100+(year-1)/400)-((START_YEAR-1)/4-(START_YEAR-1)/100+(START_YEAR-1)/400);
    year_total_count = year-START_YEAR;
    second_count = (year_total_count-leap_year_count)*ONE_COMMON_YEAR+leap_year_count*(ONE_COMMON_YEAR+ONE_DAY);
    if(cur_is_leap)//当前年是否闰年
    {
        for(i=0;i<(month-1);i++)
        {
            second_count+=leap_year[i]*ONE_DAY;
        }
    }
    else
    {
        for(i=0;i<(month-1);i++)
        {
            second_count+=common_year[i]*ONE_DAY;
        } 
    }
    second_count+=(date-1)*ONE_DAY+(hour)*60*60+(minute)*60+seconds;
    if (SecondCount!=NULL)
    {
        *SecondCount =second_count;
    }
    return 0;
}



