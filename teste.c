int cmpVertex(const void *a, const void *b){
    VertexImp arg1 = * (const VertexImp *)a;
    VertexImp arg2 = * (const VertexImp *)b;


    if(arg1->angle < arg2->angle) return -1;
    else if(arg1->angle > arg2->angle) return 1;

    else if(arg1->dist > arg2->dist) return -1;
    else if(arg1->dist < arg2->dist) return 1;

    else if(arg1->start && !arg2->start) return -1;
    else if(!arg1->start && arg2->start) return 1;
    return 0;
}

void sortVertex(Vertex v, int size, FILE *arqSvgQ){
    VertexImp *vertices = (VertexImp *) v;
    qsort(vertices, size, sizeof(VertexImp), cmpVertex);

    Form circle;
    for(int i = 0; i < size; i++){
        if(vertices[i]->start)
            circle = createCircle("", vertices[i]->x, vertices[i]->y, 3, "green", "green", "1");
        else
            circle = createCircle("", vertices[i]->x, vertices[i]->y, 3, "red", "red", "1");

        if(vertices[i]->x == 155)
            printf("%lf %lf %d %lf\n", vertices[i]->x, vertices[i]->y, vertices[i]->start, vertices[i]->angle);
        if(vertices[i]->x == 200 && vertices[i]->y == 220)
            printf("%lf %lf %d %lf\n", vertices[i]->x, vertices[i]->y, vertices[i]->start, vertices[i]->angle);
        printCircle(arqSvgQ, circle);
    }
}