#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <Windows.h>
#include <tchar.h>
#include <list>
#include <vector>
#include <queue>
#include <iterator>
#include <math.h>
#include <WinDef.h>
#include <wtypes.h>
#include <codecvt>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "ShellAPI.h"

using namespace std;

typedef unsigned int UINT;
typedef sf::Vector2f VECT;

#define INT(x) (static_cast<int> (x))

#define BUFSIZE MAX_PATH
#define WINDOW_SIZE 700
#define CELL_SIZE 14
#define BORDER_SIZE WINDOW_SIZE/50
#define CHARACTER_SIZE WINDOW_SIZE/40