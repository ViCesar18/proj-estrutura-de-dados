#include "queryBuildings.h"

void treatDQ(FILE *arqTxt, FILE *arqSvgQ, List blocks, char metric[], Form circle){
    Block block;
    Form ring1 = createCircle("0", getFormX(circle), getFormY(circle), 18, "green", "none", "5");
    Form ring2 = createCircle("0", getFormX(circle), getFormY(circle), 13, "lightgreen", "none", "5");

    fprintf(arqTxt, "dq %s %lf\n", metric, getFormR(circle));
    fprintf(arqTxt, "\tEquipamento Urbano: %s (%lf %lf)\n", getFormId(circle), getFormX(circle), getFormY(circle));
    printCircle(arqSvgQ, ring1);
    printCircle(arqSvgQ, ring2);

    free(ring1);
    free(ring2);

    if(!strcmp(metric, "L1")){
        for(int i = 0; i < getSize(blocks); i++){
            block = getElementByIndex(blocks, i);
            if(quadInsideCirc(block, circle, "L1")){
                deleteElement(blocks, getBlockCep(block));
                fprintf(arqTxt, "\tQuadra Removida: %s\n", getBlockCep(block));
            }
        }
    }
    else if(!strcmp(metric, "L2")){
        for(int i = 0; i < getSize(blocks); i++){
            block = getElementByIndex(blocks, i);
            if(quadInsideCirc(block, circle, "L2")){
                deleteElement(blocks, getBlockCep(block));
                fprintf(arqTxt, "\tQuadra Removida: %s\n", getBlockCep(block));
            }
        }
    }
}

void treatCBQ(FILE *arqTxt, List blocks, Form circle, char cstrk[]){
    Block block;
    
    fprintf(arqTxt, "cbq %lf %lf %lf %s\n", getFormX(circle), getFormY(circle), getFormR(circle), cstrk);
    for(int i = getFirst(blocks); i != getNulo(); i = getNext(blocks, i)){
        block = getElementByIndex(blocks, i);
        if(quadInsideCirc(block, circle, "L2")){
            setBlockStrokeColor(block, cstrk);
            fprintf(arqTxt, "\tCor da borda da quadra alterada: %s\n", getBlockCep(block));
        }
    }
}

void treatTRNS(FILE *arqTxt, List blocks, List hydrants, List tLights, List rTowers, Form rect, double dx, double dy, FILE *arqSvgQ){
    Block block;
    Hydrant hydrant;
    TrafficLight tLight;
    RadioTower rTower;

    for(int i = getFirst(blocks); i != getNulo(); i = getNext(blocks, i)){
        block = getElementByIndex(blocks, i);
        if(quadInsideRect(block, rect)){
            setBlockX(block, getBlockX(block) + dx);
            setBlockY(block, getBlockY(block) + dy);
        }
    }

    for(int i = getFirst(hydrants); i != getNulo(); i = getNext(hydrants, i)){
        hydrant = getElementByIndex(hydrants, i);
        if(pointInsideFigure(getHydrantX(hydrant), getHydrantY(hydrant), rect, "r", "L2")){
            setHydrantX(hydrant, getHydrantX(hydrant) + dx);
            setHydrantY(hydrant, getHydrantY(hydrant) + dy);
        }
    }

    for(int i = getFirst(tLights); i != getNulo(); i = getNext(tLights, i)){
        tLight = getElementByIndex(tLights, i);
        if(pointInsideFigure(getHydrantX(tLight), getHydrantY(tLight), rect, "r", "L2")){
            setHydrantX(tLight, getTrafficLightX(tLight) + dx);
            setHydrantY(tLight, getTrafficLightY(tLight) + dy);
        }
    }

    for(int i = getFirst(rTowers); i != getNulo(); i = getNext(rTowers, i)){
        rTower = getElementByIndex(rTowers, i);
        if(pointInsideFigure(getHydrantX(rTower), getHydrantY(rTower), rect, "r", "L2")){
            setHydrantX(rTower, getRadioTowerX(rTower) + dx);
            setHydrantY(rTower, getRadioTowerY(rTower) + dy);
        }
    }
}

typedef struct stDist{
    Element *element;
    double dist;
} *DistImp;

double getDist(Dist distAux){
    DistImp dist = (DistImp) distAux;

    return dist->dist;
}

void treatFI(FILE *arqSvg, FILE *arqTxt, List auxList, double x, double y, int ns, double r, List tLights, List hydrants){
    Form ring;
    Wall line;

    double dist;
    TrafficLight tLight;
    DistImp *tLightDists = (DistImp *) malloc(getSize(tLights) * sizeof(DistImp));
    int i, cont = 0;

    printFire(arqSvg, x, y);
    
    for(i = getFirst(tLights); i != getNulo(); i = getNext(tLights, i)){
        tLight = getElementByIndex(tLights, i);

        tLightDists[cont] = (DistImp) malloc(sizeof(struct stDist));
        tLightDists[cont]->element = tLight;
        tLightDists[cont]->dist = distEuclid(x, y, getTrafficLightX(tLight), getTrafficLightY(tLight));

        cont++;
    }

    min_heap_sort((void *) tLightDists, getSize(tLights) - 1, ns);
    reverseVector((void *) tLightDists, getSize(tLights) - 1);

    Hydrant hydrant;
    DistImp *hydrantDists = (DistImp *) malloc(getSize(hydrants) * sizeof(DistImp));
    cont = 0;

    for(i = getFirst(hydrants); i != getNulo(); i = getNext(hydrants, i)){
        hydrant = getElementByIndex(hydrants, i);

        hydrantDists[cont] = (DistImp) malloc(sizeof(struct stDist));
        hydrantDists[cont]->element = hydrant;
        hydrantDists[cont]->dist = distEuclid(x, y, getHydrantX(hydrant), getHydrantY(hydrant));

        cont++;
    }

    min_heap_sort((void *) hydrantDists, getSize(hydrants) - 1, getSize(hydrants));
    reverseVector((void *) hydrantDists, getSize(hydrants) - 1);

    fprintf(arqTxt, "Incêndio em %lf %lf!\n", x, y);
    fprintf(arqTxt, "Semáforos com a programação alterada:\n");
    for(i = 0; i < ns; i++){
        fprintf(arqTxt, "%s ", getTrafficLightId(tLightDists[i]->element));
        ring = createCircle("", getTrafficLightX(tLightDists[i]->element), getTrafficLightY(tLightDists[i]->element), 9, "green", "none", "3");
        line = createWall(x, y, getTrafficLightX(tLightDists[i]->element), getTrafficLightY(tLightDists[i]->element));
        insertElement(auxList, ring, "c");
        insertElement(auxList, line, "w");
    }
    
    fprintf(arqTxt, "\n\nHidrantes ativados:\n");
    for(i = 0; i < getSize(hydrants); i++){
        if(hydrantDists[i]->dist <= r){
            fprintf(arqTxt, "%s ", getHydrantId(hydrantDists[i]->element));
            ring = createCircle("", getHydrantX(hydrantDists[i]->element), getHydrantY(hydrantDists[i]->element), 9, "green", "none", "3");
            line = createWall(x, y, getHydrantX(hydrantDists[i]->element), getHydrantY(hydrantDists[i]->element));
            insertElement(auxList, ring, "c");
            insertElement(auxList, line, "w");
        }
        else{
            break;
        }
    }
    fprintf(arqTxt, "\n\n");

    for(int i = 0; i < getSize(tLights); i++){
        free(tLightDists[i]);
    }
    free(tLightDists);

    for(i = 0; i < getSize(hydrants); i++){
        free(hydrantDists[i]);
    }
    free(hydrantDists);
}

void getAddress(char cep[], char face[], int num, double *x, double *y, List blocks){
    Block block;
    char type[4];

    block = getElementById(blocks, cep, type);

    if(!strcmp(face, "N")){
        *x = getBlockX(block) + num;
        *y = getBlockY(block) + getBlockH(block);
    }
    else if(!strcmp(face, "S")){
        *x = getBlockX(block) + num;
        *y = getBlockY(block);
    }
    else if(!strcmp(face, "O")){
        *x = getBlockX(block) + getBlockW(block);
        *y = getBlockY(block) + num;
    }
    else if(!strcmp(face, "L")){
        *x = getBlockX(block);
        *y = getBlockY(block) + num;
    }
}

void treatFH(FILE *arqTxt, FILE *arqSvg, List hydrants, int k, double x, double y, List auxList){
    int i, cont = 0;
    Form ring;
    Wall line;
    DistImp *hydrantDists = (DistImp *) malloc(getSize(hydrants) * sizeof(DistImp));

    for(i = getFirst(hydrants); i != getNulo(); i = getNext(hydrants, i)){
        Hydrant hydrant = getElementByIndex(hydrants, i);
        hydrantDists[cont] = (DistImp) malloc(sizeof(struct stDist));
        hydrantDists[cont]->element = hydrant;
        hydrantDists[cont]->dist = distEuclid(x, y, getHydrantX(hydrant), getHydrantY(hydrant));

        cont++;
    }

    if(k < 0){
        k *= -1;
        min_heap_sort((void *)hydrantDists, getSize(hydrants) - 1, k);
        fprintf(arqTxt, "Hidrantes mais próximos do endeço:\n");
    }
    else if(k > 0){
        max_heap_sort((void *)hydrantDists, getSize(hydrants) - 1, k);
        fprintf(arqTxt, "Hidrantes mais distantes do endeço:\n");
    }
    
    reverseVector((void *)hydrantDists, getSize(hydrants) - 1);

    ring = createCircle("", x, y, 10, "red", "yellow", "4");
    insertElement(auxList, ring, "c");

    for(i = 0; i < k; i++){
        fprintf(arqTxt, "%s ", getHydrantId(hydrantDists[i]->element));
        ring = createCircle("", getHydrantX(hydrantDists[i]->element), getHydrantY(hydrantDists[i]->element), 9, "green", "none", "3");
        line = createWall(x, y, getHydrantX(hydrantDists[i]->element), getHydrantY(hydrantDists[i]->element));
        insertElement(auxList, ring, "c");
        insertElement(auxList, line, "w");
    }
    fprintf(arqTxt, "\n\n");

    for(i = 0; i < getSize(hydrants); i++){
        free(hydrantDists[i]);
    }
    free(hydrantDists);
}

void treatFS(FILE *arqTxt, FILE *arqSvg, List tLights, int k, double x, double y, List auxList){
    int i, cont = 0;
    Form ring;
    Wall line;
    DistImp *tLightDists = (DistImp *) malloc(getSize(tLights) * sizeof(DistImp));

    for(i = getFirst(tLights); i != getNulo(); i = getNext(tLights, i)){
        Hydrant tLight = getElementByIndex(tLights, i);
        tLightDists[cont] = (DistImp) malloc(sizeof(struct stDist));
        tLightDists[cont]->element = tLight;
        tLightDists[cont]->dist = distEuclid(x, y, getTrafficLightX(tLight), getTrafficLightY(tLight));

        cont++;
    }

    min_heap_sort((void *)tLightDists, getSize(tLights) - 1, k);
    fprintf(arqTxt, "Semáforos mais próximos do endeço:\n");
    
    reverseVector((void *)tLightDists, getSize(tLights) - 1);

    ring = createCircle("", x, y, 10, "red", "yellow", "4");
    insertElement(auxList, ring, "c");

    for(i = 0; i < k; i++){
        fprintf(arqTxt, "%s ", getTrafficLightId(tLightDists[i]->element));
        ring = createCircle("", getTrafficLightX(tLightDists[i]->element), getTrafficLightY(tLightDists[i]->element), 9, "green", "none", "3");
        line = createWall(x, y, getTrafficLightX(tLightDists[i]->element), getTrafficLightY(tLightDists[i]->element));
        insertElement(auxList, ring, "c");
        insertElement(auxList, line, "w");
    }
    fprintf(arqTxt, "\n\n");

    for(i = 0; i < getSize(tLights); i++){
        free(tLightDists[i]);
    }
    free(tLightDists);
}