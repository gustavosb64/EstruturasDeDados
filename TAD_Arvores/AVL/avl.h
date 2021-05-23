#ifndef AVL_H
#define AVL_H

typedef int elem;
typedef struct node_ Node;
typedef struct tree_ Tree;

Tree* CreateTree();
Node* RotRR(Node **node);
Node* RotLL(Node **node);
Node* RotLR(Node **node);
Node* RotRL(Node **node);
int BF(Node *node);
Node* ReBalance(Node **node);
int IsEmptyTree(Tree *T);
int TreeHeight(Node *node);
int IsInAVL(Tree *T, elem x);
Node* SearchAVL(Node *node, elem x);
Node* SearchLargest(Node *node);
int AddAVL(Tree *T, elem x);
int RemoveAVL(Tree *T, elem x);
int InsertNode(Node **node, elem x);
int RemoveNode(Node **node, elem x);
void FreeTree(Node *node);

void em_ordem(Node *node);
void pre_ordem(Node *p);
void pos_ordem(Node *p);

//---------------------------------------//
Node* SearchParent(Node *node, elem x);
Node* SearchLargestWithParent(Node *node, Node **aux_node_parent);
Node* SearchWithParent(Node *node, Node **aux_node_parent, elem x);

#endif
