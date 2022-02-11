#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

//create a new list
list_t *create_empty_list(){
	list_t *list;
	list = malloc(sizeof(*list));
	assert(list);
	list -> head = list -> foot = NULL;
	return list;
}                                                              
                           
//add a new business node to the list
list_t *add_to_list(list_t *list, business_t *new_business){
	//if it is the first element to be inserted into the list
	if(list -> head == NULL){
		list -> head = list -> foot = new_business;
	}
	else{
		list -> foot -> next = new_business;
		list -> foot = new_business;
	}
	
	return list;
	
}


/*output to outfile the details of businesses at the nearest point to the 
  query point*/
void output_map1(FILE *outfile, double *query, list_t *list){
	business_t *ptr = list->head;
	while(ptr){
		fprintf(outfile, "%lf %lf -->", query[0], query[1]);
		//prints out the data of the businesses
		print_data(outfile, ptr);
		ptr = ptr->next;                       
	}
}

/*output to output file the details of all the points within the input radius 
  of the query point*/
void output_map2(FILE *outfile, double *query, list_t *list, double radius){
	business_t *ptr = list->head;
	while(ptr){
		fprintf(outfile, "%lf %lf %lf -->", query[0], query[1], radius);
		//prints out the data of the businesses
		print_data(outfile, ptr);
		ptr = ptr->next;
	}
 }      



//frees the list
void free_list(list_t *list){
	business_t *current, *prev;
	assert(list);
	current = list -> head;
	while(current != NULL){
		prev = current;
		current = current -> next;
		//free the data associated to the list
		free_data(prev);
		free(prev);
	}
	free(list);	
} 

