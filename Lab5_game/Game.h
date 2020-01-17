#pragma once
#include "head.h"
#include "Map.h"

class Game {
	public:
		shared_ptr<Map> map;
		bool start;
		COORD castle;
		vector<enemy> enemies;
		vector<tower> towers;

		Game(string fileName);

		bool save_game(string fileName);

		void StartGame(sf::RenderWindow &window, UINT *tickCount);	
		void defineEfficiency();
		void defDirection(list<COORD>::iterator cur_pos, list<COORD>::iterator pos, sf::Sprite &sprite);
};



bool upload_map(Game*& myMap , string fileName);
