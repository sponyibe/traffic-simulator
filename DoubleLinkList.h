#ifndef DOUBLELINKLIST_H
#define DOUBLELINKLIST_H

#include "Car.h"

typedef struct Node* PNode;
typedef struct Node
{
    Car car;
    PNode previous;
    PNode next;
} Node;

// The type for link list 
typedef struct
{
    PNode head;
    PNode tail;
    int size;
} DList;

PNode   MakeNode(Car car);
void    FreeNode(PNode p);
DList*  InitList();
void    DestroyList(DList *plist);
void    ClearList(DList *plist);
PNode   GetFirst(DList *plist);
int     IsEmpty(DList *plist);
PNode   DelFirst(DList *plist);
PNode   InsLast(DList *plist, PNode s);
void    ListTraverse(DList *plist, void(*visit)(Car));

#endif
