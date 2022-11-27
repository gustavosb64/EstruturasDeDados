#ifndef LARGE_NUMBER_H
#define LARGE_NUMBER_H

#include "linked_list.h"

typedef struct largeNumber LargeNumber;

LargeNumber* read_large_number();

int print_large_number(LargeNumber* LN);

int is_greater(LargeNumber *LN_1, LargeNumber *LN_2);

int is_less(LargeNumber *LN_1, LargeNumber *LN_2);

int is_equal(LargeNumber *LN_1, LargeNumber *LN_2);

LargeNumber* sum(LargeNumber *LN_1, LargeNumber *LN_2, LargeNumber *LN_res);

LargeNumber* subtract(LargeNumber *LN_1, LargeNumber *LN_2, LargeNumber *LN_res);

void free_large_number(LargeNumber *LN);

void read_operation();


#endif