#include "expr.h"
#include "type.h"
#include "param_list.h"
#include "globl.h"
#include "scope.h"
#include "symbol.h"
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
		printf("type error: In call to function %s, expected %d parameters, but received %d\n", function_name, param-1, func_params);
		error_count++;
		return;
	} 
	if(!p) {
		struct expr *e1;
		if(e->kind == EXPR_COMMA) e1 = e->left;
		else e1 = e;
		struct type *t = expr_typecheck(e1);
		printf("type error: In call to function %s, expected %d parameters, but received %d\n", function_name, param-1, func_params);
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

