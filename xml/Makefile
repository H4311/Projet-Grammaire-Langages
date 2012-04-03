CXX = g++
LD = g++
EXE = xml
CXXFLAGS = -g
LDFLAGS =

all: xml
	

xml: Data.o Element.o EmptyElement.o Content.o main.o Comment.o SpecialElement.o
	$(LD) -o $(EXE) $^ $(LDFLAGS)

%.o: %.cpp %.h
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f *.o $(EXE)
