#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "shell.h"

unsigned int *generate_gaps(int n) {
    unsigned int *gapsList = (unsigned int *) malloc(n*sizeof(unsigned int));

    unsigned int start = (unsigned int)(log(3 + 2 * n) / log(3));
    for (int i = start, j = 0; i >= 0 && j < n; j++, i -= 1) {
        gapsList[j] = (pow(3,i) - 1) / 2;
    }
    return gapsList;
}

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {

    unsigned int *gaps = generate_gaps(n);
   
    unsigned int temp = 0;
    for (unsigned int k = 0; k < n; k++) {
        for (unsigned int i = gaps[k]; i < n && i != 0; i++) {
            unsigned int gap = gaps[k];
            unsigned int j = i;
            move(stats, temp);
            temp = A[i];
            while(j >= gap  &&  cmp(stats, temp , A[j - gap]) == -1) {
                move(stats, A[j]);
                A[j] = A[j - gap];
                j -= gap;
            }
            move(stats, A[j]);
            A[j] = temp;
        }
    }
}

