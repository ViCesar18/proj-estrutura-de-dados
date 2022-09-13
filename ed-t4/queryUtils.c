#include "queryUtils.h"

void treatDMPRBT(char *type, char *pName, char *pathOut, Tree blocks, Tree hydrants, Tree tLights, Tree rTowers, Tree buildings, Tree walls){
    char *fileName;
    char *tName;

    createOutputFileName(&tName, pName);
    strcat(tName, ".svg");
    allocateFileMamory(tName, pathOut, &fileName);

    FILE* file = fopen (fileName, "w");

    if (!strcmp (type, "q")) printTreeInSVG (blocks, file, getBlockInformation, getBlockTreeX, getBlockTreeY, setBlockTreeXY);
    else if (!strcmp (type, "h")) printTreeInSVG (hydrants, file, getHydrantInformation, getHydrantTreeX, getHydrantTreeY, setHydrantTreeXY);
    else if (!strcmp (type, "s")) printTreeInSVG (tLights, file, getTrafficLightInformation, getTrafficLightTreeX, getTrafficLightTreeY, setTrafficLightTreeXY);
    else if (!strcmp (type, "t")) printTreeInSVG (rTowers, file, getRadioTowerInformation, getRadioTowerTreeX, getRadioTowerTreeY, setRadioTowerTreeXY);
    else if (!strcmp (type, "p")) printTreeInSVG (buildings, file, getBuildingInformation, getBuildingTreeX, getBuildingTreeY, setBuildingTreeXY);
    else if (!strcmp (type, "m")) printTreeInSVG (walls, file, getWallInformation, getWallTreeX, getWallTreeY, setWallTreeXY);
    else printf ("Arvore nao encontrada!\n");

    free(tName);
    free(fileName);
    fclose (file);
}