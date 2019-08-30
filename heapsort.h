#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <stdio.h>
#include "operations.h"
#include "queryBuildings.h"

typedef void *Dist;

void min_heapify(Dist vet[], int i, int heapSize);

void min_build_heap(Dist vet[], int heapSize);

void min_heap_sort(Dist vet[], int heapSize, int k);

void max_heapify(Dist vet[], int i, int heapSize);

void max_build_heap(Dist vet[], int heapSize);

void max_heap_sort(Dist vet[], int heapSize, int k);

#endif