#Project Geometry test

BIN = bin/Geometry
OBJ = bin/main.o bin/draw.o bin/complex.o bin/point.o bin/line.o bin/element.o bin/transform.o
LIB = -lGL -lglut -g3 -Wl,-rpath,/usr/local/lib/x86_64-linux-gnu
CXX = g++
CXXFLAGS = -Wall -g3

.PHONY: test clean cleanbackup cb

$(BIN): bin $(OBJ)
	$(CXX) $(OBJ) -o $(BIN) $(LIB)

bin:
	mkdir bin

test : $(BIN)
	./$(BIN)

bin/main.o : main.cpp element.h draw.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/draw.o : draw.cpp element.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/complex.o : complex.cpp element.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/point.o : point.cpp element.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/line.o : line.cpp element.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/element.o : element.cpp element.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/transform.o : transform.cpp element.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

cleanbackup :
	rm -f *~ *.orig

cb : cleanbackup

clean :
	rm -f $(BIN) $(OBJ)
