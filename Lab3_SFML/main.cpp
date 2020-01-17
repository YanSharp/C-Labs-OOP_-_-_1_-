#include <SFML/Graphics.hpp>
#include "circle.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000,1000), "Circles!");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        dravingOneHundredCircles(window);
        window.display();
    }

    return 0;

}

