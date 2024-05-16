//
// Created by andre on 07/05/24.
//

#ifndef TABULEIRO_PERGUNTAS_H
#define TABULEIRO_PERGUNTAS_H

typedef struct Pergunta{

    char questao[250];
    char tipo[20];
    char respostaA[50];
    char respostaB[50];
    char respostaC[50];
    char respostaD[50];
    char respostaCerta[1];
    int ponto;

}Pergunta;

Pergunta *perguntasInitF(Pergunta *pergunta1, int qtd);
Pergunta *perguntasInitM(Pergunta *pergunta1, int qtd);
Pergunta *perguntasInitD(Pergunta *pergunta1, int qtd);
void embaralharPerguntas(Pergunta pergunta1[], int qtd);
int qtdPerguntas(FILE *dados);

#endif //TABULEIRO_PERGUNTAS_H
