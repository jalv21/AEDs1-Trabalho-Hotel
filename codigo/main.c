/*  
Este é o arquivo "main.c"

Descrição: Este é o arquivo principal do código do projeto na linguagem C, ele é responsável por exibir o menu e executar as funções da biblioteca criada para realizar as operações necessárias.

Funções: 
int main()

Autor: J
Data de início: 14 Jun. 2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <stdbool.h>
#include "Process.h"

int main() {
  FILE *f;
  int escolha;
  setlocale(LC_ALL, "portuguese");
  srand(time(NULL));

  if((f = fopen("teste.dat", "r+b")) == NULL) {
    if((f = fopen("teste.dat", "w+b")) == NULL) {
      printf("Erro! O arquivo não foi criado!");
      exit(1);
    }
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

  if (scanf("%i", &escolha) != 1) {
    printf("Erro ao ler a escolha.");
  }
  printf("\n\n");

  while (escolha != 7 && escolha < 7 && escolha > 0) {
    switch (escolha) {
    case 1:
      cadCliente(f);
      break;
    case 2:
      cadFuncionario();
      break;
    case 3:
      cadQuarto();
      break;
    case 4: cadEstadia();
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

  if (scanf("%i", &escolha) != 1) {
    printf("Erro ao ler a escolha.");
  }
  printf("\n\n");
  }
  return 0;
}