#ifndef SEMAPHORE__H
#define SEMAPHORE__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Semaphore;

Semaphore criarSemaphore(char id[], double x, double y, char strokeCollor[], char fillCollor[], char sw[]);

char *getSemaphoreId(Semaphore s);

double getSemaphoreX(Semaphore s);

double getSemaphoreY(Semaphore s);

char *getSemaphoreStrokeCollor(Semaphore s);

char *getSemaphoreFillCollor(Semaphore s);

char *getSemaphoreSw(Semaphore s);

void setSemaphoreX(Semaphore s, double x);

void setSemaphoreY(Semaphore s, double y);

#endif