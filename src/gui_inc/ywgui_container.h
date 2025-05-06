/****************************************************************************************/
//
// Copyright (C), 2005-2010, FULAN Electronics Technology Development Co., Ltd.
//
// �ļ�����		ywgui_container.h
//
// �����ߣ�		ZDY
//
// �������ڣ�	2008/06/23
//
// �ļ�������	
//
// ��ǰά���ߣ�
//
// �����£�
//
/****************************************************************************************/
#ifndef _YWGUI_CONTAINER_H_20091111_
#define _YWGUI_CONTAINER_H_20091111_

#ifdef __cplusplus
extern "C" {
#endif 


#define YWGUI_CT_GETCTRLHANDLE    0x0350

typedef struct YWGUI_Container_s
{
    DWORD              dwStyle;            // dwStyle

    DWORD              ControlNum;         //�ؼ���
    YWGUI_HWnd_T*      hCtrl;              //�����ؼ������пؼ��ľ������
    U16*               CtrlID;             //�����ؼ������пؼ�ID����

    YWGUI_HWnd_T       hHide;              //���صĿؼ�����Ҫ�����л������ؼ�ʱ�����пؼ�����ΪNormal״̬
    
    YWGUI_ContainerCtrlTemplate_T* pCtrlTemplate; //�ؼ�ģ������
   
    DWORD              dwAddData;    
}YWGUI_Container_T;
typedef YWGUI_Container_T* YWGUI_Container_P;


#ifdef __cplusplus
}
#endif 

#endif
