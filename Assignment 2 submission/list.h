#ifndef LISTH
#define LISTH

#include <stdio.h>
#include "data.h"

typedef struct list list_t;
struct list{
	business_t *head;
	business_t *foot; 
};                 

list_t *create_empty_list();
list_t *add_to_list(list_t *list, business_t *new_business);
void output_map1(FILE *outfile, double *query, list_t *list);
void output_map2(FILE *outfile, double *query, list_t *list, double radius);
void free_list(list_t *list);


#endif