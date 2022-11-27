#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "large_number.h"
#include "utils.h"

struct largeNumber{
    List *number;
    char flag_negative;
};

/* Creates a default LargeNumber* */
static LargeNumber* create_large_number(){
    
    LargeNumber *LN = (LargeNumber *) malloc(sizeof(LargeNumber));
    LN->number = NULL;
    LN->flag_negative = 0;

    return LN;
}

/* Reads a large number from stdin and stores it in a LargeNumber* */
LargeNumber* read_large_number(){

    LargeNumber *LN = create_large_number();
    LN->number = create_list();

    char *s_num = read_word();
    int n;

    /* reads number backwards and stores a 
     * maximum of 4 digits in each node */
    int s_size = strlen(s_num);
    for (int i = s_size-4; i>=0; i-=4){
        n = atoi(&s_num[i]);
        add_last_elem_list(LN->number, n);

        s_num[i] = '\0';
    }
    if(strlen(s_num) > 0){
    
        /* in case the last character is just the negative sign,
         * flag_negative is set to 1 */
        if (!strcmp(s_num, "-")){
            LN->flag_negative = 1;
        }
        else{
            n = atoi(s_num);         
            add_last_elem_list(LN->number, n);
        }
    }
    /* in case the last number is negative, flag_negative is set 
     * to 1 and the number is stored as its absolut value */
    if (n < 0){
        LN->flag_negative = 1;
        set_opposite_last_elem(LN->number);
    }

    free(s_num);

    return LN;
}

/* Prints all nodes from a LargeNumber->number */
int print_large_number(LargeNumber* LN){

    // if LN is negative, print the sign
    if(LN->flag_negative == 1) printf("-");

    return print_list_no_space(LN->number);
}

/* Checks whether LN_1 > LN_2 */
int is_greater(LargeNumber *LN_1, LargeNumber *LN_2){

    /* if they have different signs, the comparison is direct */
    if (LN_1->flag_negative != LN_2->flag_negative){
        if (LN_1->flag_negative == 1) return 0;
        else return 1;
    }

    int res = compare_lists(LN_1->number, LN_2->number);

    // if both are negative, the result is inverted
    if (LN_1->flag_negative == 1) res *= -1;

    if (res > 0) return 1;
    else return 0;
    
}

/* Checks whether LN_1 < LN_2 */
int is_less(LargeNumber *LN_1, LargeNumber *LN_2){

    /* if they have different signs, the comparison is direct */
    if (LN_1->flag_negative != LN_2->flag_negative){
        if (LN_1->flag_negative == 1) return 1;
        else return 0;
    }

    int res = compare_lists(LN_1->number, LN_2->number);

    // if both are negative, the result is inverted
    if (LN_1->flag_negative == 1) res *= -1;

    if (res < 0) return 1;
    else return 0;

}

/* Checks whether LN_1 == LN_2 */
int is_equal(LargeNumber *LN_1, LargeNumber *LN_2){
    int res = compare_lists(LN_1->number, LN_2->number);
    if (res == 0) return 1;
    else return 0;
}

/* Executes LN_res = LN_1 + LN_2 */
LargeNumber* sum(LargeNumber *LN_1, LargeNumber *LN_2, LargeNumber *LN_res){

    LN_res->number = sum_lists(LN_1->number, LN_2->number);
    
    return LN_res;
}

/* Executes LN_res = LN_1 - LN_2 */
LargeNumber* subtract(LargeNumber *LN_1, LargeNumber *LN_2, LargeNumber *LN_res){

    /* the largest number is the one to be subtracted from */
    int comp = compare_lists(LN_1->number, LN_2->number);

    if (comp >= 0){

        // the resulting number has the same sign as the largest list
        LN_res->flag_negative = LN_1->flag_negative;
        LN_res->number = subtract_lists(LN_1->number, LN_2->number);
    }
    else{

        // the resulting number has the same sign as the largest list
        LN_res->flag_negative = LN_2->flag_negative;
        LN_res->number = subtract_lists(LN_2->number, LN_1->number);
    }

    return LN_res;
}

/* Executes requested operation */
static void exe_operation(char *operation, LargeNumber *LN_1, LargeNumber *LN_2){

    printf("Resultado :: ");

    // LN_1 > LN_2 
    if (!strcmp(operation, "maior"))
        printf("%s\n", boolean_print(is_greater(LN_1, LN_2)));

    // LN_1 < LN_2 
    else if (!strcmp(operation, "menor"))
        printf("%s\n", boolean_print(is_less(LN_1, LN_2)));

    // LN_1 == LN_2 
    else if (!strcmp(operation, "igual"))
        printf("%s\n", boolean_print(is_equal(LN_1, LN_2)));

    // LN_1 + LN_2 
    else if (!strcmp(operation, "soma")){

        LargeNumber *LN_res = create_large_number();

        /* if both numbers have the same sign */
        if (LN_1->flag_negative == LN_2->flag_negative){

            LN_res->flag_negative = LN_1->flag_negative;
            LN_res = sum(LN_1, LN_2, LN_res);

            print_large_number(LN_res);
        }

        /* otherwise, a subtraction is performed */
        else{
            LN_res = subtract(LN_1, LN_2, LN_res);
            print_large_number(LN_res);
        }

        free_large_number(LN_res);
    }

    return;
}

/* Free memory from given LargeNumber* */
void free_large_number(LargeNumber *LN){
    free_list(LN->number);
    free(LN);
    return;
}

/* Read operations from input */
void read_operation(){

    /* reads input from stdin */
    char *operation = read_word();
    LargeNumber *LN_1 = read_large_number();
    LargeNumber *LN_2 = read_large_number();

    /* executes requested operation */
    exe_operation(operation, LN_1, LN_2);

    /* free memory */
    free(operation);
    free_large_number(LN_1);
    free_large_number(LN_2);

    return;
}
