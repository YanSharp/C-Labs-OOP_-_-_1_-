#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <Windows.h>
#include <list>
#include <algorithm>
#include <vector>
#include <queue>
#include <memory>
#include <SFML/Graphics.hpp>

typedef unsigned int UINT;

using namespace std;

#define MAX 255
#define MAP_SIZE 20
#define SIZE 50
#define SPEED 400

enum cell_type {
	BASE = 43,//+//255,0,0
	NOT_ROAD = 88,//X//63,63,63
	ROAD = 35,//#//127,127,127
	TOWER = 64,//@//63,255,63
	ENEMY_SPAWN = 33,//!//0,0,255
	BEST_TOWER = 42//*//31,255,127
};

struct cell {
	char type;
};

struct tower{
	COORD coord;
	UINT efficiency;
};

struct enemy{
    list<COORD> shortWay;
    //int health;
    //int speed;
	list<COORD>::iterator cur_pos;
	COORD entry;
};

