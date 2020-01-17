all: solve

solve: main.o mod.o
		g++ main.o mod.o -o main

main.o: main.cpp
		g++ -c main.cpp

mod.o: mod.cpp
		g++ -c mod.cpp

clean:
	del -rf *.o main
