all: solve

solve: circle.dll main.o
		g++ main.o circle.dll -o main -L "../SFML/lib/"  -lsfml-graphics-d -lsfml-window-d -lsfml-system-d

main.o: main.cpp
		g++ -c main.cpp -I "../SFML/include/"

circle.dll: circle.o
		g++ -shared circle.o -o circle.dll -L "../SFML/lib/"  -lsfml-graphics-d -lsfml-window-d -lsfml-system-d

circle.o: circle.cpp
		g++ -c circle.cpp -I "../SFML/include/"
		
clean:
	del -rf *.o main