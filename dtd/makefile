CXX = g++
LD = g++
EXE = dtd
CXXFLAGS = -g
LDFLAGS =

all: xml
	

xml: Document.o Attribute.o Element.o TestPut.o
	$(LD) -o $(EXE) $^ $(LDFLAGS)

%.o: %.cpp %.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f *.o 

mrproper: clean
	rm -f $(EXE)
