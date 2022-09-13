#include "hydrant.h"

typedef struct stHydrant{
    char id[32], strokeColor[24], fillColor[24], sw[12];
    double x, y;
    int treeX, treeY;
}*HydrantImp;

Hydrant createHydrant(char id[], double x, double y, char strokeColor[], char fillColor[], char sw[]){
    HydrantImp hydrant = (HydrantImp) malloc(sizeof(struct stHydrant));

    strcpy(hydrant->id, id);
    hydrant->x = x;
    hydrant->y = y;
    strcpy(hydrant->strokeColor, strokeColor);
    strcpy(hydrant->fillColor, fillColor);
    strcpy(hydrant->sw, sw);

    hydrant->treeX = 0;
    hydrant->treeY = 0;

    return hydrant;
}

int comparatorHydrant(Hydrant h1, Hydrant h2){
    HydrantImp hydrant1 = (HydrantImp) h1;
    HydrantImp hydrant2 = (HydrantImp) h2;

    if(hydrant1->x < hydrant2->x) return -1;
    else if(hydrant1->x > hydrant2->x) return 1;
    else{
        if(hydrant1->y < hydrant2->y) return -1;
        else if(hydrant1->y > hydrant2->y) return 1;
        else return 0;
    }
}

char *getHydrantId(Hydrant h){
    HydrantImp hydrant = (HydrantImp) h;

    return hydrant->id;
}

void getHydrantInformation(Hydrant h, char *info, char *posic){
    HydrantImp hydrant = (HydrantImp) h;
    
    sprintf(info, "%s", hydrant->id);
    sprintf(posic, "(%lf, %lf)", hydrant->x, hydrant->y);
}

double getHydrantX(Hydrant h){
    HydrantImp hydrant = (HydrantImp) h;

    return hydrant->x;
}

double getHydrantY(Hydrant h){
    HydrantImp hydrant = (HydrantImp) h;

    return hydrant->y;
}

char *getHydrantStrokeColor(Hydrant h){
    HydrantImp hydrant = (HydrantImp) h;

    return hydrant->strokeColor;
}

char *getHydrantFillColor(Hydrant h){
    HydrantImp hydrant = (HydrantImp) h;

    return hydrant->fillColor;
}

char *getHydrantSw(Hydrant h){
    HydrantImp hydrant = (HydrantImp) h;

    return hydrant->sw;
}

int getHydrantTreeX(Hydrant h){
    HydrantImp hydrant = (HydrantImp) h;

    return hydrant->treeX;
}

int getHydrantTreeY(Hydrant h){
    HydrantImp hydrant = (HydrantImp) h;

    return hydrant->treeY;
}

void setHydrantX(Hydrant h, double x){
    HydrantImp hydrant = (HydrantImp) h;

    hydrant->x = x;
}

void setHydrantY(Hydrant h, double y){
    HydrantImp hydrant = (HydrantImp) h;

    hydrant->y = y;
}

void setHydrantTreeXY(Hydrant h, int x, int y){
    HydrantImp hydrant = (HydrantImp) h;

    hydrant->x = x;
    hydrant->y = y;
}

void destroyHydrant(Hydrant h){
    HydrantImp hydrant = (HydrantImp) h;

    free(hydrant);
}