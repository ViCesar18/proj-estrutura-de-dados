#ifndef RADIO_TOWER__H
#define RADIO_TOWER__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *RadioTower;

/*TAD das torres de radio*/

/*Coloca os dados de radio-base em uma estrutura e retorna a estrutura*/
RadioTower createRadioTower(char id[], double x, double y, char strokeColor[], char fillColor[], char sw[]);

/*Compara os id's das torres de radio rb1 e rb2*/
int comparatorRadioTower(RadioTower rb1, RadioTower rb2);

/*Getters e setters para a radio-base*/
char *getRadioTowerId(RadioTower r);

void getRadioTowerInformation(RadioTower r, char *info, char *posic);

double getRadioTowerX(RadioTower r);

double getRadioTowerY(RadioTower r);

char *getRadioTowerStrokeColor(RadioTower r);

char *getRadioTowerFillColor(RadioTower r);

char *getRadioTowerSw(RadioTower r);

void setRadioTowerX(RadioTower r, double x);

void setRadioTowerY(RadioTower r, double y);
/*Fim getters e setters*/

/*Libera memoria de uma quadra*/
void destroyRadioTower(RadioTower r);

#endif