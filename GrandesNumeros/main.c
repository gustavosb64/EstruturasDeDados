#include <stdio.h>
#include "large_number.h"

int main(){

    /**********************************************************
     *********INPUT FORMAT*************************************
     **********************************************************
     *** (int) number_of_operations              **************
     *** (char*) operation_name number1 number2  **************
     ***                                                     **
     *** operation_name must be: [maior, menor, igual, soma] **
     ***  * maior: is number1  larger  than number2 ?  ********
     ***  * menor: is number1  less    than number2 ?  ********
     ***  * igual: is number1  equal     to number2 ?  ********
     ***  * soma:  number1 + number2                   ********
     **********************************************************/
    
    /* reads number of operations */
    int n_operations;
    scanf("%d ", &n_operations);

    /* reads and executes the requested operations */
    for (int i=0; i < n_operations; i++){
        read_operation();
    }

    return 0;
}
