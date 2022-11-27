#ifndef LINKED_LIST_H
#define LINKED_LIST_H


typedef int elem;

typedef struct node Node;

typedef struct list List;

List* create_list();

int is_empty_list(List *list);

size_t get_list_size(List *list);

int set_opposite_last_elem(List *list);

int compare_lists(List *L1, List *L2);

int add_last_elem_list(List *list, elem e);

int remove_last_elem_list(List *list, elem *e);

int print_list(List *list);

int print_list_no_space(List *list);

int free_list(List *list);

List* sum_lists(List *L1, List *L2);

List* subtract_lists(List *L1, List *L2);


#endif