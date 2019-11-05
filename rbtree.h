#ifndef RB_TREE
#define RB_TREE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*TAD da Arvore Rubro Negra*/

typedef void *Element;
typedef void *Tree;
typedef void *Node;;

/*Aloca memoria para uma arvore vazia e retorna essa arvore*/
Tree createRBTree(int (*comparator)(Element, Element));

/*Retorna o elemento armazenado pelo no n*/
Element getElement(Tree t, Node n);

/*Retorna o no que contem o elemento element*/
Node findNode(Tree t, Element element);

/*Insere o no n na arvore t*/
void insertNode(Tree t, Element element);

/*Remove o no que armazena o elemento element da arvore t*/
void removeNode(Tree t, Element element);

/*Desalcoa a memoria armazenada para a arvore, seus nos e seus elementos*/
void destroyRBTree(Tree t);

/*Retorna o no identificado pelo id*/
Node getElementById(Tree t, char id[]);

/*Escreve a arvore t no terminal*/
void printTree(Node n, int level);

/*Desenha a arvore t no arquivo SVG*/
void printTreeInSVG(Tree t, FILE* svg);

#endif