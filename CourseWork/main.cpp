#include "files_manager.h"

int main(){
    FreeConsole();
    setlocale(LC_ALL, "Russian");
    sf::RenderWindow window(sf::VideoMode(2*WINDOW_SIZE, WINDOW_SIZE), "File manager");
    files_manager fileManager(window);
    
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::TextEntered)
                fileManager.inputText(event); 

            if(event.type == sf::Event::KeyPressed){
                fileManager.Navigator(event);
            }
        }
        fileManager.Explore(window);
        window.display();
    }
}