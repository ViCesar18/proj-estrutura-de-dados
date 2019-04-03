#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inSVG.h"
#include "outSVG.h"
#include "consulta.h"
#include "structs.h"

int main(int argc, char *argv[]){
    int nx = 1000;
    char *pathIn = NULL, *nameIn = NULL, *arqGeo = NULL;
    char *nameConsulta = NULL, *arqQry = NULL;
    char *pathOut = NULL, *nameOut = NULL, *arqSVG = NULL;
    char *nameTXT, *arqTXT;
    char *nameOut2, *arqSVG2;
    char forma, q[3];
    FILE *arqIn, *arqOut, *arqConsul, *arqTexto, *arqOut2;

    int j, k;
    double x, y;
    char sufixo[30], cor[10];

    Formas *figuras;

    /*Recebe os parametros da main (argv)*/
    receberParametros(argc, argv, &pathIn, &nameIn, &nameConsulta, &pathOut);
    
    /*Prepara o diretorio para abrir os arquivos de entrada*/
    //.geo
    if(pathIn != NULL){
        alocarMemoria(nameIn, pathIn, &arqGeo);
        arqIn = fopen(arqGeo, "r");
    }
    else{
        arqIn = fopen(nameIn, "r");
    }

    //.qry, .txt e .svg(2)
    if(nameConsulta != NULL){
        if(pathIn != NULL){
            alocarMemoria(nameConsulta, pathIn, &arqQry);
            arqConsul = fopen(arqQry, "r");
        }
        else{
            arqConsul = fopen(nameConsulta, "r");
        }

        criarArqSaida2(&nameTXT, nameIn, nameConsulta);
        strcat(nameTXT, ".txt");
        alocarMemoria(nameTXT, pathOut, &arqTXT);
        arqTexto = fopen(arqTXT, "w");

        criarArqSaida2(&nameOut2, nameIn, nameConsulta);
        strcat(nameOut2, ".svg");
        alocarMemoria(nameOut2, pathOut, &arqSVG2);
        arqOut2 = fopen(arqSVG2, "w");

        fputs("<svg>\n", arqOut2);
    }

    /*Prepara o diretorio para criar o arquivo de saida*/
    //.svg(1)
    criarArqSaida(&nameOut, nameIn);
    strcat(nameOut, ".svg");
    alocarMemoria(nameOut, pathOut, &arqSVG);
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
            lerCirculo(arqIn, figuras, arqOut, arqOut2);
        }
        else if(forma == 'r'){
            lerRetangulo(arqIn, figuras, arqOut, arqOut2);
        }
        else if(forma == 'n'){
            nx = lerNX(arqIn);
            figuras = realloc(figuras, nx * sizeof(Formas));
        }
        else if(forma == 't'){
            lerTexto(arqIn, arqOut, arqOut2);
        }
    }

    if(nameConsulta != NULL){
        while(1){
            lerQry(arqConsul, q);

            if(feof(arqConsul))
                break;

            if(strcmp(q, "o?") == 0){
                lerO(arqConsul, &j, &k);
                verificarO(arqTexto, arqOut2, figuras[j], figuras[k]);
            }
            else if(strcmp(q, "i?") == 0){
                lerI(arqConsul, &j, &x, &y);
            }
            else if(strcmp(q, "d?") == 0){
                lerD(arqConsul, &j, &k);
            }
            else if(strcmp(q, "bb") == 0){
                lerBB(arqConsul, sufixo, cor);
            }
        }
    }


    /*Finalizacao e fechamento dos arquivos*/
    fputs("\n</svg>\n", arqOut);
    if(nameConsulta != NULL){
        fclose(arqConsul);
        fclose(arqTexto);
        fputs("\n</svg>\n", arqOut2);
        fclose(arqOut2);

        free(nameConsulta);
        free(nameOut2);
        free(arqSVG2);
        free(nameTXT);
        free(arqTXT);
        free(arqQry);
    }
    fclose(arqOut);
    fclose(arqIn);
 
    /*Libera a memoria reservada para strings e vetores*/
    free(pathIn);
    free(nameIn);
    free(arqGeo);
    free(pathOut);
    free(nameOut);
    free(arqSVG);
    free(figuras);

    return 0;
}
