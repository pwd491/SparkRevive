/*$Source: D:/STB_PROD_APP/plugin_sdk/inc/ywimg_ext.h,v $*/
/*****************************�ļ�ͷ��ע��*************************************/
//
//			Copyright (C), 2009-2014, AV Frontier Tech. Co., Ltd.
//
//
// �� �� ����	$RCSfile: ywimg_ext.h,v $
//
// �� �� �ߣ�	D26LF
//
// ����ʱ�䣺	2009.12.09
//
// �����£�	$Date: 2012/03/31 07:35:41 $
//
//				$Author: D60NXF $
//
//				$Revision: 1.2 $
//
//				$State: Exp $
//
// �ļ�������	ͼƬ����ģ��
//
/******************************************************************************/

#ifndef __YWIMG_EXT_H
#define __YWIMG_EXT_H

/********************************  �ļ�����************************************/


#ifdef __cplusplus
extern "C" {
#endif


/********************************  ��������************************************/

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

/********************************  ���ݽṹ************************************/

/********************************  �� �� ��************************************/

/********************************  ��������************************************/

/********************************  ��������************************************/

/********************************  ��������************************************/


YW_ErrorType_T YWIMG_LoadDiBitmap(YWMID_DibitmapData_T *pstDiBmp, const U8 *psFileName);
YW_ErrorType_T YWIMG_LoadDiBitmapFromMem(YWMID_DibitmapData_T *pstDiBmp,
                                                    const void  *pMem, U32 uSize,
                                                    const S8 *pcExt);
/*YW_ErrorType_T YWIMG_LoadDiBitmapFromMemType(YWMID_DibitmapData_T *pstDiBmp,
                                                    const void  *pMem, U32 uSize,
                                                    YWMID_BitmapType_T eBitType);*/

void YWIMG_UnLoadDiBitmap(YWMID_DibitmapData_T *pstDiBmp);

/********************************  ��������************************************/


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
//��ͼƬ���ͺ�ŵ�midͷ�ļ��У�������subsys�澯
//
//Revision 1.5  2010/07/22 10:27:48  d26lf
//�޸�YWVFS_BitmapType_TΪYWIMG_BitmapType_T
//
//Revision 1.4  2010/07/13 02:17:54  d26lf
//����YWIMG_LoadDiBitmapFromMemType
//
//Revision 1.3  2010/07/12 12:13:26  d26lf
//���Ӵ��ڴ����ͼƬ�ӿ�
//
//Revision 1.2  2010/02/01 06:53:41  D54SLY
//7111 new add
//
//Revision 1.1  2009/12/22 10:19:23  d26lf
//����ͼƬ����ģ��
//
/* EOL-------------------------------------------------------------------*/

