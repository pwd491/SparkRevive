#ifndef _YWGUI_HASH_H_20080417_
#define  _YWGUI_HASH_H_20080417_

#ifdef __cplusplus
extern "C" {
#endif 

#define HASHTABLE_MIN_SIZE      32          
#define HASHTABLE_MAX_SIZE      40960

#define HASH_THREAD_SAFE        0x00000001  
#define HASH_RESIZABLE          0x00000002

typedef unsigned int GHANDLE;

typedef GHANDLE (*HASHFUNC)  (GHANDLE key);
typedef BOOL    (*EQUALFUNC) (GHANDLE keya, GHANDLE keyb);

typedef struct _HASHNODE
{
    GHANDLE key;
    GHANDLE value;
    struct _HASHNODE *next;
} HASHNODE;

typedef struct _HASHTABLE
{
    DWORD      dwFlags;

    HASHNODE   **pNodes;
    YWGUI_Size_T     size;
    S32        nrNodes;

    HASHFUNC   pfnHash;
    EQUALFUNC  pfnEqual;


    YWGUI_MutexID_T  lock;

} HASHTABLE;

extern HASHTABLE* HashTableCreate (void* memStart, YWGUI_Size_T hash_size, BOOL bThreadSafe,
                            HASHFUNC hash_func, EQUALFUNC equal_func);
extern S32 HashTableInsert (HASHTABLE *hash_table, GHANDLE key, GHANDLE value);
extern void HashTableDestroy (HASHTABLE *hash_table);
extern GHANDLE HashTableLookup (HASHTABLE *hash_table, GHANDLE key);
extern GHANDLE HashTableQuery (HASHTABLE *hash_table, S32 index);
extern BOOL       HashTableRemove (HASHTABLE *hash_table, GHANDLE key);
extern YWGUI_Size_T HashTableSize (HASHTABLE *hash_table);

#ifdef __cplusplus
}
#endif 

#endif


