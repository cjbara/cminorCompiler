#include "param_list.h"
#include <stdio.h>
#include <stdlib.h>

//create a new param_list
struct param_list * param_list_create(char *name, struct type *type){
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
