#ifndef RADIO__H
#define RADIO__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Radio;

Radio criarRadio(char id[], double x, double y, char strokeCollor[], char fillCollor[], char sw[]);

char *getRadioId(Radio r);

double getRadioX(Radio r);

double getRadioY(Radio r);

char *getRadioStrokeCollor(Radio r);

char *getRadioFillCollor(Radio r);

char *getRadioSw(Radio r);

void setRadioX(Radio r, double x);

void setRadioY(Radio r, double y);

#endif