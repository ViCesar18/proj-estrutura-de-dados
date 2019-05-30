#include "consulta.h"

double distEuclid(double x1, double y1, double x2, double y2){

    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

double ManhattanDist(double x1, double y1, double x2, double y2){

    return fabs(x1 - x2) + fabs(y1 - y2);
}

double clamp(double pComp, double pMin, double pMax){

    if(pComp > pMax)
        return pMax;
    else if(pComp < pMin)
        return pMin;
    else
        return pComp;
}

void verificarO(FILE *txt, FILE *svg2, Form figura1, Form figura2, char type1[], char type2[]){
    double a, xProx, yProx;
    bool colisao;

    char id1[32], id2[32];

    strcpy(id1, getFormId(figura1));
    strcpy(id2, getFormId(figura2));
    double r1 = getFormR(figura1);
    double r2 = getFormR(figura2);
    double x1 = getFormX(figura1);
    double x2 = getFormX(figura2);
    double y1 = getFormY(figura1);
    double y2 = getFormY(figura2);
    double w1 = getFormW(figura1);
    double w2 = getFormW(figura2);
    double h1 = getFormH(figura1);
    double h2 = getFormH(figura2);

    if(!strcmp(type1, "c") && !strcmp(type2, "c")){
        if(r1 + r2 >= distEuclid(x1, y1, x2, y2)){
            fprintf(txt, "o? %s %s\nSIM\n\n", id1, id2);
            colisao = true;
        }
        else{
            fprintf(txt, "o? %s %s\nNAO\n\n", id1, id2);
            colisao = false;
        }
        retanguloEnvolveCirculo(svg2, figura1, figura2, colisao);
    }
    else if(!strcmp(type1, "r") && !strcmp(type2, "r")){
        if(x1 <= x2 + w2 && y1 <= y2 + h2 && x1 + w1 >= x2 && y1 + h1 >= y2){
            fprintf(txt, "o? %s %s\nSIM\n\n", id1, id2);
            colisao = true;
        }
        else{
            fprintf(txt, "o? %s %s\nNAO\n\n", id1, id2);
            colisao = false;
        }
        retanguloEnvolveRetangulo(svg2, figura1, figura2, colisao);
    }
    else if(!strcmp(type1, "c") && !strcmp(type2, "r") || !strcmp(type1, "r") && !strcmp(type2, "c")){
        if(!strcmp(type1, "r") && !strcmp(type2, "c")){
            double auxX = x1;
            x1 = x2;
            x2 = auxX;
            double auxY = y1;
            y1 = y2;
            y2 = auxY;
            double auxW = w1;
            w1 = w2;
            w2 = auxW;
            double auxH = h1;
            h1 = h2;
            h2 = auxH;
            double auxR = r1;
            r1 = r2;
            r2 = auxR;
        }

        xProx = clamp(x1, x2, x2 + w2);
        yProx = clamp(y1, y2, y2 + h2);

        if(distEuclid(x1, y1, xProx, yProx) <= r1){
            fprintf(txt, "o? %s %s\nSIM\n\n", id1, id2);
            colisao = true;
        }
        else{
            fprintf(txt, "o? %s %s\nNAO\n\n", id1, id2);
            colisao = false;
        }
        retanguloEnvolveCR(svg2, figura1, figura2, colisao);
    }
}

bool pontoInsideFigura(double x, double y, Elemento elemento, char type[], char met[]){
    if(!strcmp(type, "c")){
        if(!strcmp(met, "L2")){
            if(distEuclid(getFormX(elemento), getFormY(elemento), x, y) <= getFormR(elemento))
                return true;
            else
                return false;
        }
        else if(!strcmp(met, "L1")){
            if(ManhattanDist(getFormX(elemento), getFormY(elemento), x, y) <= getFormR(elemento))
                return true;
            else
                return false;
        }
    }
    else if(!strcmp(type, "r")){
        if(x >= getFormX(elemento) && y >= getFormY(elemento) && x <= getFormX(elemento) + getFormW(elemento) && y <= getFormY(elemento) + getFormH(elemento))
            return true;
        else
            return false;
    }
    else if(!strcmp(type, "q")){
        if(x >= getBlockX(elemento) && y >= getBlockY(elemento) && x <= getBlockX(elemento) + getBlockW(elemento) && y <= getBlockY(elemento) + getBlockH(elemento))
            return true;
        else
            return false;
    }
}

void verificarI(FILE *txt, FILE *svg2, Form figura, double x, double y, char typeF[]){
    double xP = x;
    double yP = y;
    double rP = 3;
    char strokeCollorP[24], fillCollorP[24], idF[32];

    strcpy(idF, getFormId(figura));
    double xF = getFormX(figura);
    double yF = getFormY(figura);
    double rF = getFormR(figura);
    double wF = getFormW(figura);
    double hF = getFormH(figura);

    if(!strcmp(typeF, "c")){
        if(pontoInsideFigura(x, y, figura, "c", "L2")){
            fprintf(txt, "i? %s %lf %lf\nINTERNO\n\n", idF, x, y);
            strcpy(strokeCollorP, "green");
            strcpy(fillCollorP, "green");
        }
        else{
            fprintf(txt, "i? %s %lf %lf\nNAO INTERNO\n\n", idF, x, y);
            strcpy(strokeCollorP, "red");
            strcpy(fillCollorP, "red");
        }
        Form ponto = criarCirculo("0", xP, yP, rP, strokeCollorP, fillCollorP, "1");
        printarCirculo(svg2, ponto);
        printarLinha(svg2, xF, yF, xP, yP, "black");
        free(ponto);
    }
    else{
        if(pontoInsideFigura(x, y, figura, "r", "L2")){
            fprintf(txt, "i? %s %lf %lf\nINTERNO\n\n", idF, x, y);
            strcpy(strokeCollorP, "green");
            strcpy(fillCollorP, "green");
        }
        else{
            fprintf(txt, "i? %s %lf %lf\nNAO INTERNO\n\n", idF, x, y);
            strcpy(strokeCollorP, "red");
            strcpy(fillCollorP, "red");
        }

        Form ponto = criarCirculo("0", xP, yP, rP, strokeCollorP, fillCollorP, "1");
        printarCirculo(svg2, ponto);
        printarLinha(svg2, xF + wF / 2, yF + hF / 2, xP, yP, "black");
        free(ponto);
    }
}

void verificarD(FILE *txt, FILE *svg2, Form figura1, Form figura2, char type1[], char type2[]){
    double dist;
    char distText[32], id1[32], id2[32];
    double xL, yL;

    strcpy(id1, getFormId(figura1));
    strcpy(id2, getFormId(figura2));
    double x1 = getFormX(figura1);
    double x2 = getFormX(figura2);
    double y1 = getFormY(figura1);
    double y2 = getFormY(figura2);
    double r1 = getFormR(figura1);
    double r2 = getFormR(figura2);
    double w1 = getFormW(figura1);
    double w2 = getFormW(figura2);
    double h1 = getFormH(figura1);
    double h2 = getFormH(figura2);

    if(!strcmp(type1, "c") && !strcmp(type2, "c")){
        dist = distEuclid(x1, y1, x2, y2);
        printarLinha(svg2, x1, y1, x2, y2, "black");
        xL = (x1 + x2) / 2;
        yL = (y1 + y2) / 2;
    }
    else if(!strcmp(type1, "r") && !strcmp(type2, "r")){
        dist = distEuclid(x1 + w1 / 2, y1 + h1 / 2, x2 + w2 / 2, y2 + h2 / 2);
        printarLinha(svg2, x1 + w1 / 2, y1 + h1 / 2, x2 + w2 / 2, y2 + h2 / 2, "black");
        xL = (x1 + w1 / 2 + x2 + w2 / 2) / 2;
        yL = (y1 + h1 / 2 + y2 + h2 / 2) / 2;
    }
    else if(!strcmp(type1, "r") && !strcmp(type2, "c")){
        dist = distEuclid(x1 + w1 / 2, y1 + h1 / 2, x2, y2);
        printarLinha(svg2, x1 + w1 / 2, y1 + h1 / 2, x2, y2, "black");
        xL = (x1 + w1 / 2 + x2) / 2;
        yL = (y1 + h1 / 2 + y2) / 2;
    }
    else{
        dist = distEuclid(x1, y1, x2 + w2 / 2, y2 + h2 / 2);
        printarLinha(svg2, x1, y1, x2 + w2 / 2, y2 + h2 / 2, "black");
        xL = (x1 + x2 + w2 / 2) / 2;
        yL = (y1 + y2 + h2 / 2) / 2;
    }

    fprintf(txt, "d? %s %s\n%lf\n\n", id1, id2, dist);
    sprintf(distText, "%lf", dist);
    printarTexto(svg2, xL, yL, distText, "black");
}

void verificarBB(int nx, FILE *svg3, Lista figuras, char cor[]){
    int i = 0;
    double xC, yC, rX, rY;

    fprintf(svg3, "<svg>\n");

    imprimirBB(figuras, svg3, cor);

    fprintf(svg3, "\n</svg>");
}

void retanguloEnvolveCirculo(FILE *svg2, Form figura1, Form figura2, bool colisao){
    double xMenor, yMenor, rMenor, xMaior, yMaior, rMaior;

    double x1 = getFormX(figura1);
    double x2 = getFormX(figura2);
    double y1 = getFormY(figura1);
    double y2 = getFormY(figura2);
    double r1 = getFormR(figura1);
    double r2 = getFormR(figura2);

    if(x1 < x2){
        xMenor = x1;
        xMaior = x2;
        rMenor = r1;
        rMaior = r2;
    }
    else{
        xMenor = x2;
        xMaior = x1;
        rMenor = r2;
        rMaior = r1;
    }

    if(y1 < y2){
        yMenor = y1;
        yMaior = y2;
    }
    else{
        yMenor = y2;
        yMaior = y1;
    }

    int strokeR;
    double xR = xMenor - rMenor;
    double yR = yMenor - rMenor;
    double wR = (xMaior + rMaior) - (xMenor - rMenor);
    double hR = (yMaior + rMaior) - (yMenor - rMenor);
    char strokeCollorR[24], fillCollorR[24];

    strcpy(strokeCollorR, "black");
    strcpy(fillCollorR, "none");

    if(colisao)
        strokeR = 0;
    else
        strokeR = 5;

    Form retangulo = criarRect("0", xR, yR, wR, hR, strokeCollorR, fillCollorR, strokeR, "1");

    printarRetangulo(svg2, retangulo);
    free(retangulo);
}

void retanguloEnvolveRetangulo(FILE *svg2, Form figura1, Form figura2, bool colisao){
    double xMenor, yMenor, xMaior, yMaior, hMenor, hMaior, wMenor, wMaior;

    double x1 = getFormX(figura1);
    double x2 = getFormX(figura2);
    double y1 = getFormY(figura1);
    double y2 = getFormY(figura2);
    double w1 = getFormW(figura1);
    double w2 = getFormW(figura2);
    double h1 = getFormH(figura1);
    double h2 = getFormH(figura2);

    if(x1 < x2){
        xMenor = x1;
        xMaior = x2;
        wMenor = w2;
        wMaior = w2;
    }
    else{
        xMenor = x2;
        xMaior = x1;
        wMenor = w2;
        wMaior = w1;
    }
    
    if(y1 < y2){
        yMenor = y1;
        yMaior = y2;
        hMenor = h1;
        hMaior = h2;
    }
    else{
        yMenor = y2;
        yMaior = y1;
        hMenor = h2;
        hMaior = h1;
    }

    int strokeR;
    double xR = xMenor;
    double yR = yMenor;
    double wR = xMaior + wMaior - xMenor;
    double hR = yMaior + hMaior - yMenor;
    char strokeCollorR[24], fillCollorR[24];

    strcpy(strokeCollorR, "black");
    strcpy(fillCollorR, "none");
    if(colisao)
        strokeR = 0;
    else
        strokeR = 5;

    Form retangulo = criarRect("0", xR, yR, wR, hR, strokeCollorR, fillCollorR, strokeR, "1");

    printarRetangulo(svg2, retangulo);
    free(retangulo);
}

void retanguloEnvolveCR(FILE *svg2, Form figura1, Form figura2, bool colisao){
    double xMenor, xMaior, yMenor, yMaior;
    
    double x1 = getFormX(figura1);
    double x2 = getFormX(figura2);
    double y1 = getFormY(figura1);
    double y2 = getFormY(figura2);
    double r1 = getFormR(figura1);
    double w2 = getFormW(figura2);
    double h2 = getFormH(figura2);

    if(x1 - r1 < x2)
        xMenor = x1 - r1;
    else
        xMenor = x2;

    if(x1 + r1 > x2 + w2)
        xMaior = x1 + r1;
    else
        xMaior = x2 + w2;

    if(y1 - r1 < y2)
        yMenor = y1 - r1;
    else
        yMenor = y2;

    if(y1 + r1 > y2 + h2)
        yMaior = y1 + r1;
    else
        yMaior = y2 + h2;
    
    int strokeR;
    double xR = xMenor;
    double yR = yMenor;
    double wR = xMaior - xMenor;
    double hR = yMaior - yMenor;
    char strokeCollorR[24], fillCollorR[24];

    strcpy(strokeCollorR, "black");
    strcpy(fillCollorR, "none");
    if(colisao)
        strokeR = 0;
    else
        strokeR = 5;

    Form retangulo = criarRect("0", xR, yR, wR, hR, strokeCollorR, fillCollorR, strokeR, "1");

    printarRetangulo(svg2, retangulo);
    free(retangulo);
}

bool quadInsideCirc(Block block, Form circulo, char met[]){
    double x = getBlockX(block);
    double y = getBlockY(block);
    double w = getBlockW(block);
    double h = getBlockH(block);

    if(pontoInsideFigura(x, y, circulo, "c", met) && pontoInsideFigura(x + w, y, circulo, "c", met) && 
    pontoInsideFigura(x, y + h, circulo, "c", met) && pontoInsideFigura(x + w, y + h, circulo, "c", met))
        return true;
    else
        return false;
}

bool quadInsideRect(Block block, Form retangulo){
    double x = getBlockX(block);
    double y = getBlockY(block);
    double w = getBlockW(block);
    double h = getBlockH(block);

    if(pontoInsideFigura(x, y, retangulo, "r", "L2") && pontoInsideFigura(x + w, y, retangulo, "r", "L2") && 
    pontoInsideFigura(x, y + h, retangulo, "r", "L2") && pontoInsideFigura(x + w, y + h, retangulo, "r", "L2"))
        return true;
    else
        return false;
}