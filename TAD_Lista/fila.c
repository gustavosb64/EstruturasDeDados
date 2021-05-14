#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
 
typedef struct fila_{
    int ini, fim, total;
    elem val[TamFila];
}Fila;

void Cria(Fila *F){
    F->ini = 0;
    F->fim = 0;
    F->total = 0; 
}

void Esvazia(Fila *F){
    F->ini=0;
    F->fim=0;
    F->val[F->ini] = 0;
    F->total = 0; 
}

int EstaVazia(Fila *F){
    if (F->total) return 1;
    else return 0;
}

int EstaCheia(Fila *F){
    if (F->total == TamFila) return 1;
    else return 0;
}

void Entra(Fila *F, elem x, int *error){

    if(EstaCheia(F)){
        *error = 1;
        return;
    } 

    F->val[F->fim] = *x;
    if(F->fim == TamFila-1) F->fim = 0;
    else F->fim++;

    F->total++;
    *erro = 0;
 
    return;
}

void Sai(Fila *F, elem *x, int *error){

    if(EstaVazia(F)){
        *error = 1;
        return;
    } 

    *x = F->val[F->ini];
    if(F->ini == TamFila-1) F->ini = 0;
    else F->ini++;

    F->total--;
    *erro = 0;
 
    return;
}

int EstaOrdenada(Fila F){
    
    if(EstaVazia(&F)){
        *error = 1;
        return;
    } 
    
    elem x,y;
    int local_err;

    Pop(&F, &x, &local_err);
    while(!EstaVazia(&F)){

        Pop(&F, &y, &local_err);

        if (x > y) return 0;
        else x = y;
    }

    return 1;
}
