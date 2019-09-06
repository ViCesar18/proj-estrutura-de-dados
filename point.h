#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <stdlib.h>

typedef void *Point;

Point createPoint(double x, double y);

double getPointX(Point p);

double getPointY(Point p);

void setPointMin(Point p, double x, double y);

void setPointMax(Point p, double x, double y);

void freePoint(Point p);

#endif