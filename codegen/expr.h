#include "param_list.h"
#include <stdio.h>

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
	EXPR_BLOCK_COMMA,
	EXPR_COMMA
} expr_t;

struct expr {
	expr_t kind;
	struct expr *left;
	struct expr *right;
	const char *name;
	struct symbol *symbol;
	int reg;
	int literal_value;
	const char *string_literal;
};

struct expr * expr_create(expr_t, struct expr *, struct expr *);
struct expr * expr_create_int_value(int);
struct expr * expr_create_char_value(char);
struct expr * expr_create_bool_value(int);
struct expr * expr_create_string_value(const char *);
struct expr * expr_create_ident(char *);
void expr_delete(struct expr *);
void expr_print(struct expr *);
void expr_pretty_print(struct expr *);

void expr_resolve(struct expr *e);
int expr_is_constant(struct expr *e);
struct type * expr_typecheck(struct expr *e);

int exprs_in_block(struct expr *e);
int array_call_subtypes(struct expr *e);

void function_typecheck(const char *function_name, struct expr *e, struct param_list *p, int param, int func_params);

int function_params(struct expr *e);

void expr_codegen(struct expr *e, FILE *file);
void compare(struct expr *e, FILE *file);
