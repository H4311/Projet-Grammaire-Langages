CXX = g++
CXXFLAGS = -Wall #-Werror -pedantic
EXEC_NAME = test_validation
INCLUDES = 
LIBS = -lboost_regex
OBJ_FILES = Test.o Validateur.o
OBJ_FILES_DEP = ../xml/*.o ../dtd/*.o

XML_REP = ../xml/
DTD_REP = ../dtd/

all: $(EXEC_NAME)

.PHONY: clean rebuild

test: all
	./$(EXEC_NAME)

clean:
	make clean -C $(XML_REP)
	make clean -C $(DTD_REP)
	rm $(EXEC_NAME) $(OBJ_FILES)

rebuild: clean all

$(EXEC_NAME): $(OBJ_FILES)
	make -C $(XML_REP)
	make -C $(DTD_REP)
	$(CXX) -o $(EXEC_NAME) $(OBJ_FILES) $(OBJ_FILES_DEP) $(LIBS)
	rm Test.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<
