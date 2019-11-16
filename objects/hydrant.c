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

char *getHydrantInformation(Hydrant h, char *info){
    HydrantImp hydrant = (HydrantImp) h;
    sprintf(info, "%s\n(%.2lf, %.2lf)", hydrant->id, hydrant->x, hydrant->y);

    return info;
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

void destroyHydrant(Hydrant h){
    HydrantImp hydrant = (HydrantImp) h;

    free(hydrant);
}