#include "polygon.h"

typedef struct stPolygon{
    Segment firstSegment, lastSegment;
    double xMin, xMax;
    bool firstInsert;
    double lastX, lastY;
} *PolygonImp;

Polygon createPolygon(){
    PolygonImp polygon = (PolygonImp) malloc(sizeof(struct stPolygon));

    polygon->firstSegment = NULL;
    polygon->lastSegment = NULL;
    polygon->firstInsert = true;

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

void insertPointPolygon(Polygon p, double x, double y){
    PolygonImp polygon = (PolygonImp) p;

    if(!polygon->firstInsert){
        if(polygon->lastX != x || polygon->lastY != y){
            Segment segment = createSegment(createVertex(createPoint(polygon->lastX, polygon->lastY), 0, 0), createVertex(createPoint(x, y), 0, 0));
            
            if(polygon->firstSegment == NULL){
                polygon->firstSegment = segment;
            }
            else{
                setSegmentProx(polygon->lastSegment, segment);
            }
            polygon->lastSegment = segment;

            if(x < polygon->xMin) polygon->xMin = x;
            if(x > polygon->xMax) polygon->xMax = x;
        }
    }
    else{
        polygon->firstInsert = false;
        polygon->xMin = x;
        polygon->xMax = x;
    }

    polygon->lastX = x;
    polygon->lastY = y;
}

void connectPolygon(Polygon p){
    PolygonImp polygon = (PolygonImp) p;

    double xFirst = getPointX(getVertexV(getSegmentV1(polygon->firstSegment)));
    double yFirst = getPointY(getVertexV(getSegmentV1(polygon->firstSegment)));

    Segment segment = createSegment(createVertex(createPoint(polygon->lastX, polygon->lastY), 0, 0), createVertex(createPoint(xFirst, yFirst), 0, 0));

    setSegmentProx(polygon->lastSegment, segment);
    polygon->lastSegment = segment;
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