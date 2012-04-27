CXX = g++
LD = g++
EXE = xpath
CXXFLAGS = -g -Wall -DYYDEBUG=1 -I..
LDFLAGS = -lboost_regex
OBJ = XPath.o Test.o
XML_OBJ = ../xml/*.o

all: exe

test: exe
	./$(EXE)

exe: deps  $(OBJ)
	$(CXX) -o $(EXE) $(XML_OBJ) $(OBJ) $(LDFLAGS)
	rm Test.o

deps:
	make -C ../xml

%.o: %.cpp %.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)
	

.PHONY: clean mrproper
clean:
	rm -rf *.o

mrproper: clean 
	rm -rf $(EXE)

