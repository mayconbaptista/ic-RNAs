#include "funcAtivacao.h"
#include <math.h>

int fun_degral (double *dados,RNA *rna)
{
    double soma=0;
    for(int i = 0; i < rna->tam_pesos; i++)
    {
        soma += (dados[i]) * (rna->pesos[i]);
    }

    soma = soma - rna->bias;
    if(soma >= 0)
        return 1;
    else
        return 0;
}

int fun_degral_bipolar (double *dados,RNA *rna)
{
    double soma=0;
    for(int i = 0; i < rna->tam_pesos; i++)
        soma += (dados[i]) * (rna->pesos[i]);

    soma = soma - rna->bias;
    if(soma >= 0)
        return 1;
    else
        return-1;
}

