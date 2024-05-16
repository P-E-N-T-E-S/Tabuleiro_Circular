#include <stdio.h>
#include <stdlib.h>
#include "tabuleiro.h"
#include "perguntas.h"
#include "ranking.h"

int main(void) {
    //setup
    Casa *head=NULL, *tail=NULL;
    Pergunta *facil = NULL, *medio = NULL, *dificil = NULL;
    int qtdfacil = 0, qtdmedia = 0, qtddificil = 0;
    char dump;
    FILE *facilarq = fopen("facil.txt", "r");
    FILE *mediaarq = fopen("medio.txt", "r");
    FILE *dificilarq = fopen("dificil.txt", "r");
    qtdfacil = qtdPerguntas(facilarq);
    qtdmedia = qtdPerguntas(mediaarq);
    qtddificil = qtdPerguntas(dificilarq);

    facil = perguntasInitF(facil, qtdfacil);
    medio = perguntasInitM(medio, qtdmedia);
    dificil = perguntasInitD(dificil, qtddificil);

    inicializarTabuleiro(&head, &tail, facil, medio, dificil);

    int escolha;
    while(1){
        system("clear");
        printf("Bem vindo ao TABULEIRO CIRCULAR\n");
        printf("Escolha uma das opções:\n");
        printf("1) Jogar uma partida\n");
        printf("2) Regras\n");
        printf("3) Ver vencedores\n");
        printf("4) sair!\n");
        scanf("%i",&escolha);
        system("clear");
        if (escolha == 1){
            int qtdjogadores, rounds, resultado;
            char enter;
            printf("Quantos jogadores vão disputar essa partida?\n");
            scanf("%d", &qtdjogadores);
            Jogador jogadores[qtdjogadores];
            cadastrarJogadores(jogadores, head, qtdjogadores);
            printf("Quantos rounds vão ser jogados?\nCada round corresponde a um turno de cada jogador\n");
            scanf("%d", &rounds);
            system("clear");
            //execucao do jogo
            printf("Agora vamos ver a ordem dos jogadores pelo dado\n");
            scanf("%c", &enter);
            for(int i=0; i<qtdjogadores; i++){
                printf("Jogador: %s, pressione Enter para rodar seu dado...\n", jogadores[i].nome);
                scanf("%c", &enter);
                resultado = D6();
                jogadores[i].dadoposicao = resultado;
                printf("O resultado do seu dado foi: %d\n", resultado);
            }
            esperar();
            system("clear");

            iniciativaJogadores(jogadores, qtdjogadores);

            printf("A ordem dos jogadores ficou:\n");
            imprimirJogadores(jogadores, qtdjogadores);

            for(int i=0; i<rounds; i++){
                for(int j=0; j<qtdjogadores; j++){
                    printf("Vez do jogador: %s - %d pontos\n", jogadores[j].nome, jogadores[j].pontuacao);
                    printf("Pressione Enter para rodar seu dado\n");
                    scanf("%c", &enter);
                    resultado = D6();
                    printf("Voce tirou %d!\n", resultado);
                    printf("Andando %d passos...\n", resultado);
                    avancar(&jogadores[j], resultado);
                }
            }
            finalizarJogo(jogadores, rounds, qtdjogadores);
            break;
        }
        if (escolha == 2){
            regras();
            scanf("%c", &dump);
            printf("\n");
        }
        if (escolha == 3){
            lerVencedor();
        }
        if (escolha == 4){
            exit(0);
        }
        else{
            printf("Opção inválida, tente novamente!\n");
        }
    }
    return 0;
}

