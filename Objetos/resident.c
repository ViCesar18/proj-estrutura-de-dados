#include "resident.h"

typedef struct stResident {
    char cpf[32], cep[32], face[2], compl[16];
    int num;
} *ResidentImp;

Resident createResident (char cpf[], char cep[], char face[], char compl[], int num){
    ResidentImp rResident = (ResidentImp) malloc (sizeof (struct stResident));

    strcpy (rResident->cpf, cpf);
    strcpy (rResident->cep, cep);
    strcpy (rResident->face, face);
    strcpy (rResident->compl, compl);
    rResident->num = num;

    return rResident;
}