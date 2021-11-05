#include "io.h"
#include "code.h"
#include "defines.h"

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>




int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int numBytesRead = 0;
    
    if (infile != 0) {
        while (nbytes > 0) {
            int n = read(infile, buf+numBytesRead, BLOCK);
            // printf("Finishing reading: %d\n", n);
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

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int numBytesWritten = 0;
    
        while (nbytes > 0) {
            int n = write(outfile, buf+numBytesWritten, BLOCK);
            // printf("Finishing reading: %d\n", n);
            if (n <= 0) {
                break;
            }
            numBytesWritten += n;
            nbytes -= n;
        }
        return numBytesWritten;
    return 0;

}

// bool read_bit(int infile, uint8_t *bit);

// void write_code(int outfile, Code *c);

// void flush_codes(int outfile);


