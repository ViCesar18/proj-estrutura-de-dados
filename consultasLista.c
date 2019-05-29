#include "consultasLista.h"

void verificarDQ(FILE *txt, FILE *svg2, Lista blocks, char metrica[], Form circulo){
    Block block;
    int tam = getTam(blocks);
    Form anel1 = criarCirculo("0", getFormX(circulo), getFormY(circulo), 18, "green", "none", "5");
    Form anel2 = criarCirculo("0", getFormX(circulo), getFormY(circulo), 13, "lightgreen", "none", "5");

    fprintf(txt, "dq %s %lf\n", metrica, getFormR(circulo));
    fprintf(txt, "\tEquipamento Urbado: %s (%lf %lf)\n", getFormId(circulo), getFormX(circulo), getFormY(circulo));
    printarCirculo(svg2, anel1);
    printarCirculo(svg2, anel2);

    if(!strcmp(metrica, "L1")){
        for(int i = 0; i < tam; i++){
            block = getElementoByIndex(blocks, i);
            if(quadInsideCirc(block, circulo, "L1")){
                deletarElemento(blocks, getBlockCep(block));
                fprintf(txt, "\tQuadra Removida: %s\n", getBlockCep(block));
            }
        }
    }
    else if(!strcmp(metrica, "L2")){
        for(int i = 0; i < tam; i++){
            block = getElementoByIndex(blocks, i);
            if(quadInsideCirc(block, circulo, "L2")){
                deletarElemento(blocks, getBlockCep(block));
                fprintf(txt, "\tQuadra Removida: %s\n", getBlockCep(block));
            }
        }
    }
}