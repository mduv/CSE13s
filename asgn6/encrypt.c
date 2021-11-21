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
static FILE *pubkeyfile = NULL;

bool verbose_mode = false;

int main(int argc, char **argv) {
    int opt = 0;
    optind = 1;
    
    input = stdin;
    output = stdout;
    char *pub_filename = "rsa.pub";

    // Parse command-line options using getopt() and handle them accordingly.

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n\tEncrypts data using RSA encryption.\n\tEncrypted data is decrypted by the decrypt program.\n\nUSAGE\n\t./encrypt [-hv] [-i infile] [-o outfile] -n pubkey\n\nOPTIONS"
                    "\n\t-h              Display program usage and help."
                    "\n\t-v              Display verbose program output."
                    "\n\t-i infile       Input file of data to encrypt (default: stdin)."
                    "\n\t-o outfile      Output file for encrypted data (default: stdout)."
                    "\n\t-n pbfile       Public key file (default: rsa.pub).\n");
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
            pub_filename = optarg;
            break;
        case 'v':
            verbose_mode = true;
            break;
        }
    }

    /* Open the public key files using fopen(). */


    pubkeyfile = fopen(pub_filename, "r");
    if (pubkeyfile == NULL) {
        perror("Error: unable to open public key file.");
        return (-1);
    }


    /* Read the public key from the opened public key file. */

    mpz_t p, q, n, e, m, d, s;
    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    mpz_init(e);
    mpz_init(m);
    mpz_init(d);
    mpz_init(s);
    char * username;
    username = getenv ("USER");

    
    rsa_read_pub(n, e, s, username, pubkeyfile);


    /* Convert the username that was read in to an mpz_t. This will be the expected value of the verified
    signature. Verify the signature using rsa_verify(), reporting an error and exiting the program if
    the signature couldn’t be verified. */

    mpz_t name;
    mpz_init(name);
    
    mpz_set_str(name, username, 62);


    if (!rsa_verify(name, s, e, n)) {
        printf("Error: unable to verify signature.\n");
        return (-1);
    }

    /* Encrypt the file using rsa_encrypt_file(). */

    rsa_encrypt_file(input, output, n, e);
    
    if (verbose_mode) {
        printf("user = %s\n", username);
        gmp_printf("s (%zu bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_printf("n (%zu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%zu bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
    }
    

    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(n);
    mpz_clear(e);
    mpz_clear(m);
    mpz_clear(d);
    mpz_clear(s);
    mpz_clear(name);
    fclose(pubkeyfile);
    fclose(input);
    fclose(output);


    return 0;
}
