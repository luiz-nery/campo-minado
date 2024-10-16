#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void imprimeMatriz(int ordem, int **mat);
int** criaMatriz(int linha, int coluna);
void jogo(int dificuldade);
int perdeu(int x, int y);
void insereBomba(int**mat, int bomba, int ordem);
//int** posBomba(int** coordBomb, int bomba);
int verificaCoordenadas(int x, int y, int tam);

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
    int matCampo[ordem][ordem];

    for(int i = 0; i < ordem; i++){
        for(int j = 0; j < ordem; j++){
            if(!verificaCoordenadas(i,j, ordem)){
                matCampo[i][j] = 88;
            }else{
                matCampo[i][j] = mat[i][j];
            }
            
        }
    }
    printf("    ");
    for(int x = 1; x <= 10; x++){
        printf("%d ", x);
    }
    printf("\n\n");

      for(int i = 0; i < ordem; i++){

        if(i+1 < 10) printf("%d   ", i+1);
        else printf("%d  ", i+1);

        for(int j = 0; j < ordem; j++){
            if(matCampo[i][j] == 88) printf("%c ", matCampo[i][j]);
            else printf("%d ", matCampo[i][j]);
        }
        printf("\n");
    }
   /* for(int i = 0; i < ordem; i++){
        if(i+1 < 10) printf("%d   ", i+1);
        else printf("%d  ", i+1);

        for(int j = 0; j < ordem; j++){
            if(mat[i][j+1] < 0 && j + 1 < ordem) printf("%d", mat[i][j]);
            else if(mat[i][j]<0) printf("%d ", mat[i][j]);
            else printf("%d ", mat[i][j]);
        }
        printf("\n");
    }*/
}
int** criaMatriz(int linha, int coluna){
    int **mat = (int**) malloc(linha*coluna*sizeof(int*));//matriz que representa o campo minado
    //alocação da matriz
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
/*int posBomba(int** coordBomb, int bomba){
    int **pBomba = (int**) malloc(2*bomba*sizeof(int*));
    if(pBomba == NULL){
        exit(1);
    }
    for(int i = 0; i < bomba; i++){
        pBomba[i] = (int*) malloc(bomba*sizeof(int));
        if(pBomba[i] == NULL){
            exit(1);
        }
    }
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < bomba; j++){
            pBomba[i][j] = coordBomb[i][j];
        }
    }


}*/
void jogo(int dificuldade){
    int **campo, ordem, bomba;
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
    imprimeMatriz(ordem, campo);
    int x, y, cont = 0;
    do{
        scanf("%d,%d", &x, &y);
        if(!verificaCoordenadas(x,y, ordem)){
            imprimeMatriz(ordem, campo);
        }else{
            printf("ja inseriu essas\n");
        }
    }while(x && y);
    

    for(int i = 0; i < ordem; i++){
        free(campo[i]);
    }
    free(campo);
}

int verificaCoordenadas(int x, int y, int tam){
    int **vetXY;
    vetXY = criaMatriz(tam,2);
    
    if(vetXY[x][0] != 0 || vetXY[y][1]!= 0){
        vetXY[x][0] = 1;
        vetXY[y][1] = 1;
        printf("%d", vetXY[x][y]);
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
        //posBomba(i,j,bomba);
        coordBomba[0][cont] = i;
        coordBomba[1][cont] = j;
        
    }
    //posBomba(coordBomba, bomba);
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
