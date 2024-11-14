#include<stdio.h>
#include<stdlib.h>
#include<time.h>


void cria_arquivo_txt(char log[100]){
    FILE *arquivo = fopen(log, "w");
    if(arquivo == NULL) exit(1);
    time_t hora;
    hora = time(NULL);
    struct tm dt = *localtime(&hora);
    fprintf(arquivo, "Data: %d/%d/%d\n",dt.tm_mday,dt.tm_mon+1,dt.tm_year+1900);
    fprintf(arquivo, "Tempo inicio: %d:%d:%d\n",dt.tm_hour,dt.tm_min,dt.tm_sec);
    
    fclose(arquivo);

}
FILE*  escreve_arquivo_txt(char log[100]){
    FILE* arquivo = fopen(log, "a");
    if(arquivo == NULL) exit(1);
    return arquivo;

}
void escreve_matriz_no_txt(int ordem, int **mat, char log[100], int valorEscondido){
    FILE *arquivo = fopen(log, "a");
    if(arquivo == NULL) exit(1);
    time_t hora;
    hora = time(NULL);
    struct tm dt = *localtime(&hora);
    fprintf(arquivo,"     ");
    for(int x = 1; x <= ordem; x++){
        if(x <= 10){
         fprintf(arquivo," %d ",x);
        }
        else{
            fprintf(arquivo,"%d ", x);
        }
    }

    fprintf(arquivo,"\n");
    fprintf(arquivo,"     ");
    for(int i = 0; i < ordem; i++){
        fprintf(arquivo,"---");
    }
    fprintf(arquivo,"\n");

    for(int i = 0; i < ordem; i++){

        if(i+1 < 10){ 
            fprintf(arquivo,"%d |  ",i+1);
        }
        else{ 
            fprintf(arquivo,"%d|  ",i+1);
        }

        for(int j = 0; j < ordem; j++){
            if(mat[i][j] == valorEscondido){ 
                fprintf(arquivo, " X ");
            }
            else if(mat[i][j] < 0  ){ 
                fprintf(arquivo,"%d ", mat[i][j]);
            }
            else{ 
                fprintf(arquivo," %d ", mat[i][j]);
            }
        }
        fprintf(arquivo,"\n");
        
    }
    fprintf(arquivo, "\nData: %d/%d/%d\n",dt.tm_mday,dt.tm_mon+1,dt.tm_year+1900);
    fprintf(arquivo, "Tempo atual: %d:%d:%d\n",dt.tm_hour,dt.tm_min,dt.tm_sec);
    fclose(arquivo);
}