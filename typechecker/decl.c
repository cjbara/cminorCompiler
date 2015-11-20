#include "decl.h"
#include "scope.h"
#include "symbol.h"
#include "type.h"
#include "expr.h"
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
		scope_enter();
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
		stmt_typecheck(d->code, d->symbol);
	}
	decl_typecheck(d->next);
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
		for(i; i<indent; i++) printf("\t");
		printf("\n}\n");
	} else if (d->value) {
		printf(" = ");
		expr_print(d->value);
		printf(";\n");
	} else {
		printf(";\n");
	}
	decl_print(d->next, indent);
}




