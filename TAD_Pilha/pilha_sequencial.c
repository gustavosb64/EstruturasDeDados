#include <stdio.h>
#include <stdlib.h>
#include "pilha_sequencial.h"

#define SIZE 4096

typedef struct pilha_{
    elem val[SIZE];
    int n_elem;
}Pilha;

void Create(Pilha *P){
    P->n_elem = 0;
    return;
}

void Empty(Pilha *P){
    P->n_elem = 0;
    return;
}

int IsEmpty(Pilha *P){
    if (P->n_elem == 0) return 1;
    else return 0;
}

int IsFull(Pilha *P){
    if (P->n_elem == SIZE) return 1;
    else return 0;
}

void Push(Pilha *P, elem *x, int *error){
    
    if (IsFull(P)){
        *error = 1;
        return;
    }

    P->val[P->n_elem - 1] = x;
    P->n_elem++;

    return;
}

void Pop(Pilha *P, elem *x, int *error){
    
    if (IsEmpty(P)){
        *error = 1;
        return;
    }

    *x = P->val[P->n_elem - 1];
    P->n_elem--;

    return;
}

void Top(Pilha *P, elem, *x, int *error){
    
    if (IsEmpty(P)){
        *error = 1;
        return;
    }
    *x = P->val[P->n_elem - 1];

    return;
}

void Print(Pilha P, int *error){
    elem x;

    while (!IsEmpty(&P)){
        Pop(&P, &x, error); 
        printf("%d\n",x);
    }

    return;
}

int AreEqual(Pilha P1, Pilha P2, int *error){
    elem x1, x2;
    int error1, error2;

    while (!IsEmpty(&P1) && !IsEmpty(&P2)){
        Pop(&P1, &x1, error1); 
        Pop(&P2, &x2, error2); 
        if (x1 != x2 || error1 != error1) return 0;
    }

    return 1;
}

void Reverse(Pilha *P, int *error){

    if (IsEmpty(P)){
        *error = 1;
        return;
    }

    Pilha *Paux = (Pilha) malloc(1 * sizeof(Pilha));;
    Create(P);
    int local_error;

    while (!IsEmpty){
        Pop(P, Paux[Paux->n_elem], &local_error);
        Paux->n_elem++;
    } 

    P = Paux;

    return;
}
