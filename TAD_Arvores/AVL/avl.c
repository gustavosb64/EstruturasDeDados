#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

struct node_{
    elem x;
    struct node_ *left;
    struct node_ *right;
};

struct tree_{
    Node *root;
};

Tree* CreateTree(){
    Tree *T = (Tree *) malloc(sizeof(Tree));
    T->root = NULL;
    return T;
}

Node* RotRR(Node **node){

    Node *aux_node = (*node)->left;
    (*node)->left = aux_node->right;
    aux_node->right = (*node);
    
    return aux_node;
}

Node* RotLL(Node **node){

    Node *aux_node = (*node)->right;
    (*node)->right = aux_node->left;
    aux_node->left = (*node);
    
    return aux_node;
}

Node* RotLR(Node **node){
    (*node)->left = RotLL(&(*node)->left);
    (*node) = RotRR(node);

    return (*node);
}

Node* RotRL(Node **node){
    (*node)->right = RotRR(&(*node)->right);
    (*node) = RotLL(node);

    return (*node);
}

int BF(Node *node){

    if (node == NULL) return 0;

    int h_left, h_right;
    
    h_left = TreeHeight(node->left); 
    h_right = TreeHeight(node->right); 

    return (h_right - h_left); 
}

Node* ReBalance(Node **node){
    int n_bf = BF(*node);

    if (n_bf >= 2){
        if (BF((*node)->right) < 0) (*node) = RotRL(node);
        else (*node) = RotLL(node);
    }
    else if(n_bf <= -2){
        if (BF((*node)->left) > 0) (*node) = RotLR(node);
        else (*node) = RotRR(node);
    }

   return (*node);
}

int IsEmptyTree(Tree *T){
    if (T->root == NULL) return 1;
    else return 0;
}

int TreeHeight(Node *node){

    if (node == NULL) return 0;

    int n_left = 0;
    int n_right = 0;

    if (node->left != NULL) n_left = TreeHeight(node->left);
    if (node->right != NULL) n_right = TreeHeight(node->right);

    if (n_left > n_right) return (n_left+1);
    else return (n_right+1);
}

int IsInAVL(Tree *T, elem x){

    if (IsEmptyTree(T)) return 1;

    if (SearchAVL(T->root, x) == NULL) return 2;
    return 0;
}

Node* SearchAVL(Node *node, elem x){

    if (node == NULL) return NULL;
    
    if (node->x == x) return node;

    if (node->x > x) return SearchAVL(node->left, x);

    return SearchAVL(node->right, x);
}

Node* SearchLargest(Node *node){    
    Node *aux_node = node;

    while (aux_node->right != NULL) 
        aux_node = aux_node->right;

    return aux_node;
}

int AddAVL(Tree *T, elem x){
    return InsertNode(&T->root, x);
}

int RemoveAVL(Tree *T, elem x){
    return RemoveNode(&T->root,x);
}

int InsertNode(Node **node, elem x){

    if (*node == NULL){
        (*node) = (Node *) malloc(sizeof(Node));
        (*node)->x = x;
        (*node)->left = NULL;
        (*node)->right = NULL;
        
        return 0;
    }
    else if (x == (*node)->x) return 1;

    if (x < (*node)->x) InsertNode(&(*node)->left, x);
    else if (x > ((*node)->x)) InsertNode(&(*node)->right, x);

    (*node) = ReBalance(node);

    return 0;
}

int RemoveNode(Node **node, elem x){

    if ((*node) == NULL) return 1;
    if ((*node)->x > x){
        RemoveNode(&(*node)->left, x);
        ReBalance(&(*node));
        return 0;
    }
    if ((*node)->x < x){
        RemoveNode(&(*node)->right, x);
        ReBalance(&(*node));
        return 0;
    }

    if ((*node)->left != NULL && (*node)->right != NULL){ 
        Node *left_largest = SearchLargest((*node)->left);
        (*node)->x = left_largest->x;
        RemoveNode(&(*node)->left, (*node)->x);

        return 0;
    }

    Node *aux_node;

    if ((*node)->left == NULL && (*node)->right == NULL) aux_node = NULL; 
    else if ((*node)->left != NULL && (*node)->right == NULL) aux_node = (*node)->left;
    else if ((*node)->left == NULL && (*node)->right != NULL) aux_node = (*node)->right;
 
    Node *aux_node2;
    aux_node2 = (*node);
    (*node) = aux_node;
 
    free(aux_node2);

    return 0;
}

void FreeTree(Node *p){
    if (p != NULL){
        FreeTree(p->left); 
        Node *p_aux = p->right;
        free(p);
        FreeTree(p_aux); 
    }

    return;
}

void em_ordem(Node *p){
    if (p != NULL){
        em_ordem(p->left); 
        printf("%d\n",p->x);
        em_ordem(p->right); 
    }

    return;
}

void pre_ordem(Node *p){
    if (p != NULL){
        printf("%d\n",p->x);
        pre_ordem(p->left);
        pre_ordem(p->right);
    }

    return;
}

void pos_ordem(Node *p){
    if (p != NULL){
        em_ordem(p->left);
        em_ordem(p->right);
        printf("%d\n",p->x);
    }

    return;
}

//-----------------------------------------------//
Node* SearchParent(Node *node, elem x){

    if (node == NULL) return NULL;
    
    if ((node->left != NULL && node->left->x == x) || (node->right != NULL && node->right->x == x)){ 
        return node;
    }

    if (node->x > x){
        return SearchParent(node->left, x);
    }

    return SearchParent(node->right, x);

}

Node* SearchLargestWithParent(Node *node, Node **aux_node_parent){
    Node *aux_node = node;

    while (aux_node->right != NULL){    
        *aux_node_parent = aux_node;
        aux_node = aux_node->right;
    }

    return aux_node;
}

Node* SearchWithParent(Node *node, Node **parent, elem x){

    if (node == NULL) return NULL;
    
    if (node->x == x){ 
        return node;
    }

    (*parent) = node; 

    if (node->x > x){
        return SearchWithParent(node->left, &(*parent), x);
    }

    return SearchWithParent(node->right,&(*parent), x);

}

/*
void PrintEmOrdem(Node *node){

    if(node == NULL) return;

    if(node->left != NULL){
        printf("left\n");
        PrintPreOrdem(node->left);
    }
    printf("%d\n",node->x);
    if(node->right != NULL){
        printf("right\n");
        PrintPreOrdem(node->right);
    }

    printf("return\n");
    return;
}
*/
