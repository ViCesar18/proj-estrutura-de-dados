#include "interactive.h"

void console (char *pathIn, char *pathOut, char *nameInT, int nm, int np, 
            Tree figures, Tree blocks, Tree hydrants, Tree tLights, Tree rTowers, Tree walls, Tree buildings, 
            HashTable formsTable, HashTable blocksTable, HashTable hydrantsTable, HashTable tLightsTable, HashTable rTowersTable, 
            HashTable persons, HashTable residents, HashTable stores, HashTable storeTypes) {

    char comando[24], arg1[8], arg2[8], arg3[8];
    while (1){
        printf ("Insira o comando: ");
        //__fpurge(stdin);
        fgets (comando, 24, stdin);
        sscanf (comando, "%s %s %s", arg1, arg2, arg3);

        if (strcmp (arg1, "sai") == 0) break;

        else if (strcmp (arg1, "q") == 0){
            FILE *arqQuery = NULL, *arqText = NULL, *arqSvgQ = NULL, *arqAux = NULL;
            char *nameQueryT = NULL, *arqQry = NULL, *arqTxt = NULL, *nameTxt = NULL, *nameOutQ = NULL, *arqOutQ = NULL;

            //Tratando arqQuery
            if(arg2 != NULL){
                treatFileName(arg2, &nameQueryT);

                if(pathIn != NULL){
                    allocateFileMamory(arg2, pathIn, &arqQry);
                    arqQuery = fopen(arqQry, "r");
                    checkFile(arqQuery, arqQry);
                }
                else{
                    arqQuery = fopen(arg2, "r");
                    checkFile(arqQuery, arg2);
                }
            }

            //Tratando resto
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

            printf("Arquivo de Consulta %s lido com sucesso.\n", arg2);

            treatQueries(arqQuery, arqText, arqSvgQ, arqAux, nameInT, nameQueryT, pathOut, nm, np, figures, blocks, hydrants, tLights, rTowers, walls, 
            buildings, formsTable, blocksTable, hydrantsTable, tLightsTable, rTowersTable, persons, residents, stores, storeTypes);

            printQuery(arqSvgQ, arqAux, figures, blocks, hydrants, tLights, rTowers, buildings, walls);

            free(nameQueryT);
            free(nameOutQ);
            free(arqOutQ);
            free(nameTxt);
            free(arqTxt);
            free(arqQry);
        }

        else if (strcmp (arg1, "dmprbt") == 0){
            treatDMPRBT(arg2, arg3, pathOut, blocks, hydrants, tLights, rTowers, buildings, walls);
            printf ("Arvore: %s\nNome do arquivo gerado: %s\n", arg2, arg3);
        }

        else if (strcmp (arg1, "nav") == 0){
            if(!strcmp(arg2, "q")){
                Node aux = getTreeRoot(blocks);
                while(1){
                    if(aux != getNil(blocks)){
                        Block block = getElement(blocks, aux);
                        printf("\nCor do No: %s\n", getNodeColor(aux) == 0 ? "Vermelho" : "Preto");
                        printf("CEP: %s\n", getBlockCep(block));
                        printf("X: %lf\n", getBlockX(block));
                        printf("Y: %lf\n", getBlockY(block));
                        printf("W: %lf\n", getBlockW(block));
                        printf("H: %lf\n", getBlockH(block));
                        printf("Preenchimento: %s\n", getBlockFillColor(block));
                        printf("Borda: %s\n", getBlockStrokeColor(block));
                        printf("Largura da Borda: %s\n", getBlockSw(block));
                    }

                    printf ("> ");
                    fgets(arg3, 8, stdin);
                    if(!strcmp(arg3, "e\n")){
                        if(getLeft(blocks, aux) == getNil(blocks)) printf("\nNo nao tem filho esquerdo!\n");
                        else aux = getLeft(blocks, aux);
                    }
                    else if(!strcmp(arg3, "d\n")){
                        if(getRight(blocks, aux) == getNil(blocks)) printf("\nNo nao tem filho direito!\n");
                        else aux = getRight(blocks, aux);
                    }
                    else if(!strcmp(arg3, "p\n")){
                        if(aux == getTreeRoot(blocks)) printf("\nNo nao tem pai!\n");
                        else aux = getParent(blocks, aux);
                    }
                    else if(!strcmp(arg3, "x\n")) break;
                    else printf("\nComando invalido!\n");
                }
            }
            else if(!strcmp(arg2, "h")){
                Node aux = getTreeRoot(hydrants);
                while(1){
                    if(aux != getNil(hydrants)){
                        Hydrant hydrant = getElement(hydrants, aux);
                        printf("\nCor do No: %s\n", getNodeColor(aux) == 0 ? "Vermelho" : "Preto");
                        printf("ID: %s\n", getHydrantId(hydrant));
                        printf("X: %lf\n", getHydrantX(hydrant));
                        printf("Y: %lf\n", getHydrantY(hydrant));
                        printf("Preenchimento: %s\n", getHydrantFillColor(hydrant));
                        printf("Borda: %s\n", getHydrantStrokeColor(hydrant));
                        printf("Largura da Borda: %s\n", getHydrantSw(hydrant));
                    }

                    printf ("> ");
                    fgets(arg3, 8, stdin);
                    if(!strcmp(arg3, "e\n")){
                        if(getLeft(hydrants, aux) == getNil(hydrants)) printf("\nNo nao tem filho esquerdo!\n");
                        else aux = getLeft(hydrants, aux);
                    }
                    else if(!strcmp(arg3, "d\n")){
                        if(getRight(hydrants, aux) == getNil(hydrants)) printf("\nNo nao tem filho direito!\n");
                        else aux = getRight(hydrants, aux);
                    }
                    else if(!strcmp(arg3, "p\n")){
                        if(aux == getTreeRoot(hydrants)) printf("\nNo nao tem pai!\n");
                        else aux = getParent(hydrants, aux);
                    }
                    else if(!strcmp(arg3, "x\n")) break;
                    else printf("\nComando invalido!\n");
                }
            }
            else if(!strcmp(arg2, "s")){
                Node aux = getTreeRoot(tLights);
                while(1){
                    if(aux != getNil(tLights)){
                        TrafficLight tLight = getElement(tLights, aux);
                        printf("\nCor do No: %s\n", getNodeColor(aux) == 0 ? "Vermelho" : "Preto");
                        printf("ID: %s\n", getTrafficLightId(tLight));
                        printf("X: %lf\n", getTrafficLightX(tLight));
                        printf("Y: %lf\n", getTrafficLightY(tLight));
                        printf("Preenchimento: %s\n", getTrafficLightFillColor(tLight));
                        printf("Borda: %s\n", getTrafficLightStrokeColor(tLight));
                        printf("Largura da Borda: %s\n", getTrafficLightSw(tLight));
                    }

                    printf ("> ");
                    fgets(arg3, 8, stdin);
                    if(!strcmp(arg3, "e\n")){
                        if(getLeft(tLights, aux) == getNil(tLights)) printf("\nNo nao tem filho esquerdo!\n");
                        else aux = getLeft(tLights, aux);
                    }
                    else if(!strcmp(arg3, "d\n")){
                        if(getRight(tLights, aux) == getNil(tLights)) printf("\nNo nao tem filho direito!\n");
                        else aux = getRight(tLights, aux);
                    }
                    else if(!strcmp(arg3, "p\n")){
                        if(aux == getTreeRoot(tLights)) printf("\nNo nao tem pai!\n");
                        else aux = getParent(tLights, aux);
                    }
                    else if(!strcmp(arg3, "x\n")) break;
                    else printf("\nComando invalido!\n");
                }
            }
            else if(!strcmp(arg2, "t")){
                Node aux = getTreeRoot(rTowers);
                while(1){
                    if(aux != getNil(rTowers)){
                        RadioTower rTower = getElement(rTowers, aux);
                        printf("\nCor do No: %s\n", getNodeColor(aux) == 0 ? "Vermelho" : "Preto");
                        printf("ID: %s\n", getRadioTowerId(rTower));
                        printf("X: %lf\n", getRadioTowerX(rTowers));
                        printf("Y: %lf\n", getRadioTowerY(rTower));
                        printf("Preenchimento: %s\n", getRadioTowerFillColor(rTower));
                        printf("Borda: %s\n", getRadioTowerStrokeColor(rTower));
                        printf("Largura da Borda: %s\n", getRadioTowerSw(rTower));
                    }

                    printf ("> ");
                    fgets(arg3, 8, stdin);
                    if(!strcmp(arg3, "e\n")){
                        if(getLeft(rTowers, aux) == getNil(rTowers)) printf("\nNo nao tem filho esquerdo!\n");
                        else aux = getLeft(rTowers, aux);
                    }
                    else if(!strcmp(arg3, "d\n")){
                        if(getRight(rTowers, aux) == getNil(rTowers)) printf("\nNo nao tem filho direito!\n");
                        else aux = getRight(rTowers, aux);
                    }
                    else if(!strcmp(arg3, "p\n")){
                        if(aux == getTreeRoot(rTowers)) printf("\nNo nao tem pai!\n");
                        else aux = getParent(rTowers, aux);
                    }
                    else if(!strcmp(arg3, "x\n")) break;
                    else printf("\nComando invalido!\n");
                }
            }
            else if(!strcmp(arg2, "p")){
                Node aux = getTreeRoot(buildings);
                while(1){
                    if(aux != getNil(buildings)){
                        Building building = getElement(buildings, aux);
                        printf("\nCor do No: %s\n", getNodeColor(aux) == 0 ? "Vermelho" : "Preto");
                        printf("CEP: %s\n", getBuildingCep(building));
                        printf("Face: %s\n", getBuildingFace(building));
                        printf("Numero: %d\n", getBuildingNum(building));
                        printf("Tamanho da Face: %lf\n", getBuildingFaceSize(building));
                        printf("Profundidade: %lf\n", getBuildingDepth(building));
                        printf("Margem: %lf\n", getBuildingMargin(building));
                        printf("X: %lf\n", getBuildingX(building));
                        printf("Y: %lf\n", getBuildingY(building));
                        printf("W: %lf\n", getBuildingW(building));
                        printf("H: %lf\n", getBuildingH(building));
                    }

                    printf ("> ");
                    fgets(arg3, 8, stdin);
                    if(!strcmp(arg3, "e\n")){
                        if(getLeft(buildings, aux) == getNil(buildings)) printf("\nNo nao tem filho esquerdo!\n");
                        else aux = getLeft(buildings, aux);
                    }
                    else if(!strcmp(arg3, "d\n")){
                        if(getRight(buildings, aux) == getNil(buildings)) printf("\nNo nao tem filho direito!\n");
                        else aux = getRight(buildings, aux);
                    }
                    else if(!strcmp(arg3, "p\n")){
                        if(aux == getTreeRoot(buildings)) printf("\nNo nao tem pai!\n");
                        else aux = getParent(buildings, aux);
                    }
                    else if(!strcmp(arg3, "x\n")) break;
                    else printf("\nComando invalido!\n");
                }
            }
            else if(!strcmp(arg2, "m")){
                Node aux = getTreeRoot(walls);
                while(1){
                    if(aux != getNil(walls)){
                        Wall wall = getElement(walls, aux);
                        printf("\nCor do No: %s\n", getNodeColor(aux) == 0 ? "Vermelho" : "Preto");
                        printf("X1: %lf\n", getWallX1(wall));
                        printf("Y1: %lf\n", getWallY1(wall));
                        printf("X2: %lf\n", getWallX2(wall));
                        printf("Y2: %lf\n", getWallY2(wall));
                        printf("Tamanho: %lf\n", getWallSize(wall));
                    }

                    printf ("> ");
                    fgets(arg3, 8, stdin);
                    if(!strcmp(arg3, "e\n")){
                        if(getLeft(walls, aux) == getNil(walls)) printf("\nNo nao tem filho esquerdo!\n");
                        else aux = getLeft(walls, aux);
                    }
                    else if(!strcmp(arg3, "d\n")){
                        if(getRight(walls, aux) == getNil(walls)) printf("\nNo nao tem filho direito!\n");
                        else aux = getRight(walls, aux);
                    }
                    else if(!strcmp(arg3, "p\n")){
                        if(aux == getTreeRoot(walls)) printf("\nNo nao tem pai!\n");
                        else aux = getParent(walls, aux);
                    }
                    else if(!strcmp(arg3, "x\n")) break;
                    else printf("\nComando invalido!\n");
                }
            }
        }

        else{
            printf ("\nComando invalido!\n\n");
        }
    }
    
    return;
}

