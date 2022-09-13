#ifndef IN_SVG
#define IN_SVG

#include "structs.h"

/*Nesse header encontra-se todas as funcoes relacionadas a entrada/leitura de dados*/

/*Verifica se o arquivo em questao foi aberto com sucesso, caso contrario, sai do programa*/
void verificarArquivo(FILE *arq, char nome[]);

/*Funcao que recebe os parametros digitados do terminal*/
void receberParametros(int argc, char *argv[], char **pathIn, char **nameIn, char **nameConsulta, char **pathOut);

/*Trata o nome do arquivo geo/qry caso ele seja passado como parametro junto com um diretorio relativo*/
void tratarNome(char nameIn[], char **nameInT);

/*aloca memoria e cria os diretorios, tambem verifica se a '/' foi ou nao inserida*/
void alocarMemoria(char nome[], char dir[], char **arq);

/*Le o valor de NX do arquivo de entrada .geo*/
int lerNX(FILE *arq);

/*Le o parametro do arquivo de entrada .geo para definir a forma geometrica a ser desenhada*/
void lerFormaGeometrica(FILE *arq, char *forma);

/*Le as informacoes de circulo do arquivo .geo e armazena na struct*/
void lerCirculo(FILE *arqIn, Formas figuras[], FILE *arqOut, FILE *arqOut2);

/*Le as informacoes de retangulo do arquivo .geo e armazena na struct*/
void lerRetangulo(FILE *arqIn, Formas figuras[], FILE *arqOut, FILE *arqOut2);

/*Le as informacoes de texto do arquivo .geo e armazena em variaveis locais*/
void lerTexto(FILE *arqIn, FILE *arqOut, FILE *arqOut2);

/*Le qual o comando de consulta do arquivo qry*/
void lerQry(FILE *arqConsul, char q[]);

/*Le os parametros de consulta do comando "o?"*/
void lerO(FILE *arqConsul, int *j, int *k);

/*Le os parametros de consulta do comando "i?"*/
void lerI(FILE *arqConsul, int *j, double *x, double *y);

/*Le os parametros de consulta do comando "d?"*/
void lerD(FILE *arqConsul, int *j, int *k);

/*Le os parametros de consulta do comando "bb"*/
void lerBB(FILE *arqConsul, char sufixo[], char cor[]);

#endif