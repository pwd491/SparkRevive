#ifndef __EMU_KEYDB_H__
#define __EMU_KEYDB_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_COMMENT        		24

#define GET_HIWORD(x) (U16)((x&0xFFFF0000 )>>16)
#define GET_LOWWORD(x) (U16)(x&0x0000FFFF)

#define SET_HIWORD(src,dest) dest=((dest&0x0000FFFF )|(src<<16))
#define SET_LOWWORD(src,dest) dest=((dest&0xFFFF0000 )|src)
#define IS_BISS(caid) ((caid&0xFF00)==0x2600)

#if 1
enum
{
	SYS__8B_KEY = 1,
	SYS_16B_KEY	,
	CNX_EXP_KEY	,
	CNX_MOD_KEY	,
	VIA_AES_KEY	,
	DCW_ODD_KEY	,
	DCW_EVN_KEY	,
	CW_EF10_KEY	,
	CW_EF20_KEY	,
	CW_EF21_KEY	,
	CW_EF30_KEY	,
	CW_EF31_KEY	,
	N1_PK_KEY	,
	N2_IDEA_ECM	,
	N2_IDEA_EMM	,
	N2_RSA_ECM	,
	N2_RSA_EMM	,
	N2_VK_EMM_G	,
	N2_VK_ECM	,
	SYS_32B_KEY	,
	MAX_KEY_TYPE
};
#endif

typedef struct {
	unsigned int	provider;  				/* 4 bytes    */
	unsigned short	system_id;  			  /* 2 bytes	 */
	unsigned char	key_type; 				 /* 1 byte. 	*/
	unsigned char	keyid; 					 /* 1 byte  	*/
	unsigned char	*key;		/* 96 bytes	*/
	char				comment[MAX_COMMENT];  /* 14 bytes	*/
} cakey_t;

/* Possible Icon data */
typedef enum {
	RED,
	GREEN,
	YELLOW,
	WHITE,
	BLUE,
	UPDOWN_ARROW,
	LEFTRIGHT_ARROW,
	ENTER,
	LAST_ICON
} KEY_TYPE;



#ifdef __cplusplus
}
#endif

#endif


