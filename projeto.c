#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_P,
    DIAGONAL_S
} Direcao;

typedef struct {
    char dono;
    Direcao dir;
} Celula;

void exibeTabuleiro(Celula **tabuleiro, int N);
int validaJogada(Celula **tabuleiro, int linha, int coluna, int ultimaLinha, int ultimaColuna, int N, int jogadaLivre);
void fazInsert(Celula **tabuleiro, int linha, int coluna, int jogador, int N);
int verificaVitoria(Celula **tabuleiro, int jogador, int N);
void inicializaTabuleiro(Celula **tabuleiro, int N);
void coordenadaParaIndice(char entrada[], int *linha, int *coluna);
int encontrarMaiorRegiao(Celula **tabuleiro, int jogador, int N);

int main() {
    int N;
    printf("Digite o tamanho do tabuleiro (ex: 20 para 20x20): ");
    scanf("%d", &N);

    Celula **tabuleiro = malloc(N * sizeof(Celula *));
    for (int i = 0; i < N; i++) {
        tabuleiro[i] = malloc(N * sizeof(Celula));
    }

    inicializaTabuleiro(tabuleiro, N);

    int turno = 0;
    int jogadorAtual = 1;
    int ultimaLinha = -1, ultimaColuna = -1;

    while (turno < 30) { 
        exibeTabuleiro(tabuleiro, N);
        printf("\nTurno %d - Jogador %d\n", turno + 1, jogadorAtual);

        int jogadaPossivel = 0;
        if (ultimaLinha != -1 && ultimaColuna != -1) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (validaJogada(tabuleiro, i, j, ultimaLinha, ultimaColuna, N, 0)) {
                        jogadaPossivel = 1;
                        break;
                    }
                }
                if (jogadaPossivel) break;
            }
        } else {
            jogadaPossivel = 1;
        }

        char jogada[5];
        int linha, coluna;
        int jogadaValida;

        if (jogadaPossivel) {
            printf("Digite sua jogada (ex: A1): ");
            scanf("%s", jogada);
            coordenadaParaIndice(jogada, &linha, &coluna);
            jogadaValida = validaJogada(tabuleiro, linha, coluna, ultimaLinha, ultimaColuna, N, 0);
        } else {
            printf("Nenhum movimento valido na direcao. Digite uma jogada livre (ex: A1): ");
            scanf("%s", jogada);
            coordenadaParaIndice(jogada, &linha, &coluna);
            jogadaValida = validaJogada(tabuleiro, linha, coluna, -1, -1, N, 1);
        }

        if (jogadaValida) {
            fazInsert(tabuleiro, linha, coluna, jogadorAtual, N);

            printf("Jogador %d jogou em %c%d\n", 
                   jogadorAtual, 'A' + linha, coluna + 1);

            Direcao proxima = tabuleiro[linha][coluna].dir;
            switch (proxima) {
                case HORIZONTAL: 
                    printf("Proxima jogada deve ser na HORIZONTAL (-).\n"); 
                    break;
                case VERTICAL: 
                    printf("Proxima jogada deve ser na VERTICAL (|).\n"); 
                    break;
                case DIAGONAL_P: 
                    printf("Proxima jogada deve ser na DIAGONAL PRINCIPAL (\\).\n"); 
                    break;
                case DIAGONAL_S: 
                    printf("Proxima jogada deve ser na DIAGONAL SECUNDARIA (/).\n"); 
                    break;
            }

            if (verificaVitoria(tabuleiro, jogadorAtual, N)) {
                exibeTabuleiro(tabuleiro, N);
                printf("\nJogador %d venceu!\n", jogadorAtual);
                return 0;
            }

            ultimaLinha = linha;
            ultimaColuna = coluna;
            jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
            turno++;
        } else {
            printf("Jogada invalida. Tente novamente.\n");
        }
    }

    exibeTabuleiro(tabuleiro, N);
    printf("\nFim de jogo por limite de turnos.\n");

    int maiorRegiaoJogador1 = encontrarMaiorRegiao(tabuleiro, 1, N);
    int maiorRegiaoJogador2 = encontrarMaiorRegiao(tabuleiro, 2, N);

    if (maiorRegiaoJogador1 > maiorRegiaoJogador2) {
        printf("Jogador 1 venceu com a maior regiao de %d pecas!\n", maiorRegiaoJogador1);
    } else if (maiorRegiaoJogador2 > maiorRegiaoJogador1) {
        printf("Jogador 2 venceu com a maior regiao de %d pecas!\n", maiorRegiaoJogador2);
    } else {
        printf("Empate!\n");
    }

    for (int i = 0; i < N; i++) free(tabuleiro[i]);
    free(tabuleiro);

    return 0;
}

void inicializaTabuleiro(Celula **tabuleiro, int N) {
    int total = N * N;
    Direcao *dirs = malloc(total * sizeof(Direcao));

    int q = total / 4;
    int idx = 0;
    for (int i = 0; i < q; i++) dirs[idx++] = HORIZONTAL;
    for (int i = 0; i < q; i++) dirs[idx++] = VERTICAL;
    for (int i = 0; i < q; i++) dirs[idx++] = DIAGONAL_P;
    for (int i = 0; i < total - 3 * q; i++) dirs[idx++] = DIAGONAL_S;

    srand(time(NULL));
    for (int i = total - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Direcao tmp = dirs[i];
        dirs[i] = dirs[j];
        dirs[j] = tmp;
    }

    idx = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tabuleiro[i][j].dono = ' ';
            tabuleiro[i][j].dir = dirs[idx++];
        }
    }

    free(dirs);
}

void exibeTabuleiro(Celula **tabuleiro, int N) {
    printf("    ");
    for (int j = 0; j < N; j++) printf("%3d ", j + 1);
    printf("\n");

    for (int i = 0; i < N; i++) {
        printf("%c ", 'A' + i);
        for (int j = 0; j < N; j++) {
            char simbolo;
            switch (tabuleiro[i][j].dir) {
                case HORIZONTAL: simbolo = '-'; break;
                case VERTICAL: simbolo = '|'; break;
                case DIAGONAL_P: simbolo = '\\'; break;
                case DIAGONAL_S: simbolo = '/'; break;
            }
            printf("[%c%c] ", tabuleiro[i][j].dono == ' ' ? '.' : tabuleiro[i][j].dono, simbolo);
        }
        printf("\n");
    }
}

int validaJogada(Celula **tabuleiro, int linha, int coluna, int ultimaLinha, int ultimaColuna, int N, int jogadaLivre) {
    if (linha < 0 || linha >= N || coluna < 0 || coluna >= N) return 0;
    if (tabuleiro[linha][coluna].dono != ' ') return 0;

    if (jogadaLivre) {
        return 1;
    }

    if (ultimaLinha != -1 && ultimaColuna != -1) {
        Direcao dirAnterior = tabuleiro[ultimaLinha][ultimaColuna].dir;
        switch (dirAnterior) {
            case VERTICAL:
                if (coluna != ultimaColuna) return 0;
                break;
            case HORIZONTAL:
                if (linha != ultimaLinha) return 0;
                break;
            case DIAGONAL_P:
                if (abs(linha - ultimaLinha) != abs(coluna - ultimaColuna)) return 0;
                break;
            case DIAGONAL_S:
                if (abs(linha - ultimaLinha) != abs(coluna - ultimaColuna) || (linha - ultimaLinha) == (coluna - ultimaColuna)) return 0;
                break;
        }
    }
    return 1;
}

void fazInsert(Celula **tabuleiro, int linha, int coluna, int jogador, int N) {
    char meuSimbolo = (jogador == 1) ? 'X' : 'O';
    char oponenteSimbolo = (jogador == 1) ? 'O' : 'X';
    
    tabuleiro[linha][coluna].dono = meuSimbolo;

    int direcoes[8][2] = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}, 
        {1, 1}, {-1, -1}, {1, -1}, {-1, 1}
    };

    for (int i = 0; i < 8; i++) {
        int dirL = direcoes[i][0];
        int dirC = direcoes[i][1];
        int l = linha + dirL;
        int c = coluna + dirC;
        
        if (l >= 0 && l < N && c >= 0 && c < N && tabuleiro[l][c].dono == oponenteSimbolo) {
            int temFim = 0;
            int k = 1;
            while (l + k * dirL >= 0 && l + k * dirL < N && c + k * dirC >= 0 && c + k * dirC < N) {
                if (tabuleiro[l + k * dirL][c + k * dirC].dono == meuSimbolo) {
                    temFim = 1;
                    break;
                }
                if (tabuleiro[l + k * dirL][c + k * dirC].dono == ' ') {
                    break;
                }
                k++;
            }
            if (temFim) {
                for (int m = 0; m < k; m++) {
                    tabuleiro[l + m * dirL][c + m * dirC].dono = meuSimbolo;
                }
            }
        }
    }
}

int verificaVitoria(Celula **tabuleiro, int jogador, int N) {
    char simbolo = (jogador == 1) ? 'X' : 'O';

    for (int i = 0; i < N; i++) {
        int count = 0;
        for (int j = 0; j < N; j++) {
            count = (tabuleiro[i][j].dono == simbolo) ? count + 1 : 0;
            if (count >= 5) return 1;
        }
    }

    for (int j = 0; j < N; j++) {
        int count = 0;
        for (int i = 0; i < N; i++) {
            count = (tabuleiro[i][j].dono == simbolo) ? count + 1 : 0;
            if (count >= 5) return 1;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int count_p = 0;
            for (int k = 0; i + k < N && j + k < N; k++) {
                count_p = (tabuleiro[i + k][j + k].dono == simbolo) ? count_p + 1 : 0;
                if (count_p >= 5) return 1;
            }

            int count_s = 0;
            for (int k = 0; i + k < N && j - k >= 0; k++) {
                count_s = (tabuleiro[i + k][j - k].dono == simbolo) ? count_s + 1 : 0;
                if (count_s >= 5) return 1;
            }
        }
    }
    return 0;
}

void coordenadaParaIndice(char entrada[], int *linha, int *coluna) {
    *linha = entrada[0] - 'A';
    *coluna = atoi(&entrada[1]) - 1; 
}

int encontrarMaiorRegiao(Celula **tabuleiro, int jogador, int N) {
    char simbolo = (jogador == 1) ? 'X' : 'O';
    int maxCount = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int count_h = 0;
            for (int k = 0; j + k < N; k++) {
                count_h = (tabuleiro[i][j + k].dono == simbolo) ? count_h + 1 : 0;
                if (count_h > maxCount) maxCount = count_h;
            }

            int count_v = 0;
            for (int k = 0; i + k < N; k++) {
                count_v = (tabuleiro[i + k][j].dono == simbolo) ? count_v + 1 : 0;
                if (count_v > maxCount) maxCount = count_v;
            }

            int count_p = 0;
            for (int k = 0; i + k < N && j + k < N; k++) {
                count_p = (tabuleiro[i + k][j + k].dono == simbolo) ? count_p + 1 : 0;
                if (count_p > maxCount) maxCount = count_p;
            }

            int count_s = 0;
            for (int k = 0; i + k < N && j - k >= 0; k++) {
                count_s = (tabuleiro[i + k][j - k].dono == simbolo) ? count_s + 1 : 0;
                if (count_s > maxCount) maxCount = count_s;
            }
        }
    }
    return maxCount;
}
