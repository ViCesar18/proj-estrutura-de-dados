#ifndef OUT_SVG
#define OUT_SVG

#include "structs.h"

void criarArqSaida(char **nameOut, char nameIn[]);

void printarCirculo(FILE *arqOut, Formas figuras);

void printarRetangulo(FILE *arqOut, Formas figuras);

void printarTexto(FILE *arqOut, double x, double y, char text[]);



#endif