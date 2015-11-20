#include "scope.h"
#include "hash_table.h"
#include "globl.h"
#include <stdio.h>
#include <stdlib.h>

struct hash_table_list *head; 
int error_count = 0;

void init_globals(){
	head = malloc(sizeof(*head));
	head->hash_table = hash_table_create(127, hash_string);
	head->next = 0;
	head->scope_variables = 0;
}

void delete_globals(){
	scope_leave();
}

void scope_enter() {
	struct hash_table_list *h;
	h = malloc(sizeof(*h));
	h->hash_table = hash_table_create(127, hash_string);
	h->scope_variables = 0;

	//add this new hash table to the linked list
	h->next = head;
	head = h;
}

void scope_leave() {
	struct hash_table_list *h = head;
	head = head->next;
	hash_table_delete(h->hash_table);
	free(h);
}

int scope_level() {
	struct hash_table_list *h = head;
	int i=1;
	while(h->next != 0){
		h = h->next;
		i++;
	}
	return i;
}

void scope_bind(const char *name, struct symbol *sym) {
	hash_table_insert(head->hash_table, name, sym);
}

struct symbol * scope_lookup(const char *name) {
	struct symbol *s;
	struct hash_table_list *h = head;
	while(h){
		s = hash_table_lookup(h->hash_table, name);
		if(s) return s;
		h = h->next;
	}
}

struct symbol * scope_lookup_local(const char *name) {
	struct symbol *s;
	s = hash_table_lookup(head->hash_table, name);
	if(s) return s;
	else return 0;
}
