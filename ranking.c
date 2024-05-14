//
// Created by Evaldo Cunha Filho on 14/05/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabuleiro.h"


//Jogador *jogadores = (Jogador*)malloc(tamanho * sizeof(Jogador));

void troca(Jogador *a,Jogador *b){
    Jogador temp = *a;
    *a = *b;
    *b = temp;
}


void classificarJogadores(Jogador *jogadores, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < tamanho; j++) {
            if (jogadores[j].pontuacao > jogadores[max_idx].pontuacao) {
                max_idx = j;
            }else if(jogadores[j].dadoposicao == jogadores[max_idx].dadoposicao) {
                if (strcmp(jogadores[j].nome, jogadores[max_idx].nome) < 0) {
                    max_idx = j;
                }
            }
        }
        if(max_idx != i){
            troca(&jogadores[max_idx], &jogadores[i]);
        }
    }
}

void imprimirJogadores(Jogador *jogadores, int tamanho) {
    printf("Jogadores:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Nome: %s | Pontuacao: %d\n", jogadores[i].nome, jogadores[i].pontuacao);
    }
}

void cadastrarJogadores(Jogador *jogadores, Casa *head, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("Cadastro do Jogador %d:\n", i + 1);

        jogadores[i].nome = (char*)malloc(50 * sizeof(char));

        printf("Nome: ");
        scanf("%s", jogadores[i].nome);
        jogadores[i].id = i;
        jogadores[i].pontuacao = 0;
        jogadores[i].dadoposicao = 0;
        jogadores[i].posicao = head;
    }
}

void iniciativaJogadores(Jogador *jogadores, int tamanho) { //selection sort
    for (int i = 0; i < tamanho - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < tamanho; j++) {
            if (jogadores[j].dadoposicao > jogadores[max_idx].dadoposicao) {
                max_idx = j;
            } else if (jogadores[j].dadoposicao == jogadores[max_idx].dadoposicao) {
                if (strcmp(jogadores[j].nome, jogadores[max_idx].nome) < 0) {
                    max_idx = j;
                }
            }
        }

        if (max_idx != i) {
            troca(&jogadores[max_idx], &jogadores[i]);
        }
    }
}