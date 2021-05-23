/*CÓDIGO NÃO TERMINADO*/

#include <stdio.h>
#include <stdlib.h>
#include "matrizes_esparsas.h"

struct node_{
    int row, col;
    elem val;
    struct node_ *next_row;
    struct node_ *next_col;
};

struct mat_{
    Node **col;
    Node **row;
};

Mat* CreateMat(int n_row, int n_col){
    Mat *M = (Mat *) malloc(sizeof(M));      

    M->col = (Node **) malloc(n_col * sizeof(Node*));
    for (int i=0; i<n_col; i++)
        M->col[i] = NULL;

    M->row = (Node **) malloc(n_row * sizeof(Node*));
    for (int i=0; i<n_row; i++)
        M->row[i] = NULL;

    return M;
}

int Insert(Mat *M, int n_row, int n_col, elem e){
    
    Node *node = (Node *) malloc(sizeof(Node));
    node->row = n_row;
    node->col = n_col;
    node->val = e;

    Node *aux_node;

    aux_node = M->row[n_row]; 
    while (aux_node->next_col != NULL){
        if (aux_node->next_row->col > n_col){
            node->next_col = aux_node->next_col;
            aux_node->next_col = node;
            break;
        }
        aux_node = aux_node->next_col; 
    }

    aux_node = M->col[n_col]; 
    while (aux_node->next_row != NULL){
        if (aux_node->next_col->col > n_col){
            node->next_row = aux_node->next_row;
            aux_node->next_row = node;
            break;
        }
        aux_node = aux_node->next_row; 
    }


    return 0;
}

void PrintMat(Mat *M){

    return;
}
