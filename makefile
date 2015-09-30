OBJS = main.o draw.o element.o
CC = g++
CFLAGS = -Wall -O -g -lGL -lglut

Geometry : $(OBJS)
	$(CC) $(OBJS) -o Geometry -lGL -lglut

main.o : main.cpp element.h draw.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o

draw.o : draw.cpp element.h
	$(CC) $(CFLAGS) -c draw.cpp -o draw.o

element.o : element.cpp
	$(CC) $(CFLAGS) -c element.cpp -o element.o

clean :
	rm -rf *.o Geometry
