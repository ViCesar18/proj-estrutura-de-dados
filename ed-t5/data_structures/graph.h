#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "priority_queue.h"
#include "../geometry/forms.h"
#include "../outSVG.h"

typedef void *GVertex;
typedef void *Edge;
typedef void *GNode;
typedef void *Graph;

Graph createGraph(int size);

double getGraphVertexDist(GNode n);

int getGraphFree(Graph g);

GNode getGraphNode(Graph g, int i);

char *getGraphNodeId(GNode n);

double getGraphNodeX(GNode n);

double getGraphNodeY(GNode n);

GVertex getGraphNodeP(GNode n);

double getGraphVertexX(GVertex v);

double getGraphVertexY(GVertex v);

GNode getGraphVertexNode(GVertex v);

bool addVertex(Graph g, char *id, double x, double y);

bool addEdge(Graph g, char *id1, char *id2, char *street, char *bR, char *bL, double length, double speed);

bool depthSearch(Graph g, char *id);

bool widthSearch(Graph g, char *id);

bool shortestWat_Dijkstra(Graph g, char *id, bool itsSpeed);

void printGraphVertexInformation(FILE *arqSVG, Graph g);

void destroyGraph(Graph g);

#endif