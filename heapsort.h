#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <stdio.h>

void heapify(double vet[], int i, int heapSize);

void build_heap(double vet[], int heapSize);

void heap_sort(double vet[], int heapSize, int k);

#endif