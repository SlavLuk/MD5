#ifndef HELP_H

#define HELP_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void help()
{
    fprintf(stderr,
            "Usage: md5 [OPTION] <file>\n"
            "A procedure for running md5.\n\n"
            "./md5 <file location>\n\n"
            "Option:\n"
            "-h , -help        print this help message.\n"
            "-t , -test        run tests to check that the code is correct.\n"
            "-f , -file        print file full path.\n" // column indices?
            "-v ,              print version.\n"
            "If -n option is not given the algorithm runs until the end.\n\n" // until the end?
            "<file> may be any file to be hashed.\n");
    exit(0);
}

#endif