#include "hydrant.h"

typedef struct stHydrant{
    char id[32], strokeColor[24], fillColor[24], sw[12];
    double x, y;
}*HydrantImp;

Hydrant createHydrant(char id[], double x, double y, char strokeColor[], char fillColor[], char sw[]){
    HydrantImp hydrant = (HydrantImp) malloc(sizeof(struct stHydrant));

    strcpy(hydrant->id, id);
    hydrant->x = x;
    hydrant->y = y;
    strcpy(hydrant->strokeColor, strokeColor);
    strcpy(hydrant->fillColor, fillColor);
    strcpy(hydrant->sw, sw);

    return hydrant;
}

int comparatorHydrant(Hydrant h1, Hydrant h2){
    HydrantImp hydrant1 = (HydrantImp) h1;
    HydrantImp hydrant2 = (HydrantImp) h2;

    return strcmp(hydrant1->id, hydrant2->id);
}

char *getHydrantId(Hydrant h){
    HydrantImp hydrant = (HydrantImp) h;

    return hydrant->id;
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

void setHydrantX(Hydrant h, double x){
    HydrantImp hydrant = (HydrantImp) h;

    hydrant->x = x;
}

void setHydrantY(Hydrant h, double y){
    HydrantImp hydrant = (HydrantImp) h;

    hydrant->y = y;
}

void freeHydrant(Hydrant h){
    HydrantImp hydrant = (HydrantImp) h;

    free(hydrant);
}