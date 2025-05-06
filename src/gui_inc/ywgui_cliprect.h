#ifndef _YWGUI_CLIPRECT_H_20080421_
#define  _YWGUI_CLIPRECT_H_20080421_

#ifdef __cplusplus
extern "C" {
#endif 

/**************************常数定义***************************/

/**************************宏定义*****************************/

/***************************类型定义**************************/

typedef struct YWGUI_ClipRect_s
{
     /* The clipping rectangle itself.     */
    YWGUI_Rect_T rc;
    
    /**  The next clipping rectangle.     */
    struct YWGUI_ClipRect_s* next;

    /* The previous clipping rectangle.*/
    struct YWGUI_ClipRect_s* prev;
} YWGUI_ClipRect_T;
typedef YWGUI_ClipRect_T* YWGUI_ClipRect_P;

typedef struct YWGUI_ClipRgn_s
{

   /*** The bounding rect of the region.    */
    YWGUI_Rect_T            rcBound;
   
   /** * Head of the clipping rectangle list.    */
    YWGUI_ClipRect_P       pHead;
   
   /** * Tail of the clipping rectangle list.    */
    YWGUI_ClipRect_P       pTail;
   
   /**    * The private block data heap used to allocate clipping rectangles.    */
    YWGUI_BlockHeap_P      ptHeap;
} YWGUI_ClipRgn_T;

typedef YWGUI_ClipRgn_T* YWGUI_ClipRgn_P;

typedef struct YWGUI_InvRgn_s
{
    YWGUI_MutexID_T         lock;
    YWGUI_ClipRgn_T         rgn;
    BOOL                    bEraseBkgnd;
} YWGUI_InvRgn_T;
typedef YWGUI_InvRgn_T* YWGUI_InvRgn_P;

typedef struct YWGUI_InvInfo_s
{
    YWGUI_InvRgn_T tWindowInvRgn;       //窗口坐标系
    YWGUI_InvRgn_T tClientInvRgn;       //客户区坐标系
}YWGUI_InvInfo_T;

typedef struct YWGUI_GcrInfo_s
{
    YWGUI_MutexID_T             lock;
    YWGUI_ClipRgn_T             crgn;
    U32                         age;
} YWGUI_GcrInfo_T;
typedef YWGUI_GcrInfo_T* YWGUI_GcrInfo_P;



/**************************宏函数定义*****************************/
#define YWGUI_FreeClipRect(heap, pClipRect)   BlockDataFree (heap, pClipRect)
#define YWGUI_ClipRectAlloc(heap)             BlockDataAlloc (heap)

#define YWGUI_LockGcrInfo(ptGcrInfo)    YWGUI_MutexWait((ptGcrInfo)->lock)
#define YWGUI_UnlockGcrInfo(ptGcrInfo)  YWGUI_MutexSend((ptGcrInfo)->lock)

/****************************函数声明************************/



extern void  YWGUI_InitClipRgn (YWGUI_ClipRgn_T *pRgn,YWGUI_BlockHeap_T * ptHeap);
extern BOOL  YWGUI_SetClipRgn (YWGUI_ClipRgn_T* pRgn, const YWGUI_Rect_T* pRect);
extern void  YWGUI_EmptyClipRgn (YWGUI_ClipRgn_T* pRgn);
extern BOOL  YWGUI_CopyRegion (YWGUI_ClipRgn_T* pDstRgn, const YWGUI_ClipRgn_T* pSrcRgn);


extern BOOL YWGUI_SubtractClipRect (YWGUI_ClipRgn_T* pRegion, const YWGUI_Rect_T* pRect);
extern BOOL  YWGUI_AddClipRect (YWGUI_ClipRgn_T* pRegion, const YWGUI_Rect_T *pRect);
extern BOOL  YWGUI_IntersectClipRect (YWGUI_ClipRgn_T* pRegion, const YWGUI_Rect_T* pRect);

extern BOOL  SubtractRegion (YWGUI_ClipRgn_T *pDestRgn, const YWGUI_ClipRgn_T *pMinuendRgn, const YWGUI_ClipRgn_T *pSubtrahendRgn);
extern BOOL  UnionRegion (YWGUI_ClipRgn_T *dst, const YWGUI_ClipRgn_T *src1, const YWGUI_ClipRgn_T *src2);
extern BOOL  IntersectRegion (YWGUI_ClipRgn_T *dst, const YWGUI_ClipRgn_T *src1, const YWGUI_ClipRgn_T *src2);

#ifdef __cplusplus
}
#endif 

#endif

