#include "expr.h"
#include <stdio.h>
#include <stdlib.h>

//create a new expression without a value
struct expr * expr_create(expr_t kind, struct expr *left, struct expr *right){
	struct expr *e;
	e = malloc(sizeof(*e));
	e->kind = kind;
	e->left = left;
	e->right = right;
	e->name = 0;
	e->symbol = 0;
	e->string_literal = 0;
	e->literal_value = 0;
	return e;
}

//create a new expression as an integer literal
struct expr * expr_create_int_value(int int_val){
	struct expr *e = expr_create(EXPR_INTEGER_LITERAL, 0, 0);
	e->literal_value = int_val;
	return e;
}

//create a new expression as a char literal
struct expr * expr_create_char_value(char char_val){
	struct expr *e = expr_create(EXPR_CHAR_LITERAL, 0, 0);
	e->literal_value = char_val;
	return e;
}

//create a new expression as a string literal
struct expr * expr_create_string_value(char *string_val){
	struct expr *e = expr_create(EXPR_STRING_LITERAL, 0, 0);
	e->string_literal = string_val;
	return e;
}

//create a new expression as an ident
struct expr * expr_create_ident(char *name){
	struct expr *e = expr_create(EXPR_IDENT, 0, 0);
	e->name = name;
	return e;
}

//recursively delete an expression tree
void expr_delete(struct expr *e){
	if(!e) return;
	expr_delete(e->left);
	expr_delete(e->right);
	free(e);
}

//recursively prints out an expression tree
void expr_print(struct expr *e){
	if(!e) return;
	if(e->kind == EXPR_PARENS) {
		printf("(");
		expr_print(e->right);
		printf(")");
	} else if(e->kind == EXPR_FCALL){
		expr_print(e->left);
		printf("(");
		expr_print(e->right);
		printf(")");
	} else if(e->kind == EXPR_ARRCALL){
		expr_print(e->left);
		expr_print(e->right);
	} else if(e->kind == EXPR_ARRINDEX){
		printf("[");
		expr_print(e->left);
		printf("]");
		expr_print(e->right);
	} else if(e->kind == EXPR_BLOCK){
		printf("{");
		expr_print(e->right);
		printf("}");
	} else { 
		if(e->left || e->right){
			//printf("(");
			expr_print(e->left);
			expr_pretty_print(e);
			expr_print(e->right);
			//printf(")");
		} else {
			expr_print(e->left);
			expr_pretty_print(e);
			expr_print(e->right);
		}
	}
}

void expr_pretty_print(struct expr *e){
	switch(e->kind){
		case EXPR_ASSIGNMENT: printf("="); break;
		case EXPR_GE: printf(">="); break;
		case EXPR_LE: printf("<="); break;
		case EXPR_GT: printf(">"); break;
		case EXPR_LT: printf("<"); break;
		case EXPR_EQ: printf("=="); break;
		case EXPR_NE: printf("!="); break;
		case EXPR_ADD: printf("+"); break;
		case EXPR_SUB: printf("-"); break;
		case EXPR_MUL: printf("*"); break;
		case EXPR_DIV: printf("/"); break;
		case EXPR_MOD: printf("%%"); break;
		case EXPR_POW: printf("^"); break;
		case EXPR_LOGICAL_NOT: printf("!"); break;
		case EXPR_LOGICAL_AND: printf("&&"); break;
		case EXPR_LOGICAL_OR: printf("||"); break;
		case EXPR_POSTFIX_PLUS: printf("++"); break;
		case EXPR_POSTFIX_MINUS: printf("--"); break;
		case EXPR_IDENT: printf("%s",e->name); break;
		case EXPR_INTEGER_LITERAL: printf("%d", e->literal_value); break;
		case EXPR_STRING_LITERAL: printf("\"%s\"", e->string_literal); break;
		case EXPR_CHAR_LITERAL: printf("\'%c\'", e->literal_value); break;
		case EXPR_TRUE: printf("true"); break;
		case EXPR_FALSE: printf("false"); break;
		case EXPR_COMMA: printf(", "); break;
	}
}
