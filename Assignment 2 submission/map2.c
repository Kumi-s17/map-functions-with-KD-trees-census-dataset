#include"data.h"
#include"tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//main program controls all the action
int main (int argc, char **argv){                     
	struct node *root = NULL;
	double query[2];
	double radius;
	int comp, num_nodes;
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

	//open the output file if present and else create new file
	FILE *outfile = fopen(argv[2], "w");
	assert(outfile);

    /*while there is an input query, write to output file the businesses found 
      within the radius of the query point*/
    while(scanf("%lf%lf%lf",&query[0], &query[1], &radius) == 3){  
		comp = 0;
		//number of locations of businesses found within the radius
		num_nodes = 0;
		search_radius(outfile, root, query, radius, &comp, &num_nodes, 0);
		//output to stdout
		printf("%lf %lf %lf --> %d\n", query[0], query[1], radius, comp);
		//If there are no locations with businesses within the radius
		if(num_nodes == 0){
			fprintf(outfile, "%lf %lf %lf --> NOTFOUND\n", query[0], query[1], 
				            radius);
		}
		
	}

    fclose(fp);   
    fclose(outfile); 

    free_tree(root);
    
	return 0;     
}
