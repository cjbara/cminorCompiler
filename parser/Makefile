all: cminor

cminor: token.o lex.yy.o cminor.o error.o
	gcc lex.yy.o token.o cminor.o error.o -o cminor

cminor.o: cminor.c
	gcc -c cminor.c

token.o: token.c
	gcc -c token.c

error.o: error.c
	gcc -c error.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: scanner.l
	flex scanner.l

clean:
	rm *.o lex.yy.c cminor *.out
