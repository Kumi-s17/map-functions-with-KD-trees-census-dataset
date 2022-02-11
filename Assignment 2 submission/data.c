#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "data.h"

//insert and returns a business node with its fields filled
//adapted from https://github.com/anhvir/c203/blob/master/avo.zip
business_t *get_next_data(FILE *fp){
	char *s = get_field(fp, C);
	//if EOF
	if(!s){
		return NULL;
	}
	business_t *new_business = malloc (sizeof(*new_business));
    assert(new_business);

    new_business -> data[CENSUS_YEAR] = s;
    new_business -> data[BLOCK_ID] = get_field(fp, C);
	new_business -> data[PROPERTY_ID] = get_field(fp, C);
	new_business -> data[BASE_PROPERTY_ID] = get_field(fp, C);
	new_business -> data[SMALL_AREA] = get_field(fp, C);
	new_business -> data[TRADING_NAME] = get_field(fp, C);
	new_business -> data[INDUSTRY_CODE] = get_field(fp, C);
	new_business -> data[INDUSTRY_DESCRIPTION] = get_field(fp, C);
	new_business -> data[X_COORD] = get_field(fp, C);
	new_business -> data[Y_COORD] = get_field(fp, C);

	//To localize reading errors, read until \n here
	new_business -> data[LOCATION] = get_field(fp, NL);
	new_business -> next = NULL;

	return new_business;
}

// get & return next csv field, which might or might not start with "
//    the field deds withj "deli", which can be  a comma or a newline
//taken from https://github.com/anhvir/c203/blob/master/avo.zip
char *get_field(FILE *f, char deli) {
	char *s = NULL;
	size_t l = 0;

	// get first component of the field
	//if EOF
    if (getdelim(&s, &l, deli, f) <=0) { 
		if (s) free(s);
		return NULL;
	}  

	// simple return for field not starting with "
	if (*s != Q) {  
		chop(s, deli);
		return s;
	}
	// buffer, +3 for possible \r \n \0
	char line[FIELD_LEN + 3]; 
	// add first component to buffer, skipping "
	int cont= scopy(line, s+1, deli);  

	// if not yet finish the quote, continue
	while (cont) {  
		// p= the end of buffer "line"
		char *p= line+strlen(line);  
		// gets a new csv component to s  
		getdelim(&s, &l, deli, f);   
		// and appends its to the end of "line"
		cont= scopy(p, s, deli);       
	}
    free(s);
	 // returns a dynamic copy of buffer "line"
	return my_strdup(line);            
}	



// chop the last characters of s if they are delim or \n \r ...	
//taken from https://github.com/anhvir/c203/blob/master/avo.zip
void chop(char *s, char delim) {
	int l = strlen(s)- 1;
	// first: chop \n or \r or any invisible characters (Windows problem!) 
	for (; l>=0 && isspace(s[l]) ; l--) s[l]= '\0';
    // then, chop the delim itself
	if (s[l]==delim) s[l]= '\0';
}

// copying s to t, while reducing pair "" to a single "
//     return 0 if s contains final "  (ie. s is the last component of a field)
//            1 otherwise (ie. s not yet finished)
//taken from https://github.com/anhvir/c203/blob/master/avo.zip
int scopy(char *t, char *s, char deli) {
	char *p= t, *q= s;
	char prev=' ';
	while (*q) {
		// if single " followed by a non-quote
		if (*q==Q && prev!=Q && (*(q+1)!=Q) ) {  
			*p= '\0'; 
			// then it's the end of field
			return 0;                            
		}
		// if a quote follows a previous quote
		if (*q==Q && prev==Q) {                  
			prev= ' ';
			// do not copy this quote
			q++;                                 
			continue;
		}
		// set prev
		prev= *q;   
		// and copy current char of s to t                             
		*p++= *q++;                              
	}
	*p= '\0';
    return 1;
}


//outputs the data of a business in the list to the output file
 void print_data(FILE *outfile, business_t *business){
	 fprintf(outfile, " Census year: %s || ", business -> data[CENSUS_YEAR]);
	 fprintf(outfile, "Block ID: %s || ", business -> data[BLOCK_ID]);

	 fprintf(outfile, "Property ID: %s || ", business -> data[PROPERTY_ID]);
	 fprintf(outfile, "Base property ID: %s || ", 
	 	 business -> data[BASE_PROPERTY_ID]);

	 fprintf(outfile, "CLUE small area: %s || ", business -> data[SMALL_AREA]);
	 fprintf(outfile, "Trading Name: %s || ", business -> data[TRADING_NAME]);

	 fprintf(outfile, "Industry (ANZSIC4) code: %s || ", 
	 	 business -> data[INDUSTRY_CODE]);
	 fprintf(outfile, "Industry (ANZSIC4) description: %s || ", 
	 	 business -> data[INDUSTRY_DESCRIPTION]); 

	 fprintf(outfile, "x coordinate: %s || ", business -> data[X_COORD]);
	 fprintf(outfile, "y coordinate: %s || ", business -> data[Y_COORD]);  
	 fprintf(outfile, "Location: %s || ", business -> data[LOCATION]);
	 fprintf(outfile, "\n");                
}


//free the data stored in the linked list
void free_data(business_t *business){
	free(business -> data[CENSUS_YEAR]);
	free(business -> data[BLOCK_ID]);
	free(business -> data[PROPERTY_ID]);
	free(business -> data[BASE_PROPERTY_ID]);
	free(business -> data[SMALL_AREA]);
	free(business -> data[TRADING_NAME]);
	free(business -> data[INDUSTRY_CODE]);
	free(business -> data[INDUSTRY_DESCRIPTION]);
	free(business -> data[X_COORD]);
	free(business -> data[Y_COORD]);
	free(business -> data[LOCATION]);
	
}

