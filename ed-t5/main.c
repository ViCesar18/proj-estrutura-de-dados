#ifndef PRINCIPAL
#define PRINCIPAL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inGEO.h"
#include "outSVG.h"
#include "queryForms.h"
#include "queryBuildings.h"
#include "./data_structures/rbtree.h"
#include "geometry/forms.h"
#include "geometry/segment.h"
#include "geometry/vertex.h"
#include "geometry/point.h"
#include "./data_structures/hash_table.h"
#include "utils/bomb.h"
#include "city_elements/store.h"
#include "city_elements/resident.h"
#include "city_elements/person.h"
#include "utils/interactive.h"
#include "queryResident.h"
#include "queryStore.h"
#include "inQRY.h"
#include "data_structures/graph.h"

int main(int argc, char *argv[]){
    int nx = 1000, nq = 1000, nh = 1000, ns = 1000, nr = 1000, np = 1000, nm = 1000;  //Número máximo padrão dos elementos urbanos
    char *pathIn = NULL;    //Diretório de entrada
    char *nameIn = NULL, *nameInT = NULL, *arqIn = NULL;   //Dados para o arquivo de entrada (.geo)
    char *nameEC = NULL, *nameECT = NULL, *arqEC = NULL;
    char *namePM = NULL, *namePMT = NULL, *arqPM = NULL;
    char *nameVia = NULL, *nameViaT = NULL, *arqV = NULL;
    char *isInteractive = NULL;
    char *nameQuery = NULL, *nameQueryT = NULL, *arqQry = NULL; //Dados para o arquivo de entrada (.qry)
    char *pathOut = NULL;   //Diretório de saída
    char *nameOut = NULL, *arqOut = NULL;   //Dados para o arquivo de saída (.svg)
    char *nameOutQ = NULL, *arqOutQ = NULL; //Dados para o segundo arquivo de saida (.svg com .qry aplicado)
    char *nameTxt = NULL, *arqTxt = NULL;   //Dados para o arquivo de saída (.txt)
    char *nameOutBB = NULL, *arqOutBB = NULL; //Dados para o terceiro arquivo de saida (.svg com o bb aplicado)
    FILE *arqGeo = NULL, *arqQuery = NULL, *arqSvg = NULL, *arqSvgQ = NULL, *arqText = NULL, *arqSvgBB = NULL, *arqEst = NULL, *arqPes = NULL, *arqAux = NULL, *arqVia = NULL; //Arquivos

    char command[8];   //Armazena o comando lido do arquivo .qry

    char cfillQ[24], cstrkQ[24], cfillH[24], cstrkH[24], cfillS[24], cstrkS[24], cfillR[24], cstrkR[24];    //Cores para quadras, hidrântes, semáforos e torres de rádio
    char swQ[12] = {"1"}, swH[12] = {"1"}, swS[12] = {"1"}, swR[12] = {"1"};    //Espessura de borda de quadras, hidrântes, semáforos e torres de rádio
    char cw[12] = {"1"}, rw[12] = {"1"};    //Espessura de borda de círculos e retângulos

    //Seta cores padrões para os elementos urbanos
    strcpy(cfillQ, "orange");
    strcpy(cstrkQ, "black");
    strcpy(cfillH, "red");
    strcpy(cstrkH, "yellow");
    strcpy(cfillS, "green");
    strcpy(cstrkS, "red");
    strcpy(cfillR, "gray");
    strcpy(cstrkR, "black");

    Tree figures, blocks, hydrants, tLights, rTowers, buildings, walls;    //Arvore rubro negra de cada elemento urbano
    Graph pathways; //Grafo da via urbada da cidade

    /*Recebe os parametros da main (argv)*/
    receiveParameters(argc, argv, &pathIn, &nameIn, &nameQuery, &nameEC, &namePM, &pathOut, &isInteractive, &nameVia);

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

    //.ec
    if (nameEC != NULL){
        treatFileName (nameEC, &nameECT);

        if (pathIn != NULL){
            allocateFileMamory (nameEC, pathIn, &arqEC);
            arqEst = fopen (arqEC, "r");
            checkFile (arqEst, arqEC);
        }
        else{
            arqEst = fopen (nameEC, "r");
            checkFile (arqEst, nameEC);
        }
    }

    //.pm
    if (namePM != NULL){
        treatFileName (namePM, &namePMT);

        if (pathIn != NULL){
            allocateFileMamory (namePM, pathIn, &arqPM);
            arqPes = fopen (arqPM, "r");
            checkFile (arqPes, arqPM);
        }
        else{
            arqPes = fopen (namePM, "r");
            checkFile (arqPes, namePM);
        }
    }

    //.via
    if(nameVia != NULL){
        treatFileName(nameVia, &nameViaT);

        if(pathIn != NULL){
            allocateFileMamory(nameVia, pathIn, &arqV);
            arqVia = fopen(arqV, "r");
            checkFile(arqVia, arqV);
        }
        else{
            arqVia = fopen(nameVia, "r");
            checkFile(arqVia, nameVia);
        }
    }
    
    /*Prepara o diretorio para criar os arquivos de saida*/
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
    HashTable hydrantsTable = createHashTable(nh, NULL);
    HashTable tLightsTable = createHashTable(ns, NULL);
    HashTable rTowersTable = createHashTable(nr, NULL);
    HashTable buildingsTable = createHashTable(np, NULL);
    HashTable stores = createHashTable(1000, destroyStore);
    HashTable storeTypes = createHashTable(1000, destroyStore);
    HashTable persons = createHashTable(1000, destroyPerson);
    HashTable residents = createHashTable(1000, destroyResident);
    
    /*Le os dados dos elementos do arquivo de entrada .geo*/
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
            scanBuilding(arqGeo, buildings, blocksTable, buildingsTable);
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

    /*Le os dados dos elementos do arquivo de entrada .pm*/
    if (namePM != NULL){
        while (1){
            fscanf (arqPes, "%s", command);

            if (feof (arqPes))
                break;

            if (!strcmp (command, "p")){
                scanPerson (arqPes, persons);
            }
            else if (!strcmp (command, "m")){
                scanResident (arqPes, residents, persons, buildingsTable, blocksTable);
            }
        }
    }

    /*Le os dados dos elementos do arquivo de entrada .ec*/
    if (nameEC != NULL){
        while (1){
            fscanf (arqEst, "%s", command);

            if (feof (arqEst))
                break;
            
            if (!strcmp (command, "t")){
                scanStoreType (arqEst, storeTypes);
            }
            if (!strcmp (command, "e")){
                scanStore (arqEst, stores, storeTypes, persons, blocksTable);
            }
        }
    }

    /*Le os dados dos elementos do arquivo de entrada .via*/
    if(arqVia != NULL){
        pathways = createGraph(10000);  //Cria o grafo caso o arquivo de vias exista

        while(1){
            fscanf(arqVia, "%s", command);

            if(feof(arqVia))
                break;

            if(!strcmp(command, "v")){
                scanGraphVertex(arqVia, pathways);
            }
            else if(!strcmp(command, "e")){
                scanGraphEdge(arqVia, pathways);
            }
        }
    }

    /*Le os dados de consulta(se existir)*/
    if(arqSvgQ != NULL){
        treatQueries(arqQuery, arqText, arqSvgQ, arqAux, nameInT, nameQueryT, pathIn, pathOut, nm, np, figures, blocks, hydrants, 
        tLights, rTowers, walls, buildings, formsTable, blocksTable, hydrantsTable, tLightsTable, rTowersTable, buildingsTable, persons, residents, stores, storeTypes, pathways);

        printQuery(arqSvgQ, arqAux, figures, blocks, hydrants, tLights, rTowers, buildings, walls);
    }

    //Loop de interatividade(se existir)
    if (isInteractive != NULL){
        console(pathIn, pathOut, nameInT, nm, np, figures, blocks, hydrants, tLights, rTowers, walls, buildings, formsTable, blocksTable, 
        hydrantsTable, tLightsTable, rTowersTable, buildingsTable, persons, residents, stores, storeTypes, pathways);
    }

    /*Finalização, libreracao de memoria e fechamento dos arquivos*/
    fputs("\n</svg>\n", arqSvg);

    //Fecha os arquivos .geo e .svg(1)
    fclose(arqSvg);
    fclose(arqGeo);
    
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

    //.ec
    if (nameEC != NULL){
        free (nameEC);
        free (nameECT);
        free (arqEC);
        fclose(arqEst);
    }

    //.pm
    if (namePM != NULL){
        free (namePM);
        free (namePMT);
        free (arqPM);
        fclose(arqPes);
    }

    //interatividade
    if (isInteractive != NULL){
        free (isInteractive);
    }

    if(nameVia != NULL){
        free(nameVia);
        free(nameViaT);
        free(arqV);
        fclose(arqVia);

        //Liberação da memória do grafo
        destroyGraph(pathways);
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
    destroyHashTable(buildingsTable);
    destroyHashTable(stores);
    destroyHashTable(storeTypes);
    destroyHashTable(persons);
    destroyHashTable(residents);

    return 0;
}

#endif