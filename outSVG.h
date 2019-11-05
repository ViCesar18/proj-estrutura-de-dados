#ifndef OUT_SVG
#define OUT_SVG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbtree.h"
#include "./Objetos/forms.h"
#include "./Objetos/block.h"
#include "./Objetos/hydrant.h"
#include "./Objetos/traffic_light.h"
#include "./Objetos/radio_tower.h"
#include "./Objetos/building.h"
#include "./Objetos/wall.h"
#include "vertex.h"
#include "point.h"

typedef void* Vertex;
typedef void* Wall;

/*Nesse header encontra-se todas as funcoes relacionadas a saida de dados*/

/*Aloca memoria e recebe o nome do arquivo de saida em questao*/
void createOutputFileName(char **nameOut, char nameIn[]);

/*Aloca memoria e recebe o nome do arquivo SVG de consulta, alem de tratar o '-'*/
void createOutputQryFileName(char **nameOut, char nameIn[], char nameQuery[]);

/*Aloca memoria e recebe o nome do arquivo SVG de bounding box, alem de tratar os '-'*/
void createOutputBBFileName(char **nameOut, char nameIn[], char nameQuery[], char suffix[]);

/*Desenha um circulo no arquivo SVG*/
void printCircle(FILE *arqOut, Form circle);

/*Desenha um retangulo no arquivo SVG*/
void printRect(FILE *arqOut, Form rect);

/*Escreve um texto no arquivo SVG*/
void printText(FILE *arqOut, double x, double y, char text[], char fillColor[]);

/*Desenha uma linha no arquivo SVG*/
void printLine(FILE *arqOut, double x1, double y1, double x2, double y2, char color[]);

/*Desenha uma elipse no arquivo SVG*/
void printEllipse(FILE *arqOut, double xC, double yC, double rX, double rY, char cor[]);

/*Desenha uma quadra no arquivo SVG*/
void printBlock(FILE *arqOut, Block block);

/*Desenha um hidrante no arquivo SVG*/
void printHydrant(FILE *arqOut, Hydrant hydrant);

/*Desenha um semaforo no arquivo SVG*/
void printTrafficLight(FILE *arqOut, TrafficLight tLight);

/*Desenha uma torre de radio no arquivo SVG*/
void printRadioTower(FILE *arqOut, RadioTower rTower);

/*Desenha um predio no arquivo SVG*/
void printBuilding(FILE *arqOut, Building building, Block block);

/*Desenha um muro no arquivo SVG*/
void printWall(FILE *arqOut, Wall wall);

/*Imprime os elementos da lista e suas bounding box correspondentes no arquivo SVG passado como parametro*/
//void printBB(List figures, FILE *arq, char color[]);

/*Desenha uma bomba no arquivo SVG*/
void printBomb(FILE *arq, double x, double y);

/*Desenha fogo no arquivo SVG*/
void printFire(FILE *arq, double x, double y);

/*Desenha um triangulo no arquivo SVG*/
void printTriangle(FILE *SVG, Form triangle);

void printTriangle2(FILE *arq, double x, double y, Vertex p2, Vertex p3);

#endif