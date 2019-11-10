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
        setBlockX(block, getBlockX(block) + dx);
        setBlockY(block, getBlockY(block) + dy);
    }

    treatTRNS_block(arqTxt, blocks, getRight(blocks, node), rect, dx, dy, arqSvgQ);
}

void treatTRNS_hydrant(FILE *arqTxt, Tree hydrants, Node node, Form rect, double dx, double dy, FILE *arqSvgQ){
    Hydrant hydrant = getElement(hydrants, node);

    if(node == getNil(hydrants)) return;

    treatTRNS_hydrant(arqTxt, hydrants, getLeft(hydrants, node), rect, dx, dy, arqSvgQ);

    if(pointInsideFigure(getHydrantX(hydrant), getHydrantY(hydrant), rect, "r", "L2")){
        setHydrantX(hydrant, getHydrantX(hydrant) + dx);
        setHydrantY(hydrant, getHydrantY(hydrant) + dy);
    }

    treatTRNS_hydrant(arqTxt, hydrants, getRight(hydrants, node), rect, dx, dy, arqSvgQ);
}

void treatTRNS_tLight(FILE *arqTxt, Tree tLights, Node node, Form rect, double dx, double dy, FILE *arqSvgQ){
    TrafficLight tLight = getElement(tLights, node);

    if(node == getNil(tLights)) return;

    treatTRNS_tLight(arqTxt, tLights, getLeft(tLights, node), rect, dx, dy, arqSvgQ);

    if(pointInsideFigure(getHydrantX(tLight), getHydrantY(tLight), rect, "r", "L2")){
        setHydrantX(tLight, getTrafficLightX(tLight) + dx);
        setHydrantY(tLight, getTrafficLightY(tLight) + dy);
    }

    treatTRNS_tLight(arqTxt, tLights, getRight(tLights, node), rect, dx, dy, arqSvgQ);
}

void treatTRNS_rTower(FILE *arqTxt, Tree rTowers, Node node, Form rect, double dx, double dy, FILE *arqSvgQ){
    RadioTower rTower = getElement(rTowers, node);

    if(node == getNil(rTowers)) return;

    treatTRNS_rTower(arqTxt, rTowers, getLeft(rTowers, node), rect, dx, dy, arqSvgQ);

    if(pointInsideFigure(getHydrantX(rTower), getHydrantY(rTower), rect, "r", "L2")){
        setHydrantX(rTower, getRadioTowerX(rTower) + dx);
        setHydrantY(rTower, getRadioTowerY(rTower) + dy);
    }

    treatTRNS_rTower(arqTxt, rTowers, getRight(rTowers, node), rect, dx, dy, arqSvgQ);
}

typedef struct stDist{
    Element *element;
    double dist;
} *DistImp;

double getDist(Dist distAux){
    DistImp dist = (DistImp) distAux;

    return dist->dist;
}

void treeToListDists(double x, double y, Tree tree, Node node, DistImp *listDists, int *cont, double (getX)(Element), double (getY)(Element)){
    Element element = getElement(tree, node);

    if(node == getNil(tree)) return;

    treeToListDists(x, y, tree, getLeft(tree, node), listDists, &(*cont), getX, getY);

    listDists[*cont] = (DistImp) malloc(sizeof(struct stDist));
    listDists[*cont]->element = element;
    listDists[*cont]->dist = distEuclid(x, y, getX(element), getY(element));

    (*cont)++;

    treeToListDists(x, y, tree, getRight(tree, node), listDists, &(*cont), getX, getY);

}

void treatFI(FILE *arqSvg, FILE *arqTxt, double x, double y, int ns, double r, Tree tLights, Tree hydrants){
    Form ring;
    Wall line;
    double dist;
    int cont = 0, ntLights;

    ntLights = getSize(tLights);

    DistImp *tLightDists = (DistImp *) malloc(ntLights * sizeof(DistImp));

    printFire(arqSvg, x, y);

    treeToListDists(x, y, tLights, getTreeRoot(tLights), tLightDists, &cont, getTrafficLightX, getTrafficLightY);

    min_heap_sort((void *) tLightDists, ntLights - 1, ns);
    reverseVector((void *) tLightDists, ntLights - 1);

    Hydrant hydrant;
    int nHydrants = getSize(hydrants);

    DistImp *hydrantDists = (DistImp *) malloc(nHydrants * sizeof(DistImp));
    cont = 0;

    treeToListDists(x, y, hydrants, getTreeRoot(hydrants), hydrantDists, &cont, getHydrantX, getHydrantY);

    min_heap_sort((void *) hydrantDists, nHydrants - 1, nHydrants);
    reverseVector((void *) hydrantDists, nHydrants - 1);

    fprintf(arqTxt, "Incêndio em %lf %lf!\n", x, y);
    fprintf(arqTxt, "Semáforos com a programação alterada:\n");
    for(int i = 0; i < ns; i++){
        fprintf(arqTxt, "%s ", getTrafficLightId(tLightDists[i]->element));
        ring = createCircle("", getTrafficLightX(tLightDists[i]->element), getTrafficLightY(tLightDists[i]->element), 9, "green", "none", "3");
        line = createWall(x, y, getTrafficLightX(tLightDists[i]->element), getTrafficLightY(tLightDists[i]->element));

        printCircle(arqSvg, ring);
        printWall(arqSvg, line);

        destroyForm(ring);
        destroyWall(line);
    }

    fprintf(arqTxt, "\n\nHidrantes ativados:\n");
    for(int i = 0; i < nHydrants; i++){
        if(hydrantDists[i]->dist <= r){
            fprintf(arqTxt, "%s ", getHydrantId(hydrantDists[i]->element));
            ring = createCircle("", getHydrantX(hydrantDists[i]->element), getHydrantY(hydrantDists[i]->element), 9, "green", "none", "3");
            line = createWall(x, y, getHydrantX(hydrantDists[i]->element), getHydrantY(hydrantDists[i]->element));

            printCircle(arqSvg, ring);
            printWall(arqSvg, line);

            destroyForm(ring);
            destroyWall(line);
        }
        else{
            break;
        }
    }
    fprintf(arqTxt, "\n\n");

    for(int i = 0; i < ntLights; i++)
        free(tLightDists[i]);
    free(tLightDists);

    for(int i = 0; i < nHydrants; i++)
        free(hydrantDists[i]);
    free(hydrantDists);
}

void getAddress(char cep[], char face[], int num, double *x, double *y, HashTable blocksTable){
    char type[4];

    Block block = searchHashTable(blocksTable, cep);

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

void treatFH(FILE *arqTxt, FILE *arqSvg, Tree hydrants, int k, double x, double y){
    int i, cont = 0, nHydrants = getSize(hydrants);
    Form ring;
    Wall line;

    DistImp *hydrantDists = (DistImp *) malloc(nHydrants * sizeof(DistImp));

    treeToListDists(x, y, hydrants, getTreeRoot(hydrants), hydrantDists, &cont, getHydrantX, getHydrantY);

    if(k < 0){
        k = -k;
        min_heap_sort((void *)hydrantDists, nHydrants - 1, k);
        fprintf(arqTxt, "Hidrantes mais próximos do endeço:\n");
    }
    else if(k > 0){
        max_heap_sort((void *)hydrantDists, nHydrants - 1, k);
        fprintf(arqTxt, "Hidrantes mais distantes do endeço:\n");
    }
    
    reverseVector((void *)hydrantDists, nHydrants - 1);

    for(i = 0; i < k; i++){
        fprintf(arqTxt, "%s ", getHydrantId(hydrantDists[i]->element));
        ring = createCircle("", getHydrantX(hydrantDists[i]->element), getHydrantY(hydrantDists[i]->element), 9, "green", "none", "3");
        line = createWall(x, y, getHydrantX(hydrantDists[i]->element), getHydrantY(hydrantDists[i]->element));

        printCircle(arqSvg, ring);
        printWall(arqSvg, line);

        destroyForm(ring);
        destroyWall(line);
    }
    fprintf(arqTxt, "\n\n");

    for(i = 0; i < nHydrants; i++){
        free(hydrantDists[i]);
    }
    free(hydrantDists);
}

void treatFS(FILE *arqTxt, FILE *arqSvg, Tree tLights, int k, double x, double y){
    int i, cont = 0, ntLights = getSize(tLights);
    Form ring;
    Wall line;

    DistImp *tLightDists = (DistImp *) malloc(ntLights * sizeof(DistImp));

    treeToListDists(x, y, tLights, getTreeRoot(tLights), tLightDists, &cont, getTrafficLightX, getTrafficLightY);

    min_heap_sort((void *)tLightDists, ntLights - 1, k);
    fprintf(arqTxt, "Semáforos mais próximos do endeço:\n");
    
    reverseVector((void *)tLightDists, ntLights - 1);

    for(i = 0; i < k; i++){
        fprintf(arqTxt, "%s ", getTrafficLightId(tLightDists[i]->element));
        ring = createCircle("", getTrafficLightX(tLightDists[i]->element), getTrafficLightY(tLightDists[i]->element), 9, "green", "none", "3");
        line = createWall(x, y, getTrafficLightX(tLightDists[i]->element), getTrafficLightY(tLightDists[i]->element));

        printCircle(arqSvg, ring);
        printWall(arqSvg, line);

        destroyForm(ring);
        destroyWall(line);
    }
    fprintf(arqTxt, "\n\n");

    for(i = 0; i < ntLights; i++){
        free(tLightDists[i]);
    }
    free(tLightDists);
}
