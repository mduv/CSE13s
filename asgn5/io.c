#include "io.h"
#include "code.h"
#include "defines.h"

#include <stdint.h>
#include <unistd.h>

// static uint8_t write_bit_top = 0;
// static uint8_t write_bit_buffer[BLOCK] = {0};

// int read_bytes(int infile, uint8_t *buf, int nbytes) {
//     // create two variables
//     // one for bytes read so far during this function,
//     while((read(infile, buf + bytes_read_in, nbytes - bytes_read_in)) > 0) {
//         bytes_read += ;
//         if(bytes_read_in == nbytes) {
//             break;
//         }
//     }
//     return bytes_read;
// }

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int numBytesRead = 0;
    while (nbytes > 0)
    {
        int n = read(infile, buf+numBytesRead, nbytes);

        if (n == 0) {
            break;
        }
        numBytesRead += n;
        nbytes -= n;
    }
    return numBytesRead;
    
}

int write_bytes(int outfile, uint8_t *buf, int nbytes);

bool read_bit(int infile, uint8_t *bit);

void write_code(int outfile, Code *c);

void flush_codes(int outfile);


