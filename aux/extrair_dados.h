#ifndef EXTRAIRDADOS_H
#define EXTRAIRDADOS_H

struct entrada
{
    double **dados;
    int nlins;
    int ncols;
    char end[30]; 
};
typedef struct entrada data;

int extrair (data *input);

void libera_dados (data *input);

void imprime (data input);

#endif