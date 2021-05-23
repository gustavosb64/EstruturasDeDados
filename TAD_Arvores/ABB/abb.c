#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

typedef struct node_{
    elem x;
    struct node_ *left;
    struct node_ *right;
}Node;

typedef struct tree_{
    Node *root;
}Tree;

Tree* CreateTree(){
    Tree *T = (Tree *) malloc(sizeof(Tree));
    T->root = NULL;
    return T;
}

int IsEmptyTree(Tree *T){
    if (T->root == NULL) return 1;
    else return 0;
}

int TreeHeight(Node *node){
    int n_left = 0;
    int n_right = 0;

    if (node->left != NULL){
        n_left = TreeHeight(node->left);
    }
    if (node->right != NULL){
        n_right = TreeHeight(node->right);
    }

    if (n_left > n_right) return (n_left+1);
    else return (n_right+1);
}

int IsInABB(Tree *T, elem x){

    if (IsEmptyTree(T)) return 1;

    if (SearchABB(T->root, x) == NULL) return 2;
    return 0;
}

Node* SearchABB(Node *node, elem x){

    if (node == NULL) return NULL;
    
    if (node->x == x){ 
        return node;
    }

    if (node->x > x){
        return SearchABB(node->left, x);
    }

    return SearchABB(node->right, x);
}

int AddABB(Tree *T, elem x){
    return InsertNode(&T->root, x);
}

int InsertNode(Node **node, elem x){

    if (*node == NULL){
        (*node) = (Node *) malloc(sizeof(Node));
        (*node)->x = x;
        (*node)->left = NULL;
        (*node)->right = NULL;

        return 0;
    }
    if (x == (*node)->x) return 1;

    if (x < (*node)->x) InsertNode(&(*node)->left, x);
    else InsertNode(&(*node)->right, x);

    return 0;
}

Node* SearchGreatest(Node *node, Node **aux_node_parent){
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

int RemoveNode(Tree *T, elem x){
    Node *aux_node;

    Node *parent = NULL;
    Node *node = SearchWithParent(T->root, &parent, x);

    if (node->left != NULL && node->right != NULL){

        Node *aux_node_parent = node; 
        aux_node = SearchGreatest(node->left, &aux_node_parent);        

        if (aux_node->left != NULL){
            if (aux_node_parent == node) node->left = aux_node->left;       
            else aux_node_parent->right = aux_node->left;
        }
        else node->left = NULL;

        node->x = aux_node->x;

        free(aux_node);

        return 0;
    }

    if (node->left == NULL && node->right == NULL) aux_node = NULL; 
    else if (node->left != NULL && node->right == NULL) aux_node = node->left;
    else if (node->left == NULL && node->right != NULL) aux_node = node->right;

    if (parent != NULL){
        if (parent->x > node->x) parent->left = aux_node;
        else parent->right = aux_node;
    }
    else T->root = aux_node; 

    free(node);

    return 0;
}

void PrintPreOrdem(Node *node){

    if(node == NULL) return;

    printf("%d\n",node->x);
    if(node->left != NULL) PrintPreOrdem(node->left);
    if(node->right != NULL) PrintPreOrdem(node->right); 

    return;
}

void PrintPosOrdem(Node *node){

    if(node == NULL) return;
    if(node->left != NULL) PrintPreOrdem(node->left);
    if(node->right != NULL) PrintPreOrdem(node->right);
    printf("%d\n",node->x);

    return;
}

void PrintEmOrdem(Node *p){
    if (p != NULL){
        PrintEmOrdem(p->left); 
        printf("%d\n",p->x);
        PrintEmOrdem(p->right); 
    }

    return;
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
