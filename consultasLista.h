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

/*Remove todas as quadras que estiverem inteiramente dentro do circulo dependendo da metrica (L1 ou L2)*/
void verificarDQ(FILE *txt, FILE *svg2, Lista blocks, char metrica[], Form circulo);

/*Muda a cor da borda de todas as quadras que estiverem inteiramente dentro do circulo*/
void verificarCBQ(FILE *txt, Lista blocks, Form circulo, char cstrk[]);

/*Move todos os equipamentos urbanos que estão inteiramente dentro do retangulo em dx no eixo X e dy no eixo Y*/
void verificarTRNS(FILE *txt, Lista blocks, Lista hydrants, Lista semaphores, Lista radios, Form retangulo, double dx, double dy, FILE *svg2);

#endif