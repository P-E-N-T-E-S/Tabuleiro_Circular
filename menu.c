#include <stdio.h>
#include "ranking.h"
#include "tabuleiro.h"

int main(){
  int qnt_players, i = 0;
  printf("Bem vindo ao TABULEIRO CIRCULAR");
  printf("Quantos jogadores vão jogar?");
  scanf("%d", &qnt_players);
  Jogador *jogadores = (Jogador*)malloc(qnt_players * sizeof(Jogador));
  while(qnt_players != i){
    cadastrarJogadores(jogadores, qnt_players);
  }
}
