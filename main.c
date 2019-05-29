#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inSVG.h"
#include "outSVG.h"
#include "consulta.h"
#include "lista.h"
#include "forms.h"
#include "consultasLista.h"

int main(int argc, char *argv[]){
    int nx = 1000, nq = 1000, nh = 1000, ns = 1000, nr = 1000;
    char *pathIn = NULL, *nameIn = NULL, *nameInT = NULL, *arqGeo = NULL;
    char *nameConsulta = NULL, *nameConsultaT = NULL, *arqQry = NULL;
    char *pathOut = NULL, *nameOut = NULL, *arqSVG = NULL;
    char *nameTXT = NULL, *arqTXT = NULL;
    char *nameOut2 = NULL, *arqSVG2 = NULL;
    char *nameOut3 = NULL, *arqSVG3 = NULL;
    char command[12];
    FILE *arqIn = NULL, *arqOut = NULL, *arqConsul = NULL, *arqTexto = NULL, *arqOut2 = NULL, *arqOut3 = NULL;

    char j[32], k[32];
    double x, y;
    char sufixo[32], cor[24];

    char metrica[4], id[32];
    double r;

    char cfillQ[24], cstrkQ[24], cfillH[24], cstrkH[24], cfillS[24], cstrkS[24], cfillR[24], cstrkR[24];
    char swQ[12], swH[12], swS[12], swR[12];
    char cw[12] = {"1"}, rw[12] = {"1"};

    strcpy(cfillQ, "orange");
    strcpy(cstrkQ, "black");
    strcpy(cfillH, "red");
    strcpy(cstrkH, "yellow");
    strcpy(cfillS, "green");
    strcpy(cstrkS, "red");
    strcpy(cfillR, "gray");
    strcpy(cstrkR, "black");

    Lista figuras, blocks, hydrants, semaphores, radios;
    Form figura1, figura2;
    char type1[4], type2[4];

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

    /*Procura o NX*/
    while(1){
        if(feof(arqIn))
            break;

        fscanf(arqIn, "%s", command);
        
        if(!strcmp(command, "nx")){
            lerNX(arqIn, &nx, &nq, &nh, &ns, &nr);
            break;
        }
    }

    rewind(arqIn);

    /*Cria as listas*/
    figuras = criarLista(nx);
    blocks = criarLista(nq);
    hydrants = criarLista(nh);
    semaphores = criarLista(ns);
    radios = criarLista(nr);
    
    /*Le os dados das formas geometricas do arquivo de entrada*/
    while(1){
        if(feof(arqIn))
            break;

        fscanf(arqIn, "%s", command);

        if(!strcmp(command, "c")){
            lerCirculo(arqIn, figuras, cw);
        }
        else if(!strcmp(command, "r")){
            lerRetangulo(arqIn, figuras, rw);
        }
        else if(!strcmp(command, "t")){
            lerTexto(arqIn, arqOut, arqOut2);
        }
        else if(!strcmp(command, "q")){
            lerQuadra(arqIn, blocks, cfillQ, cstrkQ, swQ);
        }
        else if(!strcmp(command, "h")){
            lerHidrante(arqIn, hydrants, cfillH, cstrkH, swH);
        }
        else if(!strcmp(command, "s")){
            lerSemaforo(arqIn, semaphores, cfillS, cstrkS, swS);
        }
        else if(!strcmp(command, "rb")){
            lerRadio(arqIn, radios, cfillR, cstrkR, swR);
        }
        else if(!strcmp(command, "cq")){
            alterarCor(arqIn, cfillQ, cstrkQ, swQ);
        }
        else if(!strcmp(command, "ch")){
            alterarCor(arqIn, cfillH, cstrkH, swH);
        }
        else if(!strcmp(command, "cr")){
            alterarCor(arqIn, cfillR, cstrkR, swR);
        }
        else if(!strcmp(command, "cs")){
            alterarCor(arqIn, cfillS, cstrkS, swS);
        }
        else if(!strcmp(command, "sw")){
            alterarEspessura(arqIn, cw, rw);
        }
    }
    
    imprimirLista(figuras, arqOut);
    imprimirLista(blocks, arqOut);
    imprimirLista(hydrants, arqOut);
    imprimirLista(semaphores, arqOut);
    imprimirLista(radios, arqOut);

    if(arqOut2 != NULL)
        imprimirLista(figuras, arqOut2);
    
    /*Le os dados de consulta(se existir)*/
    if(nameConsulta != NULL){
        while(1){
            fscanf(arqConsul, "%s", command);

            if(feof(arqConsul))
                break;

            if(!strcmp(command, "o?")){
                lerO(arqConsul, j, k);
                figura1 = getElementoById(figuras, j, type1);
                figura2 = getElementoById(figuras, k, type2);
                verificarO(arqTexto, arqOut2, figura1, figura2, type1, type2);
            }
            else if(!strcmp(command, "i?")){
                lerI(arqConsul, j, &x, &y);
                figura1 = getElementoById(figuras, j, type1);
                verificarI(arqTexto, arqOut2, figura1, x, y, type1);
            }
            else if(!strcmp(command, "d?")){
                lerD(arqConsul, j, k);
                figura1 = getElementoById(figuras, j, type1);
                figura2 = getElementoById(figuras, k, type2);
                verificarD(arqTexto, arqOut2, figura1, figura2, type1, type2);
            }
            else if(!strcmp(command, "bb")){
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
            else if(!strcmp(command, "dq")){
                lerDQ(arqConsul, metrica, id, &r);
                figura1 = getElementoByIdListas(blocks, hydrants, semaphores, radios, id, type1);
                if(!strcmp(type1, "h")){
                    x = getHydrantX(figura1);
                    y = getHydrantY(figura1);
                    strcpy(id, getHydrantId(figura1));
                }
                else if(!strcmp(type1, "s")){
                    x = getSemaphoreX(figura1);
                    y = getSemaphoreY(figura1);
                    strcpy(id, getSemaphoreId(figura1));
                }
                else if(!strcmp(type1, "rb")){
                    x = getRadioX(figura1);
                    y = getRadioY(figura1);
                    strcpy(id, getRadioId(figura1));
                }
                Form circulo = criarCirculo(id, x, y, r, "black", "none", "1");
                verificarDQ(arqTexto, arqOut2, blocks, metrica, circulo);
            }
            else if(!strcmp(command, "del")){
                fscanf(arqConsul, "%s", id);
                figura1 = getElementoByIdListas(blocks, hydrants, semaphores, radios, id, type1);
                if(!strcmp(type1, "h"))
                    deletarElemento(hydrants, id);
                else if(!strcmp(type1, "s"))
                    deletarElemento(semaphores, id);
                else if(!strcmp(type1, "rb"))
                    deletarElemento(radios, id);
                else if(!strcmp(type1, "q"))
                    deletarElemento(blocks, id);
            }
        }
    }
    if(arqOut2 != NULL){
        imprimirLista(blocks, arqOut2);
        imprimirLista(hydrants, arqOut2);
        imprimirLista(semaphores, arqOut2);
        imprimirLista(radios, arqOut2);
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
