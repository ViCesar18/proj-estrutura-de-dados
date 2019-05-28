#include "forms.h"

typedef struct stForm{
    int id, stroke;
    char type;
    double x, y, r, w, h;
    char strokeCollor[24], fillCollor[24];
}*FormImp;

Form criarCirculo(int id, double x, double y, double r, char strokeCollor[], char fillCollor[]){
    FormImp circulo = (FormImp)malloc(sizeof(struct stForm));

    circulo->id = id;
    circulo->type = 'c';
    circulo->x = x;
    circulo->y = y;
    circulo->r = r;
    strcpy(circulo->strokeCollor, strokeCollor);
    strcpy(circulo->fillCollor, fillCollor);

    return circulo;
}

Form criarRect(int id, double x, double y, double w, double h, char strokeCollor[], char fillCollor[], int stroke){
    FormImp rect = (FormImp)malloc(sizeof(struct stForm));

    rect->id = id;
    rect->stroke = stroke;
    rect->type = 'r';
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
    strcpy(rect->strokeCollor, strokeCollor);
    strcpy(rect->fillCollor, fillCollor);

    return rect;
}

int getFormId(Form f){
    FormImp form = (FormImp) f;

    return form->id;
}

int getFormStroke(Form f){
    FormImp form = (FormImp) f;

    return form->stroke;
}

char getFormType(Form f){
    FormImp form = (FormImp) f;

    return form->type;
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