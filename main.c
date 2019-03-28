#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inSVG.h"
#include "structs.h"

int main(int argc, char *argv[]){
    int i = 1, j = 0;
    int nx = 1000;
    char *pathIn = NULL, *nameIn = NULL, *arqGeo = NULL;
    char *nameConsulta = NULL;
    char *pathOut = NULL, *nameOut = NULL, *arqSVG = NULL;
    char forma;
    FILE *arqIn, *arqOut;

    Formas *figuras;

    /*Recebe os parametros da main (argv)*/
    receberParametros(argc, argv, &pathIn, &nameIn, &nameConsulta, &pathOut);
    
    /*Prepara o diretorio para abrir o arquivo de entrada*/
    if(pathIn != NULL){
        if(pathIn[strlen(pathIn) - 1] == '/'){
            arqGeo = (char *)malloc((strlen(pathIn) + strlen(nameIn) + 1) * sizeof(char));
            sprintf(arqGeo, "%s%s", pathIn, nameIn);
        }
        else{
            arqGeo = (char *)malloc((strlen(pathIn) + strlen(nameIn) + 2) * sizeof(char));
            sprintf(arqGeo, "%s/%s", pathIn, nameIn);
        }

        arqIn = fopen(arqGeo, "r");
    }
    else{
        arqIn = fopen(nameIn, "r");
    }

    /*Prepara o diretorio para criar o arquivo de saida*/
    nameOut = (char *)malloc(strlen(nameIn) * sizeof(char));
    while(nameIn[j] != '.'){
        nameOut[j] = nameIn[j];
        j++;
    }
    strcat(nameOut, ".svg");
    if(pathOut[strlen(pathOut) - 1] == '/'){
        arqSVG = (char *)malloc((strlen(pathOut) + strlen(nameOut) + 1) * sizeof(char));
        sprintf(arqSVG, "%s%s", pathOut, nameOut);
    }
    else{
        arqSVG = (char *)malloc((strlen(pathOut) + strlen(nameOut) + 2) * sizeof(char));
        sprintf(arqSVG, "%s/%s", pathOut, nameOut);
    }

    arqOut = fopen(arqSVG, "w");
    fputs("<svg>\n", arqOut);

    /*Cria o vetor de structs para armazenar as dados das formas*/
    figuras = (Formas *)malloc(nx * sizeof(Formas));

    /*Le os dados das formas geometricas do arquivo de entrada*/
    while(1){
        if(feof(arqIn))
            break;

        lerFormaGeometrica(arqIn, &forma);

        if(forma == 'c'){
            lerCirculo(arqIn, figuras, arqOut);
        }
        else if(forma == 'r'){
            lerRetangulo(arqIn, figuras, arqOut);
        }
        else if(forma == 'n'){
            nx = lerNX(arqIn);
            figuras = realloc(figuras, nx * sizeof(Formas));
        }
        else if(forma == 't'){
            lerTexto(arqIn, arqOut);
        }
    }

    fputs("\n</svg>\n", arqOut);
    fclose(arqOut);
    fclose(arqIn);

    /*Libera a memoria reservada para strings e vetores*/
    free(pathIn);
    free(nameIn);
    free(nameConsulta);
    free(pathOut);
    free(nameOut);
    free(arqSVG);
    free(figuras);

    return 0;
}
