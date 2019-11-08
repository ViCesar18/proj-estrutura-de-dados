#include "outSVG.h"

void createOutputFileName(char **nameOut, char nameIn[]){
    int i = 0;

    *nameOut = (char *)malloc((strlen(nameIn) + 1) * sizeof(char));

    while(nameIn[i] != '.'){
        (*nameOut)[i] = nameIn[i];
        i++;
    }
    (*nameOut)[i] = '\0';
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

    (*nameOut)[j] = '\0';
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

    (*nameOut)[j] = '\0';
}

/*Printa as informacoes de circulo armazenadas no vetor de struct e formatadas para SVG no arquivo SVG*/
void printCircle(FILE *arqOut, Form circle){
    if(strcmp(getFormType(circle), "c") != 0) return;

    fprintf(arqOut, "\n<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\"/>\n", getFormX(circle),
     getFormY(circle), getFormR(circle), getFormStrokeColor(circle), getFormFillColor(circle), getFormSw(circle));
}

/*Printa as informacoes de retangulo armazenadas no vetor de struct e formatadas para SVG no arquivo SVG*/
void printRect(FILE *arqOut, Form rect){
    if(strcmp(getFormType(rect), "r") != 0) return;

    fprintf(arqOut, "\n<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-dasharray=\"%d\" stroke-width=\"%s\"/>\n",
    getFormX(rect), getFormY(rect), getFormW(rect), getFormH(rect), getFormStrokeColor(rect), getFormFillColor(rect), getFormStroke(rect), getFormSw(rect));
}

/*Printa as informacoes de texto armazenadas em variaveis locais no vetor de struct e formatadas para SVG no arquivo SVG*/
void printText(FILE *arqOut, double x, double y, char text[], char fillColor[]){

    fprintf(arqOut, "\n<text x=\"%lf\" y=\"%lf\" fill=\"%s\" dominant-baseline=\"baseline\" text-anchor=\"middle\" font-family=\"Arial\" style=\"stroke-width:0.2px;\">%s</text>\n", x, y, fillColor, text);
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

    printText(arqOut, getBlockX(block) + 18, getBlockY(block) + 12, getBlockCep(block), getBlockStrokeColor(block));
}

void printHydrant(FILE *arqOut, Hydrant hydrant){
    fprintf(arqOut, "\n<circle cx=\"%lf\" cy=\"%lf\" r=\"6\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\"/>\n", getHydrantX(hydrant), 
    getHydrantY(hydrant), getHydrantStrokeColor(hydrant), getHydrantFillColor(hydrant), getHydrantSw(hydrant));

    printText(arqOut, getHydrantX(hydrant), getHydrantY(hydrant) + 4, "H", getHydrantStrokeColor(hydrant));
}

void printTrafficLight(FILE *arqOut, TrafficLight tLight){
    fprintf(arqOut, "\n<rect x=\"%lf\" y=\"%lf\" width=\"10\" height=\"10\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\"/>\n", 
    getTrafficLightX(tLight) - 5, getTrafficLightY(tLight) - 5, getTrafficLightStrokeColor(tLight), getTrafficLightFillColor(tLight), getTrafficLightSw(tLight));

    printText(arqOut, getTrafficLightX(tLight), getTrafficLightY(tLight) + 4, "S", getTrafficLightStrokeColor(tLight));
}

void printRadioTower(FILE *arqOut, RadioTower rTower){
    fprintf(arqOut, "\n<circle cx=\"%lf\" cy=\"%lf\" r=\"9\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\"/>\n", 
    getRadioTowerX(rTower), getRadioTowerY(rTower), getRadioTowerStrokeColor(rTower), getRadioTowerFillColor(rTower), getRadioTowerSw(rTower));

    printText(arqOut, getRadioTowerX(rTower), getRadioTowerY(rTower) + 4, "RB", getRadioTowerStrokeColor(rTower));
}

int i = 0;

void printBuilding(FILE *arqOut, Building building){
    Form rect;
    char face[2];
    strcpy(face, getBuildingFace(building));
    int num = getBuildingNum(building);
    Block block = getBuildingBlock(building);
    double faceSize = getBuildingFaceSize(building), depth = getBuildingDepth(building), margin = getBuildingMargin(building);
    double xB = getBlockX(block), yB = getBlockY(block), wB = getBlockW(block), hB = getBlockH(block);
    i++;
    double x, y, w, h;

    char text[4];

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

    rect = createRect("0", x, y, w, h, "black", "white", 0, "1");
    printRect(arqOut, rect);

    sprintf(text, "%d", getBuildingNum(building));
    printText(arqOut, getBuildingX(building) + getBuildingW(building) / 2, getBuildingY(building) + getBuildingH(building) / 2 + 4, text, "black");

    destroyForm(rect);
}

void printWall(FILE *arqOut, Wall wall){
    
    printLine(arqOut, getWallX1(wall), getWallY1(wall), getWallX2(wall), getWallY2(wall), "black");
}

void printBB(Tree forms, Node node, FILE *arq, char color[]){
    double x, y, w, h, rx, ry;
    char strokeColorR[24], fillColorR[24];

    if(node == getNil(forms)) return;

    printBB(forms, getLeft(forms, node), arq, color);

    Form form = getElement(forms, node);
    
    if(!strcmp(getFormType(form), "c")){
        printCircle(arq, form);
        x = getFormX(form) - getFormR(form);
        y = getFormY(form) - getFormR(form);
        w = 2 * getFormR(form);
        h = 2 * getFormR(form);
        strcpy(strokeColorR, color);
        strcpy(fillColorR, "none");
        Form retangulo = createRect("0", x, y, w, h, strokeColorR, fillColorR, 0, "1");
        printRect(arq, retangulo);
        free(retangulo);
    }
    else if(!strcmp(getFormType(form), "r")){
        printRect(arq, form);
        x = getFormX(form) + getFormW(form) / 2;
        y = getFormY(form) + getFormH(form) / 2;
        rx = getFormW(form) / 2;
        ry = getFormH(form) / 2;
        printEllipse(arq, x, y, rx, ry, color);
    }
    
    printBB(forms, getRight(forms, node), arq, color);
}

void printBomb(FILE *arq, double x, double y){

    fprintf(arq, "\n<g transform=\"translate (%lf %lf) scale(0.05 0.05)\"><path d=\"m419.922 511.794c-2.94 0-5.869-.863-8.395-2.568l-103.005-69.548c-4.131-2.789-6.606-7.448-6.606-12.432v-131.749c0-8.284 18.368-21.514 20.295-24.588 4.4-7.02 13.658-9.143 20.676-4.743l85 53.279c4.376 2.743 7.034 7.544 7.034 12.709v164.64c0 5.548-3.062 10.643-7.961 13.246-2.208 1.173-4.627 1.754-7.038 1.754z\" fill=\"#e0d2cd\"/><path d=\"m91.872 511.794c-2.412 0-4.83-.581-7.038-1.754-4.899-2.604-7.961-7.698-7.961-13.246v-164.64c0-5.165 2.657-9.967 7.034-12.709l85-53.279c5.736-3.596 13.17-2.903 18.143 1.689l18 16.622c3.075 2.84 4.823 6.834 4.823 11.02v131.749c0 4.984-2.476 9.643-6.606 12.431l-103 69.548c-2.526 1.706-5.455 2.569-8.395 2.569z\" fill=\"#eee1dc\"/><path d=\"m174.897 346.897-50.11-90.104c-11.683-20.983-16.893-39.479-16.893-59.974v-48.819c0-17.204 2.95-33.731 8.372-49.103 20.296-57.546 260.857-56.104 280.278 3 4.769 14.515 7.35 30.013 7.35 46.103v48.582c0 20.464-5.192 38.932-16.836 59.88l-50.162 90.436h-161.999z\" fill=\"#fff4f4\"/><path d=\"m396.544 101.897c-9.752-29.678-75.264-44.816-140.647-45.248v290.248h81l50.162-90.436c11.644-20.948 16.836-39.416 16.836-59.88v-48.581c0-16.09-2.581-31.589-7.351-46.103z\" fill=\"#f6efea\"/><path d=\"m116.278 98.897h279.232c-20.297-57.544-75.213-98.897-139.615-98.897s-119.319 41.353-139.617 98.897z\" fill=\"#ff1f3e\"/><path d=\"m171.601 340.897 28.986 52.075c.117.209.239.417.365.621l.245.395c2.737 4.405 7.555 7.084 12.741 7.084h.013l83.956-.072c5.442-.004 10.454-2.956 13.098-7.712l29.121-52.391z\" fill=\"#00347b\"/><path d=\"m255.897 98.897h139.614c-20.298-57.543-75.213-98.896-139.614-98.897z\" fill=\"#d10050\"/><path d=\"m255.897 340.897v60.138l42.01-.035c5.442-.004 10.454-2.956 13.098-7.712l29.121-52.391z\" fill=\"#001737\"/></g>\n", x - 13, y - 10);
}

void printFire(FILE *arq, double x, double y){
    fprintf(arq, "\n<g transform=\"translate (%lf %lf) scale (0.03 0.03)\"><sodipodi:namedview id=\"base\" bordercolor=\"#666666\" inkscape:pageshadow=\"2\" inkscape:guide-bbox=\"true\" pagecolor=\"#ffffff\" inkscape:window-height=\"1025\" inkscape:window-maximized=\"0\" inkscape:zoom=\"0.49910994\" inkscape:window-x=\"0\" showgrid=\"false\" borderopacity=\"1.0\" inkscape:current-layer=\"g3884\" inkscape:cx=\"-570.58125\" inkscape:cy=\"142.05854\" showguides=\"true\" inkscape:window-y=\"0\" inkscape:window-width=\"1680\" inkscape:pageopacity=\"0.0\" inkscape:document-units=\"px\"> <sodipodi:guide id=\"guide2887\" position=\"458.57609,-142.25867\" orientation=\"0,1\"/> <sodipodi:guide id=\"guide2889\" position=\"172.06607,-102.18734\" orientation=\"1,0\"/><sodipodi:guide id=\"guide2891\" position=\"524.69378,557.98785\" orientation=\"1,0\"/><sodipodi:guide id=\"guide3800\" position=\"226.42691,3.6478138\" orientation=\"0,1\"/></sodipodi:namedview><g id=\"g3884\" inkscape:label=\"layer\" transform=\"translate(-394.91 432.31)\" inkscape:groupmode=\"layer\"><path id=\"path3918\" sodipodi:nodetypes=\"cccccccccccc\" style=\"fill-rule:evenodd;stroke:#ff0000;fill:#ff1546\" d=\"m613.07-150.19c13.524 59.513-1 119.56-1 119.56-25.88-20.537-41.452-44.412-45.094-59.281-18.704 25.095-8.6167 110.84 0 137.78-23.206-13.328-19.237-18.178-41.25-72.156-13.718 71.114 14.897 146.5 41.254 188.82 22.043 0 30.998-0.00001 54.361-0.00001 58.71-32.9 102.22-102.74 109.1-178.62-13.678 5.4452-18.035 26.778-57.5 29.875 10.301-20.966 25.5-83.556 21.938-113.34-12.995 32.042-14.686 53.692-38.344 56.656-5.3729-49.303-22.825-85.578-43.469-109.28z\"/><path id=\"path2969\" sodipodi:nodetypes=\"cccscccccccccccccccsscccccccc\" style=\"stroke:#ff2e20;stroke-width:5;fill:#ffe411\" d=\"m609.79-429.81c-61.656 30.741-21.947 101.41-42.809 160.51 0 0-22.645-65.892-66.472-60.856 6.6165 11.248 16.184 22.473 22.062 33.812 20.737 40.005 6.8438 110.97 6.8438 110.97s-49.32-41.902-88.531-41.875c20.654 42.149 47.526 77.286 29.062 128.69-5.3864-2.8936-43.92-16.72-72.531-18.906 66.992 108.31 1.4014 263.64 169.56 283.16-26.975-41.759-55.315-117.06-41.254-189.95 22.013 53.979 18.051 58.806 41.257 72.133-8.6167-26.938-18.704-112.67 0-137.77 3.6416 14.869 19.2 38.729 45.08 59.266 0 0 14.526-60.043 1.0018-119.56 20.644 23.703 38.11 59.976 43.483 109.28 23.658-2.964 25.357-24.601 38.352-56.643 3.5624 29.788-11.639 92.363-21.939 113.33 39.465-3.0968 43.799-24.429 57.477-29.874-6.8877 75.881-50.652 146.88-109.36 179.79 107.41-1.1477 137.59-21.569 166.86-90.385 7.2252-16.986 9.7061-36.286 17.158-56.338 16.098-43.317 31.1-59.986 38.871-104.83-16.691 18.061-52.423 24.308-52.423 24.308s22.188-109.75-25.812-140.03c0.56839 18.514 5.3226 72.94-20.781 75.688 0.67694-58.843 3.3622-168.55-70.781-188.19 1.3959 9.4923 4.3126 16.048 6.4062 22.469 1.9436 7.4061 8.7084 32.46-1 33.781-16.568-57.555-51.221-50.876-69.781-171.97z\"/></g><metadata><rdf:RDF><cc:Work><dc:format>image/svg+xml</dc:format><dc:type rdf:resource=\"http://purl.org/dc/dcmitype/StillImage\"/><cc:license rdf:resource=\"http://creativecommons.org/licenses/publicdomain/\"/><dc:publisher><cc:Agent rdf:about=\"http://openclipart.org/\"><dc:title>Openclipart</dc:title></cc:Agent></dc:publisher><dc:title>Fire</dc:title><dc:date>2012-04-30T03:50:15</dc:date><dc:description/><dc:source>https://openclipart.org/detail/169759/fire-by-cybergedeon-169759</dc:source><dc:creator><cc:Agent><dc:title>dominiquechappard</dc:title></cc:Agent></dc:creator><dc:subject><rdf:Bag><rdf:li>burning</rdf:li><rdf:li>danger</rdf:li><rdf:li>fire</rdf:li><rdf:li>flame</rdf:li></rdf:Bag></dc:subject></cc:Work><cc:License rdf:about=\"http://creativecommons.org/licenses/publicdomain/\"><cc:permits rdf:resource=\"http://creativecommons.org/ns#Reproduction\"/><cc:permits rdf:resource=\"http://creativecommons.org/ns#Distribution\"/><cc:permits rdf:resource=\"http://creativecommons.org/ns#DerivativeWorks\"/></cc:License></rdf:RDF></metadata></g>\n", x - 7, y - 12);
}

void printTriangle(FILE *arq, Form triangle){
    if(strcmp(getFormType(triangle), "t") != 0) return;

	double x2 = getPointX(getVertexV(getFormV2(triangle))), y2 = getPointY(getVertexV(getFormV2(triangle)));
	double x3 = getPointX(getVertexV(getFormV3(triangle))), y3 = getPointY(getVertexV(getFormV3(triangle)));
    
	fprintf(arq, "<polygon points=\"%lf,%lf %lf,%lf %lf,%lf\" style=\"fill: lawngreen; opacity: 0.5\"/>\n", getFormX(triangle), getFormY(triangle), x2, y2, x3, y3);
}

void printTriangle2(FILE *arq, double x, double y, Vertex p2, Vertex p3){
	double x2 = getPointX(getVertexV(p2)), y2 = getPointY(getVertexV(p2));
	double x3 = getPointX(getVertexV(p3)), y3 = getPointY(getVertexV(p3));
    
	fprintf(arq, "<polygon points=\"%lf,%lf %lf,%lf %lf,%lf\" style=\"fill: lawngreen; opacity: 0.5\"/>\n", x, y, x2, y2, x3, y3);
}