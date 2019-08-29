#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <stdio.h>
#include "operations.h"
#include "queryBuildings.h"

typedef void *Dist;

void heapify(Dist vet[], int i, int heapSize);

void build_heap(Dist vet[], int heapSize);

void heap_sort(Dist vet[], int heapSize, int k);

#endif