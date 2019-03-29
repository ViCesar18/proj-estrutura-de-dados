#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inSVG.h"
#include "structs.h"
#include "outSVG.h"

void receberParametros(int argc, char *argv[], char **pathIn, char **nameIn, char **nameConsulta, char **pathOut){
    int i = 1;

    while(i < argc){
        if(strcmp("-e", argv[i]) == 0){
            i++;
            *pathIn = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*pathIn, argv[i]);
        }
        else if(strcmp("-f", argv[i]) == 0){
            i++;
            *nameIn = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*nameIn, argv[i]);
        }
        else if(strcmp("-q", argv[i]) == 0){
            i++;
            *nameConsulta = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*nameConsulta, argv[i]);
        }
        else if(strcmp("-o", argv[i]) == 0){
            i++;
            *pathOut = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*pathOut, argv[i]);
        }
        i++;
    }
}

void alocarMemoria(char nome[], char dir[], char **arq){

    if(dir[strlen(dir) - 1] == '/'){
        *arq = (char *)malloc((strlen(dir) + strlen(nome) + 1) * sizeof(char));
        sprintf(*arq, "%s%s", dir, nome);
    }
    else{
        *arq = (char *)malloc((strlen(dir) + strlen(nome) + 2) * sizeof(char));
        sprintf(*arq, "%s/%s", dir, nome);
    }
}

int lerNX(FILE *arq){
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