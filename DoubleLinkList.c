#include<malloc.h>
#include"DoubleLinkList.h"

PNode MakeNode(Car car)
{
    PNode p = NULL;
    p = (PNode)malloc(sizeof(Node));
    if (p != NULL)
    {
        p->car = car;
        p->previous = NULL;
        p->next = NULL;
    }
    return p;
}

void FreeNode(PNode p)
{
    if (!p)
        free(p);
}

Car invliad = { -1, -1, 0 };
DList* InitList()
{
    DList *plist = (DList *)malloc(sizeof(DList));
    PNode head = MakeNode(invliad);
    if (plist != NULL)
    {
        if (head != NULL)
        {
            plist->head = head;
            plist->tail = head;
            plist->size = 0;
        }
        else
            return NULL;
    }
    return plist;
}

void DestroyList(DList *plist)
{
    ClearList(plist);
    free(plist->head);
    free(plist);
}

int IsEmpty(DList *plist)
{
    if (plist->size == 0 && plist->tail == plist->head)
        return 1;
    else
        return 0;
}

void ClearList(DList *plist)
{
    PNode temp, p = plist->tail;
    while (!IsEmpty(plist))
    {
        temp = p->previous;
        FreeNode(p);
        p = temp;
        temp->next = NULL;
        plist->tail = temp;
        plist->size--;
    }
}

PNode DelFirst(DList *plist)
{
    PNode head = plist->head;
    PNode p = head->next;
    if (p != NULL)
    {
        if (p == plist->tail)
            plist->tail = p->previous;
        head->next = p->next;
        if (head->next)
            head->next->previous = head;
        plist->size--;
    }
    return p;
}

PNode GetFirst(DList* plist)
{
    PNode head = plist->head;
    return head->next;
}

PNode InsLast(DList *plist, PNode s)
{
    PNode tail = plist->tail;
    s->next = tail->next;
    s->previous = tail;
    tail->next = s;
    plist->tail = s;
    plist->size++;
    return s;
}

void ListTraverse(DList *plist, void(*visit)(Car))
{
    PNode p = plist->head;
    if (! IsEmpty(plist))
    {
        while (p->next != NULL)
        {
            p = p->next;
            visit(p->car);
        }
    }
}
