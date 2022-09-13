#ifndef QUERY_BUILDINGS__H
#define QUERY_BUILDINGS__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils/operations.h"
#include "outSVG.h"
#include "./geometry/forms.h"
#include "./data_structures/rbtree.h"
#include "./data_structures/hash_table.h"

/*Nesse header encontras-se todas as funcoes relacionadas aos comandos de construcoes e objetos urbanos do arquivo de consulta(.qry), 
aqui são feitas as verificacoes e os calculos matematicos*/

typedef void* Dist;
typedef void* Tree;
typedef void* Element;

/*Remove todas as quadras que estiverem inteiramente dentro do circulo dependendo da metrica (L1 ou L2)*/
void treatDQ(FILE *arqTxt, FILE *arqSvgQ, Tree blocks, HashTable blocksTable, char metric[], Form circle);

void deleteBlock(Block block, Tree blocks, HashTable blocksTable);

void deleteHydrant(Hydrant hydrant, Tree hydrants, HashTable hydrantsTable);

void deleteTrafficLight(TrafficLight tLight, Tree tLights, HashTable tLightsTable);

void deleteRadioTower(RadioTower rTower, Tree rTowers, HashTable rTowersTable);

void deleteBuilding(Building building, Tree buildings, HashTable buildingsTable);

void treatDEL(FILE *arqText, char *id, Tree blocks, HashTable blocksTable, Tree hydrants, HashTable hydrantsTable, Tree tLights, HashTable tLightsTable, Tree rTowers, HashTable rTowersTable);

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

#endif