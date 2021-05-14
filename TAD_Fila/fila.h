#ifndef FILA_H
#define FILA_H

typedef int elem;
typedef struct fila_ Fila;

void Cria(Fila *F);
void Esvazia(Fila *F);
int EstaVazia(Fila *F);
int EstaCheia(Fila *F);
void Entra(Fila *F, elem x, int *error);
void Sai(Fila *F, elem *x, int *error);
int EstaOrdenada(Fila F);

#endif
