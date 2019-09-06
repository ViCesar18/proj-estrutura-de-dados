#ifndef BOMB_H
#define BOMB_H

#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "vertex.h"
#include "segment.h"
#include "list.h"

#define PI 3.14159265359

void bombAreaRadiation(double x, double y, int capacity, List walls, List buildings, int *vectSize, FILE *arq);

#endif