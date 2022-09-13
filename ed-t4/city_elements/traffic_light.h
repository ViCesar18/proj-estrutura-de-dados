#ifndef TRAFFIC_LIGHT__H
#define TRAFFIC_LIGHT__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *TrafficLight;

/*TAD dos semaforos*/

/*Coloca os dados de semaforo em uma estrutura e retorna a estrutura*/
TrafficLight createTrafficLight(char id[], double x, double y, char strokeColor[], char fillColor[], char sw[]);

/*Compara os id's dos semaforos tf1 e tf2*/
int comparatorTrafficLight(TrafficLight tf1, TrafficLight tf2);

/*Getters e setters para o semaforo*/
char *getTrafficLightId(TrafficLight s);

void getTrafficLightInformation(TrafficLight s, char *info, char *posic);

double getTrafficLightX(TrafficLight s);

double getTrafficLightY(TrafficLight s);

char *getTrafficLightStrokeColor(TrafficLight s);

char *getTrafficLightFillColor(TrafficLight s);

char *getTrafficLightSw(TrafficLight s);

int getTrafficLightTreeX(TrafficLight s);

int getTrafficLightTreeY(TrafficLight s);

void setTrafficLightX(TrafficLight s, double x);

void setTrafficLightY(TrafficLight s, double y);

void setTrafficLightTreeXY(TrafficLight s, int x, int y);
/*Fim getters e setters*/

/*Libera memoria de um semaforo*/
void destroyTrafficLight(TrafficLight s);

#endif