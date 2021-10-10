#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int num_terms = 0;

double pi_bbp(void) { // I get 63440 terms before converging
    // k_terms = 0;
    double bbp_coef = 1;
    double bbp_frac = 0;
    double prev_val = 1;
    double current_val = 0;
    double k = 0;
    // int i = 5;
    num_terms = 0;

    while (absolute(prev_val - current_val) > EPSILON) {

        prev_val = current_val;
        if (k == 0) {
            bbp_coef = 1;
        } else {
            bbp_coef = bbp_coef / 16.0;
        }
        bbp_frac = (k * (120 * k + 151) + 47) / (k * (k * (k * (512 * k + 1024) + 712) + 194) + 15);
        current_val += (bbp_coef * bbp_frac);
        k = k + 1;

        // i--;

        num_terms++;
        // ...same as in madhava.c that we went over
    }
    return current_val;
}

int pi_bbp_terms(void) {
    return num_terms;
}
