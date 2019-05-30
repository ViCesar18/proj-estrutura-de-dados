#ifndef IN_SVG
#define IN_SVG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "outSVG.h"
#include "lista.h"
#include "forms.h"
#include "block.h"
#include "hydrant.h"
#include "semaphore.h"
#include "radio.h"

/*Nesse header encontra-se todas as funcoes relacionadas a entrada/leitura de dados*/

/*Verifica se o arquivo em questao foi aberto com sucesso, caso contrario, sai do programa*/
void verificarArquivo(FILE *arq, char nome[]);

/*Funcao que recebe os parametros digitados do terminal*/
void receberParametros(int argc, char *argv[], char **pathIn, char **nameIn, char **nameConsulta, char **pathOut);

/*Trata o nome do arquivo geo/qry caso ele seja passado como parametro junto com um diretorio relativo*/
void tratarNome(char nameIn[], char **nameInT);

/*aloca memoria e cria os diretorios, tambem verifica se a '/' foi ou nao inserida*/
void alocarMemoria(char nome[], char dir[], char **arq);

/*Le os valores de NX do arquivo de entrada .geo*/
void lerNX(FILE *arq, int *nx, int *nq, int *nh, int *ns, int *nr);

/*Le as informacoes de circulo do arquivo .geo e armazena na lista figuras*/
void lerCirculo(FILE *arqIn, Lista figuras, char cw[]);

/*Le as informacoes de retangulo do arquivo .geo e armazena na lista figuras*/
void lerRetangulo(FILE *arqIn, Lista figuras, char rw[]);

/*Le as informacoes de quadra do arquivo .geo e armazena na lista blocks*/
void lerQuadra(FILE *arqIn, Lista blocks, char strokeCollor[], char fillCollor[], char sw[]);

/*Le as informacoes de hidrante do arquivo .geo e armazena na lista hydrants*/
void lerHidrante(FILE *arqIn, Lista hydrants, char fillCollor[], char strokeCollor[], char sw[]);

/*Le as informacoes de semaforo do arquivo .geo e armazena na lista semaphores*/
void lerSemaforo(FILE *arqIn, Lista semaphores, char fillCollor[], char strokeCollor[], char sw[]);

/*Le as informacoes de radio-base do arquivo .geo e armazena na lista radios*/
void lerRadio(FILE *arqIn, Lista radios, char fillCollor[], char strokeCollor[], char sw[]);

/*Muda a cor de todos os elementos que vierem abaixo do comando ch do arquivo .geo*/
void alterarCor(FILE *arqIn, char fillCollor[], char strokeCollor[], char sw[]);

/*Muda a espessura de todos os circulos e retangulos que vierem abaixo do comando sw do arquivo .geo*/
void alterarEspessura(FILE *arqIn, char cw[], char rw[]);

/*Le as informacoes de texto do arquivo .geo e armazena em variaveis locais*/
void lerTexto(FILE *arqIn, FILE *arqOut, FILE *arqOut2);

/*Le os parametros de consulta do comando "o?"*/
void lerO(FILE *arqConsul, char j[], char k[]);

/*Le os parametros de consulta do comando "i?"*/
void lerI(FILE *arqConsul, char j[], double *x, double *y);

/*Le os parametros de consulta do comando "d?"*/
void lerD(FILE *arqConsul, char j[], char k[]);

/*Le os parametros de consulta do comando "bb"*/
void lerBB(FILE *arqConsul, char sufixo[], char cor[]);

/*Le os parametros de consulta do comando "dq"*/
void lerDQ(FILE *arqConsul, char L[], char id[], double *r);

/*Le os parametros de consulta do comando "cbq" e retorna um circulo com os parametros passados*/
Elemento lerCBQ(FILE *arqConsul, char cstrk[]);

/*Le os parametros de consulta do comando "trns" e retorna um retangulo com os parametros passados*/
Elemento lerTRNS(FILE *arqConsul, double *dx, double *dy);

#endif