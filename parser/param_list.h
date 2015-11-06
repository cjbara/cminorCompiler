struct param_list {
	char *name;
	struct type *type;
	struct symbol *symbol;
	struct param_list *next;
};

struct param_list * param_list_create(char *, struct type *);
void param_list_delete(struct param_list *);
void param_list_print(struct param_list *);
