#ifndef _YWGUI_PICTURE_H_20080617_
#define  _YWGUI_PICTURE_H_20080617_

//特定控件的消息从0x0300开始定义
//其中0x0300~0x034F是内部消息
//0x0350~0x03AF 是向应用开放的消息

/*
YWGUI_PTM_SETPICTURE
wParam -- 设备无关位图结构指针
lParam -- TRUE --马上显示新的位图; FALSE--不马上显示 
*/
#define YWGUI_PTM_SETPICTURE         0x310



#ifdef __cplusplus
extern "C" {
#endif 







#ifdef __cplusplus
}
#endif 

#endif


