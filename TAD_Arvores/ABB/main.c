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
    elem x;

    printf("\n---------------------\n");
    printf("Removendo 0:\n");
    x = 0;
    RemoveNode(T, x);
    PrintEmOrdem(T->root); 
    printf("\n---------------------\n");
    printf("Removendo 22:\n");
    x = 22;
    RemoveNode(T, x);
    PrintEmOrdem(T->root); 
    printf("\n---------------------\n");
    printf("Removendo 5:\n");
    x = 5;
    RemoveNode(T, x);
    PrintEmOrdem(T->root); 

    FreeTree(T->root);
    free(T);

    return 0;
}
