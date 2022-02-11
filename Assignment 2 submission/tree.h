#ifndef TREEH
#define TREEH

#define EPS 1e-9
#define INF 1e+9

#include <stdio.h>
#include "list.h"

typedef struct node node_t;
struct node{
    double key[2];
    list_t *list;  
    node_t *left;
    node_t *right;
};
              
node_t *create_node(business_t *new_business);
node_t *insert_node(node_t *root, business_t *new_business, int d);
double search_nearest(node_t *root, double *query, struct node *champion_node, 
	                      double *champion_distance, int *comp, int d);
int search_radius(FILE *outfile, node_t *root, double *query, 
	                      double radius, int *comp, int *num_nodes, int d);
double get_distance(double *query, double *key);
void free_tree(node_t *root);

#endif
