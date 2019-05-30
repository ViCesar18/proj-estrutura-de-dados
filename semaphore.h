#ifndef SEMAPHORE__H
#define SEMAPHORE__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Semaphore;

/*Coloca os dados de semaforo em uma estrutura e retorna a estrutura*/
Semaphore criarSemaphore(char id[], double x, double y, char strokeCollor[], char fillCollor[], char sw[]);

/*Getters e setters para o semaforo*/
char *getSemaphoreId(Semaphore s);

double getSemaphoreX(Semaphore s);

double getSemaphoreY(Semaphore s);

char *getSemaphoreStrokeCollor(Semaphore s);

char *getSemaphoreFillCollor(Semaphore s);

char *getSemaphoreSw(Semaphore s);

void setSemaphoreX(Semaphore s, double x);

void setSemaphoreY(Semaphore s, double y);
/*Fim getters e setters*/

/*Libera memoria de um semaforo*/
void freeSemaphore(Semaphore s);

#endif