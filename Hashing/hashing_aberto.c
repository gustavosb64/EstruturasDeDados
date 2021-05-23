#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define B 11
#define hashing(k) (k%B)

typedef int Hash;

typedef struct list_{
    int x;
    struct list_ *next;
}List;

List* CreateHash(){
    List *H = (List *) malloc(B * sizeof(List));
    for (int i=0; i<B; i++){
        H[i].x = -1;
        H[i].next = NULL;
    }
    
    return H;
}

int inserir(List* H, int c){

    int j = hashing(c);
    printf("#%d\n",j);
    printf("H[j]: %p\t%d\t%p\n",&H[j], H[j].x, H[j].next);

    List *aux = &H[j];
    printf("aux : %p\t%d\t%p\n",aux, aux->x, aux->next);
    while (aux->next != NULL){
        if (aux->x == c) return -1;
        aux = aux->next; 
    }
    if (aux->x == c) return -1;      

    List new;
    new.x = c;
    new.next = NULL;

    aux->next = &new;
    printf("aux : %p\t%d\t%p\n",aux, aux->x, aux->next);
    printf("H[j]: %p\t%d\t%p\n",&H[j], H[j].x, H[j].next);


    return 0;
}

int buscar(List *H, int c){
    int i,j;

    for(i=0; i<B; i++){
        j = hashing(c);
        if (H[j].x == c) return j;
    }

    return -1;
}

int main(int argc, char *argv[]){
    char *c = (char *) calloc(100, sizeof(char));

    List *H = CreateHash();

    printf("@H[j]: %p\t%d\t%p\n",&H[4], H[4].x, H[4].next);
    inserir(H, 4);
    printf("@H[j]: %p\t%d\t%p\n",&H[4], H[4].x, H[4].next);

    if (buscar(H, 4) != -1) printf("Achei!\n");
    printf("@%d\n",H[4]);

    free(H);

    return 0;
}
