#ifndef IN_QRY_H
#define IN_QRY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inSVG.h"
#include "queryForms.h"
#include "queryBuildings.h"
#include "queryResident.h"
#include "queryStore.h"
#include "bomb.h"
#include "objects/forms.h"
#include "data_structures/rbtree.h"
#include "data_structures/hash_table.h"
#include "queryUtils.h"

void treatQueries(FILE *arqQuery, FILE *arqText, FILE *arqSvgQ, FILE *arqAux, char *nameInT, char *nameQueryT, char *pathOut, int nm, int np, 
                Tree figures, Tree blocks, Tree hydrants, Tree tLights, Tree rTowers, Tree walls, Tree buildings, 
                HashTable formsTable, HashTable blocksTable, HashTable hydrantsTable, HashTable tLightsTable, HashTable rTowersTable, 
                HashTable persons, HashTable residents, HashTable stores, HashTable storeTypes);

void printQuery(FILE *arqSvgQ, FILE *arqAux, Tree figures, Tree blocks, Tree hydrants, Tree tLights, Tree rTowers, Tree buildings, Tree walls);

#endif