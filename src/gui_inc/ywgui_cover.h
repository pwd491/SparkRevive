#ifndef _YWGUI_COVER_H_20080417_
#define  _YWGUI_COVER_H_20080417_

#ifndef WIN32
    #include "ywgui_wrap.h" //yw平台封装
#else
    //#include "win32.h"   
    #include "..\\support\\win32\\include\\win32.h" 
#endif

#ifdef __cplusplus
extern "C" {
#endif 

extern void*  YWGUI_SafeMalloc(U32 Size);

#ifdef  _YWGUI_CHECK_MEM_LEAK_
    extern void *g_pLeakCheckMem;//定位内存泄漏时用
    #define YWGUI_MemMalloc(size) (g_pLeakCheckMem = YWGUI_Malloc(size),YWGUI_MemSet(g_pLeakCheckMem,0,size), g_pLeakCheckMem)
#else
    #define YWGUI_MemMalloc    YWGUI_SafeMalloc
#endif


//检测平台的Endian
typedef struct YWGUI_EndianGroup_s
{
     U8 little_endian;
     U8 Reserved[3];
}YWGUI_EndianGroup_T;

typedef union YWGUI_EndianTest_s
{
    U32 Reserved;
    YWGUI_EndianGroup_T value;
}YWGUI_EndianTest_T;

extern YWGUI_EndianTest_T g_uEndianTest;
#define YWGUI_IsLittleEndian() (g_uEndianTest.value.little_endian)


#define YWGUI_MemFree(pMem)        do {\
                                        if((pMem)!=NULL)\
                                        {\
                                            YWGUI_Free(pMem);\
                                            (pMem)=NULL;\
                                        }\
                                    }while(0)   


extern S32  ASCII_strcasecmp(const S8 *s1, const S8 *s2);
extern S32  ASCII_ToUpperString(const S8* pszString,S8* pszbuf,S32 buf_size);


extern YWGUI_Char_T* YWGUI_strdup (const YWGUI_Char_T *pStr);
  
extern YWGUI_Char_T* YWGUI_strnchr(const YWGUI_Char_T *pStr,S32 n,YWGUI_Char_T ch);
                                    

#ifdef __cplusplus
}
#endif 

#endif

