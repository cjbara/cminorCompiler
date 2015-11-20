#ifndef SYMBOL_KIND
#define SYMBOL_KIND
typedef enum {
	SCOPE_LOCAL,
	SCOPE_PARAM,
	SCOPE_GLOBAL,
} symbol_kind_t;

#endif

#ifndef SYMBOL
#define SYMBOL
struct symbol {
	symbol_kind_t kind;
	int which;
	struct type *type;
	const char *name;
	int defined;
};
#endif

struct symbol * symbol_create(symbol_kind_t kind, struct type *type, const char *name);
void symbol_print(struct symbol *s);
