#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linked_list.h"

#define NUM_OF_DIGITS 4
#define MAX_NUM pow(10, NUM_OF_DIGITS) 

struct node{
    elem val;
    struct node *next;
};

struct list{
    struct node *first; 
    struct node *last; 
    size_t n_elem;
};

List* create_list(){
    List *list = (List *) malloc(sizeof(List));
    if (list == NULL){
        printf("create_list FAILED: Memory is full.\n");
        return NULL;
    }

    list->first = NULL;
    list->last = list->first;

    list->n_elem = 0;

    return list;
}

int is_empty_list(List *list){
    if (list->n_elem == 0) return 1;
    else return 0;
}

size_t get_list_size(List *list){
    return list->n_elem; 
}

int set_opposite_last_elem(List *list){

    if (list == NULL || is_empty_list(list)) return 1;

    list->last->val *= -1;

    return 0;
}

static int compare_nodes(Node *N1, Node *N2){
    
    /* since the numbers are stored backwards,
     * the comparison starts from the last node */
    int comp = 0;
    if (N1->next != NULL){
        comp = compare_nodes(N1->next, N2->next);
    }

    /* if the previous nodes are equal, 
     * the current nodes are compared. */
    if (comp == 0){
        if (N1->val == N2->val) return 0;
        if (N1->val > N2->val) return 1;
        if (N1->val < N2->val) return -1;
    }

    return comp;
}

/* Return:
 *  return  1: L1 is larger
 *  return -1: L2 is larger
 *  return  0: both are equal
*/
int compare_lists(List *L1, List *L2){

    if (L1->n_elem > L2->n_elem) return 1;
    if (L1->n_elem < L2->n_elem) return -1;

    /* if they cannot be compared by size, 
     * they are compared node to node */
    return compare_nodes(L1->first, L2->first);
}

int add_last_elem_list(List *list, elem e){
    Node *aux_node = (Node *) malloc(sizeof(Node));
    if (aux_node == NULL) return 1;

    if (is_empty_list(list)){
        list->first = aux_node;
    }
    else {
        list->last->next = aux_node;
    }

    list->last = aux_node;

    list->last->val = e;
    list->last->next = NULL;

    list->n_elem++;

    return 0;
}

static int recursive_removal_from_last_elem(Node *node, List *list, elem *e){

    /* flag used to sign to the node right before
     * the last element */
    int flag_new_last = 0;

    if (node->next != NULL)
        flag_new_last = recursive_removal_from_last_elem(node->next, list, e);
    else{
        *e = list->last->val;
        free(list->last);

        list->n_elem--;

        return 1;
    }

    /* if this flag_new_last == 1, current node is 
     * the new last element from the list */
    if (flag_new_last == 1){
        node->next = NULL;
        list->last = node;
    }

    return 0;
}

int remove_last_elem_list(List *list, elem *e){

    if(is_empty_list(list)) return 1;

    int flag_new_last = recursive_removal_from_last_elem(list->first, list, e);

    /* if flag_new_last == 1, 
     * the list is now empty */
    if (flag_new_last == 1){
        list->first = NULL;
        list->last = NULL;
    }

    return 0;
}

int print_list(List *list){

    if(is_empty_list(list)) return 1;

    Node *aux_node = list->first;

    while(aux_node!=NULL){
        printf("%d\n",aux_node->val);
        aux_node = aux_node->next;
    }

    return 0;
}

static void print_nodes_backwards(Node *node){

    if (node->next != NULL)
        print_nodes_backwards(node->next);
    else{
        printf("%d",node->val);
        return;
    }

    /* adds '0' between the numbers when needed. */
    int i = MAX_NUM/10;
    while(node->val < i && i > 1){
        printf("0");
        i = i/10;
    }
    printf("%d",node->val);

    return;
}

int print_list_no_space(List *list){

    if(list == NULL || is_empty_list(list)) return 1;

    print_nodes_backwards(list->first);
    printf("\n");

    return 0;
}

int free_list(List *list){

    if(is_empty_list(list)){
        free(list->first);
        free(list);
        return 1;
    }

    Node *aux_node = list->first;
    Node *aux_node2;
    while(aux_node!=NULL){
        aux_node2 = aux_node;
        aux_node = aux_node->next;
        free(aux_node2);
    }
    free(aux_node);
    free(list);

    return 0;
}

List* sum_lists(List *L1, List *L2){

    List *L_res = create_list();

    Node *aux_node_1 = L1->first;
    Node *aux_node_2 = L2->first;

    int cur_sum = 0, carry = 0;
    while (aux_node_1 != NULL && aux_node_2 != NULL){

        cur_sum = (aux_node_1->val + carry) + aux_node_2->val;

        /* if the sum has more than 4 digits, the carry 
         * value must be incremented to the next node */
        if (cur_sum >= MAX_NUM){
            carry = 1;
            cur_sum -= MAX_NUM;
        } 
        else{
            carry = 0;
        }
        
        add_last_elem_list(L_res, cur_sum);
        
        aux_node_1 = aux_node_1->next;
        aux_node_2 = aux_node_2->next;
    }

    /* if there are still nodes in one of the lists, they are copied
     * into the resulting list */
    Node *remaining_nodes = NULL;
    if (aux_node_1 != NULL) remaining_nodes = aux_node_1;
    else if (aux_node_2 != NULL) remaining_nodes = aux_node_2;
    while (remaining_nodes != NULL){
        remaining_nodes->val += carry;
        carry = 0;
        add_last_elem_list(L_res, remaining_nodes->val);
        remaining_nodes = remaining_nodes->next;
    }

    /* if carry is not 0, it must be incremented 
     * to the resulting number */
    if(carry > 0){
        add_last_elem_list(L_res, carry);
    }

    return L_res;
}

List* subtract_lists(List *L1, List *L2){

    List *L_res = create_list();

    Node *aux_node_1 = L1->first;
    Node *aux_node_2 = L2->first;

    int cur_val = 0, carry = 0;
    while (aux_node_1 != NULL && aux_node_2 != NULL){
        
        cur_val = (aux_node_1->val - carry) - aux_node_2->val;

        if (cur_val < 0){
            carry = 1;
            cur_val += MAX_NUM;
        }
        else{
            carry = 0;
        }

        add_last_elem_list(L_res, cur_val);
        
        aux_node_1 = aux_node_1->next;
        aux_node_2 = aux_node_2->next;
    }

    /* if there are still nodes in one of the lists, they are copied
     * into the resulting list */
    Node *remaining_nodes = NULL;
    if (aux_node_1 != NULL) remaining_nodes = aux_node_1;
    else if (aux_node_2 != NULL) remaining_nodes = aux_node_2;
    while (remaining_nodes != NULL){
        remaining_nodes->val -= carry;
        carry = 0;
        add_last_elem_list(L_res, remaining_nodes->val);
        remaining_nodes = remaining_nodes->next;
    }

    /* if the last element is now 0, it 
     * must be removed from the list */
    if(L_res->last->val == 0){
        elem e;
        remove_last_elem_list(L_res, &e);
    }

    return L_res;
}
