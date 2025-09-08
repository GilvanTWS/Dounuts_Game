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
int validaJogada(Celula **tabuleiro, int linha, int coluna, int ultimaLinha, int ultimaColuna, int N);
int fazInsert(Celula **tabuleiro, int linha, int coluna, int jogador, int N);
int verificaVitoria(Celula **tabuleiro, int jogador, int N);
void inicializaTabuleiro(Celula **tabuleiro, int N);
void coordenadaParaIndice(char entrada[], int *linha, int *coluna);

int main() {
    int N;
    printf("Digite o tamanho do tabuleiro (ex: 20 para 20x20): ");
    scanf("%d", &N);

    // alocação dinâmica do tabuleiro
    Celula **tabuleiro = malloc(N * sizeof(Celula *));
    for (int i = 0; i < N; i++) {
        tabuleiro[i] = malloc(N * sizeof(Celula));
    }

    inicializaTabuleiro(tabuleiro, N);

    int turno = 0;
    int jogadorAtual = 1;
    int ultimaLinha = -1, ultimaColuna = -1;

    while (turno < N * N) {
        exibeTabuleiro(tabuleiro, N);
        printf("\nTurno %d - Jogador %d\n", turno + 1, jogadorAtual);
        printf("Digite sua jogada (ex: A1): ");

        char jogada[5];
        scanf("%s", jogada);

        int linha, coluna;
        coordenadaParaIndice(jogada, &linha, &coluna);

        if (validaJogada(tabuleiro, linha, coluna, ultimaLinha, ultimaColuna, N)) {
            tabuleiro[linha][coluna].dono = (jogadorAtual == 1) ? 'X' : 'O';

            fazInsert(tabuleiro, linha, coluna, jogadorAtual, N);

            printf("Jogador %d jogou em %c%d\n", 
                   jogadorAtual, 'A' + linha, coluna + 1);

            Direcao proxima = tabuleiro[linha][coluna].dir;
            switch (proxima) {
                case HORIZONTAL: 
                    printf("Próxima jogada deve ser na HORIZONTAL (-).\n"); 
                    break;
                case VERTICAL: 
                    printf("Próxima jogada deve ser na VERTICAL (|).\n"); 
                    break;
                case DIAGONAL_P: 
                    printf("Próxima jogada deve ser na DIAGONAL PRINCIPAL (\\).\n"); 
                    break;
                case DIAGONAL_S: 
                    printf("Próxima jogada deve ser na DIAGONAL SECUNDÁRIA (/).\n"); 
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
            printf("Jogada inválida. Tente novamente.\n");
        }
    }

    exibeTabuleiro(tabuleiro, N);
    printf("\nFim de jogo por limite de turnos.\n");

    // liberar memória
    for (int i = 0; i < N; i++) free(tabuleiro[i]);
    free(tabuleiro);

    return 0;
}

void inicializaTabuleiro(Celula **tabuleiro, int N) {
    int total = N * N;
    Direcao *dirs = malloc(total * sizeof(Direcao));

    // proporções fixas (25% de cada tipo)
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

int validaJogada(Celula **tabuleiro, int linha, int coluna, int ultimaLinha, int ultimaColuna, int N) {
    if (linha < 0 || linha >= N || coluna < 0 || coluna >= N) return 0;
    if (tabuleiro[linha][coluna].dono != ' ') return 0;

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
                if ((linha - ultimaLinha) != (coluna - ultimaColuna)) return 0;
                break;
            case DIAGONAL_S:
                if ((linha - ultimaLinha) != -(coluna - ultimaColuna)) return 0;
                break;
        }
    }
    return 1;
}

int fazInsert(Celula **tabuleiro, int linha, int coluna, int jogador, int N) {
    char simbolo = (jogador == 1) ? 'X' : 'O';

    for (int i = linha + 1; i < N; i++) {
        if (tabuleiro[i][coluna].dono == simbolo) {
            for (int k = linha + 1; k < i; k++) tabuleiro[k][coluna].dono = simbolo;
            break;
        }
    }
    for (int j = coluna + 1; j < N; j++) {
        if (tabuleiro[linha][j].dono == simbolo) {
            for (int k = coluna + 1; k < j; k++) tabuleiro[linha][k].dono = simbolo;
            break;
        }
    }
    return 0;
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
    return 0;
}

void coordenadaParaIndice(char entrada[], int *linha, int *coluna) {
    *linha = entrada[0] - 'A';
    *coluna = atoi(&entrada[1]) - 1; // suporta números com 2+ dígitos
}
