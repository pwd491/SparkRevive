



#ifndef ___YWIPTV__H___
#define ___YWIPTV__H___


#define XML_ELEMENT_WEBTVS 		"webtvs"
#define XML_ELEMENT_WEBTV 		"webtv"

#define ATTR_WEBTV_TITLE 		"title"
#define ATTR_WEBTV_URL 			"url"
#define ATTR_WEBTV_DESCRIPTION 	"description"
#define ATTR_WEBTV_TYPE 		"type"

#define WEBTV_XML_PATH 			"/var/etc/"
#define WEBTV_XML_FILE			"webtv.xml"


#define TITLE_LEN 64
#define URL_LEN 256
#define DESCRIPTION_LEN 256


typedef enum
{
	WEBTV_PLAY = 1,
	WEBTV_PAUSE,
	WEBTV_STOP,
}YW_WEBTV_PLAYSTATUS_T;


typedef struct YW_WEBTV_Node_s
{
	YWLIB_ListHead_T list;

    char title[TITLE_LEN];
	char url[URL_LEN];
	char description[DESCRIPTION_LEN];
	char mediatype;
}YW_WEBTV_Node_t;

typedef struct YW_WEBTV_Info_s
{
    int num;
	YWLIB_ListHead_T  listhead;
}YW_WEBTV_Info_t;


YWGUI_HWnd_T YWIpTv_CreateWindow(YWGUI_HWnd_T hHost);



#endif



