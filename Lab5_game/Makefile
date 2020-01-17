all: solve

solve: main.o Game.o Map.o pathFinder.o Texture_pool.o
		g++ main.o Game.o Map.o pathFinder.o Texture_pool.o -o main -L "../SFML/lib" -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
		g++ -c main.cpp -I "../SFML/include"

Game.o: Game.cpp
		g++ -c Game.cpp -I "../SFML/include"

Map.o: Map.cpp
		g++ -c Map.cpp -I "../SFML/include"

pathFinder.o: pathFinder.cpp
		g++ -c pathFinder.cpp -I "../SFML/include"

Texture_pool.o: Texture_pool.cpp
		g++ -c Texture_pool.cpp -I "../SFML/include"
clean:
	del -rf *.o main