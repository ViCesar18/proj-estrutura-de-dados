#ifndef ESTRUTURAS__STRUCTS
#define ESTRUTURAS__STRUCTS

/*Structs para armazenar os circulos, retangulos e textos para o arquivo svg*/
typedef struct{
    char f;
    int id, tracoR;
    double rC, xC, yC, wR, hR, xR, yR;
    char strokeCollorC[10], fillCollorC[10], strokeCollorR[10], fillCollorR[10];
}Formas;

#endif