//
// Created by Evaldo Cunha Filho on 30/04/24.
//
#include "tabuleiro.h"
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

//se o tipo é TRUE, a casa é de pergunta
//se a ida é um TRUE, é para avancar



void regredir(Jogador *jogador, int posicoes);
void incluir(Casa **head, Casa **tail, Pergunta *pergunta, int posicao, int tipo, int acao, int ida);
void avancar(Jogador *jogador, int posicoes);

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
    if(jogador->posicao->tipo == TRUE){
        jogador->pontuacao += pergunta(jogador, jogador->posicao);
    }else{
        if(jogador->posicao->ida == TRUE){
            avancar(jogador, jogador->posicao->acao);
        }else{
            regredir(jogador, posicoes);
        }
    }
}

void regredir(Jogador *jogador, int posicoes){
    for(int i=0; i<posicoes; i++){
        jogador->posicao = jogador->posicao->prev;
    }
    if(jogador->posicao->tipo == TRUE){
        jogador->pontuacao += pergunta(jogador, jogador->posicao);
    }else{
        if(jogador->posicao->ida == TRUE){
            avancar(jogador, jogador->posicao->acao);
        }else{
            regredir(jogador, posicoes);
        }
    }
}

int pergunta(Jogador *jogador, Casa *casa){
    Pergunta pergunta = casa->pergunta;
}