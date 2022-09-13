#include "vertex.h"

typedef struct stVertex{
    Point v;
    double dist, angle;
    bool start;
    Segment s;
} *VertexImp;

Vertex createVertex(Point p, double xB, double yB){
    VertexImp vertex = (VertexImp) malloc(sizeof(struct stVertex));

    vertex->v = p;
    vertex->dist = distEuclid(getPointX(p), getPointY(p), xB, yB);
    vertex->angle = atan2(getPointY(p) - yB, getPointX(p) - xB);

    return vertex;
}

int comparatorVertex(Vertex v1, Vertex v2){
    VertexImp vertex1 = (VertexImp) v1;
    VertexImp vertex2 = (VertexImp) v2;

    return comparatorPoint(vertex1->v, vertex2->v);
}

Point getVertexV(Vertex v){
    VertexImp vertex = (VertexImp) v;

    return vertex->v;
}

double getVertexDist(Vertex v){
    VertexImp vertex = (VertexImp) v;

    return vertex->dist;
}

double getVertexAngle(Vertex v){
    VertexImp vertex = (VertexImp) v;

    return vertex->angle;
}

bool getVertexStart(Vertex v){
    VertexImp vertex = (VertexImp) v;

    return vertex->start;
}

Segment getVertexSegment(Vertex v){
    VertexImp vertex = (VertexImp) v;

    return vertex->s;
}

void setVertexSegment(Vertex v, Segment s){
    VertexImp vertex = (VertexImp) v;

    vertex->s = s;
}

void setVertexStart(Vertex v, bool start){
    VertexImp vertex = (VertexImp) v;

    vertex->start = start;
}

void setVertexAngle(Vertex v, double angle){
    VertexImp vertex = (VertexImp) v;

    vertex->angle = angle;
}

void freeVertex(Vertex v){
    VertexImp vertex = (VertexImp) v;

    freePoint(vertex->v);
    free(vertex);
}