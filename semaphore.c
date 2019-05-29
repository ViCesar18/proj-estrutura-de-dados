#include "semaphore.h"

typedef struct stSemaphore{
    char id[32], strokeCollor[24], fillCollor[24], sw[12];
    double x, y;
}*SemaphoreImp;

Semaphore criarSemaphore(char id[], double x, double y, char strokeCollor[], char fillCollor[], char sw[]){
    SemaphoreImp semaphore = (SemaphoreImp) malloc(sizeof(struct stSemaphore));

    strcpy(semaphore->id, id);
    semaphore->x = x;
    semaphore->y = y;
    strcpy(semaphore->strokeCollor, strokeCollor);
    strcpy(semaphore->fillCollor, fillCollor);
    strcpy(semaphore->sw, sw);

    return semaphore;
}

char *getSemaphoreId(Semaphore s){
    SemaphoreImp semaphore = (SemaphoreImp) s;

    return semaphore->id;
}

double getSemaphoreX(Semaphore s){
    SemaphoreImp semaphore = (SemaphoreImp) s;

    return semaphore->x;
}

double getSemaphoreY(Semaphore s){
    SemaphoreImp semaphore = (SemaphoreImp) s;

    return semaphore->y;
}

char *getSemaphoreStrokeCollor(Semaphore s){
    SemaphoreImp semaphore = (SemaphoreImp) s;

    return semaphore->strokeCollor;
}

char *getSemaphoreFillCollor(Semaphore s){
    SemaphoreImp semaphore = (SemaphoreImp) s;

    return semaphore->fillCollor;
}

char *getSemaphoreSw(Semaphore s){
    SemaphoreImp semaphore = (SemaphoreImp) s;

    return semaphore->sw;
}