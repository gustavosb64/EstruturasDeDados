#ifndef LISTA_GENERALIZADA_H
#define LISTA_GENERALIZADA_H

typedef int elem;
typedef struct node_ Node;
typedef struct list_ List;
typedef union info_ Info;

List* CreateList();
Node* CreateNode();
int AddLastElem(List *list, Info info, char type);
int RemoveLastElem(List *list, Info *info);
int SearchElem(List *list, elem x, int *error);
int SearchElemSubRoutine(Node *node, elem x);
int AreEqual(List *L1, List *L2, int *error);
int AreEqualNodes(Node *node1, Node *node2, int *error);
Node* GetNode(List *list);
int PrintList(List *list);
int PrintNodes(Node *node, int cont);

#endif
