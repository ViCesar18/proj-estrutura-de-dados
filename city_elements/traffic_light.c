#include "traffic_light.h"

typedef struct stTrafficLight{
    char id[32], strokeColor[24], fillColor[24], sw[12];
    double x, y;
}*TrafficLightImp;

TrafficLight createTrafficLight(char id[], double x, double y, char strokeColor[], char fillColor[], char sw[]){
    TrafficLightImp tLight = (TrafficLightImp) malloc(sizeof(struct stTrafficLight));

    strcpy(tLight->id, id);
    tLight->x = x;
    tLight->y = y;
    strcpy(tLight->strokeColor, strokeColor);
    strcpy(tLight->fillColor, fillColor);
    strcpy(tLight->sw, sw);

    return tLight;
}

int comparatorTrafficLight(TrafficLight tf1, TrafficLight tf2){
    TrafficLightImp tLight1 = (TrafficLightImp) tf1;
    TrafficLightImp tLight2 = (TrafficLightImp) tf2;

    if(tLight1->x < tLight2->x) return -1;
    else if(tLight1->x > tLight2->x) return 1;
    else{
        if(tLight1->y < tLight2->y) return -1;
        else if(tLight1->y > tLight2->y) return 1;
        else return 0;
    }
}

char *getTrafficLightId(TrafficLight s){
    TrafficLightImp tLight = (TrafficLightImp) s;

    return tLight->id;
}

void getTrafficLightInformation(TrafficLight s, char *info, char *posic){
    TrafficLightImp tLight = (TrafficLightImp) s;

    sprintf(info, "%s", tLight->id);
    sprintf(posic, "(%lf, %lf)", tLight->x, tLight->y);
}

double getTrafficLightX(TrafficLight s){
    TrafficLightImp tLight = (TrafficLightImp) s;

    return tLight->x;
}

double getTrafficLightY(TrafficLight s){
    TrafficLightImp tLight = (TrafficLightImp) s;

    return tLight->y;
}

char *getTrafficLightStrokeColor(TrafficLight s){
    TrafficLightImp tLight = (TrafficLightImp) s;

    return tLight->strokeColor;
}

char *getTrafficLightFillColor(TrafficLight s){
    TrafficLightImp tLight = (TrafficLightImp) s;

    return tLight->fillColor;
}

char *getTrafficLightSw(TrafficLight s){
    TrafficLightImp tLight = (TrafficLightImp) s;

    return tLight->sw;
}

void setTrafficLightX(TrafficLight s, double x){
    TrafficLightImp tLight = (TrafficLightImp) s;

    tLight->x = x;
}

void setTrafficLightY(TrafficLight s, double y){
    TrafficLightImp tLight = (TrafficLightImp) s;

    tLight->y = y;
}

void destroyTrafficLight(TrafficLight s){
    TrafficLightImp tLight = (TrafficLightImp) s;

    free(tLight);
}