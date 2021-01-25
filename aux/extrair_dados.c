#include "extrair_dados.h"
#include <stdlib.h>
#include <stdio.h>

void remove_endl (data *input)
{
    if(input != NULL && input->end != NULL)
    {
        int i=0;
        while(input->end[i] != '\n' && i < 29)
            i++;

        input->end[i] = '\0';
    }
}

int extrair (data *input)
{
    if(input == NULL)
        return -1;
    else
    {
        remove_endl(input);
        FILE *arg = fopen(input->end,"r");
        if(arg == NULL)
            return -2;
        else
        {
            fscanf(arg, "%d %d\n",&input->nlins,&input->ncols);
            input->dados = (double**) malloc (input->nlins*sizeof(double*));

            for(int i = 0; i < input->nlins; i++)
                input->dados[i] = (double*) malloc (input->ncols*(sizeof(double)));

            for (int i = 0; i < input->nlins; i++)
            {
                for(int j = 0; j < input->ncols; j++)
                {
                    fscanf(arg,"%lf ",&input->dados[i][j]);
                }
            }
            fclose(arg);
            return 0;// sucess
        }
    }
}

void libera_dados (data *input)
{
    if(input != NULL)
    {
        for(int i = 0; i < input->nlins; i++)
        {
            free(input->dados[i]);
        }
        free(input->dados);
    }
}

void imprime (data input)
{
    if(input.dados != NULL)
    {
        for(int i = 0; i < input.nlins; i++)
        {
            for(int j = 0; j < input.ncols; j++)
            {
                printf("(lin-%d/col-%d) %.4lf",i,j,input.dados[i][j]);
            }
            printf("\n");
        }
    }
}