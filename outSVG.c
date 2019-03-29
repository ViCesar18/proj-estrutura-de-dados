#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outSVG.h"
#include "structs.h"

void criarArqSaida(char **nameOut, char nameIn[]){
    int i = 0;

    *nameOut = (char *)malloc(strlen(nameIn) * sizeof(char));
    while(nameIn[i] != '.'){
        (*nameOut)[i] = nameIn[i];
        i++;
    }
}

/*Printa as informacoes de circulo armazenadas no vetor de struct e formatadas para SVG no arquivo SVG*/
void printarCirculo(FILE *arqOut, Formas figuras){

    fprintf(arqOut, "\n<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\"/>\n", 
    figuras.xC, figuras.yC, figuras.rC, figuras.strokeCollorC, figuras.fillCollorC);
}

/*Printa as informacoes de retangulo armazenadas no vetor de struct e formatadas para SVG no arquivo SVG*/
void printarRetangulo(FILE *arqOut, Formas figuras){

    fprintf(arqOut, "\n<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\"/>\n",
    figuras.xR, figuras.yR, figuras.wR, figuras.hR, figuras.strokeCollorR, figuras.fillCollorR);
}

/*Printa as informacoes de texto armazenadas em variaveis locais no vetor de struct e formatadas para SVG no arquivo SVG*/
void printarTexto(FILE *arqOut, double x, double y, char text[]){

    fprintf(arqOut, "\n<text x=\"%lf\" y=\"%lf\">%s</text>\n", x, y, text);
}