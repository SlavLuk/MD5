# Theory of Algorithms Project

>Title: MD5 message-digest algorithm
>
>Author: Slav Lukyanov
>
>Student-ID: G00339839
>
>Module: Theory of Algorithms
>
>Year: 4
>
>Lecturer: Ian McLoughlin

## Introduction

# MD5 (MD5 message-digest algorithm)
MD5 processes a variable-length message (file as input) into a fixed-length output of 128 bits.
This MD5 was written in C as part of my studies in GMIT in the Theory of Algorithms module.

## Setup and Usage

### Prerequisites

1. <a href="https://sourceforge.net/projects/mingw/">MinGW - Minimalist GNU for Windows Compiler Collection (GCC)</a>
2. <a href="https://github.com/SlavLuk/MD5">Clone repo</a>

### Running the Program
First compile the program using gcc

> gcc -o md5 md5.c 

This command will compile md5.c file into and executable (.exe)

To execute the programme :
>type ./md5 and enter in a file name you would like to hash and it will return a result

The output after the program has run should be a series of characters
an example input and output can be seen below
><img src="https://github.com/SlavLuk/MD5/blob/master/img/example.PNG">

## Project Testing

To make sure that the program was up to standard it was tested using two 
different md5 programs. One was an online <a href="http://onlinemd5.com">md5 converter</a> and the second was a 
terminal converter called open ssl. On both occasions the tests passed.
 
1.Empty file

An open ssl example can be seen below which hashes empty file
><img src="https://github.com/SlavLuk/MD5/blob/master/img/empty.png">
Online md5 converter hashes the same empty file
><img src="https://github.com/SlavLuk/MD5/blob/master/img/online.png">
And md5 from my windows machine the same empty file
><img src="https://github.com/SlavLuk/MD5/blob/master/img/mine.png">

2.Large file(War and Peace by graf Leo Tolstoy)

OpenSSL hashes large file
><img src="https://github.com/SlavLuk/MD5/blob/master/img/warssl.png">
On line MD5 checksum
><img src="https://github.com/SlavLuk/MD5/blob/master/img/warline.png">
Hashed large file from my windows 10
><img src="https://github.com/SlavLuk/MD5/blob/master/img/warmine.png">

## Problems Encountered

### Newline character '\n'

During development and testing I encountered an error when running the algorithm on Windows devices.
When I looked further into the error specific to the OS, I found that files with a newline
control character caused the hash to differ from the hash online and Linux.

To denote a single line break, Unix programs use line feed, whose hexadecimal value in ASCII is 0a, 
while most programs common to MS-DOS and Microsoft Windows
use carriage return+line feed, whose hexadecimal value in ASCII is 0d 0a.

To overcome this problem i pre-prosessed text file.The tr command is available on 
virtually every Unix-like system and can be used to perform arbitrary replacement operations 
on single characters.
A DOS/Windows text file can be converted to Unix format by simply removing all ASCII LF
characters with:
>$ tr -d '\n' < inputfile > outputfile
The file command can identify the type of line endings:
>$ file myfile.txt
>myfile.txt: ASCII English text, with CRLF line terminators



