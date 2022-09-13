#include "segment.h"

#define PI 3.14159265

typedef struct stSegment{
    Vertex v1;
    Vertex v2;
    double xBiombo;
    double yBiombo;
    double distance;
    struct stSegment *prox;
} *SegmentImp;

Segment createSegment(Vertex v1, Vertex v2){
    SegmentImp segment = (SegmentImp) malloc(sizeof(struct stSegment));

    segment->v1 = v1;
    segment->v2 = v2;
    segment->xBiombo = getPointX(getVertexV(v1));
    segment->yBiombo = getPointY(getVertexV(v2));
    segment->prox = NULL;
    setVertexSegment(v1, segment);
    setVertexSegment(v2, segment);

    return segment;
}

int comparatorSegment(Segment s1, Segment s2){
    SegmentImp segment1 = (SegmentImp) s1;
    SegmentImp segment2 = (SegmentImp) s2;
    int r1 = comparatorVertex(segment1->v1, segment2->v1);
    int r2 = comparatorVertex(segment1->v2, segment2->v2);

    if(r1 != 0) return r1;
    else return r2;
}

Vertex getSegmentV1(Segment s){
    SegmentImp segment = (SegmentImp) s;

    return segment->v1;
}

Vertex getSegmentV2(Segment s){
    SegmentImp segment = (SegmentImp) s;

    return segment->v2;
}

Segment getSegmentProx(Segment s){
    SegmentImp segment = (SegmentImp) s;

    return segment->prox;
}

Vertex getSegmentVStart(Segment s){
    SegmentImp segment = (SegmentImp) s;

    if(getVertexStart(segment->v1)) return segment->v1;
    else return segment->v2;
}

Vertex getSegmentVEnd(Segment s){
    SegmentImp segment = (SegmentImp) s;

    if(!getVertexStart(segment->v1)) return segment->v1;
    else return segment->v2;
}

double getSegmentDistance(Segment s){
    SegmentImp segment = (SegmentImp) s;

    return segment->distance;
}

double getSegmentXBiombo(Segment s){
    SegmentImp segment = (SegmentImp) s;

    return segment->xBiombo;
}

double getSegmentYBiombo(Segment s){
    SegmentImp segment = (SegmentImp) s;

    return segment->yBiombo;
}

void setSegmentStartVertex(Segment s){
    SegmentImp segment = (SegmentImp) s;

    if(getVertexAngle(segment->v1) < getVertexAngle(segment->v2)){
        setVertexStart(segment->v1, true);
        setVertexStart(segment->v2, false);
    }
    else if(getVertexAngle(segment->v2) < getVertexAngle(segment->v1)){
        setVertexStart(segment->v1, false);
        setVertexStart(segment->v2, true);
    }
    else if(getVertexDist(segment->v1) < getVertexDist(segment->v2)){
        setVertexStart(segment->v1, true);
        setVertexStart(segment->v2, false);
    }
    else{
        setVertexStart(segment->v1, false);
        setVertexStart(segment->v2, true);
    }
}

void setSegmentProx(Segment s, Segment prox){
    SegmentImp segment = (SegmentImp) s;

    segment->prox = prox;
}

void setSegmentDistance(Segment s, double dist){
    SegmentImp segment = (SegmentImp) s;

    segment->distance = dist;
}

void setSegmentXYBiombo(Segment s, double x, double y){
    SegmentImp segment = (SegmentImp) s;

    segment->xBiombo = x;
    segment->yBiombo = y;
}

void freeSegment(Segment s){
    SegmentImp segment = (SegmentImp) s;
    
    freeVertex(segment->v1);
    freeVertex(segment->v2);
    free(segment);
}