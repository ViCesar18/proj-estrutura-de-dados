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

void lerNX(FILE *arq, int *nx, int *nq, int *nh, int *ns, int *nr){

    fscanf(arq, "%d", nx);
    fscanf(arq, "%d", nq);
    fscanf(arq, "%d", nh);
    fscanf(arq, "%d", ns);
    fscanf(arq, "%d", nr);
}

void lerCirculo(FILE *arqIn, Lista figuras, char cw[]){
    char id[32];
    double r, x, y;
    char strokeCollor[24], fillCollor[24];

    fscanf(arqIn, "%s", id);
    fscanf(arqIn, "%lf", &r);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);
    fscanf(arqIn, "%s", strokeCollor);
    fscanf(arqIn, "%s", fillCollor);

    Form circulo = criarCirculo(id, x, y, r, strokeCollor, fillCollor, cw);

    inserirElemento(figuras, circulo, "c");
}

void lerRetangulo(FILE *arqIn, Lista figuras, char rw[]){
    char id[32];
    double x, y, w, h;
    char strokeCollor[24], fillCollor[24];

    fscanf(arqIn, "%s", id);
    fscanf(arqIn, "%lf", &w);
    fscanf(arqIn, "%lf", &h);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);
    fscanf(arqIn, "%s", strokeCollor);
    fscanf(arqIn, "%s", fillCollor);

    Form rect = criarRect(id, x, y, w, h, strokeCollor, fillCollor, 0, rw);

    inserirElemento(figuras, rect, "r");
}

void lerQuadra(FILE *arqIn, Lista blocks, char fillCollor[], char strokeCollor[], char sw[]){
    char cep[64];
    double x, y, w, h;

    fscanf(arqIn, "%s", cep);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);
    fscanf(arqIn, "%lf", &w);
    fscanf(arqIn, "%lf", &h);

    Block block = criarBlock(cep, x, y, w, h, strokeCollor, fillCollor, sw);

    inserirElemento(blocks, block, "q");
}

void lerHidrante(FILE *arqIn, Lista hydrants, char fillCollor[], char strokeCollor[], char sw[]){
    char id[32];
    double x, y;

    fscanf(arqIn, "%s", id);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);

    Hydrant hydrant = criarHydrant(id, x, y, strokeCollor, fillCollor, sw);

    inserirElemento(hydrants, hydrant, "h");
}

void lerSemaforo(FILE *arqIn, Lista semaphores, char fillCollor[], char strokeCollor[], char sw[]){
    char id[32];
    double x, y;

    fscanf(arqIn, "%s", id);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);

    Semaphore semaphore = criarSemaphore(id, x, y, strokeCollor, fillCollor, sw);

    inserirElemento(semaphores, semaphore, "s");
}

void lerRadio(FILE *arqIn, Lista radios, char fillCollor[], char strokeCollor[], char sw[]){
    char id[32];
    double x, y;

    fscanf(arqIn, "%s", id);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);

    Radio radio = criarRadio(id, x, y, strokeCollor, fillCollor, sw);

    inserirElemento(radios, radio, "rb");
}

void alterarCor(FILE *arqIn, char fillCollor[], char strokeCollor[], char sw[]){

    fscanf(arqIn, "%s", fillCollor);
    fscanf(arqIn, "%s", strokeCollor);
    fscanf(arqIn, "%s", sw);
}

void alterarEspessura(FILE *arqIn, char cw[], char rw[]){

    fscanf(arqIn, "%s", cw);
    fscanf(arqIn, "%s", rw);
}

void lerTexto(FILE *arqIn, FILE *arqOut, FILE *arqOut2){
    double x, y;
    char text[128];

    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);
    fgets(text, 128, arqIn);

    printarTexto(arqOut, x, y, text, "black");
    if(arqOut2 != NULL)
        printarTexto(arqOut2, x, y, text, "black");
}

void lerO(FILE *arqConsul, char j[], char k[]){

    fscanf(arqConsul, "%s", j);
    fscanf(arqConsul, "%s", k);
}

void lerI(FILE *arqConsul, char j[], double *x, double *y){

    fscanf(arqConsul, "%s", j);
    fscanf(arqConsul, "%lf", x);
    fscanf(arqConsul, "%lf", y);
}

void lerD(FILE *arqConsul, char j[], char k[]){

    fscanf(arqConsul, "%s", j);
    fscanf(arqConsul, "%s", k);
}

void lerBB(FILE *arqConsul, char sufixo[], char cor[]){

    fscanf(arqConsul, "%s", sufixo);
    fscanf(arqConsul, "%s", cor);
}

void lerDQ(FILE *arqConsul, char L[], char id[], double *r){

    fscanf(arqConsul, "%s", L);
    fscanf(arqConsul, "%s", id);
    fscanf(arqConsul, "%lf", r);
}