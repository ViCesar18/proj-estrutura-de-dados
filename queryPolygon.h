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

void treatCATAC(FILE *arqSVG, FILE *arqTxt, char *fName, char *pathIn, Tree blocks, Tree hydrants, Tree tLights, 
                Tree rTowers, Tree buildings, HashTable blocksTable, HashTable hydrantsTable, HashTable tLightsTable, HashTable rTowersTable, 
                HashTable buildingsTable, HashTable residents);

#endif