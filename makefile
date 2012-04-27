CXX = g++
CXXFLAGS = -Wall #-Werror -pedantic
EXEC_NAME = main
INCLUDES = 
LIBS = -lboost_program_options -lboost_regex
OBJ_FILES = Main.o
OBJ_FILES_DEP = xml/*.o dtd/*.o validation/*.o xsl/*.o xpath/*.o

XML_REP = xml/
DTD_REP = dtd/
XSL_REP = xsl/
VAL_REP = validation/
XPA_REP = xpath/

all: fils $(EXEC_NAME) 

test: all
	@echo "TESTS XML"
	@(cd $(XML_REP) && ./test_xml)
	@echo "\n\nTESTS DTD"
	@(cd $(DTD_REP) && ./test_dtd)
	@echo "\n\nTESTS VALIDATION"
	@(cd $(VAL_REP) && ./test_validation)
	@echo "\n\nTESTS XSL"
	@(cd $(XSL_REP) && ./test_xsl)
	@echo "\n\nTESTS XPATH"
	@(cd $(XPA_REP) && ./test_xpath)

fils:
	make -C $(XML_REP)
	make -C $(DTD_REP)
	make -C $(VAL_REP)
	make -C $(XSL_REP)
	make -C $(XPA_REP)

.PHONY: clean rebuild

clean:
	make clean -C $(XML_REP)
	make clean -C $(DTD_REP)
	make clean -C $(VAL_REP)
	make clean -C $(XSL_REP)
	make clean -C $(XPA_REP)
	rm -rf $(EXEC_NAME) $(OBJ_FILES)

rebuild: clean all

$(EXEC_NAME): $(OBJ_FILES) $(XPA_REP) $(XML_REP) $(DTD_REP) $(XSL_REP) $(VAL_REP)
	$(CXX) -o $(EXEC_NAME) $(OBJ_FILES) $(OBJ_FILES_DEP) $(LIBS)

Main.o: Main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<
