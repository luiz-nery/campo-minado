#include "matriz.h"
#include "log.h"

#define valorEscondido 88
#define bombasDificuldade1 15
#define bombasDificuldade2 60
#define bombasDificuldade3 135
#define log "campo_minado.txt"

void jogo();
void vizinhaDasBombas(int bomba, int coordBomba[][bomba], int ordem, int **mat);
void insereBomba(int**mat, int bomba, int ordem);
int verificaCoordenadas(int x, int y,int ordem, int**matLido, int **matEscondida);
int perdeu(int x, int y,int ordem, int **campo);
int ganhou(int movimentos, int ordem, int bombas);
int sair(int x);//função que sai do jogo
void libera_campo(int **matVisivel, int **matEscondida, int x, int y, int ordem, int *movimentos);

//inicia o jogo
int main(){
    jogo();
    return 0;
}
void jogo(){
    int valorPreencheMatriz, dificuldade;
    int **matEscondida, ordem, bomba;//campo é a matriz principal
    int **matVisivel;//matriz impressa pro usuário com x's nas posicoes
    int **matCoordenadasLidas;//matriz que guarda as coordenadas lidas
    int x, y, movimentos = 0;
    FILE *arquivo;
    printf("Escolha a dificuldade:\n");
    printf("(1)Facil\n");
    printf("(2)Medio\n");
    printf("(3)Dificil\n");
    printf("(0)Sair\n");
    scanf("%d", &dificuldade);

    switch(dificuldade){
        case 1:
            ordem = 10;
            bomba = bombasDificuldade1;
            matEscondida = criaMatriz(ordem,ordem);
        break;
        case 2:
            ordem = 20;
            bomba = bombasDificuldade2;
            matEscondida = criaMatriz(ordem,ordem);
        break;
        case 3:
            ordem = 30;
            bomba = bombasDificuldade3;
            matEscondida = criaMatriz(ordem,ordem);
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
    matVisivel = criaMatriz(ordem, ordem);
    matCoordenadasLidas = criaMatriz(ordem, ordem);
    valorPreencheMatriz = 0;
    inicializaMatriz(matEscondida,valorPreencheMatriz,ordem,ordem);
    inicializaMatriz(matCoordenadasLidas, valorPreencheMatriz , ordem, ordem);
    inicializaMatriz(matVisivel,valorEscondido,ordem,ordem);
    insereBomba(matEscondida, bomba, ordem);
    imprimeMatriz(ordem, matVisivel, valorEscondido);
    cria_arquivo_txt(log);
    escreve_matriz_no_txt(ordem, matVisivel, log, valorEscondido);
    do{ 
        printf("Digite as coordenadas x,y (ou 0 para sair)\n");
        scanf("%d,%d", &x, &y);
        if(x != 0){
            arquivo = escreve_arquivo_txt(log);
            fprintf(arquivo,"%d,%d\n",x,y);
            fclose(arquivo);
        }
        printf("\n");
        x--;
        y--;
        if(verificaCoordenadas(x,y,ordem, matCoordenadasLidas,matEscondida) == 1 && matVisivel[x][y] == valorEscondido){
            libera_campo(matVisivel, matEscondida, x, y, ordem, &movimentos);
            imprimeMatriz(ordem, matVisivel, valorEscondido);
            arquivo = escreve_arquivo_txt(log);
            printf("Casas abertas: %d\n", movimentos);
            fprintf(arquivo,"Casas abertas: %d\n", movimentos);
            fclose(arquivo);
           
        }else if((x >= ordem || y >= ordem || x < 0 || y < 0) && (x != -1)){
            imprimeMatriz(ordem, matVisivel, valorEscondido);
            printf("coordenadas invalidas\n");
        }else if(matVisivel[x][y] != valorEscondido){
            imprimeMatriz(ordem, matVisivel, valorEscondido);
            printf("casa aberta\n");
        }
        escreve_matriz_no_txt(ordem, matVisivel, log, valorEscondido);

    }while(ganhou(movimentos, ordem, bomba) == 1 && perdeu(x,y,ordem,matEscondida) == 1 && !sair(x));
    //liberando a memória
    for(int i = 0; i < ordem; i++){
        free(matEscondida[i]);
    }
    for(int i = 0; i < ordem; i++){
        free(matVisivel[i]);
    }
    for(int i = 0; i < ordem; i++){
        free(matCoordenadasLidas[i]);
    }
    free(matCoordenadasLidas);
    free(matVisivel);
    free(matEscondida);
    fclose(arquivo);
}

void libera_campo(int **matVisivel, int **matEscondida, int x, int y, int ordem, int *movimentos){
    if((x >= 0 && x < ordem) && (y >= 0 && y < ordem)){
        if(matEscondida[x][y] == 0 && matVisivel[x][y] == valorEscondido){
            matVisivel[x][y] = matEscondida[x][y];
            *movimentos = *movimentos + 1;
            libera_campo(matVisivel, matEscondida,x,y-1, ordem, movimentos);
            libera_campo(matVisivel, matEscondida,x,y+1, ordem, movimentos);
            libera_campo(matVisivel, matEscondida,x-1,y, ordem, movimentos);
            libera_campo(matVisivel, matEscondida,x+1,y, ordem, movimentos);
            libera_campo(matVisivel, matEscondida,x-1,y-1, ordem, movimentos);
            libera_campo(matVisivel, matEscondida,x+1,y-1, ordem, movimentos);
            libera_campo(matVisivel, matEscondida,x-1,y+1, ordem, movimentos);
            libera_campo(matVisivel, matEscondida,x+1,y+1, ordem, movimentos);
        }else if(matVisivel[x][y] == valorEscondido && matEscondida[x][y] != 0){
            matVisivel[x][y] = matEscondida[x][y];
            *movimentos = *movimentos + 1;
        }
    }
}




void vizinhaDasBombas(int bomba, int coordBomba[][bomba], int ordem, int **mat){
    int x = 0, y = 1;
    for(int i = 0; i < ordem; i++){
        for(int j = 0; j < ordem; j++){
            for(int k = 0; k < bomba; k++){
                if(((i == coordBomba[x][k] && (j == coordBomba[y][k] - 1 || j == coordBomba[y][k] + 1))
                 || (i == coordBomba[x][k] - 1 && (j == coordBomba[y][k] || j == coordBomba[y][k] + 1 || j == coordBomba[y][k]-1))
                 || (i == coordBomba[x][k] + 1 && (j == coordBomba[y][k] || j == coordBomba[y][k] + 1 || j == coordBomba[y][k]-1)))
                 && mat[i][j] != -1){
                    mat[i][j]++;
                }
            }
            
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
        if(mat[i][j] != -1){
            mat[i][j] = -1;
            coordBomba[x][cont] = i;
            coordBomba[y][cont] = j;
        }else cont--;
    }
    vizinhaDasBombas(bomba, coordBomba, ordem, mat);
    
}


/*verifica se as coordenada já foram usadas
    coloca o valor 1 na posicao x,y de uma matriz que representa a tentativa do usuário
    ex:
    0 0 0                   0 1 0
    0 0 0  x = 1, y = 2 ->  0 0 0
    0 0 0                   0 0 0
*/
int verificaCoordenadas(int x, int y,int ordem, int**matLido, int **matEscondida){
    int valido = 0;
    if (x >= 0 && y >= 0 && x < ordem && y < ordem && x!= -1 && y!=-1){
        if(matLido[x][y] == 0 && matEscondida[x][y] != -1){
            matLido[x][y] = 1;
            valido = 1;
        }
    }
    
    return valido;
}
int sair(int x){
    int saiu = 0;
    if(x == -1){
        saiu = 1;
        printf("Obrigado por jogar!\n");
    }
    return saiu;
}
//verifica a cada rodada se o usuário encontrou uma bomba
int perdeu(int x, int y,int ordem, int **campo){
    int fim = 1;
   
    if(x >= 0 && x < ordem && y >= 0 && y < ordem){
        if(campo[x][y] == -1){
            FILE*arquivo = escreve_arquivo_txt(log);
            fprintf(arquivo, "Game over!\n");
            fclose(arquivo);
            imprimeMatriz(ordem, campo, valorEscondido);
            escreve_matriz_no_txt(ordem, campo, log, valorEscondido);
            fim = 0;
        }
    }

    return fim;
}
int ganhou(int movimentos, int ordem, int bombas){
    int ganha = 1;
    
    if(movimentos == (ordem*ordem - bombas)){
        ganha = 0;
        FILE *arquivo = escreve_arquivo_txt(log);
        fprintf(arquivo, "Parabens, voce eh fera!\n");
        fclose(arquivo);
        printf("Parabens, voce eh fera!\n");
    }

    return ganha;
}