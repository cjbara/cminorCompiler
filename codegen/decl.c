#include "decl.h"
#include "scope.h"
#include "symbol.h"
#include "type.h"
#include "expr.h"
#include "stmt.h"
#include "globl.h"
#include <stdio.h>
#include <stdlib.h>

//create a new declaration
struct decl * decl_create(const char *name, struct type *type, struct expr *value, struct stmt *code) {
	struct decl *d;
	d = malloc(sizeof(*d));
	d->name = name;
	d->type = type;
	d->value = value;
	d->code = code;
	d->next = 0;
	d->symbol = 0; 

	return d;
}

void decl_delete(struct decl *d){
	if(!d) return;
	type_delete(d->type);
	expr_delete(d->value);
	stmt_delete(d->code);
	decl_delete(d->next);
	
	free(d);
}

void decl_print(struct decl *d, int indent){
	if(!d) return;
	
	int i = 0;
	for(i; i<indent; i++) printf("\t");
	printf("%s: ", d->name);
	type_print(d->type);
	if(d->code){ //print the code
		printf(" = {\n");
		stmt_print(d->code, indent+1);
		for(i=0; i<indent; i++) printf("\t");
		printf("}\n");
	} else if (d->value) {
		printf(" = ");
		expr_print(d->value);
		printf(";\n");
	} else {
		printf(";\n");
	}
	decl_print(d->next, indent);
}

void decl_resolve(struct decl *d) {
	if(!d) return;
	struct symbol *sym;

	if(scope_level() == 1) sym = symbol_create(SCOPE_GLOBAL, d->type, d->name);
	else sym = symbol_create(SCOPE_LOCAL, d->type, d->name);
	
	struct symbol *sym2 = scope_lookup_local(d->name);
	if(d->type->kind == TYPE_FUNCTION && sym2) {
		if(sym2->type->kind == TYPE_FUNCTION){
			//check if the new declaration is compatible
			if(!param_list_compare(sym2->type->params, sym->type->params)){
				printf("resolve error: bad redeclaration of function %s, parameters do not match initial declaration\n", sym2->name);
				error_count++;
			}
			if(!type_compare(sym2->type, sym->type)){
				printf("resolve error: bad redeclaration of function %s, return type does not match initial declaration\n", sym2->name);
				error_count++;
			}
			if(sym2->defined){
				printf("resolve error: function %s has already been defined. Redefinition is not permitted\n", sym->name);
				error_count++;
			}
			if(d->code) sym2->defined = 1;
		}
	} 
	if(scope_lookup_local(d->name) && sym2->type->kind != TYPE_FUNCTION) {
		printf("resolve error: ");
		printf("%s is already declared as a ", d->name);
		if(scope_level() != 1) printf("local ");
		else printf("global ");
		printf("variable of type ");
		type_print(sym2->type);
		if(scope_level() != 1) printf(" in this scope");
		printf("\n");
		error_count++;
	}

	scope_bind(d->name, sym);
	d->symbol = sym;
	expr_resolve(d->value);
	if(d->code) {
		scope_enter(1);
		param_list_resolve(d->type->params);
		stmt_resolve(d->code);
		scope_leave();
	}
	decl_resolve(d->next);
}

void decl_typecheck(struct decl *d) {
	if(!d) return;
	struct type *e_type = expr_typecheck(d->value);
	if(d->value){
		if(!type_compare(d->type, e_type) && d->type->kind != TYPE_FUNCTION){
			//declaration error message
			printf("type error: cannot assign ");
			type_print(e_type);
			printf(" ");
			expr_print(d->value);
			printf(" to ");
			type_print(d->type);
			printf(" %s\n", d->name);
			error_count++;
		} 
	}
	if(d->symbol->kind == SCOPE_GLOBAL && !expr_is_constant(d->value)){
		printf("type error: cannot assign non-constant value ");
		expr_print(d->value);
		printf(" to global declaration of %s\n", d->name);
		error_count++;
	}
	if(d->code){
		if(d->symbol->kind != SCOPE_GLOBAL) { //no functions at the local scope
			printf("type error: function %s must be declared at global scope\n", d->name);
			error_count++;
		} else {
			stmt_typecheck(d->code, d->symbol);
			//determine the number of locals and params in a function
			decl_function_params(d);
			decl_function_locals(d);
		}
	}
	if(d->type->kind == TYPE_STRING && d->value) {
		d->symbol->string_literal = d->value->string_literal;
	}
	decl_typecheck(d->next);
}

void decl_function_params(struct decl *d) {
	//checks how many parameters a function has, and binds this number to its symbol
	if(!d->symbol) return;
	
	struct param_list *p = d->type->params;
	d->symbol->func_params = 0;
	while(p) {
		d->symbol->func_params++;
		p = p->next;
	}
	//printf("Function %s has %d parameters\n", d->name, d->symbol->func_params);
}

void decl_function_locals(struct decl *d) {
	//checks how many local vars a function has, and binds this number to its symbol
	if(!d->symbol) return;
	
	struct stmt *s = d->code;
	d->symbol->func_locals = 0;
	while(s) {
		d->symbol->func_locals += stmt_function_locals(s);
		s = s->next;
	}
	//printf("Function %s has %d local variables\n", d->name, d->symbol->func_locals);
}

void decl_codegen(struct decl *d, FILE *file) {
	if(!d) return;

	//Global declarations are treated differently than locals
	if(d->symbol->kind == SCOPE_GLOBAL){
		switch(d->type->kind) {
			case TYPE_BOOLEAN:
			case TYPE_CHARACTER:
			case TYPE_INTEGER:
				fprintf(file, "\n\t#Declaring global variable %s\n", d->name);
				fprintf(file, ".data\n%s: .quad ", d->name);
				if(d->value) { //print out literal value
					fprintf(file, "%d\n", d->value->literal_value);
				} else {	//otherwise initialize to 0
					fprintf(file, "0\n");
				}
				break;
			case TYPE_STRING:
				fprintf(file, "\n\t#Declaring global string %s\n", d->name);
				fprintf(file, ".data\n%s: .string \"", d->name);
				if(d->value){
					fprintf(file, "%s", d->value->string_literal);
				}
				fprintf(file, "\"\n");
				break;
			case TYPE_FUNCTION:
				if(d->code){
					fprintf(file, "\n\t#Defining function %s\n", d->name);
					fprintf(file, ".text\n.global %s\n%s:\n", d->name, d->name);
					preamble(d, file);
					//function body
					stmt_codegen(d->code, file);
					postamble(file);
				} else {
					fprintf(file, "\n\t#Defining function %s\n", d->name);
					fprintf(file, "\n\t#Declaring function %s\n", d->name);
					fprintf(file, ".global %s\n", d->name);
				}
				break;
			case TYPE_ARRAY:
				array_error();
		}
	} else { //the declaration is a local/param
		if(d->value) {
			expr_codegen(d->value, file);
			fprintf(file, "\tMOV %s, %s\n", register_name(d->value->reg), symbol_code(d->symbol));
			register_free(d->value->reg);
		}
	}
	decl_codegen(d->next, file);
}

void preamble(struct decl *d, FILE *file) {
	//preamble for any function
	//Two parts change depending on number of params/local vars
	fprintf(file, "\tPUSHQ %%rbp\n");
	fprintf(file, "\tMOV %%rsp, %%rbp\n");
	//Push all the parameters onto the stack
	//switch is in decreasing order so each param leads to the other params getting pushed
	int i=1;
	while(i <= d->symbol->func_params){
		switch (i) {
			case 1: fprintf(file, "\tPUSHQ %%rdi\n"); break;
			case 2: fprintf(file, "\tPUSHQ %%rsi\n"); break;
			case 3: fprintf(file, "\tPUSHQ %%rdx\n"); break;
			case 4: fprintf(file, "\tPUSHQ %%rcx\n"); break;
			case 5: fprintf(file, "\tPUSHQ %%r8\n"); break;
			case 6: fprintf(file, "\tPUSHQ %%r9\n"); break;
		}
		i++;
	}
	//allocate space for locals
	fprintf(file, "\tSUBQ $%d, %%rsp\n", 8 * d->symbol->func_locals);//*locals);
	//save registers on stack
	fprintf(file, "\tPUSHQ %%rbx\n");
	fprintf(file, "\tPUSHQ %%r12\n");
	fprintf(file, "\tPUSHQ %%r13\n");
	fprintf(file, "\tPUSHQ %%r14\n");
	fprintf(file, "\tPUSHQ %%r15\n");
}

void postamble(FILE *file) {
	//postamble for any function
	fprintf(file, "\tPOPQ %%r15\n");
	fprintf(file, "\tPOPQ %%r14\n");
	fprintf(file, "\tPOPQ %%r13\n");
	fprintf(file, "\tPOPQ %%r12\n");
	fprintf(file, "\tPOPQ %%rbx\n");
	//restore the stack pointer 
	fprintf(file, "\tMOV %%rbp, %%rsp\n");
	fprintf(file, "\tPOPQ %%rbp\n");
	//return
	fprintf(file, "\n\tRET\n\n");
}
