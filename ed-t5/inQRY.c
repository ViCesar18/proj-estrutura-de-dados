#include "inQRY.h"

void scanO(FILE *arqQuery, char j[], char k[]){

    fscanf(arqQuery, "%s", j);
    fscanf(arqQuery, "%s", k);
}

void scanI(FILE *arqQuery, char j[], double *x, double *y){

    fscanf(arqQuery, "%s", j);
    fscanf(arqQuery, "%lf", x);
    fscanf(arqQuery, "%lf", y);
}

void scanD(FILE *arqQuery, char j[], char k[]){

    fscanf(arqQuery, "%s", j);
    fscanf(arqQuery, "%s", k);
}

void scanBB(FILE *arqQuery, char suffix[], char color[]){

    fscanf(arqQuery, "%s", suffix);
    fscanf(arqQuery, "%s", color);
}

void scanDQ(FILE *arqQuery, char metric[], char id[], double *r){

    fscanf(arqQuery, "%s", metric);
    fscanf(arqQuery, "%s", id);
    fscanf(arqQuery, "%lf", r);
}

Element scanCBQ(FILE *arqQuery, char cstrk[]){
    double x, y, r;

    fscanf(arqQuery, "%lf", &x);
    fscanf(arqQuery, "%lf", &y);
    fscanf(arqQuery, "%lf", &r);
    fscanf(arqQuery, "%s", cstrk);

    Form circle = createCircle("0", x, y, r, "black", "none", "1");

    return circle;
}

Element scanTRNS(FILE *arqQuery, double *dx, double *dy){
    double x, y, w, h;

    fscanf(arqQuery, "%lf", &x);
    fscanf(arqQuery, "%lf", &y);
    fscanf(arqQuery, "%lf", &w);
    fscanf(arqQuery, "%lf", &h);
    fscanf(arqQuery, "%lf", dx);
    fscanf(arqQuery, "%lf", dy);

    Form rect = createRect("0", x, y, w, h, "black", "none", 0, "1");

    return rect;
}

void scanFI(FILE *arqQuery, double *x, double *y, int *n, double *r){

    fscanf(arqQuery, "%lf", x);
    fscanf(arqQuery, "%lf", y);
    fscanf(arqQuery, "%d", n);
    fscanf(arqQuery, "%lf", r);
}

void scanFHFS(FILE *arqQuery, int *k, char cep[], char face[], int *num){

    fscanf(arqQuery, "%d", k);
    fscanf(arqQuery, "%s", cep);
    fscanf(arqQuery, "%s", face);
    fscanf(arqQuery, "%d", num);
}

void scanBRL(FILE *arqQuery, double *x, double *y){

    fscanf(arqQuery, "%lf", x);
    fscanf(arqQuery, "%lf", y);
}

void scanM (FILE *arqQuery, char cep[]){
    fscanf (arqQuery, "%s", cep);
}

void scanDM (FILE *arqQuery, char cpf[]){
    fscanf (arqQuery, "%s", cpf);
}

void scanDE (FILE *arqQuery, char cnpj[]){
    fscanf (arqQuery, "%s", cnpj);
}

void scanMud (FILE *arqQuery, char cpf[], char cep[], char face[], int *num, char compl[]){
    fscanf (arqQuery, "%s", cpf);
    fscanf (arqQuery, "%s", cep);
    fscanf (arqQuery, "%s", face);
    fscanf (arqQuery, "%d", num);
    fscanf (arqQuery, "%s", compl);
}

void scanDMPRBT(FILE *arqQuery, char *type, char *fileName){
    fscanf(arqQuery, "%s", type);
    fscanf(arqQuery, "%s", fileName);
}

void treatQueries(FILE *arqQuery, FILE *arqText, FILE *arqSvgQ, FILE *arqAux, char *nameInT, char *nameQueryT, char *pathIn, char *pathOut, int nm, int np, 
                Tree figures, Tree blocks, Tree hydrants, Tree tLights, Tree rTowers, Tree walls, Tree buildings, 
                HashTable formsTable, HashTable blocksTable, HashTable hydrantsTable, HashTable tLightsTable, HashTable rTowersTable, HashTable buildingsTable, 
                HashTable persons, HashTable residents, HashTable stores, HashTable storeTypes, Graph pathways){

    char command[8];
    char sufixo[32], cor[32], cor2[32], id1[32], id2[32], metric[4], cep[32], cpf[32], cnpj[32], face[2], compl[32];
    double x, y, r;
    int n, k, vectSize = 0;
    Element element1, element2;
    char cstrkQ[24];

    //Dados para a consulta de bouding box
    FILE *arqSvgBB = NULL;
    char *nameOutBB = NULL, *arqOutBB = NULL;

    //Dados para a consulta de vias
    FILE *arqSvgVia = NULL;
    char *nameOutVia = NULL, *arqOutVia = NULL;

    //Registradores [R0 - R10]
    Point *registers = (Point) calloc(11, sizeof(Point));

    while(1){
        fscanf(arqQuery, "%s", command);

        if(feof(arqQuery))
            break;

        if(!strcmp(command, "o?")){
            scanO(arqQuery, id1, id2);
            element1 = searchHashTable(formsTable, id1);
            element2 = searchHashTable(formsTable, id2);
            treatO(arqText, arqAux, element1, element2);
        }
        else if(!strcmp(command, "i?")){
            scanI(arqQuery, id1, &x, &y);
            element1 = searchHashTable(formsTable, id1);
            treatI(arqText, arqAux, element1, x, y);
        }
        else if(!strcmp(command, "d?")){
            scanD(arqQuery, id1, id2);
            element1 = searchHashTable(formsTable, id1);
            element2 = searchHashTable(formsTable, id2);
            treatD(arqText, arqAux, element1, element2);
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
            element1 = searchHashTable(hydrantsTable, id1);
            if(element1 != NULL){
                x = getHydrantX(element1);
                y = getHydrantY(element1);
                strcpy(id1, getHydrantId(element1));
            }
            else{
                element1 = searchHashTable(tLightsTable, id1);
                if(element1 != NULL){
                    x = getTrafficLightX(element1);
                    y = getTrafficLightY(element1);
                    strcpy(id1, getTrafficLightId(element1));
                }
                else{
                    element1 = searchHashTable(rTowersTable, id1);
                    if(element1 != NULL){
                        x = getRadioTowerX(element1);
                        y = getRadioTowerY(element1);
                        strcpy(id1, getRadioTowerId(element1));
                    }
                }
            }

            Form circle = createCircle(id1, x, y, r, "black", "none", "1");
            treatDQ(arqText, arqSvgQ, blocks, blocksTable, metric, circle);
            fprintf(arqText, "\n");
            free(circle);
        }
        else if(!strcmp(command, "del")){
            fscanf(arqQuery, "%s", id1);
            treatDEL(arqText, id1, blocks, blocksTable, hydrants, hydrantsTable, tLights, tLightsTable, rTowers, rTowersTable);
        }
        else if(!strcmp(command, "cbq")){
            element1 = scanCBQ(arqQuery, cstrkQ);

            fprintf(arqText, "cbq %lf %lf %lf %s\n", getFormX(element1), getFormY(element1), getFormR(element1), cstrkQ);
            treatCBQ(arqText, blocks, getTreeRoot(blocks), element1, cstrkQ);
            fprintf(arqText, "\n");

            free(element1);
        }
        else if(!strcmp(command, "crd?")){
            fscanf(arqQuery, "%s", id1);

            element1 = searchHashTable(blocksTable, id1);
            if(element1 != NULL)
                fprintf(arqText, "crd? %s\n\tQuadra %s: (%lf, %lf)\n", id1, id1, getBlockX(element1), getBlockY(element1));
            else{
                element1 = searchHashTable(hydrantsTable, id1);
                if(element1 != NULL)
                    fprintf(arqText, "crd? %s\n\tHidrante %s: (%lf, %lf)\n", id1, id1, getHydrantX(element1), getHydrantY(element1));
                else{
                    element1 = searchHashTable(tLightsTable, id1);
                    if(element1 != NULL)
                        fprintf(arqText, "crd? %s\n\tSemáforo %s: (%lf, %lf)\n", id1, id1, getTrafficLightX(element1), getTrafficLightY(element1));
                    else{
                        element1 = searchHashTable(rTowersTable, id1);
                        if(element1 != NULL)
                            fprintf(arqText, "crd? %s\n\tRadio-Base %s: (%lf, %lf)\n", id1, id1, getRadioTowerX(element1), getRadioTowerY(element1));
                        else
                            fprintf(arqText, "crd? %s\n\tEquipamento Urbano não encontrado!\n", id1);
                    }
                }
            }
        }
        else if(!strcmp(command, "trns")){
            Form rect = scanTRNS(arqQuery, &x, &y);

            treatTRNS_block(arqText, blocks, getTreeRoot(blocks), rect, x, y, arqSvgQ);
            treatTRNS_hydrant(arqText, hydrants, getTreeRoot(hydrants), rect, x, y, arqSvgQ);
            treatTRNS_tLight(arqText, tLights, getTreeRoot(tLights), rect, x, y, arqSvgQ);
            treatTRNS_rTower(arqText, rTowers, getTreeRoot(rTowers), rect, x, y, arqSvgQ);
            free(rect);
        }
        else if(!strcmp(command, "brl")){
            fscanf(arqQuery, "%lf", &x);
            fscanf(arqQuery, "%lf", &y);
            Polygon polygon = createPolygon();
            bombAreaRadiation(arqAux, polygon, x, y, walls, buildings, false);

            fprintf(arqAux, "<polygon points=\"");
            for(Segment aux = getPolygonFirstSegment(polygon); aux != NULL; aux = getSegmentProx(aux))
                fprintf(arqAux, "%lf,%lf ", getPointX(getVertexV(getSegmentV1(aux))), getPointY(getVertexV(getSegmentV1(aux))));
            fprintf(arqAux, "\" opacity=\"0.5\" style=\"fill:lime;stroke:purple;stroke-width:1\" />");

        }
        else if(!strcmp(command, "fi")){
            scanFI(arqQuery, &x, &y, &n, &r);
            treatFI(arqAux, arqText, x, y, n, r, tLights, hydrants);
        }
        else if(!strcmp(command, "fh")){
            scanFHFS(arqQuery, &k, id1, id2, &n);
            getAddress(id1, id2, n, &x, &y, blocksTable);
            treatFH(arqText, arqAux, hydrants, k, x, y);
        }
        else if(!strcmp(command, "fs")){
            scanFHFS(arqQuery, &k, id1, id2, &n);
            getAddress(id1, id2, n, &x, &y, blocksTable);
            treatFS(arqText, arqSvgQ, tLights, k, x, y);
        }
        else if(!strcmp(command, "brn")){
            fscanf(arqQuery, "%lf", &x);
            fscanf(arqQuery, "%lf", &y);
            fscanf(arqQuery, "%s", id1);
            treatBRN(arqAux, arqText, pathIn, x, y, walls, buildings, id1, residents);
        }
        else if (!strcmp (command, "m?")){
            scanM (arqQuery, cep);
            treatM (arqText, persons, residents, cep);
        }
        else if(!strcmp(command, "mplg?")){
            fscanf(arqQuery, "%s", id1);
            treatMPLG(arqAux, arqText, id1, pathIn, blocks, buildings);
        }
        else if (!strcmp (command, "dm?")){
            scanDM (arqQuery, cpf);
            fprintf (arqText,"dm? %s\n", cpf);
            printResidentData (cpf, residents, arqText);
            fprintf (arqText, "\n");
        }
        else if (!strcmp (command, "de?")){
            scanDE (arqQuery, cnpj);
            fprintf (arqText, "de? %s\n", cnpj);
            printStoreData (cnpj, stores, arqText);
            fprintf (arqText, "\n");
        }
        else if (!strcmp (command, "mud")){
            scanMud (arqQuery, cpf, cep, face, &n, compl);
            fprintf (arqText, "mud %s %s %s %d %s\n", cpf, cep, face, n, compl);
            treatMud (arqText, residents, buildingsTable, cpf, cep, face, n, compl);
            fprintf (arqText, "\n");
        }
        else if(!strcmp(command, "eplg?")){
            fscanf(arqQuery, "%s", id1);
            fscanf(arqQuery, "%s", id2);
            treatEPLG(arqAux, arqText, id1, id2, pathIn, stores);
        }
        else if(!strcmp(command, "catac")){
            fscanf(arqQuery, "%s", id1);
            treatCATAC(arqAux, arqText, id1, pathIn, blocks, hydrants, tLights, rTowers, buildings, blocksTable, hydrantsTable, tLightsTable, rTowersTable, 
            buildingsTable, residents);
        }
        else if(!strcmp(command, "dmprbt")){
            scanDMPRBT(arqQuery, id1, id2);
            treatDMPRBT(id1, id2, pathOut, blocks, hydrants, tLights, rTowers, buildings, walls);
        }
        else if(!strcmp(command, "@m?")){
            fscanf(arqQuery, "%s", id1);
            fscanf(arqQuery, "%s", cep);
            
            treatRegisterM(registers, id1, cep, residents);
        }
        else if(!strcmp(command, "@e?")){
            fscanf(arqQuery, "%s", id1);
            fscanf(arqQuery, "%s", cep);
            fscanf(arqQuery, "%s", face);
            fscanf(arqQuery, "%d", &n);

            treatRegisterE(registers, id1, cep, face, n, blocksTable);
        }
        else if(!strcmp(command, "@g?")){
            fscanf(arqQuery, "%s", id1);
            fscanf(arqQuery, "%s", id2);

            treatRegisterG(registers, id1, id2, hydrantsTable, tLightsTable, rTowersTable);
        }
        else if(!strcmp(command, "@xy")){
            fscanf(arqQuery, "%s", id1);
            fscanf(arqQuery, "%lf", &x);
            fscanf(arqQuery, "%lf", &y);

            Point point = createPoint(x, y);
            setRegister(registers, id1, point);
        }
        else if(!strcmp(command, "p?")){
            fscanf(arqQuery, "%s", sufixo);
            fscanf(arqQuery, "%s", id1);
            fscanf(arqQuery, "%s", id2);
            fscanf(arqQuery, "%s", cor);
            fscanf(arqQuery, "%s", cor2);

            createOutputBBFileName(&nameOutVia, nameInT, nameQueryT, sufixo);
            strcat(nameOutVia, ".svg");
            allocateFileMamory(nameOutVia, pathOut, &arqOutVia);
            arqSvgVia = fopen(arqOutVia, "w");
            checkFile(arqSvgVia, arqOutVia);

            fprintf(arqSvgVia, "<svg>\n");
            printTreeElements(figures, getTreeRoot(figures), arqSvgVia, printRect);
            printTreeElements(figures, getTreeRoot(figures), arqSvgVia, printCircle);
            printTreeElements(blocks, getTreeRoot(blocks), arqSvgVia, printBlock);
            printTreeElements(hydrants, getTreeRoot(hydrants), arqSvgVia, printHydrant);
            printTreeElements(tLights, getTreeRoot(tLights), arqSvgVia, printTrafficLight);
            printTreeElements(rTowers, getTreeRoot(rTowers), arqSvgVia, printRadioTower);
            printTreeElements(buildings, getTreeRoot(buildings), arqSvgVia, printBuilding);
            printTreeElements(walls, getTreeRoot(walls), arqSvgVia, printWall);

            treatP(arqSvgVia, registers, id1, id2, cor, cor2, pathways);
            fprintf(arqSvgVia, "\n</svg>");

            fclose(arqSvgVia);
            free(nameOutVia);
            free(arqOutVia);
        }
    }

    fclose(arqQuery);
    fclose(arqText);
}

void printQuery(FILE *arqSvgQ, FILE *arqAux, Tree figures, Tree blocks, Tree hydrants, Tree tLights, Tree rTowers, Tree buildings, Tree walls){

    printTreeElements(figures, getTreeRoot(figures), arqSvgQ, printCircle);
    printTreeElements(figures, getTreeRoot(figures), arqSvgQ, printRect);
    printTreeElements(blocks, getTreeRoot(blocks), arqSvgQ, printBlock);
    printTreeElements(hydrants, getTreeRoot(hydrants), arqSvgQ, printHydrant);
    printTreeElements(tLights, getTreeRoot(tLights), arqSvgQ, printTrafficLight);
    printTreeElements(rTowers, getTreeRoot(rTowers), arqSvgQ, printRadioTower);
    printTreeElements(buildings, getTreeRoot(buildings), arqSvgQ, printBuilding);
    printTreeElements(walls, getTreeRoot(walls), arqSvgQ, printWall);

    /*Tratamento para desenhar a radiacao luminosa da bomba acima de tudo*/
    rewind(arqAux);
    char c;
    while((c = fgetc(arqAux)) != EOF)
        fputc(c, arqSvgQ);

    fputs("\n</svg>\n", arqSvgQ);
    fclose(arqSvgQ);
    remove("arqAux.txt");
    fclose(arqAux);
}