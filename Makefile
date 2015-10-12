#Project Geometry test

DIR = bin
BIN = $(DIR)/Geometry
OBJ = $(DIR)/main.o $(DIR)/draw.o $(DIR)/complex.o $(DIR)/point.o $(DIR)/line.o $(DIR)/element.o $(DIR)/transform.o $(DIR)/model.o
LIB = -Lfreeglut -Wl,-Bstatic -lglut -Wl,-Bdynamic -lGL -lX11 -lXxf86vm -lXrandr -lXi -g3
CXX = g++
CXXFLAGS = -I"freeglut/include" -Wall -g3

.PHONY: test clean cleanbackup cb win

$(BIN): $(DIR) $(OBJ)
	$(CXX) $(OBJ) -o $(BIN) $(LIB)

$(DIR):
	mkdir $(DIR)

test : $(BIN)
	./$(BIN)

$(DIR)/main.o : main.cpp element.h draw.h model.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/draw.o : draw.cpp element.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/complex.o : complex.cpp element.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/point.o : point.cpp element.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/line.o : line.cpp element.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/element.o : element.cpp element.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/transform.o : transform.cpp element.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/model.o : model.cpp element.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

cleanbackup :
	rm -vf *~ *.orig .*~

cb : cleanbackup

clean :
	rm -vf $(BIN) $(OBJ)
