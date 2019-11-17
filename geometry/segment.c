#include "segment.h"

#define PI 3.14159265

typedef struct stSegment{
    Vertex v1;
    Vertex v2;
} *SegmentImp;

Segment createSegment(Vertex v1, Vertex v2){
    SegmentImp segment = (SegmentImp) malloc(sizeof(struct stSegment));

    segment->v1 = v1;
    segment->v2 = v2;

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

void freeSegment(Segment s){
    SegmentImp segment = (SegmentImp) s;
    
    freeVertex(segment->v1);
    freeVertex(segment->v2);
    free(segment);
}