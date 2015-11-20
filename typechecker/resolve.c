#include "resolve.h"

void resolve(){
	head->hash_table = hash_table_create(127, hash_string);
	head->next = 0;
	error_count = 0;

}


