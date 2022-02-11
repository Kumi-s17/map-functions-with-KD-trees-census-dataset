#include"data.h"
#include"tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


//main program controls all the action
int main (int argc, char **argv){                     
	struct node *root = NULL;
	struct node *champion_node = malloc(sizeof(*champion_node));
	assert(champion_node);
	double query[2];
	int comp;
	double champion_distance;
	business_t *d;
	
    //open the input csv file
	FILE *fp = fopen(argv[1], "r");
	assert(fp);
	
	//skips header row of input csv file
	while (fgetc(fp) != '\n' && !feof(fp));
	
	//read in and insert data from input file into the 2D tree
	while ((d = get_next_data(fp))){
		root = insert_node(root, d, 0);    
	} 


	//open the output file if present and else create a new one with that name
	FILE *outfile = fopen(argv[2], "w");
	assert(outfile);
	                           

	/*while there is an input query, find and write to output file the closest 
	  business/businesses*/
    while(scanf("%lf%lf",&query[0], &query[1]) == 2){  
		comp = 0;
		champion_distance = INF;
		search_nearest(root, query, champion_node, &champion_distance, 
			                  &comp, 0);
    	output_map1(outfile, query, champion_node -> list);
		//print out the number of comparisons to stdout
		printf("%lf %lf --> %d\n", query[0], query[1], comp);
	}


	fclose(fp); 
	fclose(outfile); 

    free_tree(root);
	free(champion_node);
    
	return 0;     
}
