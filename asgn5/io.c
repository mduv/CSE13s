#include "io.h"
#include "code.h"
#include "defines.h"

#include <stdint.h>
#include <unistd.h>




int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int numBytesRead = 0;
    if (infile != 0) {
        while (nbytes > 0) {
            int n = read(infile, buf+numBytesRead, nbytes);
            if (n <= 0) {
                break;
            }
            numBytesRead += n;
            nbytes -= n;
        }
        return numBytesRead;
    }
    return 0;
}

// int write_bytes(int outfile, uint8_t *buf, int nbytes);

// bool read_bit(int infile, uint8_t *bit);

// void write_code(int outfile, Code *c);

// void flush_codes(int outfile);


