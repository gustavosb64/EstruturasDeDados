#ifndef GRANDES_NUMEROS_H
#define GRANDES_NUMEROS_H

typedef struct number_ Number;
typedef struct largeNumber_ LargeNumber;

LargeNumber* StoreNumber(char *s_num);
LargeNumber* Sum(LargeNumber *LN1, LargeNumber *LN2, int *error);
int PrintNumber(LargeNumber *LN);

#endif
