#ifndef RADIO__H
#define RADIO__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Radio;

/*Coloca os dados de radio-base em uma estrutura e retorna a estrutura*/
Radio criarRadio(char id[], double x, double y, char strokeCollor[], char fillCollor[], char sw[]);

/*Getters e setters para a radio-base*/
char *getRadioId(Radio r);

double getRadioX(Radio r);

double getRadioY(Radio r);

char *getRadioStrokeCollor(Radio r);

char *getRadioFillCollor(Radio r);

char *getRadioSw(Radio r);

void setRadioX(Radio r, double x);

void setRadioY(Radio r, double y);
/*Fim getters e setters*/

/*Libera memoria de uma quadra*/
void freeRadio(Radio r);

#endif