#include "wall.h"

typedef struct stWall{
    double x1, y1, x2, y2;
}*WallImp;

Wall createWall(double x1, double y1, double x2, double y2){
    WallImp wall = (WallImp) malloc(sizeof(struct stWall));

    wall->x1 = x1;
    wall->y1 = y1;
    wall->x2 = x2;
    wall->y2 = y2;

    return wall;
}

double getWallX1(Wall w){
    WallImp wall = (WallImp) w;

    return wall->x1;
}

double getWallY1(Wall w){
    WallImp wall = (WallImp) w;

    return wall->y1;
}

double getWallX2(Wall w){
    WallImp wall = (WallImp) w;

    return wall->x2;
}

double getWallY2(Wall w){
    WallImp wall = (WallImp) w;

    return wall->y2;
}

void freeWall(Wall w){
    WallImp wall = (WallImp) w;

    free(wall);
}