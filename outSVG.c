#include "outSVG.h"

void createOutputFileName(char **nameOut, char nameIn[]){
    int i = 0;

    *nameOut = (char *)malloc((strlen(nameIn) + 1) * sizeof(char));

    while(nameIn[i] != '.'){
        (*nameOut)[i] = nameIn[i];
        i++;
    }
}

void createOutputQryFileName(char **nameOut, char nameIn[], char nameQuery[]){
    int i = 0, j = 0;

    *nameOut = (char *)malloc((strlen(nameIn) + strlen(nameQuery)) * sizeof(char));
    while(nameIn[i] != '.'){
        (*nameOut)[i] = nameIn[i];
        i++;
        j++;
    }
    strcat(*nameOut, "-");
    i = 0;
    j++;
    while(nameQuery[i] != '.'){
        (*nameOut)[j] = nameQuery[i];
        i++;
        j++;
    }
}

void createOutputBBFileName(char **nameOut, char nameIn[], char nameQuery[], char suffix[]){
    int i = 0, j = 0;

    *nameOut = (char *)malloc((strlen(nameIn) + strlen(nameQuery) + strlen(suffix)) * sizeof(char));
    while(nameIn[i] != '.'){
        (*nameOut)[i] = nameIn[i];
        i++;
        j++;
    }
    strcat(*nameOut, "-");
    i = 0;
    j++;
    while(nameQuery[i] != '.'){
        (*nameOut)[j] = nameQuery[i];
        i++;
        j++;
    }
    strcat(*nameOut, "-");
    i = 0;
    j++;
    while(suffix[i] != '\0'){
        (*nameOut)[j] = suffix[i];
        i++;
        j++;
    }
}

/*Printa as informacoes de circulo armazenadas no vetor de struct e formatadas para SVG no arquivo SVG*/
void printCircle(FILE *arqOut, Form circle){
    fprintf(arqOut, "\n<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\"/>\n", getFormX(circle),
     getFormY(circle), getFormR(circle), getFormStrokeColor(circle), getFormFillColor(circle), getFormSw(circle));
}

/*Printa as informacoes de retangulo armazenadas no vetor de struct e formatadas para SVG no arquivo SVG*/
void printRect(FILE *arqOut, Form rect){

    fprintf(arqOut, "\n<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-dasharray=\"%d\" stroke-width=\"%s\"/>\n",
    getFormX(rect), getFormY(rect), getFormW(rect), getFormH(rect), getFormStrokeColor(rect), getFormFillColor(rect), getFormStroke(rect), getFormSw(rect));
}

/*Printa as informacoes de texto armazenadas em variaveis locais no vetor de struct e formatadas para SVG no arquivo SVG*/
void printText(FILE *arqOut, double x, double y, char text[], char fillColor[]){

    fprintf(arqOut, "\n<text x=\"%lf\" y=\"%lf\" fill=\"%s\">%s</text>\n", x, y, fillColor, text);
}

void printLine(FILE *arqOut, double x1, double y1, double x2, double y2, char color[]){

    fprintf(arqOut, "\n<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\"/>\n", x1, y1, x2, y2, color);
}

void printEllipse(FILE *arqOut, double xC, double yC, double rX, double rY, char cor[]){

    fprintf(arqOut, "\n<ellipse cx=\"%lf\" cy=\"%lf\" rx=\"%lf\" ry=\"%lf\" fill=\"none\" stroke=\"%s\"/>\n", xC, yC, rX, rY, cor);
}

void printBlock(FILE *arqOut, Block block){

    fprintf(arqOut, "\n<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-dasharray=\"0\" stroke-width=\"%s\"/>\n",
    getBlockX(block), getBlockY(block), getBlockW(block), getBlockH(block), getBlockStrokeColor(block), 
    getBlockFillColor(block), getBlockSw(block));
}

void printHydrant(FILE *arqOut, Hydrant hydrant){
    fprintf(arqOut, "\n<circle cx=\"%lf\" cy=\"%lf\" r=\"6\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\"/>\n", getHydrantX(hydrant), 
    getHydrantY(hydrant), getHydrantStrokeColor(hydrant), getHydrantFillColor(hydrant), getHydrantSw(hydrant));

    printText(arqOut, getHydrantX(hydrant) - 4.5, getHydrantY(hydrant) + 4, "H", getHydrantStrokeColor(hydrant));
}

void printTrafficLight(FILE *arqOut, TrafficLight tLight){
    fprintf(arqOut, "\n<rect x=\"%lf\" y=\"%lf\" width=\"10\" height=\"10\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\"/>\n", 
    getTrafficLightX(tLight) - 5, getTrafficLightY(tLight) - 5, getTrafficLightStrokeColor(tLight), getTrafficLightFillColor(tLight), getTrafficLightSw(tLight));

    printText(arqOut, getTrafficLightX(tLight) - 3.5, getTrafficLightY(tLight) + 4, "S", getTrafficLightStrokeColor(tLight));
}

void printRadioTower(FILE *arqOut, RadioTower rTower){
    fprintf(arqOut, "\n<circle cx=\"%lf\" cy=\"%lf\" r=\"9\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\"/>\n", 
    getRadioTowerX(rTower), getRadioTowerY(rTower), getRadioTowerStrokeColor(rTower), getRadioTowerFillColor(rTower), getRadioTowerSw(rTower));

    printText(arqOut, getRadioTowerX(rTower) - 7.5, getRadioTowerY(rTower) + 4, "RB", getRadioTowerStrokeColor(rTower));
}

void printBuilding(FILE *arqOut, Building building, Block block){
    Form rect;
    char face[2];
    strcpy(face, getBuildingFace(building));
    int num = getBuildingNum(building);
    double faceSize = getBuildingFaceSize(building), depth = getBuildingDepth(building), margin = getBuildingMargin(building);
    double xB = getBlockX(block), yB = getBlockY(block), wB = getBlockW(block), hB = getBlockH(block);
    double x, y, w, h;

    if(!strcmp(face, "N")){
        x = xB + num - faceSize / 2;
        y = yB + hB - margin - depth;
        w = faceSize;
        h = depth;
    }
    else if(!strcmp(face, "S")){
        x = xB + num - faceSize / 2;
        y = yB + margin;
        w = faceSize;
        h = depth;
    }
    else if(!strcmp(face, "O")){
        x = xB + wB - margin - depth;
        y = yB + num - faceSize / 2;
        w = depth;
        h = faceSize;
    }
    else if(!strcmp(face, "L")){
        x = xB + margin;
        y = yB + num - faceSize / 2;
        w = depth;
        h = faceSize;
    }

    setBuildingX(building, x);
    setBuildingY(building, y);
    setBuildingW(building, w);
    setBuildingH(building, h);

    rect = createRect("", x, y, w, h, "black", "white", 0, "1");
    printRect(arqOut, rect);

    freeForm(rect);
}

void printWall(FILE *arqOut, Wall wall){
    
    printLine(arqOut, getWallX1(wall), getWallY1(wall), getWallX2(wall), getWallY2(wall), "black");
}

void printBB(List figures, FILE *arq, char color[]){

    double x, y, w, h, rx, ry;
    char strokeColorR[24], fillColorR[24];
    Form figure;

    for(int i = getFirst(figures); i != getNulo(); i = getNext(figures, i)){
        figure = getElementByIndex(figures, i);
        
        if(!strcmp(getType(figures, i), "c")){
            printCircle(arq, figure);
            x = getFormX(figure) - getFormR(figure);
            y = getFormY(figure) - getFormR(figure);
            w = 2 * getFormR(figure);
            h = 2 * getFormR(figure);
            strcpy(strokeColorR, color);
            strcpy(fillColorR, "none");
            Form retangulo = createRect("0", x, y, w, h, strokeColorR, fillColorR, 0, "1");
            printRect(arq, retangulo);
            free(retangulo);
        }
        else if(!strcmp(getType(figures, i), "r")){
            printRect(arq, figure);
            x = getFormX(figure) + getFormW(figure) / 2;
            y = getFormY(figure) + getFormH(figure) / 2;
            rx = getFormW(figure) / 2;
            ry = getFormH(figure) / 2;
            printEllipse(arq, x, y, rx, ry, color);
        }
    }
}

void printBomb(FILE *arq, double x, double y){

    fprintf(arq, "\n<g transform=\"translate (%lf %lf) scale(0.05 0.05)\"><path d=\"m419.922 511.794c-2.94 0-5.869-.863-8.395-2.568l-103.005-69.548c-4.131-2.789-6.606-7.448-6.606-12.432v-131.749c0-8.284 18.368-21.514 20.295-24.588 4.4-7.02 13.658-9.143 20.676-4.743l85 53.279c4.376 2.743 7.034 7.544 7.034 12.709v164.64c0 5.548-3.062 10.643-7.961 13.246-2.208 1.173-4.627 1.754-7.038 1.754z\" fill=\"#e0d2cd\"/><path d=\"m91.872 511.794c-2.412 0-4.83-.581-7.038-1.754-4.899-2.604-7.961-7.698-7.961-13.246v-164.64c0-5.165 2.657-9.967 7.034-12.709l85-53.279c5.736-3.596 13.17-2.903 18.143 1.689l18 16.622c3.075 2.84 4.823 6.834 4.823 11.02v131.749c0 4.984-2.476 9.643-6.606 12.431l-103 69.548c-2.526 1.706-5.455 2.569-8.395 2.569z\" fill=\"#eee1dc\"/><path d=\"m174.897 346.897-50.11-90.104c-11.683-20.983-16.893-39.479-16.893-59.974v-48.819c0-17.204 2.95-33.731 8.372-49.103 20.296-57.546 260.857-56.104 280.278 3 4.769 14.515 7.35 30.013 7.35 46.103v48.582c0 20.464-5.192 38.932-16.836 59.88l-50.162 90.436h-161.999z\" fill=\"#fff4f4\"/><path d=\"m396.544 101.897c-9.752-29.678-75.264-44.816-140.647-45.248v290.248h81l50.162-90.436c11.644-20.948 16.836-39.416 16.836-59.88v-48.581c0-16.09-2.581-31.589-7.351-46.103z\" fill=\"#f6efea\"/><path d=\"m116.278 98.897h279.232c-20.297-57.544-75.213-98.897-139.615-98.897s-119.319 41.353-139.617 98.897z\" fill=\"#ff1f3e\"/><path d=\"m171.601 340.897 28.986 52.075c.117.209.239.417.365.621l.245.395c2.737 4.405 7.555 7.084 12.741 7.084h.013l83.956-.072c5.442-.004 10.454-2.956 13.098-7.712l29.121-52.391z\" fill=\"#00347b\"/><path d=\"m255.897 98.897h139.614c-20.298-57.543-75.213-98.896-139.614-98.897z\" fill=\"#d10050\"/><path d=\"m255.897 340.897v60.138l42.01-.035c5.442-.004 10.454-2.956 13.098-7.712l29.121-52.391z\" fill=\"#001737\"/></g>\n", x, y);
}