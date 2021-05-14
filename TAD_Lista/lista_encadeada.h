#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

typedef int elem;

typedef struct node_ Node;
typedef struct list_ List;

List* CreateList();
int IsEmpty(List *list);
int AddLastElem(List *list, elem e);
int AddFirstElem(List *list, elem e);
int AddMiddleElem(List *list, elem e, int index);
int RemoveLastElem(List *list, elem *e);
int RemoveFirstElem(List *list, elem *e);
int RemoveOddEven(List *list, elem *e);
int InList(List *list, elem e);
Node* SearchElem(List *list, elem e, int *error, int *index);
int SearchRemoveElem(List *list, elem *e, elem *dest_elem);
int IndexRemoveElem(List *list, elem *e, int index);
int RemoveMiddleElem(Node *node, elem *e);
int PrintList(List *list);

#endif
