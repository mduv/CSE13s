#include "randstate.h"
#include "numtheory.h"
// #include "node.h"
// #include "huffman.h"
// #include <string.h>
// #include "stack.h"
// #include "pq.h"
// #include "header.h"
// #include "io.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

// #define OPTIONS "vhi:o:"

// static FILE *input = NULL;
// static FILE *input2 = NULL;
// uint64_t hist[ALPHABET] = { 0 };
// Code table[ALPHABET] = { 0 };
// uint16_t permissions;
// uint16_t unique_symbols;
// uint64_t file_size;
// int output_fd = 1;
// bool verbose_mode = false;
// uint64_t compressed_file_size;

// void build_histogram() {
//     uint8_t buf = 0;
//     hist[0] = 1;
//     hist[255] = 1;
//     unique_symbols = 2;
//     while (true) {
//         buf = fgetc(input);
//         if (feof(input)) {
//             break;
//         }
//         if (hist[buf] == 0) {
//             unique_symbols++;
//         }
//         hist[buf]++;
//     }
// }

// Header header_create() {
//     Header h;
//     h.magic = MAGIC;
//     h.permissions = permissions;
//     h.tree_size = (3 * unique_symbols) - 1;
//     h.file_size = file_size;
//     return h;
// }

// int main(int argc, char **argv) {
//     int opt = 0;
//     optind = 1;

//     input = stdin;
//     input2 = stdin;

//     while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
//         switch (opt) {
//         case 'h':
//             printf("SYNOPSIS\n\tA Huffman encoder.\n\tCompresses a file using the Huffman coding "
//                    "algorithm.\n\nUSAGE\n\t./encode [-h] [-i infile] [-o outfile]\n\nOPTIONS\n\t-h "
//                    "            Program usage and help.\n\t-v             Print compression "
//                    "statistics.\n\t-i infile      Input file to compress.\n\t-o outfile     Output "
//                    "of compressed data.\n");
//             return 0;
//             break;
//         case 'i':
//             // inputfile_name = optarg;
//             input = fopen(optarg, "r");
//             input2 = fopen(optarg, "r");
//             if (input == NULL) {
//                 perror("Error: unable to read header.");
//                 return (-1);
//             }
//             struct stat stat_buf;
//             if (stat(optarg, &stat_buf) == -1) {
//                 perror("Error: unable to read header.");
//                 return (-1);
//             }
//             permissions = stat_buf.st_mode;
//             file_size = stat_buf.st_size;
//             break;
//         case 'o':
//             output_fd = open(optarg, O_WRONLY | O_APPEND | O_CREAT);
//             if (output_fd < 0) {
//                 perror("Error: unable to open file.");
//                 return (-1);
//             }
//             break;
//         case 'v':
//             verbose_mode = true;
//             // Uncompressed file size: 7 bytes
//             printf("Uncompressed file size: %lu bytes\n", file_size);
//             // Compressed file size: 32 bytes
//             // Space saving: -357.14%
//             break;
//             return 0;
//         }
//     }

//     build_histogram();
//     Header h = header_create();
//     //printf("h.magic:%X, h.permissions:%X, h.tree_size:%X, h.file_size:%llX\n", h.magic, h.permissions, h.tree_size, h.file_size);
//     fchmod(output_fd, h.permissions);
//     write(output_fd, &h, sizeof(Header));

//     Node *root = build_tree(hist);
//     dump_tree(output_fd, root);

//     build_codes(root, table);
//     while (true) {
//         int buf = fgetc(input2);
//         if (feof(input2)) {
//             break;
//         }
//         Code c = table[buf];
//         write_code(output_fd, &c);
//     }
//     flush_codes(output_fd);
//     delete_tree(&root);

//     fclose(input);
//     fclose(input2);
//     if (verbose_mode) {
//         struct stat stat_buf;
//         if (fstat(output_fd, &stat_buf) == -1) {
//             perror("Error: unable to read header.");
//             return (-1);
//         }
//         compressed_file_size = stat_buf.st_size;
//         printf("Compressed file size: %lu bytes\n", compressed_file_size);

//         float space_savings = 100 * (1 - ((float) compressed_file_size / file_size));
//         printf("Space saving: %f%%\n", space_savings);
//     }
//     close(output_fd);
// }

int main() {
    randstate_init(1024);
    // rintf("hello\n");
    mpz_t p, a;
    // mpz_t x, y, z, out;
    mpz_init (p);
    // mpz_init (a);
    // mpz_init (z);
    // mpz_init(out);
    mpz_init_set_si(a, 103);


    // mpz_init_set_si(x, 15);
    // mpz_init_set_si(a, 1);
    // mpz_init_set_si(z, 53);
    // mpz_init_set_si(b, 25);
    // mpz_init_set_si(n, 25);
    // gmp_printf("result: %d\n", (mpz_get_ui(a) == 20));
    // mod_inverse(i, a, n);
    // mod_inverse(i, a, n);
    // gmp_printf
    // gmp_printf("i: %Zd\n", i);
    bool z = is_prime(a, 10);
    printf("isprime: %d\n", z);

    // pow_mod(out, x, y, z);
    // is_prime(mpz_t n, uint64_t iters);
    // printf("%d\n", is_prime(n, 100));
    // gmp_printf("powermod: %Zd\n", out);
    // bool num_is_prime = is_prime(a, 1000);
    //printf("The number is a prime: %d\n", num_is_prime);
    // gmp_printf("prime?: %Zd\n", is_prime(a, 10));
    // gmp_printf("odd?: %Zd\n", mpz_odd_p(a));
    // make_prime(p, 16, 1000);
    randstate_clear();
    return 1;
}
