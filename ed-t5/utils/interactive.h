#ifndef INTERACTIVE_H
#define INTERACTIVE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inQRY.h"
#include "../queryUtils.h"

void console (char *pathIn, char *pathOut, char *nameInT, int nm, int np, 
            Tree figures, Tree blocks, Tree hydrants, Tree tLights, Tree rTowers, Tree walls, Tree buildings, 
            HashTable formsTable, HashTable blocksTable, HashTable hydrantsTable, HashTable tLightsTable, HashTable rTowersTable, HashTable buildingsTable, 
            HashTable persons, HashTable residents, HashTable stores, HashTable storeTypes, Graph pathways);

#endif