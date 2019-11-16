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
Tree createRBTree(int (*comparator)(Element, Element), void (*destroy)(Element));

/*Retorna o elemento armazenado pelo no n*/
Element getElement(Tree t, Node n);

/*Retorna a raiz da arvore t*/
Node getTreeRoot(Tree t);

Node getNil(Tree t);

Node getLeft(Tree t, Node n);

Node getRight(Tree t, Node n);

int getSize(Tree t);

/*Retorna o no que contem o elemento element*/
Node findNode(Tree t, Element element);

/*Insere o no n na arvore t*/
void insertNode(Tree t, Element element);

/*Remove o no que armazena o elemento element da arvore t*/
void removeNode(Tree t, Element element);

/*Desalcoa a memoria armazenada para a arvore, seus nos e seus elementos*/
void destroyRBTree(Tree t);

/*Escreve a arvore t no terminal*/
void printTree(Node n, int level);

/*Desenha os elementos armazenados na arvore t no arquivo svg*/
void printTreeElements(Tree t, Node n, FILE *arqSVG, void (*printElement)(FILE*, Element));

//void printTreeInSVG_util(TreeImp tree, Node n, int x, FILE* svg, char *(getId)(Element));

/*Desenha a arvore t no arquivo SVG*/
void printTreeInSVG(Tree t, FILE* svg, void (getId)(Element, char*, char*));

#endif