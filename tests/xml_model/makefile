CXX = clang++
LD = g++
EXE = test_xml
CXXFLAGS = -g -Wall -DYYDEBUG=1 -I../../xml/
LDFLAGS = 
OBJ = ../../xml/*.o test.o

all: test

test: test.o
	$(CXX) -o $(EXE) $(OBJ) $(LDFLAGS)

test.o: test.cpp
	$(CXX) -o test.o -c $< $(CXXFLAGS)
	

.PHONY: clean mrproper
clean:
	rm -rf *.o

mrproper: clean 
	rm -rf $(EXE)

