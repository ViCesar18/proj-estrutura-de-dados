#include "heapsort.h"

void min_heapify(Dist vet[], int i, int heapSize){
    Dist aux;
    double distI, distLeft, distRight, distLowest;
    int left, right, lowest;

    left = 2 * i + 1;
    right = 2 * i + 2;

    distI = getDist(vet[i]);
    if(left < heapSize)
        distLeft = getDist(vet[left]);

    if (right < heapSize)
        distRight = getDist(vet[right]);

    if(left < heapSize && distLeft < distI)
        lowest = left;
    else
        lowest = i;

    distLowest = getDist(vet[lowest]);

    if(right < heapSize && distRight < distLowest)
        lowest = right;

    if(lowest != i){
        aux = vet[lowest];
        vet[lowest] = vet[i];
        vet[i] = aux;
        
        min_heapify(vet, lowest, heapSize);
    }
}

void min_build_heap(Dist vet[], int heapSize){
    int i;

    for(i = heapSize / 2; i >= 0; i--){
        min_heapify(vet, i, heapSize);
    }
}

void min_heap_sort(Dist vet[], int heapSize, int k){
    Dist aux;
    int i;

    min_build_heap(vet, heapSize);

    int kNearests = heapSize - k;
    
    for(i = heapSize; i > kNearests; i--){
        aux = vet[i];
        vet[i] = vet[0];
        vet[0] = aux;
        heapSize--;

        min_heapify(vet, 0, heapSize);
    }
}

void max_heapify(Dist vet[], int i, int heapSize){
    Dist aux;
    double distI, distLeft, distRight, distLowest;
    int left, right, largest;

    left = 2 * i + 1;
    right = 2 * i + 2;

    distI = getDist(vet[i]);
    if(left < heapSize)
        distLeft = getDist(vet[left]);

    if (right < heapSize)
        distRight = getDist(vet[right]);

    if(left < heapSize && distLeft > distI)
        largest = left;
    else
        largest = i;

    distLowest = getDist(vet[largest]);

    if(right < heapSize && distRight > distLowest)
        largest = right;

    if(largest != i){
        aux = vet[largest];
        vet[largest] = vet[i];
        vet[i] = aux;
        
        max_heapify(vet, largest, heapSize);
    }
}

void max_build_heap(Dist vet[], int heapSize){
    int i;

    for(i = heapSize / 2; i >= 0; i--){
        max_heapify(vet, i, heapSize);
    }
}

void max_heap_sort(Dist vet[], int heapSize, int k){
    Dist aux;
    int i;

    max_build_heap(vet, heapSize);

    int kNearests = heapSize - k;
    
    for(i = heapSize; i > kNearests; i--){
        aux = vet[i];
        vet[i] = vet[0];
        vet[0] = aux;
        heapSize--;

        max_heapify(vet, 0, heapSize);
    }
}