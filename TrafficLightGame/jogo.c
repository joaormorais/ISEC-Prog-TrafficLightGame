/*
 
 Instituto Superior de Engenharia de Coimbra
 Trabalho realizado no âmbito da disciplica de Programação por João Morais (2019134282)
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "guarda.h"
#include "jogo.h"
#include "computador.h"
#include "verifica.h"

void inicia_jogo(int nL, int nC, int tam, char tabuleiro[]) {

    for (int i = 0; i < tam; i++) {

        tabuleiro[i] = '.'; // atribuir valores ao tabuleiro para depois mostrar

    }

    // mostrar a primeira tabela do jogo
    mostra_tabuleiro(nL, nC, tam, tabuleiro);

}

void mostra_tabuleiro(int nL, int nC, int tam, char tabuleiro[]) {

    int nlinha = 1; // -- START estrutura exterior do tabuleiro 
    int ncoluna = 1;

    printf("\n   ");

    for (int i = 0; i < nC; i++) {

        printf("%d ", ncoluna);
        ncoluna++;

    }

    printf("\n");

    for (int i = 0; i < nL; i++) {

        printf("%d ", nlinha); // -- END estrutura exterior do tabuleiro 

        for (int j = 0; j < nC; j++) {

            printf("%2c", tabuleiro[(i * (nC)) + j]); // mostra o tabuleiro

        }
        printf("\n");
        nlinha++;
    }
}

void jogadas(int nL, int nC, int tam, char tabuleiro[], int computador, int doisjogadores, guarda_tab *guarda_jogada, int *vitoria, controlo legal) {

    int *linhaoucoluna = 0;

    while (1) {

        int escolhaA;
        int escolhaB;

        //do {
            do {

                printf("\n------ [JOGADOR A] ------\n");
                printf("\nO Jogador A pode jogar %d pedra(s) e adicionar %d linhas/colunas\n", legal.podejogarpedraA, legal.podeadicionarA);
                printf("\nQual e a jogada que pretende fazer?\n");
                printf("1 - jogar uma peca\n2 - colocar uma pedra\n3 - adicionar uma linha/coluna\n4 - ver o historico de jogadas\n5 - voltar sem guardar\n6 - guardar jogo e voltar\n");
                printf("---> ");
                scanf("%d", &escolhaA);

                if (escolhaA == 4)
                    mostraJogadas(guarda_jogada);

            } while (1 > escolhaA > 6 || escolhaA == 4);
        //} while (escolhaA == 2 && legal.podejogarpedraA < 1 || escolhaA == 3 && legal.podeadicionarA < 1);

        switch (escolhaA) {

            case 1:

                guarda_jogada = jogapeca(nL, nC, tam, tabuleiro, 'A', guarda_jogada); // função para jogar uma peça

                vitoria = verificaVitoria(nL, nC, tam, tabuleiro);

                if (vitoria == 1) {
                    printf("\nO jogador A venceu o jogo!\n");
                    escreveVitoria(nL, nC, tam, tabuleiro, 'A', guarda_jogada);
                    return;
                }

                if (computador == 1) {

                    guarda_jogada = jogadaPC(&nL, &nC, &tam, tabuleiro, &legal.pedrasPC, &legal.adicionaLCpc, guarda_jogada);

                    vitoria = verificaVitoria(nL, nC, tam, tabuleiro);

                    if (vitoria == 1) {
                        printf("\nO computador venceu o jogo!\n");
                        escreveVitoria(nL, nC, tam, tabuleiro, 'C', guarda_jogada);
                        return;
                    }
                }

                break;

            case 2:
                legal.podejogarpedra = legal.podejogarpedraA;
                guarda_jogada = jogapedra(nL, nC, tam, tabuleiro, 'A', legal.podejogarpedra, guarda_jogada); // função para jogar uma pedra
                (legal.podejogarpedraA)--;

                if (computador == 1) {

                    guarda_jogada = jogadaPC(&nL, &nC, &tam, tabuleiro, legal.pedrasPC, legal.adicionaLCpc, guarda_jogada);

                    vitoria = verificaVitoria(nL, nC, tam, tabuleiro);

                    if (vitoria == 1) {
                        printf("\nO computador venceu o jogo!\n");
                        escreveVitoria(nL, nC, tam, tabuleiro, 'C', guarda_jogada);
                        return;
                    }
                }

                break;

            case 3:
            {
                legal.podeadicionar = legal.podeadicionarA;
                tabuleiro = adicionalinhacoluna(&nL, &nC, &tam, tabuleiro, 'A', legal.podeadicionar, &linhaoucoluna, guarda_jogada); // função para adicionar um linha/coluna
                (legal.podeadicionarA)--;

                if (linhaoucoluna == 1) {
                    guarda_jogada = guardaJogada(0, 0, nL, nC, tam, tabuleiro, 'A', 'L', guarda_jogada);
                } else if (linhaoucoluna == 2) {
                    guarda_jogada = guardaJogada(0, 0, nL, nC, tam, tabuleiro, 'A', 'C', guarda_jogada);
                }

                if (computador == 1) {

                    guarda_jogada = jogadaPC(&nL, &nC, &tam, tabuleiro, legal.pedrasPC, legal.adicionaLCpc, guarda_jogada);

                    vitoria = verificaVitoria(nL, nC, tam, tabuleiro);

                    if (vitoria == 1) {
                        printf("\nO computador venceu o jogo!\n");
                        escreveVitoria(nL, nC, tam, tabuleiro, 'A', guarda_jogada);
                        return;
                    }
                }

                break;
            }

            case 5:
            {
                int certeza;

                printf("\nTem a certeza que quer terminar o jogo sem o guardar?\n1 - Sim\n2 - Nao\n");
                printf("---> ");
                scanf("%d", &certeza);

                if (certeza == 1) {
                    printf("\nTerminaste o jogo!\n");
                    free(tabuleiro);
                    return;
                } else
                    break;
            }


            case 6:
            {
                escreveJogada(nL, nC, tam, tabuleiro, 'A', computador, doisjogadores, legal);

                printf("\nJogo guardado!\n");
                free(tabuleiro);
                return;
            }

        }

        if (doisjogadores == 1) {

            //do {
                do {

                    printf("\n------ [JOGADOR B] ------\n");
                    printf("O Jogador B pode jogar %d pedra(s) e adicionar %d linhas/colunas\n", legal.podejogarpedraB, legal.podeadicionarB);
                    printf("\nQual e a jogada que pretende fazer?\n");
                    printf("1 - jogar uma peca\n2 - colocar uma pedra\n3 - adicionar uma linha/coluna\n4 - ver o historico de jogadas\n5 - voltar sem guardar\n6 - guardar jogo e voltar\n");
                    printf("---> ");
                    scanf("%d", &escolhaB);

                    if (escolhaB == 4)
                        mostraJogadas(guarda_jogada);

                } while (1 > escolhaB > 5 || escolhaB == 4);
            //} while (escolhaB == 2 && legal.podejogarpedraB < 1 || escolhaB == 3 && legal.podeadicionarB < 1);

            switch (escolhaB) {

                case 1:

                    guarda_jogada = jogapeca(nL, nC, tam, tabuleiro, 'B', guarda_jogada); // função para jogar uma peça

                    vitoria = verificaVitoria(nL, nC, tam, tabuleiro);

                    if (vitoria == 1) {
                        printf("\nO jogador B venceu o jogo!\n");
                        escreveVitoria(nL, nC, tam, tabuleiro, 'B', guarda_jogada);
                        return;
                    }

                    break;

                case 2:
                    legal.podejogarpedra = legal.podejogarpedraB;
                    guarda_jogada = jogapedra(nL, nC, tam, tabuleiro, 'B', legal.podejogarpedra, guarda_jogada); // função para jogar uma pedra
                    (legal.podejogarpedraB)--;

                    break;

                case 3:
                {
                    legal.podeadicionar = legal.podeadicionarB;
                    tabuleiro = adicionalinhacoluna(&nL, &nC, &tam, tabuleiro, 'B', legal.podeadicionar, &linhaoucoluna, guarda_jogada); // função para adicionar um linha/coluna
                    (legal.podeadicionarB)--;

                    if (linhaoucoluna == 1) {
                        guarda_jogada = guardaJogada(0, 0, nL, nC, tam, tabuleiro, 'B', 'L', guarda_jogada);
                    } else if (linhaoucoluna == 2) {
                        guarda_jogada = guardaJogada(0, 0, nL, nC, tam, tabuleiro, 'B', 'C', guarda_jogada);
                    }

                    break;
                }

                case 5:
                {
                    int certeza;

                    printf("\nTem a certeza que quer terminar o jogo sem o guardar?\n1 - Sim\n2 - Nao\n");
                    printf("---> ");
                    scanf("%d", &certeza);

                    if (certeza == 1) {
                        printf("\nTerminaste o jogo!\n");
                        free(tabuleiro);
                        return;
                    } else
                        break;
                }

                case 6:
                {
                    escreveJogada(nL, nC, tam, tabuleiro, 'B', computador, doisjogadores, legal);

                    printf("\nJogo guardado!\n");
                    free(tabuleiro);
                    return;
                }

            }

        }
    }
}

guarda_tab * jogapeca(int nL, int nC, int tam, char tabuleiro[], char jogador, guarda_tab * guarda_jogada) {

    char jogada;
    int jogadaL, jogadaC, legal = 0;

    do {
        printf("\nEm que linha deseja jogar? (entre 1 e %d)\n", nL);
        printf("---> ");
        scanf("%d", &jogadaL);
        printf("\nEm que coluna deseja jogar? (entre 1 e %d)\n", nC);
        printf("---> ");
        scanf("%d", &jogadaC);

        if (jogadaL > 0 && jogadaL <= nL && jogadaC > 0 && jogadaC <= nC) {
            do {
                printf("\nQue peca pretende jogar?\n");
                printf("G - peca verde\nY - peca amarela\nR - peca vermelha\n");
                printf("---> ");
                scanf(" %c", &jogada);

                switch (jogada) {

                    case 'G':
                        // uma vez que as posições do tabuleiro são 0, 1, 2 (...) retirei 1 unidade para a peça ir para a posição correta
                        jogadaL -= 1;
                        jogadaC -= 1;

                        legal = verificaP1(nL, nC, tam, tabuleiro, jogadaL, jogadaC, jogada); // verificar se a jogada é legal

                        if (legal == 0)
                            jogapeca(nL, nC, tam, tabuleiro, jogador, guarda_jogada);

                        guarda_jogada = guardaJogada(jogadaL, jogadaC, nL, nC, tam, tabuleiro, jogador, 'G', guarda_jogada);

                        return guarda_jogada;

                    case 'Y':
                        // uma vez que as posições do tabuleiro são 0, 1, 2 (...) retiramos 1 unidade para a peça ir para a posição correta
                        jogadaL -= 1;
                        jogadaC -= 1;

                        legal = verificaP2(nL, nC, tam, tabuleiro, jogadaL, jogadaC, jogada); // verificar se a jogada é legal

                        if (legal == 0)
                            jogapeca(nL, nC, tam, tabuleiro, jogador, guarda_jogada);

                        guarda_jogada = guardaJogada(jogadaL, jogadaC, nL, nC, tam, tabuleiro, jogador, 'Y', guarda_jogada);

                        return guarda_jogada;

                    case 'R':
                        // uma vez que as posições do tabuleiro são 0, 1, 2 (...) retiramos 1 unidade para a peça ir para a posição correta
                        jogadaL -= 1;
                        jogadaC -= 1;

                        legal = verificaP3(nL, nC, tam, tabuleiro, jogadaL, jogadaC, jogada); // verificar se a jogada é legal

                        if (legal == 0)
                            jogapeca(nL, nC, tam, tabuleiro, jogador, guarda_jogada);

                        guarda_jogada = guardaJogada(jogadaL, jogadaC, nL, nC, tam, tabuleiro, jogador, 'R', guarda_jogada);

                        return guarda_jogada;

                }
            } while (jogada != 'G' || jogada != 'Y' || jogada != 'R');
        }
    } while (jogadaL < 1 || jogadaL > nL || jogadaC < 1 || jogadaC > nC);

    return; // voltar às diferentes jogadas do player

}

guarda_tab * jogapedra(int nL, int nC, int tam, char tabuleiro[], char jogador, int podejogarpedra, guarda_tab * guarda_jogada) {

    // primeira condição de todas que evita trabalho por parte do utilizador caso ele não possa jogar mais pedras

    if (podejogarpedra < 1) {
        printf("\nNao tens mais pedras para jogar!\n");
        return;
    }

    char jogada;
    int jogadaL, jogadaC, legal;

    do {
        printf("\nEm que linha deseja jogar? (entre 1 e %d)\n", nL);
        printf("---> ");
        scanf("%d", &jogadaL);
        printf("\nEm que coluna deseja jogar? (entre 1 e %d)\n", nC);
        printf("---> ");
        scanf("%d", &jogadaC);

        // uma vez que as posições do tabuleiro são 0, 1, 2 (...) retiramos 1 unidade para a peça ir para a posição correta
        jogadaL -= 1;
        jogadaC -= 1;

        legal = verificaP4(nL, nC, tam, tabuleiro, jogadaL, jogadaC, jogada);

        if (legal == 0)
            jogapedra(nL, nC, tam, tabuleiro, podejogarpedra, jogador, guarda_jogada);

    } while (3 > jogadaL > nL || 3 > jogadaC > nC);

    guarda_jogada = guardaJogada(jogadaL, jogadaC, nL, nC, tam, tabuleiro, jogador, 'P', guarda_jogada);

    return guarda_jogada;

}

char* adicionalinhacoluna(int *nL, int *nC, int *tam, char tabuleiro[], char jogador, int podeadicionar, int *linhaoucoluna, guarda_tab * guarda_jogada) {

    if (podeadicionar <= 2 && podeadicionar > 0) {
        char escolha;

        do {
            printf("\nDeseja adicionar uma linha, ou uma coluna?\nL - linha\nC - coluna\n---> ");
            //fflush(stdin);
            scanf(" %c", &escolha);

            switch (escolha) {

                case 'L':
                {
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

                    mostra_tabuleiro(*nL, *nC, *tam, tabuleiro_v2);

                    *linhaoucoluna = 1;

                    return tabuleiro_v2;
                }

                case 'C':
                {
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

                        mostra_tabuleiro(*nL, *nC, *tam, tabuleiro_v2);

                        *linhaoucoluna = 2;

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

                        mostra_tabuleiro(*nL, *nC, *tam, tabuleiro_v2);

                        *linhaoucoluna = 2;

                        return tabuleiro_v2;
                    }
                }
            }

        } while (escolha != 'L' && escolha != 'C');

    } else {
        printf("\nNao pode adicionar linhas/colunas\n");
    }

}

int jogadaParaJogadorB(int nL, int nC, int tam, char tabuleiro[], guarda_tab *guarda_jogada, int *vitoria, controlo legal) {

    int escolhaB;

    do {

        printf("\n------ [JOGADOR B] ------\n");
        printf("\nQual e a jogada que pretende fazer?\n");
        printf("1 - jogar uma peca\n2 - colocar uma pedra\n3 - adicionar uma linha/coluna\n4 - ver o historico de jogadas\n5 - voltar ao menu\n");
        printf("---> ");
        scanf("%d", &escolhaB);

        if (escolhaB == 4)
            mostraJogadas(guarda_jogada);

    } while (1 > escolhaB > 5 || escolhaB == 4);

    switch (escolhaB) {

        case 1:

            guarda_jogada = jogapeca(nL, nC, tam, tabuleiro, 'B', guarda_jogada);

            vitoria = verificaVitoria(nL, nC, tam, tabuleiro);

            if (vitoria == 1) {
                printf("\nO jogador B venceu o jogo!\n");
                escreveVitoria(nL, nC, tam, tabuleiro, 'B', guarda_jogada);
                return 1;
            }

            return 0;

        case 2:
            legal.podejogarpedra = legal.podejogarpedraB;
            guarda_jogada = jogapedra(nL, nC, tam, tabuleiro, 'B', legal.podejogarpedra, guarda_jogada);
            legal.podejogarpedraB--;

            return 0;

        case 3:
        {
            char *linhaoucolunaB;
            legal.podeadicionar = legal.podeadicionarB;
            tabuleiro = adicionalinhacoluna(&nL, &nC, &tam, tabuleiro, 'B', legal.podeadicionar, &linhaoucolunaB, guarda_jogada);
            legal.podeadicionarB--;

            return 0;
        }

        case 5:
        {
            printf("\nVoltou ao menu principal.\n");
            return 1;
        }


    }

}