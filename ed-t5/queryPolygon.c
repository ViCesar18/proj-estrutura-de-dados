#include "queryPolygon.h"

void treatBRN(FILE *arqSVG, FILE *arqText, char *pathIn, double x, double y, Tree walls, Tree buildings, char *nPol, HashTable residents){
    Polygon polygon = createPolygon();
    bombAreaRadiation(arqSVG, polygon, x, y, walls, buildings, true);

    fprintf(arqSVG, "<polygon points=\"");
    for(Segment aux = getPolygonFirstSegment(polygon); aux != NULL; aux = getSegmentProx(aux))
        fprintf(arqSVG, "%lf,%lf ", getPointX(getVertexV(getSegmentV1(aux))), getPointY(getVertexV(getSegmentV1(aux))));
    fprintf(arqSVG, "\" opacity=\"0.5\" style=\"fill:lime;stroke:purple;stroke-width:1\" />");

    char *fDirectory;
    FILE *pFile;

    if(pathIn != NULL){
        allocateFileMamory(nPol, pathIn, &fDirectory);
        pFile = fopen(fDirectory, "w");
        free(fDirectory);
        checkFile(pFile, fDirectory);
    }
    else{
        pFile = fopen(nPol, "w");
        checkFile(pFile, nPol);
    }

    for(Segment aux = getPolygonFirstSegment(polygon); aux != NULL; aux = getSegmentProx(aux)){
        fprintf(pFile, "%lf %lf\n", getPointX(getVertexV(getSegmentV1(aux))), getPointY(getVertexV(getSegmentV1(aux))));
    }
    fclose(pFile);

    fprintf(arqText, "Área e Moradores afetados pela Bomba de Radiação Luminosa:\n");

    for(int i = 0; i < getHashTableSize(residents); i++){
        ListNode node = getHashNode(residents, i);
        while(node != NULL){
            Resident resident = getHashNodeElement(node);
            Point p = createPoint(getResidentX(resident), getResidentY(resident));

            if(pointInsidePolygon(p, polygon)){
                Person person = getResidentPerson(resident);
                fprintf(arqText, "\tMorador: %s %s\n\tCPF: %s\n\n", getPersonName(person), getPersonLastName(person), getPersonCpf(person));
            }
            freePoint(p);
            node = getHashNodeNext(node);
        }
    }
}

void treatMPLG_blocks(FILE *arqSvg, Tree blocks, Node node, Polygon polygon){
    if(node == getNil(blocks)) return;

    treatMPLG_blocks(arqSvg, blocks, getLeft(blocks, node), polygon);

    Block block = getElement(blocks, node);
    Point p1 = createPoint(getBlockX(block), getBlockY(block));
    Point p2 = createPoint(getBlockX(block) + getBlockW(block), getBlockY(block));
    Point p3 = createPoint(getBlockX(block), getBlockY(block) + getBlockH(block));
    Point p4 = createPoint(getBlockX(block) + getBlockW(block), getBlockY(block) + getBlockH(block));
    
    if(pointInsidePolygon(p1, polygon) || pointInsidePolygon(p2, polygon) || pointInsidePolygon(p3, polygon) || pointInsidePolygon(p4, polygon)){
        setBlockSW(block, "5");

        HashTable residents = getBlockResidents(block);
        int cont = 0;
        for(int i = 0; i < getHashTableSize(residents); i++){
            ListNode node = getHashNode(residents, i);
            while(node != NULL){
                cont++;
                node = getHashNodeNext(node);
            }
        }
        char nResidents[64];
        sprintf(nResidents, "Moradores: %d", cont);
        printText(arqSvg, getBlockX(block) + 38, getBlockY(block) + 22, nResidents, getBlockStrokeColor(block));
    }

    freePoint(p1);
    freePoint(p2);
    freePoint(p3);
    freePoint(p4);

    treatMPLG_blocks(arqSvg, blocks, getRight(blocks, node), polygon);
}

void treatMPLG_buildings(FILE *arqTxt, Tree buildings, Node node, Polygon polygon){
    if(node == getNil(buildings)) return;

    treatMPLG_buildings(arqTxt, buildings, getLeft(buildings, node), polygon);

    Building building = getElement(buildings, node);
    Form rect = createRect("", getBuildingX(building), getBuildingY(building), getBuildingW(building), getBuildingH(building), "", "", 0, "");
    if(rectInsidePolygon(rect, polygon) && getBuildingNResidents(building) > 0){
        setBuildingFillCollor(building, "yellow");
        HashTable residents = getBuildingResidents(building);
        
        for(int i = 0; i < getHashTableSize(residents); i++){
            ListNode node = getHashNode(residents, i);
            while(node != NULL){
                Resident resident = getHashNodeElement(node);
                Person person = getResidentPerson(resident);

                fprintf (arqTxt, "-%s %s:\n\tCPF: %s\n\tSexo: %s\n\tNascimento: %s\n\tCEP: %s, Face: %s, Número: %d, Complemento: %s\n", getPersonName (person), getPersonLastName(person), getPersonCpf (person), getPersonSexo (person), getPersonNascimento(person), getResidentCep (resident), getResidentFace(resident), getResidentNum (resident), getResidentCompl (resident));
                
                node = getHashNodeNext(node);
            }
        }
    }
    destroyForm(rect);

    treatMPLG_buildings(arqTxt, buildings, getRight(buildings, node), polygon);
}

void treatMPLG(FILE *arqSVG, FILE *arqTxt, char *fName, char *pathIn, Tree blocks, Tree buildings){
    double x, y;
    
    char *fDirectory;
    FILE *pFile;

    if(pathIn != NULL){
        allocateFileMamory(fName, pathIn, &fDirectory);
        pFile = fopen(fDirectory, "r");
        free(fDirectory);
        checkFile(pFile, fDirectory);
    }
    else{
        pFile = fopen(fName, "r");
        checkFile(pFile, fName);
    }

    Polygon polygon = createPolygon();
    while(1){
        fscanf(pFile, "%lf", &x);
        fscanf(pFile, "%lf", &y);

        insertPointPolygon(polygon, x, y);

        if(feof(pFile)) break;
    }
    fclose(pFile);
    connectPolygon(polygon);

    fprintf(arqSVG, "<polygon points=\"");
    for(Segment aux = getPolygonFirstSegment(polygon); aux != NULL; aux = getSegmentProx(aux))
        fprintf(arqSVG, "%lf,%lf ", getPointX(getVertexV(getSegmentV1(aux))), getPointY(getVertexV(getSegmentV1(aux))));
    fprintf(arqSVG, "\" opacity=\"0.5\" style=\"fill:lime;stroke:purple;stroke-width:1\" />");

    treatMPLG_blocks(arqSVG, blocks, getTreeRoot(blocks), polygon);

    fprintf (arqTxt, "mplg? Moradores dos prédios inteiramente contidos no poligono:\n");
    treatMPLG_buildings(arqTxt, buildings, getTreeRoot(buildings), polygon);

    destroyPolygon(polygon);
}

void treatEPLG(FILE *arqSVG, FILE *arqTxt, char *fName, char *codt, char *pathIn, HashTable stores){
    double x, y;
    
    char *fDirectory;
    FILE *pFile;

    if(pathIn != NULL){
        allocateFileMamory(fName, pathIn, &fDirectory);
        pFile = fopen(fDirectory, "r");
        free(fDirectory);
        checkFile(pFile, fDirectory);
    }
    else{
        pFile = fopen(fName, "r");
        checkFile(pFile, fName);
    }

    Polygon polygon = createPolygon();
    while(1){
        fscanf(pFile, "%lf", &x);
        fscanf(pFile, "%lf", &y);

        insertPointPolygon(polygon, x, y);

        if(feof(pFile)) break;
    }
    fclose(pFile);
    connectPolygon(polygon);

    fprintf(arqSVG, "<polygon points=\"");
    for(Segment aux = getPolygonFirstSegment(polygon); aux != NULL; aux = getSegmentProx(aux))
        fprintf(arqSVG, "%lf,%lf ", getPointX(getVertexV(getSegmentV1(aux))), getPointY(getVertexV(getSegmentV1(aux))));
    fprintf(arqSVG, "\" opacity=\"0.5\" style=\"fill:lime;stroke:purple;stroke-width:1\" />");

    fprintf (arqTxt, "eplg? Estabelecimentos comerciais do tipo %s inteiramente contidos no poligono:\n", codt);

    for(int i = 0; i < getHashTableSize(stores); i++){
        ListNode node = getHashNode(stores, i);
        while(node != NULL){
            Store store = getHashNodeElement(node);
            Person owner = getStoreOwner(store);
            StoreType sType = getStoreStoreType(store);

            if(!strcmp(codt, "*")){
                Point p  = createPoint(getStoreX(store), getStoreY(store));
                if(pointInsidePolygon(p, polygon)){
                    Block block = getStoreBlock(store);

                    fprintf (arqTxt, "-%s:\n\tCNPJ: %s\n\tTipo: %s\n\tProprietário: %s %s\n\tCPF: %s\n\tCEP: %s, Face: %s, Número: %d\n\n", getStoreName(store), getStoreCnpj(store), getStoreTypeCodt(sType),getPersonName(owner), getPersonLastName(owner), getPersonCpf(owner), getStoreCep(store), getStoreFace(store), getStoreNum(store));

                    setBlockFillColor(block, "yellow");

                    Form circle = createCircle("", getStoreX(store), getStoreY(store), 5, "red", "none", "2");
                    printCircle(arqSVG, circle);
                    free(circle);
                }
                freePoint(p);
            }
            else{
                if(!strcmp(codt, getStoreTypeCodt(getStoreStoreType(store)))){
                    Point p  = createPoint(getStoreX(store), getStoreY(store));

                    if(pointInsidePolygon(p, polygon)){
                        Block block = getStoreBlock(store);
                        fprintf (arqTxt, "-%s:\n\tCNPJ: %s\n\tTipo: %s\n\tProprietário: %s %s\n\tCPF: %s\n\tCEP: %s, Face: %s, Número: %d\n\n", getStoreName(store), getStoreCnpj(store), getStoreTypeCodt(sType),getPersonName(owner), getPersonLastName(owner), getPersonCpf(owner), getStoreCep(store), getStoreFace(store), getStoreNum(store));
                        setBlockFillColor(block, "yellow");

                        Form circle = createCircle("", getStoreX(store), getStoreY(store), 5, "red", "none", "2");
                        printCircle(arqSVG, circle);
                        free(circle);
                    }
                    freePoint(p);
                }
            }

            node = getHashNodeNext(node);
        }
    }

    destroyPolygon(polygon);
}

int static counterDeletedElements = 0;

void treatCATAC_blocks(FILE *arqTxt, Tree blocks, Node node, HashTable blocksTable, Polygon polygon, Block deletedBlocks[]){
    if(node == getNil(blocks)) return;
    
    treatCATAC_blocks(arqTxt, blocks, getLeft(blocks, node), blocksTable, polygon, deletedBlocks);

    treatCATAC_blocks(arqTxt, blocks, getRight(blocks, node), blocksTable, polygon, deletedBlocks);

    Block block = getElement(blocks, node);
    Form rect = createRect("", getBlockX(block), getBlockY(block), getBlockW(block), getBlockH(block), "", "", 0, "");

    if(rectInsidePolygon(rect, polygon)){
        fprintf(arqTxt, "\t-Quadra removida: %s\n", getBlockCep(block));
        deletedBlocks[counterDeletedElements] = block;
        counterDeletedElements++;
    }

    destroyForm(rect);
}

void treatCATAC_hydrants(FILE *arqTxt, Tree hydrants, Node node, HashTable hydrantsTable, Polygon polygon, Hydrant deletedHydrants[]){
    if(node == getNil(hydrants)) return;

    treatCATAC_hydrants(arqTxt, hydrants, getLeft(hydrants, node), hydrantsTable, polygon, deletedHydrants);
    
    Hydrant hydrant = getElement(hydrants, node);
    Point p = createPoint(getHydrantX(hydrant), getHydrantY(hydrant));
    if(pointInsidePolygon(p, polygon)){
        fprintf(arqTxt, "\t-Hidrante removido: %s\n", getHydrantId(hydrant));
        deletedHydrants[counterDeletedElements] = hydrant;
        counterDeletedElements++;
    }

    treatCATAC_hydrants(arqTxt, hydrants, getRight(hydrants, node), hydrantsTable, polygon, deletedHydrants);

    freePoint(p);
}

void treatCATAC_tLights(FILE *arqTxt, Tree tLights, Node node, HashTable tLightsTable, Polygon polygon, TrafficLight deletedTLights[]){
    if(node == getNil(tLights)) return;

    treatCATAC_tLights(arqTxt, tLights, getLeft(tLights, node), tLightsTable, polygon, deletedTLights);

    treatCATAC_tLights(arqTxt, tLights, getRight(tLights, node), tLightsTable, polygon, deletedTLights);

    TrafficLight tLight = getElement(tLights, node);
    Point p = createPoint(getTrafficLightX(tLight), getTrafficLightY(tLight));
    if(pointInsidePolygon(p, polygon)){
        fprintf(arqTxt, "\t-Semáforo removido: %s\n", getTrafficLightId(tLight));
        deletedTLights[counterDeletedElements] = tLight;
        counterDeletedElements++;
    }

    freePoint(p);
}

void treatCATAC_rTowers(FILE *svg, FILE *arqTxt, Tree rTowers, Node node, HashTable rTowersTable, Polygon polygon, RadioTower deletedRTowers[]){
    if(node == getNil(rTowers)) return;

    treatCATAC_rTowers(svg, arqTxt, rTowers, getLeft(rTowers, node), rTowersTable, polygon, deletedRTowers);

    treatCATAC_rTowers(svg, arqTxt, rTowers, getRight(rTowers, node), rTowersTable, polygon, deletedRTowers);

    RadioTower rTower = getElement(rTowers, node);
    Point p = createPoint(getRadioTowerX(rTower), getRadioTowerY(rTower));
    
    //printLine(svg, getRadioTowerX(rTower), getRadioTowerY(rTower), getPolygonXMax(polygon) + 1, getRadioTowerY(rTower), "black");
    if(pointInsidePolygon(p, polygon)){
        fprintf(arqTxt, "\t-Torre de Rádio removida: %s\n", getRadioTowerId(rTower));
        deletedRTowers[counterDeletedElements] = rTower;
        counterDeletedElements++;
    }

    freePoint(p);
}

void treatCATAC_buildings(FILE *arqSVG, FILE *arqTxt, Tree buildings, Node node, HashTable buildingsTable, Polygon polygon, Building deletedBuildings[]){
    if(node == getNil(buildings)) return;
    
    treatCATAC_buildings(arqSVG, arqTxt, buildings, getLeft(buildings, node), buildingsTable, polygon, deletedBuildings);

    treatCATAC_buildings(arqSVG, arqTxt, buildings, getRight(buildings, node), buildingsTable, polygon, deletedBuildings);

    Building building = getElement(buildings, node);
    Form rect = createRect("", getBuildingX(building), getBuildingY(building), getBuildingW(building), getBuildingH(building), "", "", 0, "");

    if(rectInsidePolygon(rect, polygon)){
        printLine(arqSVG, getBuildingX(building), getBuildingY(building), getBuildingX(building) + getBuildingW(building), getBuildingY(building) + getBuildingH(building), "red");
        printLine(arqSVG, getBuildingX(building) + getBuildingW(building), getBuildingY(building), getBuildingX(building), getBuildingY(building) + getBuildingH(building), "red");
        char nResidents[8];
        sprintf(nResidents, "%d", getBuildingNResidents(building));
        printText(arqSVG, getBuildingX(building) + getBuildingW(building) / 2, getBuildingY(building), nResidents, "black");

        fprintf(arqTxt, "\t-Prédio removido: %s, %s, %d\n", getBuildingCep(building), getBuildingFace(building), getBuildingNum(building));
        deletedBuildings[counterDeletedElements] = building;
        counterDeletedElements++;
    }

    destroyForm(rect);
}

void treatCATAC(FILE *arqSVG, FILE *arqTxt, char *fName, char *pathIn, Tree blocks, Tree hydrants, Tree tLights, 
                Tree rTowers, Tree buildings, HashTable blocksTable, HashTable hydrantsTable, HashTable tLightsTable, HashTable rTowersTable, 
                HashTable buildingsTable, HashTable residents){
    double x, y;

    char *fDirectory;
    FILE *pFile;

    if(pathIn != NULL){
        allocateFileMamory(fName, pathIn, &fDirectory);
        pFile = fopen(fDirectory, "r");
        free(fDirectory);
        checkFile(pFile, fDirectory);
    }
    else{
        pFile = fopen(fName, "r");
        checkFile(pFile, fName);
    }

    Polygon polygon = createPolygon();
    while(1){
        fscanf(pFile, "%lf", &x);
        fscanf(pFile, "%lf", &y);

        insertPointPolygon(polygon, x, y);

        if(feof(pFile)) break;
    }
    fclose(pFile);
    connectPolygon(polygon);

    fprintf(arqSVG, "<polygon points=\"");
    for(Segment aux = getPolygonFirstSegment(polygon); aux != NULL; aux = getSegmentProx(aux))
        fprintf(arqSVG, "%lf,%lf ", getPointX(getVertexV(getSegmentV1(aux))), getPointY(getVertexV(getSegmentV1(aux))));
    fprintf(arqSVG, "\" opacity=\"0.5\" style=\"fill:lime;stroke:purple;stroke-width:1\" />");

    fprintf(arqTxt, "Cataclisma na área do polígono %s!!!\n", fName);

    counterDeletedElements = 0;
    Block *deletedBlocks = malloc(getSize(blocks) * sizeof(Block));
    treatCATAC_blocks(arqTxt, blocks, getTreeRoot(blocks), blocksTable, polygon, deletedBlocks);
    for(int i = 0; i < counterDeletedElements; i++) deleteBlock(deletedBlocks[i], blocks, blocksTable);
    free(deletedBlocks);

    counterDeletedElements = 0;
    Hydrant *deletedHydrants = malloc(getSize(hydrants) * sizeof(Hydrant));
    treatCATAC_hydrants(arqTxt, hydrants, getTreeRoot(hydrants), hydrantsTable, polygon, deletedHydrants);
    for(int i = 0; i < counterDeletedElements; i++) deleteHydrant(deletedHydrants[i], hydrants, hydrantsTable);
    free(deletedHydrants);

    counterDeletedElements = 0;
    TrafficLight *deletedTLights = malloc(getSize(tLights) * sizeof(TrafficLight));
    treatCATAC_tLights(arqTxt, tLights, getTreeRoot(tLights), tLightsTable, polygon, deletedTLights);
    for(int i = 0; i < counterDeletedElements; i++) deleteTrafficLight(deletedTLights[i], tLights, tLightsTable);
    free(deletedTLights);

    counterDeletedElements = 0;
    RadioTower *deletedRTowers = malloc(getSize(rTowers) * sizeof(RadioTower));
    treatCATAC_rTowers(arqSVG, arqTxt, rTowers, getTreeRoot(rTowers), rTowersTable, polygon, deletedRTowers);
    for(int i = 0; i < counterDeletedElements; i++) deleteRadioTower(deletedRTowers[i], rTowers, rTowersTable);
    free(deletedRTowers);

    counterDeletedElements = 0;
    Building *deletedBuildings = malloc(getSize(buildings) * sizeof(Building));
    treatCATAC_buildings(arqSVG, arqTxt, buildings, getTreeRoot(buildings), buildingsTable, polygon, deletedBuildings);
    for(int i = 0; i < counterDeletedElements; i++) deleteBuilding(deletedBuildings[i], buildings, buildingsTable);
    free(deletedBuildings);

    destroyPolygon(polygon);
}