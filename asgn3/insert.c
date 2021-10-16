#include <stdio.h>
#include <stdlib.h>
#include "insert.h"

void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t temp;
    int j;
        
    for (unsigned int i = 1; i < n; i++) {
        j = i;
        move(stats, temp);
        temp = A[i];
        while( j > 0 && (cmp(stats, temp, A[j - 1]) == -1)) {  
            move(stats, A[j]);    
            A[j] = A[j - 1];
            j  -= 1;
        }
        move(stats, A[j]);      
        A[j] = temp;
    }
}

