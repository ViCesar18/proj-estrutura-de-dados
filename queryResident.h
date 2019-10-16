#ifndef QUERY_RESIDENT__H
#define QUERY_RESIDENT__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "./Objetos/person.h"
#include "./Objetos/resident.h"

void printResidentData (char cpf[], List residents, List persons, FILE* arq);
void treatM (FILE *arqTxt, List persons, List residents, char cep[]);
    
#endif