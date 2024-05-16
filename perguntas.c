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

int qtdPerguntas(FILE *dados);

//Essa função lê as perguntas de nível fácil arquivo 'facil.txt', aloca a memória necessária, e atribui o valor devido a variável 
//apropriada. Logo após chama a função de Shuffle com o objetivo de aleatoriezar a ordem das perguntas para tornar cada jogo unico
Pergunta *perguntasInitF(Pergunta *pergunta1, int qtd){
    pergunta1 = (Pergunta *)malloc(qtd * sizeof(Pergunta)); //Alocando memória
    FILE *facila = fopen("facil.txt", "r"); //Abrindo o arquivo

    for (int i = 0; i < qtd; ++i) {   //Atribuindo valores
        fscanf(facila, "%[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %d\n",pergunta1[i].questao,pergunta1[i].tipo, pergunta1[i].respostaA, pergunta1[i].respostaB, pergunta1[i].respostaC,pergunta1[i].respostaD, pergunta1[i].respostaCerta, &pergunta1[i].ponto);
    }

    fclose(facila);

    embaralharPerguntas(pergunta1, qtd); //Realiza a troca dos endereços das perguntas
    return pergunta1;
}

//Essa função lê as perguntas de nível medio arquivo 'medio.txt', aloca a memória necessária, e atribui o valor devido a variável 
//apropriada. Logo após chama a função de Shuffle com o objetivo de aleatoriezar a ordem das perguntas para tornar cada jogo unico
Pergunta *perguntasInitM(Pergunta *pergunta1, int qtd){
    pergunta1 = (Pergunta *)malloc(qtd * sizeof(Pergunta)); //Alocando memória
    FILE *facila = fopen("medio.txt", "r"); //Abrindo arquivo

    for (int i = 0; i < qtd; ++i) { //Atribuindo valores
        fscanf(facila, "%[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %d\n",pergunta1[i].questao,pergunta1[i].tipo, pergunta1[i].respostaA, pergunta1[i].respostaB, pergunta1[i].respostaC,pergunta1[i].respostaD, pergunta1[i].respostaCerta, &pergunta1[i].ponto);
    }

    fclose(facila);

    embaralharPerguntas(pergunta1, qtd); //Realiza a troca dos endereços das perguntas
    return pergunta1;
}

//Essa função lê as perguntas de nível dificil arquivo 'dificil.txt', aloca a memória necessária, e atribui o valor devido a variável 
//apropriada. Logo após chama a função de Shuffle com o objetivo de aleatoriezar a ordem das perguntas para tornar cada jogo unico
Pergunta *perguntasInitD(Pergunta *pergunta1, int qtd){
    pergunta1 = (Pergunta *)malloc(qtd * sizeof(Pergunta)); //Alocando Memoria
    FILE *facila = fopen("dificil.txt", "r");   //Abrindo arquivo

    for (int i = 0; i < qtd; ++i) {//Atribuindo os valores
        fscanf(facila, "%[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %[^\n] %d\n",pergunta1[i].questao,pergunta1[i].tipo, pergunta1[i].respostaA, pergunta1[i].respostaB, pergunta1[i].respostaC,pergunta1[i].respostaD, pergunta1[i].respostaCerta, &pergunta1[i].ponto);
    }

    fclose(facila);

    embaralharPerguntas(pergunta1, qtd); //Realiza a troca dos endereços das perguntas
    return pergunta1;
}

//A função qtdPerguntas lê um arquivo e verifica a quantidade de perguntas para utiliza-las na alocação de memória das Inits
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

//A função de embaralhar pergunta faz um 'Shuffle' com uma seed aleatória para garantir que cada jogo seja unico.
void embaralharPerguntas(Pergunta pergunta[], int qtd) {
    srand((unsigned)time(NULL)); //Seta uma seed aleatória
    for (int i = qtd - 1; i > 0; --i) {
        int indice = rand() % i; //Gera um valor aleatório usando a seed previamente setada
        if (indice != i) {
            Pergunta temp = pergunta[i];        //
            pergunta[i] = pergunta[indice];     // Troca da ordem
            pergunta[indice] = temp;            //
        }
    }
}