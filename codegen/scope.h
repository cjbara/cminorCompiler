#include "symbol.h"

struct hash_table_list {
	struct hash_table *hash_table;
	struct hash_table_list *next;
	int scope_variables;
};

void init_globals();
void delete_globals();
void scope_enter(int function); //create a new scope
void scope_leave(); //leave current scope
int scope_level(); //returns number of scopes 

void scope_bind(const char *name, struct symbol *sym); //define new
struct symbol * scope_lookup(const char *name); //is a var defined
struct symbol * scope_lookup_local(const char *name); //is a var defined
