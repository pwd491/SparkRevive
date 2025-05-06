/*$Source: D:/STB_PROD_APP/plugin_sdk/inc/ywimg_ext.h,v $*/
/*****************************文件头部注释*************************************/
//
//			Copyright (C), 2009-2014, AV Frontier Tech. Co., Ltd.
//
//
// 文 件 名：	$RCSfile: ywimg_ext.h,v $
//
// 创 建 者：	D26LF
//
// 创建时间：	2009.12.09
//
// 最后更新：	$Date: 2012/03/31 07:35:41 $
//
//				$Author: D60NXF $
//
//				$Revision: 1.2 $
//
//				$State: Exp $
//
// 文件描述：	图片解码模块
//
/******************************************************************************/

#ifndef __YWIMG_EXT_H
#define __YWIMG_EXT_H

/********************************  文件包含************************************/


#ifdef __cplusplus
extern "C" {
#endif


/********************************  常量定义************************************/

enum
{
    YWIMG_ERROR_BMP_IMAGE_TYPE  = YW_MODULE_SET_ID(YWMID_MODULE_IMG_ID ),    //Not a valid bitmap.
    YWIMG_ERROR_BMP_UNKNOWN_TYPE,     //Not recongnized bitmap type.
    YWIMG_ERROR_BMP_CANT_READ,        //Read error.
    YWIMG_ERROR_BMP_CANT_SAVE,        //Save error.
    YWIMG_ERROR_BMP_NOT_SUPPORTED,    //Not supported bitmap type.
    YWIMG_ERROR_BMP_MEM,              //Memory allocation error.
    YWIMG_ERROR_BMP_LOAD,             //Loading error.
    YWIMG_ERROR_BMP_FILEIO,           //IO failed.
    YWIMG_ERROR_BMP_OTHER,            //Other error.
    YWIMG_ERROR_BMP_ERROR_SOURCE,     //A error data source.
};

/********************************  数据结构************************************/

/********************************  宏 定 义************************************/

/********************************  变量定义************************************/

/********************************  变量引用************************************/

/********************************  函数声明************************************/


YW_ErrorType_T YWIMG_LoadDiBitmap(YWMID_DibitmapData_T *pstDiBmp, const U8 *psFileName);
YW_ErrorType_T YWIMG_LoadDiBitmapFromMem(YWMID_DibitmapData_T *pstDiBmp,
                                                    const void  *pMem, U32 uSize,
                                                    const S8 *pcExt);
/*YW_ErrorType_T YWIMG_LoadDiBitmapFromMemType(YWMID_DibitmapData_T *pstDiBmp,
                                                    const void  *pMem, U32 uSize,
                                                    YWMID_BitmapType_T eBitType);*/

void YWIMG_UnLoadDiBitmap(YWMID_DibitmapData_T *pstDiBmp);

/********************************  函数定义************************************/


#ifdef __cplusplus
}
#endif


#endif  /* __YWIMG_EXT_H */
/* EOF------------------------------------------------------------------------*/

/* BOL-------------------------------------------------------------------*/
//$Log: ywimg_ext.h,v $
//Revision 1.2  2012/03/31 07:35:41  D60NXF
//no message
//
//Revision 1.1  2012/03/27 10:23:49  D60NXF
//no message
//
//Revision 1.6  2010/07/23 02:30:41  d26lf
//把图片类型宏放到mid头文件中，并消除subsys告警
//
//Revision 1.5  2010/07/22 10:27:48  d26lf
//修改YWVFS_BitmapType_T为YWIMG_BitmapType_T
//
//Revision 1.4  2010/07/13 02:17:54  d26lf
//增加YWIMG_LoadDiBitmapFromMemType
//
//Revision 1.3  2010/07/12 12:13:26  d26lf
//增加从内存加载图片接口
//
//Revision 1.2  2010/02/01 06:53:41  D54SLY
//7111 new add
//
//Revision 1.1  2009/12/22 10:19:23  d26lf
//增加图片解码模块
//
/* EOL-------------------------------------------------------------------*/

