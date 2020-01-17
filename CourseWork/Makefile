all: solve

solve: main.o panel.o files_manager.o searcher.o
		g++ main.o panel.o files_manager.o searcher.o -o main -L "../SFML/lib" -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
		g++ -c main.cpp -I "../SFML/include"

panel.o: panel.cpp
		g++ -c panel.cpp -I "../SFML/include"

files_manager.o: files_manager.cpp
		g++ -c files_manager.cpp -I "../SFML/include"

searcher.o: searcher.cpp
		g++ -c searcher.cpp -I "../SFML/include"

clean:
	del -rf *.o main