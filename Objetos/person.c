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

char* getPersonCpf (Person p){ 
    PersonImp person = (PersonImp) p;

    return person->cpf;
}

char* getPersonNome (Person p){ 
    PersonImp person = (PersonImp) p;

    return person->nome;
}

char* getPersonSobrenome (Person p){ 
    PersonImp person = (PersonImp) p;

    return person->sobrenome;
}

char* getPersonSexo (Person p){ 
    PersonImp person = (PersonImp) p;

    return person->sexo;
}

char* getPersonNascimento (Person p){ 
    PersonImp person = (PersonImp) p;

    return person->nascimento;
}

