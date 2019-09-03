#ifndef SEGMENTS_H
#define SEGMENTS_H

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef void *Segment;

Segment allocateSegments(int capacity);

void insertSegment(Segment segmentAux, int *size, double x1, double y1, double x2, double y2);

Segment createSegments(int capacity, List walls, List buildings, int *vectSize);

void printSegments(FILE *arqSvgQ, Segment s, int size);

/*double getSegmentX1(Segment segmentAux, int index);

double getSegmentY1(Segment segmentAux, int index);

double getSegmentX2(Segment segmentAux, int index);

double getSegmentY2(Segment segmentAux, int index);*/

#endif