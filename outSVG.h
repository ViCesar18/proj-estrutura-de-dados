#ifndef OUT_SVG
#define OUT_SVG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "./Objetos/forms.h"
#include "./Objetos/block.h"
#include "./Objetos/hydrant.h"
#include "./Objetos/traffic_light.h"
#include "./Objetos/radio_tower.h"
#include "./Objetos/building.h"
#include "./Objetos/wall.h"

/*Nesse header encontra-se todas as funcoes relacionadas a saida de dados*/

/*Aloca memoria e recebe o nome do arquivo de saida em questao*/
void createOutputFileName(char **nameOut, char nameIn[]);

/*Aloca memoria e recebe o nome do arquivo de saida em questao, alem de tratar o '-'*/
void createOutputQryFileName(char **nameOut, char nameIn[], char nameQuery[]);

/*Aloca memoria e recebe o nome do arquivo de saida em questao, alem de tratar os '-'*/
void createOutputBBFileName(char **nameOut, char nameIn[], char nameQuery[], char suffix[]);

/*Recebe como parametros as informacoes para desenhar um circulo em um arquivo SVG*/
void printCircle(FILE *arqOut, Form circle);

/*Recebe como parametros as informacoes para desenhar um retangulo em um arquivo SVG*/
void printRect(FILE *arqOut, Form rect);

/*Recebe como parametros as informacoes para desenhar um texto em um arquivo SVG*/
void printText(FILE *arqOut, double x, double y, char text[], char fillColor[]);

/*Recebe como parametros as informacoes para desenhar uma linha em um arquivo SVG*/
void printLine(FILE *arqOut, double x1, double y1, double x2, double y2, char color[]);

/*Recebe como parametros as informacoes para desenhar uma elipse em um arquivo SVG*/
void printEllipse(FILE *arqOut, double xC, double yC, double rX, double rY, char cor[]);

void printBlock(FILE *arqOut, Block block);

void printHydrant(FILE *arqOut, Hydrant hydrant);

void printTrafficLight(FILE *arqOut, TrafficLight tLight);

void printRadioTower(FILE *arqOut, RadioTower rTower);

void printBuilding(FILE *arqOut, Building building, Block block);

void printWall(FILE *arqOut, Wall wall);

/*Imprime os elementos da lista e suas bounding box correspondentes no arquivo SVG passado como parametro*/
void printBB(List figures, FILE *arq, char color[]);

#endif