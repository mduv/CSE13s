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

    // comparision with beta != 0
    while ((mpz_cmp_si(beta, 0)) != 0) // while b != 0
    {
        mpz_set (t, beta);              // set t to b
        mpz_mod (beta, alpha, beta);    // set b to a mod b
        mpz_set (alpha, t);             // set a to t

    }

    mpz_set (d, alpha); // set d to a

    mpz_clear (alpha);
    mpz_clear (beta);
    mpz_clear (t);

}

// Computes the inverse i of a modulo n. In the event that a modular inverse cannot be found, set i to 0.
void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {
    // initialize variables
    mpz_t r, r_inverse, t, t_inverse, q, aux1, aux2;
    mpz_init (r);
    mpz_init (r_inverse);
    mpz_init (q);
    mpz_init (aux1);
    mpz_init (aux2);

    // set variables
    mpz_set (r, n); // set r to n
    mpz_set (r_inverse, a); // set r' to a
    mpz_init_set_si(t, 0); // set t to 0
    mpz_init_set_si(t_inverse, 1); // set t' to 1

    while ((mpz_cmp_si(r_inverse, 0)) != 0) { // r' != 0
        mpz_fdiv_q(q, r, r_inverse); // set q to r/r'

        // (r, r') <- (r', r - q x r')
        mpz_set (aux2, r); 
        mpz_set (r, r_inverse); 
        mpz_mul (aux1, q, r_inverse); // set aux1 to q*r'
        mpz_sub (r_inverse, aux2, aux1);   // set r' to r-aux1

        // (t, t') <- (t', t - q * t')
        mpz_set (aux2, t); // set aux2 to t
        mpz_set (t, t_inverse); // set t to t'
        mpz_mul (aux1, q, t_inverse); // set aux1 tp q*t'
        mpz_sub (t_inverse, aux2, aux1);   // set t' to t-aux1
    }

    if ((mpz_cmp_si(r, 1)) > 0) {   // if r > 1
        // no inverse
        mpz_set_si(i, 0);        // set i to 0
        mpz_clear (r);
        mpz_clear (r_inverse);
        mpz_clear (t);
        mpz_clear (t_inverse);
        mpz_clear (q);
        mpz_clear (aux1);
        mpz_clear (aux2);
        return;
    }

    if ((mpz_cmp_si(t, 0)) < 0) {   // if t < 0
        mpz_add (t, t, n);          // t = t + n
    }
    
    mpz_set (i, t); // set i to t
    mpz_clear (r);
    mpz_clear (r_inverse);
    mpz_clear (t);
    mpz_clear (t_inverse);
    mpz_clear (q);
    mpz_clear (aux1);
    mpz_clear (aux2);
}

// Performs fast modular exponentiation, computing base raised to the exponent power modulo modulus,
// and storing the computed result in out.
void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {

    mpz_t p, v, aux1, ex, exp, two;
    mpz_init(p);
    mpz_init(aux1);
    mpz_init(ex);
    mpz_init(exp);
    mpz_set (exp, exponent);

    mpz_init_set_si(v, 1); // set v to 1
    mpz_init_set_si(two, 2);
    mpz_set (p, base); // set p to base    

    while (mpz_cmp_si(exp, 0) > 0) { // while exp > 0
        mpz_mod(ex, exp, two);
        if(mpz_cmp_si(ex, 1) == 0) { // if d is odd
            // v ← (v×p) mod n
            mpz_mul (aux1, v, p); 
            mpz_mod (v, aux1, modulus);
        }

        // p ← (p×p) mod n
        mpz_mul (aux1, p, p); 
        mpz_mod (p, aux1, modulus);

         // d ← d/2
        mpz_fdiv_q_ui(exp, exp, 2); 
    }

    mpz_set (out, v); // set out to v

    mpz_clear (p);
    mpz_clear (v);
    mpz_clear (aux1);
    mpz_clear (ex);
    mpz_clear (exp);
    mpz_clear (two);
}

bool is_prime(mpz_t n, uint64_t iters) {

    // special case numbers less than 3 as we can generate random numbers only for higher numbers
    if (mpz_cmp_si(n, 1) <= 0) {
        return false;
    }
    if (mpz_cmp_si(n, 2) == 0) {
        return true;
    }
    if (mpz_cmp_si(n, 3) == 0) {
        return true;
    }

    mpz_t r, y, a, n_minus_1, n_minus_3, two, ex1;
    
    mpz_init(r);
    mpz_init(y);
    mpz_init(a);
    mpz_init(n_minus_1);
    mpz_init(n_minus_3);
    mpz_init_set_si(two, 2); // set two to 2
    mpz_init(ex1);
    
    mpz_sub_ui(r, n, 1); // set r to n -1
    mpz_sub_ui(n_minus_1, n, 1); // set nminus1 to n -1
    mpz_sub_ui(n_minus_3, n, 3);
    
    mpz_mod_ui(ex1, r, 2);
    int64_t s = 0;
    while (mpz_cmp_si(ex1, 0) == 0) { // while r is even
        s++;
        mpz_fdiv_q_ui(r, r, 2);
        mpz_mod_ui(ex1, r, 2);
    }

    for (uint64_t i = 0; i<iters; i++) {        
        // random number between 0 and n-2
        mpz_urandomm (a, state, n_minus_3); // random number between 0 and n-4
        mpz_add (a, a, two); // add two

        pow_mod(y, a, r, n);
        if ((mpz_cmp_si(y, 1) != 0) && (mpz_cmp(y,n_minus_1) != 0)) {   // y != 1 and y != n-1
            int64_t j = 1;            
            while ((j <= s-1) && (mpz_cmp(y,n_minus_1) != 0)) {  // j ≤s−1
                pow_mod(y, y, two, n);
                if (mpz_cmp_si(y, 1) == 0) {    
                    mpz_clear(r);
                    mpz_clear(y);
                    mpz_clear(a);
                    mpz_clear(n_minus_1);
                    mpz_clear(n_minus_3);
                    mpz_clear(two);
                    mpz_clear(ex1);
                    return false;
                }
                j++;
            }

            if ((mpz_cmp(y,n_minus_1) != 0)) {
                mpz_clear(r);
                mpz_clear(y);
                mpz_clear(a);
                mpz_clear(n_minus_1);
                mpz_clear(n_minus_3);
                mpz_clear(two);
                mpz_clear(ex1);
                return false;
            }
        }
    }

    mpz_clear(r);
    mpz_clear(y);
    mpz_clear(a);
    mpz_clear(n_minus_1);
    mpz_clear(n_minus_3);
    mpz_clear(two);
    mpz_clear(ex1);
    return true;
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    mpz_t x;
    mpz_init(x);
    
    mpz_rrandomb (x, state, bits);
    bool y = is_prime(x, iters);
    while (!y || (mpz_sizeinbase(x, 2) < bits)) {
        mpz_rrandomb(x, state, bits);
        y = is_prime(x, bits);
    }
    
    mpz_set (p, x);
    mpz_clear(x);
}


