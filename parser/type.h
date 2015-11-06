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
	struct expr *number;
};

struct type * type_create(type_kind_t, struct param_list *, struct type *, struct expr *);
void type_delete(struct type *);
void type_print(struct type *);
void type_pretty_print(struct type *);
