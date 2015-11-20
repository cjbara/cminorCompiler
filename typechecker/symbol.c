#include "symbol.h"
#include "globl.h"
#include "scope.h"
#include <stdio.h>
#include <stdlib.h>

struct symbol * symbol_create(symbol_kind_t kind, struct type *type, const char *name) {
	struct symbol *s;
	s = malloc(sizeof(*s));
	s->kind = kind;
	s->type = type;
	s->name = name;
	s->defined = 0;
	
	if(s->kind != SCOPE_GLOBAL){
		s->which = head->scope_variables;
		head->scope_variables++;
	}

	return s;
}

void symbol_print(struct symbol *s) {
	if(!s) return;
	switch(s->kind){
		case SCOPE_LOCAL:
			printf("local %d", s->which);
			break;
		case SCOPE_PARAM:
			printf("param %d", s->which);
			break;
		case SCOPE_GLOBAL:
			printf("global %s", s->name);
			break;
	}
	printf("\n");
}
