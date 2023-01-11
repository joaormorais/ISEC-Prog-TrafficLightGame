/*
 
 Instituto Superior de Engenharia de Coimbra
 Trabalho realizado no âmbito da disciplica de Programação por João Morais (2019134282)
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jogo.h"
#include "computador.h"
#include "guarda.h"
#include "utils.h"

int probabilidadePC() {

    int probabilidade = intUniformRnd(1, 5);

    return probabilidade;

}

guarda_tab* jogadaPC(int *nL, int *nC, int *tam, char tabuleiro[], int *pedrasPC, int *adicionaLCpc, guarda_tab *guarda_jogada) {

    // as jogadas do computador são feitas de forma aleatória até uma delas ser considerada válida

    int jogadaValida = 0;

    do {

        int p = probabilidadePC();
        //printf("\n---- jogada do PC : %d ----\n", p); // debug

        switch (p) {

            case 1: // computador vai tentar jogar a peça verde
            {

                int jogadaLpc = intUniformRnd(1, *nL) - 1; // o -1 serve para a peça ser jogada na posição correta
                int jogadaCpc = intUniformRnd(1, *nC) - 1; // o -1 serve para a peça ser jogada na posição correta    

                jogadaValida = verificaPC1(*nL, *nC, *tam, tabuleiro, jogadaLpc, jogadaCpc, jogadaPC);

                if (jogadaValida == 1) {

                    tabuleiro[(jogadaLpc * (*nC)) + jogadaCpc] = G;
                    guarda_jogada = guardaJogada(jogadaLpc, jogadaCpc, *nL, *nC, *tam, tabuleiro, 'C', 'G', guarda_jogada);
                    printf("\n... o computador vai jogar!\n");
                    mostra_tabuleiro(*nL, *nC, *tam, tabuleiro);
                    printf("\nO computador jogou na linha %d e na coluna %d a peca G!\n", jogadaLpc + 1, jogadaCpc + 1);
                    return guarda_jogada;

                }
                break;

            }

            case 2: // computador vai tentar jogar a peça amarela
            {

                int jogadaLpc = intUniformRnd(1, *nL) - 1; // o -1 serve para a peça ser jogada na posição correta
                int jogadaCpc = intUniformRnd(1, *nC) - 1; // o -1 serve para a peça ser jogada na posição correta    

                jogadaValida = verificaPC2(*nL, *nC, *tam, tabuleiro, jogadaLpc, jogadaCpc, jogadaPC);

                if (jogadaValida == 1) {

                    tabuleiro[(jogadaLpc * (*nC)) + jogadaCpc] = Y;
                    guarda_jogada = guardaJogada(jogadaLpc, jogadaCpc, *nL, *nC, *tam, tabuleiro, 'C', 'Y', guarda_jogada);
                    printf("\n... o computador vai jogar!\n");
                    mostra_tabuleiro(*nL, *nC, *tam, tabuleiro);
                    printf("\nO computador jogou na linha %d e na coluna %d a peca Y!\n", jogadaLpc + 1, jogadaCpc + 1);
                    return guarda_jogada;

                }
                break;
            }

            case 3: // computador vai tentar jogar a peça vermelha
            {

                int jogadaLpc = intUniformRnd(1, *nL) - 1; // o -1 serve para a peça ser jogada na posição correta
                int jogadaCpc = intUniformRnd(1, *nC) - 1; // o -1 serve para a peça ser jogada na posição correta    

                jogadaValida = verificaPC3(*nL, *nC, *tam, tabuleiro, jogadaLpc, jogadaCpc, jogadaPC);

                if (jogadaValida == 1) {

                    tabuleiro[(jogadaLpc * (*nC)) + jogadaCpc] = R;
                    guarda_jogada = guardaJogada(jogadaLpc, jogadaCpc, *nL, *nC, *tam, tabuleiro, 'C', 'R', guarda_jogada);
                    printf("\n... o computador vai jogar!\n");
                    mostra_tabuleiro(*nL, *nC, *tam, tabuleiro);
                    printf("\nO computador jogou na linha %d e na coluna %d a peca R!\n", jogadaLpc + 1, jogadaCpc + 1);
                    return guarda_jogada;

                }
                break;
            }

            case 4: // computador vai tentar jogar uma pedra
            {

                int jogadaLpc = intUniformRnd(1, *nL) - 1; // o -1 serve para a peça ser jogada na posição correta
                int jogadaCpc = intUniformRnd(1, *nC) - 1; // o -1 serve para a peça ser jogada na posição correta    

                jogadaValida = verificaPC4(*nL, *nC, *tam, tabuleiro, jogadaLpc, jogadaCpc, jogadaPC, pedrasPC);

                if (jogadaValida == 1) {

                    tabuleiro[(jogadaLpc * (*nC)) + jogadaCpc] = PEDRA;
                    guarda_jogada = guardaJogada(jogadaLpc, jogadaCpc, *nL, *nC, *tam, tabuleiro, 'C', 'P', guarda_jogada);
                    printf("\n... o computador vai jogar!\n");
                    mostra_tabuleiro(*nL, *nC, *tam, tabuleiro);
                    printf("\nO computador jogou na linha %d e na coluna %d uma pedra!\n", jogadaLpc + 1, jogadaCpc + 1);
                    return guarda_jogada;
                }
                break;
            }

            case 5: // computador vai tentar adicionar uma linha/coluna
            {

                if (*adicionaLCpc <= 2 && *adicionaLCpc > 0) {

                    int adcLCpc = intUniformRnd(1, 2); // alterar isto para o pc poder jogar colunas

                    if (adcLCpc == 1) {
                        tabuleiro = adicionalinhaPC(nL, nC, tam, tabuleiro, guarda_jogada);
                        (*adicionaLCpc)--;

                        guarda_jogada = guardaJogada(0, 0, nL, nC, tam, tabuleiro, 'C', 'L', guarda_jogada);

                        printf("\nO computador adicionou uma nova linha!\n");
                        return guarda_jogada;
                    } else {
                        tabuleiro = adicionacolunaPC(nL, nC, tam, tabuleiro, guarda_jogada);
                        (*adicionaLCpc)--;

                        guarda_jogada = guardaJogada(0, 0, *nL, *nC, *tam, tabuleiro, 'C', 'C', guarda_jogada);

                        printf("\nO computador adicionou uma nova coluna!\n");
                        return guarda_jogada;
                    }

                }
                break;
            }
        }
    } while (jogadaValida == 0);
}

int verificaPC1(int nL, int nC, int tam, char tabuleiro[], int jogadaLpc, int jogadaCpc, char jogadaPC) {

    int valida = 0;

    // verifica se não está a jogar a mesma peça

    if (tabuleiro[(jogadaLpc * nC) + jogadaCpc] == G) {
        return valida;
    }

    // verifica se não está a jogar em cima de uma pedra

    if (tabuleiro[(jogadaLpc * nC) + jogadaCpc] == PEDRA) {
        return valida;
    }

    // verificar se é possível jogar a peça verde

    if (tabuleiro[(jogadaLpc * nC) + jogadaCpc] == Y) {
        return valida;
    } else if (tabuleiro[(jogadaLpc * nC) + jogadaCpc] == R) {
        return valida;
    }

    valida = 1;

    return valida;

}

int verificaPC2(int nL, int nC, int tam, char tabuleiro[], int jogadaLpc, int jogadaCpc, char jogadaPC) {

    int valida = 0;

    // verifica se não está a jogar a mesma peça

    if (tabuleiro[(jogadaLpc * nC) + jogadaCpc] == Y) {
        return valida;
    }

    // verifica se não está a jogar em cima de uma pedra

    if (tabuleiro[(jogadaLpc * nC) + jogadaCpc] == PEDRA) {
        return valida;
    }

    // verificar se é possível jogar a peça amarela

    if (tabuleiro[(jogadaLpc * nC) + jogadaCpc] == R) {
        return valida;
    } else if (tabuleiro[(jogadaLpc * nC) + jogadaCpc] == '.') {
        return valida;
    }

    valida = 1;

    return valida;

}

int verificaPC3(int nL, int nC, int tam, char tabuleiro[], int jogadaLpc, int jogadaCpc, char jogadaPC) {

    int valida = 0;

    // verifica se não está a jogar a mesma peça

    if (tabuleiro[(jogadaLpc * nC) + jogadaCpc] == R) {
        return valida;
    }

    // verifica se não está a jogar em cima de uma pedra

    if (tabuleiro[(jogadaLpc * nC) + jogadaCpc] == PEDRA) {
        return valida;
    }

    // verificar se é possível jogar a peça vermelha

    if (tabuleiro[(jogadaLpc * nC) + jogadaCpc] == G) {
        return valida;
    } else if (tabuleiro[(jogadaLpc * nC) + jogadaCpc] == '.') {
        return valida;
    }

    valida = 1;

    return valida;

}

int verificaPC4(int nL, int nC, int tam, char tabuleiro[], int jogadaLpc, int jogadaCpc, char jogadaPC, int *pedrasPC) {

    int valida = 0;

    // verifica se ainda pode jogar pedras

    if (*pedrasPC < 1)
        return valida;

    // verifica se não está a jogar a mesma peça

    if (tabuleiro[(jogadaLpc * nC) + jogadaCpc] == PEDRA)
        return valida;

    // verificar se é possível jogar uma pedra

    if (tabuleiro[(jogadaLpc * nC) + jogadaCpc] != '.') {
        return valida;
    }

    (*pedrasPC)--;

    valida = 1;

    return valida;

}

char* adicionalinhaPC(int *nL, int *nC, int *tam, char tabuleiro[], guarda_tab *guarda_jogada) {

    int novasLinhas = *nL + 1;

    char *tabuleiro_v2 = (char*) malloc(novasLinhas * *nC * sizeof (char));

    if (tabuleiro_v2 == NULL) {
        printf("\n[E R R O]\nErro ao alocar memória.\n");
        return tabuleiro;
    }

    tabuleiro_v2 = tabuleiro;

    for (int i = 0; i < *nC; i++)
        tabuleiro_v2[((*nL) * (*nC)) + i] = '.';


    (*nL)++;
    *tam = *nL * *nC;

    printf("\n... o computador vai jogar!\n");

    mostra_tabuleiro(*nL, *nC, *tam, tabuleiro_v2);

    return tabuleiro_v2;

}

char* adicionacolunaPC(int *nL, int *nC, int *tam, char tabuleiro[], guarda_tab *guarda_jogada) {

    if (*nC == *nL) {

        int novasColunas = *nC + 1;

        char *tabuleiro_v2 = malloc(*nL * novasColunas * sizeof (char));

        if (tabuleiro_v2 == NULL) {
            printf("\n[E R R O]\nErro ao alocar memória.\n");
            return tabuleiro;
        }

        int ajeita = 1;

        (*nC)++;
        *tam = *nL * *nC;

        for (int i = 0; i < *tam; i++)
            tabuleiro_v2[i] = '.';

        for (int i = 0; i < *nL; i++) {
            for (int j = 1; j < *nC; j++) { // ajeitar as posições do tabuleiro
                tabuleiro_v2[(i * (*nC)) + j - ajeita] = tabuleiro[(i * (*nL)) + j - 1];
            }
        }

        printf("\n");

        printf("\n... o computador vai jogar!\n");

        mostra_tabuleiro(*nL, *nC, *tam, tabuleiro_v2);

        return tabuleiro_v2;

    } else if (*nL > *nC || *nL < *nC) {

        int novasColunas = *nC + 1;

        char *tabuleiro_v2 = malloc(*nL * novasColunas * sizeof (char));

        if (tabuleiro_v2 == NULL) {
            printf("\n[E R R O]\nErro ao alocar memória.\n");
            return tabuleiro;
        }

        int ajeita = 1, ajeita2 = 1;

        (*nC)++;
        *tam = *nL * *nC;

        for (int i = 0; i < *tam; i++)
            tabuleiro_v2[i] = '.';

        for (int i = 1; i <= *nL; i++) {
            for (int j = 1; j < *nC; j++) { // ajeitar as posições do tabuleiro
                tabuleiro_v2[((i - 1) * (*nC)) + j - ajeita] = tabuleiro[((i - 1) * (*nC)) + j - ajeita2];
                tabuleiro_v2[(*nC * i) - 1] = '.';

            }
            ajeita2++;
        }

        printf("\n");

        printf("\n... o computador vai jogar!\n");

        mostra_tabuleiro(*nL, *nC, *tam, tabuleiro_v2);

        return tabuleiro_v2;
    }

}

