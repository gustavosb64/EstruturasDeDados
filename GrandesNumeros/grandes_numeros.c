#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grandes_numeros.h"

#define LIM 10

struct number_{
    int val;
    struct number_ *next;
};

struct largeNumber_{
    Number *start;
};

LargeNumber* StoreNumber(char *s_num){

    LargeNumber *LN = (LargeNumber *) malloc(sizeof(LargeNumber));
    Number *n = (Number *) malloc(sizeof(Number));
    n->val = atoi(&s_num[strlen(s_num)-1]);
    s_num[strlen(s_num)-1] = 0;
    LN->start = n;

    for (int i = (strlen(s_num)-1); i >= 0; i--){
        Number *aux_n = (Number *) malloc(sizeof(Number));
        n->next = aux_n;

        aux_n->val = atoi(&s_num[i]); 
        s_num[i] = 0;

        n = aux_n;
    }
    
    n->next = LN->start;
    
    return LN;
}

LargeNumber* Sum(LargeNumber *LN1, LargeNumber *LN2, int *error){
    
    LargeNumber *LN_sum = (LargeNumber *) malloc(sizeof(LargeNumber));
    Number *n_sum = (Number *) malloc(sizeof(Number));

    int i1 = LN1->start->val;
    int i2 = LN2->start->val;
    int i_sum = i1 + i2;

    n_sum->val = (i_sum%LIM);
    i_sum /= LIM;

    LN_sum->start = n_sum;
    n_sum->next = LN_sum->start;

    Number *n1 = LN1->start->next;
    Number *n2 = LN2->start->next;

    if (n1 != LN1->start) i1 = n1->val;
    else i1 = 0;
    if (n2 != LN2->start) i2 = n2->val;
    else i2 = 0;

    while(i_sum != 0 || n1 != LN1->start || n2 != LN2->start){
        Number *new_n_sum = (Number *) malloc(sizeof(Number));

        i_sum += i1 + i2;
        new_n_sum->val = (i_sum%LIM);
        
        i_sum /= LIM;

        n_sum->next = new_n_sum;
        n_sum = new_n_sum;

        if (n1 == LN1->start) i1 = 0;
        else{
            n1 = n1->next;
            i1 = n1->val;
        }

        if (n2 == LN2->start) i2 = 0;
        else{
            n2 = n2->next;
            i2 = n2->val;
        }

    }

    n_sum->next = LN_sum->start;

    return LN_sum;

}

int PrintNumber(LargeNumber *LN){
    Number *aux_n = LN->start;
   
    do{ 
        printf("%d\n",aux_n->val);
        aux_n = aux_n->next;
    } while(aux_n != LN->start);

    return 0;
}
/* FUNÇÕES NÃO TESTADAS
LargeNumber* StoreNumber(int i){
    LargeNumber *LN = (LargeNumber *) malloc(sizeof(LargeNumber));
    Number *n = (Number *) malloc(sizeof(Number));

    n->val = -1;

    LN->start = n;

    Number *aux_n; 
    n->next = aux_n;

    aux_n = (Number*) malloc(sizeof(Number));
    do{
        if(i%LIM){
            aux_n->val = i%LIM;
            Number *aux_n2 = (Number *) malloc(sizeof(Number)); 
            aux_n2->val = 0;
            aux_n->next = aux_n2;
            aux_n = aux_n2;
            aux_n->next = NULL;
            i -= (i%LIM);
        }
        else{
            aux_n->val = LIM/i;    
            aux_n->next = LN->start;
        }
    }while(aux_n->next == NULL);
*/
/*
    do{
        aux_n = (Number *) malloc(sizeof(Number));
   		if (i%LIM){
   		   aux_n->val = i%LIM;
   		   printf("Ola\n");
   		   i -= (i%LIM);
           aux_n->next = NULL;
   		   aux_n = aux_n->next;
        }
   		else{
   		   aux_n->val = i/LIM;
   		   aux_n->next = LN->start;
        }
    }while(aux_n->next != LN->start);
*/
/*
    return LN;
}
*/
