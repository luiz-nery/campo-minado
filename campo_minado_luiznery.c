#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void imprimeMatriz(int ordem, int **mat);
int** criaMatriz(int linha, int coluna);
void jogo();
int perdeu(int x, int y,int ordem, int **campo);
void insereBomba(int**mat, int bomba, int ordem);
void inicializaMatriz(int** mat, int valor,int linha, int coluna);
int verificaCoordenadas(int x, int y,int ordem, int**matLido);

//inicia o jogo
int main(){
    
    jogo();
    return 0;
}
      
void jogo(){
    int dificuldade;
    int **campo, ordem, bomba;//campo é a matriz principal
    int **matCampo;//matriz impressa pro usuário com x's nas posicoes
    int **matCoordenadasLidas;//matriz que guarda as coordenadas lidas

    printf("Escolha a dificuldade:\n");
    printf("(1)Facil\n");
    printf("(2)Medio\n");
    printf("(3)Dificil\n");
    printf("(0)Sair\n");
    scanf("%d", &dificuldade);

    switch(dificuldade){
        case 1:
            ordem = 10;
            bomba = 3;
            campo = criaMatriz(ordem,ordem);
        break;
        case 2:
            ordem = 20;
            bomba = 6;
            campo = criaMatriz(ordem,ordem);
        break;
        case 3:
            ordem = 30;
            bomba = 9;
            campo = criaMatriz(ordem,ordem);
        break;
        case 0:
            printf("Obrigado por jogar\n");
            exit(1);
        break;
        default:
            printf("dificuldade inválida\n");
            int main();
        break;
    }
    inicializaMatriz(campo,0,ordem,ordem);
    insereBomba(campo, bomba, ordem);
    matCampo = criaMatriz(ordem, ordem);
    matCoordenadasLidas = criaMatriz(ordem, ordem);
    inicializaMatriz(matCoordenadasLidas, 0 , ordem, ordem);
    inicializaMatriz(matCampo,88,ordem,ordem);

    imprimeMatriz(ordem, matCampo);
    int x, y, cont = 0;
    do{
        printf("Digite as coordenadas x,y (ou 0 para sair)\n");
        scanf("%d,%d", &x, &y);
        printf("\n");
        x = x - 1; 
        y = y - 1;

        printf("Movimentos: %d\n", cont);
        if(!verificaCoordenadas(x,y,ordem, matCoordenadasLidas)){
            matCampo[x][y] = campo[x][y];
            imprimeMatriz(ordem, matCampo);
            cont++;
            x++;
            y++;
        }else if((x >= ordem || y >= ordem || x < 0 || y < 0) && (x != -1 && y != -1)){
            imprimeMatriz(ordem, matCampo);
            printf("coordenadas invalidas\n");
        }else if(x != -1 && y != - 1){
            imprimeMatriz(ordem, matCampo);
            printf("ja inseriu essas\n");
        }
        
        if(cont == (ordem*ordem - bomba)){
            printf("Voce eh fera\n");
            imprimeMatriz(ordem, campo);
            printf("Que tal mais uma?\n");
        }

    }while((cont < (ordem*ordem - bomba)) && perdeu(x,y,ordem,campo));
    jogo();
    //liberando a memória
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

void imprimeMatriz(int ordem, int **mat){
    printf("     ");
    for(int x = 1; x <= ordem; x++){
        if(x <= 10) printf(" %d ", x);
        else printf("%d ", x);
        
    }
    printf("\n");
    printf("     ");
    for(int i = 0; i < ordem; i++){
        printf("---");
    }
    printf("\n");

      for(int i = 0; i < ordem; i++){

        if(i+1 < 10) printf("%d |  ", i+1);
        else printf("%d|  ", i+1);

        for(int j = 0; j < ordem; j++){
            if(mat[i][j] == 88) printf(" %c ", mat[i][j]);
            else if(mat[i][j] < 0  ) printf("%d ", mat[i][j]);
            else printf(" %d ", mat[i][j]);
        }
        printf("\n");
    }
   
}
//função para criar as matrizes alocadas dinamicamente
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
//inicializa a matriz com um valor indicado, serve pra inicializar com 0 ou 88(simbolo)
void inicializaMatriz(int** mat, int valor,int linha, int coluna){
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            mat[i][j] = valor;
        }
    }
}


//verifica a cada rodada se o usuário encontrou uma bomba
int perdeu(int x, int y,int ordem, int **campo){
    int fim;
    if(x >= 0 && x < ordem && y >= 0 && y < ordem){
        if(campo[x][y] == -1){
            printf("Voce Perdeu!\n");
            imprimeMatriz(ordem, campo);
            fim = 0;
        }else{
            printf("Ufa! sem bombas por aqui\n");
            if(campo[x][y]>0){
                printf("Mas, cuidado! ha bombas por perto\n");
            }
            fim = 1;
        } 
    }else if(x == -1 || y == -1){
        fim = 0;
        
    }else{
        fim = 1;
    }
    return fim;
}

/*verifica se as coordenada já foram usadas
    coloca o valor 1 na posicao x,y de uma matriz que representa a tentativa do usuário
    ex:
    0 0 0                   0 1 0
    0 0 0  x = 1, y = 2 ->  0 0 0
    0 0 0                   0 0 0
*/
int verificaCoordenadas(int x, int y,int ordem, int**matLido){
    int lido = 1;
    if (x >= 0 && y >= 0 && x < ordem && y < ordem){
        if(matLido[x][y] == 0){
            matLido[x][y] = 1;
            lido = 0;
        }
    }
    
    return lido;
}

//escolhe randomicamente as coordenadas das bombas e insere na matriz campo 
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
