#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define PASSWORD_IMPLEMENTATION
#include "password.h"

#define MAXPASSSIZE 5

void printpw(int pwsize, char opt)
{
    unsigned char pssw[pwsize];
    switch (opt) {
    case 'c': if (randchar(pssw, pwsize) < 0) exit(1); break;
    case 'd': if (randnum(pssw, pwsize) < 0) exit(1); break;
    case 'a': if (randalphabet(pssw, pwsize) < 0) exit(1); break;
    case 'n': if (randalphanum(pssw, pwsize) < 0) exit(1); break;
    }
    printf("%s\n", pssw);
}

void checkpwsize(int *pwsize)
{
    *pwsize = atoi(optarg);
    if (*pwsize <= 0) {
	fprintf(stderr, "ERROR: Argument password size <= 0\n");
	exit(1);
    }
}

int main(int argc, char **argv)
{
    int opt = 0;
    int PWsize;
    const char *Usage = "[-c char [int]] [-d digit [int]] [-a alphabet [int]] [-n alphanumeric [int]]";
    while ((opt = getopt(argc, argv, "c:d:a:n:h")) != -1) {
	switch (opt) {
	case 'c':
	    checkpwsize(&PWsize);
	    printpw(PWsize, 'c');
	    return 0;

	case 'd':
	    checkpwsize(&PWsize);
	    printpw(PWsize, 'd');
	    return 0;

	case 'a':
	    checkpwsize(&PWsize);
	    printpw(PWsize, 'a');
	    return 0;

	case 'n':
	    checkpwsize(&PWsize);
	    printpw(PWsize, 'n');
	    return 0;

	case 'h':
	    fprintf(stdout, "INFO: Usage: %s\n", Usage);
	    return 0;


	    default: /* '?' */
	    fprintf(stderr, "ERROR: Invalid usage: %s\n", Usage);
	    return 1;
	}
    }
    fprintf(stderr, "ERROR: Invalid usage: %s\n", Usage);
    return 2;
}
