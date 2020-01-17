#include "ModelMap.h"

ModelMap::ModelMap(const int w, const int h):
	width(w), height(h){
		area = new cell*[height];
		for (int i = 0; i < height; i++)
		{
			area[i] = new cell[width];
		}
}

ModelMap::ModelMap(string fileName){
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

	area = new cell*[height];
	for (int i = 0; i < height; i++){
		area[i] = new cell[width];
	}

	//cout<< width << '\t' << height << endl;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			map.read(&area[x][y].type, sizeof(char));
			//cout<<map.tellg()<<(char)myMap->area[x][y].type<<endl;
			if(area[x][y].type == ENEMY_SPAWN){
				enemies.push_back(enemy());
				enemies.back().entry.X = x;
				enemies.back().entry.Y = y;
				//cout<< myMap->enemies[count].entry.X << '\t' << myMap->enemies[count].entry.Y << endl;
			}
			if(area[x][y].type == BASE){
				castle.X = x;
				castle.Y = y;
				//cout<<"found castle!"<<endl;
			}
			if(area[x][y].type == TOWER){
				towers.push_back(tower());
				towers.back().coord.X = x;
				towers.back().coord.Y = y;
			}
		}
		map.seekg(2, map.cur);
	}
	int i = 0;

	map.close();
}

ModelMap::~ModelMap() {		
	for (int i = 0; i < height; i++){
		delete[] area[i];
	}
	delete[] area;
}

//Конструктор копирования
ModelMap::ModelMap(const ModelMap & ModMap) {
	width = ModMap.width;
	height = ModMap.height;
	area = new cell*[height];
	for (int i = 0; i < height; i++){
		area[i] = new cell[width];
	}
	//copy all values
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			area[i][j].type =ModMap.area[i][j].type;
		}
	}
}

void ModelMap::drawMap(sf::RenderWindow &window){
       sf::RectangleShape cell(sf::Vector2f(SIZE, SIZE));
	   //cell.setOutlineThickness(SIZE/5);
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				cell.setPosition(j*SIZE,i*SIZE);
                switch (area[j][i].type){
                    case BASE:
                    cell.setFillColor(sf::Color(255,0,0));
					//cell.setOutlineColor(sf::Color(255,0,0));
                    window.draw(cell);
                    break;

                    case NOT_ROAD:
                    cell.setFillColor(sf::Color(63,63,63));
					//cell.setOutlineColor(sf::Color(63,63,63));
                    window.draw(cell);
                    break;

                    case ROAD:
                    cell.setFillColor(sf::Color(127,127,127));
					//cell.setOutlineColor(sf::Color(127,127,127));
                    window.draw(cell);
                    break;

                    case TOWER:
                    cell.setFillColor(sf::Color(63,255,63));
					//cell.setOutlineColor(sf::Color(63,255,63));
                    window.draw(cell);
                    break;

                    case ENEMY_SPAWN:
                    cell.setFillColor(sf::Color(0,0,255));
					//cell.setOutlineColor(sf::Color(0,0,255));
                    window.draw(cell);
                    break;

					case BEST_TOWER:
                    //cell.setFillColor(sf::Color(63,255,63));
					//cell.setOutlineColor(sf::Color(0,127,127));
					cell.setFillColor(sf::Color(0,127,63));
                    window.draw(cell);
                    break;
                }
			}
		}

		//cell.setPosition(entry.X*SIZE,entry.Y*SIZE);
		//cell.setFillColor(sf::Color(0,255,255));
        //window.draw(cell);
}

void ModelMap::StartGame(sf::RenderWindow &window, unsigned int *tickCount){
	sf::RectangleShape footprint(sf::Vector2f(SIZE/5, SIZE/5));
	for(int i = 0; i < enemies.size(); i++){
		if(enemies[i].cur_pos != enemies[i].shortWay.begin()){
			list<COORD>::iterator track = enemies[i].cur_pos;
			track--;
			footprint.setFillColor(sf::Color(60,60,60));
			footprint.setPosition(((*track).X + 0.4)*SIZE,((*track).Y + 0.4)*SIZE);
			window.draw(footprint);
			if(track != enemies[i].shortWay.begin()){
				track--;
				footprint.setFillColor(sf::Color(68,68,68));
				footprint.setPosition(((*track).X + 0.4)*SIZE,((*track).Y + 0.4)*SIZE);
				window.draw(footprint);
					if(track != enemies[i].shortWay.begin()){
						track--;
						footprint.setFillColor(sf::Color(76,76,76));
						footprint.setPosition(((*track).X + 0.4)*SIZE,((*track).Y + 0.4)*SIZE);
						window.draw(footprint);
					}
			}
		}
	}
	for(int i = 0; i < enemies.size(); i++){
		footprint.setFillColor(sf::Color(255,0,0));
		footprint.setPosition(((*enemies[i].cur_pos).X + 0.4)*SIZE,((*enemies[i].cur_pos).Y + 0.4)*SIZE);
		window.draw(footprint);
	}
	if(GetTickCount() - *tickCount > SPEED){
		*tickCount = GetTickCount();
		for(int i = 0; i < enemies.size(); i++){
			if(enemies[i].cur_pos != enemies[i].shortWay.end()){
				enemies[i].cur_pos++;
				//cout << (*enemies[i].cur_pos).X << '\t' << (*enemies[i].cur_pos).Y << endl;
			}
			else enemies[i].cur_pos = enemies[i].shortWay.begin();
		}
	}
}

void ModelMap::drawPath(sf::RenderWindow &window, list<COORD> shortWay){

	sf::CircleShape cell((float)SIZE/2);
	list<COORD>::iterator it=shortWay.begin();

	while(it!=shortWay.end()){				 
		cell.setPosition((*it).X*SIZE,(*it).Y*SIZE);
		cell.setFillColor(sf::Color(200,0,0));
		window.draw(cell);
		it++;            
    }

}

void ModelMap::defineEfficiency(){
    int x, y, rad;
	for(int i= 0; i < towers.size();i++){
		x = towers[i].coord.X;
		y = towers[i].coord.Y;
		rad = 2;
		for(int Xcoord = -rad; Xcoord <= rad; Xcoord++){
			for(int Ycoord = -rad; Ycoord <= rad; Ycoord++){
				if((x+Xcoord) < width && (y+Ycoord) < height && (x+Xcoord) > 0 && (y+Ycoord) > 0 && field[x+Xcoord][y+Ycoord].type == ROAD){
					for(int unit = 0; unit < enemies.size(); unit++){
						for(list<COORD>::iterator cell = enemies[unit].short_way.begin(); cell != enemies[unit].short_way.end(); cell++){
							if((*cell).X == (x+Xcoord) && (*cell).Y == (y+Ycoord))    towers[i].efficiency++;
							}
					}
				}  
			}
		}
	}

	sort(towers.begin(), towers.end(), [](const tower& a, const tower& b){return a.efficiency > b.efficiency;});
	for(int i= 0; i < 10; i++)
		area[towers[i].coord.X][towers[i].coord.Y].type = BEST_TOWER;

}

bool save_map(ModelMap * myMap, string fileName) {
	ofstream mapFile(fileName, ios::out | ios::binary);
	if (!mapFile.is_open()) {
		cout << "Can't open file. Check it please!" << endl;
		return false;
	}

	mapFile << myMap->width << '\n' << myMap->height << '\n';
	for (int i = 0; i < myMap->height; i++) {
		for (int j = 0; j < myMap->width; j++) {			
			mapFile << myMap->area[i][j].type;
		}
	mapFile << endl;
	}
	mapFile.close();
	return true;
}

