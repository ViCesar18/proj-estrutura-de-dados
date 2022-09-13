#ifndef QUERY_BUILDINGS__H
#define QUERY_BUILDINGS__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "operations.h"
#include "outSVG.h"
#include "./Objetos/forms.h"
#include "list.h"
#include "heapsort.h"

/*Nesse header encontras-se todas as funcoes relacionadas aos comandos de construcoes e objetos urbanos do arquivo de consulta(.qry), 
aqui são feitas as verificacoes e os calculos matematicos*/

typedef void *Dist;

/*Remove todas as quadras que estiverem inteiramente dentro do circulo dependendo da metrica (L1 ou L2)*/
void treatDQ(FILE *arqTxt, FILE *arqSvgQ, List blocks, char metric[], Form circle);

/*Muda a cor da borda de todas as quadras que estiverem inteiramente dentro do circulo*/
void treatCBQ(FILE *arqTxt, List blocks, Form circle, char cstrk[]);

/*Move todos os equipamentos urbanos que estão inteiramente dentro do retangulo em dx no eixo X e dy no eixo Y*/
void treatTRNS(FILE *arqTxt, List blocks, List hydrants, List tLights, List rTowers, Form rect, double dx, double dy, FILE *arqSvgQ);

/*Retorna a distancia armazenada em uma na estrutura*/
double getDist(Dist distAux);

/*Identifica os ns semaforos mais proximos e os hidrantes em um raio r do foco de incendio (x, y)*/
void treatFI(FILE *arqSvg, FILE *arqTxt, List auxList, double x, double y, int ns, double r, List tLights, List hydrants);

/*Retorna o ponto de endereco (x, y) de um determinado predio*/
void getAddress(char cep[], char face[], int num, double *x, double *y, List blocks);

/*Identifica os k hidrantes mais proximos ou mais distantes de um determinado ponto (x, y)*/
void treatFH(FILE *arqTxt, FILE *arqSvg, List hydrants, int k, double x, double y, List auxList);

/*Identifica os k semaforos mais proximos de um determinado ponto (x, y)*/
void treatFS(FILE *arqTxt, FILE *arqSvg, List hydrants, int k, double x, double y, List auxList);

#endif