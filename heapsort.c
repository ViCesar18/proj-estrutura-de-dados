#include "heapsort.h"

void heapify(Dist vet[], int i, int heapSize){
    printf("%d %d\n", i, heapSize);
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
        printf("Aqui!\n");
        aux = vet[lowest];
        vet[lowest] = vet[i];
        vet[i] = aux;
        printf("eae\n");
        
        heapify(vet, lowest, heapSize);
    }
}

void build_heap(Dist vet[], int heapSize){
    int i;

    for(i = heapSize / 2; i >= 0; i--){
        heapify(vet, i, heapSize);
    }
}

void heap_sort(Dist vet[], int heapSize, int k){
    Dist aux;
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