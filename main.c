#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inSVG.h"
#include "outSVG.h"
#include "queryForms.h"
#include "queryBuildings.h"
#include "queryResident.h"
#include "queryStore.h"
#include "list.h"
#include "Objetos/forms.h"
#include "segment.h"
#include "vertex.h"
#include "point.h"
#include "bomb.h"

int main(int argc, char *argv[]){
    int nx = 1000, nq = 1000, nh = 1000, ns = 1000, nr = 1000, np = 1000, nm = 1000;  //Número máximo padrão das formas
    char *pathIn = NULL;    //Diretório de entrada
    char *nameIn = NULL, *nameInT = NULL, *arqIn = NULL;   //Dados para o arquivo de entrada (.geo)
    char *nameEC = NULL, *nameECT = NULL, *arqEC = NULL;
    char *namePM = NULL, *namePMT = NULL, *arqPM = NULL;
    char *nameQuery = NULL, *nameQueryT = NULL, *arqQry = NULL; //Dados para o arquivo de entrada (.qry)
    char *pathOut = NULL;   //Diretório de saída
    char *nameOut = NULL, *arqOut = NULL;   //Dados para o arquivo de saída (.svg)
    char *nameOutQ = NULL, *arqOutQ = NULL; //Dados para o segundo arquivo de saida (.svg com .qry aplicado)
    char *nameTxt = NULL, *arqTxt = NULL;   //Dados para o arquivo de saída (.txt)
    char *nameOutBB = NULL, *arqOutBB = NULL; //Dados para o terceiro arquivo de saida (.svg com o bb aplicado)
    FILE *arqGeo = NULL, *arqQuery = NULL, *arqSvg = NULL, *arqSvgQ = NULL, *arqText = NULL, *arqSvgBB = NULL, *arqEst = NULL, *arqPes = NULL; //Arquivos

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

    List figures, blocks, hydrants, tLights, rTowers, buildings, walls, auxList, stores, storeTypes, persons, residents;    //Listas de cada objeto urbano
    Form figure1, figure2;  //Armazena uma forma
    char type1[4], type2[4];    //Armazena o tipo do objeto urbano em questão

    Segment *segments; //Vetor de segmentos que barra o a luz da bomba de radiacao luminosa
    Vertex vertices;

    /*Recebe os parametros da main (argv)*/
    receiveParameters(argc, argv, &pathIn, &nameIn, &nameQuery, &nameEC, &namePM, &pathOut);

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

    fputs("<svg>\n", arqSvg);

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

    /*Cria as listas*/
    figures = createList(nx);
    blocks = createList(nq);
    hydrants = createList(nh);
    tLights = createList(ns);
    rTowers = createList(nr);
    buildings = createList(np);
    walls = createList(nm);
    stores = createList (100000);
    persons = createList (100000);
    residents = createList (100000);
    storeTypes = createList (100000);
    auxList = createList(100000);

    
    /*Le os dados das formas do arquivo de entrada*/
    while(1){
        if(feof(arqGeo))
            break;

        fscanf(arqGeo, "%s", command);

        if(!strcmp(command, "c")){
            scanCircle(arqGeo, figures, cw);
        }
        else if(!strcmp(command, "r")){
            scanRect(arqGeo, figures, rw);
        }
        else if(!strcmp(command, "t")){
            scanText(arqGeo, arqSvg, arqSvgQ);
        }
        else if(!strcmp(command, "q")){
            scanBlock(arqGeo, blocks, cfillQ, cstrkQ, swQ);
        }
        else if(!strcmp(command, "h")){
            scanHydrant(arqGeo, hydrants, cfillH, cstrkH, swH);
        }
        else if(!strcmp(command, "s")){
            scanTrafficLight(arqGeo, tLights, cfillS, cstrkS, swS);
        }
        else if(!strcmp(command, "rb")){
            scanRadioTower(arqGeo, rTowers, cfillR, cstrkR, swR);
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
            scanBuilding(arqGeo, buildings);
        }
        else if(!strcmp(command, "mur")){
            scanWall(arqGeo, walls);
        }
    }
    
    /*Imprime todo o conteudo das listas no arquivo .svg(1)*/
    printList(figures, arqSvg);
    printList(blocks, arqSvg);
    printList(hydrants, arqSvg);
    printList(tLights, arqSvg);
    printList(rTowers, arqSvg);
    printBuildingList(blocks, buildings, arqSvg);
    printList(walls, arqSvg);

    if (nameEC != NULL){
        while (1){
            fscanf (arqEst, "%s", command);

            if (feof (arqEst))
                break;
            
            if (!strcmp (command, "t")){
                scanStoreType (arqEst, storeTypes);
            }
            if (!strcmp (command, "e")){
                scanStore (arqEst, stores);
            }
        }
    }

    if (namePM != NULL){
        while (1){
            fscanf (arqPes, "%s", command);

            if (feof (arqPes))
                break;

            if (!strcmp (command, "p")){
                scanPerson (arqPes, persons);
            }
            else if (!strcmp (command, "m")){
                scanResident (arqPes, residents);
            }
        }
    }
    
    /*Le os dados de consulta(se existir)*/
    if(nameQuery != NULL){
        while(1){
            fscanf(arqQuery, "%s", command);

            if(feof(arqQuery))
                break;

            if(!strcmp(command, "o?")){
                scanO(arqQuery, id1, id2);
                figure1 = getElementById(figures, id1, type1);
                figure2 = getElementById(figures, id2, type2);
                treatO(arqText, arqSvgQ, figure1, figure2, type1, type2);
            }
            else if(!strcmp(command, "i?")){
                scanI(arqQuery, id1, &x, &y);
                figure1 = getElementById(figures, id1, type1);
                treatI(arqText, arqSvgQ, figure1, x, y, type1);
            }
            else if(!strcmp(command, "d?")){
                scanD(arqQuery, id1, id2);
                figure1 = getElementById(figures, id1, type1);
                figure2 = getElementById(figures, id2, type2);
                treatD(arqText, arqSvgQ, figure1, figure2, type1, type2);
            }
            else if(!strcmp(command, "bb")){
                scanBB(arqQuery, sufixo, cor);
                createOutputBBFileName(&nameOutBB, nameInT, nameQueryT, sufixo);
                strcat(nameOutBB, ".svg");
                allocateFileMamory(nameOutBB, pathOut, &arqOutBB);
                arqSvgBB = fopen(arqOutBB, "w");
                checkFile(arqSvgBB, arqOutBB);
                treatBB(arqSvgBB, figures, cor);
                fclose(arqSvgBB);
                free(nameOutBB);
                free(arqOutBB);
            }
            else if(!strcmp(command, "dq")){
                scanDQ(arqQuery, metric, id1, &r);
                figure1 = getElementByIdInLists(blocks, hydrants, tLights, rTowers, id1, type1);
                if(!strcmp(type1, "h")){
                    x = getHydrantX(figure1);
                    y = getHydrantY(figure1);
                    strcpy(id1, getHydrantId(figure1));
                }
                else if(!strcmp(type1, "s")){
                    x = getTrafficLightX(figure1);
                    y = getTrafficLightY(figure1);
                    strcpy(id1, getTrafficLightId(figure1));
                }
                else if(!strcmp(type1, "rb")){
                    x = getRadioTowerX(figure1);
                    y = getRadioTowerY(figure1);
                    strcpy(id1, getRadioTowerId(figure1));
                }
                Form circle = createCircle(id1, x, y, r, "black", "none", "1");
                treatDQ(arqText, arqSvgQ, blocks, metric, circle);
                fprintf(arqText, "\n");
                free(circle);
            }
            else if(!strcmp(command, "del")){
                fscanf(arqQuery, "%s", id1);
                figure1 = getElementByIdInLists(blocks, hydrants, tLights, rTowers, id1, type1);
                if(!strcmp(type1, "h")){
                    x = getHydrantX(figure1);
                    y = getHydrantY(figure1);
                    deleteElement(hydrants, id1);
                }
                else if(!strcmp(type1, "s")){
                    x = getTrafficLightX(figure1);
                    y = getTrafficLightY(figure1);
                    deleteElement(tLights, id1);
                }
                else if(!strcmp(type1, "rb")){
                    x = getRadioTowerX(figure1);
                    y = getRadioTowerY(figure1);
                    deleteElement(rTowers, id1);
                }
                else if(!strcmp(type1, "q")){
                    x = getBlockX(figure1);
                    y = getBlockY(figure1);
                    deleteElement(blocks, id1);
                }
                fprintf(arqText, "del %s\n", id1);
                fprintf(arqText, "\tEquipamento Urbano Removido: %s (%lf %lf)\n\n", id1, x, y);
            }
            else if(!strcmp(command, "cbq")){
                figure1 = scanCBQ(arqQuery, cstrkQ);

                treatCBQ(arqText, blocks, figure1, cstrkQ);
                fprintf(arqText, "\n");

                free(figure1);
            }
            else if(!strcmp(command, "crd?")){
                fscanf(arqQuery, "%s", id1);

                figure1 = getElementByIdInLists(blocks, hydrants, tLights, rTowers, id1, type1);
                fprintf(arqText, "crd? %s\n", id1);

                if(figure1 != NULL){
                    if(!strcmp(type1, "q")){
                        fprintf(arqText, "\tQuadra %s: (%lf, %lf)\n", id1, getBlockX(figure1), getBlockY(figure1));
                    }
                    else if(!strcmp(type1, "h")){
                        fprintf(arqText, "\tHidrante %s: (%lf, %lf)\n", id1, getHydrantX(figure1), getHydrantY(figure1));
                    }
                    else if(!strcmp(type1, "s")){
                        fprintf(arqText, "\tSemáforo %s: (%lf, %lf)\n", id1, getTrafficLightX(figure1), getTrafficLightY(figure1));
                    }
                    else if(!strcmp(type1, "rb")){
                        fprintf(arqText, "\tRadio-Base %s: (%lf, %lf)\n", id1, getRadioTowerX(figure1), getRadioTowerY(figure1));
                    }
                }
                else{
                    fprintf(arqText, "\tEquipamento Urbano não encontrado!\n");
                }
                fprintf(arqText, "\n");
            }
            else if(!strcmp(command, "trns")){
                Form rect = scanTRNS(arqQuery, &x, &y);

                treatTRNS(arqText, blocks, hydrants, tLights, rTowers, rect, x, y, arqSvgQ);
                free(rect);
            }
            else if(!strcmp(command, "fi")){
                scanFI(arqQuery, &x, &y, &n, &r);
                treatFI(arqSvgQ, arqText, auxList, x, y, n, r, tLights, hydrants);
            }
            else if(!strcmp(command, "fh")){
                scanFHFS(arqQuery, &k, id1, id2, &n);
                getAddress(id1, id2, n, &x, &y, blocks);
                treatFH(arqText, arqSvgQ, hydrants, k, x, y, auxList);
            }
            else if(!strcmp(command, "fs")){
                scanFHFS(arqQuery, &k, id1, id2, &n);
                getAddress(id1, id2, n, &x, &y, blocks);
                treatFS(arqText, arqSvgQ, tLights, k, x, y, auxList);
            }
            else if(!strcmp(command, "brl")){
                scanBRL(arqQuery, &x, &y);
                Form circle = createCircle("", x, y, 5, "black", "red", "2");
                insertElement(auxList, circle, "c");
                int capacitySegments = nm + np * 4 + 4;
                bombAreaRadiation(x, y, capacitySegments, walls, buildings, auxList, arqSvgQ);
            }
            else if (!strcmp (command, "m?")){
                scanM (arqQuery, cep);
                treatM (arqText, persons, residents, cep);    
            }
            else if (!strcmp (command, "dm?")){
                scanDM (arqQuery, cpf);
                fprintf (arqText,"dm? %s\n", cpf);
                printResidentData (cpf, residents, persons, arqText);
                fprintf (arqText, "\n");
            }
            else if (!strcmp (command, "de?")){
                scanDE (arqQuery, cnpj);
                fprintf (arqText, "de? %s\n", cnpj);
                printStoreData (cnpj, stores, persons, storeTypes, arqText);
                fprintf (arqText, "\n");
            }
            else if (!strcmp (command, "mud")){
                scanMud (arqQuery, cpf, cep, face, &n, compl);
                fprintf (arqText, "mud %s %s %s %d %s\n", cpf, cep, face, n, compl);

                treatMud (arqText, persons, residents, cpf, cep, face, n, compl);
                fprintf (arqText, "\n");
            }
        }
    }

    /*Imprime os objetos urbanos no arquivo .svg(2) (caso exista)*/
    if(arqSvgQ != NULL){
        printList(figures, arqSvgQ);
        printList(blocks, arqSvgQ);
        printList(hydrants, arqSvgQ);
        printList(tLights, arqSvgQ);
        printList(rTowers, arqSvgQ);
        printBuildingList(blocks, buildings, arqSvgQ);
        printList(walls, arqSvgQ);
        printList(auxList, arqSvgQ);
    }

    /*Finalização, libreracao de memoria e fechamento dos arquivos*/
    fputs("\n</svg>\n", arqSvg);

    //Fecha os arquivos .geo e .svg(1)
    fclose(arqSvg);
    fclose(arqGeo);

    //Fecha os arquivos relacionados ao arquivo .qry (se existir)
    if(nameQuery != NULL){
        fclose(arqQuery);
        fclose(arqText);
        fputs("\n</svg>\n", arqSvgQ);
        fclose(arqSvgQ);
    }
    
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
    }

    if (namePM != NULL){
        free (namePM);
        free (namePMT);
        free (arqPM);
    }

    //Liberação da memória das listas
    deallocateList(figures, freeForm);
    deallocateList(blocks, freeBlock);
    deallocateList(hydrants, freeHydrant);
    deallocateList(tLights, freeTrafficLight);
    deallocateList(rTowers, freeRadioTower);
    deallocateList(buildings, freeBuilding);
    deallocateList(walls, freeWall);
    deallocateList(auxList, freeForm);
    //deallocateList(auxList, freeWall);

    return 0;
}
