#include "segments.h"

#define PI 3.14159265

typedef struct stSegment{
    double x1, y1, x2, y2;
} *SegmentImp;

typedef struct stVertex{
    double x, y, angle, dist;
    bool start;
    Segment segment;
} *VertexImp;

Segment allocateSegments(int capacity){
    SegmentImp *segments = (SegmentImp *) malloc(capacity * sizeof(SegmentImp));

    return segments;
}

void insertSegment(Segment segmentAux, int *size, double x1, double y1, double x2, double y2){
    SegmentImp *segments = (SegmentImp *) segmentAux;

    segments[*size] = (SegmentImp) malloc(sizeof(struct stSegment));

    segments[*size]->x1 = x1;
    segments[*size]->y1 = y1;
    segments[*size]->x2 = x2;
    segments[*size]->y2 = y2;
    
    (*size)++;
}

Segment createSegments(int capacity, List walls, List buildings, int *vectSize){
    SegmentImp *segments = allocateSegments(capacity);

    for(int i = getFirst(walls); i != getNulo(); i = getNext(walls, i)){
        Wall wall = getElementByIndex(walls, i);
        insertSegment(segments, vectSize, getWallX1(wall), getWallY1(wall), getWallX2(wall), getWallY2(wall));
    }
    
    for(int i = getFirst(buildings); i != getNulo(); i = getNext(buildings, i)){
        Building building = getElementByIndex(buildings, i);

        insertSegment(segments, vectSize, getBuildingX(building), getBuildingY(building), getBuildingX(building) + getBuildingW(building), getBuildingY(building));
        insertSegment(segments, vectSize, getBuildingX(building) + getBuildingW(building), getBuildingY(building), getBuildingX(building) + getBuildingW(building), getBuildingY(building) + getBuildingH(buildings));
        insertSegment(segments, vectSize, getBuildingX(building) + getBuildingW(building), getBuildingY(building) + getBuildingH(building), getBuildingX(building), getBuildingY(building) + getBuildingH(building));
        insertSegment(segments, vectSize, getBuildingX(building), getBuildingY(building) + getBuildingH(building), getBuildingX(building), getBuildingY(building));
    }

    return segments;
}

void printSegments(FILE *arqSvgQ, Segment s, int size){
    SegmentImp *segments = (SegmentImp*) s;

    for(int i = 0; i < size; i++){
            printLine(arqSvgQ, segments[i]->x1, segments[i]->y1, segments[i]->x2, segments[i]->y2, "yellow");
        }
}

Vertex createVertices(double x, double y, int capacity, Segment s, int size, FILE *arqSvgQ){
    int j = 0, k = 1;
    SegmentImp *segments = (SegmentImp *) s;
    VertexImp *vertices = (VertexImp *) malloc(capacity * sizeof(VertexImp));

    for(int i = 0; i < size; i++){
        vertices[j] = (VertexImp) malloc(sizeof(struct stVertex));
        vertices[j]->x = segments[i]->x1;
        vertices[j]->y = segments[i]->y1;
        vertices[j]->dist = distEuclid(x, y, vertices[j]->x, vertices[j]->y);
        vertices[j]->angle = atan2(vertices[j]->y - y, vertices[j]->x - x) * 180 / PI;
        

        vertices[k] = (VertexImp) malloc(sizeof(struct stVertex));
        vertices[k]->x = segments[i]->x2;
        vertices[k]->y = segments[i]->y2;
        vertices[k]->dist = distEuclid(x, y, vertices[k]->x, vertices[k]->y);
        vertices[k]->angle = atan2(vertices[k]->y - y, vertices[k]->x - x) * 180 / PI;

        if(vertices[j]->angle < vertices[k]->angle){
            vertices[j]->start = true;
            vertices[k]->start = false;
        }
        else{
            vertices[j]->start = false;
            vertices[k]->start = true;
        }

        j += 2;
        k += 2;
    }

    return vertices;
}

int cmpVertex(const void *a, const void *b){
    VertexImp arg1 = * (const VertexImp *)a;
    VertexImp arg2 = * (const VertexImp *)b;


    if(arg1->angle < arg2->angle) return -1;
    else if(arg1->angle > arg2->angle) return 1;

    else if(arg1->dist < arg2->dist) return -1;
    else if(arg1->dist > arg2->dist) return 1;

    else if(arg1->start && !arg2->start) return -1;
    else if(!arg1->start && arg2->start) return 1;
    return 0;
}

void sortVertex(Vertex v, int size, FILE *arqSvgQ){
    VertexImp *vertices = (VertexImp *) v;

    qsort(vertices, size, sizeof(VertexImp), cmpVertex);

    Form circle;
    for(int i = 0; i < 6; i++){
        printf("%lf %lf\n", vertices[i]->x, vertices[i]->y);
        if(vertices[i]->start)
            circle = createCircle("", vertices[i]->x, vertices[i]->y, 3, "green", "green", "1");
        else
            circle = createCircle("", vertices[i]->x, vertices[i]->y, 3, "red", "red", "1");

        printCircle(arqSvgQ, circle);
    }
}