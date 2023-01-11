/*
 
 Instituto Superior de Engenharia de Coimbra
 Trabalho realizado no âmbito da disciplica de Programação por João Morais (2019134282)
 
 */

#ifndef COMPUTADOR_H
#define COMPUTADOR_H

int probabilidadePC();

guarda_tab* jogadaPC(int *nL, int *nC, int *tam, char tabuleiro[], int *pedrasPC, int *adicionaLCpc, guarda_tab *guarda_jogada);

int verificaPC1(int nL, int nC, int tam, char tabuleiro[], int jogadaLpc, int jogadaCpc, char jogadaPC);

int verificaPC2(int nL, int nC, int tam, char tabuleiro[], int jogadaLpc, int jogadaCpc, char jogadaPC);

int verificaPC3(int nL, int nC, int tam, char tabuleiro[], int jogadaLpc, int jogadaCpc, char jogadaPC);

int verificaPC4(int nL, int nC, int tam, char tabuleiro[], int jogadaLpc, int jogadaCpc, char jogadaPC, int *pedrasPC);

char* adicionalinhaPC(int *nL, int *nC, int *tam, char tabuleiro[], guarda_tab *guarda_jogada);

char* adicionacolunaPC(int *nL, int *nC, int *tam, char tabuleiro[], guarda_tab *guarda_jogada);

#endif /* COMPUTADOR_H */

