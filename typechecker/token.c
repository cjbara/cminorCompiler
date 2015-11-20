#include "token.h"
#include "error.h"

const char * token_string(token_t t){
  switch(t){
	case TOKEN_ARRAY: return "ARRAY"; break;
	case TOKEN_BOOLEAN: return "BOOLEAN"; break;
	case TOKEN_CHAR: return "CHARACTER"; break;
	case TOKEN_ELSE: return "ELSE"; break;
	case TOKEN_FALSE: return "FALSE"; break;
	case TOKEN_FOR: return "FOR"; break;
	case TOKEN_FUNCTION: return "FUNCTION"; break;
	case TOKEN_IF: return "IF"; break;
	case TOKEN_INTEGER: return "INTEGER"; break;
	case TOKEN_PRINT: return "PRINT"; break;
	case TOKEN_RETURN: return "RETURN"; break;
	case TOKEN_STRING: return "STRING"; break;
	case TOKEN_TRUE: return "TRUE"; break;
	case TOKEN_VOID: return "VOID"; break;
	case TOKEN_IDENT: return "IDENTIFIER"; break;
	case TOKEN_STRING_LITERAL: return "STRING_LITERAL"; break;
	case TOKEN_INTEGER_LITERAL: return "INTEGER_LITERAL"; break;
	case TOKEN_CHAR_LITERAL: return "CHARACTER_LITERAL"; break;
	case TOKEN_SEMICOLON: return "SEMICOLON"; break;
	case TOKEN_GE: return "GE"; break;
	case TOKEN_LE: return "LE"; break;
	case TOKEN_GT: return "GT"; break;
	case TOKEN_LT: return "LT"; break;
	case TOKEN_EQ: return "EQ"; break;
	case TOKEN_NE: return "NE"; break;
	case TOKEN_POSTFIX_PLUS: return "POSTFIX_PLUS"; break;
	case TOKEN_POSTFIX_MINUS: return "POSTFIX_MINUS"; break;
	case TOKEN_EXPONENT: return "EXPONENT"; break;
	case TOKEN_MULTIPLY: return "MULTIPLY"; break;
	case TOKEN_DIVIDE: return "DIVIDE"; break;
	case TOKEN_MODULUS: return "MODULUS"; break;
	case TOKEN_PLUS: return "PLUS"; break;
	case TOKEN_MINUS: return "MINUS"; break;
	case TOKEN_LOGICAL_AND: return "LOGICAL_AND"; break;
	case TOKEN_LOGICAL_OR: return "LOGICAL_OR"; break;
	case TOKEN_LOGICAL_NOT: return "LOGICAL_NOT"; break;
	case TOKEN_ASSIGNMENT: return "ASSIGNMENT"; break;
	case TOKEN_LPAREN: return "LPAREN"; break;
	case TOKEN_RPAREN: return "RPAREN"; break;
	case TOKEN_LBRACKET: return "LBRACKET"; break;
	case TOKEN_RBRACKET: return "RBRACKET"; break;
	case TOKEN_LCURLY: return "LCURLY"; break;
	case TOKEN_RCURLY: return "RCURLY"; break;
	case TOKEN_COLON: return "COLON"; break;
	case TOKEN_COMMA: return "COMMA"; break;
  }
}
