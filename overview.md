# MD5 hasing Algorithm 
#### by James Mullarkey (G00345716)

## Introduction 
#### My github repository consistis of:
  **.gitignore file** - to so no executebale file is added to the repository.
  
  **README.md** - contains information how to run the MD5 file.
  
  **md5.c** - contains the code for a MD5 hasing algorithm.
  
  **sha256.c** - contains the code for a SHA256 hasing algorithm.
My MD5 algrithm works by runnging these commands:
* make md5
* ./md5 "The quick brown fox jumps over the lazy dog"

make md5 - created the exicutable file and "./md5 "The quick....." runs it with the input string"
the input string is then used to hash in the algorithm when it is passed to the nextblock fucntion.

First the legth of the string is calculated. The lenth after padding is calculated divisable by 512 blocks, 
except the last balck which is 512-64 = 448(64 bit space made for the length of the string input 
to appended to the end, as the algorithm requires). 

calloc() is used to append the zeros to the empty spaces 
in the new length of the input(padding). 1 bit is added to the end of the string before the zeros, using the 
initial length place holder. The initial length is added to the end of the padded input(in bits). 

The message is processed in 512-bit chunks to pad and the resulting hash ia appends to the 4 hash variables set 
out by the standard documentation. The resulting hash is output ot the user.



An introduction to your repository and code. Describe
what is contained in the repository and what the code does.

## Run 
You should explain how to download, compile, and run your code.
Include instructions of how to install the compiler.
Test Explain how to run the tests included in your code.


## Algorithm 
Give an overview and explanation of the main algorithm(s)
in your code. You might use a well-thought out diagram here.

## Complexity 
This should be the most significant part of the report.
You must give an analysis of the complexity of the MD5 algorithm,
including the complexity of algorithms that attempt to reverse the
algorithm. That is, algorithms that attempt to find an input for
which the MD5 algorithm produces a given output. You should
research this topic before writing this section and your analysis
should be carefully referenced.

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


Provide a list of references used in your project. The
references should not just be a list of websites. Instead, there
should be a short explanation of why each reference is relevant to
your document.
