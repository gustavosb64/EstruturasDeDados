#include <stdio.h>
#include <stdlib.h>
#include "lista_generalizada.h"

typedef union info_{
    elem atom;
    struct node_ *sublist;
}Info;

struct node_{
    Info info;
    char type;
    struct node_ *prev;
    struct node_ *next;
};

struct list_{
    Node *first;
    Node *last;
};

List* CreateList(){
    List *list = (List *) malloc(sizeof(List));

    list->first = NULL;
    list->last = NULL;

    return list;
}

Node* GetNodeList(List *list){
    return list->first;
}

int IsEmptyList(List *list){
    if (list->first == NULL) return 1;
    else return 0;
}

int AddLastElemList(List *list, Info info, char type){
    
    Node *node = (Node *) malloc(sizeof(Node));
    if (node == NULL) return 1;

    if(IsEmptyList(list)){
        list->first = node;
        node->prev = NULL;
    }
    else{
        list->last->next = node;
        node->prev = list->last;
    }

    node->info = info;
    node->type = type; 
    node->next = NULL;

    list->last = node;

    return 0;
}

int RemoveLastElemList(List *list, Info *info){

    if(IsEmptyList(list)) return 1;

    Node *aux_node = list->last;
    *info = list->last->info; 

    if(aux_node == list->first){
        list->last = NULL;
        list->first = NULL;
    }
    else{
        list->last = aux_node->prev;
        list->last->next = NULL;
    }

    free(aux_node);

    return 0;
}

int SearchElem(List *list, elem x, int *error){

    if(IsEmptyList(list)){
        *error = 1;
        return 0;
    }

    return SearchElemSubRoutine(list->first, x);
}

int SearchElemSubRoutine(Node *node, elem x){

    while (node != NULL){
        if(node->type == 2){
            if(SearchElemSubRoutine(node->info.sublist, x)) return 1;
        }
        else if(node->info.atom == x) return 1;

        node = node->next;
    }

    return 0;
}

int AreEqual(List *L1, List *L2, int *error){

    if(IsEmptyList(L1) || IsEmptyList(L2)){
        *error = 1;
        return 0;
    }

    return AreEqualNodes(L1->first, L2->first, error);
}

int AreEqualNodes(Node *node1, Node *node2, int *error){

    while(node1 != NULL && node2 != NULL){

        if(node1->type != node2->type) return 0;

        if(node1->type == 2) AreEqualNodes(node1->info.sublist, node2->info.sublist, error);
        else if(node1->info.atom != node2->info.atom) return 0;

        node1 = node1->next;
        node2 = node2->next;
    }

    if (node1 == node2) return 1;

    return 0;
}


int PrintList(List *list){

    if(IsEmptyList(list)) return 1;
    
    PrintNodes(list->first, 0);

    return 0;
}

int PrintNodes(Node *node, int cont){

    if(node == NULL) return 1;

    while(node!=NULL){

        if (node->type == 2){
            for (int i=0; i < cont; i++)
                printf("   ");
            printf("SUBLIST{\n");

            PrintNodes(node->info.sublist, cont+1);

            for (int i=0; i < cont; i++)
                printf("   ");
            printf("}\n");
        }
        else{
            for (int i=0; i < cont; i++)
                printf("   ");
            if(cont > 0) printf("|->");

            printf("%d\n",node->info.atom);
        }

        node = node->next;
    }

    return 0;
}

/* FUNÇÕES NÃO TESTADAS
int SearchElemSubRoutine(Node *node, elem x){

    [...]

    Info info;
    info.atom = x;
    if(AddLastElemList(list, info, 1)){
        *error = 2;
        return 0;
    }

    if(SearchElemSubRoutine(list->first, x) == list->last){
        RemoveLastElemList(list, &info);
        *error = 0;
        return 0;
    }
     
    RemoveLastElemList(list, &info);
    *error = 0;
    return 1;


int SearchElemSubRoutine(Node *node, elem x){

    [...]

    while (node->info.atom != x){
        if(node->type == 2){
            Node *aux_node = SearchElemSubRoutine(node->info.sublist, x);
             
        }
        node = node->next;
    }

    return node;
}

*/
