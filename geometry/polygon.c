#include "polygon.h"

typedef struct stPolygon{
    Segment firstSegment;
    double xMax;
} *PolygonImp;

Polygon createPolygon(Segment s){
    PolygonImp polygon = (PolygonImp) malloc(sizeof(struct stPolygon));

    polygon->firstSegment = s;

    return polygon;
}

Segment getPolygonFirstSegment(Polygon p){
    PolygonImp polygon = (PolygonImp) p;

    return polygon->firstSegment;
}

double getPolygonXMax(Polygon p){
    PolygonImp polygon = (PolygonImp) p;

    return polygon->xMax;
}

void setPolygonXMax(Polygon p, double xMax){
    PolygonImp polygon = (PolygonImp) p;

    polygon->xMax = xMax;
}

void destroyPolygon(Polygon p){
    PolygonImp polygon = (PolygonImp) p;

    Segment s = polygon->firstSegment;
    while(s != NULL){
        Segment aux = getSegmentProx(s);
        freeSegment(s);
        s = aux;
    }
    free(polygon);
}