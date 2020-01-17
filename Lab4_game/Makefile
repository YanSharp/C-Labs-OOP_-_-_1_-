all: solve

solve: main.o ModelMap.o pathFinder.o
		g++ main.o ModelMap.o pathFinder.o -o main -L "../SFML/lib" -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
		g++ -c main.cpp -I "../SFML/include"

ModelMap.o: ModelMap.cpp
		g++ -c ModelMap.cpp -I "../SFML/include"

pathFinder.o: pathFinder.cpp
		g++ -c pathFinder.cpp -I "../SFML/include"

clean:
	del -rf *.o main