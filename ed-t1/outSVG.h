#ifndef OUT_SVG
#define OUT_SVG

#include "structs.h"

/*Nesse header encontra-se todas as funcoes relacionadas a saida de dados*/

/*Aloca memoria e recebe o nome do arquivo de saida em questao*/
void criarArqSaida(char **nameOut, char nameIn[]);

/*Aloca memoria e recebe o nome do arquivo de saida em questao, alem de tratar o '-'*/
void criarArqSaida2(char **nameOut, char nameIn[], char nameConsulta[]);

/*Aloca memoria e recebe o nome do arquivo de saida em questao, alem de tratar os '-'*/
void criarArqSaida3(char **nameOut, char nameIn[], char nameConsulta[], char sufixo[]);

/*Recebe como parametros as informacoes para desenhar um circulo em um arquivo SVG*/
void printarCirculo(FILE *arqOut, Formas figuras);

/*Recebe como parametros as informacoes para desenhar um retangulo em um arquivo SVG*/
void printarRetangulo(FILE *arqOut, Formas figuras);

/*Recebe como parametros as informacoes para desenhar um texto em um arquivo SVG*/
void printarTexto(FILE *arqOut, double x, double y, char text[]);

/*Recebe como parametros as informacoes para desenhar uma linha em um arquivo SVG*/
void printarLinha(FILE *arqOut, double x1, double y1, double x2, double y2, char color[]);

/*Recebe como parametros as informacoes para desenhar uma elipse em um arquivo SVG*/
void printarElipse(FILE *arqOut, double xC, double yC, double rX, double rY, char cor[]);

#endif