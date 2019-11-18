#include "wall.h"

typedef struct stWall{
    double x1, y1, x2, y2, size;
}*WallImp;

Wall createWall(double x1, double y1, double x2, double y2){
    WallImp wall = (WallImp) malloc(sizeof(struct stWall));

    wall->x1 = x1;
    wall->y1 = y1;
    wall->x2 = x2;
    wall->y2 = y2;
    wall->size = distEuclid(x1, y1, x2, y2);

    return wall;
}

int comparatorWall(Wall w1, Wall w2){
    WallImp wall1 = (WallImp) w1;
    WallImp wall2 = (WallImp) w2;
    
    if(wall1->x1 < wall2->x1) return -1;
    else if(wall1->x1 > wall2->x1) return 1;
    else{
        if(wall1->y1 < wall2->y1) return -1;
        else if(wall1->y1 > wall2->y1) return 1;
        else return 0;
    }
}

double getWallSize(Wall w){
    WallImp wall = (WallImp) w;

    return wall->size;
}

void getWallInformation(Wall w, char *info, char *posic){
    WallImp wall = (WallImp) w;

    sprintf(info, "%s", wall->size);
    sprintf(posic, "(%lf, %lf)", wall->x1, wall->y1);
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

void destroyWall(Wall w){
    WallImp wall = (WallImp) w;

    free(wall);
}