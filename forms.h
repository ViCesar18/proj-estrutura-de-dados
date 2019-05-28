#ifndef FORMS__H
#define FORMS__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Form;

Form criarCirculo(int id, double x, double y, double r, char strokeCollor[], char fillCollor[]);

Form criarRect(int id, double x, double y, double w, double h, char strokeCollor[], char fillCollor[], int stroke);

int getFormId(Form f);

int getFormStroke(Form f);

char getFormType(Form f);

double getFormX(Form f);

double getFormY(Form f);

double getFormR(Form f);

double getFormW(Form f);

double getFormH(Form f);

char *getFormStrokeCollor(Form f);

char *getFormFillCollor(Form f);

#endif