#include "queryUtils.h"

void treatDMPRBT(char *type, char *pName, char *pathOut, Tree blocks, Tree hydrants, Tree tLights, Tree rTowers, Tree buildings, Tree walls){
    char *fileName;
    char *tName;

    createOutputFileName(&tName, pName);
    strcat(tName, ".svg");
    allocateFileMamory(tName, pathOut, &fileName);

    FILE* file = fopen (fileName, "w");

    if (!strcmp (type, "q")) printTreeInSVG (blocks, file, getBlockInformation);
    else if (!strcmp (type, "h")) printTreeInSVG (hydrants, file, getHydrantInformation);
    else if (!strcmp (type, "s")) printTreeInSVG (tLights, file, getTrafficLightInformation);
    else if (!strcmp (type, "t")) printTreeInSVG (rTowers, file, getRadioTowerInformation);
    else if (!strcmp (type, "p")) printTreeInSVG (buildings, file, getBuildingInformation);
    else if (!strcmp (type, "m")) printTreeInSVG (walls, file, getWallInformation);
    else printf ("Arvore nao encontrada!\n");

    free(tName);
    free(fileName);
    fclose (file);
}