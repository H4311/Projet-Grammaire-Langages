all: bison flex
	g++ -o main lex.yy.c calc.tab.c

bison:
	bison -d calc.y

flex:
	flex calc.lex

clean:
	rm *.o
