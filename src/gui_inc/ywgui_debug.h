#ifndef _YWGUI_DEBUG_H_20080416_
#define  _YWGUI_DEBUG_H_20080416_

#ifdef __cplusplus
extern "C" {
#endif 

/**********************************编译开关*********************/

#if 0
#if  _YWGUI_DEBUG_
    #define _YWGUI_DEBUG_LEVEL_         _YWGUI_DEBUG_LEVEL_ALL

    #if (_YWGUI_DEBUG_LEVEL_ >= _YWGUI_DEBUG_LEVEL_ERROR)
    //#define YWGUI_ASSERT                YWGUI_AssertTrace
    //#define YWGUI_DBGINFO_E(x)          YWGUI_Trace x             
    #endif
    
    #if (_YWGUI_DEBUG_LEVEL_ >= _YWGUI_DEBUG_LEVEL1)
    //#define YWGUI_DBGINFO_L1(x)         YWGUI_Trace x  

    //#define YWGUI_PRINT(x)              YWGUI_printf x  


    #define _YWGUI_ENTRY_SAFE_CHECK_    //入口检查
    #endif

    #if (_YWGUI_DEBUG_LEVEL_ >= _YWGUI_DEBUG_LEVEL2)
    //#define YWGUI_DBGINFO_L2(x)         YWGUI_Trace x  
    #endif

    #if (_YWGUI_DEBUG_LEVEL_ >= _YWGUI_DEBUG_LEVEL_ALL)
    //#define YWGUI_DBGINFO(x)            YWGUI_Trace x  

    
    #define  _YWGUI_TRACE_VER_
    //#define  _YWGUI_TRACE_MSG_ 
    //#define  _YWGUI_TRACE_FONT_ 
    //#define  _YWGUI_TRACE_KEY_
    #endif
#endif

#ifndef YWGUI_ASSERT
    //#define YWGUI_ASSERT(exp)
#endif
#ifndef YWGUI_DBGINFO_E
    //#define YWGUI_DBGINFO_E(x)
#endif
#ifndef YWGUI_DBGINFO_L1
    //#define YWGUI_DBGINFO_L1(x)
#endif
#ifndef YWGUI_DBGINFO_L2
    //#define YWGUI_DBGINFO_L2(x)
#endif
#ifndef YWGUI_DBGINFO
    //#define YWGUI_DBGINFO(x)
#endif


#ifndef YWGUI_PRINT
    //#define YWGUI_PRINT(x)
#endif


#endif
/*************************宏定义*****************************/
#ifdef _YWGUI_TRACE_MSG_
    #define YWGUI_MSG_CODE_MASK             0x03 //打印 hWnd,iMsg
    #define YWGUI_MSG_ALL_MASK              0x0f //打印 hWnd,iMsg,wParam,lParam
    
    #define YWGUI_MSGSTR_MAXLEN             200
#endif


/***************************常数定义*************************/


/***************************类型定义*************************/



/***************************函数声明*************************/
#ifdef _YWGUI_TRACE_MSG_
    extern BOOL  YWGUI_Message2Str (U8 bitMask,YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam, LPARAM lParam,S8* pszMsgInfo,S32 buf_size);
#endif
    
#ifdef _YWGUI_ENTRY_SAFE_CHECK_
    extern BOOL YWGUI_CallerSafeCheck(YWGUI_HWnd_T hWnd,BOOL bAllowDesktopThread);
#endif

#ifdef _YWGUI_TRACE_VER_
    extern void YWGUI_Print_Version(void);
#endif


extern void YWGUI_Trace_Buffer(U8*pBuf,U32 len);


#ifdef __cplusplus
}
#endif 

#endif

