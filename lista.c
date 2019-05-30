#include "lista.h"

#define NULO -1

typedef struct{
    Elemento elemento;
    char type[4];
    int ant, prox;
}NodeImp;

typedef struct stLista{
    NodeImp *node;
    int inicio, fim;
    int livre, tam, tamMax;
}*ListaImp;

Lista criarLista(int capacidade){

    ListaImp lista = (ListaImp) malloc(sizeof(struct stLista));

    lista->node = (NodeImp*) malloc(capacidade * sizeof(NodeImp));
    lista->tamMax = capacidade;

    for(int i = 0; i < lista->tamMax; i++){
        lista->node[i].prox = i + 1;
    }


    lista->node[lista->tamMax - 1].prox = NULO;
    lista->inicio = NULO;
    lista->fim = NULO;
    lista->livre = 0;
    lista->tam = 0;

    return lista;
}

int getFirst(Lista listaAux){
    ListaImp lista = (ListaImp) listaAux;

    return lista->inicio;
}

int getNulo(){

    return NULO;
}

int getProx(Lista listaAux, int i){
    ListaImp lista = (ListaImp) listaAux;

    return lista->node[i].prox;
}

int getLivre(Lista listaAux){
    ListaImp lista = (ListaImp) listaAux;
    int iLivre;

    iLivre = lista->livre;

    lista->livre = lista->node[lista->livre].prox;

    return iLivre;
}

int getTam(Lista listaAux){
    ListaImp lista = (ListaImp) listaAux;

    return lista->tam;
}

void inserirElemento(Lista listaAux, Elemento elemento, char type[]){
    ListaImp lista = (ListaImp) listaAux;
    int iLivre = getLivre(listaAux);
    if(lista->tam <= lista->tamMax){
        if(lista->inicio == NULO){
            lista->node[iLivre].elemento = elemento;
            lista->node[iLivre].prox = NULO;
            lista->node[iLivre].ant = NULO;
            strcpy(lista->node[iLivre].type, type);
            lista->inicio = 0;
            lista->fim = 0;
        }
        else{
            lista->node[iLivre].elemento = elemento;
            lista->node[iLivre].prox = NULO;
            lista->node[iLivre].ant = lista->fim;
            strcpy(lista->node[iLivre].type, type);
            lista->node[lista->fim].prox = iLivre;
            lista->fim = iLivre;
        }
        lista->tam++;
    }
}

void deletarElemento(Lista listaAux, char id[]){
    ListaImp lista = (ListaImp) listaAux;
    int index;

    for(int i = lista->inicio; i != NULO; i = lista->node[i].prox){
        if(!strcmp(getBlockCep(lista->node[i].elemento), id)){
            index = i;
            break;
        }
    }

    if(index == lista->inicio){
        lista->inicio = lista->node[index].prox;
        lista->node[lista->node[index].prox].ant = NULO;
    }
    else if(lista->node[index].prox == NULO){
        lista->fim = lista->node[index].ant;
        lista->node[lista->fim].prox = NULO;
    }
    else{
        lista->node[lista->node[index].ant].prox = lista->node[index].prox;
        lista->node[lista->node[index].prox].ant = lista->node[index].ant;
    }
    lista->node[index].prox = lista->livre;
    lista->livre = index;
    lista->tam--;
    free(lista->node[index].elemento);
}

Elemento getElementoByIndex(Lista listaAux, int i){
    ListaImp lista = (ListaImp) listaAux;

    return lista->node[i].elemento;
}

Elemento getElementoById(Lista listaAux, char id[], char type[]){
    ListaImp lista = (ListaImp) listaAux;

    for(int i = lista->inicio; i != NULO; i = lista->node[i].prox){
        if(!strcmp(getFormId(lista->node[i].elemento), id)){
            strcpy(type, lista->node[i].type);
            return lista->node[i].elemento;
        }
    }

    return NULL;
}

Elemento getElementoByIdListas(Lista lista1, Lista lista2, Lista lista3, Lista lista4, char id[], char type[]){
    Elemento elemento;

    elemento = getElementoById(lista1, id, type);
    if(elemento == NULL)
        elemento = getElementoById(lista2, id, type);
    if(elemento == NULL)
        elemento = getElementoById(lista3, id, type);
    if(elemento == NULL)
        elemento = getElementoById(lista4, id, type);

    return elemento;
}

void imprimirLista(Lista listaAux, FILE *arqOut){
    ListaImp lista = (ListaImp) listaAux;

    for(int i = lista->inicio; i != NULO; i = lista->node[i].prox){
        if(!strcmp(lista->node[i].type, "c")){
            printarCirculo(arqOut, lista->node[i].elemento);
        }
        else if(!strcmp(lista->node[i].type, "r")){
            printarRetangulo(arqOut, lista->node[i].elemento);
        }
        else if(!strcmp(lista->node[i].type, "q")){
            printarQuadra(arqOut, lista->node[i].elemento);
        }
        else if(!strcmp(lista->node[i].type, "h")){
            printarHidrante(arqOut, lista->node[i].elemento);
        }
        else if(!strcmp(lista->node[i].type, "s")){
            printarSemaforo(arqOut, lista->node[i].elemento);
        }
        else if(!strcmp(lista->node[i].type, "rb")){
            printarRadio(arqOut, lista->node[i].elemento);
        }
    }
}

void imprimirBB(Lista listaAux, FILE *arq, char cor[]){
    ListaImp lista = (ListaImp) listaAux;

    double x, y, w, h, rx, ry;
    char strokeCollorR[24], fillCollorR[24];

    for(int i = lista->inicio; i != NULO; i = lista->node[i].prox){
        if(!strcmp(lista->node[i].type, "c")){
            printarCirculo(arq, lista->node[i].elemento);
            x = getFormX(lista->node[i].elemento) - getFormR(lista->node[i].elemento);
            y = getFormY(lista->node[i].elemento) - getFormR(lista->node[i].elemento);
            w = 2 * getFormR(lista->node[i].elemento);
            h = 2 * getFormR(lista->node[i].elemento);
            strcpy(strokeCollorR, cor);
            strcpy(fillCollorR, "none");
            Form retangulo = criarRect("0", x, y, w, h, strokeCollorR, fillCollorR, 0, "1");
            printarRetangulo(arq, retangulo);
        }
        else if(!strcmp(lista->node[i].type, "r")){
            printarRetangulo(arq, lista->node[i].elemento);
            x = getFormX(lista->node[i].elemento) + getFormW(lista->node[i].elemento) / 2;
            y = getFormY(lista->node[i].elemento) + getFormH(lista->node[i].elemento) / 2;
            rx = getFormW(lista->node[i].elemento) / 2;
            ry = getFormH(lista->node[i].elemento) / 2;
            printarElipse(arq, x, y, rx, ry, cor);
        }
    }
}

void desalocarLista (Lista listaAux, void (*freeElemento)(Elemento elemento)){
    ListaImp lista = (ListaImp) listaAux;

    if (lista->inicio == NULO){
        free (lista->node);
        free (lista);
        return;
    }

    int i = lista->inicio;
    while (1){
        if (lista->node[i].prox == NULO){
            freeElemento (lista->node[i].elemento);
            free (lista->node);
            free (lista);
            break;
        }
        else {
            i = lista->node[i].prox;
            freeElemento (lista->node[lista->node[i].ant].elemento);
        }
    }
}