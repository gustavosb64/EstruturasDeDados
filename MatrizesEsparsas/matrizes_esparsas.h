#ifndef MATRIZES_ESPARSAS_H
#define MATRIZES_ESPARSAS_H

typedef int elem;
typedef struct node_ Node;
typedef struct mat_ Mat;

Mat* CreateMat(int n_row, int n_col);
void PrintMat(Mat *M);


#endif
