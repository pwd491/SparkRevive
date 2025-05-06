#ifndef _YWGUI_COMMON_H_20080620_
#define  _YWGUI_COMMON_H_20080620_

/**********************************���뿪��*************************************/
//��ywgui_ext.hͷ�ļ�ʶ���Լ��ǰ�����ywgui�ڲ������ⲿ
#define YWGUI_WITHIN


//�����debug�汾��release  �汾�Ŀ���
#define _YWGUI_DEBUG_                   1// 1--debug version; 0 --release version
#define _YWGUI_DEBUG_LEVEL_ERROR        0
#define _YWGUI_DEBUG_LEVEL1             1
#define _YWGUI_DEBUG_LEVEL2             2 //����Խ��,������ϢԽ��
#define _YWGUI_DEBUG_LEVEL_ALL          10



/***********************************ƽ̨����*************************************/
#ifndef WIN32
#include "ywdefs.h"
#include "ywos.h"
#include "ywlib.h"

#define YWGUI_TRACE_PARAM       YWOS_TRACE_ERROR

#else
#define YWGUI_TRACE_PARAM       0

#endif

/***********************************ͷ�ļ�*************************************/

#include "ywgui_ext.h"
#include "ywgui_predef.h"
#include "ywgui_cover.h"
#include "ywgui_debug.h"



#endif

