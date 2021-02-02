#ifndef FUNCATIVACAO_H
#define FUNCATIVACAO_H

typedef struct dados_neuronios
{
    double *pesos;
    double bias;
    double taxa;
    double precisao;
    int tam_pesos;
    int epoca;
}RNA;

int fun_degrau (double *dados,RNA *rna);

int fun_degrau_bipolar (double *dados,RNA rna);

#endif