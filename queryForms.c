#include "queryForms.h"

void treatO(FILE *arqTxt, FILE *arqSvgQ, Form figure1, Form figure2){
    double a, xProx, yProx;
    bool collision;

    char id1[32], id2[32];
    
    strcpy(id1, getFormId(figure1));
    strcpy(id2, getFormId(figure2));
    double r1 = getFormR(figure1);
    double r2 = getFormR(figure2);
    double x1 = getFormX(figure1);
    double x2 = getFormX(figure2);
    double y1 = getFormY(figure1);
    double y2 = getFormY(figure2);
    double w1 = getFormW(figure1);
    double w2 = getFormW(figure2);
    double h1 = getFormH(figure1);
    double h2 = getFormH(figure2);
    
    char *type1 = getFormType(figure1);
    char *type2 = getFormType(figure2);
    
    if(!strcmp(type1, "c") && !strcmp(type2, "c")){
        if(r1 + r2 >= distEuclid(x1, y1, x2, y2)){
            fprintf(arqTxt, "o? %s %s\nSIM\n\n", id1, id2);
            collision = true;
        }
        else{
            fprintf(arqTxt, "o? %s %s\nNAO\n\n", id1, id2);
            collision = false;
        }
        rectSurroundsCircles(arqSvgQ, figure1, figure2, collision);
    }
    else if(!strcmp(type1, "r") && !strcmp(type2, "r")){
        if(x1 <= x2 + w2 && y1 <= y2 + h2 && x1 + w1 >= x2 && y1 + h1 >= y2){
            fprintf(arqTxt, "o? %s %s\nSIM\n\n", id1, id2);
            collision = true;
        }
        else{
            fprintf(arqTxt, "o? %s %s\nNAO\n\n", id1, id2);
            collision = false;
        }
        rectSurroundsRects(arqSvgQ, figure1, figure2, collision);
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
            fprintf(arqTxt, "o? %s %s\nSIM\n\n", id1, id2);
            collision = true;
        }
        else{
            fprintf(arqTxt, "o? %s %s\nNAO\n\n", id1, id2);
            collision = false;
        }
        rectSurroundsCircleAndRect(arqSvgQ, figure1, figure2, collision);
    }
}

void treatI(FILE *arqTxt, FILE *arqSvgQ, Form figure, double x, double y){
    double xP = x;
    double yP = y;
    double rP = 3;
    char strokeColorP[24], fillColorP[24], idF[32];

    strcpy(idF, getFormId(figure));
    double xF = getFormX(figure);
    double yF = getFormY(figure);
    double rF = getFormR(figure);
    double wF = getFormW(figure);
    double hF = getFormH(figure);
    char *type = getFormType(figure);

    if(!strcmp(type, "c")){
        if(pointInsideFigure(x, y, figure, "c", "L2")){
            fprintf(arqTxt, "i? %s %lf %lf\nINTERNO\n\n", idF, x, y);
            strcpy(strokeColorP, "green");
            strcpy(fillColorP, "green");
        }
        else{
            fprintf(arqTxt, "i? %s %lf %lf\nNAO INTERNO\n\n", idF, x, y);
            strcpy(strokeColorP, "red");
            strcpy(fillColorP, "red");
        }
        Form ponto = createCircle("0", xP, yP, rP, strokeColorP, fillColorP, "1");
        printCircle(arqSvgQ, ponto);
        printLine(arqSvgQ, xF, yF, xP, yP, "black");
        free(ponto);
    }
    else{
        if(pointInsideFigure(x, y, figure, "r", "L2")){
            fprintf(arqTxt, "i? %s %lf %lf\nINTERNO\n\n", idF, x, y);
            strcpy(strokeColorP, "green");
            strcpy(fillColorP, "green");
        }
        else{
            fprintf(arqTxt, "i? %s %lf %lf\nNAO INTERNO\n\n", idF, x, y);
            strcpy(strokeColorP, "red");
            strcpy(fillColorP, "red");
        }

        Form ponto = createCircle("0", xP, yP, rP, strokeColorP, fillColorP, "1");
        printCircle(arqSvgQ, ponto);
        printLine(arqSvgQ, xF + wF / 2, yF + hF / 2, xP, yP, "black");
        free(ponto);
    }
}

void treatD(FILE *arqTxt, FILE *arqSvgQ, Form figure1, Form figure2){
    double dist;
    char distText[32], id1[32], id2[32];
    double xL, yL;

    strcpy(id1, getFormId(figure1));
    strcpy(id2, getFormId(figure2));
    double x1 = getFormX(figure1);
    double x2 = getFormX(figure2);
    double y1 = getFormY(figure1);
    double y2 = getFormY(figure2);
    double r1 = getFormR(figure1);
    double r2 = getFormR(figure2);
    double w1 = getFormW(figure1);
    double w2 = getFormW(figure2);
    double h1 = getFormH(figure1);
    double h2 = getFormH(figure2);
    char *type1 = getFormType(figure1);
    char *type2 = getFormType(figure2);

    if(!strcmp(type1, "c") && !strcmp(type2, "c")){
        dist = distEuclid(x1, y1, x2, y2);
        printLine(arqSvgQ, x1, y1, x2, y2, "black");
        xL = (x1 + x2) / 2;
        yL = (y1 + y2) / 2;
    }
    else if(!strcmp(type1, "r") && !strcmp(type2, "r")){
        dist = distEuclid(x1 + w1 / 2, y1 + h1 / 2, x2 + w2 / 2, y2 + h2 / 2);
        printLine(arqSvgQ, x1 + w1 / 2, y1 + h1 / 2, x2 + w2 / 2, y2 + h2 / 2, "black");
        xL = (x1 + w1 / 2 + x2 + w2 / 2) / 2;
        yL = (y1 + h1 / 2 + y2 + h2 / 2) / 2;
    }
    else if(!strcmp(type1, "r") && !strcmp(type2, "c")){
        dist = distEuclid(x1 + w1 / 2, y1 + h1 / 2, x2, y2);
        printLine(arqSvgQ, x1 + w1 / 2, y1 + h1 / 2, x2, y2, "black");
        xL = (x1 + w1 / 2 + x2) / 2;
        yL = (y1 + h1 / 2 + y2) / 2;
    }
    else{
        dist = distEuclid(x1, y1, x2 + w2 / 2, y2 + h2 / 2);
        printLine(arqSvgQ, x1, y1, x2 + w2 / 2, y2 + h2 / 2, "black");
        xL = (x1 + x2 + w2 / 2) / 2;
        yL = (y1 + y2 + h2 / 2) / 2;
    }

    fprintf(arqTxt, "d? %s %s\n%lf\n\n", id1, id2, dist);
    sprintf(distText, "%lf", dist);
    printText(arqSvgQ, xL, yL, distText, "black");
}

void treatBB(FILE *arqSvgBB, Tree figures, char color[]){
    int i = 0;
    double xC, yC, rX, rY;

    fprintf(arqSvgBB, "<svg>\n");

    printBB(figures, getTreeRoot(figures), arqSvgBB, color);

    fprintf(arqSvgBB, "\n</svg>");
}