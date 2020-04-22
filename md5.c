#include <stdio.h>
#include <inttypes.h>


// Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating
uint32_t s[64], K[64];
uint32_t i;

// s specifies the per-round shift amounts
s = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20, 
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23, 
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 
};

// Use binary integer part of the sines of integers (Radians) as constants:
K = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 
};

// Initialize variables:
uint32_t a0 = 0x67452301;   // A
uint32_t b0 = 0xefcdab89;   // B
uint32_t c0 = 0x98badcfe;   // C
uint32_t d0 = 0x10325476;   // D


// 64 byte variable(Block of memory) accessed using 3 types as shown
// problem with compiler and OS sometimes 
// depending on how(the order) the OS reads the Block in each type 
union block {
	uint64_t sixfour[8];
	uint32_t threetwo[16];
	uint8_t eight[64];
};

// enum is set to read at start
// if i cant read 64 bits from file pad and finish
// keeps track of where we are in padding the message
enum flag {
    READ, PAD0, FINISH
};

// is passed next block (*M)
// star (*) means memory address
// Reads the next Block of the padded message from input file
int nextblock(union block *M, FILE *infile, uint64_t *nobits, enum flag *status) {

    int i; 

    // finnish breaks while loop in hash
    if(*status == FINISH)
        return 0;

    if (*status== PAD0) {
        // padding with zeros
        for (int i = 0; i < 56; i++)
            M->eight[i] = 0x00;
        // adding leagth of input to the end
        M->sixfour[7] = bswap_64(*nobits);
        *status = FINISH;
        return 1;
    }

	size_t nobytesread = fread(M->eight, 1, 64, infile);
    if(nobytesread == 64){
        for (i = 0; i < 16; i++){
            // bswap changes to big endian integers
            M->threetwo[i] = bswap_32(M->threetwo[i]);
        }
        return 1;
    }

    // pad in last block if possible (can fit)
    // otherwise add another block full of padding
    if(nobytesread < 56) {
        // adding 1 to message block before the zeros
        // has to be a multiple of 8 i.e. 1000 0000
        M->eight[nobytesread] = 0x80; // 0x80 is 1000 0000 in hexidecimal
        
        // padding with zeros
        for (i = nobytesread +1; i<56; i++) 
            M->eight[i] = 0;
        // everything but the last 64 bit integer i.e. 14*32
        // rather than 16*32
        for (i = 0; i < 14; i++)
            // bswap changes to big endian integers
            M->threetwo[i] = bswap_32(M->threetwo[i]);
        // bswap swaps endian
        // adding leagth of input to the end
        M->sixfour[7] = bswap_64(*nobits);
        *status = FINISH;
        return 1;


    }

    // last block to big to pad in the same block, 
    // extra block full of padding added
    
    // adding 1 to message block before the zeros
    // has to be a multiple of 8 i.e. 1000 0000
    M->eight[nobytesread] = 0x80; // 0x80 is 1000 0000 in hexidecimal
    // padding with zeros
    for (int i = nobytesread + 1; i < 64; i++)
        M->eight[i] = 0;
    for (i = 0; i < 16; i++)
        // bswap changes to big endian integers
        M->threetwo[i] = bswap_32(M->threetwo[i]);
    *status  = PAD0;
    return 1;
}
