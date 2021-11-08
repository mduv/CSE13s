#include "code.h"
#include "defines.h"
#include "node.h"
#include "huffman.h"
#include <string.h>
#include "stack.h"
#include "pq.h"
#include "header.h"
#include "io.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define OPTIONS "vhi:o:"

uint64_t hist[ALPHABET] = { 0 };
Code table[ALPHABET] = { 0 };
int input_fd;
int output_fd = 1;
bool verbose_mode = false;
uint64_t compressed_file_size;
uint64_t uncompressed_file_size;

int main(int argc, char **argv) {
    int opt = 0;
    optind = 1;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n\tA Huffman decoder.\n\tDecompresses a file using the Huffman coding "
                   "algorithm.\n\nUSAGE\n\t./decode [-h] [-i infile] [-o outfile]\n\nOPTIONS\n\t-h "
                   "            Program usage and help.\n\t-v             Print compression "
                   "statistics.\n\t-i infile      Input file to decompress.\n\t-o outfile     "
                   "Output of decompressed data.\n");
            break;
        case 'i':
            input_fd = open(optarg, O_RDONLY);
            if (input_fd < 0) {
                perror("Error: unable to read header.");
                return (-1);
            }
            struct stat stat_buf;
            if (stat(optarg, &stat_buf) == -1) {
                perror("Error: unable to read header.");
                return (-1);
            }
            compressed_file_size = stat_buf.st_size;
            break;
        case 'o':
            output_fd = open(optarg, O_WRONLY | O_APPEND | O_CREAT);
            if (output_fd < 0) {
                perror("Error: unable to open file");
                return (-1);
            }
            break;
        case 'v':
            verbose_mode = true;
            // Uncompressed file size: 7 bytes
            printf("Compressed file size: %lu bytes\n", compressed_file_size);
            // Compressed file size: 32 bytes
            // Space saving: -357.14%
            break;
            return 0;
        }
    }

    /* Read in the header from infile and verify the magic number. If the magic number does not match
    0xBEEFD00D (defined as MAGIC in defines.h), then an invalid file was passed to your program.
    Display a helpful error message and quit. */
    Header h;
    Header *ptr_to_h = &h;
    uint8_t *ptr_to_bytes = (uint8_t *) ptr_to_h;
    read_bytes(input_fd, ptr_to_bytes, sizeof(Header));
    if (h.magic != MAGIC) {
        // perror("Error: magic number does not match");
        return -1;
    }

    //printf("h.magic:%X, h.permissions:%X, h.tree_size:%X, h.file_size:%llX\n", h.magic, h.permissions, h.tree_size, h.file_size);
    fchmod(output_fd, h.permissions);

    // Rebuild tree from the bytes read from the file
    uint8_t *tree_buf = (uint8_t *) malloc(h.tree_size);
    read_bytes(input_fd, tree_buf, h.tree_size);
    Node *root = rebuild_tree(h.tree_size, tree_buf);

    uint8_t bit = 0;
    Node *current_node = root;
    uint64_t i = 0;
    while (i < h.file_size) {
        read_bit(input_fd, &bit);
        if (bit == 0) {
            current_node = current_node->left;
            if (current_node->left == NULL && current_node->right == NULL) {
                write_bytes(output_fd, &(current_node->symbol), sizeof(current_node->symbol));
                i++;
                current_node = root;
            }
        } else {
            current_node = current_node->right;
            if (current_node->left == NULL && current_node->right == NULL) {
                write_bytes(output_fd, &(current_node->symbol), sizeof(current_node->symbol));
                i++;
                current_node = root;
            }
        }
    }

    close(input_fd);
    if (verbose_mode) {
        struct stat stat_buf;
        if (fstat(output_fd, &stat_buf) == -1) {
            perror("Error: unable to read header.");
            return (-1);
        }
        uncompressed_file_size = stat_buf.st_size;
        printf("Uncompressed file size: %lu bytes\n", uncompressed_file_size);

        float space_savings = 100 * (1 - ((float) compressed_file_size / uncompressed_file_size));
        printf("Space saving: %f%%\n", space_savings);
    }
    close(output_fd);
}
