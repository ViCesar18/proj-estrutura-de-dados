#ifndef CONSULTA__H
#define CONSULTA__H

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "outSVG.h"
#include "./Objetos/forms.h"
#include "list.h"

/*Nesse header encontra-se todas as funcoes relacionadas ao arquivo de consulta(.qry), aqui são feitas as verificacoes
e os calculos matematicos*/

/*Calcula a distancia euclidiana entre dois pontos*/
double distEuclid(double x1, double y1, double x2, double y2);

/*Calcula a distancia de Manhattan entre dois pontos*/
double ManhattanDist(double x1, double y1, double x2, double y2);

/*Determina a coordenada(x ou y), pertencente a um certo intervalo, mais proxima de uma coordenada(x ou y)*/
double clamp(double xC, double min, double max);

/*Verifica se uma figura (c ou r) esta colidindo com outra (c ou r)*/
void treatO(FILE *arqTxt, FILE *arqSvgQ, Form figure1, Form figure2, char type1[], char type2[]);

/*Verifica se um ponto esta dentro de um circulo, retangulo ou quadra*/
bool pointInsideFigure(double x, double y, Element element, char type[], char met[]);

/*Verifica se um ponto (x,y) esta dentro ou fora de uma figura (c ou r)*/
void treatI(FILE *arqTxt, FILE *arqSvgQ, Form figure, double x, double y, char type[]);

/*Determina a distancia entre o centro de massa de duas figuras e desenha uma linha entre elas*/
void treatD(FILE *arqTxt, FILE *arqSvgQ, Form figure1, Form figure2, char type1[], char type2[]);

/*Desenha um quadrado em volta de todos os circulos e uma elipse dentro de todos os retangulos desenhados no svg(bounding box)*/
void treatBB(FILE *arqSvgBB, List figures, char color[]);

/*Desenha um retangulo que envolve dois circulos(continuo em caso de colisao, tracejado caso contrario)*/
void rectSurroundsCircles(FILE *arqSvgQ, Form figure1, Form figure2, bool collision);

/*Desenha um retangulo que envolve dois retangulos(continuo em caso de colisao, tracejado caso contrario)*/
void rectSurroundsRects(FILE *arqSvgQ, Form figure1, Form figure2, bool collision);

/*Desenha um retangulo que envolve um circulo e um retangulo(continuo em caso de colisao, tracejado caso contrario)*/
void rectSurroundsCircleAndRect(FILE *arqSvgQ, Form figure1, Form figure2, bool collision);

/*Retorna true se a quadra esta inteiramente dentro do circulo dependendo da metrica (L1 ou L2), false caso contrario*/
bool quadInsideCirc(Block block, Form circle, char met[]);

/*Retorna true se uma quadra esta inteiramente dentro de um retangulo, false caso contrario*/
bool quadInsideRect(Block block, Form rect);

#endif