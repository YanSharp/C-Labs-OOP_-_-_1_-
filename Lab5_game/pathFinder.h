#pragma once
#include "head.h"
#include "Map.h"

class PathFinder{
    public:   
        list<COORD> shortWay;
        PathFinder(shared_ptr<Map> mapP, COORD endP);
        //~PathFinder();
        void findShortWay(enemy& unit);
    private:
        vector<vector<int>> visited;// матрица посещаемости
        queue <COORD> plan;
        vector<vector<int>> path;
        vector<vector<cell>> map;
        int width;
        int height;
        COORD begin;
        COORD end;
    
        void find_path( short row, short col);
        void recoverPath();
        void clearMap();
};//нахождение пути