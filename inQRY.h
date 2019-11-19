#ifndef IN_QRY_H
#define IN_QRY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inGEO.h"
#include "queryForms.h"
#include "queryBuildings.h"
#include "queryResident.h"
#include "queryStore.h"
#include "utils/bomb.h"
#include "geometry/forms.h"
#include "data_structures/rbtree.h"
#include "data_structures/hash_table.h"
#include "queryUtils.h"
#include "queryFire.h"
#include "queryPolygon.h"

/*Le os parametros de consulta do comando "o?"*/
void scanO(FILE *arqQuery, char j[], char k[]);

/*Le os parametros de consulta do comando "i?"*/
void scanI(FILE *arqQuery, char j[], double *x, double *y);

/*Le os parametros de consulta do comando "d?"*/
void scanD(FILE *arqQuery, char j[], char k[]);

/*Le os parametros de consulta do comando "bb"*/
void scanBB(FILE *arqQuery, char suffix[], char color[]);

/*Le os parametros de consulta do comando "dq"*/
void scanDQ(FILE *arqQuery, char metric[], char id[], double *r);

/*Le os parametros de consulta do comando "cbq" e retorna um circulo com os parametros passados*/
Element scanCBQ(FILE *arqQuery, char cstrk[]);

/*Le os parametros de consulta do comando "trns" e retorna um retangulo com os parametros passados*/
Element scanTRNS(FILE *arqQuery, double *dx, double *dy);

/*Le os parametros de consulta do comando "fi" e retorna um retangulo com os parametros passados*/
void scanFI(FILE *arqQuery, double *x, double *y, int *n, double *r);

/*Le os parametros de consulta do comando "fh" e "fs" e retorna um retangulo com os parametros passados*/
void scanFHFS(FILE *arqQuery, int *k, char cep[], char face[], int *num);

/*Le os parametros de consulta do comando "brl"*/
void scanBRL(FILE *arqQuery, double *x, double *y);

void scanM (FILE *arqQuery, char cep[]);

void scanDM (FILE *arqQuery, char cpf[]);

void scanDE (FILE *arqQuery, char cnpj[]);

void scanMud (FILE *arqQuery, char cpf[], char cep[], char face[], int *num, char compl[]);

void scanDMPRBT(FILE *arqQuery, char *type, char *fileName);

void treatQueries(FILE *arqQuery, FILE *arqText, FILE *arqSvgQ, FILE *arqAux, char *nameInT, char *nameQueryT, char*PathIn, char *pathOut, int nm, int np, 
                Tree figures, Tree blocks, Tree hydrants, Tree tLights, Tree rTowers, Tree walls, Tree buildings, 
                HashTable formsTable, HashTable blocksTable, HashTable hydrantsTable, HashTable tLightsTable, HashTable rTowersTable, 
                HashTable persons, HashTable residents, HashTable stores, HashTable storeTypes);

void printQuery(FILE *arqSvgQ, FILE *arqAux, Tree figures, Tree blocks, Tree hydrants, Tree tLights, Tree rTowers, Tree buildings, Tree walls);

#endif