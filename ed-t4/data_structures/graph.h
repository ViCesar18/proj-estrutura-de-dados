#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "priority_queue.h"

typedef void *GVertex;
typedef void *Edge;
typedef void *GNode;
typedef void *Graph;

Graph createGraph(int size);

double getGraphVertexDist(GNode n);

bool addVertex(Graph g, char *id, double x, double y);

bool addEdge(Graph g, char *id1, char *id2, char *street, char *bR, char *bL, double length, double speed);

void destroyGraph(Graph g);

#endif