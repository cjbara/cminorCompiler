#include <stdio.h>
extern int yylex();
extern char * yytext;
extern FILE * yyin;

extern int yyparse();
extern struct decl *AST;

extern struct hash_table_list *head;
extern int error_count;
