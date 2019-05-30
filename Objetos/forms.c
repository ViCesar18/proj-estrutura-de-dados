#include "forms.h"

typedef struct stForm{
    char id[32];
    int stroke;
    double x, y, r, w, h;
    char strokeCollor[24], fillCollor[24], sw[12];
}*FormImp;

Form criarCirculo(char id[], double x, double y, double r, char strokeCollor[], char fillCollor[], char sw[]){
    FormImp circulo = (FormImp)malloc(sizeof(struct stForm));

    strcpy(circulo->id, id);
    circulo->x = x;
    circulo->y = y;
    circulo->r = r;
    strcpy(circulo->strokeCollor, strokeCollor);
    strcpy(circulo->fillCollor, fillCollor);
    strcpy(circulo->sw, sw);

    return circulo;
}

Form criarRect(char id[], double x, double y, double w, double h, char strokeCollor[], char fillCollor[], int stroke, char sw[]){
    FormImp rect = (FormImp)malloc(sizeof(struct stForm));

    strcpy(rect->id, id);
    rect->stroke = stroke;
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
    strcpy(rect->strokeCollor, strokeCollor);
    strcpy(rect->fillCollor, fillCollor);
    strcpy(rect->sw, sw);

    return rect;
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

char *getFormStrokeCollor(Form f){
    FormImp form = (FormImp) f;

    return form->strokeCollor;
}

char *getFormFillCollor(Form f){
    FormImp form = (FormImp) f;

    return form->fillCollor;
}

char *getFormSw(Form f){
    FormImp form = (FormImp) f;

    return form->sw;
}

void freeForm(Form f){
    FormImp form = (FormImp) f;

    free(form);
}