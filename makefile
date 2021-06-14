.PHONY: clean dirs

BIN=bin
SRC=src
TEST=test
OBJ=obj
GUI=gui
LIBS=-lgtest -lpthread

all: clean dirs $(BIN)/filesystem

$(BIN)/filesystem:	$(GUI)/tree_test.cpp $(GUI)/tree_test.h $(GUI)/tree_frame.h $(GUI)/node_data.h $(OBJ)/buildtree_visitor.o $(OBJ)/read_visitor.o $(OBJ)/setpath_visitor.o | $(BIN)
	g++ $< $(OBJ)/buildtree_visitor.o $(OBJ)/read_visitor.o $(OBJ)/setpath_visitor.o `wx-config --libs` `wx-config --cxxflags` -o $@

$(OBJ)/text_frame.o: $(GUI)/text_frame.cpp $(GUI)/text_frame.h | $(OBJ)
	g++ -c $< `wx-config --cxxflags` -o $@

$(OBJ)/buildtree_visitor.o: $(GUI)/buildtree_visitor.cpp $(GUI)/buildtree_visitor.h 
	g++ -std=c++11 -c $< `wx-config --cxxflags` -o $@

$(OBJ)/read_visitor.o: $(GUI)/read_visitor.cpp $(GUI)/read_visitor.h 
	g++ -std=c++11 -c $< `wx-config --cxxflags` -o $@

$(OBJ)/setpath_visitor.o: $(SRC)/setpath_visitor.cpp $(SRC)/setpath_visitor.h 
	g++ -std=c++11 -c $< -o $@

dirs:
	mkdir -p $(SRC) $(TEST) $(BIN) $(OBJ)

clean:
	rm -rf $(BIN) $(OBJ)

stat:
	wc src/* test/*
