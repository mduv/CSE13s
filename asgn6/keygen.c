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

#define OPTIONS "vhi:b:n:d:s:"

static FILE *pubkeyfile = NULL;
static FILE *privkeyfile = NULL;


uint64_t iters;
uint64_t bits;
uint64_t seed;
time_t seconds;

bool verbose_mode = false;


int main(int argc, char **argv) {
    int opt = 0;
    optind = 1;
    char *pub_filename = "rsa.pub";
    char *priv_filename = "rsa.priv";

    seconds = time(NULL);
    seed = seconds;
    iters = 50;
    bits = 256;

    int permissions = 0600;

    // Parse command-line options using getopt() and handle them accordingly.

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n\tGenerates an RSA public/private key pair.\n\nUSAGE\n\t./keygen [-hv] [-b bits] -n pbfile -d pvfile\n\nOPTIONS"
                    "\n\t-h              Display program usage and help."
                    "\n\t-v              Display verbose program output."
                    "\n\t-b bits         Minimum bits needed for public key n (default: 256)."
                    "\n\t-i confidence   Miller-Rabin iterations for testing primes (default: 50)."
                    "\n\t-n pbfile       Public key file (default: rsa.pub)."
                    "\n\t-d pvfile       Private key file (default: rsa.priv)."
                    "\n\t-s seed         Random seed for testing.\n");
            break;
        case 'n':
            pub_filename = optarg;
            break;
        case 'd':
            priv_filename = optarg;
            break;
        case 's':
            seed = atoi(optarg);
            break;
        case 'b':
            bits = atoi(optarg);
            break;
        case 'i':
            iters = atoi(optarg);
            break;
        case 'v':
            verbose_mode = true;
            break;
        }
    }
    /* Open the public key files using fopen(). */


    pubkeyfile = fopen(pub_filename, "w+");
    if (pubkeyfile == NULL) {
        perror("Error: unable to open public key file.");
        return (-1);
    }


    /* Open the private key files using fopen(). */

    privkeyfile = fopen(priv_filename, "w+");
    int privkeyfile_fd = fileno(privkeyfile);
    if (privkeyfile == NULL) {
        perror("Error: unable to open private key file.");
        return (-1);
    }
    
    

    
    /* Using fchmod() and fileno(), make sure that the private key file permissions are set to 0600 */
    fchmod(privkeyfile_fd, permissions);


    /* Initialize the random state using randstate_init(), using the set seed. */
    randstate_init(seed);




    /* Make the public and private keys using rsa_make_pub() and rsa_make_priv(), respectively. */

    mpz_t p, q, n, e, m, d, s;
    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    mpz_init(e);
    mpz_init(m);
    mpz_init(d);
    mpz_init(s);



    rsa_make_pub(p, q, n, e, bits, iters);
    
    rsa_make_priv(d, e, p, q);



    


    /* Get the current user’s name as a string. You will want to use getenv(). */
    char * username;
    username = getenv ("USER");

    /* Convert the username into an mpz_t with mpz_set_str(), specifying the base as 62. */

    mpz_t name;
    mpz_init(name);
    
    mpz_set_str(name, username, 62);

    /* Then, use rsa_sign() to compute the signature of the username. */
    
    
    rsa_sign(s, name, d, n);

    /* Write the computed public and private key to their respective files. */

    rsa_write_pub(n, e, s, username, pubkeyfile);
    rsa_write_priv(n, d, privkeyfile);

    
    if (verbose_mode) {
        printf("user = %s\n", username);
        gmp_printf("s (%zu bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_printf("p (%zu bits) = %Zd\n", mpz_sizeinbase(p, 2), p);
        gmp_printf("q (%zu bits) = %Zd\n", mpz_sizeinbase(q, 2), q);
        gmp_printf("n (%zu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%zu bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
        gmp_printf("d (%zu bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }
    

    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(n);
    mpz_clear(e);
    mpz_clear(m);
    mpz_clear(d);
    mpz_clear(name);
    mpz_clear(s);
    fclose(pubkeyfile);
    fclose(privkeyfile);
    free(username);
    randstate_clear();

    return 0;
}
