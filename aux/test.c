#include "extrair_dados.h"
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    int a = -1;
    double b = -1.0000;

    if(a == b)
        printf("Certo!!\n");
    else
        printf("Erro!!\n");
    return 0;

    data input;
    printf("Entre com endereço: ");
    setbuf(stdin,NULL);
    fgets(input.end, 30, stdin);
    
}
