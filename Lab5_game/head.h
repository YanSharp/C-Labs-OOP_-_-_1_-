#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <list>
#include <algorithm>
#include <vector>
#include <queue>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>

typedef unsigned int UINT;

using namespace std;

#define MAX 255
#define MAP_SIZE 20
#define SIZE 50
#define SPEED 400

#define INT(x) (static_cast<int> (x))
#define CHAR(x) (static_cast<char> (x))

enum class cell_type{
	ENEMY1 = 1,
	ENEMY2 = 2,
	FOOTPRINT1 = 3,
	FOOTPRINT2 = 4,
	BASE = 43,//+//255,0,0
	NOT_ROAD = 88,//X//63,63,63
	ROAD = 35,//#//127,127,127
	TOWER = 64,//@//63,255,63
	ENEMY_SPAWN = 33,//!//0,0,255
	BEST_TOWER = 42//*//31,255,127
};

bool operator==( const cell_type& left, const cell_type& right ){
	return INT( left ) == INT( right );
}
bool operator>( const cell_type& left, const cell_type& right ){
	return INT( left ) > INT( right );
}
bool operator<( const cell_type& left, const cell_type& right ){
	return INT( left ) < INT( right );
}

struct cell {
	char type;
};

struct tower{
	COORD coord;
	UINT efficiency;
};

class enemy{
	public:
		list<COORD> shortWay;
		//int health;
		//int speed;
		COORD entry;

		list<COORD>::iterator get_cur_pos(){	return cur_pos;	}
		void set_cur_pos(list<COORD>::iterator it){	cur_pos = it;	}

	private:
		list<COORD>::iterator cur_pos;
};
