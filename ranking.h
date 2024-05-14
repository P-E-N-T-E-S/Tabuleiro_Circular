//
// Created by Evaldo Cunha Filho on 14/05/24.
//

#ifndef TABULEIRO_RANKING_H
#define TABULEIRO_RANKING_H

#include <stdio.h>
#include "perguntas.h"
#include "tabuleiro.h"

void troca(Jogador *a,Jogador *b);;
void imprimirJogadores(Jogador *jogadores, int tamanho);
void cadastrarJogadores(Jogador *jogadores, Casa *head, int tamanho);
void iniciativaJogadores(Jogador *jogadores, int tamanho);
void classificarJogadores(Jogador *jogadores, int tamanho);
int existencia(const char *fname);
void regras();
void escVencedor(FILE arquivo);


#endif //TABULEIRO_RANKING_H
