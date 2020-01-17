#pragma once
#include "head.h"

class ModelMap {
	public:
		UINT width;//width
		UINT height;//height
		cell **area; //cell type
		COORD castle;
		//COORD entry;
		vector<enemy> enemies;
		vector<tower> towers;

		void setCell(int i, int j, cell c){	area[i][j] = c;}
		cell getCell(int i, int j ){return area[i][j];	}

		ModelMap(const int w, const int h);
		ModelMap(string fileName);
		ModelMap(const ModelMap & ModMap);
		~ModelMap();

		void drawMap(sf::RenderWindow &window);
		void drawPath(sf::RenderWindow &window, list<COORD> shortWay);
		void StartGame(sf::RenderWindow &window, unsigned int *tickCount);	
		void defineEfficiency();
};


bool save_map(ModelMap * myMap, string fileName);

