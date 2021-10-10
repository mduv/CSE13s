#include "mathlib.h"
#include <stdlib.h>
#include <stdio.h>

static int num_terms = 0;

double e(void) {
    num_terms = 1;
    double prev_val = 0;
    double current_val = 1;
    double k_factorial = 0;
    double k = 0;


    while (absolute(current_val - prev_val) > EPSILON) {
        if (k == 0) {
            k_factorial = 1;
            k = k + 1;
        }
        else {
            prev_val = current_val;
            k_factorial = k_factorial * k;
            current_val += (1/k_factorial);
            k = k + 1;
        }
        printf("current val: %f, k factorial: %f, prev val: %f, diff: %f\n", 
            current_val, k_factorial, prev_val, absolute(prev_val - current_val));

        num_terms = num_terms + 1;
    }

    return current_val;
}

int e_terms(void) {
    return num_terms;
}

