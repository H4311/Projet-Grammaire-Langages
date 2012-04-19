CXX = g++
CXXFLAGS = -Wall #-Werror -pedantic
EXEC_NAME = main
INCLUDES = 
LIBS = -lboost_program_options
OBJ_FILES = Main.o
OBJ_FILES_DEP = AnalyseurXML/*.o AnalyseurDTD/*.o

all: $(EXEC_NAME)

clean:
	make clean -C AnalyseurXML/
	make clean -C AnalyseurDTD/
	rm $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME): $(OBJ_FILES)
	make -C AnalyseurXML/
	make -C AnalyseurDTD/
	$(CXX) -o $(EXEC_NAME) $(OBJ_FILES) $(OBJ_FILES_DEP) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<
