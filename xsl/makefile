CXX = g++
LD = g++
EXE = xsl
CXXFLAGS = -g -Wall -DYYDEBUG=1 -I../xml
LDFLAGS = 
OBJ = XSLProcessor.o
XML_OBJ = ../xml/*.o

all: exe

exe: xml  $(OBJ)
	$(CXX) -o $(EXE) $(XML_OBJ) $(OBJ) $(LDFLAGS)

xml:
	make -C ../xml

%.o: %.cpp %.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)
	

.PHONY: clean mrproper
clean:
	rm -rf *.o

mrproper: clean 
	rm -rf $(EXE)

