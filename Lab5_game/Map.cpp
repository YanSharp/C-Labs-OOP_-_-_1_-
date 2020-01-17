#include "Map.h"

Map::Map (string fileName){
    char line[MAX];

	ifstream map(fileName, ios::binary);
	if (!map.is_open()) {
		//cout << "Can't open file. Check it please!" << endl;
		return;
	}
	cout << "File opened!" << endl;


	map.getline(line,MAX);
	width = atoi(line);
	map.getline(line,MAX);
	height = atoi(line);

	area.resize(width);
	for (int i = 0; i < width; i++){
		area[i].resize(height);
	}

	//cout<< width << '\t' << height << endl;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			map.read(&area[x][y].type, sizeof(char));
        }
		map.seekg(2, map.cur);
	}
	map.close();
}

void Map::drawMap(sf::RenderWindow &window){
       //sf::RectangleShape cell(sf::Vector2f(SIZE, SIZE));
       sf::Sprite cell(Texture_pool::Instance().textures.find(INT(cell_type::BASE))->second, (sf::IntRect (0,0,SIZE,SIZE)));
	   //cell.setOutlineThickness(SIZE/5);
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				cell.setPosition(j*SIZE,i*SIZE);
                switch (area[j][i].type){
                    case INT(cell_type::BASE):
                    //cell.setFillColor(sf::Color(255,0,0));
                    cell.setTexture(Texture_pool::Instance().textures.find(INT(cell_type::BASE))->second, false);
					//cell.setOutlineColor(sf::Color(255,0,0));
                    window.draw(cell);
                    break;

                    case INT(cell_type::NOT_ROAD):
                    //cell.setFillColor(sf::Color(63,63,63));
                    cell.setTexture(Texture_pool::Instance().textures.find(INT(cell_type::NOT_ROAD))->second, false);
					//cell.setOutlineColor(sf::Color(63,63,63));
                    window.draw(cell);
                    break;

                    case INT(cell_type::ROAD):
                    //cell.setFillColor(sf::Color(127,127,127));
					cell.setTexture(Texture_pool::Instance().textures.find(INT(cell_type::ROAD))->second, false);
					//cell.setOutlineColor(sf::Color(127,127,127));
                    window.draw(cell);
                    break;

                    case INT(cell_type::TOWER):
                    //cell.setFillColor(sf::Color(63,255,63));
					cell.setTexture(Texture_pool::Instance().textures.find(INT(cell_type::TOWER))->second, false);
					/*for(int i = 0; i < 10; i++){
						if(towers[i].coord.X == j && towers[i].coord.Y == i)
							//cell.setFillColor(sf::Color(0,127,63));
							cell.setTexture(&(Texture_pool::Instance().textures.find(INT(cell_type::BEST_TOWER))->second), false);
					}*/
					//cell.setOutlineColor(sf::Color(63,255,63));
                    window.draw(cell);
                    break;

                    case INT(cell_type::ENEMY_SPAWN):
                    //cell.setFillColor(sf::Color(0,0,255));
					cell.setTexture(Texture_pool::Instance().textures.find(INT(cell_type::ENEMY_SPAWN))->second, false);
					//cell.setOutlineColor(sf::Color(0,0,255));
                    window.draw(cell);
                    break;

					case INT(cell_type::BEST_TOWER):
                    //cell.setFillColor(sf::Color(63,255,63));
					cell.setTexture(Texture_pool::Instance().textures.find(INT(cell_type::BEST_TOWER))->second, false);
					//cell.setOutlineColor(sf::Color(0,127,127));
					//cell.setFillColor(sf::Color(0,127,63));
                    window.draw(cell);
                    break;
                }
			}
		}

		//cell.setPosition(entry.X*SIZE,entry.Y*SIZE);
		//cell.setFillColor(sf::Color(0,255,255));
        //window.draw(cell);
}
