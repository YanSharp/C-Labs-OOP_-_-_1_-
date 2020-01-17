#include "Game.h"
#include "pathFinder.h"

int main(){

    unique_ptr<Game> game(new Game("map.map"));
    PathFinder PF(game->map, game->castle);

    for(int i= 0; i<game->enemies.size();i++)
        PF.findShortWay(game->enemies[i]);
    
    game->defineEfficiency();
    int flag = game->enemies.size();
    bool start = 0;
    UINT timer = GetTickCount();
    sf::RenderWindow window(sf::VideoMode(SIZE*game->map->width, SIZE*game->map->height), "TowerDefence");

    while (window.isOpen())
    {       
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed){
                switch(event.key.code){

                case sf::Keyboard::Space:
                if(game->start == 0)  game->start = 1;
                else game->start = 0;
                }
            }
        }

        window.clear();
        game->StartGame(window, &timer);

        window.display();
        
    }
    
    return 1;
}