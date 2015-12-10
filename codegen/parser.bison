/* Parser for CMinor language */

/* Declare tokens here */
%token TOKEN_ARRAY
%token TOKEN_BOOLEAN
%token TOKEN_CHAR
%token TOKEN_ELSE
%token TOKEN_FALSE
%token TOKEN_FOR
%token TOKEN_FUNCTION
%token TOKEN_IF
%token TOKEN_INTEGER
%token TOKEN_PRINT
%token TOKEN_RETURN
%token TOKEN_STRING
%token TOKEN_TRUE
%token TOKEN_VOID
%token TOKEN_IDENT
%token TOKEN_STRING_LITERAL
%token TOKEN_INTEGER_LITERAL
%token TOKEN_CHAR_LITERAL
%token TOKEN_SEMICOLON
%token TOKEN_GE
%token TOKEN_LE
%token TOKEN_GT
%token TOKEN_LT
%token TOKEN_EQ
%token TOKEN_NE
%token TOKEN_POSTFIX_PLUS
%token TOKEN_POSTFIX_MINUS
%token TOKEN_EXPONENT
%token TOKEN_MULTIPLY
%token TOKEN_DIVIDE
%token TOKEN_MODULUS
%token TOKEN_PLUS
%token TOKEN_MINUS
%token TOKEN_LOGICAL_AND
%token TOKEN_LOGICAL_OR
%token TOKEN_LOGICAL_NOT
%token TOKEN_ASSIGNMENT
%token TOKEN_LPAREN
%token TOKEN_RPAREN
%token TOKEN_LBRACKET
%token TOKEN_RBRACKET
%token TOKEN_LCURLY
%token TOKEN_RCURLY
%token TOKEN_COMMA
%token TOKEN_COLON

/* Declare which types are generated by the bison file */
%union {
	struct decl *decl;
	struct param_list *param_list;
	struct stmt *stmt;
	struct expr *expr;
	struct type *type;
};

%type <decl> program decl_list decl
%type <type> type type_basic type_array type_function
%type <stmt> stmt stmt_list matched unmatched
%type <param_list> param_list non_empty_param_list param
%type <expr> opt_expr expr_block expr_block_list non_empty_expr_block_list expr_list non_empty_expr_list expr assignment_expr logical_or_expr logical_and_expr equality_expr comparison_expr add_expr mult_expr exponent factor pre_post_incr primary_expr integer string char ident non_empty_array_index array_index

%{
	#include <stdio.h>
	#include <math.h>
	#include "globl.h"

/* Include all of the prototypes for the structs */
	#include "decl.h"
	#include "stmt.h"
	#include "param_list.h"
	#include "expr.h"
	#include "type.h"

/* declare these for use in the parser */
	extern int yyerror( char *str );

/* initialize the global struct decl * variable for use in main */
	struct decl *AST = 0;

%}

%% /* Grammar rules and actions follow. */

program	: decl_list
		{ AST = $1; return 0; } 
	;

decl_list: decl decl_list
		{ $1->next = $2;
		  $$ = $1; }
	| /* nothing */
		{ $$ = 0; }
	;

decl	: ident TOKEN_COLON type TOKEN_SEMICOLON
		{ $$ = decl_create($1->name, $3, 0, 0); }
	| ident TOKEN_COLON type_basic TOKEN_ASSIGNMENT expr TOKEN_SEMICOLON
		{ $$ = decl_create($1->name, $3, $5, 0); }
	| ident TOKEN_COLON type_function TOKEN_ASSIGNMENT TOKEN_LCURLY stmt_list TOKEN_RCURLY
		{ $$ = decl_create($1->name, $3, 0, $6); }
	| ident TOKEN_COLON type_array TOKEN_ASSIGNMENT expr_block TOKEN_SEMICOLON
		{ $$ = decl_create($1->name, $3, $5, 0); }
	;

type	: type_basic
		{ $$ = $1; }
	| type_array
		{ $$ = $1; }
	| type_function
		{ $$ = $1; }
	;

type_basic : TOKEN_STRING
		{ $$ = type_create(TYPE_STRING, 0, 0, 0); }
	| TOKEN_INTEGER
		{ $$ = type_create(TYPE_INTEGER, 0, 0, 0); }
	| TOKEN_CHAR
		{ $$ = type_create(TYPE_CHARACTER, 0, 0, 0); }
	| TOKEN_BOOLEAN
		{ $$ = type_create(TYPE_BOOLEAN, 0, 0, 0); }
	| TOKEN_VOID
		{ $$ = type_create(TYPE_VOID, 0, 0, 0); }
	;
	
type_array : TOKEN_ARRAY TOKEN_LBRACKET integer TOKEN_RBRACKET type
		{ $$ = type_create(TYPE_ARRAY, 0, $5, $3->literal_value); }
	| TOKEN_ARRAY TOKEN_LBRACKET TOKEN_RBRACKET type
		{ $$ = type_create(TYPE_ARRAY, 0, $4, 0); }
	;

type_function : TOKEN_FUNCTION type TOKEN_LPAREN param_list TOKEN_RPAREN
		{ $$ = type_create(TYPE_FUNCTION, $4, $2, 0); }
	;

param_list : /* nothing */
		{ $$ = 0; }
	| non_empty_param_list
		{ $$ = $1; }
	;

non_empty_param_list : param 
		{ $$ = $1; }
	| param TOKEN_COMMA non_empty_param_list
		{ $1->next = $3;
		  $$ = $1; }
	;

param	: ident TOKEN_COLON type
		{ $$ = param_list_create($1->name, $3); }
	;

stmt_list : /* nothing */
		{ $$ = 0; }
	| stmt stmt_list
		{ $1->next = $2;
		  $$ = $1; }
	;

stmt	: matched
		{ $$ = $1; }
	| unmatched
		{ $$ = $1; }
	;

matched : decl
		{ $$ = stmt_create(STMT_DECL, $1, 0, 0, 0, 0, 0); }
	| TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN matched TOKEN_ELSE matched
		{ $$ = stmt_create(STMT_IF_ELSE, 0, 0, $3, 0, $5, $7); }
	| expr TOKEN_SEMICOLON
		{ $$ = stmt_create(STMT_EXPR, 0, 0, $1, 0, 0, 0); }
	| TOKEN_LCURLY stmt_list TOKEN_RCURLY
		{ $$ = stmt_create(STMT_BLOCK, 0, 0, 0, 0, $2, 0); }
	| TOKEN_RETURN opt_expr TOKEN_SEMICOLON
		{ $$ = stmt_create(STMT_RETURN, 0, 0, $2, 0, 0, 0); }
	| TOKEN_PRINT expr_list TOKEN_SEMICOLON
		{ $$ = stmt_create(STMT_PRINT, 0, 0, $2, 0, 0, 0); }
	| TOKEN_FOR TOKEN_LPAREN opt_expr TOKEN_SEMICOLON opt_expr TOKEN_SEMICOLON opt_expr TOKEN_RPAREN matched
		{ $$ = stmt_create(STMT_FOR, 0, $3, $5, $7, $9, 0); }
	;

unmatched : TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN stmt
		{ $$ = stmt_create(STMT_IF_ELSE, 0, 0, $3, 0, $5, 0); }
	| TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN matched TOKEN_ELSE unmatched
		{ $$ = stmt_create(STMT_IF_ELSE, 0, 0, $3, 0, $5, $7); }
	;

opt_expr : /* Nothing */ 
		{ $$ = 0; }
	| expr
		{ $$ = $1; }
	;

expr_block : TOKEN_LCURLY expr_block_list TOKEN_RCURLY 
		{ $$ = $2; }
	;

expr_block_list : /* Nothing */
		{ $$ = 0; }
	| non_empty_expr_block_list
		{ $$ = expr_create(EXPR_BLOCK, 0, $1); }
	;

non_empty_expr_block_list : expr
		{ $$ = $1; }
	| expr TOKEN_COMMA non_empty_expr_block_list
		{ $$ = expr_create(EXPR_BLOCK_COMMA, $1, $3); }
	;

expr_list : /* Nothing */
		{ $$ = 0; }
	| non_empty_expr_list
		{ $$ = $1; }
	;

non_empty_expr_list : expr
		{ $$ = $1; }
	| expr TOKEN_COMMA non_empty_expr_list
		{ $$ = expr_create(EXPR_COMMA, $1, $3); }
	;

expr	: assignment_expr
		{ $$ = $1; }
	;

assignment_expr : assignment_expr TOKEN_ASSIGNMENT logical_or_expr
		{ $$ = expr_create(EXPR_ASSIGNMENT, $1, $3); }
	| logical_or_expr
		{ $$ = $1; }
	;

logical_or_expr : logical_or_expr TOKEN_LOGICAL_OR logical_and_expr
		{ $$ = expr_create(EXPR_LOGICAL_OR, $1, $3); }
	| logical_and_expr
		{ $$ = $1; }
	;

logical_and_expr : logical_and_expr TOKEN_LOGICAL_AND equality_expr
		{ $$ = expr_create(EXPR_LOGICAL_AND, $1, $3); }
	| equality_expr
		{ $$ = $1; }
	;

equality_expr : equality_expr TOKEN_EQ comparison_expr
		{ $$ = expr_create(EXPR_EQ, $1, $3); }
	| equality_expr TOKEN_NE comparison_expr
		{ $$ = expr_create(EXPR_NE, $1, $3); }
	| comparison_expr
		{ $$ = $1; }
	;

comparison_expr : comparison_expr TOKEN_GE add_expr
		{ $$ = expr_create(EXPR_GE, $1, $3); }
	| comparison_expr TOKEN_LE add_expr
		{ $$ = expr_create(EXPR_LE, $1, $3); }
	| comparison_expr TOKEN_GT add_expr
		{ $$ = expr_create(EXPR_GT, $1, $3); }
	| comparison_expr TOKEN_LT add_expr
		{ $$ = expr_create(EXPR_LT, $1, $3); }
	| add_expr
		{ $$ = $1; }
	;

add_expr : add_expr TOKEN_PLUS mult_expr
		{ $$ = expr_create(EXPR_ADD, $1, $3); }
	| add_expr TOKEN_MINUS mult_expr
		{ $$ = expr_create(EXPR_SUB, $1, $3); }
	| mult_expr
		{ $$ = $1; }
	; 

mult_expr: mult_expr TOKEN_MULTIPLY exponent
		{ $$ = expr_create(EXPR_MUL, $1, $3); }
	| mult_expr TOKEN_DIVIDE exponent
		{ $$ = expr_create(EXPR_DIV, $1, $3); }
	| mult_expr TOKEN_MODULUS exponent
		{ $$ = expr_create(EXPR_MOD, $1, $3); }
	| exponent
		{ $$ = $1; }
	;

exponent : exponent TOKEN_EXPONENT factor
		{ $$ = expr_create(EXPR_POW, $1, $3); }
	| factor
		{ $$ = $1; }
	;

factor	: TOKEN_MINUS factor
		{ $$ = expr_create(EXPR_SUB, expr_create_int_value(0), $2); }
	| TOKEN_LOGICAL_NOT factor
		{ $$ = expr_create(EXPR_LOGICAL_NOT, 0, $2); }
	| pre_post_incr
		{ $$ = $1; }
	;

pre_post_incr : pre_post_incr TOKEN_POSTFIX_PLUS
		{ $$ = expr_create(EXPR_POSTFIX_PLUS, $1, 0); }
	| pre_post_incr TOKEN_POSTFIX_MINUS
		{ $$ = expr_create(EXPR_POSTFIX_MINUS, $1, 0); }
	| primary_expr
		{ $$ = $1; }
	;

primary_expr : ident
		{ $$ = $1; }
	| integer
		{ $$ = $1; }
	| string
		{ $$ = $1; }
	| char
		{ $$ = $1; }
	| TOKEN_TRUE
		{ $$ = expr_create_bool_value(1); }
	| TOKEN_FALSE
		{ $$ = expr_create_bool_value(0); }
	| TOKEN_LPAREN expr TOKEN_RPAREN
		{ $$ = expr_create(EXPR_PARENS, 0, $2); }
	| ident TOKEN_LPAREN expr_list TOKEN_RPAREN
		{ $$ = expr_create(EXPR_FCALL, $1, $3); }
	| ident non_empty_array_index
		{ $$ = expr_create(EXPR_ARRCALL, $1, $2); }
	;

non_empty_array_index : TOKEN_LBRACKET expr TOKEN_RBRACKET array_index
		{ $$ = expr_create(EXPR_ARRINDEX, $2, $4); }
	;

array_index : TOKEN_LBRACKET expr TOKEN_RBRACKET array_index
		{ $$ = expr_create(EXPR_ARRINDEX, $2, $4); }
	| /* nothing */
		{ $$ = 0; }
	;

ident	: TOKEN_IDENT
		{ char *c;
		  c = (char *)malloc(strlen(yytext)); 
		  strcpy(c, yytext);
		  $$ = expr_create_ident(c); }
	;

integer	: TOKEN_INTEGER_LITERAL
		{ int i = atof(yytext);
		  $$ = expr_create_int_value(i); }
	;

string 	: TOKEN_STRING_LITERAL
		{ char *c;
		  c = (char *)malloc(strlen(yytext)); 
		  strcpy(c, yytext+1);
		  int i;
		  for(i=0; c[i]!='\0'; i++);
		  c[i-1]='\0';
		  $$ = expr_create_string_value(c); }
	;

char	: TOKEN_CHAR_LITERAL
		{ char c = yytext[1]; 
		  char c2 = yytext[2];
		  if(c=='\\' && c2=='n'){
			c = '\n';
		  } else if(c=='\\' && c2=='0') {
			c = '\0';
		  } else if(c=='\\' && c2=='t') {
			c = '\t';
		  } else if(c=='\\' && c2) {
			c = yytext[2];
		  }
		  $$ = expr_create_char_value(c); }
	;

%%

int yyerror( char *str )
{
	printf("parse error: %s\n",str);
	return 1;
}
