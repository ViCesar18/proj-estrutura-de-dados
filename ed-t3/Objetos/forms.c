#include "forms.h"

typedef struct stForm{
    char id[32];
    int stroke;
    double x, y, r, w, h;
    Vertex v2, v3;
    char strokeColor[24], fillColor[24], sw[12];
}*FormImp;

Form createCircle(char id[], double x, double y, double r, char strokeColor[], char fillColor[], char sw[]){
    FormImp circle = (FormImp)malloc(sizeof(struct stForm));

    strcpy(circle->id, id);
    circle->x = x;
    circle->y = y;
    circle->r = r;
    strcpy(circle->strokeColor, strokeColor);
    strcpy(circle->fillColor, fillColor);
    strcpy(circle->sw, sw);

    return circle;
}

Form createRect(char id[], double x, double y, double w, double h, char strokeColor[], char fillColor[], int stroke, char sw[]){
    FormImp rect = (FormImp)malloc(sizeof(struct stForm));

    strcpy(rect->id, id);
    rect->stroke = stroke;
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
    strcpy(rect->strokeColor, strokeColor);
    strcpy(rect->fillColor, fillColor);
    strcpy(rect->sw, sw);

    return rect;
}

Form createTriangle(double x, double y, Vertex v2, Vertex v3){
    FormImp triangle = (FormImp)malloc(sizeof(struct stForm));

    triangle->x = x;
    triangle->y = y;
    triangle->v2 = v2;
    triangle->v3 = v3;

    return triangle;
}

char  *getFormId(Form f){
    FormImp form = (FormImp) f;

    return form->id;
}

int getFormStroke(Form f){
    FormImp form = (FormImp) f;

    return form->stroke;
}

double getFormX(Form f){
    FormImp form = (FormImp) f;

    return form->x;
}

double getFormY(Form f){
    FormImp form = (FormImp) f;

    return form->y;
}

double getFormR(Form f){
    FormImp form = (FormImp) f;

    return form->r;
}

double getFormW(Form f){
    FormImp form = (FormImp) f;

    return form->w;
}

double getFormH(Form f){
    FormImp form = (FormImp) f;

    return form->h;
}

Vertex getFormV2(Form f){
    FormImp form = (FormImp) f;

    return form->v2;
}

Vertex getFormV3(Form f){
    FormImp form = (FormImp) f;

    return form->v3;
}

char *getFormStrokeColor(Form f){
    FormImp form = (FormImp) f;

    return form->strokeColor;
}

char *getFormFillColor(Form f){
    FormImp form = (FormImp) f;

    return form->fillColor;
}

char *getFormSw(Form f){
    FormImp form = (FormImp) f;

    return form->sw;
}

void freeForm(Form f){
    FormImp form = (FormImp) f;

    free(form);
}