#include "hydrant.h"

typedef struct stHydrant{
    char id[32], strokeCollor[24], fillCollor[24], sw[12];
    double x, y;
}*HydrantImp;

Hydrant criarHydrant(char id[], double x, double y, char strokeCollor[], char fillCollor[], char sw[]){
    HydrantImp hydrant = (HydrantImp) malloc(sizeof(struct stHydrant));

    strcpy(hydrant->id, id);
    hydrant->x = x;
    hydrant->y = y;
    strcpy(hydrant->strokeCollor, strokeCollor);
    strcpy(hydrant->fillCollor, fillCollor);
    strcpy(hydrant->sw, sw);

    return hydrant;
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

char *getHydrantStrokeCollor(Hydrant h){
    HydrantImp hydrant = (HydrantImp) h;

    return hydrant->strokeCollor;
}

char *getHydrantFillCollor(Hydrant h){
    HydrantImp hydrant = (HydrantImp) h;

    return hydrant->fillCollor;
}

char *getHydrantSw(Hydrant h){
    HydrantImp hydrant = (HydrantImp) h;

    return hydrant->sw;
}