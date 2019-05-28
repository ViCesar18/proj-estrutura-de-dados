#ifndef LISTA__H
#define LISTA__H

typedef void *Elemento;
typedef void *Lista;

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "outSVG.h"
#include "forms.h"

Lista criarLista(int capacidade);

int getLivre(Lista listaAux);

void inserirElemento(Lista listaAux, Elemento elemento);

void deletarElemento(Lista listaAux, int index);

Elemento getElementoByIndex(Lista ListaAux, int i);

Elemento getElementoById(Lista ListaAux, int id);

void imprimirLista(Lista listaAux, FILE *arqOut);

void imprimirBB(Lista listaAux, FILE *arq, char cor[]);

#endif