//
// Created by Evaldo Cunha Filho on 30/04/24.
//
#include "tabuleiro.h"
#include "perguntas.h"
#include "ranking.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TAMANHOTABULEIRO 30
#define ANSI_COLOR_RED     	"\x1b[31m" //cores em ANSI utilizadas
#define ANSI_COLOR_GREEN	"\e[0;32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//se o tipo é 0, a casa é de pergunta, se é 1 a casa é de avancar e se é 2 é a casa de ganhar pontos
//se a ida é um TRUE, é para avancar, se for FALSE é regredir
//se a casa for de acao o acao é quantas casas ela vai avancar/regredir, se for de ganhar pontos é quantos pontos eles ganham





void regredir(Jogador *jogador, int posicoes);
void incluir(Casa **head, Casa **tail, Pergunta pergunta[], int posicao, int tipo, int acao, int ida);
void avancar(Jogador *jogador, int posicoes);
void inicializarTabuleiro(Casa **head, Casa **tail, Pergunta facil[], Pergunta media[], Pergunta dificil[]);
void pousar(Jogador *jogador);
int D6();
void esperar();

void incluir(Casa **head, Casa **tail, Pergunta *pergunta, int posicao, int tipo, int acao, int ida){
    Casa *nova = (Casa *)malloc(sizeof(Casa));
    nova->posicao = posicao;
    nova->tipo = tipo;
    nova->acao = acao;
    nova->pergunta = pergunta;
    nova->ida = ida;
    if(*head == NULL){
        nova->next = nova;
        nova->prev = nova;
        (*head) = nova;
        (*tail) = nova;
    }else{
        (*tail)->next = nova;
        nova->prev = (*tail);
        nova->next = (*head);
        (*tail) = nova;
        (*head)->prev = nova;
    }
}

void avancar(Jogador *jogador, int posicoes){
    for(int i=0; i<posicoes; i++){
        jogador->posicao = jogador->posicao->next;
    }
    pousar(jogador);
}

void regredir(Jogador *jogador, int posicoes){
    for(int i=0; i<posicoes; i++){
        jogador->posicao = jogador->posicao->prev;
    }
    pousar(jogador);
}

void inicializarTabuleiro(Casa **head, Casa **tail, Pergunta facil[], Pergunta media[], Pergunta dificil[]){
    int j=0, k=0, f=0,m=0,d=0;
    int idaarray[] = {1, 1, 0, 0, 1, 1};
    int acaoarray[] = {3, 2, 2, 3, 1, 2};
    int pergunta[] = {3,1,2,3,1,2,3,2,2,3,2,1,1,3,3,2,1,2,3,2,1,1};
    for(int i=0; i < TAMANHOTABULEIRO; i++){
        if(i == 0){
            incluir(head, tail, NULL, i, 2, 3, 0);
        }else if(i == 1 || i == 8 || i == 12 || i == 19 || i == 24 || i == 26){
            incluir(head, tail, NULL, i, 1, acaoarray[j], idaarray[j]);
            j++;
        }else{
            switch (pergunta[k]) {
                case 1:
                    incluir(head, tail, &facil[f], i, 0, 1, 0);
                    f++;
                    break;
                case 2:
                    incluir(head, tail, &media[m], i, 0, 1, 0);
                    m++;
                    break;
                case 3:
                    incluir(head, tail, &dificil[m], i, 0, 1, 0);
                    d++;
                    break;
            }
            k++;
        }
    }
}

void pergunta(Jogador *jogador, Casa *casa){
    Pergunta *pergunta = casa->pergunta;
    char aceitar, resposta, espera;
    switch (pergunta->ponto) {
        case 1:
            printf("voce caiu em uma casa com uma pergunta facil\n");
            printf("pergunta do tipo: %s\n", pergunta->tipo);
            break;
        case 2:
            printf("voce caiu em uma casa com uma pergunta media\n");
            printf("pergunta do tipo: %s\n", pergunta->tipo);
            break;
        case 3:
            printf("voce caiu em uma casa com uma pergunta dificil, alto risco e alta recompensa\n");
            printf("pergunta do tipo: %s\n", pergunta->tipo);
            break;
        default:
            exit(1);
    }
    printf("voce deseja responder a pergunta?[y/n]\n");
    scanf("%c", &aceitar);
    scanf("%c", &espera);
    system("clear");
    if(aceitar == 'y'){
        printf("%s\n%s\n%s\n%s\n%s\n", pergunta->questao, pergunta->respostaA, pergunta->respostaB, pergunta->respostaC, pergunta->respostaD);
        printf("Sua resposta: ");
        scanf("%c", &resposta);
        if(resposta == pergunta->respostaCerta[0] || resposta == pergunta->respostaCerta[0]-32){
            printf(ANSI_COLOR_GREEN "Resposta correta!\n" ANSI_COLOR_RESET);
            printf("\nVoce ganhou %d pontos!\n", pergunta->ponto);
            jogador->pontuacao += pergunta->ponto;
            esperar();
            system("clear");
        }else{
            printf(ANSI_COLOR_RED "Resposta errada!\n" ANSI_COLOR_RESET);
            printf("\nVoce perdeu %d pontos!\n", pergunta->ponto);
            jogador->pontuacao -= pergunta->ponto;
            esperar();
            system("clear");
        }
    }

}

int D6(){
    srand((unsigned) time(NULL));
    return (rand() % 6 + 1);
}

void pousar(Jogador *jogador){
    if(jogador->posicao->tipo == 0){
        pergunta(jogador, jogador->posicao);
    }else if(jogador->posicao->tipo == 1){
        if(jogador->posicao->ida == 1){
            printf(ANSI_COLOR_GREEN "Voce caiu em uma casa de avanco, e vai avancar %d passos!\n" ANSI_COLOR_RESET, jogador->posicao->acao);
            printf("Andando %d passos...\n", jogador->posicao->acao);
            system("clear");
            avancar(jogador, jogador->posicao->acao);
        }else{
            printf(ANSI_COLOR_RED "Voce caiu em uma casa de regresso, e vai voltar %d passos!\n" ANSI_COLOR_RESET, jogador->posicao->acao);
            printf("Voltando %d passos...\n", jogador->posicao->acao);
            regredir(jogador, jogador->posicao->acao);
        }
    }else{
        printf(ANSI_COLOR_GREEN "Voce ganhou 3 pontos por passar no inicio!" ANSI_COLOR_RESET);
        jogador->pontuacao += jogador->posicao->acao;
        esperar();
    }
}

void esperar(){
    char enter;
    printf("Pressione qualquer tecla para continuar...");
    scanf("%c", &enter);
}

void finalizarJogo(Jogador *jogadores, int rounds, int qtdjogadores){
    classificarJogadores(jogadores, qtdjogadores);
    printf(ANSI_COLOR_GREEN "\n------Fim do jogo------\n" ANSI_COLOR_RESET);
    printf("O grande vencedor e...\n");
    printf("Parabens %s, voce dominou o Tabuleiro circular com %d pontos\n", jogadores[0].nome, jogadores[0].pontuacao);
    printf("Ranking dos jogadores:\n");
    imprimirJogadores(jogadores, qtdjogadores);
    escVencedor(jogadores[0].nome);
    printf("Pressione Enter para sair...");
    esperar();
}
