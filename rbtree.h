#ifndef RB_TREE
#define RB_TREE

#include <stdio.h>
#include <stdlib.h>
#include "./Objetos/block.h"
#include "./Objetos/forms.h"
#include "./Objetos/building.h"

typedef void* Tree;
typedef void* Element;

/*Inicializa uma arvore*/
Tree createTree();

/*Aloca memoria para o no p*/
Tree initialize(Tree p, Element element);

/*Retorna o vo do no n*/
Tree grandparent(Tree n);

/*Retorna o filho direito do no n*/
Tree getRight(Tree n);

/*Retorna o filho esquerdo do no n*/
Tree getLeft(Tree n);

/*Retorna o elemento armazenado pelo no n*/
Element getElement(Tree n);

/*Retorna o tio do no n*/
Tree uncle(Tree n);

/*Retorna o irmao do no n*/
Tree sibling(Tree n);

/*Retorna a cor do no n*/
Tree colorOf(Tree n);

/*Retorna o numero de nos da arvore*/
void nNodes(Tree n, int *size);

/*Insere o elemento element na arvore tree*/
void insertNode(Tree* tree, Element element, int comparator(Element, Element));

/*Executa as verificacoes e corrige a arvore para continuar a ser uma arvore rubro negra ao inserir um elemento*/
void insertUtil(Tree n);

/*Substitui o no o pelo no n*/
void replaceNode(Tree *t, Tree o, Tree n);

/*Remove o elemento element da arvore t*/
void removeNode(Tree *t, Element element, int comparator(Element, Element));

/*Executa as verificacoes e corrige a arvore para continuar a ser uma arvore rubro negra ao remover um elemento*/
void removeUtil(Tree n);

/*Rotaciona o no n para a direita*/
void rotateRight(Tree n);

/*Rotaciona o no n para a esquerda*/
void rotateLeft(Tree n);

/*Retorna o no pertencente a arvore t que contem o elemento element*/
Tree findNode(Tree *t, Element element, int comparator(Element, Element));

/*Libera memoria para a arvore t*/
void freeRBTree(Tree t);

Tree getElementById(Tree n, char id[]);

Element getElementByIdInLists(Tree t1, Tree t2, Tree t3, Tree t4, char id[]);

/*Desenha no svg os elementos da arvore*/
void printTree(Tree treeAux, FILE *arqOut, void print(FILE*, Element));

void printBuildingTree(Tree blockAux, Tree buildingAux, FILE *arqOut);

#endif