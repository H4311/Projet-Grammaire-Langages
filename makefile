CXX = g++
CXXFLAGS = -Wall #-Werror -pedantic
EXEC_NAME = main
INCLUDES = 
LIBS = -lboost_program_options
OBJ_FILES = Main.o
OBJ_FILES_DEP = xml/*.o AnalyseurDTD/*.o # xsl/*.o

XML_REP = xml/
DTD_REP = AnalyseurDTD/
XSL_REP = xsl/

all: $(EXEC_NAME)

.PHONY: clean rebuild

clean:
	make clean -C $(XML_REP)
	make clean -C $(DTD_REP)
#	make clean -C $(XSL_REP)
	rm $(EXEC_NAME) $(OBJ_FILES)

rebuild: clean all

$(EXEC_NAME): $(OBJ_FILES)
	make -C $(XML_REP)
	make -C $(DTD_REP)
#	make -C $(XSL_REP)
	$(CXX) -o $(EXEC_NAME) $(OBJ_FILES) $(OBJ_FILES_DEP) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<
