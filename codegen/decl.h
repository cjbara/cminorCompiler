#include <stdio.h>

struct decl {
	const char *name;
	struct type *type;
	struct expr *value;
	struct stmt *code;
	struct symbol *symbol;
	struct decl *next;
};

struct decl * decl_create(const char *, struct type *, struct expr *, struct stmt *);
void decl_delete(struct decl *);
void decl_print(struct decl *, int);

void decl_resolve(struct decl *d);
void decl_typecheck(struct decl *d);

void decl_function_params(struct decl *d);
void decl_function_locals(struct decl *d);

void decl_codegen(struct decl *d, FILE *file);
void preamble(struct decl *d, FILE *file);
void postamble(FILE *file);


