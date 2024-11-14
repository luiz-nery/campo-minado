#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int** criaMatriz(int linha, int coluna);
void inicializaMatriz(int** mat, int valor,int linha, int coluna);
void imprimeMatriz(int ordem, int **mat, int valorEscondido);


int** criaMatriz(int linha, int coluna){
    int **mat = (int**) malloc(linha*sizeof(int*));//matriz que representa o campo minado
    if(mat == NULL){
        exit(1);
    }
    for(int i = 0; i < linha; i++){
        mat[i] = (int*) malloc(coluna*sizeof(int));
        if(mat[i] == NULL){
            exit(1);
        }
    }
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            mat[i][j] = 0;
        }
    }
    
    return mat;
}

void inicializaMatriz(int** mat, int valor,int linha, int coluna){
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            mat[i][j] = valor;
        }
    }
}

void imprimeMatriz(int ordem, int **mat, int valorEscondido){
    printf("     ");
    for(int x = 1; x <= ordem; x++){
        if(x <= 10){
         printf(" %d ", x);
        }
        else{
            printf("%d ", x);
        } 
    }
    printf("\n");
    printf("     ");
    for(int i = 0; i < ordem; i++){
        printf("---");
    }
    printf("\n");

      for(int i = 0; i < ordem; i++){

        if(i+1 < 10){ 
            printf("%d |  ", i+1);
        }
        else{ 
            printf("%d|  ", i+1);
            
        }

        for(int j = 0; j < ordem; j++){
            if(mat[i][j] == valorEscondido){ 
                printf(" X ");
            
            }
            else if(mat[i][j] < 0  ){ 
                printf("%d ", mat[i][j]);
               
            }
            else{ 
                printf(" %d ", mat[i][j]);
               
            }
        }
        printf("\n");
      
    }
   
}

