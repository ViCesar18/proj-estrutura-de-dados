#include "radio.h"

typedef struct stRadio{
    char id[32], strokeCollor[24], fillCollor[24], sw[12];
    double x, y;    
}*RadioImp;

Radio criarRadio(char id[], double x, double y, char strokeCollor[], char fillCollor[], char sw[]){
    RadioImp radio = (RadioImp) malloc(sizeof(struct stRadio));

    strcpy(radio->id, id);
    radio->x = x;
    radio->y = y;
    strcpy(radio->strokeCollor, strokeCollor);
    strcpy(radio->fillCollor, fillCollor);
    strcpy(radio->sw, sw);

    return radio;
}

char *getRadioId(Radio r){
    RadioImp radio = (RadioImp) r;

    return radio->id;
}

double getRadioX(Radio r){
    RadioImp radio = (RadioImp) r;

    return radio->x;
}

double getRadioY(Radio r){
    RadioImp radio = (RadioImp) r;

    return radio->y;
}

char *getRadioStrokeCollor(Radio r){
    RadioImp radio = (RadioImp) r;

    return radio->strokeCollor;
}

char *getRadioFillCollor(Radio r){
    RadioImp radio = (RadioImp) r;

    return radio->fillCollor;
}

char *getRadioSw(Radio r){
    RadioImp radio = (RadioImp) r;

    return radio->sw;
}

void setRadioX(Radio r, double x){
    RadioImp radio = (RadioImp) r;

    radio->x = x;
}

void setRadioY(Radio r, double y){
    RadioImp radio = (RadioImp) r;

    radio->y = y;
}