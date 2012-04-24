CXX = g++
LD = g++
EXE = dtd
CXXFLAGS = -g
LDFLAGS =

all: dtd
	

dtd: Document.o Attribute.o Element.o
#	$(LD) -o $(EXE) $^ $(LDFLAGS)

%.o: %.cpp %.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f *.o 

mrproper: clean
	rm -f $(EXE)
