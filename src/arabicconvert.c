/************************************************************************************/
//
// Copyright (C), 2005-2010, FULAN Electronics Technology Development Co., Ltd.
//
// 文件名：		arabic_convert.c
//
// 创建者：		XYJ
//
// 创建日期：	2008/07/11
//
// 文件描述：	阿拉伯字符集处理
//
// 当前维护者：XYJ
//
// 最后更新：2008/07/11
//
// MEMO：
//
/************************************************************************************/
//#include "Typedef.h"
#include "ywdefs.h"
#include "ywos.h"
#include "ywlib.h"

//#include "ywhal_assert.h"

//#include "ywlib_charmap.h"
//#include "ywlib_iso5937.h"

#define MAX_CHARS       1024*4
#define MAX_WORDS       1024

#define BIDI_NULL       0
#define BIDI_LTR        1
#define BIDI_RTL        2
#define BIDI_SPC        3
#define BIDI_PUN        4

#define JOIN_NONE       0
#define JOIN_RIGT       1
#define JOIN_LEFT       2
#define JOIN_DUAL       3

#define ARABIC_OTHER    0
#define ARABIC_ALEF     1
#define ARABIC_LAM      2
#define ARABIC_WAW      ARABIC_OTHER
#define ARABIC_YEH      ARABIC_OTHER
#define ARABIC_BEH      ARABIC_OTHER
#define ARABIC_TEH      ARABIC_OTHER
#define ARABIC_HAH      ARABIC_OTHER
#define ARABIC_DAL      ARABIC_OTHER
#define ARABIC_REH      ARABIC_OTHER
#define ARABIC_SEEN     ARABIC_OTHER
#define ARABIC_SAD      ARABIC_OTHER
#define ARABIC_TAH      ARABIC_OTHER
#define ARABIC_AIN      ARABIC_OTHER
#define ARABIC_FEH      ARABIC_OTHER
#define ARABIC_QAF      ARABIC_OTHER
#define ARABIC_KAF      ARABIC_OTHER
#define ARABIC_MEEM     ARABIC_OTHER
#define ARABIC_NOON     ARABIC_OTHER
#define ARABIC_HEH      ARABIC_OTHER
#define ARABIC_NOJOIN   ARABIC_OTHER


struct arabic_join
{
    U16 unicode;
    U16 present;
    U8 join;
    U8 group;
};


static const struct arabic_join arabic_code_info[] =
{
    { 0x0621, 0xFE80, JOIN_NONE, ARABIC_NOJOIN },
    { 0x0622, 0xFE81, JOIN_RIGT, ARABIC_ALEF },
    { 0x0623, 0xFE83, JOIN_RIGT, ARABIC_ALEF },
    { 0x0624, 0xFE85, JOIN_RIGT, ARABIC_WAW },
    { 0x0625, 0xFE87, JOIN_RIGT, ARABIC_ALEF },
    { 0x0626, 0xFE89, JOIN_DUAL, ARABIC_YEH },
    { 0x0627, 0xFE8D, JOIN_RIGT, ARABIC_ALEF },
    { 0x0628, 0xFE8F, JOIN_DUAL, ARABIC_BEH },
    { 0x0629, 0xFE93, JOIN_RIGT, ARABIC_TEH },
    { 0x062A, 0xFE95, JOIN_DUAL, ARABIC_BEH },
    { 0x062B, 0xFE99, JOIN_DUAL, ARABIC_BEH },
    { 0x062C, 0xFE9D, JOIN_DUAL, ARABIC_HAH },
    { 0x062D, 0xFEA1, JOIN_DUAL, ARABIC_HAH },
    { 0x062E, 0xFEA5, JOIN_DUAL, ARABIC_HAH },
    { 0x062F, 0xFEA9, JOIN_RIGT, ARABIC_DAL },
    { 0x0630, 0xFEAB, JOIN_RIGT, ARABIC_DAL },
    { 0x0631, 0xFEAD, JOIN_RIGT, ARABIC_REH },
    { 0x0632, 0xFEAF, JOIN_RIGT, ARABIC_REH },
    { 0x0633, 0xFEB1, JOIN_DUAL, ARABIC_SEEN },
    { 0x0634, 0xFEB5, JOIN_DUAL, ARABIC_SEEN },
    { 0x0635, 0xFEB9, JOIN_DUAL, ARABIC_SAD },
    { 0x0636, 0xFEBD, JOIN_DUAL, ARABIC_SAD },
    { 0x0637, 0xFEC1, JOIN_DUAL, ARABIC_TAH },
    { 0x0638, 0xFEC5, JOIN_DUAL, ARABIC_TAH },
    { 0x0639, 0xFEC9, JOIN_DUAL, ARABIC_AIN },
    { 0x063A, 0xFECD, JOIN_DUAL, ARABIC_AIN },
    { 0x0640, 0x0640, JOIN_DUAL, ARABIC_NOJOIN },
    { 0x0641, 0xFED1, JOIN_DUAL, ARABIC_FEH },
    { 0x0642, 0xFED5, JOIN_DUAL, ARABIC_QAF },
    { 0x0643, 0xFED9, JOIN_DUAL, ARABIC_KAF },
    { 0x0644, 0xFEDD, JOIN_DUAL, ARABIC_LAM },
    { 0x0645, 0xFEE1, JOIN_DUAL, ARABIC_MEEM },
    { 0x0646, 0xFEE5, JOIN_DUAL, ARABIC_NOON },
    { 0x0647, 0xFEE9, JOIN_DUAL, ARABIC_HEH },
    { 0x0648, 0xFEED, JOIN_RIGT, ARABIC_WAW },
    { 0x0649, 0xFEEF, JOIN_DUAL, ARABIC_YEH },
    { 0x064A, 0xFEF1, JOIN_DUAL, ARABIC_YEH },
    { 0x200C, 0x200C, JOIN_NONE, ARABIC_NOJOIN },
    { 0x200D, 0x200D, JOIN_DUAL, ARABIC_NOJOIN },
};

#define MAX_INFO    (sizeof(arabic_code_info) / \
      sizeof(arabic_code_info[0]))



U32 get_dir(U16 code)
{
    U32 dir;

    if (code == 0x0009 || code == 0x0020)
        dir = BIDI_SPC;
    else if (code == 0x200C || code == 0x200D)
        dir = BIDI_RTL;
    /* Arabic */
    else if ((0x0600 <= code && code <= 0x06FF) || \
          (0x0750 <= code && code <= 0x077F)/* || \
          (0xFB50 <= code && code <= 0xFDFF) || \
          (0xFE70 <= code && code <= 0xFEFC)*/)
        dir = BIDI_RTL;
    else if ((0x21 <= code && code <= 0x2F) || \
            (0x3A<= code && code <= 0x40) || \
            (0x5B <= code && code <= 0x60) || \
            (0x7B <= code && code <= 0x7E))
    {
        dir =BIDI_PUN;
    }
    else
        dir = BIDI_LTR;

    return dir;
}



void merge_seg(U32 idx, U8 dir,U32 *segments,U16 *word_pos[],U8 *word_dir)
{
    U32 i;
    U32  segmentsTemp =*segments;

    if((segments==NULL)||(word_pos==NULL)||(word_dir==NULL))
    {
        return;
    }

    if(*segments>MAX_WORDS)
    {
        return;
    }
    for (i = idx + 1; i <= segmentsTemp - 1; i++)
    {
        word_pos[i] = word_pos[i + 1];
        word_dir[i] = word_dir[i + 1];
    }
    word_dir[idx] = dir;
    segmentsTemp--;
    *segments =segmentsTemp;

}


void absorb_spc(U8 dir,U32 *segments,U16 *word_pos[],U8 *word_dir)
{
    U32 i;
    U32  segmentsTemp =*segments;

    if((segments==NULL)||(word_dir==NULL)||(word_pos==NULL))
    {
        return;
    }
    if(*segments>MAX_WORDS)
    {
        return;
    }

    for (i = 0; i < segmentsTemp; i++)
    {
        if (word_dir[i] == dir)
        {
            while (i > 0 && word_dir[i - 1] == BIDI_SPC)
            {
                merge_seg(--i, dir,&segmentsTemp,word_pos,word_dir);
                if (i > 0 && word_dir[i - 1] == word_dir[i])
                {
                    merge_seg(--i, dir,&segmentsTemp,word_pos,word_dir);
                }
            }
            while (i < segmentsTemp - 1 && word_dir[i + 1] == BIDI_SPC)
            {
                merge_seg(i, dir,&segmentsTemp,word_pos,word_dir);
                if (i < segmentsTemp - 1 && word_dir[i] == word_dir[i + 1])
                {
                    merge_seg(i, dir,&segmentsTemp,word_pos,word_dir);
                }
            }
        }
    }
    *segments =segmentsTemp;

}



BOOL dir_split(U16 **str, U16 *end,U16 *word_pos[],U8 *word_dir,U32 *segments)
{
    U16 code;
    U16 *begin;
    U32 dir, dir_last;
    U32 stage;
    BOOL ret=FALSE;
    U32 segmentsTemp =0;

    if((segments==NULL)||(word_dir==NULL)||(word_pos==NULL)||(str==NULL)||(end==NULL))
    {
        return FALSE;
    }

    begin = *str;
    dir_last = BIDI_NULL;
    segmentsTemp = 0;
    code = *begin;
    stage = 0;
    while (begin < end)
    {
        if (code == 0x000D)
            stage = 1;
        else if (code == 0x000A && stage == 1)
            break;
        else
            stage = 0;
        dir = get_dir(code);
        if(dir==BIDI_RTL)
        {
            ret =TRUE;
        }
        if (dir != dir_last)
        {
            dir_last = dir;
            word_pos[segmentsTemp] = begin;
            word_dir[segmentsTemp] = dir;
            segmentsTemp++;
        }
        code = *++begin;
        if(segmentsTemp >= MAX_WORDS)
        {
//            YWOSTRACE((YWOS_TRACE_INFO,"\n segments = %d\n",segmentsTemp));
            segmentsTemp = MAX_WORDS;
            break;
        }
    }
    if (begin < end)
        begin--;
    word_pos[segmentsTemp] = begin;
    word_dir[segmentsTemp] = BIDI_NULL;
    *str = begin;

    absorb_spc(BIDI_RTL,&segmentsTemp,word_pos,word_dir);
    absorb_spc(BIDI_LTR,&segmentsTemp,word_pos,word_dir);
    *segments =segmentsTemp;
    return ret;
}



void latin_line(U16 *begin, U16 *end,U16 *str_out)
{
    if((str_out==NULL)||(begin==NULL)||(end==NULL))
    {
        return;
    }
    while (begin <= end)
    {
        *str_out++ = *begin++;
    }
}



void punctuation_line(U16 *begin, U16 *end,U16 *str_out)
{
    if((str_out==NULL)||(begin==NULL)||(end==NULL))
    {
        return;
    }
    while ( end>=begin)
    {
        if(*end==(U16)'('||*end==(U16)')')
        {
            *str_out++=(*end==(U16)'(')?(U16)')':(U16)'(';
        }
        else if(*end==(U16)'['||*end==(U16)']')
        {
            *str_out++=(*begin==(U16)'[')?(U16)']':(U16)'[';
        }
        else if(*end==(U16)'{'||*end==(U16)'}')
        {
            *str_out++=(*end==(U16)'{')?(U16)'}':(U16)'{';
        }
        else if(*end==(U16)'<'||*end==(U16)'>')
        {
            *str_out++=(*end==(U16)'<')?(U16)'>':(U16)'<';
        }
        else
        {
           *str_out++ = *end;
        }
        end--;
    }
}



struct arabic_join *seek_info(U16 code)
{
    U32 i;

    for (i = 0; i < MAX_INFO; i++)
    {
        if (arabic_code_info[i].unicode == code)
            break;
    }

    return i == MAX_INFO ? NULL : \
          (struct arabic_join *)&arabic_code_info[i];
}



U16 get_ligature(U16 present)
{
    switch (present)
    {
    case 0xFE82:
        return 0xFEF5;
    case 0xFE84:
        return 0xFEF7;
    case 0xFE88:
        return 0xFEF9;
    case 0xFE8E:
        return 0xFEFB;
    default:
		break;  //DBG_PRINTF("Error Ligature: %04X\n", present);
    }
    return 0x0020;
}



void out_char(U16 code, U8 mode,U16 *str_out,S32 *str_out_len,U8 *group_last)
{
    U8 group;
    U16 present;
    S32 iLen = *str_out_len;
    struct arabic_join *code_info;

    if((str_out==NULL)||(str_out_len==NULL)||(group_last==NULL))
    {
        return;
    }

    *str_out_len = 0;
    code_info = seek_info(code);
    if (code_info == NULL)
    {
        *str_out++ = code;
        iLen++;
        *str_out_len = iLen;
        *group_last = ARABIC_OTHER;
        return;
    }
    group = code_info->group;
    if (group == ARABIC_LAM && *group_last == ARABIC_ALEF)
    {
        str_out--;
        iLen--;

        present = get_ligature(*str_out);
        mode &= 1;
    }
    else
    {
        present = code_info->present;
    }
    if (present != 0x200C && present != 0x200D)
    {
        *str_out++ = present + mode;
        iLen++;
    }
    *str_out_len = iLen;

}



void arabic_line(U16 *end, U16 *begin,U16 *str_out,S32 *str_out_len)
{
    U16 code, code_last;
    U8 join, join_last;
    U8 mode, mode_last;
    struct arabic_join *info;
    U8 group_last;
    U16 *str_out_buffer;
    S32 lenTemp =0;

    if((end==NULL)||(begin==NULL)||(str_out==NULL)||(str_out_len==NULL))
    {
        return;
    }

    *str_out_len =0;
    group_last = ARABIC_OTHER;
    code_last = 0;
    join_last = JOIN_NONE;
    mode_last = JOIN_NONE;
    str_out_buffer = str_out;
    while (end >= begin)
    {
        info = seek_info(code = *end);
        join = info == NULL ? JOIN_NONE : info->join;

        if ((join_last & JOIN_RIGT) && (join & JOIN_LEFT))
        {
            mode_last |= JOIN_RIGT;
            mode = JOIN_LEFT;
        }
        else
        {
            mode = JOIN_NONE;
        }

        if (code_last)
        {
            lenTemp =0;
            out_char(code_last, mode_last,str_out_buffer,&lenTemp,&group_last);
            str_out_buffer +=lenTemp;
            *str_out_len += lenTemp;
        }

        mode_last = mode;
        code_last = code;
        join_last = join;

        end--;
    }
    if (code_last)
    {
        lenTemp =0;
        out_char(code_last, mode_last,str_out_buffer,&lenTemp,&group_last);
        str_out_buffer += lenTemp;
        *str_out_len += lenTemp;
    }
}



U32 YWLIB_ArabicProcess(U16 *str, U32 size)
{
    U32 len = 0;
    U16 *ptr;
    U16 *begin;
    U16 *end;
    BOOL  bHaveArabic =0;

    U16 *word_pos[MAX_WORDS+1];
    U8 word_dir[MAX_WORDS+1];
    U16 str_buf[MAX_CHARS+1];
    U16 *str_out;
    U32 segments =0;

    if (size == 0)
    {
        return 0;
    }

    ptr = str;
    str_out = str_buf;
    if(size >= MAX_CHARS)
    {
        size = MAX_CHARS - 1;
        str[MAX_CHARS-1] = 0x0000;
    }
//    YWOSTRACE((YWOS_TRACE_INFO,"\nstr size = %d\n",size));

    bHaveArabic =dir_split(&str, str + size,word_pos,word_dir,&segments);
    if(!bHaveArabic)
    {
        return size;
    }

    if(segments>MAX_WORDS)
    {
        return size;
    }

    while (segments)
    {
        end = word_pos[segments--] - 1;
        begin = word_pos[segments];
        if(end<begin||(end-begin)>MAX_CHARS)
        {
            continue;
        }
        if (word_dir[segments] == BIDI_LTR)
        {
            latin_line(begin, end,str_out);
            str_out += end - begin + 1;
        }
        else if(word_dir[segments] == BIDI_PUN)
        {
            punctuation_line(begin, end,str_out);
            str_out += end - begin + 1;
        }
        else
        {
            S32 len_ara =0;
            arabic_line(end, begin,str_out,&len_ara);
            if(len_ara <= MAX_CHARS)
            {
                str_out += len_ara;
            }
        }

    }
    len = str_out - str_buf;
    YWLIB_Memcpy(ptr, str_buf, len * 2);
    ptr[len] = 0;

    return len;
}



