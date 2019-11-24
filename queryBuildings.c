#include "queryBuildings.h"

void treatDQ_Util(FILE *arqTxt, FILE *arqSvgQ, Tree blocks, Node node, HashTable blocksTable, char *metric, Form circle){
    Block block = getElement(blocks, node);

    if(!strcmp(metric, "L1")){
        if(node == getNil(blocks)) return;

        treatDQ_Util(arqTxt, arqSvgQ, blocks, getLeft(blocks, node), blocksTable, metric, circle);

        treatDQ_Util(arqTxt, arqSvgQ, blocks, getRight(blocks, node), blocksTable, metric, circle);

        if(quadInsideCirc(block, circle, "L1")){
            fprintf(arqTxt, "\tQuadra Removida: %s\n", getBlockCep(block));
            removeNode(blocks, block);
            removeHashTable(blocksTable, getBlockCep(block));
            destroyBlock(block);
        }
    }
    else if(!strcmp(metric, "L2")){
        if(node == getNil(blocks)) return;

        treatDQ_Util(arqTxt, arqSvgQ, blocks, getLeft(blocks, node), blocksTable, metric, circle);

        treatDQ_Util(arqTxt, arqSvgQ, blocks, getRight(blocks, node), blocksTable, metric, circle);

        if(quadInsideCirc(block, circle, "L2")){
            fprintf(arqTxt, "\tQuadra Removida: %s\n", getBlockCep(block));
            removeNode(blocks, block);
            removeHashTable(blocksTable, getBlockCep(block));
            destroyBlock(block);
        }
    }
}

void treatDQ(FILE *arqTxt, FILE *arqSvgQ, Tree blocks, HashTable blocksTable, char metric[], Form circle){
    Form ring1 = createCircle("0", getFormX(circle), getFormY(circle), 18, "green", "none", "5");
    Form ring2 = createCircle("0", getFormX(circle), getFormY(circle), 13, "lightgreen", "none", "5");

    fprintf(arqTxt, "dq %s %lf\n", metric, getFormR(circle));
    fprintf(arqTxt, "\tEquipamento Urbano: %s (%lf %lf)\n", getFormId(circle), getFormX(circle), getFormY(circle));
    printCircle(arqSvgQ, ring1);
    printCircle(arqSvgQ, ring2);

    free(ring1);
    free(ring2);

    treatDQ_Util(arqTxt, arqSvgQ, blocks, getTreeRoot(blocks), blocksTable, metric, circle);
}

void deleteBlock(Block block, Tree blocks, HashTable blocksTable){

    removeNode(blocks, block);
    removeHashTable(blocksTable, getBlockCep(block));
    destroyBlock(block);
}

void deleteHydrant(Hydrant hydrant, Tree hydrants, HashTable hydrantsTable){

    removeNode(hydrants, hydrant);
    removeHashTable(hydrantsTable, getHydrantId(hydrant));
    destroyHydrant(hydrant);
}

void deleteBuilding(Building building, Tree buildings, HashTable buildingsTable){

    removeNode(buildings, building);
    removeHashTable(buildingsTable, getBuildingKey(building));
    destroyBuilding(building);
}

void deleteTrafficLight(TrafficLight tLight, Tree tLights, HashTable tLightsTable){

    removeNode(tLights, tLight);
    removeHashTable(tLightsTable, getTrafficLightId(tLight));
    destroyTrafficLight(tLight);
}

void deleteRadioTower(RadioTower rTower, Tree rTowers, HashTable rTowersTable){

    removeNode(rTowers, rTower);
    removeHashTable(rTowersTable, getRadioTowerId(rTower));
    destroyRadioTower(rTower);
}

void treatDEL(FILE *arqText, char *id, Tree blocks, HashTable blocksTable, Tree hydrants, HashTable hydrantsTable, Tree tLights, HashTable tLightsTable, Tree rTowers, HashTable rTowersTable){
    double x, y;

    Element element = searchHashTable(blocksTable, id);
    if(element != NULL){
        x = getBlockX(element);
        y = getBlockY(element);
        deleteBlock(element, blocks, blocksTable);
    }
    else{
        element = searchHashTable(hydrantsTable, id);
        if(element != NULL){
            x = getHydrantX(element);
            y = getHydrantY(element);
            deleteHydrant(element, hydrants, hydrantsTable);
        }
        else{
            element = searchHashTable(tLightsTable, id);
            if(element != NULL){
                x = getTrafficLightX(element);
                y = getTrafficLightY(element);
                deleteTrafficLight(element, tLights, tLightsTable);
            }
            else{
                element = searchHashTable(rTowersTable, id);
                if(element != NULL){
                    x = getRadioTowerX(element);
                    y = getRadioTowerY(element);
                    deleteRadioTower(element, rTowers, rTowersTable);
                }
            }
        }
    }
    fprintf(arqText, "del %s\n", id);
    fprintf(arqText, "\tEquipamento Urbano Removido: %s (%lf %lf)\n\n", id, x, y);
}

void treatCBQ(FILE *arqTxt, Tree blocks, Node node, Form circle, char *cstrk){
    Block block = getElement(blocks, node);
    
    if(node == getNil(blocks)) return;

    treatCBQ(arqTxt, blocks, getLeft(blocks, node), circle, cstrk);

    if(quadInsideCirc(block, circle, "L2")){
        setBlockStrokeColor(block, cstrk);
        fprintf(arqTxt, "\tCor da borda da quadra alterada: %s\n", getBlockCep(block));
    }

    treatCBQ(arqTxt, blocks, getRight(blocks, node), circle, cstrk);
}

void treatTRNS_block(FILE *arqTxt, Tree blocks, Node node, Form rect, double dx, double dy, FILE *arqSvgQ){
    Block block = getElement(blocks, node);

    if(node == getNil(blocks)) return;

    treatTRNS_block(arqTxt, blocks, getLeft(blocks, node), rect, dx, dy, arqSvgQ);

    if(quadInsideRect(block, rect)){
        fprintf(arqTxt, "\tQuadra Movida: %s\n\tPosicao Anterior: (%lf, %lf) ", getBlockCep(block), getBlockX(block), getBlockY(block));
        setBlockX(block, getBlockX(block) + dx);
        setBlockY(block, getBlockY(block) + dy);
        fprintf(arqTxt, "Posicao Atual: (%lf, %lf)\n\n", getBlockX(block), getBlockY(block));
    }

    treatTRNS_block(arqTxt, blocks, getRight(blocks, node), rect, dx, dy, arqSvgQ);
}

void treatTRNS_hydrant(FILE *arqTxt, Tree hydrants, Node node, Form rect, double dx, double dy, FILE *arqSvgQ){
    Hydrant hydrant = getElement(hydrants, node);

    if(node == getNil(hydrants)) return;

    treatTRNS_hydrant(arqTxt, hydrants, getLeft(hydrants, node), rect, dx, dy, arqSvgQ);

    if(pointInsideFigure(getHydrantX(hydrant), getHydrantY(hydrant), rect, "r", "L2")){
        fprintf(arqTxt, "\tHidrante Movido: %s\n\tPosicao Anterior: (%lf, %lf) ", getHydrantId(hydrant), getHydrantX(hydrant), getHydrantY(hydrant));
        setHydrantX(hydrant, getHydrantX(hydrant) + dx);
        setHydrantY(hydrant, getHydrantY(hydrant) + dy);
        fprintf(arqTxt, "Posicao Atual: (%lf, %lf)\n\n", getHydrantX(hydrant), getHydrantY(hydrant));
    }

    treatTRNS_hydrant(arqTxt, hydrants, getRight(hydrants, node), rect, dx, dy, arqSvgQ);
}

void treatTRNS_tLight(FILE *arqTxt, Tree tLights, Node node, Form rect, double dx, double dy, FILE *arqSvgQ){
    TrafficLight tLight = getElement(tLights, node);

    if(node == getNil(tLights)) return;

    treatTRNS_tLight(arqTxt, tLights, getLeft(tLights, node), rect, dx, dy, arqSvgQ);

    if(pointInsideFigure(getHydrantX(tLight), getHydrantY(tLight), rect, "r", "L2")){
        fprintf(arqTxt, "\tSemáforo Movido: %s\n\tPosicao Anterior: (%lf, %lf) ", getTrafficLightId(tLight), getTrafficLightX(tLight), getTrafficLightY(tLight));
        setHydrantX(tLight, getTrafficLightX(tLight) + dx);
        setHydrantY(tLight, getTrafficLightY(tLight) + dy);
        fprintf(arqTxt, "Posicao Atual: (%lf, %lf)\n\n", getTrafficLightX(tLight), getTrafficLightY(tLight));
    }

    treatTRNS_tLight(arqTxt, tLights, getRight(tLights, node), rect, dx, dy, arqSvgQ);
}

void treatTRNS_rTower(FILE *arqTxt, Tree rTowers, Node node, Form rect, double dx, double dy, FILE *arqSvgQ){
    RadioTower rTower = getElement(rTowers, node);

    if(node == getNil(rTowers)) return;

    treatTRNS_rTower(arqTxt, rTowers, getLeft(rTowers, node), rect, dx, dy, arqSvgQ);

    if(pointInsideFigure(getHydrantX(rTower), getHydrantY(rTower), rect, "r", "L2")){
        fprintf(arqTxt, "\tTorre de Rádio Movido: %s\n\tPosicao Anterior: (%lf, %lf) ", getRadioTowerId(rTower), getRadioTowerX(rTower), getRadioTowerY(rTower));
        setHydrantX(rTower, getRadioTowerX(rTower) + dx);
        setHydrantY(rTower, getRadioTowerY(rTower) + dy);
        fprintf(arqTxt, "Posicao Atual: (%lf, %lf)\n\n", getRadioTowerX(rTower), getRadioTowerY(rTower));
    }

    treatTRNS_rTower(arqTxt, rTowers, getRight(rTowers, node), rect, dx, dy, arqSvgQ);
}