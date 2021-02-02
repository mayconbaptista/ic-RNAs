#include "extrair_dados.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void)
{
    data dados;
    strcpy(dados.end,"./aux/apendice2.txt\n");
    int res = extrair(&dados);
    if(res == 0)
    {
        for(int i = 0; i < dados.nlins; i++)
        {
            for(int j = 0; j < dados.ncols; j++)
            {
                printf("%.4lf\t");
            }
        }
        libera_dados(&dados);
    }
    else
        printf("Erro!\n");
    return 0;
}

int resultado (data dados)
{
    double soma, pesos[dados.ncols-1];
    for(int i = 0; i < dados.nlins; i++)
    {
        soma = 0;
        for(int j = 0; j < dados.ncols; j++)
        {
            soma += dados
        }
    }
}
