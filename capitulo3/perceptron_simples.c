#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "../funcAtivacao.h"
#include "../aux/extrair_dados.h"

#define SUCESS 0
#define ERRO -1
#define INVALID_IMPUT -2
#define OPEN_ARG_ERRO -3

void imprime_pesos (double *vet, double bias)
{
    for(int i = 0; i < 3; i++)
    {
        printf("%.4lf ",vet[i]);
    }
    printf("%.4lf\n",bias);
}


int supervisionado (RNA *rna,data *imput)
{
    if(rna == NULL || imput == NULL || imput == NULL)
        return INVALID_IMPUT;
    else
    {
        int result;
        char erro = 'n';
        for(int i = 0; i < imput->nlins; i++)// numero de epocas e msm linhas em dados
        {
            imprime_pesos(rna->pesos, rna->bias);
            result = fun_degral_bipolar (imput->dados[i], rna);
            if(result != imput->dados[i][imput->ncols-1])
            {
                for(int j = 0; j < imput->ncols-1; j++)
                    rna->pesos[j] += rna->taxa * (imput->dados[i][imput->ncols-1] - result) * imput->dados[i][j];
                
                rna->bias += rna->taxa * (imput->dados[i][imput->ncols-1] - result) * (-1);
                erro = 's';
            }   
            else 
                erro = 'n';
        }
        if(erro == 'n')
            return SUCESS;
        else
            return ERRO;
    }
}

int main (void)
{
    RNA rna;
    data input;
    int result;

    printf("Entre con o enreço dos dados: ");
    setbuf(stdin, NULL);
    fgets(input.end, 30, stdin);
    printf("Entre com taxa de aprendizagem: ");
    scanf("%lf",&rna.taxa);

    result = extrair(&input);
    if(result != SUCESS)
    {
        printf("Erro! ao obter dados de treinamento!\n");
        exit(1);
    }

    //imprime (input);
    rna.tam_pesos = input.ncols-1;
    rna.pesos = (double*) malloc (rna.tam_pesos*sizeof(double));// alocando o espaço para os pesos

    //inicializando os pesos e o bias 0<n<1;
    for(int i = 0; i < rna.tam_pesos; i++)
    {
        rna.pesos[i] = rand() % 1000;
        rna.pesos[i] /= 1000; 
    }
    rna.bias = rand () % 1000;
    rna.bias /= 1000; 

    result = supervisionado(&rna, &input);
    if(result != SUCESS)
    {
        free(rna.pesos);
        libera_dados (&input);
        printf("Erro! aprendizado imcompleto!\n");
        exit(1);
    }else
        printf("terinameno completado com sucesso!\n");//aqui
    
    double vet[input.ncols-1];
    char continua;

    do{
        printf("Entre com os dados\n");
        for(int i = 0; i < rna.tam_pesos; i++)
        {
            printf("%d : ",i+1);
            scanf("%lf",&vet[i]);
        }

        result = fun_degral_bipolar (vet, &rna);
        if(result == 1)
            printf("CLASSE A\n");
        else
            printf("CLASSE B\n");

        printf("Deseja continuar (s/n): ");
        setbuf(stdin, NULL);
        scanf("%c",&continua);
    }while(continua != 'n');

    free(rna.pesos);
    libera_dados (&input);
    return 0;
}
