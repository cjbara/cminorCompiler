#include "stmt.h"
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
