#pragma once
#include "head.h"
#include "Texture_pool.h"

class Map {
	public:
        UINT width;//width
		UINT height;//height
		vector<vector<cell>> area; //cell type

        //Map(const int w, const int h);
        Map(string fileName);

        void drawMap(sf::RenderWindow &window);

};
