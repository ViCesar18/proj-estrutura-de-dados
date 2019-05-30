#ifndef CONSULTAS_LISTA__H
#define CONSULTAS_LISTA__H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "consulta.h"
#include "outSVG.h"
#include "lista.h"
#include "forms.h"
#include "block.h"

void verificarDQ(FILE *txt, FILE *svg2, Lista blocks, char metrica[], Form circulo);

void verificarCBQ(FILE *txt, Lista blocks, Form circulo, char cstrk[]);

void verificarTRNS(FILE *txt, Lista blocks, Lista hydrants, Lista semaphores, Lista radios, Form retangulo, double dx, double dy, FILE *svg2);

#endif