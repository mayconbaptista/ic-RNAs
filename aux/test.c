#include "extrair_dados.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

double sigmoide (const double *dados, const double *pesos, int size)
{
    double soma = 0;
    for(int i = 0; i < size; i++)
        soma += dados[i] * pesos[i];
    soma -= pesos[size];
    soma = 1/(pow())
}


int main (void)
{
    data input;
    strcpy(input.end,"./aux/apendice3_5-8.txt\n");
    int result = extrair(&input);
    if(result == 0)
    {
        imprime(input);
        libera_dados(&input);
    }
    else
        printf("Erro na leitura\n");
    return 0;
}