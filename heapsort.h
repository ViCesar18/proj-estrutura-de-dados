#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <stdio.h>
#include "operations.h"
#include "queryBuildings.h"

typedef void *Dist;

/*Nesse header encontram-se as funcoes de ordenacao pelo metodo heapsort*/

/*Transforma em heap um vetor vet que alguma vez ja foi um heap (decrescente)*/
void min_heapify(Dist vet[], int i, int heapSize);

/*Constroi um heap do vetor vet em ordem decrescente*/
void min_build_heap(Dist vet[], int heapSize);

/*Ordena o vetor vet em ordem decrescente*/
void min_heap_sort(Dist vet[], int heapSize, int k);

/*Transforma em heap um vetor vet que alguma vez ja foi um heap (crescente)*/
void max_heapify(Dist vet[], int i, int heapSize);

/*Constroi um heap do vetor vet em ordem crescente*/
void max_build_heap(Dist vet[], int heapSize);

/*Ordena o vetor vet em ordem crescente*/
void max_heap_sort(Dist vet[], int heapSize, int k);

#endif