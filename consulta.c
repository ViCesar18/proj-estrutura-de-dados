#include <stdio.h>
#include <math.h>
#include "structs.h"

double distEuclid(double x1, double y1, double x2, double y2){
    double dist;

    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

void verificarO(FILE *txt, Formas figura1, Formas figura2){
    double a;

    if(figura1.f == 'c' && figura2.f == 'c'){
        if(figura1.rC + figura2.rC >= distEuclid(figura1.xC, figura1.yC, figura2.xC, figura2.yC)){
            fprintf(txt, "o? %d %d\nSIM", figura1.idC, figura2.idC);
            desenha
        }
        else{
            fprintf(txt, "o? %d %d\nNAO", figura1.idC, figura2.idC);
        }
    }
}