all: solve

solve: main.o image.o pool.o
		g++ main.o image.o pool.o -o main

main.o: main.cpp
		g++ -c main.cpp

image.o: image.cpp
		g++ -c image.cpp

pool.o: pool.cpp
		g++ -c pool.cpp

clean:
	del -rf *.o main