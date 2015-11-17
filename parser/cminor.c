#include "token.h"
#include "globl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse();

int main(int argc, char *argv[]){
  char* filename;
  if(argc == 3 && strcmp(argv[1], "-parse") == 0){
	filename = argv[2];
	/* open the file for reading */
	yyin = fopen(filename, "r");

	/* parse the file */
	return parse(); // return code associated with the parse
	  
  } else {
	return 2;
  }
}

//This function parses an already scanned file
int parse(){
    if(yyparse()==0) {
    	printf("parse successful!\n");
	decl_print(parse_result, 0);
	return 0;
    } else {
	printf("parse failed!\n");
	return 1;
    }
    free(parse_result);
}
