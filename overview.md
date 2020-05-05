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
## Test
## Algorithm
## Complexity
## References
