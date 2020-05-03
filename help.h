#ifndef HELP_H

#define HELP_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define WINDOWS /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

// print help menu
void help()
{
    fprintf(stderr,
            "\nUsage: md5 [OPTION] <file>\n"
            "A procedure for running md5.\n\n"
            "./md5 -f <file>\n\n"
            "Option:\n"
            "-h        print this help message.\n"
            "-t        run tests to check that the code is correct.\n"
            "-d        print current working directory.\n"
            "-f <file> run specified file as argument.\n"
            "-v        print version.\n\n"

            "<file> may be any file to be hashed.\n");
    exit(0);
}

// print current working directory
void cwd()
{

    char buff[FILENAME_MAX];
    GetCurrentDir(buff, FILENAME_MAX);
    printf("Current working dir: %s\n", buff);
}

void version()
{

    printf(" version 1.0.0");
}

#endif