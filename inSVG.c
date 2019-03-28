#include <stdio.h>
#include <stdlib.h>
#include "inSVG.h"
#include "structs.h"
#include "outSVG.h"

int criarStruct(FILE *arq){
    int nx;

    fgetc(arq);
    fscanf(arq, "%d", &nx);

    return nx;

}

void lerFormaGeometrica(FILE *arq, char *forma){

    fscanf(arq, "%c", forma);
}

void lerCirculo(FILE *arqIn, Formas figuras[], FILE *arqOut){
    int id;

    fscanf(arqIn, "%d", &id);
    figuras[id].idC = id;
    fscanf(arqIn, "%lf", &figuras[id].rC);
    fscanf(arqIn, "%lf", &figuras[id].xC);
    fscanf(arqIn, "%lf", &figuras[id].yC);
    fscanf(arqIn, "%s", figuras[id].strokeCollorC);
    fscanf(arqIn, "%s", figuras[id].fillCollorC);

    printarCirculo(arqOut, figuras[id]);

}

void lerRetangulo(FILE *arqIn, Formas figuras[], FILE *arqOut){
    int id;

    fscanf(arqIn, "%d", &id);
    figuras[id].idR = id;
    fscanf(arqIn, "%lf", &figuras[id].wR);
    fscanf(arqIn, "%lf", &figuras[id].hR);
    fscanf(arqIn, "%lf", &figuras[id].xR);
    fscanf(arqIn, "%lf", &figuras[id].yR);
    fscanf(arqIn, "%s", figuras[id].strokeCollorR);
    fscanf(arqIn, "%s", figuras[id].fillCollorR);

    printarRetangulo(arqOut, figuras[id]);

}

void lerTexto(FILE *arqIn, FILE *arqOut){
    double x, y;
    char text[30];

    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);
    fscanf(arqIn, "%s", text);

    printarTexto(arqOut, x, y, text);
}