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

void treatO(FILE *arqTxt, FILE *arqSvgQ, Form figure1, Form figure2, char type1[], char type2[]){
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

    if(!strcmp(type1, "c") && !strcmp(type2, "c")){
        if(r1 + r2 >= distEuclid(x1, y1, x2, y2)){
            fprintf(arqTxt, "o? %s %s\nSIM\n\n", id1, id2);
            collision = true;
        }
        else{
            fprintf(arqTxt, "o? %s %s\nNAO\n\n", id1, id2);
            collision = false;
        }
        rectSurroundsCircle(arqSvgQ, figure1, figure2, collision);
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
        rectSurroundsRect(arqSvgQ, figure1, figure2, collision);
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

bool pointInsideFigure(double x, double y, Element element, char type[], char met[]){
    if(!strcmp(type, "c")){
        if(!strcmp(met, "L2")){
            if(distEuclid(getFormX(element), getFormY(element), x, y) <= getFormR(element))
                return true;
            else
                return false;
        }
        else if(!strcmp(met, "L1")){
            if(ManhattanDist(getFormX(element), getFormY(element), x, y) <= getFormR(element))
                return true;
            else
                return false;
        }
    }
    else if(!strcmp(type, "r")){
        if(x >= getFormX(element) && y >= getFormY(element) && x <= getFormX(element) + getFormW(element) && y <= getFormY(element) + getFormH(element))
            return true;
        else
            return false;
    }
    else if(!strcmp(type, "q")){
        if(x >= getBlockX(element) && y >= getBlockY(element) && x <= getBlockX(element) + getBlockW(element) && y <= getBlockY(element) + getBlockH(element))
            return true;
        else
            return false;
    }
}

void treatI(FILE *arqTxt, FILE *arqSvgQ, Form figure, double x, double y, char type[]){
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

void treatD(FILE *arqTxt, FILE *arqSvgQ, Form figure1, Form figure2, char type1[], char type2[]){
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

void treatBB(FILE *arqSvgBB, List figures, char color[]){
    int i = 0;
    double xC, yC, rX, rY;

    fprintf(arqSvgBB, "<svg>\n");

    printBB(figures, arqSvgBB, color);

    fprintf(arqSvgBB, "\n</svg>");
}

void rectSurroundsCircles(FILE *arqSvgQ, Form figure1, Form figure2, bool collision){
    double xSmaller, ySmaller, rSmaller, xBigger, yBigger, rBigger;

    double x1 = getFormX(figure1);
    double x2 = getFormX(figure2);
    double y1 = getFormY(figure1);
    double y2 = getFormY(figure2);
    double r1 = getFormR(figure1);
    double r2 = getFormR(figure2);

    if(x1 < x2){
        xSmaller = x1;
        xBigger = x2;
        rSmaller = r1;
        rBigger = r2;
    }
    else{
        xSmaller = x2;
        xBigger = x1;
        rSmaller = r2;
        rBigger = r1;
    }

    if(y1 < y2){
        ySmaller = y1;
        yBigger = y2;
    }
    else{
        ySmaller = y2;
        yBigger = y1;
    }

    int strokeR;
    double xR = xSmaller - rSmaller;
    double yR = ySmaller - rSmaller;
    double wR = (xBigger + rBigger) - (xSmaller - rSmaller);
    double hR = (yBigger + rBigger) - (ySmaller - rSmaller);
    char strokeColorR[24], fillColorR[24];

    strcpy(strokeColorR, "black");
    strcpy(fillColorR, "none");

    if(collision)
        strokeR = 0;
    else
        strokeR = 5;

    Form rect = createRect("0", xR, yR, wR, hR, strokeColorR, fillColorR, strokeR, "1");

    printRect(arqSvgQ, rect);
    free(rect);
}

void rectSurroundsRects(FILE *arqSvgQ, Form figure1, Form figure2, bool collision){
    double xSmaller, ySmaller, xBigger, yBigger, hMenor, hMaior, wMenor, wMaior;

    double x1 = getFormX(figure1);
    double x2 = getFormX(figure2);
    double y1 = getFormY(figure1);
    double y2 = getFormY(figure2);
    double w1 = getFormW(figure1);
    double w2 = getFormW(figure2);
    double h1 = getFormH(figure1);
    double h2 = getFormH(figure2);

    if(x1 < x2){
        xSmaller = x1;
        xBigger = x2;
        wMenor = w2;
        wMaior = w2;
    }
    else{
        xSmaller = x2;
        xBigger = x1;
        wMenor = w2;
        wMaior = w1;
    }
    
    if(y1 < y2){
        ySmaller = y1;
        yBigger = y2;
        hMenor = h1;
        hMaior = h2;
    }
    else{
        ySmaller = y2;
        yBigger = y1;
        hMenor = h2;
        hMaior = h1;
    }

    int strokeR;
    double xR = xSmaller;
    double yR = ySmaller;
    double wR = xBigger + wMaior - xSmaller;
    double hR = yBigger + hMaior - ySmaller;
    char strokeColorR[24], fillColorR[24];

    strcpy(strokeColorR, "black");
    strcpy(fillColorR, "none");
    if(collision)
        strokeR = 0;
    else
        strokeR = 5;

    Form rect = createRect("0", xR, yR, wR, hR, strokeColorR, fillColorR, strokeR, "1");

    printRect(arqSvgQ, rect);
    free(rect);
}

void rectSurroundsCircleAndRect(FILE *arqSvgQ, Form figure1, Form figure2, bool collision){
    double xSmaller, xBigger, ySmaller, yBigger;
    
    double x1 = getFormX(figure1);
    double x2 = getFormX(figure2);
    double y1 = getFormY(figure1);
    double y2 = getFormY(figure2);
    double r1 = getFormR(figure1);
    double w2 = getFormW(figure2);
    double h2 = getFormH(figure2);

    if(x1 - r1 < x2)
        xSmaller = x1 - r1;
    else
        xSmaller = x2;

    if(x1 + r1 > x2 + w2)
        xBigger = x1 + r1;
    else
        xBigger = x2 + w2;

    if(y1 - r1 < y2)
        ySmaller = y1 - r1;
    else
        ySmaller = y2;

    if(y1 + r1 > y2 + h2)
        yBigger = y1 + r1;
    else
        yBigger = y2 + h2;
    
    int strokeR;
    double xR = xSmaller;
    double yR = ySmaller;
    double wR = xBigger - xSmaller;
    double hR = yBigger - ySmaller;
    char strokeColorR[24], fillColorR[24];

    strcpy(strokeColorR, "black");
    strcpy(fillColorR, "none");
    if(collision)
        strokeR = 0;
    else
        strokeR = 5;

    Form rect = createRect("0", xR, yR, wR, hR, strokeColorR, fillColorR, strokeR, "1");

    printRect(arqSvgQ, rect);
    free(rect);
}

bool quadInsideCirc(Block block, Form circle, char met[]){
    double x = getBlockX(block);
    double y = getBlockY(block);
    double w = getBlockW(block);
    double h = getBlockH(block);

    if(pointInsideFigure(x, y, circle, "c", met) && pointInsideFigure(x + w, y, circle, "c", met) && 
    pointInsideFigure(x, y + h, circle, "c", met) && pointInsideFigure(x + w, y + h, circle, "c", met))
        return true;
    else
        return false;
}

bool quadInsideRect(Block block, Form rect){
    double x = getBlockX(block);
    double y = getBlockY(block);
    double w = getBlockW(block);
    double h = getBlockH(block);

    if(pointInsideFigure(x, y, rect, "r", "L2") && pointInsideFigure(x + w, y, rect, "r", "L2") && 
    pointInsideFigure(x, y + h, rect, "r", "L2") && pointInsideFigure(x + w, y + h, rect, "r", "L2"))
        return true;
    else
        return false;
}