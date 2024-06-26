//
// Created by Evaldo Cunha Filho on 30/04/24.
//
#include "tabuleiro.h"
#include "perguntas.h"
#include "ranking.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define TAMANHOTABULEIRO 30
#define ANSI_COLOR_RED     	"\x1b[31m" //cores em ANSI utilizadas
#define ANSI_COLOR_GREEN	"\e[0;32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//se o tipo é 0, a casa é de pergunta, se é 1 a casa é de avancar e se é 2 é a casa de ganhar pontos
//se a ida é um TRUE, é para avancar, se for FALSE é regredir
//se a casa for de acao o acao é quantas casas ela vai avancar/regredir, se for de ganhar pontos é quantos pontos eles ganham





void regredir(Jogador *jogador, int posicoes);
void incluir(Casa **head, Casa **tail, Pergunta pergunta[], int posicao, int tipo, int acao, int ida);
void avancar(Jogador *jogador, int posicoes);
void inicializarTabuleiro(Casa **head, Casa **tail, Pergunta facil[], Pergunta media[], Pergunta dificil[]);
void pousar(Jogador *jogador);
int D6();
void esperar();

void incluir(Casa **head, Casa **tail, Pergunta *pergunta, int posicao, int tipo, int acao, int ida){
    /*
     * Função para incluir novos nós na lista circular duplamente encadeada, ela pode receber alguns desses parâmetros como nulo ou zero,
     * de acordo com o tipo da casa
     */
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
        (*head)->prev = nova;
    }
}

void avancar(Jogador *jogador, int posicoes){
    /*
     *Função para avancar um jogador em um numero de casas passados como parâmetro, ele anda no sentido horário da lista circular
     */
    for(int i=0; i<posicoes; i++){
        jogador->posicao = jogador->posicao->next;
    }
    pousar(jogador);
}

void regredir(Jogador *jogador, int posicoes){
    /*
    *Função para voltar um jogador em um numero de casas passados como parâmetro, ele anda no sentido anti-horário da lista circular
    */
    for(int i=0; i<posicoes; i++){
        jogador->posicao = jogador->posicao->prev;
    }
    pousar(jogador);
}

void inicializarTabuleiro(Casa **head, Casa **tail, Pergunta facil[], Pergunta media[], Pergunta dificil[]){
    /*
     * Função para criar o tabuleiro circular, ele ja tem definido qual cada tipo de casa nos arrays e nos ifs, ele chama varias vezes a função incluir
     * passando os parametros de acordo com cada tipo de casa
     */
    int j=0, k=0, f=0,m=0,d=0;
    int idaarray[] = {1, 1, 0, 0, 1, 1};
    int acaoarray[] = {3, 2, 2, 3, 1, 2};
    int pergunta[] = {3,1,2,3,1,2,3,2,2,3,2,1,1,3,3,2,1,2,3,2,1,1};
    for(int i=0; i < TAMANHOTABULEIRO; i++){
        if(i == 0){
            incluir(head, tail, NULL, i+1, 2, 3, 0);
        }else if(i == 1 || i == 8 || i == 12 || i == 19 || i == 24 || i == 26){
            incluir(head, tail, NULL, i+1, 1, acaoarray[j], idaarray[j]);
            j++;
        }else{
            switch (pergunta[k]) {
                case 1:
                    incluir(head, tail, &facil[f], i+1, 0, 1, 0);
                    f++;
                    break;
                case 2:
                    incluir(head, tail, &media[m], i+1, 0, 1, 0);
                    m++;
                    break;
                case 3:
                    incluir(head, tail, &dificil[m], i+1, 0, 1, 0);
                    d++;
                    break;
            }
            k++;
        }
    }
}

void pergunta(Jogador *jogador, Casa *casa){
    /*
     * Função que faz ao jogador a pergunta referente a casa em que ele está, verifica qual o nivel da pergunta e associa a pontuacao correta ao jogador
     * tambem permite que ele possa escolher nao responder a pergunta
     */
    Pergunta *pergunta = casa->pergunta;
    char aceitar, resposta, espera, dump;
    switch (pergunta->ponto) {
        case 1:
            printf("voce caiu em uma casa com uma pergunta facil\n");
            printf("pergunta do tipo: %s\n", pergunta->tipo);
            break;
        case 2:
            printf("voce caiu em uma casa com uma pergunta media\n");
            printf("pergunta do tipo: %s\n", pergunta->tipo);
            break;
        case 3:
            printf("voce caiu em uma casa com uma pergunta dificil, alto risco e alta recompensa\n");
            printf("pergunta do tipo: %s\n", pergunta->tipo);
            break;
        default:
            exit(1);
    }
    printf("voce deseja responder a pergunta?[y/n]\n");
    scanf("%c", &aceitar);
    scanf("%c", &espera);
    system("clear");
    if(aceitar == 'y'){
        printf("%s\n%s\n%s\n%s\n%s\n", pergunta->questao, pergunta->respostaA, pergunta->respostaB, pergunta->respostaC, pergunta->respostaD);
        printf("Sua resposta: ");
        scanf("%c", &resposta);
        if(resposta == pergunta->respostaCerta[0] || resposta == pergunta->respostaCerta[0]-32){
            printf(ANSI_COLOR_GREEN "Resposta correta!\n" ANSI_COLOR_RESET);
            printf("\nVoce ganhou %d pontos!\n", pergunta->ponto);
            jogador->pontuacao += pergunta->ponto;
            sleep(2);
            scanf("%c", &dump);
            system("clear");
        }else{
            printf(ANSI_COLOR_RED "Resposta errada!\n" ANSI_COLOR_RESET);
            printf("A resposta correta e: %c", pergunta->respostaCerta[0]);
            printf("\nVoce perdeu %d pontos!\n", pergunta->ponto);
            jogador->pontuacao -= pergunta->ponto;
            sleep(2);
            scanf("%c", &dump);
            system("clear");
        }
    }

}

int D6(){
    /*
     * Função que imita um dado de 6 lados usando a função random
     */
    srand((unsigned) time(NULL));
    int resultado = (rand() % 6 + 1);
    return resultado;
}

void pousar(Jogador *jogador){
    /*
     * Função para fazer com que o jogador execute a ação das casas ao aterrisar nelas, essa funcao anuncia a ação e executa a sua devida função
     */
    if(jogador->posicao->tipo == 0){
        pergunta(jogador, jogador->posicao);
    }else if(jogador->posicao->tipo == 1){
        if(jogador->posicao->ida == 1){
            printf(ANSI_COLOR_GREEN "Voce caiu em uma casa de avanco, e vai avancar %d passos!\n" ANSI_COLOR_RESET, jogador->posicao->acao);
            printf("Andando %d passos...\n", jogador->posicao->acao);
            sleep(2);
            system("clear");
            avancar(jogador, jogador->posicao->acao);
        }else{
            printf(ANSI_COLOR_RED "Voce caiu em uma casa de regresso, e vai voltar %d passos!\n" ANSI_COLOR_RESET, jogador->posicao->acao);
            printf("Voltando %d passos...\n", jogador->posicao->acao);
            sleep(2);
            system("clear");
            regredir(jogador, jogador->posicao->acao);
        }
    }else{
        printf(ANSI_COLOR_GREEN "Voce ganhou 3 pontos por passar no inicio!" ANSI_COLOR_RESET);
        jogador->pontuacao += jogador->posicao->acao;
        esperar();
    }
}

void esperar(){
    /*
     * Função para esperar uma tecla do usuário para seguir o fluxo
     */
    char enter;
    printf("Pressione qualquer tecla para continuar...\n");
    scanf("%c", &enter);
}

void finalizarJogo(Jogador *jogadores, int qtdjogadores){
    /*
     * Função executada no fim dos rounds definidos pelos jogadores ela mostra o ranking dos jogadores e salva o vencedor em um arquivo
     */
    classificarJogadores(jogadores, qtdjogadores);
    printf(ANSI_COLOR_GREEN "\n------Fim do jogo------\n" ANSI_COLOR_RESET);
    printf("O grande vencedor e...\n");
    printf("Parabens %s, voce dominou o Tabuleiro circular com %d pontos\n", jogadores[0].nome, jogadores[0].pontuacao);
    printf("Ranking dos jogadores:\n");
    imprimirJogadores(jogadores, qtdjogadores);
    escVencedor(jogadores[0].nome);
    printf("Pressione Enter para sair...");
    esperar();
}
