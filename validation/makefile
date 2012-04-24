CXX = g++
CXXFLAGS = -Wall #-Werror -pedantic
EXEC_NAME = main
INCLUDES = 
LIBS = 
OBJ_FILES = Test.o
OBJ_FILES_DEP = ../xml/*.o ../dtd/*.o

XML_REP = ../xml/
DTD_REP = ../dtd/

all: $(EXEC_NAME)

.PHONY: clean rebuild

clean:
	make clean -C $(XML_REP)
	make clean -C $(DTD_REP)
	rm $(EXEC_NAME) $(OBJ_FILES)

rebuild: clean all

$(EXEC_NAME): $(OBJ_FILES)
	make -C $(XML_REP)
	make -C $(DTD_REP)
	$(CXX) -o $(EXEC_NAME) $(OBJ_FILES) $(OBJ_FILES_DEP) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<
