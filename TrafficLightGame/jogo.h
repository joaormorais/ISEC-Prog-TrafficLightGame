/*
 
 Instituto Superior de Engenharia de Coimbra
 Trabalho realizado no âmbito da disciplica de Programação por João Morais (2019134282)
 
 */

#include "guarda.h"

#ifndef JOGO_H
#define JOGO_H

#define G 'G'
#define Y 'Y'
#define R 'R'
#define PEDRA 'P'

void inicia_jogo(int nL, int nC, int tam, char tabuleiro[]);

void mostra_tabuleiro(int nL, int nC, int tam, char tabuleiro[]);

void jogadas(int nL, int nC, int tam, char tabuleiro[], int computador, int doisjogadores, guarda_tab *guarda_jogada, int *vitoria, controlo legal);

guarda_tab* jogapeca(int nL, int nC, int tam, char tabuleiro[], char jogador, guarda_tab *guarda_jogada);

guarda_tab* jogapedra(int nL, int nC, int tam, char tabuleiro[], char jogador, int podejogarpedra, guarda_tab *guarda_jogada);

char* adicionalinhacoluna(int *nL, int *nC, int *tam, char tabuleiro[], char jogador, int podeadicionar, int *linhaoucoluna, guarda_tab *guarda_jogada);

int jogadaParaJogadorB(int nL, int nC, int tam, char tabuleiro[], guarda_tab *guarda_jogada, int *vitoria, controlo legal);

#endif /* JOGO_H */

