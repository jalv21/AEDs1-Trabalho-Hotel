#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <time.h>
#include "Process.h"

int main() {
  setlocale(LC_ALL, "portuguese");
  srand(time(NULL));
  int escolha;

  // Exibição do menu
  printf("=== BEM-VINDO AO HOTEL DESCANSO GARANTIDO === \n\n");
  printf("Menu \n\n");
  printf("1 - Cadastrar um cliente \n");
  printf("2 - Cadastrar um funcionário \n");
  printf("3 - Cadastrar um quarto \n");
  printf("4 - Cadastrar uma estadia \n");
  printf("5 - Pesquisar \n");
  printf("6 - Dar baixa em estadia \n");
  printf("7 - SAIR \n\n");

  // Leitura da escolha
  scanf("%i", &escolha);
  printf("\n\n");

  //loop do menu até escolher "SAIR"
  while(escolha != 7 && escolha < 7 && escolha > 0) {
    switch(escolha) {
      case 1: cadCliente();
        break;
      case 2: cadFuncionario();
        break;
      case 3: cadQuarto();
        break;
      case 4: /*função*/;
        break;
      case 5: /*função*/;
        break;
      case 6: /*função*/;
        break;
    }
    printf("=== BEM-VINDO AO HOTEL DESCANSO GARANTIDO === \n\n");
    printf("Menu \n\n");
    printf("1 - Cadastrar um cliente \n");
    printf("2 - Cadastrar um funcionário \n");
    printf("3 - Cadastrar um quarto \n");
    printf("4 - Cadastrar uma estadia \n");
    printf("5 - Pesquisar \n");
    printf("6 - Dar baixa em estadia \n");
    printf("7 - SAIR \n\n");

    scanf("%i", &escolha);
  }
  return 0;
}