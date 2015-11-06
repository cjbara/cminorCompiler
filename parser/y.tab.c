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
#line 4 "parser.bison"
  #include <stdio.h>
  #include <math.h>
#line 26 "y.tab.c"
#define TOKEN_ASSIGNEMENT 257
#define TOKEN_SEMICOLON 258
#define TOKEN_LCURLY 259
#define TOKEN_RCURLY 260
#define TOKEN_STRING 261
#define TOKEN_INTEGER 262
#define TOKEN_CHAR 263
#define TOKEN_BOOLEAN 264
#define TOKEN_ARRAY 265
#define TOKEN_LBRACKET 266
#define TOKEN_RBRACKET 267
#define TOKEN_FUNCTION 268
#define TOKEN_LPAREN 269
#define TOKEN_RPAREN 270
#define TOKEN 271
#define VOID 272
#define TOKEN_IDENT 273
#define TOKEN_COLON 274
#define TOKEN_PLUS 275
#define TOKEN_MINUS 276
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    1,    1,    2,    2,    2,    6,    6,    6,    6,
    6,    6,    6,    7,    7,    3,    5,    5,    8,    8,
    8,    4,    4,    4,
};
short yylen[] = {                                         2,
    1,    2,    0,    4,    2,    6,    1,    1,    1,    1,
    5,    5,    2,    0,    2,    3,    0,    2,    1,    2,
    0,    3,    3,    0,
};
short yydefred[] = {                                      3,
    0,    0,    0,    2,    0,    0,    0,    5,    7,    8,
    9,   10,    0,    0,    0,   16,   17,    0,   24,    0,
   13,    0,    4,   24,   24,    0,   14,    0,   19,    0,
   18,    0,    0,    0,    0,    6,   20,   11,   12,   15,
};
short yydgoto[] = {                                       1,
    2,    4,    5,   18,   22,   16,   35,   31,
};
short yysindex[] = {                                      0,
    0, -256, -265,    0, -217, -234, -227,    0,    0,    0,
    0,    0, -231, -234, -228,    0,    0, -257,    0, -224,
    0, -258,    0,    0,    0, -264,    0, -212,    0, -254,
    0, -233, -233, -234, -260,    0,    0,    0,    0,    0,
};
short yyrindex[] = {                                      0,
    0,   47,    0,    0,    0,    0, -252,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -250,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -253, -251,    0,    0,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,   26,   15,   14,    0,  -14,    0,    0,
};
#define YYTABLESIZE 50
short yytable[] = {                                      20,
   23,   28,   34,   37,   22,   24,   23,   21,    6,   39,
   24,   25,    3,   22,    3,   23,    3,   24,   25,   38,
   24,   25,   24,   24,   21,   21,    9,   10,   11,   12,
   13,   17,   26,   14,   19,   30,   15,   32,   33,    7,
    8,   24,   25,   21,   27,   36,    1,   29,    0,   40,
};
short yycheck[] = {                                      14,
  258,  260,  267,  258,  258,  258,  258,  258,  274,  270,
  275,  276,  273,  267,  273,  267,  273,  275,  276,   34,
  275,  276,  275,  276,  275,  276,  261,  262,  263,  264,
  265,  259,   19,  268,  266,   22,  271,   24,   25,  257,
  258,  275,  276,  272,  269,  258,    0,   22,   -1,   35,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 276
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"TOKEN_ASSIGNEMENT",
"TOKEN_SEMICOLON","TOKEN_LCURLY","TOKEN_RCURLY","TOKEN_STRING","TOKEN_INTEGER",
"TOKEN_CHAR","TOKEN_BOOLEAN","TOKEN_ARRAY","TOKEN_LBRACKET","TOKEN_RBRACKET",
"TOKEN_FUNCTION","TOKEN_LPAREN","TOKEN_RPAREN","TOKEN","VOID","TOKEN_IDENT",
"TOKEN_COLON","TOKEN_PLUS","TOKEN_MINUS",
};
char *yyrule[] = {
"$accept : program",
"program : decl_list",
"decl_list : decl_list decl",
"decl_list :",
"decl : param TOKEN_ASSIGNEMENT expr TOKEN_SEMICOLON",
"decl : param TOKEN_SEMICOLON",
"decl : param TOKEN_ASSIGNEMENT TOKEN_LCURLY stmt_list TOKEN_RCURLY TOKEN_SEMICOLON",
"type : TOKEN_STRING",
"type : TOKEN_INTEGER",
"type : TOKEN_CHAR",
"type : TOKEN_BOOLEAN",
"type : TOKEN_ARRAY TOKEN_LBRACKET expr TOKEN_RBRACKET type",
"type : TOKEN_FUNCTION type TOKEN_LPAREN param_list TOKEN_RPAREN",
"type : TOKEN VOID",
"param_list :",
"param_list : param_list param",
"param : TOKEN_IDENT TOKEN_COLON type",
"stmt_list :",
"stmt_list : stmt_list stmt",
"stmt : decl",
"stmt : expr TOKEN_SEMICOLON",
"stmt :",
"expr : expr TOKEN_PLUS expr",
"expr : expr TOKEN_MINUS expr",
"expr :",
};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
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
