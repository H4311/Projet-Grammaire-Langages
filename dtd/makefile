CXX = g++
LD = g++
EXE = test_dtd
OBJ = Document.o Declaration.o AttributeList.o Attribute.o Element.o ContentSpec.o Children.o ChoiceSeq.o Choice.o Seq.o Name.o Test.o
CXXFLAGS = -g
LDFLAGS =

all: flexbison dtd 

test: all
	./$(EXE)

flexbison: dtd.l dtd.y
	flex -P dtd dtd.l
	bison -p dtd --debug --verbose --defines=dtd.tab.h dtd.y
	g++ -g -DYYDEBUG=1 -c lex.dtd.c dtd.tab.c 

dtd: $(OBJ)
	$(LD) -o $(EXE) $^ $(LDFLAGS)
	rm Test.o

%.o: %.cpp %.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean

clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output *.o

mrproper: clean
	rm -f $(EXE)
