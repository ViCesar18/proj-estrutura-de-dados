#include "segments.h"

typedef struct stSegment{
    double x1, y1, x2, y2;
} *SegmentImp;

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
    Segment segments = allocateSegments(capacity);

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

/*double getSegmentX1(Segment segmentAux, int index){
    SegmentImp *segments = (SegmentImp *) segmentAux;

    return segments[index]->x1;
}

double getSegmentY1(Segment segmentAux, int index){
    SegmentImp *segments = (SegmentImp *) segmentAux;

    return segments[index]->y1;
}

double getSegmentX2(Segment segmentAux, int index){
    SegmentImp *segments = (SegmentImp *) segmentAux;

    return segments[index]->x2;
}

double getSegmentY2(Segment segmentAux, int index){
    SegmentImp *segments = (SegmentImp *) segmentAux;

    return segments[index]->y2;
}*/