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

#endif