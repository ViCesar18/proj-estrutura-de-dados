#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "outSVG.h"
#include "structs.h"

double distEuclid(double x1, double y1, double x2, double y2){
    double dist;

    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

double clamp(double pComp, double pMin, double pMax){

    if(pComp > pMax)
        return pMax;
    else if(pComp < pMin)
        return pMin;
    else
        return pComp;
}

void retanguloEnvolveCirculo(FILE *svg2, Formas figura1, Formas figura2, bool colisao){
    double xMenor, yMenor, rMenor, xMaior, yMaior, rMaior;
    Formas retangulo;

    if(figura1.xC < figura2.xC){
        xMenor = figura1.xC;
        xMaior = figura2.xC;
        rMenor = figura1.rC;
        rMaior = figura2.rC;
    }
    else{
        xMenor = figura2.xC;
        xMaior = figura1.xC;
        rMenor = figura2.rC;
        rMaior = figura1.rC;
    }

    if(figura1.yC < figura2.yC){
        yMenor = figura1.yC;
        yMaior = figura2.yC;
    }
    else{
        yMenor = figura2.yC;
        yMaior = figura1.yC;
    }

    retangulo.xR = xMenor - rMenor;
    retangulo.yR = yMenor - rMenor;
    retangulo.wR = (xMaior + rMaior) - (xMenor - rMenor);
    retangulo.hR = (yMaior + rMaior) - (yMenor - rMenor);
    strcpy(retangulo.strokeCollorR, "black");
    strcpy(retangulo.fillCollorR, "none");
    if(colisao)
        retangulo.tracoR = 0;
    else
        retangulo.tracoR = 5;

    printarRetangulo(svg2, retangulo);
}

void retanguloEnvolveRetangulo(FILE *svg2, Formas figura1, Formas figura2, bool colisao){
    double xMenor, yMenor, xMaior, yMaior, hMenor, hMaior, wMenor, wMaior;
    Formas retangulo;

    if(figura1.xR < figura2.xR){
        xMenor = figura1.xR;
        xMaior = figura2.xR;
        wMenor = figura1.wR;
        wMaior = figura2.wR;
    }
    else{
        xMenor = figura2.xR;
        xMaior = figura1.xR;
        wMenor = figura2.wR;
        wMaior = figura1.wR;
    }
    
    if(figura1.yR < figura2.yR){
        yMenor = figura1.yR;
        yMaior = figura2.yR;
        hMenor = figura1.hR;
        hMaior = figura2.hR;
    }
    else{
        yMenor = figura2.yR;
        yMaior = figura1.yR;
        hMenor = figura2.hR;
        hMaior = figura1.hR;
    }

    retangulo.xR = xMenor;
    retangulo.yR = yMenor;
    retangulo.wR = xMaior + wMaior - xMenor;
    retangulo.hR = yMaior + hMaior - yMenor;
    strcpy(retangulo.strokeCollorR, "black");
    strcpy(retangulo.fillCollorR, "none");
    if(colisao)
        retangulo.tracoR = 0;
    else
        retangulo.tracoR = 5;

    printarRetangulo(svg2, retangulo);
}

void retanguloEnvolveCR(FILE *svg2, Formas figura1, Formas figura2, bool colisao){
    double xMenor, xMaior, yMenor, yMaior;
    Formas retangulo;

    if(figura1.xC - figura1.rC < figura2.xR)
        xMenor = figura1.xC -figura1.rC;
    else
        xMenor = figura2.xR;

    if(figura1.xC + figura1.rC > figura2.xR + figura2.wR)
        xMaior = figura1.xC + figura1.rC;
    else
        xMaior = figura2.xR + figura2.wR;

    if(figura1.yC - figura1.rC < figura2.yR)
        yMenor = figura1.yC - figura1.rC;
    else
        yMenor = figura2.yR;

    if(figura1.yC + figura1.rC > figura2.yR + figura2.hR)
        yMaior = figura1.yC + figura1.rC;
    else
        yMaior = figura2.yR + figura2.hR;
    
    retangulo.xR = xMenor;
    retangulo.yR = yMenor;
    retangulo.wR = xMaior - xMenor;
    retangulo.hR = yMaior - yMenor;
    strcpy(retangulo.strokeCollorR, "black");
    strcpy(retangulo.fillCollorR, "none");
    if(colisao)
        retangulo.tracoR = 0;
    else
        retangulo.tracoR = 5;

    printarRetangulo(svg2, retangulo);
}

void verificarO(FILE *txt, FILE *svg2, Formas figura1, Formas figura2){
    double a, xProx, yProx;
    bool colisao;
    Formas aux;

    if(figura1.f == 'c' && figura2.f == 'c'){
        if(figura1.rC + figura2.rC >= distEuclid(figura1.xC, figura1.yC, figura2.xC, figura2.yC)){
            fprintf(txt, "o? %d %d\nSIM\n\n", figura1.idC, figura2.idC);
            colisao = true;
        }
        else{
            fprintf(txt, "o? %d %d\nNAO\n\n", figura1.idC, figura2.idC);
            colisao = false;
        }
        retanguloEnvolveCirculo(svg2, figura1, figura2, colisao);
    }
    else if(figura1.f == 'r' && figura2.f == 'r'){
        if(figura1.xR <=figura2.xR + figura2.wR && figura1.yR <= figura2.yR + figura2.hR
        && figura1.xR + figura1.wR >= figura2.xR && figura1.yR + figura1.hR >= figura2.yR){
            fprintf(txt, "o? %d %d\nSIM\n\n", figura1.idR, figura2.idR);
            colisao = true;
        }
        else{
            fprintf(txt, "o? %d %d\nNAO\n\n", figura1.idR, figura2.idR);
            colisao = false;
        }
        retanguloEnvolveRetangulo(svg2, figura1, figura2, colisao);
    }
    else if(figura1.f == 'c' && figura2.f == 'r' || figura1.f == 'r' && figura2.f == 'c'){
        if(figura1.f == 'r' && figura2.f == 'c'){
            aux = figura1;
            figura1 = figura2;
            figura2 = aux;
            aux.idC = figura1.idC;
            figura1.idC = figura2.idR;
            figura2.idR = aux.idC;
        }

        xProx = clamp(figura1.xC, figura2.xR, figura2.xR + figura2.wR);
        yProx = clamp(figura1.yC, figura2.yR, figura2.yR + figura2.hR);

        if(distEuclid(figura1.xC, figura1.yC, xProx, yProx) <= figura1.rC){
            fprintf(txt, "o? %d %d\nSIM\n\n", figura1.idC, figura2.idR);
            colisao = true;
        }
        else{
            fprintf(txt, "o? %d %d\nNAO\n\n", figura1.idC, figura2.idR);
            colisao = false;
        }
        retanguloEnvolveCR(svg2, figura1, figura2, colisao);
    }
}

void verificarI(FILE *txt, FILE *svg2, Formas figura, double x, double y){
    Formas ponto;

    ponto.xC = x;
    ponto.yC = y;
    ponto.rC = 2;

    if(figura.f == 'c'){
        if(figura.xC + figura.rC >= x && figura.yC + figura.rC >= y && figura.xC - figura.rC <= x
        && figura.yC - figura.rC <= y){
            fprintf(txt, "i? %d %fl %fl\nINTERNO\n\n", figura.idC, x, y);
            strcpy(ponto.strokeCollorC, "green");
            strcpy(ponto.fillCollorC, "green");
            printarCirculo(svg2, ponto);
        }
        else{
            fprintf(txt, "i? %d %fl %fl\nNAO INTERNO\n\n", figura.idC, x, y);
            strcpy(ponto.strokeCollorC, "red");
            strcpy(ponto.fillCollorC, "red");
            printarCirculo(svg2, ponto);
        }
    }
}