#include"queryResident.h"

void printResidentData (char cpf[], List residents, List persons, FILE* arq){
    Resident resident;
    Person person;

    for (int i = getFirst (residents); i != getNulo(); i = getNext (residents, i)){
        resident = getElementByIndex (residents, i);
        char* cpfResident = getResidentCpf (resident);

        for (int i = getFirst (persons); i != getNulo(); i = getNext (persons, i)){
            person = getElementByIndex (persons, i);
            char* cpfPerson = getPersonCpf (person);

            if (strcmp (cpfPerson, cpfResident) == 0) break;
        }

        if (strcmp(cpf, getResidentCpf (resident)) == 0)
            fprintf (arq, "-%s %s:\n\tCPF: %s\n\tSexo: %s\n\tNascimento: %s\n\tCEP: %s, Face: %s ,Numero: %d, Complemento: %s\n", getPersonNome (person), getPersonSobrenome(person), getPersonCpf (person), getPersonSexo (person), getPersonNascimento(person), getResidentCep (resident), getResidentFace(resident), getResidentNum (resident), getResidentCompl (resident));
    }
}

void treatM (FILE *arqTxt, List persons, List residents, char cep[]){
    Resident resident;
    Person person;
    fprintf (arqTxt, "m? %s\nMoradores do cep fornecido: \n", cep);

    for (int i = getFirst (residents); i != getNulo(); i = getNext (residents, i)){
        resident = getElementByIndex (residents, i);
        char* cepResident = getResidentCep (resident);

        if (strcmp (cepResident, cep) == 0)
            printResidentData (getResidentCpf (resident), residents, persons, arqTxt);
    }
    fprintf (arqTxt,"\n");
}

