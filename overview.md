# MD5 hasing Algorithm 
#### by James Mullarkey (G00345716)

## Introduction 
#### My github repository consistis of:
  **.gitignore file** - to so no executebale file is added to the repository.
  
  **README.md** - contains information how to run the MD5 file.
  
  **md5.c** - contains the code for a MD5 hasing algorithm.
  
  **sha256.c** - contains the code for a SHA256 hasing algorithm.

First the length of the string is calculated. The lenth after padding is calculated divisible by 512 blocks, 
except the last black which is 512-64 = 448(64 bit space made for the length of the string input 
to appended to the end, as the algorithm requires). 

calloc() is used to append the zeros to the empty spaces 
in the new length of the input(padding). 1 bit is added to the end of the string before the zeros, using the 
initial length place holder. The initial length is added to the end of the padded input(in bits). 

The message is processed in 512-bit chunks to pad and the resulting hash ia appends to the 4 hash variables set 
out by the standard documentation. The resulting hash is output ot the user.


## Run 
My MD5 algrithm works by runnging these commands:
* make md5
* ./md5 "The quick brown fox jumps over the lazy dog"

make md5 - created the executable file and ./md5 "The quick brown fox jumps over the lazy dog" runs the algorithm with the input string.

The input string is then used to hash in the algorithm when it is passed to the nextblock fucntion.


## Algorithm 
The MD5 message-digest algorithm is hashing algorithm that is used to hash a user input resulting in a 128-bit hash. This Algorithm pads a user input by adding zeros to it until the length of them input it divisible by 512 bits (blocks) with 64 bits left empty at the end for the length of the original input to be appended. 1-bit is placed in the position before the padded zeros, right after the initial message ends. 
Then the length of the original message is appended to the end of the padded making the new input divisible by 512-bits.

Once padding is finished it is time for the message to be hashed using the calculations from the documentation. These calculations use logical operators. Its uses logical AND, logical OR, logical XOR, One’s Complement, Right Shift and Left Shift. Then the 128-bit hash is returned to the user.

![Image of Algorithm](https://github.com/jaymz95/TheoryOfAlgProject/blob/master/Diagram.jpg)

## Complexity 
Seeing how I used C to code the algorithm I will be referencing the C operators in this document. In C the operators needed are as follows:
| Operator Name  | Symbol  | 
|---|---|
| AND Operator  | &  |
| OR Operator  | |  | 
| One’s Complement Operator   | ~  | 
| XOR Operator | ^  | 
| Right Shift Operator  | >>  |
| Left Shift Operator   | <<  |

#### Pseudocode (Wikipedia)

The MD5 hash is calculated according to this algorithm. All values are in little-endian.
```// Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating
var int s[64], K[64]
var int i

// s specifies the per-round shift amounts
s[ 0..15] := { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22 }
s[16..31] := { 5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20 }
s[32..47] := { 4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23 }
s[48..63] := { 6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 }

// Use binary integer part of the sines of integers (Radians) as constants:
for i from 0 to 63 do
    K[i] := floor(232 × abs (sin(i + 1)))
end for
// (Or just use the following precomputed table):
K[ 0.. 3] := { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee }
K[ 4.. 7] := { 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 }
K[ 8..11] := { 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be }
K[12..15] := { 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 }
K[16..19] := { 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa }
K[20..23] := { 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 }
K[24..27] := { 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed }
K[28..31] := { 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a }
K[32..35] := { 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c }
K[36..39] := { 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 }
K[40..43] := { 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05 }
K[44..47] := { 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665 }
K[48..51] := { 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039 }
K[52..55] := { 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1 }
K[56..59] := { 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1 }
K[60..63] := { 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 }

// Initialize variables:
var int a0 := 0x67452301   // A
var int b0 := 0xefcdab89   // B
var int c0 := 0x98badcfe   // C
var int d0 := 0x10325476   // D

// Pre-processing: adding a single 1 bit
append "1" bit to message    
// Notice: the input bytes are considered as bits strings,
//  where the first bit is the most significant bit of the byte.[50]

// Pre-processing: padding with zeros
append "0" bit until message length in bits ≡ 448 (mod 512)
append original length in bits mod 264 to message

// Process the message in successive 512-bit chunks:
for each 512-bit chunk of padded message do
    break chunk into sixteen 32-bit words M[j], 0 ≤ j ≤ 15
    // Initialize hash value for this chunk:
    var int A := a0
    var int B := b0
    var int C := c0
    var int D := d0
    // Main loop:
    for i from 0 to 63 do
        var int F, g
        if 0 ≤ i ≤ 15 then
            F := (B and C) or ((not B) and D)
            g := i
        else if 16 ≤ i ≤ 31 then
            F := (D and B) or ((not D) and C)
            g := (5×i + 1) mod 16
        else if 32 ≤ i ≤ 47 then
            F := B xor C xor D
            g := (3×i + 5) mod 16
        else if 48 ≤ i ≤ 63 then
            F := C xor (B or (not D))
            g := (7×i) mod 16
        // Be wary of the below definitions of a,b,c,d
        F := F + A + K[i] + M[g]  // M[g] must be a 32-bits block
        A := D
        D := C
        C := B
        B := B + leftrotate(F, s[i])
    end for
    // Add this chunk's hash to result so far:
    a0 := a0 + A
    b0 := b0 + B
    c0 := c0 + C
    d0 := d0 + D
end for

var char digest[16] := a0 append b0 append c0 append d0 // (Output is in little-endian)

// leftrotate function definition
leftrotate (x, c)
    return (x << c) binary or (x >> (32-c));
refernce: Wikipedia (https://en.wikipedia.org/wiki/MD5)
Pseudocode used for basis of project
```

#### Endian
Big Endian and little Endian is the order of bits in a binary representation of a number. When using the MD5 Message Digest Algorithm, different machines can get different results this is because Big Endian machine will display the resulting hash in a different order to a Little Endian machine. For this algorithm the result is in Little Endian as the Documentation suggests.
A Big Endian machine puts the most significant bits to the front whereas a Little Endian machine does the opposite.  



## References 
***MD5 Hashing Algorithm Documentation*** https://tools.ietf.org/html/rfc1321s

***Additional resource for coding my Algorithm*** https://en.wikipedia.org/wiki/MD5

***Additional resource for coding my Algorithm from github*** https://gist.github.com/creationix/4710780

***Logical Oporators in C documentaion*** https://www.tutorialspoint.com/cprogramming/c_operators.htm

***Information on memcpy() functionality*** https://www.tutorialspoint.com/c_standard_library/c_function_memcpy.htm

***Command line arguments in C*** https://www.tutorialspoint.com/cprogramming/c_command_line_arguments.htm

***How pointers work in C*** https://www.programiz.com/c-programming/c-pointers

***How memory Allocation works in C*** https://www.programiz.com/c-programming/c-dynamic-memory-allocation

***Endianness in programming*** https://en.wikipedia.org/wiki/Endianness

***Getopt arguments in C*** https://www.gnu.org/software/libc/manual/html_node/Getopt.html

***Command line arguments in C*** https://www.geeksforgeeks.org/getopt-function-in-c-to-parse-command-line-arguments/

***String concatinate in c*** https://www.techonthenet.com/c_language/standard_library_functions/string_h/strcat.php

***String compare in c*** https://stackoverflow.com/questions/8004237/how-do-i-properly-compare-strings

***Convert uint32_t to string in c for testing*** https://www.geeksforgeeks.org/what-is-the-best-way-in-c-to-convert-a-number-to-a-string/
