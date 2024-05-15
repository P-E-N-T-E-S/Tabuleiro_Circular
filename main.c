#include <stdio.h>
#include <stdlib.h>
#include "tabuleiro.h"
#include "perguntas.h"
#include "ranking.h"

int main(void) {
    //setup
    Casa *head=NULL, *tail=NULL;
    Pergunta *perguntas;
    FILE *arqperguntas;
    int qtdperguntas;
    arqperguntas = fopen("perguntas.txt", "w");
    qtdperguntas = qtdPerguntas(arqperguntas);
    fseek(arqperguntas, 0, 0);
    perguntasInitF(perguntas, arqperguntas, qtdperguntas);
    inicializarTabuleiro(&head, &tail, );
    int escolha;
    while(1){
        printf("Bem vindo ao TABULEIRO CIRCULAR");
        printf("Escolha uma das opções:");
        printf("1) Jogar uma partida");
        printf("2) Regras");
        printf("3) Ver vencedores");
        printf("4) sair!");
        scanf("%i",&escolha);
        if (escolha == 1){
            int qtdjogadores, rounds, resultado;
            char enter;
            printf("Quantos jogadores vão disputar essa partida?\n");
            scanf("%d", &qtdjogadores);
            Jogador jogadores[qtdjogadores];
            cadastrarJogadores(jogadores, head, qtdjogadores);
            printf("Quantos rounds vão ser jogados?\nCada round corresponde a um turno de cada jogador\n");
            scanf("%d", &rounds);
            //execucao do jogo
            printf("Agora vamos ver a ordem dos jogadores pelo dado");
            for(int i=0; i<qtdjogadores; i++){
                printf("Jogador: %s, pressione Enter para rodar seu dado...\n", jogadores[i].nome);
                scanf("%c", &enter);
                resultado = D6();
                jogadores[i].dadoposicao = resultado;
                printf("O resultado do seu dado foi: %d", resultado);
            }

            iniciativaJogadores(jogadores, qtdjogadores);

            printf("A ordem dos jogadores ficou:\n");
            imprimirJogadores(jogadores, qtdjogadores);
            printf("Jogador %s, pressione Enter para iniciar o jogo", jogadores[0].nome);
            scanf("%c", &enter);

            for(int i=0; i<rounds; i++){
                for(int j=0; j<qtdjogadores; j++){
                    printf("Vez do jogador: %s\n", jogadores[j].nome);
                    printf("Pressione Enter para rodar seu dado\n");
                    scanf("%c", &enter);
                    resultado = D6();
                    printf("Voce tirou %d!\n", resultado);
                    printf("Andando %d passos...\n", resultado);
                    avancar(&jogadores[i], resultado);
                }
            }
            finalizarJogo(jogadores, rounds, qtdjogadores);
            break;
        }
        if (escolha == 2){
            regras();
        }
        if (escolha == 3){
            //opcao 3
        }
        if (escolha == 4){
            exit(0);
        }
        else{
            printf("Opção inválida, tente novamente!");
        }
    }
    return 0;
}

