#ifndef IN_SVG
#define IN_SVG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "outSVG.h"
#include "list.h"
#include "./Objetos/forms.h"
#include "./Objetos/block.h"
#include "./Objetos/hydrant.h"
#include "./Objetos/traffic_light.h"
#include "./Objetos/radio_tower.h"

/*Nesse header encontra-se todas as funcoes relacionadas a entrada/leitura de dados*/

/*Verifica se o arquivo em questao foi aberto com sucesso, caso contrario, sai do programa*/
void checkFile(FILE *arq, char fname[]);

/*Função que recebe os parâmetros digitados do terminal*/
void receiveParameters(int argc, char *argv[], char **pathIn, char **nameIn, char **nameConsulta, char **pathOut);

/*Trata o nome do arquivo geo/qry caso ele seja passado como parametro junto com um diretorio relativo*/
void treatFileName(char nameIn[], char **nameInT);

/*aloca memoria e cria os diretorios, tambem verifica se a '/' foi ou nao inserida*/
void allocateFileMamory(char fname[], char path[], char **arq);

/*Le os valores de NX do arquivo de entrada .geo*/
void scanNX(FILE *arq, int *nx, int *nq, int *nh, int *ns, int *nr);

/*Le as informacoes de circulo do arquivo .geo e armazena na lista figuras*/
void scanCircle(FILE *arqIn, List figures, char cw[]);

/*Le as informacoes de retangulo do arquivo .geo e armazena na lista figuras*/
void scanRect(FILE *arqIn, List figures, char rw[]);

/*Le as informacoes de quadra do arquivo .geo e armazena na lista blocks*/
void scanBlock(FILE *arqIn, List blocks, char strokeColor[], char fillColor[], char sw[]);

/*Le as informacoes de hidrante do arquivo .geo e armazena na lista hydrants*/
void scanHydrant(FILE *arqIn, List hydrants, char fillColor[], char strokeColor[], char sw[]);

/*Le as informacoes de semaforo do arquivo .geo e armazena na lista tLights*/
void scanTrafficLight(FILE *arqIn, List tLights, char fillColor[], char strokeColor[], char sw[]);

/*Le as informacoes de radio-base do arquivo .geo e armazena na lista radios*/
void scanRadioTower(FILE *arqIn, List rTowers, char fillColor[], char strokeColor[], char sw[]);

/*Muda a cor de todos os elementos que vierem abaixo do comando ch do arquivo .geo*/
void changeColor(FILE *arqIn, char fillColor[], char strokeColor[], char sw[]);

/*Muda a espessura de todos os circulos e retangulos que vierem abaixo do comando sw do arquivo .geo*/
void changeThickness(FILE *arqIn, char cw[], char rw[]);

/*Le as informacoes de texto do arquivo .geo e armazena em variaveis locais*/
void scanText(FILE *arqIn, FILE *arqOut, FILE *arqOut2);

/*Le os parametros de consulta do comando "o?"*/
void scanO(FILE *arqQuery, char j[], char k[]);

/*Le os parametros de consulta do comando "i?"*/
void scanI(FILE *arqQuery, char j[], double *x, double *y);

/*Le os parametros de consulta do comando "d?"*/
void scanD(FILE *arqQuery, char j[], char k[]);

/*Le os parametros de consulta do comando "bb"*/
void scanBB(FILE *arqQuery, char suffix[], char color[]);

/*Le os parametros de consulta do comando "dq"*/
void scanDQ(FILE *arqQuery, char metric[], char id[], double *r);

/*Le os parametros de consulta do comando "cbq" e retorna um circulo com os parametros passados*/
Element scanCBQ(FILE *arqQuery, char cstrk[]);

/*Le os parametros de consulta do comando "trns" e retorna um retangulo com os parametros passados*/
Element scanTRNS(FILE *arqQuery, double *dx, double *dy);

#endif