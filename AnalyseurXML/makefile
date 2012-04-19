CXX = g++
LD = g++
EXE = xmlparser
CXXFLAGS = -g -Wall -DYYDEBUG=1
LDFLAGS = 
OBJ = lex.xml.o xml.tab.o xml/Data.o xml/Element.o xml/EmptyElement.o xml/Content.o xml/Comment.o xml/Document.o

all: analyseXML

analyseXML: $(OBJ)
	flex -P xml xml.l
	bison -p xml --debug --verbose --defines=xml.tab.h xml.y
	# $(LD) -o $(EXE) $^ $(LDFLAGS)

.PHONY: clean mrproper
clean:
	rm -rf *.tab.c lex.*.c *.tab.h *.output

mrproper: clean all
	
%.o: %.cpp %.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)
