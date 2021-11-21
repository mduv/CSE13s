#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <gmp.h>
#include "randstate.h"
#include "numtheory.h"
#include "rsa.h"


/* Begin by creating primes p and q using make_prime(). We first need to decide the number of
bits that go to each prime respectively such that log2(n) ≥nbits. Let the number of bits for p
be a random number in the range [nbits/4,(3×nbits)/4). The remaining bits will go to q. The
number of Miller-Rabin iterations is specified by iters. */

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {

    uint64_t bits_for_p = rand() % (((3 * nbits)/4) + 1 - nbits/4) + nbits/4;
    make_prime(p, bits_for_p, iters);
    make_prime(q, nbits - bits_for_p, iters);
    mpz_mul(n, p, q);


    // Next, compute φ(n) = (p−1)(q−1)
    mpz_t totient_n, one, psub1, qsub1;
    mpz_init(totient_n);
    mpz_init(psub1);
    mpz_init(qsub1);
    mpz_init_set_si(one, 1);

    mpz_sub(psub1, p, one);
    mpz_sub(qsub1, q, one);

    mpz_mul(totient_n, psub1, qsub1);

    /* We now need to find a suitable public exponent e. In a loop, generate random numbers of around
    nbits using mpz_urandomb(). Compute the gcd() of each random number and the computed
    totient. Stop the loop you have found a number coprime (gcd is 1) with the totient: that will be the public
    exponent.*/

    mpz_t rand, g;
    mpz_init(rand);
    mpz_init(g);

    while (true) {
        mpz_rrandomb(rand, state, nbits);
        gcd(g, rand, totient_n);
        if (mpz_cmp_si(g,1) == 0) {
            mpz_set(e,rand);
            break;
        }
    }

    mpz_clear(totient_n);
    mpz_clear(one);
    mpz_clear(psub1);
    mpz_clear(qsub1);
    mpz_clear(rand);
    mpz_clear(g);
}


/*Writes a public RSA key to pbfile. The format of a public key should be n, e, s, then the username, each
of which are written with a trailing newline. The values n, e, and s should be written as hexstrings. See
the GMP functions for formatted output for help with writing hexstrings.*/

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%ZX\n%ZX\n%ZX\n%s\n", n, e, s, username);

}


/* Reads a public RSA key from pbfile. The format of a public should be n, e, s, then the username, each of
which should have been written with a trailing newline. The values n, e, and s should have been written
as hexstrings. See the GMP functions for formatted input for help with reading hexstrings. */

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%ZX\n%ZX\n%ZX\n%s\n", n, e, s, username);
}

/* Creates a new RSA private key d given primes p and q and public exponent e. To compute d, simply
compute the inverse of e modulo φ(n) = (p−1)(q−1). */

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t totient_n, one, psub1, qsub1;
    mpz_init(totient_n);
    mpz_init(psub1);
    mpz_init(qsub1);
    mpz_init_set_si(one, 1);

    mpz_sub(psub1, p, one);
    mpz_sub(qsub1, q, one);

    mpz_mul(totient_n, psub1, qsub1);

    mod_inverse(d, e, totient_n);


    mpz_clear(totient_n);
    mpz_clear(one);
    mpz_clear(psub1);
    mpz_clear(qsub1);
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%ZX\n%ZX\n", n, d);
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%ZX\n%ZX\n", n, d);
}


/* Performs RSA encryption, computing ciphertext c by encrypting message m using public exponent e and
modulus n. Remember, encryption with RSA is defined as E(m) = c = m^e (mod n).*/

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    
    
    // Calculate the block size k. This should be k = b(log2(n)−1)/8.

    int k = (mpz_sizeinbase(n, 2) - 1) / 8;

    /* Dynamically allocate an array that can hold k bytes. This array should be of type (uint8_t *) and
    will serve as the block. */ 

    uint8_t *buffer = (uint8_t *)malloc(k);

    /* Set the zeroth byte of the block to 0xFF. This effectively prepends the workaround byte that we
    need. */
    buffer[0] = 0xFF;

    mpz_t c;
    mpz_init(c);


    int numofbytesread = fread(buffer+1, 1, k-1, infile);

    mpz_t m;
    mpz_init(m);

    while (numofbytesread > 0) {
        mpz_import(m, numofbytesread+1, 1, sizeof(buffer[0]), 1, 0, buffer);
        rsa_encrypt(c, m, e, n);
        gmp_fprintf(outfile, "%ZX\n", c);
        
        numofbytesread = fread(buffer+1, 1, k-1, infile);
    }
    
    


    mpz_clear(m);
    mpz_clear(c);
    free(buffer);
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n);
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {

    int k = (mpz_sizeinbase(n, 2) - 1) / 8;
    uint8_t *buffer = (uint8_t *)malloc(k);

    mpz_t c;
    mpz_init(c);

    int fields_read = gmp_fscanf(infile, "%ZX\n", c);

    mpz_t m;
    mpz_init(m);

    unsigned long valid_bytes = 0;

    while (fields_read != EOF) {
        rsa_decrypt(m, c, d, n);
        mpz_export(buffer, &valid_bytes, 1, sizeof(buffer[0]), 1, 0, m);
        
        fwrite(buffer+1, 1, valid_bytes-1, outfile);

        fields_read = gmp_fscanf(infile, "%ZX\n", c);
    }
    
    mpz_clear(m);
    mpz_clear(c);
    free(buffer);
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_init(t);
    pow_mod(t, s, e, n);
    if (mpz_cmp(t,m) == 0){
        mpz_clear(t);
        return true;
    } else {
        mpz_clear(t);
        return false;
    }
}


