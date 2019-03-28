#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inSVG.h"
#include "structs.h"

int main(int argc, char *argv[]){
    int i = 1, j = 0;
    int nx;
    char *pathIn = NULL, *nameIn = NULL, *arqGeo = NULL;
    char *nameConsulta = NULL;
    char *pathOut = NULL, *nameOut = NULL, *arqSVG = NULL;
    char forma;
    FILE *arqIn, *arqOut;

    Formas *figuras;

    /*Recebe os parametros da main (argv)*/
    while(i < argc){
        if(strcmp("-e", argv[i]) == 0){
            i++;
            pathIn = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(pathIn, argv[i]);
        }
        else if(strcmp("-f", argv[i]) == 0){
            i++;
            nameIn = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(nameIn, argv[i]);
        }
        else if(strcmp("-q", argv[i]) == 0){
            i++;
            nameConsulta = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(nameConsulta, argv[i]);
        }
        else if(strcmp("-o", argv[i]) == 0){
            i++;
            pathOut = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(pathOut, argv[i]);
        }
        i++;
    }
    
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
            nx = criarStruct(arqIn);
            figuras = (Formas *)malloc(nx * sizeof(Formas));
        }
        else if(forma == 't'){
            lerTexto(arqIn, arqOut);
        }
    }

    fputs("</svg>\n", arqOut);
    fclose(arqOut);
    fclose(arqIn);

    /*printf("%d\n", figuras[1].idC);
    printf("%lf\n", figuras[1].rC);
    printf("%lf\n", figuras[1].xC);
    printf("%lf\n", figuras[1].yC);
    printf("%s\n", figuras[1].strokeCollorC);
    printf("%s\n", figuras[1].fillCollorC);

    printf("%d\n", figuras[2].idR);
    printf("%lf\n", figuras[2].wR);
    printf("%lf\n", figuras[2].hR);
    printf("%lf\n", figuras[2].xR);
    printf("%lf\n", figuras[2].yR);
    printf("%s\n", figuras[2].strokeCollorR);
    printf("%s\n", figuras[2].fillCollorR);

    printf("%d\n", figuras[8].idR);
    printf("%lf\n", figuras[8].wR);
    printf("%lf\n", figuras[8].hR);
    printf("%lf\n", figuras[8].xR);
    printf("%lf\n", figuras[8].yR);
    printf("%s\n", figuras[8].strokeCollorR);
    printf("%s\n", figuras[8].fillCollorR);

    printf("%d\n", figuras[4].idC);
    printf("%lf\n", figuras[4].rC);
    printf("%lf\n", figuras[4].xC);
    printf("%lf\n", figuras[4].yC);
    printf("%s\n", figuras[4].strokeCollorC);
    printf("%s\n", figuras[4].fillCollorC);*/

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