#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"

/*Nesse header encontram-se todas as funcoes relacionadas a manipulacao de segmentos*/

typedef void *Segment;
typedef void *Vertex;

/*Cria um segmento*/
Segment createSegment(Vertex v1, Vertex v2);

int comparatorSegment(Segment s1, Segment s2);

/*Inicio Getters e Setters de segmento*/
Vertex getSegmentV1(Segment s);

Vertex getSegmentV2(Segment s);

Segment getSegmentProx(Segment s);

Vertex getSegmentVStart(Segment s);

Vertex getSegmentVEnd(Segment s);

double getSegmentDistance(Segment s);

double getSegmentXBiombo(Segment s);

double getSegmentYBiombo(Segment s);

void setSegmentStartVertex(Segment s);

void setSegmentProx(Segment s, Segment prox);

void setSegmentXYBiombo(Segment s, double x, double y);

void setSegmentDistance(Segment s, double dist);
/*Fim Getters e Setters de segmento*/

/*Libera memoria de um segmento s*/
void freeSegment(Segment s);

#endif