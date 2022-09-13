#include"queryResident.h"

void treatM (FILE *arqTxt, HashTable persons, HashTable residents, char cep[]){

    fprintf (arqTxt, "m? %s\nMoradores do CEP fornecido: \n", cep);

    for(int i = 0; i < getHashTableSize(residents); i++){
        ListNode node = getHashNode(residents, i);
        while(node != NULL){
            Resident resident = getHashNodeElement(node);
            char *cepResident = getResidentCep(resident);

            if(!strcmp(cepResident, cep)){
                Person person = getResidentPerson(resident);
                fprintf (arqTxt, "-%s %s:\n\tCPF: %s\n\tSexo: %s\n\tNascimento: %s\n\tCEP: %s, Face: %s, Número: %d, Complemento: %s\n", getPersonName (person), getPersonLastName(person), getPersonCpf (person), getPersonSexo (person), getPersonNascimento(person), getResidentCep (resident), getResidentFace(resident), getResidentNum (resident), getResidentCompl (resident));
            }
            
            node = getHashNodeNext(node);
        }
    }

    fprintf (arqTxt,"\n");
}

void printResidentData(char *cpf, HashTable residents, FILE *arqTxt){
    bool found = false;

    for(int i = 0; i < getHashTableSize(residents); i++){
        ListNode node = getHashNode(residents, i);
        while(node != NULL){
            Resident resident = getHashNodeElement(node);

            if(!strcmp(cpf, getResidentCpf(resident))){
                found = true;
                Person person = getResidentPerson(resident);
                fprintf (arqTxt, "-%s %s:\n\tCPF: %s\n\tSexo: %s\n\tNascimento: %s\n\tCEP: %s, Face: %s, Número: %d, Complemento: %s\n", getPersonName (person), getPersonLastName(person), getPersonCpf (person), getPersonSexo (person), getPersonNascimento(person), getResidentCep (resident), getResidentFace(resident), getResidentNum (resident), getResidentCompl (resident));
                break;
            }

            node = getHashNodeNext(node);
        }

        if(found) break;
    }

    if(!found)
        fprintf(arqTxt, "-A pessoa do CPF indicado não é um morador ou não existe!");
}

void treatMud (FILE *arqTxt, HashTable residents, HashTable buildingsTable, char cpf[], char cep[], char face[], int num, char compl[]){
    Resident resident;

    bool found = false;
    for(int i = 0; i < getHashTableSize(residents); i++){
        ListNode node = getHashNode(residents, i);
        while(node != NULL){
            resident = getHashNodeElement(node);

            if(!strcmp(cpf, getResidentCpf(resident))){
                found = true;
                break;
            }

            node = getHashNodeNext(node);
        }
        
        if(found) break;
    }

    Person person = getResidentPerson(resident);
    Building building = getResidentBuilding(resident);

    fprintf (arqTxt, "-%s %s:\n\tCPF: %s\n\tSexo: %s\n\tNascimento: %s\n", getPersonName (person), getPersonLastName(person), getPersonCpf (person), getPersonSexo (person), getPersonNascimento(person));
    fprintf (arqTxt, "\tEndereço antigo:\n");
    fprintf(arqTxt, "\t-CEP: %s, Face: %s, Número: %d, Complemento: %s\n", getResidentCep(resident), getResidentFace(resident), getResidentNum(resident), getResidentCompl(resident));

    if(building != NULL){
        removeHashTable(getBuildingResidents(building), getPersonCpf(person));
        decreaseBuildingNResidents(building);
    }

    changeResidentAdress (resident, cep, face, num, compl);

    char key[64];
    char n[8];
    sprintf(n, "%d", num);
    strcpy(key, cep);
    strcat(key, face);
    strcat(key, n);
    Building newBuilding = searchHashTable(buildingsTable, key);
    setResidentBuilding(resident, newBuilding);

    if(newBuilding != NULL){
        insertHashTable(getBuildingResidents(newBuilding), getPersonCpf(person), resident);
        increaseBuildingNResidents(newBuilding);
    }
    
    fprintf (arqTxt, "\tEndereço novo: \n");
    fprintf(arqTxt, "\t-CEP: %s, Face: %s, Número: %d, Complemento: %s\n", getResidentCep(resident), getResidentFace(resident), getResidentNum(resident), getResidentCompl(resident));
}