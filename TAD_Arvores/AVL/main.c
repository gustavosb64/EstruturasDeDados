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
    em_ordem(T->root); 
    printf("\n---------------------\n");
    pre_ordem(T->root); 
    printf("\n---------------------\n");
    pos_ordem(T->root); 
    printf("\n---------------------\n");
/*
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


    em_ordem(T->root); 
    printf("\n---------------------\n");
    pre_ordem(T->root); 
*/

/*
    T->root = RotRL(&(T->root));

    SearchAVL(T->root,4);

    switch(RemoveAVL(T, x)){
        case 1: printf("memoria cheia\n");
                break;
        case 2: printf("nao achou\n");
                break;
    }

    elem x;

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
    printf("\n---------------------\n");
    pre_ordem(T->root); 
*/
/*
    printf("\n---------------------\n");
    x = 4;
    RemoveNode(T, x);
    printf("\n---------------------\n");
    x = 7;
    RemoveNode(T, x);
    printf("\n---------------------\n");
    x = 22;
    RemoveNode(T, x);
    printf("\n---------------------\n");
    x = 22;

//  remover(&(T->root), &x);

    PrintEmOrdem(T->root); 

*/
    FreeTree(T->root);
    free(T);

    return 0;
}
