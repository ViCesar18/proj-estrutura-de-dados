#include <stdio.h>
#include "outSVG.h"
#include "structs.h"

void printarCirculo(FILE *arqOut, Formas figuras){

    fprintf(arqOut, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\"/>", 
    figuras.xC, figuras.yC, figuras.rC, figuras.strokeCollorC, figuras.fillCollorC);
}

void printarRetangulo(FILE *arqOut, Formas figuras){

    fprintf(arqOut, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\"/>",
    figuras.xR, figuras.yR, figuras.wR, figuras.hR, figuras.strokeCollorR, figuras.fillCollorR);
}

void printarTexto(FILE *arqOut, double x, double y, char text[]){

    fprintf(arqOut, "<text x=\"%lf\" y=\"%lf\">%s</text>", x, y, text);
}