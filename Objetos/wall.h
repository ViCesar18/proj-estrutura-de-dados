#ifndef WALL__H
#define WALL__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Wall;

/*Coloca os dados de quadra em uma estrutura e retorna a estrutura*/
Wall createWall(double x1, double y1, double x2, double y2);

/*Getters e setters para a quadra*/
double getWallX1(Wall w);

double getWallY1(Wall w);

double getWallX2(Wall w);

double getWallY2(Wall w);

/*Libera memoria de uma quadra*/
void freeWall(Wall w);

#endif