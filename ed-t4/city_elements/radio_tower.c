#include "radio_tower.h"

typedef struct stRadioTower{
    char id[32], strokeColor[24], fillColor[24], sw[12];
    double x, y;
    int treeX, treeY;
}*RadioTowerImp;

RadioTower createRadioTower(char id[], double x, double y, char strokeColor[], char fillColor[], char sw[]){
    RadioTowerImp rTower = (RadioTowerImp) malloc(sizeof(struct stRadioTower));

    strcpy(rTower->id, id);
    rTower->x = x;
    rTower->y = y;
    strcpy(rTower->strokeColor, strokeColor);
    strcpy(rTower->fillColor, fillColor);
    strcpy(rTower->sw, sw);

    rTower->treeX = 0;
    rTower->treeY = 0;

    return rTower;
}

int comparatorRadioTower(RadioTower rb1, RadioTower rb2){
    RadioTowerImp radioTower1 = (RadioTowerImp) rb1;
    RadioTowerImp radioTower2 = (RadioTowerImp) rb2;

    if(radioTower1->x < radioTower2->x) return -1;
    else if(radioTower1->x > radioTower2->x) return 1;
    else{
        if(radioTower1->y < radioTower2->y) return -1;
        else if(radioTower1->y > radioTower2->y) return 1;
        else return 0;
    }
}

char *getRadioTowerId(RadioTower r){
    RadioTowerImp rTower = (RadioTowerImp) r;

    return rTower->id;
}

void getRadioTowerInformation(RadioTower r, char *info, char *posic){
    RadioTowerImp rTower = (RadioTowerImp) r;

    sprintf(info, "%s", rTower->id);
    sprintf(posic, "(%lf, %lf)", rTower->x, rTower->y);
}

double getRadioTowerX(RadioTower r){
    RadioTowerImp rTower = (RadioTowerImp) r;

    return rTower->x;
}

double getRadioTowerY(RadioTower r){
    RadioTowerImp rTower = (RadioTowerImp) r;

    return rTower->y;
}

char *getRadioTowerStrokeColor(RadioTower r){
    RadioTowerImp rTower = (RadioTowerImp) r;

    return rTower->strokeColor;
}

char *getRadioTowerFillColor(RadioTower r){
    RadioTowerImp rTower = (RadioTowerImp) r;

    return rTower->fillColor;
}

char *getRadioTowerSw(RadioTower r){
    RadioTowerImp rTower = (RadioTowerImp) r;

    return rTower->sw;
}

int getRadioTowerTreeX(RadioTower r){
    RadioTowerImp rTower = (RadioTowerImp) r;

    return rTower->treeX;
}

int getRadioTowerTreeY(RadioTower r){
    RadioTowerImp rTower = (RadioTowerImp) r;

    return rTower->treeY;
}

void setRadioTowerX(RadioTower r, double x){
    RadioTowerImp rTower = (RadioTowerImp) r;

    rTower->x = x;
}

void setRadioTowerY(RadioTower r, double y){
    RadioTowerImp rTower = (RadioTowerImp) r;

    rTower->y = y;
}

void setRadioTowerTreeXY(RadioTower r, int x, int y){
    RadioTowerImp rTower = (RadioTowerImp) r;

    rTower->treeX = x;
    rTower->treeY = y;
}

void destroyRadioTower(RadioTower r){
    RadioTowerImp rTower = (RadioTowerImp) r;

    free(rTower);
}