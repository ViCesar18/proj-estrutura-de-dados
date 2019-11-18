#ifndef POLYGON_H
#define POLYGON_H

#include <stdio.h>
#include <stdlib.h>
#include "segment.h"

typedef void *Polygon;

Polygon createPolygon(Segment s);

Segment getPolygonFirstSegment(Polygon p);

void destroyPolygon(Polygon p);

#endif