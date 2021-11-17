#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>

#include "numtheory.h"
#include "randstate.h"


// computes the gcd of a and b, storing the value of the computed divisor in d

// initialize ints
// set ints
// comparisions
// find mod function

void gcd(mpz_t d, mpz_t a, mpz_t b) {
    mpz_t alpha, beta, t;
    mpz_init (alpha);
    mpz_init (beta);
    mpz_init (t);

    mpz_set (alpha, a);
    mpz_set (beta, b);    

    // gmp_printf("alpha: %d\n", alpha);

    while ((mpz_cmp_ui(beta, 0)) != 0) // while b != 0
    {
        mpz_set (t, beta);              // set t to b
        // gmp_printf("t: %d\n", t);
        mpz_mod (beta, alpha, beta);    // set b to a mod b
        mpz_set (alpha, t);             // set a to to

    }

    mpz_set (d, alpha); // set d to a

    // gmp_printf("gcd: %d", d);

}

void mod_inverse(mpz_t i, mpz_t a, mpz_t n);

void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus);

bool is_prime(mpz_t n, uint64_t iters);

void make_prime(mpz_t p, uint64_t bits, uint64_t iters);


