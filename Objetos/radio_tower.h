#ifndef RADIO_TOWER__H
#define RADIO_TOWER__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *RadioTower;

/*TAD das torres de radio*/

/*Coloca os dados de radio-base em uma estrutura e retorna a estrutura*/
RadioTower createRadioTower(char id[], double x, double y, char strokeColor[], char fillColor[], char sw[]);

/*Getters e setters para a radio-base*/
char *getRadioTowerId(RadioTower r);

double getRadioTowerX(RadioTower r);

double getRadioTowerY(RadioTower r);

char *getRadioTowerStrokeColor(RadioTower r);

char *getRadioTowerFillColor(RadioTower r);

char *getRadioTowerSw(RadioTower r);

void setRadioTowerX(RadioTower r, double x);

void setRadioTowerY(RadioTower r, double y);
/*Fim getters e setters*/

/*Libera memoria de uma quadra*/
void freeRadioTower(RadioTower r);

#endif