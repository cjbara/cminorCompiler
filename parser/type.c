#include "type.h"
#include <stdio.h>
#include <stdlib.h>

//create a new type variable
struct type * type_create(type_kind_t kind, struct param_list *p, struct type *s, struct expr *e){
	struct type * t;
	t = malloc(sizeof(*t));
	t->kind = kind;
	t->params = p;
	t->subtype = s;
	t->number = e;
	return t;
}

//delete a type
void type_delete(struct type *t){
	if(!t) return;
	param_list_delete(t->params);
	type_delete(t->subtype);

	free(t);
}

void type_print(struct type *t){
	if(!t) return;
	switch(t->kind){
		case TYPE_BOOLEAN: printf("boolean"); break;
		case TYPE_CHARACTER: printf("char"); break;
		case TYPE_INTEGER: printf("integer"); break;
		case TYPE_STRING: printf("string"); break;
		case TYPE_ARRAY: 
			printf("array [");
			expr_print(t->number);
			printf("] "); 
			type_print(t->subtype); 
			break;
		case TYPE_FUNCTION: printf("function "); type_print(t->subtype); printf("("); param_list_print(t->params); printf(")"); break;
		case TYPE_VOID: printf(""); break;
	}
}
