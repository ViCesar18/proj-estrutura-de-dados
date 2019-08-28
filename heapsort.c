#include "heapsort.h"

void heapify(double vet[], int i, int heapSize){
    double aux;
    int left, right, lowest;

    left = 2 * i + 1;
    right = 2 * i + 2;

    if(left <= heapSize && vet[left] < vet[i])
        lowest = left;
    else
        lowest = i;

    if(right <= heapSize && vet[right] < vet[lowest])
        lowest = right;

    if(lowest != i){
        aux = vet[lowest];
        vet[lowest] = vet[i];
        vet[i] = aux;
        
        heapify(vet, lowest, heapSize);
    }
}

void build_heap(double vet[], int heapSize){
    int i;

    for(i = heapSize / 2; i >= 0; i--){
        heapify(vet, i, heapSize);
    }
}

void heap_sort(double vet[], int heapSize, int k){
    double aux;
    int i;

    build_heap(vet, heapSize);

    int kNearests = heapSize - k;
    
    for(i = heapSize; i > kNearests; i--){
        aux = vet[i];
        vet[i] = vet[0];
        vet[0] = aux;
        heapSize--;

        heapify(vet, 0, heapSize);
    }
}