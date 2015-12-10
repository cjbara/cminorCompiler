#include "globl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse();
int ast_print();
int resolve();
int typecheck();
int codegen(char *inputfile, char *outputfile);
FILE * outfile;

int main(int argc, char *argv[]){
	char *filename;
	char *outputfile;
	if(argc == 4 && strcmp(argv[1], "-codegen") == 0){
		filename = argv[2];
		outputfile = argv[3];
		/* open the file for reading */
		yyin = fopen(filename, "r");
		outfile = fopen(outputfile, "w");

		/* generate the code for the file */
		return codegen(filename, outputfile); // return code associated with the generation
	} else if(argc == 3 && strcmp(argv[1], "-codegen") == 0) {
		printf("error: you must supply both an input file and an output file\n");
		return 2;
	} else {
		printf("error: you must use the flag '-codegen' and supply two file names\n");
		return 2;
	}
}

//This function resolves the names and builds the symbol table
int resolve(){
	init_globals();
	decl_resolve(AST);
	delete_globals();

	if(error_count){
		printf("Total name resolution errors: %d\n\n", error_count);
		return 1;
	} else {
		printf("No name resolution errors found.\n");
		return 0;
	}
}

//This function checks types in the AST using the symbol table
int typecheck(){
	decl_typecheck(AST);
	if(error_count){
		printf("Total type errors: %d\n\n", error_count);
		return 1;
	} else {
		printf("No type errors found.\n");
		return 0;
	}
}

//generate the assembly code
int codegen(char *inputfile, char *outputfile) {
	printf("\nCompiling %s\n", inputfile);
	printf("\n***** Parsing *****\n");
	if(yyparse()) return 1; //bad parse
	printf("\nNo parse errors found.\n");
	printf("\n***** Abstract Syntax Tree *****\n\n");
	decl_print(AST, 0);
	printf("\n***** Resolving Symbols *****\n\n");
	if(resolve()) return 1;
	printf("\n***** Type Checking *****\n\n");
	if(typecheck()) return 1;
	printf("\n***** Generating Code *****\n\n");
	decl_codegen(AST, outfile);
	printf("Successfully generated code in file: '%s'\n\n", outputfile);
	fclose(outfile);
	return 0;
}
