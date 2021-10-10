Assignment 2 - A little slice of pi

This program implements a small number of mathematical functions (ex and pix), mimicking <math.h>, and uses them to compute the fundamental constants e and π. It also includes a test harness which compares the implemented functions with that of the math library's. Analysis and finding are presented in a writeup pdf.

Building

Build the program with:
make

Running

Run the program with:
$ ./mathlib-test [-aebmrvnsh]

OPTIONS
 	-a   Runs all tests.
 	-e   Runs e test.
 	-b   Runs BBP pi test.
 	-m   Runs Madhava pi test.
 	-r   Runs Euler pi test.
 	-v   Runs Viete pi test.
 	-n   Runs Newton square root tests.
 	-s   Print verbose statistics.
 	-h   Display program synopsis and usage.