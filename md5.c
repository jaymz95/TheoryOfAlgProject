#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <byteswap.h>

//Define word Section 2.1
#define WORD uint32_t

// Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating

uint32_t i;

// s specifies the per-round shift amounts
uint32_t s[64] = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20, 
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23, 
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 
};

// Use binary integer part of the sines of integers (Radians) as constants:
uint32_t K[64] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 
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


// leftitrotate function definition
#define leftitrotate(x, c) ((x << c) | (x >> (32-c)));

// is passed next block (*M)
// star (*) means memory address
// Reads the next Block of the padded message from input file
int nextblock(uint8_t *original_input) {

    int i;
    // Message (to prepare)
    uint8_t *input = NULL; 

    size_t initial_len = strlen(original_input);
    
    // Pre-processing: padding with zeros
    //append "0" bit until message length in bit ≡ 448 (mod 512)
    //append length mod (2 pow 64) to message
    
    // making sure its a multiple of 64 - 8 bytes 
    // to add the 8 byte length to the end making 
    // the total size divisible by 64
    // i.e. the last block will be 448 bits rather than 512
    // then the last 64 bits will be added (the initial length)
    int new_len = ((((initial_len + 8) / 64) + 1) * 64) - 8;

    //Number of arguments: Unlike malloc(), calloc() takes two arguments:
    // "new_len + 64" Number of blocks to be allocated.
    // "1" Size of each block.

    // this line appends zeros (1 bit is added to the begining of these zeros after this line)
    input = calloc(new_len + 64, 1); // also appends "0" bits 
                                   // (we allocate also 64 extra bytes )
    
    // copying initial_msg to msg 
    // with the size of initial message length
    // (+ 1) appending 1 bit
    memcpy(input, original_input, initial_len);
    input[initial_len] = 128; // write the "1" bit

    // message length in bits rather than bytes
    // appends the length in bits at the end of the hash
    uint32_t bits_len = 8*initial_len; 
    memcpy(input + new_len, &bits_len, 4);

    
    // Section 6.2.2
    WORD *W;

    // Process the message in successive 512-bit chunks:
    // for each 512-bit chunk of message:
    int offset;
    for(offset=0; offset < new_len; offset += (512/8)) {
        // dereferencing pointer (M->threeteo[t])
        *W = (uint32_t *) (input + offset);
        
        // Initialize hash value for this chunk:
        uint32_t A = a0;
        uint32_t B = b0;
        uint32_t C = c0;
        uint32_t D = d0;
        
        // Main loop:
        uint32_t i;
        for(i = 0; i<64; i++) {
            uint32_t F, g;
            if (i >= 0 && i < 16){
                F = (B & C) | ((~B) & D);
                g = i;
            }
            else if (i >= 16 && i <= 31) {
                F = (D & B) | ((~D) & C);
                g = (5*i + 1) % 16;
            }
            else if (i >= 32 && i <= 47) {
                F = B ^ C ^ D;
                g = (3*i + 5) % 16;
            }
            else if (i >= 48 && i <= 63) {
                F = C ^ (B | (~D));
                g = (7*i) % 16;
            }
            // Be wary of the below definitions of a,b,c,d
            F = F + A + K[i] + W[g];  // M[g] must be a 32-bits block
            //uint32_t temp = A;
            A = D;
            D = C;
            C = B;
            B = B + leftitrotate(F, s[i]);
        }
        a0 = a0 + A;
        b0 = b0 + B;
        c0 = c0 + C;
        d0 = d0 + D;
    }
    
    // cleanup local msg variable for next time method is called
    free(input);

    //nexthash(input);

}

void nexthash(uint8_t *input) {
    

}
// The command line arguments are handled using main() function arguments 
// where argc refers to the number of arguments passed, and argv[] is a 
// pointer array which points to each argument passed to the program
int main(int argc, char *argv[]) {
    char *input;
    // Expect and open a single filename
	if (argc != 2) {
		printf("Error: expected string as argument.\n");
		return 1;
	}
    input = argv[1];
    //size_t len = strlen(msg);
    //md5(msg, len);

	// FILE *infile = fopen(argv[1], "rb");
	// if (!infile) {
	// 	printf("Error: couldn't open file %s.\n", argv[1]);
	// 	return 1;
	// }

    //FILE *infile = "The quick brown fox jumps over the lazy dog.";
	
    // current padded message block
	//union block M;
    //uint64_t nobits = 0;

    // Section 5.3.3
    // WORD H[] = {
    //     0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    //     0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19  
    // };
    
    // read thriugh all of the padded message blocks
    // structs and unions in c are passed by value
    // pass the address of M (&)
    // while (nextblock(&M, (uint32_t*)input, &nobits, &status)) {
    //     //calculate the next hash value
    //     // M is not a pointer in this case (no arrow (->))
    //     // M.threetwo with no [] passes the
    //     // memory address of the first 32 integers
    //     nexthash(M.threetwo);
        
    // }
    nextblock(input);
    printf("\n%2.2x%2.2x%2.2x%2.2x\n\n", bswap_32(h0), bswap_32(h1), bswap_32(h2), bswap_32(h3));
   
    //uint32_t digest[16] = { a0, b0, c0, d0 }; // (Output is in little-endian)

    // for (int i = 0; i < 4; i++){
    //     printf("%02" PRIx32 " ", digest[i]);
    // }
    // printf("\n");
	//fclose(infile);

	return 0;
}
