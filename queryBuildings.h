#ifndef QUERY_BUILDINGS__H
#define QUERY_BUILDINGS__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "operations.h"
#include "outSVG.h"
#include "./objects/forms.h"
#include "./data_structures/rbtree.h"
#include "heapsort.h"
#include "./data_structures/hash_table.h"

/*Nesse header encontras-se todas as funcoes relacionadas aos comandos de construcoes e objetos urbanos do arquivo de consulta(.qry), 
aqui são feitas as verificacoes e os calculos matematicos*/

typedef void* Dist;
typedef void* Tree;
typedef void* Element;

/*Remove todas as quadras que estiverem inteiramente dentro do circulo dependendo da metrica (L1 ou L2)*/
void treatDQ(FILE *arqTxt, FILE *arqSvgQ, Tree blocks, Node node, char metric[], Form circle);

/*Muda a cor da borda de todas as quadras que estiverem inteiramente dentro do circulo*/
void treatCBQ(FILE *arqTxt, Tree blocks, Node node, Form circle, char *cstrk);

/*Move todas as quadras que estão inteiramente dentro do retangulo em dx no eixo X e dy no eixo Y*/
void treatTRNS_block(FILE *arqTxt, Tree blocks, Node node, Form rect, double dx, double dy, FILE *arqSvgQ);

/*Move todos os hidrantes que estão inteiramente dentro do retangulo em dx no eixo X e dy no eixo Y*/
void treatTRNS_hydrant(FILE *arqTxt, Tree hydrants, Node node, Form rect, double dx, double dy, FILE *arqSvgQ);

/*Move todos semaforos que estão inteiramente dentro do retangulo em dx no eixo X e dy no eixo Y*/
void treatTRNS_tLight(FILE *arqTxt, Tree tLights, Node node, Form rect, double dx, double dy, FILE *arqSvgQ);

/*Move todas as torres de radio que estão inteiramente dentro do retangulo em dx no eixo X e dy no eixo Y*/
void treatTRNS_rTower(FILE *arqTxt, Tree rTowers, Node node, Form rect, double dx, double dy, FILE *arqSvgQ);

/*Retorna a distancia armazenada em uma na estrutura*/
double getDist(Dist distAux);

/*Identifica os ns semaforos mais proximos e os hidrantes em um raio r do foco de incendio (x, y)*/
void treatFI(FILE *arqSvg, FILE *arqTxt, double x, double y, int ns, double r, Tree tLights, Tree hydrants);

/*Retorna o ponto de endereco (x, y) de um determinado predio*/
void getAddress(char cep[], char face[], int num, double *x, double *y, HashTable blocksTable);

/*Identifica os k hidrantes mais proximos ou mais distantes de um determinado ponto (x, y)*/
void treatFH(FILE *arqTxt, FILE *arqSvg, Tree hydrants, int k, double x, double y);

/*Identifica os k semaforos mais proximos de um determinado ponto (x, y)*/
void treatFS(FILE *arqTxt, FILE *arqSvg, Tree hydrantRoot, int k, double x, double y);

#endif