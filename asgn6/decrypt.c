#include <gmp.h>
#include <time.h>
#include "numtheory.h"
#include "rsa.h"
#include "randstate.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define OPTIONS "vhi:o:n:"

static FILE *input = NULL;
static FILE *output = NULL;
static FILE *privkeyfile = NULL;

bool verbose_mode = false;

int main(int argc, char **argv) {
    int opt = 0;
    optind = 1;
    
    input = stdin;
    output = stdout;
    char *priv_filename = "rsa.priv";

    // Parse command-line options using getopt() and handle them accordingly.

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n\tDecrypts data using RSA decryption.\n\tEncrypted data is encrypted by the encrypt program.\n\nUSAGE\n\t./decrypt [-hv] [-i infile] [-o outfile] -n privkey\n\nOPTIONS"
                    "\n\t-h              Display program usage and help."
                    "\n\t-v              Display verbose program output."
                    "\n\t-i infile       Input file of data to decrypt (default: stdin)."
                    "\n\t-o outfile      Output file for decrypted data (default: stdout)."
                    "\n\t-n pvfile       Private key file (default: rsa.priv).\n");
            break;
        case 'i':
            input = fopen(optarg, "r");
            if (input == NULL) {
                perror("Error: unable to read infile.");
                return (-1);
            }
            break;
        case 'o':
            output = fopen(optarg, "w+");
            if (output == NULL) {
                perror("Error: unable to read outfile.");
                return (-1);
            }
            break;
        case 'n':
            priv_filename = optarg;
            break;
        case 'v':
            verbose_mode = true;
            break;
        }
    }

    /* Open the private key file using fopen(). Print a helpful error and exit the program in the event of
    failure. */


    privkeyfile = fopen(priv_filename, "r");
    if (privkeyfile == NULL) {
        perror("Error: unable to open private key file.");
        return (-1);
    }


    /* Read the private key from the opened private key file. */

    mpz_t n, e, d;
    mpz_init(n);
    mpz_init(e);
    mpz_init(d);
    
    rsa_read_priv(n, d, privkeyfile);


    /* Decrypt the file using rsa_decrypt_file(). */

    rsa_decrypt_file(input, output, n, d);
    
    if (verbose_mode) {
        gmp_printf("n (%zu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("d (%zu bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }
    

    mpz_clear(n);
    mpz_clear(e);
    mpz_clear(d);
    fclose(privkeyfile);
    fclose(input);
    fclose(output);
    // free(priv_filename);


    return 0;
}
