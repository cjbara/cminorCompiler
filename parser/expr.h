typedef enum {
	EXPR_ASSIGNMENT,
	EXPR_GE,
	EXPR_LE,
	EXPR_GT,
	EXPR_LT,
	EXPR_EQ,
	EXPR_NE,
	EXPR_ADD,
	EXPR_SUB,
	EXPR_MUL,
	EXPR_DIV,
	EXPR_MOD,
	EXPR_POW,
	EXPR_LOGICAL_NOT,
	EXPR_LOGICAL_AND,
	EXPR_LOGICAL_OR,
	EXPR_POSTFIX_PLUS,
	EXPR_POSTFIX_MINUS,
	EXPR_IDENT,
	EXPR_INTEGER_LITERAL,
	EXPR_STRING_LITERAL,
	EXPR_CHAR_LITERAL,
	EXPR_TRUE,
	EXPR_FALSE,
	EXPR_FCALL,
	EXPR_ARRCALL,
	EXPR_ARRINDEX,
	EXPR_PARENS,
	EXPR_BLOCK,
	EXPR_COMMA,
	EXPR_LIST
} expr_t;

struct expr {
	expr_t kind;
	struct expr *left;
	struct expr *right;
	char *name;
	struct symbol *symbol;
	int literal_value;
	char *string_literal;
};

struct expr * expr_create(expr_t, struct expr *, struct expr *);
struct expr * expr_create_int_value(int);
struct expr * expr_create_char_value(char);
struct expr * expr_create_string_value(char *);
struct expr * expr_create_ident(char *);
void expr_delete(struct expr *);
void expr_print(struct expr *);
void expr_pretty_print(struct expr *);
