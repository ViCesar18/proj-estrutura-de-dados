#ifndef BOMB_H
#define BOMB_H

#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "vertex.h"
#include "segment.h"
#include "list.h"

#define PI 3.14159265359

/*Neste header encontram-se as funcoes relacionadas ao calculo e desenho da consulta brl*/

/*Funcao de comparacao passada como parametro para o qsort*/
int cmpVertex(const void *a, const void *b);

/*Retorna o segmento com vertices no centro de explosao da bomba e no vertice V*/
Segment segmentBombVertex(double xc, double yc, Vertex v, Point pontoMin, Point pontoMax);

/*Calcula a area de radiacao luminosa da bomba brl e desenha esse area no arquivo SVG*/
void bombAreaRadiation(double x, double y, int capacity, List walls, List buildings, List auxList, FILE *arq);

#endif