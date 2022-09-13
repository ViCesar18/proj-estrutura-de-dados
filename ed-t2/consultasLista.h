#ifndef CONSULTAS_LISTA__H
#define CONSULTAS_LISTA__H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "consulta.h"
#include "outSVG.h"
#include "list.h"
#include "./Objetos/forms.h"
#include "./Objetos/block.h"

/*Remove todas as quadras que estiverem inteiramente dentro do circulo dependendo da metrica (L1 ou L2)*/
void treatDQ(FILE *arqTxt, FILE *arqSvgQ, List blocks, char metric[], Form circle);

/*Muda a cor da borda de todas as quadras que estiverem inteiramente dentro do circulo*/
void treatCBQ(FILE *arqTxt, List blocks, Form circle, char cstrk[]);

/*Move todos os equipamentos urbanos que estão inteiramente dentro do retangulo em dx no eixo X e dy no eixo Y*/
void treatTRNS(FILE *arqTxt, List blocks, List hydrants, List tLights, List rTowers, Form rect, double dx, double dy, FILE *arqSvgQ);

#endif