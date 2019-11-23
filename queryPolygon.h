#ifndef QUERY_POLYGON_H
#define QUERY_POLYGON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "inGEO.h"
#include "geometry/point.h"
#include "geometry/vertex.h"
#include "geometry/segment.h"
#include "geometry/polygon.h"

void treatMPLG(FILE *arqSVG, FILE *arqTxt, char *fName, char *pathIn, Tree blocks, Tree buildings);

void treatEPLG(FILE *arqSVG, FILE *arqTxt, char *fName, char *storeType, char *pathIn, HashTable stores);

#endif