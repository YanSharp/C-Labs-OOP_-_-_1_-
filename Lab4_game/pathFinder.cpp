#include "pathFinder.h"


PathFinder::PathFinder(int sizeX, int sizeY, COORD endP, cell **mapP) : width(sizeX), height(sizeY){
    visited = new int * [height];
    path = new int * [height];
    //устанавливаем  конечную точку
    end.X = endP.X;
    end.Y = endP.Y;
    map=mapP;   // массив для хранения лабиринта
    //выделяем память
    for(int i=0; i<height; i++){         
        visited[i] = new int [width]; // массив для хранения информации о посещении клеток
        path[i] = new int [width];  // массив для хранения найденных путей            
    }
    clearMap();//подготовка карты посещений и путей
}

PathFinder::~PathFinder(){
    for (int i = 0; i < height; i++){
		delete[] visited[i];
        delete[] path[i];
	}
	delete[] visited;
    delete[] path;
}

void PathFinder::findShortWay(enemy& unit){
        clearMap();//подготовка карты посещений и путей

        //устанавливаем начало пути
        begin.X = unit.entry.X;
        begin.Y = unit.entry.Y;

        plan.push(begin);  // заносим начальную клетку в план посещения
        path[begin.X][begin.Y] = 1;

        while(!plan.empty()){ // пока очередь посещения клеток непустая
        COORD cur = plan.front();  
        plan.pop();
        find_path( cur.X, cur.Y); // продолжаем поиск пути    
        
    }
    recoverPath();
    shortWay.reverse();
    shortWay.pop_back();
    swap(shortWay, unit.shortWay);
    unit.cur_pos = unit.shortWay.begin();
}

void PathFinder::find_path( short row, short col){  
    if(!visited[row][col]){
        COORD cur ;
        /* проверяем не вышли ли мы за границы лабиринта, есть ли клетка 
        в массиве посещенных и можно ли через нее пройти*/
     
        if ((row+1) < height && (row+1) >= 0 && !visited[row+1][col] &&
            (map[row+1][col].type == ROAD || map[row+1][col].type == BASE)) {
                path[row+1][col] = path[row][col] + 1;
                cur.X=row+1;
                cur.Y=col;
                plan.push(cur);            
        }
        if((row-1) < height && (row-1) >= 0 && !visited[row-1][col] && 
            (map[row-1][col].type == ROAD || map[row-1][col].type == BASE)) {
                path[row-1][col] = path[row][col] + 1;
                cur.X=row-1;
                cur.Y=col;
                plan.push(cur);
        }
        if((col + 1) < width && (col + 1) >= 0 && !visited[row][col+1] && 
            (map[row][col+1].type == ROAD || map[row][col+1].type == BASE)) {
                path[row][col+1] = path[row][col] + 1;
                cur.X=row;
                cur.Y=col+1;
                plan.push(cur);
        }
        if((col - 1) < width && (col - 1) >= 0 && !visited[row][col-1] && 
            (map[row][col-1].type == ROAD || map[row][col-1].type == BASE)) {
                path[row][col-1] = path[row][col] + 1;
                cur.X=row;
                cur.Y=col-1;
                plan.push(cur);
        }
        visited[row][col] = 1; /* отмечаем клетку в которой побывали */
        //cout<<" path  "<<path[row][col]<<endl;
    }
}

void PathFinder::recoverPath() {        
    if(!visited[end.X][end.Y]){
        cout << "Not way" << endl;
    }
    else {       
        short x = end.X;
        short y = end.Y;
        shortWay.push_back(end);
        while (path[x][y] != 2) { // восстановление пути*/
            if ((x-1) >= 0 && (x-1) < width && (path[x-1][y] == path[x][y] - 1)) {
                shortWay.push_back(COORD{--x,y});
            }
            else if ((x+1) >= 0 && (x+1) < width && (path[x+1][y] == path[x][y] - 1)) {
                shortWay.push_back(COORD{++x,y});
            }
            else if ((y-1) >= 0 && (y-1) < height && (path[x][y-1] == path[x][y] - 1)) {
                shortWay.push_back(COORD{x,--y});
            }
            else if ((y+1) >= 0 && (y+1) < height && (path[x][y+1] == path[x][y] - 1)) {
                shortWay.push_back(COORD{x,++y});
            }
        }            
    }
}

void PathFinder::clearMap(){
    for(int i=0; i<width; i++){ 
        for(int j=0; j<height; j++){
                visited[i][j] = 0;  
                path[i][j] = -1; 
            }
        }
}