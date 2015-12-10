#include "error.h"
#include "globl.h"
#include <stdio.h>
#include <stdlib.h>

void scan_error(int line) {
	printf("scan error near line %d: %s is not a valid character\n", line, yytext);
	exit(1);
}

void resolve_error(const char *name){
	printf("resolve error: %s has not been declared in this scope\n", name);
	error_count++;
}

void register_error() {
	printf("codegen error: out of registers\n");
	exit(1);
}

void array_error() {
	printf("codegen error: arrays are not supported in C-minor\n");
	exit(1);
}

void fcall_error() {
	printf("codegen error: function calls cannot have more than 6 arguments in C-minor\n");
	exit(1);
}

