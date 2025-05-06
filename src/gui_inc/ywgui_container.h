/****************************************************************************************/
//
// Copyright (C), 2005-2010, FULAN Electronics Technology Development Co., Ltd.
//
// 文件名：		ywgui_container.h
//
// 创建者：		ZDY
//
// 创建日期：	2008/06/23
//
// 文件描述：	
//
// 当前维护者：
//
// 最后更新：
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

    DWORD              ControlNum;         //控件数
    YWGUI_HWnd_T*      hCtrl;              //容器控件中所有控件的句柄数组
    U16*               CtrlID;             //容器控件中所有控件ID数组

    YWGUI_HWnd_T       hHide;              //隐藏的控件，主要用于切换容器控件时把所有控件设置为Normal状态
    
    YWGUI_ContainerCtrlTemplate_T* pCtrlTemplate; //控件模板数组
   
    DWORD              dwAddData;    
}YWGUI_Container_T;
typedef YWGUI_Container_T* YWGUI_Container_P;


#ifdef __cplusplus
}
#endif 

#endif
