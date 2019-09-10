#ifndef VERTEX_H
#define VERTEX_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "operations.h"
#include "point.h"
#include "segment.h"

/*Nesse header encontram-se todas as funcoes relacionadas com a manipulacao de vertices*/

typedef void *Vertex;
typedef void *Segment;

/*Cria um vertice*/
Vertex createVertex(Point p, double xB, double yB);

/*Inicio Getters e Setters de vertice*/
Point getVertexV(Vertex v);

double getVertexDist(Vertex v);

double getVertexAngle(Vertex v);

bool getVertexStart(Vertex v);

Segment getVertexSegment(Vertex v);

void setVertexSegment(Vertex v, Segment s);

void setVertexStart(Vertex v, bool start);

void setVertexAngle(Vertex v, double angle);
/*Fim Getters e Setters de vertice*/

/*Libera memoria de um vertice v*/
void freeVertex(Vertex v);

#endif