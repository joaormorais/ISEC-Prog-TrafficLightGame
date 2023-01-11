/*
 
 Instituto Superior de Engenharia de Coimbra
 Trabalho realizado no âmbito da disciplica de Programação por João Morais (2019134282)
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jogo.h"
#include "computador.h"
#include "verifica.h"

int verificaP1(int nL, int nC, int tam, char tabuleiro[], int jogadaL, int jogadaC, char jogada) {

    int legal = 0;

    // verifica se não está a jogar a mesma peça

    if (tabuleiro[(jogadaL * nC) + jogadaC] == G) {
        printf("\nNao podes jogar uma peca igual a peca existente no tabuleiro\n");
        return legal;
    }

    // verifica se não está a jogar em cima de uma pedra

    if (tabuleiro[(jogadaL * nC) + jogadaC] == PEDRA) {
        printf("\nNao podes jogar uma peca em cima de uma pedra\n");
        return legal;
    }

    // verificar se é possível jogar a peça verde

    if (tabuleiro[(jogadaL * nC) + jogadaC] == Y) {
        printf("\nNao podes jogar uma peca verde em cima de uma peca amarela\n");
        return legal;
    } else if (tabuleiro[(jogadaL * nC) + jogadaC] == R) {
        printf("\nNao podes jogar uma peca verde em cima de uma peca vermelha\n");
        return legal;
    }


    // introduz a peça e mostra a tabela com a jogada feita

    tabuleiro[(jogadaL * nC) + jogadaC] = G;

    mostra_tabuleiro(nL, nC, tam, tabuleiro);

    legal = 1;

    return legal;

}

int verificaP2(int nL, int nC, int tam, char tabuleiro[], int jogadaL, int jogadaC, char jogada) {

    int legal = 0;

    // verifica se não está a jogar a mesma peça

    if (tabuleiro[(jogadaL * nC) + jogadaC] == Y) {
        printf("\nNao podes jogar uma peca igual a peca existente no tabuleiro\n");
        return legal;
    }

    // verifica se não está a jogar em cima de uma pedra

    if (tabuleiro[(jogadaL * nC) + jogadaC] == PEDRA) {
        printf("\nNao podes jogar uma peca em cima de uma pedra\n");
        return legal;
    }

    // verificar se é possível jogar a peça amarela

    if (tabuleiro[(jogadaL * nC) + jogadaC] == R) {
        printf("\nNao podes jogar uma amarela verde em cima de uma peca vermelha\n");
        return legal;
    } else if (tabuleiro[(jogadaL * nC) + jogadaC] == '.') {
        printf("\nNao podes jogar uma peca amarela num espaco vazio\n");
        return legal;
    }

    // introduz a peça e mostra a tabela com a jogada feita

    tabuleiro[(jogadaL * nC) + jogadaC] = Y;

    mostra_tabuleiro(nL, nC, tam, tabuleiro);

    legal = 1;

    return legal;

}

int verificaP3(int nL, int nC, int tam, char tabuleiro[], int jogadaL, int jogadaC, char jogada) {

    int legal = 0;

    // verifica se não está a jogar a mesma peça

    if (tabuleiro[(jogadaL * nC) + jogadaC] == R) {
        printf("\nNao podes jogar uma peca igual a peca existente no tabuleiro\n");
        return legal;
    }

    // verifica se não está a jogar em cima de uma pedra

    if (tabuleiro[(jogadaL * nC) + jogadaC] == PEDRA) {
        printf("\nNao podes jogar uma peca em cima de uma pedra\n");
        return legal;
    }

    // verificar se é possível jogar a peça vermelha

    if (tabuleiro[(jogadaL * nC) + jogadaC] == G) {
        printf("\nNao podes jogar uma peca vermelha em cima de uma peca verde!\n");
        return legal;
    } else if (tabuleiro[(jogadaL * nC) + jogadaC] == '.') {
        printf("\nNao podes jogar uma peca vermelha num espaco vazio!\n");
        return legal;
    }

    // introduz a peça e mostra a tabela com a jogada feita

    tabuleiro[(jogadaL * nC) + jogadaC] = R;

    mostra_tabuleiro(nL, nC, tam, tabuleiro);

    legal = 1;

    return legal;

}

int verificaP4(int nL, int nC, int tam, char tabuleiro[], int jogadaL, int jogadaC, char jogada) {

    int legal = 0;

    // verifica se não está a jogar a mesma peça

    if (tabuleiro[(jogadaL * nC) + jogadaC] == PEDRA) {
        printf("\nNao podes jogar uma peca igual a peca existente no tabuleiro!\n");
        return legal;
    }

    // verificar se é possível jogar uma pedra

    if (tabuleiro[(jogadaL * nC) + jogadaC] == '.') {
        tabuleiro[(jogadaL * nC) + jogadaC] = PEDRA;
        mostra_tabuleiro(nL, nC, tam, tabuleiro);
    } else {
        printf("\nNao podes jogar uma pedra em cima de uma peca existente!\n");
        return legal;
    }

    legal = 1;

    return legal;

}

int verificaVitoria(int nL, int nC, int tam, char tabuleiro[]) {

    int vitoria = 0, igualLinhas = 0, igualColunas = 0, igualDiagonalE = 0, igualDiagonalD;

    // Verificar linhas

    for (int i = 0; i < nL; i++) {
        for (int j = 1; j < nC; j++)
            if (tabuleiro[i * nC] != '.' && tabuleiro[i * nC] == tabuleiro[(i * nC) + j]) // verificar as linhas
                igualLinhas++;

        if (igualLinhas == nC - 1) {
            vitoria = 1;
            printf("\nA vitoria deu-se ao completar uma linha com pecas iguais!\n"); // vitoria por linhas iguais
        }

        igualLinhas = 0;
    }

    // Verificar colunas

    for (int i = 0; i < nC; i++) {
        for (int j = 1; j < nL; j++)
            if (tabuleiro[i] != '.' && tabuleiro[i] == tabuleiro[i + (nC * j)])
                igualColunas++;

        if (igualColunas == nL - 1) {
            vitoria = 1;
            printf("\nA vitoria deu-se ao completar uma coluna com pecas iguais!\n"); // vitoria por colunas iguais
        }

        igualColunas = 0;
    }

    // Verificar diagonais

    for (int j = 1; j < nL; j++)
        if (tabuleiro[0] != '.' && tabuleiro[0] == tabuleiro[j + (nC * j)])
            igualDiagonalE++;
        else if (tabuleiro[nC - 1] != '.' && tabuleiro[nC - 1] == tabuleiro[(nC - 1) + ((nC - 1) * j)])
            igualDiagonalD++;

    if (igualDiagonalE == nL - 1 && nL == nC) {
        vitoria = 1;
        printf("\nA vitoria deu-se ao completar uma diagonal com pecas iguais!\n");
    }

    if (igualDiagonalD == nL - 1 && nL == nC) {
        vitoria = 1;
        printf("\nA vitoria deu-se ao completar uma diagonal com pecas iguais!\n");
    }

    return vitoria;

}