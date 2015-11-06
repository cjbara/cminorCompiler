#include "decl.h"
#include <stdio.h>
#include <stdlib.h>

//create a new declaration
struct decl * decl_create(char *name, struct type *type, struct expr *value, struct stmt *code) {
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




