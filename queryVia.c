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