#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

typedef struct tree_{
    Node *root;
}Tree;

int main(int argc, char *argv[]){
    Tree *T;
    T = CreateTree();

    AddABB(T, 22);
    AddABB(T, 1);
    AddABB(T, 7);
    AddABB(T, 4);
    AddABB(T, 3);
    AddABB(T, 2);
    AddABB(T, 0);
    AddABB(T, 6);
    AddABB(T, 5);
    AddABB(T, 10);

    PrintEmOrdem(T->root); 
/*
    SearchABB(T->root,4);

    switch(RemoveABB(T, x)){
        case 1: printf("memoria cheia\n");
                break;
        case 2: printf("nao achou\n");
                break;
    }

*/
    elem x;

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
*/
    printf("\n---------------------\n");
    x = 0;
    RemoveNode(T, x);

//  remover(&(T->root), &x);

    PrintEmOrdem(T->root); 

    FreeTree(T->root);
    free(T);

    return 0;
}
