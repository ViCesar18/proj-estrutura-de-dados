#ifndef FORMS__H
#define FORMS__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Form;
typedef void *Vertex;

/*TAD das formas*/

/*Coloca os dados de circulo em uma estrutura e retorna a estrutura*/
Form createCircle(char id[], double x, double y, double r, char strokeColor[], char fillColor[], char sw[]);

/*Coloca os dados de retangulo em uma estrutura e retorna a estrutura*/
Form createRect(char id[], double x, double y, double w, double h, char strokeColor[], char fillColor[], int stroke, char sw[]);

/*Coloca os dados de triangulo em uma estrutura e retorna a estrutura*/
Form createTriangle(double x, double y, Vertex v2, Vertex v3);

/*Getters e setters para a forma*/
char *getFormId(Form f);

int getFormStroke(Form f);

double getFormX(Form f);

double getFormY(Form f);

double getFormR(Form f);

double getFormW(Form f);

double getFormH(Form f);

Vertex getFormV2(Form f);

Vertex getFormV3(Form f);

char *getFormStrokeColor(Form f);

char *getFormFillColor(Form f);

char *getFormSw(Form f);
/*Fim getters e setters*/

/*Libera memoria de uma forma*/
void freeForm(Form f);

#endif