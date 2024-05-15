//
// Created by andre on 30/04/2024.
//

#include "tabuleiro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

Pergunta *perguntasInitF(Pergunta *pergunta1, int qtd){
    pergunta1 = (Pergunta *)malloc(qtd * sizeof(Pergunta));
    FILE *facila = fopen("facil.txt", "r");

    for (int i = 0; i < qtd; ++i) {
        fscanf(facila, "%[^\n]%s\n\n%s\n%s\n%s\n%s\n%s\n%d\n",pergunta1[i].questao,pergunta1[i].tipo, pergunta1[i].respostaA, pergunta1[i].respostaB, pergunta1[i].respostaC,pergunta1[i].respostaD, pergunta1[i].respostaCerta, &pergunta1[i].ponto);
    }

    fclose(facila);

    srand((unsigned)time(NULL));
    for (int i = qtd - 1; i > 0; --i) {
        int indice = rand() % i;
        if (indice != i) {
            Pergunta temp = pergunta1[i];
            pergunta1[i] = pergunta1[indice];
            pergunta1[indice] = temp;
        }
    }
    return pergunta1;
}


Pergunta *perguntasInitM(Pergunta *pergunta1, int qtd){
    pergunta1 = (Pergunta *)malloc(qtd * sizeof(Pergunta));
    FILE *facila = fopen("medio.txt", "r");

    for (int i = 0; i < qtd; ++i) {
        fscanf(facila, "%[^\n]%s\n\n%s\n%s\n%s\n%s\n%s\n%d\n",pergunta1[i].questao,pergunta1[i].tipo, pergunta1[i].respostaA, pergunta1[i].respostaB, pergunta1[i].respostaC,pergunta1[i].respostaD, pergunta1[i].respostaCerta, &pergunta1[i].ponto);
    }

    fclose(facila);

    srand((unsigned)time(NULL));
    for (int i = qtd - 1; i > 0; --i) {
        int indice = rand() % i;
        if (indice != i) {
            Pergunta temp = pergunta1[i];
            pergunta1[i] = pergunta1[indice];
            pergunta1[indice] = temp;
        }
    }
    return pergunta1;
}


Pergunta *perguntasInitD(Pergunta *pergunta1, int qtd){
    pergunta1 = (Pergunta *)malloc(qtd * sizeof(Pergunta));
    FILE *facila = fopen("dificil.txt", "r");

    for (int i = 0; i < qtd; ++i) {
        fscanf(facila, "%[^\n]%s\n\n%s\n%s\n%s\n%s\n%s\n%d\n",pergunta1[i].questao,pergunta1[i].tipo, pergunta1[i].respostaA, pergunta1[i].respostaB, pergunta1[i].respostaC,pergunta1[i].respostaD, pergunta1[i].respostaCerta, &pergunta1[i].ponto);
    }

    fclose(facila);

    srand((unsigned)time(NULL));
    for (int i = qtd - 1; i > 0; --i) {
        int indice = rand() % i;
        if (indice != i) {
            Pergunta temp = pergunta1[i];
            pergunta1[i] = pergunta1[indice];
            pergunta1[indice] = temp;
        }
    }
    return pergunta1;
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

void embaralharPerguntas(Pergunta pergunta[], int qtd) {
    srand((unsigned)time(NULL));
    for (int i = qtd - 1; i > 0; --i) {
        int indice = rand() % i;
        if (indice != i) {
            Pergunta temp = pergunta[i];
            pergunta[i] = pergunta[indice];
            pergunta[indice] = temp;
        }
    }
}