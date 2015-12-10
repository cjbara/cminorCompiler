#include <stdio.h>
extern int yylex();
extern char * yytext;
extern FILE * yyin;
extern FILE * outfile;

extern int yyparse();
extern struct decl *AST;

extern struct hash_table_list *head;
extern int error_count;
extern int label_count;
extern int string_number;
