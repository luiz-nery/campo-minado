#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void imprimeMatriz(int ordem, int **mat);
int** criaMatriz(int linha, int coluna);
void jogo(int dificuldade);
int perdeu(int valor,int ordem, int**campo);
void insereBomba(int**mat, int bomba, int ordem);
void inicializaMatriz(int** mat, int valor,int linha, int coluna);
int verificaCoordenadas(int x, int y, int**matLido, int ordem);

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
    for(int x = 1; x <= ordem; x++){
        printf(" %d ", x);
    }
    printf("\n\n");

      for(int i = 0; i < ordem; i++){

        if(i+1 < 10) printf("%d   ", i+1);
        else printf("%d  ", i+1);

        for(int j = 0; j < ordem; j++){
            if(mat[i][j] == 88) printf(" %c ", mat[i][j]);
            else if(mat[i][j] < 0  ) printf("%d ", mat[i][j]);
            else printf(" %d ", mat[i][j]);
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
            ordem = 3;
            bomba = 1;
            campo = criaMatriz(ordem,ordem);
            inicializaMatriz(campo,0,ordem,ordem);
            insereBomba(campo, bomba, ordem);
        break;
        case 2:
            ordem = 20;
            bomba = 6;
            campo = criaMatriz(ordem,ordem);
            inicializaMatriz(campo,0,ordem,ordem);
            insereBomba(campo, bomba, ordem);
        break;
        case 3:
            ordem = 30;
            bomba = 9;
            campo = criaMatriz(ordem,ordem);
            inicializaMatriz(campo,0,ordem,ordem);
            insereBomba(campo, bomba, ordem);
        break;
        default:
            printf("dificuldade inválida\n");
            int main();
        break;
    }
    matCampo = criaMatriz(ordem, ordem);
    matCoordenadasLidas = criaMatriz(ordem*ordem,2);
    inicializaMatriz(matCoordenadasLidas, -1 , ordem, 2);
    inicializaMatriz(matCampo,88,ordem,ordem);

    imprimeMatriz(ordem, matCampo);
    int x, y, cont = 0;
    do{
        scanf("%d,%d", &x, &y);
        x = x - 1; 
        y = y - 1;
        if(verificaCoordenadas(x,y, matCoordenadasLidas, ordem) && (x >= 0 && y >= 0)){
            matCampo[x][y] = campo[x][y];
            imprimeMatriz(ordem, matCampo);
        }else{
            printf("ja inseriu essas\n");
        }
        cont++;
        if(cont == (ordem*ordem - bomba)){
            printf("Voce eh fera\n");
        }

    }while(((x && y) || cont <= (ordem*ordem - bomba)) && perdeu(campo[x][y],ordem,campo));
    

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
int perdeu(int valor,int ordem, int **campo){
    if(valor == -1){
        printf("Voce Perdeu!\n");
        imprimeMatriz(ordem, campo);
        return 0;
    }else return 1;
}
int verificaCoordenadas(int x, int y, int**matLido, int ordem){
    int lido = 0;
    for(int i = 0; i < ordem*ordem; i++){
      
        if(i > 0){
            if(matLido[i][0] == -1 && matLido[i-1][0] != x && matLido[i-1][1] != y){
                matLido[i][0] = x;
                matLido[i][1] = y;
            }
        }else if(matLido[i][0] == -1){
            matLido[i][0] = x;
            matLido[i][1] = y;
        }
        printf("%d %d \n", matLido[i][0], matLido[i][1]);
    }
    for(int i = 0; i < ordem*ordem; i++){
        
        if(matLido[i][0] == x && matLido[i][1] == y){
            lido = 1;
        }
        
    }
    return lido;
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
        printf("%d %d\n", coordBomba[0][cont], coordBomba[1][cont]);
        
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
