#include <stdio.h>

#define TAM_TAB 10       // Tamanho do tabuleiro
#define TAM_HAB 5        // Tamanho das matrizes de habilidade (5x5)
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Função para inicializar o tabuleiro com zeros
void inicializarTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            if (tabuleiro[i][j] == AGUA)
                printf("~ "); // Água
            else if (tabuleiro[i][j] == NAVIO)
                printf("N "); // Navio
            else if (tabuleiro[i][j] == HABILIDADE)
                printf("* "); // Área de habilidade
            else
                printf("? "); // Caso inesperado
        }
        printf("\n");
    }
    printf("\nLegenda: ~ = água | N = navio | * = habilidade\n");
}

// Função para posicionar dois navios fixos (um horizontal e um vertical)
void posicionarNavios(int tabuleiro[TAM_TAB][TAM_TAB]) {
    int linha_h = 2, coluna_h = 4;
    int linha_v = 5, coluna_v = 7;

    // Navio horizontal
    for (int j = 0; j < 3; j++)
        tabuleiro[linha_h][coluna_h + j] = NAVIO;

    // Navio vertical
    for (int i = 0; i < 3; i++)
        tabuleiro[linha_v + i][coluna_v] = NAVIO;
}

// ----------------------
// MATRIZES DE HABILIDADES
// ----------------------

// Cria uma matriz em forma de cone apontando para baixo
void criarCone(int cone[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // Condição: forma de cone (triângulo isósceles apontando para baixo)
            if (j >= (TAM_HAB / 2 - i) && j <= (TAM_HAB / 2 + i))
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Cria uma matriz em forma de cruz
void criarCruz(int cruz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // Linha e coluna centrais = 1
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Cria uma matriz em forma de octaedro (losango)
void criarOctaedro(int octaedro[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // A distância de (i,j) ao centro deve ser menor ou igual ao raio
            if (abs(i - centro) + abs(j - centro) <= centro)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }
}

// Função genérica para aplicar uma habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TAB][TAM_TAB], int habilidade[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    int centro = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTab = origemLinha - centro + i;
                int colunaTab = origemColuna - centro + j;

                // Garante que está dentro dos limites do tabuleiro
                if (linhaTab >= 0 && linhaTab < TAM_TAB && colunaTab >= 0 && colunaTab < TAM_TAB) {
                    // Marca a área da habilidade (sem sobrescrever navios)
                    if (tabuleiro[linhaTab][colunaTab] == AGUA)
                        tabuleiro[linhaTab][colunaTab] = HABILIDADE;
                }
            }
        }
    }
}

// Função auxiliar para exibir uma matriz de habilidade
void exibirHabilidade(int habilidade[TAM_HAB][TAM_HAB], const char *nome) {
    printf("\n=== MATRIZ DE HABILIDADE: %s ===\n", nome);
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            printf("%d ", habilidade[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TAB][TAM_TAB];

    // Inicializa e posiciona navios
    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);

    // Cria as três habilidades
    int cone[TAM_HAB][TAM_HAB], cruz[TAM_HAB][TAM_HAB], octaedro[TAM_HAB][TAM_HAB];
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Exibe as matrizes das habilidades
    exibirHabilidade(cone, "CONE");
    exibirHabilidade(cruz, "CRUZ");
    exibirHabilidade(octaedro, "OCTAEDRO");

    // Define pontos de origem para as habilidades no tabuleiro
    int origemConeLinha = 1, origemConeColuna = 2;
    int origemCruzLinha = 6, origemCruzColuna = 4;
    int origemOctaedroLinha = 8, origemOctaedroColuna = 8;

    // Aplica as habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, origemConeLinha, origemConeColuna);
    aplicarHabilidade(tabuleiro, cruz, origemCruzLinha, origemCruzColuna);
    aplicarHabilidade(tabuleiro, octaedro, origemOctaedroLinha, origemOctaedroColuna);

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}