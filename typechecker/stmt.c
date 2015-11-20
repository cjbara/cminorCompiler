#include "stmt.h"
#include "type.h"
#include "expr.h"
#include "symbol.h"
#include "globl.h"
#include <stdio.h>
#include <stdlib.h>

struct stmt * stmt_create(stmt_kind_t kind, struct decl *decl, struct expr *init_expr, struct expr *expr, struct expr *next_expr, struct stmt *body, struct stmt *else_body){
	struct stmt * s;
	s = malloc(sizeof(*s));
	
	s->kind = kind;
	s->decl = decl;
	s->init_expr = init_expr;
	s->expr = expr;
	s->next_expr = next_expr;
	s->body = body;
	s->else_body = else_body;

	return s;
}

//deletes a statement and all of its pointers
void stmt_delete(struct stmt *s){
	if(!s) return;
	decl_delete(s->decl);
	expr_delete(s->init_expr);
	expr_delete(s->expr);
	expr_delete(s->next_expr);
	stmt_delete(s->body);
	stmt_delete(s->else_body);

	free(s);
}

//resolves the names of statements
void stmt_resolve(struct stmt *s){
	if(!s) return;
	switch(s->kind) {
		case STMT_DECL: 
			decl_resolve(s->decl); 
			break;
		case STMT_EXPR: 
			expr_resolve(s->expr); 
			break;
		case STMT_IF_ELSE: 
			expr_resolve(s->expr); 
			stmt_resolve(s->body);
			stmt_resolve(s->else_body);
			break;
		case STMT_FOR: 
			expr_resolve(s->init_expr);
			expr_resolve(s->expr);
			expr_resolve(s->next_expr);
			stmt_resolve(s->body);
			break;
		case STMT_PRINT: 
			expr_resolve(s->expr);
			break;
		case STMT_RETURN: 
			expr_resolve(s->expr);
			break;
		case STMT_BLOCK: 
			scope_enter();
			stmt_resolve(s->body);
			scope_leave();
			break;
	}
	stmt_resolve(s->next);
}

void stmt_typecheck(struct stmt *s, struct symbol *current_function) {
	if(!s) return;
	struct type *T;
	switch(s->kind){
		case STMT_DECL:
			decl_typecheck(s->decl);
			break;
		case STMT_EXPR:
			expr_typecheck(s->expr);
			break;
		case STMT_IF_ELSE:
			T = expr_typecheck(s->expr);
			if(T->kind != TYPE_BOOLEAN){
				printf("type error: you must have a boolean expression as condition of an if statement. Condition is currently: ");
				type_print(T);
				expr_print(s->expr);
				printf("\n");
				error_count++;
			}
			stmt_typecheck(s->body, current_function);
			stmt_typecheck(s->else_body, current_function);
			break;
		case STMT_FOR:
			expr_typecheck(s->init_expr); //we don't care what these are
			expr_typecheck(s->next_expr); //we only care about the internally consistency of these two, make sure they pass expr_typechecks 
			T = expr_typecheck(s->expr);
			if(T->kind != TYPE_BOOLEAN && T->kind != TYPE_VOID) {
				printf("type error: middle condtion of a for loop must be boolean or void. Condtion is currently: ");
				type_print(T);
				expr_print(s->expr);
				printf("\n");
				error_count++;
			}
			stmt_typecheck(s->body, current_function);
			break;
		case STMT_PRINT:
			expr_typecheck(s->expr);
			break;
		case STMT_RETURN:
			T = expr_typecheck(s->expr);
			if(!type_compare(T, current_function->type->subtype)){
				printf("type error: in function %s, expected return type ", current_function->name);
				type_print(current_function->type->subtype);
				printf(", but return expression ");
				expr_print(s->expr);
				printf(" is of type ");
				type_print(T);
				printf("\n");
				error_count++;
			}
			break;
		case STMT_BLOCK:
			stmt_typecheck(s->body, current_function);
			break;
	}
	stmt_typecheck(s->next, current_function);
}

//prints everything in a statement
void stmt_print(struct stmt *s, int indent){
	if(!s) return;
	int i = 0;
	switch(s->kind){
		case STMT_DECL: 
			decl_print(s->decl, indent); 
			break;
		case STMT_EXPR: 
			for(i=0; i<indent; i++) printf("\t");
			expr_print(s->expr); 
			printf(";\n");
			break;
		case STMT_IF_ELSE: 
			for(i=0; i<indent; i++) printf("\t");
			printf("if ("); 
			expr_print(s->expr);
			printf(") \n");
			stmt_print(s->body, indent);
			if(s->else_body){
				printf("else ");
				stmt_print(s->else_body, indent);
			} else { printf("\n"); }
			break;
		case STMT_FOR: 
			for(i=0; i<indent; i++) printf("\t");
			printf("for ("); 
			expr_print(s->init_expr); 
			printf("; ");
			expr_print(s->expr); 
			printf("; ");
			expr_print(s->next_expr); 
			printf(") ");
			stmt_print(s->body, indent);
			printf("\n");
			break;
		case STMT_PRINT: 
			for(i=0; i<indent; i++) printf("\t");
			printf("print "); 
			expr_print(s->expr);
			printf(";\n"); 
			break;
		case STMT_RETURN:
			for(i=0; i<indent; i++) printf("\t");
			printf("return "); 
			expr_print(s->expr);
			printf(";\n"); 
			break;
		case STMT_BLOCK: 
			printf("{\n");
			stmt_print(s->body, indent+1);
			printf("\n");
			for(i=0; i<indent; i++) printf("\t");
			printf("} ");
			break;
	}
	stmt_print(s->next, indent);
}
