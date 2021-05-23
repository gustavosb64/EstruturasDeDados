#include <stdio.h>
#include <stdlib.h>

#define B 11
#define hashing(k) (k%B)

typedef int elem;

typedef struct hash_{
    elem info;
    struct hash_ *next;
}Hash;

typedef struct h_list_{
    Hash *first;
}H_List;

H_List* CreateHash(int n){
    H_List *HL = (H_List *) malloc(n * sizeof(H_List));
    for (int i=0; i<n; i++) 
        HL[i].first = NULL;

    return HL;
}

int Insert(H_List **HL, elem k){
    int i = hashing(k);

    if((*HL)[i].first == NULL){
        Hash *H = (Hash *) malloc(sizeof(Hash));
        H->info = k;
        H->next = NULL; 

        (*HL)[i].first = H;
        return 0;
    } 

    Hash *H_aux = (*HL)[i].first;

    if (H_aux->info == k) return 1;
    while (H_aux->next != NULL){
        H_aux = H_aux->next;
        if (H_aux->info == k) return 1;
    }

    Hash *H = (Hash *) malloc(sizeof(Hash));
    H->info = k;
    H->next = NULL; 

    H_aux->next = H;

    return 0;
}

int Search(H_List *HL, elem k){
    int i = hashing(k);

    Hash *H_aux = HL[i].first;
    while (H_aux != NULL){
        if (H_aux->info == k) return 1;
        H_aux = H_aux->next;
    }

    return 0;
}

int main(int argc, char *argv[]){
    H_List *HL;
    int n = 8;

    HL = CreateHash(n);

    int k;
    k = 4;
    Insert(&HL, k); 
    k = 14;
    Insert(&HL, k); 
    k = 6;
    Insert(&HL, k); 
    k = 98;
    Insert(&HL, k); 

    printf("%d",Search(HL,98));

    return 0;
}
