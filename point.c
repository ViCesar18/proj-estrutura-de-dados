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