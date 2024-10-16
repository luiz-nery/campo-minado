#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void imprimeMatriz(int ordem, int **mat);
int** criaMatriz(int linha, int coluna);
void jogo(int dificuldade);
int perdeu(int x, int y);
void insereBomba(int**mat, int bomba, int ordem);
void inicializaMatriz(int** mat, int valor,int linha, int coluna);
int verificaCoordenadas(int x, int y, int**matLido);

int main(){
    int dificuldade;
    printf("Escolha a dificuldade:\n");
    printf("(1)Facil\n");
    printf("(2)Medio\n");
    printf("(3)Dificil\n");
    scanf("%d", &dificuldade);
    jogo(dificuldade);
    return 0;
}

void imprimeMatriz(int ordem, int **mat){
    printf("    ");
    for(int x = 1; x <= 10; x++){
        printf("%d ", x);
    }
    printf("\n\n");

      for(int i = 0; i < ordem; i++){

        if(i+1 < 10) printf("%d   ", i+1);
        else printf("%d  ", i+1);

        for(int j = 0; j < ordem; j++){
            if(mat[i][j] == 88) printf("%c ", mat[i][j]);
            else printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
   
}
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
void jogo(int dificuldade){
    int **campo, ordem, bomba;
    int **matCampo;
    int **matCoordenadasLidas;
    switch(dificuldade){
        case 1:
            ordem = 10;
            bomba = 3;
            campo = criaMatriz(ordem,ordem);
            insereBomba(campo, bomba, ordem);
        break;
        case 2:
            ordem = 20;
            bomba = 6;
            campo = criaMatriz(ordem,ordem);
            insereBomba(campo, bomba, ordem);
        break;
        case 3:
            ordem = 30;
            bomba = 9;
            campo = criaMatriz(ordem,ordem);
            insereBomba(campo, bomba, ordem);
        break;
        default:
            printf("dificuldade inválida\n");
            int main();
        break;
    }
    matCoordenadasLidas = criaMatriz(ordem,2);
    inicializaMatriz(matCoordenadasLidas, 0 , ordem, 2);
    inicializaMatriz(campo,0,ordem,ordem);
    inicializaMatriz(matCampo,88,ordem,ordem);

    imprimeMatriz(ordem, matCampo);
    int x, y, cont = 0;
    while(scanf("%d,%d", &x, &y), (x && y) || cont <= (ordem*ordem - bomba)){
        if(verificaCoordenadas(x,y, matCoordenadasLidas)){
            imprimeMatriz(ordem, campo);
        }else{
            printf("ja inseriu essas\n");
        }
        cont++;
    }
    

    for(int i = 0; i < ordem; i++){
        free(campo[i]);
    }
    for(int i = 0; i < ordem; i++){
        free(matCampo[i]);
    }
    for(int i = 0; i < 2; i++){
        free(matCoordenadasLidas[i]);
    }
    free(matCoordenadasLidas);
    free(matCampo);
    free(campo);
}

int verificaCoordenadas(int x, int y, int**matLido){
    
    
    if(matLido[x][0] != 0 || matLido[y][1]!= 0){
        matLido[x][0] = 1;
        matLido[y][1] = 1;
        printf("%d", matLido[x][y]);
        return 1;
    }else return 0;
}
void insereBomba(int** mat, int bomba, int ordem){
    int coordBomba[2][bomba];
    srand(time(NULL));
    for(int cont = 0; cont < bomba; cont++){
        
        int i = rand()%ordem;
        int j = rand()%ordem;
        mat[i][j] = -1;
        coordBomba[0][cont] = i;
        coordBomba[1][cont] = j;
        
    }
    
    for(int i = 0; i < ordem; i++){
        for(int j = 0; j < ordem; j++){
            for(int k = 0; k < bomba; k++){
                if(((i == coordBomba[0][k] && (j == coordBomba[1][k] - 1 || j == coordBomba[1][k] + 1))
                 || (i == coordBomba[0][k] - 1 && (j == coordBomba[1][k] || j == coordBomba[1][k] + 1 || j == coordBomba[1][k]+1))
                 || (i == coordBomba[0][k] + 1 && (j == coordBomba[1][k] || j == coordBomba[1][k] + 1 || j == coordBomba[1][k]+1)))
                 && mat[i][j] >= 0){
                    mat[i][j]++;
                }else if(j == coordBomba[1][k] - 1 && (i == coordBomba[0][k] + 1 || i == coordBomba[0][k] - 1) && mat[i][j]>=0){
                    mat[i][j]++;
                }
            }
            
        }
    }
}
