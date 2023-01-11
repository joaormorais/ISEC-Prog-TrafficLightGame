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

guarda_tab* guardaJogada(int jogadaL, int jogadaC, int nL, int nC, int tam, char tabuleiro[], char jogador, char jogada, guarda_tab *guarda_jogada) {

    guarda_tab *aux;

    if (guarda_jogada == NULL) {

        guarda_jogada = malloc(sizeof (guarda_tab));

        if (guarda_jogada == NULL) {
            printf("\n[E R R O]\nErro ao alocar memória.\n");
            return NULL;
        }

        guarda_jogada->linha = jogadaL;
        guarda_jogada->coluna = jogadaC;
        guarda_jogada->jogada = jogada;
        guarda_jogada->jogador = jogador;
        guarda_jogada->k = 1;
        guarda_jogada->nLg = nL;
        guarda_jogada->nCg = nC;
        guarda_jogada->tamG = tam;
        //guarda_jogada->tabuleiroguardado = tabuleiro;
        strcpy(guarda_jogada->tabuleiroguardado, tabuleiro);

        guarda_jogada->proximajogada = NULL;

    } else {

        aux = malloc(sizeof (guarda_tab));

        if (aux == NULL) {
            printf("\n[E R R O]\nErro ao alocar memória.\n");
            return guarda_jogada;
        }

        aux->linha = jogadaL;
        aux->coluna = jogadaC;
        aux->jogada = jogada;
        aux->jogador = jogador;
        aux->k = guarda_jogada->k + 1;
        aux->nLg = nL;
        aux->nCg = nC;
        aux->tamG = tam;
        //aux->tabuleiroguardado = tabuleiro; 
        strcpy(aux->tabuleiroguardado, tabuleiro);

        aux->proximajogada = guarda_jogada;
        guarda_jogada = aux;

    }

    return guarda_jogada;

}

void mostraJogadas(guarda_tab *guarda_jogada) {

    if (guarda_jogada == NULL) {
        printf("\nAinda nao foram realizadas jogadas!\n");
        return;
    }

    guarda_tab *aux = guarda_jogada;

    int verJogadas, i = 0;

    do {
        printf("\n--------------- Ja foram executadas %d jogadas ---------------\n", guarda_jogada->k);

        printf("\nQuantas jogadas deseja visualizar?\n");
        printf("exemplo: se escolher 3 jogadas, o programa mostra as 3 jogadas anteriores a atual.\n");

        printf("--> ");
        scanf("%d", &verJogadas);
    } while (verJogadas > guarda_jogada->k || verJogadas < 0);

    printf("\n----------------- LISTA DE JOGADAS ANTERIORES -----------------\n");

    while (i < verJogadas) {

        printf("\n----------------------------------------------\n");

        if (aux->k == guarda_jogada->k)
            printf("Jogada numero: ATUAL\n");
        else
            printf("Jogada numero: %d\n", aux->k);

        if (aux->jogador == 'C')
            printf("Jogada feita pelo computador!\n");
        else
            printf("Jogada feita por: Jogador %c\n", aux->jogador);

        if (aux->jogada != 'L' && aux->jogada != 'C') {
            printf("Jogada feita na coluna: %d\n", aux->coluna + 1);
            printf("Jogada feita na linha: %d\n", aux->linha + 1);
        }

        if (aux->jogada == 'G')
            printf("\nFoi jogada uma peca verde\n");
        else if (aux->jogada == 'Y')
            printf("\nFoi jogada uma peca amarela\n");
        else if (aux->jogada == 'R')
            printf("\nFoi jogada uma peca vermelha\n");
        else if (aux->jogada == 'P')
            printf("\nFoi jogada uma pedra\n");
        else if (aux->jogada == 'L')
            printf("\nFoi adicionada uma linha\n");
        else if (aux->jogada == 'C')
            printf("\nFoi adicionada uma coluna\n");

        // Mostrar o tabuleiro guardado

        int nlinha = 1; // -- START estrutura exterior do tabuleiro 
        int ncoluna = 1;

        printf("\n   ");

        for (int i = 0; i < aux->nCg; i++) {

            printf("%d ", ncoluna);
            ncoluna++;

        }

        printf("\n");

        for (int i = 0; i < aux->nLg; i++) {

            printf("%d ", nlinha); // -- END estrutura exterior do tabuleiro 

            for (int j = 0; j < aux->nCg; j++) {

                printf("%2c", aux->tabuleiroguardado[(i * (aux->nCg)) + j]); // mostra o tabuleiro

            }
            printf("\n");
            nlinha++;
        }

        printf("\n----------------------------------------------\n");

        i++;

        aux = aux->proximajogada;

    }

    printf("\n----------------------------------------------------------------\n");

}

void escreveJogada(int nL, int nC, int tam, char tabuleiro[], char ultimoJogador, int computador, int doisjogadores, controlo legal) {

    jogoguardado ficheiro = {nL, nC, tam, ultimoJogador, computador, doisjogadores, legal.podejogarpedraA, legal.podejogarpedraB, legal.podejogarpedra, legal.podeadicionarA, legal.podeadicionarB, legal.podeadicionar, legal.pedrasPC, legal.adicionaLCpc};

    strcpy(ficheiro.tabuleiro2, tabuleiro);

    FILE *f = fopen("jogo.bin", "wb");

    if (f == NULL) {
        printf("\n[E R R O] nao foi possivel abrir o ficheiro para escrita\n");
        return;
    }

    fwrite(&ficheiro, sizeof (jogoguardado), 1, f);

    fclose(f);
}

void escreveVitoria(int nL, int nC, int tam, char tabuleiro[], char ultimoJogador, guarda_tab *guarda_jogada) {

    int escolha;

    printf("\nPretende guardar este jogo finalizado?\n1 - Sim\n<outro> - Nao\n-->");
    scanf("%d", &escolha);

    if (escolha == 1) {

        char *nomeFicheiro[50];
        int ultimo, i = 0;

        printf("\nQuer guardar o seu jogo num ficheiro com que nome (limite 50 caracteres)?\n-->");
        scanf("%s", &nomeFicheiro);

        guarda_tab *ficheiro2 = guarda_jogada;

        int nJogadas = contaJogadas(ficheiro2);

        strcpy(ficheiro2->tabuleiroguardado, tabuleiro);

        strcat(nomeFicheiro, ".txt");

        FILE *f2 = fopen(nomeFicheiro, "w");

        if (f2 == NULL) {
            printf("\n[E R R O] nao foi possivel abrir o ficheiro para escrita\n");
            return;
        }

        fprintf(f2, "\n----------------- RESULTADO FINAL | JOGO: %s  -----------------\n", nomeFicheiro);

        if (ultimoJogador == 'C')
            fprintf(f2, "\nVitoria por: COMPUTADOR\n");
        else
            fprintf(f2, "\nVitoria por: Jogador %c\n", ultimoJogador);

        while (i < guarda_jogada->k) {

            //fprintf(&ficheiro2, "%d", ficheiro2.); fazer um ciclo para escrever todas as jogadas

            fprintf(f2, "\n----------------------------------------------\n");
            fprintf(f2, "Jogada numero: %d\n", ficheiro2->k);

            if (ficheiro2->jogador != 'C')
                fprintf(f2, "Jogada feita por: Jogador %c\n", ficheiro2->jogador);
            else
                fprintf(f2, "Jogada feita pelo computador!\n");

            if (ficheiro2->jogada != 'L' && ficheiro2->jogada != 'C') {
                fprintf(f2, "Jogada feita na coluna: %d\n", ficheiro2->coluna + 1);
                fprintf(f2, "Jogada feita na linha: %d\n", ficheiro2->linha + 1);
            }

            if (ficheiro2->jogada == 'G')
                fprintf(f2, "\nFoi jogada uma peca verde\n");
            else if (ficheiro2->jogada == 'Y')
                fprintf(f2, "\nFoi jogada uma peca amarela\n");
            else if (ficheiro2->jogada == 'R')
                fprintf(f2, "\nFoi jogada uma peca vermelha\n");
            else if (ficheiro2->jogada == 'P')
                fprintf(f2, "\nFoi jogada uma pedra\n");
            else if (ficheiro2->jogada == 'L')
                fprintf(f2, "\nFoi adicionada uma linha\n");
            else if (ficheiro2->jogada == 'C')
                fprintf(f2, "\nFoi adicionada uma coluna\n");

            // Mostrar o tabuleiro guardado

            int nlinha = 1; // -- START estrutura exterior do tabuleiro 
            int ncoluna = 1;

            fprintf(f2, "\n   ");

            for (int i = 0; i < ficheiro2->nCg; i++) {

                fprintf(f2, "%d ", ncoluna);
                ncoluna++;

            }

            fprintf(f2, "\n");

            for (int i = 0; i < ficheiro2->nLg; i++) {

                fprintf(f2, "%d ", nlinha); // -- END estrutura exterior do tabuleiro 

                for (int j = 0; j < ficheiro2->nCg; j++) {

                    fprintf(f2, "%2c", ficheiro2->tabuleiroguardado[(i * (ficheiro2->nCg)) + j]); // mostra o tabuleiro

                }
                fprintf(f2, "\n");
                nlinha++;
            }

            fprintf(f2, "\n----------------------------------------------\n");

            i++;

            ficheiro2 = ficheiro2->proximajogada;

        }

        fprintf(f2, "\n----------------------------------------------------------------\n");

        fclose(f2);
    } else
        return;

}

int contaJogadas(guarda_tab *guarda_jogada) {

    guarda_tab *aux = guarda_jogada;
    int conta = 0;

    while (aux->proximajogada == NULL) {
        aux = aux->proximajogada; // ultima jogada feita
        conta++;
    }

    return conta;

}