typedef enum {
	TYPE_BOOLEAN,
	TYPE_CHARACTER,
	TYPE_INTEGER,
	TYPE_STRING,
	TYPE_ARRAY,
	TYPE_FUNCTION,
	TYPE_VOID
} type_kind_t;

struct type {
	type_kind_t kind;
	struct param_list *params;
	struct type *subtype;
	int number;
};

struct type * type_create(type_kind_t, struct param_list *, struct type *, int);
void type_delete(struct type *);
void type_print(struct type *);

struct type * type_copy(struct type *t);
int type_compare(struct type *a, struct type *b); //returns 1 if same, 0 otherwise

