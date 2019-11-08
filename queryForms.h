#ifndef QUERY_FORMS__H
#define QUERY_FORMS__H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "operations.h"
#include "outSVG.h"
#include "./objects/forms.h"
#include "./data_structures/rbtree.h"

/*Nesse header encontram-se todas as funcoes relacionadas aos comandos de formas do arquivo de consulta(.qry), aqui são feitas as verificacoes
e os calculos matematicos*/

/*Verifica se uma figura (c ou r) esta colidindo com outra (c ou r)*/
void treatO(FILE *arqTxt, FILE *arqSvgQ, Form figure1, Form figure2);

/*Verifica se um ponto (x,y) esta dentro ou fora de uma figura (c ou r)*/
void treatI(FILE *arqTxt, FILE *arqSvgQ, Form figure, double x, double y);

/*Determina a distancia entre o centro de massa de duas figuras e desenha uma linha entre elas*/
void treatD(FILE *arqTxt, FILE *arqSvgQ, Form figure1, Form figure2);

/*Desenha um quadrado em volta de todos os circulos e uma elipse dentro de todos os retangulos desenhados no svg(bounding box)*/
void treatBB(FILE *arqSvgBB, Tree figures, char color[]);

#endif