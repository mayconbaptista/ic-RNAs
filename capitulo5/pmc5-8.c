#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "../aux/extrair_dados.h"
#define NEPER 2.718281828459045
#define CONCLUIDO 0
#define INCONCLUIDO -1

typedef struct neuronio
{
    double **pesos_cmd1;
    double *pesos_cmd2;
    double *input_cmd2;
    double saida;
    double taxa;
    double presizao;
    int max_epocas;
    int size_cmd1;
}Neuronio;

// funçoes auxiliares
void imprime_pesos (const Neuronio *rna,data input);
void free_entrada_cmd2 (Neuronio *rna, data input);
void inicializa_pesos (Neuronio *rna, data *input);
void free_pesos (Neuronio *rna);

// s (x) = 1/ 1 + e^(-u)
double funcao_sigmoide (const double *input, const double *pesos, int tamanho)
{
    double soma=0;
    for(int i = 0; i < tamanho; i++)
        soma += input[i] * pesos[i];
    soma -= pesos[tamanho]; // bias
    return (1/pow((1 + NEPER), -soma));
}

//  s'(x) = e^(-x)/(1 + e^-x)2   
double derivada_sigmoide (double *amostras,double *pesos, int size)
{
    double soma = 0;
    for(int i = 0; i < size; i++)
    {
        soma += amostras[i] * pesos[i];
    }
    soma -= pesos[size];// bias
    return (pow(NEPER, (-soma)) / pow(1 + pow(NEPER, (-soma)), 2));
}



// 5.7 & 5.8
double erro_medio (const data *input, const Neuronio *rna)
{
    double saida, EM_geral = 0;
    for(int amostra = 0; amostra < input->N_amostras; amostra++)
    {
        for(int neur = 0; neur < rna->size_cmd1; neur++)
        {
            rna->input_cmd2[neur] = funcao_sigmoide(input->dados[amostra], rna->pesos_cmd1[neur], (input->N_entradas-1));
        }
        saida = funcao_sigmoide(rna->input_cmd2, rna->pesos_cmd2, rna->size_cmd1);
        EM_geral += (pow((input->dados[amostra][input->N_entradas -1] - saida),2));
    }
    EM_geral /= input->N_amostras;
    return EM_geral;
}

int treinamento (Neuronio *rna)
{
    data input;
    strcpy(input.end,"./aux/apendice3_5-8.txt\n");
    int result = extrair(&input);
    if(result != 0)
    {
        printf("erro dados treinamento cod %d\n",result);
        return 0;
    }

    double EM_ant, EM_atual;// variaveis auxiliares para o erro medio
    double grd1, grd2;// vaiaveis auxiliares para o gradiente;
    inicializa_pesos(rna, &input);
    imprime_pesos(rna, input);
    for(int epoca_atual = 0; epoca_atual < rna->max_epocas; epoca_atual++)
    {
        EM_ant = erro_medio (&input, rna);
        for(int amostra = 0; amostra < input.N_amostras; amostra++)
        {
            for(int j = 0; j < rna->size_cmd1; j++)
            {
                rna->input_cmd2[j] = funcao_sigmoide(input.dados[amostra], rna->pesos_cmd1[j],(input.N_entradas-1));
            }
            rna->saida = funcao_sigmoide(rna->input_cmd2, rna->pesos_cmd2, rna->size_cmd1);
            // 5.15
            grd2 = (input.dados[amostra][input.N_entradas -1] - rna->saida) * derivada_sigmoide(rna->pesos_cmd2, rna->pesos_cmd2, rna->size_cmd1);
            printf("gradiente 2 %lf\n",grd2);

            // definição 5.17
            for(int w = 0; w < rna->size_cmd1; w++)
            {
                rna->pesos_cmd2[w] += rna->taxa * grd2 * rna->input_cmd2[w];  
            }
            //rna->pesos_cmd2[rna->size_cmd1] += rna->taxa * grd2 * (-1);// ajuste bias

            // definição 5.39
            for(int neur = 0; neur < rna->size_cmd1; neur++)
            {
                for(int peso = 0; peso < input.N_entradas-1; peso++)
                {
                    grd1 = grd2 * rna->pesos_cmd2[peso] * derivada_sigmoide(input.dados[amostra], rna->pesos_cmd1[neur], input.N_entradas-1);
                    printf("gradiente %lf\n",grd1);
                    rna->pesos_cmd1[neur][peso] += rna->taxa * grd1 * input.dados[amostra][peso];
                }
                rna->pesos_cmd1[neur][input.N_entradas-1] += rna->taxa * grd1 * (-1);
            }

        }
        EM_atual = erro_medio (&input, rna);
        printf("gradiente %.4lf\n",EM_ant);
        if(fabs(EM_atual - EM_ant) <= rna->presizao)
        {
            printf("Epoca %d\n",epoca_atual);
            free(rna->input_cmd2);
            libera_dados(&input);
            return CONCLUIDO;
        }
    }
    imprime_pesos(rna, input);
    free(rna->input_cmd2);
    libera_dados(&input);
    return INCONCLUIDO;
}


int main (void)
{
    // inicializando as N_entradass;
    Neuronio rna;
    rna.presizao = 0.000001;
    rna.taxa = 0.1;
    rna.max_epocas = 1;
    rna.size_cmd1 = 10;


    int result = treinamento (&rna);
    if(result == CONCLUIDO)
    {
        printf("concluido com sucesso!\n");    
    }
    else if(result == INCONCLUIDO)
    {
        printf("Treinamento incompleto!\n");
    }
    free_pesos(&rna);
    return 0;
}


// funçoes auxliares;
void inicializa_pesos (Neuronio *rna, data *input)
{
    // alocando os pesos da primeieira camada para cada neuronio
    rna->pesos_cmd1 = (double**) malloc (rna->size_cmd1*sizeof(double*));
    for(int neur = 0; neur < rna->size_cmd1; neur++)
    {
        rna->pesos_cmd1[neur] = (double*) malloc (input->N_entradas*sizeof(double));
    }

    // alocando os pesos da segunda camada
    rna->pesos_cmd2 = (double*) malloc ((rna->size_cmd1 + 1)*sizeof(double));

    srand(time(NULL));
    for(int neur = 0; neur < rna->size_cmd1; neur++)
    {
        for(int w = 0; w < input->N_entradas; w++)
        {
            rna->pesos_cmd1[neur][w] = rand() %1000;
            rna->pesos_cmd1[neur][w] /= 1000;
        }
    }
    
    for(int W = 0; W < rna->size_cmd1; W++)
    {
        rna->pesos_cmd2[W] = rand() % 1000;
        rna->pesos_cmd2[W] /= 1000;
    }
    rna->pesos_cmd2[rna->size_cmd1] = 0;

    // inicializando o vetor que sera entrada da ultima camada
    rna->input_cmd2 = (double*) malloc (rna->size_cmd1*sizeof(double));
}

void free_pesos (Neuronio *rna)
{
    for(int i = 0; i < rna->size_cmd1; i++)
        free(rna->pesos_cmd1[i]);
    free(rna->pesos_cmd1);
    free(rna->pesos_cmd2);
}

void imprime_pesos (const Neuronio *rna,data input)
{
    for(int i = 0; i < rna->size_cmd1; i++)
    {
        for(int j = 0; j < input.N_entradas; j++)
            printf("%.4lf\t",rna->pesos_cmd1[i][j]);
        printf("\n");
    }
    for(int i = 0; i < rna->size_cmd1; i++)
        printf("%.4lf\t",rna->pesos_cmd2[i]);
    printf("\n");
}