//
// Created by Evaldo Cunha Filho on 30/04/24.
//
#include "tabuleiro.h"
#include "perguntas.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

#define TAMANHOTABULEIRO 30
#define ANSI_COLOR_RED     	"\x1b[31m" //cores em ANSI utilizadas
#define ANSI_COLOR_GRAY    	"\e[0;37m"
#define ANSI_COLOR_DARK_GRAY 	"\e[1;30m"
#define ANSI_COLOR_GREEN	"\e[0;32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//se o tipo é 0, a casa é de pergunta, se é 1 a casa é de avancar e se é 2 é a casa de ganhar pontos
//se a ida é um TRUE, é para avancar, se for FALSE é regredir
//se a casa for de acao o acao é quantas casas ela vai avancar/regredir, se for de ganhar pontos é quantos pontos eles ganham





void regredir(Jogador *jogador, int posicoes);
void incluir(Casa **head, Casa **tail, Pergunta pergunta[], int posicao, int tipo, int acao, int ida);
void avancar(Jogador *jogador, int posicoes);
void inicializarTabuleiro(Casa **head, Casa **tail, Pergunta perguntas[]);
void pousar(Jogador *jogador);
int D6();

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

void inicializarTabuleiro(Casa **head, Casa **tail, Pergunta perguntas[]){
    int j=0, k=0;
    int idaarray[] = {1, 1, 0, 0, 1, 1};
    int acaoarray[] = {3, 2, 2, 3, 1, 2};
    for(int i=0; i < TAMANHOTABULEIRO; i++){
        if(i == 0){
            incluir(head, tail, NULL, i, 2, 3, NULL);
        }else if(i == 1 || i == 8 || i == 12 || i == 19 || i == 24 || i == 26){
            incluir(head, tail, NULL, i, 1, acaoarray[j], idaarray[j]);
            j++;
        }else{
            incluir(head, tail, &perguntas[k], i, 0, NULL, NULL);
            k++;
        }
    }
}

int pergunta(Jogador *jogador, Casa *casa){
    Pergunta *pergunta = casa->pergunta;
    char tipo[10], aceitar, resposta;
    switch (pergunta->ponto) {
        case 1:
            printf("voce caiu em uma casa com uma pergunta facil\n");
            break;
        case 2:
            printf("voce caiu em uma casa com uma pergunta media\n");
            break;
        case 3:
            printf("voce caiu em uma casa com uma pergunta dificil, alto risco e alta recompensa\n");
            break;
        default:
            exit(1);
    }
    printf("voce deseja responder a pergunta?[y/n]\n");
    scanf("%c", &aceitar);
    system("clear||cls");
    if(aceitar == 'y'){
        printf("%s\n", pergunta->questao);
        printf("%s\n", pergunta->respostaA);
        printf("%s\n", pergunta->respostaB);
        printf("%s\n", pergunta->respostaC);
        printf("%s\n", pergunta->respostaD);
        printf("Sua resposta: ");
        scanf("%c", &resposta);
        if(resposta == pergunta->respostaCerta[0]){
            printf(ANSI_COLOR_GREEN "Resposta correta!" ANSI_COLOR_RESET);
            printf("\nVoce ganhou %d pontos!")
        }
    }

}

int D6(){
    srand((unsigned) time(NULL));
    return (rand() % 6 + 1);
}

void pousar(Jogador *jogador){
    if(jogador->posicao->tipo == 0){
        jogador->pontuacao += pergunta(jogador, jogador->posicao);
    }else if(jogador->posicao->tipo == 1){
        if(jogador->posicao->ida == 1){
            avancar(jogador, jogador->posicao->acao);
        }else{
            regredir(jogador, jogador->posicao->acao);
        }
    }else{
        jogador->pontuacao += jogador->posicao->acao;
    }
}