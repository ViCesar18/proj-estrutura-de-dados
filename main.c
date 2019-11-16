#ifndef PRINCIPAL
#define PRINCIPAL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inSVG.h"
#include "outSVG.h"
#include "queryForms.h"
#include "queryBuildings.h"
#include "./data_structures/rbtree.h"
#include "objects/forms.h"
#include "segment.h"
#include "vertex.h"
#include "point.h"
#include "./data_structures/hash_table.h"
#include "bomb.h"
#include "objects/store.h"
#include "objects/resident.h"
#include "objects/person.h"
#include "interactive.h"
#include "queryResident.h"
#include "queryStore.h"
#include "inQRY.h"

int main(int argc, char *argv[]){
    int nx = 1000, nq = 1000, nh = 1000, ns = 1000, nr = 1000, np = 1000, nm = 1000;  //Número máximo padrão das formas
    char *pathIn = NULL;    //Diretório de entrada
    char *nameIn = NULL, *nameInT = NULL, *arqIn = NULL;   //Dados para o arquivo de entrada (.geo)
    char *nameEC = NULL, *nameECT = NULL, *arqEC = NULL;
    char *namePM = NULL, *namePMT = NULL, *arqPM = NULL;
    char *isInteractive = NULL;
    char *nameQuery = NULL, *nameQueryT = NULL, *arqQry = NULL; //Dados para o arquivo de entrada (.qry)
    char *pathOut = NULL;   //Diretório de saída
    char *nameOut = NULL, *arqOut = NULL;   //Dados para o arquivo de saída (.svg)
    char *nameOutQ = NULL, *arqOutQ = NULL; //Dados para o segundo arquivo de saida (.svg com .qry aplicado)
    char *nameTxt = NULL, *arqTxt = NULL;   //Dados para o arquivo de saída (.txt)
    char *nameOutBB = NULL, *arqOutBB = NULL; //Dados para o terceiro arquivo de saida (.svg com o bb aplicado)
    FILE *arqGeo = NULL, *arqQuery = NULL, *arqSvg = NULL, *arqSvgQ = NULL, *arqText = NULL, *arqSvgBB = NULL, *arqEst = NULL, *arqPes = NULL, *arqAux = NULL; //Arquivos

    char command[8];   //Armazena o comando lido do arquivo .qry
    char sufixo[32], cor[32], id1[32], id2[32], metric[4], cep[32], cpf[32], cnpj[32], face[2], compl[32];//Armazena os parametros do arquivo .qry (string)
    double x, y, r;        //Armazena os parametros do arquivo .qry (coordenadas)
    int n, k, vectSize = 0;                //Armazena os parametros do arquivo .qry

    char cfillQ[24], cstrkQ[24], cfillH[24], cstrkH[24], cfillS[24], cstrkS[24], cfillR[24], cstrkR[24];    //Cores para quadras, hidrântes, semáforos e torres de rádio
    char swQ[12] = {"1"}, swH[12] = {"1"}, swS[12] = {"1"}, swR[12] = {"1"};    //Espessura de borda de quadras, hidrântes, semáforos e torres de rádio
    char cw[12] = {"1"}, rw[12] = {"1"};    //Espessura de borda de círculos e retângulos

    //Seta cores padrões para os objetos urbanos
    strcpy(cfillQ, "orange");
    strcpy(cstrkQ, "black");
    strcpy(cfillH, "red");
    strcpy(cstrkH, "yellow");
    strcpy(cfillS, "green");
    strcpy(cstrkS, "red");
    strcpy(cfillR, "gray");
    strcpy(cstrkR, "black");

    Tree figures, blocks, hydrants, tLights, rTowers, buildings, walls;    //Arvore rubro negra de cada objeto urbano
    Element element1, element2;  //Armazena uma forma
    char type1[4], type2[4];    //Armazena o tipo do objeto urbano em questão

    Segment *segments; //Vetor de segmentos que barra o a luz da bomba de radiacao luminosa
    Vertex vertices;

    /*Recebe os parametros da main (argv)*/
    receiveParameters(argc, argv, &pathIn, &nameIn, &nameQuery, &nameEC, &namePM, &pathOut, &isInteractive);

    /*Trata o nome do arquivo de entrada se ele for um diretorio relativo*/
    treatFileName(nameIn, &nameInT);
    
    /*Prepara o diretorio para abrir os arquivos de entrada*/
    //.geo
    if(pathIn != NULL){
        allocateFileMamory(nameIn, pathIn, &arqIn);
        arqGeo = fopen(arqIn, "r");
        checkFile(arqGeo, arqIn);
    }
    else{
        arqGeo = fopen(nameIn, "r");
        checkFile(arqGeo, nameIn);
    }
    
    //.qry, .txt e .svg(2)(se existir)
    if(nameQuery != NULL){
        treatFileName(nameQuery, &nameQueryT);

        if(pathIn != NULL){
            allocateFileMamory(nameQuery, pathIn, &arqQry);
            arqQuery = fopen(arqQry, "r");
            checkFile(arqQuery, arqQry);
        }
        else{
            arqQuery = fopen(nameQuery, "r");
            checkFile(arqQuery, nameQuery);
        }
    }

    if (nameEC != NULL){
        treatFileName (nameEC, &nameECT);

        if (pathIn != NULL){
            allocateFileMamory (nameEC, pathIn, &arqEC);
            arqEst = fopen (arqEC, "r");
            checkFile (arqEst, nameEC);
        }
        else{
            arqEst = fopen (nameEC, "r");
            checkFile (arqEst, nameEC);
        }
    }

    if (namePM != NULL){
        treatFileName (namePM, &namePMT);

        if (pathIn != NULL){
            allocateFileMamory (namePM, pathIn, &arqPM);
            arqPes = fopen (arqPM, "r");
            checkFile (arqPes, namePM);
        }
        else{
            arqPes = fopen (namePM, "r");
            checkFile (arqPes, namePM);
        }
    }
    
    /*Prepara o diretorio para criar o arquivo de saida*/
    //.svg(1)
    createOutputFileName(&nameOut, nameInT);
    strcat(nameOut, ".svg");
    allocateFileMamory(nameOut, pathOut, &arqOut);
    arqSvg = fopen(arqOut, "w");
    checkFile(arqSvg, arqOut);

    fputs("<svg xmlns=\"http://www.w3.org/2000/svg\">\n", arqSvg);

    //.txt e .svg(2)
    if(nameQuery != NULL){
        createOutputQryFileName(&nameTxt, nameInT, nameQueryT);
        strcat(nameTxt, ".txt");
        allocateFileMamory(nameTxt, pathOut, &arqTxt);
        arqText = fopen(arqTxt, "w");
        checkFile(arqText, arqTxt);

        createOutputQryFileName(&nameOutQ, nameInT, nameQueryT);
        strcat(nameOutQ, ".svg");
        allocateFileMamory(nameOutQ, pathOut, &arqOutQ);
        arqSvgQ = fopen(arqOutQ, "w");
        checkFile(arqSvgQ, arqOutQ);
        fputs("<svg>\n", arqSvgQ);
        arqAux = fopen("arqAux.txt", "w+");
    }

    /*Procura o NX*/
    while(1){
        if(feof(arqGeo))
            break;

        fscanf(arqGeo, "%s", command);
        
        if(!strcmp(command, "nx")){
            scanNX(arqGeo, &nx, &nq, &nh, &ns, &nr, &np, &nm);
            break;
        }
    }

    /*Retorna ao início do arquivo .geo*/
    rewind(arqGeo);

    /*Cria as arvores rubro-negras*/
    figures = createRBTree(comparatorForm, destroyForm);
    blocks = createRBTree(comparatorBlock, destroyBlock);
    hydrants = createRBTree(comparatorHydrant, destroyHydrant);
    tLights = createRBTree(comparatorTrafficLight, destroyTrafficLight);
    rTowers = createRBTree(comparatorRadioTower, destroyRadioTower);
    buildings = createRBTree(comparatorBuilding, destroyBuilding);
    walls = createRBTree(comparatorWall, destroyWall);

    /*Cria as tabelas hash*/
    HashTable blocksTable = createHashTable(nq, NULL);
    HashTable formsTable = createHashTable(nx, NULL);
    HashTable hydrantsTable = createHashTable(1000, NULL);
    HashTable tLightsTable = createHashTable(1000, NULL);
    HashTable rTowersTable = createHashTable(1000, NULL);
    HashTable stores = createHashTable(10000, destroyStore);
    HashTable storeTypes = createHashTable(1000, destroyStore);
    HashTable persons = createHashTable(10000, destroyPerson);
    HashTable residents = createHashTable(10000, destroyResident);
    
    /*Le os dados das formas do arquivo de entrada*/
    while(1){
        fscanf(arqGeo, "%s", command);

        if(feof(arqGeo))
            break;

        if(!strcmp(command, "c")){
            scanCircle(arqGeo, figures, formsTable, cw);
        }
        else if(!strcmp(command, "r")){
            scanRect(arqGeo, figures, formsTable, rw);
        }
        else if(!strcmp(command, "t")){
            scanText(arqGeo, arqSvg, arqSvgQ);
        }
        else if(!strcmp(command, "q")){
            scanBlock(arqGeo, blocks, blocksTable, cfillQ, cstrkQ, swQ);
        }
        else if(!strcmp(command, "h")){
            scanHydrant(arqGeo, hydrants, hydrantsTable, cfillH, cstrkH, swH);
        }
        else if(!strcmp(command, "s")){
            scanTrafficLight(arqGeo, tLights, tLightsTable, cfillS, cstrkS, swS);
        }
        else if(!strcmp(command, "rb")){
            scanRadioTower(arqGeo, rTowers, rTowersTable, cfillR, cstrkR, swR);
        }
        else if(!strcmp(command, "cq")){
            changeColor(arqGeo, cfillQ, cstrkQ, swQ);
        }
        else if(!strcmp(command, "ch")){
            changeColor(arqGeo, cfillH, cstrkH, swH);
        }
        else if(!strcmp(command, "cr")){
            changeColor(arqGeo, cfillR, cstrkR, swR);
        }
        else if(!strcmp(command, "cs")){
            changeColor(arqGeo, cfillS, cstrkS, swS);
        }
        else if(!strcmp(command, "sw")){
            changeThickness(arqGeo, cw, rw);
        }
        else if(!strcmp(command, "prd")){
            scanBuilding(arqGeo, buildings, blocksTable);
        }
        else if(!strcmp(command, "mur")){
            scanWall(arqGeo, walls);
        }
    }

    /*Imprime todo o conteudo das listas no arquivo .svg(1)*/
    printTreeElements(figures, getTreeRoot(figures), arqSvg, printRect);
    printTreeElements(figures, getTreeRoot(figures), arqSvg, printCircle);
    printTreeElements(blocks, getTreeRoot(blocks), arqSvg, printBlock);
    printTreeElements(hydrants, getTreeRoot(hydrants), arqSvg, printHydrant);
    printTreeElements(tLights, getTreeRoot(tLights), arqSvg, printTrafficLight);
    printTreeElements(rTowers, getTreeRoot(rTowers), arqSvg, printRadioTower);
    printTreeElements(buildings, getTreeRoot(buildings), arqSvg, printBuilding);
    printTreeElements(walls, getTreeRoot(walls), arqSvg, printWall);

    if (namePM != NULL){
        while (1){
            fscanf (arqPes, "%s", command);

            if (feof (arqPes))
                break;

            if (!strcmp (command, "p")){
                scanPerson (arqPes, persons);
            }
            else if (!strcmp (command, "m")){
                scanResident (arqPes, residents, persons);
            }
        }
    }

    if (nameEC != NULL){
        while (1){
            fscanf (arqEst, "%s", command);

            if (feof (arqEst))
                break;
            
            if (!strcmp (command, "t")){
                scanStoreType (arqEst, storeTypes);
            }
            if (!strcmp (command, "e")){
                scanStore (arqEst, stores, storeTypes, persons);
            }
        }
    }

    /*Le os dados de consulta(se existir)*/
    if(arqSvgQ != NULL){
        treatQueries(arqQuery, arqText, arqSvgQ, arqAux, nameInT, nameQueryT, pathOut, nm, np, figures, blocks, hydrants, 
        tLights, rTowers, walls, buildings, formsTable, blocksTable, hydrantsTable, tLightsTable, rTowersTable, persons, residents, stores, storeTypes);

        printQuery(arqSvgQ, arqAux, figures, blocks, hydrants, tLights, rTowers, buildings, walls);
    }

    /*Imprime os objetos urbanos no arquivo .svg(2) (caso exista)*/

    /*Finalização, libreracao de memoria e fechamento dos arquivos*/
    fputs("\n</svg>\n", arqSvg);

    if (isInteractive != NULL){
        console(pathIn, pathOut, nameInT, nm, np, figures, blocks, hydrants, tLights, rTowers, walls, buildings, formsTable, blocksTable, 
        hydrantsTable, tLightsTable, rTowersTable, persons, residents, stores, storeTypes);
    }

    //Fecha os arquivos .geo e .svg(1)
    fclose(arqSvg);
    fclose(arqGeo);

    //Fecha os arquivos relacionados ao arquivo .qry (se existir)
    
    //Liberação da memória relacionada aos arquivos .geo e .svg(1)
    free(pathIn);
    free(nameIn);
    free(nameInT);
    free(arqIn);
    free(pathOut);
    free(nameOut);
    free(arqOut);

    //Liberação da memória relacionada ao arquivo .qry (se existir)
    if(nameQuery != NULL){
        free(nameQuery);
        free(nameQueryT);
        free(nameOutQ);
        free(arqOutQ);
        free(nameTxt);
        free(arqTxt);
        free(arqQry);
    }

    if (nameEC != NULL){
        free (nameEC);
        free (nameECT);
        free (arqEC);
        fclose(arqEst);
    }

    if (namePM != NULL){
        free (namePM);
        free (namePMT);
        free (arqPM);
        fclose(arqPes);
    }

    if (isInteractive != NULL){
        free (isInteractive);
    }

    //Liberação da memória das asvores
    destroyRBTree(figures);
    destroyRBTree(blocks);
    destroyRBTree(hydrants);
    destroyRBTree(tLights);
    destroyRBTree(rTowers);
    destroyRBTree(buildings);
    destroyRBTree(walls);

    //Liberação da memória das tabelas hash
    destroyHashTable(blocksTable);
    destroyHashTable(formsTable);
    destroyHashTable(hydrantsTable);
    destroyHashTable(tLightsTable);
    destroyHashTable(rTowersTable);
    destroyHashTable(stores);
    destroyHashTable(storeTypes);
    destroyHashTable(persons);
    destroyHashTable(residents);

    return 0;
}

#endif