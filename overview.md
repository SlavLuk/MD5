## Introduction

This repository contains a project completed for GMIT's Theory of Algorithms module. It involves writing a program in the 
C programming language to perform the MD5 (message-digest) algorithm, specifically MD5 processes a variable-length 
message (file as input) into a fixed-length output of 128 bits. 
Initially this repository contained README.md file describing running ,testing the program and md5.c file the implemention code of 
MD5 algorithm, later a few files were added to accommodate extra requirements added in a light of canceling written exams such as 
getopt.h header file implementing getopt function found in the <a href="https://www.gnu.org/software/libc/manual/html_node/Using-Getopt.html#Using-Getopt">POSIX specification</a>
This getopt function was modified and adapted for working on Windows machine,it is being used to accept command line arguments.I adapted this implemention from
<a href="https://gist.github.com/superwills/5815344#file-getopt-c">here.</a> Another help.h header file contains menu functions being invoked from md5.c. The main
md5.c file processes a user input (file input) and outputs a fixed-length result of hashed string of 128 bits.
The algorithm is based on the <a href="https://tools.ietf.org/pdf/rfc1321.pdf">Request for comments: 1321</a>, the md5 message-digest algorithm.
## Run

### Prerequisites
The only requirement for this program is a C compiler.The given instruction is applied for Windows machine.
 1. Download MinGW for Windows(GCC).
><a href="https://sourceforge.net/projects/mingw/">MinGW - Minimalist GNU for Windows Compiler Collection (GCC)</a>
 2. Follow instructions from MinGW installer.

 3. After installation done, go and copy your path to MinGW\bin directory.
```sh
    C:\MinGW\bin
```
 4. Go to environment variables.
><img src="https://github.com/SlavLuk/MD5/blob/master/img/env.png">
 5. Select path on system variables, click edit, new and paste into MinGW\bin directory apply and close all windows.
><img src="https://github.com/SlavLuk/MD5/blob/master/img/path.png">
><img src="https://github.com/SlavLuk/MD5/blob/master/img/new.png">
 6. Check GCC compiler version from command line
><img src="https://github.com/SlavLuk/MD5/blob/master/img/confirm.png">

### Download
There are two ways to download repository 
 1. Clone this reposiory to your machine as a zip file
><img src="https://github.com/SlavLuk/MD5/blob/master/img/clone.png">
 2. Or copy link to directory
><img src="https://github.com/SlavLuk/MD5/blob/master/img/link.png">
 - Open command prompt, enter
```sh
    git clone https://github.com/SlavLuk/MD5
```
### Compile the program

 1. Start up Visual Studio code IDE
 2. In VS code open folder of downloaded repository 
 3. Open up terminal by pressing
```sh
    Ctrl + '
```
 4. Enter
```sh
    gcc -o md5 md5.c
```	
This will compile the program and add a ``md5.exe`` executable to the directory.

### Run the program

 1. In opened terminal enter
```sh
    ./md5 -f ./test.txt
```
 - ``./md5`` is the executable
 - ``-f`` is option (required)
 - ``./test.txt`` is the file name to execute
 2. For help menu enter
```sh
    ./md5 -h
```
 
## Test

To make sure that the program was up to standard it was tested using two
different md5 programs. One was an online <a href="http://onlinemd5.com">md5 converter</a> and the second was a
terminal converter called ``OpenSSL``. On both occasions the tests passed.
Please refer to <a href="https://github.com/SlavLuk/MD5/blob/master/README.md">README.md</a> for the full report.

For the project requirement i created test cases based on <a href="https://tools.ietf.org/pdf/rfc1321.pdf">appendix A.5 of RFC 1321</a> document.

 1. To run test cases enter
```sh
    ./md5 -t
```
><img src="https://github.com/SlavLuk/MD5/blob/master/img/test.png">

## Algorithm

The MD5 hashing algorithm is a one-way cryptographic function that accepts a message of any length as input and produces as output 
a 128-bit "fingerprint" or "message digest" of the input.One-way functions work in one direction, meaning that it is easy to compute the hash
value from a given message and hard to compute a message that hashes to a given hash value.
A robust one-way hash function is usually expected to satisfy some requirements, namely collision resistance, preimage resistance, second preimage resistance.
The MD5 algorithm is intended for digital signature applications, where a large file must be "compressed" in a secure manner before being encrypted with a private (secret) key under a public-key cryptosystem such as RSA.
MD5 consists of 64 operations, grouped into four rounds of 16 operations. The MD5 algorithm is designed to be quite fast on 32-bit machines. This algorithm found by Professor Ronald L. Rivest.
### The following six steps are performed to compute the message digest of the message.
 1. Step : Append Padding Bits.
>The message is "padded" (extended) so that its length (in bits) is congruent to 448, modulo 512. This padding is single 1 bit added to the end of the message, 
>followed by as many zeros are required so that the length of bits equals 448 modulo 512.Padding is always performed, even if the length of the message is already congruent to 448, modulo 512.

><img src="https://github.com/SlavLuk/MD5/blob/master/img/padding.png">
 2. Step : Append Length.
>A 64-bit representation of the message's length is appended to the result. This stage is to make the message length an exact multiple of 512 bits in length.
 3. Step : Divide the message.
>MD5 processes the input string in 512-bit blocks, divided into 16 32-bit sub-blocks. The output of the algorithm is set of four 32-bit blocks, which concatenate to form single 128-bit hash value.
 4. Step : Initialize MD Buffer.
>Four 32-bit variable are initialized:
 - A = 0x01234567
 - B = 0x89ABCDEF
 - C = 0xFEBCDA98
 - D = 0x76543210
>These are called chaining variables.
 5. Step : Process message.
>The main loop of the algorithm begins and continues for as many 512-bit blocks as are in the message. The four copied into the different variable: a gets A, b gets B, c gets C, and
>d gets D. the main loop has four rounds, all very similar. Each series uses a different operation 16 times. Each operation performs a nonlinear function on three of a, b, c, and d. 
>Then it adds that result to the right a variable number of bits and adds the result to one
>of a, b, c, and d. Finally, the result replaces one of a, b, c, and d.
>There are four nonlinear functions:
 - F(X,Y,Z) = (X && Y) || ((~X) && Z)
 - G(X,Y,Z) = (X && Z) || (Y && (~Z))
 - H(X,YZ) = X ^ Y ^ Z
 - I(X,Y,Z) = Y ^ (X || (~Z))
 - (|| is OR, && is AND, ^ is XOR, ~ is NOT)
 6. Step : Output.
>The message digest produced as output is A, B, C, D. That is, output begins with low-order byte of A, and end with the high-order byte of D.
### Main algorithm in md5.c explained
 - Create constants according to <a href="https://tools.ietf.org/pdf/rfc1321.pdf">request for comments: 1321.</a>
 - Read in a full text file and save the length.
 - Message length multiply by 8 (to bytes) and add 1 to the end.
 - In the loop check if a new message length is congruent to 448, modulo 512, if it is out of the loop
otherwise keep going.
 - Allocate memory and fill up with zeros (calloc function) based on new length.
 - Copy read message into new allocated memory with zeros.
 - Append '1' to the end of the message.
 - Set the last 64 bits to the message length in bits.
 - Process the message in successive 512-bit chunks.
 - Break chunk into sixteen 32-bit words.
 - The rest goes according to this pseudocode
><img src="https://github.com/SlavLuk/MD5/blob/master/img/main.png">
## Complexity
Let's analyze MD5 algorithm:
 1. Declare constants.
 2. Divide the input in blocks of constant size to loop over n times.
 3. Memory copy and allocation.
 4. Process the message in successive 512-bit chunks.
 5. Operations on basic MD5 functions.

In big-_O_ notation stage 1 uses _O_(1).In stage 2 we divide the input in blocks and in worst-case
iterate over only 447 times so the length of input has no significant effect on performence _O_(n/c).
Memory copy and  allocation in stage 3 uses _O_(1) constatnt time.Processing the input in successive 
512-bit chunks involves loop to be executed n times depending on the input length _O_(n).
Analyzing operations on basic MD5 functions we see that _f_ has a bunch of operators in loops that run constant times _O_(1).
By considering only the highest order term of the expression for the running time of the algorithm,
disregarding both the coefficient of that term and any lower order terms, 
thus the total time of MD5 on an input of length _n_ is _O_(1)+_O_(n/c)+_O_(1)+_O_(n)+_O_(1), or _O_(n).

A robust one-way hash function is usually expected to satisfy some requirements, namely collision resistance, 
preimage resistance, second preimage resistance.
Therefore some security properties are required to make a hash function _H_ suitable for
such cryptographic uses:
 1. Pre-image resistance: Given a hash value _h_ it should be hard to find any message _m_ such
that _h_ = _H_(_m_).
 2. Second pre-image resistance: Given a message _m1_ it should be hard to find another message
_m2_ != _m1_ such that _H_(_m1_) = _H_(_m2_).
 3. Collision resistance: It should be hard to find different messages _m1_, _m2_ such that _H_(_m1_) =
_H_(_m2_).

In cryptography, a pre-image attack on cryptographic hash functions tries to find a message that has a specific hash value. 
A cryptographic hash function should resist attacks on its pre-image (set of possible inputs).
#### Brute-force attack.
Brute-force attacks are an application of brute-force search, 
the general problem-solving technique of enumerating all candidates and checking each one.Brute-force attacks work by calculating 
every possible combination that could make up a hash and testing it to see if it is the correct hash.
For an _n_-bit hash, this attack has a time 
complexity 2<sup>n</sup>, which is considered too high for a typical output size of _n_ = 128 bits. 
Some significant pre-image attacks have already been discovered, but they are not yet practical.If a practical pre-image attack is 
discovered, it would drastically affect many Internet protocols.
#### Birthday attack.
A birthday attack is a type of cryptographic attack that exploits the mathematics behind the birthday problem in probability theory.
With a birthday attack, it is possible to find a collision of a hash function with time complexity in 2<sup>n/2</sup>, 
with 2<sup>n</sup> being the classical pre-image resistance security.






















## References
