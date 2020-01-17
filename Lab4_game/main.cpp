#include "ModelMap.h"
#include "pathFinder.h"

int main(){  
    //ModelMap * game;
    //upload_map(game,"map.map");
    unique_ptr<ModelMap> game(new ModelMap("map.map"));
    PathFinder PF(game->width, game->height, game->castle, game->area);
    for(int i= 0; i<game->enemies.size();i++)
        PF.findShortWay(game->enemies[i]);
    game->defineEfficiency();
    int flag = game->enemies.size();
    bool start = 0;
    UINT timer = GetTickCount();
    sf::RenderWindow window(sf::VideoMode(SIZE*game->width, SIZE*game->height), "TowerDefence"); 
    while (window.isOpen())
    {       
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed){
                switch(event.key.code){

                /*case sf::Keyboard::Up:
                game->entry.Y--;break;

                case sf::Keyboard::Down:
                game->entry.Y++;break;

                case sf::Keyboard::Left:
                game->entry.X--;break; 

                case sf::Keyboard::Right:
                game->entry.X++;break;*/

                case sf::Keyboard::PageUp:
                flag+1<game->enemies.size()?flag++:flag=0;        
                break;

                case sf::Keyboard::PageDown:
                flag-1>=0?flag--:flag=game->enemies.size();        
                break;

                case sf::Keyboard::Space:
                if(start == 0)  start = 1;
                else start = 0;
                }
            }
        }

        window.clear();
        game->drawMap(window);
        if(flag<game->enemies.size())
            game->drawPath(window, game->enemies[flag].shortWay );
        if(start){
            //cout << "Start Game"<<endl;
            game->StartGame(window, &timer);
        }
        window.display();
    }
    
    return 1;
}