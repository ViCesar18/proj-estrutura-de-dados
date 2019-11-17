#include "building.h"

typedef struct stBuilding{
    char cep[32], face[2];
    int num;
    double faceSize, depth, margin, x, y, w, h;
    Block *block;
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

char *getBuildingInformation(Building b, char *info){
    BuildingImp building = (BuildingImp) b;
    sprintf(info, "%s\n(%.2lf, %.2lf)", building->cep, building->x, building->y);

    return info;
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

void destroyBuilding(Building b){
    BuildingImp building = (BuildingImp) b;

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

void setBuildingBlock(Building b, Block block){
    BuildingImp building = (BuildingImp) b;

    building->block = block;
}