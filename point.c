#include "point.h"

typedef struct stPoint{
    double x, y;
} *PointImp;

Point createPoint(double x, double y){
    PointImp point = (PointImp) malloc(sizeof(struct stPoint));

    point->x = x;
    point->y = y;

    return point;
}

int comparatorPoint(Point p1, Point p2){
    PointImp point1 = (PointImp) p1;
    PointImp point2 = (PointImp) p2;

    if(point1->x < point2->x) return -1;
    else if(point1->x > point2->x) return 1;
    else{
        if(point1->y < point2->y) return -1;
        else if(point1->y > point2->y) return 1;
        else return 0;
    }
}

double getPointX(Point p){
    PointImp point = (PointImp) p;

    return point->x;
}

double getPointY(Point p){
    PointImp point = (PointImp) p;

    return point->y;
}

void setPointMin(Point p, double x, double y){
    PointImp point = (PointImp) p;

    if(x < point->x)
        point->x = x;
    if(y < point->y)
        point->y = y;
}

void setPointMax(Point p, double x, double y){
    PointImp point = (PointImp) p;

    if(x > point->x)
        point->x = x;
    if(y > point->y)
        point->y = y;
}

void freePoint(Point p){
    PointImp point = (PointImp) p;

    free(point);
}