#ifndef BLOCK__H
#define BLOCK__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Block;

Block criarBlock(char cep[], double x, double y, double w, double h, char strokeCollor[], char fillCollor[], char sw[]);

char *getBlockCep(Block b);

double getBlockX(Block b);

double getBlockY(Block b);

double getBlockW(Block b);

double getBlockH(Block b);

char *getBlockStrokeCollor(Block b);

char *getBlockFillCollor(Block b);

char *getBlockSw(Block b);

#endif