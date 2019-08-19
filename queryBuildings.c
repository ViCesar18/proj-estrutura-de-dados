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