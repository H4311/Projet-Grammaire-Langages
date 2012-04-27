CXX = g++
CXXFLAGS = -Wall #-Werror -pedantic
EXEC_NAME = main
INCLUDES = 
LIBS = -lboost_program_options -lboost_regex
OBJ_FILES = Main.o
OBJ_FILES_DEP = xml/*.o dtd/*.o validation/*.o # xsl/*.o

XML_REP = xml/
DTD_REP = dtd/
XSL_REP = xsl/
VAL_REP = validation/

all: fils $(EXEC_NAME) 

test: all
	@echo "\n\nTESTS XML\n\n"
	@(cd $(XML_REP) && ./test_xml)
	@echo "\n\nTESTS DTD\n\n"
	@(cd $(DTD_REP) && ./test_dtd)
	@echo "\n\nTESTS VALIDATION\n\n"
	@(cd $(VAL_REP) && ./test_validation)

fils:
	make -C $(XML_REP)
	make -C $(DTD_REP)
	make -C $(VAL_REP)
	#make -C $(XSL_REP)

.PHONY: clean rebuild

clean:
	make clean -C $(XML_REP)
	make clean -C $(DTD_REP)
	make clean -C $(VAL_REP)
#	make clean -C $(XSL_REP)
	rm -rf $(EXEC_NAME) $(OBJ_FILES)

rebuild: clean all

$(EXEC_NAME): $(OBJ_FILES) $(XML_REP) $(DTD_REP) $(XSL_REP) $(VAL_REP)
	$(CXX) -o $(EXEC_NAME) $(OBJ_FILES) $(OBJ_FILES_DEP) $(LIBS)

Main.o: Main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<
