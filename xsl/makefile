CXX = g++
LD = g++
EXE = test_xsl
CXXFLAGS = -g -Wall -DYYDEBUG=1 -I..
LDFLAGS = -lboost_regex
OBJ = XSLProcessor.o Test.o
XML_OBJ = ../xml/*.o
DTD_OBJ = ../dtd/*.o
XPATH_OBJ = ../xpath/*.o
VALID_OBJ = ../validation/*.o

all: exe

test: exe
	./$(EXE)

exe: deps  $(OBJ)
	$(CXX) -o $(EXE) $(XML_OBJ) $(DTD_OBJ) $(XPATH_OBJ) $(VALID_OBJ) $(OBJ) $(LDFLAGS)

deps:
	make -C ../xml
	make -C ../dtd
	make -C ../validation
	make -C ../xpath
%.o: %.cpp %.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)
	

.PHONY: clean mrproper
clean:
	rm -rf *.o

mrproper: clean 
	rm -rf $(EXE)

