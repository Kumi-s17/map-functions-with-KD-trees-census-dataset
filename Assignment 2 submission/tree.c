#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "tree.h"


//creates and adds a new node in the 2D tree
node_t *create_node(business_t *new_business){
	node_t *new_node;
	new_node = malloc(sizeof(*new_node));
	assert(new_node);
	new_node -> key[0] = atof(new_business -> data[X_COORD]);
	new_node -> key[1] = atof(new_business -> data[Y_COORD]);
	new_node -> list = create_empty_list();
	new_node -> list = add_to_list(new_node -> list, new_business);
	new_node -> left = new_node -> right = NULL;
	return new_node;
}  
                           
/*inserts the information about the business in the correct place, inserting 
  a new node if necessary*/
node_t *insert_node(node_t *root, business_t *new_business, int d){
	//if the key appears nowhere else in the tree 
	if(root == NULL){
		root = create_node(new_business);
	}
	//if both the x and y keys of the data is the same as the node
	else if(fabs(atof(new_business -> data[X_COORD]) - (root->key[0])) < EPS 
		&& fabs(atof(new_business -> data[Y_COORD]) - root->key[1]) < EPS){
		root->list = add_to_list(root->list, new_business);
	}
	/*if the data's key that is compared is less than that of the node insert 
	to the left*/ 
	else if(atof(new_business -> data[X_COORD + d]) < (root->key[d])){
		root->left = insert_node(root->left, new_business, 1-d);
	}
	/*if the data's key that is compared is greater than or equal 
	(but the other key is not the same) to that of the node insert to the 
	right*/
    else{
		root->right = insert_node(root->right, new_business, 1-d);
    }
	
	return root;	
}


//returns the node in the 2D tree that is nearest to the query point
double search_nearest(node_t *root, double *query, struct node *champion_node, 
	                         double *champion_distance, int *comp, int d){
	if (root != NULL){
		//increment number of comparisons when a node is visited
		*comp += 1;
		//checks if there is a better champion distance
		if(get_distance(query, root->key) < *champion_distance){
			*champion_distance = get_distance(query, root->key);
			*champion_node = *root;
		}
		
		//If the query point is exactly the same as the node, stop the search.
		if (fabs(query[0] - (root->key[0])) < EPS 
			         && fabs(query[1] - (root->key[1])) < EPS){
			return *champion_distance;
		}
		/*If the element of the query is less than that of the key, search on 
		  the left of the tree*/
		else if(query[d] < root->key[d]){
			*champion_distance = search_nearest(root->left, query, 
				            champion_node, champion_distance, comp, 1-d);
			//check if we need to also check the right hand side
			if(fabs(query[d] - (root->key[d])) < *champion_distance){
				*champion_distance = search_nearest(root->right, query, 
					             champion_node, champion_distance, comp, 1-d);
			}
		}
		/*If the element of the query is more than or equal that of the key 
		 (but the other key is not the same), search on the right of the tree*/
		else{
			*champion_distance = search_nearest(root->right, query, 
				               champion_node, champion_distance, comp, 1-d);
			//check if we need to also check the left hand side
			if(fabs(query[d] - (root->key[d])) < *champion_distance){
				*champion_distance = search_nearest(root->left, query, 
					              champion_node, champion_distance, comp, 1-d);
			}
		}
	}
	return *champion_distance;
}


/*copies to output file the businesses at the locations within the radius 
  of the query point*/
int search_radius(FILE *outfile, node_t *root, double *query, 
	                         double radius, int *comp, int *num_nodes, int d){
	if (root != NULL){
		//increment number of comparisons when a node is visited
		*comp += 1;
		//Checks if the node is within the radius of the query point.
		if(get_distance(query, root->key) <= radius){
			output_map2(outfile, query, root -> list, radius);
			*num_nodes += 1;
		}

		/*If the element of the query is less than that of the key, search on 
		  the left of the tree*/
		if(query[d] < root->key[d]){
			*num_nodes = search_radius(outfile, root->left, query, 
				                                radius, comp, num_nodes, 1-d);
			//check if we need to check the right hand side
			if(fabs(query[0] - (root->key[0])) < radius || 
				                    fabs(query[1] - (root->key[1])) < radius){
				*num_nodes = search_radius(outfile, root->right, query, 
					                             radius, comp, num_nodes, 1-d);
			}
		}
		/*If the element of the query is more than or equal that of the key 
		 (but the other key is not the same), search on the right of the tree*/
		else{
			*num_nodes = search_radius(outfile, root->right, query, radius, 
				                                        comp, num_nodes, 1-d);
			//check if we need to check the left hand side
			if(fabs(query[0] - (root->key[0])) < radius || 
				                     fabs(query[1] - (root->key[1])) < radius){
				*num_nodes = search_radius(outfile, root->left, 
					                      query, radius, comp, num_nodes, 1-d);
			}
		}
	}
	return *num_nodes;
}

//return the distance between two points
double get_distance(double *query, double *key){
	double diff_x = query[0] - key[0];
	double diff_y = query[1] - key[1];
	return sqrt(pow(diff_x, 2)+ pow(diff_y, 2));
}


//frees the 2D tree
void free_tree(node_t *root){
	if(root){
		free_tree(root->left);
		free_tree(root->right);
		//free the list associated with the node of the tree
		free_list(root->list);
		free(root);	
	}
} 



   
