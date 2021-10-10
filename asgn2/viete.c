#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

int num_terms = 0;

double pi_viete(void) {
    double num = 0;

    double prev_value = 0;
    double current_value = 1;
    // int i = 7;
    num_terms = 0;
    while (absolute(current_value - prev_value) > EPSILON) {
        prev_value = current_value;
        num = sqrt_newton(2 + num);
        current_value = prev_value * (num / 2);

        // i--;
        // current_pi = prev_pi * (num / 2);
        //prev_pi = current_pi;
        num_terms = num_terms + 1;
        // printf("current value: %f, previous value: %f, num: %f\n", current_pi, prev_pi, num); */
    }

    current_value = (1 / current_value) * 2;

    // printf("hello\n");
    return current_value;
}

int pi_viete_factors(void) {
    return num_terms - 1;
}
