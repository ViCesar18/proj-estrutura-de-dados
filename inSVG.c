#include "inSVG.h"

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

    fscanf(arq, "%d", &nx);

    return nx;
}

void lerFormaGeometrica(FILE *arq, char *forma){

    fscanf(arq, "%c", forma);
}

void lerCirculo(FILE *arqIn, Lista figuras, FILE *arqOut, FILE *arqOut2){
    int id;
    double r, x, y;
    char strokeCollor[24], fillCollor[24];

    fscanf(arqIn, "%d", &id);
    fscanf(arqIn, "%lf", &r);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);
    fscanf(arqIn, "%s", strokeCollor);
    fscanf(arqIn, "%s", fillCollor);

    Form circulo = criarCirculo(id, x, y, r, strokeCollor, fillCollor);

    inserirElemento(figuras, circulo);

    /*printarCirculo(arqOut, circulo);
    if(arqOut2 != NULL)
        printarCirculo(arqOut2, stFiguras);*/
}

void lerRetangulo(FILE *arqIn, Lista figuras, FILE *arqOut, FILE *arqOut2){
    int id;
    double x, y, w, h;
    char strokeCollor[24], fillCollor[24];

    fscanf(arqIn, "%d", &id);
    fscanf(arqIn, "%lf", &w);
    fscanf(arqIn, "%lf", &h);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);
    fscanf(arqIn, "%s", strokeCollor);
    fscanf(arqIn, "%s", fillCollor);

    Form rect = criarRect(id, x, y, w, h, strokeCollor, fillCollor, 0);

    inserirElemento(figuras, rect);

    /*printarRetangulo(arqOut, figuras[id]);
    if(arqOut2 != NULL)
        printarRetangulo(arqOut2, figuras[id]);*/
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