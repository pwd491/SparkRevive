#ifndef _YWGUI_POSBAR_H_20080801_
#define  _YWGUI_POSBAR_H_20080801_
 
#ifdef __cplusplus
extern "C" {
#endif 

//特定控件的消息从0x0300开始定义
//其中0x0300~0x034F是内部消息
//0x0350~0x03AF 是向应用开放的消息

/*
YWGUI_POM_SETRANGE
wParam -- 最大值
lParam -- 保留
*/

#define YWGUI_POM_SETRANGE            0x0300

/*
YWGUI_POM_SETPOS
wParam -- pos值
lParam -- 保留
*/

#define YWGUI_POM_SETPOS            0x0301

/*
YWGUI_POM_GETPOS
wParam -- 获取pos值的指针
lParam -- 获取(max-min)值的指针 (min 固定为0,实际是得到 max 值)
*/

#define YWGUI_POM_GETPOS            0x0302


/*
YWGUI_POM_SET_THUMB_SIZE
wParam -- thumb size(单位:象素)
lParam -- 保留
*/

#define YWGUI_POM_SET_THUMB_SIZE    0x0303

/*
YWGUI_POM_GET_THUMB_RECT
wParam -- thumb rect(单位:象素,相对于控件客户区的坐标)
lParam -- 保留
*/

#define YWGUI_POM_GET_THUMB_RECT    0x0304

typedef struct YWGUI_PosbarData_s
{
    U32 min;
    U32 max;
    U32 pos;
    U32 thumbSize;              
} YWGUI_PosbarData_T;
typedef YWGUI_PosbarData_T* YWGUI_PosbarData_P;  




#ifdef __cplusplus
}
#endif 

#endif 


