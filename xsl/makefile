CXX = clang++
LD = clang++
EXE = xsl
CXXFLAGS = -g -Wall -DYYDEBUG=1 -I..
LDFLAGS = -lboost_regex
OBJ = XSLProcessor.o
XML_OBJ = ../xml/*.o
DTD_OBJ = ../dtd/*.o
VALID_OBJ = ../validation/*.o

all: exe

exe: deps  $(OBJ)
	$(CXX) -o $(EXE) $(XML_OBJ) $(DTD_OBJ) $(VALID_OBJ) $(OBJ) $(LDFLAGS)

deps:
	make -C ../xml
	make -C ../dtd
	make -C ../validation

%.o: %.cpp %.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)
	

.PHONY: clean mrproper
clean:
	rm -rf *.o

mrproper: clean 
	rm -rf $(EXE)

