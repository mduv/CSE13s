#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include "mathlib.h"



#define OPTIONS "haebmrvns"




int main(int argc, char **argv)
{
    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
            case 'e':
                printf("e() = %16.15lf, M_E = %f, diff = %16.15lf, num_terms: %d\n", e(), M_E, absolute(M_E - e()), e_terms());
                break;
            case 'v':
                printf("pi_viete(): %16.15lf, M_PI = %f, diff = %16.15lf, num_terms: %d\n", pi_viete(), M_PI, absolute(M_PI - pi_viete()), pi_viete_factors());
                break;
            case 'm':
                printf("pi_madhava(): %16.15lf, M_PI = %f, diff = %16.15lf, num_terms: %d\n", pi_madhava(), M_PI, absolute(M_PI - pi_madhava()), pi_madhava_terms());
                break;
            case 'a':
                printf("e() = %16.15lf, M_E = %f, diff = %16.15lf, num_terms: %d\n", e(), M_E, absolute(M_E - e()), e_terms());
                printf("pi_viete(): %16.15lf, M_PI = %f, diff = %16.15lf, num_terms: %d\n", pi_viete(), M_PI, absolute(M_PI - pi_viete()), pi_viete_factors());
                printf("pi_madhava(): %16.15lf, M_PI = %f, diff = %16.15lf, num_terms: %d\n", pi_madhava(), M_PI, absolute(M_PI - pi_madhava()), pi_madhava_terms());
                break;
        }
    }

    return 0;
}
