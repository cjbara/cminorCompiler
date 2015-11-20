#include "globl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse();
int ast_print();
int resolve();
int typecheck();

int main(int argc, char *argv[]){
  char* filename;
  if(argc == 3 && strcmp(argv[1], "-print") == 0){
	filename = argv[2];
	/* open the file for reading */
	yyin = fopen(filename, "r");

	/* parse the file */
	return ast_print(); // return code associated with the parse
  } else if(argc == 3 && strcmp(argv[1], "-resolve") == 0){
	filename = argv[2];
	/* open the file for reading */
	yyin = fopen(filename, "r");

	/* resolve the names in the AST */
	return resolve();
  } else if(argc == 3 && strcmp(argv[1], "-typecheck") == 0){
	filename = argv[2];
	/* open the file for reading */
	yyin = fopen(filename, "r");

	/* Check the types in the AST */
	return typecheck();
  } else {
	return 2;
  }
}

//This function resolves the names and builds the symbol table
int resolve(){
	if(parse()){
		return 1;
	}
	init_globals();
	decl_resolve(AST);
	delete_globals();

	if(error_count){
		printf("total name resolution errors: %d\n", error_count);
		return 1;
	} else {
		printf("no name resolution errors\n");
		return 0;
	}
}

//This function checks types in the AST using the symbol table
int typecheck(){
	int test = resolve();
	if(test) return test;
	decl_typecheck(AST); 
	if(error_count){
		printf("total type errors: %d\n", error_count);
		return 1;
	} else {
		printf("no type errors\n");
		return 0;
	}
}

//This function parses an already scanned file
int parse(){
    if(yyparse()==0) {
	return 0;
    } else {
	return 1;
    }
}

//Prints out the AST after parsing it
int ast_print(){
	if(!parse()){
		decl_print(AST, 0);
		return 0;
	} else {
		return 1;
	}
}
