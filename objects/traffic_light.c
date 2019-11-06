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

    return strcmp(tLight1->id, tLight2->id);
}

char *getTrafficLightId(TrafficLight s){
    TrafficLightImp tLight = (TrafficLightImp) s;

    return tLight->id;
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

void freeTrafficLight(TrafficLight s){
    TrafficLightImp tLight = (TrafficLightImp) s;

    free(tLight);
}