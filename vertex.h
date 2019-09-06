#ifndef VERTEX_H
#define VERTEX_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "operations.h"
#include "point.h"
#include "segment.h"

typedef void *Vertex;
typedef void *Segment;

Vertex createVertex(Point p, double xB, double yB);

Point getVertexV(Vertex v);

double getVertexDist(Vertex v);

double getVertexAngle(Vertex v);

bool getVertexStart(Vertex v);

void setVertexSegment(Vertex v, Segment s);

void setVertexStart(Vertex v, bool start);

void setVertexAngle(Vertex v, double angle);

void freeVertex(Vertex v);

#endif