OBJS = main.o draw.o complex.o point.o line.o element.o
CC = g++
CFLAGS = -Wall -O -g -lGL -lglut

Geometry : $(OBJS)
	$(CC) $(OBJS) -o Geometry -lGL -lglut

main.o : main.cpp element.h draw.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o

draw.o : draw.cpp element.h
	$(CC) $(CFLAGS) -c draw.cpp -o draw.o

element.o : element.cpp element.h
	$(CC) $(CFLAGS) -c element.cpp -o element.o

complex.o : complex.cpp
	$(CC) $(CFLAGS) -c complex.cpp -o complex.o

point.o : point.cpp
	$(CC) $(CFLAGS) -c point.cpp -o point.o

line.o : line.cpp
	$(CC) $(CFLAGS) -c line.cpp -o line.o

clean :
	rm -rf *.o Geometry
