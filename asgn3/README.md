Assignment 3 - Sorting: Putting your affairs in order

This program implements the sorting algorithms Insertion Sort, Shell Sort, Heap Sort, and recursive Quicksort. The test harness will test each of these sorts on an array of psuedorandom elements. Analysis and finding are presented in a writeup pdf.

Building

Build the program with:
make

Running

Run the program with:
$ ./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]

OPTIONS
    -h   display program help and usage.
    -a   enable all sorts.
    -e   enable Heap Sort.
    -i   enable Insertion Sort.
    -s   enable Shell Sort.
    -q   enable Quick Sort.
    -n length   specify number of array elements (default: 100)
    -p elements   specify number of elements to print (default: 100).
    -r seed  specify random seed (default: 13371453).