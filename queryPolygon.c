#include "queryPolygon.h"

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
    Point p11 = createPoint(getBuildingX(building), getBuildingY(building));
    Point p12 = createPoint(getBuildingX(building), getBuildingY(building));
    Point p21 = createPoint(getBuildingX(building) + getBuildingW(building), getBuildingY(building));
    Point p22 = createPoint(getBuildingX(building) + getBuildingW(building), getBuildingY(building));
    Point p31 = createPoint(getBuildingX(building), getBuildingY(building) + getBuildingH(building));
    Point p32 = createPoint(getBuildingX(building), getBuildingY(building) + getBuildingH(building));
    Point p41 = createPoint(getBuildingX(building) + getBuildingW(building), getBuildingY(building) + getBuildingH(building));
    Point p42 = createPoint(getBuildingX(building) + getBuildingW(building), getBuildingY(building) + getBuildingH(building));

    Segment s1 = createSegment(createVertex(p11, 0, 0), createVertex(p21, 0, 0));
    Segment s2 = createSegment(createVertex(p22, 0, 0), createVertex(p31, 0, 0));
    Segment s3 = createSegment(createVertex(p32, 0, 0), createVertex(p41, 0, 0));
    Segment s4 = createSegment(createVertex(p42, 0, 0), createVertex(p12, 0, 0));

    bool entirelyIn = true;

    if(pointInsidePolygon(p11, polygon) && pointInsidePolygon(p21, polygon) && pointInsidePolygon(p31, polygon) && pointInsidePolygon(p41, polygon)){
        for(Segment aux = getPolygonFirstSegment(polygon); aux != NULL; aux = getSegmentProx(aux)){
            if(checkSegmentsIntersection(s1, aux) || checkSegmentsIntersection(s2, aux) 
            || checkSegmentsIntersection(s3, aux), checkSegmentsIntersection(s4, aux)){
                entirelyIn = false;
                break;
            }
        }

        if(entirelyIn && getBuildingNResidents(building) > 0){
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
    }

    freeSegment(s1);
    freeSegment(s2);
    freeSegment(s3);
    freeSegment(s4);

    treatMPLG_buildings(arqTxt, buildings, getRight(buildings, node), polygon);
}

void treatMPLG(FILE *arqSVG, FILE *arqTxt, char *fName, char *pathIn, Tree blocks, Tree buildings){
    double x1, y1, x2, y2;
    bool first = true, verify = true;
    Segment s1, s2;
    Polygon polygon;
    Segment aux;
    
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

    while(1){
        if(first){
            fscanf(pFile, "%lf", &x1);
            fscanf(pFile, "%lf", &y1);
        }
        fscanf(pFile, "%lf", &x2);
        fscanf(pFile, "%lf", &y2);

        if(verify){
            s1 = createSegment(createVertex(createPoint(x1, y1), 0, 0), createVertex(createPoint(x2, y2), 0, 0));
            if(first){
                polygon = createPolygon(s1);
                first = false;
            }
            else{
                setSegmentProx(s2, s1);
            }
            verify = false;
        }
        else{
            s2 = createSegment(createVertex(createPoint(x1, y1), 0, 0), createVertex(createPoint(x2, y2), 0, 0));
            setSegmentProx(s1, s2);
            verify = true;
        }

        x1 = x2;
        y1 = y2;

        if(feof(pFile)) break;
    }
    fclose(pFile);

    double xMax = getPointX(getVertexV(getSegmentV1(getPolygonFirstSegment(polygon))));

    fprintf(arqSVG, "<polygon points=\"");
    for(Segment aux = getPolygonFirstSegment(polygon); aux != NULL; aux = getSegmentProx(aux)){
        fprintf(arqSVG, "%lf,%lf ", getPointX(getVertexV(getSegmentV1(aux))), getPointY(getVertexV(getSegmentV1(aux))));

        if(getPointX(getVertexV(getSegmentV1(aux))) > xMax) xMax = getPointX(getVertexV(getSegmentV1(aux)));
    }
    fprintf(arqSVG, "\" opacity=\"0.5\" style=\"fill:lime;stroke:purple;stroke-width:1\" />");

    setPolygonXMax(polygon, xMax);

    treatMPLG_blocks(arqSVG, blocks, getTreeRoot(blocks), polygon);

    fprintf (arqTxt, "mplg? Moradores dos prédios inteiramente contidos no poligono:\n");
    treatMPLG_buildings(arqTxt, buildings, getTreeRoot(buildings), polygon);

    destroyPolygon(polygon);
}

void treatEPLG(FILE *arqSVG, FILE *arqTxt, char *fName, char *codt, char *pathIn, HashTable stores){
    double x1, y1, x2, y2;
    bool first = true, verify = true;
    Segment s1, s2;
    Polygon polygon;
    Segment aux;
    
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

    while(1){
        if(first){
            fscanf(pFile, "%lf", &x1);
            fscanf(pFile, "%lf", &y1);
        }
        fscanf(pFile, "%lf", &x2);
        fscanf(pFile, "%lf", &y2);

        if(verify){
            s1 = createSegment(createVertex(createPoint(x1, y1), 0, 0), createVertex(createPoint(x2, y2), 0, 0));
            if(first){
                polygon = createPolygon(s1);
                first = false;
            }
            else{
                setSegmentProx(s2, s1);
            }
            verify = false;
        }
        else{
            s2 = createSegment(createVertex(createPoint(x1, y1), 0, 0), createVertex(createPoint(x2, y2), 0, 0));
            setSegmentProx(s1, s2);
            verify = true;
        }

        x1 = x2;
        y1 = y2;

        if(feof(pFile)) break;
    }
    fclose(pFile);

    double xMax = getPointX(getVertexV(getSegmentV1(getPolygonFirstSegment(polygon))));

    fprintf(arqSVG, "<polygon points=\"");
    for(Segment aux = getPolygonFirstSegment(polygon); aux != NULL; aux = getSegmentProx(aux)){
        fprintf(arqSVG, "%lf,%lf ", getPointX(getVertexV(getSegmentV1(aux))), getPointY(getVertexV(getSegmentV1(aux))));

        if(getPointX(getVertexV(getSegmentV1(aux))) > xMax) xMax = getPointX(getVertexV(getSegmentV1(aux)));
    }
    fprintf(arqSVG, "\" opacity=\"0.5\" style=\"fill:lime;stroke:purple;stroke-width:1\" />");

    setPolygonXMax(polygon, xMax);

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