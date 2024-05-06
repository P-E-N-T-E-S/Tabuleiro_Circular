//
// Created by Evaldo Cunha Filho on 30/04/24.
//

#ifndef TABULEIRO_TABULEIRO_H
#define TABULEIRO_TABULEIRO_H

#include <stdio.h>

typedef struct Pergunta{

    char questao[100];
    char tipo[20];
    char respostaA[20];
    char respostaB[20];
    char respostaC[20];
    char respostaD[20];
    char respostaCerta[1];
    int ponto;

}Pergunta;

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
    int pontuacao;
    Casa *posicao;
}Jogador;

// Funções do Tabuleiro
void regredir(Jogador *jogador, int posicoes);
void incluir(Casa **head, Casa **tail, Pergunta *pergunta, int posicao, int tipo, int acao, int ida);
void avancar(Jogador *jogador, int posicoes);

//Funções da pontuação
void perguntasInitF(Pergunta pergunta1[], FILE *arquivo, int qtd);
int qtdPerguntas(FILE *arquivo);
void embaralharPerguntas(Pergunta pergunta[], int qtd);

#endif //TABULEIRO_TABULEIRO_H

