#include "extrair_dados.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

void imprime_dados (double *input,double *pesos, int lin, int col)
{
    printf("Linha %d: ",lin+1);
    for(int i = 0; i < col; i++)
    {
        printf("(%.4lf*%.4lf)+",input[i],pesos[i]);
    }
    return;
}

int main (void)
{
    data input;
    strcpy(input.end,"./aux/apendice2.txt\n");
    extrair(&input);


    double soma,u, eqm=0, pesos[input.ncols];
    srand(time(NULL));
    for(int i = 0; i < input.ncols; i++)
    {
        pesos[i] = rand() % 1000;
        pesos[i] /= 1000;
    }

    for(int i = 0; i < input.nlins; i++)
    {
        soma = 0;
        u = 0;
        for(int j = 0; j < input.ncols; j++)
        {
            soma += input.dados[i][j] * pesos[j];
        }
        u =soma - pesos[input.ncols-1];
        eqm += pow((input.dados[i][input.ncols-1] - soma),2);

        imprime_dados(input.dados[i], pesos, i, input.ncols);
        printf("soma: %.4lf sinal(U): %.4lf eqm: %.4lf\n",soma,u,eqm);
    }
    eqm /= input.nlins;
    printf("Valor final eqm = %.4lf\n",eqm);
    libera_dados(&input);
    return 0;
}

int main (void)
{
    double a=-1.0000;
    unsigned double b= a;
    
}