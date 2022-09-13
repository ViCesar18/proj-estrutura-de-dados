#ifndef HYDRANT__H
#define HYDRANT__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Hydrant;

/*Coloca os dados de hidrante em uma estrutura e retorna a estrutura*/
Hydrant createHydrant(char id[], double x, double y, char strokeColor[], char fillColor[], char sw[]);

/*Getters e setters para o hidrante*/
char *getHydrantId(Hydrant h);

double getHydrantX(Hydrant h);

double getHydrantY(Hydrant h);

char *getHydrantStrokeColor(Hydrant h);

char *getHydrantFillColor(Hydrant h);

char *getHydrantSw(Hydrant h);

void setHydrantX(Hydrant h, double x);

void setHydrantY(Hydrant h, double y);
/*Fim getters e setters*/

/*Libera memoria de um hidrante*/
void freeHydrant(Hydrant h);

#endif