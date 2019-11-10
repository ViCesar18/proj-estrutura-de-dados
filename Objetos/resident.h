#ifndef RESIDENT__H
#define RESIDENT__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Resident;
Resident createResident (char cpf[], char cep[], char face[], char compl[], int num);
char* getResidentCep (Resident r);
char* getResidentCpf (Resident r);
char* getResidentFace (Resident r);
char* getResidentCompl (Resident r);
int getResidentNum (Resident r);

void setResidentCep (Resident r, char cep[]);
void setResidentFace (Resident r, char face[]);
void setResidentNum (Resident r, int num);
void setResidentCompl (Resident r, char compl[]);
void changeResidentAdress (Resident r, char cep[], char face[], int num, char compl[]);




#endif