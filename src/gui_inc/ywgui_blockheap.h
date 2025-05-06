#ifndef _YWGUI_BLOCKHEAP_H_20080416_
#define  _YWGUI_BLOCKHEAP_H_20080416_

#ifdef __cplusplus
extern "C" {
#endif 


#define BDS_FREE        0x0000
#define BDS_SPECIAL     0x0001
#define BDS_USED        0x0002


typedef struct YWGUI_BlockHeap_s
{
    YWGUI_MutexID_T  lock;
    
    YWGUI_Size_T          element_size;
    
    YWGUI_Size_T          heap_size;//¼´ÔªËØ¸öÊý
    
    /**     * The first free element in the heap.     */
    S32             free;
    
    void*           pHeapMem;
} YWGUI_BlockHeap_T;
typedef YWGUI_BlockHeap_T* YWGUI_BlockHeap_P;



#define InitClipRectHeap(heap, size)    \
                InitBlockDataHeap (heap, sizeof (YWGUI_ClipRect_T), size)
                
#define FreeClipRectHeap(heap)  DestroyBlockDataHeap(heap)

extern void InitBlockDataHeap (YWGUI_BlockHeap_P heap, YWGUI_Size_T bd_size, YWGUI_Size_T heap_size);
extern void DestroyBlockDataHeap (YWGUI_BlockHeap_P heap);
extern void* BlockDataAlloc (YWGUI_BlockHeap_P heap);
extern void BlockDataFree (YWGUI_BlockHeap_P heap, void* data);

#ifdef __cplusplus
}
#endif 

#endif

