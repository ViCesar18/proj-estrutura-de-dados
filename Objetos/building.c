#include "building.h"

typedef struct stBuilding{
    char cep[32], face[2];
    int num;
    double faceSize, depth, margin;
}*BuildingImp;

Building createBuilding(char cep[], char face[], double num, double faceSize, double depth, double margin){
    BuildingImp building = (BuildingImp)malloc(sizeof(struct stBuilding));

    strcpy(building->cep, cep);
    strcpy(building->face, face);
    building->num = num;
    building->faceSize = faceSize;
    building->depth =  depth;
    building->margin = margin;

    return building;
}

char *getBuildingCep(Building b){
    BuildingImp building = (BuildingImp) b;

    return building->cep;
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

void freeBuilding(Building b){
    BuildingImp block = (BuildingImp) b;

    free(block);   
}