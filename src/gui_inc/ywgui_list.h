#ifndef _YWGUI_LIST_H_20080516_
#define _YWGUI_LIST_H_20080516_

#ifdef __cplusplus
extern "C" {
#endif


//�������нڵ�(˳�����)
#define List_ForEach(pos,head)    \
    for ((pos) = (head)->pNext; (pos) != (head); (pos) = (pos)->pNext)

//�������нڵ�(˳�����)������ɾ����ǰ�ڵ�pos��
#define List_ForEachSafe(pos,next,head)    \
    for ((pos) = (head)->pNext,(next)=(pos)->pNext; (pos) != (head); (pos) = (next),(next)=(next)->pNext)

//�������нڵ�(�������)
#define List_ReverseForEach(pos,head)    \
    for ((pos) = (head)->pPrev; (pos) != (head); (pos) = (pos)->pPrev)


#define List_Entry(p,type,member)    (type*)((S8 *)(p)-(S32)(&(((type*)0)->member)))

//��������Ƿ�Ϊ��
#define List_Empty(head)    ((head)->pNext==(head))


//����һ����ʼ��������ͷ
#define LIST_HEAD(name)    ListNode name = {&name,&name}

//��ʼ������ͷ
#define INIT_LIST_HEAD(pNode)    (pNode)->pPrev=(pNode)->pNext=(pNode);







//��һ���½ڵ���뵽pNode֮ǰ
extern void List_InsertBefore(ListNode *pNew, ListNode *pNode);

//��һ���½ڵ���뵽pNode֮��
extern void List_InsertAfter(ListNode *pNew, ListNode *pNode);

//������ɾ��һ���ڵ�
extern void List_Del(ListNode *entry);

#ifdef __cplusplus
}
#endif

#endif
