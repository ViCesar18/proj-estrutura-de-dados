#ifndef BLOCK__H
#define BLOCK__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Block;

/*Coloca os dados de quadra em uma estrutura e retorna a estrutura*/
Block criarBlock(char cep[], double x, double y, double w, double h, char strokeCollor[], char fillCollor[], char sw[]);

/*Getters e setters para a quadra*/
char *getBlockCep(Block b);

double getBlockX(Block b);

double getBlockY(Block b);

double getBlockW(Block b);

double getBlockH(Block b);

char *getBlockStrokeCollor(Block b);

char *getBlockFillCollor(Block b);

char *getBlockSw(Block b);

void setBlockX(Block b, double x);

void setBlockY(Block b, double y);

void setBlockStrokeCollor(Block b, char strokeCollor[]);
/*Fim getters e setters*/

/*Libera memoria de uma quadra*/
void freeBlock(Block b);

#endif