CXX = clang++
LD = clang++
EXE = xsl
CXXFLAGS = -g -Wall -DYYDEBUG=1 -I..
LDFLAGS = 
OBJ = XSLProcessor.o
XML_OBJ = ../xml/*.o
DTD_OBJ = ../dtd/*.o
VALID_OBJ = ../validation/*.o

all: exe

exe: xml  $(OBJ)
	$(CXX) -o $(EXE) $(XML_OBJ) $(DTD_OBJ) $(VALID_OBJ) $(OBJ) $(LDFLAGS)

xml:
	make -C ../xml

%.o: %.cpp %.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)
	

.PHONY: clean mrproper
clean:
	rm -rf *.o

mrproper: clean 
	rm -rf $(EXE)

