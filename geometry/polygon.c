#include "polygon.h"

typedef struct stPolygon{
    Segment firstSegment;
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