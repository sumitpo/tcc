all:c99
c99:lex.yy.c y.tab.c
	gcc lex.yy.c y.tab.c -o c99
lex.yy.c:c99.l
	flex c99.l
y.tab.c:c99.y
	yacc -d c99.y
