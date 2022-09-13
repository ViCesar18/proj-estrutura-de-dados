#ifndef BLOCK__H
#define BLOCK__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Block;

/*TAD das Quadras*/

/*Coloca os dados de quadra em uma estrutura e retorna a estrutura*/
Block createBlock(char cep[], double x, double y, double w, double h, char strokeColor[], char fillColor[], char sw[]);

/*Getters e setters para a quadra*/
char *getBlockCep(Block b);

double getBlockX(Block b);

double getBlockY(Block b);

double getBlockW(Block b);

double getBlockH(Block b);

char *getBlockStrokeColor(Block b);

char *getBlockFillColor(Block b);

char *getBlockSw(Block b);

void setBlockX(Block b, double x);

void setBlockY(Block b, double y);

void setBlockStrokeColor(Block b, char strokeColor[]);
/*Fim getters e setters*/

/*Libera memoria de uma quadra*/
void freeBlock(Block b);

#endif