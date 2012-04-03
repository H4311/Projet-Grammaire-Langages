all: analyseXML
analyseXML: *.l *.y makefile
	flex -P xml xml.l
	bison -p xml --debug --verbose --defines=xml.tab.h xml.y
	g++ -g -DYYDEBUG=1 -o analyseXML  lex.xml.c  xml.tab.c
clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output analyseXML

