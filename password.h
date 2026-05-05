#ifndef PASSWORD_H_INCLUED
#define PASSWORD_H_INCLUED

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int randchar(unsigned char *buf, int nbchar);
int randnum(unsigned char *buf, int nbchar);
int randalphabet(unsigned char *buf, int nbchar);
int randalphanum(unsigned char *buf, int nbchar);

# ifdef PASSWORD_IMPLEMENTATION

// Interesting ASCII char 33-126
// ASCII alphabet : 32-57(Maj) 64-89(Lower case)
// ASCII digit : 15-25

int randchar(unsigned char *buf, int nbchar)
{
    buf[nbchar] = '\0';
    unsigned char temp;
    for (int i = 0; i < nbchar; i++) {
	if (getentropy(&temp, sizeof(temp)) < 0) {
	    fprintf(stderr, "ERROR: getentropy:: %s\n", strerror(errno));
	    return -1;
	}
	else if ((unsigned)temp > 250) {
	    i--;
	    continue;
	}

	buf[i] = temp%93+33;
    }
    return 0;
}

int randnum(unsigned char *buf, int nbchar)
{
    buf[nbchar] = '\0';
    unsigned char temp;
    for (int i = 0; i < nbchar; i++) {
	if (getentropy(&temp, sizeof(temp)) < 0) {
	    fprintf(stderr, "ERROR: getentropy:: %s\n", strerror(errno));
	    return -1;
	}
	else if ((unsigned)temp > 185) {
	    i--;
	    continue;
	}

	buf[i] = temp%10+48;
    }
    
    return 0;
}

int randalphabet(unsigned char *buf, int nbchar)
{
    buf[nbchar] = '\0';
    unsigned char temp;

    for (int i = 0; i < nbchar; i++) {
	if (getentropy(&temp, sizeof(temp)) < 0) {
	    fprintf(stderr, "ERROR: getentropy:: %s\n", strerror(errno));
	    return -1;
	}
	else if (temp > 234) {
	    i--;
	    continue;
	}
	unsigned cut = (temp > 117); // Not 50/50 because if temp == 117

	if (cut) buf[i] = temp%26+97; // Lower cases
	else     buf[i] = temp%26+65; // Upper cases
    }

    return 0;
}

int randalphanum(unsigned char *buf, int nbchar)
{

    char tab[122*2];
    tab[122*2] = '\0';
    unsigned t = 0;
    for (unsigned i = 0; i < 0xff+1; i++) {
	if ((i > 47 && i < 58) || (i > 64 && i < 91) || (i > 96 && i < 123))
	    tab[t++] = i;
    }
    for (unsigned i = t; i < 4*t; i++) {
	tab[i] = tab[i-t];
    }

    buf[nbchar] = '\0';
    unsigned char temp;
    
    for (int i = 0; i < nbchar; i++) {
	if (getentropy(&temp, sizeof(temp)) < 0) {
	    fprintf(stderr, "ERROR: getentropy:: %s\n", strerror(errno));
	    return -1;
	}
	else if ((unsigned)temp > 4*t-1) {
	    i--;
	    continue;
	}

	buf[i] = tab[(unsigned)temp];
    }

    return 0;
}


# endif // PASSWORDLIB_IMPLEMENTATION

#endif // PASSWORD_H_INCLUED
