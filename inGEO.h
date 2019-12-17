#ifndef IN_SVG
#define IN_SVG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "outSVG.h"
#include "./data_structures/rbtree.h"
#include "./geometry/forms.h"
#include "./city_elements/block.h"
#include "./city_elements/hydrant.h"
#include "./city_elements/traffic_light.h"
#include "./city_elements/radio_tower.h"
#include "./city_elements/building.h"
#include "./city_elements/wall.h"
#include "./data_structures/hash_table.h"
#include "city_elements/store.h"
#include "city_elements/person.h"
#include "city_elements/resident.h"
#include "city_elements/storeType.h"

/*Nesse header encontra-se todas as funcoes relacionadas a entrada/leitura de dados*/

/*Verifica se o arquivo em questao foi aberto com sucesso, caso contrario, sai do programa*/
void checkFile(FILE *arq, char fname[]);

/*Função que recebe os parâmetros digitados do terminal*/
void receiveParameters(int argc, char *argv[], char **pathIn, char **nameIn, char **nameConsulta, char **nameEC, char **namePM, char **pathOut, char **isInteractive);

/*Trata o nome do arquivo geo/qry caso ele seja passado como parametro junto com um diretorio relativo*/
void treatFileName(char nameIn[], char **nameInT);

/*aloca memoria e cria os diretorios, tambem verifica se a '/' foi ou nao inserida*/
void allocateFileMamory(char fname[], char path[], char **arq);

/*Le os valores de NX do arquivo de entrada .geo*/
void scanNX(FILE *arq, int *nx, int *nq, int *nh, int *ns, int *nr, int *np, int *nm);

/*Le as informacoes de circulo do arquivo .geo e armazena na lista figuras*/
void scanCircle(FILE *arqIn, Tree figures, HashTable formsTable, char cw[]);

/*Le as informacoes de retangulo do arquivo .geo e armazena na lista figuras*/
void scanRect(FILE *arqIn, Tree figures, HashTable formsTable, char rw[]);

/*Le as informacoes de quadra do arquivo .geo e armazena na lista blocks*/
void scanBlock(FILE *arqIn, Tree blocks, HashTable blocksTable, char strokeColor[], char fillColor[], char sw[]);

/*Le as informacoes de hidrante do arquivo .geo e armazena na lista hydrants*/
void scanHydrant(FILE *arqIn, Tree hydrants, HashTable hydrantsTable, char fillColor[], char strokeColor[], char sw[]);

/*Le as informacoes de semaforo do arquivo .geo e armazena na lista tLights*/
void scanTrafficLight(FILE *arqIn, Tree tLights, HashTable tLightsTable, char fillColor[], char strokeColor[], char sw[]);

/*Le as informacoes de radio-base do arquivo .geo e armazena na lista radios*/
void scanRadioTower(FILE *arqIn, Tree rTowers, HashTable rTowersTable, char fillColor[], char strokeColor[], char sw[]);

/*Muda a cor de todos os elementos que vierem abaixo do comando ch do arquivo .geo*/
void changeColor(FILE *arqIn, char fillColor[], char strokeColor[], char sw[]);

/*Muda a espessura de todos os circulos e retangulos que vierem abaixo do comando sw do arquivo .geo*/
void changeThickness(FILE *arqIn, char cw[], char rw[]);

/*Le as informacoes de predio do arquivo .geo e armazena na lista buildings*/
void scanBuilding(FILE *arqIn, Tree buildings, HashTable blocksTable, HashTable buildingsTable);

/*Le as informacoes de muro do arquivo .geo e armazena na lista walls*/
void scanWall(FILE *arqIn, Tree walls);

void scanStoreType (FILE *arqEst, HashTable storeTypes);

void scanStore (FILE *arqEst, HashTable stores, HashTable storeTypes, HashTable persons, HashTable blocksTable);

void scanPerson (FILE *arqPes, HashTable persons);

void scanResident (FILE *arqPes, HashTable residents, HashTable persons, HashTable buildingsTable, HashTable blocksTable);

/*Le as informacoes de texto do arquivo .geo e armazena em variaveis locais*/
void scanText(FILE *arqIn, FILE *arqOut, FILE *arqOut2);

#endif