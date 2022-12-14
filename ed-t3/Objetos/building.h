#ifndef BUILDING__H
#define BUILDING__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Building;

/*TAD dos predios*/

/*Coloca os dados de predio em uma estrutura e retorna a estrutura*/
Building createBuilding(char cep[], char face[], double num, double faceSize, double depth, double margin);

/*Getters e setters para a quadra*/
char *getBuildingCep(Building b);

char *getBuildingFace(Building b);

int getBuildingNum(Building b);

double getBuildingFaceSize(Building b);

double getBuildingDepth(Building b);

double getBuildingMargin(Building b);

double getBuildingX(Building b);

double getBuildingY(Building b);

double getBuildingW(Building b);

double getBuildingH(Building b);

void setBuildingX(Building b, double x);

void setBuildingY(Building b, double y);

void setBuildingW(Building b, double w);

void setBuildingH(Building b, double h);
/*Fim getters e setters*/

/*Libera memoria de um predio*/
void freeBuilding(Building b);

#endif