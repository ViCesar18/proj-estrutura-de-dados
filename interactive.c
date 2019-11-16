#include "interactive.h"

void console (char *pathIn, char *pathOut, char *nameInT, int nm, int np, 
            Tree figures, Tree blocks, Tree hydrants, Tree tLights, Tree rTowers, Tree walls, Tree buildings, 
            HashTable formsTable, HashTable blocksTable, HashTable hydrantsTable, HashTable tLightsTable, HashTable rTowersTable, 
            HashTable persons, HashTable residents, HashTable stores, HashTable storeTypes) {

    char comando[32], arg1[16], arg2[16], arg3[16];
    while (1){
        printf ("Insira o comando: ");
        fgets (comando, 32, stdin);
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
            while(1){
                printf ("> ");
                scanf("%s", arg2);
                fflush(stdin);
                if(!strcmp(arg2, "x")) break;
            }
        }

        else{
            printf ("Comando invalido!\n");
        }
    }
    
    return;
}

