#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outSVG.h"
#include "structs.h"

void criarArqSaida(char **nameOut, char nameIn[]){
    int i = 0;

    *nameOut = (char *)malloc((strlen(nameIn) + 1) * sizeof(char));

    while(nameIn[i] != '.'){
        (*nameOut)[i] = nameIn[i];
        i++;
    }
}

void criarArqSaida2(char **nameOut, char nameIn[], char nameConsulta[]){
    int i = 0, j = 0;

    *nameOut = (char *)malloc((strlen(nameIn) + strlen(nameConsulta)) * sizeof(char));
    while(nameIn[i] != '.'){
        (*nameOut)[i] = nameIn[i];
        i++;
        j++;
    }
    strcat(*nameOut, "-");
    i = 0;
    j++;
    while(nameConsulta[i] != '.'){
        (*nameOut)[j] = nameConsulta[i];
        i++;
        j++;
    }
}

void criarArqSaida3(char **nameOut, char nameIn[], char nameConsulta[], char sufixo[]){
    int i = 0, j = 0;

    *nameOut = (char *)malloc((strlen(nameIn) + strlen(nameConsulta) + strlen(sufixo)) * sizeof(char));
    while(nameIn[i] != '.'){
        (*nameOut)[i] = nameIn[i];
        i++;
        j++;
    }
    strcat(*nameOut, "-");
    i = 0;
    j++;
    while(nameConsulta[i] != '.'){
        (*nameOut)[j] = nameConsulta[i];
        i++;
        j++;
    }
    strcat(*nameOut, "-");
    i = 0;
    j++;
    while(sufixo[i] != '\0'){
        (*nameOut)[j] = sufixo[i];
        i++;
        j++;
    }
}

/*Printa as informacoes de circulo armazenadas no vetor de struct e formatadas para SVG no arquivo SVG*/
void printarCirculo(FILE *arqOut, Formas figuras){

    fprintf(arqOut, "\n<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\"/>\n", 
    figuras.xC, figuras.yC, figuras.rC, figuras.strokeCollorC, figuras.fillCollorC);
}

/*Printa as informacoes de retangulo armazenadas no vetor de struct e formatadas para SVG no arquivo SVG*/
void printarRetangulo(FILE *arqOut, Formas figuras){

    fprintf(arqOut, "\n<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-dasharray=\"%d\"/>\n",
    figuras.xR, figuras.yR, figuras.wR, figuras.hR, figuras.strokeCollorR, figuras.fillCollorR, figuras.tracoR);
}

/*Printa as informacoes de texto armazenadas em variaveis locais no vetor de struct e formatadas para SVG no arquivo SVG*/
void printarTexto(FILE *arqOut, double x, double y, char text[]){

    fprintf(arqOut, "\n<text x=\"%lf\" y=\"%lf\">%s</text>\n", x, y, text);
}

void printarLinha(FILE *arqOut, double x1, double y1, double x2, double y2, char color[]){

    fprintf(arqOut, "\n<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\"/>\n", x1, y1, x2, y2, color);
}

void printarElipse(FILE *arqOut, double xC, double yC, double rX, double rY, char cor[]){

    fprintf(arqOut, "\n<ellipse cx=\"%lf\" cy=\"%lf\" rx=\"%lf\" ry=\"%lf\" fill=\"none\" stroke=\"%s\"/>\n", xC, yC, rX, rY, cor);
}