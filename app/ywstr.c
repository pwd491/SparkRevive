/*
 * File: ywstr.c    
 * Author:  
 * Brief: the definition of string funcions.
 * 
 */

/*
 * History:
 * ================================================================
 *
 */

#include "ywgui_ext.h"
#include "ywstr_id.h"
//26 kind Language
#include "ywstr_English.h"      // for english
#include "ywstr_German.h"      // for German
#include "ywstr_Greek.h"
#include "ywstr_Spanish.h"
#include "ywstr_Italian.h"
#include "ywstr_Portuguese.h"
#include "ywstr_Turkish.h"
#include "ywstr_Polish.h"
#include "ywstr_Russia.h"
#include "ywstr_Sweden.h"
#include "ywstr_Arabic.h"
#include "ywstr_French.h"
#include "ywstr_Czech.h"
#include "ywstr_Slovakian.h"
#include "ywstr_Danish.h"
#include "ywstr_Ukraine.h"
#include "ywstr_Hungarian.h"
#include "ywstr_Romanian.h"
#include "ywstr_Bulgarian.h"
#include "ywstr_Slovenian.h"
#include "ywstr_Bosnian.h"
#include "ywstr_Croatian.h"
#include "ywstr_Finland.h"
#include "ywstr_Indonesia.h"
#include "ywstr_Kurdish.h"
#include "ywstr_Persian.h"
#include "ywstr_Hebrew.h"
#include "ywstr_Latvian.h"
#include "ywstr_Serbian.h"
#include "ywstr_Nederland.h"
#include "ywstr_Lietuva.h"

#include "ywstring.h"




#define FIRST_STR_OFFSET    4

U8 *g_pStr_tbl = NULL;
YWRES_Language_T g_Language = {0};


/*交换字符编码的高低位字节*/
static S32 YWSTR_InvertCharCode(U8 *pStr, U32 nArraysize)
{
    U32 offset  = 0;
    U8  cTempChar = 0;
    U8  cBytNumPerChar = 0;

    cBytNumPerChar = pStr[1];
    offset = (pStr[FIRST_STR_OFFSET]<<8) + pStr[FIRST_STR_OFFSET+1] + 1;

    if(cBytNumPerChar == 2)
    {
        while(offset < nArraysize)
        {
            cTempChar = *(pStr+offset);
            *(pStr+offset) = *(pStr+offset+1);
            *(pStr+offset+1) = cTempChar;

            offset += 2;
        }
    }

    return 0;
}

void YWSTR_InitString()
{
    U32 nArraysize = 0;

    //english
    nArraysize = sizeof(English_strs_array);
    YWSTR_InvertCharCode((U8*)English_strs_array, nArraysize);

    //German
    nArraysize = sizeof(German_strs_array);
    YWSTR_InvertCharCode((U8*)German_strs_array, nArraysize);

    nArraysize = sizeof(Greek_strs_array);
    YWSTR_InvertCharCode((U8*)Greek_strs_array, nArraysize);

    nArraysize = sizeof(Russia_strs_array);
    YWSTR_InvertCharCode((U8*)Russia_strs_array, nArraysize);

    nArraysize = sizeof(Spanish_strs_array);
    YWSTR_InvertCharCode((U8*)Spanish_strs_array, nArraysize);

    nArraysize = sizeof(Italian_strs_array);
    YWSTR_InvertCharCode((U8*)Italian_strs_array, nArraysize);

    nArraysize = sizeof(Portuguese_strs_array);
    YWSTR_InvertCharCode((U8*)Portuguese_strs_array, nArraysize);

    nArraysize = sizeof(Turkish_strs_array);
    YWSTR_InvertCharCode((U8*)Turkish_strs_array, nArraysize);

    nArraysize = sizeof(Polish_strs_array);
    YWSTR_InvertCharCode((U8*)Polish_strs_array, nArraysize);

    nArraysize = sizeof(Finland_strs_array);
    YWSTR_InvertCharCode((U8*)Finland_strs_array, nArraysize);

    nArraysize = sizeof(Sweden_strs_array);
    YWSTR_InvertCharCode((U8*)Sweden_strs_array, nArraysize);

    nArraysize = sizeof(Arabic_strs_array);
    YWSTR_InvertCharCode((U8*)Arabic_strs_array, nArraysize);

    nArraysize = sizeof(French_strs_array);
    YWSTR_InvertCharCode((U8*)French_strs_array, nArraysize);

    nArraysize = sizeof(Czech_strs_array);
    YWSTR_InvertCharCode((U8*)Czech_strs_array, nArraysize);

    nArraysize = sizeof(Slovakian_strs_array);
    YWSTR_InvertCharCode((U8*)Slovakian_strs_array, nArraysize);

    nArraysize = sizeof(Danish_strs_array);
    YWSTR_InvertCharCode((U8*)Danish_strs_array, nArraysize);

    nArraysize = sizeof(Ukraine_strs_array);
    YWSTR_InvertCharCode((U8*)Ukraine_strs_array, nArraysize);

    nArraysize = sizeof(Persian_strs_array);
    YWSTR_InvertCharCode((U8*)Persian_strs_array, nArraysize);

    nArraysize = sizeof(Hungarian_strs_array);
    YWSTR_InvertCharCode((U8*)Hungarian_strs_array, nArraysize);

    nArraysize = sizeof(Romanian_strs_array);
    YWSTR_InvertCharCode((U8*)Romanian_strs_array, nArraysize);

    nArraysize = sizeof(Kurdish_strs_array);
    YWSTR_InvertCharCode((U8*)Kurdish_strs_array, nArraysize);

    nArraysize = sizeof(Bosnian_strs_array);
    YWSTR_InvertCharCode((U8*)Bosnian_strs_array, nArraysize);

    nArraysize = sizeof(Croatian_strs_array);
    YWSTR_InvertCharCode((U8*)Croatian_strs_array, nArraysize);

    nArraysize = sizeof(Bulgarian_strs_array);
    YWSTR_InvertCharCode((U8*)Bulgarian_strs_array, nArraysize);

    nArraysize = sizeof(Indonesia_strs_array);
    YWSTR_InvertCharCode((U8*)Indonesia_strs_array, nArraysize);

    nArraysize = sizeof(Slovenian_strs_array);
    YWSTR_InvertCharCode((U8*)Slovenian_strs_array, nArraysize);

    nArraysize = sizeof(Hebrew_strs_array);
    YWSTR_InvertCharCode((U8*)Hebrew_strs_array, nArraysize);

    nArraysize = sizeof(Latvian_strs_array);
    YWSTR_InvertCharCode((U8*)Latvian_strs_array, nArraysize);

    nArraysize = sizeof(Serbian_strs_array);
    YWSTR_InvertCharCode((U8*)Serbian_strs_array, nArraysize);

    nArraysize = sizeof(Nederland_strs_array);
    YWSTR_InvertCharCode((U8*)Nederland_strs_array, nArraysize);

    nArraysize = sizeof(Lietuva_strs_array);
    YWSTR_InvertCharCode((U8*)Lietuva_strs_array, nArraysize);

}

S32 YWSTR_SetLanguage(YWRES_Language_T stLanguage)
{
    if((stLanguage >= LANGUAGE_COUNT) || (stLanguage == LANGUAGE_NULL))
    {
        return -1;
    }

    switch(stLanguage)
    {
        case LANGUAGE_ENGLISH: //english
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)English_strs_array;
        	break;

        case LANGUAGE_GERMAN: //German
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)German_strs_array;
        	break;

        case LANGUAGE_GREEK:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Greek_strs_array;
        	break;

        case LANGUAGE_RUSSIAN:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Russia_strs_array;
        	break;

        case LANGUAGE_SPANISH:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Spanish_strs_array;
        	break;

        case LANGUAGE_ITALIAN:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Italian_strs_array;
        	break;

        case LANGUAGE_PORTUGUESE:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Portuguese_strs_array;
        	break;

        case LANGUAGE_TURKISH:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Turkish_strs_array;
        	break;

        case LANGUAGE_POLISH:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Polish_strs_array;
        	break;

        case LANGUAGE_FIN:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Finland_strs_array;
        	break;

        case LANGUAGE_SWEDISH:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Sweden_strs_array;
        	break;

        case LANGUAGE_ARABIC:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Arabic_strs_array;
        	break;

        case LANGUAGE_FRENCH:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)French_strs_array;
        	break;

        case LANGUAGE_CZECH:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Czech_strs_array;
        	break;

        case LANGUAGE_SLOVAK:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Slovakian_strs_array;
        	break;

        case LANGUAGE_DANISH:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Danish_strs_array;
        	break;

        case LANGUAGE_UKRAINE:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Ukraine_strs_array;
        	break;

        case LANGUAGE_PERSIAN:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Persian_strs_array;
        	break;

        case LANGUAGE_HUNGARIAN:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Hungarian_strs_array;
        	break;

        case LANGUAGE_ROMANIAN:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Romanian_strs_array;
        	break;

        case LANGUAGE_KURDISH:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Kurdish_strs_array;
        	break;

        case LANGUAGE_BOSNIAN:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Bosnian_strs_array;
        	break;

        case LANGUAGE_CROATIAN:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Croatian_strs_array;
        	break;

        case LANGUAGE_BULGARIAN:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Bulgarian_strs_array;
        	break;

        case LANGUAGE_INDONESIA:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Indonesia_strs_array;
        	break;

        case LANGUAGE_SLV:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Slovenian_strs_array;
        	break;

        case LANGUAGE_HEBREW:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Hebrew_strs_array;
        	break;

        case LANGUAGE_LATVIAN:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Latvian_strs_array;
        	break;

        case LANGUAGE_SERBIAN:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Serbian_strs_array;
        	break;

        case LANGUAGE_NEDERLAND:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Nederland_strs_array;
        	break;

        case LANGUAGE_LIT:
            g_Language = stLanguage;
            g_pStr_tbl = (U8*)Lietuva_strs_array;
            break;

        default:
            return -1;
            break;
    }

    return 0;
}

YWRES_Language_T YWSTR_GetLanguage(void)
{
    return g_Language;
}

/*得到菜单语言种类的字符串。不同的菜单语言将用不同的语言表示*/
YWGUI_Char_T *YWSTR_GetMenuLangString(YWRES_Language_T stLanguage)
{
    U32 wIndex = 0;
    U8 *pStrtbl = NULL;
    U32 noffset  = 0;
    if(stLanguage <= LANGUAGE_NULL || stLanguage >= LANGUAGE_COUNT)
    {
        return (YWGUI_Char_T *)"\x0";
    }
    else
    {
        switch(stLanguage)
        {
            case LANGUAGE_ENGLISH: //english
                pStrtbl = English_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_GERMAN: //German
                pStrtbl = German_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_GREEK:
                pStrtbl = Greek_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_RUSSIAN:
                pStrtbl = Russia_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_SPANISH:
                pStrtbl = Spanish_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_ITALIAN:
                pStrtbl = Italian_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_PORTUGUESE:
                pStrtbl = Portuguese_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_TURKISH:
                pStrtbl = Turkish_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_POLISH:
                pStrtbl = Polish_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_FIN:
                pStrtbl = Finland_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_SWEDISH:
                pStrtbl = Sweden_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_ARABIC:
                pStrtbl = Arabic_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_FRENCH:
                pStrtbl = French_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_CZECH:
                pStrtbl = Czech_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_SLOVAK:
                pStrtbl = Slovakian_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_DANISH:
                pStrtbl = Danish_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_UKRAINE:
                pStrtbl = Ukraine_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_PERSIAN:
                pStrtbl = Persian_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_HUNGARIAN:
                pStrtbl = Hungarian_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_ROMANIAN:
                pStrtbl = Romanian_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_KURDISH:
                pStrtbl = Kurdish_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_BOSNIAN:
                pStrtbl = Bosnian_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_CROATIAN:
                pStrtbl = Croatian_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_BULGARIAN:
                pStrtbl = Bulgarian_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_INDONESIA:
                pStrtbl = Indonesia_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

            case LANGUAGE_SLV:
                pStrtbl = Slovenian_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
            	break;

		    case LANGUAGE_HEBREW:
                pStrtbl = Hebrew_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
		    	break;

		    case LANGUAGE_LATVIAN:
                pStrtbl = Latvian_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
    			break;

		    case LANGUAGE_SERBIAN:
                pStrtbl = Serbian_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
		    	break;

		    case LANGUAGE_NEDERLAND:
                pStrtbl = Nederland_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
		    	break;

            case LANGUAGE_LIT:
                pStrtbl = Lietuva_strs_array;
                wIndex = STR_LANGUAGE_TYPE - STR_ID_BASE - 1;
                noffset = (pStrtbl[FIRST_STR_OFFSET+2*wIndex]<<8) + pStrtbl[FIRST_STR_OFFSET+2*wIndex+1];
                return (YWGUI_Char_T *)&pStrtbl[noffset+1];
                break;

            default:
                return (YWGUI_Char_T *)"\x0";
                break;
        }
    }
    return (YWGUI_Char_T *)"\x0";
}

YWGUI_Char_T *YWSTR_GetString(S32 id)
{
    U32 wIndex = 0;
    U32 noffset  = 0;
    U32 nStrNum = 0;

    if(id < STR_ID_BASE || id >= STR_MAX || g_pStr_tbl==NULL)
    {
        return NULL;
    }
    else
    {
        if(id == STR_ID_BASE)
        {
            return (YWGUI_Char_T *)"\x0";
        }
        else
        {
            nStrNum = (g_pStr_tbl[2]<<8) + g_pStr_tbl[3];
            wIndex = id - STR_ID_BASE - 1;
            if(wIndex >= nStrNum)
                return NULL;

            noffset = (g_pStr_tbl[FIRST_STR_OFFSET+2*wIndex]<<8) + g_pStr_tbl[FIRST_STR_OFFSET+2*wIndex+1];
			
			return (YWGUI_Char_T *)&g_pStr_tbl[noffset+1];
        }
    }
}



