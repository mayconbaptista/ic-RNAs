#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "../aux/extrair_dados.h"
#include "../funcAtivacao.h"

void test_pendice1 (RNA rna)
{
    double vet[10][3] = {{-0.3665, 0.0620, 5.991},
                        {-0.7842, 1.1267, 5.5952},
                        {0.3012, 0.5611, 5.8234},
                        {0.7757, 1.0648, 8.0677},
                        {0.1570, 0.8028, 6.3040},
                        {-0.7014, 1.0316, 3.6005},
                        {0.3748, 0.1536, 6.1537},
                        {-0.6920, 0.9404, 4.4058},
                        {1.3970, 0.7141, 4.9263},
                        {-1.8842, -0.2805, 1.2548}};
    int result;
    for(int i = 0; i < 10; i++)
    {
        printf("%d volta : ",i+1);
        result = fun_degrau_bipolar(vet[i], rna);
        if(result == -1)
            printf("-1 classe P1\n");
        else
            printf("1 classe P2\n");
    }
    return;
}

void questao4 (RNA rna)
{
    
    double vet[15][4] = {{0.9694, 0.6909, 0.4334, 3.4965},
                        {0.5427, 1.3832, 0.6390, 4.0352},
                        {0.6081, -0.9196, 0.5925, 0.1016},
                        {-0.1618, 0.4694, 0.2030, 3.0117},
                        {0.1870, -0.2578, 0.6124, 1.7749},
                        {0.4891, -0.5296, 0.4378, 0.639},
                        {0.3777, 2.0149, 0.7423, 3.3932},
                        {1.1498, -0.4067, 0.2469, 1.5866},
                        {0.9325, 1.0950, 1.0359, 3.3591},
                        {0.5060, 1.3317, 0.9222, 3.7174},
                        {0.0497, -2.0656, 0.6124, -0.6585},
                        {0.4004, 3.5369, 0.9766, 5.3532},
                        {-0.1874, 1.3343, 0.5374, 3.2189},
                        {0.5060, 1.3317, 0.9222, 3.7174},
                        {1.6375, -0.7911, 0.7537, 0.5515}};
    int result;
    for(int i = 0; i < 15; i++)
    {
        result = fun_degrau_bipolar(vet[i], rna);
        if(result == -1)
            printf("-1 classe A\n");
        else
            printf("1 Classe B\n");
    }
    return;
}

void acompanha (RNA rna)
{
    printf("valor dos pesos: ");
    for(int i = 0; i < rna.tam_pesos; i++)
    {
        printf("%.4lf\t",rna.pesos[i]);
    }
    printf("Bias %.4lf\n",rna.bias);
    return;
}

double funcao_EQM (RNA *rna,data *input)
{
    double soma, eqm=0;
    for(int i = 0; i < input->nlins; i++)
    {
        soma = 0;
        for(int j = 0; j < input->ncols-1; j++)
            soma += rna->pesos[j] * input->dados[i][j];
        soma = soma - rna->bias;
        eqm += pow((input->dados[i][input->ncols-1] - soma),2);
    }
    eqm = eqm / input->nlins; 
    return eqm;
}

int adaline (RNA *rna)
{
    data input;
    strcpy(input.end,"./aux/apendice2.txt\n");

    int temp = extrair(&input);
    if(temp != 0)
    {
        printf("Erro na leitura\n");
        return -1;
    }

    rna->tam_pesos = input.ncols-1;
    rna->pesos = (double*) malloc (rna->tam_pesos*sizeof(double));
    srand(time(NULL));
    for(int i = 0; i < rna->tam_pesos; i++)
    {
        rna->pesos[i] = rand() % 1000;
        rna->pesos[i] /= 1000;
    }
    rna->bias = rand() % 1000;
    rna->bias /= 1000;
    acompanha((*rna));// acompanha os valores dos pesos inicias

    double eqm_atual, eqm_ant, soma, sinal; // variaveis auxiliares
    for(int cont = 0; cont < rna->epoca; cont++)
    {
        eqm_ant = funcao_EQM(rna, &input);
        //printf("Eqm na epoca %d %.4lf\n",cont+1,eqm_atual);
        for(int i = 0; i < input.nlins; i++)
        {
            soma = 0;
            for(int j = 0; j < input.ncols-1; j++)
            {
                soma += rna->pesos[j] * input.dados[i][j];
            }
            soma -= rna->bias;
            for(int j = 0; j < input.ncols-1; j++)
            {
                rna->pesos[j] += rna->taxa *(input.dados[i][input.ncols-1] - soma) * input.dados[i][j];
            }
            rna->bias += rna->taxa * (input.dados[i][input.ncols-1] - soma) * (-1);
        }
        eqm_atual = funcao_EQM (rna, &input);
        if(fabs(eqm_atual - eqm_ant) <= rna->precisao)
        {
            acompanha((*rna));
            printf("Epocas %d\n",cont);
            libera_dados(&input);
            return 0; // sucesso
        }
    }
    libera_dados(&input);
    return -1; // erro
}

int main (void)
{
    RNA rna;
    int result;
    //printf("entre com a taxa de aperndizado: ");
    //scanf("%lf",&rna.taxa);
    rna.taxa = 0.0025;
    ///printf("entre com o numero maximo de épocas: ");
    //scanf("%d",&rna.epoca);
    rna.epoca = 1000;
    //printf("Entre com a precisão: ");
    //scanf("%lf",&rna.precisao);
    rna.precisao = 0.000001;

    result = adaline(&rna);
    questao4(rna);
    
    /*
    if(result == 0)
    {
        double vet[rna.tam_pesos];
        char coninuar;
        do{
            printf("Entre com %d dados para conferir: ",rna.tam_pesos);
            for(int i = 0; i < rna.tam_pesos; i++)
                scanf("%lf",&vet[i]);
            if(fun_degrau_bipolar(vet, rna) == -1)
                printf("-1 Valvula A\n");
            else
                printf("1 Valvula B\n");
            printf("Deseja continuar (s/n)?: ");
            setbuf(stdin, NULL);
            scanf("%c",&coninuar);

        }while(coninuar != 'n');
    }
    else
        printf("Erro! no terinamento\n");
    */
    free(rna.pesos);
    return 0;
}