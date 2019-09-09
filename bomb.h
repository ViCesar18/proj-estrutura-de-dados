#ifndef BOMB_H
#define BOMB_H

#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "vertex.h"
#include "segment.h"
#include "list.h"

#define PI 3.14159265359

int cmpVertex(const void *a, const void *b);

Segment buscarSegmentoFormadoComVertice(double xc, double yc, Vertex v, Point pontoMin, Point pontoMax);

void bombAreaRadiation(double x, double y, int capacity, List walls, List buildings, int *vectSize, FILE *arq);

#endif