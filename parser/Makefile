all: cminor

cminor: token.o lex.yy.o cminor.o error.o parser.tab.o expr.o type.o decl.o param_list.o stmt.o
	gcc lex.yy.o token.o cminor.o error.o parser.tab.o expr.o type.o decl.o param_list.o stmt.o -o cminor

%.o: %.c 
	gcc -c $< -o $@

lex.yy.c: scanner.flex parser.tab.h
	flex scanner.flex

parser.tab.c parser.tab.h: parser.bison
	yacc -d -bparser -v parser.bison

clean:
	rm *.o lex.yy.c cminor parser.tab* parser.output
