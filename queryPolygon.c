#include "queryPolygon.h"

void treatMPLG(FILE *arqSVG, FILE *arqTxt, char *fileDirectory){
    FILE *pFile = fopen("in/e1.pol", "r");
    double x1, y1, x2, y2;
    bool first = true, verify = true;
    Segment s1, s2;
    Polygon polygon;

    while(1){
        if(first){
            fscanf(pFile, "%lf", &x1);
            fscanf(pFile, "%lf", &y1);
        }
        fscanf(pFile, "%lf", &x2);
        fscanf(pFile, "%lf", &y2);

        if(feof(pFile)){
            setSegmentProx(s2, NULL);
            printf("%lf\n", getPointX(getVertexV(getSegmentV1(getPolygonFirstSegment(polygon)))));
            break;
        }

        if(verify){
            s1 = createSegment(createVertex(createPoint(x1, y1), 0, 0), createVertex(createPoint(x2, y2), 0, 0), NULL);
            if(first){
                polygon = createPolygon(s1);
                first = false;
            }
            verify = false;
        }
        else{
            s2 = createSegment(createVertex(createPoint(x1, y1), 0, 0), createVertex(createPoint(x2, y2), 0, 0), s1);
            setSegmentProx(s1, s2);
            verify = true;
        }

        x1 = x2;
        y1 = y2;
    }


    fclose(pFile);
    destroyPolygon(polygon);
}