/*
 
 Instituto Superior de Engenharia de Coimbra
 Trabalho realizado no âmbito da disciplica de Programação por João Morais (2019134282)
 
 */

#ifndef GUARDA_H
#define GUARDA_H

typedef struct guarda {
    int linha, coluna, jogada, k, nLg, nCg, tamG; // linha e coluna onde foi feita a jogada + jogada feita + nº da jogada
    char jogador, tabuleiroguardado[256]; // jogador que fez a jogada + tabuleiro da jogada guardada

    struct guarda *proximajogada; // próxima jogada

} guarda_tab;

typedef struct jogo { //struct para quando um jogador quer parar o jogo e recomecar
    
    // estado do tabuleiro
    int nL2, nC2, tam2, ultimojogador, computador2, doisjogadores2, podejogarpedraA2, podejogarpedraB2, podejogarpedra2, podeadicionarA2, podeadicionarB2, podeadicionar2, pedrasPC2, adicionaLCpc2;
    
    char tabuleiro2[256]; // tabuleiro em que vai ser guardado o tabuleiro normal
    
} jogoguardado; 

typedef struct variaveis {
    
    int podejogarpedraA, podejogarpedraB, podejogarpedra; // variáveis que indicam a possibilidade de ser jogada uma pedra por parte de um player
    int podeadicionarA, podeadicionarB, podeadicionar; // variáveis que indicam a possibilidade de ser adicionada uma linha/coluna por parte de um player

    int pedrasPC, adicionaLCpc; // variáveis de controlo para o computador

} controlo;

guarda_tab* guardaJogada(int jogadaL, int jogadaC, int nL, int nC, int tam, char tabuleiro[], char jogador, char jogada, guarda_tab *guarda_jogada);

void mostraJogadas(guarda_tab *guarda_jogada);

void escreveJogada(int nL, int nC, int tam, char tabuleiro[], char ultimoJogador, int computador, int doisjogadores, controlo legal);

void escreveVitoria(int nL, int nC, int tam, char tabuleiro[], char ultimoJogador, guarda_tab *guarda_jogada);

int contaJogadas(guarda_tab *guarda_jogada);

#endif /* GUARDA_H */

