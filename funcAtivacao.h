#ifndef FUNCATIVACAO_H
#define FUNCATIVACAO_H

typedef struct dados_neuronios
{
    double *pesos;
    double bias;
    double taxa;
    int tam_pesos;
    int epoca;
}RNA;

int fun_degral (double *dados,RNA *rna);

int fun_degral_bipolar (double *dados,RNA *rna);

#endif