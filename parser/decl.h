struct decl {
	char *name;
	struct type *type;
	struct expr *value;
	struct stmt *code;
	struct symbol *symbol;
	struct decl *next;
};

struct decl * decl_create(char *, struct type *, struct expr *, struct stmt *);
void decl_delete(struct decl *);
void decl_print(struct decl *, int);
