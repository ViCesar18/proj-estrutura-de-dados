#include "resident.h"

typedef struct stResident {
    char cep[32], face[2], compl[16];
    int num;
    Person person;
} *ResidentImp;

Resident createResident (char cpf[], char cep[], char face[], char compl[], int num, HashTable persons, HashTable buildingsTable, HashTable blocksTable){
    ResidentImp rResident = (ResidentImp) malloc (sizeof (struct stResident));

    strcpy (rResident->cep, cep);
    strcpy (rResident->face, face);
    strcpy (rResident->compl, compl);
    rResident->num = num;

    Person person = NULL;
    bool found = false;
    for(int i = 0; i < getHashTableSize(persons); i++){
        ListNode node = getHashNode(persons, i);
        while(node != NULL){
            person = getHashNodeElement(node);
            if(!strcmp(getPersonCpf(person), cpf)){
                found = true;
                break;
            }

            node = getHashNodeNext(node);
        }

        if(found) break;
    }

    rResident->person = person;
    char key[64];
    char n[8];
    sprintf(n, "%d", rResident->num);
    strcpy(key, rResident->cep);
    strcat(key, rResident->face);
    strcat(key, n);

    Building building = searchHashTable(buildingsTable, key);

    if(building != NULL){
        insertHashTable(getBuildingResidents(building), getPersonCpf(person), rResident);
        setBuildingHasResidents(building, true);
    }

    Block block = searchHashTable(blocksTable, cep);

    if(block != NULL){
        insertHashTable(getBlockResidents(block), getPersonCpf(person), rResident);
    }

    return rResident;
}

char* getResidentCpf (Resident r){
    ResidentImp resident = (ResidentImp) r;

    return getPersonCpf(resident->person);
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

Person getResidentPerson(Resident r){
    ResidentImp resident = (ResidentImp) r;

    return resident->person;
}

void destroyResident(Resident r){
    
    free(r);
}