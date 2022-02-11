//taken from https://github.com/anhvir/c203/blob/master/avo.zip

#ifndef _UTILS_H_
#define _UTILS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* my_OOO() is a safe version of OOO()
   which check the validity of the returned value of thess OOO() functions
*/

void *my_malloc(size_t n);
FILE *my_fopen(const char *fname, const char *mode);
char *my_strdup(char *);

#endif
