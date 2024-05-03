#include <stdio.h>
#include <stdlib.h>
#include "tabuleiro.h"

int main(void) {
    //setup
    Casa *head=NULL, *tail=NULL;
    Pergunta perguntas[];
    //funcao de ler perguntas
    inicializarTabuleiro(head, tail, perguntas);

    //menu
    //funcao de iniciar jogo
    int qtdjogadores, rounds, resultado;
    char enter;
    printf("Quantos jogadores vão disputar essa partida?\n");
    scanf("%d", &qtdjogadores);
    Jogador jogadores[qtdjogadores];
    for(int i = 0; i<qtdjogadores; i++){
        //cadastrar jogadores, inicializa pontuacao como 0 e casa como head
    }
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

    //ordenacao dos jogadores

    printf("A ordem dos jogadores ficou:\n");
    for(int i=0; i<qtdjogadores; i++){
        printf("%dº - %s\n", i, jogadores[i].nome);
    }
    printf("Jogador %s, pressione Enter para iniciar o jogo", jogadores[0].nome);
    scanf("%c", &enter);
    //rodando o jogo
    for(int i=0; i<rounds; i++){
        
    }
    return 0;
}
