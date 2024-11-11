#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define valorescondido 88

void jogo();
int** criaMatriz(int linha, int coluna);
//inicializa a matriz com um valor, a saber 0 e 88(pra diferenciar a impressão de 'X' ou numero)
void inicializaMatriz(int** mat, int valor,int linha, int coluna);
//escolhe ramdomicamente os i's e j's das bombas depois insere na matriz
void insereBomba(int**mat, int bomba, int ordem);
//soma +1 nas casas vizinhas das bombas{(i,j+1), (i,j-1),(i+1,j),(i-1,j),(i+1,j+1),(i+1,j-1),(i-1,j+1),(i-1,j-1)}
void vizinhaDasBombas(int bomba, int coordBomba[][bomba], int ordem, int **mat);
void imprimeMatriz(int ordem, int **mat);
//Verifica se as coordenadas já foram usadas ou se são válidas
int verificaCoordenadas(int x, int y,int ordem, int**matLido);
//verifica se o jogador abriu uma mina
int perdeu(int x, int y,int ordem, int **campo);
//verifica se o jogador abriu todas as casas sem minas
int ganhou(int movimentos, int ordem, int bombas);
int sair(int x);//função que sai do jogo
void libera_campo(int **matEscondida, int **matCampo, int x, int y, int ordem);
//inicia o jogo
int main(){
    jogo();
    return 0;
}
void jogo(){
    int valorPreencheMatriz, dificuldade;
    int **campo, ordem, bomba;//campo é a matriz principal
    int **matEscondida;//matriz impressa pro usuário com x's nas posicoes
    int **matCoordenadasLidas;//matriz que guarda as coordenadas lidas
    int x, y, movimentos = 0;

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
            printf("dificuldade invalida\n\n");
            jogo();
        break;
    }
    matEscondida = criaMatriz(ordem, ordem);
    matCoordenadasLidas = criaMatriz(ordem, ordem);
    valorPreencheMatriz = 0;
    inicializaMatriz(campo,valorPreencheMatriz,ordem,ordem);
    inicializaMatriz(matCoordenadasLidas, valorPreencheMatriz , ordem, ordem);
    inicializaMatriz(matEscondida,valorescondido,ordem,ordem);
    insereBomba(campo, bomba, ordem);
    imprimeMatriz(ordem, matEscondida);
    
    do{ 
        printf("Digite as coordenadas x,y (ou 0 para sair)\n");
        scanf("%d,%d", &x, &y);
        printf("\n");
        x--;
        y--;
       
        if(!verificaCoordenadas(x,y,ordem, matCoordenadasLidas)){
            libera_campo(matEscondida, campo, x, y, ordem);
            matEscondida[x][y] = campo[x][y];
            imprimeMatriz(ordem, matEscondida);
            movimentos++;
            printf("Movimentos: %d\n", movimentos);
            
        }else if((x >= ordem || y >= ordem || x <= 0 || y <= 0) && (x != -1)){
            imprimeMatriz(ordem, matEscondida);
            printf("coordenadas invalidas\n");
        }else if(x != -1 && y != -1){
            imprimeMatriz(ordem, matEscondida);
            printf("ja inseriu essas\n");
        }

    }while(ganhou(movimentos, ordem*ordem, bomba) && perdeu(x,y,ordem,campo) && !sair(x));
    jogo();
    //liberando a memória
    for(int i = 0; i < ordem; i++){
        free(campo[i]);
    }
    for(int i = 0; i < ordem; i++){
        free(matEscondida[i]);
    }
    for(int i = 0; i < ordem; i++){
        free(matCoordenadasLidas[i]);
    }
    free(matCoordenadasLidas);
    free(matEscondida);
    free(campo);
    
}
void libera_campo(int **matEscondida, int **matCampo, int x, int y, int ordem){
    if((x >= 0 && x < ordem) && (y >= 0 && y < ordem)){
        if(matCampo[x][y] == 0 && matEscondida[x][y] == valorescondido){
            matEscondida[x][y] = matCampo[x][y];
            libera_campo(matEscondida, matCampo,x,y-1, ordem);
            libera_campo(matEscondida, matCampo,x,y+1, ordem);
            libera_campo(matEscondida, matCampo,x-1,y, ordem);
            libera_campo(matEscondida, matCampo,x+1,y, ordem);
            libera_campo(matEscondida, matCampo,x-1,y-1, ordem);
            libera_campo(matEscondida, matCampo,x+1,y-1, ordem);
            libera_campo(matEscondida, matCampo,x-1,y+1, ordem);
            libera_campo(matEscondida, matCampo,x+1,y+1, ordem);
        }else{
            matEscondida[x][y] = matCampo[x][y];
        }
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

void insereBomba(int** mat, int bomba, int ordem){
    int coordBomba[2][bomba];//guarda as coordenadas das bombas, sendo x a coluna 0, y a coluna 1
    int x = 0, y = 1;
    srand(time(NULL));
    for(int cont = 0; cont < bomba; cont++){
        
        int i = rand()%ordem;
        int j = rand()%ordem;
        mat[i][j] = -1;
        coordBomba[x][cont] = i;
        coordBomba[y][cont] = j;
    }
    vizinhaDasBombas(bomba, coordBomba, ordem, mat);
    
}
void vizinhaDasBombas(int bomba, int coordBomba[][bomba], int ordem, int **mat){
    int x = 0, y = 1;
    for(int i = 0; i < ordem; i++){
        for(int j = 0; j < ordem; j++){
            for(int k = 0; k < bomba; k++){
                if(((i == coordBomba[x][k] && (j == coordBomba[y][k] - 1 || j == coordBomba[y][k] + 1))
                 || (i == coordBomba[x][k] - 1 && (j == coordBomba[y][k] || j == coordBomba[y][k] + 1 || j == coordBomba[1][k]+1))
                 || (i == coordBomba[x][k] + 1 && (j == coordBomba[y][k] || j == coordBomba[y][k] + 1 || j == coordBomba[1][k]+1)))
                 && mat[i][j] >= 0){
                    mat[i][j]++;
                }else if(j == coordBomba[1][k] - 1 && (i == coordBomba[0][k] + 1 || i == coordBomba[0][k] - 1) && mat[i][j]>=0){
                    mat[i][j]++;
                }
            }
            
        }
    }
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
            if(mat[i][j] == 88) printf(" X ");
            else if(mat[i][j] < 0  ) printf("%d ", mat[i][j]);
            else printf(" %d ", mat[i][j]);
        }
        printf("\n");
    }
   
}

/*verifica se as coordenada já foram usadas
    coloca o valor 1 na posicao x,y de uma matriz que representa a tentativa do usuário
    ex:
    0 0 0                   0 1 0
    0 0 0  x = 1, y = 2 ->  0 0 0
    0 0 0                   0 0 0
*/
int verificaCoordenadas(int x, int y,int ordem, int**matLido){
    int valido = 1;
    if (x >= 0 && y >= 0 && x < ordem && y < ordem && x!= -1 && y!=-1){
        if(matLido[x][y] == 0){
            matLido[x][y] = 1;
            valido = 0;
        }
    }
    
    return valido;
}
int sair(int x){
    int saiu = 0;
    if(x == -1){
        saiu = 1;
    }
    return saiu;
}
//verifica a cada rodada se o usuário encontrou uma bomba
int perdeu(int x, int y,int ordem, int **campo){
    int fim;
    if(x >= 0 && x < ordem && y >= 0 && y < ordem){
        if(campo[x][y] == -1){
            printf("\nGame Over!\n");
            imprimeMatriz(ordem, campo);
            fim = 0;
        }else{
            printf("Ufa! sem bombas por aqui\n");
            if(campo[x][y]>0){
                printf("Mas, cuidado! ha %d bombas por perto\n", campo[x][y]);
            }
            fim = 1;
        } 
    }else{
        fim = 1;
    }
    return fim;
}
int ganhou(int movimentos, int ordem, int bombas){
    int ganha = 1;
    if(movimentos == (ordem*ordem - bombas)){
        printf("Parabens, voce eh fera\n");
        ganha = 0;
    }
    return ganha;
}
