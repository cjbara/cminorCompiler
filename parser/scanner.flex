/* Scanner for cminor */
%{
/* Needed for token_t type */
#include "parser.tab.h"
#include "globl.h"
%}

%option noyywrap

DIGIT	[0-9]
LETTER	[a-zA-Z]
WS	[\t\n ]
ID	[a-zA-Z_][a-zA-Z0-9_]{0,256}
  
%% 

{WS}+

array 		{ return TOKEN_ARRAY; }
boolean		{ return TOKEN_BOOLEAN; }
char 		{ return TOKEN_CHAR; }
else 		{ return TOKEN_ELSE; }
false 		{ return TOKEN_FALSE; }
for 		{ return TOKEN_FOR; }
function	{ return TOKEN_FUNCTION; }
if 		{ return TOKEN_IF; }
integer 	{ return TOKEN_INTEGER; }
print 		{ return TOKEN_PRINT; }
return 		{ return TOKEN_RETURN; }
string 		{ return TOKEN_STRING; }
true 		{ return TOKEN_TRUE; }
void 		{ return TOKEN_VOID; }

\"(\\.|[^\"\n])*\" {return TOKEN_STRING_LITERAL; }
\'([^\\]|\\.)\'	{ return TOKEN_CHAR_LITERAL; }
{DIGIT}+	{ return TOKEN_INTEGER_LITERAL; }

;		{ return TOKEN_SEMICOLON; }

\>\=		{ return TOKEN_GE; }
\<\=		{ return TOKEN_LE; }
\>		{ return TOKEN_GT; }
\<		{ return TOKEN_LT; }
\=\=		{ return TOKEN_EQ; }
\!\=		{ return TOKEN_NE; }

\+\+		{ return TOKEN_POSTFIX_PLUS; }
\-\-		{ return TOKEN_POSTFIX_MINUS; }
\^		{ return TOKEN_EXPONENT; }
\*		{ return TOKEN_MULTIPLY; }
\/		{ return TOKEN_DIVIDE; }
%		{ return TOKEN_MODULUS; }
\+		{ return TOKEN_PLUS; }
\-		{ return TOKEN_MINUS; }

&&		{ return TOKEN_LOGICAL_AND; }
\|\|		{ return TOKEN_LOGICAL_OR; }
\!		{ return TOKEN_LOGICAL_NOT; }
\=		{ return TOKEN_ASSIGNMENT; }

\(		{ return TOKEN_LPAREN; }
\)		{ return TOKEN_RPAREN; }
\[		{ return TOKEN_LBRACKET; }
\]		{ return TOKEN_RBRACKET; }
\{		{ return TOKEN_LCURLY; }
\}		{ return TOKEN_RCURLY; }

,		{ return TOKEN_COMMA; }
:		{ return TOKEN_COLON; }
\/\/.*		{ /*Comment, do nothing*/ }
\/\*([^\*]|[\r\n]|(\*+([^\*\/]|[\r\n])))*\*+\/ {
		 /*Comment do nothing*/}

{ID}		{ return TOKEN_IDENT; }
.		{ scan_error(); }

%%

