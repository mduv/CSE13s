Assignment 6 - Public Key Cryptography

This assignment consists of three implemented programs. The keygen program is in charge of key
generation, producing RSA public and private key pairs. The encrypt program encrypts files using
a public key, and the decrypt program decrypts the encrypted files using the corresponding private key.
The program is writted using two implemented libraries. One of the libraries holds functions relating
to the mathematics behind RSA, and the other library itself contains implementations of routines for RSA.

Building

Build the program with:
make

Running

Run the program with:
$ ./keygen [-hv] [-b bits] -n pbfile -d pvfile
$ ./encrypt [-hv] [-i infile] [-o outfile] -n pubkey
$ ./decrypt [-hv] [-i infile] [-o outfile] -n privkey


OPTIONS (keygen)
    -h              Display program usage and help.
    -v              Display verbose program output.
    -b bits         Minimum bits needed for public key n (default: 256).
    -i confidence   Miller-Rabin iterations for testing primes (default: 50).
    -n pbfile       Public key file (default: rsa.pub).
    -d pvfile       Private key file (default: rsa.priv).
    -s seed         Random seed for testing.


OPTIONS (encrypt)
    -h              Display program usage and help.
    -v              Display verbose program output.
    -i infile       Input file of data to encrypt (default: stdin).
    -o outfile      Output file for encrypted data (default: stdout).
    -n pbfile       Public key file (default: rsa.pub).

OPTIONS (decrypt)
    -h              Display program usage and help.
    -v              Display verbose program output.
    -i infile       Input file of data to decrypt (default: stdin).
    -o outfile      Output file for decrypted data (default: stdout).
    -n pvfile       Private key file (default: rsa.priv).

