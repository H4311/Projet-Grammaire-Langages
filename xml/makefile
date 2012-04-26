CXX = g++
LD = g++
EXE = test_xml
CXXFLAGS = -g -Wall -DYYDEBUG=1
LDFLAGS = 
OBJ = lex.xml.o xml.tab.o Data.o Element.o EmptyElement.o Content.o Comment.o Document.o ProcessingInstruction.o Test.o

all: analyseXML

analyseXML: flexbison $(OBJ)
	$(LD) -o $(EXE) $(OBJ) $(LDFLAGS)
	rm Test.o

flexbison: xml.l xml.y
	flex -P xml xml.l
	bison -p xml --debug --verbose --defines=xml.tab.h xml.y

test: analyseXML
	./$(EXE)

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
