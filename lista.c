#include "lista.h"

#define NULO -1

typedef struct{
    Elemento elemento;
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

int getLivre(Lista listaAux){
    ListaImp lista = (ListaImp) listaAux;
    int iLivre;

    iLivre = lista->livre;

    lista->livre = lista->node[lista->livre].prox;

    return iLivre;
}

void inserirElemento(Lista listaAux, Elemento elemento){
    ListaImp lista = (ListaImp) listaAux;
    int iLivre = getLivre(listaAux);

    if(lista->tam <= lista->tamMax){
        if(lista->inicio == NULO){
            lista->node[iLivre].elemento = elemento;
            lista->node[iLivre].prox = NULO;
            lista->node[iLivre].ant = NULO;
            lista->inicio = 0;
            lista->fim = 0;
        }
        else{
            lista->node[iLivre].elemento = elemento;
            lista->node[iLivre].prox = NULO;
            lista->node[iLivre].ant = lista->fim;
            lista->node[lista->fim].prox = iLivre;
            lista->fim = iLivre;
        }
        lista->tam++;
    }
}

void deletarElemento(Lista listaAux, int index){
    ListaImp lista = (ListaImp) listaAux;

    if(index == 0){
        lista->inicio = lista->node[lista->inicio].prox;
        lista->node[lista->node[index].prox].ant = NULO;
    }
    else if(index == lista->tam - 1){
        lista->fim = lista->node[lista->fim].ant;
        lista->node[lista->fim].prox = NULO;
    }
    else{
        lista->node[lista->node[index].ant].prox = lista->node[index].prox;
        lista->node[lista->node[index].prox].ant = lista->node[index].ant;
    }
    lista->node[index].prox = lista->livre;
    lista->livre = index;
}

Elemento getElementoByIndex(Lista listaAux, int i){
    ListaImp lista = (ListaImp) listaAux;

    return lista->node[i].elemento;
}

Elemento getElementoById(Lista listaAux, int id){
    ListaImp lista = (ListaImp) listaAux;

    for(int i = lista->inicio; i != NULO; i = lista->node[i].prox){
        if(getFormId(lista->node[i].elemento) == id){
            return lista->node[i].elemento;
        }
    }
    
    return NULL;
}

void imprimirLista(Lista listaAux, FILE *arqOut){
    ListaImp lista = (ListaImp) listaAux;

    for(int i = lista->inicio; i != NULO; i = lista->node[i].prox){
        if(getFormType(lista->node[i].elemento) == 'c'){
            printarCirculo(arqOut, lista->node[i].elemento);
        }
        else if(getFormType(lista->node[i].elemento) == 'r'){
            printarRetangulo(arqOut, lista->node[i].elemento);
        }
    }
}

void imprimirBB(Lista listaAux, FILE *arq, char cor[]){
    ListaImp lista = (ListaImp) listaAux;

    double x, y, w, h, rx, ry;
    char strokeCollorR[24], fillCollorR[24];

    for(int i = lista->inicio; i != NULO; i = lista->node[i].prox){
        if(getFormType(lista->node[i].elemento) == 'c'){
            printarCirculo(arq, lista->node[i].elemento);
            x = getFormX(lista->node[i].elemento) - getFormR(lista->node[i].elemento);
            y = getFormY(lista->node[i].elemento) - getFormR(lista->node[i].elemento);
            w = 2 * getFormR(lista->node[i].elemento);
            h = 2 * getFormR(lista->node[i].elemento);
            strcpy(strokeCollorR, cor);
            strcpy(fillCollorR, "none");
            Form retangulo = criarRect(0, x, y, w, h, strokeCollorR, fillCollorR, 0);
            printarRetangulo(arq, retangulo);
        }
        else if(getFormType(lista->node[i].elemento) == 'r'){
            printarRetangulo(arq, lista->node[i].elemento);
            x = getFormX(lista->node[i].elemento) + getFormW(lista->node[i].elemento) / 2;
            y = getFormY(lista->node[i].elemento) + getFormH(lista->node[i].elemento) / 2;
            rx = getFormW(lista->node[i].elemento) / 2;
            ry = getFormH(lista->node[i].elemento) / 2;
            printarElipse(arq, x, y, rx, ry, cor);
        }
    }
}