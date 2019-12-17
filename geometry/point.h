#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <stdlib.h>

/*Nesse header encontram-se todas as funcoes relacionadas a manipulacao de pontos*/

typedef void *Point;

/*Cria um ponto*/
Point createPoint(double x, double y);

int comparatorPoint(Point p1, Point p2);

/*Inicio Getters e Setters de ponto*/
double getPointX(Point p);

double getPointY(Point p);

void setPointMin(Point p, double x, double y);

void setPointMax(Point p, double x, double y);
/*Fim Getters e Setters de ponto*/

/*Libera memoria de um ponto p*/
void freePoint(Point p);

#endif