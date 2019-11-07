#include "inSVG.h"

void checkFile(FILE *arq, char fname[]){

    if(arq == NULL){
        printf("Arquivo nao encontrado: %s\n", fname);
        exit(1);
    }
}

void receiveParameters(int argc, char *argv[], char **pathIn, char **nameIn, char **nameConsulta, char **pathOut){
    int i = 1;

    while(i < argc){
        if(strcmp("-e", argv[i]) == 0){
            i++;
            *pathIn = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*pathIn, argv[i]);
        }
        else if(strcmp("-f", argv[i]) == 0){
            i++;
            *nameIn = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*nameIn, argv[i]);
        }
        else if(strcmp("-q", argv[i]) == 0){
            i++;
            *nameConsulta = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*nameConsulta, argv[i]);
        }
        else if(strcmp("-o", argv[i]) == 0){
            i++;
            *pathOut = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*pathOut, argv[i]);
        }
        i++;
    }
}

void treatFileName(char nameIn[], char **nameInT){
    int i = 0, j = 0, save;
    bool valid = false;

    *nameInT = (char *)malloc((strlen(nameIn) + 1) * sizeof(char));
    if(nameIn[0] == '.'){
        if(nameIn[1] == '.')
            i = 2;
        else
            i = 1;
    }

    while(1){
        if(nameIn[i] == '/'){
            save = i;
            valid = true;
        }
        else if(nameIn[i] == '.' && i != 0){
            if(valid){
                save++;
                break;
            }
            else{
                strcpy(*nameInT, nameIn);
                return;
            }
        }
        i++;
    }
    while(nameIn[save] != '\0'){
        (*nameInT)[j] = nameIn[save];
        j++;
        save++;
    }
}

void allocateFileMamory(char fname[], char path[], char **arq){

    if(path[strlen(path) - 1] == '/'){
        *arq = (char *)malloc((strlen(path) + strlen(fname) + 1) * sizeof(char));
        sprintf(*arq, "%s%s", path, fname);
    }
    else{
        *arq = (char *)malloc((strlen(path) + strlen(fname) + 2) * sizeof(char));
        sprintf(*arq, "%s/%s", path, fname);
    }

}

void scanNX(FILE *arq, int *nx, int *nq, int *nh, int *ns, int *nr, int *np, int *nm){

    fscanf(arq, "%d", nx);
    fscanf(arq, "%d", nq);
    fscanf(arq, "%d", nh);
    fscanf(arq, "%d", ns);
    fscanf(arq, "%d", nr);
    fscanf(arq, "%d", np);
    fscanf(arq, "%d", nm);
}

void scanCircle(FILE *arqIn, Tree figures, char cw[]){
    char id[32];
    double r, x, y;
    char strokeColor[24], fillColor[24];

    fscanf(arqIn, "%s", id);
    fscanf(arqIn, "%lf", &r);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);
    fscanf(arqIn, "%s", strokeColor);
    fscanf(arqIn, "%s", fillColor);

    Form circle = createCircle(id, x, y, r, strokeColor, fillColor, cw);

    insertNode(figures, circle);
}

void scanRect(FILE *arqIn, Tree figures, char rw[]){
    char id[32];
    double x, y, w, h;
    char strokeColor[24], fillColor[24];

    fscanf(arqIn, "%s", id);
    fscanf(arqIn, "%lf", &w);
    fscanf(arqIn, "%lf", &h);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);
    fscanf(arqIn, "%s", strokeColor);
    fscanf(arqIn, "%s", fillColor);

    Form rect = createRect(id, x, y, w, h, strokeColor, fillColor, 0, rw);

    insertNode(figures, rect);
}

void scanBlock(FILE *arqIn, Tree blocks, char fillColor[], char strokeColor[], char sw[]){
    char cep[64];
    double x, y, w, h;

    fscanf(arqIn, "%s", cep);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);
    fscanf(arqIn, "%lf", &w);
    fscanf(arqIn, "%lf", &h);

    Block block = createBlock(cep, x, y, w, h, strokeColor, fillColor, sw);

    insertNode(blocks, block);
}

void scanHydrant(FILE *arqIn, Tree hydrants, char fillColor[], char strokeColor[], char sw[]){
    char id[32];
    double x, y;

    fscanf(arqIn, "%s", id);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);

    Hydrant hydrant = createHydrant(id, x, y, strokeColor, fillColor, sw);

    insertNode(hydrants, hydrant);
}

void scanTrafficLight(FILE *arqIn, Tree tLights, char fillColor[], char strokeColor[], char sw[]){
    char id[32];
    double x, y;

    fscanf(arqIn, "%s", id);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);

    TrafficLight tLight = createTrafficLight(id, x, y, strokeColor, fillColor, sw);

    insertNode(tLights, tLight);
}

void scanRadioTower(FILE *arqIn, Tree rTowers, char fillColor[], char strokeColor[], char sw[]){
    char id[32];
    double x, y;

    fscanf(arqIn, "%s", id);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);

    RadioTower rTower = createRadioTower(id, x, y, strokeColor, fillColor, sw);

    insertNode(rTowers, rTower);
}

void changeColor(FILE *arqIn, char fillColor[], char strokeColor[], char sw[]){

    fscanf(arqIn, "%s", fillColor);
    fscanf(arqIn, "%s", strokeColor);
    fscanf(arqIn, "%s", sw);
}

void changeThickness(FILE *arqIn, char cw[], char rw[]){

    fscanf(arqIn, "%s", cw);
    fscanf(arqIn, "%s", rw);
}

void scanBuilding(FILE *arqIn, Tree buildings, Tree blocks){
    char cep[32], face[2];
    int num;
    double faceSize, depth, margin;

    fscanf(arqIn, "%s", cep);
    fscanf(arqIn, "%s", face);
    fscanf(arqIn, "%d", &num);
    fscanf(arqIn, "%lf", &faceSize);
    fscanf(arqIn, "%lf", &depth);
    fscanf(arqIn, "%lf", &margin);

    Building building = createBuilding(cep, face, num, faceSize, depth, margin, blocks);

    insertNode(buildings, building);
}

void scanWall(FILE *arqIn, Tree walls){
    double x1, y1, x2, y2;

    fscanf(arqIn, "%lf", &x1);
    fscanf(arqIn, "%lf", &y1);
    fscanf(arqIn, "%lf", &x2);
    fscanf(arqIn, "%lf", &y2);

    Wall wall = createWall(x1, y1, x2, y2);
    
    insertNode(walls, wall);
}

void scanText(FILE *arqIn, FILE *arqOut, FILE *arqOut2){
    double x, y;
    char text[128];

    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);
    fgets(text, 128, arqIn);

    printText(arqOut, x, y, text, "black");
    if(arqOut2 != NULL)
        printText(arqOut2, x, y, text, "black");
}

void scanO(FILE *arqQuery, char j[], char k[]){

    fscanf(arqQuery, "%s", j);
    fscanf(arqQuery, "%s", k);
}

void scanI(FILE *arqQuery, char j[], double *x, double *y){

    fscanf(arqQuery, "%s", j);
    fscanf(arqQuery, "%lf", x);
    fscanf(arqQuery, "%lf", y);
}

void scanD(FILE *arqQuery, char j[], char k[]){

    fscanf(arqQuery, "%s", j);
    fscanf(arqQuery, "%s", k);
}

void scanBB(FILE *arqQuery, char suffix[], char color[]){

    fscanf(arqQuery, "%s", suffix);
    fscanf(arqQuery, "%s", color);
}

void scanDQ(FILE *arqQuery, char metric[], char id[], double *r){

    fscanf(arqQuery, "%s", metric);
    fscanf(arqQuery, "%s", id);
    fscanf(arqQuery, "%lf", r);
}

Element scanCBQ(FILE *arqQuery, char cstrk[]){
    double x, y, r;

    fscanf(arqQuery, "%lf", &x);
    fscanf(arqQuery, "%lf", &y);
    fscanf(arqQuery, "%lf", &r);
    fscanf(arqQuery, "%s", cstrk);

    Form circle = createCircle("0", x, y, r, "black", "none", "1");

    return circle;
}

Element scanTRNS(FILE *arqQuery, double *dx, double *dy){
    double x, y, w, h;

    fscanf(arqQuery, "%lf", &x);
    fscanf(arqQuery, "%lf", &y);
    fscanf(arqQuery, "%lf", &w);
    fscanf(arqQuery, "%lf", &h);
    fscanf(arqQuery, "%lf", dx);
    fscanf(arqQuery, "%lf", dy);

    Form rect = createRect("0", x, y, w, h, "black", "none", 0, "1");

    return rect;
}

void scanFI(FILE *arqQuery, double *x, double *y, int *n, double *r){

    fscanf(arqQuery, "%lf", x);
    fscanf(arqQuery, "%lf", y);
    fscanf(arqQuery, "%d", n);
    fscanf(arqQuery, "%lf", r);
}

void scanFHFS(FILE *arqQuery, int *k, char cep[], char face[], int *num){

    fscanf(arqQuery, "%d", k);
    fscanf(arqQuery, "%s", cep);
    fscanf(arqQuery, "%s", face);
    fscanf(arqQuery, "%d", num);
}

void scanBRL(FILE *arqQuery, double *x, double *y){

    fscanf(arqQuery, "%lf", x);
    fscanf(arqQuery, "%lf", y);
}