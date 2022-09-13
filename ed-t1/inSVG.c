#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "inSVG.h"
#include "structs.h"
#include "outSVG.h"

void verificarArquivo(FILE *arq, char nome[]){

    if(arq == NULL){
        printf("Arquivo nao encontrado: %s\n", nome);
        exit(1);
    }
}

void receberParametros(int argc, char *argv[], char **pathIn, char **nameIn, char **nameConsulta, char **pathOut){
    int i = 1;

    while(i < argc){
        if(strcmp("-e", argv[i]) == 0){
            i++;
            *pathIn = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*pathIn, argv[i]);
        }
        else if(strcmp("-f", argv[i]) == 0){
            i++;
            *nameIn = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*nameIn, argv[i]);
        }
        else if(strcmp("-q", argv[i]) == 0){
            i++;
            *nameConsulta = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*nameConsulta, argv[i]);
        }
        else if(strcmp("-o", argv[i]) == 0){
            i++;
            *pathOut = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*pathOut, argv[i]);
        }
        i++;
    }
}

void tratarNome(char nameIn[], char **nameInT){
    int i = 0, j = 0, save;
    bool valid = false;

    *nameInT = (char *)malloc((strlen(nameIn) + 1) * sizeof(char));
    if(nameIn[0] == '.'){
        if(nameIn[1] == '.')
            i = 2;
        else
            i = 1;
    }

    while(1){
        if(nameIn[i] == '/'){
            save = i;
            valid = true;
        }
        else if(nameIn[i] == '.' && i != 0){
            if(valid){
                save++;
                break;
            }
            else{
                strcpy(*nameInT, nameIn);
                return;
            }
        }
        i++;
    }
    while(nameIn[save] != '\0'){
        (*nameInT)[j] = nameIn[save];
        j++;
        save++;
    }
}

void alocarMemoria(char nome[], char dir[], char **arq){

    if(dir[strlen(dir) - 1] == '/'){
        *arq = (char *)malloc((strlen(dir) + strlen(nome) + 1) * sizeof(char));
        sprintf(*arq, "%s%s", dir, nome);
    }
    else{
        *arq = (char *)malloc((strlen(dir) + strlen(nome) + 2) * sizeof(char));
        sprintf(*arq, "%s/%s", dir, nome);
    }

}

int lerNX(FILE *arq){
    int nx;

    fgetc(arq);
    fscanf(arq, "%d", &nx);

    return nx;
}

void lerFormaGeometrica(FILE *arq, char *forma){

    fscanf(arq, "%c", forma);
}

void lerCirculo(FILE *arqIn, Formas figuras[], FILE *arqOut, FILE *arqOut2){
    int id;

    fscanf(arqIn, "%d", &id);
    figuras[id].f = 'c';
    figuras[id].id = id;
    fscanf(arqIn, "%lf", &figuras[id].rC);
    fscanf(arqIn, "%lf", &figuras[id].xC);
    fscanf(arqIn, "%lf", &figuras[id].yC);
    fscanf(arqIn, "%s", figuras[id].strokeCollorC);
    fscanf(arqIn, "%s", figuras[id].fillCollorC);

    printarCirculo(arqOut, figuras[id]);
    if(arqOut2 != NULL)
        printarCirculo(arqOut2, figuras[id]);
}

void lerRetangulo(FILE *arqIn, Formas figuras[], FILE *arqOut, FILE *arqOut2){
    int id;

    fscanf(arqIn, "%d", &id);
    figuras[id].f = 'r';
    figuras[id].id = id;
    fscanf(arqIn, "%lf", &figuras[id].wR);
    fscanf(arqIn, "%lf", &figuras[id].hR);
    fscanf(arqIn, "%lf", &figuras[id].xR);
    fscanf(arqIn, "%lf", &figuras[id].yR);
    fscanf(arqIn, "%s", figuras[id].strokeCollorR);
    fscanf(arqIn, "%s", figuras[id].fillCollorR);
    figuras[id].tracoR = 0;

    printarRetangulo(arqOut, figuras[id]);
    if(arqOut2 != NULL)
        printarRetangulo(arqOut2, figuras[id]);
}

void lerTexto(FILE *arqIn, FILE *arqOut, FILE *arqOut2){
    double x, y;
    char text[128];

    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);
    fgets(text, 128, arqIn);

    printarTexto(arqOut, x, y, text);
    if(arqOut2 != NULL)
        printarTexto(arqOut2, x, y, text);
}

void lerQry(FILE *arqConsul, char q[]){
    
    fscanf(arqConsul, "%s", q);
}

void lerO(FILE *arqConsul, int *j, int *k){

    fscanf(arqConsul, "%d", j);
    fscanf(arqConsul, "%d", k);
}

void lerI(FILE *arqConsul, int *j, double *x, double *y){

    fscanf(arqConsul, "%d", j);
    fscanf(arqConsul, "%lf", x);
    fscanf(arqConsul, "%lf", y);
}

void lerD(FILE *arqConsul, int *j, int *k){

    fscanf(arqConsul, "%d", j);
    fscanf(arqConsul, "%d", k);
}

void lerBB(FILE *arqConsul, char sufixo[], char cor[]){

    fscanf(arqConsul, "%s", sufixo);
    fscanf(arqConsul, "%s", cor);
}