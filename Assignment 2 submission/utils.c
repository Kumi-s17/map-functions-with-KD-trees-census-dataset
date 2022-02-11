#include "utils.h"

//taken from https://github.com/anhvir/c203/blob/master/avo.zip
void *my_malloc(size_t n){
	assert(n>0);
	void *p= malloc(n);
	assert(p);
	return p;
} 

//taken from https://github.com/anhvir/c203/blob/master/avo.zip
FILE *my_fopen(const char *fname, const char *mode) {
	FILE *f= fopen(fname, mode);
	assert(f);
	return f;
}

//taken from https://github.com/anhvir/c203/blob/master/avo.zip
char *my_strdup(char *s) {
	char *t= strdup(s);
	assert(t);
	return t;
}
