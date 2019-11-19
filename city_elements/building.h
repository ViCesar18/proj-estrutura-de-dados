#ifndef BUILDING__H
#define BUILDING__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../data_structures/rbtree.h"
#include "../data_structures/hash_table.h"
#include "block.h"
#include "resident.h"

typedef void *Building;
typedef void *Block;

/*TAD dos predios*/

/*Coloca os dados de predio em uma estrutura e retorna a estrutura*/
Building createBuilding(char cep[], char face[], double num, double faceSize, double depth, double margin, Tree blocks);

/*Compara os cep's dos predios b1 e b2*/
int comparatorBuilding(Building b1, Building b2);

/*Getters e setters para a quadra*/
char *getBuildingCep(Building b);

void getBuildingInformation(Building b, char *info, char *posic);

char *getBuildingFace(Building b);

int getBuildingNum(Building b);

double getBuildingFaceSize(Building b);

double getBuildingDepth(Building b);

double getBuildingMargin(Building b);

double getBuildingX(Building b);

double getBuildingY(Building b);

double getBuildingW(Building b);

double getBuildingH(Building b);

Block getBuildingBlock(Building b);

char *getBuildingFillColor(Building b);

int getBuildingTreeX(Building b);

int getBuildingTreeY(Building b);

char *getBuildingKey(Building b);

HashTable getBuildingResidents(Building b);

bool getBuildingHasResidents(Building b);

void setBuildingBlock(Building b, Tree blocks);

void setBuildingFillCollor(Building b, char *fillColor);

void setBuildingTreeXY(Building b, int x, int y);

void setBuildingHasResidents(Building b, bool hasResidents);
/*Fim getters e setters*/

/*Libera memoria de um predio*/
void destroyBuilding(Building b);

#endif