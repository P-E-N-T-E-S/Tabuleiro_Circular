//
// Created by Evaldo Cunha Filho on 30/04/24.
//

#ifndef TABULEIRO_TABULEIRO_H
#define TABULEIRO_TABULEIRO_H

#include <stdio.h>
#include "perguntas.h"

typedef struct Casa{
    Pergunta *pergunta;
    int posicao;
    int tipo;
    int acao; //casas a avancar ou regredir
    int ida;
    struct Casa *next;
    struct Casa *prev;
}Casa;

typedef struct Jogador{
    char *nome;
    int dadoposicao;
    int pontuacao;
    int id;
    Casa *posicao;
    int posicaoInicial;
}Jogador;
void regredir(Jogador *jogador, int posicoes);
void incluir(Casa **head, Casa **tail, Pergunta *pergunta, int posicao, int tipo, int acao, int ida);
void avancar(Jogador *jogador, int posicoes);
int D6();
void finalizarJogo(Jogador *jogadores, int rounds, int qtdjogadores);
void inicializarTabuleiro(Casa **head, Casa **tail, Pergunta facil[], Pergunta media[], Pergunta dificil[]);
void esperar();


#endif //TABULEIRO_TABULEIRO_H


