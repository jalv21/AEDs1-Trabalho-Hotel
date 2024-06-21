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
  FILE *cliFile, *funFile, *quaFile, *estFile;
  int escolha;
  setlocale(LC_ALL, "portuguese");
  srand(time(NULL));

  if((cliFile = fopen("clientes.dat", "r+b")) == NULL) {
    if((cliFile = fopen("clientes.dat", "w+b")) == NULL) {
      printf("Erro! O arquivo não foi criado!");
      exit(1);
    }
  }

  if((funFile = fopen("funcionarios.dat", "r+b")) == NULL) {
    if((funFile = fopen("funcionarios.dat", "w+b")) == NULL) {
      printf("Erro! O arquivo não foi criado!");
      exit(1);
    }
  }

  if((quaFile = fopen("quartos.dat", "r+b")) == NULL) {
    if((quaFile = fopen("quartos.dat", "w+b")) == NULL) {
      printf("Erro! O arquivo não foi criado!");
      exit(1);
    }
  }

  if((estFile = fopen("estadias.dat", "r+b")) == NULL) {
    if((estFile = fopen("estadias.dat", "w+b")) == NULL) {
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
  printf("5 - Dar baixa em estadia \n");
  printf("6 - Pesquisar cliente ou funcionário \n");
  printf("7 - Mostrar estadias de um cliente \n");
  printf("8 - Ver pontos de fidelidade de um cliente \n");
  printf("9 - SAIR\n\n");

  if (scanf("%i", &escolha) != 1) {
    printf("Erro ao ler a escolha.");
  }
  printf("\n\n");

  while (escolha != 9 && escolha < 9 && escolha > 0) {
    switch (escolha) {
    case 1:
      cadCliente(cliFile);
      break;
    case 2:
      cadFuncionario(funFile);
      break;
    case 3:
      cadQuarto(quaFile);
      break;
    case 4: cadEstadia(estFile, cliFile, quaFile);
      break;
    case 5: baixaEstadia(estFile, cliFile, quaFile);
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
  printf("5 - Dar baixa em estadia \n");
  printf("6 - Pesquisar cliente ou funcionário \n");
  printf("7 - Mostrar estadias de um cliente \n");
  printf("8 - Ver pontos de fidelidade de um cliente \n");
  printf("9 - SAIR\n\n");

  if (scanf("%i", &escolha) != 1) {
    printf("Erro ao ler a escolha.");
  }
  printf("\n\n");
  }
  return 0;
}