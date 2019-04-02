#ifndef CONSULTA__H
#define CONSULTA__H

#include <stdbool.h>
#include "structs.h"

double distEuclid(double x1, double y1, double x2, double y2);

double clamp(double xC, double min, double max);

void verificarO(FILE *txt, FILE *svg2, Formas figura1, Formas figura2);

void retanguloEnvolveCirculo(FILE *svg2, Formas figura1, Formas figura2, bool colisao);

void retanguloEnvolveRetangulo(FILE *svg2, Formas figura1, Formas figura2, bool colisao);

void retanguloEnvolveCR(FILE *svg2, Formas figura1, Formas figura2, bool colisao);

#endif