#ifndef PARAMS
#define PARAMS
struct param_list {
	const char *name;
	struct type *type;
	struct symbol *symbol;
	struct param_list *next;
};
#endif

struct param_list * param_list_create(const char *, struct type *);
void param_list_delete(struct param_list *);
void param_list_print(struct param_list *);

void param_list_resolve(struct param_list *p);
int param_list_compare(struct param_list *a, struct param_list *b);
