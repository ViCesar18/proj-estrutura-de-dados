#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"

typedef void *Segment;
typedef void *Vertex;

Segment createSegment(Vertex v1, Vertex v2);

Vertex getSegmentV1(Segment s);

Vertex getSegmentV2(Segment s);

void setSegmentStartVertex(Segment s);

void freeSegment(Segment s);

#endif