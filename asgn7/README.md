Assignment 7 - The Great Firewall of Santa Cruz:
Bloom Filters, Linked Lists, Binary Trees and Hash Tables

This is a word filtering program for the GPRSC. It filters out and reports bad words parsed from stdin.

Building

Build the program with:
make

Running

Run the program with:
$ ./banhammer [-hs] [-t size] [-f size]

OPTIONS
  -h           Program usage and help.
  -s           Print program statistics.
  -t size      Specify hash table size (default: 2^16).
  -f size      Specify Bloom filter size (default: 2^20).
