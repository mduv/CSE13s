Assignment 5 - Huffman Coding

This program implements a Huffman encoder and decoder. This encoder will read in an input
file, find the Huffman encoding of its contents, and use the encoding to compress the file.
This decoder will read in a compressed input file and decompress it, expanding it back to
its original, uncompressed size. 

Building

Build the program with:
make

Running

Run the program with:
$ ./encode ./decode [-v] [-h] [-i infile] [-o outfile]

OPTIONS
    -h             Program usage and help.
    -v             Print compression statistics.
    -i infile      Input file to compress.
    -o outfile     Output of compressed data.
