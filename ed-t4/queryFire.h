#ifndef QUERY_FIRE
#define QUERY_FIRE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils/operations.h"
#include "outSVG.h"
#include "sort/heapsort.h"
#include "./geometry/forms.h"
#include "./data_structures/rbtree.h"
#include "./data_structures/hash_table.h"

typedef void* Element;
typedef void* Dist;
typedef void* Tree;

/*Retorna a distancia armazenada em uma na estrutura*/
double getDist(Dist distAux);

/*Identifica os ns semaforos mais proximos e os hidrantes em um raio r do foco de incendio (x, y)*/
void treatFI(FILE *arqSvg, FILE *arqTxt, double x, double y, int ns, double r, Tree tLights, Tree hydrants);

/*Retorna o ponto de endereco (x, y) de um determinado predio*/
void getAddress(char cep[], char face[], int num, double *x, double *y, HashTable blocksTable);

/*Identifica os k hidrantes mais proximos ou mais distantes de um determinado ponto (x, y)*/
void treatFH(FILE *arqTxt, FILE *arqSvg, Tree hydrants, int k, double x, double y);

/*Identifica os k semaforos mais proximos de um determinado ponto (x, y)*/
void treatFS(FILE *arqTxt, FILE *arqSvg, Tree hydrantRoot, int k, double x, double y);

#endif