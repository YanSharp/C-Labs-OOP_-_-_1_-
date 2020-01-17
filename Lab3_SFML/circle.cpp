#include <SFML/Graphics.hpp>

void dravingOneHundredCircles(sf::RenderWindow &window)
{
    float radius = 50;
    float xCount = 10;
    float yCount = 10;
    
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Blue);

    
        window.clear();
        for(int i = 0; i < xCount; i++){
            for(int j = 0; j < yCount; j++){
                shape.setPosition(2 * radius * i, 2 * radius * j);
                window.draw(shape);
            }
        }
        

}