#include "token.h"
#include "globl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int scan();

int main(int argc, char *argv[]){
  char* filename;
  char output[512];
  if(argc == 3 && strcmp(argv[1], "-scan") == 0){
	filename = argv[2];
	/* open the file for reading */
	yyin = fopen(filename, "r");

	/* Scan the file */
	return scan();
  } else {
	return 2;
  }
}

//This function scans a file
int scan(){
  	char output[512];

	/* Declare the token variable */
	token_t token;

	/* For each token, scan it */
	token = yylex();
	while(token){
	  //prints out an integer literal
	  if(token == TOKEN_INTEGER_LITERAL){
	    printf("%s %s\n", token_string(token), yytext);
	  //This else statement prints out a string or char literal
	  } else if(token == TOKEN_STRING_LITERAL || token == TOKEN_CHAR_LITERAL){
	      int i;
	      int offset = 1;
              for(i = 1; i < strlen(yytext) - 1; i++){
		if(yytext[i] == '\\'){
		  offset++;
		  i++;
		  if(yytext[i] == 'n'){
		    output[i-offset] = '\n';
		  } else if(yytext[i] == '0'){
		    output[i-offset] = '\0';
		  } else {
		    output[i-offset] = yytext[i];
		  }
		} else {
		  output[i-offset] = yytext[i];
		}
		if(i-offset >= 255){
		  fprintf(stderr,"error: string cannot exceed 255 characters\n");
		  return 1;
		}
	      }
	      output[i-offset] = '\0';
	      printf("%s %s\n", token_string(token), output);
	  //This else prints out an error message if there is a bad scan
	  } else if(token == TOKEN_ERROR){
	    error();
	    return 1;
	  //This prints out the other categories of tokens
	  } else {
	    printf("%s\n", token_string(token));
	  }
	  token = yylex();
	}
	//scan completed, successfully, return 0
	return 0;
}
