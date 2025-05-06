#ifndef _YWGUI_COMMON_H_20080620_
#define  _YWGUI_COMMON_H_20080620_

/**********************************编译开关*************************************/
//让ywgui_ext.h头文件识别自己是包含在ywgui内部还是外部
#define YWGUI_WITHIN


//编译成debug版本或release  版本的开关
#define _YWGUI_DEBUG_                   1// 1--debug version; 0 --release version
#define _YWGUI_DEBUG_LEVEL_ERROR        0
#define _YWGUI_DEBUG_LEVEL1             1
#define _YWGUI_DEBUG_LEVEL2             2 //级别越高,调试信息越多
#define _YWGUI_DEBUG_LEVEL_ALL          10



/***********************************平台差异*************************************/
#ifndef WIN32
#include "ywdefs.h"
#include "ywos.h"
#include "ywlib.h"

#define YWGUI_TRACE_PARAM       YWOS_TRACE_ERROR

#else
#define YWGUI_TRACE_PARAM       0

#endif

/***********************************头文件*************************************/

#include "ywgui_ext.h"
#include "ywgui_predef.h"
#include "ywgui_cover.h"
#include "ywgui_debug.h"



#endif

