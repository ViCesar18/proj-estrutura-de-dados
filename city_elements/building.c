#include "building.h"

typedef struct stBuilding{
    char cep[32], face[2], fillColor[24];
    int num;
    double faceSize, depth, margin, x, y, w, h;
    int treeX, treeY;
    Block *block;
    HashTable residents;
    char key[64];
    bool hasResidents;
}*BuildingImp;

Building createBuilding(char cep[], char face[], double num, double faceSize, double depth, double margin, Block block){
    BuildingImp building = (BuildingImp)malloc(sizeof(struct stBuilding));

    double xB = getBlockX(block), yB = getBlockY(block), wB = getBlockW(block), hB = getBlockH(block);

    if(!strcmp(face, "N")){
        building->x = xB + num - faceSize / 2;
        building->y = yB + hB - margin - depth;
        building->w = faceSize;
        building->h = depth;
    }
    else if(!strcmp(face, "S")){
        building->x = xB + num - faceSize / 2;
        building->y = yB + margin;
        building->w = faceSize;
        building->h = depth;
    }
    else if(!strcmp(face, "O")){
        building->x = xB + wB - margin - depth;
        building->y = yB + num - faceSize / 2;
        building->w = depth;
        building->h = faceSize;
    }
    else if(!strcmp(face, "L")){
        building->x = xB + margin;
        building->y = yB + num - faceSize / 2;
        building->w = depth;
        building->h = faceSize;
    }
    strcpy(building->cep, cep);
    strcpy(building->face, face);
    building->num = num;
    building->faceSize = faceSize;
    building->depth =  depth;
    building->margin = margin;
    setBuildingBlock(building, block);

    strcpy(building->fillColor, "white");

    building->treeX = 0;
    building->treeY = 0;

    building->residents = createHashTable(10000, NULL);
    char n[8];
    sprintf(n, "%d", building->num);

    strcpy(building->key, building->cep);
    strcat(building->key, building->face);
    strcat(building->key, n);

    building->hasResidents = false;

    return building;
}

int comparatorBuilding(Building b1, Building b2){
    BuildingImp building1 = (BuildingImp) b1;
    BuildingImp building2 = (BuildingImp) b2;

    if(building1->x < building2->x) return -1;
    else if(building1->x > building2->x) return 1;
    else{
        if(building1->y < building2->y) return -1;
        else if(building1->y > building2->y) return 1;
        else return 0;
    }
}

char *getBuildingCep(Building b){
    BuildingImp building = (BuildingImp) b;

    return building->cep;
}

void getBuildingInformation(Building b, char *info, char *posic){
    BuildingImp building = (BuildingImp) b;

    sprintf(info, "%s", building->cep);
    sprintf(posic, "(%lf, %lf)", building->x, building->y);
}

char *getBuildingFace(Building b){
    BuildingImp building = (BuildingImp) b;

    return building->face;
}

int getBuildingNum(Building b){
    BuildingImp building = (BuildingImp) b;

    return building->num;
}

double getBuildingFaceSize(Building b){
    BuildingImp building = (BuildingImp) b;

    return building->faceSize;
}

double getBuildingDepth(Building b){
    BuildingImp building = (BuildingImp) b;

    return building->depth;
}

double getBuildingMargin(Building b){
    BuildingImp building = (BuildingImp) b;

    return building->margin;
}

int getBuildingTreeX(Building b){
    BuildingImp building = (BuildingImp) b;

    return building->treeX;
}

int getBuildingTreeY(Building b){
    BuildingImp building = (BuildingImp) b;

    return building->treeY;
}

void destroyBuilding(Building b){
    BuildingImp building = (BuildingImp) b;
    destroyHashTable(building->residents);
    free(building);   
}

double getBuildingX(Building b){
    BuildingImp building = (BuildingImp) b;

    return building->x;
}

double getBuildingY(Building b){
    BuildingImp building = (BuildingImp) b;

    return building->y;
}

double getBuildingW(Building b){
    BuildingImp building = (BuildingImp) b;

    return building->w;
}

double getBuildingH(Building b){
    BuildingImp building = (BuildingImp) b;

    return building->h;
}

Block getBuildingBlock(Building b){
    BuildingImp building = (BuildingImp) b;

    return building->block;
}

char *getBuildingFillColor(Building b){
    BuildingImp building = (BuildingImp) b;

    return building->fillColor;
}

char *getBuildingKey(Building b){
    BuildingImp building = (BuildingImp) b;

    return building->key;
}

HashTable getBuildingResidents(Building b){
    BuildingImp building = (BuildingImp) b;

    return building->residents;
}

bool getBuildingHasResidents(Building b){
    BuildingImp building = (BuildingImp) b;

    return building->hasResidents;
}

void setBuildingBlock(Building b, Block block){
    BuildingImp building = (BuildingImp) b;

    building->block = block;
}

void setBuildingFillCollor(Building b, char *fillColor){
    BuildingImp building = (BuildingImp) b;

    strcpy(building->fillColor, fillColor);
}

void setBuildingTreeXY(Building b, int x, int y){
    BuildingImp building = (BuildingImp) b;

    building->x = x;
    building->y = y;
}

void setBuildingHasResidents(Building b, bool hasResidents){
    BuildingImp building = (BuildingImp) b;

    building->hasResidents = hasResidents;
}