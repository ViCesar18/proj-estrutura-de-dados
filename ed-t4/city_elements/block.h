#ifndef BLOCK__H
#define BLOCK__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../data_structures/hash_table.h"

typedef void *Block;

/*TAD das Quadras*/

/*Coloca os dados de quadra em uma estrutura e retorna a estrutura*/
Block createBlock(char cep[], double x, double y, double w, double h, char strokeColor[], char fillColor[], char sw[]);

/*Compara os cep's de b1 e b2*/
int comparatorBlock(Block b1, Block b2);

/*Getters e setters para a quadra*/
char *getBlockCep(Block b);

void getBlockInformation(Block b, char *info, char *posic);

double getBlockX(Block b);

double getBlockY(Block b);

double getBlockW(Block b);

double getBlockH(Block b);

char *getBlockStrokeColor(Block b);

char *getBlockFillColor(Block b);

char *getBlockSw(Block b);

int getBlockTreeX(Block b);

int getBlockTreeY(Block b);

HashTable getBlockResidents(Block b);

void setBlockX(Block b, double x);

void setBlockY(Block b, double y);

void setBlockStrokeColor(Block b, char strokeColor[]);

void setBlockFillColor(Block b, char fillColor[]);

void setBlockSW(Block b, char sw[]);

void setBlockTreeXY(Block b, int x, int y);
/*Fim getters e setters*/

/*Libera memoria de uma quadra*/
void destroyBlock(Block b);

#endif