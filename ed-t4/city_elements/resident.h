#ifndef RESIDENT__H
#define RESIDENT__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "person.h"
#include "building.h"
#include "../data_structures/hash_table.h"

typedef void *Resident;
typedef void *Building;

Resident createResident (char cpf[], char cep[], char face[], char compl[], int num, HashTable persons, HashTable buildingsTable, HashTable blocksTable);

char* getResidentCep (Resident r);

char* getResidentCpf (Resident r);

char* getResidentFace (Resident r);

char* getResidentCompl (Resident r);

int getResidentNum (Resident r);

Person getResidentPerson(Resident r);

Building getResidentBuilding(Resident r);

double getResidentX(Resident r);

double getResidentY(Resident r);

void setResidentCep (Resident r, char cep[]);

void setResidentFace (Resident r, char face[]);

void setResidentNum (Resident r, int num);

void setResidentCompl (Resident r, char compl[]);

void setResidentBuilding(Resident r, Building b);

void changeResidentAdress (Resident r, char cep[], char face[], int num, char compl[]);

void destroyResident(Resident r);

#endif