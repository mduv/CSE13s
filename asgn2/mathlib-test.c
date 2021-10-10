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
                printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, absolute(M_E - e()));
                break;
            case 'v':
                printf("pi_viete(): %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI, absolute(M_PI - pi_viete()));
                break;
            case 'm':
                printf("pi_madhava(): %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI, absolute(M_PI - pi_madhava()));
                break;
            case 'b':
                printf("pi_bbp(): %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI, absolute(M_PI - pi_bbp()));
                break;
            case 'r':
                printf("pi_euler(): %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI, absolute(M_PI - pi_euler()));
                break;
            case 'n':
            {
                for (double i = 0.00000; i <= 10.00000; i = i + 0.10000){
                    printf("sqrt_newton(%f) = %16.15lf, sqrt(%f) = %16.15lf, diff = %16.15lf\n", i, sqrt_newton(i), i, sqrt(i), absolute(sqrt(i)-sqrt_newton(i)));
                }
                break;
            }
                
                //printf("sqrt_newton(): %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI, absolute(M_PI - pi_euler()));
                break;
            case 'a':
                printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, absolute(M_E - e()));
                printf("pi_euler(): %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI, absolute(M_PI - pi_euler()));
                printf("pi_bbp(): %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI, absolute(M_PI - pi_bbp()));
                printf("pi_madhava(): %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI, absolute(M_PI - pi_madhava()));
                printf("pi_viete(): %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI, absolute(M_PI - pi_viete()));
                
                break;
        }
    }

    return 0;
}
