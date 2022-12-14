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

/*Inicio Getters e Setters de segmento*/
Vertex getSegmentV1(Segment s);

Vertex getSegmentV2(Segment s);

void setSegmentStartVertex(Segment s);
/*Fim Getters e Setters de segmento*/

/*Libera memoria de um segmento s*/
void freeSegment(Segment s);

#endif