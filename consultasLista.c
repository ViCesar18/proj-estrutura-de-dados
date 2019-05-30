#include "consultasLista.h"

void verificarDQ(FILE *txt, FILE *svg2, Lista blocks, char metrica[], Form circulo){
    Block block;
    int tam = getTam(blocks);
    Form anel1 = criarCirculo("0", getFormX(circulo), getFormY(circulo), 18, "green", "none", "5");
    Form anel2 = criarCirculo("0", getFormX(circulo), getFormY(circulo), 13, "lightgreen", "none", "5");

    fprintf(txt, "dq %s %lf\n", metrica, getFormR(circulo));
    fprintf(txt, "\tEquipamento Urbano: %s (%lf %lf)\n", getFormId(circulo), getFormX(circulo), getFormY(circulo));
    printarCirculo(svg2, anel1);
    printarCirculo(svg2, anel2);

    free(anel1);
    free(anel2);

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

void verificarCBQ(FILE *txt, Lista blocks, Form circulo, char cstrk[]){
    Block block;
    
    fprintf(txt, "cbq %lf %lf %lf %s\n", getFormX(circulo), getFormY(circulo), getFormR(circulo), cstrk);
    for(int i = getFirst(blocks); i != getNulo(); i = getProx(blocks, i)){
        block = getElementoByIndex(blocks, i);
        if(quadInsideCirc(block, circulo, "L2")){
            setBlockStrokeCollor(block, cstrk);
            fprintf(txt, "\tCor da borda da quadra alterada: %s\n", getBlockCep(block));
        }
    }
}

void verificarTRNS(FILE *txt, Lista blocks, Lista hydrants, Lista semaphores, Lista radios, Form retangulo, double dx, double dy, FILE *svg2){
    Block block;
    Hydrant hydrant;
    Semaphore semaphore;
    Radio radio;

    for(int i = getFirst(blocks); i != getNulo(); i = getProx(blocks, i)){
        block = getElementoByIndex(blocks, i);
        if(quadInsideRect(block, retangulo)){
            setBlockX(block, getBlockX(block) + dx);
            setBlockY(block, getBlockY(block) + dy);
        }
    }

    for(int i = getFirst(hydrants); i != getNulo(); i = getProx(hydrants, i)){
        hydrant = getElementoByIndex(hydrants, i);
        if(pontoInsideFigura(getHydrantX(hydrant), getHydrantY(hydrant), retangulo, "r", "L2")){
            setHydrantX(hydrant, getHydrantX(hydrant) + dx);
            setHydrantY(hydrant, getHydrantY(hydrant) + dy);
        }
    }

    for(int i = getFirst(semaphores); i != getNulo(); i = getProx(semaphores, i)){
        semaphore = getElementoByIndex(semaphores, i);
        if(pontoInsideFigura(getHydrantX(semaphore), getHydrantY(semaphore), retangulo, "r", "L2")){
            setHydrantX(semaphore, getSemaphoreX(semaphore) + dx);
            setHydrantY(semaphore, getSemaphoreY(semaphore) + dy);
        }
    }

    for(int i = getFirst(radios); i != getNulo(); i = getProx(radios, i)){
        radio = getElementoByIndex(radios, i);
        if(pontoInsideFigura(getHydrantX(radio), getHydrantY(radio), retangulo, "r", "L2")){
            setHydrantX(radio, getRadioX(radio) + dx);
            setHydrantY(radio, getRadioY(radio) + dy);
        }
    }
}