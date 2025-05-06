/*$Source: D:/STB_PROD_APP/plugin_sdk/inc/ywstring.h,v $*/
/*****************************文件头部注释*************************************/
//
//			Copyright (C), 2009-2014, AV Frontier Tech. Co., Ltd.
//
//
// 文 件 名：	$RCSfile: ywstring.h,v $
//
// 创 建 者：	D26LF
//
// 创建时间：	2009.12.09
//
// 最后更新：	$Date: 2012/03/27 10:45:54 $
//
//				$Author: D60NXF $
//
//				$Revision: 1.1 $
//
//				$State: Exp $
//
// 文件描述：	图片解码模块
//
/******************************************************************************/

#ifndef __YWLANGUAGE_EXT_H
#define __YWLANGUAGE_EXT_H

/********************************  文件包含************************************/


#ifdef __cplusplus
extern "C" {
#endif


/********************************  常量定义************************************/
typedef enum YWRES_Language_e
{
    LANGUAGE_NULL = 0,   //null
    LANGUAGE_ENGLISH,        //英语
    LANGUAGE_GERMAN,        //德语
    LANGUAGE_GREEK,         //希腊语
    LANGUAGE_RUSSIAN,       //俄语
    LANGUAGE_SPANISH,       //西班牙语
    LANGUAGE_ITALIAN,//意大利语
    LANGUAGE_PORTUGUESE,//葡萄牙语
    LANGUAGE_TURKISH,    //土耳其语
    LANGUAGE_POLISH,        //波兰语
    LANGUAGE_FIN,			//芬兰
    LANGUAGE_SWEDISH,       //瑞典语
    LANGUAGE_ARABIC,        //阿拉伯语
    LANGUAGE_FRENCH,        //法语
    LANGUAGE_CZECH,         //捷克斯洛伐克语
    LANGUAGE_SLOVAK,//斯洛伐克语
    LANGUAGE_DANISH,//丹麦语
    LANGUAGE_UKRAINE,       //乌克兰语
    LANGUAGE_PERSIAN,		//波斯人语
    LANGUAGE_HUNGARIAN,     //匈牙利语
    LANGUAGE_ROMANIAN,      //罗马尼亚语
    LANGUAGE_KURDISH,       //库尔德语
    LANGUAGE_BOSNIAN,       //波斯尼亚语
    LANGUAGE_CROATIAN,//克罗地亚语
    LANGUAGE_BULGARIAN,     //保加利亚语
    LANGUAGE_INDONESIA,       //印尼
    LANGUAGE_SLV ,//斯洛文尼亚语
    LANGUAGE_HEBREW,//希伯来语
    LANGUAGE_LATVIAN,   //拉脱维亚语
    LANGUAGE_SERBIAN,   //塞尔维亚人语
    LANGUAGE_NEDERLAND, //荷兰语
    LANGUAGE_LIT ,//立陶宛

 /*   LANGUAGE_NORWEGIAN,     //挪威布克莫尔语
    LANGUAGE_INDIA,              //印度语
    LANGUAGE_VIETNA,            //越南语
    LANGUAGE_ESTONIAN,//爱桑尼亚语
    LANGUAGE_JAPANESE,//日语
    LANGUAGE_CHANISE,
    LANGUAGE_CATALAN,//巴伦西亚语*/
    LANGUAGE_COUNT          //语言总数
}YWRES_Language_T;



void YWSTR_InitString();
S32 YWSTR_SetLanguage(YWRES_Language_T stLanguage);

YWRES_Language_T YWSTR_GetLanguage(void);

/*得到菜单语言种类的字符串。不同的菜单语言将用不同的语言表示*/
YWGUI_Char_T *YWSTR_GetMenuLangString(YWRES_Language_T stLanguage);

YWGUI_Char_T *YWSTR_GetString(S32 id);




#ifdef __cplusplus
}
#endif


#endif  /* __YWIMG_EXT_H */
/* EOF------------------------------------------------------------------------*/

/* BOL-------------------------------------------------------------------*/

/* EOL-------------------------------------------------------------------*/

