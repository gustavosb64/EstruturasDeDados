#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

typedef struct tree_{
    Node *root;
}Tree;

int main(int argc, char *argv[]){
    Tree *T;
    T = CreateTree();

    AddAVL(T, 7);
    AddAVL(T, 4);
    AddAVL(T, 8);
    AddAVL(T, 1);
    AddAVL(T, 5);
    AddAVL(T, 22);
    AddAVL(T, 7);
    AddAVL(T, 10);
    AddAVL(T, 1);
    AddAVL(T, 0);
    AddAVL(T, 4);
    AddAVL(T, 5);
    AddAVL(T, 3);
    AddAVL(T, 2);
    AddAVL(T, 6);
    AddAVL(T, 8);
    AddAVL(T, 20);

    printf("Em ordem: \n");
    em_ordem(T->root); 
    printf("\n---------------------\n");
    printf("Pre ordem: \n");
    pre_ordem(T->root); 
    printf("\n---------------------\n");
    printf("Pos ordem: \n");
    pos_ordem(T->root); 
    printf("\n---------------------\n");
 

    elem x = 4;
    SearchAVL(T->root,x);

    switch(RemoveAVL(T, x)){
        case 1: printf("memoria cheia\n");
                break;
        case 2: printf("nao achou\n");
                break;
    }

    printf("Remove 4. Em ordem: \n");
    em_ordem(T->root); 
    printf("\n---------------------\n");
 

    x = 3;
    RemoveNode(&T->root, x);
    x = 8;
    RemoveNode(&T->root, x);
    x = 7;
    RemoveNode(&T->root, x);
    x = 5;
    RemoveNode(&T->root, x);
    x = 4;
    RemoveNode(&T->root, x);
    x = 22;
    RemoveNode(&T->root, x);
    x = 0;
    RemoveNode(&T->root, x);
    printf("Em ordem: \n");
    em_ordem(T->root); 

    printf("\n---------------------\n");
    x = 1;
    RemoveNode(&T->root, x);
    x = 2;
    RemoveNode(&T->root, x);
    x = 6;
    RemoveNode(&T->root, x);
    x = 10;
    RemoveNode(&T->root, x);
    x = 20;
    RemoveNode(&T->root, x);

    printf("Em ordem: \n");
    em_ordem(T->root); 

    //Removendo elementos inexistentes
    RemoveNode(&T->root, x);
    RemoveNode(&T->root, x);
    RemoveNode(&T->root, x);

    FreeTree(T->root);
    free(T);

    return 0;
}
