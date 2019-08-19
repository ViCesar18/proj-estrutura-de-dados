#include "operations.h"

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