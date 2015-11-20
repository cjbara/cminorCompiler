#include "error.h"
#include "globl.h"
#include <stdio.h>
#include <stdlib.h>

void scan_error() {
  printf("scan error: %s is not a valid character\n", yytext);
  exit(1);
}

void resolve_error(const char *name){
	printf("resolve error: %s has not been declared in this scope\n", name);
	error_count++;
}
