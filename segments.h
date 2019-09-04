#ifndef SEGMENTS_H
#define SEGMENTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "operations.h"
#include "list.h"

typedef void *Segment;
typedef void *Vertex;

Segment allocateSegments(int capacity);

void insertSegment(Segment segmentAux, int *size, double x1, double y1, double x2, double y2);

Segment createSegments(int capacity, List walls, List buildings, int *vectSize);

void printSegments(FILE *arqSvgQ, Segment s, int size);

Vertex createVertices(double x, double y, int capacity, Segment s, int size, FILE *arqSvgQ);

int cmpVertex(const void *a, const void *b);

void sortVertex(Vertex v, int size, FILE *arqSvgQ);

#endif