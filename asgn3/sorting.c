#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "insert.h"
#include "shell.h"
#include "quick.h"
#include "heap.h"

#include "set.h"


typedef enum { HEAP, SHELL, INSERT, QUICK, ALL } SortType;


#define OPTIONS "haeisqn:p:r:"

void intializeArray(uint32_t *numbersArray, int arraySize, uint32_t seed) {
    srandom(seed);
    for (int i = 0; i < arraySize; i++) {
        numbersArray[i] = (uint32_t)(random() & 0x3FFFFFFF);
    }
}

void printArray(uint32_t *numbersArray, int arraySize, int pElements) {
    if (arraySize > pElements) {
       arraySize = pElements;
    }
     for (int i = 1; i < arraySize+1; i++) {
        if ((i % 5) == 0 ) {
            printf("%13u\n", numbersArray[i-1]);
        } else {
           printf("%13u",numbersArray[i-1]);
        }
    }
    // if ((arraySize % 5) != 0) {
    //     printf("\n");
    // }
}


int main(int argc, char **argv) {
    int opt = 0;
    optind = 1;

    Stats stats;
    Set bitmap = 0;


    int arraySize = 100;
    int pElements = 100;
    uint32_t seed = 13371453;


    if (argc == 1) { // no args
        printf("Select at least one sort to perform\nSYNOPSIS\n\tA collection of comparison-based sorting algorithms.\n\nUSAGE\n "
                "\t./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n\nOPTIONS\n \t-h   display program help and usage."
                "\n \t-a   enable all sorts.\n \t-e   enable Heap Sort.\n \t-i   enable Insertion Sort.\n \t-s   enable Shell Sort."
                "\n \t-q   enable Quick Sort.\n \t-n length   specify number of array elements (default: 100)\n \t-p elements  "
                " specify number of elements to print (default: 100).\n \t-r seed  specify random seed (default: 13371453).\n");
        return 0;
    }
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
            case 'n': 
                arraySize = atoi(optarg);
                break;
            case 'p': 
                pElements = atoi(optarg);
                break;
            case 'r':
                seed = atoi(optarg);
            default:
                break;
        }
    }


    uint32_t *numbersArray = (uint32_t *) malloc(arraySize*sizeof(uint32_t));
    
    optind = 1;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            bitmap = insert_set(HEAP, bitmap);
            bitmap = insert_set(SHELL, bitmap);
            bitmap = insert_set(INSERT, bitmap);
            bitmap = insert_set(QUICK, bitmap);
            break;
        case 'n':
            break;
        case 'i':
            bitmap = insert_set(INSERT, bitmap);
            break;
        case 's':
            bitmap = insert_set(SHELL, bitmap);
            break;
        case 'q':
            bitmap = insert_set(QUICK, bitmap);
            break;
        case 'e':
            bitmap = insert_set(HEAP, bitmap);
            break;
        case 'h': 
            printf("Select at least one sort to perform\nSYNOPSIS\n\tA collection of comparison-based sorting algorithms.\n\nUSAGE\n"
                "\t./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n\nOPTIONS\n \t-h   display program help and usage."
                "\n \t-a   enable all sorts.\n \t-e   enable Heap Sort.\n \t-i   enable Insertion Sort.\n \t-s   enable Shell Sort."
                "\n \t-q   enable Quick Sort.\n \t-n length   specify number of array elements (default: 100)\n \t-p elements  "
                " specify number of elements to print (default: 100).\n \t-r seed  specify random seed (default: 13371453).\n");
            return 0;
        default:
            printf("Select at least one sort to perform\nSYNOPSIS\n\tA collection of comparison-based sorting algorithms.\n\nUSAGE\n "
                "\t./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n\nOPTIONS\n \t-h   display program help and usage."
                "\n \t-a   enable all sorts.\n \t-e   enable Heap Sort.\n \t-i   enable Insertion Sort.\n \t-s   enable Shell Sort."
                "\n \t-q   enable Quick Sort.\n \t-n length   specify number of array elements (default: 100)\n \t-p elements  "
                " specify number of elements to print (default: 100).\n \t-r seed  specify random seed (default: 13371453).\n");
        }
    }
    srandom(seed);
    for (int i = 0; i < arraySize; i++) {
        numbersArray[i] = (uint32_t)(random() & 0x3FFFFFFF);
    }

    if (member_set(HEAP, bitmap)) {
        reset(&stats);
        intializeArray(numbersArray, arraySize, seed);
        heap_sort(&stats, numbersArray, arraySize);
        printf("Heap Sort, %u elements, %llu moves, %llu compares\n", arraySize, stats.moves, stats.compares);
        printArray(numbersArray, arraySize, pElements);
    }

    if (member_set(SHELL, bitmap)) {
        reset(&stats);
        intializeArray(numbersArray, arraySize, seed);
        shell_sort(&stats, numbersArray, arraySize);
        printf("Shell Sort, %u elements, %llu moves, %llu compares\n", arraySize, stats.moves, stats.compares);
        printArray(numbersArray, arraySize, pElements);
    }

    if (member_set(INSERT, bitmap)) {
        reset(&stats);
        intializeArray(numbersArray, arraySize, seed);
        insertion_sort(&stats, numbersArray, arraySize);
        printf("Insertion Sort, %u elements, %llu moves, %llu compares\n", arraySize, stats.moves, stats.compares);
        printArray(numbersArray, arraySize, pElements);
    }


    if (member_set(QUICK, bitmap)) {
        reset(&stats);
        intializeArray(numbersArray, arraySize, seed);
        quick_sort(&stats, numbersArray, arraySize);
        printf("Quick Sort, %u elements, %llu moves, %llu compares\n", arraySize, stats.moves, stats.compares);
        printArray(numbersArray, arraySize, pElements);
    }

    free(numbersArray);

    return 0;
}



