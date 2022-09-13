#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inSVG.h"
#include "outSVG.h"
#include "consulta.h"
#include "structs.h"

int main(int argc, char *argv[]){
    int nx = 1000;
    char *pathIn = NULL, *nameIn = NULL, *nameInT = NULL, *arqGeo = NULL;
    char *nameConsulta = NULL, *nameConsultaT = NULL, *arqQry = NULL;
    char *pathOut = NULL, *nameOut = NULL, *arqSVG = NULL;
    char *nameTXT = NULL, *arqTXT = NULL;
    char *nameOut2 = NULL, *arqSVG2 = NULL;
    char *nameOut3 = NULL, *arqSVG3 = NULL;
    char forma, q[3];
    FILE *arqIn = NULL, *arqOut = NULL, *arqConsul = NULL, *arqTexto = NULL, *arqOut2 = NULL, *arqOut3 = NULL;

    int j, k;
    double x, y;
    char sufixo[32], cor[16];

    Formas *figuras;

    /*Recebe os parametros da main (argv)*/
    receberParametros(argc, argv, &pathIn, &nameIn, &nameConsulta, &pathOut);

    /*Trata o nome do arquivo de entrada se ele for um diretorio relativo*/
    tratarNome(nameIn, &nameInT);
    
    /*Prepara o diretorio para abrir os arquivos de entrada*/
    //.geo
    if(pathIn != NULL){
        alocarMemoria(nameIn, pathIn, &arqGeo);
        arqIn = fopen(arqGeo, "r");
        verificarArquivo(arqIn, arqGeo);
    }
    else{
        arqIn = fopen(nameIn, "r");
        verificarArquivo(arqIn, nameIn);
    }
    
    //.qry, .txt e .svg(2)(se existir)
    if(nameConsulta != NULL){
        tratarNome(nameConsulta, &nameConsultaT);

        if(pathIn != NULL){
            alocarMemoria(nameConsulta, pathIn, &arqQry);
            arqConsul = fopen(arqQry, "r");
            verificarArquivo(arqConsul, arqQry);
        }
        else{
            arqConsul = fopen(nameConsulta, "r");
            verificarArquivo(arqConsul, nameConsulta);
        }

        criarArqSaida2(&nameTXT, nameInT, nameConsultaT);
        strcat(nameTXT, ".txt");
        alocarMemoria(nameTXT, pathOut, &arqTXT);
        arqTexto = fopen(arqTXT, "w");
        verificarArquivo(arqTexto, arqTXT);

        criarArqSaida2(&nameOut2, nameInT, nameConsultaT);
        strcat(nameOut2, ".svg");
        alocarMemoria(nameOut2, pathOut, &arqSVG2);
        arqOut2 = fopen(arqSVG2, "w");
        verificarArquivo(arqOut2, arqSVG2);

        fputs("<svg>\n", arqOut2);
    }
    
    /*Prepara o diretorio para criar o arquivo de saida*/
    //.svg(1)
    criarArqSaida(&nameOut, nameInT);
    strcat(nameOut, ".svg");
    alocarMemoria(nameOut, pathOut, &arqSVG);
    arqOut = fopen(arqSVG, "w");
    verificarArquivo(arqOut, arqSVG);

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
    
    /*Le os dados de consulta(se existir)*/
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
                verificarI(arqTexto, arqOut2, figuras[j], x, y);
            }
            else if(strcmp(q, "d?") == 0){
                lerD(arqConsul, &j, &k);
                verificarD(arqTexto, arqOut2, figuras[j], figuras[k]);
            }
            else if(strcmp(q, "bb") == 0){
                lerBB(arqConsul, sufixo, cor);
                criarArqSaida3(&nameOut3, nameInT, nameConsultaT, sufixo);
                strcat(nameOut3, ".svg");
                alocarMemoria(nameOut3, pathOut, &arqSVG3);
                arqOut3 = fopen(arqSVG3, "w");
                verificarArquivo(arqOut3, arqSVG3);
                verificarBB(nx, arqOut3, figuras, cor);
                fclose(arqOut3);
                free(nameOut3);
                free(arqSVG3);
            }
        }
    }

    /*Finalizacao, libreracao de memoria e fechamento dos arquivos*/
    fputs("\n</svg>\n", arqOut);
    if(nameConsulta != NULL){
        fclose(arqConsul);
        fclose(arqTexto);
        fputs("\n</svg>\n", arqOut2);
        fclose(arqOut2);

        free(nameConsulta);
        free(nameConsultaT);
        free(nameOut2);
        free(arqSVG2);
        free(nameTXT);
        free(arqTXT);
        free(arqQry);
    }
    fclose(arqOut);
    fclose(arqIn);
 
    free(pathIn);
    free(nameIn);
    free(nameInT);
    free(arqGeo);
    free(pathOut);
    free(nameOut);
    free(arqSVG);
    free(figuras);

    return 0;
}
