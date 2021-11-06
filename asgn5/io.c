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

    if (outfile > 0) {
        while (nbytes > 0) {
            int n = write(outfile, buf+numBytesWritten, BLOCK);
            if (n <= 0) {
                break;
            }
        numBytesWritten += n;
        nbytes -= n;
        }
        return numBytesWritten;
    }
    return 0;
}

bool read_bit(int infile, uint8_t *bit) {
    static uint8_t read_bit_buffer[BLOCK] = {0};
    static uint32_t read_bit_pointer = 0;
    static uint32_t read_bit_buffer_read = 0;

    if (read_bit_pointer == 0) {
        read_bit_buffer_read = read_bytes(infile, read_bit_buffer, BLOCK);
        if (read_bit_buffer_read == 0) {
            return false;
        }
    }
    uint32_t k = read_bit_pointer / 8;  // index of which byte
    uint32_t pos = read_bit_pointer % 8;  // bit position in uint8 bit
    uint8_t flag = 1 << pos;
    if ((read_bit_buffer[k] & flag) == flag) {
        *bit = 1; // (bit u need to read from read_bit_buffer)
    } else {
        *bit = 0;
    }
    read_bit_pointer++;
    if (read_bit_pointer == (read_bit_buffer_read * 8)) {
        read_bit_pointer = 0;
    }
    return true;
}

// void write_code(int outfile, Code *c);

// void flush_codes(int outfile);


