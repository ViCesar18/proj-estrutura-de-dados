#ifndef OPERATIONS__H
#define OPERATIONS__H

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "../geometry/forms.h"
#include "../queryBuildings.h"
#include "../geometry/point.h"
#include "../geometry/segment.h"
#include "../data_structures/rbtree.h"
#include "../city_elements/block.h"
#include "../geometry/polygon.h"

/*Nesse header encontram-se todas as oprecoes utilizadas por outras funcoes em todo o resto do programa*/

typedef void *Dist;
typedef void *Segment;
typedef void *Polygon;

/*Calcula a distancia euclidiana entre dois pontos*/
double distEuclid(double x1, double y1, double x2, double y2);

/*Calcula a distancia de Manhattan entre dois pontos*/
double ManhattanDist(double x1, double y1, double x2, double y2);

/*Determina a coordenada(x ou y), pertencente a um certo intervalo, mais proxima de uma coordenada(x ou y)*/
double clamp(double xC, double min, double max);

/*Verifica se um ponto esta dentro de um circulo, retangulo ou quadra*/
bool pointInsideFigure(double x, double y, Element element, char type[], char met[]);

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

/*Inverte o vetor vet*/
void reverseVector(Dist vet[], int size);

/*Verifica a virada a esquerda do segmento AB com o ponto C*/
bool checkLeftTurn(Point a, Point b, Point c);

/*Verifica se dois segmentos se interceptao*/
bool checkSegmentsIntersection(Segment s1, Segment s2);

/*Retorna o ponto de intercessao*/
void segmentIntersection(Segment s1, Segment s2, double *x, double *y);

bool pointInsidePolygon(Point point, Polygon polygon);

bool rectInsidePolygon(Form rect, Polygon polygon);

#endif