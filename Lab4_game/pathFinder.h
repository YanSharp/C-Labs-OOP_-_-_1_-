#pragma once
#include "head.h"

class PathFinder{
    public:   
        list<COORD> shortWay;
        PathFinder(int sizeX, int sizeY, COORD endP, cell **mapP);
        ~PathFinder();
        void findShortWay(enemy& unit);
    private:
        int ** visited;// матрица посещаемости
        queue <COORD> plan;
        int** path;
        cell ** map;
        int width;
        int height;
        COORD begin;
        COORD end;
    
        void find_path( short row, short col);
        void recoverPath();
        void clearMap();
};//нахождение пути