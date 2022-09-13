#ifndef WALL__H
#define WALL__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/operations.h"

typedef void *Wall;

/*TAD dos muros*/

/*Coloca os dados de muro em uma estrutura e retorna a estrutura*/
Wall createWall(double x1, double y1, double x2, double y2);

/*Compara o tamanho dos muros w1 e w2*/
int comparatorWall(Wall w1, Wall w2);

/*Getters e setters para o muro*/
double getWallSize(Wall w);

void getWallInformation(Wall w, char *info, char *posic);

double getWallX1(Wall w);

double getWallY1(Wall w);

double getWallX2(Wall w);

double getWallY2(Wall w);

int getWallTreeX(Wall w);

int getWallTreeY(Wall w);

void setWallTreeXY(Wall w, int x, int y);
/*Libera memoria de um muro*/
void destroyWall(Wall w);

#endif