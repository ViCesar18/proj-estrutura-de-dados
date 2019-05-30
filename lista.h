#ifndef LISTA__H
#define LISTA__H

typedef void *Elemento;
typedef void *Lista;

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "outSVG.h"
#include "forms.h"

/*Cria e aloca memoria para uma lista duplamente encadeada estatica*/
Lista criarLista(int capacidade);

/*Retorna o inicio da lista*/
int getFirst(Lista listaAux);

/*Retorna a constante NULO que contem o int definido para ser o NULL da lista*/
int getNulo();

/*Retorna o elemento seguinte do index i*/
int getProx(Lista listaAux, int i);

/*Retorna a proxima posicao livre*/
int getLivre(Lista listaAux);

/*Retorna o tamanho atual da lista*/
int getTam(Lista listaAux);

/*Insere um elemento na lista*/
void inserirElemento(Lista listaAux, Elemento elemento, char type[]);

/*Deleta um elemento da lista filtrando pelo id*/
void deletarElemento(Lista listaAux, char id[]);

/*Retorna o elemento da lista cujo index é i*/
Elemento getElementoByIndex(Lista ListaAux, int i);

/*Retorna o elemento da lista cujo id é igual ao id passado como parametro*/
Elemento getElementoById(Lista ListaAux, char id[], char type[]);

/*Retorna o elemento pertencente a uma das quatro listas passadas como parametro cujo o id é igual ao passado como parametro*/
Elemento getElementoByIdListas(Lista lista1, Lista lista2, Lista lista3, Lista lista4, char id[], char type[]);

/*Imprime os elementos da lista no arquivo SVG passado como parametro*/
void imprimirLista(Lista listaAux, FILE *arqOut);

/*Imprime os elementos da lista e suas bounding box correspondentes no arquivo SVG passado como parametro*/
void imprimirBB(Lista listaAux, FILE *arq, char cor[]);

/*Desaloca uma lista*/
void desalocarLista (Lista listaAux, void (*freeElemento)(Elemento elemento));

#endif