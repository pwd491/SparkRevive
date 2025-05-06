
/**********************************文件头部注释************************************/
//
//
//  					Copyright (C), 2005-2010, AV Frontier Tech. Co., Ltd.
//
//
// 文件名：		ywyoutube_url.c
//
// 创建者：		宋立勇
//
// 创建时间：	2008.12.27
//
// 文件描述：	youtube url编解码接口实现。
//
// 修改记录：   日       期      作      者       版本      修定
//				       ---------         ---------        -----        -----
//              		       2008.12.27        宋立勇         0.01           新建
//
/*****************************************************************************************/
/************************************文件包含****************************************/
#include "ywdefs.h"
#include "ywos.h"
#include "ywlib.h"
#include "ywlib_url.h"

#define YWLIB_UNI_REPLACEMENT_CHAR (U32)0x0000FFFD
#define YWLIB_UNI_MAX_BMP (U32)0x0000FFFF
#define YWLIB_UNI_MAX_UTF16 (U32)0x0010FFFF
#define YWLIB_UNI_MAX_UTF32 (U32)0x7FFFFFFF
#define YWLIB_UNI_MAX_LEGAL_UTF32 (U32)0x0010FFFF

//static S8 hexchars[] = "0123456789abcdef";
//static S8 HEXCHARS[] = "0123456789ABCDEF";




static const S32 halfShift  = 10; /* used for shifting by 10 bits */

static const U32 halfBase = 0x0010000UL;
static const U32 halfMask = 0x3FFUL;

#define YWLIB_UNI_SUR_HIGH_START  (U32)0xD800
#define YWLIB_UNI_SUR_HIGH_END    (U32)0xDBFF
#define YWLIB_UNI_SUR_LOW_START   (U32)0xDC00
#define YWLIB_UNI_SUR_LOW_END     (U32)0xDFFF

/* --------------------------------------------------------------------- */

/*
 * Index S32o the table below with the first byte of a UTF-8 sequence to
 * get the number of trailing bytes that are supposed to follow it.
 * Note that *legal* UTF-8 values can't have 4 or 5-bytes. The table is
 * left as-is for anyone who may want to do such conversion, which was
 * allowed in earlier algorithms.
 */
static const S8 trailingBytesForUTF8[256] =
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};

/*
 * Magic values subtracted from a buffer value during U8 conversion.
 * This table contains as many values as there might be trailing bytes
 * in a UTF-8 sequence.
 */
static const U32 offsetsFromUTF8[6] =
{
    0x00000000UL, 0x00003080UL, 0x000E2080UL,
    0x03C82080UL, 0xFA082080UL, 0x82082080UL
};

/*
 * Once the bits are split out S32o bytes of UTF-8, this is a mask OR-ed
 * S32o the first byte, depending on how many bytes follow.  There are
 * as many entries in this table as there are UTF-8 sequence types.
 * (I.e., one byte sequence, two byte... etc.). Remember that sequencs
 * for *legal* UTF-8 will be 4 or fewer bytes total.
 */
static const U8 firstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

/* --------------------------------------------------------------------- */

/* The interface converts a whole buffer to avoid function-call overhead.
 * Constants have been gathered. Loops & conditionals have been removed as
 * much as possible for efficiency, in favor of drop-through switches.
 * (See "Note A" at the bottom of the file for equivalent code.)
 * If your compiler supports it, the "YWLIB_IsLegalUTF8" call can be turned
 * S32o an inline function.
 */

/* --------------------------------------------------------------------- */

YWLIB_UNIConversionResult_T YWLIB_ConvertUTF16toUTF8 (const U16** sourceStart, const U16* sourceEnd,
	                                                                                    U8** targetStart, U8* targetEnd, YWLIB_UNIConversionFlags_T flags)
{
    YWLIB_UNIConversionResult_T result = YWLIB_UNI_CONVERSION_OK;
    const U16* source = *sourceStart;
    U8* target = *targetStart;
    while (source < sourceEnd)
    {
	U32 ch;
	U16 bytesToWrite = 0;
	const U32 byteMask = 0xBF;
	const U32 byteMark = 0x80;
	const U16* oldSource = source; /* In case we have to back up because of target overflow. */
	ch = *source++;
	/* If we have a surrogate pair, convert to U32 first. */
	if (ch >= YWLIB_UNI_SUR_HIGH_START && ch <= YWLIB_UNI_SUR_HIGH_END)
	{
	    /* If the 16 bits following the high surrogate are in the source buffer... */
	    if (source < sourceEnd)
	    {
		U32 ch2 = *source;
		/* If it's a low surrogate, convert to U32. */
		if (ch2 >= YWLIB_UNI_SUR_LOW_START && ch2 <= YWLIB_UNI_SUR_LOW_END)
		{
		    ch = ((ch - YWLIB_UNI_SUR_HIGH_START) << halfShift) + (ch2 - YWLIB_UNI_SUR_LOW_START) + halfBase;
		    ++source;
		}
		else if (flags == YWLIB_UNI_STRICT_CONVERSION)
		{
		    /* it's an unpaired high surrogate */
		    --source; /* return to the illegal value itself */
		    result = YWLIB_UNI_SOURCE_ILLEGAL;
		    break;
		}
	    }
	    else
	    { /* We don't have the 16 bits following the high surrogate. */
		--source; /* return to the high surrogate */
		result = YWLIB_UNI_SOURCE_EXHAUSTED;
		break;
	    }
	}
	else if (flags == YWLIB_UNI_STRICT_CONVERSION)
	{
	    /* UTF-16 surrogate values are illegal in UTF-32 */
	    if (ch >= YWLIB_UNI_SUR_LOW_START && ch <= YWLIB_UNI_SUR_LOW_END)
	    {
		--source; /* return to the illegal value itself */
		result = YWLIB_UNI_SOURCE_ILLEGAL;
		break;
	    }
	}
	/* Figure out how many bytes the result will require */
	if (ch < (U32)0x80)
	{
	    bytesToWrite = 1;
	}
	else if (ch < (U32)0x800)
	{
	    bytesToWrite = 2;
	}
	else if (ch < (U32)0x10000)
	{
	    bytesToWrite = 3;
	}
	else if (ch < (U32)0x110000)
	{
	    bytesToWrite = 4;
	}
	else
	{
            bytesToWrite = 3;
            ch = YWLIB_UNI_REPLACEMENT_CHAR;
	}

	target += bytesToWrite;
	if (target > targetEnd)
	{
	    source = oldSource; /* Back up source point! */
	    target -= bytesToWrite;
	    result = YWLIB_UNI_TARGET_EXHAUSTED;
	    break;
	}
	switch (bytesToWrite)
	{
	    /* note: everything falls through. */
	    case 4:  *--target = (U8)((ch | byteMark) & byteMask); ch >>= 6;
	    case 3:  *--target = (U8)((ch | byteMark) & byteMask); ch >>= 6;
	    case 2:  *--target = (U8)((ch | byteMark) & byteMask); ch >>= 6;
	    case 1:  *--target =  (U8)(ch | firstByteMark[bytesToWrite]);
	}
	target += bytesToWrite;
    }
    *sourceStart = source;
    *targetStart = target;
    return result;
}

/* --------------------------------------------------------------------- */

/*
 * Utility routine to tell whether a sequence of bytes is legal UTF-8.
 * This must be called with the length pre-determined by the first byte.
 * If not calling this from ConvertU8to*, then the length can be set by:
 *  length = trailingBytesForUTF8[*source]+1;
 * and the sequence is illegal right away if there aren't that many bytes
 * available.
 * If presented with a length > 4, this returns FALSE.  The Unicode
 * definition of UTF-8 goes up to 4-byte sequences.
 */

static BOOL YWLIB_IsLegalUTF8(const U8 *source, S32 length)
{
    U8 a;
    const U8 *srcptr = source+length;
    switch (length)
    {
        default:
            return FALSE;
    	/* Everything else falls through when "TRUE"... */
        case 4:
            if ((a = (*--srcptr)) < 0x80 || a > 0xBF)
                return FALSE;
        case 3:
            if ((a = (*--srcptr)) < 0x80 || a > 0xBF)
                return FALSE;
        case 2:
            if ((a = (*--srcptr)) > 0xBF)
                return FALSE;

    	switch (*source)
    	{
    	    /* no fall-through in this inner switch */
    	    case 0xE0:
        	    if (a < 0xA0)
        	        return FALSE;
        	    break;
    	    case 0xED:
    	        if (a > 0x9F)
        	    return FALSE;
        	 break;
    	    case 0xF0:
                if (a < 0x90)
                    return FALSE;
                break;
    	    case 0xF4:
                if (a > 0x8F)
                    return FALSE;
                break;
    	    default:
                if (a < 0x80)
                    return FALSE;
    	}

        case 1:
            if (*source >= 0x80 && *source < 0xC2)
                return FALSE;
    }
    if (*source > 0xF4)
        return FALSE;
    return TRUE;
}

/* --------------------------------------------------------------------- */

/*
 * Exported function to return whether a UTF-8 sequence is legal or not.
 * This is not used here; it's just exported.
 */
BOOL YWLIB_IsLegalUTF8Sequence(const U8 *source, const U8 *sourceEnd)
{
    S32 length = trailingBytesForUTF8[*source]+1;
    if (source+length > sourceEnd)
    {
	return FALSE;
    }
    return YWLIB_IsLegalUTF8(source, length);
}

/* --------------------------------------------------------------------- */

YWLIB_UNIConversionResult_T YWLIB_ConvertUTF8toUTF16 (const U8** sourceStart, const U8* sourceEnd,
	                                                                                   U16** targetStart, U16* targetEnd, YWLIB_UNIConversionFlags_T flags)
{
    YWLIB_UNIConversionResult_T result = YWLIB_UNI_CONVERSION_OK;
    const U8* source = *sourceStart;
    U16* target = *targetStart;
    U16 * pucTargetHead = *targetStart;
    U32 uTargetLen = 0;
    while (source < sourceEnd)
    {
	U32 ch = 0;
	U16 extraBytesToRead = trailingBytesForUTF8[*source];
	if (source + extraBytesToRead >= sourceEnd)
	{
	    result = YWLIB_UNI_SOURCE_EXHAUSTED; break;
	}
	/* Do this check whether lenient or strict */
	if (! YWLIB_IsLegalUTF8(source, extraBytesToRead+1))
	{
	    result = YWLIB_UNI_SOURCE_ILLEGAL;
	    break;
	}
	/*
	 * The cases all fall through. See "Note A" below.
	 */
	switch (extraBytesToRead)
	{
	    case 5: ch += *source++; ch <<= 6; /* remember, illegal UTF-8 */
	    case 4: ch += *source++; ch <<= 6; /* remember, illegal UTF-8 */
	    case 3: ch += *source++; ch <<= 6;
	    case 2: ch += *source++; ch <<= 6;
	    case 1: ch += *source++; ch <<= 6;
	    case 0: ch += *source++;
	}
	ch -= offsetsFromUTF8[extraBytesToRead];

	if (target >= targetEnd)
	{
	    source -= (extraBytesToRead+1); /* Back up source point! */
	    result = YWLIB_UNI_TARGET_EXHAUSTED; break;
	}
	if (ch <= YWLIB_UNI_MAX_BMP)
	{ /* Target is a S8acter <= 0xFFFF */
	    /* UTF-16 surrogate values are illegal in UTF-32 */
	    if (ch >= YWLIB_UNI_SUR_HIGH_START && ch <= YWLIB_UNI_SUR_LOW_END)
	    {
		if (flags == YWLIB_UNI_STRICT_CONVERSION)
		{
		    source -= (extraBytesToRead+1); /* return to the illegal value itself */
		    result = YWLIB_UNI_SOURCE_ILLEGAL;
		    break;
		}
		else
		{
		    *target++ = YWLIB_UNI_REPLACEMENT_CHAR;
		}
	    }
	    else
	    {
		*target++ = (U16)ch; /* normal case */
	    }
	}
	else if (ch > YWLIB_UNI_MAX_UTF16)
	{
	    if (flags == YWLIB_UNI_STRICT_CONVERSION)
	    {
		result = YWLIB_UNI_SOURCE_ILLEGAL;
		source -= (extraBytesToRead+1); /* return to the start */
		break; /* Bail out; shouldn't continue */
	    }
	    else
	    {
		*target++ = YWLIB_UNI_REPLACEMENT_CHAR;
	    }
	}
	else
	{
	    /* target is a S8acter in range 0xFFFF - 0x10FFFF. */
	    if (target + 1 >= targetEnd)
	    {
		source -= (extraBytesToRead+1); /* Back up source point! */
		result = YWLIB_UNI_TARGET_EXHAUSTED; break;
	    }
	    ch -= halfBase;
	    *target++ = (U16)((ch >> halfShift) + YWLIB_UNI_SUR_HIGH_START);
	    *target++ = (U16)((ch & halfMask) + YWLIB_UNI_SUR_LOW_START);
	}
    }
    *sourceStart = source;
    *targetStart = target;
    /*阿拉伯语特殊处理*/
    uTargetLen = YWLIB_ArabicProcess(pucTargetHead, target - pucTargetHead);
    if(uTargetLen > 0)
    {
        if((pucTargetHead + uTargetLen) < targetEnd )
            *targetStart = pucTargetHead + uTargetLen;
        else
            *targetStart = targetEnd -1;
    }
    return result;
}



//add start by zsj 2010-01-07
//Note: The function YWPUBLIC_Utf8To16() is not safe, please note mem space.
YW_ErrorType_T YWPUBLIC_Utf8To16(const S8* in, S32 inLen, S8 *out, S32 outLen)
{
	const U8 *utf8 = (U8 *)in;
	U16 *utf16 = (U16 *)out;
	U16 *utf16End = NULL;

	if (NULL == in || inLen <= 0 || NULL == out || outLen <= 0
		/*|| (outLen - ((outLen % sizeof(U16)) + sizeof(U16))) <= 0*/)
	{
		//printf("parameter error.\n");
		return -1;
	}

	//utf16End = (U16 *)(out + (outLen - ((outLen % sizeof(U16)) + sizeof(U16))));
	utf16End = (U16 *)(out + (outLen - (outLen % sizeof(U16))));

	//YWOS_Trace(YWOS_TRACE_INFO, "out[0x%8x], outLen[%d], utf16[0x%8x], utf16End[0x%8x]\n",
	//	  out, outLen, utf16, utf16End);
	if (YWLIB_UNI_CONVERSION_OK !=
		YWLIB_ConvertUTF8toUTF16(&utf8, utf8 + inLen, &utf16, utf16End, YWLIB_UNI_STRICT_CONVERSION))
	{
		//printf("convert U8 to U16 error.\n");
		return -1;
	}

	return YW_NO_ERROR;
}


//Note: The function YWPUBLIC_Utf16To8() is not safe, please note mem space.
YW_ErrorType_T YWPUBLIC_Utf16To8(const S8* in, S32 inLen, S8 *out, S32 outLen)
{
	const U16 *utf16 = (U16 *)in;
	const U16 *utf16End = NULL;
	U8 *utf8 = (U8 *)out;

	if (NULL == in || inLen <= 0 || NULL == out || outLen <= 0
		/*|| (inLen - ((inLen % sizeof(U16)) + sizeof(U16))) <= 0*/)
	{
		//printf("parameter error.\n");
		return -1;
	}

	//utf16End = (U16 *)(in + (inLen - ((inLen % sizeof(U16)) + sizeof(U16))));
	utf16End = (U16 *)(in + (inLen - (inLen % sizeof(U16))));

	//YWOS_Trace(YWOS_TRACE_INFO, "in[0x%8x], inLen[%d], utf16[0x%8x], utf16End[0x%8x]\n",
		//in, inLen, utf16, utf16End);
	if (YWLIB_UNI_CONVERSION_OK !=
		YWLIB_ConvertUTF16toUTF8(&utf16, utf16End, &utf8, utf8 + outLen, YWLIB_UNI_STRICT_CONVERSION))
	{
		//printf("convert U16 to U8 error.\n");
		return -1;
	}

	return YW_NO_ERROR;
}
//add end by zsj



/*EOF*/
