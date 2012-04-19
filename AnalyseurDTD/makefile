all: analyseDTD
analyseDTD: *.l *.y makefile
	flex -P dtd dtd.l
	bison -p dtd --debug --verbose --defines=dtd.tab.h dtd.y
	g++ -g -DYYDEBUG=1 -c lex.dtd.c dtd.tab.c 
clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output

