/*
 * File: rename.c    
 * Author:  
 * Brief: the definition of rename window.
 * 
 */

/*
 * History:
 * ================================================================
 *
 */

#include "ywdefs.h"
#include "ywos.h"
#include "ywlib.h"
#include "ywmid.h"
#include "ywgui_ext.h"
#include "res_layout.h"
#include "gui.h"
#include "general.h"



#define PLUGIN_CHAR_EXTRA                 3
#define PLUGIN_RENAME_DISP_CONTENT_LEN    800
#define PLUGIN_RENAME_CONTENT_LIMIT_LEN        200

#define PLUGIN_RENAME_CURSOR '|'
#define PLUGIN_RENAME_SPACE  ' '


#define TIMER_SECONDS 0xff
typedef struct YWREAME_EditContentInfo_s
{
    S32             s32ContentLen;
    S32             s32DisplayStartPos;          //from 0
    S32             s32DisplayEndPos;            //from 0
    S32             s32CursorPos;

}YWRENAME_EditContentInfo_T;


static YWRENAME_EditContentInfo_T g_tPluginRenameContentInfo;
static YWPLUGINREAME_Param_T g_tPluginRenameParam;
static YWGUI_Char_T g_aPluginRenameEditContent[256];



static const S32 pRenameKeyValue[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '-', '!',
    '?', '<', '>', '{', '}', '\'','"', ':', ';', '+', '-', '=', '~',
    '(', ')', '@', '_', '#', '+', '&', '/', '\\',/* '[', ']',*/
    };

static BOOL g_Flash = TRUE;


static void YWPluginRenamei_SetDisplayFlash(BOOL bFlash)
{
    g_Flash = bFlash;
}



static BOOL YWPluginRenamei_GetDisplayFlash(void)
{
    return g_Flash;
}



static YWGUI_Char_T* YWPluginRenamei_DeletWchar(YWGUI_Char_T *pstr, S32 nPos)
{
//	if(nPos >= YWLIB_Wstrlen(pstr))
//			return pstr;

    YWLIB_Wstrcpy(&pstr[nPos], &pstr[nPos+1]);

    return pstr;

}

static YWGUI_Char_T* YWPluginRenamei_InsertWchar(YWGUI_Char_T *pstr, S32 nPos, YWGUI_Char_T Wchar)
{
    YWGUI_Char_T aWstr[256];

    YWLIB_Memset(aWstr, 0, sizeof(aWstr));

    YWLIB_Wstrcpy(aWstr, pstr);
    pstr[nPos] = Wchar;
    YWLIB_Wstrcpy(&pstr[nPos+1], &aWstr[nPos]);

    return pstr;
}

static YWGUI_Char_T* YWPluginRenamei_ReplaceWchar(YWGUI_Char_T *pstr, S32 nPos, YWGUI_Char_T Wchar)
{
    pstr[nPos] = Wchar;
    return pstr;
}

static BOOL YWPluginRenamei_IsStrDisplay(YWGUI_Handle_T hWnd, YWRENAME_EditContentInfo_T *ptContentInfo, YWGUI_Char_T *pStr, S32 nEditWidth)
{
    YWGUI_HDc_T hdc;
    YWGUI_Char_T WstrTemp[256];
    YWGUI_Extent_T stExtent = {0, 0};

    YWLIB_Memset(WstrTemp, 0, sizeof(WstrTemp));

    YWLIB_Wstrncpy(WstrTemp, (pStr+ptContentInfo->s32DisplayStartPos), (ptContentInfo->s32DisplayEndPos-ptContentInfo->s32DisplayStartPos+1));


    hdc = YWGUI_GetClientDC(hWnd);

    YWGUI_SetTextCharExtra(hdc, PLUGIN_CHAR_EXTRA);
    YWGUI_GetTextExtent(hdc, WstrTemp, -1, &stExtent);

    YWGUI_ReleaseDC(hdc);

 //   YWAPP_TRACE((YWOS_TRACE_INFO, "stExtent.cx : %d, nEditWidth: %d\n", stExtent.cx, nEditWidth));

    if(stExtent.cx <= nEditWidth)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static void YWPluginRenamei_TidyUpTheEditContent(YWGUI_Handle_T hWnd, YWRENAME_EditContentInfo_T *ptContentInfo, YWGUI_Char_T *pStr, S32 nEditWidth, BOOL bSartPosMov)
{
    if(YWPluginRenamei_IsStrDisplay(hWnd, ptContentInfo, pStr, nEditWidth))
        return;

    if(bSartPosMov)
    {
        ptContentInfo->s32DisplayStartPos++;
    }
    else
    {
        ptContentInfo->s32DisplayEndPos--;
    }

    while(!YWPluginRenamei_IsStrDisplay(hWnd, ptContentInfo, pStr, nEditWidth))
    {
        if(bSartPosMov)
        {
            ptContentInfo->s32DisplayStartPos++;
        }
        else
        {
            ptContentInfo->s32DisplayEndPos--;
        }

        if(ptContentInfo->s32DisplayStartPos == ptContentInfo->s32DisplayEndPos) //应该不会出现这种情况
            return;
    }
}

static void YWPluginRenamei_MoveCtrlCursor2Start(YWGUI_Handle_T hWnd, YWRENAME_EditContentInfo_T *ptContentInfo, YWGUI_Char_T *pStr, S32 nEditWidth)
{
    YWPluginRenamei_DeletWchar(pStr, ptContentInfo->s32CursorPos);
	YWPluginRenamei_InsertWchar(pStr, 0, PLUGIN_RENAME_CURSOR);

    ptContentInfo->s32DisplayStartPos = 0;
    ptContentInfo->s32DisplayEndPos = ptContentInfo->s32ContentLen-1;
    ptContentInfo->s32CursorPos = 0;

	YWPluginRenamei_TidyUpTheEditContent(hWnd, ptContentInfo, pStr, nEditWidth, FALSE);

    return;
}
/*****************************************************************************/
//	函数名称:	YWGENERAL_MoveCtrlCursor2End
//	函数说明:	将光标移到最后的位置
//	算法说明:	NA
//	输入参数:	pstr : 操作的控件内容字符串  ptContentInfo:控件内容相关信息  nEditWidth :编辑框宽度
//	输出参数:	NA
//	返 回 值:	NA
//	修改记录:	日       期      作      者       修 定
//           	-----------      ----------      -------
//             2010年01月11日      d60nxf          新 建
/*****************************************************************************/
static void YWPluginRenamei_MoveCtrlCursor2End(YWGUI_Handle_T hWnd, YWRENAME_EditContentInfo_T *ptContentInfo, YWGUI_Char_T *pStr, S32 nEditWidth)
{
    YWPluginRenamei_DeletWchar(pStr, ptContentInfo->s32CursorPos);
	YWPluginRenamei_InsertWchar(pStr, ptContentInfo->s32ContentLen-1, PLUGIN_RENAME_CURSOR);

    ptContentInfo->s32DisplayStartPos = 0;
    ptContentInfo->s32DisplayEndPos = ptContentInfo->s32ContentLen-1;
    ptContentInfo->s32CursorPos = ptContentInfo->s32ContentLen-1;;

	YWPluginRenamei_TidyUpTheEditContent(hWnd, ptContentInfo, pStr, nEditWidth, TRUE);

    return;
}


/*****************************************************************************/
//	函数名称:	YWGENERAL_LeftMoveCtrlCursor
//	函数说明:	左移控件中的光标
//	算法说明:	NA
//	输入参数:	pstr : 操作的控件内容字符串  ptContentInfo:控件内容相关信息  nEditWidth :编辑框宽度
//	输出参数:	NA
//	返 回 值:	NA
//	修改记录:	日       期      作      者       修 定
//           	-----------      ----------      -------
//             2010年01月11日      d60nxf          新 建
/*****************************************************************************/
static void YWPluginRenamei_LeftMoveCtrlCursor(YWGUI_Handle_T hWnd, YWRENAME_EditContentInfo_T *ptContentInfo, YWGUI_Char_T *pStr, S32 nEditWidth)
{
    YWGUI_Char_T Wchar;

    if(ptContentInfo->s32CursorPos == 0)
    {
        YWGUI_Char_T aWstr[256];

        YWLIB_Memset(aWstr, 0, sizeof(aWstr));
        YWLIB_Wstrcpy(aWstr, pStr);
        YWLIB_Wstrcpy(pStr, &aWstr[1]);
        pStr[ptContentInfo->s32ContentLen-1] = PLUGIN_RENAME_CURSOR;

        ptContentInfo->s32CursorPos = ptContentInfo->s32ContentLen-1;
        ptContentInfo->s32DisplayEndPos = ptContentInfo->s32ContentLen-1;

        if(YWPluginRenamei_IsStrDisplay(hWnd, ptContentInfo, pStr, nEditWidth))
        {
           return ;
        }
        else
        {
            YWPluginRenamei_TidyUpTheEditContent(hWnd, ptContentInfo, pStr, nEditWidth, TRUE);
            return ;
        }

    }

    Wchar = pStr[ptContentInfo->s32CursorPos-1];
    pStr[ptContentInfo->s32CursorPos-1] = pStr[ptContentInfo->s32CursorPos];
    pStr[ptContentInfo->s32CursorPos] = Wchar;

    ptContentInfo->s32CursorPos--;

    if(ptContentInfo->s32CursorPos >= ptContentInfo->s32DisplayStartPos)    //光标还没有到显示字符串开始的位置
    {
        return ;
    }
    else    //光标位置已经小于显示字符串开始的位置
    {
        BOOL bArriveEnd = FALSE;
        ptContentInfo->s32DisplayStartPos--;
        ptContentInfo->s32DisplayEndPos--;

        while(!YWPluginRenamei_IsStrDisplay(hWnd, ptContentInfo, pStr, nEditWidth))   //移出一个窄点的字符，移进一个宽一点的字符
        {
            ptContentInfo->s32DisplayEndPos--;
        }

        while(YWPluginRenamei_IsStrDisplay(hWnd, ptContentInfo, pStr, nEditWidth))  //移出一个宽一点的字符，移进一个窄一点的字符
        {
            if(ptContentInfo->s32DisplayStartPos == 0)   //移到了最后
            {
                bArriveEnd = TRUE;
                break;
            }
            ptContentInfo->s32DisplayStartPos--;
        }
        if(bArriveEnd)
            return;
        else                            //如果没有移动到字符串最开始位置而退出，则需要将开始位置后移动一位
            ptContentInfo->s32DisplayStartPos++;
    }

    return;
}

/*****************************************************************************/
//	函数名称:	YWGENERAL_RightMoveCtrlCursor
//	函数说明:	右移控件中的光标
//	算法说明:	NA
//	输入参数:	pstr : 操作的控件内容字符串  ptContentInfo:控件内容相关信息  nEditWidth :编辑框宽度
//	输出参数:	NA
//	返 回 值:	NA
//	修改记录:	日       期      作      者       修 定
//           	-----------      ----------      -------
//             2010年01月11日      d60nxf          新 建
/*****************************************************************************/
static void YWPluginRenamei_RightMoveCtrlCursor(YWGUI_Handle_T hWnd, YWRENAME_EditContentInfo_T *ptContentInfo, YWGUI_Char_T *pStr, S32 nEditWidth)
{
    YWGUI_Char_T Wchar;

    if(ptContentInfo->s32CursorPos == ptContentInfo->s32ContentLen-1)    //光标已经到字符串的最后
    {
        YWGUI_Char_T aWstr[256];

        YWLIB_Memset(aWstr, 0, sizeof(aWstr));
        YWLIB_Wstrcpy(aWstr, pStr);
        YWLIB_Wstrncpy(&pStr[1], aWstr, ptContentInfo->s32ContentLen-1);
        pStr[0] = PLUGIN_RENAME_CURSOR;

        ptContentInfo->s32CursorPos = 0;
        ptContentInfo->s32DisplayStartPos = 0;

        if(YWPluginRenamei_IsStrDisplay(hWnd, ptContentInfo, pStr, nEditWidth))
        {
           return ;
        }
        else
        {
            YWPluginRenamei_TidyUpTheEditContent(hWnd, ptContentInfo, pStr, nEditWidth, FALSE);
            return ;
        }

    }
    else
    {
        Wchar = pStr[ptContentInfo->s32CursorPos+1];
        pStr[ptContentInfo->s32CursorPos+1] = pStr[ptContentInfo->s32CursorPos];
        pStr[ptContentInfo->s32CursorPos] = Wchar;

        ptContentInfo->s32CursorPos++;

        if(ptContentInfo->s32CursorPos <= ptContentInfo->s32DisplayEndPos)    //光标还没有到显示字符串结束的位置
        {
            return ;
        }
        else    //光标已经大于显示字符串结束的位置
        {
            BOOL bArriveEnd = FALSE;
            ptContentInfo->s32DisplayStartPos++;
            ptContentInfo->s32DisplayEndPos++;

            while(!YWPluginRenamei_IsStrDisplay(hWnd, ptContentInfo, pStr, nEditWidth))   //移出一个窄点的字符，移进一个宽一点的字符
            {
                ptContentInfo->s32DisplayStartPos++;
            }

            while(YWPluginRenamei_IsStrDisplay(hWnd, ptContentInfo, pStr, nEditWidth))  //移出一个宽一点的字符，移进一个窄一点的字符
            {
                if(ptContentInfo->s32DisplayEndPos == ptContentInfo->s32ContentLen-1)   //移到了最后
                {
                    bArriveEnd = TRUE;
                    break;
                }
                ptContentInfo->s32DisplayEndPos++;
            }
            if(bArriveEnd)
                return;
            else
                ptContentInfo->s32DisplayEndPos--;
        }
    }

    return;
}


/*****************************************************************************/
//	函数名称:	YWGENERAL_DeleteWcharToEditCtrl
//	函数说明:	删除控件中的字符
//	算法说明:	NA
//	输入参数:	pstr : 操作的控件内容字符串  ptContentInfo:控件内容相关信息  nEditWidth :编辑框宽度
//	输出参数:	NA
//	返 回 值:	NA
//	修改记录:	日       期      作      者       修 定
//           	-----------      ----------      -------
//             2010年01月11日      d60nxf          新 建
/*****************************************************************************/
static void YWPluginRenamei_DeleteWcharFromEditCtrl(YWGUI_Handle_T hWnd, YWRENAME_EditContentInfo_T *ptContentInfo, YWGUI_Char_T *pStr, S32 nEditWidth)
{
    if(ptContentInfo->s32CursorPos == 0)
    {
        return ;
    }

    YWPluginRenamei_DeletWchar(pStr, ptContentInfo->s32CursorPos-1);
    ptContentInfo->s32CursorPos--;
    ptContentInfo->s32ContentLen--;
    ptContentInfo->s32DisplayEndPos--;

    if(ptContentInfo->s32CursorPos > ptContentInfo->s32DisplayStartPos)    //光标还没有到显示字符串开始的位置
    {
        if((ptContentInfo->s32ContentLen-1) == ptContentInfo->s32DisplayEndPos)
        {
            return;
        }
        else
        {
            ptContentInfo->s32DisplayEndPos++;

            while(YWPluginRenamei_IsStrDisplay(hWnd, ptContentInfo, pStr, nEditWidth)) //如果移进来的字符是个窄一点的字符
            {
                if((ptContentInfo->s32ContentLen-1) == ptContentInfo->s32DisplayEndPos)  //显示字符串已经移动到最后一个字符
                {
                    return;
                }

                ptContentInfo->s32DisplayEndPos++;
            }
            ptContentInfo->s32DisplayEndPos--;
        }
    }
    else    //光标已经到显示字符串开始的位置
    {
        BOOL bArriveEnd = FALSE;

        while(YWPluginRenamei_IsStrDisplay(hWnd, ptContentInfo, pStr, nEditWidth))  //移出一个宽一点的字符，移进一个窄一点的字符
        {
            if(ptContentInfo->s32DisplayStartPos == 0)   //移到了最后
            {
                bArriveEnd = TRUE;
                break;
            }
            ptContentInfo->s32DisplayStartPos--;
        }

        if(bArriveEnd)
            return;
        else                  //如果没有移动到字符串最开始位置而退出，则需要将开始位置后移动一位
            ptContentInfo->s32DisplayStartPos++;
    }

    return ;
}

/*****************************************************************************/
//	函数名称:	YWGENERALi_InsertWcharToEditCtrl
//	函数说明:	向控件插入字符
//	算法说明:	NA
//	输入参数:	pstr : 操作的控件内容字符串  ptContentInfo:控件内容相关信息
//              Wchar:要插入的字符           nEditWidth : 编辑框宽度
//	输出参数:	NA
//	返 回 值:	NA
//	修改记录:	日       期      作      者       修 定
//           	-----------      ----------      -------
//             2010年01月11日      d60nxf          新 建
/*****************************************************************************/
static void YWPluginRenamei_InsertWcharToEditCtrl(YWGUI_Handle_T hWnd, YWRENAME_EditContentInfo_T *ptContentInfo, YWGUI_Char_T *pStr, YWGUI_Char_T Wchar, S32 nEditWidth)
{
    YWPluginRenamei_InsertWchar(pStr, ptContentInfo->s32CursorPos, Wchar);



  /*  if(ptContentInfo->s32CursorPos < ptContentInfo->s32DisplayEndPos)  //如果光标不在显示字符串的最后一位
    {
        */
        ptContentInfo->s32CursorPos++;
        ptContentInfo->s32ContentLen++;
        ptContentInfo->s32DisplayEndPos++;

        if(YWPluginRenamei_IsStrDisplay(hWnd, ptContentInfo, pStr, nEditWidth))
            return;

        if(ptContentInfo->s32CursorPos == ptContentInfo->s32DisplayEndPos)  //如果光标已经到最后一位
        {
            ptContentInfo->s32DisplayStartPos++;                            //则要从开始显示字符的位置移出去
        }
        else
        {
            ptContentInfo->s32DisplayEndPos--;                                      //考虑把最后的字符移出去
        }

        while(!YWPluginRenamei_IsStrDisplay(hWnd, ptContentInfo, pStr, nEditWidth))   //如果移出去的字符是个窄一点的字符，
        {
            if(ptContentInfo->s32CursorPos == ptContentInfo->s32DisplayEndPos)  //如果光标已经到最后一位
            {
                ptContentInfo->s32DisplayStartPos++;                            //则要从开始显示字符的位置移出去
            }
            else
            {
                ptContentInfo->s32DisplayEndPos--;                              //把最后的字符移出去
            }

        }
  /*  }
    else    //如果光标在显示字符串的最后一位
    {
        ptContentInfo->s32CursorPos++;
        ptContentInfo->s32ContentLen++;
        ptContentInfo->s32DisplayEndPos++;

        if(YWPluginRenamei_IsStrDisplay(hWnd, ptContentInfo, pStr, nEditWidth))
            return;

        ptContentInfo->s32DisplayStartPos++;
        while(!YWPluginRenamei_IsStrDisplay(hWnd, ptContentInfo, pStr, nEditWidth))
        {
            ptContentInfo->s32DisplayStartPos++;
        }
    }*/
    return;
}

/*****************************************************************************/
//	函数名称:	YWGENERAL_RePlaceWcharToEditCtrl
//	函数说明:	替换控件中光标前面的一个字符
//	算法说明:	NA
//	输入参数:	pstr : 操作的控件内容字符串  ptContentInfo:控件内容相关信息
//              Wchar:要替换的字符           nEditWidth : 编辑框宽度
//	输出参数:	NA
//	返 回 值:	NA
//	修改记录:	日       期      作      者       修 定
//           	-----------      ----------      -------
//             2010年01月11日      d60nxf          新 建
/*****************************************************************************/
static void YWPluginRenamei_RePlaceWcharToEditCtrl(YWGUI_Handle_T hWnd, YWRENAME_EditContentInfo_T *ptContentInfo, YWGUI_Char_T *pStr, YWGUI_Char_T Wchar, S32 nEditWidth)
{
    if(ptContentInfo->s32CursorPos == 0)
        return;

    YWPluginRenamei_ReplaceWchar(pStr, ptContentInfo->s32CursorPos-1, Wchar);


    if(YWPluginRenamei_IsStrDisplay(hWnd, ptContentInfo, pStr, nEditWidth))
        return;

    if(ptContentInfo->s32CursorPos == ptContentInfo->s32DisplayEndPos)  //如果光标已经到最后一位
    {
        ptContentInfo->s32DisplayStartPos++;                            //则要从开始显示字符的位置移出去
    }
    else
    {
        ptContentInfo->s32DisplayEndPos--;                                      //考虑把最后的字符移出去
    }

    while(!YWPluginRenamei_IsStrDisplay(hWnd, ptContentInfo, pStr, nEditWidth))   //如果移出去的字符是个窄一点的字符，
    {
        if(ptContentInfo->s32CursorPos == ptContentInfo->s32DisplayEndPos)  //如果光标已经到最后一位
        {
            ptContentInfo->s32DisplayStartPos++;                            //则要从开始显示字符的位置移出去
        }
        else
        {
            ptContentInfo->s32DisplayEndPos--;                              //把最后的字符移出去
        }

    }

    return;
}
/*****************************************************************************/
//	函数名称:	YWGENERAL_ClearEditContent
//	函数说明:	清空编辑框的内容
//
//	算法说明:	NA
//	输入参数:	pstr : 操作的控件内容字符串  ptContentInfo:控件内容相关信息  hEdit:编辑控件句柄
//	输出参数:	NA
//	返 回 值:	NA
//	修改记录:	日       期      作      者       修 定
//           	-----------      ----------      -------
//             2010年01月11日      d60nxf          新 建
/*****************************************************************************/
static void YWPluginRenamei_ClearEditContent(YWRENAME_EditContentInfo_T *ptContentInfo, YWGUI_Char_T *pStr)
{

    S32 StrLen;

    StrLen = YWLIB_Wstrlen(pStr);
    YWLIB_Memwset(pStr, 0x0, StrLen);
    pStr[0] = PLUGIN_RENAME_CURSOR;

    ptContentInfo->s32ContentLen = 1;
    ptContentInfo->s32DisplayStartPos = 0;
    ptContentInfo->s32DisplayEndPos = 0;
    ptContentInfo->s32CursorPos = 0;
}


/*****************************************************************************/
//	函数名称:	YWGENERALi_DisplayEditContent
//	函数说明:	根据编辑框信息，显示编辑框字符
//	算法说明:	NA
//	输入参数:	pstr : 操作的控件内容字符串  ptContentInfo:控件内容相关信息  hEdit:控件句柄
//	输出参数:	NA
//	返 回 值:	NA
//	修改记录:	日       期      作      者       修 定
//           	-----------      ----------      -------
//             2010年01月11日      d60nxf          新 建
/*****************************************************************************/
static void YWPluginRenamei_DisplayEditContent(YWRENAME_EditContentInfo_T *ptContentInfo, YWGUI_Char_T *pStr, YWGUI_Handle_T hEdit)
{
    YWGUI_Char_T WstrTemp[256];
	YWGUI_Char_T wstr[256];

    YWLIB_Memset(WstrTemp, 0, sizeof(WstrTemp));
	YWLIB_Memset(wstr, 0x0, sizeof(wstr));

    if(YWPluginRenamei_GetDisplayFlash())
    {
        *(pStr+ptContentInfo->s32CursorPos) = PLUGIN_RENAME_CURSOR;
    }
    else
    {
        *(pStr+ptContentInfo->s32CursorPos) = PLUGIN_RENAME_SPACE;
    }
	YWLIB_Wstrcpy(wstr, pStr);

    YWLIB_Wstrncpy(WstrTemp, (wstr+ptContentInfo->s32DisplayStartPos),
        (ptContentInfo->s32DisplayEndPos-ptContentInfo->s32DisplayStartPos+1));

    YWGUI_SetWindowText(hEdit, WstrTemp);
}

static S32 YWPluginRenamei_RenameGetBtnIdByNumberCode(U16 scancode)
{
    S32 CtrlId = IDC_BTN_PLUGIN_RENAME_5_1;

    if(scancode == YWGUI_SCANCODE_0)
    {
        CtrlId = IDC_BTN_PLUGIN_RENAME_5_1;
    }
    else if(scancode == YWGUI_SCANCODE_1)
    {
        CtrlId = IDC_BTN_PLUGIN_RENAME_5_2;
    }
    else if(scancode == YWGUI_SCANCODE_2)
    {
        CtrlId = IDC_BTN_PLUGIN_RENAME_5_3;
    }
    else if(scancode == YWGUI_SCANCODE_3)
    {
        CtrlId = IDC_BTN_PLUGIN_RENAME_5_4;
    }
    else if(scancode == YWGUI_SCANCODE_4)
    {
        CtrlId = IDC_BTN_PLUGIN_RENAME_5_5;
    }
    else if(scancode == YWGUI_SCANCODE_5)
    {
        CtrlId = IDC_BTN_PLUGIN_RENAME_5_6;
    }
    else if(scancode == YWGUI_SCANCODE_6)
    {
        CtrlId = IDC_BTN_PLUGIN_RENAME_5_7;
    }
    else if(scancode == YWGUI_SCANCODE_7)
    {
        CtrlId = IDC_BTN_PLUGIN_RENAME_5_8;
    }
    else if(scancode == YWGUI_SCANCODE_8)
    {
        CtrlId = IDC_BTN_PLUGIN_RENAME_5_9;
    }
    else if(scancode == YWGUI_SCANCODE_9)
    {
        CtrlId = IDC_BTN_PLUGIN_RENAME_5_10;
    }

    return CtrlId;
}



static void YWPluginRenamei_InitTxt(YWGUI_HWnd_T hWnd)
{

//	YWLIB_Memset(wstr, 0, sizeof(wstr));
//	YWLIB_Astr2wstr(wstr, (S8*)"Confirm");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_PLUGIN_RENAME_CONFIRM), YWSTR_GetString(STR_CONFIRM));

//	YWLIB_Memset(wstr, 0, sizeof(wstr));
//	YWLIB_Astr2wstr(wstr, (S8*)"Prev");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_PLUGIN_RENAME_PREV), YWSTR_GetString(STR_PREV));

//	YWLIB_Memset(wstr, 0, sizeof(wstr));
//	YWLIB_Astr2wstr(wstr, (S8*)"Next");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_PLUGIN_RENAME_NEXT), YWSTR_GetString(STR_NEXT));

//	YWLIB_Memset(wstr, 0, sizeof(wstr));
//	YWLIB_Astr2wstr(wstr, (S8*)"Clear");
	YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_PLUGIN_RENAME_CLEAR), YWSTR_GetString(STR_CLEAR));

}


static void YWPluginRenamei_InitBtnTxt(YWGUI_HWnd_T hWnd)
{
	int i;
	S32 j = 0;
	YWGUI_Char_T wstr[8];

	YWLIB_Memset(wstr, 0, sizeof(wstr));

    for(i=IDC_BTN_PLUGIN_RENAME_1_1; i<=IDC_BTN_PLUGIN_RENAME_7_9; i++)
    {
        YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, i), (YWGUI_Char_T*)&pRenameKeyValue[j]);
		j++;
    }


	YWLIB_Astr2wstr(wstr, (S8*)"space");
    YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_BTN_PLUGIN_RENAME_7_10), wstr);

	YWLIB_Astr2wstr(wstr, (S8*)"back");
    YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_BTN_PLUGIN_RENAME_7_11), wstr);

}
static YWGUI_Char_T YWPluginRenamei_RenameGetWCharByBtnId(U16 id)
{
	YWGUI_Char_T wchar;

    //assert((id >= IDC_BTN_PLUGIN_RENAME_1_1) && (id <= IDC_BTN_PLUGIN_RENAME_7_9));

    wchar = (S32)pRenameKeyValue[id-IDC_BTN_PLUGIN_RENAME_1_1];

	return wchar;
}

static S32 YWPluginRenamei_WndProc(YWGUI_HWnd_T hWnd, S32 message, WPARAM wParam,LPARAM lParam)
{
    switch (message)
    {
        case YWGUI_MSG_NCCREATE:
        {
            YWGUI_SetWEColor(hWnd, YWGUI_MAINWND_BGC, Color_black);
            YWGUI_SetWEShapeState(hWnd, YWGUI_STATUS_NORMAL, &g_tSubMenuFrameShapeState);
            break;
        }

        case YWGUI_MSG_INITDIALOG:
		{
			/*YWGUI_Char_T wstr[16];

			YWLIB_Memset(wstr, 0, sizeof(wstr));
			YWLIB_Astr2wstr(wstr, (S8*)"Edit");*/
			if(g_tPluginRenameParam.pStrTitle != NULL)
			{
				YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_PLUGIN_RENAME_TITLE), g_tPluginRenameParam.pStrTitle);
			}
			else
			{
				YWGUI_SetWindowText(YWGUI_GetDlgItem(hWnd, IDC_TXT_PLUGIN_RENAME_TITLE), 
					YWSTR_GetString(STR_EDIT));
			}

			YWPluginRenamei_TidyUpTheEditContent(hWnd, &g_tPluginRenameContentInfo,
					g_tPluginRenameParam.pStrContent, PLUGIN_RENAME_DISP_CONTENT_LEN, TRUE);

			YWPluginRenamei_DisplayEditContent(&g_tPluginRenameContentInfo, g_tPluginRenameParam.pStrContent,
					YWGUI_GetDlgItem(hWnd , IDC_EDIT_PLUGIN_RENAME_CONTENT));

			YWGUI_SEditSetMaxLimit(YWGUI_GetDlgItem(hWnd, IDC_EDIT_PLUGIN_RENAME_CONTENT), g_tPluginRenameParam.nEditLimitLen);

			YWPluginRenamei_InitTxt(hWnd);
			YWPluginRenamei_InitBtnTxt(hWnd);

			YWGUI_EnableWindow(YWGUI_GetDlgItem(hWnd, IDC_EDIT_PLUGIN_RENAME_CONTENT), FALSE);
			YWGUI_SetFocus(YWGUI_GetDlgItem(hWnd, IDC_BTN_PLUGIN_RENAME_1_1));

			YWGUI_SetTimer(hWnd, TIMER_SECONDS, 1*500);

		}
            break;

        case YWGUI_MSG_TIMER:
        {
            if(TIMER_SECONDS == (S32)wParam)
            {
                if(YWPluginRenamei_GetDisplayFlash())
                {
                    YWPluginRenamei_SetDisplayFlash(FALSE);
                }
                else
                {
                    YWPluginRenamei_SetDisplayFlash(TRUE);
                }
                YWPluginRenamei_DisplayEditContent(&g_tPluginRenameContentInfo, g_tPluginRenameParam.pStrContent, YWGUI_GetDlgItem(hWnd , IDC_EDIT_PLUGIN_RENAME_CONTENT));
            }
        }
            return 0;

		case YWGUI_MSG_PAINT:
		{
			YWGUI_HDc_T hdc;
			YWGUI_Pixel_T OldColor;
			hdc = YWGUI_BeginPaint(hWnd);
//dlg	rect {0,0,1220,670}

			//title
/*			YWGUI_SetBrushColor(hdc, Color_gray, OldColor);
        	YWGUI_FillBox(hdc, 0, 0, 1220, 52);*/
			//function circle
/*		    YWGUI_SetBrushColor(hdc, Color_red, OldColor);
			YWGUI_FillCircle(hdc, 65, 640, 15);

		    YWGUI_SetBrushColor(hdc, Color_green, OldColor);
		    YWGUI_FillCircle(hdc, 245, 640, 15);

		    YWGUI_SetBrushColor(hdc, Color_yellow, OldColor);
		    YWGUI_FillCircle(hdc, 425, 640, 15);

		    YWGUI_SetBrushColor(hdc, Color_blue, OldColor);
		    YWGUI_FillCircle(hdc, 605, 640, 15);*/

			//divid bar
            YWGUI_SetBrushColor(hdc, Color_gray, OldColor);
        	YWGUI_FillBox(hdc, 0, 610, 1220,4);

			//
		/*	YWGUI_SetBrushColor(hdc, Color_gray, OldColor);
			YWGUI_FillBox(hdc, 0, 0, 1220, 2);
			YWGUI_FillBox(hdc, 0, 0, 2, 670);
			YWGUI_FillBox(hdc, 1218, 0, 2, 670);
			YWGUI_FillBox(hdc, 0, 668, 1220, 2);
            YWGUI_EndPaint(hWnd,hdc);*/

		}
			break;

		case YWGUI_MSG_COMMAND:
        {
            U16 id = (U16)YWGUI_LOWORD (wParam);
	        U16 notifyCode= (U16)YWGUI_HIWORD (wParam);
            S32 iLimitLen = 0;


            iLimitLen = YWGUI_SEditGetMaxLimit(YWGUI_GetDlgItem(hWnd, IDC_EDIT_PLUGIN_RENAME_CONTENT));

            if(notifyCode == YWGUI_NONE_CODE)
			{
                if(id == IDC_BTN_PLUGIN_RENAME_7_11)    //back
                {
                    YWPluginRenamei_DeleteWcharFromEditCtrl(hWnd, &g_tPluginRenameContentInfo, g_tPluginRenameParam.pStrContent, PLUGIN_RENAME_DISP_CONTENT_LEN);
                }
                else if(id == IDC_BTN_PLUGIN_RENAME_7_10)  //space
                {
                    YWGUI_Char_T Wchar = PLUGIN_RENAME_SPACE;

                    if(g_tPluginRenameContentInfo.s32ContentLen >= iLimitLen)
                    {
                        YWOS_Trace(YWOS_TRACE_INFO, "%s : %d Reach edit limit len\n", __FUNCTION__, __LINE__);
                        return 0;
                    }
					YWPluginRenamei_InsertWcharToEditCtrl(hWnd, &g_tPluginRenameContentInfo,
						g_tPluginRenameParam.pStrContent, Wchar, PLUGIN_RENAME_DISP_CONTENT_LEN);

                }
                else    //insert one char
                {

                    YWGUI_Char_T Wchar;
                    if(g_tPluginRenameContentInfo.s32ContentLen >= iLimitLen)
                    {
                        YWOS_Trace(YWOS_TRACE_INFO, "%s : %d Reach edit limit len\n", __FUNCTION__, __LINE__);
                        return 0;
                    }
                    Wchar = YWPluginRenamei_RenameGetWCharByBtnId(id);
					YWPluginRenamei_InsertWcharToEditCtrl(hWnd, &g_tPluginRenameContentInfo,
						g_tPluginRenameParam.pStrContent, Wchar, PLUGIN_RENAME_DISP_CONTENT_LEN);

                }
				YWPluginRenamei_DisplayEditContent(&g_tPluginRenameContentInfo, g_tPluginRenameParam.pStrContent, YWGUI_GetDlgItem(hWnd, IDC_EDIT_PLUGIN_RENAME_CONTENT));

            }

        }
            break;
        case YWGUI_MSG_KEYDOWN:
    	{
            U16 scancode=YWGUI_LOWORD(wParam);

            switch(scancode)
            {
                case YWGUI_SCANCODE_EXIT:
                    YWGUI_SendMessage(hWnd, YWGUI_MSG_CLOSE, 0, 0);
                    return 0;


				case YWGUI_SCANCODE_UP:
				{
					U16 Btnid = YWGUI_GetDlgCtrlID(YWGUI_GetFocus(hWnd));

		            if(Btnid >= IDC_BTN_PLUGIN_RENAME_1_1 && Btnid<=IDC_BTN_PLUGIN_RENAME_1_9)
		            {
		                Btnid += 78;
		            }
					else if(Btnid >= IDC_BTN_PLUGIN_RENAME_1_10 && Btnid<=IDC_BTN_PLUGIN_RENAME_1_11)
					{
						Btnid = IDC_BTN_PLUGIN_RENAME_7_10;
					}
					else if(Btnid >= IDC_BTN_PLUGIN_RENAME_1_12 && Btnid<=IDC_BTN_PLUGIN_RENAME_1_13)
					{
						Btnid = IDC_BTN_PLUGIN_RENAME_7_11;
					}
					else if(Btnid == IDC_BTN_PLUGIN_RENAME_7_10)
		            {
		                Btnid = IDC_BTN_PLUGIN_RENAME_6_10;
		            }
					else if(Btnid == IDC_BTN_PLUGIN_RENAME_7_11)
		            {
		                Btnid = IDC_BTN_PLUGIN_RENAME_6_12;
		            }
		            else
		            {
		                Btnid -= 13;
		            }

		            YWGUI_SetFocus(YWGUI_GetDlgItem(hWnd, Btnid));
				}
					return 0;
				case YWGUI_SCANCODE_DOWN:
				{
					U16 Btnid = YWGUI_GetDlgCtrlID(YWGUI_GetFocus(hWnd));

		            if(Btnid >= IDC_BTN_PLUGIN_RENAME_7_1 && Btnid<=IDC_BTN_PLUGIN_RENAME_7_9)
		            {
		                Btnid -= 78;
		            }
					else if(Btnid >= IDC_BTN_PLUGIN_RENAME_6_10 && Btnid<=IDC_BTN_PLUGIN_RENAME_6_11)
		            {
		                Btnid = IDC_BTN_PLUGIN_RENAME_7_10;
		            }
					else if(Btnid >= IDC_BTN_PLUGIN_RENAME_6_12 && Btnid<=IDC_BTN_PLUGIN_RENAME_6_13)
		            {
		                Btnid = IDC_BTN_PLUGIN_RENAME_7_11;
		            }
					else if(Btnid == IDC_BTN_PLUGIN_RENAME_7_10)
		            {
		                Btnid = IDC_BTN_PLUGIN_RENAME_1_10;
		            }
					else if(Btnid == IDC_BTN_PLUGIN_RENAME_7_11)
		            {
		                Btnid = IDC_BTN_PLUGIN_RENAME_1_12;
		            }
		            else
		            {
		                Btnid += 13;
		            }

					YWGUI_SetFocus(YWGUI_GetDlgItem(hWnd, Btnid));
				}
					return 0;
				case YWGUI_SCANCODE_LEFT:
				{
		            if(YWGUI_GetDlgCtrlID(YWGUI_GetFocus(hWnd)) == IDC_BTN_PLUGIN_RENAME_1_1)
		            {
		                YWGUI_SetFocus(YWGUI_GetDlgItem(hWnd, IDC_BTN_PLUGIN_RENAME_7_11));
						return 0;
		            }
		        }
					break;
				case YWGUI_SCANCODE_RIGHT:
				{
		            if(YWGUI_GetDlgCtrlID(YWGUI_GetFocus(hWnd)) == IDC_BTN_PLUGIN_RENAME_7_11)
		            {
		                YWGUI_SetFocus(YWGUI_GetDlgItem(hWnd, IDC_BTN_PLUGIN_RENAME_1_1));
						return 0;
		            }
		        }
					break;
                case YWGUI_SCANCODE_OK:
                    break;
		        case YWGUI_SCANCODE_RED:      //confirm
		        {
		            S32 iStrLen = 0;
		            YWPluginRenamei_DeletWchar(g_tPluginRenameParam.pStrContent, g_tPluginRenameContentInfo.s32CursorPos);

		            iStrLen = YWLIB_Wstrlen(g_tPluginRenameParam.pStrContent);
		            if(iStrLen == 0)
		            {
		                YWGUI_SendMessage(hWnd, YWGUI_MSG_KEYDOWN, YWGUI_SCANCODE_EXIT, 0);
		            }
		            else
		            {
	                    YWGUI_PostMessage(g_tPluginRenameParam.hHosting, YWPUBLIC_MSG_RENAME, (WPARAM)g_tPluginRenameParam.pStrContent, (LPARAM)TRUE);
	                    YWGUI_DestroyMainWindow(hWnd);
	                    return 0;
		            }
		        }
		           return 0;
		        case YWGUI_SCANCODE_GREEN:    //prev 光标前移一位
		        {
		            YWPluginRenamei_LeftMoveCtrlCursor(hWnd, &g_tPluginRenameContentInfo, g_tPluginRenameParam.pStrContent, PLUGIN_RENAME_DISP_CONTENT_LEN);
		            YWPluginRenamei_DisplayEditContent(&g_tPluginRenameContentInfo, g_tPluginRenameParam.pStrContent, YWGUI_GetDlgItem(hWnd, IDC_EDIT_PLUGIN_RENAME_CONTENT));
		        }
		            break;
		        case YWGUI_SCANCODE_YELLOW:   //next  光标后移一位
		        {
		            YWPluginRenamei_RightMoveCtrlCursor(hWnd, &g_tPluginRenameContentInfo, g_tPluginRenameParam.pStrContent, PLUGIN_RENAME_DISP_CONTENT_LEN);
		            YWPluginRenamei_DisplayEditContent(&g_tPluginRenameContentInfo, g_tPluginRenameParam.pStrContent, YWGUI_GetDlgItem(hWnd, IDC_EDIT_PLUGIN_RENAME_CONTENT));
				}
		            break;
				case YWGUI_SCANCODE_BLUE:   //clear
		        {
		            YWPluginRenamei_ClearEditContent(&g_tPluginRenameContentInfo, g_tPluginRenameParam.pStrContent);
		            YWPluginRenamei_DisplayEditContent(&g_tPluginRenameContentInfo, g_tPluginRenameParam.pStrContent, YWGUI_GetDlgItem(hWnd, IDC_EDIT_PLUGIN_RENAME_CONTENT));
		        }
		            break;
				case YWGUI_SCANCODE_0:
		        case YWGUI_SCANCODE_1:
		        case YWGUI_SCANCODE_2:
		        case YWGUI_SCANCODE_3:
		        case YWGUI_SCANCODE_4:
		        case YWGUI_SCANCODE_5:
		        case YWGUI_SCANCODE_6:
		        case YWGUI_SCANCODE_7:
		        case YWGUI_SCANCODE_8:
		        case YWGUI_SCANCODE_9:
		        {
		            S32 id;
		            YWGUI_Char_T Wchar;
		            S32 iLimitLen = 0;
		            iLimitLen = YWGUI_SEditGetMaxLimit(YWGUI_GetDlgItem(hWnd, IDC_EDIT_PLUGIN_RENAME_CONTENT));

		            if(g_tPluginRenameContentInfo.s32ContentLen >= iLimitLen)
		            {
						YWOS_Trace(YWOS_TRACE_ERROR, "%s : %d Reach edit limit len\n", __FUNCTION__, __LINE__);
		                return 0;
		            }

		            id = YWPluginRenamei_RenameGetBtnIdByNumberCode(scancode);
					Wchar = YWPluginRenamei_RenameGetWCharByBtnId(id);

		            YWPluginRenamei_InsertWcharToEditCtrl(hWnd, &g_tPluginRenameContentInfo, g_tPluginRenameParam.pStrContent, Wchar, PLUGIN_RENAME_DISP_CONTENT_LEN);
		            YWPluginRenamei_DisplayEditContent(&g_tPluginRenameContentInfo, g_tPluginRenameParam.pStrContent, YWGUI_GetDlgItem(hWnd, IDC_EDIT_PLUGIN_RENAME_CONTENT));
		            YWGUI_SetFocus(YWGUI_GetDlgItem(hWnd, id));
		        }
		            return 0;
					
                default:
                    break;
            }
		}
            break;


        case YWGUI_MSG_CLOSE:
            break;

        case YWGUI_MSG_DESTROY:
            break;

        default:
            break;
    }

    return YWGUI_DefaultDialogProc(hWnd,message,wParam,lParam);
}






/*create a rename window*/
YW_ErrorType_T YWPlugin_CreateRenameWindow(YWPLUGINREAME_Param_T *pPluginRenameParam)
{
    S32 strLen = 0;

    YWLIB_Memset(&g_tPluginRenameContentInfo, 0, sizeof(YWRENAME_EditContentInfo_T));
    YWLIB_Memset(g_aPluginRenameEditContent, 0, sizeof(g_aPluginRenameEditContent));
    YWLIB_Memset(&g_tPluginRenameParam, 0, sizeof(YWPLUGINREAME_Param_T));
    if(pPluginRenameParam->pStrContent != NULL)
    {
        strLen = YWLIB_Wstrlen(pPluginRenameParam->pStrContent);
        YWLIB_Wstrncpy(g_aPluginRenameEditContent, pPluginRenameParam->pStrContent, strLen);
    }

    g_aPluginRenameEditContent[strLen] = PLUGIN_RENAME_CURSOR;

    strLen = YWLIB_Wstrlen(g_aPluginRenameEditContent);
    g_tPluginRenameContentInfo.s32ContentLen = strLen;
    g_tPluginRenameContentInfo.s32DisplayStartPos = 0;
    g_tPluginRenameContentInfo.s32DisplayEndPos = strLen-1;
    g_tPluginRenameContentInfo.s32CursorPos = strLen-1;

    g_tPluginRenameParam.hHosting = pPluginRenameParam->hHosting;
    if(pPluginRenameParam->pStrTitle == NULL)
    {
        g_tPluginRenameParam.pStrTitle = NULL;
    }
    else
    {
        g_tPluginRenameParam.pStrTitle = pPluginRenameParam->pStrTitle;
    }

    if(pPluginRenameParam->nEditLimitLen > 0 && pPluginRenameParam->nEditLimitLen < PLUGIN_RENAME_CONTENT_LIMIT_LEN)
    {
        g_tPluginRenameParam.nEditLimitLen = pPluginRenameParam->nEditLimitLen+1;
    }
    else
    {
        g_tPluginRenameParam.nEditLimitLen = PLUGIN_RENAME_CONTENT_LIMIT_LEN;
    }

    g_tPluginRenameParam.pStrContent = g_aPluginRenameEditContent;


    return YWGUI_CreateDialog(IDD_PLUGIN_RENAME, pPluginRenameParam->hHosting, (YWGUI_WindowProc_P)YWPluginRenamei_WndProc, (LPARAM)0, NULL);

}







