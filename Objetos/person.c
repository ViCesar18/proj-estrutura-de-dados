#include"person.h"

typedef struct stPerson {
    char cpf[32], nome[32], sobrenome[32], sexo[2], nascimento[16];
} *PersonImp;

Person createPerson (char cpf[], char nome[], char sobrenome[], char sexo[], char nascimento[]){
    PersonImp rPerson = (PersonImp) malloc (sizeof(struct stPerson));

    strcpy (rPerson->cpf, cpf);
    strcpy (rPerson->nome, nome);
    strcpy (rPerson->sobrenome, sobrenome);
    strcpy (rPerson->sexo, sexo);
    strcpy (rPerson->nascimento, nascimento);

    return rPerson;
}