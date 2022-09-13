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
	if(xv != xc){
		a = (yv-yc)/(xv-xc);
		b = yc - a*xc;
	}

	double xq, yq;

	if(xc < xv && yc > yv){ 
		xq = (getPointY(pontoMin) - 50 - b) / a;
		yq = a * (getPointX(pontoMax) + 50) + b;
		if(distEuclid(xc, yc, xq, getPointY(pontoMin) - 50) > distEuclid(xc, yc, getPointX(pontoMax) + 50, yq)){
			yq = getPointY(pontoMin) - 50;
		}
        else{
			xq = getPointX(pontoMax) + 50;
		}
	}
    else if(xc < xv && yc == yv){
		xq = getPointX(pontoMax) + 50;
		yq = yc;
	}
    else if(xc < xv && yc < yv){
		xq = (yc + 50 - b)/a;
		yq = a*(getPointX(pontoMax) + 50) + b;
		if(distEuclid(xc, yc, xq, yc + 50) > distEuclid(xc, yc, getPointX(pontoMax) + 50, yq)){
			yq = yc + 50;
		}
        else{
			xq = getPointX(pontoMax) + 50;
		}
	}
    else if(xc > xv && yc > yv){
		xq = (getPointX(pontoMin) - 50 - b)/a;
		yq = a*(getPointX(pontoMin) - 50) + b;
		if(distEuclid(xc, yc, xq, getPointY(pontoMin) - 50) > distEuclid(xc, yc, getPointX(pontoMin) - 50, yq)){
			yq = getPointY(pontoMin) - 50;
		}
        else{
			xq = getPointX(pontoMin) - 50;
		}
	}
    else if(xc > xv && yc == yv){
		xq = getPointX(pontoMin) - 50;
		yq = yc;
	}
    else if(xc > xv && yc < yv){
		xq = (getPointY(pontoMax) + 50 - b)/a;
		yq = a*(getPointX(pontoMin) - 50) + b;
		if(distEuclid(xc, yc, xq, getPointY(pontoMax) + 50) > distEuclid(xc, yc, getPointX(pontoMin) - 50, yq)){
			yq = getPointY(pontoMax) + 50;
		}
        else{
			xq = getPointX(pontoMin) - 50;
		}
	}
    else if(xc == xv && yc > yv){
		xq = xc;
		yq = getPointY(pontoMin) - 50;
	}
    else if(xc == xv && yc < yv){
		xq = xc;
		yq = getPointY(pontoMax) + 50;
	}

    Vertex vc = createVertex(createPoint(xc, yc), xc, yc);
    Vertex vq = createVertex(createPoint(xq, yq), xc, yc);

	return createSegment(vc, vq);
}

void wallsToSegmentList(Tree walls, Node node, Segment *segments, Point pMax, double x, double y, int *index){
    Wall wall = getElement(walls, node);

    if(node == getNil(walls)) return;

    wallsToSegmentList(walls, getLeft(walls, node), segments, pMax, x, y, &(*index));

    Point p1 = createPoint(getWallX1(wall), getWallY1(wall));
    Point p2 = createPoint(getWallX2(wall), getWallY2(wall));

    setPointMax(pMax, getPointX(p1), getPointY(p1));
    setPointMax(pMax, getPointX(p2), getPointY(p2));

    //if(getPointX(p1) != x && getPointY(p2) != x && getPointY(p1) != y && getPointY(p2) != y){
        Vertex v1 = createVertex(p1, x, y);
        Vertex v2 = createVertex(p2, x, y);

        Segment s = createSegment(v1, v2);

        setSegmentStartVertex(s);

        setSegmentDistance(s, distEuclid(x, y, (getPointX(p1) + getPointX(p2)) / 2, (getPointY(p1) + getPointY(p2)) / 2));
        segments[*index] = s;
        (*index)++;
    //}

    wallsToSegmentList(walls, getRight(walls, node), segments, pMax, x, y, &(*index));
}

void buildingsToSegmentList(Tree buildings, Node node, Segment *segments, Point pMax, double x, double y, int *index){
    Building building = getElement(buildings, node);

    if(node == getNil(buildings)) return;

    buildingsToSegmentList(buildings, getLeft(buildings, node), segments, pMax, x, y, &(*index));
    
    Point pXY1 = createPoint(getBuildingX(building), getBuildingY(building));
    Point pXY2 = createPoint(getBuildingX(building), getBuildingY(building));
    Point pXWY1 = createPoint(getBuildingX(building) + getBuildingW(building), getBuildingY(building));
    Point pXWY2 = createPoint(getBuildingX(building) + getBuildingW(building), getBuildingY(building));
    Point pXYH1 = createPoint(getBuildingX(building), getBuildingY(building) + getBuildingH(building));
    Point pXYH2 = createPoint(getBuildingX(building), getBuildingY(building) + getBuildingH(building));
    Point pXWYH1 = createPoint(getBuildingX(building) + getBuildingW(building), getBuildingY(building) + getBuildingH(building));
    Point pXWYH2 = createPoint(getBuildingX(building) + getBuildingW(building), getBuildingY(building) + getBuildingH(building));
    
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
    
    Segment sTop = createSegment(vXY1, vXWY1);
    Segment sRight = createSegment(vXWY2, vXWYH1);
    Segment sBottom = createSegment(vXWYH2, vXYH1);
    Segment sLeft = createSegment(vXYH2, vXY2);
    
    setSegmentStartVertex(sTop);
    setSegmentStartVertex(sRight);
    setSegmentStartVertex(sBottom);
    setSegmentStartVertex(sLeft);
    
    setSegmentDistance(sTop, distEuclid(x, y, (getPointX(pXY1) + getPointX(pXWY1)) / 2, (getPointY(pXY1) + getPointY(pXWY1)) / 2));
    setSegmentDistance(sRight, distEuclid(x, y, (getPointX(pXWY2) + getPointX(pXWYH1)) / 2, (getPointY(pXWY2) + getPointY(pXWYH1)) / 2));
    setSegmentDistance(sBottom, distEuclid(x, y, (getPointX(pXWYH2) + getPointX(pXYH1)) / 2, (getPointY(pXWYH2) + getPointY(pXYH1)) / 2));
    setSegmentDistance(sLeft, distEuclid(x, y, (getPointX(pXYH2) + getPointX(pXY2)) / 2, (getPointY(pXYH2) + getPointY(pXY2)) / 2));
    
    segments[*index] = sTop;
    (*index)++;
    segments[*index] = sRight;
    (*index)++;
    segments[*index] = sBottom;
    (*index)++;
    segments[*index] = sLeft;
    (*index)++;
    
    buildingsToSegmentList(buildings, getRight(buildings, node), segments, pMax, x, y, &(*index));
}

void goThroughActiveSegments(Tree activeSegments, Node node, Segment sv, Segment s_v, Segment closerSegment, int dMin, double x, double y){
    Segment s = getElement(activeSegments, node);

    if(node == getNil(activeSegments)) return;

    goThroughActiveSegments(activeSegments, getLeft(activeSegments, node), sv, s_v, closerSegment, dMin, x, y);

    if(s != sv){
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

    goThroughActiveSegments(activeSegments, getRight(activeSegments, node), sv, s_v, closerSegment, dMin, x, y);
}

void bombAreaRadiation_Aux(Tree activeSegments, Node node, Segment s, double x, double y, double a1, double b1, bool vertical, double xV, double dist, 
                            bool *inFront, double *minDist, Segment closestSegmentBehind, double *xInter, double *yInter){
    if(node == getNil(activeSegments)) return;
    
    bombAreaRadiation_Aux(activeSegments, getLeft(activeSegments, node), s, x, y, a1, b1, vertical, xV, dist, &(*inFront), &(*minDist), closestSegmentBehind, 
                        &(*xInter), &(*yInter));
    
    Segment currentSegment = getElement(activeSegments, node);
    
    if(currentSegment != s){
        Vertex v1 = getSegmentV1(currentSegment);
        Vertex v2 = getSegmentV2(currentSegment);
        Point p1 = getVertexV(v1);
        Point p2 = getVertexV(v2);

        //Intersecção entre a reta anterior e a reta formada pelo segmento analisado
        double currentXInter, currentYInter;

        //Evita divisao por 0
        if(getPointX(p1) == getPointX(p2)){
            currentXInter = getPointX(p1);
            currentYInter = a1 * currentXInter + b1;
        }
        else{
            //Coeficiente Angular
            double a2 = (getPointY(p2) - getPointY(p1)) / (getPointX(p2) - getPointX(p1));

            //Termo independente
            double b2 = getPointY(p1) - a2 * getPointX(p1);

            if(vertical)
                currentXInter = xV;
            else
                currentXInter = (b2 - b1) / (a1 - a2);

            currentYInter = a2 * currentXInter + b2;
        }

        //Distância entre o ponto de intersecção e o ponto central
        double distInter = distEuclid(x, y, currentXInter, currentYInter);

        //Segmento do ponto analisado não está a frente
        if(distInter < dist || fabs(distInter - dist) < 0.000001){
            inFront = false;
        }
        else if(distInter >= dist && ((*minDist) == -1 || distInter <= (*minDist))){
            *minDist = distInter;
            closestSegmentBehind = currentSegment;
            *xInter = currentXInter;
            *yInter = currentYInter;
        }
    }

    bombAreaRadiation_Aux(activeSegments, getRight(activeSegments, node), s, x, y, a1, b1, vertical, xV, dist, &(*inFront), &(*minDist), closestSegmentBehind, 
                        &(*xInter), &(*yInter));
}

void bombAreaRadiation(FILE *arq, Polygon polygon, double x, double y, Tree walls, Tree buildings, bool brn){
    if(x == 0 && y == 0){
        insertPointPolygon(polygon, x, y);
    }

    int nBuildings = getSize(buildings);
    int nWalls = getSize(walls);

    int nSegments;

    if(brn)
        nSegments = nWalls + 4;
    else
        nSegments = nBuildings * 4 + nWalls;

    Segment *segments = malloc((nSegments * 2 + 5) * sizeof(Segment));
    Segment *segmentsP = segments;

    Point pMax = createPoint(x, y);

    int index = 0;
    if(!brn)
        buildingsToSegmentList(buildings, getTreeRoot(buildings), segmentsP, pMax, x, y, &index);
    wallsToSegmentList(walls, getTreeRoot(walls), segmentsP, pMax, x, y, &index);
    
    Segment sTop = createSegment(createVertex(createPoint(0, 0), 0, 0), createVertex(createPoint(getPointX(pMax), 0), 0, 0));
    Segment sRight = createSegment(createVertex(createPoint(getPointX(pMax), 0), 0, 0), createVertex(createPoint(getPointX(pMax), getPointY(pMax)), 0, 0));
    Segment sBottom = createSegment(createVertex(createPoint(getPointX(pMax), getPointY(pMax)), 0, 0), createVertex(createPoint(0, getPointY(pMax)), 0, 0));
    Segment sLeft = createSegment(createVertex(createPoint(0, getPointY(pMax)), 0, 0), createVertex(createPoint(0, 0), 0, 0));

    setSegmentStartVertex(sTop);
    setSegmentStartVertex(sRight);
    setSegmentStartVertex(sBottom);
    setSegmentStartVertex(sLeft);

    setSegmentDistance(sTop, distEuclid(x, y, (getPointX(getVertexV(getSegmentV1(sTop))) + getPointX(getVertexV(getSegmentV2(sTop)))) / 2, (getPointY(getVertexV(getSegmentV1(sTop))) + getPointY(getVertexV(getSegmentV2(sTop)))) / 2));
    setSegmentDistance(sRight, distEuclid(x, y, (getPointX(getVertexV(getSegmentV1(sRight))) + getPointX(getVertexV(getSegmentV2(sRight)))) / 2, (getPointY(getVertexV(getSegmentV1(sRight))) + getPointY(getVertexV(getSegmentV2(sRight)))) / 2));
    setSegmentDistance(sBottom, distEuclid(x, y, (getPointX(getVertexV(getSegmentV1(sBottom))) + getPointX(getVertexV(getSegmentV2(sBottom)))) / 2, (getPointY(getVertexV(getSegmentV1(sBottom))) + getPointY(getVertexV(getSegmentV2(sBottom)))) / 2));
    setSegmentDistance(sLeft, distEuclid(x, y, (getPointX(getVertexV(getSegmentV1(sLeft))) + getPointX(getVertexV(getSegmentV2(sLeft)))) / 2, (getPointY(getVertexV(getSegmentV1(sLeft))) + getPointY(getVertexV(getSegmentV2(sLeft)))) / 2));
    
    segmentsP[index] = sTop; index++;
    segmentsP[index] = sRight; index++;
    segmentsP[index] = sBottom; index++;
    segmentsP[index] = sLeft; index++;

    //nSegments = segmentsP - segments;

    int nVertexes = nSegments * 2;
    Vertex *vertexes = malloc(nVertexes * sizeof(Vertex));
    //Cria o vetor de pontos
    for(int i = 0; i < nSegments; i++){
        Segment s = segments[i];

        vertexes[2 * i] = getSegmentVStart(s);
        vertexes[2 * i + 1] = getSegmentVEnd(s);
    }

    //Ordena o vetor de pontos
    qsort(vertexes, nVertexes, sizeof(Vertex), cmpVertex);
    Tree activeSegments = createRBTree(comparatorSegment, freeSegment);

    for(int i = 0; i < nVertexes; i++){
        Vertex v = vertexes[i];
        Segment s = getVertexSegment(v);
        double dist = getSegmentDistance(s);
        double xV = getPointX(getVertexV(v));
        double yV = getPointY(getVertexV(v));

        //Coeficiente angular da reta formada pelo ponto de explosao e o ponto atual
        double a1;
        bool vertical = false;
        if(xV == x)
            vertical = true;
        else
            a1 = (yV - y) / (xV - x);
        //Termo independente da reta (c)
        double b1 = y - a1 * x;

        //Distância do segmento ativo mais perto que está atrás do segmento analisado
        double minDist = -1;
        Segment closestSegmentBehind = NULL;
        double xInter, yInter;
        bool inFront = true;

        //Tentativa com recursão
        /*bombAreaRadiation_Aux(activeSegments, getTreeRoot(activeSegments), s, x, y, a1, b1, vertical, xV, dist, &inFront, &minDist, closestSegmentBehind, 
                           &xInter, &yInter);*/
        
        for(Node node = getFirstNode(activeSegments); node != NULL; node = getSuccessor(activeSegments, node)){
            Segment currentSegment = getElement(activeSegments, node);
            if(currentSegment == s) continue;

            Vertex v1 = getSegmentV1(currentSegment);
            Vertex v2 = getSegmentV2(currentSegment);
            Point p1 = getVertexV(v1);
            Point p2 = getVertexV(v2);

            double currentXInter, currentYInter;

            if(getPointX(p2) == getPointX(p1)){
                currentXInter = getPointX(p1);
                currentYInter = a1 * currentXInter + b1;
            }
            else{
                double a2 = (getPointY(p2) - getPointY(p1)) / (getPointX(p2) - getPointX(p1));

                double b2 = getPointY(p1) - a2 * getPointX(p1);

                if(vertical)
                    currentXInter = getPointX(getVertexV(v));
                else
                    currentXInter = (b2 - b1) / (a1 - a2);

                currentYInter = a2 * currentXInter + b2;
            }

            double distInter = distEuclid(x, y, currentXInter, currentYInter);

            if(distInter < dist || fabs(distInter - dist) < 0.000001){
                inFront = false;
                break;
            }
            else if(distInter >= dist && (minDist == -1 || distInter <= minDist)){
                minDist = distInter;
                closestSegmentBehind = currentSegment;
                xInter = currentXInter;
                yInter = currentYInter;
            }
        }

        if(inFront){
            //Se o segmento estiver na frente de todos os ativos
            if(!getVertexStart(v)){
                double xBiombo = getSegmentXBiombo(s);
                double yBiombo = getSegmentYBiombo(s);

                //Colocar luz a partir do biombo do segmento até o ponto
                insertPointPolygon(polygon, xBiombo, yBiombo);
                insertPointPolygon(polygon, xV, yV);

                if(closestSegmentBehind != NULL){
                    //Se houver segmento atrás define o biombo desse segmento como o ponto de intersecção entre ele e a reta
                    setSegmentXYBiombo(closestSegmentBehind, xInter, yInter);
                }
            }
            else if(closestSegmentBehind != NULL){
                //Se for o vértice inicial e houver um segmento atrás
                double xBiombo = getSegmentXBiombo(closestSegmentBehind);
                double yBiombo = getSegmentYBiombo(closestSegmentBehind);

                if(vertical || fabs(a1 * xBiombo + b1 - yBiombo) > 0.000001){
                    //Colocar luz a partir do biombo desse segmento até o ponto de intersecção entre ele e a reta
                    insertPointPolygon(polygon, xBiombo, yBiombo);
                    insertPointPolygon(polygon, xInter, yInter);
                }
            }
        }

        if(getVertexStart(v)){
            insertNode(activeSegments, s);
        }
        else{
            removeNode(activeSegments, s);
        }
    }

    connectPolygon(polygon);

    printBomb(arq, x, y);

    free(vertexes);

    destroyRBTree(activeSegments);

    for(int i = 0; i < nSegments; i++) freeSegment(segments[i]);
    free(segments);
}