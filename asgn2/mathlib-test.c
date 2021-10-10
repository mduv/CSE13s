#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "haebmrvns"

int main(int argc, char **argv) {
    int opt = 0;
    int print_stats = 0;

    if (argc == 1) { // no args
        printf(
            "SYNOPSIS\n\tA test harness for the small numerical library.\n\nUSAGE\n "
            "\t./mathlib-test [-aebmrvnsh]\n\nOPTIONS\n \t-a   Runs all tests.\n \t-e   Runs e "
            "test.\n \t-b   Runs BBP pi test.\n \t-m   Runs Madhava pi test.\n \t-r   Runs Euler "
            "pi test.\n \t-v   Runs Viete pi test.\n \t-n   Runs Newton square root tests.\n \t-s  "
            " Print verbose statistics.\n \t-h   Display program synopsis and usage.\n");
    }
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 's': print_stats = 1; break;
        }
    }
    optind = 1;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 's': break;
        case 'e':
            printf(
                "e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, absolute(M_E - e()));
            if (print_stats == 1) {
                printf("e() terms = %d\n", e_terms());
            }
            break;
        case 'v':
            printf("pi_viete(): %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI,
                absolute(M_PI - pi_viete()));
            if (print_stats == 1) {
                printf("pi_viete() terms = %d\n", pi_viete_factors());
            }
            break;
        case 'm':
            printf("pi_madhava(): %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI,
                absolute(M_PI - pi_madhava()));
            if (print_stats == 1) {
                printf("pi_madhava() terms = %d\n", pi_madhava_terms());
            }
            break;
        case 'b':
            printf("pi_bbp(): %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI,
                absolute(M_PI - pi_bbp()));
            if (print_stats == 1) {
                printf("pi_bbp() terms = %d\n", pi_bbp_terms());
            }
            break;
        case 'r':
            printf("pi_euler(): %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI,
                absolute(M_PI - pi_euler()));
            if (print_stats == 1) {
                printf("pi_euler() terms = %d\n", pi_euler_terms());
            }
            break;
        case 'n': {
            for (double i = 0.00000; i <= 10.00000; i = i + 0.10000) {
                printf("sqrt_newton(%f) = %16.15lf, sqrt(%f) = %16.15lf, diff = %16.15lf\n", i,
                    sqrt_newton(i), i, sqrt(i), absolute(sqrt(i) - sqrt_newton(i)));
                if (print_stats == 1) {
                    printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
                }
            }

            break;
        }

        //printf("sqrt_newton(): %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI, absolute(M_PI - pi_euler()));
        break;
        case 'a':
            printf(
                "e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, absolute(M_E - e()));
            if (print_stats == 1) {
                printf("e() terms = %d\n", e_terms());
            }
            printf("pi_euler(): %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI,
                absolute(M_PI - pi_euler()));
            if (print_stats == 1) {
                printf("pi_euler() terms = %d\n", pi_euler_terms());
            }
            printf("pi_bbp(): %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI,
                absolute(M_PI - pi_bbp()));
            if (print_stats == 1) {
                printf("pi_bbp() terms = %d\n", pi_bbp_terms());
            }

            printf("pi_madhava(): %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI,
                absolute(M_PI - pi_madhava()));
            if (print_stats == 1) {
                printf("pi_madhava() terms = %d\n", pi_madhava_terms());
            }
            printf("pi_viete(): %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI,
                absolute(M_PI - pi_viete()));
            if (print_stats == 1) {
                printf("pi_viete() terms = %d\n", pi_viete_factors());
            }
            for (double i = 0.00000; i <= 10.00000; i = i + 0.10000) {
                printf("sqrt_newton(%f) = %16.15lf, sqrt(%f) = %16.15lf, diff = %16.15lf\n", i,
                    sqrt_newton(i), i, sqrt(i), absolute(sqrt(i) - sqrt_newton(i)));
                if (print_stats == 1) {
                    printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
                }
            }
            break;
        case 'h':
            printf("SYNOPSIS\n\tA test harness for the small numerical library.\n\nUSAGE\n "
                   "\t./mathlib-test [-aebmrvnsh]\n\nOPTIONS\n \t-a   Runs all tests.\n \t-e   "
                   "Runs e test.\n \t-b   Runs BBP pi test.\n \t-m   Runs Madhava pi test.\n \t-r  "
                   " Runs Euler pi test.\n \t-v   Runs Viete pi test.\n \t-n   Runs Newton square "
                   "root tests.\n \t-s   Print verbose statistics.\n \t-h   Display program "
                   "synopsis and usage.\n");
            break;
        default:
            printf("SYNOPSIS\n\tA test harness for the small numerical library.\n\nUSAGE\n "
                   "\t./mathlib-test [-aebmrvnsh]\n\nOPTIONS\n \t-a   Runs all tests.\n \t-e   "
                   "Runs e test.\n \t-b   Runs BBP pi test.\n \t-m   Runs Madhava pi test.\n \t-r  "
                   " Runs Euler pi test.\n \t-v   Runs Viete pi test.\n \t-n   Runs Newton square "
                   "root tests.\n \t-s   Print verbose statistics.\n \t-h   Display program "
                   "synopsis and usage.\n");
        }
    }

    return 0;
}
