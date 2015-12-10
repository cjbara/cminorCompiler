#include "stmt.h"
#include "type.h"
#include "expr.h"
#include "decl.h"
#include "globl.h"
#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>

int label_count = 0;

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
				for(i=0; i<indent; i++) printf("\t");
				printf("else");
				for(i=0; i<indent; i++) printf("\t");
				printf("\n");
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
			printf(")\n");
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
			if(s->expr){
				for(i=0; i<indent; i++) printf("\t");
				printf("return "); 
				expr_print(s->expr);
				printf(";\n"); 
			}
			break;
		case STMT_BLOCK: 
			for(i=0; i<indent; i++) printf("\t");
			printf("{\n");
			stmt_print(s->body, indent+1);
			for(i=0; i<indent; i++) printf("\t");
			printf("}\n");
			break;
	}
	stmt_print(s->next, indent);
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
			scope_enter(0);
			stmt_resolve(s->body);
			scope_leave();
			break;
	}
	stmt_resolve(s->next);
}

int stmt_function_locals(struct stmt *s) {
	if(!s) return 0;
	//calculates the number of local variables declared in for loops and if statements
	switch(s->kind) {
		case STMT_DECL: return 1;
		case STMT_EXPR: return 0;
		case STMT_IF_ELSE: return stmt_function_locals(s->body) + stmt_function_locals(s->else_body);
		case STMT_FOR: return stmt_function_locals(s->body);
		case STMT_PRINT: return 0;
		case STMT_RETURN: return 0;
		case STMT_BLOCK: return stmt_function_locals(s->body);
	}
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
				printf(" ");
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
				printf(" ");
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

void stmt_codegen(struct stmt *s, FILE *file) {
	if(!s) return;
	struct type *t;
	struct expr *e = s->expr;
	switch(s->kind) {
		case STMT_DECL:
			decl_codegen(s->decl, file);
			break;
		case STMT_BLOCK:
			//Have to account for different scopes, other variables are fine, but 
			stmt_codegen(s->body, file);
			break;
		case STMT_EXPR:
			expr_codegen(s->expr, file);
			register_free(s->expr->reg);
			break;
		case STMT_RETURN:
			expr_codegen(s->expr, file);
			fprintf(file, "\n\t#Return value\n");
			fprintf(file, "\tMOV %s, %%rax\n", register_name(s->expr->reg));
			postamble(file);
			break;
		case STMT_IF_ELSE:
			fprintf(file, "\n\t#If statement\n");
			expr_codegen(s->expr, file);
			//do the comparison
			fprintf(file, "\tCMP $0, %s\n", register_name(s->expr->reg));
			register_free(s->expr->reg);
			//jump to the right label
			int else_label = label_count++;
			int end_label = label_count++;
			fprintf(file, "\tJE L%d\n", else_label);
			stmt_codegen(s->body, file);
			fprintf(file, "\tJMP L%d\n", end_label);
			fprintf(file, "L%d:\n", else_label);
			stmt_codegen(s->else_body, file);
			fprintf(file, "L%d:\n", end_label);
			break;
		case STMT_FOR:
			fprintf(file, "\n\t#For loop\n");
			int loop_start = label_count++;
			int loop_end = label_count++;
			if(s->init_expr){
				//initial expression
				expr_codegen(s->init_expr, file);
				register_free(s->init_expr->reg);
			}
			//label 1: top of loop
			fprintf(file, "L%d:\n", loop_start);
			if(s->expr){
				expr_codegen(s->expr, file);
				fprintf(file, "\tCMP $0, %s\n", register_name(s->expr->reg));
				register_free(s->expr->reg);
				//If the above condition is true, jump to the end
				fprintf(file, "\tJE L%d\n", loop_end);
			}
			stmt_codegen(s->body, file);
			if(s->next_expr){
				//next expression
				expr_codegen(s->next_expr, file);
				register_free(s->next_expr->reg);
			}
			//jump to top of loop
			fprintf(file, "\tJMP L%d\n", loop_start);
			fprintf(file, "L%d:\n", loop_end);
			break;
		case STMT_PRINT:
			while(e){
				struct expr *e2;
				struct expr *e3;
				if(e->kind == EXPR_COMMA) e2 = e->left;
				else e2 = e;
				t = expr_typecheck(e2);
				switch(t->kind) {
					case TYPE_BOOLEAN:
						e3 = expr_create(EXPR_FCALL, expr_create_ident("print_boolean"), e2);
						expr_codegen(e3, file);
						register_free(e3->reg);
						break;
					case TYPE_CHARACTER:
						e3 = expr_create(EXPR_FCALL, expr_create_ident("print_character"), e2);
						expr_codegen(e3, file);
						register_free(e3->reg);
						break;
					case TYPE_INTEGER:
						e3 = expr_create(EXPR_FCALL, expr_create_ident("print_integer"), e2);
						expr_codegen(e3, file);
						register_free(e3->reg);
						break;
					case TYPE_STRING:
						e3 = expr_create(EXPR_FCALL, expr_create_ident("print_string"), e2);
						expr_codegen(e3, file);
						register_free(e3->reg);
						break;
				}
				if(e->kind!=EXPR_COMMA) {
					break;
				} else {
					e = e->right;
				}
			}
/* Makes it print a newline for every call to print
			e = expr_create(EXPR_FCALL, expr_create_ident("print_string"), expr_create_string_value("\\n"));
			expr_codegen(e, file);
			register_free(e->reg);
*/
			break;
	}
	stmt_codegen(s->next, file);
}
