CXX = g++
LD = g++
EXE = xmlparser
CXXFLAGS = -g -Wall -DYYDEBUG=1
LDFLAGS = 
OBJ = lex.xml.o xml.tab.o Data.o Element.o EmptyElement.o Content.o Comment.o Document.o ProcessingInstruction.o

all: analyseXML

analyseXML: flexbison $(OBJ)

flexbison: xml.l xml.y
	flex -P xml xml.l
	bison -p xml --debug --verbose --defines=xml.tab.h xml.y

.PHONY: clean mrproper
clean:
	rm -rf *.tab.c lex.*.c *.tab.h *.output *.o

mrproper: clean 
	rm -rf $(EXE)
	
%.o: %.cpp %.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

lex.xml.o: lex.xml.c
	$(CXX) -o $@ -c $< $(CXXFLAGS)

xml.tab.o: xml.tab.c
	$(CXX) -o $@ -c $< $(CXXFLAGS)
