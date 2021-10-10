#include "mathlib.h"
#include <stdlib.h>
#include <stdio.h>

static int num_terms = 0;

double pi_euler(void) { // I get 63440 terms before converging
    double k = 1;
    double prev_val = 1;
    double current_val = 0;
    num_terms = 0;
    
    while (absolute(prev_val - current_val) > EPSILON) {
        prev_val = current_val;
        current_val += (1/(k*k));
        k++;
        // if (k > 65000) {
        //     break;
        // }
        /* printf("current value: %.20f, prevval: %.20f, k: %f\n", current_val, prev_val, num_terms); */
        num_terms = num_terms + 1;

    }

    return sqrt_newton(6*current_val);
}

int pi_euler_terms(void) {
    return num_terms;
}


