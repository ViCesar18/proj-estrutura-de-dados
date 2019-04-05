#ifndef CONSULTA__H
#define CONSULTA__H

#include <stdbool.h>
#include "structs.h"

/*Calcula a distancia euclidiana entre dois pontos*/
double distEuclid(double x1, double y1, double x2, double y2);

/*Determina a coordenada(x ou y), pertencente a um certo intervalo, mais proxima de uma coordenada(x ou y)*/
double clamp(double xC, double min, double max);

/*Verifica se uma figura (c ou r) esta colidindo com outra (c ou r)*/
void verificarO(FILE *txt, FILE *svg2, Formas figura1, Formas figura2);

/*Verifica se um ponto (x,y) esta dentro ou fora de uma figura (c ou r)*/
void verificarI(FILE *txt, FILE *svg2, Formas figura, double x, double y);

/*Determina a distancia entre o centro de massa de duas figuras e desenha uma linha entre elas*/
void verificarD(FILE *txt, FILE *svg2, Formas figura1, Formas figura2);

/*Desenha um quadrado em volta de todos os circulos e uma elipse dentro de todos os retangulos desenhados no svg(bounding box)*/
void verificarBB(int nx, FILE *svg3, Formas figuras[], char cor[]);

/*Desenha um retangulo que envolve dois circulos(continuo em caso de colisao, tracejado caso contrario)*/
void retanguloEnvolveCirculo(FILE *svg2, Formas figura1, Formas figura2, bool colisao);

/*Desenha um retangulo que envolve dois retangulos(continuo em caso de colisao, tracejado caso contrario)*/
void retanguloEnvolveRetangulo(FILE *svg2, Formas figura1, Formas figura2, bool colisao);

/*Desenha um retangulo que envolve um circulo e um retangulo(continuo em caso de colisao, tracejado caso contrario)*/
void retanguloEnvolveCR(FILE *svg2, Formas figura1, Formas figura2, bool colisao);

#endif