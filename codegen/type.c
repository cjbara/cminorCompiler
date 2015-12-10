#include "type.h"
#include "expr.h"
#include <stdio.h>
#include <stdlib.h>

//create a new type variable
struct type * type_create(type_kind_t kind, struct param_list *p, struct type *s, int num){
	struct type * t;
	t = malloc(sizeof(*t));
	t->kind = kind;
	t->params = p;
	t->subtype = s;
	t->number = num;
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
			printf("array [%d] ", t->number); 
			type_print(t->subtype); 
			break;
		case TYPE_FUNCTION: printf("function "); type_print(t->subtype); printf(" ("); param_list_print(t->params); printf(")"); break;
		case TYPE_VOID: printf("void"); break;
	}
}

//copies a type and returns it
struct type * type_copy(struct type *t) {
	struct type *copy = type_create(t->kind, t->params, t->subtype, t->number);
	return copy;
}

//Recursively checks if two types are the same
int type_compare(struct type *a, struct type *b) {
	if(!a && !b) return 1; //if they are both null, return 1
	if(!a || !b) return 0; //if one is null and the other isn't, return 0

	//if any of the next 3 are not true, return 0, otherwise, return 1
	if(a->kind != b->kind) return 0;
	if(a->number != b->number) return 0;
	if(!type_compare(a->subtype, b->subtype)) return 0;
	return 1;
}

