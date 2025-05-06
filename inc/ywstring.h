/*$Source: D:/STB_PROD_APP/plugin_sdk/inc/ywstring.h,v $*/
/*****************************�ļ�ͷ��ע��*************************************/
//
//			Copyright (C), 2009-2014, AV Frontier Tech. Co., Ltd.
//
//
// �� �� ����	$RCSfile: ywstring.h,v $
//
// �� �� �ߣ�	D26LF
//
// ����ʱ�䣺	2009.12.09
//
// �����£�	$Date: 2012/03/27 10:45:54 $
//
//				$Author: D60NXF $
//
//				$Revision: 1.1 $
//
//				$State: Exp $
//
// �ļ�������	ͼƬ����ģ��
//
/******************************************************************************/

#ifndef __YWLANGUAGE_EXT_H
#define __YWLANGUAGE_EXT_H

/********************************  �ļ�����************************************/


#ifdef __cplusplus
extern "C" {
#endif


/********************************  ��������************************************/
typedef enum YWRES_Language_e
{
    LANGUAGE_NULL = 0,   //null
    LANGUAGE_ENGLISH,        //Ӣ��
    LANGUAGE_GERMAN,        //����
    LANGUAGE_GREEK,         //ϣ����
    LANGUAGE_RUSSIAN,       //����
    LANGUAGE_SPANISH,       //��������
    LANGUAGE_ITALIAN,//�������
    LANGUAGE_PORTUGUESE,//��������
    LANGUAGE_TURKISH,    //��������
    LANGUAGE_POLISH,        //������
    LANGUAGE_FIN,			//����
    LANGUAGE_SWEDISH,       //�����
    LANGUAGE_ARABIC,        //��������
    LANGUAGE_FRENCH,        //����
    LANGUAGE_CZECH,         //�ݿ�˹�工����
    LANGUAGE_SLOVAK,//˹�工����
    LANGUAGE_DANISH,//������
    LANGUAGE_UKRAINE,       //�ڿ�����
    LANGUAGE_PERSIAN,		//��˹����
    LANGUAGE_HUNGARIAN,     //��������
    LANGUAGE_ROMANIAN,      //����������
    LANGUAGE_KURDISH,       //�������
    LANGUAGE_BOSNIAN,       //��˹������
    LANGUAGE_CROATIAN,//���޵�����
    LANGUAGE_BULGARIAN,     //����������
    LANGUAGE_INDONESIA,       //ӡ��
    LANGUAGE_SLV ,//˹����������
    LANGUAGE_HEBREW,//ϣ������
    LANGUAGE_LATVIAN,   //����ά����
    LANGUAGE_SERBIAN,   //����ά������
    LANGUAGE_NEDERLAND, //������
    LANGUAGE_LIT ,//������

 /*   LANGUAGE_NORWEGIAN,     //Ų������Ī����
    LANGUAGE_INDIA,              //ӡ����
    LANGUAGE_VIETNA,            //Խ����
    LANGUAGE_ESTONIAN,//��ɣ������
    LANGUAGE_JAPANESE,//����
    LANGUAGE_CHANISE,
    LANGUAGE_CATALAN,//����������*/
    LANGUAGE_COUNT          //��������
}YWRES_Language_T;



void YWSTR_InitString();
S32 YWSTR_SetLanguage(YWRES_Language_T stLanguage);

YWRES_Language_T YWSTR_GetLanguage(void);

/*�õ��˵�����������ַ�������ͬ�Ĳ˵����Խ��ò�ͬ�����Ա�ʾ*/
YWGUI_Char_T *YWSTR_GetMenuLangString(YWRES_Language_T stLanguage);

YWGUI_Char_T *YWSTR_GetString(S32 id);




#ifdef __cplusplus
}
#endif


#endif  /* __YWIMG_EXT_H */
/* EOF------------------------------------------------------------------------*/

/* BOL-------------------------------------------------------------------*/

/* EOL-------------------------------------------------------------------*/

