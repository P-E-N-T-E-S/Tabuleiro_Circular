//
// Created by andre on 07/05/24.
//

#ifndef TABULEIRO_PERGUNTAS_H
#define TABULEIRO_PERGUNTAS_H

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

Pergunta * perguntasInitF(Pergunta *pergunta1, int qtd);
Pergunta *perguntasInitM(Pergunta *pergunta1, int qtd);
Pergunta *perguntasInitD(Pergunta *pergunta1, int qtd);
int qtdPerguntas(FILE *dados);
void embaralharPerguntas(Pergunta pergunta1[], int qtd);

#endif //TABULEIRO_PERGUNTAS_H
