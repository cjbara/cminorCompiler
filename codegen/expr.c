#include "expr.h"
#include "type.h"
#include "param_list.h"
#include "globl.h"
#include "scope.h"
#include "symbol.h"
#include "register.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int string_number = 0;

//create a new expression without a value
struct expr * expr_create(expr_t kind, struct expr *left, struct expr *right){
	struct expr *e;
	e = malloc(sizeof(*e));
	e->kind = kind;
	e->left = left;
	e->right = right;
	e->name = 0;
	e->reg = 0;
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

//create a new expression as a bool literal
struct expr * expr_create_bool_value(int value){
	struct expr *e;
	if(value) {
		e = expr_create(EXPR_TRUE, 0, 0);
		e->literal_value = 1;
	} else {
		e = expr_create(EXPR_FALSE, 0, 0);
		e->literal_value = 0;
	}
	return e;
}

//create a new expression as a string literal
struct expr * expr_create_string_value(const char *string_val){
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
		case EXPR_BLOCK_COMMA: printf(", "); break;
	}
}

//Resolves the name of an expression
void expr_resolve(struct expr *e){
	if(!e) return;
	expr_resolve(e->left);
	expr_resolve(e->right);
	if(e->kind == EXPR_IDENT) {
		e->symbol = scope_lookup(e->name);
		if(e->symbol) {
			printf("%s resolves to ");
			symbol_print(e->symbol);
		} else { //not defined in this scope
			e->symbol = 0;
			resolve_error(e->name);
		}
	}
}

int expr_is_constant(struct expr *e){
	if(!e) return 1; //null is a constant expression
	if(expr_is_constant(e->left) == 0) return 0;
	if(expr_is_constant(e->right) == 0) return 0;

	if(e->kind == EXPR_IDENT) return 0;
	else return 1;
}

struct type * expr_typecheck(struct expr *e) {
	if(!e) return type_create(TYPE_VOID, 0, 0, 0);
	struct type *L = expr_typecheck(e->left);
	struct type *R = expr_typecheck(e->right);
	switch(e->kind) {
		case EXPR_ASSIGNMENT:
			if(L->kind == TYPE_FUNCTION){
				printf("type error: cannot use assignment operator on function ");
				expr_print(e->left);
				error_count++;
			}
			if(R->kind == TYPE_FUNCTION){
				printf("type error: cannot use assignment operator on function ");
				expr_print(e->right);
				error_count++;
			}
			if(!type_compare(L, R)){
				printf("type error: cannot assign ");
				type_print(R);
				printf(" ");
				expr_print(e->right);
				printf(" to ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf("\n");
				error_count++;
			}
			return L;
			break;
		case EXPR_GE:
			if(L->kind != TYPE_INTEGER || R->kind != TYPE_INTEGER){
				printf("type error: cannot use operator >= to compare ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf(" and ");
				type_print(R);
				printf(" ");
				expr_print(e->right);
				printf(". This operator can only be used on two integers.\n");
				error_count++;
			}
			return type_create(TYPE_BOOLEAN, 0, 0, 0);
			break;
		case EXPR_LE:
			if(L->kind != TYPE_INTEGER || R->kind != TYPE_INTEGER){
				printf("type error: cannot use operator <= to compare ");
				type_print(L);
				expr_print(e->left);
				printf(" and ");
				type_print(R);
				expr_print(e->right);
				printf(". This operator can only be used on two integers.\n");
				error_count++;
			}
			return type_create(TYPE_BOOLEAN, 0, 0, 0);
			break;
		case EXPR_GT:
			if(L->kind != TYPE_INTEGER || R->kind != TYPE_INTEGER){
				printf("type error: cannot use operator > to compare ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf(" and ");
				type_print(R);
				printf(" ");
				expr_print(e->right);
				printf(". This operator can only be used on two integers.\n");
				error_count++;
			}
			return type_create(TYPE_BOOLEAN, 0, 0, 0);
			break;
		case EXPR_LT:
			if(L->kind != TYPE_INTEGER || R->kind != TYPE_INTEGER){
				printf("type error: cannot use operator < to compare ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf(" and ");
				type_print(R);
				printf(" ");
				expr_print(e->right);
				printf(". This operator can only be used on two integers.\n");
				error_count++;
			}
			return type_create(TYPE_BOOLEAN, 0, 0, 0);
			break;
		case EXPR_EQ:
			if(L->kind == TYPE_ARRAY){
				printf("type error: cannot use operator == on array ");
				expr_print(e->left);
				printf("\n");
				error_count++;	
			} else if(L->kind == TYPE_FUNCTION){
				printf("type error: cannot use operator == on function ");
				expr_print(e->left);
				printf("\n");
				error_count++;	
			}
			if(R->kind == TYPE_ARRAY){
				printf("type error: cannot use operator == on array ");
				expr_print(e->right);
				printf("\n");
				error_count++;	
			} else if(R->kind == TYPE_FUNCTION){
				printf("type error: cannot use operator == on function ");
				expr_print(e->right);
				printf("\n");
				error_count++;	
			}
			if(L->kind != R->kind){
				printf("type error: cannot use operator == to compare ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf(" and ");
				type_print(R);
				printf(" ");
				expr_print(e->right);
				printf("\n");
				error_count++;
			}
			return type_create(TYPE_BOOLEAN, 0, 0, 0);
			break;
		case EXPR_NE:
			if(L->kind == TYPE_ARRAY){
				printf("type error: cannot use operator != on array ");
				expr_print(e->left);
				printf("\n");
				error_count++;	
			} else if(L->kind == TYPE_FUNCTION){
				printf("type error: cannot use operator != on function ");
				expr_print(e->left);
				printf("\n");
				error_count++;	
			}
			if(R->kind == TYPE_ARRAY){
				printf("type error: cannot use operator != on array ");
				expr_print(e->right);
				printf("\n");
				error_count++;	
			} else if(R->kind == TYPE_FUNCTION){
				printf("type error: cannot use operator != on function ");
				expr_print(e->right);
				printf("\n");
				error_count++;	
			}
			if(L->kind != R->kind){
				printf("type error: cannot use operator != to compare ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf(" and ");
				type_print(R);
				printf(" ");
				expr_print(e->right);
				printf("\n");
				error_count++;
			}
			return type_create(TYPE_BOOLEAN, 0, 0, 0);
			break;
		case EXPR_ADD:
			if(L->kind != TYPE_INTEGER || R->kind != TYPE_INTEGER){
				printf("type error: cannot add ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf(" to ");
				type_print(R);
				printf(" ");
				expr_print(e->right);
				printf("\n");
				error_count++;
			}
			return type_create(TYPE_INTEGER, 0, 0, 0);
			break;
		case EXPR_SUB:
				
			if((L->kind != TYPE_INTEGER || R->kind != TYPE_INTEGER) && L->kind != TYPE_VOID){
				printf("type error: cannot subtract ");
				type_print(R);
				printf(" ");
				expr_print(e->right);
				printf(" from ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf("\n");
				error_count++;
			}
			return type_create(TYPE_INTEGER, 0, 0, 0);
			break;
		case EXPR_MUL:
			if(L->kind != TYPE_INTEGER || R->kind != TYPE_INTEGER){
				printf("type error: cannot multiply ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf(" with ");
				type_print(R);
				printf(" ");
				expr_print(e->right);
				printf("\n");
				error_count++;
			}
			return type_create(TYPE_INTEGER, 0, 0, 0);
			break;
		case EXPR_DIV:
			if(L->kind != TYPE_INTEGER || R->kind != TYPE_INTEGER){
				printf("type error: cannot divide ");
				type_print(R);
				printf(" ");
				expr_print(e->right);
				printf(" from ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf("\n");
				error_count++;
			}
			return type_create(TYPE_INTEGER, 0, 0, 0);
			break;
		case EXPR_MOD:
			if(L->kind != TYPE_INTEGER || R->kind != TYPE_INTEGER){
				printf("type error: cannot perform modular division ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf(" mod ");
				type_print(R);
				printf(" ");
				expr_print(e->right);
				printf("\n");
				error_count++;
			}
			return type_create(TYPE_INTEGER, 0, 0, 0);
			break;
		case EXPR_POW:
			if(L->kind != TYPE_INTEGER || R->kind != TYPE_INTEGER){
				printf("type error: cannot exponentiate ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf(" ^ ");
				type_print(R);
				printf(" ");
				expr_print(e->right);
				printf("\n");
				error_count++;
			}
			return type_create(TYPE_INTEGER, 0, 0, 0);
			break;
		case EXPR_POSTFIX_PLUS:
			if(L->kind != TYPE_INTEGER){
				printf("type error: cannot increment ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf("\n");
				error_count++;
			} 
			if(e->left->kind != EXPR_IDENT) {
				printf("type error: cannot increment non-variable ");
				expr_print(e->left);
				printf("\n");
				error_count++;
			}	
			return type_create(TYPE_INTEGER, 0, 0, 0);
			break;
		case EXPR_POSTFIX_MINUS:
			if(L->kind != TYPE_INTEGER){
				printf("type error: cannot decrement ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf("\n");
				error_count++;
			}
			if(e->left->kind != EXPR_IDENT) {
				printf("type error: cannot decrement non-variable ");
				expr_print(e->left);
				printf("\n");
				error_count++;
			}	
			return type_create(TYPE_INTEGER, 0, 0, 0);
			break;
		case EXPR_LOGICAL_NOT:
			if(R->kind != TYPE_BOOLEAN){
				printf("type error: cannot negate non-boolean ");
				type_print(R);
				printf(" ");
				expr_print(e->right);
				printf("\n");
				error_count++;
			}
			return type_create(TYPE_BOOLEAN, 0, 0, 0);
			break;
		case EXPR_LOGICAL_AND:
			if(L->kind != TYPE_BOOLEAN || R->kind != TYPE_BOOLEAN){
				printf("type error: cannot use && to compare non-boolean ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf(" and ");
				type_print(R);
				printf(" ");
				expr_print(e->right);
				printf("\n");
				error_count++;
			}
			return type_create(TYPE_BOOLEAN, 0, 0, 0);
			break;
		case EXPR_LOGICAL_OR:
			if(L->kind != TYPE_BOOLEAN || R->kind != TYPE_BOOLEAN){
				printf("type error: cannot use && to compare non-boolean ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf(" and ");
				type_print(R);
				printf(" ");
				expr_print(e->right);
				printf("\n");
				error_count++;
			}
			return type_create(TYPE_BOOLEAN, 0, 0, 0);
			break;
		case EXPR_INTEGER_LITERAL:
			return type_create(TYPE_INTEGER, 0, 0, 0);
			break;
		case EXPR_STRING_LITERAL:
			return type_create(TYPE_STRING, 0, 0, 0);
			break;
		case EXPR_CHAR_LITERAL:
			return type_create(TYPE_CHARACTER, 0, 0, 0);
			break;
		case EXPR_TRUE:
			return type_create(TYPE_BOOLEAN, 0, 0, 0);
			break;
		case EXPR_FALSE:
			return type_create(TYPE_BOOLEAN, 0, 0, 0);
			break;
		case EXPR_IDENT:
			return e->symbol->type;
			break;
		case EXPR_FCALL:
			if(L->kind != TYPE_FUNCTION) {
				printf("type error: cannot execute function call to non-function ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf("\n");
				error_count++;
			}
			function_typecheck(e->left->name, e->right, e->left->symbol->type->params, 1, function_params(e)+1);
			return L->subtype;
			break;
		case EXPR_ARRCALL:
			if(L->kind != TYPE_ARRAY) {
				printf("type error: cannot index into non-array ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf("\n");
				error_count++;
			} 
			//return the number of subtypes that the index requires
			int i;
			struct type *T = L;
			for(i = 0; i < array_call_subtypes(e->right); i++){
				T = T->subtype;
			}
			return T;
			break;
		case EXPR_ARRINDEX:
			if(L->kind != TYPE_INTEGER){
				printf("type error: cannot index an array using non-integer ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf("\n");
				error_count++;
			}
			return type_create(TYPE_INTEGER, 0, 0, 0);
			break;
		case EXPR_PARENS:
			return R;
			break;
		case EXPR_BLOCK:
			return type_create(TYPE_ARRAY, 0, R, exprs_in_block(e)-1);
			break;
		case EXPR_BLOCK_COMMA:
			if(L->kind != R->kind && R->kind != TYPE_VOID){
				printf("type error: cannot have ");
				type_print(L);
				printf(" ");
				expr_print(e->left);
				printf(" and ");
				type_print(R);
				printf(" ");
				expr_print(e->right);
				printf(" in the same expression list\n");
				error_count++;
				return type_create(TYPE_VOID,0,0,0);
			}
			return L;
			break;
		case EXPR_COMMA:
			return R;
			break;
	}
}

int exprs_in_block(struct expr *e){
	if(!e) return 0;
	int count = 0;
	if(e->kind != EXPR_BLOCK_COMMA) count = 1;
	return exprs_in_block(e->left) + exprs_in_block(e->right) + count;
}

int array_call_subtypes(struct expr *e) {
	if(!e) return 0;
	int count = 0;
	if(e->kind == EXPR_ARRINDEX) count = 1;
	return array_call_subtypes(e->right) + count;
}

//checks if a function call matches up to the function types
void function_typecheck(const char *function_name, struct expr *e, struct param_list *p, int param, int func_params) {
	if(!e && !p) return; //only for no parameters
	if(!e) {
		printf("type error: In call to function %s, expected %d parameters, but received %d\n", function_name, param, func_params);
		error_count++;
		return;
	} 
	if(!p) {
		struct expr *e1;
		if(e->kind == EXPR_COMMA) e1 = e->left;
		else e1 = e;
		struct type *t = expr_typecheck(e1);
		printf("type error: In call to function %s, expected %d parameters, but received %d\n", function_name, param, func_params);
		error_count++;
		return;
	}
	int last_expr = 0, last_param = 0;
	if(e->kind != EXPR_COMMA) last_expr = 1;
	if(!p->next) last_param = 1;

	struct type *t = expr_typecheck(e->left);
	if(e->kind == EXPR_COMMA){
		if(!type_compare(t, p->type)){
			printf("type error: In call to function %s, expected parameter %d to be of type ", function_name, param);
			type_print(p->type);
			printf(". Instead, expression ");
			expr_print(e->left);
			printf(" of type ");
			type_print(t);
			printf(" was passed to parameter %d\n", param);
			error_count++;
		}	
	}

	if(last_expr && last_param) return;
	function_typecheck(function_name, e->right, p->next, ++param, func_params);
}

int function_params(struct expr *e){
	if(!e) return 0;
	int count = 0;
	if(e->kind == EXPR_COMMA) count = 1;
	return function_params(e->right) + count;
}

//Generates code and writes it to a file
void expr_codegen(struct expr *e, FILE *file) {
	if(!e) return;
	struct expr *e2;
	switch(e->kind) {
		case EXPR_ASSIGNMENT:
			fprintf(file, "\n\t#Assignment of %s %d right value\n", e->left->symbol->name, e->left->symbol->which);
			expr_codegen(e->right, file);
			fprintf(file, "\n\t#Assignment assign to %s %d\n", e->left->symbol->name, e->left->symbol->which);
			fprintf(file, "\tMOV %s, %s\n", register_name(e->right->reg), symbol_code(e->left->symbol));
			e->reg = e->right->reg;
			register_free(e->left->reg);
			break;
		case EXPR_GE: //all of these go to the compare function
		case EXPR_LE:
		case EXPR_GT:
		case EXPR_LT:
		case EXPR_EQ:
		case EXPR_NE:
			compare(e, file);
			break;
		case EXPR_ADD:
			expr_codegen(e->left, file);
			expr_codegen(e->right, file);
			fprintf(file, "\n\t#Addition\n");
			fprintf(file, "\tADD %s, %s\n", register_name(e->left->reg), register_name(e->right->reg));
			e->reg = e->right->reg;
			register_free(e->left->reg);
			break;
		case EXPR_SUB:
			expr_codegen(e->left, file);
			expr_codegen(e->right, file);
			fprintf(file, "\n\t#Subtraction\n");
			fprintf(file, "\tSUB %s, %s\n", register_name(e->right->reg), register_name(e->left->reg));
			e->reg = e->left->reg;
			register_free(e->right->reg);
			break;
		case EXPR_MUL:
			expr_codegen(e->left, file);
			expr_codegen(e->right, file);
			fprintf(file, "\n\t#Multiplication\n");
			fprintf(file, "\tMOV %s, %%rax\n", register_name(e->left->reg));
			fprintf(file, "\tIMUL %s\n", register_name(e->right->reg));
			fprintf(file, "\tMOV %%rax, %s\n", register_name(e->right->reg));
			register_free(e->left->reg);
			e->reg = e->right->reg;
			break;
		case EXPR_DIV:
			expr_codegen(e->left, file);
			expr_codegen(e->right, file);
			fprintf(file, "\n\t#Division\n");
			fprintf(file, "\tMOV %s, %%rax\n", register_name(e->left->reg));
			fprintf(file, "\tCQO\n");
			fprintf(file, "\tIDIV %s\n", register_name(e->right->reg));
			fprintf(file, "\tMOV %%rax, %s\n", register_name(e->right->reg));
			register_free(e->left->reg);
			e->reg = e->right->reg;
			break;
		case EXPR_MOD:
			expr_codegen(e->left, file);
			expr_codegen(e->right, file);
			fprintf(file, "\n\t#Modulus\n");
			fprintf(file, "\tMOV %s, %%rax\n", register_name(e->left->reg));
			fprintf(file, "\tCQO\n");
			fprintf(file, "\tIDIV %s\n", register_name(e->right->reg));
			fprintf(file, "\tMOV %%rdx, %s\n", register_name(e->right->reg));
			register_free(e->left->reg);
			e->reg = e->right->reg;
			break;
		case EXPR_POW:
			expr_codegen(e->left, file);
			expr_codegen(e->right, file);
			int label_start = label_count++;
			int label_end = label_count++;
			fprintf(file, "\n\t#Exponent function\n");
			fprintf(file, "\tMOV $1, %%rax\n");
			fprintf(file, "L%d:\n", label_start);
			fprintf(file, "\tCMP $0, %s\n", register_name(e->right->reg));
			fprintf(file, "\tJE L%d\n", label_end);
			fprintf(file, "\tSUB $1, %s\n", register_name(e->right->reg));
			fprintf(file, "\tMUL %s\n", register_name(e->left->reg));
			fprintf(file, "\tJMP L%d\n", label_start);
			fprintf(file, "L%d:\n", label_end);
			register_free(e->left->reg);
			register_free(e->right->reg);
			e->reg = register_alloc();
			fprintf(file, "\tMOV %%rax, %s\n", register_name(e->reg));
			break;
		case EXPR_LOGICAL_NOT:
			expr_codegen(e->right, file);
			fprintf(file, "\n\t#Logical Not\n");
			e->reg = e->right->reg;		
			fprintf(file, "\tCMPQ $0, %s\n", register_name(e->reg));
			fprintf(file, "\tJNE L%d\n", label_count);
			fprintf(file, "\tMOV $1, %s\n", register_name(e->reg));
			fprintf(file, "\tJMP L%d\n", label_count+1);
			fprintf(file, "L%d:\n", label_count++);
			fprintf(file, "\tMOV $0, %s\n", register_name(e->reg));
			fprintf(file, "L%d:\n", label_count++);
			break;
		case EXPR_LOGICAL_AND:
			expr_codegen(e->left, file);
			expr_codegen(e->right, file);
			fprintf(file, "\n\t#Logical And\n");
			fprintf(file, "\tAND %s, %s\n", register_name(e->left->reg), register_name(e->right->reg));
			e->reg = e->right->reg;
			register_free(e->left->reg);
			break;
		case EXPR_LOGICAL_OR:
			expr_codegen(e->left, file);
			expr_codegen(e->right, file);
			fprintf(file, "\n\t#Logical Or\n");
			fprintf(file, "\tOR %s, %s\n", register_name(e->left->reg), register_name(e->right->reg));
			e->reg = e->right->reg;
			register_free(e->left->reg);
			break;
		case EXPR_POSTFIX_PLUS:
			expr_codegen(e->left, file);
			fprintf(file, "\n\t#Increment\n");
			e->reg = register_alloc();
			fprintf(file, "\tMOV %s, %s\n", register_name(e->left->reg), register_name(e->reg));
			fprintf(file, "\tADD $1, %s\n", register_name(e->left->reg));
			fprintf(file, "\tMOV %s, %s\n", register_name(e->left->reg), symbol_code(e->left->symbol));
			register_free(e->left->reg);
			break;
		case EXPR_POSTFIX_MINUS:
			expr_codegen(e->left, file);
			fprintf(file, "\n\t#Increment\n");
			e->reg = register_alloc();
			fprintf(file, "\tMOV %s, %s\n", register_name(e->left->reg), register_name(e->reg));
			fprintf(file, "\tSUB $1, %s\n", register_name(e->left->reg));
			fprintf(file, "\tMOV %s, %s\n", register_name(e->left->reg), symbol_code(e->left->symbol));
			register_free(e->left->reg);
			break;
		case EXPR_IDENT:
			fprintf(file, "\n\t#Identifier %d %s\n", e->symbol->which, e->symbol->name);
			
			e->reg = register_alloc();
			fprintf(file, "\tMOV %s, %s\n", symbol_code(e->symbol), register_name(e->reg));
			break;
		case EXPR_INTEGER_LITERAL:
			//comment label
			fprintf(file, "\n\t#Integer literal %d\n", e->literal_value);

			e->reg = register_alloc();
			fprintf(file, "\tMOV $%d, %s\n", e->literal_value, register_name(e->reg));
			break;
		case EXPR_STRING_LITERAL:
			//comment label
			fprintf(file, "\n\t#String literal %s\n", e->string_literal);

			e->reg = register_alloc();
			fprintf(file, ".data\nSTR%d: \n.string \"%s\"\n.text\n", string_number, e->string_literal);
			fprintf(file, "\tLEA STR%d, %s\n", string_number++, register_name(e->reg));
			break;
		case EXPR_CHAR_LITERAL:
			fprintf(file, "\n\t#Char literal %c\n", e->literal_value);
			e->reg = register_alloc();
			fprintf(file, "\tMOV $%d, %s\n", e->literal_value, register_name(e->reg));
			break;
		case EXPR_TRUE:
			fprintf(file, "\n\t#True\n");
			e->reg = register_alloc();
			fprintf(file, "\tMOV $%d, %s\n", e->literal_value, register_name(e->reg));
			break;
		case EXPR_FALSE:
			fprintf(file, "\n\t#False\n");
			e->reg = register_alloc();
			fprintf(file, "\tMOV $%d, %s\n", e->literal_value, register_name(e->reg));
			register_free(e->reg);
			break;
		case EXPR_FCALL:
			if(function_params(e) >= 6) fcall_error();
			e->reg = register_alloc();
			fprintf(file, "\n\t#Calling function %s\n", e->left->name);
			if(!e->right){
				/* do nothing for no params */
			} else if(e->right->kind != EXPR_COMMA){ //this means single argument
				expr_codegen(e->right, file);
				fprintf(file, "\n\t#Move Only Argument\n");
				fprintf(file, "\tMOV %s, %%rdi\n", register_name(e->right->reg));
				register_free(e->right->reg);
			} else { //multiple parameters
				struct expr *param = e->right;
				int param_number = 0;
				while(param->kind == EXPR_COMMA){
					expr_codegen(param->left, file);
					fprintf(file, "\n\t#Move Argument %d\n", param_number);
					fprintf(file, "\tMOV %s, ", register_name(param->left->reg));
					register_free(param->left->reg);
					switch(param_number++){
						case 0: fprintf(file, "%%rdi"); break;
						case 1: fprintf(file, "%%rsi"); break;
						case 2: fprintf(file, "%%rdx"); break;
						case 3: fprintf(file, "%%rcx"); break;
						case 4: fprintf(file, "%%r8"); break;
						case 5: fprintf(file, "%%r9"); break;
					}	
					fprintf(file, "\n");
					param = param->right;
				}
				expr_codegen(param, file);
				fprintf(file, "\n\t#Move Argument %d\n", param_number);
				fprintf(file, "\tMOV %s, ", register_name(param->reg));
				switch(param_number++){
					case 0: fprintf(file, "%%rdi"); break;
					case 1: fprintf(file, "%%rsi"); break;
					case 2: fprintf(file, "%%rdx"); break;
					case 3: fprintf(file, "%%rcx"); break;
					case 4: fprintf(file, "%%r8"); break;
					case 5: fprintf(file, "%%r9"); break;
				}	
				fprintf(file, "\n");
				register_free(param->reg);
			}
			
			fprintf(file, "\tPUSH %%r10\n");
			fprintf(file, "\tPUSH %%r11\n");
			fprintf(file, "\n\tCALL %s\n\n", e->left->name);
			fprintf(file, "\tPOP %%r11\n");
			fprintf(file, "\tPOP %%r10\n");
			fprintf(file, "\tMOV %%rax, %s\n", register_name(e->reg));
			
			break;
		case EXPR_PARENS:
			expr_codegen(e->right, file);
			e->reg = e->right->reg;
			break;
		case EXPR_ARRCALL:	//These 4 have to do with arrays
		case EXPR_ARRINDEX:	//We are not implementing arrays for codegen
		case EXPR_BLOCK:
		case EXPR_BLOCK_COMMA:
			array_error();
			break;
	}
}

int param_number(struct expr *func, struct expr *param){
	int i=0;
	while(func != param){
		i++;
		func = func->right;
	}
	return i;
}

void compare(struct expr *e, FILE *file) {
	expr_codegen(e->left, file);
	expr_codegen(e->right, file);
	e->reg = register_alloc();
	
	if(expr_typecheck(e->left)->kind==TYPE_STRING && expr_typecheck(e->right)->kind==TYPE_STRING){
		fprintf(file, "\n\t#String comparison\n");
		const char *left;
		const char *right;
		//get the correct string for left
		if(e->left->kind==EXPR_STRING_LITERAL) left = e->left->string_literal;
		else if(e->left->kind==EXPR_IDENT) left = e->left->symbol->string_literal;

		//get the correct string for right
		if(e->right->kind==EXPR_STRING_LITERAL) right = e->right->string_literal;
		else if(e->right->kind==EXPR_IDENT) right = e->right->symbol->string_literal;

		//compare the strings
		int result = strcmp(left, right);
		if(e->kind == EXPR_EQ){
			if(result){
				fprintf(file, "\tMOV $0, %s\n", register_name(e->reg));
			} else {
				fprintf(file, "\tMOV $1, %s\n", register_name(e->reg));
			}
		} else if(e->kind == EXPR_NE){
			if(result){
				fprintf(file, "\tMOV $1, %s\n", register_name(e->reg));
			} else {
				fprintf(file, "\tMOV $0, %s\n", register_name(e->reg));
			}
		}
	} else {
		fprintf(file, "\n\t#Comparison\n");
		fprintf(file, "\tCMP %s, %s\n", register_name(e->right->reg), register_name(e->left->reg));
		register_free(e->left->reg);
		register_free(e->right->reg);
		char *jump = malloc(4);
		switch(e->kind){
			case EXPR_GE:
				strcpy(jump, "JGE");
				break;
			case EXPR_LE:
				strcpy(jump, "JLE");
				break;
			case EXPR_GT:
				strcpy(jump, "JG");
				break;
			case EXPR_LT:
				strcpy(jump, "JL");
				break;
			case EXPR_EQ:
				strcpy(jump, "JE");
				break;
			case EXPR_NE:
				strcpy(jump, "JNE");
				break;
		}
		int label_true = label_count++;
		int label_false = label_count++;
		fprintf(file, "\t%s L%d\n", jump, label_true);
		fprintf(file, "\tMOV $0, %s\n", register_name(e->reg));
		fprintf(file, "\tJMP L%d\n", label_false);
		fprintf(file, "L%d:\n", label_true);
		fprintf(file, "\tMOV $1, %s\n", register_name(e->reg));
		fprintf(file, "L%d:\n", label_false);
		free(jump);
	}
}
