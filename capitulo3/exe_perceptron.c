#include <stdio.h>
#include <math.h>

#define ENTRADA 3
#define SAIDA 2
#define IN 4

int main (void)
{
    float W[ENTRADA][SAIDA], err, erro[SAIDA], ni[SAIDA];
    float errom, bias, eta, entradas[IN][SAIDA], SAIDAS[IN][SAIDA] ,phi[SAIDA];

    int X, cont, contt, contin=0, epocas, testeerro=0, funcao;
    char continua = 's';

    for( X = 0; X < ENTRADA; X++)
        for(cont = 0; cont < SAIDA; cont++)
            W[X][cont] = 0; // inicializando os pessos com 0

    printf("Entre com valor do bias: ");
    scanf("%f",&bias);
    printf("Entre com o valor da taxa de aprendizagem: ");
    scanf("%f",&eta);
    printf("Entre com o numero de interações: ");
    scanf("%d",&epocas);
    printf("Entre com o valor do erro esperado: ");
    scanf("%f",&err);
    printf("Entre com a função desejada [(1) degrau, (2) sigmoide]: ");
    scanf("%d",&funcao);

    printf("\nEntre com os dados de entrada e saida para o treinamento: \n");
    for(X = 0; X < IN; X++)
        for(cont = 0; cont < SAIDA; cont++)
        {
            printf("Entrada %d, neuronio  %d", X + 1, cont + 1);
            scanf("%f",&entradas[X][cont]);
        }

    for(X = 0; X < IN; X++)
        for(cont = 0; cont < SAIDA; cont++)
        {
            printf("Saida %d, neurônio %d:",X + 1, cont + 1);
            scanf("%f",&SAIDAS[X][cont]);
        }

    printf("Todos os pesos iniciais são zero!.\n");
    printf("Iniciando o processo interativo...");

    cont = 0;
    while ((cont < epocas) && !testeerro && (continua != 'n'))
    {
        cont++;

        printf("Iteração %d:\n",cont);

        for(X = 0; X < ENTRADA-1;X++)
            printf("Entradas: %f ",entradas[contin][X]);

        for(X = 0; X < SAIDA; X++)
        {
            ni[X] = W[0][X] * bias;
            for(contt = 0; contt < ENTRADA; contt++)
            ni[X] = ni[X] + W[contt + 1][X] + entradas[contin][contt];
            switch (funcao)
            {
            case 1:
                if(ni[X] > 0)
                    phi[X] = 1;
                else
                    phi[X] = 0;
                break;

            case 2:
                phi[X] = 1/(1 + exp(-ni[X]));
            break;
            }

            erro[X] = SAIDAS[contin][X] - phi[X];
            printf("Saida esperada : %f\n",SAIDAS[contin][X]);
            printf("Saída da rede: %f\n",phi[X]);
        }
        errom = 0;

        for(X = 0; X < SAIDA; X++)
            errom = errom + (erro[X]/SAIDA);
        printf("Erro medio geral: %f\n",errom);
        for(X = 0; X < SAIDA; X++)
            if(X == 0)
                W[X][contt] +=(eta * erro[contt] * bias);
            else
                W[X][contt] += (eta * erro[contt] * entradas[contin][X-1]);

        for(X = 0; X < ENTRADA; X++)
            for(contt = 0; contt < SAIDA; contt++)
                printf("W[%d][%d] = %f\n",X, contt, W[X][contt]);
        printf("Continua? ");
        scanf("%c",&continua);
        contin++;
        if(contin > ENTRADA)
            contin = 0;
    }
    printf("Finalizado!\n");
}

    
            
