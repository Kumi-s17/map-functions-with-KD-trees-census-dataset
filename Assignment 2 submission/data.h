#ifndef DATA_H
#define DATA_H

#define C ','     
#define Q '\"'   
#define NL '\n' 

#define FIELD_LEN 128
#define NUMCOLUMS 11

#define CENSUS_YEAR 0
#define BLOCK_ID 1
#define PROPERTY_ID 2
#define BASE_PROPERTY_ID 3
#define SMALL_AREA 4
#define TRADING_NAME 5
#define INDUSTRY_CODE 6
#define INDUSTRY_DESCRIPTION 7
#define X_COORD 8
#define Y_COORD 9
#define LOCATION 10

#include <stdio.h>
#include "utils.h"

typedef struct business business_t;
struct business{
    char *data[NUMCOLUMS];
    business_t *next;
};

business_t *get_next_data(FILE *fp);
char *get_field(FILE *f, char deli);
void chop(char *s, char delim);
int scopy(char *t, char *s, char deli);
void print_data(FILE *outfile, business_t *business);
void free_data(business_t *business);

#endif