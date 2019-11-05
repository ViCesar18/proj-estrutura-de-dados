#include "queryBuildings.h"

void treatDQ(FILE *arqTxt, FILE *arqSvgQ, Tree blockRoot, char metric[], Form circle){
    Block block;
    Form ring1 = createCircle("0", getFormX(circle), getFormY(circle), 18, "green", "none", "5");
    Form ring2 = createCircle("0", getFormX(circle), getFormY(circle), 13, "lightgreen", "none", "5");

    fprintf(arqTxt, "dq %s %lf\n", metric, getFormR(circle));
    fprintf(arqTxt, "\tEquipamento Urbano: %s (%lf %lf)\n", getFormId(circle), getFormX(circle), getFormY(circle));
    printCircle(arqSvgQ, ring1);
    printCircle(arqSvgQ, ring2);

    free(ring1);
    free(ring2);

    block = getElement(blockRoot);

    if(!strcmp(metric, "L1")){
        if(quadInsideCirc(block, circle, "L1")){
            fprintf(arqTxt, "\tQuadra Removida: %s\n", getBlockCep(block));
            removeNode(blockRoot, block, comparatorBlock);
        }
        if(getLeft(blockRoot) != NULL)
            treatDQ(arqTxt, arqSvgQ, getLeft(blockRoot), metric, circle);
        if(getRight(blockRoot) != NULL)
        treatDQ(arqTxt, arqSvgQ, getRight(blockRoot), metric, circle);
    }
    else if(!strcmp(metric, "L2")){
        if(quadInsideCirc(getElement(blockRoot), circle, "L2")){
            block = getElement(blockRoot);
            fprintf(arqTxt, "\tQuadra Removida: %s\n", getBlockCep(block));
            removeNode(blockRoot, block, comparatorBlock);
        }
        if(getLeft(blockRoot) != NULL)
            treatDQ(arqTxt, arqSvgQ, getLeft(blockRoot), metric, circle);
        if(getRight(blockRoot) != NULL)
            treatDQ(arqTxt, arqSvgQ, getRight(blockRoot), metric, circle);
    }
}

void treatCBQ(FILE *arqTxt, Tree blockRoot, Form circle, char cstrk[]){
    Block block;
    
    fprintf(arqTxt, "cbq %lf %lf %lf %s\n", getFormX(circle), getFormY(circle), getFormR(circle), cstrk);

    block = getElement(blockRoot);
    if(quadInsideCirc(block, circle, "L2")){
        setBlockStrokeColor(block, cstrk);
        fprintf(arqTxt, "\tCor da borda da quadra alterada: %s\n", getBlockCep(block));
    }
    
    if(getLeft(blockRoot) != NULL)
        treatCBQ(arqTxt, getLeft(blockRoot), circle, cstrk);
    if(getRight(blockRoot) != NULL)
        treatCBQ(arqTxt, getLeft(blockRoot), circle, cstrk);
}

void treatTRNS_block(FILE *arqTxt, Tree blockRoot, Form rect, double dx, double dy, FILE *arqSvgQ){
    Block block;

    block = getElement(blockRoot);
    if(quadInsideRect(block, rect)){
        setBlockX(block, getBlockX(block) + dx);
        setBlockY(block, getBlockY(block) + dy);
    }

    if(getLeft(blockRoot) != NULL)
        treatTRNS_block(arqTxt, getLeft(blockRoot), rect, dx, dy, arqSvgQ);
    if(getRight(blockRoot) != NULL)
        treatTRNS_block(arqTxt, getRight(blockRoot), rect, dx, dy, arqSvgQ);
}

void treatTRNS_hydrant(FILE *arqTxt, Tree hydrantRoot, Form rect, double dx, double dy, FILE *arqSvgQ){
    Hydrant hydrant;

    hydrant = getElement(hydrantRoot);
    if(pointInsideFigure(getHydrantX(hydrant), getHydrantY(hydrant), rect, "r", "L2")){
        setHydrantX(hydrant, getHydrantX(hydrant) + dx);
        setHydrantY(hydrant, getHydrantY(hydrant) + dy);
    }

    if(getLeft(hydrantRoot) != NULL)
        treatTRNS_hydrant(arqTxt, getLeft(hydrantRoot), rect, dx, dy, arqSvgQ);
    if(getRight(hydrantRoot) != NULL)
        treatTRNS_hydrant(arqTxt, getRight(hydrantRoot), rect, dx, dy, arqSvgQ);
}

void treatTRNS_tLight(FILE *arqTxt, Tree tLightRoot, Form rect, double dx, double dy, FILE *arqSvgQ){
    TrafficLight tLight;

    tLight = getElement(tLightRoot);
    if(pointInsideFigure(getHydrantX(tLight), getHydrantY(tLight), rect, "r", "L2")){
        setHydrantX(tLight, getTrafficLightX(tLight) + dx);
        setHydrantY(tLight, getTrafficLightY(tLight) + dy);
    }

    if(getLeft(tLightRoot) != NULL)
        treatTRNS_tLight(arqTxt, getLeft(tLightRoot), rect, dx, dy, arqSvgQ);
    if(getRight(tLightRoot) != NULL)
        treatTRNS_tLight(arqTxt, getRight(tLightRoot), rect, dx, dy, arqSvgQ);
}

void treatTRNS_rTower(FILE *arqTxt, Tree rTowerRoot, Form rect, double dx, double dy, FILE *arqSvgQ){
    RadioTower rTower;

    rTower = getElement(rTowerRoot);
    if(pointInsideFigure(getHydrantX(rTower), getHydrantY(rTower), rect, "r", "L2")){
        setHydrantX(rTower, getRadioTowerX(rTower) + dx);
        setHydrantY(rTower, getRadioTowerY(rTower) + dy);
    }

    if(getLeft(rTowerRoot) != NULL)
        treatTRNS_rTower(arqTxt, getLeft(rTowerRoot), rect, dx, dy, arqSvgQ);
    if(getRight(rTowerRoot) != NULL)
        treatTRNS_rTower(arqTxt, getRight(rTowerRoot), rect, dx, dy, arqSvgQ);
}

typedef struct stDist{
    Element *element;
    double dist;
} *DistImp;

double getDist(Dist distAux){
    DistImp dist = (DistImp) distAux;

    return dist->dist;
}

void treeToListDists(double x, double y, Tree root, Dist lD, int *cont, double getX(Element), double getY(Element)){
    Element element;
    DistImp* listDists = (DistImp*) lD;

    element = getElement(root);

    listDists[*cont] = (DistImp) malloc(sizeof(struct stDist));
    listDists[*cont]->element = element;
    listDists[*cont]->dist = distEuclid(x, y, getX(element), getY(element));

    (*cont)++;

    if(getLeft(root) != NULL)
        treeToListDists(x, y, getLeft(root), &listDists, &(*cont), getX, getY);
    if(getRight(root) != NULL)
        treeToListDists(x, y, getRight(root), &listDists, &(*cont), getX, getY);

}

void treatFI(FILE *arqSvg, FILE *arqTxt, Tree auxTree, double x, double y, int ns, double r, Tree tLightRoot, Tree hydrantRoot){
    Form ring;
    Wall line;
    double dist;
    int cont = 0, ntLights = 0;;

    nNodes(tLightRoot, &ntLights);

    DistImp *tLightDists = (DistImp *) malloc(ntLights * sizeof(DistImp));

    printFire(arqSvg, x, y);

    treeToListDists(x, y, tLightRoot, &tLightDists, &cont, getTrafficLightX, getTrafficLightY);

    min_heap_sort((void *) tLightDists, ntLights - 1, ns);
    reverseVector((void *) tLightDists, ntLights - 1);

    Hydrant hydrant;
    int nHydrants = 0;

    nNodes(hydrantRoot, &nHydrants);

    DistImp *hydrantDists = (DistImp *) malloc(nHydrants * sizeof(DistImp));
    cont = 0;

    treeToListDists(x, y, hydrantRoot, &hydrantDists, &cont, getHydrantX, getHydrantY);

    min_heap_sort((void *) hydrantDists, nHydrants - 1, nHydrants);
    reverseVector((void *) hydrantDists, nHydrants - 1);

    fprintf(arqTxt, "Incêndio em %lf %lf!\n", x, y);
    fprintf(arqTxt, "Semáforos com a programação alterada:\n");
    for(int i = 0; i < ns; i++){
        fprintf(arqTxt, "%s ", getTrafficLightId(tLightDists[i]->element));
        ring = createCircle("", getTrafficLightX(tLightDists[i]->element), getTrafficLightY(tLightDists[i]->element), 9, "green", "none", "3");
        line = createWall(x, y, getTrafficLightX(tLightDists[i]->element), getTrafficLightY(tLightDists[i]->element));

        insertNode(auxTree, ring, comparatorForm);
        insertNode(auxTree, line, comparatorWall);
    }
    
    fprintf(arqTxt, "\n\nHidrantes ativados:\n");
    for(int i = 0; i < nHydrants; i++){
        if(hydrantDists[i]->dist <= r){
            fprintf(arqTxt, "%s ", getHydrantId(hydrantDists[i]->element));
            ring = createCircle("", getHydrantX(hydrantDists[i]->element), getHydrantY(hydrantDists[i]->element), 9, "green", "none", "3");
            line = createWall(x, y, getHydrantX(hydrantDists[i]->element), getHydrantY(hydrantDists[i]->element));

            insertNode(&auxTree, ring, comparatorForm);
            insertNode(&auxTree, line, comparatorWall);
        }
        else{
            break;
        }
    }
    fprintf(arqTxt, "\n\n");

    for(int i = 0; i < ntLights; i++){
        free(tLightDists[i]);
    }
    free(tLightDists);

    for(int i = 0; i < nHydrants; i++){
        free(hydrantDists[i]);
    }
    free(hydrantDists);
}

void getAddress(char cep[], char face[], int num, double *x, double *y, Tree blockRoot){
    Block block;
    char type[4];

    block = getElementById(blockRoot, cep);

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

void treatFH(FILE *arqTxt, FILE *arqSvg, Tree hydrantRoot, int k, double x, double y, Tree auxTree){
    int i, cont = 0, nHydrants = 0;
    Form ring;
    Wall line;

    nNodes(hydrantRoot, &nHydrants);

    DistImp *hydrantDists = (DistImp *) malloc(nHydrants * sizeof(DistImp));

    treeToListDists(x, y, hydrantRoot, &hydrantDists, &cont, getHydrantX, getHydrantY);

    if(k < 0){
        k *= -1;
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

        insertNode(&auxTree, ring, comparatorForm);
        insertNode(&auxTree, line, comparatorWall);
    }
    fprintf(arqTxt, "\n\n");

    for(i = 0; i < nHydrants; i++){
        free(hydrantDists[i]);
    }
    free(hydrantDists);
}

void treatFS(FILE *arqTxt, FILE *arqSvg, Tree tLightRoot, int k, double x, double y, Tree auxTree){
    int i, cont = 0, ntLights = 0;
    Form ring;
    Wall line;

    nNodes(tLightRoot, &ntLights);

    DistImp *tLightDists = (DistImp *) malloc(ntLights * sizeof(DistImp));

    treeToListDists(x, y, tLightRoot, &tLightDists, &cont, getTrafficLightX, getTrafficLightY);

    min_heap_sort((void *)tLightDists, ntLights - 1, k);
    fprintf(arqTxt, "Semáforos mais próximos do endeço:\n");
    
    reverseVector((void *)tLightDists, ntLights - 1);

    for(i = 0; i < k; i++){
        fprintf(arqTxt, "%s ", getTrafficLightId(tLightDists[i]->element));
        ring = createCircle("", getTrafficLightX(tLightDists[i]->element), getTrafficLightY(tLightDists[i]->element), 9, "green", "none", "3");
        line = createWall(x, y, getTrafficLightX(tLightDists[i]->element), getTrafficLightY(tLightDists[i]->element));

        insertNode(&auxTree, ring, comparatorForm);
        insertNode(&auxTree, line, comparatorWall);
    }
    fprintf(arqTxt, "\n\n");

    for(i = 0; i < ntLights; i++){
        free(tLightDists[i]);
    }
    free(tLightDists);
}