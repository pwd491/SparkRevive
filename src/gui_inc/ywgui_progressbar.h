#ifndef _YWGUI_PROGRESSBAR_H_20081114_
#define  _YWGUI_PROGRESSBAR_H_20081114_
 
#ifdef __cplusplus
extern "C" {
#endif 

//特定控件的消息从0x0300开始定义
//其中0x0300~0x034F是内部消息
//0x0350~0x03AF 是向应用开放的消息

/*
YWGUI_PBM_SETRANGE
wParam -- 最大值
lParam -- 保留
*/

#define YWGUI_PBM_SETRANGE            0x0300

/*
YWGUI_PBM_SETPOS
wParam -- pos值
lParam -- 保留
*/

#define YWGUI_PBM_SETPOS                0x0301

/*
YWGUI_PBM_GETPOS
wParam -- 获取pos值的指针
lParam -- 获取(max-min)值的指针 (min 固定为0,实际是得到 max 值)
*/

#define YWGUI_PBM_GETPOS                0x0302


/*
YWGUI_PBM_SET_STEP_SIZE
wParam -- Thumb size(单位:象素)
lParam -- Interval size(单位:象素)
*/

#define YWGUI_PBM_SET_STEP_SIZE         0x0303

/*
YWGUI_PBM_GETPOS_RECT
wParam -- 获取rect值的指针
lParam -- lParam -- 保留
*/

#define YWGUI_PBM_GETPOS_RECT          0x0304


typedef struct YWGUI_ProgressbarData_s
{
    U32 min;
    U32 max;
    U32 pos;
    U32 stepInterval; 
    U32 stepThumb;
} YWGUI_ProgressbarData_T;
typedef YWGUI_ProgressbarData_T* YWGUI_ProgressbarData_P;  






#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif /* _YWGUI_PROGRESSBAR_H_20081114_ */



