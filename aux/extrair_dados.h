#ifndef EXTRAIRDADOS_H
#define EXTRAIRDADOS_H

struct entrada
{
    double **dados;
    int N_amostras;// tamanho linhas
    int N_entradas;// tamanho de colunas
    char end[30]; // endereço dos dados
};
typedef struct entrada data;

int extrair (data *input);

void libera_dados (data *input);

void imprime (data input);

#endif