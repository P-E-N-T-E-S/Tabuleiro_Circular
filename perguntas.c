//
// Created by andre on 30/04/2024.
//

#include "tabuleiro.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

#define TRUE 1
#define FALSE 0


void perguntasInitF(Pergunta pergunta1[], FILE *arquivo, int qtd){
    for (int i = 0; i < qtd; ++i) {
            fscanf(arquivo, "%[^\n]%s\n\n%s\n%s\n%s\n%s\n%s\n%d\n",pergunta1[i].questao,pergunta1[i].tipo, pergunta1[i].respostaA, pergunta1[i].respostaB, pergunta1[i].respostaC,pergunta1[i].respostaD, pergunta1[i].respostaCerta, &pergunta1[i].ponto);

    }

    for (int i = 0; i < qtd; ++i) {
        printf( "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n", pergunta1[i].questao,pergunta1[i].tipo, pergunta1[i].respostaA, pergunta1[i].respostaB, pergunta1[i].respostaC,pergunta1[i].respostaD, pergunta1[i].respostaCerta, pergunta1[i].ponto);
    }

    for (int i = 0; i < qtd; ++i) {
        embaralharPerguntas(pergunta1, qtd);
    }

    for (int i = 0; i < qtd; ++i) {
        printf( "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n", pergunta1[i].questao,pergunta1[i].tipo, pergunta1[i].respostaA, pergunta1[i].respostaB, pergunta1[i].respostaC,pergunta1[i].respostaD, pergunta1[i].respostaCerta, pergunta1[i].ponto);
    }
}

int qtdPerguntas(FILE *dados) {
    int linhas = 0;
    char ch;

    while ((ch = fgetc(dados)) != EOF) {
        if (ch == '\n') {
            linhas++;
        }
    }

    linhas++;
    linhas = linhas/8;
    return linhas;
}

void embaralharPerguntas(Pergunta pergunta[], int qtd){
    struct Pergunta pergunta1;

    srand((unsigned) time(NULL));
    for (int i = 0; i < qtd; ++i) {
        int indice = rand() % qtd;
            pergunta1 = pergunta[i];
            pergunta[i] = pergunta[indice];
            pergunta[indice] = pergunta1;
        }
    }