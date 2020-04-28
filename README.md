# TheoryOfAlgProject

### Comments in code explains code as you go through it

![Image of Algorithm](https://github.com/jaymz95/TheoryOfAlgProject/blob/master/Theoryof.png)

## How to run code:
#####   cd TheoryOfAlgProject
#####   make md5
#####   ./md5 "The quick brown fox jumps over the lazy dog"
###   result should be: 9e107d9d372bb6826bd81d3542a419d6
#####    result is in big endian(using bswap)

### Implementaion:
I wrote this program using the modules weekly video tutorials for the SHA265 hashing algorithm. I used this allong with the "The MD5 Message-Digest Algorithm" (https://tools.ietf.org/html/rfc1321) to create a rough version of the algorithm, altough it did not work correctly, so i used https://en.wikipedia.org/wiki/MD5 and https://gist.github.com/creationix/4710780 to fix the parts of my algorithm that didnt work. This can be shown in my commit history.

### How it works:
This program works by getting input string from user.
Pre-processing: padding with zeros.
Append "0" bit until message length in bit ≡ 448 (mod 512).
Making sure its a multiple of 64 (- 8) bytes (the 8 byte input length is appended to the end) making the total size divisible by 64
i.e. the last block will be 448 bits rather than 512 then the last 64 bits will be added (the initial length).

Number of arguments: Unlike malloc(), calloc() takes two arguments:
   "new_len + 64" Number of blocks to be allocated.
   "1" Size of each block.
Append 1 bit to the original size position of the input i.e. before the zeros.
Input length in bits rather than bytes and appends the input length in bits at the end of the hash.

Process the message in successive 512-bit chunks using the psudeocode from wikipedia:
Cleanup local input variable for next time method is called.
Print out hash as big endian using bswap to convert it.

## references:
####  https://tools.ietf.org/html/rfc1321
####  https://en.wikipedia.org/wiki/MD5
####  https://gist.github.com/creationix/4710780
####  https://www.tutorialspoint.com/cprogramming/c_operators.htm
####  https://www.tutorialspoint.com/c_standard_library/c_function_memcpy.htm
####  https://www.tutorialspoint.com/cprogramming/c_command_line_arguments.htm
####  https://www.programiz.com/c-programming/c-pointers
####  https://www.programiz.com/c-programming/c-dynamic-memory-allocation
####  https://en.wikipedia.org/wiki/Endianness
