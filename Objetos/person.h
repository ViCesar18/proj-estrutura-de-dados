#ifndef PERSON__H
#define PERSON__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Person;
Person createPerson (char cpf[], char nome[], char sobrenome[], char sexo[], char nascimento[]);


#endif