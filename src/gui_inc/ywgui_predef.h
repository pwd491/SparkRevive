#ifndef _YWGUI_PREDEF_H_20080416_
#define  _YWGUI_PREDEF_H_20080416_



/****************************************编译开关*******************************/
#define _YWGUI_CTRL_STATIC_SUPPORT_
#define _YWGUI_CTRL_PICTURE_SUPPORT_
#define _YWGUI_CTRL_BUTTON_SUPPORT_
#define _YWGUI_CTRL_POSBAR_SUPPORT_
#define _YWGUI_CTRL_PROGRESSBAR_SUPPORT_
#define _YWGUI_CTRL_EDIT_SUPPORT_
#define _YWGUI_CTRL_SEDIT_SUPPORT_
#define _YWGUI_CTRL_LISTBOX_SUPPORT_
#define _YWGUI_CTRL_LISTVIEW_SUPPORT_
#define _YWGUI_CTRL_LRCOMBOBOX_SUPPORT_
#define _YWGUI_CTRL_LISTTABLE_SUPPORT_
#define _YWGUI_CTRL_CONTAINER_SUPPORT_

#define _YWGUI_UNICODE_SUPPORT_


#define _YWGUI_INREGULAR_WINDOW_SUPPORT_

#define _YWGUI_BITMAP_ACCEL_SUPPORT_




/***************************数据类型定义********************************/
typedef const U8*              YWGUI_ConstU8Ptr;
typedef U32                    YWGUI_HSurface_T;

/**************************常数定义*********************************/
#define YWGUI_S32_MAX           (0x7fffffff)
#define YWGUI_U32_MAX           (0xffffffff)
#define YWGUI_S16_MAX           (0x7fff)
#define YWGUI_U16_MAX           (0xffff)

#define YWGUI_DESKTOP_WIDTH     (1128)//(1920)
#define YWGUI_DESKTOP_HEIGHT    (920)//(1080)


/**************************宏定义*********************************/



/***********************宏函数定义************************************/


#define YWGUI_IsNullAsciiStr(szStr)         ((szStr)==NULL || (szStr)[0]==0)
#define YWGUI_IsAlpha(c)                    (((c)>='a' && (c)<='z' )||((c)>='A' && (c)<='Z' ))
#define YWGUI_ToUpper(c)                    (((c) >= 'a' && (c) <= 'z') ? ((c) - 0x20) : (c) ) 
#define YWGUI_ABS(x)                        (((x)<0) ? (-(x)) : (x))
#define YWGUI_IntegerMultiple(val,divisor)  (((val)/(divisor))*(divisor))

//以下宏定义是对(abgr: 最高数值位->最低数值位)格式的组装和拆分
//0bgr
#define YWGUI_MAKE_RGB(r,g,b)         ((U32)((r)&0xff)|((U32)((g)&0xff)<<8)|((U32)((b)&0xff)<<16))
//abgr
#define YWGUI_MAKE_RGBA(a,r,g,b)      ((U32)((r)&0xff)|((U32)((g)&0xff)<<8)|((U32)((b)&0xff)<<16)|((U32)((a)&0xff)<<24))
#define YWGUI_GetRValue(bgr)          ((U8)(bgr))
#define YWGUI_GetGValue(bgr)          ((U8)(((U16)(bgr)) >> 8))
#define YWGUI_GetBValue(bgr)          ((U8)((bgr) >> 16))
#define YWGUI_GetAValue(abgr)         ((U8)((abgr) >> 24))

/***********************************************************/




#endif

