#include "io.h"
#include "code.h"
#include "defines.h"

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

#define BITS_IN_BLOCK         (BLOCK * 8)             // 4KB blocks.



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

/* The same bit-buffering logic used in read_bit() will be used in here as well. This function will also
make use of a static buffer (we recommend this buffer to be static to the file, not just this function) and
an index. Each bit in the code c will be buffered into the buffer. The bits will be buffered starting from the
0th bit in c. When the buffer of BLOCK bytes is filled with bits, write the contents of the buffer to outfile. */

static uint8_t write_code_buffer[BLOCK] = {0};
static uint32_t index = 0;


void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < code_size(c); i++) {
        code_get_bit(c, i); // code bit
        // write code bit into correct index of buffer
        uint32_t k = index / 8;  // index of which byte in buffer
        uint32_t pos = index % 8;  // bit position in uint8 bit in buffer
        uint8_t flag = 1 << pos;  // shifted position
        if (code_get_bit(c, i) == 1) {
            write_code_buffer[k] = code_get_bit(c, i) | flag;
        } else {
            flag = ~flag;
            write_code_buffer[k] = code_get_bit(c, i) & flag;
        }
        index++;
        if (index == BITS_IN_BLOCK) {
            write_bytes(outfile, write_code_buffer, BLOCK);
            index = 0;
            // write_code_buffer[BLOCK] = {0};
        }
    }
}

bool clear_bit(uint32_t bit_position) {
    if (bit_position < (BITS_IN_BLOCK)) {
        uint32_t k = bit_position / 8;  // index of which byte in buffer
        uint32_t pos = bit_position % 8;  // bit position in uint8 bit in buffer
        uint8_t flag = 1 << pos;  // shifted position
        flag = ~flag;
        write_code_buffer[k] = write_code_buffer[k] & flag;
        return 1;
    } else {
        return 0;
    }
}

void flush_codes(int outfile) {
    for (uint32_t i = index; i < BITS_IN_BLOCK; i++) {
        clear_bit(i);
    }
    write_bytes(outfile, write_code_buffer, BLOCK);
}



