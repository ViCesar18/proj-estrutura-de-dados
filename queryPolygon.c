#include "queryPolygon.h"

void treatMPLG_blocks(Tree blocks, Node node, Polygon polygon){
    if(node == getNil(blocks)) return;

    treatMPLG_blocks(blocks, getLeft(blocks, node), polygon);

    Block block = getElement(blocks, node);
    Point p1 = createPoint(getBlockX(block), getBlockY(block));
    Point p2 = createPoint(getBlockX(block) + getBlockW(block), getBlockY(block));
    Point p3 = createPoint(getBlockX(block), getBlockY(block) + getBlockH(block));
    Point p4 = createPoint(getBlockX(block) + getBlockW(block), getBlockY(block) + getBlockH(block));
    
    if(pointInsidePolygon(p1, polygon) || pointInsidePolygon(p2, polygon) || pointInsidePolygon(p3, polygon) || pointInsidePolygon(p4, polygon)){
        setBlockSW(block, "5");
    }

    treatMPLG_blocks(blocks, getRight(blocks, node), polygon);
}

void treatMPLG_buildings(Tree buildings, Node node, Polygon polygon){
    if(node == getNil(buildings)) return;

    treatMPLG_buildings(buildings, getLeft(buildings, node), polygon);

    Building building = getElement(buildings, node);
    Point p1 = createPoint(getBuildingX(building), getBuildingY(building));
    Point p2 = createPoint(getBuildingX(building) + getBuildingW(building), getBuildingY(building));
    Point p3 = createPoint(getBuildingX(building), getBuildingY(building) + getBuildingH(building));
    Point p4 = createPoint(getBuildingX(building) + getBuildingW(building), getBuildingY(building) + getBuildingH(building));

    Segment s1 = createSegment(createVertex(p1, 0, 0), createVertex(p2, 0, 0));
    Segment s2 = createSegment(createVertex(p2, 0, 0), createVertex(p3, 0, 0));
    Segment s3 = createSegment(createVertex(p3, 0, 0), createVertex(p4, 0, 0));
    Segment s4 = createSegment(createVertex(p4, 0, 0), createVertex(p1, 0, 0));

    bool entirelyIn = true;

    if(pointInsidePolygon(p1, polygon) && pointInsidePolygon(p2, polygon) && pointInsidePolygon(p3, polygon) && pointInsidePolygon(p4, polygon)){
        for(Segment aux = getPolygonFirstSegment(polygon); aux != NULL; aux = getSegmentProx(aux)){
            if(checkSegmentsIntersection(s1, aux) || checkSegmentsIntersection(s2, aux) 
            || checkSegmentsIntersection(s3, aux), checkSegmentsIntersection(s4, aux)){
                entirelyIn = false;
                break;
            }
        }

        if(entirelyIn){
            setBuildingFillCollor(building, "black");
        }
    }

    treatMPLG_buildings(buildings, getRight(buildings, node), polygon);
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

    treatMPLG_blocks(blocks, getTreeRoot(blocks), polygon);

    treatMPLG_buildings(buildings, getTreeRoot(buildings), polygon);

    destroyPolygon(polygon);
}