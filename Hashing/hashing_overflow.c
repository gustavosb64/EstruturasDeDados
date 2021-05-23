/*CÓDIGO NÃO COMPLETO*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define B 11
#define h(k,i) (k+i)%B

typedef int List;

List* CreateHash(){
    List *H_List = (List *) malloc(B * sizeof(List));
    memset(H_List, -1, B*sizeof(int));
    
    return H_List;
}

/*
int hash_function(List *H_List, char c, int *cont){
    *cont = *cont + 1;
    if (*cont == B-1) return -1;

    char k = c%B;

    if(H_List[k] == -1 || H_List[k] == -2){
        H_List[k] = c;
        return k; 
    }
    
    return hash_function(H_List, (c+1), cont);
 
}
*/

int inserir(List* H, int c){
    int i,j;

    for(i=0; i<B; i++){
        j = h(c,i);
        if (H[j] == -1 || H[j] == -2){
            H[j] = c;
            return j;
        }        
    }

    return -1;
}

int buscar(List *H, int c){
    int i,j;

    for(i=0; i<B; i++){
        j = h(c,i);
        if (H[j] == c) return j;
    }

    return -1;
}

int main(int argc, char *argv[]){
    char *c = (char *) calloc(100, sizeof(char));

    List* H = CreateHash();

    int k;
    for (int i=0; i < 9; i++){
        k = 0;
        scanf(" %s",&c);
        for(int j=0; j<strlen(c); j++)
            k += c[j];

        printf("%d\n",inserir(H, k));
    }

    printf("---------------\n");
    for (int i=0; i < 5; i++){
        scanf(" %s",&c);
        printf("%d\n",buscar(H, k));
    }

    free(H);

    return 0;
}
