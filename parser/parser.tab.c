#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20070509

#define YYEMPTY (-1)
#define yyclearin    (yychar = YYEMPTY)
#define yyerrok      (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

extern int yyparse(void);

static int yygrowstack(void);
#define YYPREFIX "yy"
#line 52 "parser.bison"
typedef union {
	struct decl *decl;
	struct param_list *param_list;
	struct stmt *stmt;
	struct expr *expr;
	struct type *type;
} YYSTYPE;
#line 67 "parser.bison"
  #include <stdio.h>
  #include <math.h>
  #include "globl.h"

/* Include all of the prototypes for the structs */
  #include "decl.h"
  #include "stmt.h"
  #include "param_list.h"
  #include "expr.h"
  #include "type.h"

/* declare these for use in the parser */
  extern int yyerror( char *str );

/* initialize the global struct decl * variable for use in main */
  struct decl *parse_result = 0;

#line 49 "parser.tab.c"
#define TOKEN_ARRAY 257
#define TOKEN_BOOLEAN 258
#define TOKEN_CHAR 259
#define TOKEN_ELSE 260
#define TOKEN_FALSE 261
#define TOKEN_FOR 262
#define TOKEN_FUNCTION 263
#define TOKEN_IF 264
#define TOKEN_INTEGER 265
#define TOKEN_PRINT 266
#define TOKEN_RETURN 267
#define TOKEN_STRING 268
#define TOKEN_TRUE 269
#define TOKEN_VOID 270
#define TOKEN_IDENT 271
#define TOKEN_STRING_LITERAL 272
#define TOKEN_INTEGER_LITERAL 273
#define TOKEN_CHAR_LITERAL 274
#define TOKEN_SEMICOLON 275
#define TOKEN_GE 276
#define TOKEN_LE 277
#define TOKEN_GT 278
#define TOKEN_LT 279
#define TOKEN_EQ 280
#define TOKEN_NE 281
#define TOKEN_POSTFIX_PLUS 282
#define TOKEN_POSTFIX_MINUS 283
#define TOKEN_EXPONENT 284
#define TOKEN_MULTIPLY 285
#define TOKEN_DIVIDE 286
#define TOKEN_MODULUS 287
#define TOKEN_PLUS 288
#define TOKEN_MINUS 289
#define TOKEN_LOGICAL_AND 290
#define TOKEN_LOGICAL_OR 291
#define TOKEN_LOGICAL_NOT 292
#define TOKEN_ASSIGNMENT 293
#define TOKEN_LPAREN 294
#define TOKEN_RPAREN 295
#define TOKEN_LBRACKET 296
#define TOKEN_RBRACKET 297
#define TOKEN_LCURLY 298
#define TOKEN_RCURLY 299
#define TOKEN_COMMA 300
#define TOKEN_COLON 301
#define TOKEN_ERROR 302
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    1,    1,    2,    2,    2,    2,    3,    3,    3,
    4,    4,    4,    4,    4,    5,    6,   11,   11,   12,
   12,   13,    8,    8,    7,    7,    9,    9,    9,    9,
    9,    9,    9,   10,   10,   14,   14,   15,   15,   16,
   16,   17,   18,   18,   19,   19,   19,   20,   20,   20,
   20,   20,   20,   20,   21,   21,   21,   22,   22,   22,
   22,   23,   23,   24,   24,   24,   25,   25,   25,   26,
   26,   26,   26,   26,   26,   26,   26,   26,   30,   27,
   28,   29,
};
short yylen[] = {                                         2,
    1,    2,    0,    4,    6,    7,    8,    1,    1,    1,
    1,    1,    1,    1,    1,    5,    5,    0,    1,    1,
    3,    3,    0,    2,    1,    1,    1,    7,    2,    3,
    3,    3,    9,    5,    7,    0,    1,    0,    1,    1,
    3,    1,    3,    1,    3,    3,    1,    3,    3,    3,
    3,    3,    3,    1,    3,    3,    1,    3,    3,    3,
    1,    3,    1,    2,    2,    1,    2,    2,    1,    1,
    1,    1,    1,    1,    1,    3,    4,    4,    1,    1,
    1,    1,
};
short yydefred[] = {                                      0,
   79,    0,    1,    0,    0,    2,    0,    0,   14,   13,
    0,   12,   11,   15,    0,    0,    0,    0,    0,    0,
    8,    9,   10,    4,    0,    0,    0,   75,   74,   81,
   80,   82,    0,    0,    0,    0,   37,    0,    0,    0,
    0,    0,    0,   63,    0,   69,   71,   72,   73,    0,
    0,    0,    0,    0,   64,   65,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   67,   68,    0,    0,    0,   19,    0,
    0,    5,    0,   39,    0,    0,    0,    0,    0,    0,
   27,    0,    0,   25,   26,    0,    0,   76,   16,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   62,    0,    0,   17,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   24,    6,   29,   77,
   78,   21,   22,    7,   41,    0,    0,   32,   31,   30,
    0,    0,    0,   34,    0,    0,    0,    0,   28,   35,
    0,    0,   33,    0,    0,    0,    0,    0,
};
short yydgoto[] = {                                       2,
    3,   91,   15,   21,   22,   23,   92,   93,   94,   95,
   78,   79,   80,   36,   83,   84,   96,   38,   39,   40,
   41,   42,   43,   44,   45,   46,   47,   48,   49,   50,
};
short yysindex[] = {                                   -268,
    0,    0,    0, -268, -290,    0,  378, -275,    0,    0,
  378,    0,    0,    0, -243, -247, -242, -233, -230, -231,
    0,    0,    0,    0, -230, -226, -224,    0,    0,    0,
    0,    0, -230, -230, -230, -229,    0, -217, -185,   76,
 -175, -220, -205,    0, -138,    0,    0,    0,    0, -282,
 -268, -192, -230, -244,    0,    0, -209,  378, -230, -230,
 -230, -230, -230, -230, -230, -230, -230, -230, -230, -230,
 -230, -230, -230,    0,    0, -230, -230, -207,    0, -202,
 -200,    0, -190,    0, -193, -176, -174, -230, -230, -244,
    0, -244, -170,    0,    0, -150, -261,    0,    0, -185,
   76,   76, -175, -175, -175, -175, -175, -175, -220, -220,
 -205, -205, -205,    0, -164, -160,    0, -268,  378, -136,
 -230, -230, -230, -133, -128, -145,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -103, -118,    0,    0,    0,
 -230, -244,  -93,    0,  -76, -230, -244, -110,    0,    0,
 -177, -108,    0, -230,  -89, -177,  -52, -177,
};
short yyrindex[] = {                                    210,
    0,    0,    0,  210,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -63,  -53,  -43,  -74,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  161, -222, -167,
  148,   70,  -34,    0,  -60,    0,    0,    0,    0,  -86,
  -61,    0,  -51,  -50,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -59,  -47,    0,    0,  -57,
    0,    0,    0,    0, -129,    0,    0,  -17,  -15,  -50,
    0,  -50,    0,    0,    0,    0,  341,    0,    0, -159,
 -126,  315,  174,  200,  226,  252,  278,  304,   96,  122,
   -8,   18,   44,    0,    0,    0,    0,    0,    0,    0,
    0,  -15,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -15,    0,    0,    0, -111,  -33,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
  260,    9,   -9,  267,  268,  269,  142,  -54, -132,  139,
    0,  170,    0,  -85,   23,  169,  -19,    0,  241,  115,
  316,  111,   10,  -26,    0,    0,    0,    0,    0,    1,
};
#define YYTABLESIZE 648
short yytable[] = {                                      37,
    5,   20,    1,  125,    5,   52,   55,   56,    4,  145,
    7,   76,    4,   77,  149,   57,   28,   86,  153,   87,
   19,   88,   89,  157,   29,  149,    1,   30,   31,   32,
   28,   24,   76,   85,   77,  126,  136,  127,   29,    7,
    1,   30,   31,   32,   33,   25,  114,   34,   99,   35,
   26,   81,   44,   90,   97,  143,   85,   85,   33,   27,
  148,   34,   51,   35,   70,   71,   72,   58,   85,   37,
   44,   53,   44,   54,   44,   59,   44,   44,   73,  111,
  112,  113,   82,   28,   86,   98,  152,  117,   88,   89,
   97,   29,   97,    1,   30,   31,   32,  118,  115,  116,
  119,   85,   37,  137,   60,   61,  121,   47,  120,  133,
  124,   33,   68,   69,   34,   43,   35,  122,   81,  123,
   90,   37,   47,   47,  129,   47,   37,   47,  128,   47,
  130,   47,   47,   43,  155,   43,  131,   43,  134,   43,
   43,  138,   97,   74,   75,   40,  139,   97,   45,   25,
   25,   97,   25,  140,   25,   25,   97,   25,   97,   25,
   25,   25,   25,   45,   45,   40,   45,   40,   45,   40,
   45,  141,   45,   45,  101,  102,  142,   25,  109,  110,
   25,  146,   25,  147,  151,  154,   25,   25,   70,   70,
   70,   70,   70,   70,   70,   70,   70,   70,   70,   70,
   70,   70,   70,   70,   70,  156,   70,  158,   70,    3,
   70,    8,   70,   70,   66,   66,   66,   66,   66,   66,
   66,    9,   36,   66,   66,   66,   66,   66,   66,   66,
   66,   10,   66,   18,   66,   38,   66,   20,   66,   66,
   61,   61,   61,   61,   61,   61,   61,   38,   23,   38,
   61,   61,   61,   61,   61,   61,   61,   38,   61,   36,
   61,   36,   61,    6,   61,   61,   58,   58,   58,   58,
   58,   58,   58,   16,   17,   18,   58,   58,   58,   58,
   58,   58,   58,  144,   58,  150,   58,  132,   58,  135,
   58,   58,   59,   59,   59,   59,   59,   59,   59,  100,
    0,    0,   59,   59,   59,   59,   59,   59,   59,    0,
   59,    0,   59,    0,   59,    0,   59,   59,   60,   60,
   60,   60,   60,   60,   60,    0,    0,    0,   60,   60,
   60,   60,   60,   60,   60,    0,   60,    0,   60,    0,
   60,    0,   60,   60,   57,   57,   57,   57,   57,   57,
   57,   62,   63,   64,   65,   66,   67,   57,   57,   57,
   57,    0,   57,    0,   57,    0,   57,    0,   57,   57,
   55,   55,   55,   55,   55,   55,   55,  103,  104,  105,
  106,  107,  108,   55,   55,   55,   55,    0,   55,    0,
   55,    0,   55,    0,   55,   55,   56,   56,   56,   56,
   56,   56,   56,    0,    0,    0,    0,    0,    0,   56,
   56,   56,   56,    0,   56,    0,   56,    0,   56,    0,
   56,   56,   54,   54,   54,   54,   54,   54,   54,    0,
    0,    0,    0,    0,    0,   42,    0,   54,   54,    0,
   54,    0,   54,    0,   54,    0,   54,   54,   48,   48,
   48,   48,   48,   48,   48,   42,    0,   42,    0,   42,
   42,    0,    0,   48,   48,    0,   48,    0,   48,    0,
   48,    0,   48,   48,   49,   49,   49,   49,   49,   49,
   49,    0,    0,    0,    0,    0,    0,    0,    0,   49,
   49,    0,   49,    0,   49,    0,   49,    0,   49,   49,
   50,   50,   50,   50,   50,   50,   50,    0,    0,    0,
    0,    0,    0,    0,    0,   50,   50,    0,   50,    0,
   50,    0,   50,    0,   50,   50,   51,   51,   51,   51,
   51,   51,   51,    0,    0,    0,    0,    0,    0,    0,
    0,   51,   51,    0,   51,    0,   51,    0,   51,    0,
   51,   51,   52,   52,   52,   52,   52,   52,   52,    0,
    0,    0,    0,    0,    0,    0,    0,   52,   52,    0,
   52,    0,   52,    0,   52,    0,   52,   52,   53,   53,
   53,   53,   53,   53,   53,    0,    0,    0,    0,   46,
    0,    0,    0,   53,   53,    0,   53,    0,   53,    0,
   53,    0,   53,   53,   46,   46,    0,   46,    0,   46,
    0,   46,    0,   46,   46,   70,   70,   70,   70,   70,
   70,   70,   70,   70,   70,   70,   70,   70,   70,   70,
   70,   70,    0,   70,    8,    9,   10,    0,    0,    0,
   11,    0,   12,    0,    0,   13,    0,   14,
};
short yycheck[] = {                                      19,
    0,   11,  271,   89,    4,   25,   33,   34,    0,  142,
  301,  294,    4,  296,  147,   35,  261,  262,  151,  264,
  296,  266,  267,  156,  269,  158,  271,  272,  273,  274,
  261,  275,  294,   53,  296,   90,  122,   92,  269,  301,
  271,  272,  273,  274,  289,  293,   73,  292,   58,  294,
  293,   51,  275,  298,   54,  141,   76,   77,  289,  293,
  146,  292,  294,  294,  285,  286,  287,  297,   88,   89,
  293,  298,  295,  298,  297,  293,  299,  300,  284,   70,
   71,   72,  275,  261,  262,  295,  264,  295,  266,  267,
   90,  269,   92,  271,  272,  273,  274,  300,   76,   77,
  301,  121,  122,  123,  290,  291,  300,  275,  299,  119,
   88,  289,  288,  289,  292,  275,  294,  294,  118,  294,
  298,  141,  290,  291,  275,  293,  146,  295,  299,  297,
  295,  299,  300,  293,  154,  295,  297,  297,  275,  299,
  300,  275,  142,  282,  283,  275,  275,  147,  275,  261,
  262,  151,  264,  299,  266,  267,  156,  269,  158,  271,
  272,  273,  274,  290,  291,  295,  293,  297,  295,  299,
  297,  275,  299,  300,   60,   61,  295,  289,   68,   69,
  292,  275,  294,  260,  295,  294,  298,  299,  275,  276,
  277,  278,  279,  280,  281,  282,  283,  284,  285,  286,
  287,  288,  289,  290,  291,  295,  293,  260,  295,    0,
  297,  275,  299,  300,  275,  276,  277,  278,  279,  280,
  281,  275,  297,  284,  285,  286,  287,  288,  289,  290,
  291,  275,  293,  295,  295,  295,  297,  295,  299,  300,
  275,  276,  277,  278,  279,  280,  281,  299,  299,  297,
  285,  286,  287,  288,  289,  290,  291,  275,  293,  275,
  295,  295,  297,    4,  299,  300,  275,  276,  277,  278,
  279,  280,  281,    7,    7,    7,  285,  286,  287,  288,
  289,  290,  291,  142,  293,  147,  295,  118,  297,  121,
  299,  300,  275,  276,  277,  278,  279,  280,  281,   59,
   -1,   -1,  285,  286,  287,  288,  289,  290,  291,   -1,
  293,   -1,  295,   -1,  297,   -1,  299,  300,  275,  276,
  277,  278,  279,  280,  281,   -1,   -1,   -1,  285,  286,
  287,  288,  289,  290,  291,   -1,  293,   -1,  295,   -1,
  297,   -1,  299,  300,  275,  276,  277,  278,  279,  280,
  281,  276,  277,  278,  279,  280,  281,  288,  289,  290,
  291,   -1,  293,   -1,  295,   -1,  297,   -1,  299,  300,
  275,  276,  277,  278,  279,  280,  281,   62,   63,   64,
   65,   66,   67,  288,  289,  290,  291,   -1,  293,   -1,
  295,   -1,  297,   -1,  299,  300,  275,  276,  277,  278,
  279,  280,  281,   -1,   -1,   -1,   -1,   -1,   -1,  288,
  289,  290,  291,   -1,  293,   -1,  295,   -1,  297,   -1,
  299,  300,  275,  276,  277,  278,  279,  280,  281,   -1,
   -1,   -1,   -1,   -1,   -1,  275,   -1,  290,  291,   -1,
  293,   -1,  295,   -1,  297,   -1,  299,  300,  275,  276,
  277,  278,  279,  280,  281,  295,   -1,  297,   -1,  299,
  300,   -1,   -1,  290,  291,   -1,  293,   -1,  295,   -1,
  297,   -1,  299,  300,  275,  276,  277,  278,  279,  280,
  281,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  290,
  291,   -1,  293,   -1,  295,   -1,  297,   -1,  299,  300,
  275,  276,  277,  278,  279,  280,  281,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  290,  291,   -1,  293,   -1,
  295,   -1,  297,   -1,  299,  300,  275,  276,  277,  278,
  279,  280,  281,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  290,  291,   -1,  293,   -1,  295,   -1,  297,   -1,
  299,  300,  275,  276,  277,  278,  279,  280,  281,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  290,  291,   -1,
  293,   -1,  295,   -1,  297,   -1,  299,  300,  275,  276,
  277,  278,  279,  280,  281,   -1,   -1,   -1,   -1,  275,
   -1,   -1,   -1,  290,  291,   -1,  293,   -1,  295,   -1,
  297,   -1,  299,  300,  290,  291,   -1,  293,   -1,  295,
   -1,  297,   -1,  299,  300,  275,  276,  277,  278,  279,
  280,  281,  282,  283,  284,  285,  286,  287,  288,  289,
  290,  291,   -1,  293,  257,  258,  259,   -1,   -1,   -1,
  263,   -1,  265,   -1,   -1,  268,   -1,  270,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 302
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"TOKEN_ARRAY","TOKEN_BOOLEAN",
"TOKEN_CHAR","TOKEN_ELSE","TOKEN_FALSE","TOKEN_FOR","TOKEN_FUNCTION","TOKEN_IF",
"TOKEN_INTEGER","TOKEN_PRINT","TOKEN_RETURN","TOKEN_STRING","TOKEN_TRUE",
"TOKEN_VOID","TOKEN_IDENT","TOKEN_STRING_LITERAL","TOKEN_INTEGER_LITERAL",
"TOKEN_CHAR_LITERAL","TOKEN_SEMICOLON","TOKEN_GE","TOKEN_LE","TOKEN_GT",
"TOKEN_LT","TOKEN_EQ","TOKEN_NE","TOKEN_POSTFIX_PLUS","TOKEN_POSTFIX_MINUS",
"TOKEN_EXPONENT","TOKEN_MULTIPLY","TOKEN_DIVIDE","TOKEN_MODULUS","TOKEN_PLUS",
"TOKEN_MINUS","TOKEN_LOGICAL_AND","TOKEN_LOGICAL_OR","TOKEN_LOGICAL_NOT",
"TOKEN_ASSIGNMENT","TOKEN_LPAREN","TOKEN_RPAREN","TOKEN_LBRACKET",
"TOKEN_RBRACKET","TOKEN_LCURLY","TOKEN_RCURLY","TOKEN_COMMA","TOKEN_COLON",
"TOKEN_ERROR",
};
char *yyrule[] = {
"$accept : program",
"program : decl_list",
"decl_list : decl decl_list",
"decl_list :",
"decl : ident TOKEN_COLON type TOKEN_SEMICOLON",
"decl : ident TOKEN_COLON type_basic TOKEN_ASSIGNMENT expr TOKEN_SEMICOLON",
"decl : ident TOKEN_COLON type_function TOKEN_ASSIGNMENT TOKEN_LCURLY stmt_list TOKEN_RCURLY",
"decl : ident TOKEN_COLON type_array TOKEN_ASSIGNMENT TOKEN_LCURLY expr_list TOKEN_RCURLY TOKEN_SEMICOLON",
"type : type_basic",
"type : type_array",
"type : type_function",
"type_basic : TOKEN_STRING",
"type_basic : TOKEN_INTEGER",
"type_basic : TOKEN_CHAR",
"type_basic : TOKEN_BOOLEAN",
"type_basic : TOKEN_VOID",
"type_array : TOKEN_ARRAY TOKEN_LBRACKET opt_expr TOKEN_RBRACKET type",
"type_function : TOKEN_FUNCTION type TOKEN_LPAREN param_list TOKEN_RPAREN",
"param_list :",
"param_list : non_empty_param_list",
"non_empty_param_list : param",
"non_empty_param_list : param TOKEN_COMMA non_empty_param_list",
"param : ident TOKEN_COLON type",
"stmt_list :",
"stmt_list : stmt stmt_list",
"stmt : matched",
"stmt : unmatched",
"matched : decl",
"matched : TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN matched TOKEN_ELSE matched",
"matched : expr TOKEN_SEMICOLON",
"matched : TOKEN_LCURLY stmt_list TOKEN_RCURLY",
"matched : TOKEN_RETURN opt_expr TOKEN_SEMICOLON",
"matched : TOKEN_PRINT expr_list TOKEN_SEMICOLON",
"matched : TOKEN_FOR TOKEN_LPAREN opt_expr TOKEN_SEMICOLON opt_expr TOKEN_SEMICOLON opt_expr TOKEN_RPAREN matched",
"unmatched : TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN stmt",
"unmatched : TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN matched TOKEN_ELSE unmatched",
"opt_expr :",
"opt_expr : expr",
"expr_list :",
"expr_list : non_empty_expr_list",
"non_empty_expr_list : expr",
"non_empty_expr_list : expr TOKEN_COMMA non_empty_expr_list",
"expr : assignment_expr",
"assignment_expr : assignment_expr TOKEN_ASSIGNMENT logical_expr",
"assignment_expr : logical_expr",
"logical_expr : logical_expr TOKEN_LOGICAL_AND comparison_expr",
"logical_expr : logical_expr TOKEN_LOGICAL_OR comparison_expr",
"logical_expr : comparison_expr",
"comparison_expr : comparison_expr TOKEN_GE add_expr",
"comparison_expr : comparison_expr TOKEN_LE add_expr",
"comparison_expr : comparison_expr TOKEN_GT add_expr",
"comparison_expr : comparison_expr TOKEN_LT add_expr",
"comparison_expr : comparison_expr TOKEN_EQ add_expr",
"comparison_expr : comparison_expr TOKEN_NE add_expr",
"comparison_expr : add_expr",
"add_expr : add_expr TOKEN_PLUS mult_expr",
"add_expr : add_expr TOKEN_MINUS mult_expr",
"add_expr : mult_expr",
"mult_expr : mult_expr TOKEN_MULTIPLY exponent",
"mult_expr : mult_expr TOKEN_DIVIDE exponent",
"mult_expr : mult_expr TOKEN_MODULUS exponent",
"mult_expr : exponent",
"exponent : exponent TOKEN_EXPONENT factor",
"exponent : factor",
"factor : TOKEN_MINUS factor",
"factor : TOKEN_LOGICAL_NOT factor",
"factor : pre_post_incr",
"pre_post_incr : pre_post_incr TOKEN_POSTFIX_PLUS",
"pre_post_incr : pre_post_incr TOKEN_POSTFIX_MINUS",
"pre_post_incr : primary_expr",
"primary_expr : ident",
"primary_expr : integer",
"primary_expr : string",
"primary_expr : char",
"primary_expr : TOKEN_TRUE",
"primary_expr : TOKEN_FALSE",
"primary_expr : TOKEN_LPAREN expr TOKEN_RPAREN",
"primary_expr : ident TOKEN_LPAREN expr_list TOKEN_RPAREN",
"primary_expr : ident TOKEN_LBRACKET expr_list TOKEN_RBRACKET",
"ident : TOKEN_IDENT",
"integer : TOKEN_INTEGER_LITERAL",
"string : TOKEN_STRING_LITERAL",
"char : TOKEN_CHAR_LITERAL",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static int      yystacksize;
#line 329 "parser.bison"

int yyerror( char *str )
{
	printf("parse error: %s\n",str);
	return 1;
}
#line 469 "parser.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

#ifdef lint
    goto yyerrlab;
#endif

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 89 "parser.bison"
{ parse_result = yyvsp[0].decl; return 0; }
break;
case 2:
#line 93 "parser.bison"
{ yyvsp[-1].decl->next = yyvsp[0].decl;
		  yyval.decl = yyvsp[-1].decl; }
break;
case 3:
#line 96 "parser.bison"
{ yyval.decl = 0; }
break;
case 4:
#line 100 "parser.bison"
{ yyval.decl = decl_create(yyvsp[-3].expr->name, yyvsp[-1].type, 0, 0); }
break;
case 5:
#line 102 "parser.bison"
{ yyval.decl = decl_create(yyvsp[-5].expr->name, yyvsp[-3].type, yyvsp[-1].expr, 0); }
break;
case 6:
#line 104 "parser.bison"
{ yyval.decl = decl_create(yyvsp[-6].expr->name, yyvsp[-4].type, 0, yyvsp[-1].stmt); }
break;
case 7:
#line 106 "parser.bison"
{ yyval.decl = decl_create(yyvsp[-7].expr->name, yyvsp[-5].type, expr_create(EXPR_BLOCK, 0, yyvsp[-2].expr), 0); }
break;
case 8:
#line 110 "parser.bison"
{ yyval.type = yyvsp[0].type; }
break;
case 9:
#line 112 "parser.bison"
{ yyval.type = yyvsp[0].type; }
break;
case 10:
#line 114 "parser.bison"
{ yyval.type = yyvsp[0].type; }
break;
case 11:
#line 118 "parser.bison"
{ yyval.type = type_create(TYPE_STRING, 0, 0, 0); }
break;
case 12:
#line 120 "parser.bison"
{ yyval.type = type_create(TYPE_INTEGER, 0, 0, 0); }
break;
case 13:
#line 122 "parser.bison"
{ yyval.type = type_create(TYPE_CHARACTER, 0, 0, 0); }
break;
case 14:
#line 124 "parser.bison"
{ yyval.type = type_create(TYPE_BOOLEAN, 0, 0, 0); }
break;
case 15:
#line 126 "parser.bison"
{ yyval.type = type_create(TYPE_VOID, 0, 0, 0); }
break;
case 16:
#line 130 "parser.bison"
{ yyval.type = type_create(TYPE_ARRAY, 0, yyvsp[0].type, yyvsp[-2].expr); }
break;
case 17:
#line 134 "parser.bison"
{ yyval.type = type_create(TYPE_FUNCTION, yyvsp[-1].param_list, yyvsp[-3].type, 0); }
break;
case 18:
#line 138 "parser.bison"
{ yyval.param_list = 0; }
break;
case 19:
#line 140 "parser.bison"
{ yyval.param_list = yyvsp[0].param_list; }
break;
case 20:
#line 144 "parser.bison"
{ yyval.param_list = yyvsp[0].param_list; }
break;
case 21:
#line 146 "parser.bison"
{ yyvsp[-2].param_list->next = yyvsp[0].param_list;
		  yyval.param_list = yyvsp[-2].param_list; }
break;
case 22:
#line 151 "parser.bison"
{ yyval.param_list = param_list_create(yyvsp[-2].expr->name, yyvsp[0].type); }
break;
case 23:
#line 155 "parser.bison"
{ yyval.stmt = 0; }
break;
case 24:
#line 157 "parser.bison"
{ yyvsp[-1].stmt->next = yyvsp[0].stmt;
		  yyval.stmt = yyvsp[-1].stmt; }
break;
case 25:
#line 162 "parser.bison"
{ yyval.stmt = yyvsp[0].stmt; }
break;
case 26:
#line 164 "parser.bison"
{ yyval.stmt = yyvsp[0].stmt; }
break;
case 27:
#line 168 "parser.bison"
{ yyval.stmt = stmt_create(STMT_DECL, yyvsp[0].decl, 0, 0, 0, 0, 0); }
break;
case 28:
#line 170 "parser.bison"
{ yyval.stmt = stmt_create(STMT_IF_ELSE, 0, 0, yyvsp[-4].expr, 0, yyvsp[-2].stmt, yyvsp[0].stmt); }
break;
case 29:
#line 172 "parser.bison"
{ yyval.stmt = stmt_create(STMT_EXPR, 0, 0, yyvsp[-1].expr, 0, 0, 0); }
break;
case 30:
#line 174 "parser.bison"
{ yyval.stmt = stmt_create(STMT_BLOCK, 0, 0, 0, 0, yyvsp[-1].stmt, 0); }
break;
case 31:
#line 176 "parser.bison"
{ yyval.stmt = stmt_create(STMT_RETURN, 0, 0, yyvsp[-1].expr, 0, 0, 0); }
break;
case 32:
#line 178 "parser.bison"
{ yyval.stmt = stmt_create(STMT_PRINT, 0, 0, yyvsp[-1].expr, 0, 0, 0); }
break;
case 33:
#line 180 "parser.bison"
{ yyval.stmt = stmt_create(STMT_FOR, 0, yyvsp[-6].expr, yyvsp[-4].expr, yyvsp[-2].expr, yyvsp[0].stmt, 0); }
break;
case 34:
#line 184 "parser.bison"
{ yyval.stmt = stmt_create(STMT_IF_ELSE, 0, 0, yyvsp[-2].expr, 0, yyvsp[0].stmt, 0); }
break;
case 35:
#line 186 "parser.bison"
{ yyval.stmt = stmt_create(STMT_IF_ELSE, 0, 0, yyvsp[-4].expr, 0, yyvsp[-2].stmt, yyvsp[0].stmt); }
break;
case 36:
#line 190 "parser.bison"
{ yyval.expr = 0; }
break;
case 37:
#line 192 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 38:
#line 196 "parser.bison"
{ yyval.expr = 0; }
break;
case 39:
#line 198 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 40:
#line 202 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 41:
#line 204 "parser.bison"
{ yyval.expr = expr_create(EXPR_COMMA, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 42:
#line 208 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 43:
#line 212 "parser.bison"
{ yyval.expr = expr_create(EXPR_ASSIGNMENT, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 44:
#line 214 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 45:
#line 218 "parser.bison"
{ yyval.expr = expr_create(EXPR_LOGICAL_AND, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 46:
#line 220 "parser.bison"
{ yyval.expr = expr_create(EXPR_LOGICAL_OR, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 47:
#line 222 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 48:
#line 226 "parser.bison"
{ yyval.expr = expr_create(EXPR_GE, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 49:
#line 228 "parser.bison"
{ yyval.expr = expr_create(EXPR_LE, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 50:
#line 230 "parser.bison"
{ yyval.expr = expr_create(EXPR_GT, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 51:
#line 232 "parser.bison"
{ yyval.expr = expr_create(EXPR_LT, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 52:
#line 234 "parser.bison"
{ yyval.expr = expr_create(EXPR_EQ, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 53:
#line 236 "parser.bison"
{ yyval.expr = expr_create(EXPR_NE, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 54:
#line 238 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 55:
#line 242 "parser.bison"
{ yyval.expr = expr_create(EXPR_ADD, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 56:
#line 244 "parser.bison"
{ yyval.expr = expr_create(EXPR_SUB, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 57:
#line 246 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 58:
#line 250 "parser.bison"
{ yyval.expr = expr_create(EXPR_MUL, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 59:
#line 252 "parser.bison"
{ yyval.expr = expr_create(EXPR_DIV, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 60:
#line 254 "parser.bison"
{ yyval.expr = expr_create(EXPR_MOD, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 61:
#line 256 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 62:
#line 260 "parser.bison"
{ yyval.expr = expr_create(EXPR_POW, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 63:
#line 262 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 64:
#line 266 "parser.bison"
{ yyval.expr = expr_create(EXPR_SUB, 0, yyvsp[0].expr); }
break;
case 65:
#line 268 "parser.bison"
{ yyval.expr = expr_create(EXPR_LOGICAL_NOT, 0, yyvsp[0].expr); }
break;
case 66:
#line 270 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 67:
#line 274 "parser.bison"
{ yyval.expr = expr_create(EXPR_POSTFIX_PLUS, yyvsp[-1].expr, 0); }
break;
case 68:
#line 276 "parser.bison"
{ yyval.expr = expr_create(EXPR_POSTFIX_MINUS, yyvsp[-1].expr, 0); }
break;
case 69:
#line 278 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 70:
#line 282 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 71:
#line 284 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 72:
#line 286 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 73:
#line 288 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 74:
#line 290 "parser.bison"
{ yyval.expr = expr_create(EXPR_TRUE, 0, 0); }
break;
case 75:
#line 292 "parser.bison"
{ yyval.expr = expr_create(EXPR_FALSE, 0, 0); }
break;
case 76:
#line 294 "parser.bison"
{ yyval.expr = expr_create(EXPR_PARENS, 0, yyvsp[-1].expr); }
break;
case 77:
#line 296 "parser.bison"
{ yyval.expr = expr_create(EXPR_FCALL, yyvsp[-3].expr, yyvsp[-1].expr); }
break;
case 78:
#line 298 "parser.bison"
{ yyval.expr = expr_create(EXPR_ARRINDEX, yyvsp[-3].expr, yyvsp[-1].expr); }
break;
case 79:
#line 302 "parser.bison"
{ char *c;
		  c = (char *)malloc(strlen(yytext)); 
		  strcpy(c, yytext);
		  yyval.expr = expr_create_ident(c); }
break;
case 80:
#line 309 "parser.bison"
{ int i = atof(yytext);
		  yyval.expr = expr_create_int_value(i); }
break;
case 81:
#line 314 "parser.bison"
{ char *c;
		  c = (char *)malloc(strlen(yytext)); 
		  strcpy(c, yytext+1);
		  int i;
		  for(i=0; c[i]!='\0'; i++);
		  c[i-1]='\0';
		  yyval.expr = expr_create_string_value(c); }
break;
case 82:
#line 324 "parser.bison"
{ char c = yytext[1]; 
		  yyval.expr = expr_create_char_value(c); }
break;
#line 992 "parser.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
