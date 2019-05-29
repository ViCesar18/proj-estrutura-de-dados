#ifndef HYDRANT__H
#define HYDRANT__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Hydrant;

Hydrant criarHydrant(char id[], double x, double y, char strokeCollor[], char fillCollor[], char sw[]);

char *getHydrantId(Hydrant h);

double getHydrantX(Hydrant h);

double getHydrantY(Hydrant h);

char *getHydrantStrokeCollor(Hydrant h);

char *getHydrantFillCollor(Hydrant h);

char *getHydrantSw(Hydrant h);

#endif