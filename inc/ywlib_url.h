/**********************************文件头部注释************************************/
//
//
//  					Copyright (C), 2005-2010, AV Frontier Tech. Co., Ltd.
//
//
// 文件名：		ywlib.h
//
// 创建者：
//
// 创建时间：	2007.12.15
//
// 文件描述：
//
// 修改记录：   日       期      作      者       版本      修定
//				       ---------         ---------        -----        -----
/*****************************************************************************************/

/************************************函数定义****************************************/

#ifndef __YWLIB_URL_H__
#define __YWLIB_URL_H__

//#include "ywevt.h"

#ifdef __cplusplus
extern "C" {
#endif

/*add by sly  start*/
typedef enum
{
	YWLIB_UNI_CONVERSION_OK, 		/* conversion successful */
	YWLIB_UNI_SOURCE_EXHAUSTED,	/* partial S8acter in source, but hit end */
	YWLIB_UNI_TARGET_EXHAUSTED,	/* insuff. room in target for conversion */
	YWLIB_UNI_SOURCE_ILLEGAL		/* source sequence is illegal/malformed */
} YWLIB_UNIConversionResult_T;

typedef enum
{
	YWLIB_UNI_STRICT_CONVERSION = 0,
	YWLIB_UNI_LENIENT_CONVERSION
} YWLIB_UNIConversionFlags_T;

YW_ErrorType_T YWPUBLIC_Utf8To16(const S8* in, S32 inLen, S8 *out, S32 outLen);
YW_ErrorType_T YWPUBLIC_Utf16To8(const S8* in, S32 inLen, S8 *out, S32 outLen);



#ifdef __cplusplus
}
#endif
#endif
