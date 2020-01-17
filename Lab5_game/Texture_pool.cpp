#include "Texture_pool.h"

Texture_pool::Texture_pool(){

    sf::Texture texture;

    texture.loadFromFile("Textures/castle.jpg");
    textures.insert(pair<int, sf::Texture>(INT(cell_type::BASE), texture));

    texture.loadFromFile("Textures/road.jpg");
    textures.insert(pair<int, sf::Texture>(INT(cell_type::ROAD), texture));

    texture.loadFromFile("Textures/tower(0).jpg");
    textures.insert(pair<int, sf::Texture>(INT(cell_type::TOWER), texture));

    texture.loadFromFile("Textures/grass.jpg");
    textures.insert(pair<int, sf::Texture>(INT(cell_type::NOT_ROAD), texture));

    texture.loadFromFile("Textures/enemy_spawn.jpg");
    textures.insert(pair<int, sf::Texture>(INT(cell_type::ENEMY_SPAWN), texture));
    
    texture.loadFromFile("Textures/best_tower.jpg");
    textures.insert(pair<int, sf::Texture>(INT(cell_type::BEST_TOWER), texture));

    texture.loadFromFile("Textures/enemy(1)t.jpg");
    textures.insert(pair<int, sf::Texture>(INT(cell_type::ENEMY1), texture));

    texture.loadFromFile("Textures/enemy(2)t.jpg");
    textures.insert(pair<int, sf::Texture>(INT(cell_type::ENEMY2), texture));

    texture.loadFromFile("Textures/track(1)t.jpg");
    textures.insert(pair<int, sf::Texture>(INT(cell_type::FOOTPRINT1), texture));

    texture.loadFromFile("Textures/track(2)t.jpg");
    textures.insert(pair<int, sf::Texture>(INT(cell_type::FOOTPRINT2), texture));
}