#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

typedef void *Element;
typedef void *Queue;

Queue createQueue();

int getQueueSize(Queue q);

void insertQueue(Queue q, Element element);

Element removeQueue(Queue q);

void insertPrior(Queue q, Element element);

Element removePrior(Queue q);

#endif