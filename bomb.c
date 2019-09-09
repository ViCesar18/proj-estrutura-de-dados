#include "bomb.h"

int cmpVertex(const void *a, const void *b){
    Vertex arg1 = * (const Vertex *)a;
    Vertex arg2 = * (const Vertex *)b;

    if(getVertexAngle(arg1) < getVertexAngle(arg2)) return -1;
    else if(getVertexAngle(arg1) > getVertexAngle(arg2)) return 1;

    else if(getVertexDist(arg1) < getVertexDist(arg2)) return -1;
    else if(getVertexDist(arg1) > getVertexDist(arg2)) return 1;

    else if(!getVertexStart(arg1) && getVertexStart(arg2)) return -1;
    else if(getVertexStart(arg1) && !getVertexStart(arg2)) return 1;
    return 0;
}

Segment buscarSegmentoFormadoComVertice(double xc, double yc, Vertex v, Point pontoMin, Point pontoMax) {
	double xv = getPointX(getVertexV(v)), yv = getPointY(getVertexV(v));
	double a, b;
	if(xv != xc) { // reta perpendicular ver dps
		a = (yv-yc)/(xv-xc);
		b = yc - a*xc;
	}

	double xq, yq;
	// y = ax + b
	// x = (y-b)/a
	if(xc < xv && yc > yv) { 
		xq = (getPointY(pontoMin) - 50 - b)/a;
		yq = a*(getPointX(pontoMax) + 50) + b;
		if(distEuclid(xc, yc, xq, getPointY(pontoMin) - 50) > distEuclid(xc, yc, getPointX(pontoMax) + 50, yq)) {
			yq = getPointY(pontoMin) - 50;
		} else {
			xq = getPointX(pontoMax) + 50;
		}
	} else if(xc < xv && yc == yv) { // certo
		xq = getPointX(pontoMax) + 50;
		yq = yc;
	} else if(xc < xv && yc < yv) {
		xq = (yc + 50 - b)/a;
		yq = a*(getPointX(pontoMax) + 50) + b;
		if(distEuclid(xc, yc, xq, yc + 50) > distEuclid(xc, yc, getPointX(pontoMax) + 50, yq)) {
			yq = yc + 50;
		} else {
			xq = getPointX(pontoMax) + 50;
		}
	} else if(xc > xv && yc > yv) {
		xq = (getPointX(pontoMin) - 50 - b)/a;
		yq = a*(getPointX(pontoMin) - 50) + b;
		if(distEuclid(xc, yc, xq, getPointY(pontoMin) - 50) > distEuclid(xc, yc, getPointX(pontoMin) - 50, yq)) {
			yq = getPointY(pontoMin) - 50;
		} else {
			xq = getPointX(pontoMin) - 50;
		}
	} else if(xc > xv && yc == yv) { // certo
		xq = getPointX(pontoMin) - 50;
		yq = yc;
	} else if(xc > xv && yc < yv) {
		xq = (getPointY(pontoMax) + 50 - b)/a;
		yq = a*(getPointX(pontoMin) - 50) + b;
		if(distEuclid(xc, yc, xq, getPointY(pontoMax) + 50) > distEuclid(xc, yc, getPointX(pontoMin) - 50, yq)) {
			yq = getPointY(pontoMax) + 50;
		} else {
			xq = getPointX(pontoMin) - 50;
		}
	} else if(xc == xv && yc > yv) { // certo
		xq = xc;
		yq = getPointY(pontoMin) - 50;
	} else if(xc == xv && yc < yv) { // certo
		xq = xc;
		yq = getPointY(pontoMax) + 50;
	}

	// ver como vou dar free dps
    Vertex vc = createVertex(createPoint(xc, yc), xc, yc);
    Vertex vq = createVertex(createPoint(xq, yq), xc, yc);

	return createSegment(vc, vq);
}

void bombAreaRadiation(double x, double y, int capacity, List walls, List buildings, int *vectSize, FILE *arq){
    Segment *segments = (Segment *) malloc(capacity * sizeof(Segment));
    Point pMin = createPoint(x, y);
    Point pMax = createPoint(x, y);
    int index = 0;

    for(int i = getFirst(walls); i != getNulo(); i = getNext(walls, i)){
        Wall wall = getElementByIndex(walls, i);
        
        Point p1 = createPoint(getWallX1(wall), getWallY1(wall));
        Point p2 = createPoint(getWallX2(wall), getWallY2(wall));

        setPointMin(pMin, getPointX(p1), getPointY(p1));
        setPointMin(pMin, getPointX(p2), getPointY(p2));
        setPointMax(pMax, getPointX(p1), getPointY(p1));
        setPointMax(pMax, getPointX(p2), getPointY(p2));

        if(getPointX(p1) == x && getPointY(p2) == x || getPointY(p1) == y && getPointY(p2) == y)
            continue;

        Vertex v1 = createVertex(p1, x, y);
        Vertex v2 = createVertex(p2, x, y);

        Segment s = createSegment(v1, v2);

        setSegmentStartVertex(s);

        segments[index] = s;
        index++;
    }
    
    for(int i = getFirst(buildings); i != getNulo(); i = getNext(buildings, i)){
        Building building = getElementByIndex(buildings, i);

        Point pXY1 = createPoint(getBuildingX(building), getBuildingY(building));
        Point pXY2 = createPoint(getBuildingX(building), getBuildingY(building));
        Point pXWY1 = createPoint(getBuildingX(building) + getBuildingW(building), getBuildingY(building));
        Point pXWY2 = createPoint(getBuildingX(building) + getBuildingW(building), getBuildingY(building));
        Point pXYH1 = createPoint(getBuildingX(building), getBuildingY(building) + getBuildingH(building));
        Point pXYH2 = createPoint(getBuildingX(building), getBuildingY(building) + getBuildingH(building));
        Point pXWYH1 = createPoint(getBuildingX(building) + getBuildingW(building), getBuildingY(building) + getBuildingH(building));
        Point pXWYH2 = createPoint(getBuildingX(building) + getBuildingW(building), getBuildingY(building) + getBuildingH(building));

        setPointMin(pMin, getPointX(pXY1), getPointY(pXY1));
        setPointMin(pMin, getPointX(pXWY1), getPointY(pXWY1));
        setPointMin(pMin, getPointX(pXYH1), getPointY(pXYH1));
        setPointMin(pMin, getPointX(pXWYH1), getPointY(pXWYH1));
        setPointMax(pMax, getPointX(pXY2), getPointY(pXY2));
        setPointMax(pMax, getPointX(pXWY2), getPointY(pXWY2));
        setPointMax(pMax, getPointX(pXYH2), getPointY(pXYH2));
        setPointMax(pMax, getPointX(pXWYH2), getPointY(pXWYH2));

        Vertex vXY1 = createVertex(pXY1, x, y);
        Vertex vXY2 = createVertex(pXY2, x, y);
        Vertex vXWY1 = createVertex(pXWY1, x, y);
        Vertex vXWY2 = createVertex(pXWY2, x, y);
        Vertex vXYH1 = createVertex(pXYH1, x, y);
        Vertex vXYH2 = createVertex(pXYH2, x, y);
        Vertex vXWYH1 = createVertex(pXWYH1, x, y);
        Vertex vXWYH2 = createVertex(pXWYH2, x, y);

        Segment sC = createSegment(vXY1, vXWY1);
        Segment sD = createSegment(vXWY2, vXWYH1);
        Segment sB = createSegment(vXWYH2, vXYH1);
        Segment sE = createSegment(vXYH2, vXY2);

        setSegmentStartVertex(sC);
        setSegmentStartVertex(sD);
        setSegmentStartVertex(sB);
        setSegmentStartVertex(sE);

        segments[index] = sC;
        index++;
        segments[index] = sD;
        index++;
        segments[index] = sB;
        index++;
        segments[index] = sE;
        index++;
    }

    /*Criacao do retangulo que envolve todos os segmentos(borda)*/
    capacity += 4;

    Point pXY1 = createPoint(getPointX(pMin) - 100, getPointY(pMin) - 100);
    Point pXY2 = createPoint(getPointX(pMin) - 100, getPointY(pMin) - 100);
    Point pXWY1 = createPoint(getPointX(pMax) + 100, getPointY(pMin) - 100);
    Point pXWY2 = createPoint(getPointX(pMax) + 100, getPointY(pMin) - 100);
    Point pXYH1 = createPoint(getPointX(pMin) - 100, getPointY(pMax) + 100);
    Point pXYH2 = createPoint(getPointX(pMin) - 100, getPointY(pMax) + 100);
    Point pXWYH1 = createPoint(getPointX(pMax) + 100, getPointY(pMax) + 100);
    Point pXWYH2 = createPoint(getPointX(pMax) + 100, getPointY(pMax) + 100);

    Vertex vXY1 = createVertex(pXY1, x, y);
    Vertex vXY2 = createVertex(pXY2, x, y);
    Vertex vXWY1 = createVertex(pXWY1, x, y);
    Vertex vXWY2 = createVertex(pXWY2, x, y);
    Vertex vXYH1 = createVertex(pXYH1, x, y);
    Vertex vXYH2 = createVertex(pXYH2, x, y);
    Vertex vXWYH1 = createVertex(pXWYH1, x, y);
    Vertex vXWYH2 = createVertex(pXWYH2, x, y);

    Segment sC = createSegment(vXY1, vXWY1);
    Segment sE = createSegment(vXWY2, vXWYH1);
    Segment sB = createSegment(vXWYH2, vXYH1);
    Segment sD = createSegment(vXYH2, vXY2);

    setSegmentStartVertex(sC);
    setSegmentStartVertex(sE);
    setSegmentStartVertex(sB);
    setSegmentStartVertex(sD);

    segments[index] = sC;
    index++;
    segments[index] = sE;
    index++;
    segments[index] = sB;
    index++;
    segments[index] = sD;
    index++;

    Point pBomb1 = createPoint(x, y);
    Point pBomb2 = createPoint(getPointX(pMin) - 101, y);
    Vertex vStart = createVertex(pBomb1, 0, 0);
    Vertex vEnd = createVertex(pBomb2, 0, 0);
    Segment startSegment = createSegment(vStart, vEnd);
    setVertexSegment(vStart, startSegment);
    setVertexSegment(vEnd, startSegment);
    setVertexStart(vStart, true);
    setVertexStart(vEnd, false);

    printBomb(arq, x, y);

    int segmentsSize = index;

    int capacityVertices = capacity * 2;
    index = 0;

    Vertex *vertices = (Vertex *) malloc(capacityVertices * sizeof(Vertex));

    for(int i = 0; i < segmentsSize; i++){
        if(checkSegmentsIntersection(startSegment, segments[i])){
            capacityVertices += 2;
            vertices = (Vertex *) realloc(vertices, capacityVertices * sizeof(Vertex));

            double interX, interY;
            segmentIntersection(startSegment, segments[i], &interX, &interY);

            Vertex vStart = getVertexStart(getSegmentV1(segments[i])) ? getSegmentV1(segments[i]) : getSegmentV2(segments[i]);
            Vertex vEnd = getVertexStart(getSegmentV2(segments[i])) ? getSegmentV2(segments[i]) : getSegmentV1(segments[i]);

            Point pInter = createPoint(interX, interY);
            Vertex vInterStart = createVertex(pInter, x, y);
            setVertexStart(vInterStart, true);
            setVertexAngle(vInterStart, -PI);

            Vertex vInterEnd = createVertex(pInter, x, y);
            setVertexStart(vInterEnd, false);
            setVertexAngle(vInterEnd, PI);

            Segment s1 = createSegment(vStart, vInterEnd);
            Segment s2 = createSegment(vInterStart, vEnd);

            setVertexSegment(vStart, s1);
            setVertexSegment(vInterEnd, s1);
            setVertexSegment(vInterStart, s2);
            setVertexSegment(vEnd, s2);

            vertices[index] = vStart;
            index++;
            vertices[index] = vInterEnd;
            index++;
            vertices[index] = vInterStart;
            index++;
            vertices[index] = vEnd;
            index++;
        }
        else{
            Vertex v1 = getSegmentV1(segments[i]);
            Vertex v2 = getSegmentV2(segments[i]);

            setVertexSegment(v1, segments[i]);
            setVertexSegment(v2, segments[i]);

            setVertexSegment(v1, segments[i]);
            setVertexSegment(v2, segments[i]);

            vertices[index] = v1;
            index++;
            vertices[index] = v2;
            index++;
        }
    }
    int verticesSize = index;

    qsort(vertices, verticesSize, sizeof(Vertex), cmpVertex);

    List activeSegments = createList((int) verticesSize / 2);
    Vertex biombo = createVertex(createPoint(getPointX(getVertexV(vertices[0])), getPointY(getVertexV(vertices[0]))), x, y);
    setVertexSegment(biombo, getVertexSegment(vertices[0]));

    for(int i = 0; i < verticesSize; i++){
        Vertex v = vertices[i];
        Segment sv = getVertexSegment(v);
        Segment s_v = buscarSegmentoFormadoComVertice(x, y, v, pMin, pMax);
        Segment closerSegment = NULL;

        double dMin = __INT_MAX__;

        for(int j = getFirst(activeSegments); j != getNulo(); j = getNext(activeSegments, j)){
            Segment s = getElementByIndex(activeSegments, j);

            if(s == sv) continue;

            if(checkSegmentsIntersection(s_v, s)){
                double xInter, yInter;
                segmentIntersection(s_v, s, &xInter, &yInter);

                double distBombInter = distEuclid(x, y, xInter, yInter);
                if(distBombInter < dMin){
                    dMin = distBombInter;
                    closerSegment = s;
                }
            }
        }

        if(getVertexStart(v)){
            bool itsCloserSegment;

            if(distEuclid(x, y, getPointX(getVertexV(v)), getPointY(getVertexV(v))) < dMin)
                itsCloserSegment = true;
            else
                itsCloserSegment = false;

            if(itsCloserSegment){
                double biomboInterX, biomboInterY;

                segmentIntersection(s_v, getVertexSegment(biombo), &biomboInterX, &biomboInterY);
                Vertex vInter = createVertex(createPoint(biomboInterX, biomboInterY), x, y);
                Segment s1 = createSegment(biombo, vInter);
                Segment s2 = createSegment(vInter, v);

                svg_escreverTriangulo(arq, x, y, biombo, vInter);

                biombo = v;
            }     
            insertElement(activeSegments, sv, "seg");       
        }
        else{
            bool itsCloserSegment;

            if(distEuclid(x, y, getPointX(getVertexV(v)), getPointY(getVertexV(v))) <= dMin)
                itsCloserSegment = true;
            else
                itsCloserSegment = false;

            if(itsCloserSegment){
                if(closerSegment != NULL){
                    double biomboInterX, biomboInterY;
                    segmentIntersection(s_v, closerSegment, &biomboInterX, &biomboInterY);
                    Vertex vInter = createVertex(createPoint(biomboInterX, biomboInterY), x, y);

                    Segment s1 = createSegment(biombo, v);
                    Segment s2 = createSegment(v, vInter);

                    svg_escreverTriangulo(arq, x, y, v, vInter);
                    svg_escreverTriangulo(arq, x, y, biombo, v);

                    biombo = vInter;
                    setVertexSegment(biombo, closerSegment);
                }
                else{
                    Segment s = createSegment(biombo, v);
                    svg_escreverTriangulo(arq, x, y, biombo, v);
                    biombo = v;
                }
            }
            lista_excluirObjetoMemoria(activeSegments, sv);
        }
    }

    for(int i = 0; i < segmentsSize; i++){
        Wall w = createWall(getPointX(getVertexV(getSegmentV1((Segment)segments[i]))), getPointY(getVertexV(getSegmentV1((Segment)segments[i]))), getPointX(getVertexV(getSegmentV2((Segment)segments[i]))), getPointY(getVertexV(getSegmentV2((Segment)segments[i]))));
        printWall(arq, w);
        freeWall(w);
    }

    for(int i = 0; i < verticesSize; i++){
        Form circle;

        if(getVertexStart(vertices[i])){
            circle = createCircle("", getPointX(getVertexV(vertices[i])), getPointY(getVertexV(vertices[i])), 3, "green", "green", "1");
        }
        else{
            circle = createCircle("", getPointX(getVertexV(vertices[i])), getPointY(getVertexV(vertices[i])), 3, "red", "red", "1");
        }

        printCircle(arq, circle);
        freeForm(circle);
    }

    for(int i = 0; i < segmentsSize; i++){
        freeSegment(segments[i]);
    }
    freePoint(pMin);
    freePoint(pMax);
    freeSegment(startSegment);
    free(segments);
    free(vertices);
}