#ifndef QUERY_BUILDINGS__H
#define QUERY_BUILDINGS__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "operations.h"
#include "outSVG.h"
#include "./Objetos/forms.h"
#include "list.h"
#include "heapsort.h"

typedef void *Dist;

/*Remove todas as quadras que estiverem inteiramente dentro do circulo dependendo da metrica (L1 ou L2)*/
void treatDQ(FILE *arqTxt, FILE *arqSvgQ, List blocks, char metric[], Form circle);

/*Muda a cor da borda de todas as quadras que estiverem inteiramente dentro do circulo*/
void treatCBQ(FILE *arqTxt, List blocks, Form circle, char cstrk[]);

/*Move todos os equipamentos urbanos que estão inteiramente dentro do retangulo em dx no eixo X e dy no eixo Y*/
void treatTRNS(FILE *arqTxt, List blocks, List hydrants, List tLights, List rTowers, Form rect, double dx, double dy, FILE *arqSvgQ);

int cmpDoubles(const void *a, const void *b);

double getDist(Dist distAux);

void treatFI(FILE *arqTxt, double x, double y, int ns, double r, List tLights, List hydrants);

#endif