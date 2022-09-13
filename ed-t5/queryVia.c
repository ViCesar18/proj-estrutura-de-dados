#include "queryVia.h"

void setRegister(Point *registers, char *r, Point point){
    if(!strcmp("R0", r))
        registers[0] = point;
    else if(!strcmp("R1", r))
        registers[1] = point;
    else if(!strcmp("R2", r))
        registers[2] = point;
    else if(!strcmp("R3", r))
        registers[3] = point;
    else if(!strcmp("R4", r))
        registers[4] = point;
    else if(!strcmp("R5", r))
        registers[5] = point;
    else if(!strcmp("R6", r))
        registers[6] = point;
    else if(!strcmp("R7", r))
        registers[7] = point;
    else if(!strcmp("R8", r))
        registers[8] = point;
    else if(!strcmp("R9", r))
        registers[9] = point;
    else if(!strcmp("R10", r))
        registers[10] = point;
    else
        printf("Registrador Invalido!\n");
}

Point getRegisterPoint(Point *registers, char *r){
    if(!strcmp("R0", r))
        return registers[0];
    else if(!strcmp("R1", r))
        return registers[1];
    else if(!strcmp("R2", r))
        return registers[2];
    else if(!strcmp("R3", r))
        return registers[3];
    else if(!strcmp("R4", r))
        return registers[4];
    else if(!strcmp("R5", r))
        return registers[5];
    else if(!strcmp("R6", r))
        return registers[6];
    else if(!strcmp("R7", r))
        return registers[7];
    else if(!strcmp("R8", r))
        return registers[8];
    else if(!strcmp("R9", r))
        return registers[9];
    else if(!strcmp("R10", r))
        return registers[10];
    else
        printf("Registrador Invalido!\n");
}

void treatRegisterM(Point *registers, char *r, char *cep, HashTable residents){
    Resident resident = searchHashTable(residents, cep);

    double x = getResidentX(resident);
    double y = getResidentY(resident);

    Point point = createPoint(x, y);

    setRegister(registers, r, point);
}

void treatRegisterE(Point *registers, char *r, char *cep, char *face, int num, HashTable blocks){
    Block block = searchHashTable(blocks, cep);

    double x, y;
    double xB = getBlockX(block), yB = getBlockY(block), wB = getBlockW(block), hB = getBlockH(block);

    if(!strcmp("N", face)){
        x = xB + num;
        y = yB + yB;
    }
    else if(!strcmp("S", face)){
        x = xB + num;
        y = yB;
    }
    else if(!strcmp("L", face)){
        x = xB;
        y = yB + num;
    }
    else if(!strcmp("O", face)){
        x = xB + wB;
        y = yB + num;
    }

    Point point = createPoint(x, y);
    setRegister(registers, r, point);
}

void treatRegisterG(Point *registers, char *r, char *id, HashTable hydrants, HashTable tLights, HashTable rTowers){
    double x, y;

    Element element = searchHashTable(hydrants, id);
    if(element == NULL){
        element = searchHashTable(tLights, id);
        
        if(element == NULL){
            element = searchHashTable(rTowers, id);
            x = getRadioTowerX(element);
            y = getRadioTowerY(element);
        }
        else{
            x = getTrafficLightX(element);
            y = getTrafficLightY(element);
        }
    }
    else{
        x = getHydrantX(element);
        y = getHydrantY(element);
    }

    Point point = createPoint(x, y);
    setRegister(registers, r, point);
}

void treatP(FILE *arqSvg, Point *registers, char *r1, char *r2, char *corMc, char *corMr, Graph pathways){
    Point p1 = getRegisterPoint(registers, r1);
    Point p2 = getRegisterPoint(registers, r2);
    GNode v1 = getGraphNode(pathways, 0);
    GNode v2 = getGraphNode(pathways, 0);

    for(int i = 0; i < getGraphFree(pathways); i++){
        GNode aux = getGraphNode(pathways, i);

        if(distEuclid(getPointX(p1), getPointY(p1), getGraphNodeX(aux), getGraphNodeY(aux)) < 
        distEuclid(getPointX(p1), getPointY(p1), getGraphNodeX(v1), getGraphNodeY(v1))){
            v1 = aux;
        }

        if(distEuclid(getPointX(p2), getPointY(p2), getGraphNodeX(aux), getGraphNodeY(aux)) < 
        distEuclid(getPointX(p2), getPointY(p2), getGraphNodeX(v2), getGraphNodeY(v2))){
            v2 = aux;
        }
    }

    //Caminho mais rápido
    shortestWat_Dijkstra(pathways, getGraphNodeId(v1), true);

    GNode aux = v2;
    while(aux != v1){
        double x1 = getGraphNodeX(aux);
        double y1 = getGraphNodeY(aux);

        Vertex vAux = getGraphNodeP(aux);
        if(vAux == NULL){
            printf("Nao existe via para o distino selecionado!\n");
            exit(1);
        }
        aux = getGraphVertexNode(vAux);

        double x2 = getGraphNodeX(aux);
        double y2 = getGraphNodeY(aux);

        printWay(arqSvg, x1, y1, x2, y2, corMr, 7);
    }

    //Caminho mais curto
    shortestWat_Dijkstra(pathways, getGraphNodeId(v1), false);

    aux = v2;
    while(aux != v1){
        double x1 = getGraphNodeX(aux);
        double y1 = getGraphNodeY(aux);

        Vertex vAux = getGraphNodeP(aux);
        if(vAux == NULL){
            printf("Nao existe via para o distino selecionado!\n");
            exit(1);
        }
        aux = getGraphVertexNode(vAux);

        double x2 = getGraphNodeX(aux);
        double y2 = getGraphNodeY(aux);

        printWay(arqSvg, x1, y1, x2, y2, corMc, 4);
    }
}