#Project Geometry test

BIN = bin/Geometry
OBJ = bin/main.o bin/draw.o bin/complex.o bin/point.o bin/line.o bin/element.o
LIB = -lGL -lglut -g3 -Wl,-rpath,/usr/local/lib/x86_64-linux-gnu
CXX = g++
CXXFLAGS = -Wall -O -g3

.PHONY: all all-before clean cleanbackup
all: all-before $(BIN)

all-before: bin

bin:
	mkdir bin

$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $(BIN) $(LIB)

bin/main.o : main.cpp element.h draw.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/draw.o : draw.cpp element.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/complex.o : complex.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/point.o : point.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/line.o : line.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/element.o : element.cpp element.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

cleanbackup :
	rm -f *~

clean :
	rm -f $(BIN) $(OBJ)
