#ifndef _YWGUI_PROGRESSBAR_H_20081114_
#define  _YWGUI_PROGRESSBAR_H_20081114_
 
#ifdef __cplusplus
extern "C" {
#endif 

//�ض��ؼ�����Ϣ��0x0300��ʼ����
//����0x0300~0x034F���ڲ���Ϣ
//0x0350~0x03AF ����Ӧ�ÿ��ŵ���Ϣ

/*
YWGUI_PBM_SETRANGE
wParam -- ���ֵ
lParam -- ����
*/

#define YWGUI_PBM_SETRANGE            0x0300

/*
YWGUI_PBM_SETPOS
wParam -- posֵ
lParam -- ����
*/

#define YWGUI_PBM_SETPOS                0x0301

/*
YWGUI_PBM_GETPOS
wParam -- ��ȡposֵ��ָ��
lParam -- ��ȡ(max-min)ֵ��ָ�� (min �̶�Ϊ0,ʵ���ǵõ� max ֵ)
*/

#define YWGUI_PBM_GETPOS                0x0302


/*
YWGUI_PBM_SET_STEP_SIZE
wParam -- Thumb size(��λ:����)
lParam -- Interval size(��λ:����)
*/

#define YWGUI_PBM_SET_STEP_SIZE         0x0303

/*
YWGUI_PBM_GETPOS_RECT
wParam -- ��ȡrectֵ��ָ��
lParam -- lParam -- ����
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



