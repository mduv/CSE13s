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
                printf("e(): %16.15lf, num_terms: %d\n", e(), e_terms());
                break;
        }
    }

    return 0;
}
