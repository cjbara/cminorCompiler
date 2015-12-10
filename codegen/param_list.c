#include "param_list.h"
#include "globl.h"
#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>

//create a new param_list
struct param_list * param_list_create(const char *name, struct type *type){
	struct param_list * p;
	p = malloc(sizeof(*p));
	p->name = name;
	p->type = type;
	p->next = 0; 
	p->symbol = 0;

	return p;
}

//delete a param_list
void param_list_delete(struct param_list *p){
	if(!p) return;
	param_list_delete(p->next);
	type_delete(p->type);

	free(p);
}

//resolves a param list
void param_list_resolve(struct param_list *p) {
	if(!p) return;
	
	struct symbol *sym = symbol_create(SCOPE_PARAM, p->type, 0);
	//check if variable already defined in this scope
	if(scope_lookup_local(p->name)){
		printf("resolve error: ");
		printf( "%s is already declared as a param in this scope\n",p->name);
		error_count++;
	}
	
	scope_bind(p->name, sym);
	
	param_list_resolve(p->next);
}

//recursively prints out a parameter list
void param_list_print(struct param_list *p){
	if(!p) return;
	printf("%s: ", p->name); 
	type_print(p->type);
	
	if(p->next){
		printf(", ");
		param_list_print(p->next);
	}
}

int param_list_compare(struct param_list *a, struct param_list *b){
	if(a == 0) {
		if(b == 0) return 1;
		else return 0;
	} else if(b == 0) {
		return 0;
	}

	if(!type_compare(a->type, b->type)) return 0;
	if(!param_list_compare(a->next, b->next)) return 0;

	return 1;
}

