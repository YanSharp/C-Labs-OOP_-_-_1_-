#include "Game.h"

Game::Game(string fileName){
	start = 0;
	map = shared_ptr<Map> (new Map("map.map"));
	for (int y = 0; y < map->height; y++) {
		for (int x = 0; x < map->width; x++) {			
			if(map->area[x][y].type == CHAR(cell_type::ENEMY_SPAWN)){
				enemies.push_back(enemy());
				enemies.back().entry.X = x;
				enemies.back().entry.Y = y;
				//cout<< myMap->enemies[count].entry.X << '\t' << myMap->enemies[count].entry.Y << endl;
			}
			if(map->area[x][y].type == CHAR(cell_type::BASE)){
				castle.X = x;
				castle.Y = y;
				//cout<<"found castle!"<<endl;
			}
			if(map->area[x][y].type == CHAR(cell_type::TOWER)){
				towers.push_back(tower());
				towers.back().coord.X = x;
				towers.back().coord.Y = y;
			}
		}
	}
}

void Game::StartGame(sf::RenderWindow &window, UINT *tickCount){
	map->drawMap(window);
	//sf::RectangleShape footprint(sf::Vector2f(SIZE/5, SIZE/5));
	sf::Sprite footprint(Texture_pool::Instance().textures.find(INT(cell_type::BASE))->second, (sf::IntRect (0,0,SIZE,SIZE)));
	if(start){
		for(int i = 0; i < enemies.size(); i++){
			if(enemies[i].get_cur_pos() != enemies[i].shortWay.begin()){
				list<COORD>::iterator track = enemies[i].get_cur_pos();
				list<COORD>::iterator tmp = enemies[i].get_cur_pos();
				track--;
				//footprint.setFillColor(sf::Color(60,60,60));
				if(((*track).X+(*track).Y)%2 == 0)
					footprint.setTexture(Texture_pool::Instance().textures.find(INT(cell_type::FOOTPRINT1))->second, false);
				else
					footprint.setTexture(Texture_pool::Instance().textures.find(INT(cell_type::FOOTPRINT2))->second, false);
				footprint.setPosition(((*track).X)*SIZE,((*track).Y)*SIZE);
				defDirection(track, tmp, footprint);
				window.draw(footprint);
				if(track != enemies[i].shortWay.begin()){
					track--;
					//footprint.setFillColor(sf::Color(68,68,68));
					if(((*track).X+(*track).Y)%2 == 0)
						footprint.setTexture(Texture_pool::Instance().textures.find(INT(cell_type::FOOTPRINT1))->second, false);
					else
						footprint.setTexture(Texture_pool::Instance().textures.find(INT(cell_type::FOOTPRINT2))->second, false);
					footprint.setPosition(((*track).X)*SIZE,((*track).Y)*SIZE);
					defDirection(track, --tmp, footprint);
					window.draw(footprint);
						if(track != enemies[i].shortWay.begin()){
							track--;
							//footprint.setFillColor(sf::Color(76,76,76));
							if(((*track).X+(*track).Y)%2 == 0)
								footprint.setTexture(Texture_pool::Instance().textures.find(INT(cell_type::FOOTPRINT1))->second, false);
							else
								footprint.setTexture(Texture_pool::Instance().textures.find(INT(cell_type::FOOTPRINT2))->second, false);
							footprint.setPosition(((*track).X)*SIZE,((*track).Y)*SIZE);
							defDirection(track, --tmp, footprint);
							window.draw(footprint);
						}
				}
			}
		}
		if(GetTickCount() - *tickCount > SPEED){
			*tickCount = GetTickCount();
			for(int i = 0; i < enemies.size(); i++){
				if(enemies[i].get_cur_pos() != enemies[i].shortWay.end()){
					enemies[i].set_cur_pos(++enemies[i].get_cur_pos());
					//cout << (*enemies[i].get_cur_pos()).X << '\t' << (*enemies[i].get_cur_pos()).Y << endl;
				}
				else enemies[i].set_cur_pos(enemies[i].shortWay.begin());
			}
		}
	}
	for(int i = 0; i < enemies.size(); i++){
		//footprint.setFillColor(sf::Color(255,0,0));
		list<COORD>::iterator tmp = enemies[i].get_cur_pos();
		if(((*enemies[i].get_cur_pos()).X + (*enemies[i].get_cur_pos()).Y) % 2 == 0)
			footprint.setTexture(Texture_pool::Instance().textures.find(INT(cell_type::ENEMY1))->second, false);
		else
			footprint.setTexture(Texture_pool::Instance().textures.find(INT(cell_type::ENEMY2))->second, false);
		footprint.setPosition(((*enemies[i].get_cur_pos()).X)*SIZE,((*enemies[i].get_cur_pos()).Y)*SIZE);
		defDirection(enemies[i].get_cur_pos(), ++tmp, footprint);
		window.draw(footprint);
	}	
}

void Game::defDirection(list<COORD>::iterator cur_pos, list<COORD>::iterator pos, sf::Sprite &sprite){
	if (((*cur_pos).X - (*pos).X) > 0) {
		sprite.setRotation(180);
		sprite.move(SIZE, SIZE);          
    }
    else if(((*cur_pos).X - (*pos).X) < 0) {
		sprite.setRotation(0);
		//sprite.move(0, 0);
    }
    else if(((*cur_pos).Y - (*pos).Y) > 0) {
		sprite.setRotation(270);
		//sprite.move(SIZE, -SIZE);
		sprite.move(0, SIZE);
    }
    else if(((*cur_pos).Y - (*pos).Y) < 0) {
		sprite.setRotation(90);
		sprite.move(SIZE, 0);
        //return 90;
    }
}

void Game::defineEfficiency(){
    int x, y;
	for(int i= 0; i < towers.size();i++){
		x = towers[i].coord.X;
		y = towers[i].coord.Y;
		if((x+2) < width && map->area[x+2][y].type == CHAR(ROAD)){
			for(int unit = 0; unit < enemies.size(); unit++){
				for(list<COORD>::iterator cell = enemies[unit].shortWay.begin(); cell != enemies[unit].shortWay.end(); cell++){
					if((*cell).X == (x+2) && (*cell).Y == y)    towers[i].efficiency++;
				}
			}
		}
		if((x-2) > 0 && map->area[x-2][y].type == CHAR(ROAD)){
			for(int unit = 0; unit < enemies.size(); unit++){
				for(list<COORD>::iterator cell = enemies[unit].shortWay.begin(); cell != enemies[unit].shortWay.end(); cell++){
					if((*cell).X == (x-2) && (*cell).Y == y)    towers[i].efficiency++;
				}
			}
		}
		if((y+2) < height && map->area[x][y+2].type == CHAR(ROAD)){
			for(int unit = 0; unit < enemies.size(); unit++){
				for(list<COORD>::iterator cell = enemies[unit].shortWay.begin(); cell != enemies[unit].shortWay.end(); cell++){
					if((*cell).X == x && (*cell).Y == (y+2))    towers[i].efficiency++;
				}
			}
		}
		if((y-2) > 0 && map->area[x][y-2].type == CHAR(ROAD)){
			for(int unit = 0; unit < enemies.size(); unit++){
				for(list<COORD>::iterator cell = enemies[unit].shortWay.begin(); cell != enemies[unit].shortWay.end(); cell++){
					if((*cell).X == x && (*cell).Y == (y-2))    towers[i].efficiency++;
				}
			}
		}
		if((x+2) < width && (y+2) < height && map->area[x+2][y+2].type == CHAR(ROAD)){
			for(int unit = 0; unit < enemies.size(); unit++){
				for(list<COORD>::iterator cell = enemies[unit].shortWay.begin(); cell != enemies[unit].shortWay.end(); cell++){
					if((*cell).X == (x+2) && (*cell).Y == (y+2))    towers[i].efficiency++;
				}
			}
		}
		if((x-2) > 0 && (y-2) > 0 && map->area[x-2][y-2].type == CHAR(ROAD)){
			for(int unit = 0; unit < enemies.size(); unit++){
				for(list<COORD>::iterator cell = enemies[unit].shortWay.begin(); cell != enemies[unit].shortWay.end(); cell++){
					if((*cell).X == (x-2) && (*cell).Y == (y-2))    towers[i].efficiency++;
				}
			}
		}
		if((y+2) < height && (x-2) > 0 && map->area[x-2][y+2].type == CHAR(ROAD)){
			for(int unit = 0; unit < enemies.size(); unit++){
				for(list<COORD>::iterator cell = enemies[unit].shortWay.begin(); cell != enemies[unit].shortWay.end(); cell++){
					if((*cell).X == (x-2) && (*cell).Y == (y+2))    towers[i].efficiency++;
				}
			}
		}
		if((y-2) > 0 && (x+2) < width && map->area[x][y-2].type == CHAR(ROAD)){
			for(int unit = 0; unit < enemies.size(); unit++){
				for(list<COORD>::iterator cell = enemies[unit].shortWay.begin(); cell != enemies[unit].shortWay.end(); cell++){
					if((*cell).X == (x+2) && (*cell).Y == (y-2))    towers[i].efficiency++;
				}
			}
		}
		if((x+2) < width && (y+1) < height && map->area[x+2][y+1].type == CHAR(ROAD)){
			for(int unit = 0; unit < enemies.size(); unit++){
				for(list<COORD>::iterator cell = enemies[unit].shortWay.begin(); cell != enemies[unit].shortWay.end(); cell++){
					if((*cell).X == (x+2) && (*cell).Y == (y+1))    towers[i].efficiency++;
				}
			}
		}
		if((x+2) < width && (y-1) > 0 && map->area[x+2][y-1].type == CHAR(ROAD)){
			for(int unit = 0; unit < enemies.size(); unit++){
				for(list<COORD>::iterator cell = enemies[unit].shortWay.begin(); cell != enemies[unit].shortWay.end(); cell++){
					if((*cell).X == (x+2) && (*cell).Y == (y-1))    towers[i].efficiency++;
				}
			}
		}
		if((y+2) < height && (x+1) < width && map->area[x+1][y+2].type == CHAR(ROAD)){
			for(int unit = 0; unit < enemies.size(); unit++){
				for(list<COORD>::iterator cell = enemies[unit].shortWay.begin(); cell != enemies[unit].shortWay.end(); cell++){
					if((*cell).X == (x+1) && (*cell).Y == (y+2))    towers[i].efficiency++;
				}
			}
		}
		if((y+2) > height && (x-1) > 0 && map->area[x-1][y+2].type == CHAR(ROAD)){
			for(int unit = 0; unit < enemies.size(); unit++){
				for(list<COORD>::iterator cell = enemies[unit].shortWay.begin(); cell != enemies[unit].shortWay.end(); cell++){
					if((*cell).X == (x+2) && (*cell).Y == (y-2))    towers[i].efficiency++;
				}
			}
		}
		if((x-2) > 0 && (y+1) < height && map->area[x-2][y+1].type == CHAR(ROAD)){
			for(int unit = 0; unit < enemies.size(); unit++){
				for(list<COORD>::iterator cell = enemies[unit].shortWay.begin(); cell != enemies[unit].shortWay.end(); cell++){
					if((*cell).X == (x-2) && (*cell).Y == (y+1))    towers[i].efficiency++;
				}
			}
		}
		if((x-2) > 0 && (y-1) > 0 && map->area[x-2][y-1].type == CHAR(ROAD)){
			for(int unit = 0; unit < enemies.size(); unit++){
				for(list<COORD>::iterator cell = enemies[unit].shortWay.begin(); cell != enemies[unit].shortWay.end(); cell++){
					if((*cell).X == (x-2) && (*cell).Y == (y-1))    towers[i].efficiency++;
				}
			}
		}
	}

	sort(towers.begin(), towers.end(), [](const tower& a, const tower& b){return a.efficiency > b.efficiency;});
	for(int i= 0; i < 10;i++)
		map->area[towers[i].coord.X][towers[i].coord.Y].type = CHAR(cell_type::BEST_TOWER);

}

bool Game::save_game(string fileName) {
	ofstream mapFile(fileName, ios::out | ios::binary);
	if (!mapFile.is_open()) {
		cout << "Can't open file. Check it please!" << endl;
		return false;
	}

	mapFile << map->width << '\n' << map->height << '\n';
	for (int i = 0; i < map->height; i++) {
		for (int j = 0; j < map->width; j++) {			
			mapFile << map->area[i][j].type;
		}
	mapFile << endl;
	}
	mapFile.close();
	return true;
}
