#ifndef IN_SVG
#define IN_SVG

#include "structs.h"

/*Cria o vetor de struct com os circulos e os retangulos*/
int criarStruct(FILE *arq);

/*Le o parametro do arquivo de entrada .geo para definir a forma geometrica a ser desenhada*/
void lerFormaGeometrica(FILE *arq, char *forma);

/*Le as informacoes de circulo do arquivo .geo e armazena na struct*/
void lerCirculo(FILE *arqIn, Formas figuras[], FILE *arqOut);

/*Le as informacoes de retangulo do arquivo .geo e armazena na struct*/
void lerRetangulo(FILE *arqIn, Formas figuras[], FILE *arqOut);

void lerTexto(FILE *arqIn, FILE *arqOut);

#endif