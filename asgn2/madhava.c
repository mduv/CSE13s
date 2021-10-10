#include "mathlib.h"
#include <stdlib.h>
#include <stdio.h>

static int num_terms = 0;

double pi_madhava(void) {
    double prev_val = 0;
    double current_val = 1;
    int k;
    double num = 1;
    double den = 0;
    double num_frac = 0; //fraction portion of series

   while (absolute(prev_val - current_val) > EPSILON) {
       // -3 pow -2 == 1/(-3pow-2)
       // prev_val = current_val;

       if(k == 0) {
           num = 1;
           k = k+1;
       } else {
           prev_val = current_val;
           num *= -3;
           num_frac = 1 / num;
           den = 2*k + 1;
           current_val += num_frac/den;
           k = k+1;
       }

       // solve for denominator
       // num_frac = 1 / num
       // current value is updated to num_frac/den
       // update the terms 
       num_terms = num_terms + 1;
    }

    return sqrt_newton(12) * current_val; 

}


int pi_madhava_terms(void) {
    return num_terms;
}


