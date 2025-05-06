
#ifndef YWNATIVE_H_
#define YWNATIVE_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __YWDEFS_H
typedef signed char		S8;
typedef unsigned char		U8;
typedef signed short		S16;
typedef unsigned short		U16;
typedef signed int			S32;
typedef unsigned int		U32;

typedef U32				BOOL;
typedef U32 				YW_ErrorType_T;
typedef U32                          YWVFS_FileHandle_T;
#endif

#ifndef YW_NO_ERROR
#define YW_NO_ERROR 0
#endif

#ifndef YW_INFINITE
#define YW_INFINITE  (0xFFFFFFFF)
#endif

#ifndef TRUE
    #define TRUE (1 == 1)
#endif
#ifndef FALSE
    #define FALSE (!TRUE)
#endif

typedef struct YWNATIVE_ListHead_s
{
	struct YWNATIVE_ListHead_s *Next, *Prev;
}YWNATIVE_ListHead_T;

typedef struct YWNATIVE_ChanInfo_s
{
    U16 uChanType;
    U16 uOnId;
    U16 uTsId;
    U16 uSId;
    S8 * pcCcId;
    S8 * pcSrvName;    
}YWNATIVE_ChanInfo_T;

typedef struct YWNATIVE_CompInfo_s
{
    S8 * pcType;
    S8 * pcEncoding;
    S8 * pcAspectRatio;
    S8 * pcLanguage;
    BOOL bEncrypted;
    U8   uAudioChannels;
}YWNATIVE_CompInfo_T;

#define YWNATIVE_LIST_HEAD_INIT(Name) { &(Name), &(Name) }

#define YWNATIVE_LIST_HEAD(Name) \
 YWNATIVE_ListHead_T Name = YWNATIVE_LIST_HEAD_INIT(Name)

#define YWNATIVE_INIT_LIST_HEAD(Ptr) do { \
 (Ptr)->Next = (Ptr); (Ptr)->Prev = (Ptr); \
} while (0)


/**
 * list_entry - get the struct for this entry
 * @ptr: the &struct list_head pointer.
 * @type: the type of the struct this is embedded in.
 * @member: the name of the list_struct within the struct.
 */
#define YWNATIVE_ListEntry(Ptr, Type, Member) \
 ((Type *)((S8 *)(Ptr)-(unsigned long)(&((Type *)0)->Member)))

/**
 * list_for_each - iterate over a list
 * @pos: the &struct list_head to use as a loop counter.
 * @head: the head for your list.
 */
#define YWNATIVE_ListForEach(Pos, Head) \
 for (Pos = (Head)->Next; Pos != (Head); Pos = Pos->Next)

/**
 * list_for_each_safe - iterate over a list safe against removal of list entry
 * @pos: the &struct list_head to use as a loop counter.
 * @n:  another &struct list_head to use as temporary storage
 * @head: the head for your list.
 */
#define YWNATIVE_ListForEachSafe(Pos, n, Head) \
 for (Pos = (Head)->Next, n = Pos->Next; Pos != (Head); \
  Pos = n, n = Pos->Next)

void YWNATIVE_ListAdd(YWNATIVE_ListHead_T *New, YWNATIVE_ListHead_T *Head);
void YWNATIVE_ListAddTail(YWNATIVE_ListHead_T *New, YWNATIVE_ListHead_T *Head);
void YWNATIVE_ListDel(YWNATIVE_ListHead_T *Entry);

enum
{
    YWNATIVE_ERROR_INIT_FAILED=1,
    YWNATIVE_ERROR_NOT_INIT,
    YWNATIVE_ERROR_ALLREADY_INIT,
    YWNATIVE_ERROR_BAD_PARAM,
    YWNATIVE_ERROR_SEND_FAILED,
    YWNATIVE_ERROR_RECV_FAILED
};

//³õÊ¼»¯native
YW_ErrorType_T YWNATIVE_Init(void);
//Ïú»Ùnative
YW_ErrorType_T YWNATIVE_Term(void);
void YWNATIVE_AddVodEventListener(void* listener);
void YWNATIVE_AddBroadcastEventListener(void * listener);
void YWNATIVE_AddHbbtvEventListener(void* listener);
void YWNATIVE_AddPmtEventListener(void* listener);
void YWNATIVE_AddDsmccEventListener(void* listener);
void YWNATIVE_AddHbbtvSurfaceCheckCallBack(void* callback);
YW_ErrorType_T YWNATIVE_GetFreeHandle(S8* pcType, U32 * identifier);
YW_ErrorType_T YWNATIVE_ReleaseHandle(U32 identifier);
YW_ErrorType_T YWNATIVE_AvPLay(U32 Identifier, U8 * url, U16* videoPId, U16 * audioPid, U16 * pcrPid, U32 * pos, U32 * speed, U8 *videoCodec, U8 * audioCodec, U8 * container);
YW_ErrorType_T YWNATIVE_AvStop(U32 identifier);
YW_ErrorType_T YWNATIVE_AvPause(U32 identifier);
YW_ErrorType_T YWNATIVE_AvResume(U32 identifier);
YW_ErrorType_T YWNATIVE_AvGetDuration(U32 identifier, U32* duration);
YW_ErrorType_T YWNATIVE_AvGetState(U32 identifier, S32* state);
YW_ErrorType_T YWNATIVE_AvGetPos(U32 identifier, U32* pos);
YW_ErrorType_T YWNATIVE_AvSetPos(U32 identifier, U32 pos);
YW_ErrorType_T YWNATIVE_AvSetWin(U32 identifier, S16 x, S16 y, S16 w, S16 h);
YW_ErrorType_T YWNATIVE_AvSetVol(U32 identifier, U8 vol);
YW_ErrorType_T YWNATIVE_AvGetVol(U32 identifier, U8 * vol);
YW_ErrorType_T YWNATIVE_AvSetSpeed(U32 identifier, S32  speed);
YW_ErrorType_T YWNATIVE_AvGetSpeed(U32 identifier, S32  *speed);
YW_ErrorType_T YWNATIVE_AvMute(U32 identifier, BOOL bMute);
YW_ErrorType_T YWNATIVE_AvSetDigMode(U32 identifier, U8 * mod);//"Off/Compressed/NonCompressed"
YW_ErrorType_T YWNATIVE_AvSetLoop(U32 identifier, U32 cout);
YW_ErrorType_T YWNATIVE_AvSetVisible(U32 identifier, BOOL bVisible);
YW_ErrorType_T YWNATIVE_AvSetFullScreen(U32 identifier, BOOL bFullScreen);
YW_ErrorType_T YWNATIVE_AvGetFullScreen(U32 identifier, BOOL * bFullScreen);
YW_ErrorType_T YWNATIVE_AvGetNrTracks(U32 identifier, U8 * count);
YW_ErrorType_T YWNATIVE_AvGetCurTrackIndex(U32 identifier, U8 * index);
YW_ErrorType_T YWNATIVE_AvSetCurTrackIndex(U32 identifier, U8  index);
YW_ErrorType_T YWNATIVE_AvGetComponents(U32 identifier, U8 * type, U8 * count, U32 ** HandleList);
YW_ErrorType_T YWNATIVE_GetComponentInfo(U32 identifier, YWNATIVE_CompInfo_T  * pstCompoInfo);
YW_ErrorType_T YWNATIVE_AvGetCurActiveComponents(U32 identifier, U8 * type, U8 * count, U32 ** HandleList);
YW_ErrorType_T YWNATIVE_AvSelectComponent(U32 identifier, U32 componentHdl);
YW_ErrorType_T YWNATIVE_AvUnSelectComponent(U32 identifier, U32 componentHdl);
YW_ErrorType_T YWNATIVE_AitStart(void);
YW_ErrorType_T YWNATIVE_AitStop(void);
YW_ErrorType_T YWNATIVE_AitInvalidate(void);
YW_ErrorType_T YWNATIVE_PmtStart(U16 uServiceId);
YW_ErrorType_T YWNATIVE_PmtStop(U16 uServiceId);
YW_ErrorType_T YWNATIVE_DsmccStart(U16 uPid);
YW_ErrorType_T YWNATIVE_DsmccStop(U16 uPid);
YW_ErrorType_T YWNATIVE_GetCurrentChannel(U32 identifier, U32* puChanHandle);
YW_ErrorType_T YWNATIVE_GetChanInfo(U32 identifier, YWNATIVE_ChanInfo_T  * pstChanInfo);
YW_ErrorType_T YWNATIVE_GetChannelList(U32 * uCount, U32** handleList);
YW_ErrorType_T YWNATIVE_SetChannel(U32 identifier, U32 channelHandle, BOOL bTrackPlay);
YW_ErrorType_T YWNATIVE_PrevChannel(U32 identifier);
YW_ErrorType_T YWNATIVE_NextChannel(U32 identifier);
YW_ErrorType_T YWNATIVE_CreateChannelObject3(U32 identifier, U16 idType, S8 *dsd, U16 sid, U32 * chanHandle);
YW_ErrorType_T YWNATIVE_CreateChannelObject6(U32 identifier, U16 idType, U16* puOnId, U16* puTsId, U16* puSId, U16* puSourceId, S8 *ipBroadcastId, U32 * chanHandle);
YW_ErrorType_T YWNATIVE_GetProgrammes(U32 identifier, U32  * uCount,  U32** handleList);
YW_ErrorType_T YWNATIVE_GetProgName(U32 identifier, S8 ** pcName);
YW_ErrorType_T YWNATIVE_GetProgDesc(U32 identifier, S8 ** pcDesc);
YW_ErrorType_T YWNATIVE_GetProgStartTime(U32 identifier, U32 * puStartTime);
YW_ErrorType_T YWNATIVE_GetProgDuration(U32 identifier, U32 * puDuration);
YW_ErrorType_T YWNATIVE_GetProgChanId(U32 identifier, S8 ** pcChanId);
YW_ErrorType_T YWNATIVE_GetProgRating(U32 identifier, U32 * uCount, U32** handleList);
YW_ErrorType_T YWNATIVE_CreatProg(U32* puIndetifer);
YW_ErrorType_T YWNATIVE_ReleaseProg(U32 identifier);
YW_ErrorType_T YWNATIVE_SetProgName(U32 identifier, S8 * pcName);
YW_ErrorType_T YWNATIVE_SetProgDesc(U32 identifier, S8 * pcDesc);
YW_ErrorType_T YWNATIVE_SetProgStartTime(U32 identifier, U32 uStartTime);
YW_ErrorType_T YWNATIVE_SetProgDuration(U32 identifier, U32 uDuration);
YW_ErrorType_T YWNATIVE_SetProgChanId(U32 identifier, S8 * pcChanId);
YW_ErrorType_T YWNATIVE_NotifyHbbtvStateChanged(S8 * state);
void YWNATIVE_SetHbbtvAppData(U16 * pAppId, U32* pOrgId, void * pHbbtvWin);

#ifdef __cplusplus
}
#endif

#endif

