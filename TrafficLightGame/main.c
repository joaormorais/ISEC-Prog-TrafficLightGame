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

int main(int argc, char** argv) {

    initRandom(); // inicializar os valores aleatórios

    int nLC, nL, nC, tam; // n linhas e colunas, n linhas, n colunas, tamanho do tabuleiro

    char *tabuleiro = NULL; // tabuleiro

    guarda_tab *guarda_jogada = NULL; // declarar e inicializar ponteiro para guardar o jogo 

    printf("\n#################################################\n");
    printf("\n   Instituto Superior de Engenharia de Coimbra   \n");
    printf("\n#################################################\n");

    printf("\nTrabalho realizado por: Joao Morais - 2019134282\n\n\n");

    // Verifica se existe um ficheiro binário

    FILE *f = fopen("jogo.bin", "rb");

    if (f != NULL) {

        char ultimoJogador; // jogador que está registado no ficheiro binário
        int jogadorBajogar = 0; // variável para saber se o jogadorB foi o último a jogar
        jogoguardado ficheiro; // variável correspondente à estrutura para um jogo guardado
        controlo legal; // variáveis de controlo de jogadas

        int recomecar; // variável para o scanf

        do {
            printf("\nExiste um jogo guardado e pronto a continuar.\nDeseja continuar esse jogo?\n1 - Sim           2 - Nao\n---> ");
            scanf("%d", &recomecar);

            if (recomecar == 1) {

                fread(&ficheiro, sizeof (jogoguardado), 1, f); // abrir o ficheiro

                // Atribuir às variáveis declaradas anteriormente, o valor presente no ficheiro binário

                nL = ficheiro.nL2;
                nC = ficheiro.nC2;
                tam = ficheiro.tam2;

                tabuleiro = malloc(nL * nC * sizeof (char)); // alocar memória para o tabuleiro

                tabuleiro = ficheiro.tabuleiro2;

                int computador = ficheiro.computador2; // variável para saber se o player está a jogar contra o computador
                int doisjogadores = ficheiro.doisjogadores2; // variável para saber se o player está a jogar contra outra pessoa

                int *vitoria = 0; // variável para saber se o jogo terminou por vitória

                legal.podejogarpedraA = ficheiro.podejogarpedraA2;
                legal.podejogarpedraB = ficheiro.podejogarpedraB2;
                legal.podejogarpedra = ficheiro.podejogarpedra2;
                legal.podeadicionarA = ficheiro.podeadicionarA2;
                legal.podeadicionarB = ficheiro.podeadicionarB2;
                legal.podeadicionar = ficheiro.podeadicionar2;

                legal.pedrasPC = ficheiro.pedrasPC2;
                legal.adicionaLCpc = ficheiro.adicionaLCpc2;

                ultimoJogador = ficheiro.ultimojogador; // saber qual é o jogador a jogar

                if (ultimoJogador == 'B')
                    jogadorBajogar = 1;

                fclose(f); // fechar o ficheiro

                // Começo das jogadas

                printf("\nO jogo vai recomecar com o seguinte tabuleiro:\n");
                mostra_tabuleiro(nL, nC, tam, tabuleiro);

                printf("\nO Jogador A pode jogar %d pedra(s) e adicionar %d linhas/colunas\n", legal.podejogarpedraA, legal.podeadicionarA);

                if (doisjogadores == 1)
                    printf("O Jogador B pode jogar %d pedra(s) e adicionar %d linhas/colunas\n", legal.podejogarpedraB, legal.podeadicionarB);
                else if (computador == 1)
                    printf("O computador pode jogar %d pedra(s) e adicionar %d linhas/colunas\n", legal.pedrasPC, legal.adicionaLCpc);

                int acabar = 0; // variável de controlo usada para caso o jogador queira ver apenas o jogo e terminar logo a seguir

                if (jogadorBajogar == 1)
                    acabar = jogadaParaJogadorB(nL, nC, tam, tabuleiro, guarda_jogada, &vitoria, legal);

                if (acabar == 0)
                    jogadas(nL, nC, tam, tabuleiro, computador, doisjogadores, guarda_jogada, &vitoria, legal);

            } else {
                fclose(f);
                break;
            }
        } while (1 > recomecar > 2);

    }

    int escolha;

    do {

        // Menu principal

        printf("\n");
        printf("1 - Iniciar novo jogo multiplayer (local)\n");
        printf("2 - Iniciar novo jogo contra o computador\n");
        printf("0 - Sair do programa\n");
        printf("---> ");
        scanf("%d", &escolha);

        // Escolhas para o menu principal

        switch (escolha) {

            case 0:
                break;

            case 1:
            {

                nLC = intUniformRnd(3, 5); // valor aleatorio uniforme entre [3, 5] para as linhas e colunas do tabuleiro

                tabuleiro = malloc(nLC * nLC * sizeof (char)); // alocar memória para o tabuleiro

                if (tabuleiro == NULL) {
                    printf("\n[E R R O]\nErro ao alocar memória.\n");
                    return (EXIT_SUCCESS);
                }

                tam = nLC * nLC; // tamanho do tabuleiro

                nL = nLC; // separar as linhas
                nC = nLC; // separar as colunas 

                // Declarar e inicializar variáveis para contrar as legalidades dos jogadores

                int *vitoria = 0; // variável para saber se o jogo terminou por vitória

                controlo legal;

                legal.podejogarpedraA = 1;
                legal.podejogarpedraB = 1;

                legal.podeadicionarA = 2;
                legal.podeadicionarB = 2;

                legal.pedrasPC = 1;
                legal.adicionaLCpc = 2;

                // Mostrar o tabuleiro em que o jogo vai ser jogado

                printf("\nO jogo esta a ser jogado num tabuleiro %d x %d\n", nL, nC);
                inicia_jogo(nL, nC, tam, tabuleiro);

                // Começo das jogadas

                int computador = 0; // 0 = o computador não joga & 1 = o computador joga
                int doisjogadores = 1; // 0 = existe um segundo player & 0 = não existe um segundo player

                jogadas(nL, nC, tam, tabuleiro, computador, doisjogadores, guarda_jogada, &vitoria, legal);

                break;
            }

            case 2:
            {

                nLC = intUniformRnd(3, 5); // valor aleatorio uniforme entre [3, 5] para as linhas e colunas do tabuleiro

                tabuleiro = malloc(nLC * nLC * sizeof (char)); // alocar memória para o tabuleiro

                if (tabuleiro == NULL) {
                    printf("\n[E R R O]\nErro ao alocar memória.\n");
                    return (EXIT_SUCCESS);
                }

                tam = nLC * nLC; // tamanho do tabuleiro

                nL = nLC; // separar as linhas
                nC = nLC; // separar as colunas 

                // Declarar e inicializar variáveis para contrar as legalidades dos jogadores

                int *vitoria = 0; // variável para saber se o jogo terminou por vitória

                controlo legal;

                legal.podejogarpedraA = 1;
                legal.podejogarpedraB = 1;

                legal.podeadicionarA = 2;
                legal.podeadicionarB = 2;

                legal.pedrasPC = 1;
                legal.adicionaLCpc = 2;

                // Mostrar o tabuleiro em que o jogo vai ser jogado

                printf("\nO jogo esta a ser jogado num tabuleiro %d x %d\n", nL, nC);
                inicia_jogo(nL, nC, tam, tabuleiro);

                // Começo das jogadas

                int computador = 1; // 0 = o computador não joga & 1 = o computador joga
                int doisjogadores = 0; // 0 = existe um segundo player & 0 = não existe um segundo player

                jogadas(nL, nC, tam, tabuleiro, computador, doisjogadores, guarda_jogada, &vitoria, legal);

                break;
            }
        }
    } while (escolha != 0 && 0 < escolha <= 2);
    return (EXIT_SUCCESS);
}

