#include "symbol.h"
#include "globl.h"
#include "scope.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct symbol * symbol_create(symbol_kind_t kind, struct type *type, const char *name) {
	struct symbol *s;
	s = malloc(sizeof(*s));
	s->kind = kind;
	s->type = type;
	s->name = name;
	s->defined = 0;
	s->which = 0;
	
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

const char * symbol_code(struct symbol *s) {
	int offset = -8;
	if(s->kind == SCOPE_PARAM) {
		offset = -8 * (s->which + 1);
	} else if(s->kind == SCOPE_LOCAL) {
		offset = -8 * (s->which + 1);
	}
	char offsetStr[20];
	sprintf(offsetStr, "%d(%%rbp)", offset);
	
	const char *returnAddr = offsetStr;
	
	switch(s->kind){
		case SCOPE_LOCAL:
			return returnAddr;
		case SCOPE_PARAM:
			return returnAddr;
		case SCOPE_GLOBAL:
			return s->name;
	}
}
