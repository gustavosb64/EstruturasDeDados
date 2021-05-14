#ifndef PILHA_H
#define PILHA_H

typedef int elem;

typedef struct pilha_ Pilha;

void Create(Pilha *P);
void Empty(Pilha *P);
int IsEmpty(Pilha P);
int IsFull(Pilha P);
void Push(Pilha *P, elem *x, int *error);
void Pop(Pilha *P, elem *x, int *error);
elem Top(Pilha P, elem *x, int *error);
void Print(Pilha P, int *error);
int AreEqual(Pilha P1, Pilha P2, int *error);
void Reverse(Pilha *P1, int *error);

#endif
