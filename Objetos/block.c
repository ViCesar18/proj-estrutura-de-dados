#include "block.h"

typedef struct stBlock{
    char cep[32], strokeColor[24], fillColor[24], sw[12];
    double x, y, w, h;
}*BlockImp;

Block createBlock(char cep[], double x, double y, double w, double h, char strokeColor[], char fillColor[], char sw[]){
    BlockImp block = (BlockImp)malloc(sizeof(struct stBlock));

    strcpy(block->cep, cep);
    block->x = x;
    block->y = y;
    block->w = w;
    block->h = h;
    strcpy(block->strokeColor, strokeColor);
    strcpy(block->fillColor, fillColor);
    strcpy(block->sw, sw);

    return block;
}

int comparatorBlock(Block b1, Block b2){
    BlockImp block1 = (BlockImp) b1;
    BlockImp block2 = (BlockImp) b2;

    return strcmp(block1->cep, block2->cep);
}

char *getBlockCep(Block b){
    BlockImp block = (BlockImp) b;

    return block->cep;
}

double getBlockX(Block b){
    BlockImp block = (BlockImp) b;

    return block->x;
}

double getBlockY(Block b){
    BlockImp block = (BlockImp) b;

    return block->y;
}

double getBlockW(Block b){
    BlockImp block = (BlockImp) b;

    return block->w;
}

double getBlockH(Block b){
    BlockImp block = (BlockImp) b;

    return block->h;
}

char *getBlockStrokeColor(Block b){
    BlockImp block = (BlockImp) b;

    return block->strokeColor;
}

char *getBlockFillColor(Block b){
    BlockImp block = (BlockImp) b;

    return block->fillColor;
}

char *getBlockSw(Block b){
    BlockImp block = (BlockImp) b;

    return block->sw;
}

void setBlockX(Block b, double x){
    BlockImp block = (BlockImp) b;

    block->x = x;
}

void setBlockY(Block b, double y){
    BlockImp block = (BlockImp) b;

    block->y = y;
}

void setBlockStrokeColor(Block b, char strokeColor[]){
    BlockImp block = (BlockImp) b;

    strcpy(block->strokeColor, strokeColor);
}

void freeBlock(Block b){
    BlockImp block = (BlockImp) b;

    free(block);   
}