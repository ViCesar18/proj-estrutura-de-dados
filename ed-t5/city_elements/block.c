#include "block.h"

typedef struct stBlock{
    char cep[32], strokeColor[24], fillColor[24], sw[12];
    double x, y, w, h;
    int treeX, treeY;
    HashTable residents;
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

    block->treeX = 0;
    block->treeY = 0;

    block->residents = createHashTable(10000, NULL);

    return block;
}

int comparatorBlock(Block b1, Block b2){
    BlockImp block1 = (BlockImp) b1;
    BlockImp block2 = (BlockImp) b2;

    if(block1->x < block2->x) return -1;
    else if(block1->x > block2->x) return 1;
    else{
        if(block1->y < block2->y) return -1;
        else if(block1->y > block2->y) return 1;
        else return 0;
    }
}

char *getBlockCep(Block b){
    BlockImp block = (BlockImp) b;

    return block->cep;
}

void getBlockInformation(Block b, char *info, char *posic){
    BlockImp block = (BlockImp) b;
    sprintf(info, "%s", block->cep);
    sprintf(posic, "(%.2lf, %.2lf)", block->x, block->y);
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

int getBlockTreeX(Block b){
    BlockImp block = (BlockImp) b;

    return block->treeX;
}

int getBlockTreeY(Block b){
    BlockImp block = (BlockImp) b;

    return block->treeY;
}

HashTable getBlockResidents(Block b){
    BlockImp block = (BlockImp) b;

    return block->residents;
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

void setBlockFillColor(Block b, char fillColor[]){
    BlockImp block = (BlockImp) b;

    strcpy(block->fillColor, fillColor);
}

void setBlockSW(Block b, char sw[]){
    BlockImp block = (BlockImp) b;

    strcpy(block->sw, sw);
}

void setBlockTreeXY(Block b, int x, int y){
    BlockImp block = (BlockImp) b;

    block->treeX = x;
    block->treeY = y;
}

void destroyBlock(Block b){
    BlockImp block = (BlockImp) b;
    destroyHashTable(block->residents);
    free(block);   
}