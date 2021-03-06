enum token {
	TOKEN_ARRAY=1,
	TOKEN_BOOLEAN,
	TOKEN_CHAR,
	TOKEN_ELSE,
	TOKEN_FALSE,
	TOKEN_FOR,
	TOKEN_FUNCTION,
	TOKEN_IF,
	TOKEN_INTEGER,
	TOKEN_PRINT,
	TOKEN_RETURN,
	TOKEN_STRING,
	TOKEN_TRUE,
	TOKEN_VOID,
	TOKEN_IDENT,
	TOKEN_STRING_LITERAL,
	TOKEN_INTEGER_LITERAL,
	TOKEN_CHAR_LITERAL,
	TOKEN_SEMICOLON,
	TOKEN_GE,
	TOKEN_LE,
	TOKEN_GT,
	TOKEN_LT,
	TOKEN_EQ,
	TOKEN_NE,
	TOKEN_POSTFIX_PLUS,
	TOKEN_POSTFIX_MINUS,
	TOKEN_EXPONENT,
	TOKEN_MULTIPLY,
	TOKEN_DIVIDE,
	TOKEN_MODULUS,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_LOGICAL_AND,
	TOKEN_LOGICAL_OR,
	TOKEN_LOGICAL_NOT,
	TOKEN_ASSIGNMENT,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_LBRACKET,
	TOKEN_RBRACKET,
	TOKEN_LCURLY,
	TOKEN_RCURLY,
	TOKEN_COMMA,
	TOKEN_COLON,
};
typedef enum token token_t;

const char * token_string(token_t t);
