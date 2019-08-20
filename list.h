#ifndef LIST__H
#define LIST__H

typedef void *Element;
typedef void *List;

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "outSVG.h"
#include "./Objetos/forms.h"
#include "./Objetos/building.h"

/*Cria e aloca memoria para uma lista duplamente encadeada estatica*/
List createList(int capacity);

/*Retorna o inicio da lista*/
int getFirst(List listAux);

/*Retorna a constante NULO que contem o int definido para ser o NULL da lista*/
int getNulo();

/*Retorna o elemento seguinte ao index i*/
int getNext(List listAux, int i);

/*Retorna o elemento anterior ao index i*/
int getPrevious(List listAux, int i);

/*Retorna a proxima posicao livre*/
int getFree(List listAux);

/*Retorna o tamanho atual da lista*/
int getSize(List listAux);

/*Retorna o fim da lista*/
int getLast(List listAux);

char *getType(List listAux, int i);

/*Insere um elemento na lista*/
void insertElement(List listAux, Element element, char type[]);

/*Insere um elemento antes do elemento na posicao "index"*/
void insertBefore(List listAux, Element element, int index);

/*Insere um elemento depois do elemento na posicao "index"*/
void insertAfter(List listAux, Element element, int index);

/*Deleta um elemento da lista filtrando pelo id*/
void deleteElement(List listAux, char id[]);

/*Retorna o elemento da lista cujo index é i*/
Element getElementByIndex(List ListaAux, int i);

/*Retorna o elemento da lista cujo id é igual ao id passado como parametro*/
Element getElementById(List ListaAux, char id[], char type[]);

/*Retorna o elemento pertencente a uma das quatro listas passadas como parametro cujo o id é igual ao passado como parametro*/
Element getElementByIdInLists(List lista1, List lista2, List lista3, List lista4, char id[], char type[]);

/*Imprime os elementos da lista no arquivo SVG passado como parametro*/
void printList(List listAux, FILE *arqOut);

void printBuildingList(List blocksAux, List buildingsAux, FILE *arqOut);

/*Imprime os elementos da lista e suas bounding box correspondentes no arquivo SVG passado como parametro*/
void printBB(List listAux, FILE *arq, char color[]);

/*Desaloca uma lista*/
void deallocateList (List listAux, void (*freeElemento)(Element element));

#endif