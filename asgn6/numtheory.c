#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>

#include "numtheory.h"
#include "randstate.h"


// computes the gcd of a and b, storing the value of the computed divisor in d
void gcd(mpz_t d, mpz_t a, mpz_t b) {
    // initialize variables
    mpz_t alpha, beta, t;
    mpz_init (alpha);
    mpz_init (beta);
    mpz_init (t);

    // set variables
    mpz_set (alpha, a);
    mpz_set (beta, b);    

    // gmp_printf("alpha: %d\n", alpha);

    // comparision with beta != 0
    while ((mpz_cmp_ui(beta, 0)) != 0) // while b != 0
    {
        mpz_set (t, beta);              // set t to b
        // gmp_printf("t: %d\n", t);
        mpz_mod (beta, alpha, beta);    // set b to a mod b
        mpz_set (alpha, t);             // set a to to

    }

    mpz_set (d, alpha); // set d to a

    // gmp_printf("gcd: %d", d);
    mpz_clear (alpha);
    mpz_clear (beta);
    mpz_clear (t);

}

// Computes the inverse i of a modulo n. In the event that a modular inverse cannot be found, set i to 0.
void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {
    // initialize variables
    mpz_t r, r_inverse, t, t_inverse, q, aux1, fake_i;
    mpz_init (r);
    mpz_init (r_inverse);
    // mpz_init (t);
    // mpz_init (t_inverse);
    mpz_init (q);
    mpz_init (aux1);

    // set variables
    mpz_set (r, n); // set r to n
    mpz_set (r_inverse, a); // set r' to a
    mpz_init_set_ui(t, 0); // set t to 0
    mpz_init_set_ui(t_inverse, 1); // set t' to 1

    while ((mpz_cmp_ui(r_inverse, 0)) != 0)  // r' != 0
    {
        mpz_fdiv_q(q, r, r_inverse); // set q to r/r'
        
        mpz_set (r, r_inverse); // set r to r'
        mpz_mul (aux1, q, r_inverse); // set aux1 tp q*r'
        mpz_sub (r_inverse, r, aux1);   // set r' to r-aux1

        mpz_set (t, t_inverse); // set t to t'
        mpz_mul (aux1, q, t_inverse); // set aux1 tp q*t'
        mpz_sub (t_inverse, t, aux1);   // set t' to t-aux1
    }

    if ((mpz_cmp_ui(r, 1)) > 0) {   // if r > 1
        mpz_init_set_ui(fake_i, 0); // set fakei to 0
        mpz_set (i, fake_i);        // set i to 0
    }
    if ((mpz_cmp_ui(t, 0)) < 0) {   // if t < 0
        mpz_add (t, t, n);          // t = t + n
    }
    
    mpz_set (i, t); // set i to t
    







}

void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus);

bool is_prime(mpz_t n, uint64_t iters);

void make_prime(mpz_t p, uint64_t bits, uint64_t iters);


