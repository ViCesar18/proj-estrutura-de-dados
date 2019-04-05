#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "outSVG.h"
#include "consulta.h"
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

void verificarO(FILE *txt, FILE *svg2, Formas figura1, Formas figura2){
    double a, xProx, yProx;
    bool colisao;
    Formas aux;

    if(figura1.f == 'c' && figura2.f == 'c'){
        if(figura1.rC + figura2.rC >= distEuclid(figura1.xC, figura1.yC, figura2.xC, figura2.yC)){
            fprintf(txt, "o? %d %d\nSIM\n\n", figura1.id, figura2.id);
            colisao = true;
        }
        else{
            fprintf(txt, "o? %d %d\nNAO\n\n", figura1.id, figura2.id);
            colisao = false;
        }
        retanguloEnvolveCirculo(svg2, figura1, figura2, colisao);
    }
    else if(figura1.f == 'r' && figura2.f == 'r'){
        if(figura1.xR <=figura2.xR + figura2.wR && figura1.yR <= figura2.yR + figura2.hR
        && figura1.xR + figura1.wR >= figura2.xR && figura1.yR + figura1.hR >= figura2.yR){
            fprintf(txt, "o? %d %d\nSIM\n\n", figura1.id, figura2.id);
            colisao = true;
        }
        else{
            fprintf(txt, "o? %d %d\nNAO\n\n", figura1.id, figura2.id);
            colisao = false;
        }
        retanguloEnvolveRetangulo(svg2, figura1, figura2, colisao);
    }
    else if(figura1.f == 'c' && figura2.f == 'r' || figura1.f == 'r' && figura2.f == 'c'){
        if(figura1.f == 'r' && figura2.f == 'c'){
            aux = figura1;
            figura1 = figura2;
            figura2 = aux;
            aux.id = figura1.id;
            figura1.id = figura2.id;
            figura2.id = aux.id;
        }

        xProx = clamp(figura1.xC, figura2.xR, figura2.xR + figura2.wR);
        yProx = clamp(figura1.yC, figura2.yR, figura2.yR + figura2.hR);

        if(distEuclid(figura1.xC, figura1.yC, xProx, yProx) <= figura1.rC){
            fprintf(txt, "o? %d %d\nSIM\n\n", figura1.id, figura2.id);
            colisao = true;
        }
        else{
            fprintf(txt, "o? %d %d\nNAO\n\n", figura1.id, figura2.id);
            colisao = false;
        }
        retanguloEnvolveCR(svg2, figura1, figura2, colisao);
    }
}

void verificarI(FILE *txt, FILE *svg2, Formas figura, double x, double y){
    Formas ponto;

    ponto.xC = x;
    ponto.yC = y;
    ponto.rC = 3;

    if(figura.f == 'c'){
        if(figura.xC + figura.rC >= x && figura.yC + figura.rC >= y && figura.xC - figura.rC <= x
        && figura.yC - figura.rC <= y){
            fprintf(txt, "i? %d %lf %lf\nINTERNO\n\n", figura.id, x, y);
            strcpy(ponto.strokeCollorC, "green");
            strcpy(ponto.fillCollorC, "green");
        }
        else{
            fprintf(txt, "i? %d %lf %lf\nNAO INTERNO\n\n", figura.id, x, y);
            strcpy(ponto.strokeCollorC, "red");
            strcpy(ponto.fillCollorC, "red");
        }
        printarCirculo(svg2, ponto);
        printarLinha(svg2, figura.xC, figura.yC, ponto.xC, ponto.yC, "black");
    }
    else{
        if(x >= figura.xR && y >= figura.yR && x <= figura.xR + figura.wR && y <= figura.yR + figura.hR){
            fprintf(txt, "i? %d %lf %lf\nINTERNO\n\n", figura.id, x, y);
            strcpy(ponto.strokeCollorC, "green");
            strcpy(ponto.fillCollorC, "green");
        }
        else{
            fprintf(txt, "i? %d %lf %lf\nNAO INTERNO\n\n", figura.id, x, y);
            strcpy(ponto.strokeCollorC, "red");
            strcpy(ponto.fillCollorC, "red");
        }
        printarCirculo(svg2, ponto);
        printarLinha(svg2, figura.xR + figura.wR / 2, figura.yR + figura.hR / 2, ponto.xC, ponto.yC, "black");
    }
}

void verificarD(FILE *txt, FILE *svg2, Formas figura1, Formas figura2){
    double dist;
    char dist2[10];
    double xL, yL;

    if(figura1.f == 'c' && figura2.f == 'c'){
        dist = distEuclid(figura1.xC, figura1.yC, figura2.xC, figura2.yC);
        printarLinha(svg2, figura1.xC, figura1.yC, figura2.xC, figura2.yC, "black");
        xL = (figura1.xC + figura2.xC) / 2;
        yL = (figura1.yC + figura2.yC) / 2;
    }
    else if(figura1.f == 'r' && figura2.f == 'r'){
        dist = distEuclid(figura1.xR + figura1.wR / 2, figura1.yR + figura1.hR / 2, 
        figura2.xR + figura2.wR / 2, figura2.yR + figura2.hR / 2);
        printarLinha(svg2, figura1.xR + figura1.wR / 2, figura1.yR + figura1.hR / 2, figura2.xR + figura2.wR / 2, figura2.yR + figura2.hR / 2, "black");
        xL = (figura1.xR + figura1.wR / 2 + figura2.xR + figura2.wR / 2) / 2;
        yL = (figura1.yR + figura1.hR / 2 + figura2.yR + figura2.hR / 2) / 2;
    }
    else if(figura1.f == 'r' && figura2.f == 'c'){
        dist = distEuclid(figura1.xR + figura1.wR / 2, figura1.yR + figura1.hR / 2, figura2.xC, figura2.yC);
        printarLinha(svg2, figura1.xR + figura1.wR / 2, figura1.yR + figura1.hR / 2, figura2.xC, figura2.yC, "black");
        xL = (figura1.xR + figura1.wR / 2 + figura2.xC) / 2;
        yL = (figura1.yR + figura1.hR / 2 + figura2.yC) / 2;
    }
    else{
        dist = distEuclid(figura1.xC, figura1.yC, figura2.xR + figura2.wR / 2, figura2.yR + figura2.hR / 2);
        printarLinha(svg2, figura1.xC, figura1.yC, figura2.xR + figura2.wR / 2, figura2.yR + figura2.hR / 2, "black");
        xL = (figura1.xC + figura2.xR + figura2.wR / 2) / 2;
        yL = (figura1.yC + figura2.yR + figura2.hR / 2) / 2;
    }

    fprintf(txt, "d? %d %d\n%lf\n\n", figura1.id, figura2.id, dist);
    sprintf(dist2, "%lf", dist);
    printarTexto(svg2, xL, yL, dist2);
}

void verificarBB(int nx, FILE *svg3, Formas figuras[], char cor[]){
    int i = 0;
    Formas quadrado;
    double xC, yC, rX, rY;

    fprintf(svg3, "<svg>\n");
    while(i <= nx){

        if(figuras[i].f == 'c'){
            printarCirculo(svg3, figuras[i]);
            quadrado.xR = figuras[i].xC - figuras[i].rC;
            quadrado.yR = figuras[i].yC - figuras[i].rC;
            quadrado.wR = 2 * figuras[i].rC;
            quadrado.hR = 2 * figuras[i].rC;
            strcpy(quadrado.strokeCollorR, cor);
            strcpy(quadrado.fillCollorR, "none");
            quadrado.tracoR = 0;
            printarRetangulo(svg3, quadrado);
        }
        else if(figuras[i].f == 'r'){
            printarRetangulo(svg3, figuras[i]);
            xC = figuras[i].xR + figuras[i].wR / 2;
            yC = figuras[i].yR + figuras[i].hR / 2;
            rX = figuras[i].wR / 2;
            rY = figuras[i].hR / 2;
            printarElipse(svg3, xC, yC, rX, rY, cor);
        }
        i++;
    }
    fprintf(svg3, "\n</svg>");
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