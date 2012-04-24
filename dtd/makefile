CXX = g++
LD = g++
EXE = dtd
OBJ = Document.o Declaration.o Attribute.o Element.o ContentSpec.o Children.o ChoiceSeq.o Choice.o Seq.o Name.o TestPut.o
CXXFLAGS = -g
LDFLAGS =

all: dtd

dtd: $(OBJ)
	$(LD) -o $(EXE) $^ $(LDFLAGS)
	rm TestPut.o

%.o: %.cpp %.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f *.o 

mrproper: clean
	rm -f $(EXE)
