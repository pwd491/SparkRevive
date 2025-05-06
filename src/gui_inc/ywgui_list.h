#ifndef _YWGUI_LIST_H_20080516_
#define _YWGUI_LIST_H_20080516_

#ifdef __cplusplus
extern "C" {
#endif


//遍历所有节点(顺序遍历)
#define List_ForEach(pos,head)    \
    for ((pos) = (head)->pNext; (pos) != (head); (pos) = (pos)->pNext)

//遍历所有节点(顺序遍历)（允许删除当前节点pos）
#define List_ForEachSafe(pos,next,head)    \
    for ((pos) = (head)->pNext,(next)=(pos)->pNext; (pos) != (head); (pos) = (next),(next)=(next)->pNext)

//遍历所有节点(倒序遍历)
#define List_ReverseForEach(pos,head)    \
    for ((pos) = (head)->pPrev; (pos) != (head); (pos) = (pos)->pPrev)


#define List_Entry(p,type,member)    (type*)((S8 *)(p)-(S32)(&(((type*)0)->member)))

//检查链表是否为空
#define List_Empty(head)    ((head)->pNext==(head))


//声明一个初始化的链表头
#define LIST_HEAD(name)    ListNode name = {&name,&name}

//初始化链表头
#define INIT_LIST_HEAD(pNode)    (pNode)->pPrev=(pNode)->pNext=(pNode);







//把一个新节点插入到pNode之前
extern void List_InsertBefore(ListNode *pNew, ListNode *pNode);

//把一个新节点插入到pNode之后
extern void List_InsertAfter(ListNode *pNew, ListNode *pNode);

//从链表删除一个节点
extern void List_Del(ListNode *entry);

#ifdef __cplusplus
}
#endif

#endif
