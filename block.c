#include "block.h"

typedef struct stBlock{
    char cep[32], strokeCollor[24], fillCollor[24], sw[12];
    double x, y, w, h;
}*BlockImp;

Block criarBlock(char cep[], double x, double y, double w, double h, char strokeCollor[], char fillCollor[], char sw[]){
    BlockImp block = (BlockImp)malloc(sizeof(struct stBlock));

    strcpy(block->cep, cep);
    block->x = x;
    block->y = y;
    block->w = w;
    block->h = h;
    strcpy(block->strokeCollor, strokeCollor);
    strcpy(block->fillCollor, fillCollor);
    strcpy(block->sw, sw);

    return block;
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

char *getBlockStrokeCollor(Block b){
    BlockImp block = (BlockImp) b;

    return block->strokeCollor;
}

char *getBlockFillCollor(Block b){
    BlockImp block = (BlockImp) b;

    return block->fillCollor;
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

void setBlockStrokeCollor(Block b, char strokeCollor[]){
    BlockImp block = (BlockImp) b;

    strcpy(block->strokeCollor, strokeCollor);
}

void freeBlock(Block b){
    BlockImp block = (BlockImp) b;

    free(block);   
}