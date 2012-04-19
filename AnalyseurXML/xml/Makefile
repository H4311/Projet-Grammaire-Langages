CC = g++
LD = g++
EXE = xml
CXXFLAGS = -g -Wall
LDFLAGS =

all: xml
	

xml: Data.o Element.o EmptyElement.o Content.o main.o Comment.o ProcessingInstruction.o Document.o
	$(LD) -o $(EXE) $^ $(LDFLAGS)

%.o: %.cpp %.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f *.o 

mrproper: clean
	rm -f $(EXE)
