#include <stdio.h>
extern int yylex();
extern char * yytext;
extern FILE * yyin;

extern int yyparse();
extern struct decl *parse_result;

