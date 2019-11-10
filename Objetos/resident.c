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

char* getResidentCpf (Resident r){
    ResidentImp resident = (ResidentImp) r;

    return resident->cpf;
}
char* getResidentCep (Resident r){
    ResidentImp resident = (ResidentImp) r;

    return resident->cep;
}
char* getResidentFace (Resident r){
    ResidentImp resident = (ResidentImp) r;

    return resident->face;
}
char* getResidentCompl (Resident r){
    ResidentImp resident = (ResidentImp) r;

    return resident->compl;
}

int getResidentNum (Resident r){
    ResidentImp resident = (ResidentImp) r;

    return resident->num;
}

void setResidentCep (Resident r, char cep[]){
    ResidentImp resident = (ResidentImp) r;

    strcpy (resident->cep, cep);
}

void setResidentFace (Resident r, char face[]){
    ResidentImp resident = (ResidentImp) r;

    strcpy (resident->face, face);
}

void setResidentNum (Resident r, int num){
    ResidentImp resident = (ResidentImp) r;

    resident->num = num;
}

void setResidentCompl (Resident r, char compl[]){
    ResidentImp resident = (ResidentImp) r;

    strcpy (resident->compl, compl);
}

void changeResidentAdress (Resident r, char cep[], char face[], int num, char compl[]){
    setResidentCep (r, cep);
    setResidentFace (r, face);
    setResidentNum (r, num);
    setResidentCompl (r, compl);
}