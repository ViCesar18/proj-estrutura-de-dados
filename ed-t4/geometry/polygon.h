#ifndef POLYGON_H
#define POLYGON_H

#include <stdio.h>
#include <stdlib.h>
#include "segment.h"

typedef void *Segment;
typedef void *Polygon;

Polygon createPolygon();

Segment getPolygonFirstSegment(Polygon p);

double getPolygonXMax(Polygon p);

void setPolygonXMax(Polygon p, double xMax);

void insertPointPolygon(Polygon p, double x, double y);

void connectPolygon(Polygon p);

void destroyPolygon(Polygon p);

#endif