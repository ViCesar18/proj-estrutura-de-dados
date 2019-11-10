#include "interactive.h"

void console () {
    char comando[32], arg1[16], arg2[16], arg3[16];
    while (1){
        printf ("Insira o comando: ");
        fgets (comando, 32, stdin);
        sscanf (comando, "%s %s %s", arg1, arg2, arg3);

        if (strcmp (arg1, "sai") == 0) break;

        else if (strcmp (arg1, "q") == 0){
            printf ("arq: %s\n", arg2);
        }

        else if (strcmp (arg1, "dmprbt") == 0){
            printf ("t: %s arq: %s\n", arg2, arg3);
        }

        else if (strcmp (arg1, "nav") == 0){
            printf ("tree: %s\n", arg2);
        }

        else{
            printf ("Comando invalido\n");
        }

    }
    
    return;
}

