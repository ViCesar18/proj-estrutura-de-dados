#ifndef PERSON__H
#define PERSON__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Person;
Person createPerson (char cpf[], char nome[], char sobrenome[], char sexo[], char nascimento[]);

char* getPersonCpf (Person p);
char* getPersonName (Person p);
char* getPersonLastName (Person p);
char* getPersonSexo (Person p);
char* getPersonNascimento (Person p);

void destroyPerson(Person p);

#endif