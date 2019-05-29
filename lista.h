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

int getTam(Lista listaAux);

void inserirElemento(Lista listaAux, Elemento elemento, char type[]);

void deletarElemento(Lista listaAux, char id[]);

Elemento getElementoByIndex(Lista ListaAux, int i);

Elemento getElementoById(Lista ListaAux, char id[], char type[]);

Elemento getElementoByIdListas(Lista lista1, Lista lista2, Lista lista3, Lista lista4, char id[], char type[]);

void imprimirLista(Lista listaAux, FILE *arqOut);

void imprimirBB(Lista listaAux, FILE *arq, char cor[]);

#endif