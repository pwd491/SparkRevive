/**********************************文件头部注释************************************/
//
//
//  					Copyright (C), 2005-2010, AV Frontier Tech. Co., Ltd.
//
//
// 文件名：		ywlib.h
//
// 创建者：
//
// 创建时间：	2007.12.15
//
// 文件描述：
//
// 修改记录：   日       期      作      者       版本      修定
//				       ---------         ---------        -----        -----
/*****************************************************************************************/

/************************************函数定义****************************************/

#ifndef __YWLIB_H__
#define __YWLIB_H__

//#include "ywevt.h"

#ifdef __cplusplus
extern "C" {
#endif

/*add by zfy*/
typedef U16 YWLIB_WChar_T;

enum
{
    YWLIB_ERROR_RBTREE_NODE_VALUE_REPEAT = YW_MODULE_SET_ID(YWOS_MODULE_LIB_ID),
    YWLIB_ERROR_RBTREE_NODE_VALUE_DELETE_INVALID,
    YWLIB_ERROR_RBTREE_NODE_NOT_FIND,
    YWLIB_ERROR_COMPRESS,
    YWLIB_ERROR_DECOMPRESS
};




#ifndef YWLIB_PART_STRING
#define YWLIB_PART_STRING

S32 YWLIB_Strlen(const S8 * pStr);
S32 YWLIB_Sprintf (S8 *pStr, const S8 * const format,...);
S32 YWLIB_Snprintf (S8 *pStr, S32 Size, const S8 * const format,...);
S8* YWLIB_Strcpy(S8 * pDstStr, const S8 *pSrcStr) ;
S8* YWLIB_Strcat(S8 * pDstStr, const S8 *pSrcStr) ;
S32 YWLIB_Strcmp(S8 * str1, S8 *str2) ;
S32 YWLIB_Strncmp(S8 * str1, S8 *str2, S32 count) ;
S8* YWLIB_Strncpy(S8 * pDstStr, const S8 *pSrcStr, S32 count) ;
S8* YWLIB_Strchr(S8 * str, S8 ch) ;
S8* YWLIB_Strstr(const S8 * str1, const S8 *str2);
S8* YWLIB_Strtok(S8 * str1, const S8 *str2) ;
S32 YWLIB_Isalpha(S32 ch) ;
S32 YWLIB_Isalnum(S32 ch) ;
S8* YWLIB_Strrchr(const S8 * s, S32 c);
YWLIB_WChar_T YWLIB_WToLower(YWLIB_WChar_T wChar);
S32 YWLIB_Wstrcasecmp(const YWLIB_WChar_T * wstr1, YWLIB_WChar_T * wstr2);
S32 YWLIB_Strcasecmp(const S8 * s1, const S8 * s2);
S32 YWLIB_Strncasecmp(const S8 * s1, const S8 * s2, U32 n);
S8* YWLIB_Strdup(const S8 * s);
S32 YWLIB_ToUpper(S32 ch);
S32 YWLIB_ToLower(S32 ch);
S32 YWLIB_Atoi(const S8 * str);
S8* YWLIB_Itoa(S32 value, S8 *str, U32 radix) ;

//U64 YWLIB_AtoI64(const S8 * str,S8 **endptr, S32 base);
//S8* YWLIB_I64toa( U64 value1, S8 *str, U32 radix );
#endif




#ifndef YWLIB_PART_ANISC
#define YWLIB_PART_ANISC

void *  YWLIB_Memset( void *s, int c, U32 n) ;
void *  YWLIB_Memcpy(void *dest, const void *src, U32 n) ;
S32     YWLIB_Memcmp(const void *s1, const void *s2, U32 n) ;
void    YWLIB_Bzero(void * s, S32 n);
void *  YWLIB_Memmove(void * dst, const void * src, U32 count);

#ifdef USE_LINUX
/*Host to network long*/
U32 YWLIB_HtoNL(U32 HostLong);
/*Host to network short*/
U16 YWLIB_HtoNS(U16 HostShort);
/*Network to Host long*/
U32 YWLIB_NtoHL(U32 NetLong);
/*Network to Host short*/
U16 YWLIB_NtoHS(U16 NetShort);
/* Converts the Internet host address cp from numbers-and-dots notation
into binary data in network byte  order.*/
U32 YWLIB_Inet_Addr(const S8* Addr);
#endif
#endif





#ifndef YWLIB_PART_WSTRING
#define YWLIB_PART_WSTRING

#define YWLIB_RESTRICT

void *YWLIB_Memwset(void *wstr,YWLIB_WChar_T wchr,U32 n);
S32 YWLIB_Wstrlen(const YWLIB_WChar_T *wstr);
YWLIB_WChar_T *YWLIB_Wstrcpy(YWLIB_WChar_T * YWLIB_RESTRICT wstrdes,const YWLIB_WChar_T * YWLIB_RESTRICT wstrsrc);
YWLIB_WChar_T *YWLIB_Wstrncpy(YWLIB_WChar_T * YWLIB_RESTRICT wstrdes,const YWLIB_WChar_T * YWLIB_RESTRICT wstrsrc,U32 n);
void *YWLIB_Memwchr(const void *wstr,YWLIB_WChar_T wchr,U32 n);
YWLIB_WChar_T *YWLIB_Wstrcat(YWLIB_WChar_T * YWLIB_RESTRICT wstrdes,const YWLIB_WChar_T * YWLIB_RESTRICT wstrsrc);
YWLIB_WChar_T *YWLIB_Wstrncat(YWLIB_WChar_T * YWLIB_RESTRICT wstrdes,const YWLIB_WChar_T * YWLIB_RESTRICT wstrsrc,U32 n);
S32 YWLIB_Wstrcmp(const YWLIB_WChar_T *wstr1,const YWLIB_WChar_T *wstr2);
S32 YWLIB_Wstrncmp(const YWLIB_WChar_T *wstr1,const YWLIB_WChar_T *wstr2,U32 n);
YWLIB_WChar_T *YWLIB_Wstrchr(const YWLIB_WChar_T *wstr,YWLIB_WChar_T wchar);
U32 YWLIB_Wstrcspn(const YWLIB_WChar_T *wstrdes,const YWLIB_WChar_T *wstrsrc);
YWLIB_WChar_T *YWLIB_Wstrpbrk(const YWLIB_WChar_T *wstrdes,const YWLIB_WChar_T *wstrsrc);
YWLIB_WChar_T *YWLIB_Wstrrchr(const YWLIB_WChar_T *wstrdes,YWLIB_WChar_T wchar);
U32 YWLIB_Wstrspn(const YWLIB_WChar_T *wstrdes,const YWLIB_WChar_T *wstrsrc);
YWLIB_WChar_T *YWLIB_Wstrstr(const YWLIB_WChar_T *wstrdes,const YWLIB_WChar_T *wstrsrc);
YWLIB_WChar_T * YWLIB_Astr2wstr(YWLIB_WChar_T *wstrdes,const S8 *strsrc);
S32 YWLIB_Wstr2AscStr(S8 * YWLIB_RESTRICT pDes, const YWLIB_WChar_T * YWLIB_RESTRICT pSrc);
YWLIB_WChar_T *YWLIB_WstrApbrk(const YWLIB_WChar_T *wstrdes,const S8 *wstrsrc);
S32 YWLIB_Swprintf(YWLIB_WChar_T *wstrdes,const YWLIB_WChar_T *format,...);
S32 YWLIB_SwprintfA(YWLIB_WChar_T *wstrdes,const S8 *format,...);//新增加
S32 YWLIB_Watoi(const YWLIB_WChar_T *wstrsrc);
YWLIB_WChar_T *YWLIB_Witoa(S32 srcarg,YWLIB_WChar_T *wstrdes,const S32 radix);
#endif





#ifndef YWLIB_PART_RBTREE
#define YWLIB_PART_RBTREE

typedef enum YWLIB_CompareType_e
{
    YWLIB_LESS_THAN, // <
    YWLIB_LESS_OR_EQUAL, // <=
    YWLIB_MORE_THAN, // >
    YWLIB_MORE_OR_EQUAL, // >=
    YWLIB_EQUAL, // ==
    YWLIB_NOT_EQUAL, // !=
    YWLIB_RANGE_OPEN_OPEN, // ()
    YWLIB_RANGE_OPEN_CLOSE, // (]
    YWLIB_RANGE_CLOSE_OPEN, // [)
    YWLIB_RANGE_CLOSE_CLOSE // []
}YWLIB_CompareType_T;

typedef enum YWLIB_CompareResult_e
{
    YWLIB_RESULT_MORE_THAN,
    YWLIB_RESULT_LESS_THAN,
    YWLIB_RESULT_EQUAL
}YWLIB_CompareResult_T;
typedef YW_ErrorType_T (*YWLIB_CompareFunc_T)(void *Key1, void *Key2, YWLIB_CompareResult_T *Result, void*UserData);

typedef  U32 YWLIB_RBTreeHandle_T;

typedef struct YWLIB_RBTreeOpenPara_s
{
    YWLIB_CompareFunc_T CompareFunc;
    void *CompareFuncUserData;
    U32 MaxNode;
    YWOS_PartitionID_T Partition;
}YWLIB_RBTreeOpenPara_T;


typedef struct YWLIB_CpEventProgress_s
{
    U64                 llTotalSize;
    U64                 llTotalCopied;
    U64                 llFileSize;
    U64                 llFileCopied;
    U32                 uCopySize;
    U32                 uTotalProgress;
    U32                 uFileProgress;
    U8                  *pcSourceDir;
    U8                  *pcDestDir;
    U8                  *pcSource;
    U8                  *pcDest;
}YWLIB_CpEventProgress_T;

typedef struct YWLIB_TarCreateEventProgress_s
{
    U64                 llTotalSize;
    U64                 llTotalCreated;
    U64                 llFileSize;
    U64                 llFileCreated;
    U32                 uCopySize;
    U32                 uTotalProgress;
    U32                 uFileProgress;
    U8                  *pcSource;
}YWLIB_TarCreateEventProgress_T;

typedef struct YWLIB_TarExtractEventProgress_s
{
    U32                 uTotal;
    U32                 uExtracted;
    U32                 uProgress;
}YWLIB_TarExtractEventProgress_T;


YW_ErrorType_T YWLIB_RBTreeInit(void);
YW_ErrorType_T YWLIB_RBTreeTerm(void);
YW_ErrorType_T YWLIB_RBTreeOpen(YWLIB_RBTreeOpenPara_T *Para ,YWLIB_RBTreeHandle_T *Handle);
YW_ErrorType_T YWLIB_RBTreeClose(YWLIB_RBTreeHandle_T Handle);
YW_ErrorType_T YWLIB_RBTreeInsert(YWLIB_RBTreeHandle_T Handle, void *Key, void *Value);
YW_ErrorType_T YWLIB_RBTreeDelete(YWLIB_RBTreeHandle_T Handle, void *Key, void *Value);


YW_ErrorType_T YWLIB_RBTreeIsExist(YWLIB_RBTreeHandle_T Handle, void *Key, BOOL *Exist);



YW_ErrorType_T YWLIB_RBTreeQueryWithMaxMemOutside(YWLIB_RBTreeHandle_T TreeHdl,
                                                                            YWLIB_CompareType_T Operation,
                                                                            void *RefKey1,
                                                                            void *RefKey2,
                                                                            BOOL Ascending,
                                                                            U32 *ValueNum,
                                                                            void **Value);



YW_ErrorType_T YWLIB_RBTreeIndexGetbyElem(YWLIB_RBTreeHandle_T Handle,
                                                                                                          void *Key,
                                                                                                          void *Value,
                                                                                                          U32 *Index);

YW_ErrorType_T YWLIB_RBTreeElemGetByIndex(YWLIB_RBTreeHandle_T Handle,
                                                                                                          U32 Index,
                                                                                                          void **Key,
                                                                                                          void **Value);
YW_ErrorType_T YWLIB_RBTreeGetAllElemCount(YWLIB_RBTreeHandle_T Handle, U32 *Count);
YW_ErrorType_T YWLIB_RBTreeQueryFirst(YWLIB_RBTreeHandle_T Handle, void *Key, void ** Value);
#endif






#ifndef YWLIB_PART_LIST
#define YWLIB_PART_LIST

typedef struct YWLIB_ListHead_s
{
	struct YWLIB_ListHead_s *Next, *Prev;
}YWLIB_ListHead_T;

#define YWLIB_LIST_HEAD_INIT(Name) { &(Name), &(Name) }

#define YWLIB_LIST_HEAD(Name) \
 YWLIB_ListHead_T Name = YWLIB_LIST_HEAD_INIT(Name)

#define YWLIB_INIT_LIST_HEAD(Ptr) do { \
 (Ptr)->Next = (Ptr); (Ptr)->Prev = (Ptr); \
} while (0)


/**
 * list_entry - get the struct for this entry
 * @ptr: the &struct list_head pointer.
 * @type: the type of the struct this is embedded in.
 * @member: the name of the list_struct within the struct.
 */
#define YWLIB_ListEntry(Ptr, Type, Member) \
 ((Type *)((S8 *)(Ptr)-(unsigned long)(&((Type *)0)->Member)))

/**
 * list_for_each - iterate over a list
 * @pos: the &struct list_head to use as a loop counter.
 * @head: the head for your list.
 */
#define YWLIB_ListForEach(Pos, Head) \
 for (Pos = (Head)->Next; Pos != (Head); Pos = Pos->Next)

/**
 * list_for_each_safe - iterate over a list safe against removal of list entry
 * @pos: the &struct list_head to use as a loop counter.
 * @n:  another &struct list_head to use as temporary storage
 * @head: the head for your list.
 */
#define YWLIB_ListForEachSafe(Pos, n, Head) \
 for (Pos = (Head)->Next, n = Pos->Next; Pos != (Head); \
  Pos = n, n = Pos->Next)

void YWLIB_ListAdd(YWLIB_ListHead_T *New, YWLIB_ListHead_T *Head);
void YWLIB_ListAddTail(YWLIB_ListHead_T *New, YWLIB_ListHead_T *Head);
void YWLIB_ListDel(YWLIB_ListHead_T *Entry);
void YWLIB_ListDelInit(YWLIB_ListHead_T *Entry);
BOOL YWLIB_ListEmpty(YWLIB_ListHead_T *Head);
#endif






U32 YWLIB_GenerateCRC32( U8 *DataBuf, U32 DataLen );
U16 YWLIB_GenerateCRC16( U8 * buffer, U32 bufLength );

void YWLIB_ConvertSecondsToDateTime(U32 SecondCount, U16 *year, U8 *month, U8 *date,U8 *hour,U8 *minute,U8 *seconds);
U32 YWLIB_ConvertDateTimeToSeconds(S32 year, S32 month, S32 date,S32 hour,S32 minute,S32 seconds,U32*SecondCount);
void  YWLIB_ConvertMjdToDate( U16  Mjd, U16  *Year, U8  *Month, U8  *Day, U8  *WeekDay );

/*DVB字符转换成UNICODE字符*/
S32 YWLIB_Dvb2Unicode(U8 *dvb, S32 length, U16 *unicode, S32 maxlen,U8 *lang);


S32 YWLIB_LocalCharSet2Unicode(U8 *dvb, S32 length, U16 *unicode, S32 maxlen,U8 *lang,U8 *charSet);
S32 YWLIB_Unicode2LocalCharSet(const U16 *unicode, S32 nLenUnicode,U8 *dvb, S32 nDvb, U8 *lang,U8 *charSet);


YW_ErrorType_T YWLIB_UrlEncode(S8  * pcInStr , S32 nInStrLen , S8 * pcOutBuf, S32 * pnOutLen);
YW_ErrorType_T YWLIB_UrlDecode(S8  *str, S8 * pcOutBuf, S32 * pnOutLen);

U32 YWLIB_ArabicProcess(U16 *str, U32 size);

#ifdef __cplusplus
}
#endif
#endif
