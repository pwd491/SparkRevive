#ifndef _YWGUI_POSBAR_H_20080801_
#define  _YWGUI_POSBAR_H_20080801_
 
#ifdef __cplusplus
extern "C" {
#endif 

//�ض��ؼ�����Ϣ��0x0300��ʼ����
//����0x0300~0x034F���ڲ���Ϣ
//0x0350~0x03AF ����Ӧ�ÿ��ŵ���Ϣ

/*
YWGUI_POM_SETRANGE
wParam -- ���ֵ
lParam -- ����
*/

#define YWGUI_POM_SETRANGE            0x0300

/*
YWGUI_POM_SETPOS
wParam -- posֵ
lParam -- ����
*/

#define YWGUI_POM_SETPOS            0x0301

/*
YWGUI_POM_GETPOS
wParam -- ��ȡposֵ��ָ��
lParam -- ��ȡ(max-min)ֵ��ָ�� (min �̶�Ϊ0,ʵ���ǵõ� max ֵ)
*/

#define YWGUI_POM_GETPOS            0x0302


/*
YWGUI_POM_SET_THUMB_SIZE
wParam -- thumb size(��λ:����)
lParam -- ����
*/

#define YWGUI_POM_SET_THUMB_SIZE    0x0303

/*
YWGUI_POM_GET_THUMB_RECT
wParam -- thumb rect(��λ:����,����ڿؼ��ͻ���������)
lParam -- ����
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


